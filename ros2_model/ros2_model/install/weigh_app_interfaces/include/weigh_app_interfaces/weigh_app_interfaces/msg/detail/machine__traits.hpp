// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/Machine.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/machine.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/machine__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Machine & msg,
  std::ostream & out)
{
  out << "{";
  // member: app_number
  {
    out << "app_number: ";
    rosidl_generator_traits::value_to_yaml(msg.app_number, out);
    out << ", ";
  }

  // member: payload_ratio
  {
    out << "payload_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio, out);
    out << ", ";
  }

  // member: payload_ratio_status
  {
    out << "payload_ratio_status: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio_status, out);
    out << ", ";
  }

  // member: payload_ratio_raw
  {
    out << "payload_ratio_raw: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio_raw, out);
    out << ", ";
  }

  // member: payload_ratio_raw_status
  {
    out << "payload_ratio_raw_status: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio_raw_status, out);
    out << ", ";
  }

  // member: payload_weight
  {
    out << "payload_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_weight, out);
    out << ", ";
  }

  // member: payload_weight_status
  {
    out << "payload_weight_status: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_weight_status, out);
    out << ", ";
  }

  // member: payload_calc_method
  {
    out << "payload_calc_method: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_calc_method, out);
    out << ", ";
  }

  // member: lift_valve_cmd
  {
    out << "lift_valve_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_valve_cmd, out);
    out << ", ";
  }

  // member: tilt_valve_cmd
  {
    out << "tilt_valve_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_valve_cmd, out);
    out << ", ";
  }

  // member: bucket_angle
  {
    out << "bucket_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_angle, out);
    out << ", ";
  }

  // member: lift_angle
  {
    out << "lift_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_angle, out);
    out << ", ";
  }

  // member: tilt_lever_cmd
  {
    out << "tilt_lever_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_lever_cmd, out);
    out << ", ";
  }

  // member: tilt_cyl_pos
  {
    out << "tilt_cyl_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_cyl_pos, out);
    out << ", ";
  }

  // member: impl_operation_status
  {
    out << "impl_operation_status: ";
    rosidl_generator_traits::value_to_yaml(msg.impl_operation_status, out);
    out << ", ";
  }

  // member: machine_idle_status
  {
    out << "machine_idle_status: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_idle_status, out);
    out << ", ";
  }

  // member: dump_solenoid_percent
  {
    out << "dump_solenoid_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.dump_solenoid_percent, out);
    out << ", ";
  }

  // member: rack_solenoid_percent
  {
    out << "rack_solenoid_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.rack_solenoid_percent, out);
    out << ", ";
  }

  // member: lower_solenoid_percent
  {
    out << "lower_solenoid_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.lower_solenoid_percent, out);
    out << ", ";
  }

  // member: raise_solenoid_percent
  {
    out << "raise_solenoid_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_solenoid_percent, out);
    out << ", ";
  }

  // member: brake_pedal_position
  {
    out << "brake_pedal_position: ";
    rosidl_generator_traits::value_to_yaml(msg.brake_pedal_position, out);
    out << ", ";
  }

  // member: lift_cylinder_he_pressure
  {
    out << "lift_cylinder_he_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cylinder_he_pressure, out);
    out << ", ";
  }

  // member: lift_cylinder_re_pressure
  {
    out << "lift_cylinder_re_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cylinder_re_pressure, out);
    out << ", ";
  }

  // member: hydarulic_oil_temp
  {
    out << "hydarulic_oil_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.hydarulic_oil_temp, out);
    out << ", ";
  }

  // member: bucket_payload
  {
    out << "bucket_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_payload, out);
    out << ", ";
  }

  // member: desired_gear
  {
    out << "desired_gear: ";
    rosidl_generator_traits::value_to_yaml(msg.desired_gear, out);
    out << ", ";
  }

  // member: ground_speed
  {
    out << "ground_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.ground_speed, out);
    out << ", ";
  }

  // member: engine_speed
  {
    out << "engine_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.engine_speed, out);
    out << ", ";
  }

  // member: torque_converter_speed
  {
    out << "torque_converter_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.torque_converter_speed, out);
    out << ", ";
  }

  // member: keyswitch_state
  {
    out << "keyswitch_state: ";
    rosidl_generator_traits::value_to_yaml(msg.keyswitch_state, out);
    out << ", ";
  }

  // member: real_time
  {
    out << "real_time: ";
    rosidl_generator_traits::value_to_yaml(msg.real_time, out);
    out << ", ";
  }

  // member: real_time_status
  {
    out << "real_time_status: ";
    rosidl_generator_traits::value_to_yaml(msg.real_time_status, out);
    out << ", ";
  }

  // member: timezone_offset
  {
    out << "timezone_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.timezone_offset, out);
    out << ", ";
  }

  // member: total_fuel_high_res
  {
    out << "total_fuel_high_res: ";
    rosidl_generator_traits::value_to_yaml(msg.total_fuel_high_res, out);
    out << ", ";
  }

  // member: total_fuel_low_res
  {
    out << "total_fuel_low_res: ";
    rosidl_generator_traits::value_to_yaml(msg.total_fuel_low_res, out);
    out << ", ";
  }

  // member: fuel_rate
  {
    out << "fuel_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.fuel_rate, out);
    out << ", ";
  }

  // member: ard_fuel_rate
  {
    out << "ard_fuel_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.ard_fuel_rate, out);
    out << ", ";
  }

  // member: service_hour_meter
  {
    out << "service_hour_meter: ";
    rosidl_generator_traits::value_to_yaml(msg.service_hour_meter, out);
    out << ", ";
  }

  // member: external_force_normalized
  {
    out << "external_force_normalized: ";
    rosidl_generator_traits::value_to_yaml(msg.external_force_normalized, out);
    out << ", ";
  }

  // member: gps_latitude
  {
    out << "gps_latitude: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_latitude, out);
    out << ", ";
  }

  // member: gps_longitude
  {
    out << "gps_longitude: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_longitude, out);
    out << ", ";
  }

  // member: gps_status
  {
    out << "gps_status: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Machine & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: app_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "app_number: ";
    rosidl_generator_traits::value_to_yaml(msg.app_number, out);
    out << "\n";
  }

  // member: payload_ratio
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio, out);
    out << "\n";
  }

  // member: payload_ratio_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_ratio_status: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio_status, out);
    out << "\n";
  }

  // member: payload_ratio_raw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_ratio_raw: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio_raw, out);
    out << "\n";
  }

  // member: payload_ratio_raw_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_ratio_raw_status: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_ratio_raw_status, out);
    out << "\n";
  }

  // member: payload_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_weight, out);
    out << "\n";
  }

  // member: payload_weight_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_weight_status: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_weight_status, out);
    out << "\n";
  }

  // member: payload_calc_method
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_calc_method: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_calc_method, out);
    out << "\n";
  }

  // member: lift_valve_cmd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_valve_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_valve_cmd, out);
    out << "\n";
  }

  // member: tilt_valve_cmd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_valve_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_valve_cmd, out);
    out << "\n";
  }

  // member: bucket_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bucket_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_angle, out);
    out << "\n";
  }

  // member: lift_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_angle, out);
    out << "\n";
  }

  // member: tilt_lever_cmd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_lever_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_lever_cmd, out);
    out << "\n";
  }

  // member: tilt_cyl_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_cyl_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_cyl_pos, out);
    out << "\n";
  }

  // member: impl_operation_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "impl_operation_status: ";
    rosidl_generator_traits::value_to_yaml(msg.impl_operation_status, out);
    out << "\n";
  }

  // member: machine_idle_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "machine_idle_status: ";
    rosidl_generator_traits::value_to_yaml(msg.machine_idle_status, out);
    out << "\n";
  }

  // member: dump_solenoid_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dump_solenoid_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.dump_solenoid_percent, out);
    out << "\n";
  }

  // member: rack_solenoid_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rack_solenoid_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.rack_solenoid_percent, out);
    out << "\n";
  }

  // member: lower_solenoid_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lower_solenoid_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.lower_solenoid_percent, out);
    out << "\n";
  }

  // member: raise_solenoid_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raise_solenoid_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_solenoid_percent, out);
    out << "\n";
  }

  // member: brake_pedal_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "brake_pedal_position: ";
    rosidl_generator_traits::value_to_yaml(msg.brake_pedal_position, out);
    out << "\n";
  }

  // member: lift_cylinder_he_pressure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_cylinder_he_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cylinder_he_pressure, out);
    out << "\n";
  }

  // member: lift_cylinder_re_pressure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_cylinder_re_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cylinder_re_pressure, out);
    out << "\n";
  }

  // member: hydarulic_oil_temp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hydarulic_oil_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.hydarulic_oil_temp, out);
    out << "\n";
  }

  // member: bucket_payload
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bucket_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_payload, out);
    out << "\n";
  }

  // member: desired_gear
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "desired_gear: ";
    rosidl_generator_traits::value_to_yaml(msg.desired_gear, out);
    out << "\n";
  }

  // member: ground_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ground_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.ground_speed, out);
    out << "\n";
  }

  // member: engine_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "engine_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.engine_speed, out);
    out << "\n";
  }

  // member: torque_converter_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "torque_converter_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.torque_converter_speed, out);
    out << "\n";
  }

  // member: keyswitch_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "keyswitch_state: ";
    rosidl_generator_traits::value_to_yaml(msg.keyswitch_state, out);
    out << "\n";
  }

  // member: real_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "real_time: ";
    rosidl_generator_traits::value_to_yaml(msg.real_time, out);
    out << "\n";
  }

  // member: real_time_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "real_time_status: ";
    rosidl_generator_traits::value_to_yaml(msg.real_time_status, out);
    out << "\n";
  }

  // member: timezone_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timezone_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.timezone_offset, out);
    out << "\n";
  }

  // member: total_fuel_high_res
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_fuel_high_res: ";
    rosidl_generator_traits::value_to_yaml(msg.total_fuel_high_res, out);
    out << "\n";
  }

  // member: total_fuel_low_res
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_fuel_low_res: ";
    rosidl_generator_traits::value_to_yaml(msg.total_fuel_low_res, out);
    out << "\n";
  }

  // member: fuel_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fuel_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.fuel_rate, out);
    out << "\n";
  }

  // member: ard_fuel_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ard_fuel_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.ard_fuel_rate, out);
    out << "\n";
  }

  // member: service_hour_meter
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "service_hour_meter: ";
    rosidl_generator_traits::value_to_yaml(msg.service_hour_meter, out);
    out << "\n";
  }

  // member: external_force_normalized
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "external_force_normalized: ";
    rosidl_generator_traits::value_to_yaml(msg.external_force_normalized, out);
    out << "\n";
  }

  // member: gps_latitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gps_latitude: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_latitude, out);
    out << "\n";
  }

  // member: gps_longitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gps_longitude: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_longitude, out);
    out << "\n";
  }

  // member: gps_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gps_status: ";
    rosidl_generator_traits::value_to_yaml(msg.gps_status, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Machine & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace weigh_app_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use weigh_app_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const weigh_app_interfaces::msg::Machine & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::Machine & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::Machine>()
{
  return "weigh_app_interfaces::msg::Machine";
}

template<>
inline const char * name<weigh_app_interfaces::msg::Machine>()
{
  return "weigh_app_interfaces/msg/Machine";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::Machine>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::Machine>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::Machine>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__TRAITS_HPP_
