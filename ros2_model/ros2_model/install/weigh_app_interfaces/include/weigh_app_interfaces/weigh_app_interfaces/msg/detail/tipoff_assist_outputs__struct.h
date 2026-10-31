// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/TipoffAssistOutputs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_assist_outputs.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/TipoffAssistOutputs in the package weigh_app_interfaces.
/**
  * TipoffAssistOutputs
 */
typedef struct weigh_app_interfaces__msg__TipoffAssistOutputs
{
  float tilt_sensitivity_out;
  float tilt_pressure_out;
  float arbitrated_payload_norm_error_out;
  uint8_t weigh_status_out;
  float payload_norm_stdev_out;
  uint8_t pcs_weight_accuracy_out;
  float current_weight_norm_error_out;
  uint8_t error_code_out;
  float spill_rate_out;
  float payload_send_to_cpm;
  uint8_t payload_status_send_to_cpm;
  float bucket_payload_target;
  float unsecured_payload_upper_bound_norm;
  float unsecured_payload_lower_bound_norm;
  uint8_t unsecured_pfw_status;
  float min_secure_bucket_angle;
} weigh_app_interfaces__msg__TipoffAssistOutputs;

// Struct for a sequence of weigh_app_interfaces__msg__TipoffAssistOutputs.
typedef struct weigh_app_interfaces__msg__TipoffAssistOutputs__Sequence
{
  weigh_app_interfaces__msg__TipoffAssistOutputs * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__TipoffAssistOutputs__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__STRUCT_H_
