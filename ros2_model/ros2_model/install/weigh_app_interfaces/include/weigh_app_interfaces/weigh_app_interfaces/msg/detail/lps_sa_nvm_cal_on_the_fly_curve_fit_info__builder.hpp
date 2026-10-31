// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyCurveFitInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_curve_fit_info.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_curve_fit_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaNvmCalOnTheFlyCurveFitInfo_imu_cal_results
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyCurveFitInfo_imu_cal_results(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo imu_cal_results(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo::_imu_cal_results_type arg)
  {
    msg_.imu_cal_results = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo msg_;
};

class Init_LpsSaNvmCalOnTheFlyCurveFitInfo_lower_num_points
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyCurveFitInfo_lower_num_points(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyCurveFitInfo_imu_cal_results lower_num_points(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo::_lower_num_points_type arg)
  {
    msg_.lower_num_points = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyCurveFitInfo_imu_cal_results(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo msg_;
};

class Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_num_points
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_num_points(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyCurveFitInfo_lower_num_points raise_num_points(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo::_raise_num_points_type arg)
  {
    msg_.raise_num_points = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyCurveFitInfo_lower_num_points(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo msg_;
};

class Init_LpsSaNvmCalOnTheFlyCurveFitInfo_internal_step
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyCurveFitInfo_internal_step(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_num_points internal_step(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo::_internal_step_type arg)
  {
    msg_.internal_step = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_num_points(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo msg_;
};

class Init_LpsSaNvmCalOnTheFlyCurveFitInfo_lower_slow_fit_done
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyCurveFitInfo_lower_slow_fit_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyCurveFitInfo_internal_step lower_slow_fit_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo::_lower_slow_fit_done_type arg)
  {
    msg_.lower_slow_fit_done = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyCurveFitInfo_internal_step(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo msg_;
};

class Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_fast_fit_done
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_fast_fit_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyCurveFitInfo_lower_slow_fit_done raise_fast_fit_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo::_raise_fast_fit_done_type arg)
  {
    msg_.raise_fast_fit_done = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyCurveFitInfo_lower_slow_fit_done(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo msg_;
};

class Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_slow_fit_done
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_slow_fit_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_fast_fit_done raise_slow_fit_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo::_raise_slow_fit_done_type arg)
  {
    msg_.raise_slow_fit_done = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_fast_fit_done(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo msg_;
};

class Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_fast_vel_done
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_fast_vel_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_slow_fit_done raise_fast_vel_done(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo::_raise_fast_vel_done_type arg)
  {
    msg_.raise_fast_vel_done = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_slow_fit_done(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo msg_;
};

class Init_LpsSaNvmCalOnTheFlyCurveFitInfo_enforce_lower_detent
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyCurveFitInfo_enforce_lower_detent(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_fast_vel_done enforce_lower_detent(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo::_enforce_lower_detent_type arg)
  {
    msg_.enforce_lower_detent = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyCurveFitInfo_raise_fast_vel_done(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo msg_;
};

class Init_LpsSaNvmCalOnTheFlyCurveFitInfo_enforce_raise_detent
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyCurveFitInfo_enforce_raise_detent(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyCurveFitInfo_enforce_lower_detent enforce_raise_detent(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo::_enforce_raise_detent_type arg)
  {
    msg_.enforce_raise_detent = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyCurveFitInfo_enforce_lower_detent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo msg_;
};

class Init_LpsSaNvmCalOnTheFlyCurveFitInfo_hyd_oil_temp_met
{
public:
  Init_LpsSaNvmCalOnTheFlyCurveFitInfo_hyd_oil_temp_met()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaNvmCalOnTheFlyCurveFitInfo_enforce_raise_detent hyd_oil_temp_met(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo::_hyd_oil_temp_met_type arg)
  {
    msg_.hyd_oil_temp_met = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyCurveFitInfo_enforce_raise_detent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaNvmCalOnTheFlyCurveFitInfo_hyd_oil_temp_met();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__BUILDER_HPP_
