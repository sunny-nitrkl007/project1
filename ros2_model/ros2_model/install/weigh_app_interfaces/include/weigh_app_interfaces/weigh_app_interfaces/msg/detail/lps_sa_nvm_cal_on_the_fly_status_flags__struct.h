// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyStatusFlags.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_status_flags.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LpsSaNvmCalOnTheFlyStatusFlags in the package weigh_app_interfaces.
/**
  * LpsSaNvmCalOnTheFlyDataChannelStorage::LpsSaNvmCalOnTheFlyDataChannel_StatusFlags_t
 */
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyStatusFlags
{
  bool cal_in_progress;
  bool empty_bkt_cal_done;
  bool full_bkt_cal_done;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyStatusFlags;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyStatusFlags.
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyStatusFlags__Sequence
{
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyStatusFlags * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyStatusFlags__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__STRUCT_H_
