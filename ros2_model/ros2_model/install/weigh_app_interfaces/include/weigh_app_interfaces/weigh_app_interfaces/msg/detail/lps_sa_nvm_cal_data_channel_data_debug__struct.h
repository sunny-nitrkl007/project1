// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannelDataDebug.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel_data_debug.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LpsSaNvmCalDataChannelDataDebug in the package weigh_app_interfaces.
/**
  * LpsSaNvmCalDataChannelStorage::LpsSaNvmCalDataChannel_DataDebug_t
 */
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataDebug
{
  int32_t lift_full_lower_dc_inf_value;
  int32_t lift_full_raise_dc_inf_value;
  int32_t tilt_full_dump_dc_inf_value;
  int32_t tilt_full_rack_dc_inf_value;
  int32_t tilt_dump_stop_angle_inf_value;
  int32_t tilt_rack_stop_angle_inf_value;
  float pcs_vel_slope;
  float pcs_cal_weight;
  float zero_weight;
  float cal_adjust;
  float temp_slope;
  float empty_temp;
  float full_temp;
  float empty_bucket_weight_est;
  float cal_adjust_temp;
  int32_t hyd_oil_type_index;
} weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataDebug;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataDebug.
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataDebug__Sequence
{
  weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataDebug * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataDebug__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__STRUCT_H_
