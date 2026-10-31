// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/DemoAppTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/demo_app_tx_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/demo_app_tx_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_DemoAppTxChannel_angle_abc_demo
{
public:
  explicit Init_DemoAppTxChannel_angle_abc_demo(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::DemoAppTxChannel angle_abc_demo(::weigh_app_interfaces::msg::DemoAppTxChannel::_angle_abc_demo_type arg)
  {
    msg_.angle_abc_demo = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_angle_afe_demo
{
public:
  explicit Init_DemoAppTxChannel_angle_afe_demo(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_angle_abc_demo angle_afe_demo(::weigh_app_interfaces::msg::DemoAppTxChannel::_angle_afe_demo_type arg)
  {
    msg_.angle_afe_demo = std::move(arg);
    return Init_DemoAppTxChannel_angle_abc_demo(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_angle_lift_demo
{
public:
  explicit Init_DemoAppTxChannel_angle_lift_demo(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_angle_afe_demo angle_lift_demo(::weigh_app_interfaces::msg::DemoAppTxChannel::_angle_lift_demo_type arg)
  {
    msg_.angle_lift_demo = std::move(arg);
    return Init_DemoAppTxChannel_angle_afe_demo(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_pres_lift_re_demo
{
public:
  explicit Init_DemoAppTxChannel_pres_lift_re_demo(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_angle_lift_demo pres_lift_re_demo(::weigh_app_interfaces::msg::DemoAppTxChannel::_pres_lift_re_demo_type arg)
  {
    msg_.pres_lift_re_demo = std::move(arg);
    return Init_DemoAppTxChannel_angle_lift_demo(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_pres_lift_he_demo
{
public:
  explicit Init_DemoAppTxChannel_pres_lift_he_demo(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_pres_lift_re_demo pres_lift_he_demo(::weigh_app_interfaces::msg::DemoAppTxChannel::_pres_lift_he_demo_type arg)
  {
    msg_.pres_lift_he_demo = std::move(arg);
    return Init_DemoAppTxChannel_pres_lift_re_demo(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_weight1
{
public:
  explicit Init_DemoAppTxChannel_weight1(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_pres_lift_he_demo weight1(::weigh_app_interfaces::msg::DemoAppTxChannel::_weight1_type arg)
  {
    msg_.weight1 = std::move(arg);
    return Init_DemoAppTxChannel_pres_lift_he_demo(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_carry
{
public:
  explicit Init_DemoAppTxChannel_carry(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_weight1 carry(::weigh_app_interfaces::msg::DemoAppTxChannel::_carry_type arg)
  {
    msg_.carry = std::move(arg);
    return Init_DemoAppTxChannel_weight1(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_rack
{
public:
  explicit Init_DemoAppTxChannel_rack(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_carry rack(::weigh_app_interfaces::msg::DemoAppTxChannel::_rack_type arg)
  {
    msg_.rack = std::move(arg);
    return Init_DemoAppTxChannel_carry(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_pdump
{
public:
  explicit Init_DemoAppTxChannel_pdump(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_rack pdump(::weigh_app_interfaces::msg::DemoAppTxChannel::_pdump_type arg)
  {
    msg_.pdump = std::move(arg);
    return Init_DemoAppTxChannel_rack(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_dump
{
public:
  explicit Init_DemoAppTxChannel_dump(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_pdump dump(::weigh_app_interfaces::msg::DemoAppTxChannel::_dump_type arg)
  {
    msg_.dump = std::move(arg);
    return Init_DemoAppTxChannel_pdump(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_llw
{
public:
  explicit Init_DemoAppTxChannel_llw(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_dump llw(::weigh_app_interfaces::msg::DemoAppTxChannel::_llw_type arg)
  {
    msg_.llw = std::move(arg);
    return Init_DemoAppTxChannel_dump(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_wrw
{
public:
  explicit Init_DemoAppTxChannel_wrw(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_llw wrw(::weigh_app_interfaces::msg::DemoAppTxChannel::_wrw_type arg)
  {
    msg_.wrw = std::move(arg);
    return Init_DemoAppTxChannel_llw(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_dig
{
public:
  explicit Init_DemoAppTxChannel_dig(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_wrw dig(::weigh_app_interfaces::msg::DemoAppTxChannel::_dig_type arg)
  {
    msg_.dig = std::move(arg);
    return Init_DemoAppTxChannel_wrw(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_payload_rate
{
public:
  explicit Init_DemoAppTxChannel_payload_rate(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_dig payload_rate(::weigh_app_interfaces::msg::DemoAppTxChannel::_payload_rate_type arg)
  {
    msg_.payload_rate = std::move(arg);
    return Init_DemoAppTxChannel_dig(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_payload
{
public:
  explicit Init_DemoAppTxChannel_payload(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_payload_rate payload(::weigh_app_interfaces::msg::DemoAppTxChannel::_payload_type arg)
  {
    msg_.payload = std::move(arg);
    return Init_DemoAppTxChannel_payload_rate(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_tiltposition_rate
{
public:
  explicit Init_DemoAppTxChannel_tiltposition_rate(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_payload tiltposition_rate(::weigh_app_interfaces::msg::DemoAppTxChannel::_tiltposition_rate_type arg)
  {
    msg_.tiltposition_rate = std::move(arg);
    return Init_DemoAppTxChannel_payload(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_tiltposition
{
public:
  explicit Init_DemoAppTxChannel_tiltposition(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_tiltposition_rate tiltposition(::weigh_app_interfaces::msg::DemoAppTxChannel::_tiltposition_type arg)
  {
    msg_.tiltposition = std::move(arg);
    return Init_DemoAppTxChannel_tiltposition_rate(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_liftposition_rate
{
public:
  explicit Init_DemoAppTxChannel_liftposition_rate(::weigh_app_interfaces::msg::DemoAppTxChannel & msg)
  : msg_(msg)
  {}
  Init_DemoAppTxChannel_tiltposition liftposition_rate(::weigh_app_interfaces::msg::DemoAppTxChannel::_liftposition_rate_type arg)
  {
    msg_.liftposition_rate = std::move(arg);
    return Init_DemoAppTxChannel_tiltposition(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

class Init_DemoAppTxChannel_liftposition
{
public:
  Init_DemoAppTxChannel_liftposition()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DemoAppTxChannel_liftposition_rate liftposition(::weigh_app_interfaces::msg::DemoAppTxChannel::_liftposition_type arg)
  {
    msg_.liftposition = std::move(arg);
    return Init_DemoAppTxChannel_liftposition_rate(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DemoAppTxChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::DemoAppTxChannel>()
{
  return weigh_app_interfaces::msg::builder::Init_DemoAppTxChannel_liftposition();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__BUILDER_HPP_
