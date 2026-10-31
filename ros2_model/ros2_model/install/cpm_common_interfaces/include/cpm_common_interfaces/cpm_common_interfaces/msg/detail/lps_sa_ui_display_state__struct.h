// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LpsSaUIDisplayState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_ui_display_state.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'settings'
#include "cpm_common_interfaces/msg/detail/lps_sa_ui_display_settings__struct.h"

/// Struct defined in msg/LpsSaUIDisplayState in the package cpm_common_interfaces.
/**
  * LpsSaUIDisplayState
 */
typedef struct cpm_common_interfaces__msg__LpsSaUIDisplayState
{
  bool service_mode_enable_code_entered;
  bool in_service_mode;
  bool in_verification_mode;
  uint32_t heartbeat_count;
  uint16_t document_id;
  float weight_capacity;
  int32_t weight_decimal_precision;
  float weight_interval;
  cpm_common_interfaces__msg__LpsSaUIDisplaySettings settings;
} cpm_common_interfaces__msg__LpsSaUIDisplayState;

// Struct for a sequence of cpm_common_interfaces__msg__LpsSaUIDisplayState.
typedef struct cpm_common_interfaces__msg__LpsSaUIDisplayState__Sequence
{
  cpm_common_interfaces__msg__LpsSaUIDisplayState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LpsSaUIDisplayState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__STRUCT_H_
