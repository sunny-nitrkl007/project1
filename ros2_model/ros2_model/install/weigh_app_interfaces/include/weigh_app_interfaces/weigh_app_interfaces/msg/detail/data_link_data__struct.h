// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/DataLinkData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/data_link_data.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'params'
#include "weigh_app_interfaces/msg/detail/data_link_param__struct.h"

/// Struct defined in msg/DataLinkData in the package weigh_app_interfaces.
/**
  * DataLinkDataStorage
 */
typedef struct weigh_app_interfaces__msg__DataLinkData
{
  weigh_app_interfaces__msg__DataLinkParam__Sequence params;
} weigh_app_interfaces__msg__DataLinkData;

// Struct for a sequence of weigh_app_interfaces__msg__DataLinkData.
typedef struct weigh_app_interfaces__msg__DataLinkData__Sequence
{
  weigh_app_interfaces__msg__DataLinkData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__DataLinkData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__STRUCT_H_
