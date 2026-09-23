#include "DataLinkDataPublish.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "demo_sim_model_if.h"
#include "demo_sim_a6n2_po.h"
#include "demo_sim_a6n2.h"


#ifdef __cplusplus
}
#endif


using namespace task;
constexpr uint32_t HYD_OIL_TEMP = 0x0045;
constexpr uint32_t P_M_FEATURE_ENABLE_STATUS = 0xD10EE7;
constexpr uint32_t SEA_LEVEL_2 = 0xD11884;
extern demo_sim_a6n2_catParameters_si_RAM_t demo_sim_a6n2_catParameters_si_RAM;
/******************************************************************************
FUNCTION NAME:getTaskImplementation
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
AbstractTaskCore* task::getTaskImplementation(void )
{
    static DemoApp thisTask("DemoApp");
    return &thisTask;
}


DemoApp::DemoApp( const std::string& taskName ):
    Task( taskName ),
    dlData_(),
    dataLinkDataOutput_(nullptr),
    DemoAppScsTxIn(nullptr),
    DemoAppScsTxout(nullptr),
    DemoAppScsReqstIn(nullptr),
    liftposition_(10.f),
    liftposition_rate_(15.f), // Maximum Raise Speed
    tiltposition_(100.f),
    tiltposition_rate_(30.f), // Maximum Rack Speed
    payload_(8.f),
    payload_rate_(20.f) {}

/*
 Destructor
 */
DemoApp::~DemoApp() {
}

/******************************************************************************
FUNCTION NAME:Initialize
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
bool DemoApp::initialize( )
{
    bool somethingWrong = true;
    if(!task::InterfaceDb::bind("DataLinkDataOutput", dataLinkDataOutput_)) {
        AIS_LOG_ERROR("No DataLinkDataOutput channel defined.");
        somethingWrong = false;
    }
    DemoAppScsTxout  = dynamic_cast<DemoAppTxChannelOutput*>( InterfaceDb::fetch("DemoAppTxChannelOutput"));
    DemoAppScsTxIn = dynamic_cast<DemoAppTxChannelInput*>( InterfaceDb::fetch("DemoAppTxChannelInput"));
    DemoAppScsReqstIn = dynamic_cast<DemoAppReqstChannelInput*>( InterfaceDb::fetch("DemoAppReqstChannelInput"));
    if ( !DemoAppScsTxIn ) {
        AIS_LOG_ERROR("Interface DemoAppScsTxIn not configured");
        somethingWrong = false;
    }
    if ( !DemoAppScsReqstIn ) {
        AIS_LOG_ERROR("SCS interface for Demo app not configured");
        somethingWrong = false;
    }
    if ( !DemoAppScsTxout ) {
        AIS_LOG_ERROR("Demo App Scs Tx out not configured");
        somethingWrong = false;
    }

    InitDataLinkData();
    demo_sim_a6n2_work.demo_sim_a6n2_M.demo_sim_a6n2_catParameters_si_RAM_p = &demo_sim_a6n2_catParameters_si_RAM;

    demo_sim_a6n2_po_init();

    return somethingWrong;
}

/******************************************************************************
FUNCTION NAME:executive
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
bool DemoApp::executive( )
{
    PublishDataLinkData();
    ReadDemoAppScsIn();
    ReadPWM_API();

    return true;
}

/******************************************************************************
FUNCTION NAME:InitDataLinkData
DESCRIPTION: Add PID's that we want to simulate over Data link
PARAMETER DESCRIPTION:
RETURN VALUE:none
*******************************************************************************/
void DemoApp::InitDataLinkData()
{
    //Add all pid's that you want to simulate here.
    //Hydraulic oil temp: (45)
    hydtempparam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_CDL);
    hydtempparam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
    hydtempparam.SetParameterType(CDL2_I16_DSI);
    hydtempparam.SetParamId(HYD_OIL_TEMP);
    hydtempparam.SetSid(0x2E);
    hydtempparam.SetScaling(1.0);
    hydtempparam.SetOffset(0);
    dlData_.AddDataLinkParam(hydtempparam);

    //Production Measurement Feature Enabled Status: (D10EE7)
    prodparam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_CDL);
    prodparam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
    prodparam.SetParameterType(CDL2_U8_DSI);
    prodparam.SetParamId(P_M_FEATURE_ENABLE_STATUS);
    prodparam.SetSid(0x2E);
    prodparam.SetScaling(1.0);
    prodparam.SetOffset(0);
    dlData_.AddDataLinkParam(prodparam);

    //SEA production measurement level 2 feature installation status: (D11884)
    seainstallparam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_CDL);
    seainstallparam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
    seainstallparam.SetParameterType(CDL2_U8_DSI);
    seainstallparam.SetParamId(SEA_LEVEL_2);
    seainstallparam.SetSid(0x2E);
    seainstallparam.SetScaling(1.0);
    seainstallparam.SetOffset(0);
    dlData_.AddDataLinkParam(seainstallparam);

    // Engine Speed
    engineSpeedParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_CDL);
    engineSpeedParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN);
    engineSpeedParam.SetParameterType(CDL2_VAR_NO_DSI);
    engineSpeedParam.SetVarLengthParamType(VarLengthDataLinkParamFactory::PGN);
    engineSpeedParam.SetParamId(61444);
    engineSpeedParam.SetSid(0x00);
    engineSpeedParam.SetScaling(1);
    engineSpeedParam.SetOffset(0);
    dlData_.AddDataLinkParam(engineSpeedParam);

    // Service Mode
    serviceModeParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_CDL);
    serviceModeParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
    serviceModeParam.SetParameterType(CDL2_U16_DSI);
    serviceModeParam.SetParamId(0xD1000E);
    serviceModeParam.SetSid(0x28);
    serviceModeParam.SetScaling(1);
    serviceModeParam.SetOffset(0);
    dlData_.AddDataLinkParam(serviceModeParam);

    // Total Fuel Used High Resolution
    totalFuelUsedHrParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_CDL);
    totalFuelUsedHrParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
    totalFuelUsedHrParam.SetParameterType(CDL2_U32_DSI);
    totalFuelUsedHrParam.SetParamId(0xFE5D);
    totalFuelUsedHrParam.SetSid(0x00);
    totalFuelUsedHrParam.SetScaling(0.001);
    totalFuelUsedHrParam.SetOffset(0);
    dlData_.AddDataLinkParam(totalFuelUsedHrParam);

    // Total Fuel Used Low Resolution
