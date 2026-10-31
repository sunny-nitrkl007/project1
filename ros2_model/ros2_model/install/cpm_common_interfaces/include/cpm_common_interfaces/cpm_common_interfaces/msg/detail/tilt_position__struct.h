// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/TiltPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/tilt_position.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__TILT_POSITION__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__TILT_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/TiltPosition in the package cpm_common_interfaces.
/**
  * LpsSaTiltPosition_t
 */
typedef struct cpm_common_interfaces__msg__TiltPosition
{
  float angle;
  float percent_angle;
  float cylinder_length;
  float percent_cylinder_length;
  float cylinder_extension;
  float bucket_angle;
  int32_t status;
} cpm_common_interfaces__msg__TiltPosition;

// Struct for a sequence of cpm_common_interfaces__msg__TiltPosition.
typedef struct cpm_common_interfaces__msg__TiltPosition__Sequence
{
  cpm_common_interfaces__msg__TiltPosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__TiltPosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__TILT_POSITION__STRUCT_H_
