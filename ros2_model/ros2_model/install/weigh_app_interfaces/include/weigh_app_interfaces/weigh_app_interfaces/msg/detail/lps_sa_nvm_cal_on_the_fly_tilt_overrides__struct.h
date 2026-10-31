// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyTiltOverrides.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_tilt_overrides.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LpsSaNvmCalOnTheFlyTiltOverrides in the package weigh_app_interfaces.
/**
  * LpsSaNvmCalOnTheFlyTiltOverrides_t
 */
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides
{
  uint8_t lps_cal_tilt_ovr_state;
  float tilt_noise_max;
  float tilt_noise_min;
  float desired_tilt_extmm;
  uint8_t count_of_samples;
  float tilt_dump_cmd_ovr;
  bool lps_cal_tilt_ovr_start_request;
  bool cal_tilt_override_complete;
  bool cal_tilt_override_fail;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides.
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence
{
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__STRUCT_H_
