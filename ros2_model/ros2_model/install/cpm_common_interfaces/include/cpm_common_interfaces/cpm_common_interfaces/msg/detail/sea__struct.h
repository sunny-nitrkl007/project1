// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/SEA.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/sea.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SEA__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SEA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'STATUS_UNKNOWN'.
enum
{
  cpm_common_interfaces__msg__SEA__STATUS_UNKNOWN = 0
};

/// Constant 'STATUS_NOT_INSTALLED'.
enum
{
  cpm_common_interfaces__msg__SEA__STATUS_NOT_INSTALLED = 1
};

/// Constant 'STATUS_INSTALLED'.
enum
{
  cpm_common_interfaces__msg__SEA__STATUS_INSTALLED = 2
};

/// Constant 'STATUS_ENABLED'.
enum
{
  cpm_common_interfaces__msg__SEA__STATUS_ENABLED = 3
};

/// Constant 'STATUS_TEMP_INSTALLED'.
enum
{
  cpm_common_interfaces__msg__SEA__STATUS_TEMP_INSTALLED = 4
};

/// Struct defined in msg/SEA in the package cpm_common_interfaces.
/**
  * SEAStatusCodes
 */
typedef struct cpm_common_interfaces__msg__SEA
{
  /// SEA
  uint16_t free_count;
  uint16_t reason_code;
  uint16_t status;
} cpm_common_interfaces__msg__SEA;

// Struct for a sequence of cpm_common_interfaces__msg__SEA.
typedef struct cpm_common_interfaces__msg__SEA__Sequence
{
  cpm_common_interfaces__msg__SEA * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__SEA__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SEA__STRUCT_H_
