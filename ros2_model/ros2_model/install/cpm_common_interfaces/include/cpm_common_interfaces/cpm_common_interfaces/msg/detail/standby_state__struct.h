// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/StandbyState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/standby_state.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__STANDBY_STATE__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__STANDBY_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'ACTIVATED'.
enum
{
  cpm_common_interfaces__msg__StandbyState__ACTIVATED = 0
};

/// Constant 'DEACTIVATED'.
enum
{
  cpm_common_interfaces__msg__StandbyState__DEACTIVATED = 1
};

/// Struct defined in msg/StandbyState in the package cpm_common_interfaces.
/**
  * LpsSaJobMgrStandbyState_t
 */
typedef struct cpm_common_interfaces__msg__StandbyState
{
  uint8_t value;
} cpm_common_interfaces__msg__StandbyState;

// Struct for a sequence of cpm_common_interfaces__msg__StandbyState.
typedef struct cpm_common_interfaces__msg__StandbyState__Sequence
{
  cpm_common_interfaces__msg__StandbyState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__StandbyState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__STANDBY_STATE__STRUCT_H_
