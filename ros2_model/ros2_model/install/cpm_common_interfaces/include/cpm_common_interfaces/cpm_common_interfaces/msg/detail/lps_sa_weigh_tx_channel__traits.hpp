// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaWeighTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_tx_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/lps_sa_weigh_tx_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'payload'
#include "cpm_common_interfaces/msg/detail/payload__traits.hpp"
// Member 'lft_seal_status'
#include "cpm_common_interfaces/msg/detail/lft_seal_status__traits.hpp"
// Member 'lift_position'
#include "cpm_common_interfaces/msg/detail/lift_position__traits.hpp"
// Member 'lift_cyl_vel'
// Member 'lift_valve_command'
// Member 'tilt_valve_command'
#include "cpm_common_interfaces/msg/detail/float_io__traits.hpp"
// Member 'tilt_position'
#include "cpm_common_interfaces/msg/detail/tilt_position__traits.hpp"
// Member 'weigh_range'
#include "cpm_common_interfaces/msg/detail/weigh_range__traits.hpp"
// Member 'event_state'
#include "cpm_common_interfaces/msg/detail/acd_event_pop_up__traits.hpp"
// Member 'diag_state'
#include "cpm_common_interfaces/msg/detail/acd_diag_pop_up__traits.hpp"
// Member 'info_state'
#include "cpm_common_interfaces/msg/detail/acd_info_pop_up__traits.hpp"
// Member 'pid_data'
#include "cpm_common_interfaces/msg/detail/weigh_pid_data__traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaWeighTxChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: time_point_ns
  {
    out << "time_point_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.time_point_ns, out);
    out << ", ";
  }

  // member: dig_stat
  {
    out << "dig_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_stat, out);
    out << ", ";
  }

  // member: cal_stat
  {
    out << "cal_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_stat, out);
    out << ", ";
  }

  // member: dump_stat
  {
    out << "dump_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.dump_stat, out);
    out << ", ";
  }

  // member: best_bkt_wt_in_tonnes
  {
    out << "best_bkt_wt_in_tonnes: ";
    rosidl_generator_traits::value_to_yaml(msg.best_bkt_wt_in_tonnes, out);
    out << ", ";
  }

  // member: warmup_lifts_required
  {
    out << "warmup_lifts_required: ";
    rosidl_generator_traits::value_to_yaml(msg.warmup_lifts_required, out);
    out << ", ";
  }

  // member: payload_calc_meth
  {
    out << "payload_calc_meth: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_calc_meth, out);
    out << ", ";
  }

  // member: bkt_wt_latched_flag
  {
    out << "bkt_wt_latched_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.bkt_wt_latched_flag, out);
    out << ", ";
  }

  // member: latch_conditions_met
  {
    out << "latch_conditions_met: ";
    rosidl_generator_traits::value_to_yaml(msg.latch_conditions_met, out);
    out << ", ";
  }

  // member: zero_available
  {
    out << "zero_available: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_available, out);
    out << ", ";
  }

  // member: payload
  {
    out << "payload: ";
    to_flow_style_yaml(msg.payload, out);
    out << ", ";
  }

  // member: lft_seal_status
  {
    out << "lft_seal_status: ";
    to_flow_style_yaml(msg.lft_seal_status, out);
    out << ", ";
  }

  // member: flash_enabled
  {
    out << "flash_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.flash_enabled, out);
    out << ", ";
  }

  // member: lift_position_sensor_id
  {
    out << "lift_position_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_position_sensor_id, out);
    out << ", ";
  }

  // member: tilt_position_sensor_id
  {
    out << "tilt_position_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_position_sensor_id, out);
    out << ", ";
  }

  // member: lift_head_end_pressure_sensor_id
  {
    out << "lift_head_end_pressure_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_head_end_pressure_sensor_id, out);
    out << ", ";
  }

  // member: lift_rod_end_pressure_sensor_id
  {
    out << "lift_rod_end_pressure_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_rod_end_pressure_sensor_id, out);
    out << ", ";
  }

  // member: hydraulic_oil_temperature_sensor_id
  {
    out << "hydraulic_oil_temperature_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.hydraulic_oil_temperature_sensor_id, out);
    out << ", ";
  }

  // member: imu_sensor_id
  {
    out << "imu_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.imu_sensor_id, out);
    out << ", ";
  }

  // member: implement_serial_num
  {
    out << "implement_serial_num: ";
    rosidl_generator_traits::value_to_yaml(msg.implement_serial_num, out);
    out << ", ";
  }

  // member: work_tool_id
  {
    out << "work_tool_id: ";
    rosidl_generator_traits::value_to_yaml(msg.work_tool_id, out);
    out << ", ";
  }

  // member: lift_position
  {
    out << "lift_position: ";
    to_flow_style_yaml(msg.lift_position, out);
    out << ", ";
  }

  // member: lift_cyl_vel
  {
    out << "lift_cyl_vel: ";
    to_flow_style_yaml(msg.lift_cyl_vel, out);
    out << ", ";
  }

  // member: tilt_position
  {
    out << "tilt_position: ";
    to_flow_style_yaml(msg.tilt_position, out);
    out << ", ";
  }

  // member: weigh_range
  {
    out << "weigh_range: ";
    to_flow_style_yaml(msg.weigh_range, out);
    out << ", ";
  }

  // member: indicator
  {
    out << "indicator: ";
    rosidl_generator_traits::value_to_yaml(msg.indicator, out);
    out << ", ";
  }

  // member: cal_wt
  {
    out << "cal_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_wt, out);
    out << ", ";
  }

  // member: lift_stalled
  {
    out << "lift_stalled: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_stalled, out);
    out << ", ";
  }

  // member: lift_valve_command
  {
    out << "lift_valve_command: ";
    to_flow_style_yaml(msg.lift_valve_command, out);
    out << ", ";
  }

  // member: tilt_valve_command
  {
    out << "tilt_valve_command: ";
    to_flow_style_yaml(msg.tilt_valve_command, out);
    out << ", ";
  }

  // member: event_state
  {
    out << "event_state: ";
    to_flow_style_yaml(msg.event_state, out);
    out << ", ";
  }

  // member: diag_state
  {
    out << "diag_state: ";
    to_flow_style_yaml(msg.diag_state, out);
    out << ", ";
  }

  // member: info_state
  {
    out << "info_state: ";
    to_flow_style_yaml(msg.info_state, out);
    out << ", ";
  }

  // member: show_exclamation_point
  {
    out << "show_exclamation_point: ";
    rosidl_generator_traits::value_to_yaml(msg.show_exclamation_point, out);
    out << ", ";
  }

  // member: excessive_pitch
  {
    out << "excessive_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.excessive_pitch, out);
    out << ", ";
  }

  // member: bucket_fully_racked
  {
    out << "bucket_fully_racked: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_fully_racked, out);
    out << ", ";
  }

  // member: zero_weight
  {
    out << "zero_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_weight, out);
    out << ", ";
  }

  // member: simple_cal_adjust
  {
    out << "simple_cal_adjust: ";
    rosidl_generator_traits::value_to_yaml(msg.simple_cal_adjust, out);
    out << ", ";
  }

  // member: engine_speed_rpm
  {
    out << "engine_speed_rpm: ";
    rosidl_generator_traits::value_to_yaml(msg.engine_speed_rpm, out);
    out << ", ";
  }

  // member: pid_data
  {
    out << "pid_data: ";
    to_flow_style_yaml(msg.pid_data, out);
    out << ", ";
  }

  // member: can11_message_timeout_flag
  {
    out << "can11_message_timeout_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.can11_message_timeout_flag, out);
    out << ", ";
  }

  // member: toa_anchored_zero_offset
  {
    out << "toa_anchored_zero_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_anchored_zero_offset, out);
    out << ", ";
  }

  // member: toa_anchored_factor
  {
    out << "toa_anchored_factor: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_anchored_factor, out);
    out << ", ";
  }

  // member: toa_anchor_status
  {
    out << "toa_anchor_status: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_anchor_status, out);
    out << ", ";
  }

  // member: payload_cal_in_progress
  {
    out << "payload_cal_in_progress: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_cal_in_progress, out);
    out << ", ";
  }

  // member: test_status
  {
    out << "test_status: ";
    rosidl_generator_traits::value_to_yaml(msg.test_status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaWeighTxChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: time_point_ns
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_point_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.time_point_ns, out);
    out << "\n";
  }

  // member: dig_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dig_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_stat, out);
    out << "\n";
  }

  // member: cal_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_stat, out);
    out << "\n";
  }

  // member: dump_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dump_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.dump_stat, out);
    out << "\n";
  }

  // member: best_bkt_wt_in_tonnes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "best_bkt_wt_in_tonnes: ";
    rosidl_generator_traits::value_to_yaml(msg.best_bkt_wt_in_tonnes, out);
    out << "\n";
  }

  // member: warmup_lifts_required
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "warmup_lifts_required: ";
    rosidl_generator_traits::value_to_yaml(msg.warmup_lifts_required, out);
    out << "\n";
  }

  // member: payload_calc_meth
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_calc_meth: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_calc_meth, out);
    out << "\n";
  }

  // member: bkt_wt_latched_flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bkt_wt_latched_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.bkt_wt_latched_flag, out);
    out << "\n";
  }

  // member: latch_conditions_met
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "latch_conditions_met: ";
    rosidl_generator_traits::value_to_yaml(msg.latch_conditions_met, out);
    out << "\n";
  }

  // member: zero_available
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zero_available: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_available, out);
    out << "\n";
  }

  // member: payload
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload:\n";
    to_block_style_yaml(msg.payload, out, indentation + 2);
  }

  // member: lft_seal_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lft_seal_status:\n";
    to_block_style_yaml(msg.lft_seal_status, out, indentation + 2);
  }

  // member: flash_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "flash_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.flash_enabled, out);
    out << "\n";
  }

  // member: lift_position_sensor_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_position_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_position_sensor_id, out);
    out << "\n";
  }

  // member: tilt_position_sensor_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_position_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_position_sensor_id, out);
    out << "\n";
  }

  // member: lift_head_end_pressure_sensor_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_head_end_pressure_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_head_end_pressure_sensor_id, out);
    out << "\n";
  }

  // member: lift_rod_end_pressure_sensor_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_rod_end_pressure_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_rod_end_pressure_sensor_id, out);
    out << "\n";
  }

  // member: hydraulic_oil_temperature_sensor_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hydraulic_oil_temperature_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.hydraulic_oil_temperature_sensor_id, out);
    out << "\n";
  }

  // member: imu_sensor_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "imu_sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.imu_sensor_id, out);
    out << "\n";
  }

  // member: implement_serial_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "implement_serial_num: ";
    rosidl_generator_traits::value_to_yaml(msg.implement_serial_num, out);
    out << "\n";
  }

  // member: work_tool_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "work_tool_id: ";
    rosidl_generator_traits::value_to_yaml(msg.work_tool_id, out);
    out << "\n";
  }

  // member: lift_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_position:\n";
    to_block_style_yaml(msg.lift_position, out, indentation + 2);
  }

  // member: lift_cyl_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_cyl_vel:\n";
    to_block_style_yaml(msg.lift_cyl_vel, out, indentation + 2);
  }

  // member: tilt_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_position:\n";
    to_block_style_yaml(msg.tilt_position, out, indentation + 2);
  }

  // member: weigh_range
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weigh_range:\n";
    to_block_style_yaml(msg.weigh_range, out, indentation + 2);
  }

  // member: indicator
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "indicator: ";
    rosidl_generator_traits::value_to_yaml(msg.indicator, out);
    out << "\n";
  }

  // member: cal_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_wt, out);
    out << "\n";
  }

  // member: lift_stalled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_stalled: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_stalled, out);
    out << "\n";
  }

  // member: lift_valve_command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_valve_command:\n";
    to_block_style_yaml(msg.lift_valve_command, out, indentation + 2);
  }

  // member: tilt_valve_command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_valve_command:\n";
    to_block_style_yaml(msg.tilt_valve_command, out, indentation + 2);
  }

  // member: event_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "event_state:\n";
    to_block_style_yaml(msg.event_state, out, indentation + 2);
  }

  // member: diag_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "diag_state:\n";
    to_block_style_yaml(msg.diag_state, out, indentation + 2);
  }

  // member: info_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info_state:\n";
    to_block_style_yaml(msg.info_state, out, indentation + 2);
  }

  // member: show_exclamation_point
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "show_exclamation_point: ";
    rosidl_generator_traits::value_to_yaml(msg.show_exclamation_point, out);
    out << "\n";
  }

  // member: excessive_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "excessive_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.excessive_pitch, out);
    out << "\n";
  }

  // member: bucket_fully_racked
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bucket_fully_racked: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_fully_racked, out);
    out << "\n";
  }

  // member: zero_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zero_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_weight, out);
    out << "\n";
  }

  // member: simple_cal_adjust
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "simple_cal_adjust: ";
    rosidl_generator_traits::value_to_yaml(msg.simple_cal_adjust, out);
    out << "\n";
  }

  // member: engine_speed_rpm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "engine_speed_rpm: ";
    rosidl_generator_traits::value_to_yaml(msg.engine_speed_rpm, out);
    out << "\n";
  }

  // member: pid_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pid_data:\n";
    to_block_style_yaml(msg.pid_data, out, indentation + 2);
  }

  // member: can11_message_timeout_flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "can11_message_timeout_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.can11_message_timeout_flag, out);
    out << "\n";
  }

  // member: toa_anchored_zero_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_anchored_zero_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_anchored_zero_offset, out);
    out << "\n";
  }

  // member: toa_anchored_factor
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_anchored_factor: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_anchored_factor, out);
    out << "\n";
  }

  // member: toa_anchor_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_anchor_status: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_anchor_status, out);
    out << "\n";
  }

  // member: payload_cal_in_progress
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_cal_in_progress: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_cal_in_progress, out);
    out << "\n";
  }

  // member: test_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "test_status: ";
    rosidl_generator_traits::value_to_yaml(msg.test_status, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaWeighTxChannel & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace cpm_common_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cpm_common_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::LpsSaWeighTxChannel & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::LpsSaWeighTxChannel>()
{
  return "cpm_common_interfaces::msg::LpsSaWeighTxChannel";
}

template<>
inline const char * name<cpm_common_interfaces::msg::LpsSaWeighTxChannel>()
{
  return "cpm_common_interfaces/msg/LpsSaWeighTxChannel";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::LpsSaWeighTxChannel>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::LpsSaWeighTxChannel>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cpm_common_interfaces::msg::LpsSaWeighTxChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__TRAITS_HPP_
