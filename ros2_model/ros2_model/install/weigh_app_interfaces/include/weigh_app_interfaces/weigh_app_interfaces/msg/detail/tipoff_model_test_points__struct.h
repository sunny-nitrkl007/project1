// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/TipoffModelTestPoints.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_model_test_points.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/TipoffModelTestPoints in the package weigh_app_interfaces.
/**
  * TipoffModelTestPointsStorage
 */
typedef struct weigh_app_interfaces__msg__TipoffModelTestPoints
{
  bool toa_pfw_sec_latch;
  float toa_pfw_sec_payload;
  uint8_t toa_pfw_sec_status;
  float toa_pfw_sec_st_dev;
  float toa_target_payload_final;
  bool toa_target_payload_status;
  float toa_pfw_nl_notch_mean_est;
  float toa_pfw_nl_notch_st_dev_est;
  float toa_lw_lpf_post;
  float toa_payload_adjusted;
  float toa_send_payload_arb;
  float toa_sfunc_in_grav_x;
  float toa_sfunc_in_grav_y;
  float toa_sfunc_in_lift_force;
  float toa_sfunc_in_tilt_force;
  float toa_sfunc_out_raw_mass_tonne;
  uint32_t toa_app_number;
  float toa_lift_bore_dia;
  float toa_lift_rod_dia;
  float toa_payload_anc_adjusted;
  float toa_payload_anc_zeroed;
  float toa_rated_payload;
  float toa_tilt_bore_dia;
  uint8_t toa_tilt_num_cyl;
  float toa_tilt_rod_dia;
  float toa_tool_bc_length;
  float toa_imu_cal_pitch_angle;
  uint8_t toa_pfw_unsec_status;
  float toa_pfw_unsec_bound_lower;
  float toa_pfw_unsec_bound_upper;
  float toa_lw_spill_rate;
  uint8_t toa_lw_status;
  float toa_raw_dist;
  float toa_raw_payload;
  float toa_payload_zeroed;
  bool toa_pfw_is_warm;
  bool toa_pfw_sec_is_secure;
  bool toa_pfw_sec_is_no_sliding;
  bool toa_pfw_sec_is_no_collapsing;
  bool toa_pfw_sec_is_racked;
  float toa_pfw_sec_min_bucket_ang;
  bool toa_pfw_mc_ok;
  bool toa_pfw_mc_maybe_stalled;
  bool toa_pfw_mc_maybe_rack_stall;
  bool toa_pfw_mc_maybe_grounded;
  float toa_stat_payload_nl_notch_one_up;
  float toa_stat_payload_nl_notch_one_low;
  float toa_stat_payload_nl_notch_one_size;
  float toa_stat_payload_nl_notch_two_up;
  float toa_stat_payload_nl_notch_two_low;
  float toa_stat_payload_nl_notch_two_size;
  float toa_stat_payload_nl_one_up;
  float toa_stat_payload_nl_one_low;
  float toa_stat_payload_nl_one_size;
  float toa_stat_payload_nl_two_up;
  float toa_stat_payload_nl_two_low;
  float toa_stat_payload_nl_two_size;
  float toa_pfw_nl_st_dev_est;
  float toa_pfw_nl_mean_est;
  float toa_pfw_payload_filt_final;
  float toa_pfw_payload_notch_filt_final;
  float toa_pfw_payload_notch_post;
  bool toa_pfw_latch_invalidate;
  float toa_imu_raw_eef_accl_x;
  float toa_imu_raw_eef_accl_y;
  float toa_imu_raw_eef_accl_z;
  float toa_imu_neef_grav_x;
  float toa_imu_neef_grav_y;
  float toa_imu_neef_grav_z;
  float toa_imu_neef_pitch;
  float toa_target_comp_margin;
  float toa_target_payload_post_comp;
  float toa_target_payload_pre_comp;
  float toa_stat_payload_secure_two_size;
  float toa_stat_payload_secure_one_upper;
  float toa_stat_payload_secure_one_lower;
  float toa_stat_payload_secure_one_size;
  float toa_stat_payload_secure_two_upper;
  float toa_stat_payload_secure_two_lower;
  float toa_send_cpm_live_payload;
  float toa_tool_bc_angle;
} weigh_app_interfaces__msg__TipoffModelTestPoints;

// Struct for a sequence of weigh_app_interfaces__msg__TipoffModelTestPoints.
typedef struct weigh_app_interfaces__msg__TipoffModelTestPoints__Sequence
{
  weigh_app_interfaces__msg__TipoffModelTestPoints * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__TipoffModelTestPoints__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__STRUCT_H_
