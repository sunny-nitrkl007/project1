/**
***************************************************************************
* @file XcpServerTask.cpp
* A simple task to use as an empty starting point
*
* Copyright 2010
*
* National Robotics Engineering Center, Carnegie Mellon University
* 10 40th Street, Pittsburgh, PA 15201
* www.rec.ri.cmu.edu
*
* Control Instructions (who can see this code): NREC Confidential.
* Not for public release unless permission granted by program manager.
*
* Usage Rights (who can use this code): Usage allowed for all NREC
* programs with permissions from author and program manager.
*
* This notice must appear in all copies of this file and its derivatives.
*
* Created under Program: ACRS
*
* History of Significant Contributions (don't put commit logs here):
* 2010-10-22 cbaker@rec.ri.cmu.edu  Created file.
***************************************************************************
*/
#include <unistd.h>

#include <map>

#include <boost/filesystem.hpp>

#include "ROS2Logger.hpp"

#include "xcp_server/XCPServer.h"
#include "xcpServerDb_private.h"

#include "XcpServerTask.h"

namespace fs = boost::filesystem;

#define XCP_SERVER_APP_LOG_ROOT (R"(/opt/appdata/CPM/debug)")

#define XCP_SERVER_APP_TOA_LOG_PATH (R"(/opt/appdata/CPM/debug/toa_log.csv)")

// 12 TOA per hour, 10 hours, 80 bytes per TOA = 9600 bytes per shift
#define XCP_SERVER_APP_TOA_LOG_MAX_SIZE (10000)
//#define XCP_SERVER_APP_TOA_LOG_MAX_SIZE (300)

static void makeAppLogRoot()
{
    boost::system::error_code ec;

    // Make sure the directory exists
    fs::create_directories(XCP_SERVER_APP_LOG_ROOT, ec);

    if (ec) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Cannot create %s directory for logging.", XCP_SERVER_APP_LOG_ROOT);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Constructs an instance of this class.
///
///////////////////////////////////////////////////////////////////////////////
XcpServerTask::XcpServerTask(const std::string &taskName) :
        ros2_wrapper::Ros2TaskWrapper(taskName),
        m_xcpScsInputs(),
        toaLogging(),
        rosInputs_()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys this class
///
///////////////////////////////////////////////////////////////////////////////
XcpServerTask::~XcpServerTask()
{
    cleanupRosInterfaces();
}

template<typename Msg>
bool XcpServerTask::createRosInput(const rclcpp::Node::SharedPtr& rosNode,
        ros2_wrapper::RosInputInterface<Msg>*& input, const std::string& topic, size_t qosDepth)
{
    input = new ros2_wrapper::RosInputInterface<Msg>(rosNode, topic, qosDepth);
    if (!input) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "%s ROS2 input not initialized.", topic.c_str());
        return false;
    }
    return true;
}

template<typename Msg>
bool XcpServerTask::createRosInput(const rclcpp::Node::SharedPtr& rosNode,
        ros2_wrapper::RosInputInterface<Msg>*& input, const std::string& topic, const rclcpp::QoS& qos)
{
    input = new ros2_wrapper::RosInputInterface<Msg>(rosNode, topic, qos);
    if (!input) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "%s ROS2 input not initialized.", topic.c_str());
        return false;
    }
    return true;
}

void XcpServerTask::cleanupRosInterfaces()
{
    // Unbind first: m_xcpScsInputs holds non-owning pointers to these inputs.
    m_xcpScsInputs.stop();

    delete rosInputs_.systemHardwareHealth;
    delete rosInputs_.weighReqst;
    delete rosInputs_.weighResp;
    delete rosInputs_.weighTx;
    delete rosInputs_.weighDebug;
    delete rosInputs_.weighInitDebug;
    delete rosInputs_.nvmCalData;
    delete rosInputs_.nvmCalOnTheFlyData;
    delete rosInputs_.jobMgrTx;
    delete rosInputs_.pwmInputChannels;
    delete rosInputs_.jobMgrReqst;
    delete rosInputs_.jobMgrResp;
    delete rosInputs_.jobMgrDebug;
    delete rosInputs_.switchInput;
    delete rosInputs_.cycleSegTx;
    delete rosInputs_.workOrderAssistTx;
    delete rosInputs_.tipoffModelTestPoints;
    delete rosInputs_.autonomyConditionDiagnosticsTx;
    delete rosInputs_.bemSimState;
    delete rosInputs_.displayState;
    delete rosInputs_.widgetsDebugData;
    delete rosInputs_.dataLinkData;
    rosInputs_ = XcpScsInputs::RosInputs();
}

