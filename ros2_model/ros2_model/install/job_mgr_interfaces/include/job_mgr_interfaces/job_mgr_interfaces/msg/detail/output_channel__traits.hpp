// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/OutputChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/output_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/output_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'commands'
#include "job_mgr_interfaces/msg/detail/output_cmd__traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const OutputChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: commands
  {
    if (msg.commands.size() == 0) {
      out << "commands: []";
    } else {
      out << "commands: [";
      size_t pending_items = msg.commands.size();
      for (auto item : msg.commands) {
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
  const OutputChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: commands
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.commands.size() == 0) {
      out << "commands: []\n";
    } else {
      out << "commands:\n";
      for (auto item : msg.commands) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const OutputChannel & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::OutputChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::OutputChannel & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::OutputChannel>()
{
  return "job_mgr_interfaces::msg::OutputChannel";
}

template<>
inline const char * name<job_mgr_interfaces::msg::OutputChannel>()
{
  return "job_mgr_interfaces/msg/OutputChannel";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::OutputChannel>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::OutputChannel>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<job_mgr_interfaces::msg::OutputChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__TRAITS_HPP_
