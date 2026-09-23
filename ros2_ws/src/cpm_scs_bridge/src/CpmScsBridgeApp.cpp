/*******************************************************************************
FILE NAME: CpmScsBridgeApp.cpp
DESCRIPTION: see CpmScsBridgeApp.h
*******************************************************************************/
#include "cpm_scs_bridge/CpmScsBridgeApp.h"

#include <ais/AisLog.h>

using task::InterfaceDb;

CpmScsBridgeApp::CpmScsBridgeApp( const std::string& taskName ) :
    task::Task( taskName ),
    rosNode_(),
    executor_(),
    jobMgrTxIn_( nullptr ), jobMgrTxScsOut_( nullptr ),
    jobMgrRespIn_( nullptr ), jobMgrRespScsOut_( nullptr ),
    jobMgrDebugIn_( nullptr ), jobMgrDebugScsOut_( nullptr ),
    loadRecordIn_( nullptr ), loadRecordScsOut_( nullptr ),
    outputChannelIn_( nullptr ), outputChannelScsOut_( nullptr ),
    reqstChannelScsIn_( nullptr ), reqstChannelOut_( nullptr ),
    switchInputScsIn_( nullptr ), switchInputOut_( nullptr ),
    aisJhm2TxScsIn_( nullptr ), aisJhm2TxOut_( nullptr ),
    displayStateScsIn_( nullptr ), displayStateOut_( nullptr ),
    shmClockScsIn_( nullptr ), shmClockOut_( nullptr ),
    dataLinkDataScsIn_( nullptr ), dataLinkDataOut_( nullptr ),
    autonomyConditionDiagnosticsTxScsIn_( nullptr ), autonomyConditionDiagnosticsTxOut_( nullptr ),
    eddtScsIn_( nullptr ), eddtOut_( nullptr )
{
}

CpmScsBridgeApp::~CpmScsBridgeApp( )
{
}

