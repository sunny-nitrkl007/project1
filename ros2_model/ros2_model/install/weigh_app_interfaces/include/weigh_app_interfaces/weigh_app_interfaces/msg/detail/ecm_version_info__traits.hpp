// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/EcmVersionInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ecm_version_info.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/ecm_version_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const EcmVersionInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: serial_num
  {
    out << "serial_num: ";
    rosidl_generator_traits::value_to_yaml(msg.serial_num, out);
    out << ", ";
  }

  // member: part_num
  {
    out << "part_num: ";
    rosidl_generator_traits::value_to_yaml(msg.part_num, out);
    out << ", ";
  }

  // member: dom
  {
    out << "dom: ";
    rosidl_generator_traits::value_to_yaml(msg.dom, out);
    out << ", ";
  }

  // member: mac0
  {
    out << "mac0: ";
    rosidl_generator_traits::value_to_yaml(msg.mac0, out);
    out << ", ";
  }

  // member: mac1
  {
    out << "mac1: ";
    rosidl_generator_traits::value_to_yaml(msg.mac1, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EcmVersionInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: serial_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "serial_num: ";
    rosidl_generator_traits::value_to_yaml(msg.serial_num, out);
    out << "\n";
  }

  // member: part_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "part_num: ";
    rosidl_generator_traits::value_to_yaml(msg.part_num, out);
    out << "\n";
  }

  // member: dom
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dom: ";
    rosidl_generator_traits::value_to_yaml(msg.dom, out);
    out << "\n";
  }

  // member: mac0
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mac0: ";
    rosidl_generator_traits::value_to_yaml(msg.mac0, out);
    out << "\n";
  }

  // member: mac1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mac1: ";
    rosidl_generator_traits::value_to_yaml(msg.mac1, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EcmVersionInfo & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::EcmVersionInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::EcmVersionInfo & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::EcmVersionInfo>()
{
  return "weigh_app_interfaces::msg::EcmVersionInfo";
}

template<>
inline const char * name<weigh_app_interfaces::msg::EcmVersionInfo>()
{
  return "weigh_app_interfaces/msg/EcmVersionInfo";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::EcmVersionInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::EcmVersionInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<weigh_app_interfaces::msg::EcmVersionInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__TRAITS_HPP_
