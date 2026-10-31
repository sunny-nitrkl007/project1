// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaWeighReqstChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_reqst_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/lps_sa_weigh_reqst_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'command'
#include "cpm_common_interfaces/msg/detail/weigh_reqst_channel_command__traits.hpp"
// Member 'arg_map'
#include "cpm_common_interfaces/msg/detail/float_pair__traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaWeighReqstChannel & msg,
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

  // member: command
  {
    out << "command: ";
    to_flow_style_yaml(msg.command, out);
    out << ", ";
  }

  // member: arg_b
  {
    out << "arg_b: ";
    rosidl_generator_traits::value_to_yaml(msg.arg_b, out);
    out << ", ";
  }

  // member: arg_f1
  {
    out << "arg_f1: ";
    rosidl_generator_traits::value_to_yaml(msg.arg_f1, out);
    out << ", ";
  }

  // member: arg_f2
  {
    out << "arg_f2: ";
    rosidl_generator_traits::value_to_yaml(msg.arg_f2, out);
    out << ", ";
  }

  // member: arg_s
  {
    out << "arg_s: ";
    rosidl_generator_traits::value_to_yaml(msg.arg_s, out);
    out << ", ";
  }

  // member: arg_u
  {
    out << "arg_u: ";
    rosidl_generator_traits::value_to_yaml(msg.arg_u, out);
    out << ", ";
  }

  // member: arg_map
  {
    if (msg.arg_map.size() == 0) {
      out << "arg_map: []";
    } else {
      out << "arg_map: [";
      size_t pending_items = msg.arg_map.size();
      for (auto item : msg.arg_map) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaWeighReqstChannel & msg,
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

  // member: command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command:\n";
    to_block_style_yaml(msg.command, out, indentation + 2);
  }

  // member: arg_b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arg_b: ";
    rosidl_generator_traits::value_to_yaml(msg.arg_b, out);
    out << "\n";
  }

  // member: arg_f1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arg_f1: ";
    rosidl_generator_traits::value_to_yaml(msg.arg_f1, out);
    out << "\n";
  }

  // member: arg_f2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arg_f2: ";
    rosidl_generator_traits::value_to_yaml(msg.arg_f2, out);
    out << "\n";
  }

  // member: arg_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arg_s: ";
    rosidl_generator_traits::value_to_yaml(msg.arg_s, out);
    out << "\n";
  }

  // member: arg_u
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arg_u: ";
    rosidl_generator_traits::value_to_yaml(msg.arg_u, out);
    out << "\n";
  }

  // member: arg_map
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.arg_map.size() == 0) {
      out << "arg_map: []\n";
    } else {
      out << "arg_map:\n";
      for (auto item : msg.arg_map) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaWeighReqstChannel & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::LpsSaWeighReqstChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::LpsSaWeighReqstChannel & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>()
{
  return "cpm_common_interfaces::msg::LpsSaWeighReqstChannel";
}

template<>
inline const char * name<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>()
{
  return "cpm_common_interfaces/msg/LpsSaWeighReqstChannel";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__TRAITS_HPP_
