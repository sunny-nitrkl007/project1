// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/Machine.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/machine.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/machine__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_Machine_gps_status
{
public:
  explicit Init_Machine_gps_status(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::Machine gps_status(::weigh_app_interfaces::msg::Machine::_gps_status_type arg)
  {
    msg_.gps_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_gps_longitude
{
public:
  explicit Init_Machine_gps_longitude(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_gps_status gps_longitude(::weigh_app_interfaces::msg::Machine::_gps_longitude_type arg)
  {
    msg_.gps_longitude = std::move(arg);
    return Init_Machine_gps_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_gps_latitude
{
public:
  explicit Init_Machine_gps_latitude(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_gps_longitude gps_latitude(::weigh_app_interfaces::msg::Machine::_gps_latitude_type arg)
  {
    msg_.gps_latitude = std::move(arg);
    return Init_Machine_gps_longitude(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_external_force_normalized
{
public:
  explicit Init_Machine_external_force_normalized(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_gps_latitude external_force_normalized(::weigh_app_interfaces::msg::Machine::_external_force_normalized_type arg)
  {
    msg_.external_force_normalized = std::move(arg);
    return Init_Machine_gps_latitude(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_service_hour_meter
{
public:
  explicit Init_Machine_service_hour_meter(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_external_force_normalized service_hour_meter(::weigh_app_interfaces::msg::Machine::_service_hour_meter_type arg)
  {
    msg_.service_hour_meter = std::move(arg);
    return Init_Machine_external_force_normalized(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_ard_fuel_rate
{
public:
  explicit Init_Machine_ard_fuel_rate(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_service_hour_meter ard_fuel_rate(::weigh_app_interfaces::msg::Machine::_ard_fuel_rate_type arg)
  {
    msg_.ard_fuel_rate = std::move(arg);
    return Init_Machine_service_hour_meter(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_fuel_rate
{
public:
  explicit Init_Machine_fuel_rate(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_ard_fuel_rate fuel_rate(::weigh_app_interfaces::msg::Machine::_fuel_rate_type arg)
  {
    msg_.fuel_rate = std::move(arg);
    return Init_Machine_ard_fuel_rate(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_total_fuel_low_res
{
public:
  explicit Init_Machine_total_fuel_low_res(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_fuel_rate total_fuel_low_res(::weigh_app_interfaces::msg::Machine::_total_fuel_low_res_type arg)
  {
    msg_.total_fuel_low_res = std::move(arg);
    return Init_Machine_fuel_rate(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_total_fuel_high_res
{
public:
  explicit Init_Machine_total_fuel_high_res(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_total_fuel_low_res total_fuel_high_res(::weigh_app_interfaces::msg::Machine::_total_fuel_high_res_type arg)
  {
    msg_.total_fuel_high_res = std::move(arg);
    return Init_Machine_total_fuel_low_res(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_timezone_offset
{
public:
  explicit Init_Machine_timezone_offset(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_total_fuel_high_res timezone_offset(::weigh_app_interfaces::msg::Machine::_timezone_offset_type arg)
  {
    msg_.timezone_offset = std::move(arg);
    return Init_Machine_total_fuel_high_res(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_real_time_status
{
public:
  explicit Init_Machine_real_time_status(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_timezone_offset real_time_status(::weigh_app_interfaces::msg::Machine::_real_time_status_type arg)
  {
    msg_.real_time_status = std::move(arg);
    return Init_Machine_timezone_offset(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_real_time
{
public:
  explicit Init_Machine_real_time(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_real_time_status real_time(::weigh_app_interfaces::msg::Machine::_real_time_type arg)
  {
    msg_.real_time = std::move(arg);
    return Init_Machine_real_time_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_keyswitch_state
{
public:
  explicit Init_Machine_keyswitch_state(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_real_time keyswitch_state(::weigh_app_interfaces::msg::Machine::_keyswitch_state_type arg)
  {
    msg_.keyswitch_state = std::move(arg);
    return Init_Machine_real_time(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_torque_converter_speed
{
public:
  explicit Init_Machine_torque_converter_speed(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_keyswitch_state torque_converter_speed(::weigh_app_interfaces::msg::Machine::_torque_converter_speed_type arg)
  {
    msg_.torque_converter_speed = std::move(arg);
    return Init_Machine_keyswitch_state(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_engine_speed
{
public:
  explicit Init_Machine_engine_speed(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_torque_converter_speed engine_speed(::weigh_app_interfaces::msg::Machine::_engine_speed_type arg)
  {
    msg_.engine_speed = std::move(arg);
    return Init_Machine_torque_converter_speed(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_ground_speed
{
public:
  explicit Init_Machine_ground_speed(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_engine_speed ground_speed(::weigh_app_interfaces::msg::Machine::_ground_speed_type arg)
  {
    msg_.ground_speed = std::move(arg);
    return Init_Machine_engine_speed(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_desired_gear
{
public:
  explicit Init_Machine_desired_gear(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_ground_speed desired_gear(::weigh_app_interfaces::msg::Machine::_desired_gear_type arg)
  {
    msg_.desired_gear = std::move(arg);
    return Init_Machine_ground_speed(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_bucket_payload
{
public:
  explicit Init_Machine_bucket_payload(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_desired_gear bucket_payload(::weigh_app_interfaces::msg::Machine::_bucket_payload_type arg)
  {
    msg_.bucket_payload = std::move(arg);
    return Init_Machine_desired_gear(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_hydarulic_oil_temp
{
public:
  explicit Init_Machine_hydarulic_oil_temp(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_bucket_payload hydarulic_oil_temp(::weigh_app_interfaces::msg::Machine::_hydarulic_oil_temp_type arg)
  {
    msg_.hydarulic_oil_temp = std::move(arg);
    return Init_Machine_bucket_payload(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_lift_cylinder_re_pressure
{
public:
  explicit Init_Machine_lift_cylinder_re_pressure(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_hydarulic_oil_temp lift_cylinder_re_pressure(::weigh_app_interfaces::msg::Machine::_lift_cylinder_re_pressure_type arg)
  {
    msg_.lift_cylinder_re_pressure = std::move(arg);
    return Init_Machine_hydarulic_oil_temp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_lift_cylinder_he_pressure
{
public:
  explicit Init_Machine_lift_cylinder_he_pressure(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_lift_cylinder_re_pressure lift_cylinder_he_pressure(::weigh_app_interfaces::msg::Machine::_lift_cylinder_he_pressure_type arg)
  {
    msg_.lift_cylinder_he_pressure = std::move(arg);
    return Init_Machine_lift_cylinder_re_pressure(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_brake_pedal_position
{
public:
  explicit Init_Machine_brake_pedal_position(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_lift_cylinder_he_pressure brake_pedal_position(::weigh_app_interfaces::msg::Machine::_brake_pedal_position_type arg)
  {
    msg_.brake_pedal_position = std::move(arg);
    return Init_Machine_lift_cylinder_he_pressure(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_raise_solenoid_percent
{
public:
  explicit Init_Machine_raise_solenoid_percent(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_brake_pedal_position raise_solenoid_percent(::weigh_app_interfaces::msg::Machine::_raise_solenoid_percent_type arg)
  {
    msg_.raise_solenoid_percent = std::move(arg);
    return Init_Machine_brake_pedal_position(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_lower_solenoid_percent
{
public:
  explicit Init_Machine_lower_solenoid_percent(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_raise_solenoid_percent lower_solenoid_percent(::weigh_app_interfaces::msg::Machine::_lower_solenoid_percent_type arg)
  {
    msg_.lower_solenoid_percent = std::move(arg);
    return Init_Machine_raise_solenoid_percent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_rack_solenoid_percent
{
public:
  explicit Init_Machine_rack_solenoid_percent(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_lower_solenoid_percent rack_solenoid_percent(::weigh_app_interfaces::msg::Machine::_rack_solenoid_percent_type arg)
  {
    msg_.rack_solenoid_percent = std::move(arg);
    return Init_Machine_lower_solenoid_percent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_dump_solenoid_percent
{
public:
  explicit Init_Machine_dump_solenoid_percent(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_rack_solenoid_percent dump_solenoid_percent(::weigh_app_interfaces::msg::Machine::_dump_solenoid_percent_type arg)
  {
    msg_.dump_solenoid_percent = std::move(arg);
    return Init_Machine_rack_solenoid_percent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_machine_idle_status
{
public:
  explicit Init_Machine_machine_idle_status(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_dump_solenoid_percent machine_idle_status(::weigh_app_interfaces::msg::Machine::_machine_idle_status_type arg)
  {
    msg_.machine_idle_status = std::move(arg);
    return Init_Machine_dump_solenoid_percent(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_impl_operation_status
{
public:
  explicit Init_Machine_impl_operation_status(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_machine_idle_status impl_operation_status(::weigh_app_interfaces::msg::Machine::_impl_operation_status_type arg)
  {
    msg_.impl_operation_status = std::move(arg);
    return Init_Machine_machine_idle_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_tilt_cyl_pos
{
public:
  explicit Init_Machine_tilt_cyl_pos(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_impl_operation_status tilt_cyl_pos(::weigh_app_interfaces::msg::Machine::_tilt_cyl_pos_type arg)
  {
    msg_.tilt_cyl_pos = std::move(arg);
    return Init_Machine_impl_operation_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_tilt_lever_cmd
{
public:
  explicit Init_Machine_tilt_lever_cmd(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_tilt_cyl_pos tilt_lever_cmd(::weigh_app_interfaces::msg::Machine::_tilt_lever_cmd_type arg)
  {
    msg_.tilt_lever_cmd = std::move(arg);
    return Init_Machine_tilt_cyl_pos(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_lift_angle
{
public:
  explicit Init_Machine_lift_angle(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_tilt_lever_cmd lift_angle(::weigh_app_interfaces::msg::Machine::_lift_angle_type arg)
  {
    msg_.lift_angle = std::move(arg);
    return Init_Machine_tilt_lever_cmd(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_bucket_angle
{
public:
  explicit Init_Machine_bucket_angle(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_lift_angle bucket_angle(::weigh_app_interfaces::msg::Machine::_bucket_angle_type arg)
  {
    msg_.bucket_angle = std::move(arg);
    return Init_Machine_lift_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_tilt_valve_cmd
{
public:
  explicit Init_Machine_tilt_valve_cmd(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_bucket_angle tilt_valve_cmd(::weigh_app_interfaces::msg::Machine::_tilt_valve_cmd_type arg)
  {
    msg_.tilt_valve_cmd = std::move(arg);
    return Init_Machine_bucket_angle(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_lift_valve_cmd
{
public:
  explicit Init_Machine_lift_valve_cmd(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_tilt_valve_cmd lift_valve_cmd(::weigh_app_interfaces::msg::Machine::_lift_valve_cmd_type arg)
  {
    msg_.lift_valve_cmd = std::move(arg);
    return Init_Machine_tilt_valve_cmd(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_payload_calc_method
{
public:
  explicit Init_Machine_payload_calc_method(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_lift_valve_cmd payload_calc_method(::weigh_app_interfaces::msg::Machine::_payload_calc_method_type arg)
  {
    msg_.payload_calc_method = std::move(arg);
    return Init_Machine_lift_valve_cmd(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_payload_weight_status
{
public:
  explicit Init_Machine_payload_weight_status(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_payload_calc_method payload_weight_status(::weigh_app_interfaces::msg::Machine::_payload_weight_status_type arg)
  {
    msg_.payload_weight_status = std::move(arg);
    return Init_Machine_payload_calc_method(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_payload_weight
{
public:
  explicit Init_Machine_payload_weight(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_payload_weight_status payload_weight(::weigh_app_interfaces::msg::Machine::_payload_weight_type arg)
  {
    msg_.payload_weight = std::move(arg);
    return Init_Machine_payload_weight_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_payload_ratio_raw_status
{
public:
  explicit Init_Machine_payload_ratio_raw_status(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_payload_weight payload_ratio_raw_status(::weigh_app_interfaces::msg::Machine::_payload_ratio_raw_status_type arg)
  {
    msg_.payload_ratio_raw_status = std::move(arg);
    return Init_Machine_payload_weight(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_payload_ratio_raw
{
public:
  explicit Init_Machine_payload_ratio_raw(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_payload_ratio_raw_status payload_ratio_raw(::weigh_app_interfaces::msg::Machine::_payload_ratio_raw_type arg)
  {
    msg_.payload_ratio_raw = std::move(arg);
    return Init_Machine_payload_ratio_raw_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_payload_ratio_status
{
public:
  explicit Init_Machine_payload_ratio_status(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_payload_ratio_raw payload_ratio_status(::weigh_app_interfaces::msg::Machine::_payload_ratio_status_type arg)
  {
    msg_.payload_ratio_status = std::move(arg);
    return Init_Machine_payload_ratio_raw(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_payload_ratio
{
public:
  explicit Init_Machine_payload_ratio(::weigh_app_interfaces::msg::Machine & msg)
  : msg_(msg)
  {}
  Init_Machine_payload_ratio_status payload_ratio(::weigh_app_interfaces::msg::Machine::_payload_ratio_type arg)
  {
    msg_.payload_ratio = std::move(arg);
    return Init_Machine_payload_ratio_status(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

class Init_Machine_app_number
{
public:
  Init_Machine_app_number()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Machine_payload_ratio app_number(::weigh_app_interfaces::msg::Machine::_app_number_type arg)
  {
    msg_.app_number = std::move(arg);
    return Init_Machine_payload_ratio(msg_);
  }

private:
  ::weigh_app_interfaces::msg::Machine msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::Machine>()
{
  return weigh_app_interfaces::msg::builder::Init_Machine_app_number();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__BUILDER_HPP_
