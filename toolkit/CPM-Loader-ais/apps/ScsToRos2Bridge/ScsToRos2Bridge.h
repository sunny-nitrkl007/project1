/*******************************************************************************
** COPYRIGHT (C) 2026 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: ScsToRos2Bridge.h
DESCRIPTION:
    Provides bidirectional AIS SCS <-> ROS2/DDS forwarding for JobMgr and
    WeighApp migration channels. Each channel flow is bridged in exactly one
    direction to avoid feedback loops; DataLinkData is published on both a
    reduced JobMgr topic and a full-fidelity WeighApp topic.

    See porting_artefacts/plan.md and apps/ScsToRos2Bridge/README.md.
*******************************************************************************/
#ifndef SCSTOROS2BRIDGE_H
#define SCSTOROS2BRIDGE_H

#include <chrono>
#include <deque>
#include <memory>
#include "VP3BridgeSupport.h"
#include <string>

#include <ais/task/Task.h>
#include <ais/interfaces/ProcessHealth/InterfaceTypes.h>

#include <interfaces/LpsSaJobMgrReqstChannel/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrRespChannel/InterfaceTypes.h>
#include <interfaces/AisJhm2TxChannel/InterfaceTypes.h>
#include <interfaces/SwitchInputScs/InterfaceTypes.h>
#include <interfaces/LpsSaLoadRecordChannel/Channel/Output/channel.h>
#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>
#include <interfaces/LpsSaWeighReqstChannel/InterfaceTypes.h>
#include <interfaces/LpsSaWeighRespChannel/InterfaceTypes.h>
#include <interfaces/LpsSaWeighTxChannel/InterfaceTypes.h>
#include <interfaces/ShmClock/InterfaceTypes.h>
#include <interfaces/LpsSaUI/DisplayStateInterfaceInputChannel.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/AutonomyConditionDiagnostics/TxInterfaceInputChannel.h>
#include <interfaces/EventDiagnosticData/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrTxChannel/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrDebugChannel/InterfaceTypes.h>
#include <interfaces/OutputChannel/InterfaceTypes.h>
#include <interfaces/LpsSaWeighInitDebugChannel/InterfaceTypes.h>
#include <interfaces/DemoAppTxChannel/InterfaceTypes.h>
#include <interfaces/ReadyToFlashStatus/InterfaceTypes.h>
#include <interfaces/TipoffModelTestPoints/InterfaceTypes.h>
#include <interfaces/LpsSaTotals/PrinterCnfgInterfaceInputChannel.h>
#include <interfaces/SerialPrinter/RequestInterfaceInputChannel.h>
#include <ais/interfaces/SystemHardwareHealth/InterfaceTypes.h>
#include <ais/interfaces/SystemHardwareHealthRequest/InterfaceTypes.h>
#include <interfaces/PartNumbers/InterfaceTypes.h>
#include <interfaces/VP3Record/InterfaceTypes.h>
#include <interfaces/CreateFileRequest/InterfaceTypes.h>
#include <interfaces/AppReg/InterfaceTypes.h>
#include <interfaces/FileTransferBridgeRequest/InterfaceTypes.h>
#include <cpm_common_interfaces/msg/vp3_record.hpp>
#include <cpm_common_interfaces/msg/create_file_request.hpp>
#include <cpm_common_interfaces/msg/app_reg.hpp>
#include <cpm_common_interfaces/msg/file_transfer_bridge_request.hpp>
#include <interfaces/PwmInputChannels/InterfaceTypes.h>
#include <interfaces/WorkOrderAssist/TxInterfaceInputChannel.h>
#include <interfaces/CycleSeg/TxInterfaceInputChannel.h>
#include <interfaces/WidgetsDebugData/InterfaceTypes.h>
#include <interfaces/LpsSaUI/BEMSimStateInterfaceInputChannel.h>
#include <cpm_common_interfaces/msg/serial_printer_request.hpp>
#ifdef UNAVAILABLE
#undef UNAVAILABLE
#endif

#ifdef AVAILABLE
#undef AVAILABLE
#endif