//    totalFuelUsedLrParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
//    totalFuelUsedLrParam.SetParameterType(CDL2_U32_DSI);
//    totalFuelUsedLrParam.SetParamId(0xC8);
//    totalFuelUsedLrParam.SetSid(0x00);
//    totalFuelUsedLrParam.SetScaling(0.125);
//    totalFuelUsedLrParam.SetOffset(0);
//    dlData_.AddDataLinkParam(totalFuelUsedLrParam);
}

/******************************************************************************
FUNCTION NAME:PublishDataLinkData
DESCRIPTION:Update values and publish data link data
PARAMETER DESCRIPTION:
RETURN VALUE:None
*******************************************************************************/
void DemoApp::PublishDataLinkData()
{
    //Set Hydraulic oil temp
    hydtempparam.SetLastValue(hyd_temp_value, 0);
    dlData_.UpdateDataLinkParam(hydtempparam);

    //Set SEA install status
    seainstallparam.SetLastValue(sea_level_2, 0);
    dlData_.UpdateDataLinkParam(seainstallparam);

    //Set Production measurement feature enable status:
    prodparam.SetLastValue(production_measurement, 0);
    dlData_.UpdateDataLinkParam(prodparam);

    { // Set engine speed
        // Set engine speed to 2000 RPM -> 0.125 RPM/bit -> 16000 bits -> 0x3E80
        uint8_t dataBuffer[] = { 0x00, 0x00, 0x00, 0x80, 0x3E, 0x00, 0x00, 0x00 };
        engineSpeedParam.SetVarLengthParamValue(dataBuffer, sizeof(dataBuffer)/sizeof(dataBuffer[0]), DataLinkParam::DSI_CODE_OK());
        dlData_.UpdateDataLinkParam(engineSpeedParam);
    }

    // Set Service Mode Status
    serviceModeParam.SetLastValue(0x000C, DataLinkParam::DSI_CODE_OK());
    dlData_.UpdateDataLinkParam(serviceModeParam);

    //Set Total Fuel Used High Resolution
    updateTotalFuel();
    totalFuelUsedHrParam.SetLastValue(total_fuel_used_, DataLinkParam::DSI_CODE_OK());
    dlData_.UpdateDataLinkParam(totalFuelUsedHrParam);

    dataLinkDataOutput_->publish(dlData_); // Publish data link data
    dlData_.HandleDataLinkDataMap();
    dlData_.ClearDlpDiagInfo();
}