/******************************************************************************
FUNCTION NAME: CpmScsBridgeApp::initialize
DESCRIPTION:
    Binds the real SCS side of each of JobMgr's 13 bridge legs (same
    InterfaceDb keys LpsSaJobMgrApp used before Step 4 converted it -- see
    that file's git history at commit cad392b) and constructs a
    ros2_wrapper object on the exact topic name/type JobMgr's own
    already-converted code uses for the same channel (verified against
    the working CPM-Loader-ais/apps/LpsSaJobMgrApp/LpsSaJobMgrApp.cpp).
    A leg with a failed SCS-side fetch/bind is left nullptr and its
    relay method becomes a no-op for that leg -- same convention
    LpsSaJobMgrApp uses for displayStateInput_/eddtInputChannel_.
*******************************************************************************/
bool CpmScsBridgeApp::initialize( )
{
    if (!rclcpp::ok()) {
        rclcpp::init(0, nullptr);
    }
    rosNode_ = std::make_shared<rclcpp::Node>("cpm_scs_bridge_node");
    executor_.add_node(rosNode_);

    /* ---- Publisher relays: ROS2 -> SCS ---- */

    jobMgrTxIn_     = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>(rosNode_, "lps_sa_job_mgr_tx_channel");
    jobMgrTxScsOut_ = dynamic_cast<LpsSaJobMgrTxChannelOutput*>( InterfaceDb::fetch("LpsSaJobMgrTxChannelOutput") );
    if (nullptr == jobMgrTxScsOut_) {
        AIS_LOG_ERROR("Interface LpsSaJobMgrTxChannelOutput not configured.");
    }

    jobMgrRespIn_     = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>(rosNode_, "lps_sa_job_mgr_resp_channel");
    jobMgrRespScsOut_ = dynamic_cast<LpsSaJobMgrRespChannelOutput*>( InterfaceDb::fetch("LpsSaJobMgrRespChannelOutput") );
    if (nullptr == jobMgrRespScsOut_) {
        AIS_LOG_ERROR("Interface LpsSaJobMgrRespChannelOutput not configured.");
    }

    jobMgrDebugIn_     = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>(rosNode_, "lps_sa_job_mgr_debug_channel");
    jobMgrDebugScsOut_ = dynamic_cast<LpsSaJobMgrDebugChannelOutput*>( InterfaceDb::fetch("LpsSaJobMgrDebugChannelOutput") );
    if (nullptr == jobMgrDebugScsOut_) {
        AIS_LOG_ERROR("Interface LpsSaJobMgrDebugChannelOutput not configured.");
    }

    loadRecordIn_     = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>(rosNode_, "load_record");
    loadRecordScsOut_ = dynamic_cast<LpsSaLoadRecordChannelOutputChannel*>( InterfaceDb::fetch("LoadRecordOutput") );
    if (nullptr == loadRecordScsOut_) {
        AIS_LOG_ERROR("Interface LoadRecordOutput not configured.");
    }

    outputChannelIn_     = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::OutputChannel>(rosNode_, "output_channel");
    outputChannelScsOut_ = dynamic_cast<OutputChannelOutput*>( InterfaceDb::fetch("OutputChannelOutput") );
    if (nullptr == outputChannelScsOut_) {
        AIS_LOG_ERROR("Interface OutputChannelOutput not configured.");
    }

    /* ---- Subscriber relays: SCS -> ROS2 ---- */

    reqstChannelScsIn_ = dynamic_cast<LpsSaJobMgrReqstChannelInput*>( InterfaceDb::fetch("LpsSaJobMgrReqstChannelInput") );
    if (nullptr == reqstChannelScsIn_) {
        AIS_LOG_ERROR("Interface LpsSaJobMgrReqstChannelInput not configured.");
    }
    reqstChannelOut_ = new ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>(rosNode_, "lps_sa_job_mgr_reqst_channel");

    switchInputScsIn_ = dynamic_cast<SwitchInputScsInput*>( InterfaceDb::fetch("SwitchInputScsInput") );
    if (nullptr == switchInputScsIn_) {
        AIS_LOG_ERROR("Interface SwitchInputScsInput not configured.");
    }
    switchInputOut_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::SwitchInputScs>(rosNode_, "switch_input_scs");

    aisJhm2TxScsIn_ = dynamic_cast<AisJhm2TxChannelInput*>( InterfaceDb::fetch("AisJhm2TxChannelInput") );
    if (nullptr == aisJhm2TxScsIn_) {
        AIS_LOG_ERROR("Interface AisJhm2TxChannelInput not configured.");
    }
    aisJhm2TxOut_ = new ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::AisJhm2TxChannel>(rosNode_, "ais_jhm2_tx_channel");

    if (!InterfaceDb::bind("DisplayStateInput", displayStateScsIn_)) {
        AIS_LOG_ERROR("Interface DisplayStateInput not configured.");
        displayStateScsIn_ = nullptr;
    }
    displayStateOut_ = new ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface>(rosNode_, "display_state");

    shmClockScsIn_ = dynamic_cast<ShmClockInput*>( InterfaceDb::fetch("ShmClockInput") );
    if (nullptr == shmClockScsIn_) {
        AIS_LOG_ERROR("Interface ShmClockInput not configured.");
    }
    shmClockOut_ = new ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::ShmClockInput>(rosNode_, "shm_clock");

    if (!InterfaceDb::bind("DataLinkDataInput", dataLinkDataScsIn_)) {
        AIS_LOG_ERROR("Interface DataLinkDataInput not configured.");
        dataLinkDataScsIn_ = nullptr;
    }
    dataLinkDataOut_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::DataLinkData>(rosNode_, "data_link_data");

    autonomyConditionDiagnosticsTxScsIn_ = dynamic_cast<AutonomyConditionDiagnosticsTxInterfaceInputChannel*>( InterfaceDb::fetch("AutonomyConditionDiagnosticsTxChannelInput") );
    if (nullptr == autonomyConditionDiagnosticsTxScsIn_) {
        AIS_LOG_ERROR("Interface AutonomyConditionDiagnosticsTxChannelInput not configured.");
    }
    autonomyConditionDiagnosticsTxOut_ = new ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>(rosNode_, "autonomy_condition_diagnostics_tx_channel");

    if (!InterfaceDb::bind("EventDiagnosticDataInput", eddtScsIn_)) {
        AIS_LOG_ERROR("Interface EventDiagnosticDataInput not configured.");
        eddtScsIn_ = nullptr;
    }
    eddtOut_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::EventDiagnosticData>(rosNode_, "event_diagnostic_data");

    return true;
}

/******************************************************************************
FUNCTION NAME: CpmScsBridgeApp::executive
DESCRIPTION: Drains pending DDS messages, then runs each leg's relay once.
    Same single-thread/no-mutex reasoning as LpsSaJobMgrApp::executive() --
    spin_some() and every get()/publish() below run synchronously on this
    one thread, once per tick.
*******************************************************************************/
bool CpmScsBridgeApp::executive( )
{
    executor_.spin_some();

    relayJobMgrTxChannel();
    relayJobMgrRespChannel();
    relayJobMgrDebugChannel();
    relayLoadRecordChannel();
    relayOutputChannel();

    relayReqstChannel();
    relaySwitchInputScs();
    relayAisJhm2TxChannel();
    relayDisplayState();
    relayShmClock();
    relayDataLinkData();
    relayAutonomyConditionDiagnosticsTx();
    relayEventDiagnosticData();

    return true;
}

void CpmScsBridgeApp::cleanup( )
{
    AIS_LOG_INFO("CpmScsBridgeApp::cleanup");
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}
