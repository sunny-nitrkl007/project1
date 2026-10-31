// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'lps_sa_nvm_calibration_data_main'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel_data_main__struct.h"
// Member 'lps_sa_nvm_calibration_data_debug'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel_data_debug__struct.h"
// Member 'imu_cal_results'
#include "weigh_app_interfaces/msg/detail/lps_cal_imu_results__struct.h"

/// Struct defined in msg/LpsSaNvmCalDataChannel in the package weigh_app_interfaces.
/**
  * LpsSaNvmCalDataChannelStorage
 */
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalDataChannel
{
  weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataMain lps_sa_nvm_calibration_data_main;
  weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataDebug lps_sa_nvm_calibration_data_debug;
  weigh_app_interfaces__msg__LpsCalIMUResults imu_cal_results;
} weigh_app_interfaces__msg__LpsSaNvmCalDataChannel;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaNvmCalDataChannel.
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalDataChannel__Sequence
{
  weigh_app_interfaces__msg__LpsSaNvmCalDataChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaNvmCalDataChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__STRUCT_H_
