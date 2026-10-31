// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/TipoffAssistInputs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_assist_inputs.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/tipoff_assist_inputs__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TipoffAssistInputs & msg,
  std::ostream & out)
{
  out << "{";
  // member: input_status
  {
    out << "input_status: ";
    rosidl_generator_traits::value_to_yaml(msg.input_status, out);
    out << ", ";
  }

  // member: invalidate_outputs
  {
    out << "invalidate_outputs: ";
    rosidl_generator_traits::value_to_yaml(msg.invalidate_outputs, out);
    out << ", ";
  }

  // member: lift_valve_cmd
  {
    out << "lift_valve_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_valve_cmd, out);
    out << ", ";
  }

  // member: tilt_valve_cmd
  {
    out << "tilt_valve_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_valve_cmd, out);
    out << ", ";
  }

  // member: tilt_extension
  {
    out << "tilt_extension: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_extension, out);
    out << ", ";
  }

  // member: lift_angle
  {
    out << "lift_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_angle, out);
    out << ", ";
  }

  // member: lift_he_pressure
  {
    out << "lift_he_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_he_pressure, out);
    out << ", ";
  }

  // member: lift_re_pressure
  {
    out << "lift_re_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_re_pressure, out);
    out << ", ";
  }

  // member: tilt_he_pressure
  {
    out << "tilt_he_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_he_pressure, out);
    out << ", ";
  }

  // member: tilt_re_pressure
  {
    out << "tilt_re_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_re_pressure, out);
    out << ", ";
  }

  // member: eef_imu_accel_x
  {
    out << "eef_imu_accel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.eef_imu_accel_x, out);
    out << ", ";
  }

  // member: eef_imu_accel_y
  {
    out << "eef_imu_accel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.eef_imu_accel_y, out);
    out << ", ";
  }

  // member: eef_imu_accel_z
  {
    out << "eef_imu_accel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.eef_imu_accel_z, out);
    out << ", ";
  }

  // member: steering_angle
  {
    out << "steering_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_angle, out);
    out << ", ";
  }

  // member: tool_mass
  {
    out << "tool_mass: ";
    rosidl_generator_traits::value_to_yaml(msg.tool_mass, out);
    out << ", ";
  }

  // member: truck_target_wt
  {
    out << "truck_target_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_target_wt, out);
    out << ", ";
  }

  // member: truck_start_weight
  {
    out << "truck_start_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_start_weight, out);
    out << ", ";
  }

  // member: bucket_current_weight_accuracy
  {
    out << "bucket_current_weight_accuracy: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_current_weight_accuracy, out);
    out << ", ";
  }

  // member: bucket_current_weight
  {
    out << "bucket_current_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_current_weight, out);
    out << ", ";
  }

  // member: tipoff_mode
  {
    out << "tipoff_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_mode, out);
    out << ", ";
  }

  // member: zero_offset
  {
    out << "zero_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_offset, out);
    out << ", ";
  }

  // member: simple_cal_factor
  {
    out << "simple_cal_factor: ";
    rosidl_generator_traits::value_to_yaml(msg.simple_cal_factor, out);
    out << ", ";
  }

  // member: mach_pitch_cal_offset
  {
    out << "mach_pitch_cal_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.mach_pitch_cal_offset, out);
    out << ", ";
  }

  // member: unlatch_trigger
  {
    out << "unlatch_trigger: ";
    rosidl_generator_traits::value_to_yaml(msg.unlatch_trigger, out);
    out << ", ";
  }

  // member: bucket_angle
  {
    out << "bucket_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_angle, out);
    out << ", ";
  }

  // member: anchor_zero_offset
  {
    out << "anchor_zero_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.anchor_zero_offset, out);
    out << ", ";
  }

  // member: anchor_factor
  {
    out << "anchor_factor: ";
    rosidl_generator_traits::value_to_yaml(msg.anchor_factor, out);
    out << ", ";
  }

  // member: pass_count
  {
    out << "pass_count: ";
    rosidl_generator_traits::value_to_yaml(msg.pass_count, out);
    out << ", ";
  }

  // member: lift_norm_angle
  {
    out << "lift_norm_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_norm_angle, out);
    out << ", ";
  }

  // member: lift_norm_length
  {
    out << "lift_norm_length: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_norm_length, out);
    out << ", ";
  }

  // member: tilt_norm_angle
  {
    out << "tilt_norm_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_norm_angle, out);
    out << ", ";
  }

  // member: tilt_norm_length
  {
    out << "tilt_norm_length: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_norm_length, out);
    out << ", ";
  }

  // member: friction_mu
  {
    out << "friction_mu: ";
    rosidl_generator_traits::value_to_yaml(msg.friction_mu, out);
    out << ", ";
  }

  // member: friction_offset
  {
    out << "friction_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.friction_offset, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TipoffAssistInputs & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: input_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "input_status: ";
    rosidl_generator_traits::value_to_yaml(msg.input_status, out);
    out << "\n";
  }

  // member: invalidate_outputs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "invalidate_outputs: ";
    rosidl_generator_traits::value_to_yaml(msg.invalidate_outputs, out);
    out << "\n";
  }

  // member: lift_valve_cmd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_valve_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_valve_cmd, out);
    out << "\n";
  }

  // member: tilt_valve_cmd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_valve_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_valve_cmd, out);
    out << "\n";
  }

  // member: tilt_extension
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_extension: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_extension, out);
    out << "\n";
  }

  // member: lift_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_angle, out);
    out << "\n";
  }

  // member: lift_he_pressure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_he_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_he_pressure, out);
    out << "\n";
  }

  // member: lift_re_pressure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_re_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_re_pressure, out);
    out << "\n";
  }

  // member: tilt_he_pressure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_he_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_he_pressure, out);
    out << "\n";
  }

  // member: tilt_re_pressure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_re_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_re_pressure, out);
    out << "\n";
  }

  // member: eef_imu_accel_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eef_imu_accel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.eef_imu_accel_x, out);
    out << "\n";
  }

  // member: eef_imu_accel_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eef_imu_accel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.eef_imu_accel_y, out);
    out << "\n";
  }

  // member: eef_imu_accel_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eef_imu_accel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.eef_imu_accel_z, out);
    out << "\n";
  }

  // member: steering_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steering_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_angle, out);
    out << "\n";
  }

  // member: tool_mass
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tool_mass: ";
    rosidl_generator_traits::value_to_yaml(msg.tool_mass, out);
    out << "\n";
  }

  // member: truck_target_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_target_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_target_wt, out);
    out << "\n";
  }

  // member: truck_start_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_start_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_start_weight, out);
    out << "\n";
  }

  // member: bucket_current_weight_accuracy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bucket_current_weight_accuracy: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_current_weight_accuracy, out);
    out << "\n";
  }

  // member: bucket_current_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bucket_current_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_current_weight, out);
    out << "\n";
  }

  // member: tipoff_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tipoff_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_mode, out);
    out << "\n";
  }

  // member: zero_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zero_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_offset, out);
    out << "\n";
  }

  // member: simple_cal_factor
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "simple_cal_factor: ";
    rosidl_generator_traits::value_to_yaml(msg.simple_cal_factor, out);
    out << "\n";
  }

  // member: mach_pitch_cal_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mach_pitch_cal_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.mach_pitch_cal_offset, out);
    out << "\n";
  }

  // member: unlatch_trigger
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "unlatch_trigger: ";
    rosidl_generator_traits::value_to_yaml(msg.unlatch_trigger, out);
    out << "\n";
  }

  // member: bucket_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bucket_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_angle, out);
    out << "\n";
  }

  // member: anchor_zero_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "anchor_zero_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.anchor_zero_offset, out);
    out << "\n";
  }

  // member: anchor_factor
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "anchor_factor: ";
    rosidl_generator_traits::value_to_yaml(msg.anchor_factor, out);
    out << "\n";
  }

  // member: pass_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pass_count: ";
    rosidl_generator_traits::value_to_yaml(msg.pass_count, out);
    out << "\n";
  }

  // member: lift_norm_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_norm_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_norm_angle, out);
    out << "\n";
  }

  // member: lift_norm_length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_norm_length: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_norm_length, out);
    out << "\n";
  }

  // member: tilt_norm_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_norm_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_norm_angle, out);
    out << "\n";
  }

  // member: tilt_norm_length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_norm_length: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_norm_length, out);
    out << "\n";
  }

  // member: friction_mu
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "friction_mu: ";
    rosidl_generator_traits::value_to_yaml(msg.friction_mu, out);
    out << "\n";
  }

  // member: friction_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "friction_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.friction_offset, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TipoffAssistInputs & msg, bool use_flow_style = false)
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

}  // namespace weigh_app_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use weigh_app_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const weigh_app_interfaces::msg::TipoffAssistInputs & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::TipoffAssistInputs & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::TipoffAssistInputs>()
{
  return "weigh_app_interfaces::msg::TipoffAssistInputs";
}

template<>
inline const char * name<weigh_app_interfaces::msg::TipoffAssistInputs>()
{
  return "weigh_app_interfaces/msg/TipoffAssistInputs";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::TipoffAssistInputs>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::TipoffAssistInputs>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::TipoffAssistInputs>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__TRAITS_HPP_
