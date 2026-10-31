// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/SystemHardwareHealthRequest.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/system_hardware_health_request.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_REQUEST__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_REQUEST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/SystemHardwareHealthRequest in the package weigh_app_interfaces.
/**
  * SystemHardwareHealthRequestStorage
 */
typedef struct weigh_app_interfaces__msg__SystemHardwareHealthRequest
{
  uint8_t structure_needs_at_least_one_member;
} weigh_app_interfaces__msg__SystemHardwareHealthRequest;

// Struct for a sequence of weigh_app_interfaces__msg__SystemHardwareHealthRequest.
typedef struct weigh_app_interfaces__msg__SystemHardwareHealthRequest__Sequence
{
  weigh_app_interfaces__msg__SystemHardwareHealthRequest * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__SystemHardwareHealthRequest__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_REQUEST__STRUCT_H_
