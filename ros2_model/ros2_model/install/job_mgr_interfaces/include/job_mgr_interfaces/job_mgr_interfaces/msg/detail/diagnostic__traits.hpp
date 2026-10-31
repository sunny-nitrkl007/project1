// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/Diagnostic.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/diagnostic.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/diagnostic__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'jname'
#include "job_mgr_interfaces/msg/detail/j1939_name__traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Diagnostic & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: cid
  {
    out << "cid: ";
    rosidl_generator_traits::value_to_yaml(msg.cid, out);
    out << ", ";
  }

  // member: fmi
  {
    out << "fmi: ";
    rosidl_generator_traits::value_to_yaml(msg.fmi, out);
    out << ", ";
  }

  // member: wci
  {
    out << "wci: ";
    rosidl_generator_traits::value_to_yaml(msg.wci, out);
    out << ", ";
  }

  // member: annunc_value
  {
    out << "annunc_value: ";
    rosidl_generator_traits::value_to_yaml(msg.annunc_value, out);
    out << ", ";
  }

  // member: description
  {
    out << "description: ";
    rosidl_generator_traits::value_to_yaml(msg.description, out);
    out << ", ";
  }

  // member: subsystem
  {
    out << "subsystem: ";
    rosidl_generator_traits::value_to_yaml(msg.subsystem, out);
    out << ", ";
  }

  // member: gps_time_sec_us
  {
    out << "gps_time_sec_us: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_time_sec_us, out);
    out << ", ";
  }

  // member: service_hour_meter_sec
  {
    out << "service_hour_meter_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.service_hour_meter_sec, out);
    out << ", ";
  }

  // member: occurrence_count
  {
    out << "occurrence_count: ";
    rosidl_generator_traits::value_to_yaml(msg.occurrence_count, out);
    out << ", ";
  }

  // member: category
  {
    out << "category: ";
    rosidl_generator_traits::value_to_yaml(msg.category, out);
    out << ", ";
  }

  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: last_occurrence_set
  {
    out << "last_occurrence_set: ";
    rosidl_generator_traits::value_to_yaml(msg.last_occurrence_set, out);
    out << ", ";
  }

  // member: last_occ_duration
  {
    out << "last_occ_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.last_occ_duration, out);
    out << ", ";
  }

  // member: pid
  {
    out << "pid: ";
    rosidl_generator_traits::value_to_yaml(msg.pid, out);
    out << ", ";
  }

  // member: worst_case_val
  {
    out << "worst_case_val: ";
    rosidl_generator_traits::value_to_yaml(msg.worst_case_val, out);
    out << ", ";
  }

  // member: event_trig_val
  {
    out << "event_trig_val: ";
    rosidl_generator_traits::value_to_yaml(msg.event_trig_val, out);
    out << ", ";
  }

  // member: jname
  {
    out << "jname: ";
    to_flow_style_yaml(msg.jname, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Diagnostic & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: cid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cid: ";
    rosidl_generator_traits::value_to_yaml(msg.cid, out);
    out << "\n";
  }

  // member: fmi
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fmi: ";
    rosidl_generator_traits::value_to_yaml(msg.fmi, out);
    out << "\n";
  }

  // member: wci
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wci: ";
    rosidl_generator_traits::value_to_yaml(msg.wci, out);
    out << "\n";
  }

  // member: annunc_value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "annunc_value: ";
    rosidl_generator_traits::value_to_yaml(msg.annunc_value, out);
    out << "\n";
  }

  // member: description
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "description: ";
    rosidl_generator_traits::value_to_yaml(msg.description, out);
    out << "\n";
  }

  // member: subsystem
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "subsystem: ";
    rosidl_generator_traits::value_to_yaml(msg.subsystem, out);
    out << "\n";
  }

  // member: gps_time_sec_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gps_time_sec_us: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_time_sec_us, out);
    out << "\n";
  }

  // member: service_hour_meter_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "service_hour_meter_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.service_hour_meter_sec, out);
    out << "\n";
  }

  // member: occurrence_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "occurrence_count: ";
    rosidl_generator_traits::value_to_yaml(msg.occurrence_count, out);
    out << "\n";
  }

  // member: category
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "category: ";
    rosidl_generator_traits::value_to_yaml(msg.category, out);
    out << "\n";
  }

  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: last_occurrence_set
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_occurrence_set: ";
    rosidl_generator_traits::value_to_yaml(msg.last_occurrence_set, out);
    out << "\n";
  }

  // member: last_occ_duration
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_occ_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.last_occ_duration, out);
    out << "\n";
  }

  // member: pid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pid: ";
    rosidl_generator_traits::value_to_yaml(msg.pid, out);
    out << "\n";
  }

  // member: worst_case_val
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "worst_case_val: ";
    rosidl_generator_traits::value_to_yaml(msg.worst_case_val, out);
    out << "\n";
  }

  // member: event_trig_val
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "event_trig_val: ";
    rosidl_generator_traits::value_to_yaml(msg.event_trig_val, out);
    out << "\n";
  }

  // member: jname
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "jname:\n";
    to_block_style_yaml(msg.jname, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Diagnostic & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::Diagnostic & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::Diagnostic & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::Diagnostic>()
{
  return "job_mgr_interfaces::msg::Diagnostic";
}

template<>
inline const char * name<job_mgr_interfaces::msg::Diagnostic>()
{
  return "job_mgr_interfaces/msg/Diagnostic";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::Diagnostic>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::Diagnostic>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<job_mgr_interfaces::msg::Diagnostic>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__TRAITS_HPP_
