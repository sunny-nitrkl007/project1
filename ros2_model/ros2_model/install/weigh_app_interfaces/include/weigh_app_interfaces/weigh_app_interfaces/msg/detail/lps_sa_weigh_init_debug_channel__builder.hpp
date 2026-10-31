// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaWeighInitDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_weigh_init_debug_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_weigh_init_debug_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaWeighInitDebugChannel_tilt_comp_gain_scalar
{
public:
  explicit Init_LpsSaWeighInitDebugChannel_tilt_comp_gain_scalar(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel tilt_comp_gain_scalar(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel::_tilt_comp_gain_scalar_type arg)
  {
    msg_.tilt_comp_gain_scalar = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel msg_;
};

class Init_LpsSaWeighInitDebugChannel_start_of_weigh
{
public:
  explicit Init_LpsSaWeighInitDebugChannel_start_of_weigh(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighInitDebugChannel_tilt_comp_gain_scalar start_of_weigh(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel::_start_of_weigh_type arg)
  {
    msg_.start_of_weigh = std::move(arg);
    return Init_LpsSaWeighInitDebugChannel_tilt_comp_gain_scalar(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel msg_;
};

class Init_LpsSaWeighInitDebugChannel_dig_target_wt
{
public:
  explicit Init_LpsSaWeighInitDebugChannel_dig_target_wt(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighInitDebugChannel_start_of_weigh dig_target_wt(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel::_dig_target_wt_type arg)
  {
    msg_.dig_target_wt = std::move(arg);
    return Init_LpsSaWeighInitDebugChannel_start_of_weigh(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel msg_;
};

class Init_LpsSaWeighInitDebugChannel_zero_weight
{
public:
  explicit Init_LpsSaWeighInitDebugChannel_zero_weight(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighInitDebugChannel_dig_target_wt zero_weight(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel::_zero_weight_type arg)
  {
    msg_.zero_weight = std::move(arg);
    return Init_LpsSaWeighInitDebugChannel_dig_target_wt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel msg_;
};

class Init_LpsSaWeighInitDebugChannel_cal_adjust
{
public:
  explicit Init_LpsSaWeighInitDebugChannel_cal_adjust(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighInitDebugChannel_zero_weight cal_adjust(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel::_cal_adjust_type arg)
  {
    msg_.cal_adjust = std::move(arg);
    return Init_LpsSaWeighInitDebugChannel_zero_weight(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel msg_;
};

class Init_LpsSaWeighInitDebugChannel_cal_status
{
public:
  explicit Init_LpsSaWeighInitDebugChannel_cal_status(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighInitDebugChannel_cal_adjust cal_status(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel::_cal_status_type arg)
  {
    msg_.cal_status = std::move(arg);
    return Init_LpsSaWeighInitDebugChannel_cal_adjust(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel msg_;
};

class Init_LpsSaWeighInitDebugChannel_cal_weight
{
public:
  explicit Init_LpsSaWeighInitDebugChannel_cal_weight(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighInitDebugChannel_cal_status cal_weight(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel::_cal_weight_type arg)
  {
    msg_.cal_weight = std::move(arg);
    return Init_LpsSaWeighInitDebugChannel_cal_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel msg_;
};

class Init_LpsSaWeighInitDebugChannel_exec_rate
{
public:
  Init_LpsSaWeighInitDebugChannel_exec_rate()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaWeighInitDebugChannel_cal_weight exec_rate(::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel::_exec_rate_type arg)
  {
    msg_.exec_rate = std::move(arg);
    return Init_LpsSaWeighInitDebugChannel_cal_weight(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaWeighInitDebugChannel_exec_rate();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__BUILDER_HPP_
