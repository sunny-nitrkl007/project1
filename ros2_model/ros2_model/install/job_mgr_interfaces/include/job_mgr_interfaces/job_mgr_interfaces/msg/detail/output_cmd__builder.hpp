// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/OutputCmd.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/output_cmd.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/output_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_OutputCmd_total_duration
{
public:
  explicit Init_OutputCmd_total_duration(::job_mgr_interfaces::msg::OutputCmd & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::OutputCmd total_duration(::job_mgr_interfaces::msg::OutputCmd::_total_duration_type arg)
  {
    msg_.total_duration = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::OutputCmd msg_;
};

class Init_OutputCmd_final_state
{
public:
  explicit Init_OutputCmd_final_state(::job_mgr_interfaces::msg::OutputCmd & msg)
  : msg_(msg)
  {}
  Init_OutputCmd_total_duration final_state(::job_mgr_interfaces::msg::OutputCmd::_final_state_type arg)
  {
    msg_.final_state = std::move(arg);
    return Init_OutputCmd_total_duration(msg_);
  }

private:
  ::job_mgr_interfaces::msg::OutputCmd msg_;
};

class Init_OutputCmd_state_change_duration
{
public:
  explicit Init_OutputCmd_state_change_duration(::job_mgr_interfaces::msg::OutputCmd & msg)
  : msg_(msg)
  {}
  Init_OutputCmd_final_state state_change_duration(::job_mgr_interfaces::msg::OutputCmd::_state_change_duration_type arg)
  {
    msg_.state_change_duration = std::move(arg);
    return Init_OutputCmd_final_state(msg_);
  }

private:
  ::job_mgr_interfaces::msg::OutputCmd msg_;
};

class Init_OutputCmd_initial_state
{
public:
  explicit Init_OutputCmd_initial_state(::job_mgr_interfaces::msg::OutputCmd & msg)
  : msg_(msg)
  {}
  Init_OutputCmd_state_change_duration initial_state(::job_mgr_interfaces::msg::OutputCmd::_initial_state_type arg)
  {
    msg_.initial_state = std::move(arg);
    return Init_OutputCmd_state_change_duration(msg_);
  }

private:
  ::job_mgr_interfaces::msg::OutputCmd msg_;
};

class Init_OutputCmd_output_port
{
public:
  Init_OutputCmd_output_port()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OutputCmd_initial_state output_port(::job_mgr_interfaces::msg::OutputCmd::_output_port_type arg)
  {
    msg_.output_port = std::move(arg);
    return Init_OutputCmd_initial_state(msg_);
  }

private:
  ::job_mgr_interfaces::msg::OutputCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::OutputCmd>()
{
  return job_mgr_interfaces::msg::builder::Init_OutputCmd_output_port();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__BUILDER_HPP_
