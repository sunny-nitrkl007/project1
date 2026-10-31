// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/TipOffTriggerType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/tip_off_trigger_type.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_TRIGGER_TYPE__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_TRIGGER_TYPE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'AUTO'.
enum
{
  cpm_common_interfaces__msg__TipOffTriggerType__AUTO = 0
};

/// Constant 'MANUAL'.
enum
{
  cpm_common_interfaces__msg__TipOffTriggerType__MANUAL = 1
};

/// Constant 'DISABLED'.
enum
{
  cpm_common_interfaces__msg__TipOffTriggerType__DISABLED = 2
};

/// Struct defined in msg/TipOffTriggerType in the package cpm_common_interfaces.
/**
  * LpsSaTipOffTriggerType_t
 */
typedef struct cpm_common_interfaces__msg__TipOffTriggerType
{
  uint8_t value;
} cpm_common_interfaces__msg__TipOffTriggerType;

// Struct for a sequence of cpm_common_interfaces__msg__TipOffTriggerType.
typedef struct cpm_common_interfaces__msg__TipOffTriggerType__Sequence
{
  cpm_common_interfaces__msg__TipOffTriggerType * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__TipOffTriggerType__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_TRIGGER_TYPE__STRUCT_H_
