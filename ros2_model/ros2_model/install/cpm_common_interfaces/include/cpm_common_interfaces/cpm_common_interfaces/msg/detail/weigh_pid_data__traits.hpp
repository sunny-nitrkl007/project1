// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/WeighPidData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/weigh_pid_data.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/weigh_pid_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'prod_measure_sensor_status'
#include "cpm_common_interfaces/msg/detail/prod_measure_sensor_status__traits.hpp"
// Member 'link_sensor_cal_lim'
#include "cpm_common_interfaces/msg/detail/link_sensor_cal_lim__traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const WeighPidData & msg,
  std::ostream & out)
{
  out << "{";
  // member: pload_sys_zero_stat
  {
    out << "pload_sys_zero_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.pload_sys_zero_stat, out);
    out << ", ";
  }

  // member: ldr_payload_stat
  {
    out << "ldr_payload_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.ldr_payload_stat, out);
    out << ", ";
  }

  // member: overload_warning_enabled
  {
    out << "overload_warning_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warning_enabled, out);
    out << ", ";
  }

  // member: prod_measure_sensor_status
  {
    out << "prod_measure_sensor_status: ";
    to_flow_style_yaml(msg.prod_measure_sensor_status, out);
    out << ", ";
  }

  // member: link_sensor_cal_lim
  {
    out << "link_sensor_cal_lim: ";
    to_flow_style_yaml(msg.link_sensor_cal_lim, out);
    out << ", ";
  }

  // member: loader_bkt_pload_tgt_wt
  {
    out << "loader_bkt_pload_tgt_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.loader_bkt_pload_tgt_wt, out);
    out << ", ";
  }

  // member: loader_bkt_pload_tgt_wt_per
  {
    out << "loader_bkt_pload_tgt_wt_per: ";
    rosidl_generator_traits::value_to_yaml(msg.loader_bkt_pload_tgt_wt_per, out);
    out << ", ";
  }

  // member: pload_sys_zero_req_stat
  {
    out << "pload_sys_zero_req_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.pload_sys_zero_req_stat, out);
    out << ", ";
  }

  // member: pload_sys_cal_wt_entry_req_stat
  {
    out << "pload_sys_cal_wt_entry_req_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.pload_sys_cal_wt_entry_req_stat, out);
    out << ", ";
  }

  // member: last_pload_wt
  {
    out << "last_pload_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.last_pload_wt, out);
    out << ", ";
  }

  // member: prod_measure_weigh_status
  {
    out << "prod_measure_weigh_status: ";
    rosidl_generator_traits::value_to_yaml(msg.prod_measure_weigh_status, out);
    out << ", ";
  }

  // member: bkt_payload_data
  {
    out << "bkt_payload_data: ";
    rosidl_generator_traits::value_to_yaml(msg.bkt_payload_data, out);
    out << ", ";
  }

  // member: qr_hyd_oil_temp_min_c
  {
    out << "qr_hyd_oil_temp_min_c: ";
    rosidl_generator_traits::value_to_yaml(msg.qr_hyd_oil_temp_min_c, out);
    out << ", ";
  }

  // member: qr_lift_cyl_vel_min_mm_sec
  {
    out << "qr_lift_cyl_vel_min_mm_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.qr_lift_cyl_vel_min_mm_sec, out);
    out << ", ";
  }

  // member: qr_lift_cyl_vel_max_mm_sec
  {
    out << "qr_lift_cyl_vel_max_mm_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.qr_lift_cyl_vel_max_mm_sec, out);
    out << ", ";
  }

  // member: machine_rear_lateral_acceleration
  {
    out << "machine_rear_lateral_acceleration: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_rear_lateral_acceleration, out);
    out << ", ";
  }

  // member: machine_rear_longitudinal_acceleration
  {
    out << "machine_rear_longitudinal_acceleration: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_rear_longitudinal_acceleration, out);
    out << ", ";
  }

  // member: machine_rear_vertical_acceleration
  {
    out << "machine_rear_vertical_acceleration: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_rear_vertical_acceleration, out);
    out << ", ";
  }

  // member: machine_pitch
  {
    out << "machine_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_pitch, out);
    out << ", ";
  }

  // member: machine_slope
  {
    out << "machine_slope: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_slope, out);
    out << ", ";
  }

  // member: machine_rear_roll
  {
    out << "machine_rear_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_rear_roll, out);
    out << ", ";
  }

  // member: machine_rear_side_slope
  {
    out << "machine_rear_side_slope: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_rear_side_slope, out);
    out << ", ";
  }

  // member: machine_roll
  {
    out << "machine_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_roll, out);
    out << ", ";
  }

  // member: machine_side_slope
  {
    out << "machine_side_slope: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_side_slope, out);
    out << ", ";
  }

  // member: tipoff_pitch_cal_offset
  {
    out << "tipoff_pitch_cal_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_pitch_cal_offset, out);
    out << ", ";
  }

  // member: hyd_oil_temp_enabled
  {
    out << "hyd_oil_temp_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.hyd_oil_temp_enabled, out);
    out << ", ";
  }

  // member: audible_weight_enabled
  {
    out << "audible_weight_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.audible_weight_enabled, out);
    out << ", ";
  }

  // member: audible_weight_command
  {
    out << "audible_weight_command: ";
    rosidl_generator_traits::value_to_yaml(msg.audible_weight_command, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const WeighPidData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pload_sys_zero_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pload_sys_zero_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.pload_sys_zero_stat, out);
    out << "\n";
  }

  // member: ldr_payload_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ldr_payload_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.ldr_payload_stat, out);
    out << "\n";
  }

  // member: overload_warning_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "overload_warning_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warning_enabled, out);
    out << "\n";
  }

  // member: prod_measure_sensor_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "prod_measure_sensor_status:\n";
    to_block_style_yaml(msg.prod_measure_sensor_status, out, indentation + 2);
  }

  // member: link_sensor_cal_lim
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "link_sensor_cal_lim:\n";
    to_block_style_yaml(msg.link_sensor_cal_lim, out, indentation + 2);
  }

  // member: loader_bkt_pload_tgt_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "loader_bkt_pload_tgt_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.loader_bkt_pload_tgt_wt, out);
    out << "\n";
  }

  // member: loader_bkt_pload_tgt_wt_per
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "loader_bkt_pload_tgt_wt_per: ";
    rosidl_generator_traits::value_to_yaml(msg.loader_bkt_pload_tgt_wt_per, out);
    out << "\n";
  }

  // member: pload_sys_zero_req_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pload_sys_zero_req_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.pload_sys_zero_req_stat, out);
    out << "\n";
  }

  // member: pload_sys_cal_wt_entry_req_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pload_sys_cal_wt_entry_req_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.pload_sys_cal_wt_entry_req_stat, out);
    out << "\n";
  }

  // member: last_pload_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_pload_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.last_pload_wt, out);
    out << "\n";
  }

  // member: prod_measure_weigh_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "prod_measure_weigh_status: ";
    rosidl_generator_traits::value_to_yaml(msg.prod_measure_weigh_status, out);
    out << "\n";
  }

  // member: bkt_payload_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bkt_payload_data: ";
    rosidl_generator_traits::value_to_yaml(msg.bkt_payload_data, out);
    out << "\n";
  }

  // member: qr_hyd_oil_temp_min_c
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "qr_hyd_oil_temp_min_c: ";
    rosidl_generator_traits::value_to_yaml(msg.qr_hyd_oil_temp_min_c, out);
    out << "\n";
  }

  // member: qr_lift_cyl_vel_min_mm_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "qr_lift_cyl_vel_min_mm_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.qr_lift_cyl_vel_min_mm_sec, out);
    out << "\n";
  }

  // member: qr_lift_cyl_vel_max_mm_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "qr_lift_cyl_vel_max_mm_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.qr_lift_cyl_vel_max_mm_sec, out);
    out << "\n";
  }

  // member: machine_rear_lateral_acceleration
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "machine_rear_lateral_acceleration: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_rear_lateral_acceleration, out);
    out << "\n";
  }

  // member: machine_rear_longitudinal_acceleration
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "machine_rear_longitudinal_acceleration: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_rear_longitudinal_acceleration, out);
    out << "\n";
  }

  // member: machine_rear_vertical_acceleration
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "machine_rear_vertical_acceleration: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_rear_vertical_acceleration, out);
    out << "\n";
  }

  // member: machine_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "machine_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_pitch, out);
    out << "\n";
  }

  // member: machine_slope
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "machine_slope: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_slope, out);
    out << "\n";
  }

  // member: machine_rear_roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "machine_rear_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_rear_roll, out);
    out << "\n";
  }

  // member: machine_rear_side_slope
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "machine_rear_side_slope: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_rear_side_slope, out);
    out << "\n";
  }

  // member: machine_roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "machine_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_roll, out);
    out << "\n";
  }

  // member: machine_side_slope
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "machine_side_slope: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_side_slope, out);
    out << "\n";
  }

  // member: tipoff_pitch_cal_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tipoff_pitch_cal_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_pitch_cal_offset, out);
    out << "\n";
  }

  // member: hyd_oil_temp_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hyd_oil_temp_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.hyd_oil_temp_enabled, out);
    out << "\n";
  }

  // member: audible_weight_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "audible_weight_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.audible_weight_enabled, out);
    out << "\n";
  }

  // member: audible_weight_command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "audible_weight_command: ";
    rosidl_generator_traits::value_to_yaml(msg.audible_weight_command, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const WeighPidData & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::WeighPidData & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::WeighPidData & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::WeighPidData>()
{
  return "cpm_common_interfaces::msg::WeighPidData";
}

template<>
inline const char * name<cpm_common_interfaces::msg::WeighPidData>()
{
  return "cpm_common_interfaces/msg/WeighPidData";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::WeighPidData>
  : std::integral_constant<bool, has_fixed_size<cpm_common_interfaces::msg::LinkSensorCalLim>::value && has_fixed_size<cpm_common_interfaces::msg::ProdMeasureSensorStatus>::value> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::WeighPidData>
  : std::integral_constant<bool, has_bounded_size<cpm_common_interfaces::msg::LinkSensorCalLim>::value && has_bounded_size<cpm_common_interfaces::msg::ProdMeasureSensorStatus>::value> {};

template<>
struct is_message<cpm_common_interfaces::msg::WeighPidData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__TRAITS_HPP_
