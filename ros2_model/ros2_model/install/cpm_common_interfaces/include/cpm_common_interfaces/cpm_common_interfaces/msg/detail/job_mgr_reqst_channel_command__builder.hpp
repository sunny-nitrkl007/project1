// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/JobMgrReqstChannelCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/job_mgr_reqst_channel_command.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/job_mgr_reqst_channel_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_JobMgrReqstChannelCommand_value
{
public:
  Init_JobMgrReqstChannelCommand_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cpm_common_interfaces::msg::JobMgrReqstChannelCommand value(::cpm_common_interfaces::msg::JobMgrReqstChannelCommand::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::JobMgrReqstChannelCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::JobMgrReqstChannelCommand>()
{
  return cpm_common_interfaces::msg::builder::Init_JobMgrReqstChannelCommand_value();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__BUILDER_HPP_
