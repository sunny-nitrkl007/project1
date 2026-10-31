// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/ReadyToFlashStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ready_to_flash_status.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/ready_to_flash_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ReadyToFlashStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: task_name
  {
    out << "task_name: ";
    rosidl_generator_traits::value_to_yaml(msg.task_name, out);
    out << ", ";
  }

  // member: host_name
  {
    out << "host_name: ";
    rosidl_generator_traits::value_to_yaml(msg.host_name, out);
    out << ", ";
  }

  // member: ready_code
  {
    out << "ready_code: ";
    rosidl_generator_traits::value_to_yaml(msg.ready_code, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ReadyToFlashStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: task_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_name: ";
    rosidl_generator_traits::value_to_yaml(msg.task_name, out);
    out << "\n";
  }

  // member: host_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "host_name: ";
    rosidl_generator_traits::value_to_yaml(msg.host_name, out);
    out << "\n";
  }

  // member: ready_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ready_code: ";
    rosidl_generator_traits::value_to_yaml(msg.ready_code, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ReadyToFlashStatus & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::ReadyToFlashStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::ReadyToFlashStatus & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::ReadyToFlashStatus>()
{
  return "weigh_app_interfaces::msg::ReadyToFlashStatus";
}

template<>
inline const char * name<weigh_app_interfaces::msg::ReadyToFlashStatus>()
{
  return "weigh_app_interfaces/msg/ReadyToFlashStatus";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::ReadyToFlashStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::ReadyToFlashStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<weigh_app_interfaces::msg::ReadyToFlashStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__TRAITS_HPP_
