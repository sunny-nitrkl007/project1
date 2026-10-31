// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/EcmVersionInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ecm_version_info.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'serial_num'
// Member 'part_num'
// Member 'dom'
// Member 'mac0'
// Member 'mac1'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/EcmVersionInfo in the package weigh_app_interfaces.
/**
  * EcmVersionInfo
 */
typedef struct weigh_app_interfaces__msg__EcmVersionInfo
{
  rosidl_runtime_c__String serial_num;
  rosidl_runtime_c__String part_num;
  rosidl_runtime_c__String dom;
  rosidl_runtime_c__String mac0;
  rosidl_runtime_c__String mac1;
} weigh_app_interfaces__msg__EcmVersionInfo;

// Struct for a sequence of weigh_app_interfaces__msg__EcmVersionInfo.
typedef struct weigh_app_interfaces__msg__EcmVersionInfo__Sequence
{
  weigh_app_interfaces__msg__EcmVersionInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__EcmVersionInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__STRUCT_H_
