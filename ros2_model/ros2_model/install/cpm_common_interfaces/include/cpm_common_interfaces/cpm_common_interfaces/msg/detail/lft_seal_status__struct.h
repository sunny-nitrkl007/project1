// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LftSealStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lft_seal_status.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LftSealStatus in the package cpm_common_interfaces.
/**
  * LpsSaLftSealStatus_t
 */
typedef struct cpm_common_interfaces__msg__LftSealStatus
{
  bool sealed;
  int64_t seal_time_ns;
  uint32_t seal_id;
} cpm_common_interfaces__msg__LftSealStatus;

// Struct for a sequence of cpm_common_interfaces__msg__LftSealStatus.
typedef struct cpm_common_interfaces__msg__LftSealStatus__Sequence
{
  cpm_common_interfaces__msg__LftSealStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LftSealStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__STRUCT_H_
