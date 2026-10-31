// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/SwitchInputScs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/switch_input_scs.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/switch_input_scs__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stg_values'
#include "job_mgr_interfaces/msg/detail/stg__traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SwitchInputScs & msg,
  std::ostream & out)
{
  out << "{";
  // member: stg_values
  {
    if (msg.stg_values.size() == 0) {
      out << "stg_values: []";
    } else {
      out << "stg_values: [";
      size_t pending_items = msg.stg_values.size();
      for (auto item : msg.stg_values) {
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
  const SwitchInputScs & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stg_values
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.stg_values.size() == 0) {
      out << "stg_values: []\n";
    } else {
      out << "stg_values:\n";
      for (auto item : msg.stg_values) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SwitchInputScs & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::SwitchInputScs & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::SwitchInputScs & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::SwitchInputScs>()
{
  return "job_mgr_interfaces::msg::SwitchInputScs";
}

template<>
inline const char * name<job_mgr_interfaces::msg::SwitchInputScs>()
{
  return "job_mgr_interfaces/msg/SwitchInputScs";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::SwitchInputScs>
  : std::integral_constant<bool, has_fixed_size<job_mgr_interfaces::msg::STG>::value> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::SwitchInputScs>
  : std::integral_constant<bool, has_bounded_size<job_mgr_interfaces::msg::STG>::value> {};

template<>
struct is_message<job_mgr_interfaces::msg::SwitchInputScs>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__TRAITS_HPP_
