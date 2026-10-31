// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/DiskSpaceRemain.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/disk_space_remain.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DISK_SPACE_REMAIN__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DISK_SPACE_REMAIN__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'filesystem'
// Member 'percent_use'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/DiskSpaceRemain in the package weigh_app_interfaces.
/**
  * DiskSpaceRemain
 */
typedef struct weigh_app_interfaces__msg__DiskSpaceRemain
{
  rosidl_runtime_c__String filesystem;
  uint32_t avail_kb;
  rosidl_runtime_c__String percent_use;
} weigh_app_interfaces__msg__DiskSpaceRemain;

// Struct for a sequence of weigh_app_interfaces__msg__DiskSpaceRemain.
typedef struct weigh_app_interfaces__msg__DiskSpaceRemain__Sequence
{
  weigh_app_interfaces__msg__DiskSpaceRemain * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__DiskSpaceRemain__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DISK_SPACE_REMAIN__STRUCT_H_
