// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LinkSensorCalLim.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/link_sensor_cal_lim.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LinkSensorCalLim in the package cpm_common_interfaces.
/**
  * LinkSensorCalLim_t
 */
typedef struct cpm_common_interfaces__msg__LinkSensorCalLim
{
  float lift_pos_sensor_dc;
  float lift_pos_sensor_full_raise_dc;
  float lift_pos_sensor_full_lower_dc;
  float tilt_pos_sensor_dc;
  float tilt_pos_sensor_full_rack_dc;
  float tilt_pos_sensor_full_dump_dc;
} cpm_common_interfaces__msg__LinkSensorCalLim;

// Struct for a sequence of cpm_common_interfaces__msg__LinkSensorCalLim.
typedef struct cpm_common_interfaces__msg__LinkSensorCalLim__Sequence
{
  cpm_common_interfaces__msg__LinkSensorCalLim * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LinkSensorCalLim__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__STRUCT_H_
