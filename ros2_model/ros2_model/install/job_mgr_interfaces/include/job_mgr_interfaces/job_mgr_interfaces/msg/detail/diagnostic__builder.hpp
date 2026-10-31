// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/Diagnostic.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/diagnostic.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/diagnostic__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_Diagnostic_jname
{
public:
  explicit Init_Diagnostic_jname(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::Diagnostic jname(::job_mgr_interfaces::msg::Diagnostic::_jname_type arg)
  {
    msg_.jname = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_event_trig_val
{
public:
  explicit Init_Diagnostic_event_trig_val(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_jname event_trig_val(::job_mgr_interfaces::msg::Diagnostic::_event_trig_val_type arg)
  {
    msg_.event_trig_val = std::move(arg);
    return Init_Diagnostic_jname(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_worst_case_val
{
public:
  explicit Init_Diagnostic_worst_case_val(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_event_trig_val worst_case_val(::job_mgr_interfaces::msg::Diagnostic::_worst_case_val_type arg)
  {
    msg_.worst_case_val = std::move(arg);
    return Init_Diagnostic_event_trig_val(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_pid
{
public:
  explicit Init_Diagnostic_pid(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_worst_case_val pid(::job_mgr_interfaces::msg::Diagnostic::_pid_type arg)
  {
    msg_.pid = std::move(arg);
    return Init_Diagnostic_worst_case_val(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_last_occ_duration
{
public:
  explicit Init_Diagnostic_last_occ_duration(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_pid last_occ_duration(::job_mgr_interfaces::msg::Diagnostic::_last_occ_duration_type arg)
  {
    msg_.last_occ_duration = std::move(arg);
    return Init_Diagnostic_pid(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_last_occurrence_set
{
public:
  explicit Init_Diagnostic_last_occurrence_set(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_last_occ_duration last_occurrence_set(::job_mgr_interfaces::msg::Diagnostic::_last_occurrence_set_type arg)
  {
    msg_.last_occurrence_set = std::move(arg);
    return Init_Diagnostic_last_occ_duration(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_status
{
public:
  explicit Init_Diagnostic_status(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_last_occurrence_set status(::job_mgr_interfaces::msg::Diagnostic::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_Diagnostic_last_occurrence_set(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_category
{
public:
  explicit Init_Diagnostic_category(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_status category(::job_mgr_interfaces::msg::Diagnostic::_category_type arg)
  {
    msg_.category = std::move(arg);
    return Init_Diagnostic_status(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_occurrence_count
{
public:
  explicit Init_Diagnostic_occurrence_count(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_category occurrence_count(::job_mgr_interfaces::msg::Diagnostic::_occurrence_count_type arg)
  {
    msg_.occurrence_count = std::move(arg);
    return Init_Diagnostic_category(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_service_hour_meter_sec
{
public:
  explicit Init_Diagnostic_service_hour_meter_sec(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_occurrence_count service_hour_meter_sec(::job_mgr_interfaces::msg::Diagnostic::_service_hour_meter_sec_type arg)
  {
    msg_.service_hour_meter_sec = std::move(arg);
    return Init_Diagnostic_occurrence_count(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_gps_time_sec_us
{
public:
  explicit Init_Diagnostic_gps_time_sec_us(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_service_hour_meter_sec gps_time_sec_us(::job_mgr_interfaces::msg::Diagnostic::_gps_time_sec_us_type arg)
  {
    msg_.gps_time_sec_us = std::move(arg);
    return Init_Diagnostic_service_hour_meter_sec(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_subsystem
{
public:
  explicit Init_Diagnostic_subsystem(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_gps_time_sec_us subsystem(::job_mgr_interfaces::msg::Diagnostic::_subsystem_type arg)
  {
    msg_.subsystem = std::move(arg);
    return Init_Diagnostic_gps_time_sec_us(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_description
{
public:
  explicit Init_Diagnostic_description(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_subsystem description(::job_mgr_interfaces::msg::Diagnostic::_description_type arg)
  {
    msg_.description = std::move(arg);
    return Init_Diagnostic_subsystem(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_annunc_value
{
public:
  explicit Init_Diagnostic_annunc_value(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_description annunc_value(::job_mgr_interfaces::msg::Diagnostic::_annunc_value_type arg)
  {
    msg_.annunc_value = std::move(arg);
    return Init_Diagnostic_description(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_wci
{
public:
  explicit Init_Diagnostic_wci(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_annunc_value wci(::job_mgr_interfaces::msg::Diagnostic::_wci_type arg)
  {
    msg_.wci = std::move(arg);
    return Init_Diagnostic_annunc_value(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_fmi
{
public:
  explicit Init_Diagnostic_fmi(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_wci fmi(::job_mgr_interfaces::msg::Diagnostic::_fmi_type arg)
  {
    msg_.fmi = std::move(arg);
    return Init_Diagnostic_wci(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_cid
{
public:
  explicit Init_Diagnostic_cid(::job_mgr_interfaces::msg::Diagnostic & msg)
  : msg_(msg)
  {}
  Init_Diagnostic_fmi cid(::job_mgr_interfaces::msg::Diagnostic::_cid_type arg)
  {
    msg_.cid = std::move(arg);
    return Init_Diagnostic_fmi(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

class Init_Diagnostic_id
{
public:
  Init_Diagnostic_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Diagnostic_cid id(::job_mgr_interfaces::msg::Diagnostic::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Diagnostic_cid(msg_);
  }

private:
  ::job_mgr_interfaces::msg::Diagnostic msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::Diagnostic>()
{
  return job_mgr_interfaces::msg::builder::Init_Diagnostic_id();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__BUILDER_HPP_
