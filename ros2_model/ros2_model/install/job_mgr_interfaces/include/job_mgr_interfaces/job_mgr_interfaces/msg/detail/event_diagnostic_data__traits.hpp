// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/EventDiagnosticData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/event_diagnostic_data.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/event_diagnostic_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'active_diagnostics'
#include "job_mgr_interfaces/msg/detail/diagnostic__traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const EventDiagnosticData & msg,
  std::ostream & out)
{
  out << "{";
  // member: dnsname
  {
    out << "dnsname: ";
    rosidl_generator_traits::value_to_yaml(msg.dnsname, out);
    out << ", ";
  }

  // member: active_diagnostics
  {
    if (msg.active_diagnostics.size() == 0) {
      out << "active_diagnostics: []";
    } else {
      out << "active_diagnostics: [";
      size_t pending_items = msg.active_diagnostics.size();
      for (auto item : msg.active_diagnostics) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: payload_crc
  {
    out << "payload_crc: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_crc, out);
    out << ", ";
  }

  // member: payload_last_update_time_us
  {
    out << "payload_last_update_time_us: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_last_update_time_us, out);
    out << ", ";
  }

  // member: highest_warning_level
  {
    out << "highest_warning_level: ";
    rosidl_generator_traits::value_to_yaml(msg.highest_warning_level, out);
    out << ", ";
  }

  // member: highest_annunciation_level
  {
    out << "highest_annunciation_level: ";
    rosidl_generator_traits::value_to_yaml(msg.highest_annunciation_level, out);
    out << ", ";
  }

  // member: source
  {
    out << "source: ";
    rosidl_generator_traits::value_to_yaml(msg.source, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EventDiagnosticData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: dnsname
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dnsname: ";
    rosidl_generator_traits::value_to_yaml(msg.dnsname, out);
    out << "\n";
  }

  // member: active_diagnostics
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.active_diagnostics.size() == 0) {
      out << "active_diagnostics: []\n";
    } else {
      out << "active_diagnostics:\n";
      for (auto item : msg.active_diagnostics) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: payload_crc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_crc: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_crc, out);
    out << "\n";
  }

  // member: payload_last_update_time_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_last_update_time_us: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_last_update_time_us, out);
    out << "\n";
  }

  // member: highest_warning_level
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "highest_warning_level: ";
    rosidl_generator_traits::value_to_yaml(msg.highest_warning_level, out);
    out << "\n";
  }

  // member: highest_annunciation_level
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "highest_annunciation_level: ";
    rosidl_generator_traits::value_to_yaml(msg.highest_annunciation_level, out);
    out << "\n";
  }

  // member: source
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "source: ";
    rosidl_generator_traits::value_to_yaml(msg.source, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EventDiagnosticData & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::EventDiagnosticData & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::EventDiagnosticData & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::EventDiagnosticData>()
{
  return "job_mgr_interfaces::msg::EventDiagnosticData";
}

template<>
inline const char * name<job_mgr_interfaces::msg::EventDiagnosticData>()
{
  return "job_mgr_interfaces/msg/EventDiagnosticData";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::EventDiagnosticData>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::EventDiagnosticData>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<job_mgr_interfaces::msg::EventDiagnosticData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__TRAITS_HPP_
