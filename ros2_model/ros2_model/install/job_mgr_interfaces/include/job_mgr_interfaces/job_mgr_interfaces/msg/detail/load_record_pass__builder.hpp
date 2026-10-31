// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/LoadRecordPass.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_pass.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/load_record_pass__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_LoadRecordPass_time
{
public:
  explicit Init_LoadRecordPass_time(::job_mgr_interfaces::msg::LoadRecordPass & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::LoadRecordPass time(::job_mgr_interfaces::msg::LoadRecordPass::_time_type arg)
  {
    msg_.time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordPass msg_;
};

class Init_LoadRecordPass_calc_method
{
public:
  explicit Init_LoadRecordPass_calc_method(::job_mgr_interfaces::msg::LoadRecordPass & msg)
  : msg_(msg)
  {}
  Init_LoadRecordPass_time calc_method(::job_mgr_interfaces::msg::LoadRecordPass::_calc_method_type arg)
  {
    msg_.calc_method = std::move(arg);
    return Init_LoadRecordPass_time(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordPass msg_;
};

class Init_LoadRecordPass_weight_tonnes
{
public:
  Init_LoadRecordPass_weight_tonnes()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LoadRecordPass_calc_method weight_tonnes(::job_mgr_interfaces::msg::LoadRecordPass::_weight_tonnes_type arg)
  {
    msg_.weight_tonnes = std::move(arg);
    return Init_LoadRecordPass_calc_method(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LoadRecordPass msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::LoadRecordPass>()
{
  return job_mgr_interfaces::msg::builder::Init_LoadRecordPass_weight_tonnes();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__BUILDER_HPP_
