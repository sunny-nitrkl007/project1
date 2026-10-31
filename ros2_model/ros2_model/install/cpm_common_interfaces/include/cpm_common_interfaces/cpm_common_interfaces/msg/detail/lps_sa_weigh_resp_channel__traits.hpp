// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaWeighRespChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_resp_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/lps_sa_weigh_resp_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'command'
#include "cpm_common_interfaces/msg/detail/weigh_reqst_channel_command__traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaWeighRespChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: app_name
  {
    out << "app_name: ";
    rosidl_generator_traits::value_to_yaml(msg.app_name, out);
    out << ", ";
  }

  // member: app_request_id
  {
    out << "app_request_id: ";
    rosidl_generator_traits::value_to_yaml(msg.app_request_id, out);
    out << ", ";
  }

  // member: time_point_ns
  {
    out << "time_point_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.time_point_ns, out);
    out << ", ";
  }

  // member: command
  {
    out << "command: ";
    to_flow_style_yaml(msg.command, out);
    out << ", ";
  }

  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: arg1
  {
    out << "arg1: ";
    rosidl_generator_traits::value_to_yaml(msg.arg1, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaWeighRespChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: app_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "app_name: ";
    rosidl_generator_traits::value_to_yaml(msg.app_name, out);
    out << "\n";
  }

  // member: app_request_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "app_request_id: ";
    rosidl_generator_traits::value_to_yaml(msg.app_request_id, out);
    out << "\n";
  }

  // member: time_point_ns
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_point_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.time_point_ns, out);
    out << "\n";
  }

  // member: command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command:\n";
    to_block_style_yaml(msg.command, out, indentation + 2);
  }

  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: arg1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arg1: ";
    rosidl_generator_traits::value_to_yaml(msg.arg1, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaWeighRespChannel & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::LpsSaWeighRespChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::LpsSaWeighRespChannel & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::LpsSaWeighRespChannel>()
{
  return "cpm_common_interfaces::msg::LpsSaWeighRespChannel";
}

template<>
inline const char * name<cpm_common_interfaces::msg::LpsSaWeighRespChannel>()
{
  return "cpm_common_interfaces/msg/LpsSaWeighRespChannel";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::LpsSaWeighRespChannel>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::LpsSaWeighRespChannel>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cpm_common_interfaces::msg::LpsSaWeighRespChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__TRAITS_HPP_
