// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaWeighTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_tx_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/lps_sa_weigh_tx_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaWeighTxChannel_test_status
{
public:
  explicit Init_LpsSaWeighTxChannel_test_status(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel test_status(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_test_status_type arg)
  {
    msg_.test_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_payload_cal_in_progress
{
public:
  explicit Init_LpsSaWeighTxChannel_payload_cal_in_progress(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_test_status payload_cal_in_progress(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_payload_cal_in_progress_type arg)
  {
    msg_.payload_cal_in_progress = std::move(arg);
    return Init_LpsSaWeighTxChannel_test_status(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_toa_anchor_status
{
public:
  explicit Init_LpsSaWeighTxChannel_toa_anchor_status(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_payload_cal_in_progress toa_anchor_status(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_toa_anchor_status_type arg)
  {
    msg_.toa_anchor_status = std::move(arg);
    return Init_LpsSaWeighTxChannel_payload_cal_in_progress(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_toa_anchored_factor
{
public:
  explicit Init_LpsSaWeighTxChannel_toa_anchored_factor(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_toa_anchor_status toa_anchored_factor(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_toa_anchored_factor_type arg)
  {
    msg_.toa_anchored_factor = std::move(arg);
    return Init_LpsSaWeighTxChannel_toa_anchor_status(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_toa_anchored_zero_offset
{
public:
  explicit Init_LpsSaWeighTxChannel_toa_anchored_zero_offset(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_toa_anchored_factor toa_anchored_zero_offset(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_toa_anchored_zero_offset_type arg)
  {
    msg_.toa_anchored_zero_offset = std::move(arg);
    return Init_LpsSaWeighTxChannel_toa_anchored_factor(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_can11_message_timeout_flag
{
public:
  explicit Init_LpsSaWeighTxChannel_can11_message_timeout_flag(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_toa_anchored_zero_offset can11_message_timeout_flag(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_can11_message_timeout_flag_type arg)
  {
    msg_.can11_message_timeout_flag = std::move(arg);
    return Init_LpsSaWeighTxChannel_toa_anchored_zero_offset(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_pid_data
{
public:
  explicit Init_LpsSaWeighTxChannel_pid_data(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_can11_message_timeout_flag pid_data(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_pid_data_type arg)
  {
    msg_.pid_data = std::move(arg);
    return Init_LpsSaWeighTxChannel_can11_message_timeout_flag(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_engine_speed_rpm
{
public:
  explicit Init_LpsSaWeighTxChannel_engine_speed_rpm(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_pid_data engine_speed_rpm(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_engine_speed_rpm_type arg)
  {
    msg_.engine_speed_rpm = std::move(arg);
    return Init_LpsSaWeighTxChannel_pid_data(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_simple_cal_adjust
{
public:
  explicit Init_LpsSaWeighTxChannel_simple_cal_adjust(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_engine_speed_rpm simple_cal_adjust(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_simple_cal_adjust_type arg)
  {
    msg_.simple_cal_adjust = std::move(arg);
    return Init_LpsSaWeighTxChannel_engine_speed_rpm(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_zero_weight
{
public:
  explicit Init_LpsSaWeighTxChannel_zero_weight(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_simple_cal_adjust zero_weight(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_zero_weight_type arg)
  {
    msg_.zero_weight = std::move(arg);
    return Init_LpsSaWeighTxChannel_simple_cal_adjust(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_bucket_fully_racked
{
public:
  explicit Init_LpsSaWeighTxChannel_bucket_fully_racked(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_zero_weight bucket_fully_racked(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_bucket_fully_racked_type arg)
  {
    msg_.bucket_fully_racked = std::move(arg);
    return Init_LpsSaWeighTxChannel_zero_weight(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_excessive_pitch
{
public:
  explicit Init_LpsSaWeighTxChannel_excessive_pitch(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_bucket_fully_racked excessive_pitch(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_excessive_pitch_type arg)
  {
    msg_.excessive_pitch = std::move(arg);
    return Init_LpsSaWeighTxChannel_bucket_fully_racked(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_show_exclamation_point
{
public:
  explicit Init_LpsSaWeighTxChannel_show_exclamation_point(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_excessive_pitch show_exclamation_point(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_show_exclamation_point_type arg)
  {
    msg_.show_exclamation_point = std::move(arg);
    return Init_LpsSaWeighTxChannel_excessive_pitch(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_info_state
{
public:
  explicit Init_LpsSaWeighTxChannel_info_state(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_show_exclamation_point info_state(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_info_state_type arg)
  {
    msg_.info_state = std::move(arg);
    return Init_LpsSaWeighTxChannel_show_exclamation_point(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_diag_state
{
public:
  explicit Init_LpsSaWeighTxChannel_diag_state(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_info_state diag_state(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_diag_state_type arg)
  {
    msg_.diag_state = std::move(arg);
    return Init_LpsSaWeighTxChannel_info_state(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_event_state
{
public:
  explicit Init_LpsSaWeighTxChannel_event_state(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_diag_state event_state(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_event_state_type arg)
  {
    msg_.event_state = std::move(arg);
    return Init_LpsSaWeighTxChannel_diag_state(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_tilt_valve_command
{
public:
  explicit Init_LpsSaWeighTxChannel_tilt_valve_command(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_event_state tilt_valve_command(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_tilt_valve_command_type arg)
  {
    msg_.tilt_valve_command = std::move(arg);
    return Init_LpsSaWeighTxChannel_event_state(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_lift_valve_command
{
public:
  explicit Init_LpsSaWeighTxChannel_lift_valve_command(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_tilt_valve_command lift_valve_command(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_lift_valve_command_type arg)
  {
    msg_.lift_valve_command = std::move(arg);
    return Init_LpsSaWeighTxChannel_tilt_valve_command(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_lift_stalled
{
public:
  explicit Init_LpsSaWeighTxChannel_lift_stalled(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_lift_valve_command lift_stalled(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_lift_stalled_type arg)
  {
    msg_.lift_stalled = std::move(arg);
    return Init_LpsSaWeighTxChannel_lift_valve_command(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_cal_wt
{
public:
  explicit Init_LpsSaWeighTxChannel_cal_wt(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_lift_stalled cal_wt(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_cal_wt_type arg)
  {
    msg_.cal_wt = std::move(arg);
    return Init_LpsSaWeighTxChannel_lift_stalled(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_indicator
{
public:
  explicit Init_LpsSaWeighTxChannel_indicator(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_cal_wt indicator(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_indicator_type arg)
  {
    msg_.indicator = std::move(arg);
    return Init_LpsSaWeighTxChannel_cal_wt(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_weigh_range
{
public:
  explicit Init_LpsSaWeighTxChannel_weigh_range(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_indicator weigh_range(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_weigh_range_type arg)
  {
    msg_.weigh_range = std::move(arg);
    return Init_LpsSaWeighTxChannel_indicator(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_tilt_position
{
public:
  explicit Init_LpsSaWeighTxChannel_tilt_position(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_weigh_range tilt_position(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_tilt_position_type arg)
  {
    msg_.tilt_position = std::move(arg);
    return Init_LpsSaWeighTxChannel_weigh_range(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_lift_cyl_vel
{
public:
  explicit Init_LpsSaWeighTxChannel_lift_cyl_vel(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_tilt_position lift_cyl_vel(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_lift_cyl_vel_type arg)
  {
    msg_.lift_cyl_vel = std::move(arg);
    return Init_LpsSaWeighTxChannel_tilt_position(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_lift_position
{
public:
  explicit Init_LpsSaWeighTxChannel_lift_position(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_lift_cyl_vel lift_position(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_lift_position_type arg)
  {
    msg_.lift_position = std::move(arg);
    return Init_LpsSaWeighTxChannel_lift_cyl_vel(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_work_tool_id
{
public:
  explicit Init_LpsSaWeighTxChannel_work_tool_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_lift_position work_tool_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_work_tool_id_type arg)
  {
    msg_.work_tool_id = std::move(arg);
    return Init_LpsSaWeighTxChannel_lift_position(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_implement_serial_num
{
public:
  explicit Init_LpsSaWeighTxChannel_implement_serial_num(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_work_tool_id implement_serial_num(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_implement_serial_num_type arg)
  {
    msg_.implement_serial_num = std::move(arg);
    return Init_LpsSaWeighTxChannel_work_tool_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_imu_sensor_id
{
public:
  explicit Init_LpsSaWeighTxChannel_imu_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_implement_serial_num imu_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_imu_sensor_id_type arg)
  {
    msg_.imu_sensor_id = std::move(arg);
    return Init_LpsSaWeighTxChannel_implement_serial_num(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_hydraulic_oil_temperature_sensor_id
{
public:
  explicit Init_LpsSaWeighTxChannel_hydraulic_oil_temperature_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_imu_sensor_id hydraulic_oil_temperature_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_hydraulic_oil_temperature_sensor_id_type arg)
  {
    msg_.hydraulic_oil_temperature_sensor_id = std::move(arg);
    return Init_LpsSaWeighTxChannel_imu_sensor_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_lift_rod_end_pressure_sensor_id
{
public:
  explicit Init_LpsSaWeighTxChannel_lift_rod_end_pressure_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_hydraulic_oil_temperature_sensor_id lift_rod_end_pressure_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_lift_rod_end_pressure_sensor_id_type arg)
  {
    msg_.lift_rod_end_pressure_sensor_id = std::move(arg);
    return Init_LpsSaWeighTxChannel_hydraulic_oil_temperature_sensor_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_lift_head_end_pressure_sensor_id
{
public:
  explicit Init_LpsSaWeighTxChannel_lift_head_end_pressure_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_lift_rod_end_pressure_sensor_id lift_head_end_pressure_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_lift_head_end_pressure_sensor_id_type arg)
  {
    msg_.lift_head_end_pressure_sensor_id = std::move(arg);
    return Init_LpsSaWeighTxChannel_lift_rod_end_pressure_sensor_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_tilt_position_sensor_id
{
public:
  explicit Init_LpsSaWeighTxChannel_tilt_position_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_lift_head_end_pressure_sensor_id tilt_position_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_tilt_position_sensor_id_type arg)
  {
    msg_.tilt_position_sensor_id = std::move(arg);
    return Init_LpsSaWeighTxChannel_lift_head_end_pressure_sensor_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_lift_position_sensor_id
{
public:
  explicit Init_LpsSaWeighTxChannel_lift_position_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_tilt_position_sensor_id lift_position_sensor_id(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_lift_position_sensor_id_type arg)
  {
    msg_.lift_position_sensor_id = std::move(arg);
    return Init_LpsSaWeighTxChannel_tilt_position_sensor_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_flash_enabled
{
public:
  explicit Init_LpsSaWeighTxChannel_flash_enabled(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_lift_position_sensor_id flash_enabled(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_flash_enabled_type arg)
  {
    msg_.flash_enabled = std::move(arg);
    return Init_LpsSaWeighTxChannel_lift_position_sensor_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_lft_seal_status
{
public:
  explicit Init_LpsSaWeighTxChannel_lft_seal_status(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_flash_enabled lft_seal_status(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_lft_seal_status_type arg)
  {
    msg_.lft_seal_status = std::move(arg);
    return Init_LpsSaWeighTxChannel_flash_enabled(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_payload
{
public:
  explicit Init_LpsSaWeighTxChannel_payload(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_lft_seal_status payload(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_payload_type arg)
  {
    msg_.payload = std::move(arg);
    return Init_LpsSaWeighTxChannel_lft_seal_status(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_zero_available
{
public:
  explicit Init_LpsSaWeighTxChannel_zero_available(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_payload zero_available(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_zero_available_type arg)
  {
    msg_.zero_available = std::move(arg);
    return Init_LpsSaWeighTxChannel_payload(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_latch_conditions_met
{
public:
  explicit Init_LpsSaWeighTxChannel_latch_conditions_met(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_zero_available latch_conditions_met(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_latch_conditions_met_type arg)
  {
    msg_.latch_conditions_met = std::move(arg);
    return Init_LpsSaWeighTxChannel_zero_available(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_bkt_wt_latched_flag
{
public:
  explicit Init_LpsSaWeighTxChannel_bkt_wt_latched_flag(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_latch_conditions_met bkt_wt_latched_flag(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_bkt_wt_latched_flag_type arg)
  {
    msg_.bkt_wt_latched_flag = std::move(arg);
    return Init_LpsSaWeighTxChannel_latch_conditions_met(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_payload_calc_meth
{
public:
  explicit Init_LpsSaWeighTxChannel_payload_calc_meth(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_bkt_wt_latched_flag payload_calc_meth(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_payload_calc_meth_type arg)
  {
    msg_.payload_calc_meth = std::move(arg);
    return Init_LpsSaWeighTxChannel_bkt_wt_latched_flag(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_warmup_lifts_required
{
public:
  explicit Init_LpsSaWeighTxChannel_warmup_lifts_required(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_payload_calc_meth warmup_lifts_required(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_warmup_lifts_required_type arg)
  {
    msg_.warmup_lifts_required = std::move(arg);
    return Init_LpsSaWeighTxChannel_payload_calc_meth(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_best_bkt_wt_in_tonnes
{
public:
  explicit Init_LpsSaWeighTxChannel_best_bkt_wt_in_tonnes(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_warmup_lifts_required best_bkt_wt_in_tonnes(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_best_bkt_wt_in_tonnes_type arg)
  {
    msg_.best_bkt_wt_in_tonnes = std::move(arg);
    return Init_LpsSaWeighTxChannel_warmup_lifts_required(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_dump_stat
{
public:
  explicit Init_LpsSaWeighTxChannel_dump_stat(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_best_bkt_wt_in_tonnes dump_stat(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_dump_stat_type arg)
  {
    msg_.dump_stat = std::move(arg);
    return Init_LpsSaWeighTxChannel_best_bkt_wt_in_tonnes(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_cal_stat
{
public:
  explicit Init_LpsSaWeighTxChannel_cal_stat(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_dump_stat cal_stat(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_cal_stat_type arg)
  {
    msg_.cal_stat = std::move(arg);
    return Init_LpsSaWeighTxChannel_dump_stat(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_dig_stat
{
public:
  explicit Init_LpsSaWeighTxChannel_dig_stat(::cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighTxChannel_cal_stat dig_stat(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_dig_stat_type arg)
  {
    msg_.dig_stat = std::move(arg);
    return Init_LpsSaWeighTxChannel_cal_stat(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

class Init_LpsSaWeighTxChannel_time_point_ns
{
public:
  Init_LpsSaWeighTxChannel_time_point_ns()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaWeighTxChannel_dig_stat time_point_ns(::cpm_common_interfaces::msg::LpsSaWeighTxChannel::_time_point_ns_type arg)
  {
    msg_.time_point_ns = std::move(arg);
    return Init_LpsSaWeighTxChannel_dig_stat(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighTxChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LpsSaWeighTxChannel>()
{
  return cpm_common_interfaces::msg::builder::Init_LpsSaWeighTxChannel_time_point_ns();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__BUILDER_HPP_
