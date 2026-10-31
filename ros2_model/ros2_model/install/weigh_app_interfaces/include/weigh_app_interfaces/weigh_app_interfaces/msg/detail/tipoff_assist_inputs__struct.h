// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/TipoffAssistInputs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_assist_inputs.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/TipoffAssistInputs in the package weigh_app_interfaces.
/**
  * TipoffAssistInputs
 */
typedef struct weigh_app_interfaces__msg__TipoffAssistInputs
{
  /// Input status bitfield packed into uint16
  uint16_t input_status;
  bool invalidate_outputs;
  float lift_valve_cmd;
  float tilt_valve_cmd;
  float tilt_extension;
  float lift_angle;
  float lift_he_pressure;
  float lift_re_pressure;
  float tilt_he_pressure;
  float tilt_re_pressure;
  float eef_imu_accel_x;
  float eef_imu_accel_y;
  float eef_imu_accel_z;
  float steering_angle;
  float tool_mass;
  float truck_target_wt;
  float truck_start_weight;
  uint8_t bucket_current_weight_accuracy;
  float bucket_current_weight;
  uint8_t tipoff_mode;
  float zero_offset;
  float simple_cal_factor;
  float mach_pitch_cal_offset;
  bool unlatch_trigger;
  float bucket_angle;
  float anchor_zero_offset;
  float anchor_factor;
  uint16_t pass_count;
  float lift_norm_angle;
  float lift_norm_length;
  float tilt_norm_angle;
  float tilt_norm_length;
  float friction_mu;
  float friction_offset;
} weigh_app_interfaces__msg__TipoffAssistInputs;

// Struct for a sequence of weigh_app_interfaces__msg__TipoffAssistInputs.
typedef struct weigh_app_interfaces__msg__TipoffAssistInputs__Sequence
{
  weigh_app_interfaces__msg__TipoffAssistInputs * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__TipoffAssistInputs__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__STRUCT_H_
