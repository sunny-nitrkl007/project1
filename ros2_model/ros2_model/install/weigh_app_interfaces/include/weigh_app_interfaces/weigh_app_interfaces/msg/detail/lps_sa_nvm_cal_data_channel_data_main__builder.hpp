// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannelDataMain.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel_data_main.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel_data_main__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaNvmCalDataChannelDataMain_raise_fast_delta_p_full
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_raise_fast_delta_p_full(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain raise_fast_delta_p_full(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_raise_fast_delta_p_full_type arg)
  {
    msg_.raise_fast_delta_p_full = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_raise_speed_full_fast
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_raise_speed_full_fast(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_raise_fast_delta_p_full raise_speed_full_fast(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_raise_speed_full_fast_type arg)
  {
    msg_.raise_speed_full_fast = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_raise_fast_delta_p_full(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_raise_speed_full_slow
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_raise_speed_full_slow(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_raise_speed_full_fast raise_speed_full_slow(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_raise_speed_full_slow_type arg)
  {
    msg_.raise_speed_full_slow = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_raise_speed_full_fast(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_raise_fast_delta_p_empty
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_raise_fast_delta_p_empty(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_raise_speed_full_slow raise_fast_delta_p_empty(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_raise_fast_delta_p_empty_type arg)
  {
    msg_.raise_fast_delta_p_empty = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_raise_speed_full_slow(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_raise_speed_empty_fast
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_raise_speed_empty_fast(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_raise_fast_delta_p_empty raise_speed_empty_fast(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_raise_speed_empty_fast_type arg)
  {
    msg_.raise_speed_empty_fast = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_raise_fast_delta_p_empty(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_raise_speed_empty_slow
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_raise_speed_empty_slow(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_raise_speed_empty_fast raise_speed_empty_slow(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_raise_speed_empty_slow_type arg)
  {
    msg_.raise_speed_empty_slow = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_raise_speed_empty_fast(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_lower_slow_full_pressures
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_lower_slow_full_pressures(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_raise_speed_empty_slow lower_slow_full_pressures(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_lower_slow_full_pressures_type arg)
  {
    msg_.lower_slow_full_pressures = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_raise_speed_empty_slow(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_lower_slow_full_lift_heights
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_lower_slow_full_lift_heights(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_lower_slow_full_pressures lower_slow_full_lift_heights(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_lower_slow_full_lift_heights_type arg)
  {
    msg_.lower_slow_full_lift_heights = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_lower_slow_full_pressures(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_raise_slow_full_pressures
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_raise_slow_full_pressures(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_lower_slow_full_lift_heights raise_slow_full_pressures(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_raise_slow_full_pressures_type arg)
  {
    msg_.raise_slow_full_pressures = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_lower_slow_full_lift_heights(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_raise_slow_full_lift_heights
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_raise_slow_full_lift_heights(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_raise_slow_full_pressures raise_slow_full_lift_heights(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_raise_slow_full_lift_heights_type arg)
  {
    msg_.raise_slow_full_lift_heights = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_raise_slow_full_pressures(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_lower_slow_empty_pressures
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_lower_slow_empty_pressures(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_raise_slow_full_lift_heights lower_slow_empty_pressures(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_lower_slow_empty_pressures_type arg)
  {
    msg_.lower_slow_empty_pressures = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_raise_slow_full_lift_heights(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_lower_slow_empty_lift_heights
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_lower_slow_empty_lift_heights(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_lower_slow_empty_pressures lower_slow_empty_lift_heights(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_lower_slow_empty_lift_heights_type arg)
  {
    msg_.lower_slow_empty_lift_heights = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_lower_slow_empty_pressures(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_raise_slow_empty_pressures
{
public:
  explicit Init_LpsSaNvmCalDataChannelDataMain_raise_slow_empty_pressures(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_lower_slow_empty_lift_heights raise_slow_empty_pressures(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_raise_slow_empty_pressures_type arg)
  {
    msg_.raise_slow_empty_pressures = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_lower_slow_empty_lift_heights(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

class Init_LpsSaNvmCalDataChannelDataMain_raise_slow_empty_lift_heights
{
public:
  Init_LpsSaNvmCalDataChannelDataMain_raise_slow_empty_lift_heights()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaNvmCalDataChannelDataMain_raise_slow_empty_pressures raise_slow_empty_lift_heights(::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain::_raise_slow_empty_lift_heights_type arg)
  {
    msg_.raise_slow_empty_lift_heights = std::move(arg);
    return Init_LpsSaNvmCalDataChannelDataMain_raise_slow_empty_pressures(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaNvmCalDataChannelDataMain_raise_slow_empty_lift_heights();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__BUILDER_HPP_