/* ROS2/DDS wrapper + generated message headers */
#include "rclcpp/rclcpp.hpp"
#include "ros2wrapper/RosInputInterface.h"
#include "ros2wrapper/RosOutputInterface.h"
#include <cpm_common_interfaces/msg/lps_sa_job_mgr_reqst_channel.hpp>
#include <job_mgr_interfaces/msg/lps_sa_job_mgr_resp_channel.hpp>
#include <cpm_common_interfaces/msg/ais_jhm2_tx_channel.hpp>
#include <job_mgr_interfaces/msg/switch_input_scs.hpp>
#include <cpm_common_interfaces/msg/process_health.hpp>
#include <job_mgr_interfaces/msg/lps_sa_load_record_channel.hpp>
#include <cpm_common_interfaces/msg/lps_sa_weigh_reqst_channel.hpp>
#include <cpm_common_interfaces/msg/lps_sa_weigh_resp_channel.hpp>
#include <cpm_common_interfaces/msg/lps_sa_weigh_tx_channel.hpp>
#include <cpm_common_interfaces/msg/shm_clock_input.hpp>
#include <cpm_common_interfaces/msg/lps_sa_ui_display_state_interface.hpp>
#include <job_mgr_interfaces/msg/data_link_data.hpp>
#include <job_mgr_interfaces/msg/event_diagnostic_data.hpp>
#include <cpm_common_interfaces/msg/autonomy_condition_diagnostics_tx_channel.hpp>
#include <job_mgr_interfaces/msg/lps_sa_job_mgr_tx_channel.hpp>
#include <job_mgr_interfaces/msg/lps_sa_job_mgr_debug_channel.hpp>
#include <job_mgr_interfaces/msg/output_channel.hpp>
#include <weigh_app_interfaces/msg/lps_sa_weigh_init_debug_channel.hpp>
#include <weigh_app_interfaces/msg/demo_app_tx_channel.hpp>
#include <weigh_app_interfaces/msg/part_numbers.hpp>
#include <weigh_app_interfaces/msg/system_hardware_health_storage.hpp>
#include <weigh_app_interfaces/msg/system_hardware_health_request.hpp>
#include <weigh_app_interfaces/msg/ready_to_flash_status.hpp>
#include <weigh_app_interfaces/msg/lps_sa_weigh_debug_channel.hpp>
#include <weigh_app_interfaces/msg/data_link_data.hpp>
#include <interfaces/LpsSaWeighDebugChannel/InterfaceTypes.h>
#include <weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel.hpp>
#include <interfaces/LpsSaNvmCalDataChannel/InterfaceTypes.h>
#include <weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_data_channel.hpp>
#include <interfaces/LpsSaNvmCalOnTheFlyDataChannel/InterfaceTypes.h>
#include <weigh_app_interfaces/msg/cal_mgr_cmd_reqst.hpp>
#include <interfaces/CalMgrCmdReqst/InterfaceTypes.h>
#include <weigh_app_interfaces/msg/cal_mgr_cmd_resp.hpp>
#include <weigh_app_interfaces/msg/tipoff_model_test_points.hpp>
#include <weigh_app_interfaces/msg/lps_sa_totals_printer_cnfg.hpp>
#include <weigh_app_interfaces/msg/pwm_input_channels.hpp>
#include <cpm_common_interfaces/msg/work_order_assist_tx_channel.hpp>
#include <cpm_common_interfaces/msg/cycle_seg_tx_channel.hpp>
#include <cpm_common_interfaces/msg/widgets_debug_data.hpp>
#include <cpm_common_interfaces/msg/lps_sa_ui_bem_sim_state_interface.hpp>
#include <interfaces/CalMgrCmdResp/InterfaceTypes.h>

