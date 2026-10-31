// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/OutputChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/output_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/output_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_OutputChannel_commands
{
public:
  Init_OutputChannel_commands()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::job_mgr_interfaces::msg::OutputChannel commands(::job_mgr_interfaces::msg::OutputChannel::_commands_type arg)
  {
    msg_.commands = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::OutputChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::OutputChannel>()
{
  return job_mgr_interfaces::msg::builder::Init_OutputChannel_commands();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__BUILDER_HPP_
