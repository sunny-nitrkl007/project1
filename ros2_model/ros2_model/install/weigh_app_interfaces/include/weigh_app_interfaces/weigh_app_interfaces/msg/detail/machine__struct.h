// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/Machine.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/machine.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Machine in the package weigh_app_interfaces.
/**
  * MachineStorage
 */
typedef struct weigh_app_interfaces__msg__Machine
{
  uint16_t app_number;
  float payload_ratio;
  uint16_t payload_ratio_status;
  float payload_ratio_raw;
  uint16_t payload_ratio_raw_status;
  float payload_weight;
  uint16_t payload_weight_status;
  uint16_t payload_calc_method;
  int16_t lift_valve_cmd;
  int16_t tilt_valve_cmd;
  int16_t bucket_angle;
  float lift_angle;
  int16_t tilt_lever_cmd;
  uint16_t tilt_cyl_pos;
  uint16_t impl_operation_status;
  uint16_t machine_idle_status;
  uint8_t dump_solenoid_percent;
  uint8_t rack_solenoid_percent;
  uint8_t lower_solenoid_percent;
  uint8_t raise_solenoid_percent;
  float brake_pedal_position;
  uint16_t lift_cylinder_he_pressure;
  uint16_t lift_cylinder_re_pressure;
  int16_t hydarulic_oil_temp;
  float bucket_payload;
  int16_t desired_gear;
  int16_t ground_speed;
  int16_t engine_speed;
  int16_t torque_converter_speed;
  uint16_t keyswitch_state;
  uint32_t real_time;
  uint8_t real_time_status;
  int16_t timezone_offset;
  uint32_t total_fuel_high_res;
  uint32_t total_fuel_low_res;
  uint16_t fuel_rate;
  uint16_t ard_fuel_rate;
  uint32_t service_hour_meter;
  int16_t external_force_normalized;
  uint32_t gps_latitude;
  uint32_t gps_longitude;
  uint8_t gps_status;
} weigh_app_interfaces__msg__Machine;

// Struct for a sequence of weigh_app_interfaces__msg__Machine.
typedef struct weigh_app_interfaces__msg__Machine__Sequence
{
  weigh_app_interfaces__msg__Machine * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__Machine__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__MACHINE__STRUCT_H_
