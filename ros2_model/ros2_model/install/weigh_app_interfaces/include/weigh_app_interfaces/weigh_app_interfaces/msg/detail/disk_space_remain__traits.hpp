// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/DiskSpaceRemain.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/disk_space_remain.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DISK_SPACE_REMAIN__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DISK_SPACE_REMAIN__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/disk_space_remain__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const DiskSpaceRemain & msg,
  std::ostream & out)
{
  out << "{";
  // member: filesystem
  {
    out << "filesystem: ";
    rosidl_generator_traits::value_to_yaml(msg.filesystem, out);
    out << ", ";
  }

  // member: avail_kb
  {
    out << "avail_kb: ";
    rosidl_generator_traits::value_to_yaml(msg.avail_kb, out);
    out << ", ";
  }

  // member: percent_use
  {
    out << "percent_use: ";
    rosidl_generator_traits::value_to_yaml(msg.percent_use, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DiskSpaceRemain & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: filesystem
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "filesystem: ";
    rosidl_generator_traits::value_to_yaml(msg.filesystem, out);
    out << "\n";
  }

  // member: avail_kb
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "avail_kb: ";
    rosidl_generator_traits::value_to_yaml(msg.avail_kb, out);
    out << "\n";
  }

  // member: percent_use
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "percent_use: ";
    rosidl_generator_traits::value_to_yaml(msg.percent_use, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DiskSpaceRemain & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::DiskSpaceRemain & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::DiskSpaceRemain & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::DiskSpaceRemain>()
{
  return "weigh_app_interfaces::msg::DiskSpaceRemain";
}

template<>
inline const char * name<weigh_app_interfaces::msg::DiskSpaceRemain>()
{
  return "weigh_app_interfaces/msg/DiskSpaceRemain";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::DiskSpaceRemain>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::DiskSpaceRemain>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<weigh_app_interfaces::msg::DiskSpaceRemain>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DISK_SPACE_REMAIN__TRAITS_HPP_
