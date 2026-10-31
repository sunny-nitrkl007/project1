// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LpsSaWeighRespChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_resp_channel.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__STRUCT_H_

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
// Member 'arg1'
#include "rosidl_runtime_c/string.h"
// Member 'command'
#include "cpm_common_interfaces/msg/detail/weigh_reqst_channel_command__struct.h"

/// Struct defined in msg/LpsSaWeighRespChannel in the package cpm_common_interfaces.
/**
  * LpsSaWeighRespChannelStorage
 */
typedef struct cpm_common_interfaces__msg__LpsSaWeighRespChannel
{
  rosidl_runtime_c__String app_name;
  uint32_t app_request_id;
  int64_t time_point_ns;
  cpm_common_interfaces__msg__WeighReqstChannelCommand command;
  bool success;
  rosidl_runtime_c__String arg1;
} cpm_common_interfaces__msg__LpsSaWeighRespChannel;

// Struct for a sequence of cpm_common_interfaces__msg__LpsSaWeighRespChannel.
typedef struct cpm_common_interfaces__msg__LpsSaWeighRespChannel__Sequence
{
  cpm_common_interfaces__msg__LpsSaWeighRespChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LpsSaWeighRespChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__STRUCT_H_
