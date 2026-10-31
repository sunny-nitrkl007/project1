// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaUIDisplayState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_ui_display_state.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/lps_sa_ui_display_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'settings'
#include "cpm_common_interfaces/msg/detail/lps_sa_ui_display_settings__traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaUIDisplayState & msg,
  std::ostream & out)
{
  out << "{";
  // member: service_mode_enable_code_entered
  {
    out << "service_mode_enable_code_entered: ";
    rosidl_generator_traits::value_to_yaml(msg.service_mode_enable_code_entered, out);
    out << ", ";
  }

  // member: in_service_mode
  {
    out << "in_service_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.in_service_mode, out);
    out << ", ";
  }

  // member: in_verification_mode
  {
    out << "in_verification_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.in_verification_mode, out);
    out << ", ";
  }

  // member: heartbeat_count
  {
    out << "heartbeat_count: ";
    rosidl_generator_traits::value_to_yaml(msg.heartbeat_count, out);
    out << ", ";
  }

  // member: document_id
  {
    out << "document_id: ";
    rosidl_generator_traits::value_to_yaml(msg.document_id, out);
    out << ", ";
  }

  // member: weight_capacity
  {
    out << "weight_capacity: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_capacity, out);
    out << ", ";
  }

  // member: weight_decimal_precision
  {
    out << "weight_decimal_precision: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_decimal_precision, out);
    out << ", ";
  }

  // member: weight_interval
  {
    out << "weight_interval: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_interval, out);
    out << ", ";
  }

  // member: settings
  {
    out << "settings: ";
    to_flow_style_yaml(msg.settings, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaUIDisplayState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: service_mode_enable_code_entered
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "service_mode_enable_code_entered: ";
    rosidl_generator_traits::value_to_yaml(msg.service_mode_enable_code_entered, out);
    out << "\n";
  }

  // member: in_service_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "in_service_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.in_service_mode, out);
    out << "\n";
  }

  // member: in_verification_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "in_verification_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.in_verification_mode, out);
    out << "\n";
  }

  // member: heartbeat_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "heartbeat_count: ";
    rosidl_generator_traits::value_to_yaml(msg.heartbeat_count, out);
    out << "\n";
  }

  // member: document_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "document_id: ";
    rosidl_generator_traits::value_to_yaml(msg.document_id, out);
    out << "\n";
  }

  // member: weight_capacity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weight_capacity: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_capacity, out);
    out << "\n";
  }

  // member: weight_decimal_precision
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weight_decimal_precision: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_decimal_precision, out);
    out << "\n";
  }

  // member: weight_interval
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weight_interval: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_interval, out);
    out << "\n";
  }

  // member: settings
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "settings:\n";
    to_block_style_yaml(msg.settings, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaUIDisplayState & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::LpsSaUIDisplayState & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::LpsSaUIDisplayState & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::LpsSaUIDisplayState>()
{
  return "cpm_common_interfaces::msg::LpsSaUIDisplayState";
}

template<>
inline const char * name<cpm_common_interfaces::msg::LpsSaUIDisplayState>()
{
  return "cpm_common_interfaces/msg/LpsSaUIDisplayState";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::LpsSaUIDisplayState>
  : std::integral_constant<bool, has_fixed_size<cpm_common_interfaces::msg::LpsSaUIDisplaySettings>::value> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::LpsSaUIDisplayState>
  : std::integral_constant<bool, has_bounded_size<cpm_common_interfaces::msg::LpsSaUIDisplaySettings>::value> {};

template<>
struct is_message<cpm_common_interfaces::msg::LpsSaUIDisplayState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__TRAITS_HPP_
