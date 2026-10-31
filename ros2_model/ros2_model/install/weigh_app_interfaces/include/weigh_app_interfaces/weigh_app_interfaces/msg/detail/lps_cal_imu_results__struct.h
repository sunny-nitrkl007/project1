// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsCalIMUResults.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_cal_imu_results.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LpsCalIMUResults in the package weigh_app_interfaces.
/**
  * LpsCalIMUResults_t
 */
typedef struct weigh_app_interfaces__msg__LpsCalIMUResults
{
  float full_slow_imu_offset_temp1;
  float full_slow_imu_offset_temp2;
  float full_slow_imu_offset_temp3;
  float full_slow_lumped_weight_temp1;
  float full_slow_lumped_weight_temp2;
  float full_slow_lumped_weight_temp3;
  float empty_slow_imu_offset_temp1;
  float empty_slow_imu_offset_temp2;
  float empty_slow_imu_offset_temp3;
  float empty_slow_lumped_weight_temp1;
  float empty_slow_lumped_weight_temp2;
  float empty_slow_lumped_weight_temp3;
  float full_slow_imu_offset_final;
  float empty_slow_imu_offset_final;
  float full_slow_lumped_weight_final;
  float empty_slow_lumped_weight_final;
} weigh_app_interfaces__msg__LpsCalIMUResults;

// Struct for a sequence of weigh_app_interfaces__msg__LpsCalIMUResults.
typedef struct weigh_app_interfaces__msg__LpsCalIMUResults__Sequence
{
  weigh_app_interfaces__msg__LpsCalIMUResults * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsCalIMUResults__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__STRUCT_H_
