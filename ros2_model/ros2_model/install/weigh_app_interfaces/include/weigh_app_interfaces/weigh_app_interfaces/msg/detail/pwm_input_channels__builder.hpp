// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/PwmInputChannels.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/pwm_input_channels.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/pwm_input_channels__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_PwmInputChannels_timeout
{
public:
  explicit Init_PwmInputChannels_timeout(::weigh_app_interfaces::msg::PwmInputChannels & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::PwmInputChannels timeout(::weigh_app_interfaces::msg::PwmInputChannels::_timeout_type arg)
  {
    msg_.timeout = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PwmInputChannels msg_;
};

class Init_PwmInputChannels_switch_status
{
public:
  explicit Init_PwmInputChannels_switch_status(::weigh_app_interfaces::msg::PwmInputChannels & msg)
  : msg_(msg)
  {}
  Init_PwmInputChannels_timeout switch_status(::weigh_app_interfaces::msg::PwmInputChannels::_switch_status_type arg)
  {
    msg_.switch_status = std::move(arg);
    return Init_PwmInputChannels_timeout(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PwmInputChannels msg_;
};

class Init_PwmInputChannels_width
{
public:
  explicit Init_PwmInputChannels_width(::weigh_app_interfaces::msg::PwmInputChannels & msg)
  : msg_(msg)
  {}
  Init_PwmInputChannels_switch_status width(::weigh_app_interfaces::msg::PwmInputChannels::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_PwmInputChannels_switch_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PwmInputChannels msg_;
};

class Init_PwmInputChannels_period
{
public:
  Init_PwmInputChannels_period()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PwmInputChannels_width period(::weigh_app_interfaces::msg::PwmInputChannels::_period_type arg)
  {
    msg_.period = std::move(arg);
    return Init_PwmInputChannels_width(msg_);
  }

private:
  ::weigh_app_interfaces::msg::PwmInputChannels msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::PwmInputChannels>()
{
  return weigh_app_interfaces::msg::builder::Init_PwmInputChannels_period();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__BUILDER_HPP_
