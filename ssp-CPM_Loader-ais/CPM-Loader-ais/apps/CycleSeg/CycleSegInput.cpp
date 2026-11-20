#include <chrono>

#include <oel_pack.h>

#include <catdllib_fid_def.h>
#include <ksw.h>

#include <ais/task/Task.h>
#include <ais/log/Logger.h>

#include <chrono/convert.hpp>

#include <interfaces/DataLinkData/GPSDataLinkParam.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <LIBINFO_WL_if.h>

#ifdef __cplusplus
}
#endif

#include "CycleSegInput.h"

#define SHM_CLOCK_CHANNEL_DATA_TIMEOUT_SECONDS (3.0)
#define WEIGH_TX_CHANNEL_DATA_TIMEOUT_SECONDS (2.0)
#define JOB_MGR_TX_CHANNEL_DATA_TIMEOUT_SECONDS (2.0)

enum Gear {
  FORWARD = 0x4000,
  REVERSE = 0x1000
};

static void initCycleSegModelData(uint16_t appNumber);

gps_struct gpsData;
unsigned_8 keyOffStatus;  // Currently unused
int_16 timeZoneOffset = 0;
unsigned_32 serviceMeterHours = 0;

// This GPS library callback function provides the most recent GPS status value to the GPS library
// whenever the GPS library function gps_update is called.
extern "C" unsigned_8 GetGpsKeyoffStatus(void)
{
    AIS_LOG_INFO("GetGpsKeyoffStatus = %x", keyOffStatus);
    return keyOffStatus;
}

// This GPS library callback function provides the most recent GPS timestamp service hour meter value to the GPS library
// whenever the GPS library function gps_update is called.
extern "C" unsigned_32 GetGpsShm()
{
    AIS_LOG_INFO("GetGpsShm = %x", serviceMeterHours);
    return serviceMeterHours;
}

// This GPS library callback function provides the most recent GPS timestamp time zone offset value to the GPS library
// whenever the GPS library function gps_update is called.
extern "C" int_16 GetGpsTimezoneOffset()
{
    AIS_LOG_INFO("GetGpsTimezoneOffset = %x", timeZoneOffset);
    return timeZoneOffset;
}

// This GPS library callback function provides the most recent GPS local time, latitude, and longitude value to the GPS library
// whenever the GPS library function gps_update is called.
extern "C" gps_struct GetGpsData()
{
    AIS_LOG_INFO("GetGpsData called");
    return gpsData;
}

// This GPS library callback function provides the most recent GPS timestamp UTC value formatted to
// seconds since 1/1/2000 to the GPS library whenever the GPS library function gps_update is called.
extern "C" unsigned_32 GetGpsUtc()
{
    // Convert GPS time stamp (Time/Date $F835) to seconds since 1/1/2000
    struct clock_tm gps_time;

    // GPS Seconds Resolution: 0.25 sec/bit
    constexpr int_16 QtrsPerWhole = 4;
    gps_time.tm_sec = static_cast<int_16>(gpsData.timest.sec / QtrsPerWhole);  // quarter secs to secs, truncate

    // GPS Minutes Resolution: 1 minute/bit
    gps_time.tm_min = static_cast<int_16>(gpsData.timest.min);

    // GPS Hours Resolution: 1 hour/bit
    gps_time.tm_hour = static_cast<int_16>(gpsData.timest.hour);

    // GPS Day Resolution: 0.25 day/bit
    gps_time.tm_mday = static_cast<int_16>(gpsData.timest.day / QtrsPerWhole); // quarter days to days, truncate

    // GPS time stamp uses 1 for January, etc, while clock_tm uses 0
    constexpr int_16 GpsMonOffset = 1;
    gps_time.tm_mon = static_cast<int_16>(gpsData.timest.mon - GpsMonOffset);  // change 1-12 to 0-11

    // GPS bases year 1985 as 0, while clock_tm struct bases year 1900 as 0, 2000 as 100
    // clock_tm_to_seconds() subtracts 100 from year before calculating
    constexpr int_16 GpsBaseYear = 85;
    gps_time.tm_year = static_cast<int_16>(gpsData.timest.year + GpsBaseYear); // adjust for conversion to seconds

    AIS_LOG_INFO("tm_sec = %d", gps_time.tm_sec);
    AIS_LOG_INFO("tm_min = %d", gps_time.tm_min);
    AIS_LOG_INFO("tm_hour = %d", gps_time.tm_hour);
    AIS_LOG_INFO("tm_mday = %d", gps_time.tm_mday);
    AIS_LOG_INFO("tm_mon = %d", gps_time.tm_mon);
    AIS_LOG_INFO("tm_year = %d", gps_time.tm_year);
    return clock_tm_to_seconds(&gps_time);
}