void DemoApp::ReadPWM_API()
{
    DemoAppTxChannel pwm_in;
    pos_lift_desired = liftposition_;
    pos_lift_rate = liftposition_rate_;
    pos_tilt_desired = tiltposition_;
    pos_tilt_rate = tiltposition_rate_;
    payload_desired = payload_;
    payload_rate = payload_rate_;
    demo_sim_a6n2_po_0();

    {
        DemoAppTxChannel txout1;
        txout1.pres_lift_he_demo = angle_lift_het;   // Lift He Pressure (angle_lift_het = Lift He Pressure)
        txout1.pres_lift_re_demo = pres_lift_re;     // Lift Re pressure
        txout1.angle_lift_demo = angle_lift;
        txout1.angle_AFE_demo = angle_AFE;
        txout1.angle_ABC_demo = angle_ABC_supplement;
        txout1.liftposition = liftposition_;
        txout1.liftposition_rate = liftposition_rate_;
        txout1.tiltposition = tiltposition_;
        txout1.tiltposition_rate = tiltposition_rate_;
        txout1.payload = payload_;
        txout1.payload_rate = payload_rate_;
        DemoAppScsTxout->publish(txout1);
    }
}


void DemoApp::ReadDemoAppScsIn()
{
    DemoAppReqstChannel request;
    DemoAppTxChannel demoIn;
    while (DemoAppScsReqstIn->get(request)) {
        for (const auto& r : request.requests) {
            switch (r.command) {
            case (DemoAppReqstCommand::WRITE_LIFT_POSITION): {
                liftposition_ = r.liftposition();
                break;
            }
            case (DemoAppReqstCommand::WRITE_LIFT_POSITION_RATE): {
                liftposition_rate_ = r.liftposition_rate();
                break;
            }
            case (DemoAppReqstCommand::WRITE_TILT_POSITION): {
                tiltposition_ = r.tiltposition();
                break;
            }
            case (DemoAppReqstCommand::WRITE_TILT_POSITION_RATE): {
                tiltposition_rate_ = r.tiltposition_rate();
                break;
            }
            case (DemoAppReqstCommand::WRITE_PAYLOAD): {
                payload_ = r.payload();
                break;
            }
            case (DemoAppReqstCommand::WRITE_PAYLOAD_RATE): {
                payload_rate_ = r.payload_rate();
                break;
            }
            case (DemoAppReqstCommand::DIG): {
                payload_rate_ = 20.f;
                payload_ = r.weight1();
                tiltposition_ = 100.f;
                tiltposition_rate_ = 30.f; // Maximum Rack Speed
                liftposition_ = 10.f;
                liftposition_rate_ = 35.f; // Float Lower Speed
                break;
            }
            case (DemoAppReqstCommand::WRW): {
                liftposition_ = 90.f;
                liftposition_rate_ = 15.f; // Maximum Raise Speed
                break;
            }
            case (DemoAppReqstCommand::LLW): {
                liftposition_ = 45.f;
                liftposition_rate_ = 5.f; // Slow Raise Speed
                break;
            }
            case (DemoAppReqstCommand::DUMP): {
                tiltposition_ = 0.f;
                tiltposition_rate_ = 35.f; // Maximum Dump Speed
                break;
            }
            case (DemoAppReqstCommand::PDUMP): {
                payload_rate_ = 20.f;
                payload_ = r.weight1();
                tiltposition_ = 65.f;
                tiltposition_rate_ = 35.f; // Maximum Dump Speed
                break;
            }
            case (DemoAppReqstCommand::CARRY): {
                tiltposition_ = 100.f;
                tiltposition_rate_ = 30.f; // Maximum Rack Speed
                liftposition_ = 10.f;
                liftposition_rate_ = 35.f; // Float Lower Speed
                break;
            }
            case (DemoAppReqstCommand::NONE):
            default: {
                break;
            }
            }
        }
    }
}

/******************************************************************************
FUNCTION NAME:Demo App cleanup
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE: None
*******************************************************************************/
void  DemoApp::cleanup( )
{
    AIS_LOG_INFO("DemoApp::cleanup");
}
