// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/TipoffAssistInputs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_assist_inputs.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/tipoff_assist_inputs__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_TipoffAssistInputs_friction_offset
{
public:
  explicit Init_TipoffAssistInputs_friction_offset(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::TipoffAssistInputs friction_offset(::weigh_app_interfaces::msg::TipoffAssistInputs::_friction_offset_type arg)
  {
    msg_.friction_offset = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_friction_mu
{
public:
  explicit Init_TipoffAssistInputs_friction_mu(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_friction_offset friction_mu(::weigh_app_interfaces::msg::TipoffAssistInputs::_friction_mu_type arg)
  {
    msg_.friction_mu = std::move(arg);
    return Init_TipoffAssistInputs_friction_offset(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_tilt_norm_length
{
public:
  explicit Init_TipoffAssistInputs_tilt_norm_length(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_friction_mu tilt_norm_length(::weigh_app_interfaces::msg::TipoffAssistInputs::_tilt_norm_length_type arg)
  {
    msg_.tilt_norm_length = std::move(arg);
    return Init_TipoffAssistInputs_friction_mu(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_tilt_norm_angle
{
public:
  explicit Init_TipoffAssistInputs_tilt_norm_angle(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_tilt_norm_length tilt_norm_angle(::weigh_app_interfaces::msg::TipoffAssistInputs::_tilt_norm_angle_type arg)
  {
    msg_.tilt_norm_angle = std::move(arg);
    return Init_TipoffAssistInputs_tilt_norm_length(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_lift_norm_length
{
public:
  explicit Init_TipoffAssistInputs_lift_norm_length(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_tilt_norm_angle lift_norm_length(::weigh_app_interfaces::msg::TipoffAssistInputs::_lift_norm_length_type arg)
  {
    msg_.lift_norm_length = std::move(arg);
    return Init_TipoffAssistInputs_tilt_norm_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_lift_norm_angle
{
public:
  explicit Init_TipoffAssistInputs_lift_norm_angle(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_lift_norm_length lift_norm_angle(::weigh_app_interfaces::msg::TipoffAssistInputs::_lift_norm_angle_type arg)
  {
    msg_.lift_norm_angle = std::move(arg);
    return Init_TipoffAssistInputs_lift_norm_length(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_pass_count
{
public:
  explicit Init_TipoffAssistInputs_pass_count(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_lift_norm_angle pass_count(::weigh_app_interfaces::msg::TipoffAssistInputs::_pass_count_type arg)
  {
    msg_.pass_count = std::move(arg);
    return Init_TipoffAssistInputs_lift_norm_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_anchor_factor
{
public:
  explicit Init_TipoffAssistInputs_anchor_factor(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_pass_count anchor_factor(::weigh_app_interfaces::msg::TipoffAssistInputs::_anchor_factor_type arg)
  {
    msg_.anchor_factor = std::move(arg);
    return Init_TipoffAssistInputs_pass_count(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_anchor_zero_offset
{
public:
  explicit Init_TipoffAssistInputs_anchor_zero_offset(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_anchor_factor anchor_zero_offset(::weigh_app_interfaces::msg::TipoffAssistInputs::_anchor_zero_offset_type arg)
  {
    msg_.anchor_zero_offset = std::move(arg);
    return Init_TipoffAssistInputs_anchor_factor(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_bucket_angle
{
public:
  explicit Init_TipoffAssistInputs_bucket_angle(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_anchor_zero_offset bucket_angle(::weigh_app_interfaces::msg::TipoffAssistInputs::_bucket_angle_type arg)
  {
    msg_.bucket_angle = std::move(arg);
    return Init_TipoffAssistInputs_anchor_zero_offset(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_unlatch_trigger
{
public:
  explicit Init_TipoffAssistInputs_unlatch_trigger(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_bucket_angle unlatch_trigger(::weigh_app_interfaces::msg::TipoffAssistInputs::_unlatch_trigger_type arg)
  {
    msg_.unlatch_trigger = std::move(arg);
    return Init_TipoffAssistInputs_bucket_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_mach_pitch_cal_offset
{
public:
  explicit Init_TipoffAssistInputs_mach_pitch_cal_offset(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_unlatch_trigger mach_pitch_cal_offset(::weigh_app_interfaces::msg::TipoffAssistInputs::_mach_pitch_cal_offset_type arg)
  {
    msg_.mach_pitch_cal_offset = std::move(arg);
    return Init_TipoffAssistInputs_unlatch_trigger(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_simple_cal_factor
{
public:
  explicit Init_TipoffAssistInputs_simple_cal_factor(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_mach_pitch_cal_offset simple_cal_factor(::weigh_app_interfaces::msg::TipoffAssistInputs::_simple_cal_factor_type arg)
  {
    msg_.simple_cal_factor = std::move(arg);
    return Init_TipoffAssistInputs_mach_pitch_cal_offset(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_zero_offset
{
public:
  explicit Init_TipoffAssistInputs_zero_offset(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_simple_cal_factor zero_offset(::weigh_app_interfaces::msg::TipoffAssistInputs::_zero_offset_type arg)
  {
    msg_.zero_offset = std::move(arg);
    return Init_TipoffAssistInputs_simple_cal_factor(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_tipoff_mode
{
public:
  explicit Init_TipoffAssistInputs_tipoff_mode(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_zero_offset tipoff_mode(::weigh_app_interfaces::msg::TipoffAssistInputs::_tipoff_mode_type arg)
  {
    msg_.tipoff_mode = std::move(arg);
    return Init_TipoffAssistInputs_zero_offset(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_bucket_current_weight
{
public:
  explicit Init_TipoffAssistInputs_bucket_current_weight(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_tipoff_mode bucket_current_weight(::weigh_app_interfaces::msg::TipoffAssistInputs::_bucket_current_weight_type arg)
  {
    msg_.bucket_current_weight = std::move(arg);
    return Init_TipoffAssistInputs_tipoff_mode(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_bucket_current_weight_accuracy
{
public:
  explicit Init_TipoffAssistInputs_bucket_current_weight_accuracy(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_bucket_current_weight bucket_current_weight_accuracy(::weigh_app_interfaces::msg::TipoffAssistInputs::_bucket_current_weight_accuracy_type arg)
  {
    msg_.bucket_current_weight_accuracy = std::move(arg);
    return Init_TipoffAssistInputs_bucket_current_weight(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_truck_start_weight
{
public:
  explicit Init_TipoffAssistInputs_truck_start_weight(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_bucket_current_weight_accuracy truck_start_weight(::weigh_app_interfaces::msg::TipoffAssistInputs::_truck_start_weight_type arg)
  {
    msg_.truck_start_weight = std::move(arg);
    return Init_TipoffAssistInputs_bucket_current_weight_accuracy(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_truck_target_wt
{
public:
  explicit Init_TipoffAssistInputs_truck_target_wt(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_truck_start_weight truck_target_wt(::weigh_app_interfaces::msg::TipoffAssistInputs::_truck_target_wt_type arg)
  {
    msg_.truck_target_wt = std::move(arg);
    return Init_TipoffAssistInputs_truck_start_weight(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_tool_mass
{
public:
  explicit Init_TipoffAssistInputs_tool_mass(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_truck_target_wt tool_mass(::weigh_app_interfaces::msg::TipoffAssistInputs::_tool_mass_type arg)
  {
    msg_.tool_mass = std::move(arg);
    return Init_TipoffAssistInputs_truck_target_wt(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_steering_angle
{
public:
  explicit Init_TipoffAssistInputs_steering_angle(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_tool_mass steering_angle(::weigh_app_interfaces::msg::TipoffAssistInputs::_steering_angle_type arg)
  {
    msg_.steering_angle = std::move(arg);
    return Init_TipoffAssistInputs_tool_mass(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_eef_imu_accel_z
{
public:
  explicit Init_TipoffAssistInputs_eef_imu_accel_z(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_steering_angle eef_imu_accel_z(::weigh_app_interfaces::msg::TipoffAssistInputs::_eef_imu_accel_z_type arg)
  {
    msg_.eef_imu_accel_z = std::move(arg);
    return Init_TipoffAssistInputs_steering_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_eef_imu_accel_y
{
public:
  explicit Init_TipoffAssistInputs_eef_imu_accel_y(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_eef_imu_accel_z eef_imu_accel_y(::weigh_app_interfaces::msg::TipoffAssistInputs::_eef_imu_accel_y_type arg)
  {
    msg_.eef_imu_accel_y = std::move(arg);
    return Init_TipoffAssistInputs_eef_imu_accel_z(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_eef_imu_accel_x
{
public:
  explicit Init_TipoffAssistInputs_eef_imu_accel_x(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_eef_imu_accel_y eef_imu_accel_x(::weigh_app_interfaces::msg::TipoffAssistInputs::_eef_imu_accel_x_type arg)
  {
    msg_.eef_imu_accel_x = std::move(arg);
    return Init_TipoffAssistInputs_eef_imu_accel_y(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_tilt_re_pressure
{
public:
  explicit Init_TipoffAssistInputs_tilt_re_pressure(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_eef_imu_accel_x tilt_re_pressure(::weigh_app_interfaces::msg::TipoffAssistInputs::_tilt_re_pressure_type arg)
  {
    msg_.tilt_re_pressure = std::move(arg);
    return Init_TipoffAssistInputs_eef_imu_accel_x(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_tilt_he_pressure
{
public:
  explicit Init_TipoffAssistInputs_tilt_he_pressure(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_tilt_re_pressure tilt_he_pressure(::weigh_app_interfaces::msg::TipoffAssistInputs::_tilt_he_pressure_type arg)
  {
    msg_.tilt_he_pressure = std::move(arg);
    return Init_TipoffAssistInputs_tilt_re_pressure(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_lift_re_pressure
{
public:
  explicit Init_TipoffAssistInputs_lift_re_pressure(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_tilt_he_pressure lift_re_pressure(::weigh_app_interfaces::msg::TipoffAssistInputs::_lift_re_pressure_type arg)
  {
    msg_.lift_re_pressure = std::move(arg);
    return Init_TipoffAssistInputs_tilt_he_pressure(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_lift_he_pressure
{
public:
  explicit Init_TipoffAssistInputs_lift_he_pressure(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_lift_re_pressure lift_he_pressure(::weigh_app_interfaces::msg::TipoffAssistInputs::_lift_he_pressure_type arg)
  {
    msg_.lift_he_pressure = std::move(arg);
    return Init_TipoffAssistInputs_lift_re_pressure(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_lift_angle
{
public:
  explicit Init_TipoffAssistInputs_lift_angle(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_lift_he_pressure lift_angle(::weigh_app_interfaces::msg::TipoffAssistInputs::_lift_angle_type arg)
  {
    msg_.lift_angle = std::move(arg);
    return Init_TipoffAssistInputs_lift_he_pressure(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_tilt_extension
{
public:
  explicit Init_TipoffAssistInputs_tilt_extension(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_lift_angle tilt_extension(::weigh_app_interfaces::msg::TipoffAssistInputs::_tilt_extension_type arg)
  {
    msg_.tilt_extension = std::move(arg);
    return Init_TipoffAssistInputs_lift_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_tilt_valve_cmd
{
public:
  explicit Init_TipoffAssistInputs_tilt_valve_cmd(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_tilt_extension tilt_valve_cmd(::weigh_app_interfaces::msg::TipoffAssistInputs::_tilt_valve_cmd_type arg)
  {
    msg_.tilt_valve_cmd = std::move(arg);
    return Init_TipoffAssistInputs_tilt_extension(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_lift_valve_cmd
{
public:
  explicit Init_TipoffAssistInputs_lift_valve_cmd(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_tilt_valve_cmd lift_valve_cmd(::weigh_app_interfaces::msg::TipoffAssistInputs::_lift_valve_cmd_type arg)
  {
    msg_.lift_valve_cmd = std::move(arg);
    return Init_TipoffAssistInputs_tilt_valve_cmd(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_invalidate_outputs
{
public:
  explicit Init_TipoffAssistInputs_invalidate_outputs(::weigh_app_interfaces::msg::TipoffAssistInputs & msg)
  : msg_(msg)
  {}
  Init_TipoffAssistInputs_lift_valve_cmd invalidate_outputs(::weigh_app_interfaces::msg::TipoffAssistInputs::_invalidate_outputs_type arg)
  {
    msg_.invalidate_outputs = std::move(arg);
    return Init_TipoffAssistInputs_lift_valve_cmd(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

class Init_TipoffAssistInputs_input_status
{
public:
  Init_TipoffAssistInputs_input_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TipoffAssistInputs_invalidate_outputs input_status(::weigh_app_interfaces::msg::TipoffAssistInputs::_input_status_type arg)
  {
    msg_.input_status = std::move(arg);
    return Init_TipoffAssistInputs_invalidate_outputs(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TipoffAssistInputs msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::TipoffAssistInputs>()
{
  return weigh_app_interfaces::msg::builder::Init_TipoffAssistInputs_input_status();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__BUILDER_HPP_