class ScsToRos2Bridge: public task::Task
{
public:
    ScsToRos2Bridge( const std::string& taskName );
    virtual ~ScsToRos2Bridge( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

private:
    /*----------------------------------------------------------------------
    ** AIS SCS side. Bound via InterfaceDb::bind, exactly like
    ** hornOnStoreTest.h binds LpsSaJobMgrReqstChannelOutput/
    ** LpsSaJobMgrTxChannelInput today -- real, working precedent in this
    ** repo for a standalone process binding these interface names.
    **--------------------------------------------------------------------*/
    LpsSaJobMgrReqstChannelInput*  jobMgrReqstScsIn_;   /* subscribe: requests from WorkOrderAssist / hornOnStoreTest / AisJhm2RequestProcessor / LpsSaWeighApp */
    LpsSaJobMgrRespChannelOutput*  jobMgrRespScsOut_;   /* publish: forwards JobMgr's ack to AutonomyConditionDiagnostics / AisJhm2RequestProcessor */
    AisJhm2TxChannelInput*         aisJhm2TxScsIn_;     /* subscribe: JHM2 dispatch data from AisJhm2RequestProcessor */
    SwitchInputScsOutput*          switchInputScsOut_;   /* publish: SwitchInputApp's ROS2 states to legacy ACD / aisXcpServer */
    ProcessHealthOutput* processHealthScsOut_;
    LpsSaLoadRecordChannelOutputChannel* loadRecordScsOut_; /* publish: forwards ROS2 load records to LpsSaTotalsApp/WorkOrderAssist/AisJhm2RequestProcessor */
    LpsSaWeighReqstChannelInput*   weighReqstScsIn_;    /* subscribe: requests from SCS producers */
    LpsSaWeighRespChannelOutput*   weighRespScsOut_;    /* publish: ROS2 responses to SCS consumers */
    LpsSaWeighTxChannelOutput*     weighTxScsOut_;      /* publish: ROS2 telemetry to SCS consumers */
    ShmClockInput*                  shmClockScsIn_;      /* subscribe: clock data from AIS SCS */
    LpsSaUIDisplayStateInterfaceInputChannel* displayStateScsIn_; /* subscribe: UI display state from AIS SCS */
    DataLinkDataInput* dataLinkDataScsIn_;
    AutonomyConditionDiagnosticsTxInterfaceInputChannel* autonomyConditionDiagnosticsTxScsIn_;
    EventDiagnosticDataInput* eventDiagnosticDataScsIn_;
    LpsSaJobMgrTxChannelOutput* jobMgrTxScsOut_;
    LpsSaJobMgrDebugChannelOutput* jobMgrDebugScsOut_;
    OutputChannelOutput* outputChannelScsOut_;
    LpsSaWeighInitDebugChannelOutput* weighInitDebugScsOut_;
    LpsSaWeighDebugChannelOutput*         weighDebugScsOut_;
    LpsSaNvmCalDataChannelOutput*         nvmCalDataScsOut_;
    LpsSaNvmCalOnTheFlyDataChannelOutput* nvmCalOnTheFlyDataScsOut_;
    CalMgrCmdReqstInput*                  calMgrCmdReqstScsIn_;       /* read cmd from ACD on AIS SCS -> forward to ROS2 WeighApp */
    CalMgrCmdRespOutput*                  calMgrCmdRespScsOut_;       /* write resp from ROS2 WeighApp -> AIS SCS ACD consumer */
    DemoAppTxChannelInput* demoAppTxScsIn_;
    PartNumbersInput* partNumbersScsIn_;
    TipoffModelTestPointsOutput*          tipoffTestPointsScsOut_;    /* write tipoff diagnostics from ROS2 WeighApp -> AIS SCS (no SCS reader since aisXcpServer moved to ROS2; kept by default) */
    LpsSaTotalsPrinterCnfgInterfaceInputChannel* printerCnfgScsIn_;  /* read printer cfg from AIS SCS LpsSaTotalsApp -> forward to ROS2 WeighApp */
    SystemHardwareHealthInput* systemHardwareHealthScsIn_;
    SystemHardwareHealthRequestOutput* systemHardwareHealthRequestScsIn_;
    ReadyToFlashStatusOutput* readyToFlashScsOut_;
    PwmInputChannelsInput* pwmInputChannelsScsIn_;  /* read PWM inputs from AIS SCS PwmInput -> forward to ROS2 aisXcpServer */
    WorkOrderAssistTxInterfaceInputChannel* workOrderAssistTxScsIn_;   /* AIS SCS WorkOrderAssist -> ROS2 aisXcpServer */
    CycleSegTxInterfaceInputChannel* cycleSegTxScsIn_;                 /* AIS SCS CycleSeg -> ROS2 aisXcpServer */
    WidgetsDebugDataInput* widgetsDebugDataScsIn_;                     /* AIS SCS WidgetApp -> ROS2 aisXcpServer */
    LpsSaUIBEMSimStateInterfaceInputChannel* bemSimStateScsIn_;        /* AIS SCS AisJhm2DataServer -> ROS2 aisXcpServer */

    /*----------------------------------------------------------------------
    ** ROS2 side. One shared node + executor for this process, mirroring
    ** the pattern already used in LpsSaJobMgrApp.h/LpsSaWeighApp.h.
    **--------------------------------------------------------------------*/
    rclcpp::Node::SharedPtr rosNode_;
    rclcpp::executors::SingleThreadedExecutor executor_;

    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>> jobMgrReqstRosOut_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>>       jobMgrRespRosIn_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::AisJhm2TxChannel>>         aisJhm2TxRosOut_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::SwitchInputScs>>               switchInputRosIn_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::ProcessHealth>> processHealthRosIn_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>>       loadRecordRosIn_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>>   weighReqstRosOut_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighRespChannel>>     weighRespRosIn_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighTxChannel>>       weighTxRosIn_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::ShmClockInput>>             shmClockRosOut_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface>> displayStateRosOut_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::DataLinkData>> dataLinkDataRosOut_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::DataLinkData>> weighAppDataLinkDataRosOut_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>> autonomyConditionDiagnosticsTxRosOut_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::EventDiagnosticData>> eventDiagnosticDataRosOut_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>> jobMgrTxRosIn_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>> jobMgrDebugRosIn_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::OutputChannel>> outputChannelRosIn_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel>> weighInitDebugRosIn_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::DemoAppTxChannel>> demoAppTxRosOut_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::PartNumbers>> partNumbersRosOut_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::SystemHardwareHealthStorage>> systemHardwareHealthRosOut_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::SystemHardwareHealthRequest>> systemHardwareHealthRequestRosIn_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::ReadyToFlashStatus>> readyToFlashRosIn_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaWeighDebugChannel>>         weighDebugRosIn_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel>>         nvmCalDataRosIn_;
    std::unique_ptr<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel>> nvmCalOnTheFlyDataRosIn_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::CalMgrCmdReqst>>                calMgrCmdReqstRosOut_; /* AIS SCS -> ROS2 (WeighApp subscriber) */
    std::unique_ptr<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::CalMgrCmdResp>>                  calMgrCmdRespRosIn_;   /* ROS2 -> AIS SCS (ACD consumer) */
    std::unique_ptr<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::TipoffModelTestPoints>>          tipoffTestPointsRosIn_;  /* ROS2 -> AIS SCS (no SCS reader since aisXcpServer moved to ROS2; kept by default) */
    std::unique_ptr<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg>>        printerCnfgRosOut_;      /* AIS SCS -> ROS2 (WeighApp subscriber) */
    VP3RecordInput* vp3RecordScsIn_ = nullptr;
    CreateFileRequestInput* createFileRequestScsIn_ = nullptr;
    AppRegInput* appRegScsIn_ = nullptr;
    AppRegOutput* appRegScsOut_ = nullptr;
    FileTransferBridgeRequestOutput* fileTransferScsOut_ = nullptr;
    SerialPrinterRequestInterfaceInputChannel* serialPrinterRequestScsIn_ = nullptr;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::VP3Record>> vp3RecordRosOut_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::CreateFileRequest>> createFileRequestRosOut_;
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::AppReg>> appRegRosOut_;
    rclcpp::Subscription<cpm_common_interfaces::msg::AppReg>::SharedPtr appRegRosIn_;
    rclcpp::Subscription<cpm_common_interfaces::msg::FileTransferBridgeRequest>::SharedPtr fileTransferRosIn_;
    std::deque<cpm_common_interfaces::msg::AppReg> appRegQueue_;
    std::deque<cpm_common_interfaces::msg::FileTransferBridgeRequest> fileTransferQueue_;
    vp3_bridge::DrainState vp3Drain_;
    bool initialized_ = false;
    bool cleanedUp_ = false;
    void forwardVP3();
    std::unique_ptr<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::PwmInputChannels>>              pwmInputChannelsRosOut_; /* AIS SCS -> ROS2 (aisXcpServer subscriber) */
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::WorkOrderAssistTxChannel>>    workOrderAssistTxRosOut_;  /* AIS SCS -> ROS2 (aisXcpServer subscriber) */
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::CycleSegTxChannel>>           cycleSegTxRosOut_;         /* AIS SCS -> ROS2 (aisXcpServer subscriber) */
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::WidgetsDebugData>>            widgetsDebugDataRosOut_;   /* AIS SCS -> ROS2 (aisXcpServer subscriber) */
    std::unique_ptr<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaUIBemSimStateInterface>> bemSimStateRosOut_;        /* AIS SCS -> ROS2 (aisXcpServer subscriber) */
    rclcpp::Publisher<cpm_common_interfaces::msg::SerialPrinterRequest>::SharedPtr serialPrinterRequestRosOut_;    
    void printGraphInfo();
    /* Conversion helpers -- pure, no side effects, no I/O. Static private
       methods rather than free functions so they stay scoped to this class
       instead of polluting translation-unit-global namespace. */
    static cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel convertJobMgrReqstToRos(const LpsSaJobMgrReqstChannel& scs);
    static LpsSaJobMgrRespChannel convertJobMgrRespToScs(const job_mgr_interfaces::msg::LpsSaJobMgrRespChannel& ros);
    static cpm_common_interfaces::msg::AisJhm2TxChannel convertAisJhm2TxToRos(const AisJhm2TxChannel& scs);
    static SwitchInputScs convertSwitchInputToScs(const job_mgr_interfaces::msg::SwitchInputScs& ros);
    static ProcessHealthMessage convertProcessHealthToScs(const cpm_common_interfaces::msg::ProcessHealth& ros);
    static LpsSaLoadRecordChannel convertLoadRecordToScs(const job_mgr_interfaces::msg::LpsSaLoadRecordChannel& ros);
    static cpm_common_interfaces::msg::LpsSaWeighReqstChannel convertWeighReqstToRos(const LpsSaWeighReqstChannel& scs);
    static LpsSaWeighRespChannel convertWeighRespToScs(const cpm_common_interfaces::msg::LpsSaWeighRespChannel& ros);
    static LpsSaWeighTxChannel convertWeighTxToScs(const cpm_common_interfaces::msg::LpsSaWeighTxChannel& ros);
    static cpm_common_interfaces::msg::ShmClockInput convertShmClockToRos(ShmClock& scs);
    static cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface convertDisplayStateToRos(const LpsSaUIDisplayStateInterface& scs);
    static job_mgr_interfaces::msg::DataLinkData convertDataLinkDataToRos(DataLinkData& scs);
    static weigh_app_interfaces::msg::DataLinkData convertWeighAppDataLinkDataToRos(DataLinkData& scs);
    static cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel convertAutonomyConditionDiagnosticsTxToRos(const AutonomyConditionDiagnosticsTxInterface& scs);
    static job_mgr_interfaces::msg::EventDiagnosticData convertEventDiagnosticDataToRos(EventDiagnosticData& scs);
    static LpsSaJobMgrTxChannel convertJobMgrTxToScs(const job_mgr_interfaces::msg::LpsSaJobMgrTxChannel& ros);
    static OutputChannel convertOutputChannelToScs(const job_mgr_interfaces::msg::OutputChannel& ros);
    static LpsSaWeighInitDebugChannel convertWeighInitDebugToScs(const weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel& ros);
    static weigh_app_interfaces::msg::DemoAppTxChannel convertDemoAppTxToRos(const DemoAppTxChannel& scs);
    static weigh_app_interfaces::msg::PartNumbers convertPartNumbersToRos(const PartNumbers& scs);
    static weigh_app_interfaces::msg::SystemHardwareHealthStorage convertSystemHardwareHealthToRos(const SystemHardwareHealth& scs);
    static SystemHardwareHealthRequest convertSystemHardwareHealthRequestToScs(const weigh_app_interfaces::msg::SystemHardwareHealthRequest& ros);
    static ReadyToFlashStatus convertReadyToFlashToScs(const weigh_app_interfaces::msg::ReadyToFlashStatus& ros);
    static LpsSaWeighDebugChannel convertWeighDebugToScs(const weigh_app_interfaces::msg::LpsSaWeighDebugChannel& ros);
    static LpsSaNvmCalDataChannel convertNvmCalDataToScs(const weigh_app_interfaces::msg::LpsSaNvmCalDataChannel& ros);
    static LpsSaNvmCalOnTheFlyDataChannel convertNvmCalOnTheFlyDataToScs(const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel& ros);
    static weigh_app_interfaces::msg::CalMgrCmdReqst convertCalMgrCmdReqstToRos(const CalMgrCmdReqst& scs);
    static CalMgrCmdResp convertCalMgrCmdRespToScs(const weigh_app_interfaces::msg::CalMgrCmdResp& ros);
    static TipoffModelTestPoints convertTipoffTestPointsToScs(const weigh_app_interfaces::msg::TipoffModelTestPoints& ros);
    static weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg convertPrinterCnfgToRos(const LpsSaTotalsPrinterCnfgInterface& scs);
    static weigh_app_interfaces::msg::PwmInputChannels convertPwmInputChannelsToRos(const PwmInputChannels& scs);
    static cpm_common_interfaces::msg::WorkOrderAssistTxChannel convertWorkOrderAssistTxToRos(const WorkOrderAssistTxInterface& scs);
    static cpm_common_interfaces::msg::CycleSegTxChannel convertCycleSegTxToRos(const CycleSegTxInterface& scs);
    static cpm_common_interfaces::msg::WidgetsDebugData convertWidgetsDebugDataToRos(const WidgetsDebugData& scs);
    static cpm_common_interfaces::msg::LpsSaUIBemSimStateInterface convertBemSimStateToRos(const LpsSaUIBEMSimStateInterface& scs);
    static cpm_common_interfaces::msg::SerialPrinterRequest convertSerialPrinterRequestToRos(const SerialPrinterRequestInterface& scs);
};

#endif
