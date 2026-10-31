// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LpsSaWeighReqstChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_reqst_channel.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'app_name'
// Member 'arg_s'
#include "rosidl_runtime_c/string.h"
// Member 'command'
#include "cpm_common_interfaces/msg/detail/weigh_reqst_channel_command__struct.h"
// Member 'arg_map'
#include "cpm_common_interfaces/msg/detail/float_pair__struct.h"

/// Struct defined in msg/LpsSaWeighReqstChannel in the package cpm_common_interfaces.
/**
  * LpsSaWeighReqstChannelStorage
 */
typedef struct cpm_common_interfaces__msg__LpsSaWeighReqstChannel
{
  rosidl_runtime_c__String app_name;
  uint32_t app_request_id;
  cpm_common_interfaces__msg__WeighReqstChannelCommand command;
  bool arg_b;
  float arg_f1;
  float arg_f2;
  rosidl_runtime_c__String arg_s;
  uint32_t arg_u;
  cpm_common_interfaces__msg__FloatPair__Sequence arg_map;
} cpm_common_interfaces__msg__LpsSaWeighReqstChannel;

// Struct for a sequence of cpm_common_interfaces__msg__LpsSaWeighReqstChannel.
typedef struct cpm_common_interfaces__msg__LpsSaWeighReqstChannel__Sequence
{
  cpm_common_interfaces__msg__LpsSaWeighReqstChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LpsSaWeighReqstChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__STRUCT_H_
