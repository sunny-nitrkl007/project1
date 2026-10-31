// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/Payload.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/payload.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/payload__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Payload & msg,
  std::ostream & out)
{
  out << "{";
  // member: payload_ratio_raw
  {
    out << "payload_ratio_raw: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio_raw, out);
    out << ", ";
  }

  // member: payload_ratio
  {
    out << "payload_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio, out);
    out << ", ";
  }

  // member: payload_ratio_status
  {
    out << "payload_ratio_status: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio_status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Payload & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: payload_ratio_raw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_ratio_raw: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio_raw, out);
    out << "\n";
  }

  // member: payload_ratio
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio, out);
    out << "\n";
  }

  // member: payload_ratio_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_ratio_status: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio_status, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Payload & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::Payload & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::Payload & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::Payload>()
{
  return "cpm_common_interfaces::msg::Payload";
}

template<>
inline const char * name<cpm_common_interfaces::msg::Payload>()
{
  return "cpm_common_interfaces/msg/Payload";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::Payload>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::Payload>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cpm_common_interfaces::msg::Payload>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__TRAITS_HPP_
