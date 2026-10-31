// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LiftPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lift_position.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LiftPosition in the package cpm_common_interfaces.
/**
  * LpsSaLiftPosition_t
 */
typedef struct cpm_common_interfaces__msg__LiftPosition
{
  float angle;
  float percent_angle;
  float cylinder_length;
  float percent_cylinder_length;
  float cylinder_extension;
  int32_t status;
} cpm_common_interfaces__msg__LiftPosition;

// Struct for a sequence of cpm_common_interfaces__msg__LiftPosition.
typedef struct cpm_common_interfaces__msg__LiftPosition__Sequence
{
  cpm_common_interfaces__msg__LiftPosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LiftPosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__STRUCT_H_