CycleSegInput::CycleSegInput() :
    gpsConfig{nullptr, DefaultGpsDistanceThreshold, DefaultGpsTimeThreshold},
    gpsAccessorFunctions(),
    previousPositionStatus(POS_INVALID),
    shmClockInputChannel_(nullptr),
    lastWeighTxTime_(TimePoint::min()),
    weighTxInputChannel_(nullptr),
    weighTxChannelData_(),
    dataLinkDataInputChannel_(nullptr) {
}

bool CycleSegInput::initialize(uint16_t appNumber, ConfigSection taskCfg) {
    bool everythingOk = true;
    rubyCfg = taskCfg;

    initCycleSegModelData(appNumber);

    // Initialize input channels
    if (!task::InterfaceDb::bind("ShmClockInput", shmClockInputChannel_)) {
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("WeighTxInput", weighTxInputChannel_)) {
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("DatalinkDataInput", dataLinkDataInputChannel_)) {
        everythingOk = false;
    }

    if (!Initialize_GPS())
    {
        everythingOk = false;
    }

    return everythingOk;
}

void CycleSegInput::update() {
    auto steadyNow = SteadyClock::now();

    { // Keyswitch
        if (KSW_KEYSWITCH_ASSERTED == ksw_keyswitch_get()) {
            LIBPROD_keyswitch_state = 1; // Keyswitch ON
        }
        else {
            LIBPROD_keyswitch_state = 0; // Keyswitch OFF
        }
    }

    { // Time
        LIBPROD_real_time = tes_common_ais::systemClockTimePointToUidTime(); // 1 second/bit since 6-Jan-1980
    }

    { // Read SHM clock inputs
        if (nullptr != shmClockInputChannel_) {
            bool newData = false;
            ShmClock data;
            while (shmClockInputChannel_->get(data)) {
                newData = true;
            }
            if (newData) {
                lastShmClockTime_ = steadyNow;
                shmClockChannelData_ = data;
                serviceMeterHours = shmClockChannelData_.get_SHM();
            }
        }

        if (steadyNow > (lastShmClockTime_ + std::chrono::seconds(static_cast<std::chrono::seconds::rep>(SHM_CLOCK_CHANNEL_DATA_TIMEOUT_SECONDS)))) {
            // Timeout
            LIBPROD_service_hour_meter = UNKNOWN4U + FMICNM;

            // LIBPROD_timezone_offset = LIBPROD_timezone_offset; // Last know good value

            LIBPROD_realTime_status = UNKNOWN1U + FMICNM; // non-zero is bad

            AIS_LOG_WARN("Timeout receiving ShmClock input.");
        }
        else {
            LIBPROD_service_hour_meter = shmClockChannelData_.get_SHM(); // 1 sec/bit

            { // Timezone Offset
                int32_t temp = shmClockChannelData_.get_UTC_offset();
                if (temp > INT16_MAX) {
                    temp = INT16_MAX;
                }
                else if (temp < INT16_MIN) {
                    temp = INT16_MIN;
                }
                LIBPROD_timezone_offset = static_cast<int16_t>(temp);
            }

            LIBPROD_realTime_status = 0; // non-zero is bad
        }
    }

    { // Read weigh app inputs
        if (nullptr != weighTxInputChannel_) {
            bool newData = false;
            LpsSaWeighTxChannel data;
            while (weighTxInputChannel_->get(data)) {
                newData = true;
            }
            if (newData) {
                lastWeighTxTime_ = steadyNow;
                weighTxChannelData_ = data;
            }
        }

        if (steadyNow > (lastWeighTxTime_ + std::chrono::seconds(static_cast<std::chrono::seconds::rep>(WEIGH_TX_CHANNEL_DATA_TIMEOUT_SECONDS)))) {
            // Timeout
            LIBPROD_payload_weight_status = 0; //Unavailable
            LIBPROD_payload_ratio = 0.f; // float 1.0 means full rated load
            LIBPROD_payload_ratio_status = 1; // 0 = OK, 1 = FAULTED, 2 = RAISE_STALL, 3 = LOWER_STALL
            LIBPROD_payload_ratio_raw = 0.f; // float 1.0 means full rated load
            LIBPROD_payload_ratio_raw_status = 1; // 0 = OK, 1 = FAULTED, 2 = RAISE_STALL, 3 = LOWER_STALL

            LIBPROD_lift_valve_cmd = UNKNOWN2S + FMICNM; // 0.0625 %/bit
            LIBPROD_tilt_valve_cmd = UNKNOWN2S + FMICNM; // 0.0625 %/bit

            LIBPROD_bucket_angle = UNKNOWN2S + FMICNM; // 0.015625 degrees/bit
            LIBPROD_lift_angle = UNKNOWN2S + FMICNM; // 0.015625 degrees/bit

            LIBPROD_tilt_cyl_pos = UNKNOWN2U + FMICNM; // 2^-8 %/bit. 0.00390625 %/bit. 2560 = 10%.

            LIBPROD_payload_weight = 0.f; // tonnes
            LIBPROD_payload_calc_method = 0; // Buettner special encoding

            AIS_LOG_WARN("Timeout receiving WeighTx input.");
        }
        else {
            // Update parameters
            LIBPROD_payload_weight_status = (BUCKET_PAYLOAD_AVAILABLE == weighTxChannelData_.PidData.BktPayloadData) ? 1 : 0; // 0 = Unavailable, 1 = Available
            LIBPROD_payload_ratio = weighTxChannelData_.Payload.payloadRatio; // float 1.0 means full rated load
            LIBPROD_payload_ratio_status = static_cast<uint16_t>(weighTxChannelData_.Payload.payloadRatioStatus); // 0 = OK, 1 = FAULTED, 2 = RAISE_STALL, 3 = LOWER_STALL
            LIBPROD_payload_ratio_raw = weighTxChannelData_.Payload.payloadRatioRaw; // float 1.0 means full rated load
            LIBPROD_payload_ratio_raw_status = static_cast<uint16_t>(weighTxChannelData_.Payload.payloadRatioStatus); // 0 = OK, 1 = FAULTED, 2 = RAISE_STALL, 3 = LOWER_STALL

            if (LPS_STATUS_OK == weighTxChannelData_.LiftValveCommand.Stat) {
                LIBPROD_lift_valve_cmd = weighTxChannelData_.LiftValveCommand.Val * (float)(1UL<<4); // 0.0625 %/bit
            }
            else {
                LIBPROD_lift_valve_cmd = UNKNOWN2S + FMICNM;
            }

            if (LPS_STATUS_OK == weighTxChannelData_.TiltValveCommand.Stat) {
                LIBPROD_tilt_valve_cmd = weighTxChannelData_.TiltValveCommand.Val * (float)(1UL<<4); // 0.0625 %/bit
            }
            else {
                LIBPROD_tilt_valve_cmd = UNKNOWN2S + FMICNM;
            }

            if (LPS_STATUS_OK == weighTxChannelData_.LiftPosition.status) {
                LIBPROD_lift_angle = weighTxChannelData_.LiftPosition.angle * (float)(1UL<<6); // 0.015625 degrees/bit
            }
            else {
                LIBPROD_lift_angle = UNKNOWN2S + FMICNM; // 0.015625 degrees/bit
            }

            if (LPS_STATUS_OK == weighTxChannelData_.TiltPosition.status) {
                LIBPROD_bucket_angle = weighTxChannelData_.TiltPosition.bucketAngle * (float)(1UL<<6); // 0.015625 degrees/bit
                LIBPROD_tilt_cyl_pos = weighTxChannelData_.TiltPosition.percentCylinderLength * (float)(1<<8); // 2560 = 10%.  2^-8 %/bit. 0.00390625 %/bit
            }
            else {
                LIBPROD_bucket_angle = UNKNOWN2S + FMICNM;
                LIBPROD_tilt_cyl_pos = UNKNOWN2U + FMICNM;
            }

            LIBPROD_payload_weight = weighTxChannelData_.BestBktWtInTonnes; // tonnes
            LIBPROD_payload_calc_method = weighTxChannelData_.PayloadCalcMeth; // Buettner special encoding
        }
    }

    { // Read datalink inputs
        if (nullptr != dataLinkDataInputChannel_) {
            DataLinkData data;
            while (dataLinkDataInputChannel_->get(data)) {
                // loop through the parameters looking for the ones we care about.
                for (const auto& param : data.GetParams()) {

                    switch (param.GetParamIdentifierType()) {

                    // PGN
                    case (DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN): {
                        switch (param.GetParamId()) {

                        // EEC1
                        case (61444): {
                            if ((VarLengthDataLinkParamPool::PGN == param.GetVarLengthParamType()) &&
                                    (0 == param.GetVarLengthParamDsi()) &&
                                    param.GetVarParamBlockLength() >= 8) {
                                const uint8_t* data = param.GetVarParamBlock();
                                uint16_t temp;
                                data += 3; // Advance to byte 4
                                OEL_UNPACK_LE_16_NO_INCR(data, temp);

                                // Same as datalink scaling 0.125 rpm/bit
                                if (temp >= INT16_MAX) {
                                    LIBPROD_engine_spd_rpm = INT16_MAX;
                                }
                                else {
                                    LIBPROD_engine_spd_rpm = (int16_t)temp;
                                }
                                AIS_LOG_INFO("EEC1: %d", LIBPROD_engine_spd_rpm);
                            }
                            else {
                                LIBPROD_engine_spd_rpm = UNKNOWN2S + FMICNM;
                                AIS_LOG_INFO("EEC1 fault: %x", LIBPROD_engine_spd_rpm);
                            }
                            break;
                        }

                        // LFE1
                        case (65266): {
                            if ((VarLengthDataLinkParamPool::PGN == param.GetVarLengthParamType()) &&
                                    (0 == param.GetVarLengthParamDsi()) &&
                                    param.GetVarParamBlockLength() >= 8) {
                                const uint8_t* data = param.GetVarParamBlock();
                                uint16_t temp;
                                OEL_UNPACK_LE_16_NO_INCR(data, temp);

                                // Same as datalink scaling 0.05 l/h/bit
                                LIBPROD_fuel_rate = temp;
                                AIS_LOG_INFO("LFE1: %d", LIBPROD_fuel_rate);
                            }
                            else {
                                LIBPROD_fuel_rate = UNKNOWN2U + FMICNM;
                                AIS_LOG_INFO("LFE1 fault: %x", LIBPROD_fuel_rate);
                            }
                            break;
                        }

                        default: {
                            break;
                        }

                        }
                        break;
                    }

                    // CDL PIDs
                    case (DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID): {
                        switch (param.GetParamId()) {

                        // Ground Speed
                        case (0xF4FD): {
                            AIS_LOG_INFO("Ground Speed dsi %u", param.GetLastValueDsi());
                            if (0 == param.GetLastValueDsi()) {
                                float temp = param.GetLastValue<int16_t>();
                                temp = temp * 0.0036f; // from 1 mm/sec -> 1 km/hour
                                temp = temp * (1UL<<8); // from 1 km/hour -> 2^-8 km/hour
                                LIBPROD_ground_spd_kph = static_cast<int16_t>(temp);
                                AIS_LOG_INFO("Ground Speed %d", LIBPROD_ground_spd_kph);
                            }
                            else {
                                LIBPROD_ground_spd_kph = UNKNOWN2S + FMICNM;
                                AIS_LOG_INFO("Ground Speed fault %x", LIBPROD_ground_spd_kph);
                            }
                            break;
                        }

                        // Direction Switch Position
                        case (0xF074): {
                            AIS_LOG_INFO("Direction Switch Position dsi %u", param.GetLastValueDsi());
                            if (0 == param.GetLastValueDsi()) {
                                uint8_t data = param.GetLastValue<uint8_t>();
                                if (0x01 == data) {
                                    /* Forward */
                                    LIBPROD_desired_gear = (int16_t)(1);
                                    AIS_LOG_INFO("Direction Switch Position Forward %x", LIBPROD_desired_gear);
                                }
                                else if (0x00 == data) {
                                    /* Reverse */
                                    LIBPROD_desired_gear = (int16_t)(-1);
                                    AIS_LOG_INFO("Direction Switch Position Reverse %x", LIBPROD_desired_gear);
                                }
                                else {
                                    // Neutral or Park
                                    LIBPROD_desired_gear = 0;
                                    AIS_LOG_INFO("Direction Switch Position N or P %x", LIBPROD_desired_gear);
                                }
                            }
                            else {
                                /* Mind you that we set to bad with a 2-byte signed dsi
                                 * value, since this is what it expects */
                                LIBPROD_desired_gear = UNKNOWN2S + FMICNM;
                                AIS_LOG_INFO("Direction Switch Position fault %x", LIBPROD_desired_gear);
                            }
                            break;
                        }

                        // Actual Gear
                        case (0xF5D9): {
                            AIS_LOG_INFO("Actual Gear dsi %u", param.GetLastValueDsi());
                            if (0 == param.GetLastValueDsi()) {
                                uint16_t data = (uint16_t)param.GetLastGoodValueEng();
                                if (data & FORWARD) {
                                    /* Forward */
                                    LIBPROD_desired_gear = (int16_t)(1);
                                    AIS_LOG_INFO("Actual Gear Forward %x", LIBPROD_desired_gear);
                                }
                                else if (data & REVERSE) {
                                    /* Reverse */
                                    LIBPROD_desired_gear = (int16_t)(-1);
                                    AIS_LOG_INFO("Actual Gear Reverse %x", LIBPROD_desired_gear);
                                }
                                else {
                                    // Neutral or Park
                                    LIBPROD_desired_gear = 0;
                                    AIS_LOG_INFO("Actual Gear N or P %x", LIBPROD_desired_gear);
                                }
                            }
                            else {
                                // bad data
                                LIBPROD_desired_gear = UNKNOWN2S + FMICNM;
                                AIS_LOG_INFO("Actual Gear fault %x", LIBPROD_desired_gear);
                            }
                            break;
                        }

                        // Tilt Lever Position
                        case (0xF49C): {
                            AIS_LOG_INFO("Tilt Lever Position dsi %u", param.GetLastValueDsi());
                            if (0 == param.GetLastValueDsi()) {
                                // PID is 1 %/bit signed 2 bytes
                                float temp = param.GetLastValue<int16_t>();
                                if (temp > 100) {
                                    temp = 100;
                                }
                                else if (temp < -100) {
                                    temp = -100;
                                }
                                temp = temp * (1UL<<4); // from 1 % -> 2^-4 %
                                LIBPROD_tilt_lever_cmd = static_cast<int16_t>(temp); // 0.0625 %/bit
                                AIS_LOG_INFO("Tilt Lever Position %d", LIBPROD_tilt_lever_cmd);
                            }
                            else {
                                // bad data
                                LIBPROD_tilt_lever_cmd = UNKNOWN2S + FMICNM;
                                AIS_LOG_INFO("Tilt Lever Position fault %x", LIBPROD_tilt_lever_cmd);
                            }
                            break;
                        }

                        // Machine Idle Status
                        case (0xD10AB5): {
                            AIS_LOG_INFO("Machine Idle Status dsi %u", param.GetLastValueDsi());
                            if (0 == param.GetLastValueDsi()) {
                                // Same as datalink encoding
                                LIBPROD_machine_idle_status = param.GetLastValue<uint16_t>();
                                AIS_LOG_INFO("Machine Idle Status %x", LIBPROD_machine_idle_status);
                            }
                            else {
                                // bad data
                                LIBPROD_machine_idle_status = UNKNOWN2U + FMICNM;
                                AIS_LOG_INFO("Machine Idle Status fault %x", LIBPROD_machine_idle_status);
                            }
                            break;
                        }

                        // Total Fuel Low Res
                        case (0xC8): {
                            AIS_LOG_INFO("Total Fuel Low Res dsi %u", param.GetLastValueDsi());
                            if (0 == param.GetLastValueDsi()) {
                                // Same as datalink scaling 0.125 gal/bit
                                LIBPROD_total_fuel_low_res = param.GetLastValue<uint32_t>();
                                AIS_LOG_INFO("Total Fuel Low Res %u", LIBPROD_total_fuel_low_res);
                            }
                            else {
                                // bad data
                                LIBPROD_total_fuel_low_res = UNKNOWN4U + FMICNM;
                                AIS_LOG_INFO("Total Fuel Low Res fault %x", LIBPROD_total_fuel_low_res);
                            }
                            break;
                        }

                        // Total Fuel High Res
                        case (0xFE5D): {
                            AIS_LOG_INFO("Total Fuel High Res dsi %u", param.GetLastValueDsi());
                            if (0 == param.GetLastValueDsi()) {
                                // Same as datalink scaling 0.001 gal/bit
                                LIBPROD_total_fuel_high_res = param.GetLastValue<uint32_t>();
                                AIS_LOG_INFO("Total Fuel High Res %u", LIBPROD_total_fuel_high_res);
                            }
                            else {
                                // bad data
                                LIBPROD_total_fuel_high_res = UNKNOWN4U + FMICNM;
                                AIS_LOG_INFO("Total Fuel High Res fault %x", LIBPROD_total_fuel_high_res);
                            }
                            break;
                        }

                        // GPS
                        case (0xF84D): {
                            AIS_LOG_INFO("GPS dsi %u", param.GetLastValueDsi());
                            if ((VarLengthDataLinkParamPool::GPS == param.GetVarLengthParamType()) &&
                                    (0 == param.GetVarLengthParamDsi()) &&
                                    (param.GetVarParamBlockLength() >= GPSDataLinkParam::m_GpsParamSize)) {
                                // Unfortunatley we have to cast away const to create a GPSDataLinkParam
                                const GPSDataLinkParam gpsParam(const_cast<DataLinkParam&>(param));
                                GPSDataLinkParam::GpsLatitude_t gpsLatitude;
                                GPSDataLinkParam::GpsLongitude_t gpsLongitude;
                                gpsParam.GetGpsLatitude(gpsLatitude);
                                gpsParam.GetGpsLongitude(gpsLongitude);
                                gpsData.pos_cmd = gpsParam.GetPositionCommand();
                                gpsData.timest.sec = gpsParam.GetTimestampSeconds();
                                gpsData.timest.min = gpsParam.GetTimestampMinutes();
                                gpsData.timest.hour = gpsParam.GetTimestampHours();
                                gpsData.timest.mon = gpsParam.GetTimestampMonth();
                                gpsData.timest.day = gpsParam.GetTimestampDay();
                                gpsData.timest.year = gpsParam.GetTimestampYear();
                                gpsData.pos_status = static_cast<unsigned_8>(gpsParam.GetGpsStatus());
                                std::memcpy(gpsData.GPS_Lat, gpsLatitude, GPSDataLinkParam::m_GpsLatitudeSize);
                                std::memcpy(gpsData.GPS_Long, gpsLongitude, GPSDataLinkParam::m_GpsLongitudeSize);

                                AIS_LOG_INFO("gpsData.pos_cmd = %x", gpsData.pos_cmd);
                                AIS_LOG_INFO("gpsData.timest.sec = %x", gpsData.timest.sec);
                                AIS_LOG_INFO("gpsData.timest.min = %x", gpsData.timest.min);
                                AIS_LOG_INFO("gpsData.timest.hour = %x", gpsData.timest.hour);
                                AIS_LOG_INFO("gpsData.timest.mon = %x", gpsData.timest.mon);
                                AIS_LOG_INFO("gpsData.timest.day = %x", gpsData.timest.day);
                                AIS_LOG_INFO("gpsData.timest.year = %x", gpsData.timest.year);
                                AIS_LOG_INFO("gpsData.pos_status = %x", gpsData.pos_status);
                                AIS_LOG_INFO("gpsData.GPS_Lat[0] = %x", gpsData.GPS_Lat[0]);
                                AIS_LOG_INFO("gpsData.GPS_Lat[1] = %x", gpsData.GPS_Lat[1]);
                                AIS_LOG_INFO("gpsData.GPS_Lat[2] = %x", gpsData.GPS_Lat[2]);
                                AIS_LOG_INFO("gpsData.GPS_Long[0] = %x", gpsData.GPS_Long[0]);
                                AIS_LOG_INFO("gpsData.GPS_Long[1] = %x", gpsData.GPS_Long[1]);
                                AIS_LOG_INFO("gpsData.GPS_Long[2] = %x", gpsData.GPS_Long[2]);
                                if ((POS_VALID == previousPositionStatus) && (POS_VALID != gpsData.pos_status))
                                {
                                    // Enable recovery trigger by invoking external trigger when position status
                                    // transitions from valid to non-valid.  This is a precondition imposed by the
                                    // implementation of the GPS library.  The GPS library will not trigger a recovery
                                    // later when the position status transitions back to valid unless it has been preceded
                                    // by either an external trigger or a time trigger.
                                    AIS_LOG_DEBUG("Calling gps_ext_trigger after position status transition from valid to non-valid.");
                                    gps_ext_trigger();
                                }
                                previousPositionStatus = gpsData.pos_status;
                                gps_update();

                                if (GPSDataLinkParam::GpsPositionStatusType::POSITION_VALID == gpsParam.GetGpsStatus())
                                {
                                    LIBPROD_GPS_status = 0; // non-zero is bad
                                    { // Latitude 2^-17 degrees/bit
                                        double temp = gpsParam.GetGpsLatitude();
                                        if (temp >= 90.0) {
                                            temp = 0;
                                        }
                                        else if (temp <= -90.0) {
                                            temp = 180.0 * (double)(1UL<<17);
                                        }
                                        else {
                                            temp = (90.0 - temp) * (double)(1UL<<17);
                                        }
                                        temp += 0.5; // Round
                                        LIBPROD_GPS_latitude = static_cast<uint32_t>(temp);
                                        AIS_LOG_INFO("GPS lat %d", LIBPROD_GPS_latitude);
                                    }

                                    { // Longitude 2^-16 degrees/bit
                                        double temp = gpsParam.GetGpsLongitude();
                                        if (temp >= 180.0) {
                                            temp = 0;
                                        }
                                        else if (temp <= -180.0) {
                                            temp = 360.0 * (double)(1UL<<16);
                                        }
                                        else {
                                            temp = (180.0 - temp) * (double)(1UL<<16);
                                        }
                                        temp += 0.5; // Round
                                        LIBPROD_GPS_longitude = static_cast<uint32_t>(temp);
                                        AIS_LOG_INFO("GPS long %d", LIBPROD_GPS_longitude);
                                    }
                                }
                                else {
                                    LIBPROD_GPS_status = UNKNOWN1U + FMICNM; // non-zero is bad
                                    LIBPROD_GPS_latitude = 0;
                                    LIBPROD_GPS_longitude = 0;
                                    AIS_LOG_INFO("GPS Fault A %x", LIBPROD_GPS_status);
                                }
                            }
                            else {
                                LIBPROD_GPS_status = UNKNOWN1U + FMICNM; // non-zero is bad
                                LIBPROD_GPS_latitude = 0;
                                LIBPROD_GPS_longitude = 0;
                                AIS_LOG_INFO("GPS Fault B %x", LIBPROD_GPS_status);
                            }
                            break;
                        }

                        // External Force
                        case (0xD01E8C): {
                            AIS_LOG_INFO("External Force dsi %u", param.GetLastValueDsi());
                            if (0 == param.GetLastValueDsi()) {
                                // Same as datalink scaling 0.0005 g/bit
                                LIBPROD_extForceNormalized = param.GetLastValue<int16_t>();
                                AIS_LOG_INFO("External Force %d", LIBPROD_extForceNormalized);
                            }
                            else {
                                // bad data
                                LIBPROD_extForceNormalized = UNKNOWN2S + FMICNM;
                                AIS_LOG_INFO("External Force fault %x", LIBPROD_extForceNormalized);
                            }
                            break;
                        }

                        // Implement Operation Status
                        case (0xD106D9): {
                            AIS_LOG_INFO("Implement Operation Status dsi %u", param.GetLastValueDsi());
                            if (0 == param.GetLastValueDsi()) {
                                // Same as datalink encoding
                                LIBPROD_impl_operation_status = param.GetLastValue<uint16_t>();
                                AIS_LOG_INFO("Implement Operation Status %x", LIBPROD_impl_operation_status);
                            }
                            else {
                                // bad data
                                LIBPROD_impl_operation_status = 15; // Inactive
                                AIS_LOG_INFO("Implement Operation Status fault %x", LIBPROD_impl_operation_status);
                            }
                            break;
                        }

                        default: {
                            break;
                        }

                        }
                        break;
                    }

                    default: {
                        break;
                    }
                    }
                }
            }
        }
    }
}

