// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/LpsSaJobMgrDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_job_mgr_debug_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/lps_sa_job_mgr_debug_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaJobMgrDebugChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: current_state
  {
    out << "current_state: ";
    rosidl_generator_traits::value_to_yaml(msg.current_state, out);
    out << ", ";
  }

  // member: tipoff_assist_activation_count
  {
    out << "tipoff_assist_activation_count: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_assist_activation_count, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaJobMgrDebugChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: current_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_state: ";
    rosidl_generator_traits::value_to_yaml(msg.current_state, out);
    out << "\n";
  }

  // member: tipoff_assist_activation_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tipoff_assist_activation_count: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_assist_activation_count, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaJobMgrDebugChannel & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>()
{
  return "job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel";
}

template<>
inline const char * name<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>()
{
  return "job_mgr_interfaces/msg/LpsSaJobMgrDebugChannel";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__TRAITS_HPP_
