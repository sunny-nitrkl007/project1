// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/Payload.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/payload.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Payload in the package cpm_common_interfaces.
/**
  * LpsSaPayload_t
 */
typedef struct cpm_common_interfaces__msg__Payload
{
  float payload_ratio_raw;
  float payload_ratio;
  int32_t payload_ratio_status;
} cpm_common_interfaces__msg__Payload;

// Struct for a sequence of cpm_common_interfaces__msg__Payload.
typedef struct cpm_common_interfaces__msg__Payload__Sequence
{
  cpm_common_interfaces__msg__Payload * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__Payload__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__STRUCT_H_
