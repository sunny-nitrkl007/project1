// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/MaterialReport.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/material_report.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__MATERIAL_REPORT__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__MATERIAL_REPORT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/MaterialReport in the package weigh_app_interfaces.
/**
  * LpsSaTotalsPrinterCnfg::MaterialReport
 */
typedef struct weigh_app_interfaces__msg__MaterialReport
{
  bool reset_time_enabled;
} weigh_app_interfaces__msg__MaterialReport;

// Struct for a sequence of weigh_app_interfaces__msg__MaterialReport.
typedef struct weigh_app_interfaces__msg__MaterialReport__Sequence
{
  weigh_app_interfaces__msg__MaterialReport * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__MaterialReport__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__MATERIAL_REPORT__STRUCT_H_
