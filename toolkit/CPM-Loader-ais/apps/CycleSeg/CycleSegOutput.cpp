#include <ais/task/Task.h>
#include <ais/log/Logger.h>

#include <interfaces/CycleSeg/TxInterface.hpp>
#include <interfaces/VP3Record/VP3RecMgr.h>

#ifdef __cplusplus
extern "C" {
#endif
#include <LIBINFO_WL_if.h>

#ifdef __cplusplus
}
#endif

#include "CycleSegOutput.h"

// VP3 Record UIDs
char UID_SegmentId[]                  = {RECORD_ID,  RECORD_SIZE, SEGMENT_ID, UID_ID::ID_DEFAULT,UID_SIZE::ONEBYTE,UID_DataType::UNSIGNED_8, UID_COLOR::CYCLE_TIMER, DATASOURCE_STANDALONE};
char UID_SegmentTime_Start[]          = {RECORD_ID,  RECORD_SIZE, TIMESTAMP_STARTIME,UID_ID::SEGMENT_TIME_START, UID_SIZE::TENBYTE,UID_DataType::UIDTIMESTAMP,UID_COLOR::PAYLOD_CYCLE, DATASOURCE_STANDALONE};
char UID_SegmentDuration[]            = {RECORD_ID,  RECORD_SIZE, SEGMENT_DURATION,UID_ID::ID_DEFAULT, UID_SIZE::FOURBYTE,UID_DataType::SIGNED_32_FLOAT,UID_COLOR::COLOR_DEFAULT, DATASOURCE_STANDALONE};
char UID_SegmentFuelConsumed[]        = {RECORD_ID,  RECORD_SIZE, FUEL_CONSUMED,UID_ID::ID_DEFAULT, UID_SIZE::FOURBYTE,UID_DataType::SIGNED_32_FLOAT,UID_COLOR::COLOR_DEFAULT, DATASOURCE_STANDALONE};
char UID_SegmentDistanceTravelled[]   = {RECORD_ID,  RECORD_SIZE, DISTANCE_TRAVELLED, UID_ID::ID_DEFAULT, UID_SIZE::FOURBYTE, UID_DataType::SIGNED_32_FLOAT,UID_COLOR::COLOR_DEFAULT,DATASOURCE_STANDALONE};
char UID_MachineIdleDuration[]        = {RECORD_ID,  RECORD_SIZE, SEGMENT_DURATION, UID_ID::MACHINE_IDLE_DURATION, UID_SIZE::FOURBYTE, UID_DataType::SIGNED_32_FLOAT, UID_COLOR::COLOR_DEFAULT, DATASOURCE_STANDALONE};
char UID_PayloadWeight[]              = {RECORD_ID,  RECORD_SIZE, PAYLOAD_WEIGHT, UID_ID::ID_DEFAULT, UID_SIZE::FOURBYTE, UID_DataType::SIGNED_32_FLOAT, UID_COLOR::COLOR_DEFAULT, DATASOURCE_STANDALONE};
char UID_PayloadCalculationMethod[]   = {RECORD_ID,  RECORD_SIZE, PAYLOAD_CALCULATION_METHOD, UID_ID::ID_DEFAULT, UID_SIZE::TWOBYTE, UID_DataType::UNSIGNED_16, UID_COLOR::COLOR_DEFAULT, DATASOURCE_STANDALONE};


static void copy_inputs_and_outputs(CycleSegTxInterface& data);

CycleSegOutput::CycleSegOutput() :
    vp3RecordOutputChannel_(nullptr),
    txOutputChannel_(nullptr) {
}

bool CycleSegOutput::initialize() {
    bool everythingOk = true;

    // Initialize output channels
    if (!task::InterfaceDb::bind("VP3RecordOutput", vp3RecordOutputChannel_)) {
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("TxOutput", txOutputChannel_)) {
        everythingOk = false;
    }

    // Initialize the VP3 record buffer pool.
    constexpr uint16_t numberVp3OBufferObjectInstances = 10;
    if (!VP3RecMgr::getInstance()->Vp3RecBufferinit(numberVp3OBufferObjectInstances)) {
        everythingOk = false;
    }

    return everythingOk;
}

