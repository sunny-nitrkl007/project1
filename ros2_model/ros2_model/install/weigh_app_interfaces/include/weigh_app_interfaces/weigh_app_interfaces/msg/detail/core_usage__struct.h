// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/CoreUsage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/core_usage.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/CoreUsage in the package weigh_app_interfaces.
/**
  * SystemHardwareHealthStorage::CoreUsage
 */
typedef struct weigh_app_interfaces__msg__CoreUsage
{
  double cpu_usage_percent;
  double cpu_io_wait_percent;
  double cpu_irq_percent;
} weigh_app_interfaces__msg__CoreUsage;

// Struct for a sequence of weigh_app_interfaces__msg__CoreUsage.
typedef struct weigh_app_interfaces__msg__CoreUsage__Sequence
{
  weigh_app_interfaces__msg__CoreUsage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__CoreUsage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__STRUCT_H_
