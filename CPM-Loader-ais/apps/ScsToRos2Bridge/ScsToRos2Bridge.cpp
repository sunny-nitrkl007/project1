/*******************************************************************************
** COPYRIGHT (C) 2026 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: ScsToRos2Bridge.cpp
DESCRIPTION: See ScsToRos2Bridge.h for the design rationale.
*******************************************************************************/
#include "ScsToRos2Bridge.h"

#include <bitset>

#include <interfaces/LpsSaWeighReqstChannel/InterfaceTypes.h>
#include <interfaces/LpsSaWeighRespChannel/InterfaceTypes.h>
#include <interfaces/LpsSaWeighTxChannel/InterfaceTypes.h>
#include <cpm_common_interfaces/msg/lps_sa_weigh_reqst_channel.hpp>
#include <cpm_common_interfaces/msg/lps_sa_weigh_resp_channel.hpp>
#include <cpm_common_interfaces/msg/lps_sa_weigh_tx_channel.hpp>

using namespace task;

cpm_common_interfaces::msg::LpsSaWeighReqstChannel ScsToRos2Bridge::convertWeighReqstToRos(const LpsSaWeighReqstChannel& scs)
{
    cpm_common_interfaces::msg::LpsSaWeighReqstChannel ros;
    ros.app_name = scs.appName;
    ros.app_request_id = scs.appRequestId;
    ros.command.value = static_cast<uint8_t>(scs.command);
    ros.arg_b = scs.arg.b;
    ros.arg_f1 = scs.arg.f1;
    ros.arg_f2 = scs.arg.f2;
    ros.arg_s = scs.arg.s;
    ros.arg_u = scs.arg.u;
    ros.arg_map.reserve(scs.arg.map.size());
    for (const auto& value : scs.arg.map) {
        cpm_common_interfaces::msg::FloatPair pair;
        pair.first = value.first;
        pair.second = value.second;
        ros.arg_map.push_back(pair);
    }
    return ros;
}

LpsSaWeighRespChannel ScsToRos2Bridge::convertWeighRespToScs(const cpm_common_interfaces::msg::LpsSaWeighRespChannel& ros)
{
    LpsSaWeighRespChannel scs;
    scs.appName = ros.app_name;
    scs.appRequestId = ros.app_request_id;
    scs.timePoint = std::chrono::steady_clock::time_point(
            std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::nanoseconds(ros.time_point_ns)));
    scs.command = static_cast<LpsSaWeighReqstChannel::Command>(ros.command.value);
    scs.success = ros.success;
    scs.arg1 = ros.arg1;
    return scs;
}

LpsSaWeighTxChannel ScsToRos2Bridge::convertWeighTxToScs(const cpm_common_interfaces::msg::LpsSaWeighTxChannel& ros)
{
    LpsSaWeighTxChannel scs;

    scs.timePoint = std::chrono::steady_clock::time_point(
            std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::nanoseconds(ros.time_point_ns)));
    scs.DigStat = static_cast<LpsWeighBktDigStat_t>(ros.dig_stat);
    scs.CalStat = static_cast<LpsWeighCalStatus_t>(ros.cal_stat);
    scs.DumpStat = static_cast<LpsWeighBktDumpStat_t>(ros.dump_stat);
    scs.BestBktWtInTonnes = ros.best_bkt_wt_in_tonnes;
    scs.WarmupLiftsRequired = ros.warmup_lifts_required;
    scs.PayloadCalcMeth = ros.payload_calc_meth;
    scs.bktWtLatchedFlag = ros.bkt_wt_latched_flag;
    scs.latchConditionsMet = ros.latch_conditions_met;
    scs.zeroAvailable = ros.zero_available;
    scs.Payload.payloadRatioRaw = ros.payload.payload_ratio_raw;
    scs.Payload.payloadRatio = ros.payload.payload_ratio;
    scs.Payload.payloadRatioStatus = static_cast<LpsSaPayloadRatioStatus_t>(ros.payload.payload_ratio_status);
    scs.LftSealStatus.sealed = ros.lft_seal_status.sealed;
    scs.LftSealStatus.sealTime = std::chrono::system_clock::time_point(
            std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::nanoseconds(ros.lft_seal_status.seal_time_ns)));
    scs.LftSealStatus.sealId = ros.lft_seal_status.seal_id;
    scs.flashEnabled = ros.flash_enabled;

    scs.LiftPositionSensorId = ros.lift_position_sensor_id;
    scs.TiltPositionSensorId = ros.tilt_position_sensor_id;
    scs.LiftHeadEndPressureSensorId = ros.lift_head_end_pressure_sensor_id;
    scs.LiftRodEndPressureSensorId = ros.lift_rod_end_pressure_sensor_id;
    scs.HydraulicOilTemperatureSensorId = ros.hydraulic_oil_temperature_sensor_id;
    scs.ImuSensorId = ros.imu_sensor_id;
    scs.WorkToolId = ros.work_tool_id;
    scs.ImplementSerialNum = ros.implement_serial_num;

    scs.LiftPosition.angle = ros.lift_position.angle;
    scs.LiftPosition.percentAngle = ros.lift_position.percent_angle;
    scs.LiftPosition.cylinderLength = ros.lift_position.cylinder_length;
    scs.LiftPosition.percentCylinderLength = ros.lift_position.percent_cylinder_length;
    scs.LiftPosition.cylinderExtension = ros.lift_position.cylinder_extension;
    scs.LiftPosition.status = static_cast<LpsStat_t>(ros.lift_position.status);
    scs.LiftCylVel.Stat = static_cast<LpsStat_t>(ros.lift_cyl_vel.stat);
    scs.LiftCylVel.Val = ros.lift_cyl_vel.val;
    scs.TiltPosition.angle = ros.tilt_position.angle;
    scs.TiltPosition.percentAngle = ros.tilt_position.percent_angle;
    scs.TiltPosition.cylinderLength = ros.tilt_position.cylinder_length;
    scs.TiltPosition.percentCylinderLength = ros.tilt_position.percent_cylinder_length;
    scs.TiltPosition.cylinderExtension = ros.tilt_position.cylinder_extension;
    scs.TiltPosition.bucketAngle = ros.tilt_position.bucket_angle;
    scs.TiltPosition.status = static_cast<LpsStat_t>(ros.tilt_position.status);
    scs.WeighRange.WeighRangeBottom = ros.weigh_range.weigh_range_bottom;
    scs.WeighRange.WeighRangeSize = ros.weigh_range.weigh_range_size;
    scs.Indicator = static_cast<LpsWeighRangeIndicator_t>(ros.indicator);
    scs.CalWt = ros.cal_wt;
    scs.LiftStalled = ros.lift_stalled;
    scs.LiftValveCommand.Stat = static_cast<LpsStat_t>(ros.lift_valve_command.stat);
    scs.LiftValveCommand.Val = ros.lift_valve_command.val;
    scs.TiltValveCommand.Stat = static_cast<LpsStat_t>(ros.tilt_valve_command.stat);
    scs.TiltValveCommand.Val = ros.tilt_valve_command.val;
    scs.ZeroWeight = ros.zero_weight;
    scs.SimpleCalAdjust = ros.simple_cal_adjust;
    scs.EngineSpeedRPM = ros.engine_speed_rpm;
    scs.EventState = std::bitset<ACDEventPopUp::NUM_BITS>(ros.event_state.bits);
    scs.DiagState = std::bitset<ACDDiagPopUp::NUM_BITS>(ros.diag_state.bits);
    scs.InfoState = std::bitset<ACDInfoPopUp::NUM_BITS>(ros.info_state.bits);
    scs.ShowExclamationPoint = ros.show_exclamation_point;
    scs.ExcessivePitch = ros.excessive_pitch;
    scs.BucketFullyRacked = ros.bucket_fully_racked;

    scs.PidData.OverloadWarningEnabled = ros.pid_data.overload_warning_enabled;
    scs.PidData.MachineRearLateralAcceleration = ros.pid_data.machine_rear_lateral_acceleration;
    scs.PidData.MachineRearLongitudinalAcceleration = ros.pid_data.machine_rear_longitudinal_acceleration;
    scs.PidData.MachineRearVerticalAcceleration = ros.pid_data.machine_rear_vertical_acceleration;
    scs.PidData.MachinePitch = ros.pid_data.machine_pitch;
    scs.PidData.MachineSlope = ros.pid_data.machine_slope;
    scs.PidData.MachineRearRoll = ros.pid_data.machine_rear_roll;
    scs.PidData.MachineRearSideSlope = ros.pid_data.machine_rear_side_slope;
    scs.PidData.MachineRoll = ros.pid_data.machine_roll;
    scs.PidData.MachineSideSlope = ros.pid_data.machine_side_slope;
    scs.PidData.TipoffPitchCalOffset = ros.pid_data.tipoff_pitch_cal_offset;
    scs.PidData.HydOilTempEnabled = ros.pid_data.hyd_oil_temp_enabled;
    scs.PidData.AudibleWeightEnabled = ros.pid_data.audible_weight_enabled;
    scs.PidData.AudibleWeightCommand = static_cast<LpsSaWeighTxChannel::AudibleAnnunciationPriority_t>(ros.pid_data.audible_weight_command);
    scs.PidData.PloadSysCalWtEntryReqStat = static_cast<PloadSysCalWtEntryReqStat_t>(ros.pid_data.pload_sys_cal_wt_entry_req_stat);
    scs.PidData.LastPloadWt = ros.pid_data.last_pload_wt;
    scs.PidData.PloadSysZeroStat = static_cast<PloadSysZeroStat_t>(ros.pid_data.pload_sys_zero_stat);
    scs.PidData.LdrPayloadStat = ros.pid_data.ldr_payload_stat;
    scs.PidData.LoaderBktPloadTgtWt = ros.pid_data.loader_bkt_pload_tgt_wt;
    scs.PidData.LoaderBktPloadTgtWtPer = ros.pid_data.loader_bkt_pload_tgt_wt_per;
    scs.PidData.PloadSysZeroReqStat = ros.pid_data.pload_sys_zero_req_stat;
    scs.PidData.ProdMeasureWeighStatus = ACDWeighStatus::type(ros.pid_data.prod_measure_weigh_status);
    scs.PidData.BktPayloadData = static_cast<BktPayloadData_t>(ros.pid_data.bkt_payload_data);
    scs.PidData.QR_HydOilTempMin_C = ros.pid_data.qr_hyd_oil_temp_min_c;
    scs.PidData.QR_LiftCylVelMin_mm_sec = ros.pid_data.qr_lift_cyl_vel_min_mm_sec;
    scs.PidData.QR_LiftCylVelMax_mm_sec = ros.pid_data.qr_lift_cyl_vel_max_mm_sec;
    scs.PidData.ProdMeasureSensorStatus.LiftLinkDC = ros.pid_data.prod_measure_sensor_status.lift_link_dc;
    scs.PidData.ProdMeasureSensorStatus.LiftCylPos = ros.pid_data.prod_measure_sensor_status.lift_cyl_pos;
    scs.PidData.ProdMeasureSensorStatus.LiftCylHEPres = ros.pid_data.prod_measure_sensor_status.lift_cyl_he_pres;
    scs.PidData.ProdMeasureSensorStatus.LiftCylREPres = ros.pid_data.prod_measure_sensor_status.lift_cyl_re_pres;
    scs.PidData.ProdMeasureSensorStatus.TiltSensorConfig = static_cast<LpsSaWeighTxChannel::TiltSensorConfig_t>(ros.pid_data.prod_measure_sensor_status.tilt_sensor_config);
    scs.PidData.ProdMeasureSensorStatus.TiltCylHEPres = ros.pid_data.prod_measure_sensor_status.tilt_cyl_he_pres;
    scs.PidData.ProdMeasureSensorStatus.TiltCylREPres = ros.pid_data.prod_measure_sensor_status.tilt_cyl_re_pres;
    scs.PidData.ProdMeasureSensorStatus.TiltLinkDC = ros.pid_data.prod_measure_sensor_status.tilt_link_dc;
    scs.PidData.ProdMeasureSensorStatus.HydOilTemp = ros.pid_data.prod_measure_sensor_status.hyd_oil_temp;
    scs.PidData.LinkSensorCalLim.LiftPosSensorDC = ros.pid_data.link_sensor_cal_lim.lift_pos_sensor_dc;
    scs.PidData.LinkSensorCalLim.LiftPosSensorFullRaiseDC = ros.pid_data.link_sensor_cal_lim.lift_pos_sensor_full_raise_dc;
    scs.PidData.LinkSensorCalLim.LiftPosSensorFullLowerDC = ros.pid_data.link_sensor_cal_lim.lift_pos_sensor_full_lower_dc;
    scs.PidData.LinkSensorCalLim.TiltPosSensorDC = ros.pid_data.link_sensor_cal_lim.tilt_pos_sensor_dc;
    scs.PidData.LinkSensorCalLim.TiltPosSensorFullRackDC = ros.pid_data.link_sensor_cal_lim.tilt_pos_sensor_full_rack_dc;
    scs.PidData.LinkSensorCalLim.TiltPosSensorFullDumpDC = ros.pid_data.link_sensor_cal_lim.tilt_pos_sensor_full_dump_dc;

    scs.CAN11MessageTimeoutFlag = ros.can11_message_timeout_flag;
    scs.ToaAnchoredZeroOffset = ros.toa_anchored_zero_offset;
    scs.ToaAnchoredFactor = ros.toa_anchored_factor;
    scs.ToaAnchorStatus = static_cast<LpsSaWeighTxChannel::ToaAnchorStatus_t>(ros.toa_anchor_status);
    scs.PayloadCalInProgress = ros.payload_cal_in_progress;
    scs.TestStatus = static_cast<LpsSaWeighTxChannel::TestStatus_t>(ros.test_status);
    return scs;
}

/******************************************************************************
FUNCTION NAME:task::getTaskImplementation
*******************************************************************************/
AbstractTaskCore* task::getTaskImplementation(void)
{
    rclcpp::init(0, nullptr);
    std::cout << "[ROS2][Initialized][JOB_MGR_SCS_ROS2_BRIDGE]";
    static ScsToRos2Bridge thisTask("ScsToRos2Bridge");
    return dynamic_cast<Task *>(&thisTask);
}

/******************************************************************************
FUNCTION NAME:ScsToRos2Bridge::ScsToRos2Bridge()
*******************************************************************************/
ScsToRos2Bridge::ScsToRos2Bridge(const std::string& taskName):
    Task(taskName),
    jobMgrReqstScsIn_(nullptr),
    jobMgrRespScsOut_(nullptr),
    aisJhm2TxScsIn_(nullptr),
    switchInputScsIn_(nullptr),
    loadRecordScsOut_(nullptr),
    weighReqstScsIn_(nullptr),
    weighRespScsOut_(nullptr),
    weighTxScsOut_(nullptr),
    shmClockScsIn_(nullptr),
    displayStateScsIn_(nullptr),
    dataLinkDataScsIn_(nullptr),
    autonomyConditionDiagnosticsTxScsIn_(nullptr),
    eventDiagnosticDataScsIn_(nullptr),
    jobMgrTxScsOut_(nullptr),
    jobMgrDebugScsOut_(nullptr),
    outputChannelScsOut_(nullptr),
    weighInitDebugScsOut_(nullptr),
    weighDebugScsOut_(nullptr),
    nvmCalDataScsOut_(nullptr),
    nvmCalOnTheFlyDataScsOut_(nullptr),
    calMgrCmdReqstScsIn_(nullptr),
    calMgrCmdRespScsOut_(nullptr),
    demoAppTxScsIn_(nullptr),
    partNumbersScsIn_(nullptr),
    tipoffTestPointsScsOut_(nullptr),
    printerCnfgScsIn_(nullptr),
    systemHardwareHealthScsIn_(nullptr),
    systemHardwareHealthRequestScsIn_(nullptr),
    readyToFlashScsOut_(nullptr),
    rosNode_(nullptr),
    executor_(),
    jobMgrReqstRosOut_(),
    jobMgrRespRosIn_(),
    aisJhm2TxRosOut_(),
    switchInputRosOut_(),
    loadRecordRosIn_(),
    weighReqstRosOut_(),
    weighRespRosIn_(),
    weighTxRosIn_(),
    shmClockRosOut_(),
    displayStateRosOut_(),
    dataLinkDataRosOut_(),
    weighAppDataLinkDataRosOut_(),
    autonomyConditionDiagnosticsTxRosOut_(),
    eventDiagnosticDataRosOut_(),
    jobMgrTxRosIn_(),
    jobMgrDebugRosIn_(),
    outputChannelRosIn_(),
    weighInitDebugRosIn_(),
    demoAppTxRosOut_(),
    partNumbersRosOut_(),
    systemHardwareHealthRosOut_(),
    systemHardwareHealthRequestRosIn_(),
    readyToFlashRosIn_(),
    weighDebugRosIn_(),
    nvmCalDataRosIn_(),
    nvmCalOnTheFlyDataRosIn_(),
    calMgrCmdReqstRosOut_(),
    calMgrCmdRespRosIn_(),
    tipoffTestPointsRosIn_(),
    printerCnfgRosOut_()
{
}

