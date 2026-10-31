// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaWeighDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_weigh_debug_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_weigh_debug_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'inst_wt_raw'
#include "cpm_common_interfaces/msg/detail/float_io__traits.hpp"
// Member 'tipoff_inputs'
#include "weigh_app_interfaces/msg/detail/tipoff_assist_inputs__traits.hpp"
// Member 'tipoff_outputs'
#include "weigh_app_interfaces/msg/detail/tipoff_assist_outputs__traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaWeighDebugChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: reweigh_warn
  {
    out << "reweigh_warn: ";
    rosidl_generator_traits::value_to_yaml(msg.reweigh_warn, out);
    out << ", ";
  }

  // member: debug_lift_cyl_he_period
  {
    out << "debug_lift_cyl_he_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_he_period, out);
    out << ", ";
  }

  // member: debug_lift_cyl_he_width
  {
    out << "debug_lift_cyl_he_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_he_width, out);
    out << ", ";
  }

  // member: debug_lift_cyl_he_dc
  {
    out << "debug_lift_cyl_he_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_he_dc, out);
    out << ", ";
  }

  // member: debug_lift_cyl_he_press
  {
    out << "debug_lift_cyl_he_press: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_he_press, out);
    out << ", ";
  }

  // member: debug_lift_cyl_he_press_status
  {
    out << "debug_lift_cyl_he_press_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_he_press_status, out);
    out << ", ";
  }

  // member: debug_lift_cyl_re_period
  {
    out << "debug_lift_cyl_re_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_re_period, out);
    out << ", ";
  }

  // member: debug_lift_cyl_re_width
  {
    out << "debug_lift_cyl_re_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_re_width, out);
    out << ", ";
  }

  // member: debug_lift_cyl_re_dc
  {
    out << "debug_lift_cyl_re_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_re_dc, out);
    out << ", ";
  }

  // member: debug_lift_cyl_re_press
  {
    out << "debug_lift_cyl_re_press: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_re_press, out);
    out << ", ";
  }

  // member: debug_lift_cyl_re_press_status
  {
    out << "debug_lift_cyl_re_press_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_re_press_status, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_he_period
  {
    out << "debug_tilt_cyl_he_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_he_period, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_he_width
  {
    out << "debug_tilt_cyl_he_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_he_width, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_he_dc
  {
    out << "debug_tilt_cyl_he_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_he_dc, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_he_press
  {
    out << "debug_tilt_cyl_he_press: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_he_press, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_he_press_status
  {
    out << "debug_tilt_cyl_he_press_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_he_press_status, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_re_period
  {
    out << "debug_tilt_cyl_re_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_re_period, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_re_width
  {
    out << "debug_tilt_cyl_re_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_re_width, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_re_dc
  {
    out << "debug_tilt_cyl_re_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_re_dc, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_re_press
  {
    out << "debug_tilt_cyl_re_press: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_re_press, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_re_press_status
  {
    out << "debug_tilt_cyl_re_press_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_re_press_status, out);
    out << ", ";
  }

  // member: debug_lift_cyl_period
  {
    out << "debug_lift_cyl_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_period, out);
    out << ", ";
  }

  // member: debug_lift_cyl_width
  {
    out << "debug_lift_cyl_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_width, out);
    out << ", ";
  }

  // member: debug_lift_cyl_dc
  {
    out << "debug_lift_cyl_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_dc, out);
    out << ", ";
  }

  // member: debug_lift_cyl_raw_ext
  {
    out << "debug_lift_cyl_raw_ext: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_raw_ext, out);
    out << ", ";
  }

  // member: debug_lift_cyl_filt_ext
  {
    out << "debug_lift_cyl_filt_ext: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_filt_ext, out);
    out << ", ";
  }

  // member: debug_lift_cyl_norm_len
  {
    out << "debug_lift_cyl_norm_len: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_norm_len, out);
    out << ", ";
  }

  // member: debug_lift_cyl_vel
  {
    out << "debug_lift_cyl_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_vel, out);
    out << ", ";
  }

  // member: debug_lift_angle
  {
    out << "debug_lift_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_angle, out);
    out << ", ";
  }

  // member: debug_lift_ang_vel
  {
    out << "debug_lift_ang_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_ang_vel, out);
    out << ", ";
  }

  // member: debug_lift_position_status
  {
    out << "debug_lift_position_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_position_status, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_period
  {
    out << "debug_tilt_cyl_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_period, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_width
  {
    out << "debug_tilt_cyl_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_width, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_dc
  {
    out << "debug_tilt_cyl_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_dc, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_raw_len
  {
    out << "debug_tilt_cyl_raw_len: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_raw_len, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_norm_len
  {
    out << "debug_tilt_cyl_norm_len: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_norm_len, out);
    out << ", ";
  }

  // member: debug_tilt_cyl_vel
  {
    out << "debug_tilt_cyl_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_vel, out);
    out << ", ";
  }

  // member: debug_tilt_angle
  {
    out << "debug_tilt_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_angle, out);
    out << ", ";
  }

  // member: debug_tilt_angle_abc
  {
    out << "debug_tilt_angle_abc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_angle_abc, out);
    out << ", ";
  }

  // member: debug_tilt_position_status
  {
    out << "debug_tilt_position_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_position_status, out);
    out << ", ";
  }

  // member: debug_bucket_angle
  {
    out << "debug_bucket_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_bucket_angle, out);
    out << ", ";
  }

  // member: debug_bucket_angle_status
  {
    out << "debug_bucket_angle_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_bucket_angle_status, out);
    out << ", ";
  }

  // member: debug_hyd_oil_temp
  {
    out << "debug_hyd_oil_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_hyd_oil_temp, out);
    out << ", ";
  }

  // member: debug_hyd_oil_temp_status
  {
    out << "debug_hyd_oil_temp_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_hyd_oil_temp_status, out);
    out << ", ";
  }

  // member: debug_requested_gear
  {
    out << "debug_requested_gear: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_requested_gear, out);
    out << ", ";
  }

  // member: debug_requested_gear_status
  {
    out << "debug_requested_gear_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_requested_gear_status, out);
    out << ", ";
  }

  // member: debug_weigh_updt_loader_bkt_payld_trgt_wt
  {
    out << "debug_weigh_updt_loader_bkt_payld_trgt_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_weigh_updt_loader_bkt_payld_trgt_wt, out);
    out << ", ";
  }

  // member: debug_weigh_updt_clock_keyon_sec
  {
    out << "debug_weigh_updt_clock_keyon_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_weigh_updt_clock_keyon_sec, out);
    out << ", ";
  }

  // member: debug_weigh_updt_pass_count
  {
    out << "debug_weigh_updt_pass_count: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_weigh_updt_pass_count, out);
    out << ", ";
  }

  // member: best_bkt_wt_payload_calc_meth
  {
    out << "best_bkt_wt_payload_calc_meth: ";
    rosidl_generator_traits::value_to_yaml(msg.best_bkt_wt_payload_calc_meth, out);
    out << ", ";
  }

  // member: best_bkt_wt_wt
  {
    out << "best_bkt_wt_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.best_bkt_wt_wt, out);
    out << ", ";
  }

  // member: best_bkt_wt_tipoff_live_weight_in_use
  {
    out << "best_bkt_wt_tipoff_live_weight_in_use: ";
    rosidl_generator_traits::value_to_yaml(msg.best_bkt_wt_tipoff_live_weight_in_use, out);
    out << ", ";
  }

  // member: cyl_flow_const_lift_he_flow_const
  {
    out << "cyl_flow_const_lift_he_flow_const: ";
    rosidl_generator_traits::value_to_yaml(msg.cyl_flow_const_lift_he_flow_const, out);
    out << ", ";
  }

  // member: cyl_flow_const_lift_re_to_he_flow_ratio
  {
    out << "cyl_flow_const_lift_re_to_he_flow_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.cyl_flow_const_lift_re_to_he_flow_ratio, out);
    out << ", ";
  }

  // member: dig_detect_data_dig_detected
  {
    out << "dig_detect_data_dig_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_detect_data_dig_detected, out);
    out << ", ";
  }

  // member: dig_detect_data_dig_duration
  {
    out << "dig_detect_data_dig_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_detect_data_dig_duration, out);
    out << ", ";
  }

  // member: dig_detect_data_dig_started
  {
    out << "dig_detect_data_dig_started: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_detect_data_dig_started, out);
    out << ", ";
  }

  // member: dig_detect_data_dig_state
  {
    out << "dig_detect_data_dig_state: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_detect_data_dig_state, out);
    out << ", ";
  }

  // member: dig_detect_data_wt_stabilized
  {
    out << "dig_detect_data_wt_stabilized: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_detect_data_wt_stabilized, out);
    out << ", ";
  }

  // member: dump_wt_change_data_dump_cumulative_wt_change
  {
    out << "dump_wt_change_data_dump_cumulative_wt_change: ";
    rosidl_generator_traits::value_to_yaml(msg.dump_wt_change_data_dump_cumulative_wt_change, out);
    out << ", ";
  }

  // member: inst_wt_der
  {
    out << "inst_wt_der: ";
    rosidl_generator_traits::value_to_yaml(msg.inst_wt_der, out);
    out << ", ";
  }

  // member: inst_wt_filt
  {
    out << "inst_wt_filt: ";
    rosidl_generator_traits::value_to_yaml(msg.inst_wt_filt, out);
    out << ", ";
  }

  // member: inst_wt_llw_filt
  {
    out << "inst_wt_llw_filt: ";
    rosidl_generator_traits::value_to_yaml(msg.inst_wt_llw_filt, out);
    out << ", ";
  }

  // member: inst_wt_raw
  {
    out << "inst_wt_raw: ";
    to_flow_style_yaml(msg.inst_wt_raw, out);
    out << ", ";
  }

  // member: inst_wt_raw_pre_tilt_comp
  {
    out << "inst_wt_raw_pre_tilt_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.inst_wt_raw_pre_tilt_comp, out);
    out << ", ";
  }

  // member: inst_wt_raw_post_tilt_comp
  {
    out << "inst_wt_raw_post_tilt_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.inst_wt_raw_post_tilt_comp, out);
    out << ", ";
  }

  // member: lift_cyl_pressure
  {
    out << "lift_cyl_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_pressure, out);
    out << ", ";
  }

  // member: lift_cyl_pressure_v0
  {
    out << "lift_cyl_pressure_v0: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_pressure_v0, out);
    out << ", ";
  }

  // member: lift_cyl_pressure_imu_adjusted
  {
    out << "lift_cyl_pressure_imu_adjusted: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_pressure_imu_adjusted, out);
    out << ", ";
  }

  // member: live_weigh_tbl_stat
  {
    out << "live_weigh_tbl_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.live_weigh_tbl_stat, out);
    out << ", ";
  }

  // member: live_weigh_tbl_wt
  {
    out << "live_weigh_tbl_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.live_weigh_tbl_wt, out);
    out << ", ";
  }

  // member: live_weigh_tbl_use_fast_filter
  {
    out << "live_weigh_tbl_use_fast_filter: ";
    rosidl_generator_traits::value_to_yaml(msg.live_weigh_tbl_use_fast_filter, out);
    out << ", ";
  }

  // member: low_lift_wt_wt
  {
    out << "low_lift_wt_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_wt, out);
    out << ", ";
  }

  // member: low_lift_wt_confidence
  {
    out << "low_lift_wt_confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_confidence, out);
    out << ", ";
  }

  // member: low_lift_wt_confidence_est
  {
    out << "low_lift_wt_confidence_est: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_confidence_est, out);
    out << ", ";
  }

  // member: low_lift_wt_confidence_timer
  {
    out << "low_lift_wt_confidence_timer: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_confidence_timer, out);
    out << ", ";
  }

  // member: low_lift_wt_last_input
  {
    out << "low_lift_wt_last_input: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_last_input, out);
    out << ", ";
  }

  // member: low_lift_wt_mean_est
  {
    out << "low_lift_wt_mean_est: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_mean_est, out);
    out << ", ";
  }

  // member: low_lift_wt_mean_est_comp
  {
    out << "low_lift_wt_mean_est_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_mean_est_comp, out);
    out << ", ";
  }

  // member: low_lift_wt_stat
  {
    out << "low_lift_wt_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_stat, out);
    out << ", ";
  }

  // member: low_lift_wt_stdev_est
  {
    out << "low_lift_wt_stdev_est: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_stdev_est, out);
    out << ", ";
  }

  // member: low_lift_wt_variance_est
  {
    out << "low_lift_wt_variance_est: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_variance_est, out);
    out << ", ";
  }

  // member: dump_state_status
  {
    out << "dump_state_status: ";
    rosidl_generator_traits::value_to_yaml(msg.dump_state_status, out);
    out << ", ";
  }

  // member: lps_stall_detect_lift_stalled
  {
    out << "lps_stall_detect_lift_stalled: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_stall_detect_lift_stalled, out);
    out << ", ";
  }

  // member: linkage_movement_lift
  {
    out << "linkage_movement_lift: ";
    rosidl_generator_traits::value_to_yaml(msg.linkage_movement_lift, out);
    out << ", ";
  }

  // member: linkage_movement_tilt
  {
    out << "linkage_movement_tilt: ";
    rosidl_generator_traits::value_to_yaml(msg.linkage_movement_tilt, out);
    out << ", ";
  }

  // member: wrw_tbl_wk_tbl_result_weight_ave_raw
  {
    out << "wrw_tbl_wk_tbl_result_weight_ave_raw: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_wk_tbl_result_weight_ave_raw, out);
    out << ", ";
  }

  // member: wrw_tbl_wk_tbl_result_weight_ave
  {
    out << "wrw_tbl_wk_tbl_result_weight_ave: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_wk_tbl_result_weight_ave, out);
    out << ", ";
  }

  // member: wrw_tbl_op_tbl_wt
  {
    out << "wrw_tbl_op_tbl_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_op_tbl_wt, out);
    out << ", ";
  }

  // member: wrw_tbl_op_tbl_warning
  {
    out << "wrw_tbl_op_tbl_warning: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_op_tbl_warning, out);
    out << ", ";
  }

  // member: wrw_tbl_op_tbl_indicator
  {
    out << "wrw_tbl_op_tbl_indicator: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_op_tbl_indicator, out);
    out << ", ";
  }

  // member: wrw_tbl_op_tbl_status
  {
    out << "wrw_tbl_op_tbl_status: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_op_tbl_status, out);
    out << ", ";
  }

  // member: wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp
  {
    out << "wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp, out);
    out << ", ";
  }

  // member: wrw_tbl_wk_tbl_been_below_range
  {
    out << "wrw_tbl_wk_tbl_been_below_range: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_wk_tbl_been_below_range, out);
    out << ", ";
  }

  // member: zero_adj_tbl_zero_adj_status
  {
    out << "zero_adj_tbl_zero_adj_status: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_adj_tbl_zero_adj_status, out);
    out << ", ";
  }

  // member: overload_warn_tbl_bucket_load_factor
  {
    out << "overload_warn_tbl_bucket_load_factor: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warn_tbl_bucket_load_factor, out);
    out << ", ";
  }

  // member: overload_warn_tbl_dig_reverse_flag
  {
    out << "overload_warn_tbl_dig_reverse_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warn_tbl_dig_reverse_flag, out);
    out << ", ";
  }

  // member: overload_warn_tbl_in_overload_range
  {
    out << "overload_warn_tbl_in_overload_range: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warn_tbl_in_overload_range, out);
    out << ", ";
  }

  // member: overload_warn_tbl_level
  {
    out << "overload_warn_tbl_level: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warn_tbl_level, out);
    out << ", ";
  }

  // member: overload_warn_tbl_prev_dig_state
  {
    out << "overload_warn_tbl_prev_dig_state: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warn_tbl_prev_dig_state, out);
    out << ", ";
  }

  // member: lift_position_filt_length
  {
    out << "lift_position_filt_length: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_position_filt_length, out);
    out << ", ";
  }

  // member: lift_position_filt_velocity
  {
    out << "lift_position_filt_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_position_filt_velocity, out);
    out << ", ";
  }

  // member: lift_position_filt_angle
  {
    out << "lift_position_filt_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_position_filt_angle, out);
    out << ", ";
  }

  // member: tipoff_inputs
  {
    out << "tipoff_inputs: ";
    to_flow_style_yaml(msg.tipoff_inputs, out);
    out << ", ";
  }

  // member: tipoff_outputs
  {
    out << "tipoff_outputs: ";
    to_flow_style_yaml(msg.tipoff_outputs, out);
    out << ", ";
  }

  // member: chassis_imu_gravity_x
  {
    out << "chassis_imu_gravity_x: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_gravity_x, out);
    out << ", ";
  }

  // member: chassis_imu_gravity_y
  {
    out << "chassis_imu_gravity_y: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_gravity_y, out);
    out << ", ";
  }

  // member: chassis_imu_gravity_z
  {
    out << "chassis_imu_gravity_z: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_gravity_z, out);
    out << ", ";
  }

  // member: chassis_imu_velocity_x
  {
    out << "chassis_imu_velocity_x: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_velocity_x, out);
    out << ", ";
  }

  // member: chassis_imu_velocity_y
  {
    out << "chassis_imu_velocity_y: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_velocity_y, out);
    out << ", ";
  }

  // member: chassis_imu_velocity_z
  {
    out << "chassis_imu_velocity_z: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_velocity_z, out);
    out << ", ";
  }

  // member: chassis_imu_bias_mag_jerk
  {
    out << "chassis_imu_bias_mag_jerk: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_mag_jerk, out);
    out << ", ";
  }

  // member: chassis_imu_bias_mag_ang_accel
  {
    out << "chassis_imu_bias_mag_ang_accel: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_mag_ang_accel, out);
    out << ", ";
  }

  // member: chassis_imu_bias_max_ang_vel
  {
    out << "chassis_imu_bias_max_ang_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_max_ang_vel, out);
    out << ", ";
  }

  // member: chassis_imu_bias_ang_vel_x
  {
    out << "chassis_imu_bias_ang_vel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_ang_vel_x, out);
    out << ", ";
  }

  // member: chassis_imu_bias_ang_vel_y
  {
    out << "chassis_imu_bias_ang_vel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_ang_vel_y, out);
    out << ", ";
  }

  // member: chassis_imu_bias_ang_vel_z
  {
    out << "chassis_imu_bias_ang_vel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_ang_vel_z, out);
    out << ", ";
  }

  // member: chassis_imu_pitch
  {
    out << "chassis_imu_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_pitch, out);
    out << ", ";
  }

  // member: chassis_imu_roll
  {
    out << "chassis_imu_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_roll, out);
    out << ", ";
  }

  // member: chassis_imu_sensor_lin_acc_status
  {
    out << "chassis_imu_sensor_lin_acc_status: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_sensor_lin_acc_status, out);
    out << ", ";
  }

  // member: chassis_imu_sensor_ang_vel_status
  {
    out << "chassis_imu_sensor_ang_vel_status: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_sensor_ang_vel_status, out);
    out << ", ";
  }

  // member: chassis_imu_lin_acc_x
  {
    out << "chassis_imu_lin_acc_x: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_lin_acc_x, out);
    out << ", ";
  }

  // member: chassis_imu_lin_acc_y
  {
    out << "chassis_imu_lin_acc_y: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_lin_acc_y, out);
    out << ", ";
  }

  // member: chassis_imu_lin_acc_z
  {
    out << "chassis_imu_lin_acc_z: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_lin_acc_z, out);
    out << ", ";
  }

  // member: chassis_imu_ang_vel_x
  {
    out << "chassis_imu_ang_vel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_ang_vel_x, out);
    out << ", ";
  }

  // member: chassis_imu_ang_vel_y
  {
    out << "chassis_imu_ang_vel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_ang_vel_y, out);
    out << ", ";
  }

  // member: chassis_imu_ang_vel_z
  {
    out << "chassis_imu_ang_vel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_ang_vel_z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaWeighDebugChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: reweigh_warn
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reweigh_warn: ";
    rosidl_generator_traits::value_to_yaml(msg.reweigh_warn, out);
    out << "\n";
  }

  // member: debug_lift_cyl_he_period
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_he_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_he_period, out);
    out << "\n";
  }

  // member: debug_lift_cyl_he_width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_he_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_he_width, out);
    out << "\n";
  }

  // member: debug_lift_cyl_he_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_he_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_he_dc, out);
    out << "\n";
  }

  // member: debug_lift_cyl_he_press
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_he_press: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_he_press, out);
    out << "\n";
  }

  // member: debug_lift_cyl_he_press_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_he_press_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_he_press_status, out);
    out << "\n";
  }

  // member: debug_lift_cyl_re_period
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_re_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_re_period, out);
    out << "\n";
  }

  // member: debug_lift_cyl_re_width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_re_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_re_width, out);
    out << "\n";
  }

  // member: debug_lift_cyl_re_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_re_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_re_dc, out);
    out << "\n";
  }

  // member: debug_lift_cyl_re_press
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_re_press: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_re_press, out);
    out << "\n";
  }

  // member: debug_lift_cyl_re_press_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_re_press_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_re_press_status, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_he_period
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_he_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_he_period, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_he_width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_he_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_he_width, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_he_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_he_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_he_dc, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_he_press
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_he_press: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_he_press, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_he_press_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_he_press_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_he_press_status, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_re_period
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_re_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_re_period, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_re_width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_re_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_re_width, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_re_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_re_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_re_dc, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_re_press
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_re_press: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_re_press, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_re_press_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_re_press_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_re_press_status, out);
    out << "\n";
  }

  // member: debug_lift_cyl_period
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_period, out);
    out << "\n";
  }

  // member: debug_lift_cyl_width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_width, out);
    out << "\n";
  }

  // member: debug_lift_cyl_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_dc, out);
    out << "\n";
  }

  // member: debug_lift_cyl_raw_ext
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_raw_ext: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_raw_ext, out);
    out << "\n";
  }

  // member: debug_lift_cyl_filt_ext
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_filt_ext: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_filt_ext, out);
    out << "\n";
  }

  // member: debug_lift_cyl_norm_len
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_norm_len: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_norm_len, out);
    out << "\n";
  }

  // member: debug_lift_cyl_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_cyl_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_cyl_vel, out);
    out << "\n";
  }

  // member: debug_lift_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_angle, out);
    out << "\n";
  }

  // member: debug_lift_ang_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_ang_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_ang_vel, out);
    out << "\n";
  }

  // member: debug_lift_position_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_lift_position_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_lift_position_status, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_period
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_period: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_period, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_width: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_width, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_dc, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_raw_len
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_raw_len: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_raw_len, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_norm_len
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_norm_len: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_norm_len, out);
    out << "\n";
  }

  // member: debug_tilt_cyl_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_cyl_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_cyl_vel, out);
    out << "\n";
  }

  // member: debug_tilt_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_angle, out);
    out << "\n";
  }

  // member: debug_tilt_angle_abc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_angle_abc: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_angle_abc, out);
    out << "\n";
  }

  // member: debug_tilt_position_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_tilt_position_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_tilt_position_status, out);
    out << "\n";
  }

  // member: debug_bucket_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_bucket_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_bucket_angle, out);
    out << "\n";
  }

  // member: debug_bucket_angle_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_bucket_angle_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_bucket_angle_status, out);
    out << "\n";
  }

  // member: debug_hyd_oil_temp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_hyd_oil_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_hyd_oil_temp, out);
    out << "\n";
  }

  // member: debug_hyd_oil_temp_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_hyd_oil_temp_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_hyd_oil_temp_status, out);
    out << "\n";
  }

  // member: debug_requested_gear
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_requested_gear: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_requested_gear, out);
    out << "\n";
  }

  // member: debug_requested_gear_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_requested_gear_status: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_requested_gear_status, out);
    out << "\n";
  }

  // member: debug_weigh_updt_loader_bkt_payld_trgt_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_weigh_updt_loader_bkt_payld_trgt_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_weigh_updt_loader_bkt_payld_trgt_wt, out);
    out << "\n";
  }

  // member: debug_weigh_updt_clock_keyon_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_weigh_updt_clock_keyon_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_weigh_updt_clock_keyon_sec, out);
    out << "\n";
  }

  // member: debug_weigh_updt_pass_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "debug_weigh_updt_pass_count: ";
    rosidl_generator_traits::value_to_yaml(msg.debug_weigh_updt_pass_count, out);
    out << "\n";
  }

  // member: best_bkt_wt_payload_calc_meth
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "best_bkt_wt_payload_calc_meth: ";
    rosidl_generator_traits::value_to_yaml(msg.best_bkt_wt_payload_calc_meth, out);
    out << "\n";
  }

  // member: best_bkt_wt_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "best_bkt_wt_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.best_bkt_wt_wt, out);
    out << "\n";
  }

  // member: best_bkt_wt_tipoff_live_weight_in_use
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "best_bkt_wt_tipoff_live_weight_in_use: ";
    rosidl_generator_traits::value_to_yaml(msg.best_bkt_wt_tipoff_live_weight_in_use, out);
    out << "\n";
  }

  // member: cyl_flow_const_lift_he_flow_const
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cyl_flow_const_lift_he_flow_const: ";
    rosidl_generator_traits::value_to_yaml(msg.cyl_flow_const_lift_he_flow_const, out);
    out << "\n";
  }

  // member: cyl_flow_const_lift_re_to_he_flow_ratio
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cyl_flow_const_lift_re_to_he_flow_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.cyl_flow_const_lift_re_to_he_flow_ratio, out);
    out << "\n";
  }

  // member: dig_detect_data_dig_detected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dig_detect_data_dig_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_detect_data_dig_detected, out);
    out << "\n";
  }

  // member: dig_detect_data_dig_duration
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dig_detect_data_dig_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_detect_data_dig_duration, out);
    out << "\n";
  }

  // member: dig_detect_data_dig_started
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dig_detect_data_dig_started: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_detect_data_dig_started, out);
    out << "\n";
  }

  // member: dig_detect_data_dig_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dig_detect_data_dig_state: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_detect_data_dig_state, out);
    out << "\n";
  }

  // member: dig_detect_data_wt_stabilized
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dig_detect_data_wt_stabilized: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_detect_data_wt_stabilized, out);
    out << "\n";
  }

  // member: dump_wt_change_data_dump_cumulative_wt_change
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dump_wt_change_data_dump_cumulative_wt_change: ";
    rosidl_generator_traits::value_to_yaml(msg.dump_wt_change_data_dump_cumulative_wt_change, out);
    out << "\n";
  }

  // member: inst_wt_der
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "inst_wt_der: ";
    rosidl_generator_traits::value_to_yaml(msg.inst_wt_der, out);
    out << "\n";
  }

  // member: inst_wt_filt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "inst_wt_filt: ";
    rosidl_generator_traits::value_to_yaml(msg.inst_wt_filt, out);
    out << "\n";
  }

  // member: inst_wt_llw_filt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "inst_wt_llw_filt: ";
    rosidl_generator_traits::value_to_yaml(msg.inst_wt_llw_filt, out);
    out << "\n";
  }

  // member: inst_wt_raw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "inst_wt_raw:\n";
    to_block_style_yaml(msg.inst_wt_raw, out, indentation + 2);
  }

  // member: inst_wt_raw_pre_tilt_comp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "inst_wt_raw_pre_tilt_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.inst_wt_raw_pre_tilt_comp, out);
    out << "\n";
  }

  // member: inst_wt_raw_post_tilt_comp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "inst_wt_raw_post_tilt_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.inst_wt_raw_post_tilt_comp, out);
    out << "\n";
  }

  // member: lift_cyl_pressure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_cyl_pressure: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_pressure, out);
    out << "\n";
  }

  // member: lift_cyl_pressure_v0
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_cyl_pressure_v0: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_pressure_v0, out);
    out << "\n";
  }

  // member: lift_cyl_pressure_imu_adjusted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_cyl_pressure_imu_adjusted: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_pressure_imu_adjusted, out);
    out << "\n";
  }

  // member: live_weigh_tbl_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "live_weigh_tbl_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.live_weigh_tbl_stat, out);
    out << "\n";
  }

  // member: live_weigh_tbl_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "live_weigh_tbl_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.live_weigh_tbl_wt, out);
    out << "\n";
  }

  // member: live_weigh_tbl_use_fast_filter
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "live_weigh_tbl_use_fast_filter: ";
    rosidl_generator_traits::value_to_yaml(msg.live_weigh_tbl_use_fast_filter, out);
    out << "\n";
  }

  // member: low_lift_wt_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "low_lift_wt_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_wt, out);
    out << "\n";
  }

  // member: low_lift_wt_confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "low_lift_wt_confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_confidence, out);
    out << "\n";
  }

  // member: low_lift_wt_confidence_est
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "low_lift_wt_confidence_est: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_confidence_est, out);
    out << "\n";
  }

  // member: low_lift_wt_confidence_timer
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "low_lift_wt_confidence_timer: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_confidence_timer, out);
    out << "\n";
  }

  // member: low_lift_wt_last_input
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "low_lift_wt_last_input: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_last_input, out);
    out << "\n";
  }

  // member: low_lift_wt_mean_est
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "low_lift_wt_mean_est: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_mean_est, out);
    out << "\n";
  }

  // member: low_lift_wt_mean_est_comp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "low_lift_wt_mean_est_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_mean_est_comp, out);
    out << "\n";
  }

  // member: low_lift_wt_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "low_lift_wt_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_stat, out);
    out << "\n";
  }

  // member: low_lift_wt_stdev_est
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "low_lift_wt_stdev_est: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_stdev_est, out);
    out << "\n";
  }

  // member: low_lift_wt_variance_est
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "low_lift_wt_variance_est: ";
    rosidl_generator_traits::value_to_yaml(msg.low_lift_wt_variance_est, out);
    out << "\n";
  }

  // member: dump_state_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dump_state_status: ";
    rosidl_generator_traits::value_to_yaml(msg.dump_state_status, out);
    out << "\n";
  }

  // member: lps_stall_detect_lift_stalled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_stall_detect_lift_stalled: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_stall_detect_lift_stalled, out);
    out << "\n";
  }

  // member: linkage_movement_lift
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "linkage_movement_lift: ";
    rosidl_generator_traits::value_to_yaml(msg.linkage_movement_lift, out);
    out << "\n";
  }

  // member: linkage_movement_tilt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "linkage_movement_tilt: ";
    rosidl_generator_traits::value_to_yaml(msg.linkage_movement_tilt, out);
    out << "\n";
  }

  // member: wrw_tbl_wk_tbl_result_weight_ave_raw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wrw_tbl_wk_tbl_result_weight_ave_raw: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_wk_tbl_result_weight_ave_raw, out);
    out << "\n";
  }

  // member: wrw_tbl_wk_tbl_result_weight_ave
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wrw_tbl_wk_tbl_result_weight_ave: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_wk_tbl_result_weight_ave, out);
    out << "\n";
  }

  // member: wrw_tbl_op_tbl_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wrw_tbl_op_tbl_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_op_tbl_wt, out);
    out << "\n";
  }

  // member: wrw_tbl_op_tbl_warning
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wrw_tbl_op_tbl_warning: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_op_tbl_warning, out);
    out << "\n";
  }

  // member: wrw_tbl_op_tbl_indicator
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wrw_tbl_op_tbl_indicator: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_op_tbl_indicator, out);
    out << "\n";
  }

  // member: wrw_tbl_op_tbl_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wrw_tbl_op_tbl_status: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_op_tbl_status, out);
    out << "\n";
  }

  // member: wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp, out);
    out << "\n";
  }

  // member: wrw_tbl_wk_tbl_been_below_range
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wrw_tbl_wk_tbl_been_below_range: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw_tbl_wk_tbl_been_below_range, out);
    out << "\n";
  }

  // member: zero_adj_tbl_zero_adj_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zero_adj_tbl_zero_adj_status: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_adj_tbl_zero_adj_status, out);
    out << "\n";
  }

  // member: overload_warn_tbl_bucket_load_factor
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "overload_warn_tbl_bucket_load_factor: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warn_tbl_bucket_load_factor, out);
    out << "\n";
  }

  // member: overload_warn_tbl_dig_reverse_flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "overload_warn_tbl_dig_reverse_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warn_tbl_dig_reverse_flag, out);
    out << "\n";
  }

  // member: overload_warn_tbl_in_overload_range
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "overload_warn_tbl_in_overload_range: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warn_tbl_in_overload_range, out);
    out << "\n";
  }

  // member: overload_warn_tbl_level
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "overload_warn_tbl_level: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warn_tbl_level, out);
    out << "\n";
  }

  // member: overload_warn_tbl_prev_dig_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "overload_warn_tbl_prev_dig_state: ";
    rosidl_generator_traits::value_to_yaml(msg.overload_warn_tbl_prev_dig_state, out);
    out << "\n";
  }

  // member: lift_position_filt_length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_position_filt_length: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_position_filt_length, out);
    out << "\n";
  }

  // member: lift_position_filt_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_position_filt_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_position_filt_velocity, out);
    out << "\n";
  }

  // member: lift_position_filt_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_position_filt_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_position_filt_angle, out);
    out << "\n";
  }

  // member: tipoff_inputs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tipoff_inputs:\n";
    to_block_style_yaml(msg.tipoff_inputs, out, indentation + 2);
  }

  // member: tipoff_outputs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tipoff_outputs:\n";
    to_block_style_yaml(msg.tipoff_outputs, out, indentation + 2);
  }

  // member: chassis_imu_gravity_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_gravity_x: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_gravity_x, out);
    out << "\n";
  }

  // member: chassis_imu_gravity_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_gravity_y: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_gravity_y, out);
    out << "\n";
  }

  // member: chassis_imu_gravity_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_gravity_z: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_gravity_z, out);
    out << "\n";
  }

  // member: chassis_imu_velocity_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_velocity_x: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_velocity_x, out);
    out << "\n";
  }

  // member: chassis_imu_velocity_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_velocity_y: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_velocity_y, out);
    out << "\n";
  }

  // member: chassis_imu_velocity_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_velocity_z: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_velocity_z, out);
    out << "\n";
  }

  // member: chassis_imu_bias_mag_jerk
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_bias_mag_jerk: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_mag_jerk, out);
    out << "\n";
  }

  // member: chassis_imu_bias_mag_ang_accel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_bias_mag_ang_accel: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_mag_ang_accel, out);
    out << "\n";
  }

  // member: chassis_imu_bias_max_ang_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_bias_max_ang_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_max_ang_vel, out);
    out << "\n";
  }

  // member: chassis_imu_bias_ang_vel_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_bias_ang_vel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_ang_vel_x, out);
    out << "\n";
  }

  // member: chassis_imu_bias_ang_vel_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_bias_ang_vel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_ang_vel_y, out);
    out << "\n";
  }

  // member: chassis_imu_bias_ang_vel_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_bias_ang_vel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_bias_ang_vel_z, out);
    out << "\n";
  }

  // member: chassis_imu_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_pitch, out);
    out << "\n";
  }

  // member: chassis_imu_roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_roll, out);
    out << "\n";
  }

  // member: chassis_imu_sensor_lin_acc_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_sensor_lin_acc_status: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_sensor_lin_acc_status, out);
    out << "\n";
  }

  // member: chassis_imu_sensor_ang_vel_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_sensor_ang_vel_status: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_sensor_ang_vel_status, out);
    out << "\n";
  }

  // member: chassis_imu_lin_acc_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_lin_acc_x: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_lin_acc_x, out);
    out << "\n";
  }

  // member: chassis_imu_lin_acc_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_lin_acc_y: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_lin_acc_y, out);
    out << "\n";
  }

  // member: chassis_imu_lin_acc_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_lin_acc_z: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_lin_acc_z, out);
    out << "\n";
  }

  // member: chassis_imu_ang_vel_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_ang_vel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_ang_vel_x, out);
    out << "\n";
  }

  // member: chassis_imu_ang_vel_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_ang_vel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_ang_vel_y, out);
    out << "\n";
  }

  // member: chassis_imu_ang_vel_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_imu_ang_vel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_imu_ang_vel_z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaWeighDebugChannel & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace weigh_app_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use weigh_app_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaWeighDebugChannel & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaWeighDebugChannel>()
{
  return "weigh_app_interfaces::msg::LpsSaWeighDebugChannel";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaWeighDebugChannel>()
{
  return "weigh_app_interfaces/msg/LpsSaWeighDebugChannel";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaWeighDebugChannel>
  : std::integral_constant<bool, has_fixed_size<cpm_common_interfaces::msg::FloatIO>::value && has_fixed_size<weigh_app_interfaces::msg::TipoffAssistInputs>::value && has_fixed_size<weigh_app_interfaces::msg::TipoffAssistOutputs>::value> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaWeighDebugChannel>
  : std::integral_constant<bool, has_bounded_size<cpm_common_interfaces::msg::FloatIO>::value && has_bounded_size<weigh_app_interfaces::msg::TipoffAssistInputs>::value && has_bounded_size<weigh_app_interfaces::msg::TipoffAssistOutputs>::value> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaWeighDebugChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__TRAITS_HPP_
