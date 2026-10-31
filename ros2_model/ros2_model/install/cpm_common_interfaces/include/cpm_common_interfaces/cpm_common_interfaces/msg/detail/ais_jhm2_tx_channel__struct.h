// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/AisJhm2TxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/ais_jhm2_tx_channel.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'simplecal_data'
#include "cpm_common_interfaces/msg/detail/simple_cal_data_t__struct.h"
// Member 'tipoff_weight_adjust_data'
#include "cpm_common_interfaces/msg/detail/tipoff_weight_adjust_data__struct.h"

/// Struct defined in msg/AisJhm2TxChannel in the package cpm_common_interfaces.
/**
  * AisJhm2TxChannelStorage
 */
typedef struct cpm_common_interfaces__msg__AisJhm2TxChannel
{
  cpm_common_interfaces__msg__SimpleCalDataT simplecal_data;
  cpm_common_interfaces__msg__TipoffWeightAdjustData tipoff_weight_adjust_data;
} cpm_common_interfaces__msg__AisJhm2TxChannel;

// Struct for a sequence of cpm_common_interfaces__msg__AisJhm2TxChannel.
typedef struct cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence
{
  cpm_common_interfaces__msg__AisJhm2TxChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__STRUCT_H_
