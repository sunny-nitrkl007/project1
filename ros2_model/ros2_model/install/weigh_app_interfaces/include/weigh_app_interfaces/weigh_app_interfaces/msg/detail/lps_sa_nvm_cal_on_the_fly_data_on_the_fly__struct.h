// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyDataOnTheFly.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_data_on_the_fly.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'status_flags'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_status_flags__struct.h"
// Member 'curve_info'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_curve_fit_info__struct.h"
// Member 'cal_updates'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_misc_updates__struct.h"
// Member 'cal_overrides'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_overrides__struct.h"

/// Struct defined in msg/LpsSaNvmCalOnTheFlyDataOnTheFly in the package weigh_app_interfaces.
/**
  * LpsSaNvmCalOnTheFlyDataChannelStorage::LpsSaNvmCalOnTheFlyDataChannel_DataOnTheFly_t
 */
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataOnTheFly
{
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyStatusFlags status_flags;
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyCurveFitInfo curve_info;
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyMiscUpdates cal_updates;
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyOverrides cal_overrides;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataOnTheFly;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataOnTheFly.
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataOnTheFly__Sequence
{
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataOnTheFly * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataOnTheFly__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__STRUCT_H_
