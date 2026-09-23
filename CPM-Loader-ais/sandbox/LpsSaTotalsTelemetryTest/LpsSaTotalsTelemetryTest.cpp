#include "LpsSaTotalsTelemetryTest.h"

#include <array>
#include <fstream>
#include <time.h>

using namespace task;

AbstractTaskCore* task::getTaskImplementation(void) {
    static LpsSaTotalsTelemetryTest thisTask("LpsSaTotalsTelemetryTest");
    return dynamic_cast<Task*>(&thisTask);
}

LpsSaTotalsTelemetryTest::LpsSaTotalsTelemetryTest(const std::string& taskName) : Task(taskName),
        dataLinkDataOutput_(nullptr),
        partNumbersOutput_(nullptr),
        fileTransferBridgeRequestInput_(nullptr),
        lpsSaLoadRecordChannelOutput_(nullptr),
        can1DlData(),
        gpsParam(),
        intDlData(),
        operatorIdParam() {}

LpsSaTotalsTelemetryTest::~LpsSaTotalsTelemetryTest() {}

bool LpsSaTotalsTelemetryTest::initialize() {

    // Initialize the list locations input channel.
    if (!task::InterfaceDb::bind("DataLinkDataOutput", dataLinkDataOutput_) ||
        !task::InterfaceDb::bind("PartNumbersOutput", partNumbersOutput_) ||
        !task::InterfaceDb::bind("FileTransferBridgeRequestInput", fileTransferBridgeRequestInput_) ||
        !task::InterfaceDb::bind("LpsSaLoadRecordChannelOutputChannel", lpsSaLoadRecordChannelOutput_))
    {
        return false;
    }

    gpsParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_CAN1_1939);
    gpsParam.SetParamId(0xF84D);
    gpsParam.SetSid(0x25);
    gpsParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
    gpsParam.SetVarLengthParamType(VarLengthDataLinkParamFactory::GPS);
    gpsParam.SetScaling(1.0);
    gpsParam.SetOffset(0);    
    can1DlData.AddDataLinkParam(gpsParam);

    operatorIdParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_INT);
    operatorIdParam.SetSid(0x00);
    operatorIdParam.SetParamId(SecuritySystemCurrentSecurityIDParam::CatExtId);
    operatorIdParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT);
    operatorIdParam.SetVarLengthParamType(VarLengthDataLinkParamPool::CAT_EXT);
    operatorIdParam.SetParameterType(CDL2_VAR_NO_DSI);
    operatorIdParam.SetSid(0x00);
    operatorIdParam.SetScaling(0);
    operatorIdParam.SetOffset(0);
    intDlData.AddDataLinkParam(operatorIdParam);

    return true;
}