void CycleSegOutput::update(bool skipVP3) {

    if (!skipVP3) {
        if (0 != commit_segment_record) {
            AIS_LOG_NOTICE("Creating segment record for segment id %d.", segment_record_id);

            VP3Record SegmentRecord;
            SegmentRecord.setRecordType(SEGMENT);
            // Segment Block has 5 UIDs - Segment ID, Segment Start Time, Segment Duration, Fuel Consumed, Distance Traveled
            SegmentRecord.add_data_to_record(std::string(&UID_SegmentId[0],13), segment_record_id, true);
            SegmentRecord.add_timestamp(std::string(&UID_SegmentTime_Start[0],13),
                    segment_rec_start_real_time,
                    LIBPROD_timezone_offset,
                    segment_rec_hour_meter, true);

            { // Calculate segment duration
                /*
                 * dt_libinfo_Time20msLong is the data type of the model output
                 * This is scaled at 20ms per bit
                 */
                float duration = (float)segment_rec_duration * 0.02f;
                SegmentRecord.add_data_to_record(std::string(&UID_SegmentDuration[0],13), duration, true);
            }

            SegmentRecord.add_data_to_record(std::string(&UID_SegmentFuelConsumed[0],13), segment_rec_fuel_used, true);

            { // Distance traveled UID is defined as meters
                /*
                 * segment_rec_distance is in kilometers
                 */
                float distance = segment_rec_distance * 1000.f;
                SegmentRecord.add_data_to_record(std::string(&UID_SegmentDistanceTravelled[0],13), distance, true);
            }

            { // Calculate idle duration
                /*
                 * What are the units for segment_rec_idle_time?
                 * It appears that it is 1 sec per bit
                 */
                float duration = (float)segment_rec_idle_time;
                SegmentRecord.add_data_to_record(std::string(&UID_MachineIdleDuration[0],13), duration, true);
            }

            SegmentRecord.add_data_to_record(std::string(&UID_PayloadWeight[0],13), segment_rec_payload, true);

            // Payload calculation method UID is lsb first
            SegmentRecord.add_data_to_record(std::string(&UID_PayloadCalculationMethod[0],13), segment_rec_payload_calc_method, false);

            vp3RecordOutputChannel_->publish(SegmentRecord);

            /* Trigger a GPS block every time we have a seg record commit  */
            AIS_LOG_NOTICE("Creating location record.");
            gps_ext_trigger();
        }

        // Publish any VP3 records handled by VP3RecMgr
        VP3RecMgr::getInstance()->VP3RecMgrUpdate();
    }

    if (nullptr != txOutputChannel_) {
        CycleSegTxInterface data;

        data.activeSegmentId = segment_active_segment_id;
        data.digState = segment_dig_state; // 0, 1, 3
        data.segmentLastCompletedId = segment_last_completed_id;
        data.segmentSecondsSinceLastEnd = (float)segment_time_since_last_end * 0.02f; // 0.02 seconds / bit
        data.segmentSequenceNumber = segment_sequence_number;

        copy_inputs_and_outputs(data);

        txOutputChannel_->publish(data);
    }
}


