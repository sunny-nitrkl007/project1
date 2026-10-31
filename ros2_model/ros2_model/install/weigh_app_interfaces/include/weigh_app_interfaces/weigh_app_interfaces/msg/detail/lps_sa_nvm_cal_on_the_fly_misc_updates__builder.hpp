// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyMiscUpdates.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_misc_updates.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_misc_updates__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_lever_info_faulted
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_lever_info_faulted(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates lift_lever_info_faulted(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates::_lift_lever_info_faulted_type arg)
  {
    msg_.lift_lever_info_faulted = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates msg_;
};

class Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_lever_info_lever_info_available
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_lever_info_lever_info_available(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_lever_info_faulted lift_lever_info_lever_info_available(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates::_lift_lever_info_lever_info_available_type arg)
  {
    msg_.lift_lever_info_lever_info_available = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_lever_info_faulted(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates msg_;
};

class Init_LpsSaNvmCalOnTheFlyMiscUpdates_bkt_angle_stat
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyMiscUpdates_bkt_angle_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_lever_info_lever_info_available bkt_angle_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates::_bkt_angle_stat_type arg)
  {
    msg_.bkt_angle_stat = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_lever_info_lever_info_available(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates msg_;
};

class Init_LpsSaNvmCalOnTheFlyMiscUpdates_tilt_cyl_length_norm_stat
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyMiscUpdates_tilt_cyl_length_norm_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyMiscUpdates_bkt_angle_stat tilt_cyl_length_norm_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates::_tilt_cyl_length_norm_stat_type arg)
  {
    msg_.tilt_cyl_length_norm_stat = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyMiscUpdates_bkt_angle_stat(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates msg_;
};

class Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_cyl_vel_stat
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_cyl_vel_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyMiscUpdates_tilt_cyl_length_norm_stat lift_cyl_vel_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates::_lift_cyl_vel_stat_type arg)
  {
    msg_.lift_cyl_vel_stat = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyMiscUpdates_tilt_cyl_length_norm_stat(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates msg_;
};

class Init_LpsSaNvmCalOnTheFlyMiscUpdates_hyd_oil_temp_stat
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyMiscUpdates_hyd_oil_temp_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_cyl_vel_stat hyd_oil_temp_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates::_hyd_oil_temp_stat_type arg)
  {
    msg_.hyd_oil_temp_stat = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_cyl_vel_stat(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates msg_;
};

class Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_cyl_length_norm_stat
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_cyl_length_norm_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyMiscUpdates_hyd_oil_temp_stat lift_cyl_length_norm_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates::_lift_cyl_length_norm_stat_type arg)
  {
    msg_.lift_cyl_length_norm_stat = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyMiscUpdates_hyd_oil_temp_stat(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates msg_;
};

class Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_re_pres_stat
{
public:
  explicit Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_re_pres_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates & msg)
  : msg_(msg)
  {}
  Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_cyl_length_norm_stat lift_re_pres_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates::_lift_re_pres_stat_type arg)
  {
    msg_.lift_re_pres_stat = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_cyl_length_norm_stat(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates msg_;
};

class Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_he_pres_stat
{
public:
  Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_he_pres_stat()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_re_pres_stat lift_he_pres_stat(::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates::_lift_he_pres_stat_type arg)
  {
    msg_.lift_he_pres_stat = std::move(arg);
    return Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_re_pres_stat(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaNvmCalOnTheFlyMiscUpdates_lift_he_pres_stat();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__BUILDER_HPP_
