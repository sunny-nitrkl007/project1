// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyDataOnTheFly.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_data_on_the_fly.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_data_on_the_fly__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaNvmCalOnTheFlyDataOnTheFly_cal_overrides
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyDataOnTheFly_cal_overrides(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly cal_overrides(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly::_cal_overrides_type arg)
  {
    msg_.cal_overrides = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly msg_;
};

class Init_LpsSaNvmCalOnTheFlyDataOnTheFly_cal_updates
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyDataOnTheFly_cal_updates(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyDataOnTheFly_cal_overrides cal_updates(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly::_cal_updates_type arg)
  {
    msg_.cal_updates = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyDataOnTheFly_cal_overrides(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly msg_;
};

class Init_LpsSaNvmCalOnTheFlyDataOnTheFly_curve_info
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyDataOnTheFly_curve_info(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyDataOnTheFly_cal_updates curve_info(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly::_curve_info_type arg)
  {
    msg_.curve_info = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyDataOnTheFly_cal_updates(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly msg_;
};

class Init_LpsSaNvmCalOnTheFlyDataOnTheFly_status_flags
{
public:
  Init_LpsSaNvmCalOnTheFlyDataOnTheFly_status_flags()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaNvmCalOnTheFlyDataOnTheFly_curve_info status_flags(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly::_status_flags_type arg)
  {
    msg_.status_flags = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyDataOnTheFly_curve_info(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaNvmCalOnTheFlyDataOnTheFly_status_flags();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__BUILDER_HPP_