static void initCycleSegModelData(uint16_t appNumber) {
    LIBPROD_app_number = appNumber;

    LIBPROD_ground_spd_kph = UNKNOWN2S + FMICNM; // 0.00390625 km/hr/bit

    LIBPROD_payload_ratio = 0.f; // float 1.0 means full rated load
    LIBPROD_payload_ratio_status = 0; // 0 = OK, 1 = FAULTED, 2 = RAISE_STALL, 3 = LOWER_STALL
    LIBPROD_payload_ratio_raw = 0.f; // float 1.0 means full rated load
    LIBPROD_payload_ratio_raw_status = 0; // 0 = OK, 1 = FAULTED, 2 = RAISE_STALL, 3 = LOWER_STALL

    LIBPROD_lift_valve_cmd = UNKNOWN2S + FMICNM; // 0.0625 %/bit
    LIBPROD_tilt_valve_cmd = UNKNOWN2S + FMICNM; // 0.0625 %/bit

    LIBPROD_bucket_angle = UNKNOWN2S + FMICNM; // 0.015625 degrees/bit
    LIBPROD_lift_angle = UNKNOWN2S + FMICNM; // 0.015625 degrees/bit

    LIBPROD_desired_gear = UNKNOWN2S + FMICNM;
    LIBPROD_engine_spd_rpm = UNKNOWN2S + FMICNM; // 0.125 rpm/bit

    LIBPROD_tilt_lever_cmd = UNKNOWN2S + FMICNM;

    LIBPROD_tilt_cyl_pos = UNKNOWN2U + FMICNM; // 2560 = 10%.  2^-8 %/bit. 0.00390625 %/bit

    LIBPROD_machine_idle_status = UNKNOWN2U + FMICNM; // Same as PID

    LIBPROD_keyswitch_state = 1;

    LIBPROD_real_time = 0; // Get real time since some epoch
    LIBPROD_realTime_status = UNKNOWN1U + FMICNM; // non-zero is bad
    LIBPROD_timezone_offset = 0; // Minutes

    LIBPROD_total_fuel_high_res = UNKNOWN4U + FMICNM; // 0.001 gal/bit
    LIBPROD_total_fuel_low_res = UNKNOWN4U + FMICNM; // 0.125 gal/bit
    LIBPROD_fuel_rate = UNKNOWN2U + FMICNM; // 0.05 l/hr/bit
    LIBPROD_ARD_fuel_rate = UNKNOWN2U + FMICNM; // 0.000001 l/sec/bit

    LIBPROD_GPS_latitude = 0; // 7.62939E-06 degrees /bit (2^-17)
    LIBPROD_GPS_longitude = 0; // 1.52588E-05 degrees / bit (2^-16)
    LIBPROD_GPS_status = UNKNOWN1U + FMICNM; // non-zero is bad

    LIBPROD_service_hour_meter = UNKNOWN4U + FMICNM; // 1 sec/bit

    LIBPROD_payload_weight = 0.f; // tonnes
    LIBPROD_payload_weight_status = 0; // 0 = Unavailable, 1 = Available
    LIBPROD_payload_calc_method = 0; // Buettner special encoding

    LIBPROD_extForceNormalized = UNKNOWN2S + FMICNM; // 0.0005 g/bit
    LIBPROD_impl_operation_status = 15; // Same as PID

    LIBPROD_Engine_Load_Factor = 0; // NOT USED
}

