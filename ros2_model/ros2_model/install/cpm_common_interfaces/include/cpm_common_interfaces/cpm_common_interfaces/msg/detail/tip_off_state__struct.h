// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/TipOffState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/tip_off_state.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_STATE__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'PILE_ENABLE'.
enum
{
  cpm_common_interfaces__msg__TipOffState__PILE_ENABLE = 0
};

/// Constant 'TRUCK_ENABLE'.
enum
{
  cpm_common_interfaces__msg__TipOffState__TRUCK_ENABLE = 1
};

/// Constant 'UNAVAILABLE'.
enum
{
  cpm_common_interfaces__msg__TipOffState__UNAVAILABLE = 2
};

/// Struct defined in msg/TipOffState in the package cpm_common_interfaces.
/**
  * LpsSaJobMgrTipOffState_t
 */
typedef struct cpm_common_interfaces__msg__TipOffState
{
  uint8_t value;
} cpm_common_interfaces__msg__TipOffState;

// Struct for a sequence of cpm_common_interfaces__msg__TipOffState.
typedef struct cpm_common_interfaces__msg__TipOffState__Sequence
{
  cpm_common_interfaces__msg__TipOffState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__TipOffState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_STATE__STRUCT_H_
