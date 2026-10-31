// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/EventDiagnosticData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/event_diagnostic_data.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/event_diagnostic_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_EventDiagnosticData_source
{
public:
  explicit Init_EventDiagnosticData_source(::job_mgr_interfaces::msg::EventDiagnosticData & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::EventDiagnosticData source(::job_mgr_interfaces::msg::EventDiagnosticData::_source_type arg)
  {
    msg_.source = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::EventDiagnosticData msg_;
};

class Init_EventDiagnosticData_highest_annunciation_level
{
public:
  explicit Init_EventDiagnosticData_highest_annunciation_level(::job_mgr_interfaces::msg::EventDiagnosticData & msg)
  : msg_(msg)
  {}
  Init_EventDiagnosticData_source highest_annunciation_level(::job_mgr_interfaces::msg::EventDiagnosticData::_highest_annunciation_level_type arg)
  {
    msg_.highest_annunciation_level = std::move(arg);
    return Init_EventDiagnosticData_source(msg_);
  }

private:
  ::job_mgr_interfaces::msg::EventDiagnosticData msg_;
};

class Init_EventDiagnosticData_highest_warning_level
{
public:
  explicit Init_EventDiagnosticData_highest_warning_level(::job_mgr_interfaces::msg::EventDiagnosticData & msg)
  : msg_(msg)
  {}
  Init_EventDiagnosticData_highest_annunciation_level highest_warning_level(::job_mgr_interfaces::msg::EventDiagnosticData::_highest_warning_level_type arg)
  {
    msg_.highest_warning_level = std::move(arg);
    return Init_EventDiagnosticData_highest_annunciation_level(msg_);
  }

private:
  ::job_mgr_interfaces::msg::EventDiagnosticData msg_;
};

class Init_EventDiagnosticData_payload_last_update_time_us
{
public:
  explicit Init_EventDiagnosticData_payload_last_update_time_us(::job_mgr_interfaces::msg::EventDiagnosticData & msg)
  : msg_(msg)
  {}
  Init_EventDiagnosticData_highest_warning_level payload_last_update_time_us(::job_mgr_interfaces::msg::EventDiagnosticData::_payload_last_update_time_us_type arg)
  {
    msg_.payload_last_update_time_us = std::move(arg);
    return Init_EventDiagnosticData_highest_warning_level(msg_);
  }

private:
  ::job_mgr_interfaces::msg::EventDiagnosticData msg_;
};

class Init_EventDiagnosticData_payload_crc
{
public:
  explicit Init_EventDiagnosticData_payload_crc(::job_mgr_interfaces::msg::EventDiagnosticData & msg)
  : msg_(msg)
  {}
  Init_EventDiagnosticData_payload_last_update_time_us payload_crc(::job_mgr_interfaces::msg::EventDiagnosticData::_payload_crc_type arg)
  {
    msg_.payload_crc = std::move(arg);
    return Init_EventDiagnosticData_payload_last_update_time_us(msg_);
  }

private:
  ::job_mgr_interfaces::msg::EventDiagnosticData msg_;
};

class Init_EventDiagnosticData_active_diagnostics
{
public:
  explicit Init_EventDiagnosticData_active_diagnostics(::job_mgr_interfaces::msg::EventDiagnosticData & msg)
  : msg_(msg)
  {}
  Init_EventDiagnosticData_payload_crc active_diagnostics(::job_mgr_interfaces::msg::EventDiagnosticData::_active_diagnostics_type arg)
  {
    msg_.active_diagnostics = std::move(arg);
    return Init_EventDiagnosticData_payload_crc(msg_);
  }

private:
  ::job_mgr_interfaces::msg::EventDiagnosticData msg_;
};

class Init_EventDiagnosticData_dnsname
{
public:
  Init_EventDiagnosticData_dnsname()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EventDiagnosticData_active_diagnostics dnsname(::job_mgr_interfaces::msg::EventDiagnosticData::_dnsname_type arg)
  {
    msg_.dnsname = std::move(arg);
    return Init_EventDiagnosticData_active_diagnostics(msg_);
  }

private:
  ::job_mgr_interfaces::msg::EventDiagnosticData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::EventDiagnosticData>()
{
  return job_mgr_interfaces::msg::builder::Init_EventDiagnosticData_dnsname();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__BUILDER_HPP_