bool LpsSaTotalsTelemetryTest::executive() {
    static bool firstTime = true;

    PartNumbers partNumbers;
    partNumbers.SetProductIdNum("TST12345");
    partNumbersOutput_->publish(partNumbers);

    //  Latitude: 79.5 (90 - 10.5), Longitude: 124 (180 - 56)
    uint8_t gpsValue[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0xE, 0xEE, 0xEF, 0x27, 0xD2, 0x7D};
    gpsParam.SetVarLengthParamValue(&gpsValue[0], 14, 0);
    can1DlData.UpdateDataLinkParam(gpsParam);
    dataLinkDataOutput_->publish(can1DlData);
    can1DlData.HandleDataLinkDataMap();

    if (firstTime) {
        operatorIdParam.SetVarLengthParamValue(nullptr, 0, 0); // Set DSI without changing LastValue

        { // Fill in the data
            SecuritySystemCurrentSecurityIDParam idParam(operatorIdParam);
            idParam.setID(1234);
            idParam.setIDDescription("Frank");
        }
    }

    intDlData.UpdateDataLinkParam(operatorIdParam);
    dataLinkDataOutput_->publish(intDlData);
    intDlData.HandleDataLinkDataMap();

    if (firstTime)
    {
        LpsSaLoadRecordChannel loadRecord;
        auto& subtotal = loadRecord.getCurrentSubtotal();
        subtotal.truckId = 17;
        subtotal.truckName = "Beefy";
        subtotal.truckTargetWeightTonnes = 17.8;
        subtotal.materialId = 85;
        subtotal.materialName = "Granite";
        subtotal.materialDensity = 16.7;
        subtotal.addPass(5.5, 3, 15);
        subtotal.addPass(6.5, 3, 15);
        subtotal.addPass(9.1, 3, 15);
        subtotal.endTime.utcTime = std::chrono::system_clock::now();
        subtotal.endTime.shmTime = 20;
        lpsSaLoadRecordChannelOutput_->publish(loadRecord);
    }
    
    FileTransferBridgeRequest request;
    while (fileTransferBridgeRequestInput_->get(request))
    {
        AIS_LOG_ERROR("*** FileTransferBridgeRequest received");
        AIS_LOG_ERROR("TelematicsFileNumber: %u", request.fileAttr.TelematicsFileNumber);
        AIS_LOG_ERROR("DirPath: %s", request.fileAttr.DirPath.c_str());
        AIS_LOG_ERROR("Name: %s", request.fileAttr.Name.c_str());

        std::string outputStr;
        std::stringstream buffer;
        std::ifstream infile(request.fileAttr.DirPath + request.fileAttr.Name, std::ios::in | std::ios::binary);
        if (!infile)
        {
            AIS_LOG_ERROR("Cannot open input file.");
            return false;
        }
        buffer << infile.rdbuf();
        outputStr = buffer.str();
        infile.close();

        AIS_LOG_ERROR("File Size expected: %u actual: %u", request.fileAttr.SizeInBytes, outputStr.size());

        CAT::Telemetry::PcsCycle pcsCycle;
        pcsCycle.ParseFromString(outputStr);

        AIS_LOG_ERROR("**** Cycle time stamp Deserialized %lu ****", pcsCycle.message_timestamp());

        AIS_LOG_ERROR("cycle has_location %d", pcsCycle.has_location());
        if (pcsCycle.has_location())
        {
            AIS_LOG_ERROR("cycle has_latitude %d", pcsCycle.location().has_latitude());
            if (pcsCycle.location().has_latitude())
            {
                AIS_LOG_ERROR("cycle latitude %f", pcsCycle.location().latitude().value());
            }

            AIS_LOG_ERROR("cycle has_longitude %d", pcsCycle.location().has_longitude());
            if (pcsCycle.location().has_longitude())
            {
                AIS_LOG_ERROR("cycle longitude %f", pcsCycle.location().longitude().value());
            }
        }

        AIS_LOG_ERROR("cycle has_cycle_timestamp %d", pcsCycle.has_cycle_timestamp());
        if (pcsCycle.has_cycle_timestamp())
        {
            AIS_LOG_ERROR("cycle cycle_timestamp %d", pcsCycle.cycle_timestamp().value());
        }

        AIS_LOG_ERROR("cycle has_service_meter_units %d", pcsCycle.has_service_meter_units());
        if (pcsCycle.has_service_meter_units())
        {
            AIS_LOG_ERROR("cycle service_meter_units %d", pcsCycle.service_meter_units().value());
        }

        AIS_LOG_ERROR("cycle has_truck_weight %d", pcsCycle.has_truck_weight());
        if (pcsCycle.has_truck_weight())
        {
            AIS_LOG_ERROR("cycle truck_weight %f", pcsCycle.truck_weight().value());
        }

        AIS_LOG_ERROR("cycle has_truck_id %d", pcsCycle.has_truck_id());
        if (pcsCycle.has_truck_id())
        {
            AIS_LOG_ERROR("cycle truck_id %s", pcsCycle.truck_id().value().c_str());
        }

        AIS_LOG_ERROR("cycle has_blast_number %d", pcsCycle.has_blast_number());
        if (pcsCycle.has_blast_number())
        {
            AIS_LOG_ERROR("cycle blast_number %u", pcsCycle.blast_number().value());
        }

        AIS_LOG_ERROR("cycle has_loader_pass_count %d", pcsCycle.has_loader_pass_count());
        if (pcsCycle.has_loader_pass_count())
        {
            AIS_LOG_ERROR("cycle loader_pass_count %u", pcsCycle.loader_pass_count().value());
        }

        AIS_LOG_ERROR("cycle has_material_id %d", pcsCycle.has_material_id());
        if (pcsCycle.has_material_id())
        {
            AIS_LOG_ERROR("cycle material_id %u", pcsCycle.material_id().value());
        }

        AIS_LOG_ERROR("cycle has_load_site_id %d", pcsCycle.has_load_site_id());
        if (pcsCycle.has_load_site_id())
        {
            AIS_LOG_ERROR("cycle load_site_id %u", pcsCycle.load_site_id().value());
        }

        AIS_LOG_ERROR("cycle has_vims_user_info %d", pcsCycle.has_vims_user_info());
        if (pcsCycle.has_vims_user_info())
        {
            AIS_LOG_ERROR("cycle vims_user_info %s", pcsCycle.vims_user_info().value().c_str());
        }

        AIS_LOG_ERROR("cycle has_event_mask %d", pcsCycle.has_event_mask());
        if (pcsCycle.has_event_mask())
        {
            AIS_LOG_ERROR("cycle event_mask %d", pcsCycle.event_mask().reweigh_occurred());
            AIS_LOG_ERROR("cycle event_mask %d", pcsCycle.event_mask().bad_lift_included());
        }

        AIS_LOG_ERROR("cycle has_operator_id %d", pcsCycle.has_operator_id());
        if (pcsCycle.has_operator_id())
        {
            AIS_LOG_ERROR("cycle operator_id %u", pcsCycle.operator_id().value());
        }

        google::protobuf::ShutdownProtobufLibrary();
    }

    firstTime = false;
    return true;
}

void LpsSaTotalsTelemetryTest::cleanup() {
}
