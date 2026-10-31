// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/TipoffAssistOutputs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_assist_outputs.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/tipoff_assist_outputs__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TipoffAssistOutputs & msg,
  std::ostream & out)
{
  out << "{";
  // member: tilt_sensitivity_out
  {
    out << "tilt_sensitivity_out: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_sensitivity_out, out);
    out << ", ";
  }

  // member: tilt_pressure_out
  {
    out << "tilt_pressure_out: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_pressure_out, out);
    out << ", ";
  }

  // member: arbitrated_payload_norm_error_out
  {
    out << "arbitrated_payload_norm_error_out: ";
    rosidl_generator_traits::value_to_yaml(msg.arbitrated_payload_norm_error_out, out);
    out << ", ";
  }

  // member: weigh_status_out
  {
    out << "weigh_status_out: ";
    rosidl_generator_traits::value_to_yaml(msg.weigh_status_out, out);
    out << ", ";
  }

  // member: payload_norm_stdev_out
  {
    out << "payload_norm_stdev_out: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_norm_stdev_out, out);
    out << ", ";
  }

  // member: pcs_weight_accuracy_out
  {
    out << "pcs_weight_accuracy_out: ";
    rosidl_generator_traits::value_to_yaml(msg.pcs_weight_accuracy_out, out);
    out << ", ";
  }

  // member: current_weight_norm_error_out
  {
    out << "current_weight_norm_error_out: ";
    rosidl_generator_traits::value_to_yaml(msg.current_weight_norm_error_out, out);
    out << ", ";
  }

  // member: error_code_out
  {
    out << "error_code_out: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code_out, out);
    out << ", ";
  }

  // member: spill_rate_out
  {
    out << "spill_rate_out: ";
    rosidl_generator_traits::value_to_yaml(msg.spill_rate_out, out);
    out << ", ";
  }

  // member: payload_send_to_cpm
  {
    out << "payload_send_to_cpm: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_send_to_cpm, out);
    out << ", ";
  }

  // member: payload_status_send_to_cpm
  {
    out << "payload_status_send_to_cpm: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_status_send_to_cpm, out);
    out << ", ";
  }

  // member: bucket_payload_target
  {
    out << "bucket_payload_target: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_payload_target, out);
    out << ", ";
  }

  // member: unsecured_payload_upper_bound_norm
  {
    out << "unsecured_payload_upper_bound_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.unsecured_payload_upper_bound_norm, out);
    out << ", ";
  }

  // member: unsecured_payload_lower_bound_norm
  {
    out << "unsecured_payload_lower_bound_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.unsecured_payload_lower_bound_norm, out);
    out << ", ";
  }

  // member: unsecured_pfw_status
  {
    out << "unsecured_pfw_status: ";
    rosidl_generator_traits::value_to_yaml(msg.unsecured_pfw_status, out);
    out << ", ";
  }

  // member: min_secure_bucket_angle
  {
    out << "min_secure_bucket_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.min_secure_bucket_angle, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TipoffAssistOutputs & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: tilt_sensitivity_out
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_sensitivity_out: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_sensitivity_out, out);
    out << "\n";
  }

  // member: tilt_pressure_out
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_pressure_out: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_pressure_out, out);
    out << "\n";
  }

  // member: arbitrated_payload_norm_error_out
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arbitrated_payload_norm_error_out: ";
    rosidl_generator_traits::value_to_yaml(msg.arbitrated_payload_norm_error_out, out);
    out << "\n";
  }

  // member: weigh_status_out
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weigh_status_out: ";
    rosidl_generator_traits::value_to_yaml(msg.weigh_status_out, out);
    out << "\n";
  }

  // member: payload_norm_stdev_out
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_norm_stdev_out: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_norm_stdev_out, out);
    out << "\n";
  }

  // member: pcs_weight_accuracy_out
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pcs_weight_accuracy_out: ";
    rosidl_generator_traits::value_to_yaml(msg.pcs_weight_accuracy_out, out);
    out << "\n";
  }

  // member: current_weight_norm_error_out
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_weight_norm_error_out: ";
    rosidl_generator_traits::value_to_yaml(msg.current_weight_norm_error_out, out);
    out << "\n";
  }

  // member: error_code_out
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_code_out: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code_out, out);
    out << "\n";
  }

  // member: spill_rate_out
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "spill_rate_out: ";
    rosidl_generator_traits::value_to_yaml(msg.spill_rate_out, out);
    out << "\n";
  }

  // member: payload_send_to_cpm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_send_to_cpm: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_send_to_cpm, out);
    out << "\n";
  }

  // member: payload_status_send_to_cpm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_status_send_to_cpm: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_status_send_to_cpm, out);
    out << "\n";
  }

  // member: bucket_payload_target
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bucket_payload_target: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_payload_target, out);
    out << "\n";
  }

  // member: unsecured_payload_upper_bound_norm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "unsecured_payload_upper_bound_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.unsecured_payload_upper_bound_norm, out);
    out << "\n";
  }

  // member: unsecured_payload_lower_bound_norm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "unsecured_payload_lower_bound_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.unsecured_payload_lower_bound_norm, out);
    out << "\n";
  }

  // member: unsecured_pfw_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "unsecured_pfw_status: ";
    rosidl_generator_traits::value_to_yaml(msg.unsecured_pfw_status, out);
    out << "\n";
  }

  // member: min_secure_bucket_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "min_secure_bucket_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.min_secure_bucket_angle, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TipoffAssistOutputs & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::TipoffAssistOutputs & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::TipoffAssistOutputs & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::TipoffAssistOutputs>()
{
  return "weigh_app_interfaces::msg::TipoffAssistOutputs";
}

template<>
inline const char * name<weigh_app_interfaces::msg::TipoffAssistOutputs>()
{
  return "weigh_app_interfaces/msg/TipoffAssistOutputs";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::TipoffAssistOutputs>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::TipoffAssistOutputs>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::TipoffAssistOutputs>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__TRAITS_HPP_
