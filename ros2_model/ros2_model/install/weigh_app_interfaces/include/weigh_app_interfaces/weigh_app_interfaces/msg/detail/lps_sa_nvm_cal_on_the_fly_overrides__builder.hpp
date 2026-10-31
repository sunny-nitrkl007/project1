// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyOverrides.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_overrides.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_overrides__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaNvmCalOnTheFlyOverrides_tilt_overrides
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_tilt_overrides(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides tilt_overrides(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_tilt_overrides_type arg)
  {
    msg_.tilt_overrides = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lever_info_available
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lever_info_available(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_tilt_overrides lever_info_available(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lever_info_available_type arg)
  {
    msg_.lever_info_available = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_tilt_overrides(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lift_faulted
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lift_faulted(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lever_info_available lift_faulted(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lift_faulted_type arg)
  {
    msg_.lift_faulted = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lever_info_available(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_center
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_center(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lift_faulted lift_in_center(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lift_in_center_type arg)
  {
    msg_.lift_in_center = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lift_faulted(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_lower_detent
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_lower_detent(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_center lift_in_lower_detent(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lift_in_lower_detent_type arg)
  {
    msg_.lift_in_lower_detent = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_center(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_raise_detent
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_raise_detent(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_lower_detent lift_in_raise_detent(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lift_in_raise_detent_type arg)
  {
    msg_.lift_in_raise_detent = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_lower_detent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lift_valve_cmd_percent
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lift_valve_cmd_percent(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_raise_detent lift_valve_cmd_percent(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lift_valve_cmd_percent_type arg)
  {
    msg_.lift_valve_cmd_percent = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lift_in_raise_detent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_cal_ovr_acknowledge
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_cal_ovr_acknowledge(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lift_valve_cmd_percent cal_ovr_acknowledge(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_cal_ovr_acknowledge_type arg)
  {
    msg_.cal_ovr_acknowledge = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lift_valve_cmd_percent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lift_top_flag
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lift_top_flag(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_cal_ovr_acknowledge lift_top_flag(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lift_top_flag_type arg)
  {
    msg_.lift_top_flag = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_cal_ovr_acknowledge(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lift_bottom_flag
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lift_bottom_flag(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lift_top_flag lift_bottom_flag(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lift_bottom_flag_type arg)
  {
    msg_.lift_bottom_flag = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lift_top_flag(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_cal_ovr_active
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_cal_ovr_active(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lift_bottom_flag lps_cal_app_inf_cal_ovr_active(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lps_cal_app_inf_cal_ovr_active_type arg)
  {
    msg_.lps_cal_app_inf_cal_ovr_active = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lift_bottom_flag(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_eng_spd_lmt
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_eng_spd_lmt(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_cal_ovr_active lps_cal_app_inf_eng_spd_lmt(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lps_cal_app_inf_eng_spd_lmt_type arg)
  {
    msg_.lps_cal_app_inf_eng_spd_lmt = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_cal_ovr_active(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_dump_cmd_lmt
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_dump_cmd_lmt(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_eng_spd_lmt lps_cal_app_inf_dump_cmd_lmt(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lps_cal_app_inf_dump_cmd_lmt_type arg)
  {
    msg_.lps_cal_app_inf_dump_cmd_lmt = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_eng_spd_lmt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_rack_cmd_lmt
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_rack_cmd_lmt(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_dump_cmd_lmt lps_cal_app_inf_rack_cmd_lmt(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lps_cal_app_inf_rack_cmd_lmt_type arg)
  {
    msg_.lps_cal_app_inf_rack_cmd_lmt = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_dump_cmd_lmt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_lower_cmd_lmt
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_lower_cmd_lmt(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_rack_cmd_lmt lps_cal_app_inf_lower_cmd_lmt(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lps_cal_app_inf_lower_cmd_lmt_type arg)
  {
    msg_.lps_cal_app_inf_lower_cmd_lmt = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_rack_cmd_lmt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_raise_cmd_lmt
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_raise_cmd_lmt(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_lower_cmd_lmt lps_cal_app_inf_raise_cmd_lmt(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lps_cal_app_inf_raise_cmd_lmt_type arg)
  {
    msg_.lps_cal_app_inf_raise_cmd_lmt = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_lower_cmd_lmt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

class Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_ovr_state
{
public:
  Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_ovr_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_raise_cmd_lmt lps_cal_ovr_state(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides::_lps_cal_ovr_state_type arg)
  {
    msg_.lps_cal_ovr_state = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_app_inf_raise_cmd_lmt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaNvmCalOnTheFlyOverrides_lps_cal_ovr_state();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__BUILDER_HPP_
