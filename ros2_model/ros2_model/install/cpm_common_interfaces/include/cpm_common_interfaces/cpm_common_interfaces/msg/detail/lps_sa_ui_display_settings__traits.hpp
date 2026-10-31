// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaUIDisplaySettings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_ui_display_settings.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/lps_sa_ui_display_settings__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaUIDisplaySettings & msg,
  std::ostream & out)
{
  out << "{";
  // member: units
  {
    out << "units: ";
    rosidl_generator_traits::value_to_yaml(msg.units, out);
    out << ", ";
  }

  // member: language
  {
    out << "language: ";
    rosidl_generator_traits::value_to_yaml(msg.language, out);
    out << ", ";
  }

  // member: brightness
  {
    out << "brightness: ";
    rosidl_generator_traits::value_to_yaml(msg.brightness, out);
    out << ", ";
  }

  // member: time_format
  {
    out << "time_format: ";
    rosidl_generator_traits::value_to_yaml(msg.time_format, out);
    out << ", ";
  }

  // member: date_format
  {
    out << "date_format: ";
    rosidl_generator_traits::value_to_yaml(msg.date_format, out);
    out << ", ";
  }

  // member: weight_units
  {
    out << "weight_units: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_units, out);
    out << ", ";
  }

  // member: weight_precision
  {
    out << "weight_precision: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_precision, out);
    out << ", ";
  }

  // member: service_mode_enable_code
  {
    out << "service_mode_enable_code: ";
    rosidl_generator_traits::value_to_yaml(msg.service_mode_enable_code, out);
    out << ", ";
  }

  // member: keyboard_layout_setting
  {
    out << "keyboard_layout_setting: ";
    rosidl_generator_traits::value_to_yaml(msg.keyboard_layout_setting, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaUIDisplaySettings & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: units
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "units: ";
    rosidl_generator_traits::value_to_yaml(msg.units, out);
    out << "\n";
  }

  // member: language
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "language: ";
    rosidl_generator_traits::value_to_yaml(msg.language, out);
    out << "\n";
  }

  // member: brightness
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "brightness: ";
    rosidl_generator_traits::value_to_yaml(msg.brightness, out);
    out << "\n";
  }

  // member: time_format
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_format: ";
    rosidl_generator_traits::value_to_yaml(msg.time_format, out);
    out << "\n";
  }

  // member: date_format
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "date_format: ";
    rosidl_generator_traits::value_to_yaml(msg.date_format, out);
    out << "\n";
  }

  // member: weight_units
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weight_units: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_units, out);
    out << "\n";
  }

  // member: weight_precision
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weight_precision: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_precision, out);
    out << "\n";
  }

  // member: service_mode_enable_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "service_mode_enable_code: ";
    rosidl_generator_traits::value_to_yaml(msg.service_mode_enable_code, out);
    out << "\n";
  }

  // member: keyboard_layout_setting
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "keyboard_layout_setting: ";
    rosidl_generator_traits::value_to_yaml(msg.keyboard_layout_setting, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaUIDisplaySettings & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::LpsSaUIDisplaySettings & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::LpsSaUIDisplaySettings & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::LpsSaUIDisplaySettings>()
{
  return "cpm_common_interfaces::msg::LpsSaUIDisplaySettings";
}

template<>
inline const char * name<cpm_common_interfaces::msg::LpsSaUIDisplaySettings>()
{
  return "cpm_common_interfaces/msg/LpsSaUIDisplaySettings";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::LpsSaUIDisplaySettings>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::LpsSaUIDisplaySettings>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cpm_common_interfaces::msg::LpsSaUIDisplaySettings>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_SETTINGS__TRAITS_HPP_
