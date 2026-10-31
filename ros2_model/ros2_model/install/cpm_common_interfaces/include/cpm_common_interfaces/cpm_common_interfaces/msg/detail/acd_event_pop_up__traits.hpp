// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/AcdEventPopUp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/acd_event_pop_up.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/acd_event_pop_up__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const AcdEventPopUp & msg,
  std::ostream & out)
{
  out << "{";
  // member: bits
  {
    out << "bits: ";
    rosidl_generator_traits::value_to_yaml(msg.bits, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AcdEventPopUp & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: bits
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bits: ";
    rosidl_generator_traits::value_to_yaml(msg.bits, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AcdEventPopUp & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::AcdEventPopUp & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::AcdEventPopUp & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::AcdEventPopUp>()
{
  return "cpm_common_interfaces::msg::AcdEventPopUp";
}

template<>
inline const char * name<cpm_common_interfaces::msg::AcdEventPopUp>()
{
  return "cpm_common_interfaces/msg/AcdEventPopUp";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::AcdEventPopUp>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::AcdEventPopUp>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cpm_common_interfaces::msg::AcdEventPopUp>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__TRAITS_HPP_
