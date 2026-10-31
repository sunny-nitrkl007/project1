// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/ShmClockInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/shm_clock_input.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/ShmClockInput in the package cpm_common_interfaces.
/**
  * ShmClockStorage
 */
typedef struct cpm_common_interfaces__msg__ShmClockInput
{
  uint32_t shm_sec;
  int64_t utc_sec_us;
  int32_t utc_offset_min;
  uint8_t tzone_info[20];
} cpm_common_interfaces__msg__ShmClockInput;

// Struct for a sequence of cpm_common_interfaces__msg__ShmClockInput.
typedef struct cpm_common_interfaces__msg__ShmClockInput__Sequence
{
  cpm_common_interfaces__msg__ShmClockInput * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__ShmClockInput__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__STRUCT_H_
