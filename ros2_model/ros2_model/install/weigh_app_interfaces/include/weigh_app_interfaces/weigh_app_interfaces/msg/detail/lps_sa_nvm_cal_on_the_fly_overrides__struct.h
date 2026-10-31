// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyOverrides.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_overrides.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'tilt_overrides'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_tilt_overrides__struct.h"

/// Struct defined in msg/LpsSaNvmCalOnTheFlyOverrides in the package weigh_app_interfaces.
/**
  * LpsSaNvmCalOnTheFlyDataChannelStorage::LpsSaNvmCalOnTheFlyDataChannel_Overrides_t
 */
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyOverrides
{
  uint8_t lps_cal_ovr_state;
  int8_t lps_cal_app_inf_raise_cmd_lmt;
  int8_t lps_cal_app_inf_lower_cmd_lmt;
  int8_t lps_cal_app_inf_rack_cmd_lmt;
  int8_t lps_cal_app_inf_dump_cmd_lmt;
  int16_t lps_cal_app_inf_eng_spd_lmt;
  bool lps_cal_app_inf_cal_ovr_active;
  bool lift_bottom_flag;
  bool lift_top_flag;
  bool cal_ovr_acknowledge;
  float lift_valve_cmd_percent;
  bool lift_in_raise_detent;
  bool lift_in_lower_detent;
  bool lift_in_center;
  bool lift_faulted;
  bool lever_info_available;
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides tilt_overrides;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyOverrides;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyOverrides.
typedef struct weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyOverrides__Sequence
{
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyOverrides * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyOverrides__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__STRUCT_H_