bool CycleSegInput::Initialize_GPS()
{
    bool gpsInitializeSuccess = false;

    if (!rubyCfg.get("gpsDistanceThreshold", gpsConfig.gps_distance_threshold))
    {
        AIS_LOG_WARN("*** Failed to read gpsDistanceThreshold from ruby file, using default value.");
    }

    if (!rubyCfg.get("gpsTimeThreshold", gpsConfig.gps_time_threshold))
    {
        AIS_LOG_WARN("*** Failed to read gpsTimeThreshold from ruby file, using default value.");
    }

    gpsAccessorFunctions.get_keyoff_status = &GetGpsKeyoffStatus;
    gpsAccessorFunctions.get_shm = &GetGpsShm;
    gpsAccessorFunctions.get_timezone_offset = &GetGpsTimezoneOffset;
    gpsAccessorFunctions.get_utc = &GetGpsUtc;
    gpsAccessorFunctions.get_gps = &GetGpsData;
    gpsConfig.func_ptrs = &gpsAccessorFunctions;
    gpsData.pos_status = POS_INVALID;

    if (GPS_INIT_SUCCESS == gps_init(&gpsConfig))
    {
        gpsInitializeSuccess = true;
        AIS_LOG_NOTICE("GPS init Success");
    }

    return gpsInitializeSuccess;
}
