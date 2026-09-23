#include <oel_pack.h>

#include <chrono/convert.hpp>

#include "LpsSaTotalsOperatorId.h"

#include "LpsSaTotalsTelemetry.h"

void LpsSaTotalsTelemetry::initialize()
{
    // Initialize unsupported/unused fields
    ::CAT::Telemetry::GpsLocation *location = pcsCycle.mutable_location();
    location->mutable_height()->set_value(0.0f);
    location->mutable_northing()->set_value(0);
    location->mutable_easting()->set_value(0);
    location->mutable_elevation()->set_value(0);
    location->mutable_heading()->set_value(0);
    location->mutable_equipment_state_id()->set_value(0);
    location->mutable_equipment_state_flags()->set_value(0);

    ::CAT::Telemetry::GpsLocation_Accuracy *accuracy = location->mutable_accuracy();
    accuracy->set_gps_source_available(1);
    accuracy->set_data_validity(1);
    accuracy->set_filtered(1);
    accuracy->set_altitude(1);
    accuracy->set_fix_3d(1);
    accuracy->set_corrections_available(1);
    accuracy->set_fix_available(1);

    CAT::Telemetry::PcsCycle_EventMask *eventMask = pcsCycle.mutable_event_mask();
    eventMask->set_reweigh_occurred(false);
    eventMask->set_bad_lift_included(false);

    pcsCycle.mutable_blast_number()->set_value(0);
    pcsCycle.mutable_load_site_id()->set_value(0);
}

void LpsSaTotalsTelemetry::updateDataLinkData(const DataLinkData& dataLinkData)
{
    const DataLinkParam* pParam;

    // Look for GPS
    if (dataLinkData.GetParam(pParam, 0xF84D, DataLinkParam::DlpParamIdentifierType_t::DATA_LINK_PARAM_IDENTIFIER_PID)) {
        const DataLinkParam& param = *pParam;
        if ((param.IsPIDDataReceived()) &&
                (VarLengthDataLinkParamPool::GPS == param.GetVarLengthParamType()) &&
                (0 == param.GetVarLengthParamDsi()) &&
                (param.GetVarParamBlockLength() >= GPSDataLinkParam::m_GpsParamSize)) {
            // Unfortunately, we have to cast away the const here because we don't have
            // a read-only version of the GPSDataLinkParam class
            const GPSDataLinkParam gpsParam(const_cast<DataLinkParam&>(param));
            if (GPSDataLinkParam::GpsPositionStatusType::POSITION_VALID == gpsParam.GetGpsStatus()) {
                CAT::Telemetry::GpsLocation *location = pcsCycle.mutable_location();
                location->mutable_latitude()->set_value(gpsParam.GetGpsLatitude());
                location->mutable_longitude()->set_value(gpsParam.GetGpsLongitude());
            }
        }
    }
}

std::string LpsSaTotalsTelemetry::generatePcsCycleMsg(const LpsSaLoadRecordChannelStorage& loadRecord,
        const LpsSaTotalsOperatorId& operatorId)
{
    const auto& lastSubtotal = loadRecord.getCurrentSubtotal();

    // Update protobuf message based on loadRecord
    auto utcEndTime = tes_common_ais::systemClockTimePointToUidTime(lastSubtotal.endTime.utcTime);
    pcsCycle.set_message_timestamp(utcEndTime);

    pcsCycle.mutable_cycle_timestamp()->set_value(utcEndTime);
    pcsCycle.mutable_service_meter_units()->set_value(lastSubtotal.endTime.shmTime);
    pcsCycle.mutable_truck_weight()->set_value(loadRecord.weightTonnes());
    pcsCycle.mutable_truck_id()->set_value(lastSubtotal.truckName);
    pcsCycle.mutable_loader_pass_count()->set_value(loadRecord.passCount());
    pcsCycle.mutable_material_id()->set_value(lastSubtotal.materialId);
    pcsCycle.mutable_vims_user_info()->set_value(operatorId.getDescription().c_str());

    /*
     * Here we need an unsigned int, so we can try to build
     * one out of the least significant bytes of the id.
     */
    {
        uint32_t uintId;
        const auto& id = operatorId.getId();

        switch (id.size()) {
        case (0): {
            uintId = 0;
            break;
        }
        case (1): {
            OEL_UNPACK_BE_8_NO_INCR(id.data(), uintId);
            break;
        }
        case (2): {
            OEL_UNPACK_BE_16_NO_INCR(id.data(), uintId);
            break;
        }
        case (3): {
            OEL_UNPACK_BE_24_NO_INCR(id.data(), uintId);
            break;
        }
        case (4): {
            OEL_UNPACK_BE_32_NO_INCR(id.data(), uintId);
            break;
        }
        default: {
            OEL_UNPACK_BE_32_NO_INCR(id.data()+id.size()-4, uintId);
            break;
        }
        }

        pcsCycle.mutable_operator_id()->set_value(uintId);
    }

    std::string outputStr;
    pcsCycle.SerializeToString(&outputStr);

    /*
     * What is the following for?
     *
     * It literally says:
     *      "it is not safe to use any other part of the protocol buffers
     *      library after ShutdownProtobufLibrary() has been called."
     *      6/8/23 - Commented out because it was causing an exception
     *      when trying to use protobuf on the second load maybe because
     *      the protobuf library is shutdown?
     */
    //google::protobuf::ShutdownProtobufLibrary();

    return outputStr;
}
