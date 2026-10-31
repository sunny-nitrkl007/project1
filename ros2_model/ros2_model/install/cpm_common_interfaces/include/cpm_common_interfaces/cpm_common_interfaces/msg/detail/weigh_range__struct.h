// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/WeighRange.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/weigh_range.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_RANGE__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_RANGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/WeighRange in the package cpm_common_interfaces.
/**
  * LpsSaWeighRange_t
 */
typedef struct cpm_common_interfaces__msg__WeighRange
{
  float weigh_range_bottom;
  float weigh_range_size;
} cpm_common_interfaces__msg__WeighRange;

// Struct for a sequence of cpm_common_interfaces__msg__WeighRange.
typedef struct cpm_common_interfaces__msg__WeighRange__Sequence
{
  cpm_common_interfaces__msg__WeighRange * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__WeighRange__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_RANGE__STRUCT_H_
