// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannelDataMain.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel_data_main.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LpsSaNvmCalDataChannelDataMain in the package weigh_app_interfaces.
/**
  * LpsSaNvmCalDataChannelStorage::LpsSaNvmCalDataChannel_DataMain_t
 */
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataMain
{
  float raise_slow_empty_lift_heights[11];
  float raise_slow_empty_pressures[11];
  float lower_slow_empty_lift_heights[11];
  float lower_slow_empty_pressures[11];
  float raise_slow_full_lift_heights[11];
  float raise_slow_full_pressures[11];
  float lower_slow_full_lift_heights[11];
  float lower_slow_full_pressures[11];
  float raise_speed_empty_slow;
  float raise_speed_empty_fast;
  float raise_fast_delta_p_empty;
  float raise_speed_full_slow;
  float raise_speed_full_fast;
  float raise_fast_delta_p_full;
} weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataMain;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataMain.
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataMain__Sequence
{
  weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataMain * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataMain__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__STRUCT_H_