static void copy_inputs_and_outputs(CycleSegTxInterface& data)
{
    data.cycleSegIn.ground_spd_kph = LIBPROD_ground_spd_kph;
            data.cycleSegIn.payload_ratio = LIBPROD_payload_ratio;
            data.cycleSegIn.payload_ratio_status = LIBPROD_payload_ratio_status;
            data.cycleSegIn.payload_ratio_raw = LIBPROD_payload_ratio_raw;
            data.cycleSegIn.payload_ratio_raw_status = LIBPROD_payload_ratio_raw_status;
            data.cycleSegIn.lift_valve_cmd = LIBPROD_lift_valve_cmd;
            data.cycleSegIn.tilt_valve_cmd = LIBPROD_tilt_valve_cmd;
            data.cycleSegIn.bucket_angle = LIBPROD_bucket_angle;
            data.cycleSegIn.lift_angle = LIBPROD_lift_angle;
            data.cycleSegIn.desired_gear = LIBPROD_desired_gear;
            data.cycleSegIn.engine_spd_rpm = LIBPROD_engine_spd_rpm;
            data.cycleSegIn.tilt_lever_cmd = LIBPROD_tilt_lever_cmd;
            data.cycleSegIn.tilt_cyl_pos = LIBPROD_tilt_cyl_pos;
            data.cycleSegIn.machine_idle_status = LIBPROD_machine_idle_status;
            data.cycleSegIn.keyswitch_state = LIBPROD_keyswitch_state;
            data.cycleSegIn.real_time = LIBPROD_real_time;
            data.cycleSegIn.realTime_status = LIBPROD_realTime_status;
            data.cycleSegIn.timezone_offset = LIBPROD_timezone_offset;
            data.cycleSegIn.total_fuel_high_res = LIBPROD_total_fuel_high_res;
            data.cycleSegIn.total_fuel_low_res = LIBPROD_total_fuel_low_res;
            data.cycleSegIn.fuel_rate = LIBPROD_fuel_rate;
            data.cycleSegIn.ARD_fuel_rate = LIBPROD_ARD_fuel_rate;
            data.cycleSegIn.GPS_latitude = LIBPROD_GPS_latitude;
            data.cycleSegIn.GPS_longitude = LIBPROD_GPS_longitude;
            data.cycleSegIn.GPS_status = LIBPROD_GPS_status;
            data.cycleSegIn.service_hour_meter = LIBPROD_service_hour_meter;
            data.cycleSegIn.payload_weight = LIBPROD_payload_weight;
            data.cycleSegIn.payload_weight_status = LIBPROD_payload_weight_status;
            data.cycleSegIn.payload_calc_method = LIBPROD_payload_calc_method;
            data.cycleSegIn.extForceNormalized = LIBPROD_extForceNormalized;
            data.cycleSegIn.impl_operation_status = LIBPROD_impl_operation_status;
            data.cycleSegIn.Engine_Load_Factor = LIBPROD_Engine_Load_Factor;

            data.cycleSegOut.commit_segment_record = commit_segment_record;
            data.cycleSegOut.segment_record_id = segment_record_id;
            data.cycleSegOut.segment_rec_start_simTime = segment_rec_start_simTime;
            data.cycleSegOut.segment_rec_duration = segment_rec_duration;
            data.cycleSegOut.segment_rec_distance = segment_rec_distance;
            data.cycleSegOut.segment_rec_start_real_time = segment_rec_start_real_time;
            data.cycleSegOut.segment_rec_fuel_used = segment_rec_fuel_used;
            data.cycleSegOut.segment_rec_latitude = segment_rec_latitude;
            data.cycleSegOut.segment_rec_longitude = segment_rec_longitude;
            data.cycleSegOut.segment_rec_idle_time = segment_rec_idle_time;
            data.cycleSegOut.segment_rec_hour_meter = segment_rec_hour_meter;
            data.cycleSegOut.segment_rec_payload = segment_rec_payload;
            data.cycleSegOut.segment_rec_payload_calc_method = segment_rec_payload_calc_method;
            data.cycleSegOut.commit_rec_gps = commit_rec_gps;
            data.cycleSegOut.segment_dig_state = segment_dig_state;
            data.cycleSegOut.segment_last_completed_id = segment_last_completed_id;
            data.cycleSegOut.segment_time_since_last_end = segment_time_since_last_end;
            data.cycleSegOut.segment_sequence_number = segment_sequence_number;
            data.cycleSegOut.keyswitch_override_flag = keyswitch_override_flag;
            data.cycleSegOut.segment_active_segment_id = segment_active_segment_id;
}
