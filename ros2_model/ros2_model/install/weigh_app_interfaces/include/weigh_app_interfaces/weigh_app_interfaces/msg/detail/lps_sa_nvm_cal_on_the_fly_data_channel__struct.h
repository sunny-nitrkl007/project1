// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyDataChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_data_channel.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'lps_sa_nvm_calibration_data_on_the_fly'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_data_on_the_fly__struct.h"

/// Struct defined in msg/LpsSaNvmCalOnTheFlyDataChannel in the package weigh_app_interfaces.
/**
  * LpsSaNvmCalOnTheFlyDataChannelStorage
 */
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel
{
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataOnTheFly lps_sa_nvm_calibration_data_on_the_fly;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel.
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel__Sequence
{
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__STRUCT_H_
