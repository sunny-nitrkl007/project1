// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/AcdDiagPopUp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/acd_diag_pop_up.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_DIAG_POP_UP__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_DIAG_POP_UP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'TILT_RE_FREQ_ABNORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__TILT_RE_FREQ_ABNORMAL = 8
};

/// Constant 'TILT_RE_VOLTAGE_BELOW_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__TILT_RE_VOLTAGE_BELOW_NORMAL = 9
};

/// Constant 'TILT_RE_VOLTAGE_ABOVE_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__TILT_RE_VOLTAGE_ABOVE_NORMAL = 10
};

/// Constant 'TILT_HE_FREQ_ABNORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__TILT_HE_FREQ_ABNORMAL = 11
};

/// Constant 'TILT_HE_VOLTAGE_BELOW_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__TILT_HE_VOLTAGE_BELOW_NORMAL = 12
};

/// Constant 'TILT_HE_VOLTAGE_ABOVE_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__TILT_HE_VOLTAGE_ABOVE_NORMAL = 13
};

/// Constant 'HYDRAULIC_OIL_TEMP_BAD'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__HYDRAULIC_OIL_TEMP_BAD = 14
};

/// Constant 'MACHINE_MODEL_NOT_SET'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__MACHINE_MODEL_NOT_SET = 15
};

/// Constant 'PAYLOAD_SYSTEM_NOT_INSTALLED'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__PAYLOAD_SYSTEM_NOT_INSTALLED = 16
};

/// Constant 'PAYLOAD_SYSTEM_OUT_OF_CAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__PAYLOAD_SYSTEM_OUT_OF_CAL = 17
};

/// Constant 'LIFT_RE_FREQ_ABNORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__LIFT_RE_FREQ_ABNORMAL = 18
};

/// Constant 'LIFT_RE_VOLTAGE_BELOW_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__LIFT_RE_VOLTAGE_BELOW_NORMAL = 19
};

/// Constant 'LIFT_RE_VOLTAGE_ABOVE_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__LIFT_RE_VOLTAGE_ABOVE_NORMAL = 20
};

/// Constant 'LIFT_HE_FREQ_ABNORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__LIFT_HE_FREQ_ABNORMAL = 21
};

/// Constant 'LIFT_HE_VOLTAGE_BELOW_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__LIFT_HE_VOLTAGE_BELOW_NORMAL = 22
};

/// Constant 'LIFT_HE_VOLTAGE_ABOVE_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__LIFT_HE_VOLTAGE_ABOVE_NORMAL = 23
};

/// Constant 'LIFT_LINK_OUT_OF_CAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__LIFT_LINK_OUT_OF_CAL = 24
};

/// Constant 'LIFT_LINK_FREQ_ABNORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__LIFT_LINK_FREQ_ABNORMAL = 25
};

/// Constant 'LIFT_LINK_VOLTAGE_BELOW_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__LIFT_LINK_VOLTAGE_BELOW_NORMAL = 26
};

/// Constant 'LIFT_LINK_VOLTAGE_ABOVE_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__LIFT_LINK_VOLTAGE_ABOVE_NORMAL = 27
};

/// Constant 'TILT_LINK_OUT_OF_CAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__TILT_LINK_OUT_OF_CAL = 28
};

/// Constant 'TILT_LINK_FREQ_ABNORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__TILT_LINK_FREQ_ABNORMAL = 29
};

/// Constant 'TILT_LINK_VOLTAGE_BELOW_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__TILT_LINK_VOLTAGE_BELOW_NORMAL = 30
};

/// Constant 'TILT_LINK_VOLTAGE_ABOVE_NORMAL'.
enum
{
  cpm_common_interfaces__msg__AcdDiagPopUp__TILT_LINK_VOLTAGE_ABOVE_NORMAL = 31
};

/// Struct defined in msg/AcdDiagPopUp in the package cpm_common_interfaces.
/**
  * ACDDiagPopUp::type
 */
typedef struct cpm_common_interfaces__msg__AcdDiagPopUp
{
  uint32_t bits;
} cpm_common_interfaces__msg__AcdDiagPopUp;

// Struct for a sequence of cpm_common_interfaces__msg__AcdDiagPopUp.
typedef struct cpm_common_interfaces__msg__AcdDiagPopUp__Sequence
{
  cpm_common_interfaces__msg__AcdDiagPopUp * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__AcdDiagPopUp__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_DIAG_POP_UP__STRUCT_H_
