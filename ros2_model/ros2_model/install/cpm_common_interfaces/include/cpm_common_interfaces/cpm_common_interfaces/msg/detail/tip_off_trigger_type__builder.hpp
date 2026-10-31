// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/TipOffTriggerType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/tip_off_trigger_type.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_TRIGGER_TYPE__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_TRIGGER_TYPE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/tip_off_trigger_type__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_TipOffTriggerType_value
{
public:
  Init_TipOffTriggerType_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cpm_common_interfaces::msg::TipOffTriggerType value(::cpm_common_interfaces::msg::TipOffTriggerType::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TipOffTriggerType msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::TipOffTriggerType>()
{
  return cpm_common_interfaces::msg::builder::Init_TipOffTriggerType_value();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_TRIGGER_TYPE__BUILDER_HPP_