/******************************************************************************
FUNCTION NAME:ScsToRos2Bridge::~ScsToRos2Bridge()
*******************************************************************************/
ScsToRos2Bridge::~ScsToRos2Bridge()
{
}

/******************************************************************************
FUNCTION NAME:ScsToRos2Bridge::initialize
DESCRIPTION: Binds the AIS SCS side (same interface names LpsSaJobMgrApp used
    to bind before its ROS2-only cutover) and sets up the ROS2 side (same
    topic names LpsSaJobMgrApp already publishes/subscribes on).
*******************************************************************************/
bool ScsToRos2Bridge::initialize()
{
    bool everythingOk = true;

    getLogger().log_info("ScsToRos2Bridge::initialize");

    rosNode_ = std::make_shared<rclcpp::Node>("job_mgr_scs_ros2_bridge_node");
    executor_.add_node(rosNode_);

    /* AIS SCS side */
    if (!task::InterfaceDb::bind("LpsSaJobMgrReqstChannelInput", jobMgrReqstScsIn_)) {
        AIS_LOG_ERROR("LpsSaJobMgrReqstChannelInput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("LpsSaJobMgrRespChannelOutput", jobMgrRespScsOut_)) {
        AIS_LOG_ERROR("LpsSaJobMgrRespChannelOutput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("AisJhm2TxChannelInput", aisJhm2TxScsIn_)) {
        AIS_LOG_ERROR("AisJhm2TxChannelInput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("SwitchInputScsInput", switchInputScsIn_)) {
        AIS_LOG_ERROR("SwitchInputScsInput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("LoadRecordOutput", loadRecordScsOut_)) {
        AIS_LOG_ERROR("LoadRecordOutput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("LpsSaWeighReqstChannelInput", weighReqstScsIn_)) {
        AIS_LOG_ERROR("LpsSaWeighReqstChannelInput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("LpsSaWeighRespChannelOutput", weighRespScsOut_)) {
        AIS_LOG_ERROR("LpsSaWeighRespChannelOutput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("LpsSaWeighTxChannelOutput", weighTxScsOut_)) {
        AIS_LOG_ERROR("LpsSaWeighTxChannelOutput Interface not configured.");
        everythingOk = false;
    }

    /* ShmClockInput remains on the bridge's AIS SCS side; WeighApp consumes the ROS2 topic. */
    if (!task::InterfaceDb::bind("ShmClockInput", shmClockScsIn_)) {
        AIS_LOG_ERROR("ShmClockInput Interface not configured.");
        everythingOk = false;
    }

    /* DisplayStateInput remains on the bridge's AIS SCS side; WeighApp consumes the ROS2 topic. */
    if (!task::InterfaceDb::bind("DisplayStateInput", displayStateScsIn_)) {
        AIS_LOG_ERROR("DisplayStateInput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("DataLinkDataInput", dataLinkDataScsIn_)) {
        AIS_LOG_ERROR("DataLinkDataInput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("AutonomyConditionDiagnosticsTxChannelInput", autonomyConditionDiagnosticsTxScsIn_)) {
        AIS_LOG_ERROR("AutonomyConditionDiagnosticsTxChannelInput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("EventDiagnosticDataInput", eventDiagnosticDataScsIn_)) {
        AIS_LOG_ERROR("EventDiagnosticDataInput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("CalMgrCmdReqstInput", calMgrCmdReqstScsIn_)) {
        AIS_LOG_ERROR("CalMgrCmdReqstInput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("PrinterCnfgInput", printerCnfgScsIn_)) {
        AIS_LOG_ERROR("PrinterCnfgInput Interface not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("LpsSaJobMgrTxChannelOutput", jobMgrTxScsOut_) ||
            !task::InterfaceDb::bind("LpsSaJobMgrDebugChannelOutput", jobMgrDebugScsOut_) ||
            !task::InterfaceDb::bind("OutputChannelOutput", outputChannelScsOut_) ||
            !task::InterfaceDb::bind("LpsSaWeighInitDebugChannelOutput", weighInitDebugScsOut_) ||
            !task::InterfaceDb::bind("LpsSaWeighDebugChannelOutput", weighDebugScsOut_) ||
            !task::InterfaceDb::bind("LpsSaNvmCalDataChannelOutput", nvmCalDataScsOut_) ||
            !task::InterfaceDb::bind("LpsSaNvmCalOnTheFlyDataChannelOutput", nvmCalOnTheFlyDataScsOut_) ||
            !task::InterfaceDb::bind("CalMgrCmdRespOutput", calMgrCmdRespScsOut_) ||
            !task::InterfaceDb::bind("TipoffModelTestPointsOutput", tipoffTestPointsScsOut_)) {
        AIS_LOG_ERROR("One or more SCS output interfaces are not configured.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("DemoAppTxChannelInput", demoAppTxScsIn_) ||
            !task::InterfaceDb::bind("PartNumbersInput", partNumbersScsIn_) ||
            !task::InterfaceDb::bind("SystemHardwareHealthInput", systemHardwareHealthScsIn_) ||
            !task::InterfaceDb::bind("SystemHardwareHealthRequestOutput", systemHardwareHealthRequestScsIn_) ||
            !task::InterfaceDb::bind("ReadyToFlashStatusOutput", readyToFlashScsOut_)) {
        AIS_LOG_ERROR("One or more weigh-app migration SCS interfaces are not configured.");
        everythingOk = false;
    }

    /* ROS2 side -- topic names matching what LpsSaJobMgrApp subscribes/publishes */
    jobMgrReqstRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>>(
            rosNode_, "lps_sa_job_mgr_reqst_channel");
    jobMgrRespRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>>(
            rosNode_, "lps_sa_job_mgr_resp_channel");
    aisJhm2TxRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::AisJhm2TxChannel>>(
            rosNode_, "ais_jhm2_tx_channel");
    switchInputRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::SwitchInputScs>>(
            rosNode_, "switch_input_scs");
    loadRecordRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>>(
            rosNode_, "lps_sa_load_record_channel");
    weighReqstRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>>(
            rosNode_, "lps_sa_weigh_reqst_channel");
    weighRespRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighRespChannel>>(
            rosNode_, "lps_sa_weigh_resp_channel");
    weighTxRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighTxChannel>>(
            rosNode_, "lps_sa_weigh_tx_channel");
    shmClockRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::ShmClockInput>>(
            rosNode_, "shm_clock_input");
    displayStateRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface>>(
            rosNode_, "lps_sa_ui_display_state_interface");
    dataLinkDataRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::DataLinkData>>(
            rosNode_, "data_link_data");
    weighAppDataLinkDataRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::DataLinkData>>(
            rosNode_, "weigh_app_data_link_data");
    autonomyConditionDiagnosticsTxRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>>(
            rosNode_, "autonomy_condition_diagnostics_tx_channel");
    eventDiagnosticDataRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::EventDiagnosticData>>(
            rosNode_, "event_diagnostic_data");
    jobMgrTxRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>>(
            rosNode_, "lps_sa_job_mgr_tx_channel");
    jobMgrDebugRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>>(
            rosNode_, "lps_sa_job_mgr_debug_channel");
    outputChannelRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::OutputChannel>>(
            rosNode_, "output_channel");
    weighInitDebugRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel>>(
            rosNode_, "lps_sa_weigh_init_debug_channel");
    demoAppTxRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::DemoAppTxChannel>>(
            rosNode_, "demo_app_tx_channel");
    partNumbersRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::PartNumbers>>(
            rosNode_, "part_numbers");
    systemHardwareHealthRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::SystemHardwareHealthStorage>>(
            rosNode_, "system_hardware_health");
    systemHardwareHealthRequestRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::SystemHardwareHealthRequest>>(
            rosNode_, "system_hardware_health_request");
    readyToFlashRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::ReadyToFlashStatus>>(
            rosNode_, "ready_to_flash_status");
    weighDebugRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaWeighDebugChannel>>(
            rosNode_, "lps_sa_weigh_debug_channel");
    nvmCalDataRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel>>(
            rosNode_, "lps_sa_nvm_cal_data_channel");
    nvmCalOnTheFlyDataRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel>>(
            rosNode_, "lps_sa_nvm_cal_on_the_fly_data_channel");
    calMgrCmdReqstRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::CalMgrCmdReqst>>(
            rosNode_, "cal_mgr_cmd_reqst");
    calMgrCmdRespRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::CalMgrCmdResp>>(
            rosNode_, "cal_mgr_cmd_resp");
    tipoffTestPointsRosIn_ = std::make_unique<ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::TipoffModelTestPoints>>(
            rosNode_, "tipoff_model_test_points");
    printerCnfgRosOut_ = std::make_unique<ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg>>(
            rosNode_, "lps_sa_totals_printer_cnfg");

    if (!jobMgrReqstRosOut_ || !jobMgrRespRosIn_ || !aisJhm2TxRosOut_ || !switchInputRosOut_ || !loadRecordRosIn_ ||
            !weighReqstRosOut_ || !weighRespRosIn_ || !weighTxRosIn_) {
        AIS_LOG_ERROR("Failed to initialize one or more ROS2 wrapper interfaces.");
        everythingOk = false;
    }

    if (!shmClockRosOut_) {
        AIS_LOG_ERROR("Failed to initialize ShmClock ROS2 wrapper interface.");
        everythingOk = false;
    }

    if (!displayStateRosOut_) {
        AIS_LOG_ERROR("Failed to initialize DisplayState ROS2 wrapper interface.");
        everythingOk = false;
    }

    if (!dataLinkDataRosOut_ || !weighAppDataLinkDataRosOut_ || !autonomyConditionDiagnosticsTxRosOut_ || !eventDiagnosticDataRosOut_) {
        AIS_LOG_ERROR("Failed to initialize one or more ROS2 diagnostic input bridge interfaces.");
        everythingOk = false;
    }

    if (!jobMgrTxRosIn_ || !jobMgrDebugRosIn_ || !outputChannelRosIn_ || !weighInitDebugRosIn_ ||
            !weighDebugRosIn_ || !nvmCalDataRosIn_ || !nvmCalOnTheFlyDataRosIn_ ||
            !calMgrCmdReqstRosOut_ || !calMgrCmdRespRosIn_ ||
            !tipoffTestPointsRosIn_ || !printerCnfgRosOut_) {
        AIS_LOG_ERROR("Failed to initialize one or more ROS2 output bridge interfaces.");
        everythingOk = false;
    }

    if (!demoAppTxRosOut_ || !partNumbersRosOut_ || !systemHardwareHealthRosOut_ ||
            !systemHardwareHealthRequestRosIn_ || !readyToFlashRosIn_) {
        AIS_LOG_ERROR("Failed to initialize one or more weigh-app migration ROS2 interfaces.");
        everythingOk = false;
    }

    // Print the Node and topic details for debugging purpose. 
    printGraphInfo();    

    return everythingOk;
}

/******************************************************************************
FUNCTION NAME:ScsToRos2Bridge::executive
DESCRIPTION: Drains each side and forwards to the other, one direction per
    channel (see ScsToRos2Bridge.h for the direction table).
*******************************************************************************/
bool ScsToRos2Bridge::executive()
{
    executor_.spin_some();

    /* Forward 1: LpsSaJobMgrReqstChannel, AIS SCS -> ROS2 */
    if (nullptr != jobMgrReqstScsIn_) {
        LpsSaJobMgrReqstChannel reqScs;
        while (jobMgrReqstScsIn_->get(reqScs)) {
            cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel reqRos = convertJobMgrReqstToRos(reqScs);
            if (!jobMgrReqstRosOut_->publish(reqRos)) {
                AIS_LOG_ERROR("Failed to forward LpsSaJobMgrReqstChannel SCS->ROS2");
            }
        }
    }

    /* Forward 2: LpsSaJobMgrRespChannel, ROS2 -> AIS SCS */
    if (nullptr != jobMgrRespRosIn_) {
        job_mgr_interfaces::msg::LpsSaJobMgrRespChannel respRos;
        while (jobMgrRespRosIn_->get(respRos)) {
            LpsSaJobMgrRespChannel respScs = convertJobMgrRespToScs(respRos);
            if (nullptr != jobMgrRespScsOut_) {
                if (!jobMgrRespScsOut_->publish(respScs)) {
                    AIS_LOG_ERROR("Failed to forward LpsSaJobMgrRespChannel ROS2->SCS");
                }
            }
        }
    }

    /* Forward 3: AisJhm2TxChannel, AIS SCS -> ROS2 */
    if (nullptr != aisJhm2TxScsIn_) {
        AisJhm2TxChannel jhmScs;
        while (aisJhm2TxScsIn_->get(jhmScs)) {
            cpm_common_interfaces::msg::AisJhm2TxChannel jhmRos = convertAisJhm2TxToRos(jhmScs);
            if (!aisJhm2TxRosOut_->publish(jhmRos)) {
                AIS_LOG_ERROR("Failed to forward AisJhm2TxChannel SCS->ROS2");
            }
        }
    }

    /* Forward 4: SwitchInputScs, AIS SCS -> ROS2 */
    if (nullptr != switchInputScsIn_) {
        SwitchInputScs swScs;
        while (switchInputScsIn_->get(swScs)) {
            job_mgr_interfaces::msg::SwitchInputScs swRos = convertSwitchInputToRos(swScs);
            if (!switchInputRosOut_->publish(swRos)) {
                AIS_LOG_ERROR("Failed to forward SwitchInputScs SCS->ROS2");
            }
        }
    }

    /* Forward 5: LpsSaLoadRecordChannel, ROS2 -> AIS SCS */
    if (nullptr != loadRecordRosIn_) {
        job_mgr_interfaces::msg::LpsSaLoadRecordChannel lrRos;
        while (loadRecordRosIn_->get(lrRos)) {
            LpsSaLoadRecordChannel lrScs = convertLoadRecordToScs(lrRos);
            if (nullptr != loadRecordScsOut_) {
                if (!loadRecordScsOut_->publish(lrScs)) {
                    AIS_LOG_ERROR("Failed to forward LpsSaLoadRecordChannel ROS2->SCS");
                }
            }
        }
    }

    /* Forward 6: LpsSaWeighReqstChannel, AIS SCS -> ROS2 */
    if (nullptr != weighReqstScsIn_) {
        LpsSaWeighReqstChannel reqScs;
        while (weighReqstScsIn_->get(reqScs)) {
            cpm_common_interfaces::msg::LpsSaWeighReqstChannel reqRos = convertWeighReqstToRos(reqScs);
            if (nullptr != weighReqstRosOut_ && !weighReqstRosOut_->publish(reqRos)) {
                AIS_LOG_ERROR("Failed to forward LpsSaWeighReqstChannel SCS->ROS2");
            }
        }
    }

    /* Forward 7: LpsSaWeighRespChannel, ROS2 -> AIS SCS */
    if (nullptr != weighRespRosIn_) {
        cpm_common_interfaces::msg::LpsSaWeighRespChannel respRos;
        while (weighRespRosIn_->get(respRos)) {
            LpsSaWeighRespChannel respScs = convertWeighRespToScs(respRos);
            if (nullptr != weighRespScsOut_ && !weighRespScsOut_->publish(respScs)) {
                AIS_LOG_ERROR("Failed to forward LpsSaWeighRespChannel ROS2->SCS");
            }
        }
    }

    /* Forward 8: LpsSaWeighTxChannel, ROS2 -> AIS SCS */
    if (nullptr != weighTxRosIn_) {
        cpm_common_interfaces::msg::LpsSaWeighTxChannel txRos;
        while (weighTxRosIn_->get(txRos)) {
            LpsSaWeighTxChannel txScs = convertWeighTxToScs(txRos);
            if (nullptr != weighTxScsOut_ && !weighTxScsOut_->publish(txScs)) {
                AIS_LOG_ERROR("Failed to forward LpsSaWeighTxChannel ROS2->SCS");
            }
        }
    }

    /* Forward 9: ShmClock, AIS SCS -> ROS2 for WeighApp/JobMgr subscribers */
    if (nullptr != shmClockScsIn_) {
        ShmClock shmClockScs;
        while (shmClockScsIn_->get(shmClockScs)) {
            cpm_common_interfaces::msg::ShmClockInput shmClockRos = convertShmClockToRos(shmClockScs);
            if (nullptr != shmClockRosOut_ && !shmClockRosOut_->publish(shmClockRos)) {
                AIS_LOG_ERROR("Failed to forward ShmClock SCS->ROS2");
            }
        }
    }

    /* Forward 10: DisplayStateInput, AIS SCS -> ROS2 for WeighApp/JobMgr subscribers */
    if (nullptr != displayStateScsIn_) {
        LpsSaUIDisplayStateInterface displayStateScs;
        while (displayStateScsIn_->get(displayStateScs)) {
            cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface displayStateRos = convertDisplayStateToRos(displayStateScs);
            if (nullptr != displayStateRosOut_ && !displayStateRosOut_->publish(displayStateRos)) {
                AIS_LOG_ERROR("Failed to forward DisplayStateInput SCS->ROS2");
            }
        }
    }

    /* Forward 11: DataLinkData, AIS SCS -> ROS2 */
    if (nullptr != dataLinkDataScsIn_) {
        DataLinkData dataLinkDataScs;
        while (dataLinkDataScsIn_->get(dataLinkDataScs)) {
            job_mgr_interfaces::msg::DataLinkData dataLinkDataRos = convertDataLinkDataToRos(dataLinkDataScs);
            if (nullptr != dataLinkDataRosOut_ && !dataLinkDataRosOut_->publish(dataLinkDataRos)) {
                AIS_LOG_ERROR("Failed to forward DataLinkData SCS->ROS2");
            }

            weigh_app_interfaces::msg::DataLinkData weighAppDataLinkDataRos = convertWeighAppDataLinkDataToRos(dataLinkDataScs);
            if (nullptr != weighAppDataLinkDataRosOut_ && !weighAppDataLinkDataRosOut_->publish(weighAppDataLinkDataRos)) {
                AIS_LOG_ERROR("Failed to forward WeighApp DataLinkData SCS->ROS2");
            }
        }
    }

    /* Forward 12: AutonomyConditionDiagnosticsTx, AIS SCS -> ROS2 */
    if (nullptr != autonomyConditionDiagnosticsTxScsIn_) {
        AutonomyConditionDiagnosticsTxInterface acdTxScs;
        while (autonomyConditionDiagnosticsTxScsIn_->get(acdTxScs)) {
            cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel acdTxRos =
                    convertAutonomyConditionDiagnosticsTxToRos(acdTxScs);
            if (nullptr != autonomyConditionDiagnosticsTxRosOut_ && !autonomyConditionDiagnosticsTxRosOut_->publish(acdTxRos)) {
                AIS_LOG_ERROR("Failed to forward AutonomyConditionDiagnosticsTx SCS->ROS2");
            }
        }
    }

    /* Forward 13: EventDiagnosticData, AIS SCS -> ROS2 */
    if (nullptr != eventDiagnosticDataScsIn_) {
        EventDiagnosticData eventDiagnosticDataScs;
        while (eventDiagnosticDataScsIn_->get(eventDiagnosticDataScs)) {
            job_mgr_interfaces::msg::EventDiagnosticData eventDiagnosticDataRos = convertEventDiagnosticDataToRos(eventDiagnosticDataScs);
            if (nullptr != eventDiagnosticDataRosOut_ && !eventDiagnosticDataRosOut_->publish(eventDiagnosticDataRos)) {
                AIS_LOG_ERROR("Failed to forward EventDiagnosticData SCS->ROS2");
            }
        }
    }

    if (nullptr != jobMgrTxRosIn_ && nullptr != jobMgrTxScsOut_) {
        job_mgr_interfaces::msg::LpsSaJobMgrTxChannel txRos;
        while (jobMgrTxRosIn_->get(txRos)) {
            if (!jobMgrTxScsOut_->publish(convertJobMgrTxToScs(txRos))) {
                AIS_LOG_ERROR("Failed to forward LpsSaJobMgrTxChannel ROS2->SCS");
            }
        }
    }

    if (nullptr != jobMgrDebugRosIn_ && nullptr != jobMgrDebugScsOut_) {
        job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel debugRos;
        while (jobMgrDebugRosIn_->get(debugRos)) {
            LpsSaJobMgrDebugChannel debugScs;
            debugScs.currentState = debugRos.current_state;
            debugScs.tipoffAssistActivationCount = debugRos.tipoff_assist_activation_count;
            if (!jobMgrDebugScsOut_->publish(debugScs)) {
                AIS_LOG_ERROR("Failed to forward LpsSaJobMgrDebugChannel ROS2->SCS");
            }
        }
    }

    if (nullptr != outputChannelRosIn_ && nullptr != outputChannelScsOut_) {
        job_mgr_interfaces::msg::OutputChannel outputRos;
        while (outputChannelRosIn_->get(outputRos)) {
            if (!outputChannelScsOut_->publish(convertOutputChannelToScs(outputRos))) {
                AIS_LOG_ERROR("Failed to forward OutputChannel ROS2->SCS");
            }
        }
    }

    if (nullptr != weighInitDebugRosIn_ && nullptr != weighInitDebugScsOut_) {
        weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel debugRos;
        while (weighInitDebugRosIn_->get(debugRos)) {
            if (!weighInitDebugScsOut_->publish(convertWeighInitDebugToScs(debugRos))) {
                AIS_LOG_ERROR("Failed to forward LpsSaWeighInitDebugChannel ROS2->SCS");
            }
        }
    }

    /* LpsSaWeighDebugChannel: ROS2 -> AIS SCS (aisXcpServer consumer) */
    if (nullptr != weighDebugRosIn_ && nullptr != weighDebugScsOut_) {
        weigh_app_interfaces::msg::LpsSaWeighDebugChannel debugRos;
        while (weighDebugRosIn_->get(debugRos)) {
            if (!weighDebugScsOut_->publish(convertWeighDebugToScs(debugRos))) {
                AIS_LOG_ERROR("Failed to forward LpsSaWeighDebugChannel ROS2->SCS");
            }
        }
    }

    /* LpsSaNvmCalDataChannel: ROS2 -> AIS SCS (aisXcpServer consumer) */
    if (nullptr != nvmCalDataRosIn_ && nullptr != nvmCalDataScsOut_) {
        weigh_app_interfaces::msg::LpsSaNvmCalDataChannel nvmCalRos;
        while (nvmCalDataRosIn_->get(nvmCalRos)) {
            if (!nvmCalDataScsOut_->publish(convertNvmCalDataToScs(nvmCalRos))) {
                AIS_LOG_ERROR("Failed to forward LpsSaNvmCalDataChannel ROS2->SCS");
            }
        }
    }

    /* LpsSaNvmCalOnTheFlyDataChannel: ROS2 -> AIS SCS (aisXcpServer consumer) */
    if (nullptr != nvmCalOnTheFlyDataRosIn_ && nullptr != nvmCalOnTheFlyDataScsOut_) {
        weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel nvmCalOtfRos;
        while (nvmCalOnTheFlyDataRosIn_->get(nvmCalOtfRos)) {
            if (!nvmCalOnTheFlyDataScsOut_->publish(convertNvmCalOnTheFlyDataToScs(nvmCalOtfRos))) {
                AIS_LOG_ERROR("Failed to forward LpsSaNvmCalOnTheFlyDataChannel ROS2->SCS");
            }
        }
    }

    /* CalMgrCmdReqst: AIS SCS (ACD producer) -> ROS2 (WeighApp subscriber) */
    if (nullptr != calMgrCmdReqstScsIn_ && nullptr != calMgrCmdReqstRosOut_) {
        CalMgrCmdReqst reqstScs;
        while (calMgrCmdReqstScsIn_->get(reqstScs)) {
            if (!calMgrCmdReqstRosOut_->publish(convertCalMgrCmdReqstToRos(reqstScs))) {
                AIS_LOG_ERROR("Failed to forward CalMgrCmdReqst SCS->ROS2");
            }
        }
    }

    /* CalMgrCmdResp: ROS2 (WeighApp publisher) -> AIS SCS (ACD consumer) */
    if (nullptr != calMgrCmdRespRosIn_ && nullptr != calMgrCmdRespScsOut_) {
        weigh_app_interfaces::msg::CalMgrCmdResp respRos;
        while (calMgrCmdRespRosIn_->get(respRos)) {
            if (!calMgrCmdRespScsOut_->publish(convertCalMgrCmdRespToScs(respRos))) {
                AIS_LOG_ERROR("Failed to forward CalMgrCmdResp ROS2->SCS");
            }
        }
    }
    
    if (nullptr != demoAppTxScsIn_ && nullptr != demoAppTxRosOut_) {
        DemoAppTxChannel demoScs;
        while (demoAppTxScsIn_->get(demoScs)) {
            if (!demoAppTxRosOut_->publish(convertDemoAppTxToRos(demoScs))) {
                AIS_LOG_ERROR("Failed to forward DemoAppTxChannel SCS->ROS2");
            }
        }
    }

    if (nullptr != partNumbersScsIn_ && nullptr != partNumbersRosOut_) {
        PartNumbers partNumbersScs;
        while (partNumbersScsIn_->get(partNumbersScs)) {
            if (!partNumbersRosOut_->publish(convertPartNumbersToRos(partNumbersScs))) {
                AIS_LOG_ERROR("Failed to forward PartNumbers SCS->ROS2");
            }
        }
    }

    if (nullptr != systemHardwareHealthScsIn_ && nullptr != systemHardwareHealthRosOut_) {
        SystemHardwareHealth healthScs;
        while (systemHardwareHealthScsIn_->get(healthScs)) {
            if (!systemHardwareHealthRosOut_->publish(convertSystemHardwareHealthToRos(healthScs))) {
                AIS_LOG_ERROR("Failed to forward SystemHardwareHealth SCS->ROS2");
            }
        }
    }

    if (nullptr != systemHardwareHealthRequestRosIn_ && nullptr != systemHardwareHealthRequestScsIn_) {
        weigh_app_interfaces::msg::SystemHardwareHealthRequest requestRos;
        while (systemHardwareHealthRequestRosIn_->get(requestRos)) {
            if (!systemHardwareHealthRequestScsIn_->publish(convertSystemHardwareHealthRequestToScs(requestRos))) {
                AIS_LOG_ERROR("Failed to forward SystemHardwareHealthRequest ROS2->SCS");
            }
        }
    }

    if (nullptr != readyToFlashRosIn_ && nullptr != readyToFlashScsOut_) {
        weigh_app_interfaces::msg::ReadyToFlashStatus readyRos;
        while (readyToFlashRosIn_->get(readyRos)) {
            if (!readyToFlashScsOut_->publish(convertReadyToFlashToScs(readyRos))) {
                AIS_LOG_ERROR("Failed to forward ReadyToFlashStatus ROS2->SCS");
            }
        }
    }
    
    /* TipoffModelTestPoints: ROS2 (WeighApp publisher) -> AIS SCS (aisXcpServer consumer) */
    if (nullptr != tipoffTestPointsRosIn_ && nullptr != tipoffTestPointsScsOut_) {
        weigh_app_interfaces::msg::TipoffModelTestPoints tipoffRos;
        while (tipoffTestPointsRosIn_->get(tipoffRos)) {
            if (!tipoffTestPointsScsOut_->publish(convertTipoffTestPointsToScs(tipoffRos))) {
                AIS_LOG_ERROR("Failed to forward TipoffModelTestPoints ROS2->SCS");
            }
        }
    }

    /* PrinterCnfg: AIS SCS (LpsSaTotalsApp publisher) -> ROS2 (WeighApp subscriber) */
    if (nullptr != printerCnfgScsIn_ && nullptr != printerCnfgRosOut_) {
        LpsSaTotalsPrinterCnfgInterface printerCnfg;
        while (printerCnfgScsIn_->get(printerCnfg)) {
            if (!printerCnfgRosOut_->publish(convertPrinterCnfgToRos(printerCnfg))) {
                AIS_LOG_ERROR("Failed to forward PrinterCnfg SCS->ROS2");
            }
        }
    }

    return true;
}

/******************************************************************************
FUNCTION NAME:ScsToRos2Bridge::cleanup
*******************************************************************************/
void ScsToRos2Bridge::cleanup()
{
    AIS_LOG_INFO("ScsToRos2Bridge::cleanup");
    jobMgrReqstRosOut_.reset();
    jobMgrRespRosIn_.reset();
    aisJhm2TxRosOut_.reset();
    switchInputRosOut_.reset();
    loadRecordRosIn_.reset();
    weighReqstRosOut_.reset();
    weighRespRosIn_.reset();
    weighTxRosIn_.reset();
    shmClockRosOut_.reset();
    displayStateRosOut_.reset();
    dataLinkDataRosOut_.reset();
    weighAppDataLinkDataRosOut_.reset();
    autonomyConditionDiagnosticsTxRosOut_.reset();
    eventDiagnosticDataRosOut_.reset();
    jobMgrTxRosIn_.reset();
    jobMgrDebugRosIn_.reset();
    outputChannelRosIn_.reset();
    weighInitDebugRosIn_.reset();
    demoAppTxRosOut_.reset();
    partNumbersRosOut_.reset();
    systemHardwareHealthRosOut_.reset();
    systemHardwareHealthRequestRosIn_.reset();
    readyToFlashRosIn_.reset();
    weighDebugRosIn_.reset();
    nvmCalDataRosIn_.reset();
    nvmCalOnTheFlyDataRosIn_.reset();
    calMgrCmdReqstRosOut_.reset();
    calMgrCmdRespRosIn_.reset();
    tipoffTestPointsRosIn_.reset();
    printerCnfgRosOut_.reset();
    jobMgrReqstScsIn_ = nullptr;
    jobMgrRespScsOut_ = nullptr;
    aisJhm2TxScsIn_ = nullptr;
    switchInputScsIn_ = nullptr;
    loadRecordScsOut_ = nullptr;
    weighReqstScsIn_ = nullptr;
    weighRespScsOut_ = nullptr;
    weighTxScsOut_ = nullptr;
    shmClockScsIn_ = nullptr;
    displayStateScsIn_ = nullptr;
    dataLinkDataScsIn_ = nullptr;
    autonomyConditionDiagnosticsTxScsIn_ = nullptr;
    eventDiagnosticDataScsIn_ = nullptr;
    jobMgrTxScsOut_ = nullptr;
    jobMgrDebugScsOut_ = nullptr;
    outputChannelScsOut_ = nullptr;
    weighInitDebugScsOut_ = nullptr;
    weighDebugScsOut_ = nullptr;
    nvmCalDataScsOut_ = nullptr;
    nvmCalOnTheFlyDataScsOut_ = nullptr;
    calMgrCmdReqstScsIn_ = nullptr;
    calMgrCmdRespScsOut_ = nullptr;
    demoAppTxScsIn_ = nullptr;
    partNumbersScsIn_ = nullptr;
    tipoffTestPointsScsOut_ = nullptr;
    printerCnfgScsIn_ = nullptr;
    systemHardwareHealthScsIn_ = nullptr;
    systemHardwareHealthRequestScsIn_ = nullptr;
    readyToFlashScsOut_ = nullptr;
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
    rosNode_.reset();
}

/******************************************************************************
FUNCTION NAME:ScsToRos2Bridge::convertJobMgrReqstToRos
DESCRIPTION: LpsSaJobMgrReqstChannelStorage (AIS SCS) -> cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel (ROS2)
    Field-for-field mapping, verified against both:
      prod/common/interfaces/LpsSaJobMgrReqstChannel/LpsSaJobMgrReqstChannel.h
      ros2_model/src/cpm_common_interfaces/msg/LpsSaJobMgrReqstChannel.msg (+ nested .msg files)
    Enum numeric values line up 1:1 on both sides (both ultimately trace back
    to the same TIP_OFF_* #defines in LpsPtPublic.h), so plain static_cast is safe.
*******************************************************************************/
cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel ScsToRos2Bridge::convertJobMgrReqstToRos(const LpsSaJobMgrReqstChannel& scs)
{
    cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel ros;

    ros.app_name = scs.appName;
    ros.app_request_id = scs.appRequestId;

    ros.command.value = static_cast<uint8_t>(scs.command);

    ros.data_tipoff_trigger_type.value = static_cast<uint8_t>(scs.data.tipoffTriggerType);
    ros.data_tipoff_mode.value = static_cast<uint8_t>(scs.data.tipoffMode);
    ros.data_auto_store_pass_count = scs.data.autoStorePassCount;
    ros.data_task_number = scs.data.taskNumber;
    ros.data_enabled = scs.data.enabled;
    ros.data_target_type = scs.data.targetType;
    ros.data_subtotal_index = scs.data.subtotalIndex;
    ros.data_total_target_weight = scs.data.totalTargetWeight;

    ros.data_subtotal_info.subtotal_command = scs.data.subtotalInfo.command;
    ros.data_subtotal_info.current_step_number = scs.data.subtotalInfo.currentStepNumber;
    ros.data_subtotal_info.new_step_number = scs.data.subtotalInfo.newStepNumber;
    ros.data_subtotal_info.target_weight = scs.data.subtotalInfo.targetWeight;
    ros.data_subtotal_info.target_proportion = scs.data.subtotalInfo.targetProportion;
    ros.data_subtotal_info.target_passes = scs.data.subtotalInfo.targetPasses;
    ros.data_subtotal_info.material_id = scs.data.subtotalInfo.materialId;
    ros.data_subtotal_info.material_name = scs.data.subtotalInfo.materialName;
    ros.data_subtotal_info.material_density = scs.data.subtotalInfo.materialDensity;
    ros.data_subtotal_info.icon_type = scs.data.subtotalInfo.iconType;

    ros.requests.reserve(scs.requests.size());
    for (const auto& r : scs.requests) {
        cpm_common_interfaces::msg::LpsSaJobMgrReqst reqRos;
        reqRos.command = LpsSaJobMgrReqstCommand_Base_t(r.command);
        reqRos.arg1 = r.tagValue();   // arg1 is private; every accessor (materialName/truckName/tagValue) reads the same underlying arg1
        reqRos.arg2 = r.materialDensity(); // arg2 is private; materialDensity/truckTargetWeight alias the same underlying arg2
        reqRos.arg3 = r.materialId();  // arg3 is private; materialId/truckId alias the same underlying arg3
        reqRos.arg4 = r.tagName();
        ros.requests.push_back(reqRos);
    }

    return ros;
}

/******************************************************************************
FUNCTION NAME:ScsToRos2Bridge::convertJobMgrRespToScs
DESCRIPTION: job_mgr_interfaces::msg::LpsSaJobMgrRespChannel (ROS2) -> LpsSaJobMgrRespChannelStorage (AIS SCS)
    Field-for-field mapping, verified against:
      prod/common/interfaces/LpsSaJobMgrRespChannel/LpsSaJobMgrRespChannel.h
      ros2_model/src/job_mgr_interfaces/msg/LpsSaJobMgrRespChannel.msg
*******************************************************************************/
LpsSaJobMgrRespChannel ScsToRos2Bridge::convertJobMgrRespToScs(const job_mgr_interfaces::msg::LpsSaJobMgrRespChannel& ros)
{
    LpsSaJobMgrRespChannel scs;

    scs.appName = ros.app_name;
    scs.appRequestId = ros.app_request_id;
    scs.timePoint = std::chrono::steady_clock::time_point(
            std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::nanoseconds(ros.time_point_ns)));
    scs.command = static_cast<LpsSaJobMgrReqstChannel::Command>(ros.command.value);
    scs.success = ros.success;

    return scs;
}

/******************************************************************************
FUNCTION NAME:ScsToRos2Bridge::convertAisJhm2TxToRos
DESCRIPTION: AisJhm2TxChannelStorage (AIS SCS) -> cpm_common_interfaces::msg::AisJhm2TxChannel (ROS2)
    Field-for-field mapping, verified against:
      prod/common/interfaces/AisJhm2TxChannel/AisJhm2TxChannel.h
      ros2_model/src/cpm_common_interfaces/msg/AisJhm2TxChannel.msg (+ SimpleCalDataT.msg, TipoffWeightAdjustData.msg)
*******************************************************************************/
cpm_common_interfaces::msg::AisJhm2TxChannel ScsToRos2Bridge::convertAisJhm2TxToRos(const AisJhm2TxChannel& scs)
{
    cpm_common_interfaces::msg::AisJhm2TxChannel ros;

    ros.simplecal_data.time_stamp = scs.simplecal_data.timeStamp;
    ros.simplecal_data.adjtruckweight = scs.simplecal_data.adjtruckweight;
    ros.simplecal_data.zeroed_truck_wt = scs.simplecal_data.zeroedTruckWt;
    ros.simplecal_data.new_data_flag = scs.simplecal_data.newDataFlag;

    ros.tipoff_weight_adjust_data.tip_off_weight1 = scs.tipoff_weight_adjust_data.tipOffWeight1;
    ros.tipoff_weight_adjust_data.weigh_range_weight1 = scs.tipoff_weight_adjust_data.weighRangeWeight1;
    ros.tipoff_weight_adjust_data.tip_off_weight2 = scs.tipoff_weight_adjust_data.tipOffWeight2;
    ros.tipoff_weight_adjust_data.weigh_range_weight2 = scs.tipoff_weight_adjust_data.weighRangeWeight2;
    ros.tipoff_weight_adjust_data.new_data_flag = scs.tipoff_weight_adjust_data.newDataFlag;
    ros.tipoff_weight_adjust_data.reset = scs.tipoff_weight_adjust_data.reset;

    return ros;
}

/******************************************************************************
FUNCTION NAME: ScsToRos2Bridge::convertSwitchInputToRos
DESCRIPTION: SwitchInputScsStorage -> job_mgr_interfaces::msg::SwitchInputScs
    AIS side: int STG_values[4] (values 0=OPEN,1=CLOSED,2=UNKNOWN -- enum STG)
    ROS2 side: std::array<STG_, 4> stg_values where STG_.value maps the same ints.
    Confirmed from SwitchInputApp.cpp: STG4 written into index [3], same enum values.
*******************************************************************************/
job_mgr_interfaces::msg::SwitchInputScs ScsToRos2Bridge::convertSwitchInputToRos( SwitchInputScs& scs)
{
    job_mgr_interfaces::msg::SwitchInputScs ros;
    for (int i = 0; i < NO_OF_STG_INPUTS; ++i) {
        ros.stg_values[i].value = static_cast<uint8_t>(scs.get_STG_value(i));
    }
    return ros;
}

/******************************************************************************
FUNCTION NAME: ScsToRos2Bridge::convertLoadRecordToScs
DESCRIPTION: job_mgr_interfaces::msg::LpsSaLoadRecordChannel -> LpsSaLoadRecordChannelStorage
    Reverse of LpsSaJobMgrApp::convertLoadRecordToRos (LpsSaJobMgrProcess.cpp).
    All fields set via public setters or direct public member access.
    chrono: utc_time_ns (int64 nanoseconds since epoch) -> system_clock::time_point.
    Weight units: int32 -> LpsCommonWeightUnits (uint16_t enum class, same underlying value).
*******************************************************************************/
LpsSaLoadRecordChannel ScsToRos2Bridge::convertLoadRecordToScs(const job_mgr_interfaces::msg::LpsSaLoadRecordChannel& ros)
{
    LpsSaLoadRecordChannel scs;

    scs.storeAction(static_cast<LpsSaLoadRecordStoreAction>(ros.store_action));
    scs.ticketNumber(ros.ticket_number);

    scs.productId(ros.product_id);
    scs.equipmentId(ros.equipment_id);
    scs.weightInterval(ros.weight_interval);
    scs.weightDecimalPrecision(ros.weight_decimal_precision);
    scs.weightUnits(static_cast<LpsCommonWeightUnits>(static_cast<uint16_t>(ros.weight_units)));

    scs.recipeName(ros.recipe_name);
    scs.setTargetType(static_cast<LpsSaLoadRecordTargetType>(ros.target_type));
    scs.setTotalTargetWeight(ros.total_target_weight);

    scs.storeTime.utcTime = std::chrono::system_clock::time_point(
            std::chrono::duration_cast<std::chrono::system_clock::duration>(
                    std::chrono::nanoseconds(ros.store_time.utc_time_ns)));
    scs.storeTime.shmTime = ros.store_time.shm_time;

    /* Convert subtotals using public API (setters + addPass) */
    auto convertSubtotal = [](const job_mgr_interfaces::msg::LoadRecordSubtotal& rs,
                               LpsSaLoadRecordSubtotal& s)
    {
        s.startTime.utcTime = std::chrono::system_clock::time_point(
                std::chrono::duration_cast<std::chrono::system_clock::duration>(
                        std::chrono::nanoseconds(rs.start_time.utc_time_ns)));
        s.startTime.shmTime  = rs.start_time.shm_time;
        s.endTime.utcTime = std::chrono::system_clock::time_point(
                std::chrono::duration_cast<std::chrono::system_clock::duration>(
                        std::chrono::nanoseconds(rs.end_time.utc_time_ns)));
        s.endTime.shmTime    = rs.end_time.shm_time;

        s.truckId                   = rs.truck_id;
        s.truckName                 = rs.truck_name;
        s.truckTargetWeightTonnes   = rs.truck_target_weight_tonnes;
        s.targetProportion          = rs.target_proportion;
        s.targetPasses              = rs.target_passes;
        s.materialId                = rs.material_id;
        s.materialName              = rs.material_name;
        s.materialDensity           = rs.material_density;
        s.customListName1           = rs.custom_list_name1;
        s.customListName2           = rs.custom_list_name2;
        s.customListName3           = rs.custom_list_name3;
        s.customListName4           = rs.custom_list_name4;
        s.tag1                      = rs.tag1;
        s.tag2                      = rs.tag2;
        s.tag3                      = rs.tag3;
        s.tag4                      = rs.tag4;
        s.iconType                  = rs.icon_type;
        s.zeroWeight                = rs.zero_weight;
        s.calAdjust                 = rs.cal_adjust;

        for (const auto& rp : rs.passes) {
            LpsSaLoadRecordPass p;
            p.weightTonnes = rp.weight_tonnes;
            p.calcMethod   = rp.calc_method;
            p.time.utcTime = std::chrono::system_clock::time_point(
                    std::chrono::duration_cast<std::chrono::system_clock::duration>(
                            std::chrono::nanoseconds(rp.time.utc_time_ns)));
            p.time.shmTime = rp.time.shm_time;
            s.addPassRaw(p);
        }
    };

    convertSubtotal(ros.subtotal, scs.getCurrentSubtotal());
    for (const auto& rsub : ros.subtotals) {
        LpsSaLoadRecordSubtotal sub;
        convertSubtotal(rsub, sub);
        scs.addSubtotalRaw(sub);
    }

    return scs;
}

cpm_common_interfaces::msg::ShmClockInput ScsToRos2Bridge::convertShmClockToRos(ShmClock& scs)
{
    cpm_common_interfaces::msg::ShmClockInput ros;
    ros.shm_sec = scs.get_SHM();
    ros.utc_sec_us = static_cast<int64_t>(scs.get_UTC().toDouble() * 1000000.0);
    ros.utc_offset_min = scs.get_UTC_offset();
    scs.get_TZ(ros.tzone_info.data());
    return ros;
}

cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface ScsToRos2Bridge::convertDisplayStateToRos(const LpsSaUIDisplayStateInterface& scs)
{
    cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface ros;
    const LpsSaUIDisplayState& state = scs.state;
    const LpsSaUIDisplaySettings& settings = state.getSettings();

    ros.state.service_mode_enable_code_entered = state.isServiceModeEnableCodeEntered();
    ros.state.in_service_mode = state.isInServiceMode();
    ros.state.in_verification_mode = state.isInVerificationMode();
    ros.state.heartbeat_count = state.getHeartbeatCount();
    ros.state.document_id = state.getDocumentId();
    ros.state.weight_capacity = state.getWeightCapacity();
    ros.state.weight_decimal_precision = state.getWeightDecimalPrecision();
    ros.state.weight_interval = state.getWeightInterval();
    ros.state.settings.units = static_cast<uint8_t>(settings.units);
    ros.state.settings.language = static_cast<uint16_t>(settings.language);
    ros.state.settings.brightness = settings.brightness;
    ros.state.settings.time_format = static_cast<uint8_t>(settings.timeFormat);
    ros.state.settings.date_format = static_cast<uint16_t>(settings.dateFormat);
    ros.state.settings.weight_units = static_cast<int32_t>(settings.weightUnits);
    ros.state.settings.weight_precision = static_cast<int32_t>(settings.weightPrecision);
    ros.state.settings.service_mode_enable_code = settings.serviceModeEnableCode;
    ros.state.settings.keyboard_layout_setting = static_cast<uint8_t>(settings.keyboardLayoutSetting);
    return ros;
}

job_mgr_interfaces::msg::DataLinkData ScsToRos2Bridge::convertDataLinkDataToRos(DataLinkData& scs)
{
    job_mgr_interfaces::msg::DataLinkData ros;
    for (const auto& param : scs.GetParams()) {
        job_mgr_interfaces::msg::DataLinkParam rosParam;
        rosParam.param_id = param.GetParamId();
        rosParam.identifier_type = static_cast<uint8_t>(param.GetParamIdentifierType());
        rosParam.pid_data_received = param.IsPIDDataReceived();
        rosParam.last_value_dsi = param.GetLastValueDsi();
        rosParam.last_good_value_u8 = param.GetLastGoodValue<uint8_t>();
        rosParam.last_good_value_u16 = param.GetLastGoodValue<uint16_t>();
        rosParam.last_value_eng = param.GetLastValueEng();
        ros.params.push_back(rosParam);
    }
    return ros;
}

weigh_app_interfaces::msg::DataLinkData ScsToRos2Bridge::convertWeighAppDataLinkDataToRos(DataLinkData& scs)
{
    weigh_app_interfaces::msg::DataLinkData ros;
    for (auto& param : scs.GetParams()) {
        weigh_app_interfaces::msg::DataLinkParam rosParam;
        rosParam.identifier_type = static_cast<uint8_t>(param.GetParamIdentifierType());
        rosParam.sid = param.GetSid();
        rosParam.param_id = param.GetParamId();
        rosParam.units = param.GetUnits();
        rosParam.scaling = param.GetScaling();
        rosParam.offset = param.GetOffset();
        rosParam.pid_data_received = param.IsPIDDataReceived();
        rosParam.last_value_dsi = param.GetLastValueDsi();
        rosParam.last_value_i16 = param.GetLastValue<int16_t>();
        rosParam.last_value_u16 = param.GetLastValue<uint16_t>();
        rosParam.last_value_f32 = param.GetLastValue<float>();
        rosParam.last_value_eng = param.GetLastValueEng();
        rosParam.last_good_value_eng = param.GetLastGoodValueEng();
        rosParam.last_value_vector = param.GetLastValueVector();
        const auto varBlockLength = param.GetVarParamBlockLength();
        if (varBlockLength > 0) {
            const uint8_t* varBlock = param.GetVarParamBlock();
            rosParam.var_param_block.assign(varBlock, varBlock + varBlockLength);
        }
        rosParam.var_length_param_type = static_cast<uint8_t>(param.GetVarLengthParamType());
        rosParam.var_length_param_dsi = param.GetVarLengthParamDsi();
        ros.params.push_back(rosParam);
    }
    return ros;
}

cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel
ScsToRos2Bridge::convertAutonomyConditionDiagnosticsTxToRos(const AutonomyConditionDiagnosticsTxInterface& scs)
{
    cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel ros;
    ros.time_point_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(scs.timePoint.time_since_epoch()).count();
    ros.display_ethernet_bad = scs.displayEthernetBad;
    ros.product_link_ethernet_bad = scs.productLinkEthernetBad;
    ros.sea_list.reserve(scs.seaList.size());
    for (const auto& sea : scs.seaList) {
        cpm_common_interfaces::msg::SEA rosSea;
        rosSea.free_count = sea.free_count;
        rosSea.reason_code = sea.reason_code;
        rosSea.status = sea.status;
        ros.sea_list.push_back(rosSea);
    }
    return ros;
}

job_mgr_interfaces::msg::EventDiagnosticData ScsToRos2Bridge::convertEventDiagnosticDataToRos(EventDiagnosticData& scs)
{
    job_mgr_interfaces::msg::EventDiagnosticData ros;
    for (const auto& diagnostic : *scs.getListOfEventDiagnostics()) {
        job_mgr_interfaces::msg::Diagnostic rosDiagnostic;
        rosDiagnostic.cid = diagnostic.getCID();
        rosDiagnostic.category = diagnostic.category;
        rosDiagnostic.status = diagnostic.status;
        ros.active_diagnostics.push_back(rosDiagnostic);
    }
    return ros;
}

LpsSaJobMgrTxChannel ScsToRos2Bridge::convertJobMgrTxToScs(const job_mgr_interfaces::msg::LpsSaJobMgrTxChannel& ros)
{
    LpsSaJobMgrTxChannel scs;
    scs.timePoint = std::chrono::steady_clock::time_point(std::chrono::nanoseconds(ros.time_point_ns));
    scs.taskNumber = ros.task_number; scs.passCount = ros.pass_count; scs.truckWeight = ros.truck_weight;
    scs.truckWeightAccuracy = static_cast<LpsWeighBktWtAccuracy_t>(ros.truck_weight_accuracy.value); scs.TruckStartWeight = ros.truck_start_weight;
    scs.remainingWeight = ros.remaining_weight; scs.totalWeight = ros.total_weight; scs.totalWeightAccuracy = static_cast<LpsWeighBktWtAccuracy_t>(ros.total_weight_accuracy.value);
    scs.subtotalCount = ros.subtotal_count; scs.ticketId = ros.ticket_id; scs.materialId = ros.material_id; scs.materialName = ros.material_name;
    scs.materialDensity = ros.material_density; scs.truckId = ros.truck_id; scs.truckName = ros.truck_name; scs.truckTargetWeight = ros.truck_target_weight;
    scs.truckListEnabled = ros.truck_list_enabled; scs.materialListEnabled = ros.material_list_enabled; scs.tag1Enabled = ros.tag1_enabled; scs.customListName1 = ros.custom_list_name1; scs.tag1 = ros.tag1;
    scs.tag2Enabled = ros.tag2_enabled; scs.customListName2 = ros.custom_list_name2; scs.tag2 = ros.tag2; scs.tag3Enabled = ros.tag3_enabled; scs.customListName3 = ros.custom_list_name3; scs.tag3 = ros.tag3;
    scs.tag4Enabled = ros.tag4_enabled; scs.customListName4 = ros.custom_list_name4; scs.tag4 = ros.tag4; scs.ManualTipOffState = static_cast<LpsSaJobMgrManualTipOffState_t>(ros.manual_tip_off_state);
    scs.TipOffTriggerType = static_cast<LpsSaTipOffTriggerType_t>(ros.tip_off_trigger_type.value); scs.TipOffState = static_cast<LpsSaJobMgrTipOffState_t>(ros.tip_off_state.value);
    scs.TipOffStateCfg = static_cast<LpsSaJobMgrTipOffState_t>(ros.tip_off_state_cfg.value); scs.OperationMode = static_cast<LpsSaJobMgrOperationMode_t>(ros.operation_mode);
    scs.StandbyState = static_cast<LpsSaJobMgrStandbyState_t>(ros.standby_state.value); scs.ClearMinusOneEnableStat = static_cast<LpsSaJobMgrClearMinusOneEnableStat_t>(ros.clear_minus_one_enable_stat);
    scs.DispBestBktWt.val = ros.disp_best_bkt_wt.val; scs.DispBestBktWt.isOk = ros.disp_best_bkt_wt.is_ok;
    for (const auto& data : ros.simple_cal_data) { SimpleCalData_t entry; entry.timeStamp = data.time_stamp; entry.truckWt = data.truck_wt; entry.zeroedTruckWt = data.zeroed_truck_wt; scs.simpleCalData.push_back(entry); }
    scs.storeCount = ros.store_count; scs.storeRejected = ros.store_rejected; scs.ReqPloadCtrlSysStat = static_cast<ReqPloadCtrlSysStat_t>(ros.req_pload_ctrl_sys_stat);
    scs.HornStoreState = static_cast<StorePloadHornStat_t>(ros.horn_store_state); scs.AutoStorePassCount = ros.auto_store_pass_count; scs.AutoTruckIdEnabled = ros.auto_truck_id_enabled;
    scs.AutoMaterialIdEnabled = ros.auto_material_id_enabled; scs.manualAddEnabled = ros.manual_add_enabled; scs.multiTaskEnabled = ros.multi_task_enabled; scs.multiTaskCount = ros.multi_task_count;
    scs.TipoffActive = ros.tipoff_active; scs.tipoffAssistActive = ros.tipoff_assist_active; scs.tipoffAssistActiveEid = ros.tipoff_assist_active_eid; scs.manualAddAvailable = ros.manual_add_available;
    scs.splitModeEnabled = ros.split_mode_enabled; scs.lftDisabled = ros.lft_disabled; scs.targetType = ros.target_type; scs.stepNumber = ros.step_number; scs.iconType = ros.icon_type; scs.targetPasses = ros.target_passes;
    return scs;
}

OutputChannel ScsToRos2Bridge::convertOutputChannelToScs(const job_mgr_interfaces::msg::OutputChannel& ros)
{
    OutputChannel scs;
    for (const auto& command : ros.commands) {
        OutputChannel::OutputCmd scsCommand;
        scsCommand.OutputPort = static_cast<OutputChannel::Port>(command.output_port);
        scsCommand.InitialState = static_cast<OutputChannel::State>(command.initial_state);
        scsCommand.StateChangeDuration = static_cast<OutputChannel::ChangeDuration>(command.state_change_duration);
        scsCommand.TotalDuration = command.total_duration;
        scsCommand.FinalState = static_cast<OutputChannel::State>(command.final_state);
        scs.AddOutputAppCmd(scsCommand);
    }
    return scs;
}

LpsSaWeighInitDebugChannel ScsToRos2Bridge::convertWeighInitDebugToScs(const weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel& ros)
{
    LpsSaWeighInitDebugChannel scs;
    scs.m_WeighInitTbl.ExecRate = ros.exec_rate;
    scs.m_WeighInitTbl.MachSpecificCfg.CalibTbl.CalWeight = ros.cal_weight;
    scs.m_WeighInitTbl.MachSpecificCfg.CalibTbl.CalStatus = ros.cal_status;
    scs.m_WeighInitTbl.MachSpecificCfg.CalibTbl.CalAdjust = ros.cal_adjust;
    scs.m_WeighInitTbl.MachSpecificCfg.CalibTbl.ZeroWeight = ros.zero_weight;
    scs.m_WeighInitTbl.MachSpecificCfg.DigConfig.DigTargetWt = ros.dig_target_wt;
    scs.m_WeighInitTbl.MachSpecificCfg.StartOfWeigh = ros.start_of_weigh;
    scs.m_WeighInitTbl.MachSpecificCfg.TiltComp.TiltCompGainScalar = ros.tilt_comp_gain_scalar;
    return scs;
}

/******************************************************************************
FUNCTION NAME: ScsToRos2Bridge::convertWeighDebugToScs
DESCRIPTION: weigh_app_interfaces::msg::LpsSaWeighDebugChannel (ROS2)
             -> LpsSaWeighDebugChannelStorage (AIS SCS)
    Exact inverse of LpsSaWeighApp::LpsSaWeighScsDebugTx() (LpsSaScs.cpp).
    Field mapping verified against LpsSaWeighDebugChannel.h serialize() list
    and lps_sa_weigh_debug_channel__struct.hpp generated types.
    reweigh_warn: uint16_t stored via memcpy (bitfield union in AIS struct).
    All status/enum fields use static_cast with same underlying integer values.
*******************************************************************************/
LpsSaWeighDebugChannel ScsToRos2Bridge::convertWeighDebugToScs(
        const weigh_app_interfaces::msg::LpsSaWeighDebugChannel& ros)
{
    LpsSaWeighDebugChannel scs;

    memcpy(&scs.m_LpsWrk.WrwTbl.ReweighWarn, &ros.reweigh_warn, sizeof(ros.reweigh_warn));

    scs.DebugLiftCylHePress        = ros.debug_lift_cyl_he_press;
    scs.DebugLiftCylHePressStatus  = static_cast<LpsStat_t>(ros.debug_lift_cyl_he_press_status);
    scs.DebugLiftCylRePress        = ros.debug_lift_cyl_re_press;
    scs.DebugLiftCylRePressStatus  = static_cast<LpsStat_t>(ros.debug_lift_cyl_re_press_status);

    scs.DebugTiltCylHePress        = ros.debug_tilt_cyl_he_press;
    scs.DebugTiltCylHePressStatus  = static_cast<LpsStat_t>(ros.debug_tilt_cyl_he_press_status);
    scs.DebugTiltCylRePress        = ros.debug_tilt_cyl_re_press;
    scs.DebugTiltCylRePressStatus  = static_cast<LpsStat_t>(ros.debug_tilt_cyl_re_press_status);

    scs.DebugLiftCylRawExt         = ros.debug_lift_cyl_raw_ext;
    scs.DebugLiftCylFiltExt        = ros.debug_lift_cyl_filt_ext;
    scs.DebugLiftCylNormLen        = ros.debug_lift_cyl_norm_len;
    scs.DebugLiftCylVel            = ros.debug_lift_cyl_vel;
    scs.DebugLiftAngle             = ros.debug_lift_angle;
    scs.DebugLiftAngVel            = ros.debug_lift_ang_vel;
    scs.DebugLiftPositionStatus    = static_cast<LpsStat_t>(ros.debug_lift_position_status);

    scs.DebugTiltCylRawLen         = ros.debug_tilt_cyl_raw_len;
    scs.DebugTiltCylNormLen        = ros.debug_tilt_cyl_norm_len;
    scs.DebugTiltCylVel            = ros.debug_tilt_cyl_vel;
    scs.DebugTiltAngle             = ros.debug_tilt_angle;
    scs.DebugTiltAngleABC          = ros.debug_tilt_angle_abc;
    scs.DebugTiltPositionStatus    = static_cast<LpsStat_t>(ros.debug_tilt_position_status);

    scs.DebugBucketAngle           = ros.debug_bucket_angle;
    scs.DebugBucketAngleStatus     = static_cast<LpsStat_t>(ros.debug_bucket_angle_status);
    scs.DebugHydOilTemp            = ros.debug_hyd_oil_temp;
    scs.DebugHydOilTempStatus      = static_cast<LpsHydOilTempSensorStat_t>(ros.debug_hyd_oil_temp_status);
    scs.DebugRequestedGear         = ros.debug_requested_gear;
    scs.DebugRequestedGearStatus   = static_cast<LpsStat_t>(ros.debug_requested_gear_status);
    scs.DebugWeighUpdtLoaderBktPayldTrgtWt = ros.debug_weigh_updt_loader_bkt_payld_trgt_wt;
    scs.DebugWeighUpdtClockKeyonSec        = ros.debug_weigh_updt_clock_keyon_sec;
    scs.DebugWeighUpdtPassCount            = ros.debug_weigh_updt_pass_count;

    scs.m_LpsWrk.BestBktWt.PayloadCalcMeth          = ros.best_bkt_wt_payload_calc_meth;
    scs.m_LpsWrk.BestBktWt.Wt                       = ros.best_bkt_wt_wt;
    scs.m_LpsWrk.BestBktWt.TipoffLiveWeightInUse    = ros.best_bkt_wt_tipoff_live_weight_in_use;
    scs.m_LpsWrk.CylFlowConst.LiftHeFlowConst       = ros.cyl_flow_const_lift_he_flow_const;
    scs.m_LpsWrk.CylFlowConst.LiftReToHeFlowRatio   = ros.cyl_flow_const_lift_re_to_he_flow_ratio;
    scs.m_LpsWrk.DigDetectData.DigDetected           = ros.dig_detect_data_dig_detected;
    scs.m_LpsWrk.DigDetectData.DigDuration           = ros.dig_detect_data_dig_duration;
    scs.m_LpsWrk.DigDetectData.DigStarted            = ros.dig_detect_data_dig_started;
    scs.m_LpsWrk.DigDetectData.DigState              = static_cast<decltype(scs.m_LpsWrk.DigDetectData.DigState)>(ros.dig_detect_data_dig_state);
    scs.m_LpsWrk.DigDetectData.WtStabilized          = ros.dig_detect_data_wt_stabilized;
    scs.m_LpsWrk.DumpWtChangeData.DumpCumulativeWtChange = ros.dump_wt_change_data_dump_cumulative_wt_change;
    scs.m_LpsWrk.InstWtDer                           = ros.inst_wt_der;
    scs.m_LpsWrk.InstWtFilt                          = ros.inst_wt_filt;
    scs.m_LpsWrk.InstWtLlwFilt                       = ros.inst_wt_llw_filt;
    scs.m_LpsWrk.InstWtRaw.Stat                      = static_cast<decltype(scs.m_LpsWrk.InstWtRaw.Stat)>(ros.inst_wt_raw.stat);
    scs.m_LpsWrk.InstWtRaw.Val                       = ros.inst_wt_raw.val;
    scs.m_LpsWrk.InstWtRawPreTiltComp                = ros.inst_wt_raw_pre_tilt_comp;
    scs.m_LpsWrk.InstWtRawPostTiltComp               = ros.inst_wt_raw_post_tilt_comp;
    scs.m_LpsWrk.LiftCylPressure                     = ros.lift_cyl_pressure;
    scs.m_LpsWrk.LiftCylPressureV0                   = ros.lift_cyl_pressure_v0;
    scs.m_LpsWrk.LiftCylPressureIMUAdjusted          = ros.lift_cyl_pressure_imu_adjusted;
    scs.m_LpsWrk.LiveWeighTbl.Stat                   = static_cast<decltype(scs.m_LpsWrk.LiveWeighTbl.Stat)>(ros.live_weigh_tbl_stat);
    scs.m_LpsWrk.LiveWeighTbl.Wt                     = ros.live_weigh_tbl_wt;
    scs.m_LpsWrk.LiveWeighTbl.UseFastFilter          = ros.live_weigh_tbl_use_fast_filter;
    scs.m_LpsWrk.LowLiftWt.Wt                        = ros.low_lift_wt_wt;
    scs.m_LpsWrk.LowLiftWt.Confidence                = ros.low_lift_wt_confidence;
    scs.m_LpsWrk.LowLiftWt.ConfidenceEst             = ros.low_lift_wt_confidence_est;
    scs.m_LpsWrk.LowLiftWt.ConfidenceTimer           = ros.low_lift_wt_confidence_timer;
    scs.m_LpsWrk.LowLiftWt.LastInput                 = ros.low_lift_wt_last_input;
    scs.m_LpsWrk.LowLiftWt.MeanEst                   = ros.low_lift_wt_mean_est;
    scs.m_LpsWrk.LowLiftWt.MeanEstComp               = ros.low_lift_wt_mean_est_comp;
    scs.m_LpsWrk.LowLiftWt.Stat                      = static_cast<decltype(scs.m_LpsWrk.LowLiftWt.Stat)>(ros.low_lift_wt_stat);
    scs.m_LpsWrk.LowLiftWt.StdevEst                  = ros.low_lift_wt_stdev_est;
    scs.m_LpsWrk.LowLiftWt.VarianceEst               = ros.low_lift_wt_variance_est;
    scs.m_LpsWrk.DumpStateStatus                     = static_cast<decltype(scs.m_LpsWrk.DumpStateStatus)>(ros.dump_state_status);
    scs.m_LpsWrk.LpsStallDetect.liftStalled          = ros.lps_stall_detect_lift_stalled;
    scs.m_LpsWrk.LinkageMovement.lift                 = static_cast<decltype(scs.m_LpsWrk.LinkageMovement.lift)>(ros.linkage_movement_lift);
    scs.m_LpsWrk.LinkageMovement.tilt                 = static_cast<decltype(scs.m_LpsWrk.LinkageMovement.tilt)>(ros.linkage_movement_tilt);
    scs.m_LpsWrk.WrwTbl.WkTbl.result.weightAveRaw    = ros.wrw_tbl_wk_tbl_result_weight_ave_raw;
    scs.m_LpsWrk.WrwTbl.WkTbl.result.weightAve       = ros.wrw_tbl_wk_tbl_result_weight_ave;
    scs.m_LpsWrk.WrwTbl.OpTbl.Wt                     = ros.wrw_tbl_op_tbl_wt;
    scs.m_LpsWrk.WrwTbl.OpTbl.Warning                = ros.wrw_tbl_op_tbl_warning ? LPS_WEIGH_WARNING_ACTIVE : LPS_WEIGH_NO_WARNING_ACTIVE;
    scs.m_LpsWrk.WrwTbl.OpTbl.Indicator              = static_cast<decltype(scs.m_LpsWrk.WrwTbl.OpTbl.Indicator)>(ros.wrw_tbl_op_tbl_indicator);
    scs.m_LpsWrk.WrwTbl.OpTbl.Status                 = static_cast<decltype(scs.m_LpsWrk.WrwTbl.OpTbl.Status)>(ros.wrw_tbl_op_tbl_status);
    scs.m_LpsWrk.WrwTbl.WkTbl.result.weightAveRawIMUComp = ros.wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp;
    scs.m_LpsWrk.WrwTbl.WkTbl.BeenBelowRange         = ros.wrw_tbl_wk_tbl_been_below_range;
    scs.m_LpsWrk.ZeroAdjTbl.ZeroAdjStatus            = static_cast<decltype(scs.m_LpsWrk.ZeroAdjTbl.ZeroAdjStatus)>(ros.zero_adj_tbl_zero_adj_status);
    scs.m_LpsWrk.OverloadWarnTbl.BucketLoadFactor    = ros.overload_warn_tbl_bucket_load_factor;
    scs.m_LpsWrk.OverloadWarnTbl.DigReverseFlag      = ros.overload_warn_tbl_dig_reverse_flag;
    scs.m_LpsWrk.OverloadWarnTbl.InOverloadRange     = ros.overload_warn_tbl_in_overload_range;
    scs.m_LpsWrk.OverloadWarnTbl.Level               = static_cast<decltype(scs.m_LpsWrk.OverloadWarnTbl.Level)>(ros.overload_warn_tbl_level);
    scs.m_LpsWrk.OverloadWarnTbl.PrevDigState        = static_cast<decltype(scs.m_LpsWrk.OverloadWarnTbl.PrevDigState)>(ros.overload_warn_tbl_prev_dig_state);
    scs.m_LpsWrk.LiftPositionFilt.length             = ros.lift_position_filt_length;
    scs.m_LpsWrk.LiftPositionFilt.velocity           = ros.lift_position_filt_velocity;
    scs.m_LpsWrk.LiftPositionFilt.angle              = ros.lift_position_filt_angle;

    scs.m_TipoffInputs.input_status.data                  = ros.tipoff_inputs.input_status;
    scs.m_TipoffInputs.invalidate_outputs                 = ros.tipoff_inputs.invalidate_outputs;
    scs.m_TipoffInputs.lift_valve_cmd                     = ros.tipoff_inputs.lift_valve_cmd;
    scs.m_TipoffInputs.tilt_valve_cmd                     = ros.tipoff_inputs.tilt_valve_cmd;
    scs.m_TipoffInputs.tilt_extension                     = ros.tipoff_inputs.tilt_extension;
    scs.m_TipoffInputs.lift_angle                         = ros.tipoff_inputs.lift_angle;
    scs.m_TipoffInputs.lift_he_pressure                   = ros.tipoff_inputs.lift_he_pressure;
    scs.m_TipoffInputs.lift_re_pressure                   = ros.tipoff_inputs.lift_re_pressure;
    scs.m_TipoffInputs.tilt_he_pressure                   = ros.tipoff_inputs.tilt_he_pressure;
    scs.m_TipoffInputs.tilt_re_pressure                   = ros.tipoff_inputs.tilt_re_pressure;
    scs.m_TipoffInputs.eef_imu_accelX                     = ros.tipoff_inputs.eef_imu_accel_x;
    scs.m_TipoffInputs.eef_imu_accelY                     = ros.tipoff_inputs.eef_imu_accel_y;
    scs.m_TipoffInputs.eef_imu_accelZ                     = ros.tipoff_inputs.eef_imu_accel_z;
    scs.m_TipoffInputs.steering_angle                     = ros.tipoff_inputs.steering_angle;
    scs.m_TipoffInputs.tool_mass                          = ros.tipoff_inputs.tool_mass;
    scs.m_TipoffInputs.truck_target_wt                    = ros.tipoff_inputs.truck_target_wt;
    scs.m_TipoffInputs.truck_start_weight                 = ros.tipoff_inputs.truck_start_weight;
    scs.m_TipoffInputs.bucket_current_weight_accuracy     = ros.tipoff_inputs.bucket_current_weight_accuracy;
    scs.m_TipoffInputs.bucket_current_weight              = ros.tipoff_inputs.bucket_current_weight;
    scs.m_TipoffInputs.tipoff_mode                        = ros.tipoff_inputs.tipoff_mode;
    scs.m_TipoffInputs.zero_offset                        = ros.tipoff_inputs.zero_offset;
    scs.m_TipoffInputs.simple_cal_factor                  = ros.tipoff_inputs.simple_cal_factor;
    scs.m_TipoffInputs.unlatch_trigger                    = ros.tipoff_inputs.unlatch_trigger;
    scs.m_TipoffInputs.bucket_angle                       = ros.tipoff_inputs.bucket_angle;
    scs.m_TipoffInputs.anchor_zero_offset                 = ros.tipoff_inputs.anchor_zero_offset;
    scs.m_TipoffInputs.anchor_factor                      = ros.tipoff_inputs.anchor_factor;
    scs.m_TipoffInputs.pass_count                         = ros.tipoff_inputs.pass_count;
    scs.m_TipoffInputs.lift_norm_angle                    = ros.tipoff_inputs.lift_norm_angle;
    scs.m_TipoffInputs.lift_norm_length                   = ros.tipoff_inputs.lift_norm_length;
    scs.m_TipoffInputs.tilt_norm_angle                    = ros.tipoff_inputs.tilt_norm_angle;
    scs.m_TipoffInputs.tilt_norm_length                   = ros.tipoff_inputs.tilt_norm_length;
    scs.m_TipoffInputs.friction_mu                        = ros.tipoff_inputs.friction_mu;
    scs.m_TipoffInputs.friction_offset                    = ros.tipoff_inputs.friction_offset;

    scs.m_TipoffOutputs.tilt_sensitivity_out              = ros.tipoff_outputs.tilt_sensitivity_out;
    scs.m_TipoffOutputs.tilt_pressure_out                 = ros.tipoff_outputs.tilt_pressure_out;
    scs.m_TipoffOutputs.arbitrated_payload_norm_error_out = ros.tipoff_outputs.arbitrated_payload_norm_error_out;
    scs.m_TipoffOutputs.weigh_status_out                  = ros.tipoff_outputs.weigh_status_out;
    scs.m_TipoffOutputs.payload_norm_stdev_out            = ros.tipoff_outputs.payload_norm_stdev_out;
    scs.m_TipoffOutputs.pcs_weight_accuracy_out           = ros.tipoff_outputs.pcs_weight_accuracy_out;
    scs.m_TipoffOutputs.current_weight_norm_error_out     = ros.tipoff_outputs.current_weight_norm_error_out;
    scs.m_TipoffOutputs.error_code_out                    = ros.tipoff_outputs.error_code_out;
    scs.m_TipoffOutputs.spill_rate_out                    = ros.tipoff_outputs.spill_rate_out;
    scs.m_TipoffOutputs.payload_send_to_CPM               = ros.tipoff_outputs.payload_send_to_cpm;
    scs.m_TipoffOutputs.payload_status_send_to_CPM        = ros.tipoff_outputs.payload_status_send_to_cpm;
    scs.m_TipoffOutputs.bucket_payload_target             = ros.tipoff_outputs.bucket_payload_target;
    scs.m_TipoffOutputs.unsecured_payload_upper_bound_norm = ros.tipoff_outputs.unsecured_payload_upper_bound_norm;
    scs.m_TipoffOutputs.unsecured_payload_lower_bound_norm = ros.tipoff_outputs.unsecured_payload_lower_bound_norm;
    scs.m_TipoffOutputs.unsecured_PFW_status              = ros.tipoff_outputs.unsecured_pfw_status;
    scs.m_TipoffOutputs.min_secure_bucket_angle           = ros.tipoff_outputs.min_secure_bucket_angle;

    scs.chassisImuGravityX          = ros.chassis_imu_gravity_x;
    scs.chassisImuGravityY          = ros.chassis_imu_gravity_y;
    scs.chassisImuGravityZ          = ros.chassis_imu_gravity_z;
    scs.chassisImuVelocityX         = ros.chassis_imu_velocity_x;
    scs.chassisImuVelocityY         = ros.chassis_imu_velocity_y;
    scs.chassisImuVelocityZ         = ros.chassis_imu_velocity_z;
    scs.chassisImuBiasMagJerk       = ros.chassis_imu_bias_mag_jerk;
    scs.chassisImuBiasMagAngAccel   = ros.chassis_imu_bias_mag_ang_accel;
    scs.chassisImuBiasMaxAngVel     = ros.chassis_imu_bias_max_ang_vel;
    scs.chassisImuBiasAngVelX       = ros.chassis_imu_bias_ang_vel_x;
    scs.chassisImuBiasAngVelY       = ros.chassis_imu_bias_ang_vel_y;
    scs.chassisImuBiasAngVelZ       = ros.chassis_imu_bias_ang_vel_z;
    scs.chassisImuPitch             = ros.chassis_imu_pitch;
    scs.chassisImuRoll              = ros.chassis_imu_roll;
    scs.chassisImuSensorLinAccStatus = ros.chassis_imu_sensor_lin_acc_status;
    scs.chassisImuSensorAngVelStatus = ros.chassis_imu_sensor_ang_vel_status;
    scs.chassisImuLinAccX           = ros.chassis_imu_lin_acc_x;
    scs.chassisImuLinAccY           = ros.chassis_imu_lin_acc_y;
    scs.chassisImuLinAccZ           = ros.chassis_imu_lin_acc_z;
    scs.chassisImuAngVelX           = ros.chassis_imu_ang_vel_x;
    scs.chassisImuAngVelY           = ros.chassis_imu_ang_vel_y;
    scs.chassisImuAngVelZ           = ros.chassis_imu_ang_vel_z;

    return scs;
}

weigh_app_interfaces::msg::DemoAppTxChannel
ScsToRos2Bridge::convertDemoAppTxToRos(const DemoAppTxChannel& scs)
{
    weigh_app_interfaces::msg::DemoAppTxChannel ros;
    ros.liftposition = scs.liftposition;
    ros.liftposition_rate = scs.liftposition_rate;
    ros.tiltposition = scs.tiltposition;
    ros.tiltposition_rate = scs.tiltposition_rate;
    ros.payload = scs.payload;
    ros.payload_rate = scs.payload_rate;
    ros.dig = scs.dig;
    ros.wrw = scs.wrw;
    ros.llw = scs.llw;
    ros.dump = scs.dump;
    ros.pdump = scs.pdump;
    ros.rack = scs.rack;
    ros.carry = scs.carry;
    ros.weight1 = scs.weight1;
    ros.pres_lift_he_demo = scs.pres_lift_he_demo;
    ros.pres_lift_re_demo = scs.pres_lift_re_demo;
    ros.angle_lift_demo = scs.angle_lift_demo;
    ros.angle_afe_demo = scs.angle_AFE_demo;
    ros.angle_abc_demo = scs.angle_ABC_demo;
    return ros;
}

weigh_app_interfaces::msg::PartNumbers
ScsToRos2Bridge::convertPartNumbersToRos(const PartNumbers& scs)
{
    weigh_app_interfaces::msg::PartNumbers ros;
    ros.product_id_num = scs.GetProductIdNum();
    ros.equipment_id = scs.GetEquipmentId();
    ros.sw_group_part_num = scs.GetSwGroupPartNum();
    ros.sw_group_release_date = scs.GetSwGroupReleaseDate();
    ros.sw_group_description = scs.GetSwGroupDescription();
    ros.ecm_part_num = scs.GetECMPartNum();
    ros.model_num = scs.GetModelNum();
    ros.ecm_serial_num = scs.GetECMSerialNum();
    ros.product_id_num_set = scs.IsProductIdNumSet();
    ros.equipment_id_set = scs.IsEquipmentIdSet();
    ros.sw_group_part_num_set = scs.IsSwGroupPartNumSet();
    ros.sw_group_release_date_set = scs.IsSwGroupReleaseDateSet();
    ros.sw_group_description_set = scs.IsSwGroupDescriptionSet();
    ros.ecm_part_num_set = scs.IsECMPartNumSet();
    ros.model_num_set = scs.IsModelNumSet();
    ros.ecm_serial_num_set = scs.IsECMSerialNumSet();
    return ros;
}

weigh_app_interfaces::msg::SystemHardwareHealthStorage
ScsToRos2Bridge::convertSystemHardwareHealthToRos(const SystemHardwareHealth& scs)
{
    weigh_app_interfaces::msg::SystemHardwareHealthStorage ros;
    ros.source_system = scs.sourceSystem;
    ros.total_system_memory_kb = scs.totalSystemMemory_kb;
    ros.available_system_memory_kb = scs.availableSystemMemory_kb;
    ros.system_up_time_sec = scs.systemUpTime_sec;
    ros.load_avg1min = scs.loadAvg1min;
    ros.load_avg5min = scs.loadAvg5min;
    ros.load_avg15min = scs.loadAvg15min;
    ros.ecm_sw_version = scs.ecmSwVersion;
    ros.software_group_part_number = scs.softwareGroupPartNumber;
    ros.software_group_description = scs.softwareGroupDescription;
    ros.software_group_release_date = scs.softwareGroupReleaseDate;
    ros.eth0_tx_kbs = scs.eth0_tx_kbs;
    ros.eth0_rx_kbs = scs.eth0_rx_kbs;
    ros.eth1_tx_kbs = scs.eth1_tx_kbs;
    ros.eth1_rx_kbs = scs.eth1_rx_kbs;
    ros.system_cpu_usage_percent = scs.systemCpuUsage_percent;
    ros.system_cpu_io_wait_percent = scs.systemCpuIOWait_percent;
    ros.system_cpu_irq_percent = scs.systemCpuIrq_percent;
    ros.ecm_os_version = scs.ecmOsVersion;
    ros.battery_voltage = scs.battery_voltage;
    return ros;
}

SystemHardwareHealthRequest
ScsToRos2Bridge::convertSystemHardwareHealthRequestToScs(
    const weigh_app_interfaces::msg::SystemHardwareHealthRequest&)
{
    return SystemHardwareHealthRequest();
}

ReadyToFlashStatus
ScsToRos2Bridge::convertReadyToFlashToScs(
    const weigh_app_interfaces::msg::ReadyToFlashStatus& ros)
{
    ReadyToFlashStatus scs;
    scs.taskName = ros.task_name;
    scs.hostName = ros.host_name;
    scs.readyCode = static_cast<rpa_application_ready_code_t>(ros.ready_code);
    return scs;
}


/******************************************************************************
FUNCTION NAME: ScsToRos2Bridge::convertNvmCalDataToScs
DESCRIPTION: Reverse of LpsSaWeighApp::PublishCalFromNvmPayload (LpsSaScs.cpp).
             weigh_app_interfaces::msg::LpsSaNvmCalDataChannel -> LpsSaNvmCalDataChannel
*******************************************************************************/
LpsSaNvmCalDataChannel ScsToRos2Bridge::convertNvmCalDataToScs(
        const weigh_app_interfaces::msg::LpsSaNvmCalDataChannel& ros)
{
    LpsSaNvmCalDataChannel scs;
    auto& main  = ros.lps_sa_nvm_calibration_data_main;
    auto& debug = ros.lps_sa_nvm_calibration_data_debug;

    std::copy(main.raise_slow_empty_lift_heights.begin(), main.raise_slow_empty_lift_heights.end(),
              std::begin(scs.lps_sa_nvm_calibration_data_main.raise_slow_empty_lift_heights));
    std::copy(main.raise_slow_empty_pressures.begin(), main.raise_slow_empty_pressures.end(),
              std::begin(scs.lps_sa_nvm_calibration_data_main.raise_slow_empty_pressures));
    std::copy(main.lower_slow_empty_lift_heights.begin(), main.lower_slow_empty_lift_heights.end(),
              std::begin(scs.lps_sa_nvm_calibration_data_main.lower_slow_empty_lift_heights));
    std::copy(main.lower_slow_empty_pressures.begin(), main.lower_slow_empty_pressures.end(),
              std::begin(scs.lps_sa_nvm_calibration_data_main.lower_slow_empty_pressures));
    std::copy(main.raise_slow_full_lift_heights.begin(), main.raise_slow_full_lift_heights.end(),
              std::begin(scs.lps_sa_nvm_calibration_data_main.raise_slow_full_lift_heights));
    std::copy(main.raise_slow_full_pressures.begin(), main.raise_slow_full_pressures.end(),
              std::begin(scs.lps_sa_nvm_calibration_data_main.raise_slow_full_pressures));
    std::copy(main.lower_slow_full_lift_heights.begin(), main.lower_slow_full_lift_heights.end(),
              std::begin(scs.lps_sa_nvm_calibration_data_main.lower_slow_full_lift_heights));
    std::copy(main.lower_slow_full_pressures.begin(), main.lower_slow_full_pressures.end(),
              std::begin(scs.lps_sa_nvm_calibration_data_main.lower_slow_full_pressures));

    scs.lps_sa_nvm_calibration_data_main.raise_speed_empty_slow   = main.raise_speed_empty_slow;
    scs.lps_sa_nvm_calibration_data_main.raise_speed_empty_fast   = main.raise_speed_empty_fast;
    scs.lps_sa_nvm_calibration_data_main.raise_fast_delta_p_empty = main.raise_fast_delta_p_empty;
    scs.lps_sa_nvm_calibration_data_main.raise_speed_full_slow    = main.raise_speed_full_slow;
    scs.lps_sa_nvm_calibration_data_main.raise_speed_full_fast    = main.raise_speed_full_fast;
    scs.lps_sa_nvm_calibration_data_main.raise_fast_delta_p_full  = main.raise_fast_delta_p_full;

    scs.lps_sa_nvm_calibration_data_debug.lift_full_lower_DC_inf_value   = debug.lift_full_lower_dc_inf_value;
    scs.lps_sa_nvm_calibration_data_debug.lift_full_raise_DC_inf_value   = debug.lift_full_raise_dc_inf_value;
    scs.lps_sa_nvm_calibration_data_debug.tilt_full_dump_DC_inf_value    = debug.tilt_full_dump_dc_inf_value;
    scs.lps_sa_nvm_calibration_data_debug.tilt_full_rack_DC_inf_value    = debug.tilt_full_rack_dc_inf_value;
    scs.lps_sa_nvm_calibration_data_debug.tilt_dump_stop_angle_inf_value = debug.tilt_dump_stop_angle_inf_value;
    scs.lps_sa_nvm_calibration_data_debug.tilt_rack_stop_angle_inf_value = debug.tilt_rack_stop_angle_inf_value;
    scs.lps_sa_nvm_calibration_data_debug.pcs_cal_weight                 = debug.pcs_cal_weight;
    scs.lps_sa_nvm_calibration_data_debug.zero_weight                    = debug.zero_weight;
    scs.lps_sa_nvm_calibration_data_debug.cal_adjust                     = debug.cal_adjust;
    scs.lps_sa_nvm_calibration_data_debug.empty_temp                     = debug.empty_temp;
    scs.lps_sa_nvm_calibration_data_debug.full_temp                      = debug.full_temp;
    scs.lps_sa_nvm_calibration_data_debug.empty_bucket_weight_est        = debug.empty_bucket_weight_est;
    scs.lps_sa_nvm_calibration_data_debug.hyd_oil_type_index             = debug.hyd_oil_type_index;

    const auto& imu = ros.imu_cal_results;
    scs.imu_cal_results.FullSlowImuOffsetTemp1     = imu.full_slow_imu_offset_temp1;
    scs.imu_cal_results.FullSlowImuOffsetTemp2     = imu.full_slow_imu_offset_temp2;
    scs.imu_cal_results.FullSlowImuOffsetTemp3     = imu.full_slow_imu_offset_temp3;
    scs.imu_cal_results.FullSlowLumpedWeightTemp1  = imu.full_slow_lumped_weight_temp1;
    scs.imu_cal_results.FullSlowLumpedWeightTemp2  = imu.full_slow_lumped_weight_temp2;
    scs.imu_cal_results.FullSlowLumpedWeightTemp3  = imu.full_slow_lumped_weight_temp3;
    scs.imu_cal_results.EmptySlowImuOffsetTemp1    = imu.empty_slow_imu_offset_temp1;
    scs.imu_cal_results.EmptySlowImuOffsetTemp2    = imu.empty_slow_imu_offset_temp2;
    scs.imu_cal_results.EmptySlowImuOffsetTemp3    = imu.empty_slow_imu_offset_temp3;
    scs.imu_cal_results.EmptySlowLumpedWeightTemp1 = imu.empty_slow_lumped_weight_temp1;
    scs.imu_cal_results.EmptySlowLumpedWeightTemp2 = imu.empty_slow_lumped_weight_temp2;
    scs.imu_cal_results.EmptySlowLumpedWeightTemp3 = imu.empty_slow_lumped_weight_temp3;
    scs.imu_cal_results.FullSlowImuOffsetFinal     = imu.full_slow_imu_offset_final;
    scs.imu_cal_results.EmptySlowImuOffsetFinal    = imu.empty_slow_imu_offset_final;
    scs.imu_cal_results.FullSlowLumpedWeightFinal  = imu.full_slow_lumped_weight_final;
    scs.imu_cal_results.EmptySlowLumpedWeightFinal = imu.empty_slow_lumped_weight_final;

    return scs;
}

/******************************************************************************
FUNCTION NAME: ScsToRos2Bridge::convertNvmCalOnTheFlyDataToScs
DESCRIPTION: Reverse of LpsSaWeighApp::LpsSaWeighCalReqstCallback OTF publish block.
             weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel -> LpsSaNvmCalOnTheFlyDataChannel
*******************************************************************************/
LpsSaNvmCalOnTheFlyDataChannel ScsToRos2Bridge::convertNvmCalOnTheFlyDataToScs(
        const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel& ros)
{
    LpsSaNvmCalOnTheFlyDataChannel scs;
    const auto& otf = ros.lps_sa_nvm_calibration_data_on_the_fly;
    auto& s = scs.lps_sa_nvm_calibration_data_on_the_fly;

    s.statusFlags.CalInProgress    = otf.status_flags.cal_in_progress;
    s.statusFlags.EmptyBktCalDone  = otf.status_flags.empty_bkt_cal_done;
    s.statusFlags.FullBktCalDone   = otf.status_flags.full_bkt_cal_done;

    s.calUpdates.LiftHePres_Stat          = static_cast<LpsStat_t>(otf.cal_updates.lift_he_pres_stat);
    s.calUpdates.LiftRePres_Stat          = static_cast<LpsStat_t>(otf.cal_updates.lift_re_pres_stat);
    s.calUpdates.LiftCylLengthNorm_Stat   = static_cast<LpsStat_t>(otf.cal_updates.lift_cyl_length_norm_stat);
    s.calUpdates.HydOilTemp_Stat          = static_cast<LpsHydOilTempSensorStat_t>(otf.cal_updates.hyd_oil_temp_stat);
    s.calUpdates.LiftCylVel_Stat          = static_cast<LpsStat_t>(otf.cal_updates.lift_cyl_vel_stat);
    s.calUpdates.TiltCylLengthNorm_Stat   = static_cast<LpsStat_t>(otf.cal_updates.tilt_cyl_length_norm_stat);
    s.calUpdates.BktAngle_Stat            = static_cast<LpsStat_t>(otf.cal_updates.bkt_angle_stat);
    s.calUpdates.LiftLeverInfo_LeverInfoAvailable = otf.cal_updates.lift_lever_info_lever_info_available;
    s.calUpdates.LiftLeverInfo_Faulted            = otf.cal_updates.lift_lever_info_faulted;

    s.curveInfo.HydOilTempMet     = otf.curve_info.hyd_oil_temp_met;
    s.curveInfo.EnforceRaiseDetent = otf.curve_info.enforce_raise_detent;
    s.curveInfo.EnforceLowerDetent = otf.curve_info.enforce_lower_detent;
    s.curveInfo.RaiseFastVelDone  = otf.curve_info.raise_fast_vel_done;
    s.curveInfo.RaiseSlowFitDone  = otf.curve_info.raise_slow_fit_done;
    s.curveInfo.RaiseFastFitDone  = otf.curve_info.raise_fast_fit_done;
    s.curveInfo.LowerSlowFitDone  = otf.curve_info.lower_slow_fit_done;
    s.curveInfo.InternalStep      = otf.curve_info.internal_step;
    s.curveInfo.RaiseNumPoints    = otf.curve_info.raise_num_points;
    s.curveInfo.LowerNumPoints    = otf.curve_info.lower_num_points;

    const auto& imu = otf.curve_info.imu_cal_results;
    s.curveInfo.IMUCalResults.FullSlowImuOffsetTemp1     = imu.full_slow_imu_offset_temp1;
    s.curveInfo.IMUCalResults.FullSlowImuOffsetTemp2     = imu.full_slow_imu_offset_temp2;
    s.curveInfo.IMUCalResults.FullSlowImuOffsetTemp3     = imu.full_slow_imu_offset_temp3;
    s.curveInfo.IMUCalResults.FullSlowLumpedWeightTemp1  = imu.full_slow_lumped_weight_temp1;
    s.curveInfo.IMUCalResults.FullSlowLumpedWeightTemp2  = imu.full_slow_lumped_weight_temp2;
    s.curveInfo.IMUCalResults.FullSlowLumpedWeightTemp3  = imu.full_slow_lumped_weight_temp3;
    s.curveInfo.IMUCalResults.EmptySlowImuOffsetTemp1    = imu.empty_slow_imu_offset_temp1;
    s.curveInfo.IMUCalResults.EmptySlowImuOffsetTemp2    = imu.empty_slow_imu_offset_temp2;
    s.curveInfo.IMUCalResults.EmptySlowImuOffsetTemp3    = imu.empty_slow_imu_offset_temp3;
    s.curveInfo.IMUCalResults.EmptySlowLumpedWeightTemp1 = imu.empty_slow_lumped_weight_temp1;
    s.curveInfo.IMUCalResults.EmptySlowLumpedWeightTemp2 = imu.empty_slow_lumped_weight_temp2;
    s.curveInfo.IMUCalResults.EmptySlowLumpedWeightTemp3 = imu.empty_slow_lumped_weight_temp3;
    s.curveInfo.IMUCalResults.FullSlowImuOffsetFinal     = imu.full_slow_imu_offset_final;
    s.curveInfo.IMUCalResults.EmptySlowImuOffsetFinal    = imu.empty_slow_imu_offset_final;
    s.curveInfo.IMUCalResults.FullSlowLumpedWeightFinal  = imu.full_slow_lumped_weight_final;
    s.curveInfo.IMUCalResults.EmptySlowLumpedWeightFinal = imu.empty_slow_lumped_weight_final;

    s.calOverrides.LpsCalOvrState              = otf.cal_overrides.lps_cal_ovr_state;
    s.calOverrides.LiftBottomFlag              = otf.cal_overrides.lift_bottom_flag;
    s.calOverrides.LiftTopFlag                 = otf.cal_overrides.lift_top_flag;
    s.calOverrides.LpsCalAppInfCalOvrActive    = otf.cal_overrides.lps_cal_app_inf_cal_ovr_active;
    s.calOverrides.LpsCalAppInfLowerCmdLmt     = otf.cal_overrides.lps_cal_app_inf_lower_cmd_lmt;
    s.calOverrides.LpsCalAppInfRaiseCmdLmt     = otf.cal_overrides.lps_cal_app_inf_raise_cmd_lmt;
    s.calOverrides.LiftFaulted                 = otf.cal_overrides.lift_faulted;
    s.calOverrides.LiftInCenter                = otf.cal_overrides.lift_in_center;
    s.calOverrides.LiftInLowerDetent           = otf.cal_overrides.lift_in_lower_detent;
    s.calOverrides.LiftInRaiseDetent           = otf.cal_overrides.lift_in_raise_detent;
    s.calOverrides.LiftValveCmdPercent         = otf.cal_overrides.lift_valve_cmd_percent;
    s.calOverrides.CalOvrAcknowledge           = otf.cal_overrides.cal_ovr_acknowledge;
    s.calOverrides.TiltOverrides.CalTiltOverrideComplete   = otf.cal_overrides.tilt_overrides.cal_tilt_override_complete;
    s.calOverrides.TiltOverrides.CalTiltOverrideFail       = otf.cal_overrides.tilt_overrides.cal_tilt_override_fail;
    s.calOverrides.TiltOverrides.CountOfSamples            = otf.cal_overrides.tilt_overrides.count_of_samples;
    s.calOverrides.TiltOverrides.DesiredTiltExtmm          = otf.cal_overrides.tilt_overrides.desired_tilt_extmm;
    s.calOverrides.TiltOverrides.LpsCalTiltOvrStartRequest = otf.cal_overrides.tilt_overrides.lps_cal_tilt_ovr_start_request;
    s.calOverrides.TiltOverrides.LpsCalTiltOvrState        = otf.cal_overrides.tilt_overrides.lps_cal_tilt_ovr_state;
    s.calOverrides.TiltOverrides.TiltDumpCmdOvr            = otf.cal_overrides.tilt_overrides.tilt_dump_cmd_ovr;
    s.calOverrides.TiltOverrides.TiltNoiseMax              = otf.cal_overrides.tilt_overrides.tilt_noise_max;
    s.calOverrides.TiltOverrides.TiltNoiseMin              = otf.cal_overrides.tilt_overrides.tilt_noise_min;

    return scs;
}

/******************************************************************************
FUNCTION NAME: ScsToRos2Bridge::convertCalMgrCmdReqstToRos
DESCRIPTION: CalMgrCmdReqst (AIS SCS, from ACD) -> weigh_app_interfaces::msg::CalMgrCmdReqst (ROS2)
*******************************************************************************/
weigh_app_interfaces::msg::CalMgrCmdReqst ScsToRos2Bridge::convertCalMgrCmdReqstToRos(
        const CalMgrCmdReqst& scs)
{
    weigh_app_interfaces::msg::CalMgrCmdReqst ros;
    ros.calibration_request.src                    = scs.CalibrationRequest.Src;
    ros.calibration_request.dest                   = scs.CalibrationRequest.Dest;
    ros.calibration_request.calibration_reqst_flag = scs.CalibrationRequest.CalibrationReqstFlag;
    ros.calibration_request.calcmd                 = static_cast<uint8_t>(scs.CalibrationRequest.Calcmd);
    ros.calibration_request.cal_id                 = scs.CalibrationRequest.Cal_id;

    constexpr size_t numWords = (CAL_LAST_ITERM_BIT >> 5) + 1;
    ros.calibration_request.cal_iterm.resize(numWords);
    for (size_t i = 0; i < numWords; ++i) {
        ros.calibration_request.cal_iterm[i] = scs.CalibrationRequest.CalIterm[i];
    }
    return ros;
}

/******************************************************************************
FUNCTION NAME: ScsToRos2Bridge::convertCalMgrCmdRespToScs
DESCRIPTION: weigh_app_interfaces::msg::CalMgrCmdResp (ROS2, from WeighApp) -> CalMgrCmdResp (AIS SCS)
*******************************************************************************/
CalMgrCmdResp ScsToRos2Bridge::convertCalMgrCmdRespToScs(
        const weigh_app_interfaces::msg::CalMgrCmdResp& ros)
{
    CalMgrCmdResp scs;
    scs.CalibrationResp.RespCode      = static_cast<LpsSaCalRespCode_t>(ros.calibration_resp.resp_code);
    scs.CalibrationResp.CalResp       = static_cast<CAL_MGR_MR_E>(ros.calibration_resp.cal_resp);
    scs.CalibrationResp.stepNo        = ros.calibration_resp.step_no;
    scs.CalibrationResp.error         = ros.calibration_resp.error;
    scs.CalibrationResp.warning       = ros.calibration_resp.warning;
    scs.CalibrationResp.EnableQualRead = ros.calibration_resp.enable_qual_read;
    return scs;
}

/******************************************************************************
FUNCTION NAME: ScsToRos2Bridge::convertTipoffTestPointsToScs
DESCRIPTION: weigh_app_interfaces::msg::TipoffModelTestPoints (ROS2, from WeighApp) -> TipoffModelTestPoints (AIS SCS, for aisXcpServer)
*******************************************************************************/
TipoffModelTestPoints ScsToRos2Bridge::convertTipoffTestPointsToScs(
        const weigh_app_interfaces::msg::TipoffModelTestPoints& ros)
{
    TipoffModelTestPoints scs;
    scs.toa_pfwSecLatch                = ros.toa_pfw_sec_latch;
    scs.toa_pfwSecPayload              = ros.toa_pfw_sec_payload;
    scs.toa_pfwSecStatus               = ros.toa_pfw_sec_status;
    scs.toa_pfwSecStDev                = ros.toa_pfw_sec_st_dev;
    scs.toa_targetPayloadFinal         = ros.toa_target_payload_final;
    scs.toa_targetPayloadStatus        = ros.toa_target_payload_status;
    scs.toa_pfwNlNotchMeanEst          = ros.toa_pfw_nl_notch_mean_est;
    scs.toa_pfwNlNotchStDevEst         = ros.toa_pfw_nl_notch_st_dev_est;
    scs.toa_lwLpfPost                  = ros.toa_lw_lpf_post;
    scs.toa_payloadAdjusted            = ros.toa_payload_adjusted;
    scs.toa_sendPayloadArb             = ros.toa_send_payload_arb;
    scs.toa_sfuncInGravX               = ros.toa_sfunc_in_grav_x;
    scs.toa_sfuncInGravY               = ros.toa_sfunc_in_grav_y;
    scs.toa_sfuncInLiftForce           = ros.toa_sfunc_in_lift_force;
    scs.toa_sfuncInTiltForce           = ros.toa_sfunc_in_tilt_force;
    scs.toa_sfuncOutRawMassTonne       = ros.toa_sfunc_out_raw_mass_tonne;
    scs.toa_appNumber                  = ros.toa_app_number;
    scs.toa_liftBoreDia                = ros.toa_lift_bore_dia;
    scs.toa_liftRodDia                 = ros.toa_lift_rod_dia;
    scs.toa_ratedPayload               = ros.toa_rated_payload;
    scs.toa_tiltBoreDia                = ros.toa_tilt_bore_dia;
    scs.toa_tiltNumCyl                 = ros.toa_tilt_num_cyl;
    scs.toa_tiltRodDia                 = ros.toa_tilt_rod_dia;
    scs.toa_toolBcLength               = ros.toa_tool_bc_length;
    scs.toa_toolBcAngle                = ros.toa_tool_bc_angle;
    scs.toa_payloadAncAdjusted         = ros.toa_payload_anc_adjusted;
    scs.toa_payloadAncZeroed           = ros.toa_payload_anc_zeroed;
    scs.toa_imu_cal_pitch_angle        = ros.toa_imu_cal_pitch_angle;
    scs.toa_pfwUnsecStatus             = ros.toa_pfw_unsec_status;
    scs.toa_pfwUnsecBoundLower         = ros.toa_pfw_unsec_bound_lower;
    scs.toa_pfwUnsecBoundUpper         = ros.toa_pfw_unsec_bound_upper;
    scs.toa_lwSpillRate                = ros.toa_lw_spill_rate;
    scs.toa_lwStatus                   = ros.toa_lw_status;
    scs.toa_rawDist                    = ros.toa_raw_dist;
    scs.toa_rawPayload                 = ros.toa_raw_payload;
    scs.toa_payloadZeroed              = ros.toa_payload_zeroed;
    scs.toa_pfwIsWarm                  = ros.toa_pfw_is_warm;
    scs.toa_pfwSecIsSecure             = ros.toa_pfw_sec_is_secure;
    scs.toa_pfwSecIsNoSliding          = ros.toa_pfw_sec_is_no_sliding;
    scs.toa_pfwSecIsNoCollapsing       = ros.toa_pfw_sec_is_no_collapsing;
    scs.toa_pfwSecIsRacked             = ros.toa_pfw_sec_is_racked;
    scs.toa_pfwSecMinBucketAng         = ros.toa_pfw_sec_min_bucket_ang;
    scs.toa_pfwMcOk                    = ros.toa_pfw_mc_ok;
    scs.toa_pfwMcMaybeStalled          = ros.toa_pfw_mc_maybe_stalled;
    scs.toa_pfwMcMaybeRackStall        = ros.toa_pfw_mc_maybe_rack_stall;
    scs.toa_pfwMcMaybeGrounded         = ros.toa_pfw_mc_maybe_grounded;
    scs.toa_statPayloadNlNotchOneUp    = ros.toa_stat_payload_nl_notch_one_up;
    scs.toa_statPayloadNlNotchOneLow   = ros.toa_stat_payload_nl_notch_one_low;
    scs.toa_statPayloadNlNotchOneSize  = ros.toa_stat_payload_nl_notch_one_size;
    scs.toa_statPayloadNlNotchTwoUp    = ros.toa_stat_payload_nl_notch_two_up;
    scs.toa_statPayloadNlNotchTwoLow   = ros.toa_stat_payload_nl_notch_two_low;
    scs.toa_statPayloadNlNotchTwoSize  = ros.toa_stat_payload_nl_notch_two_size;
    scs.toa_statPayloadNlOneUp         = ros.toa_stat_payload_nl_one_up;
    scs.toa_statPayloadNlOneLow        = ros.toa_stat_payload_nl_one_low;
    scs.toa_statPayloadNlOneSize       = ros.toa_stat_payload_nl_one_size;
    scs.toa_statPayloadNlTwoUp         = ros.toa_stat_payload_nl_two_up;
    scs.toa_statPayloadNlTwoLow        = ros.toa_stat_payload_nl_two_low;
    scs.toa_statPayloadNlTwoSize       = ros.toa_stat_payload_nl_two_size;
    scs.toa_pfwNlStDevEst              = ros.toa_pfw_nl_st_dev_est;
    scs.toa_pfwNlMeanEst               = ros.toa_pfw_nl_mean_est;
    scs.toa_pfwPayloadFiltFinal        = ros.toa_pfw_payload_filt_final;
    scs.toa_pfwPayloadNotchFiltFinal   = ros.toa_pfw_payload_notch_filt_final;
    scs.toa_pfwPayloadNotchPost        = ros.toa_pfw_payload_notch_post;
    scs.toa_pfwLatchInvalidate         = ros.toa_pfw_latch_invalidate;
    scs.toa_imuRawEefAcclX             = ros.toa_imu_raw_eef_accl_x;
    scs.toa_imuRawEefAcclY             = ros.toa_imu_raw_eef_accl_y;
    scs.toa_imuRawEefAcclZ             = ros.toa_imu_raw_eef_accl_z;
    scs.toa_imuNeefGravX               = ros.toa_imu_neef_grav_x;
    scs.toa_imuNeefGravY               = ros.toa_imu_neef_grav_y;
    scs.toa_imuNeefGravZ               = ros.toa_imu_neef_grav_z;
    scs.toa_imuNeefPitch               = ros.toa_imu_neef_pitch;
    scs.toa_targetCompMargin           = ros.toa_target_comp_margin;
    scs.toa_targetPayloadPostComp      = ros.toa_target_payload_post_comp;
    scs.toa_targetPayloadPreComp       = ros.toa_target_payload_pre_comp;
    scs.toa_statPayloadSecureTwoSize   = ros.toa_stat_payload_secure_two_size;
    scs.toa_statPayloadSecureOneUpper  = ros.toa_stat_payload_secure_one_upper;
    scs.toa_statPayloadSecureOneLower  = ros.toa_stat_payload_secure_one_lower;
    scs.toa_statPayloadSecureOneSize   = ros.toa_stat_payload_secure_one_size;
    scs.toa_statPayloadSecureTwoUpper  = ros.toa_stat_payload_secure_two_upper;
    scs.toa_statPayloadSecureTwoLower  = ros.toa_stat_payload_secure_two_lower;
    scs.toa_sendCpmLivePayload         = ros.toa_send_cpm_live_payload;
    return scs;
}

/******************************************************************************
FUNCTION NAME: ScsToRos2Bridge::convertPrinterCnfgToRos
DESCRIPTION: LpsSaTotalsPrinterCnfgInterface (AIS SCS, from LpsSaTotalsApp) -> weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg (ROS2)
*******************************************************************************/
weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg ScsToRos2Bridge::convertPrinterCnfgToRos(
        const LpsSaTotalsPrinterCnfgInterface& scs)
{
    weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg ros;
    const auto& c = scs.config;
    ros.installed                              = c.installed;
    ros.leading_blank_lines                    = c.leadingBlankLines;
    ros.trailing_blank_lines                   = c.trailingBlankLines;
    ros.date_format                            = static_cast<uint16_t>(c.dateFormat);
    ros.date_separator                         = static_cast<uint16_t>(c.dateSeparator);
    ros.truck_ticket.num_copies                = c.truckTicket.numCopies;
    ros.truck_ticket.header_enabled            = c.truckTicket.headerEnabled;
    ros.truck_ticket.header_line1              = c.truckTicket.headerLine1;
    ros.truck_ticket.header_line2              = c.truckTicket.headerLine2;
    ros.truck_ticket.header_line3              = c.truckTicket.headerLine3;
    ros.truck_ticket.footer_line1              = c.truckTicket.footerLine1;
    ros.truck_ticket.bucket_weights_enabled    = c.truckTicket.bucketWeightsEnabled;
    ros.truck_ticket.truck_weight_enabled      = c.truckTicket.truckWeightEnabled;
    ros.truck_ticket.truck_id_enabled          = c.truckTicket.truckIdEnabled;
    ros.truck_ticket.material_id_enabled       = c.truckTicket.materialIdEnabled;
    ros.truck_ticket.store_time_enabled        = c.truckTicket.storeTimeEnabled;
    ros.truck_ticket.ticket_number             = c.truckTicket.ticketNumber;
    ros.truck_ticket.retention_period          = c.truckTicket.retentionPeriod;
    ros.truck_report.reset_time_enabled        = c.truckReport.resetTimeEnabled;
    ros.material_report.reset_time_enabled     = c.materialReport.resetTimeEnabled;
    ros.udp_transfer_ip                        = c.udpTransferIp;
    ros.udp_transfer_port                      = c.udpTransferPort;
    ros.udp_transfer_enabled                   = c.udpTransferEnabled;
    return ros;
}

void ScsToRos2Bridge::printGraphInfo()
{
   AIS_LOG_ERROR("================ ROS2 Nodes =======================");
 
    auto node_names = rosNode_->get_node_names();
 
    for (const auto & node : node_names)
    {
       AIS_LOG_ERROR("%s ", node.c_str());
    }
 
   AIS_LOG_ERROR("============= ROS2 Topics ===========================");
 
    auto topics = rosNode_->get_topic_names_and_types();
 
    for (const auto & topic : topics)
    {
       AIS_LOG_ERROR("  %s ", topic.first.c_str());
 
        for (const auto & type : topic.second)
        {
           AIS_LOG_ERROR("      Type: %s ", type.c_str());
        }
    }
 
}
