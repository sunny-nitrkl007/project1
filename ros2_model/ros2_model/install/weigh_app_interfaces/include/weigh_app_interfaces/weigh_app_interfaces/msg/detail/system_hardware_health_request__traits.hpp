// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/SystemHardwareHealthRequest.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/system_hardware_health_request.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_REQUEST__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_REQUEST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/system_hardware_health_request__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SystemHardwareHealthRequest & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SystemHardwareHealthRequest & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SystemHardwareHealthRequest & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::SystemHardwareHealthRequest & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::SystemHardwareHealthRequest & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::SystemHardwareHealthRequest>()
{
  return "weigh_app_interfaces::msg::SystemHardwareHealthRequest";
}

template<>
inline const char * name<weigh_app_interfaces::msg::SystemHardwareHealthRequest>()
{
  return "weigh_app_interfaces/msg/SystemHardwareHealthRequest";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::SystemHardwareHealthRequest>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::SystemHardwareHealthRequest>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::SystemHardwareHealthRequest>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_REQUEST__TRAITS_HPP_
