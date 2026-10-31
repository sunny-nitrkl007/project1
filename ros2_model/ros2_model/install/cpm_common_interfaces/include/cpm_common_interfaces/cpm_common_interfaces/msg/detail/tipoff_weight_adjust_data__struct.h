// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/TipoffWeightAdjustData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/tipoff_weight_adjust_data.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/TipoffWeightAdjustData in the package cpm_common_interfaces.
/**
  * AisJhm2TxChannelStorage::tipoff_weight_adjust_data_t
 */
typedef struct cpm_common_interfaces__msg__TipoffWeightAdjustData
{
  float tip_off_weight1;
  float weigh_range_weight1;
  float tip_off_weight2;
  float weigh_range_weight2;
  bool new_data_flag;
  bool reset;
} cpm_common_interfaces__msg__TipoffWeightAdjustData;

// Struct for a sequence of cpm_common_interfaces__msg__TipoffWeightAdjustData.
typedef struct cpm_common_interfaces__msg__TipoffWeightAdjustData__Sequence
{
  cpm_common_interfaces__msg__TipoffWeightAdjustData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__TipoffWeightAdjustData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__STRUCT_H_
