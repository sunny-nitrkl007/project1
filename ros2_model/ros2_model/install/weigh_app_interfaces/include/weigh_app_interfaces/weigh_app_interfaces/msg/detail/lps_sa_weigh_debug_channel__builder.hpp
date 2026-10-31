// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaWeighDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_weigh_debug_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_weigh_debug_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_z
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_z(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel chassis_imu_ang_vel_z(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_ang_vel_z_type arg)
  {
    msg_.chassis_imu_ang_vel_z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_y
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_y(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_z chassis_imu_ang_vel_y(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_ang_vel_y_type arg)
  {
    msg_.chassis_imu_ang_vel_y = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_z(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_x
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_x(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_y chassis_imu_ang_vel_x(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_ang_vel_x_type arg)
  {
    msg_.chassis_imu_ang_vel_x = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_y(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_z
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_z(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_x chassis_imu_lin_acc_z(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_lin_acc_z_type arg)
  {
    msg_.chassis_imu_lin_acc_z = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_ang_vel_x(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_y
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_y(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_z chassis_imu_lin_acc_y(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_lin_acc_y_type arg)
  {
    msg_.chassis_imu_lin_acc_y = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_z(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_x
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_x(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_y chassis_imu_lin_acc_x(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_lin_acc_x_type arg)
  {
    msg_.chassis_imu_lin_acc_x = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_y(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_sensor_ang_vel_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_sensor_ang_vel_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_x chassis_imu_sensor_ang_vel_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_sensor_ang_vel_status_type arg)
  {
    msg_.chassis_imu_sensor_ang_vel_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_lin_acc_x(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_sensor_lin_acc_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_sensor_lin_acc_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_sensor_ang_vel_status chassis_imu_sensor_lin_acc_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_sensor_lin_acc_status_type arg)
  {
    msg_.chassis_imu_sensor_lin_acc_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_sensor_ang_vel_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_roll
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_roll(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_sensor_lin_acc_status chassis_imu_roll(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_roll_type arg)
  {
    msg_.chassis_imu_roll = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_sensor_lin_acc_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_pitch
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_pitch(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_roll chassis_imu_pitch(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_pitch_type arg)
  {
    msg_.chassis_imu_pitch = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_roll(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_z
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_z(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_pitch chassis_imu_bias_ang_vel_z(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_bias_ang_vel_z_type arg)
  {
    msg_.chassis_imu_bias_ang_vel_z = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_pitch(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_y
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_y(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_z chassis_imu_bias_ang_vel_y(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_bias_ang_vel_y_type arg)
  {
    msg_.chassis_imu_bias_ang_vel_y = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_z(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_x
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_x(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_y chassis_imu_bias_ang_vel_x(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_bias_ang_vel_x_type arg)
  {
    msg_.chassis_imu_bias_ang_vel_x = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_y(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_bias_max_ang_vel
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_bias_max_ang_vel(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_x chassis_imu_bias_max_ang_vel(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_bias_max_ang_vel_type arg)
  {
    msg_.chassis_imu_bias_max_ang_vel = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_bias_ang_vel_x(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_bias_mag_ang_accel
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_bias_mag_ang_accel(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_bias_max_ang_vel chassis_imu_bias_mag_ang_accel(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_bias_mag_ang_accel_type arg)
  {
    msg_.chassis_imu_bias_mag_ang_accel = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_bias_max_ang_vel(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_bias_mag_jerk
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_bias_mag_jerk(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_bias_mag_ang_accel chassis_imu_bias_mag_jerk(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_bias_mag_jerk_type arg)
  {
    msg_.chassis_imu_bias_mag_jerk = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_bias_mag_ang_accel(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_velocity_z
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_velocity_z(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_bias_mag_jerk chassis_imu_velocity_z(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_velocity_z_type arg)
  {
    msg_.chassis_imu_velocity_z = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_bias_mag_jerk(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_velocity_y
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_velocity_y(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_velocity_z chassis_imu_velocity_y(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_velocity_y_type arg)
  {
    msg_.chassis_imu_velocity_y = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_velocity_z(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_velocity_x
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_velocity_x(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_velocity_y chassis_imu_velocity_x(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_velocity_x_type arg)
  {
    msg_.chassis_imu_velocity_x = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_velocity_y(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_gravity_z
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_gravity_z(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_velocity_x chassis_imu_gravity_z(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_gravity_z_type arg)
  {
    msg_.chassis_imu_gravity_z = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_velocity_x(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_gravity_y
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_gravity_y(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_gravity_z chassis_imu_gravity_y(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_gravity_y_type arg)
  {
    msg_.chassis_imu_gravity_y = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_gravity_z(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_chassis_imu_gravity_x
{
public:
  explicit Init_LpsSaWeighDebugChannel_chassis_imu_gravity_x(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_gravity_y chassis_imu_gravity_x(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_chassis_imu_gravity_x_type arg)
  {
    msg_.chassis_imu_gravity_x = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_gravity_y(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_tipoff_outputs
{
public:
  explicit Init_LpsSaWeighDebugChannel_tipoff_outputs(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_chassis_imu_gravity_x tipoff_outputs(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_tipoff_outputs_type arg)
  {
    msg_.tipoff_outputs = std::move(arg);
    return Init_LpsSaWeighDebugChannel_chassis_imu_gravity_x(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_tipoff_inputs
{
public:
  explicit Init_LpsSaWeighDebugChannel_tipoff_inputs(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_tipoff_outputs tipoff_inputs(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_tipoff_inputs_type arg)
  {
    msg_.tipoff_inputs = std::move(arg);
    return Init_LpsSaWeighDebugChannel_tipoff_outputs(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_lift_position_filt_angle
{
public:
  explicit Init_LpsSaWeighDebugChannel_lift_position_filt_angle(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_tipoff_inputs lift_position_filt_angle(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_lift_position_filt_angle_type arg)
  {
    msg_.lift_position_filt_angle = std::move(arg);
    return Init_LpsSaWeighDebugChannel_tipoff_inputs(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_lift_position_filt_velocity
{
public:
  explicit Init_LpsSaWeighDebugChannel_lift_position_filt_velocity(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_lift_position_filt_angle lift_position_filt_velocity(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_lift_position_filt_velocity_type arg)
  {
    msg_.lift_position_filt_velocity = std::move(arg);
    return Init_LpsSaWeighDebugChannel_lift_position_filt_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_lift_position_filt_length
{
public:
  explicit Init_LpsSaWeighDebugChannel_lift_position_filt_length(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_lift_position_filt_velocity lift_position_filt_length(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_lift_position_filt_length_type arg)
  {
    msg_.lift_position_filt_length = std::move(arg);
    return Init_LpsSaWeighDebugChannel_lift_position_filt_velocity(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_overload_warn_tbl_prev_dig_state
{
public:
  explicit Init_LpsSaWeighDebugChannel_overload_warn_tbl_prev_dig_state(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_lift_position_filt_length overload_warn_tbl_prev_dig_state(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_overload_warn_tbl_prev_dig_state_type arg)
  {
    msg_.overload_warn_tbl_prev_dig_state = std::move(arg);
    return Init_LpsSaWeighDebugChannel_lift_position_filt_length(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_overload_warn_tbl_level
{
public:
  explicit Init_LpsSaWeighDebugChannel_overload_warn_tbl_level(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_overload_warn_tbl_prev_dig_state overload_warn_tbl_level(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_overload_warn_tbl_level_type arg)
  {
    msg_.overload_warn_tbl_level = std::move(arg);
    return Init_LpsSaWeighDebugChannel_overload_warn_tbl_prev_dig_state(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_overload_warn_tbl_in_overload_range
{
public:
  explicit Init_LpsSaWeighDebugChannel_overload_warn_tbl_in_overload_range(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_overload_warn_tbl_level overload_warn_tbl_in_overload_range(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_overload_warn_tbl_in_overload_range_type arg)
  {
    msg_.overload_warn_tbl_in_overload_range = std::move(arg);
    return Init_LpsSaWeighDebugChannel_overload_warn_tbl_level(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_overload_warn_tbl_dig_reverse_flag
{
public:
  explicit Init_LpsSaWeighDebugChannel_overload_warn_tbl_dig_reverse_flag(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_overload_warn_tbl_in_overload_range overload_warn_tbl_dig_reverse_flag(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_overload_warn_tbl_dig_reverse_flag_type arg)
  {
    msg_.overload_warn_tbl_dig_reverse_flag = std::move(arg);
    return Init_LpsSaWeighDebugChannel_overload_warn_tbl_in_overload_range(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_overload_warn_tbl_bucket_load_factor
{
public:
  explicit Init_LpsSaWeighDebugChannel_overload_warn_tbl_bucket_load_factor(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_overload_warn_tbl_dig_reverse_flag overload_warn_tbl_bucket_load_factor(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_overload_warn_tbl_bucket_load_factor_type arg)
  {
    msg_.overload_warn_tbl_bucket_load_factor = std::move(arg);
    return Init_LpsSaWeighDebugChannel_overload_warn_tbl_dig_reverse_flag(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_zero_adj_tbl_zero_adj_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_zero_adj_tbl_zero_adj_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_overload_warn_tbl_bucket_load_factor zero_adj_tbl_zero_adj_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_zero_adj_tbl_zero_adj_status_type arg)
  {
    msg_.zero_adj_tbl_zero_adj_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_overload_warn_tbl_bucket_load_factor(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_been_below_range
{
public:
  explicit Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_been_below_range(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_zero_adj_tbl_zero_adj_status wrw_tbl_wk_tbl_been_below_range(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_wrw_tbl_wk_tbl_been_below_range_type arg)
  {
    msg_.wrw_tbl_wk_tbl_been_below_range = std::move(arg);
    return Init_LpsSaWeighDebugChannel_zero_adj_tbl_zero_adj_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp
{
public:
  explicit Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_been_below_range wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp_type arg)
  {
    msg_.wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp = std::move(arg);
    return Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_been_below_range(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp wrw_tbl_op_tbl_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_wrw_tbl_op_tbl_status_type arg)
  {
    msg_.wrw_tbl_op_tbl_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_indicator
{
public:
  explicit Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_indicator(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_status wrw_tbl_op_tbl_indicator(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_wrw_tbl_op_tbl_indicator_type arg)
  {
    msg_.wrw_tbl_op_tbl_indicator = std::move(arg);
    return Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_warning
{
public:
  explicit Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_warning(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_indicator wrw_tbl_op_tbl_warning(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_wrw_tbl_op_tbl_warning_type arg)
  {
    msg_.wrw_tbl_op_tbl_warning = std::move(arg);
    return Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_indicator(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_wt
{
public:
  explicit Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_wt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_warning wrw_tbl_op_tbl_wt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_wrw_tbl_op_tbl_wt_type arg)
  {
    msg_.wrw_tbl_op_tbl_wt = std::move(arg);
    return Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_warning(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave
{
public:
  explicit Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_wt wrw_tbl_wk_tbl_result_weight_ave(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_wrw_tbl_wk_tbl_result_weight_ave_type arg)
  {
    msg_.wrw_tbl_wk_tbl_result_weight_ave = std::move(arg);
    return Init_LpsSaWeighDebugChannel_wrw_tbl_op_tbl_wt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave_raw
{
public:
  explicit Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave_raw(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave wrw_tbl_wk_tbl_result_weight_ave_raw(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_wrw_tbl_wk_tbl_result_weight_ave_raw_type arg)
  {
    msg_.wrw_tbl_wk_tbl_result_weight_ave_raw = std::move(arg);
    return Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_linkage_movement_tilt
{
public:
  explicit Init_LpsSaWeighDebugChannel_linkage_movement_tilt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave_raw linkage_movement_tilt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_linkage_movement_tilt_type arg)
  {
    msg_.linkage_movement_tilt = std::move(arg);
    return Init_LpsSaWeighDebugChannel_wrw_tbl_wk_tbl_result_weight_ave_raw(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_linkage_movement_lift
{
public:
  explicit Init_LpsSaWeighDebugChannel_linkage_movement_lift(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_linkage_movement_tilt linkage_movement_lift(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_linkage_movement_lift_type arg)
  {
    msg_.linkage_movement_lift = std::move(arg);
    return Init_LpsSaWeighDebugChannel_linkage_movement_tilt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_lps_stall_detect_lift_stalled
{
public:
  explicit Init_LpsSaWeighDebugChannel_lps_stall_detect_lift_stalled(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_linkage_movement_lift lps_stall_detect_lift_stalled(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_lps_stall_detect_lift_stalled_type arg)
  {
    msg_.lps_stall_detect_lift_stalled = std::move(arg);
    return Init_LpsSaWeighDebugChannel_linkage_movement_lift(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_dump_state_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_dump_state_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_lps_stall_detect_lift_stalled dump_state_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_dump_state_status_type arg)
  {
    msg_.dump_state_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_lps_stall_detect_lift_stalled(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_low_lift_wt_variance_est
{
public:
  explicit Init_LpsSaWeighDebugChannel_low_lift_wt_variance_est(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_dump_state_status low_lift_wt_variance_est(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_low_lift_wt_variance_est_type arg)
  {
    msg_.low_lift_wt_variance_est = std::move(arg);
    return Init_LpsSaWeighDebugChannel_dump_state_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_low_lift_wt_stdev_est
{
public:
  explicit Init_LpsSaWeighDebugChannel_low_lift_wt_stdev_est(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_low_lift_wt_variance_est low_lift_wt_stdev_est(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_low_lift_wt_stdev_est_type arg)
  {
    msg_.low_lift_wt_stdev_est = std::move(arg);
    return Init_LpsSaWeighDebugChannel_low_lift_wt_variance_est(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_low_lift_wt_stat
{
public:
  explicit Init_LpsSaWeighDebugChannel_low_lift_wt_stat(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_low_lift_wt_stdev_est low_lift_wt_stat(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_low_lift_wt_stat_type arg)
  {
    msg_.low_lift_wt_stat = std::move(arg);
    return Init_LpsSaWeighDebugChannel_low_lift_wt_stdev_est(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_low_lift_wt_mean_est_comp
{
public:
  explicit Init_LpsSaWeighDebugChannel_low_lift_wt_mean_est_comp(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_low_lift_wt_stat low_lift_wt_mean_est_comp(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_low_lift_wt_mean_est_comp_type arg)
  {
    msg_.low_lift_wt_mean_est_comp = std::move(arg);
    return Init_LpsSaWeighDebugChannel_low_lift_wt_stat(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_low_lift_wt_mean_est
{
public:
  explicit Init_LpsSaWeighDebugChannel_low_lift_wt_mean_est(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_low_lift_wt_mean_est_comp low_lift_wt_mean_est(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_low_lift_wt_mean_est_type arg)
  {
    msg_.low_lift_wt_mean_est = std::move(arg);
    return Init_LpsSaWeighDebugChannel_low_lift_wt_mean_est_comp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_low_lift_wt_last_input
{
public:
  explicit Init_LpsSaWeighDebugChannel_low_lift_wt_last_input(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_low_lift_wt_mean_est low_lift_wt_last_input(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_low_lift_wt_last_input_type arg)
  {
    msg_.low_lift_wt_last_input = std::move(arg);
    return Init_LpsSaWeighDebugChannel_low_lift_wt_mean_est(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_low_lift_wt_confidence_timer
{
public:
  explicit Init_LpsSaWeighDebugChannel_low_lift_wt_confidence_timer(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_low_lift_wt_last_input low_lift_wt_confidence_timer(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_low_lift_wt_confidence_timer_type arg)
  {
    msg_.low_lift_wt_confidence_timer = std::move(arg);
    return Init_LpsSaWeighDebugChannel_low_lift_wt_last_input(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_low_lift_wt_confidence_est
{
public:
  explicit Init_LpsSaWeighDebugChannel_low_lift_wt_confidence_est(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_low_lift_wt_confidence_timer low_lift_wt_confidence_est(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_low_lift_wt_confidence_est_type arg)
  {
    msg_.low_lift_wt_confidence_est = std::move(arg);
    return Init_LpsSaWeighDebugChannel_low_lift_wt_confidence_timer(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_low_lift_wt_confidence
{
public:
  explicit Init_LpsSaWeighDebugChannel_low_lift_wt_confidence(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_low_lift_wt_confidence_est low_lift_wt_confidence(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_low_lift_wt_confidence_type arg)
  {
    msg_.low_lift_wt_confidence = std::move(arg);
    return Init_LpsSaWeighDebugChannel_low_lift_wt_confidence_est(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_low_lift_wt_wt
{
public:
  explicit Init_LpsSaWeighDebugChannel_low_lift_wt_wt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_low_lift_wt_confidence low_lift_wt_wt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_low_lift_wt_wt_type arg)
  {
    msg_.low_lift_wt_wt = std::move(arg);
    return Init_LpsSaWeighDebugChannel_low_lift_wt_confidence(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_live_weigh_tbl_use_fast_filter
{
public:
  explicit Init_LpsSaWeighDebugChannel_live_weigh_tbl_use_fast_filter(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_low_lift_wt_wt live_weigh_tbl_use_fast_filter(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_live_weigh_tbl_use_fast_filter_type arg)
  {
    msg_.live_weigh_tbl_use_fast_filter = std::move(arg);
    return Init_LpsSaWeighDebugChannel_low_lift_wt_wt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_live_weigh_tbl_wt
{
public:
  explicit Init_LpsSaWeighDebugChannel_live_weigh_tbl_wt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_live_weigh_tbl_use_fast_filter live_weigh_tbl_wt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_live_weigh_tbl_wt_type arg)
  {
    msg_.live_weigh_tbl_wt = std::move(arg);
    return Init_LpsSaWeighDebugChannel_live_weigh_tbl_use_fast_filter(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_live_weigh_tbl_stat
{
public:
  explicit Init_LpsSaWeighDebugChannel_live_weigh_tbl_stat(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_live_weigh_tbl_wt live_weigh_tbl_stat(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_live_weigh_tbl_stat_type arg)
  {
    msg_.live_weigh_tbl_stat = std::move(arg);
    return Init_LpsSaWeighDebugChannel_live_weigh_tbl_wt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_lift_cyl_pressure_imu_adjusted
{
public:
  explicit Init_LpsSaWeighDebugChannel_lift_cyl_pressure_imu_adjusted(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_live_weigh_tbl_stat lift_cyl_pressure_imu_adjusted(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_lift_cyl_pressure_imu_adjusted_type arg)
  {
    msg_.lift_cyl_pressure_imu_adjusted = std::move(arg);
    return Init_LpsSaWeighDebugChannel_live_weigh_tbl_stat(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_lift_cyl_pressure_v0
{
public:
  explicit Init_LpsSaWeighDebugChannel_lift_cyl_pressure_v0(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_lift_cyl_pressure_imu_adjusted lift_cyl_pressure_v0(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_lift_cyl_pressure_v0_type arg)
  {
    msg_.lift_cyl_pressure_v0 = std::move(arg);
    return Init_LpsSaWeighDebugChannel_lift_cyl_pressure_imu_adjusted(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_lift_cyl_pressure
{
public:
  explicit Init_LpsSaWeighDebugChannel_lift_cyl_pressure(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_lift_cyl_pressure_v0 lift_cyl_pressure(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_lift_cyl_pressure_type arg)
  {
    msg_.lift_cyl_pressure = std::move(arg);
    return Init_LpsSaWeighDebugChannel_lift_cyl_pressure_v0(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_inst_wt_raw_post_tilt_comp
{
public:
  explicit Init_LpsSaWeighDebugChannel_inst_wt_raw_post_tilt_comp(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_lift_cyl_pressure inst_wt_raw_post_tilt_comp(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_inst_wt_raw_post_tilt_comp_type arg)
  {
    msg_.inst_wt_raw_post_tilt_comp = std::move(arg);
    return Init_LpsSaWeighDebugChannel_lift_cyl_pressure(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_inst_wt_raw_pre_tilt_comp
{
public:
  explicit Init_LpsSaWeighDebugChannel_inst_wt_raw_pre_tilt_comp(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_inst_wt_raw_post_tilt_comp inst_wt_raw_pre_tilt_comp(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_inst_wt_raw_pre_tilt_comp_type arg)
  {
    msg_.inst_wt_raw_pre_tilt_comp = std::move(arg);
    return Init_LpsSaWeighDebugChannel_inst_wt_raw_post_tilt_comp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_inst_wt_raw
{
public:
  explicit Init_LpsSaWeighDebugChannel_inst_wt_raw(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_inst_wt_raw_pre_tilt_comp inst_wt_raw(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_inst_wt_raw_type arg)
  {
    msg_.inst_wt_raw = std::move(arg);
    return Init_LpsSaWeighDebugChannel_inst_wt_raw_pre_tilt_comp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_inst_wt_llw_filt
{
public:
  explicit Init_LpsSaWeighDebugChannel_inst_wt_llw_filt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_inst_wt_raw inst_wt_llw_filt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_inst_wt_llw_filt_type arg)
  {
    msg_.inst_wt_llw_filt = std::move(arg);
    return Init_LpsSaWeighDebugChannel_inst_wt_raw(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_inst_wt_filt
{
public:
  explicit Init_LpsSaWeighDebugChannel_inst_wt_filt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_inst_wt_llw_filt inst_wt_filt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_inst_wt_filt_type arg)
  {
    msg_.inst_wt_filt = std::move(arg);
    return Init_LpsSaWeighDebugChannel_inst_wt_llw_filt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_inst_wt_der
{
public:
  explicit Init_LpsSaWeighDebugChannel_inst_wt_der(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_inst_wt_filt inst_wt_der(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_inst_wt_der_type arg)
  {
    msg_.inst_wt_der = std::move(arg);
    return Init_LpsSaWeighDebugChannel_inst_wt_filt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_dump_wt_change_data_dump_cumulative_wt_change
{
public:
  explicit Init_LpsSaWeighDebugChannel_dump_wt_change_data_dump_cumulative_wt_change(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_inst_wt_der dump_wt_change_data_dump_cumulative_wt_change(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_dump_wt_change_data_dump_cumulative_wt_change_type arg)
  {
    msg_.dump_wt_change_data_dump_cumulative_wt_change = std::move(arg);
    return Init_LpsSaWeighDebugChannel_inst_wt_der(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_dig_detect_data_wt_stabilized
{
public:
  explicit Init_LpsSaWeighDebugChannel_dig_detect_data_wt_stabilized(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_dump_wt_change_data_dump_cumulative_wt_change dig_detect_data_wt_stabilized(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_dig_detect_data_wt_stabilized_type arg)
  {
    msg_.dig_detect_data_wt_stabilized = std::move(arg);
    return Init_LpsSaWeighDebugChannel_dump_wt_change_data_dump_cumulative_wt_change(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_dig_detect_data_dig_state
{
public:
  explicit Init_LpsSaWeighDebugChannel_dig_detect_data_dig_state(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_dig_detect_data_wt_stabilized dig_detect_data_dig_state(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_dig_detect_data_dig_state_type arg)
  {
    msg_.dig_detect_data_dig_state = std::move(arg);
    return Init_LpsSaWeighDebugChannel_dig_detect_data_wt_stabilized(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_dig_detect_data_dig_started
{
public:
  explicit Init_LpsSaWeighDebugChannel_dig_detect_data_dig_started(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_dig_detect_data_dig_state dig_detect_data_dig_started(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_dig_detect_data_dig_started_type arg)
  {
    msg_.dig_detect_data_dig_started = std::move(arg);
    return Init_LpsSaWeighDebugChannel_dig_detect_data_dig_state(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_dig_detect_data_dig_duration
{
public:
  explicit Init_LpsSaWeighDebugChannel_dig_detect_data_dig_duration(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_dig_detect_data_dig_started dig_detect_data_dig_duration(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_dig_detect_data_dig_duration_type arg)
  {
    msg_.dig_detect_data_dig_duration = std::move(arg);
    return Init_LpsSaWeighDebugChannel_dig_detect_data_dig_started(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_dig_detect_data_dig_detected
{
public:
  explicit Init_LpsSaWeighDebugChannel_dig_detect_data_dig_detected(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_dig_detect_data_dig_duration dig_detect_data_dig_detected(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_dig_detect_data_dig_detected_type arg)
  {
    msg_.dig_detect_data_dig_detected = std::move(arg);
    return Init_LpsSaWeighDebugChannel_dig_detect_data_dig_duration(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_cyl_flow_const_lift_re_to_he_flow_ratio
{
public:
  explicit Init_LpsSaWeighDebugChannel_cyl_flow_const_lift_re_to_he_flow_ratio(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_dig_detect_data_dig_detected cyl_flow_const_lift_re_to_he_flow_ratio(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_cyl_flow_const_lift_re_to_he_flow_ratio_type arg)
  {
    msg_.cyl_flow_const_lift_re_to_he_flow_ratio = std::move(arg);
    return Init_LpsSaWeighDebugChannel_dig_detect_data_dig_detected(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_cyl_flow_const_lift_he_flow_const
{
public:
  explicit Init_LpsSaWeighDebugChannel_cyl_flow_const_lift_he_flow_const(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_cyl_flow_const_lift_re_to_he_flow_ratio cyl_flow_const_lift_he_flow_const(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_cyl_flow_const_lift_he_flow_const_type arg)
  {
    msg_.cyl_flow_const_lift_he_flow_const = std::move(arg);
    return Init_LpsSaWeighDebugChannel_cyl_flow_const_lift_re_to_he_flow_ratio(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_best_bkt_wt_tipoff_live_weight_in_use
{
public:
  explicit Init_LpsSaWeighDebugChannel_best_bkt_wt_tipoff_live_weight_in_use(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_cyl_flow_const_lift_he_flow_const best_bkt_wt_tipoff_live_weight_in_use(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_best_bkt_wt_tipoff_live_weight_in_use_type arg)
  {
    msg_.best_bkt_wt_tipoff_live_weight_in_use = std::move(arg);
    return Init_LpsSaWeighDebugChannel_cyl_flow_const_lift_he_flow_const(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_best_bkt_wt_wt
{
public:
  explicit Init_LpsSaWeighDebugChannel_best_bkt_wt_wt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_best_bkt_wt_tipoff_live_weight_in_use best_bkt_wt_wt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_best_bkt_wt_wt_type arg)
  {
    msg_.best_bkt_wt_wt = std::move(arg);
    return Init_LpsSaWeighDebugChannel_best_bkt_wt_tipoff_live_weight_in_use(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_best_bkt_wt_payload_calc_meth
{
public:
  explicit Init_LpsSaWeighDebugChannel_best_bkt_wt_payload_calc_meth(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_best_bkt_wt_wt best_bkt_wt_payload_calc_meth(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_best_bkt_wt_payload_calc_meth_type arg)
  {
    msg_.best_bkt_wt_payload_calc_meth = std::move(arg);
    return Init_LpsSaWeighDebugChannel_best_bkt_wt_wt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_weigh_updt_pass_count
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_weigh_updt_pass_count(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_best_bkt_wt_payload_calc_meth debug_weigh_updt_pass_count(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_weigh_updt_pass_count_type arg)
  {
    msg_.debug_weigh_updt_pass_count = std::move(arg);
    return Init_LpsSaWeighDebugChannel_best_bkt_wt_payload_calc_meth(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_weigh_updt_clock_keyon_sec
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_weigh_updt_clock_keyon_sec(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_weigh_updt_pass_count debug_weigh_updt_clock_keyon_sec(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_weigh_updt_clock_keyon_sec_type arg)
  {
    msg_.debug_weigh_updt_clock_keyon_sec = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_weigh_updt_pass_count(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_weigh_updt_loader_bkt_payld_trgt_wt
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_weigh_updt_loader_bkt_payld_trgt_wt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_weigh_updt_clock_keyon_sec debug_weigh_updt_loader_bkt_payld_trgt_wt(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_weigh_updt_loader_bkt_payld_trgt_wt_type arg)
  {
    msg_.debug_weigh_updt_loader_bkt_payld_trgt_wt = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_weigh_updt_clock_keyon_sec(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_requested_gear_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_requested_gear_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_weigh_updt_loader_bkt_payld_trgt_wt debug_requested_gear_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_requested_gear_status_type arg)
  {
    msg_.debug_requested_gear_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_weigh_updt_loader_bkt_payld_trgt_wt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_requested_gear
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_requested_gear(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_requested_gear_status debug_requested_gear(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_requested_gear_type arg)
  {
    msg_.debug_requested_gear = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_requested_gear_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_hyd_oil_temp_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_hyd_oil_temp_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_requested_gear debug_hyd_oil_temp_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_hyd_oil_temp_status_type arg)
  {
    msg_.debug_hyd_oil_temp_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_requested_gear(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_hyd_oil_temp
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_hyd_oil_temp(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_hyd_oil_temp_status debug_hyd_oil_temp(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_hyd_oil_temp_type arg)
  {
    msg_.debug_hyd_oil_temp = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_hyd_oil_temp_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_bucket_angle_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_bucket_angle_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_hyd_oil_temp debug_bucket_angle_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_bucket_angle_status_type arg)
  {
    msg_.debug_bucket_angle_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_hyd_oil_temp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_bucket_angle
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_bucket_angle(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_bucket_angle_status debug_bucket_angle(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_bucket_angle_type arg)
  {
    msg_.debug_bucket_angle = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_bucket_angle_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_position_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_position_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_bucket_angle debug_tilt_position_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_position_status_type arg)
  {
    msg_.debug_tilt_position_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_bucket_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_angle_abc
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_angle_abc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_position_status debug_tilt_angle_abc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_angle_abc_type arg)
  {
    msg_.debug_tilt_angle_abc = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_position_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_angle
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_angle(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_angle_abc debug_tilt_angle(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_angle_type arg)
  {
    msg_.debug_tilt_angle = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_angle_abc(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_vel
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_vel(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_angle debug_tilt_cyl_vel(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_vel_type arg)
  {
    msg_.debug_tilt_cyl_vel = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_norm_len
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_norm_len(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_vel debug_tilt_cyl_norm_len(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_norm_len_type arg)
  {
    msg_.debug_tilt_cyl_norm_len = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_vel(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_raw_len
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_raw_len(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_norm_len debug_tilt_cyl_raw_len(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_raw_len_type arg)
  {
    msg_.debug_tilt_cyl_raw_len = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_norm_len(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_dc
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_raw_len debug_tilt_cyl_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_dc_type arg)
  {
    msg_.debug_tilt_cyl_dc = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_raw_len(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_width
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_dc debug_tilt_cyl_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_width_type arg)
  {
    msg_.debug_tilt_cyl_width = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_dc(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_period
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_width debug_tilt_cyl_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_period_type arg)
  {
    msg_.debug_tilt_cyl_period = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_width(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_position_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_position_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_period debug_lift_position_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_position_status_type arg)
  {
    msg_.debug_lift_position_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_period(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_ang_vel
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_ang_vel(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_position_status debug_lift_ang_vel(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_ang_vel_type arg)
  {
    msg_.debug_lift_ang_vel = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_position_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_angle
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_angle(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_ang_vel debug_lift_angle(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_angle_type arg)
  {
    msg_.debug_lift_angle = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_ang_vel(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_vel
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_vel(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_angle debug_lift_cyl_vel(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_vel_type arg)
  {
    msg_.debug_lift_cyl_vel = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_norm_len
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_norm_len(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_vel debug_lift_cyl_norm_len(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_norm_len_type arg)
  {
    msg_.debug_lift_cyl_norm_len = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_vel(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_filt_ext
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_filt_ext(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_norm_len debug_lift_cyl_filt_ext(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_filt_ext_type arg)
  {
    msg_.debug_lift_cyl_filt_ext = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_norm_len(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_raw_ext
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_raw_ext(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_filt_ext debug_lift_cyl_raw_ext(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_raw_ext_type arg)
  {
    msg_.debug_lift_cyl_raw_ext = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_filt_ext(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_dc
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_raw_ext debug_lift_cyl_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_dc_type arg)
  {
    msg_.debug_lift_cyl_dc = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_raw_ext(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_width
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_dc debug_lift_cyl_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_width_type arg)
  {
    msg_.debug_lift_cyl_width = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_dc(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_period
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_width debug_lift_cyl_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_period_type arg)
  {
    msg_.debug_lift_cyl_period = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_width(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_press_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_press_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_period debug_tilt_cyl_re_press_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_re_press_status_type arg)
  {
    msg_.debug_tilt_cyl_re_press_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_period(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_press
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_press(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_press_status debug_tilt_cyl_re_press(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_re_press_type arg)
  {
    msg_.debug_tilt_cyl_re_press = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_press_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_dc
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_press debug_tilt_cyl_re_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_re_dc_type arg)
  {
    msg_.debug_tilt_cyl_re_dc = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_press(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_width
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_dc debug_tilt_cyl_re_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_re_width_type arg)
  {
    msg_.debug_tilt_cyl_re_width = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_dc(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_period
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_width debug_tilt_cyl_re_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_re_period_type arg)
  {
    msg_.debug_tilt_cyl_re_period = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_width(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_press_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_press_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_period debug_tilt_cyl_he_press_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_he_press_status_type arg)
  {
    msg_.debug_tilt_cyl_he_press_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_re_period(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_press
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_press(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_press_status debug_tilt_cyl_he_press(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_he_press_type arg)
  {
    msg_.debug_tilt_cyl_he_press = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_press_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_dc
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_press debug_tilt_cyl_he_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_he_dc_type arg)
  {
    msg_.debug_tilt_cyl_he_dc = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_press(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_width
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_dc debug_tilt_cyl_he_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_he_width_type arg)
  {
    msg_.debug_tilt_cyl_he_width = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_dc(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_period
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_width debug_tilt_cyl_he_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_tilt_cyl_he_period_type arg)
  {
    msg_.debug_tilt_cyl_he_period = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_width(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_press_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_press_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_period debug_lift_cyl_re_press_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_re_press_status_type arg)
  {
    msg_.debug_lift_cyl_re_press_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_tilt_cyl_he_period(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_press
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_press(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_press_status debug_lift_cyl_re_press(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_re_press_type arg)
  {
    msg_.debug_lift_cyl_re_press = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_press_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_dc
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_press debug_lift_cyl_re_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_re_dc_type arg)
  {
    msg_.debug_lift_cyl_re_dc = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_press(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_width
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_dc debug_lift_cyl_re_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_re_width_type arg)
  {
    msg_.debug_lift_cyl_re_width = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_dc(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_period
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_width debug_lift_cyl_re_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_re_period_type arg)
  {
    msg_.debug_lift_cyl_re_period = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_width(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_press_status
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_press_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_period debug_lift_cyl_he_press_status(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_he_press_status_type arg)
  {
    msg_.debug_lift_cyl_he_press_status = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_re_period(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_press
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_press(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_press_status debug_lift_cyl_he_press(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_he_press_type arg)
  {
    msg_.debug_lift_cyl_he_press = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_press_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_dc
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_press debug_lift_cyl_he_dc(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_he_dc_type arg)
  {
    msg_.debug_lift_cyl_he_dc = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_press(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_width
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_dc debug_lift_cyl_he_width(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_he_width_type arg)
  {
    msg_.debug_lift_cyl_he_width = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_dc(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_period
{
public:
  explicit Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_width debug_lift_cyl_he_period(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_debug_lift_cyl_he_period_type arg)
  {
    msg_.debug_lift_cyl_he_period = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_width(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

class Init_LpsSaWeighDebugChannel_reweigh_warn
{
public:
  Init_LpsSaWeighDebugChannel_reweigh_warn()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_period reweigh_warn(::weigh_app_interfaces::msg::LpsSaWeighDebugChannel::_reweigh_warn_type arg)
  {
    msg_.reweigh_warn = std::move(arg);
    return Init_LpsSaWeighDebugChannel_debug_lift_cyl_he_period(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaWeighDebugChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaWeighDebugChannel>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaWeighDebugChannel_reweigh_warn();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__BUILDER_HPP_
