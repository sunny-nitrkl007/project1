// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/AcdEventPopUp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/acd_event_pop_up.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'BATTERY_HIGH'.
enum
{
  cpm_common_interfaces__msg__AcdEventPopUp__BATTERY_HIGH = 28
};

/// Constant 'BATTERY_LOW'.
enum
{
  cpm_common_interfaces__msg__AcdEventPopUp__BATTERY_LOW = 29
};

/// Constant 'PAYLOAD_LFT_NOT_SEALED'.
enum
{
  cpm_common_interfaces__msg__AcdEventPopUp__PAYLOAD_LFT_NOT_SEALED = 30
};

/// Constant 'OVERLOAD_LIMIT_EXCEEDED'.
enum
{
  cpm_common_interfaces__msg__AcdEventPopUp__OVERLOAD_LIMIT_EXCEEDED = 31
};

/// Struct defined in msg/AcdEventPopUp in the package cpm_common_interfaces.
/**
  * ACDEventPopUp::type
 */
typedef struct cpm_common_interfaces__msg__AcdEventPopUp
{
  uint32_t bits;
} cpm_common_interfaces__msg__AcdEventPopUp;

// Struct for a sequence of cpm_common_interfaces__msg__AcdEventPopUp.
typedef struct cpm_common_interfaces__msg__AcdEventPopUp__Sequence
{
  cpm_common_interfaces__msg__AcdEventPopUp * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__AcdEventPopUp__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__STRUCT_H_
