// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/ReadyToFlashStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ready_to_flash_status.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/ready_to_flash_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_ReadyToFlashStatus_ready_code
{
public:
  explicit Init_ReadyToFlashStatus_ready_code(::weigh_app_interfaces::msg::ReadyToFlashStatus & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::ReadyToFlashStatus ready_code(::weigh_app_interfaces::msg::ReadyToFlashStatus::_ready_code_type arg)
  {
    msg_.ready_code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::ReadyToFlashStatus msg_;
};

class Init_ReadyToFlashStatus_host_name
{
public:
  explicit Init_ReadyToFlashStatus_host_name(::weigh_app_interfaces::msg::ReadyToFlashStatus & msg)
  : msg_(msg)
  {}
  Init_ReadyToFlashStatus_ready_code host_name(::weigh_app_interfaces::msg::ReadyToFlashStatus::_host_name_type arg)
  {
    msg_.host_name = std::move(arg);
    return Init_ReadyToFlashStatus_ready_code(msg_);
  }

private:
  ::weigh_app_interfaces::msg::ReadyToFlashStatus msg_;
};

class Init_ReadyToFlashStatus_task_name
{
public:
  Init_ReadyToFlashStatus_task_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ReadyToFlashStatus_host_name task_name(::weigh_app_interfaces::msg::ReadyToFlashStatus::_task_name_type arg)
  {
    msg_.task_name = std::move(arg);
    return Init_ReadyToFlashStatus_host_name(msg_);
  }

private:
  ::weigh_app_interfaces::msg::ReadyToFlashStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::ReadyToFlashStatus>()
{
  return weigh_app_interfaces::msg::builder::Init_ReadyToFlashStatus_task_name();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__BUILDER_HPP_