bool XcpServerTask::initialize()
{
    { // Default matches config/XcpServerTask.rb: "loggerThreshold" => "error"
        declare_parameter<std::string>("logger_threshold", "error");
        ROS2Logger::Instance().SetLogLevel(get_parameter("logger_threshold").as_string());
    }

    { // Default matches commonTaskParams.rb on non-AUTO ECMs (A7H4): "scheduler" => SCHED_OTHER;
      // no "schedulerPriority" for SCHED_OTHER, so 0.
        declare_parameter<std::string>("scheduler", "SCHED_OTHER");
        declare_parameter<int>("scheduler_priority", 0);
        if (!applyRealtimeScheduling(get_parameter("scheduler").as_string(),
                                     static_cast<int>(get_parameter("scheduler_priority").as_int()))) {
            RCLCPP_WARN(ROS2Logger::Instance().GetLogger(), "Continuing without real-time scheduling.");
        }
    }

    RCLCPP_INFO(ROS2Logger::Instance().GetLogger(), "Hello from %s", get_name() );

    /* Former config/XcpServerTask.rb "ScsRxTimeouts" section: "<Input>_rxTimeout_sec" in seconds.
       MachineInput has no publisher (see XcpScsInputs::initReadInterface), so its timeout is not a parameter. */
    static const struct { const char* key; const char* parameter; double defaultValue; } kRxTimeouts[] = {
        { "AutonomyConditionDiagnosticsTxInput_rxTimeout_sec", "scs_rx_timeouts.autonomy_condition_diagnostics_tx_input_rx_timeout_sec", 5.0 },
        { "SystemHardwareHealthInput_rxTimeout_sec", "scs_rx_timeouts.system_hardware_health_input_rx_timeout_sec", 5.0 },
        { "LpsSaWeighReqstChannelInput_rxTimeout_sec", "scs_rx_timeouts.lps_sa_weigh_reqst_channel_input_rx_timeout_sec", 5.0 },
        { "LpsSaWeighRespChannelInput_rxTimeout_sec", "scs_rx_timeouts.lps_sa_weigh_resp_channel_input_rx_timeout_sec", 5.0 },
        { "LpsSaWeighTxChannelInput_rxTimeout_sec", "scs_rx_timeouts.lps_sa_weigh_tx_channel_input_rx_timeout_sec", 5.0 },
        { "LpsSaWeighDebugChannelInput_rxTimeout_sec", "scs_rx_timeouts.lps_sa_weigh_debug_channel_input_rx_timeout_sec", 5.0 },
        { "LpsSaNvmCalDataChannelInput_rxTimeout_sec", "scs_rx_timeouts.lps_sa_nvm_cal_data_channel_input_rx_timeout_sec", 5.0 },
        { "LpsSaNvmCalOnTheFlyDataChannelInput_rxTimeout_sec", "scs_rx_timeouts.lps_sa_nvm_cal_on_the_fly_data_channel_input_rx_timeout_sec", 5.0 },
        { "LpsSaWeighInitDebugChannelInput_rxTimeout_sec", "scs_rx_timeouts.lps_sa_weigh_init_debug_channel_input_rx_timeout_sec", 5.0 },
        { "LpsSaJobMgrTxChannelInput_rxTimeout_sec", "scs_rx_timeouts.lps_sa_job_mgr_tx_channel_input_rx_timeout_sec", 5.0 },
        { "PwmInputChannelsInput_rxTimeout_sec", "scs_rx_timeouts.pwm_input_channels_input_rx_timeout_sec", 5.0 },
        { "LpsSaJobMgrReqstChannelInput_rxTimeout_sec", "scs_rx_timeouts.lps_sa_job_mgr_reqst_channel_input_rx_timeout_sec", 5.0 },
        { "LpsSaJobMgrRespChannelInput_rxTimeout_sec", "scs_rx_timeouts.lps_sa_job_mgr_resp_channel_input_rx_timeout_sec", 5.0 },
        { "LpsSaJobMgrDebugChannelInput_rxTimeout_sec", "scs_rx_timeouts.lps_sa_job_mgr_debug_channel_input_rx_timeout_sec", 5.0 },
        { "SwitchInputScsInput_rxTimeout_sec", "scs_rx_timeouts.switch_input_scs_input_rx_timeout_sec", 5.0 },
        { "WorkOrderAssistTxInput_rxTimeout_sec", "scs_rx_timeouts.work_order_assist_tx_input_rx_timeout_sec", 10.0 },
        { "DisplayStateInput_rxTimeout_sec", "scs_rx_timeouts.display_state_input_rx_timeout_sec", 10.0 },
        { "CycleSegTxChannelInput_rxTimeout_sec", "scs_rx_timeouts.cycle_seg_tx_channel_input_rx_timeout_sec", 10.0 },
        { "WidgetsDebugDataInput_rxTimeout_sec", "scs_rx_timeouts.widgets_debug_data_input_rx_timeout_sec", 10.0 },
        { "TipoffModelTestPointsInput_rxTimeout_sec", "scs_rx_timeouts.tipoff_model_test_points_input_rx_timeout_sec", 10.0 },
        { "BEMSimStateInput_rxTimeout_sec", "scs_rx_timeouts.bem_sim_state_input_rx_timeout_sec", 10.0 },
    };
    std::map<std::string, double> cs;
    for (const auto& rxTimeout : kRxTimeouts) {
        declare_parameter<double>(rxTimeout.parameter, rxTimeout.defaultValue);
        cs[rxTimeout.key] = get_parameter(rxTimeout.parameter).as_double();
    }

    /* ROS2 inputs replacing the SCS bindings of config/XcpServerTask.rb. The last argument is the
       DDS history depth: max(10, AIS channel queueSize); the queueSize itself is applied by
       XcpScsInputs::initReadInterface(). The NVM calibration snapshot is published once by WeighApp
       with transient_local durability, so it is received even if this node starts or matches later. */
    auto rosNode = shared_from_this();
    bool everythingOk = true;
    everythingOk = createRosInput(rosNode, rosInputs_.systemHardwareHealth, "system_hardware_health", 100) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.weighReqst, "lps_sa_weigh_reqst_channel", 20) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.weighResp, "lps_sa_weigh_resp_channel", 20) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.weighTx, "lps_sa_weigh_tx_channel", 20) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.weighDebug, "lps_sa_weigh_debug_channel", 10) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.weighInitDebug, "lps_sa_weigh_init_debug_channel", 10) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.nvmCalData, "lps_sa_nvm_cal_data_channel",
            rclcpp::QoS(1).transient_local()) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.nvmCalOnTheFlyData, "lps_sa_nvm_cal_on_the_fly_data_channel", 10) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.jobMgrTx, "lps_sa_job_mgr_tx_channel", 20) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.pwmInputChannels, "pwm_input_channels", 30) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.jobMgrReqst, "lps_sa_job_mgr_reqst_channel", 20) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.jobMgrResp, "lps_sa_job_mgr_resp_channel", 20) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.jobMgrDebug, "lps_sa_job_mgr_debug_channel", 10) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.switchInput, "switch_input_scs", 10) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.cycleSegTx, "cycle_seg_tx_channel", 10) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.workOrderAssistTx, "work_order_assist_tx_channel", 10) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.tipoffModelTestPoints, "tipoff_model_test_points", 20) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.autonomyConditionDiagnosticsTx, "autonomy_condition_diagnostics_tx_channel", 10) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.bemSimState, "lps_sa_ui_bem_sim_state_interface", 10) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.displayState, "lps_sa_ui_display_state_interface", 10) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.widgetsDebugData, "widgets_debug_data", 20) && everythingOk;
    everythingOk = createRosInput(rosNode, rosInputs_.dataLinkData, "weigh_app_data_link_data", 30) && everythingOk;
    if (!everythingOk) {
        return false;
    }

    m_xcpScsInputs.initReadInterface( rosInputs_, cs );

    xcpServerDbInit(m_xcpScsInputs.db);

    makeAppLogRoot();

    toaLogging.init(XCP_SERVER_APP_TOA_LOG_PATH, XCP_SERVER_APP_TOA_LOG_MAX_SIZE);

    return true; // false causes the application to bail
}

