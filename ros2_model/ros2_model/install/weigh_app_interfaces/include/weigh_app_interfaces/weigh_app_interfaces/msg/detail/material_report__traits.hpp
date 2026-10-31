// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/MaterialReport.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/material_report.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__MATERIAL_REPORT__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__MATERIAL_REPORT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/material_report__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const MaterialReport & msg,
  std::ostream & out)
{
  out << "{";
  // member: reset_time_enabled
  {
    out << "reset_time_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_time_enabled, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MaterialReport & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: reset_time_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reset_time_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_time_enabled, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MaterialReport & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::MaterialReport & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::MaterialReport & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::MaterialReport>()
{
  return "weigh_app_interfaces::msg::MaterialReport";
}

template<>
inline const char * name<weigh_app_interfaces::msg::MaterialReport>()
{
  return "weigh_app_interfaces/msg/MaterialReport";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::MaterialReport>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::MaterialReport>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::MaterialReport>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__MATERIAL_REPORT__TRAITS_HPP_
