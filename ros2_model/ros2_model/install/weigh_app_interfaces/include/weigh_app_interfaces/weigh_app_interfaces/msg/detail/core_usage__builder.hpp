// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/CoreUsage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/core_usage.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/core_usage__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_CoreUsage_cpu_irq_percent
{
public:
  explicit Init_CoreUsage_cpu_irq_percent(::weigh_app_interfaces::msg::CoreUsage & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::CoreUsage cpu_irq_percent(::weigh_app_interfaces::msg::CoreUsage::_cpu_irq_percent_type arg)
  {
    msg_.cpu_irq_percent = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CoreUsage msg_;
};

class Init_CoreUsage_cpu_io_wait_percent
{
public:
  explicit Init_CoreUsage_cpu_io_wait_percent(::weigh_app_interfaces::msg::CoreUsage & msg)
  : msg_(msg)
  {}
  Init_CoreUsage_cpu_irq_percent cpu_io_wait_percent(::weigh_app_interfaces::msg::CoreUsage::_cpu_io_wait_percent_type arg)
  {
    msg_.cpu_io_wait_percent = std::move(arg);
    return Init_CoreUsage_cpu_irq_percent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CoreUsage msg_;
};

class Init_CoreUsage_cpu_usage_percent
{
public:
  Init_CoreUsage_cpu_usage_percent()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CoreUsage_cpu_io_wait_percent cpu_usage_percent(::weigh_app_interfaces::msg::CoreUsage::_cpu_usage_percent_type arg)
  {
    msg_.cpu_usage_percent = std::move(arg);
    return Init_CoreUsage_cpu_io_wait_percent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CoreUsage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::CoreUsage>()
{
  return weigh_app_interfaces::msg::builder::Init_CoreUsage_cpu_usage_percent();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__BUILDER_HPP_
