// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/SwitchInputScs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/switch_input_scs.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/switch_input_scs__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_SwitchInputScs_stg_values
{
public:
  Init_SwitchInputScs_stg_values()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::job_mgr_interfaces::msg::SwitchInputScs stg_values(::job_mgr_interfaces::msg::SwitchInputScs::_stg_values_type arg)
  {
    msg_.stg_values = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::SwitchInputScs msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::SwitchInputScs>()
{
  return job_mgr_interfaces::msg::builder::Init_SwitchInputScs_stg_values();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__BUILDER_HPP_
