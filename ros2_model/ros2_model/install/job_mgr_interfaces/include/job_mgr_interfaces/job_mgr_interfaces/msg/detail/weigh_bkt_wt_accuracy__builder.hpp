// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/WeighBktWtAccuracy.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/weigh_bkt_wt_accuracy.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/weigh_bkt_wt_accuracy__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_WeighBktWtAccuracy_value
{
public:
  Init_WeighBktWtAccuracy_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::job_mgr_interfaces::msg::WeighBktWtAccuracy value(::job_mgr_interfaces::msg::WeighBktWtAccuracy::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::WeighBktWtAccuracy msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::WeighBktWtAccuracy>()
{
  return job_mgr_interfaces::msg::builder::Init_WeighBktWtAccuracy_value();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__BUILDER_HPP_
