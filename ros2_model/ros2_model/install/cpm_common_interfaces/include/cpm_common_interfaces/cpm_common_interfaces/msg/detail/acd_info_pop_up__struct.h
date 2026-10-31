// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/AcdInfoPopUp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/acd_info_pop_up.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_INFO_POP_UP__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_INFO_POP_UP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'PAYLOAD_TOO_HEAVY_TO_ZERO'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_TOO_HEAVY_TO_ZERO = 0
};

/// Constant 'PAYLOAD_NOT_ZEROED'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_NOT_ZEROED = 1
};

/// Constant 'PAYLOAD_CAL_ACCEPTED'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_CAL_ACCEPTED = 2
};

/// Constant 'PAYLOAD_ZERO_ACCEPTED'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_ZERO_ACCEPTED = 3
};

/// Constant 'PAYLOAD_REWEIGH_LIFT_TOO_SLOW'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_REWEIGH_LIFT_TOO_SLOW = 4
};

/// Constant 'PAYLOAD_REWEIGH_STOPPED_IN_RANGE'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_REWEIGH_STOPPED_IN_RANGE = 5
};

/// Constant 'PAYLOAD_REWEIGH_NOT_RACKED'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_REWEIGH_NOT_RACKED = 6
};

/// Constant 'PAYLOAD_REWEIGH_SPEED_CHANGING'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_REWEIGH_SPEED_CHANGING = 7
};

/// Constant 'PAYLOAD_REWEIGH_INCONSISTENT'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_REWEIGH_INCONSISTENT = 8
};

/// Constant 'PAYLOAD_REWEIGH_PRESSURE_CHANGING'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_REWEIGH_PRESSURE_CHANGING = 9
};

/// Constant 'PAYLOAD_REWEIGH_EXCESSIVE_PITCH'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_REWEIGH_EXCESSIVE_PITCH = 10
};

/// Constant 'PAYLOAD_REWEIGH_WARMUP_LIFT'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_REWEIGH_WARMUP_LIFT = 11
};

/// Constant 'PAYLOAD_RAISE_STALL'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_RAISE_STALL = 12
};

/// Constant 'PAYLOAD_LOWER_STALL'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_LOWER_STALL = 13
};

/// Constant 'PAYLOAD_CAL_WT_ENTRY_REQUIRED'.
enum
{
  cpm_common_interfaces__msg__AcdInfoPopUp__PAYLOAD_CAL_WT_ENTRY_REQUIRED = 14
};

/// Struct defined in msg/AcdInfoPopUp in the package cpm_common_interfaces.
/**
  * ACDInfoPopUp::type
 */
typedef struct cpm_common_interfaces__msg__AcdInfoPopUp
{
  uint32_t bits;
} cpm_common_interfaces__msg__AcdInfoPopUp;

// Struct for a sequence of cpm_common_interfaces__msg__AcdInfoPopUp.
typedef struct cpm_common_interfaces__msg__AcdInfoPopUp__Sequence
{
  cpm_common_interfaces__msg__AcdInfoPopUp * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__AcdInfoPopUp__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_INFO_POP_UP__STRUCT_H_
