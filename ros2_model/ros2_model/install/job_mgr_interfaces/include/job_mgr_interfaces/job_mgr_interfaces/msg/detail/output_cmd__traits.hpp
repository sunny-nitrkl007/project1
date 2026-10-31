// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/OutputCmd.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/output_cmd.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/output_cmd__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const OutputCmd & msg,
  std::ostream & out)
{
  out << "{";
  // member: output_port
  {
    out << "output_port: ";
    rosidl_generator_traits::value_to_yaml(msg.output_port, out);
    out << ", ";
  }

  // member: initial_state
  {
    out << "initial_state: ";
    rosidl_generator_traits::value_to_yaml(msg.initial_state, out);
    out << ", ";
  }

  // member: state_change_duration
  {
    out << "state_change_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.state_change_duration, out);
    out << ", ";
  }

  // member: final_state
  {
    out << "final_state: ";
    rosidl_generator_traits::value_to_yaml(msg.final_state, out);
    out << ", ";
  }

  // member: total_duration
  {
    out << "total_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.total_duration, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const OutputCmd & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: output_port
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "output_port: ";
    rosidl_generator_traits::value_to_yaml(msg.output_port, out);
    out << "\n";
  }

  // member: initial_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "initial_state: ";
    rosidl_generator_traits::value_to_yaml(msg.initial_state, out);
    out << "\n";
  }

  // member: state_change_duration
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state_change_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.state_change_duration, out);
    out << "\n";
  }

  // member: final_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_state: ";
    rosidl_generator_traits::value_to_yaml(msg.final_state, out);
    out << "\n";
  }

  // member: total_duration
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.total_duration, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const OutputCmd & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::OutputCmd & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::OutputCmd & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::OutputCmd>()
{
  return "job_mgr_interfaces::msg::OutputCmd";
}

template<>
inline const char * name<job_mgr_interfaces::msg::OutputCmd>()
{
  return "job_mgr_interfaces/msg/OutputCmd";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::OutputCmd>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::OutputCmd>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<job_mgr_interfaces::msg::OutputCmd>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__TRAITS_HPP_
