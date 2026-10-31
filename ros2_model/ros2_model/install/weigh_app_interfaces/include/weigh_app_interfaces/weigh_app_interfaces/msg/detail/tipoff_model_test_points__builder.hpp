// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/TipoffModelTestPoints.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_model_test_points.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/tipoff_model_test_points__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_TipoffModelTestPoints_toa_tool_bc_angle
{
public:
  explicit Init_TipoffModelTestPoints_toa_tool_bc_angle(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::TipoffModelTestPoints toa_tool_bc_angle(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_tool_bc_angle_type arg)
  {
    msg_.toa_tool_bc_angle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_send_cpm_live_payload
{
public:
  explicit Init_TipoffModelTestPoints_toa_send_cpm_live_payload(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_tool_bc_angle toa_send_cpm_live_payload(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_send_cpm_live_payload_type arg)
  {
    msg_.toa_send_cpm_live_payload = std::move(arg);
    return Init_TipoffModelTestPoints_toa_tool_bc_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_secure_two_lower
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_secure_two_lower(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_send_cpm_live_payload toa_stat_payload_secure_two_lower(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_secure_two_lower_type arg)
  {
    msg_.toa_stat_payload_secure_two_lower = std::move(arg);
    return Init_TipoffModelTestPoints_toa_send_cpm_live_payload(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_secure_two_upper
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_secure_two_upper(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_secure_two_lower toa_stat_payload_secure_two_upper(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_secure_two_upper_type arg)
  {
    msg_.toa_stat_payload_secure_two_upper = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_secure_two_lower(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_secure_one_size
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_secure_one_size(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_secure_two_upper toa_stat_payload_secure_one_size(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_secure_one_size_type arg)
  {
    msg_.toa_stat_payload_secure_one_size = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_secure_two_upper(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_secure_one_lower
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_secure_one_lower(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_secure_one_size toa_stat_payload_secure_one_lower(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_secure_one_lower_type arg)
  {
    msg_.toa_stat_payload_secure_one_lower = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_secure_one_size(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_secure_one_upper
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_secure_one_upper(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_secure_one_lower toa_stat_payload_secure_one_upper(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_secure_one_upper_type arg)
  {
    msg_.toa_stat_payload_secure_one_upper = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_secure_one_lower(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_secure_two_size
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_secure_two_size(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_secure_one_upper toa_stat_payload_secure_two_size(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_secure_two_size_type arg)
  {
    msg_.toa_stat_payload_secure_two_size = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_secure_one_upper(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_target_payload_pre_comp
{
public:
  explicit Init_TipoffModelTestPoints_toa_target_payload_pre_comp(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_secure_two_size toa_target_payload_pre_comp(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_target_payload_pre_comp_type arg)
  {
    msg_.toa_target_payload_pre_comp = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_secure_two_size(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_target_payload_post_comp
{
public:
  explicit Init_TipoffModelTestPoints_toa_target_payload_post_comp(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_target_payload_pre_comp toa_target_payload_post_comp(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_target_payload_post_comp_type arg)
  {
    msg_.toa_target_payload_post_comp = std::move(arg);
    return Init_TipoffModelTestPoints_toa_target_payload_pre_comp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_target_comp_margin
{
public:
  explicit Init_TipoffModelTestPoints_toa_target_comp_margin(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_target_payload_post_comp toa_target_comp_margin(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_target_comp_margin_type arg)
  {
    msg_.toa_target_comp_margin = std::move(arg);
    return Init_TipoffModelTestPoints_toa_target_payload_post_comp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_imu_neef_pitch
{
public:
  explicit Init_TipoffModelTestPoints_toa_imu_neef_pitch(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_target_comp_margin toa_imu_neef_pitch(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_imu_neef_pitch_type arg)
  {
    msg_.toa_imu_neef_pitch = std::move(arg);
    return Init_TipoffModelTestPoints_toa_target_comp_margin(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_imu_neef_grav_z
{
public:
  explicit Init_TipoffModelTestPoints_toa_imu_neef_grav_z(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_imu_neef_pitch toa_imu_neef_grav_z(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_imu_neef_grav_z_type arg)
  {
    msg_.toa_imu_neef_grav_z = std::move(arg);
    return Init_TipoffModelTestPoints_toa_imu_neef_pitch(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_imu_neef_grav_y
{
public:
  explicit Init_TipoffModelTestPoints_toa_imu_neef_grav_y(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_imu_neef_grav_z toa_imu_neef_grav_y(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_imu_neef_grav_y_type arg)
  {
    msg_.toa_imu_neef_grav_y = std::move(arg);
    return Init_TipoffModelTestPoints_toa_imu_neef_grav_z(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_imu_neef_grav_x
{
public:
  explicit Init_TipoffModelTestPoints_toa_imu_neef_grav_x(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_imu_neef_grav_y toa_imu_neef_grav_x(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_imu_neef_grav_x_type arg)
  {
    msg_.toa_imu_neef_grav_x = std::move(arg);
    return Init_TipoffModelTestPoints_toa_imu_neef_grav_y(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_z
{
public:
  explicit Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_z(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_imu_neef_grav_x toa_imu_raw_eef_accl_z(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_imu_raw_eef_accl_z_type arg)
  {
    msg_.toa_imu_raw_eef_accl_z = std::move(arg);
    return Init_TipoffModelTestPoints_toa_imu_neef_grav_x(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_y
{
public:
  explicit Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_y(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_z toa_imu_raw_eef_accl_y(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_imu_raw_eef_accl_y_type arg)
  {
    msg_.toa_imu_raw_eef_accl_y = std::move(arg);
    return Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_z(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_x
{
public:
  explicit Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_x(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_y toa_imu_raw_eef_accl_x(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_imu_raw_eef_accl_x_type arg)
  {
    msg_.toa_imu_raw_eef_accl_x = std::move(arg);
    return Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_y(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_latch_invalidate
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_latch_invalidate(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_x toa_pfw_latch_invalidate(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_latch_invalidate_type arg)
  {
    msg_.toa_pfw_latch_invalidate = std::move(arg);
    return Init_TipoffModelTestPoints_toa_imu_raw_eef_accl_x(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_payload_notch_post
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_payload_notch_post(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_latch_invalidate toa_pfw_payload_notch_post(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_payload_notch_post_type arg)
  {
    msg_.toa_pfw_payload_notch_post = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_latch_invalidate(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_payload_notch_filt_final
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_payload_notch_filt_final(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_payload_notch_post toa_pfw_payload_notch_filt_final(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_payload_notch_filt_final_type arg)
  {
    msg_.toa_pfw_payload_notch_filt_final = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_payload_notch_post(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_payload_filt_final
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_payload_filt_final(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_payload_notch_filt_final toa_pfw_payload_filt_final(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_payload_filt_final_type arg)
  {
    msg_.toa_pfw_payload_filt_final = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_payload_notch_filt_final(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_nl_mean_est
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_nl_mean_est(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_payload_filt_final toa_pfw_nl_mean_est(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_nl_mean_est_type arg)
  {
    msg_.toa_pfw_nl_mean_est = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_payload_filt_final(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_nl_st_dev_est
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_nl_st_dev_est(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_nl_mean_est toa_pfw_nl_st_dev_est(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_nl_st_dev_est_type arg)
  {
    msg_.toa_pfw_nl_st_dev_est = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_nl_mean_est(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_two_size
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_two_size(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_nl_st_dev_est toa_stat_payload_nl_two_size(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_two_size_type arg)
  {
    msg_.toa_stat_payload_nl_two_size = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_nl_st_dev_est(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_two_low
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_two_low(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_two_size toa_stat_payload_nl_two_low(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_two_low_type arg)
  {
    msg_.toa_stat_payload_nl_two_low = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_two_size(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_two_up
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_two_up(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_two_low toa_stat_payload_nl_two_up(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_two_up_type arg)
  {
    msg_.toa_stat_payload_nl_two_up = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_two_low(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_one_size
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_one_size(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_two_up toa_stat_payload_nl_one_size(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_one_size_type arg)
  {
    msg_.toa_stat_payload_nl_one_size = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_two_up(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_one_low
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_one_low(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_one_size toa_stat_payload_nl_one_low(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_one_low_type arg)
  {
    msg_.toa_stat_payload_nl_one_low = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_one_size(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_one_up
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_one_up(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_one_low toa_stat_payload_nl_one_up(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_one_up_type arg)
  {
    msg_.toa_stat_payload_nl_one_up = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_one_low(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_size
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_size(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_one_up toa_stat_payload_nl_notch_two_size(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_notch_two_size_type arg)
  {
    msg_.toa_stat_payload_nl_notch_two_size = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_one_up(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_low
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_low(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_size toa_stat_payload_nl_notch_two_low(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_notch_two_low_type arg)
  {
    msg_.toa_stat_payload_nl_notch_two_low = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_size(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_up
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_up(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_low toa_stat_payload_nl_notch_two_up(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_notch_two_up_type arg)
  {
    msg_.toa_stat_payload_nl_notch_two_up = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_low(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_size
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_size(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_up toa_stat_payload_nl_notch_one_size(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_notch_one_size_type arg)
  {
    msg_.toa_stat_payload_nl_notch_one_size = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_two_up(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_low
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_low(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_size toa_stat_payload_nl_notch_one_low(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_notch_one_low_type arg)
  {
    msg_.toa_stat_payload_nl_notch_one_low = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_size(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_up
{
public:
  explicit Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_up(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_low toa_stat_payload_nl_notch_one_up(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_stat_payload_nl_notch_one_up_type arg)
  {
    msg_.toa_stat_payload_nl_notch_one_up = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_low(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_mc_maybe_grounded
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_mc_maybe_grounded(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_up toa_pfw_mc_maybe_grounded(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_mc_maybe_grounded_type arg)
  {
    msg_.toa_pfw_mc_maybe_grounded = std::move(arg);
    return Init_TipoffModelTestPoints_toa_stat_payload_nl_notch_one_up(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_mc_maybe_rack_stall
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_mc_maybe_rack_stall(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_mc_maybe_grounded toa_pfw_mc_maybe_rack_stall(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_mc_maybe_rack_stall_type arg)
  {
    msg_.toa_pfw_mc_maybe_rack_stall = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_mc_maybe_grounded(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_mc_maybe_stalled
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_mc_maybe_stalled(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_mc_maybe_rack_stall toa_pfw_mc_maybe_stalled(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_mc_maybe_stalled_type arg)
  {
    msg_.toa_pfw_mc_maybe_stalled = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_mc_maybe_rack_stall(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_mc_ok
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_mc_ok(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_mc_maybe_stalled toa_pfw_mc_ok(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_mc_ok_type arg)
  {
    msg_.toa_pfw_mc_ok = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_mc_maybe_stalled(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_sec_min_bucket_ang
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_sec_min_bucket_ang(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_mc_ok toa_pfw_sec_min_bucket_ang(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_sec_min_bucket_ang_type arg)
  {
    msg_.toa_pfw_sec_min_bucket_ang = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_mc_ok(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_sec_is_racked
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_sec_is_racked(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_sec_min_bucket_ang toa_pfw_sec_is_racked(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_sec_is_racked_type arg)
  {
    msg_.toa_pfw_sec_is_racked = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_sec_min_bucket_ang(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_sec_is_no_collapsing
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_sec_is_no_collapsing(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_sec_is_racked toa_pfw_sec_is_no_collapsing(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_sec_is_no_collapsing_type arg)
  {
    msg_.toa_pfw_sec_is_no_collapsing = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_sec_is_racked(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_sec_is_no_sliding
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_sec_is_no_sliding(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_sec_is_no_collapsing toa_pfw_sec_is_no_sliding(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_sec_is_no_sliding_type arg)
  {
    msg_.toa_pfw_sec_is_no_sliding = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_sec_is_no_collapsing(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_sec_is_secure
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_sec_is_secure(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_sec_is_no_sliding toa_pfw_sec_is_secure(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_sec_is_secure_type arg)
  {
    msg_.toa_pfw_sec_is_secure = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_sec_is_no_sliding(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_is_warm
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_is_warm(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_sec_is_secure toa_pfw_is_warm(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_is_warm_type arg)
  {
    msg_.toa_pfw_is_warm = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_sec_is_secure(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_payload_zeroed
{
public:
  explicit Init_TipoffModelTestPoints_toa_payload_zeroed(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_is_warm toa_payload_zeroed(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_payload_zeroed_type arg)
  {
    msg_.toa_payload_zeroed = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_is_warm(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_raw_payload
{
public:
  explicit Init_TipoffModelTestPoints_toa_raw_payload(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_payload_zeroed toa_raw_payload(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_raw_payload_type arg)
  {
    msg_.toa_raw_payload = std::move(arg);
    return Init_TipoffModelTestPoints_toa_payload_zeroed(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_raw_dist
{
public:
  explicit Init_TipoffModelTestPoints_toa_raw_dist(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_raw_payload toa_raw_dist(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_raw_dist_type arg)
  {
    msg_.toa_raw_dist = std::move(arg);
    return Init_TipoffModelTestPoints_toa_raw_payload(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_lw_status
{
public:
  explicit Init_TipoffModelTestPoints_toa_lw_status(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_raw_dist toa_lw_status(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_lw_status_type arg)
  {
    msg_.toa_lw_status = std::move(arg);
    return Init_TipoffModelTestPoints_toa_raw_dist(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_lw_spill_rate
{
public:
  explicit Init_TipoffModelTestPoints_toa_lw_spill_rate(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_lw_status toa_lw_spill_rate(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_lw_spill_rate_type arg)
  {
    msg_.toa_lw_spill_rate = std::move(arg);
    return Init_TipoffModelTestPoints_toa_lw_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_unsec_bound_upper
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_unsec_bound_upper(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_lw_spill_rate toa_pfw_unsec_bound_upper(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_unsec_bound_upper_type arg)
  {
    msg_.toa_pfw_unsec_bound_upper = std::move(arg);
    return Init_TipoffModelTestPoints_toa_lw_spill_rate(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_unsec_bound_lower
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_unsec_bound_lower(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_unsec_bound_upper toa_pfw_unsec_bound_lower(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_unsec_bound_lower_type arg)
  {
    msg_.toa_pfw_unsec_bound_lower = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_unsec_bound_upper(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_unsec_status
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_unsec_status(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_unsec_bound_lower toa_pfw_unsec_status(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_unsec_status_type arg)
  {
    msg_.toa_pfw_unsec_status = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_unsec_bound_lower(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_imu_cal_pitch_angle
{
public:
  explicit Init_TipoffModelTestPoints_toa_imu_cal_pitch_angle(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_unsec_status toa_imu_cal_pitch_angle(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_imu_cal_pitch_angle_type arg)
  {
    msg_.toa_imu_cal_pitch_angle = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_unsec_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_tool_bc_length
{
public:
  explicit Init_TipoffModelTestPoints_toa_tool_bc_length(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_imu_cal_pitch_angle toa_tool_bc_length(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_tool_bc_length_type arg)
  {
    msg_.toa_tool_bc_length = std::move(arg);
    return Init_TipoffModelTestPoints_toa_imu_cal_pitch_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_tilt_rod_dia
{
public:
  explicit Init_TipoffModelTestPoints_toa_tilt_rod_dia(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_tool_bc_length toa_tilt_rod_dia(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_tilt_rod_dia_type arg)
  {
    msg_.toa_tilt_rod_dia = std::move(arg);
    return Init_TipoffModelTestPoints_toa_tool_bc_length(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_tilt_num_cyl
{
public:
  explicit Init_TipoffModelTestPoints_toa_tilt_num_cyl(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_tilt_rod_dia toa_tilt_num_cyl(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_tilt_num_cyl_type arg)
  {
    msg_.toa_tilt_num_cyl = std::move(arg);
    return Init_TipoffModelTestPoints_toa_tilt_rod_dia(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_tilt_bore_dia
{
public:
  explicit Init_TipoffModelTestPoints_toa_tilt_bore_dia(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_tilt_num_cyl toa_tilt_bore_dia(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_tilt_bore_dia_type arg)
  {
    msg_.toa_tilt_bore_dia = std::move(arg);
    return Init_TipoffModelTestPoints_toa_tilt_num_cyl(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_rated_payload
{
public:
  explicit Init_TipoffModelTestPoints_toa_rated_payload(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_tilt_bore_dia toa_rated_payload(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_rated_payload_type arg)
  {
    msg_.toa_rated_payload = std::move(arg);
    return Init_TipoffModelTestPoints_toa_tilt_bore_dia(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_payload_anc_zeroed
{
public:
  explicit Init_TipoffModelTestPoints_toa_payload_anc_zeroed(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_rated_payload toa_payload_anc_zeroed(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_payload_anc_zeroed_type arg)
  {
    msg_.toa_payload_anc_zeroed = std::move(arg);
    return Init_TipoffModelTestPoints_toa_rated_payload(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_payload_anc_adjusted
{
public:
  explicit Init_TipoffModelTestPoints_toa_payload_anc_adjusted(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_payload_anc_zeroed toa_payload_anc_adjusted(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_payload_anc_adjusted_type arg)
  {
    msg_.toa_payload_anc_adjusted = std::move(arg);
    return Init_TipoffModelTestPoints_toa_payload_anc_zeroed(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_lift_rod_dia
{
public:
  explicit Init_TipoffModelTestPoints_toa_lift_rod_dia(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_payload_anc_adjusted toa_lift_rod_dia(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_lift_rod_dia_type arg)
  {
    msg_.toa_lift_rod_dia = std::move(arg);
    return Init_TipoffModelTestPoints_toa_payload_anc_adjusted(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_lift_bore_dia
{
public:
  explicit Init_TipoffModelTestPoints_toa_lift_bore_dia(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_lift_rod_dia toa_lift_bore_dia(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_lift_bore_dia_type arg)
  {
    msg_.toa_lift_bore_dia = std::move(arg);
    return Init_TipoffModelTestPoints_toa_lift_rod_dia(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_app_number
{
public:
  explicit Init_TipoffModelTestPoints_toa_app_number(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_lift_bore_dia toa_app_number(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_app_number_type arg)
  {
    msg_.toa_app_number = std::move(arg);
    return Init_TipoffModelTestPoints_toa_lift_bore_dia(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_sfunc_out_raw_mass_tonne
{
public:
  explicit Init_TipoffModelTestPoints_toa_sfunc_out_raw_mass_tonne(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_app_number toa_sfunc_out_raw_mass_tonne(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_sfunc_out_raw_mass_tonne_type arg)
  {
    msg_.toa_sfunc_out_raw_mass_tonne = std::move(arg);
    return Init_TipoffModelTestPoints_toa_app_number(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_sfunc_in_tilt_force
{
public:
  explicit Init_TipoffModelTestPoints_toa_sfunc_in_tilt_force(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_sfunc_out_raw_mass_tonne toa_sfunc_in_tilt_force(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_sfunc_in_tilt_force_type arg)
  {
    msg_.toa_sfunc_in_tilt_force = std::move(arg);
    return Init_TipoffModelTestPoints_toa_sfunc_out_raw_mass_tonne(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_sfunc_in_lift_force
{
public:
  explicit Init_TipoffModelTestPoints_toa_sfunc_in_lift_force(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_sfunc_in_tilt_force toa_sfunc_in_lift_force(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_sfunc_in_lift_force_type arg)
  {
    msg_.toa_sfunc_in_lift_force = std::move(arg);
    return Init_TipoffModelTestPoints_toa_sfunc_in_tilt_force(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_sfunc_in_grav_y
{
public:
  explicit Init_TipoffModelTestPoints_toa_sfunc_in_grav_y(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_sfunc_in_lift_force toa_sfunc_in_grav_y(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_sfunc_in_grav_y_type arg)
  {
    msg_.toa_sfunc_in_grav_y = std::move(arg);
    return Init_TipoffModelTestPoints_toa_sfunc_in_lift_force(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_sfunc_in_grav_x
{
public:
  explicit Init_TipoffModelTestPoints_toa_sfunc_in_grav_x(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_sfunc_in_grav_y toa_sfunc_in_grav_x(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_sfunc_in_grav_x_type arg)
  {
    msg_.toa_sfunc_in_grav_x = std::move(arg);
    return Init_TipoffModelTestPoints_toa_sfunc_in_grav_y(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_send_payload_arb
{
public:
  explicit Init_TipoffModelTestPoints_toa_send_payload_arb(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_sfunc_in_grav_x toa_send_payload_arb(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_send_payload_arb_type arg)
  {
    msg_.toa_send_payload_arb = std::move(arg);
    return Init_TipoffModelTestPoints_toa_sfunc_in_grav_x(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_payload_adjusted
{
public:
  explicit Init_TipoffModelTestPoints_toa_payload_adjusted(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_send_payload_arb toa_payload_adjusted(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_payload_adjusted_type arg)
  {
    msg_.toa_payload_adjusted = std::move(arg);
    return Init_TipoffModelTestPoints_toa_send_payload_arb(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_lw_lpf_post
{
public:
  explicit Init_TipoffModelTestPoints_toa_lw_lpf_post(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_payload_adjusted toa_lw_lpf_post(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_lw_lpf_post_type arg)
  {
    msg_.toa_lw_lpf_post = std::move(arg);
    return Init_TipoffModelTestPoints_toa_payload_adjusted(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_nl_notch_st_dev_est
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_nl_notch_st_dev_est(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_lw_lpf_post toa_pfw_nl_notch_st_dev_est(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_nl_notch_st_dev_est_type arg)
  {
    msg_.toa_pfw_nl_notch_st_dev_est = std::move(arg);
    return Init_TipoffModelTestPoints_toa_lw_lpf_post(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_nl_notch_mean_est
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_nl_notch_mean_est(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_nl_notch_st_dev_est toa_pfw_nl_notch_mean_est(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_nl_notch_mean_est_type arg)
  {
    msg_.toa_pfw_nl_notch_mean_est = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_nl_notch_st_dev_est(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_target_payload_status
{
public:
  explicit Init_TipoffModelTestPoints_toa_target_payload_status(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_nl_notch_mean_est toa_target_payload_status(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_target_payload_status_type arg)
  {
    msg_.toa_target_payload_status = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_nl_notch_mean_est(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_target_payload_final
{
public:
  explicit Init_TipoffModelTestPoints_toa_target_payload_final(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_target_payload_status toa_target_payload_final(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_target_payload_final_type arg)
  {
    msg_.toa_target_payload_final = std::move(arg);
    return Init_TipoffModelTestPoints_toa_target_payload_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_sec_st_dev
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_sec_st_dev(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_target_payload_final toa_pfw_sec_st_dev(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_sec_st_dev_type arg)
  {
    msg_.toa_pfw_sec_st_dev = std::move(arg);
    return Init_TipoffModelTestPoints_toa_target_payload_final(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_sec_status
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_sec_status(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_sec_st_dev toa_pfw_sec_status(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_sec_status_type arg)
  {
    msg_.toa_pfw_sec_status = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_sec_st_dev(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_sec_payload
{
public:
  explicit Init_TipoffModelTestPoints_toa_pfw_sec_payload(::weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
  : msg_(msg)
  {}
  Init_TipoffModelTestPoints_toa_pfw_sec_status toa_pfw_sec_payload(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_sec_payload_type arg)
  {
    msg_.toa_pfw_sec_payload = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_sec_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

class Init_TipoffModelTestPoints_toa_pfw_sec_latch
{
public:
  Init_TipoffModelTestPoints_toa_pfw_sec_latch()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TipoffModelTestPoints_toa_pfw_sec_payload toa_pfw_sec_latch(::weigh_app_interfaces::msg::TipoffModelTestPoints::_toa_pfw_sec_latch_type arg)
  {
    msg_.toa_pfw_sec_latch = std::move(arg);
    return Init_TipoffModelTestPoints_toa_pfw_sec_payload(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffModelTestPoints msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::TipoffModelTestPoints>()
{
  return weigh_app_interfaces::msg::builder::Init_TipoffModelTestPoints_toa_pfw_sec_latch();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__BUILDER_HPP_
