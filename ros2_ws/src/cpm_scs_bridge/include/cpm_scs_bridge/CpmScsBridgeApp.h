/*******************************************************************************
FILE NAME: CpmScsBridgeApp.h
DESCRIPTION:
    Development-Plan.txt Step 7. JobMgr and WeighApp (Steps 4-6) are now
    fully DDS-native for every one of their own channels -- neither app
    touches raw SCS anymore. But several of those channels still need to
    reach peers that have NOT been migrated (legacy UI, hardware/OEL,
    DisplayApp). This app is that remaining real SCS-side participant: for
    each such leg it binds the real SCS interface (task::InterfaceDb, same
    as the apps used before Step 4/5 converted them) on one side and a
    ros2_wrapper object on the SAME topic name/type JobMgr or WeighApp
    already uses on the other, and relays between them once per tick.

    Built as a task::Task (like every other app in this tree) with an
    embedded rclcpp::Node, following the exact init/executive/cleanup
    pattern already used and verified in LpsSaJobMgrApp/LpsSaWeighApp.
*******************************************************************************/
#ifndef CPM_SCS_BRIDGE_APP_H
#define CPM_SCS_BRIDGE_APP_H

#include <string>

#include <ais/task/Task.h>

#include <rclcpp/rclcpp.hpp>

#include <cpm_common_interfaces/msg/lps_sa_job_mgr_reqst_channel.hpp>
#include <job_mgr_interfaces/msg/lps_sa_job_mgr_tx_channel.hpp>
#include <job_mgr_interfaces/msg/lps_sa_job_mgr_resp_channel.hpp>
#include <job_mgr_interfaces/msg/lps_sa_job_mgr_debug_channel.hpp>
#include <job_mgr_interfaces/msg/lps_sa_load_record_channel.hpp>
#include <job_mgr_interfaces/msg/output_channel.hpp>
#include <job_mgr_interfaces/msg/switch_input_scs.hpp>
#include <cpm_common_interfaces/msg/ais_jhm2_tx_channel.hpp>
#include <cpm_common_interfaces/msg/lps_sa_ui_display_state_interface.hpp>
#include <cpm_common_interfaces/msg/shm_clock_input.hpp>
#include <job_mgr_interfaces/msg/data_link_data.hpp>
#include <cpm_common_interfaces/msg/autonomy_condition_diagnostics_tx_channel.hpp>
#include <job_mgr_interfaces/msg/event_diagnostic_data.hpp>

#include <ros2_wrapper/RosInputInterface.h>
#include <ros2_wrapper/RosOutputInterface.h>

// Real SCS-side interface types (task::InterfaceDb::fetch/bind). Same
// headers LpsSaJobMgrApp.h included before Step 4 converted it away from
// them -- see that file's git history at commit cad392b for the pre-
// conversion baseline this list was taken from.
#include <interfaces/LpsSaJobMgrDebugChannel/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrTxChannel/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrReqstChannel/InterfaceTypes.h>
#include <interfaces/SwitchInputScs/InterfaceTypes.h>
#include <interfaces/OutputChannel/InterfaceTypes.h>
#include <interfaces/AisJhm2TxChannel/InterfaceTypes.h>
#include <interfaces/LpsSaLoadRecordChannel/Channel/Output/channel.h>
#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>
#include <interfaces/LpsSaJobMgrRespChannel/LpsSaJobMgrRespChannel.h>
#include <interfaces/LpsSaJobMgrReqstChannel/LpsSaJobMgrReqstChannel.h>
#include <interfaces/LpsSaJobMgrRespChannel/InterfaceTypes.h>
#include <interfaces/LpsSaUI/DisplayStateInterfaceInputChannel.h>
#include <interfaces/ShmClock/InterfaceTypes.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/AutonomyConditionDiagnostics/TxInterfaceInputChannel.h>
#include <interfaces/EventDiagnosticData/InterfaceTypes.h>

class CpmScsBridgeApp : public task::Task
{
public:
    explicit CpmScsBridgeApp( const std::string& taskName );
    virtual ~CpmScsBridgeApp( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

private:
    rclcpp::Node::SharedPtr rosNode_;
    rclcpp::executors::SingleThreadedExecutor executor_;

    /* ---- Publisher relays: ROS2 -> SCS (Bridge reads the DDS topic  ---- */
    /* ---- JobMgr already publishes to, writes onto the real SCS side) --- */

    ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>*   jobMgrTxIn_;
    LpsSaJobMgrTxChannelOutput*                                                       jobMgrTxScsOut_;

    ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>* jobMgrRespIn_;
    LpsSaJobMgrRespChannelOutput*                                                     jobMgrRespScsOut_;

    ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>* jobMgrDebugIn_;
    LpsSaJobMgrDebugChannelOutput*                                                     jobMgrDebugScsOut_;

    ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>* loadRecordIn_;
    LpsSaLoadRecordChannelOutputChannel*                                              loadRecordScsOut_;

    ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::OutputChannel>* outputChannelIn_;
    OutputChannelOutput*                                                     outputChannelScsOut_;

    /* ---- Subscriber relays: SCS -> ROS2 (Bridge reads the real SCS  ---- */
    /* ---- side, republishes onto the topic JobMgr already subscribes to) */

    LpsSaJobMgrReqstChannelInput*                                                        reqstChannelScsIn_;  // legacy/UI leg only
    ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>* reqstChannelOut_;

    SwitchInputScsInput*                                                    switchInputScsIn_;
    ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::SwitchInputScs>* switchInputOut_;

    AisJhm2TxChannelInput*                                                       aisJhm2TxScsIn_;
    ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::AisJhm2TxChannel>* aisJhm2TxOut_;

    LpsSaUIDisplayStateInterfaceInputChannel*                                                  displayStateScsIn_;
    ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface>* displayStateOut_;

    ShmClockInput*                                                             shmClockScsIn_;
    ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::ShmClockInput>* shmClockOut_;

    DataLinkDataInput*                                                     dataLinkDataScsIn_;
    ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::DataLinkData>* dataLinkDataOut_;

    AutonomyConditionDiagnosticsTxInterfaceInputChannel*                                              autonomyConditionDiagnosticsTxScsIn_;
    ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>* autonomyConditionDiagnosticsTxOut_;

    EventDiagnosticDataInput*                                                  eddtScsIn_;
    ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::EventDiagnosticData>* eddtOut_;

    /* One relay method per leg, called from executive(). Defined in
       JobMgrRelays.cpp. Each is a no-op if its SCS-side fetch/bind failed
       (nullptr-guarded), same convention LpsSaJobMgrApp uses for
       displayStateInput_/eddtInputChannel_. */
    void relayJobMgrTxChannel();
    void relayJobMgrRespChannel();
    void relayJobMgrDebugChannel();
    void relayLoadRecordChannel();
    void relayOutputChannel();

    void relayReqstChannel();
    void relaySwitchInputScs();
    void relayAisJhm2TxChannel();
    void relayDisplayState();
    void relayShmClock();
    void relayDataLinkData();
    void relayAutonomyConditionDiagnosticsTx();
    void relayEventDiagnosticData();
};

#endif // CPM_SCS_BRIDGE_APP_H