void XcpServerTask::startExecutiveTimer()
{
    // Default matches config/XcpServerTask.rb: "cycleRate_hz" => 100
    // (must stay 100 Hz: both XCP servers declare one 10 ms DAQ event, xcpServerDb.cpp).
    declare_parameter<double>("cycle_rate_hz", 100.0);
    createExecutiveTimer(get_parameter("cycle_rate_hz").as_double());
}

bool XcpServerTask::executive()
{
    RCLCPP_INFO(ROS2Logger::Instance().GetLogger(), "%s: executive  (pid: %d)", get_name(), getpid());

    // this is where you do periodic work
    xcpServerDbUpdate();

    m_xcpScsInputs.update();

    toaLogging.update(
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.tipoff_assist_active,
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.tipoff_assist_active_eid,
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.truck_start_weight,
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.truck_target_weight,
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.disp_best_bkt_wt.val,
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.disp_best_bkt_wt.is_ok,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.tipoff_inputs.tilt_valve_cmd,
            m_xcpScsInputs.m_lpsSaWeighTxChannel.lift_position.angle,
            m_xcpScsInputs.m_lpsSaWeighTxChannel.tilt_position.bucket_angle,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.tipoff_outputs.weigh_status_out,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.tipoff_outputs.arbitrated_payload_norm_error_out,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.tipoff_outputs.payload_norm_stdev_out,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.tipoff_outputs.unsecured_pfw_status,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.tipoff_outputs.unsecured_payload_upper_bound_norm,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.tipoff_outputs.unsecured_payload_lower_bound_norm);

    return true; // false again causes the application to bail
}

void XcpServerTask::cleanup()
{
    RCLCPP_INFO(ROS2Logger::Instance().GetLogger(), "%s: cleanup  (pid: %d)", get_name(), getpid());

    executiveTimer_.reset();

    // this is where you would clean up your allocated resources (if any)
    xcpServerDbCleanup();

    cleanupRosInterfaces();

    return; // you can't really fail to "clean up"
}

int main(int argc, char** argv)
{
    return ros2_wrapper::Ros2TaskWrapper::run<XcpServerTask>(argc, argv);
}
