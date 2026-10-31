// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/FloatIO.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/float_io.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_IO__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_IO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/FloatIO in the package cpm_common_interfaces.
/**
  * LpsFloatIO_t
 */
typedef struct cpm_common_interfaces__msg__FloatIO
{
  int32_t stat;
  float val;
} cpm_common_interfaces__msg__FloatIO;

// Struct for a sequence of cpm_common_interfaces__msg__FloatIO.
typedef struct cpm_common_interfaces__msg__FloatIO__Sequence
{
  cpm_common_interfaces__msg__FloatIO * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__FloatIO__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_IO__STRUCT_H_
