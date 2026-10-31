// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyMiscUpdates.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_misc_updates.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LpsSaNvmCalOnTheFlyMiscUpdates in the package weigh_app_interfaces.
/**
  * LpsSaNvmCalOnTheFlyDataChannelStorage::LpsSaNvmCalOnTheFlyDataChannel_MiscUpdates_t
 */
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyMiscUpdates
{
  int32_t lift_he_pres_stat;
  int32_t lift_re_pres_stat;
  int32_t lift_cyl_length_norm_stat;
  int32_t hyd_oil_temp_stat;
  int32_t lift_cyl_vel_stat;
  int32_t tilt_cyl_length_norm_stat;
  int32_t bkt_angle_stat;
  bool lift_lever_info_lever_info_available;
  bool lift_lever_info_faulted;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyMiscUpdates;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyMiscUpdates.
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyMiscUpdates__Sequence
{
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyMiscUpdates * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyMiscUpdates__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__STRUCT_H_
