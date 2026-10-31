// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/TipOffState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/tip_off_state.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_STATE__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/tip_off_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_TipOffState_value
{
public:
  Init_TipOffState_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cpm_common_interfaces::msg::TipOffState value(::cpm_common_interfaces::msg::TipOffState::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TipOffState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::TipOffState>()
{
  return cpm_common_interfaces::msg::builder::Init_TipOffState_value();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_STATE__BUILDER_HPP_
