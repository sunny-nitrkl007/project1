// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/LpsSaJobMgrRespChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_job_mgr_resp_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_RESP_CHANNEL__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_RESP_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/lps_sa_job_mgr_resp_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'command'
#include "cpm_common_interfaces/msg/detail/job_mgr_reqst_channel_command__traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaJobMgrRespChannel & msg,
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
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaJobMgrRespChannel & msg,
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaJobMgrRespChannel & msg, bool use_flow_style = false)
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

}  // namespace job_mgr_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use job_mgr_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const job_mgr_interfaces::msg::LpsSaJobMgrRespChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::LpsSaJobMgrRespChannel & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>()
{
  return "job_mgr_interfaces::msg::LpsSaJobMgrRespChannel";
}

template<>
inline const char * name<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>()
{
  return "job_mgr_interfaces/msg/LpsSaJobMgrRespChannel";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_RESP_CHANNEL__TRAITS_HPP_
