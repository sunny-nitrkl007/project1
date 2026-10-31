// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/LoadRecordTimeStamp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_time_stamp.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_LoadRecordTimeStamp_shm_time
{
public:
  explicit Init_LoadRecordTimeStamp_shm_time(::job_mgr_interfaces::msg::LoadRecordTimeStamp & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::LoadRecordTimeStamp shm_time(::job_mgr_interfaces::msg::LoadRecordTimeStamp::_shm_time_type arg)
  {
    msg_.shm_time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordTimeStamp msg_;
};

class Init_LoadRecordTimeStamp_utc_time_ns
{
public:
  Init_LoadRecordTimeStamp_utc_time_ns()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LoadRecordTimeStamp_shm_time utc_time_ns(::job_mgr_interfaces::msg::LoadRecordTimeStamp::_utc_time_ns_type arg)
  {
    msg_.utc_time_ns = std::move(arg);
    return Init_LoadRecordTimeStamp_shm_time(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordTimeStamp msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::LoadRecordTimeStamp>()
{
  return job_mgr_interfaces::msg::builder::Init_LoadRecordTimeStamp_utc_time_ns();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__BUILDER_HPP_
