// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaWeighInitDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_weigh_init_debug_channel.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LpsSaWeighInitDebugChannel in the package weigh_app_interfaces.
/**
  * LpsSaWeighInitDebugChannelStorage
 */
typedef struct weigh_app_interfaces__msg__LpsSaWeighInitDebugChannel
{
  float exec_rate;
  float cal_weight;
  uint32_t cal_status;
  float cal_adjust;
  float zero_weight;
  float dig_target_wt;
  float start_of_weigh;
  float tilt_comp_gain_scalar;
} weigh_app_interfaces__msg__LpsSaWeighInitDebugChannel;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaWeighInitDebugChannel.
typedef struct weigh_app_interfaces__msg__LpsSaWeighInitDebugChannel__Sequence
{
  weigh_app_interfaces__msg__LpsSaWeighInitDebugChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaWeighInitDebugChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__STRUCT_H_
