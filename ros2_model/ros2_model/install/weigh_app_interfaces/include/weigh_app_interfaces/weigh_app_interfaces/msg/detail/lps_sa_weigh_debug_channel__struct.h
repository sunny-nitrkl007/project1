// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaWeighDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_weigh_debug_channel.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'inst_wt_raw'
#include "cpm_common_interfaces/msg/detail/float_io__struct.h"
// Member 'tipoff_inputs'
#include "weigh_app_interfaces/msg/detail/tipoff_assist_inputs__struct.h"
// Member 'tipoff_outputs'
#include "weigh_app_interfaces/msg/detail/tipoff_assist_outputs__struct.h"

/// Struct defined in msg/LpsSaWeighDebugChannel in the package weigh_app_interfaces.
/**
  * LpsSaWeighDebugChannelStorage
 */
typedef struct weigh_app_interfaces__msg__LpsSaWeighDebugChannel
{
  uint16_t reweigh_warn;
  int32_t debug_lift_cyl_he_period;
  int32_t debug_lift_cyl_he_width;
  float debug_lift_cyl_he_dc;
  float debug_lift_cyl_he_press;
  int32_t debug_lift_cyl_he_press_status;
  int32_t debug_lift_cyl_re_period;
  int32_t debug_lift_cyl_re_width;
  float debug_lift_cyl_re_dc;
  float debug_lift_cyl_re_press;
  int32_t debug_lift_cyl_re_press_status;
  int32_t debug_tilt_cyl_he_period;
  int32_t debug_tilt_cyl_he_width;
  float debug_tilt_cyl_he_dc;
  float debug_tilt_cyl_he_press;
  int32_t debug_tilt_cyl_he_press_status;
  int32_t debug_tilt_cyl_re_period;
  int32_t debug_tilt_cyl_re_width;
  float debug_tilt_cyl_re_dc;
  float debug_tilt_cyl_re_press;
  int32_t debug_tilt_cyl_re_press_status;
  int32_t debug_lift_cyl_period;
  int32_t debug_lift_cyl_width;
  float debug_lift_cyl_dc;
  float debug_lift_cyl_raw_ext;
  float debug_lift_cyl_filt_ext;
  float debug_lift_cyl_norm_len;
  float debug_lift_cyl_vel;
  float debug_lift_angle;
  float debug_lift_ang_vel;
  int32_t debug_lift_position_status;
  int32_t debug_tilt_cyl_period;
  int32_t debug_tilt_cyl_width;
  float debug_tilt_cyl_dc;
  float debug_tilt_cyl_raw_len;
  float debug_tilt_cyl_norm_len;
  float debug_tilt_cyl_vel;
  float debug_tilt_angle;
  float debug_tilt_angle_abc;
  int32_t debug_tilt_position_status;
  float debug_bucket_angle;
  int32_t debug_bucket_angle_status;
  float debug_hyd_oil_temp;
  int32_t debug_hyd_oil_temp_status;
  uint16_t debug_requested_gear;
  int32_t debug_requested_gear_status;
  float debug_weigh_updt_loader_bkt_payld_trgt_wt;
  uint32_t debug_weigh_updt_clock_keyon_sec;
  uint32_t debug_weigh_updt_pass_count;
  float best_bkt_wt_payload_calc_meth;
  float best_bkt_wt_wt;
  bool best_bkt_wt_tipoff_live_weight_in_use;
  float cyl_flow_const_lift_he_flow_const;
  float cyl_flow_const_lift_re_to_he_flow_ratio;
  bool dig_detect_data_dig_detected;
  float dig_detect_data_dig_duration;
  bool dig_detect_data_dig_started;
  uint8_t dig_detect_data_dig_state;
  bool dig_detect_data_wt_stabilized;
  float dump_wt_change_data_dump_cumulative_wt_change;
  float inst_wt_der;
  float inst_wt_filt;
  float inst_wt_llw_filt;
  cpm_common_interfaces__msg__FloatIO inst_wt_raw;
  float inst_wt_raw_pre_tilt_comp;
  float inst_wt_raw_post_tilt_comp;
  float lift_cyl_pressure;
  float lift_cyl_pressure_v0;
  float lift_cyl_pressure_imu_adjusted;
  uint8_t live_weigh_tbl_stat;
  float live_weigh_tbl_wt;
  bool live_weigh_tbl_use_fast_filter;
  float low_lift_wt_wt;
  float low_lift_wt_confidence;
  float low_lift_wt_confidence_est;
  float low_lift_wt_confidence_timer;
  float low_lift_wt_last_input;
  float low_lift_wt_mean_est;
  float low_lift_wt_mean_est_comp;
  uint8_t low_lift_wt_stat;
  float low_lift_wt_stdev_est;
  float low_lift_wt_variance_est;
  uint8_t dump_state_status;
  bool lps_stall_detect_lift_stalled;
  float linkage_movement_lift;
  float linkage_movement_tilt;
  float wrw_tbl_wk_tbl_result_weight_ave_raw;
  float wrw_tbl_wk_tbl_result_weight_ave;
  float wrw_tbl_op_tbl_wt;
  bool wrw_tbl_op_tbl_warning;
  int32_t wrw_tbl_op_tbl_indicator;
  uint8_t wrw_tbl_op_tbl_status;
  float wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp;
  bool wrw_tbl_wk_tbl_been_below_range;
  uint8_t zero_adj_tbl_zero_adj_status;
  float overload_warn_tbl_bucket_load_factor;
  bool overload_warn_tbl_dig_reverse_flag;
  bool overload_warn_tbl_in_overload_range;
  uint8_t overload_warn_tbl_level;
  uint8_t overload_warn_tbl_prev_dig_state;
  float lift_position_filt_length;
  float lift_position_filt_velocity;
  float lift_position_filt_angle;
  weigh_app_interfaces__msg__TipoffAssistInputs tipoff_inputs;
  weigh_app_interfaces__msg__TipoffAssistOutputs tipoff_outputs;
  float chassis_imu_gravity_x;
  float chassis_imu_gravity_y;
  float chassis_imu_gravity_z;
  float chassis_imu_velocity_x;
  float chassis_imu_velocity_y;
  float chassis_imu_velocity_z;
  float chassis_imu_bias_mag_jerk;
  float chassis_imu_bias_mag_ang_accel;
  float chassis_imu_bias_max_ang_vel;
  float chassis_imu_bias_ang_vel_x;
  float chassis_imu_bias_ang_vel_y;
  float chassis_imu_bias_ang_vel_z;
  float chassis_imu_pitch;
  float chassis_imu_roll;
  uint8_t chassis_imu_sensor_lin_acc_status;
  uint8_t chassis_imu_sensor_ang_vel_status;
  float chassis_imu_lin_acc_x;
  float chassis_imu_lin_acc_y;
  float chassis_imu_lin_acc_z;
  float chassis_imu_ang_vel_x;
  float chassis_imu_ang_vel_y;
  float chassis_imu_ang_vel_z;
} weigh_app_interfaces__msg__LpsSaWeighDebugChannel;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaWeighDebugChannel.
typedef struct weigh_app_interfaces__msg__LpsSaWeighDebugChannel__Sequence
{
  weigh_app_interfaces__msg__LpsSaWeighDebugChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaWeighDebugChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__STRUCT_H_
