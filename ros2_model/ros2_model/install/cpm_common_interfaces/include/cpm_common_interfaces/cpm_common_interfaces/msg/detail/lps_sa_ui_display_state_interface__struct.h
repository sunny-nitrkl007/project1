// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LpsSaUIDisplayStateInterface.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_ui_display_state_interface.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE_INTERFACE__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE_INTERFACE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'state'
#include "cpm_common_interfaces/msg/detail/lps_sa_ui_display_state__struct.h"

/// Struct defined in msg/LpsSaUIDisplayStateInterface in the package cpm_common_interfaces.
/**
  * LpsSaUIDisplayStateInterfaceStorage
 */
typedef struct cpm_common_interfaces__msg__LpsSaUIDisplayStateInterface
{
  cpm_common_interfaces__msg__LpsSaUIDisplayState state;
} cpm_common_interfaces__msg__LpsSaUIDisplayStateInterface;

// Struct for a sequence of cpm_common_interfaces__msg__LpsSaUIDisplayStateInterface.
typedef struct cpm_common_interfaces__msg__LpsSaUIDisplayStateInterface__Sequence
{
  cpm_common_interfaces__msg__LpsSaUIDisplayStateInterface * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LpsSaUIDisplayStateInterface__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE_INTERFACE__STRUCT_H_
