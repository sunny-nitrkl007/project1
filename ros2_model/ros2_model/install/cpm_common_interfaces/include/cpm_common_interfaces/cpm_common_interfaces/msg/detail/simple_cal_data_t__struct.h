// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/SimpleCalDataT.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/simple_cal_data_t.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'time_stamp'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/SimpleCalDataT in the package cpm_common_interfaces.
/**
  * AisJhm2TxChannelStorage::simplecal_data_t
 */
typedef struct cpm_common_interfaces__msg__SimpleCalDataT
{
  rosidl_runtime_c__String time_stamp;
  float adjtruckweight;
  float zeroed_truck_wt;
  bool new_data_flag;
} cpm_common_interfaces__msg__SimpleCalDataT;

// Struct for a sequence of cpm_common_interfaces__msg__SimpleCalDataT.
typedef struct cpm_common_interfaces__msg__SimpleCalDataT__Sequence
{
  cpm_common_interfaces__msg__SimpleCalDataT * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__SimpleCalDataT__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__STRUCT_H_
