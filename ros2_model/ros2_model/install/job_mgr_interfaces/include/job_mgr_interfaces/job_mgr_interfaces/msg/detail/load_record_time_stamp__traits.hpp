// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/LoadRecordTimeStamp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_time_stamp.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LoadRecordTimeStamp & msg,
  std::ostream & out)
{
  out << "{";
  // member: utc_time_ns
  {
    out << "utc_time_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.utc_time_ns, out);
    out << ", ";
  }

  // member: shm_time
  {
    out << "shm_time: ";
    rosidl_generator_traits::value_to_yaml(msg.shm_time, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LoadRecordTimeStamp & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: utc_time_ns
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "utc_time_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.utc_time_ns, out);
    out << "\n";
  }

  // member: shm_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "shm_time: ";
    rosidl_generator_traits::value_to_yaml(msg.shm_time, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LoadRecordTimeStamp & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::LoadRecordTimeStamp & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::LoadRecordTimeStamp & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::LoadRecordTimeStamp>()
{
  return "job_mgr_interfaces::msg::LoadRecordTimeStamp";
}

template<>
inline const char * name<job_mgr_interfaces::msg::LoadRecordTimeStamp>()
{
  return "job_mgr_interfaces/msg/LoadRecordTimeStamp";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::LoadRecordTimeStamp>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::LoadRecordTimeStamp>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<job_mgr_interfaces::msg::LoadRecordTimeStamp>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__TRAITS_HPP_
