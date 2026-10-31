// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/LoadRecordPass.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_pass.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/load_record_pass__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'time'
#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LoadRecordPass & msg,
  std::ostream & out)
{
  out << "{";
  // member: weight_tonnes
  {
    out << "weight_tonnes: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_tonnes, out);
    out << ", ";
  }

  // member: calc_method
  {
    out << "calc_method: ";
    rosidl_generator_traits::value_to_yaml(msg.calc_method, out);
    out << ", ";
  }

  // member: time
  {
    out << "time: ";
    to_flow_style_yaml(msg.time, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LoadRecordPass & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: weight_tonnes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weight_tonnes: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_tonnes, out);
    out << "\n";
  }

  // member: calc_method
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calc_method: ";
    rosidl_generator_traits::value_to_yaml(msg.calc_method, out);
    out << "\n";
  }

  // member: time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time:\n";
    to_block_style_yaml(msg.time, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LoadRecordPass & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::LoadRecordPass & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::LoadRecordPass & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::LoadRecordPass>()
{
  return "job_mgr_interfaces::msg::LoadRecordPass";
}

template<>
inline const char * name<job_mgr_interfaces::msg::LoadRecordPass>()
{
  return "job_mgr_interfaces/msg/LoadRecordPass";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::LoadRecordPass>
  : std::integral_constant<bool, has_fixed_size<job_mgr_interfaces::msg::LoadRecordTimeStamp>::value> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::LoadRecordPass>
  : std::integral_constant<bool, has_bounded_size<job_mgr_interfaces::msg::LoadRecordTimeStamp>::value> {};

template<>
struct is_message<job_mgr_interfaces::msg::LoadRecordPass>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__TRAITS_HPP_
