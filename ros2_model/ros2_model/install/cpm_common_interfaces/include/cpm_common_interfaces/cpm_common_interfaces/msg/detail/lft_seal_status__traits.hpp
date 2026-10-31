// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/LftSealStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lft_seal_status.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/lft_seal_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LftSealStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: sealed
  {
    out << "sealed: ";
    rosidl_generator_traits::value_to_yaml(msg.sealed, out);
    out << ", ";
  }

  // member: seal_time_ns
  {
    out << "seal_time_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.seal_time_ns, out);
    out << ", ";
  }

  // member: seal_id
  {
    out << "seal_id: ";
    rosidl_generator_traits::value_to_yaml(msg.seal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LftSealStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: sealed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sealed: ";
    rosidl_generator_traits::value_to_yaml(msg.sealed, out);
    out << "\n";
  }

  // member: seal_time_ns
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "seal_time_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.seal_time_ns, out);
    out << "\n";
  }

  // member: seal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "seal_id: ";
    rosidl_generator_traits::value_to_yaml(msg.seal_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LftSealStatus & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::LftSealStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::LftSealStatus & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::LftSealStatus>()
{
  return "cpm_common_interfaces::msg::LftSealStatus";
}

template<>
inline const char * name<cpm_common_interfaces::msg::LftSealStatus>()
{
  return "cpm_common_interfaces/msg/LftSealStatus";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::LftSealStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::LftSealStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cpm_common_interfaces::msg::LftSealStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__TRAITS_HPP_
