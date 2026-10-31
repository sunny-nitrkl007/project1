// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyCurveFitInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_curve_fit_info.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'imu_cal_results'
#include "weigh_app_interfaces/msg/detail/lps_cal_imu_results__struct.h"

/// Struct defined in msg/LpsSaNvmCalOnTheFlyCurveFitInfo in the package weigh_app_interfaces.
/**
  * LpsSaNvmCalOnTheFlyDataChannelStorage::LpsSaNvmCalOnTheFlyDataChannel_CurveFitInfo_t
 */
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyCurveFitInfo
{
  bool hyd_oil_temp_met;
  bool enforce_raise_detent;
  bool enforce_lower_detent;
  bool raise_fast_vel_done;
  bool raise_slow_fit_done;
  bool raise_fast_fit_done;
  bool lower_slow_fit_done;
  uint8_t internal_step;
  uint16_t raise_num_points;
  uint16_t lower_num_points;
  weigh_app_interfaces__msg__LpsCalIMUResults imu_cal_results;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyCurveFitInfo;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyCurveFitInfo.
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyCurveFitInfo__Sequence
{
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyCurveFitInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyCurveFitInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__STRUCT_H_
