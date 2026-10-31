// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/STG.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/stg.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__STG__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__STG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/stg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_STG_value
{
public:
  Init_STG_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::job_mgr_interfaces::msg::STG value(::job_mgr_interfaces::msg::STG::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::STG msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::STG>()
{
  return job_mgr_interfaces::msg::builder::Init_STG_value();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__STG__BUILDER_HPP_
