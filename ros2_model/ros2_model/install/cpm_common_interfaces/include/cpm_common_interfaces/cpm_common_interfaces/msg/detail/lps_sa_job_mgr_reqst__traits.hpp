// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrReqst.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_reqst.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_reqst__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaJobMgrReqst & msg,
  std::ostream & out)
{
  out << "{";
  // member: command
  {
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
    out << ", ";
  }

  // member: arg1
  {
    out << "arg1: ";
    rosidl_generator_traits::value_to_yaml(msg.arg1, out);
    out << ", ";
  }

  // member: arg2
  {
    out << "arg2: ";
    rosidl_generator_traits::value_to_yaml(msg.arg2, out);
    out << ", ";
  }

  // member: arg3
  {
    out << "arg3: ";
    rosidl_generator_traits::value_to_yaml(msg.arg3, out);
    out << ", ";
  }

  // member: arg4
  {
    out << "arg4: ";
    rosidl_generator_traits::value_to_yaml(msg.arg4, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaJobMgrReqst & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
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

  // member: arg2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arg2: ";
    rosidl_generator_traits::value_to_yaml(msg.arg2, out);
    out << "\n";
  }

  // member: arg3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arg3: ";
    rosidl_generator_traits::value_to_yaml(msg.arg3, out);
    out << "\n";
  }

  // member: arg4
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arg4: ";
    rosidl_generator_traits::value_to_yaml(msg.arg4, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaJobMgrReqst & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::LpsSaJobMgrReqst & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::LpsSaJobMgrReqst & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::LpsSaJobMgrReqst>()
{
  return "cpm_common_interfaces::msg::LpsSaJobMgrReqst";
}

template<>
inline const char * name<cpm_common_interfaces::msg::LpsSaJobMgrReqst>()
{
  return "cpm_common_interfaces/msg/LpsSaJobMgrReqst";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::LpsSaJobMgrReqst>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::LpsSaJobMgrReqst>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cpm_common_interfaces::msg::LpsSaJobMgrReqst>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__TRAITS_HPP_
