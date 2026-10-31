// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyTiltOverrides.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_tilt_overrides.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_tilt_overrides__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaNvmCalOnTheFlyTiltOverrides_cal_tilt_override_fail
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyTiltOverrides_cal_tilt_override_fail(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides cal_tilt_override_fail(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides::_cal_tilt_override_fail_type arg)
  {
    msg_.cal_tilt_override_fail = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyTiltOverrides_cal_tilt_override_complete
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyTiltOverrides_cal_tilt_override_complete(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyTiltOverrides_cal_tilt_override_fail cal_tilt_override_complete(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides::_cal_tilt_override_complete_type arg)
  {
    msg_.cal_tilt_override_complete = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyTiltOverrides_cal_tilt_override_fail(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyTiltOverrides_lps_cal_tilt_ovr_start_request
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyTiltOverrides_lps_cal_tilt_ovr_start_request(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyTiltOverrides_cal_tilt_override_complete lps_cal_tilt_ovr_start_request(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides::_lps_cal_tilt_ovr_start_request_type arg)
  {
    msg_.lps_cal_tilt_ovr_start_request = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyTiltOverrides_cal_tilt_override_complete(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_dump_cmd_ovr
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_dump_cmd_ovr(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyTiltOverrides_lps_cal_tilt_ovr_start_request tilt_dump_cmd_ovr(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides::_tilt_dump_cmd_ovr_type arg)
  {
    msg_.tilt_dump_cmd_ovr = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyTiltOverrides_lps_cal_tilt_ovr_start_request(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyTiltOverrides_count_of_samples
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyTiltOverrides_count_of_samples(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_dump_cmd_ovr count_of_samples(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides::_count_of_samples_type arg)
  {
    msg_.count_of_samples = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_dump_cmd_ovr(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyTiltOverrides_desired_tilt_extmm
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyTiltOverrides_desired_tilt_extmm(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyTiltOverrides_count_of_samples desired_tilt_extmm(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides::_desired_tilt_extmm_type arg)
  {
    msg_.desired_tilt_extmm = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyTiltOverrides_count_of_samples(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_noise_min
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_noise_min(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyTiltOverrides_desired_tilt_extmm tilt_noise_min(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides::_tilt_noise_min_type arg)
  {
    msg_.tilt_noise_min = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyTiltOverrides_desired_tilt_extmm(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_noise_max
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_noise_max(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_noise_min tilt_noise_max(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides::_tilt_noise_max_type arg)
  {
    msg_.tilt_noise_max = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_noise_min(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyTiltOverrides_lps_cal_tilt_ovr_state
{
public:
  Init_LpsSaNvmCalOnTheFlyTiltOverrides_lps_cal_tilt_ovr_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_noise_max lps_cal_tilt_ovr_state(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides::_lps_cal_tilt_ovr_state_type arg)
  {
    msg_.lps_cal_tilt_ovr_state = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyTiltOverrides_tilt_noise_max(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaNvmCalOnTheFlyTiltOverrides_lps_cal_tilt_ovr_state();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__BUILDER_HPP_
