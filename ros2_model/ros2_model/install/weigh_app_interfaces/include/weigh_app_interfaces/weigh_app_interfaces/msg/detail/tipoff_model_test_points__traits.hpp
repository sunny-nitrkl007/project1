// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/TipoffModelTestPoints.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_model_test_points.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/tipoff_model_test_points__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TipoffModelTestPoints & msg,
  std::ostream & out)
{
  out << "{";
  // member: toa_pfw_sec_latch
  {
    out << "toa_pfw_sec_latch: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_latch, out);
    out << ", ";
  }

  // member: toa_pfw_sec_payload
  {
    out << "toa_pfw_sec_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_payload, out);
    out << ", ";
  }

  // member: toa_pfw_sec_status
  {
    out << "toa_pfw_sec_status: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_status, out);
    out << ", ";
  }

  // member: toa_pfw_sec_st_dev
  {
    out << "toa_pfw_sec_st_dev: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_st_dev, out);
    out << ", ";
  }

  // member: toa_target_payload_final
  {
    out << "toa_target_payload_final: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_target_payload_final, out);
    out << ", ";
  }

  // member: toa_target_payload_status
  {
    out << "toa_target_payload_status: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_target_payload_status, out);
    out << ", ";
  }

  // member: toa_pfw_nl_notch_mean_est
  {
    out << "toa_pfw_nl_notch_mean_est: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_nl_notch_mean_est, out);
    out << ", ";
  }

  // member: toa_pfw_nl_notch_st_dev_est
  {
    out << "toa_pfw_nl_notch_st_dev_est: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_nl_notch_st_dev_est, out);
    out << ", ";
  }

  // member: toa_lw_lpf_post
  {
    out << "toa_lw_lpf_post: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_lw_lpf_post, out);
    out << ", ";
  }

  // member: toa_payload_adjusted
  {
    out << "toa_payload_adjusted: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_payload_adjusted, out);
    out << ", ";
  }

  // member: toa_send_payload_arb
  {
    out << "toa_send_payload_arb: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_send_payload_arb, out);
    out << ", ";
  }

  // member: toa_sfunc_in_grav_x
  {
    out << "toa_sfunc_in_grav_x: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_sfunc_in_grav_x, out);
    out << ", ";
  }

  // member: toa_sfunc_in_grav_y
  {
    out << "toa_sfunc_in_grav_y: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_sfunc_in_grav_y, out);
    out << ", ";
  }

  // member: toa_sfunc_in_lift_force
  {
    out << "toa_sfunc_in_lift_force: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_sfunc_in_lift_force, out);
    out << ", ";
  }

  // member: toa_sfunc_in_tilt_force
  {
    out << "toa_sfunc_in_tilt_force: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_sfunc_in_tilt_force, out);
    out << ", ";
  }

  // member: toa_sfunc_out_raw_mass_tonne
  {
    out << "toa_sfunc_out_raw_mass_tonne: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_sfunc_out_raw_mass_tonne, out);
    out << ", ";
  }

  // member: toa_app_number
  {
    out << "toa_app_number: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_app_number, out);
    out << ", ";
  }

  // member: toa_lift_bore_dia
  {
    out << "toa_lift_bore_dia: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_lift_bore_dia, out);
    out << ", ";
  }

  // member: toa_lift_rod_dia
  {
    out << "toa_lift_rod_dia: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_lift_rod_dia, out);
    out << ", ";
  }

  // member: toa_payload_anc_adjusted
  {
    out << "toa_payload_anc_adjusted: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_payload_anc_adjusted, out);
    out << ", ";
  }

  // member: toa_payload_anc_zeroed
  {
    out << "toa_payload_anc_zeroed: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_payload_anc_zeroed, out);
    out << ", ";
  }

  // member: toa_rated_payload
  {
    out << "toa_rated_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_rated_payload, out);
    out << ", ";
  }

  // member: toa_tilt_bore_dia
  {
    out << "toa_tilt_bore_dia: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_tilt_bore_dia, out);
    out << ", ";
  }

  // member: toa_tilt_num_cyl
  {
    out << "toa_tilt_num_cyl: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_tilt_num_cyl, out);
    out << ", ";
  }

  // member: toa_tilt_rod_dia
  {
    out << "toa_tilt_rod_dia: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_tilt_rod_dia, out);
    out << ", ";
  }

  // member: toa_tool_bc_length
  {
    out << "toa_tool_bc_length: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_tool_bc_length, out);
    out << ", ";
  }

  // member: toa_imu_cal_pitch_angle
  {
    out << "toa_imu_cal_pitch_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_cal_pitch_angle, out);
    out << ", ";
  }

  // member: toa_pfw_unsec_status
  {
    out << "toa_pfw_unsec_status: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_unsec_status, out);
    out << ", ";
  }

  // member: toa_pfw_unsec_bound_lower
  {
    out << "toa_pfw_unsec_bound_lower: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_unsec_bound_lower, out);
    out << ", ";
  }

  // member: toa_pfw_unsec_bound_upper
  {
    out << "toa_pfw_unsec_bound_upper: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_unsec_bound_upper, out);
    out << ", ";
  }

  // member: toa_lw_spill_rate
  {
    out << "toa_lw_spill_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_lw_spill_rate, out);
    out << ", ";
  }

  // member: toa_lw_status
  {
    out << "toa_lw_status: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_lw_status, out);
    out << ", ";
  }

  // member: toa_raw_dist
  {
    out << "toa_raw_dist: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_raw_dist, out);
    out << ", ";
  }

  // member: toa_raw_payload
  {
    out << "toa_raw_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_raw_payload, out);
    out << ", ";
  }

  // member: toa_payload_zeroed
  {
    out << "toa_payload_zeroed: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_payload_zeroed, out);
    out << ", ";
  }

  // member: toa_pfw_is_warm
  {
    out << "toa_pfw_is_warm: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_is_warm, out);
    out << ", ";
  }

  // member: toa_pfw_sec_is_secure
  {
    out << "toa_pfw_sec_is_secure: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_is_secure, out);
    out << ", ";
  }

  // member: toa_pfw_sec_is_no_sliding
  {
    out << "toa_pfw_sec_is_no_sliding: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_is_no_sliding, out);
    out << ", ";
  }

  // member: toa_pfw_sec_is_no_collapsing
  {
    out << "toa_pfw_sec_is_no_collapsing: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_is_no_collapsing, out);
    out << ", ";
  }

  // member: toa_pfw_sec_is_racked
  {
    out << "toa_pfw_sec_is_racked: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_is_racked, out);
    out << ", ";
  }

  // member: toa_pfw_sec_min_bucket_ang
  {
    out << "toa_pfw_sec_min_bucket_ang: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_min_bucket_ang, out);
    out << ", ";
  }

  // member: toa_pfw_mc_ok
  {
    out << "toa_pfw_mc_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_mc_ok, out);
    out << ", ";
  }

  // member: toa_pfw_mc_maybe_stalled
  {
    out << "toa_pfw_mc_maybe_stalled: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_mc_maybe_stalled, out);
    out << ", ";
  }

  // member: toa_pfw_mc_maybe_rack_stall
  {
    out << "toa_pfw_mc_maybe_rack_stall: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_mc_maybe_rack_stall, out);
    out << ", ";
  }

  // member: toa_pfw_mc_maybe_grounded
  {
    out << "toa_pfw_mc_maybe_grounded: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_mc_maybe_grounded, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_notch_one_up
  {
    out << "toa_stat_payload_nl_notch_one_up: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_one_up, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_notch_one_low
  {
    out << "toa_stat_payload_nl_notch_one_low: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_one_low, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_notch_one_size
  {
    out << "toa_stat_payload_nl_notch_one_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_one_size, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_notch_two_up
  {
    out << "toa_stat_payload_nl_notch_two_up: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_two_up, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_notch_two_low
  {
    out << "toa_stat_payload_nl_notch_two_low: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_two_low, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_notch_two_size
  {
    out << "toa_stat_payload_nl_notch_two_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_two_size, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_one_up
  {
    out << "toa_stat_payload_nl_one_up: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_one_up, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_one_low
  {
    out << "toa_stat_payload_nl_one_low: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_one_low, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_one_size
  {
    out << "toa_stat_payload_nl_one_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_one_size, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_two_up
  {
    out << "toa_stat_payload_nl_two_up: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_two_up, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_two_low
  {
    out << "toa_stat_payload_nl_two_low: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_two_low, out);
    out << ", ";
  }

  // member: toa_stat_payload_nl_two_size
  {
    out << "toa_stat_payload_nl_two_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_two_size, out);
    out << ", ";
  }

  // member: toa_pfw_nl_st_dev_est
  {
    out << "toa_pfw_nl_st_dev_est: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_nl_st_dev_est, out);
    out << ", ";
  }

  // member: toa_pfw_nl_mean_est
  {
    out << "toa_pfw_nl_mean_est: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_nl_mean_est, out);
    out << ", ";
  }

  // member: toa_pfw_payload_filt_final
  {
    out << "toa_pfw_payload_filt_final: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_payload_filt_final, out);
    out << ", ";
  }

  // member: toa_pfw_payload_notch_filt_final
  {
    out << "toa_pfw_payload_notch_filt_final: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_payload_notch_filt_final, out);
    out << ", ";
  }

  // member: toa_pfw_payload_notch_post
  {
    out << "toa_pfw_payload_notch_post: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_payload_notch_post, out);
    out << ", ";
  }

  // member: toa_pfw_latch_invalidate
  {
    out << "toa_pfw_latch_invalidate: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_latch_invalidate, out);
    out << ", ";
  }

  // member: toa_imu_raw_eef_accl_x
  {
    out << "toa_imu_raw_eef_accl_x: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_raw_eef_accl_x, out);
    out << ", ";
  }

  // member: toa_imu_raw_eef_accl_y
  {
    out << "toa_imu_raw_eef_accl_y: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_raw_eef_accl_y, out);
    out << ", ";
  }

  // member: toa_imu_raw_eef_accl_z
  {
    out << "toa_imu_raw_eef_accl_z: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_raw_eef_accl_z, out);
    out << ", ";
  }

  // member: toa_imu_neef_grav_x
  {
    out << "toa_imu_neef_grav_x: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_neef_grav_x, out);
    out << ", ";
  }

  // member: toa_imu_neef_grav_y
  {
    out << "toa_imu_neef_grav_y: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_neef_grav_y, out);
    out << ", ";
  }

  // member: toa_imu_neef_grav_z
  {
    out << "toa_imu_neef_grav_z: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_neef_grav_z, out);
    out << ", ";
  }

  // member: toa_imu_neef_pitch
  {
    out << "toa_imu_neef_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_neef_pitch, out);
    out << ", ";
  }

  // member: toa_target_comp_margin
  {
    out << "toa_target_comp_margin: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_target_comp_margin, out);
    out << ", ";
  }

  // member: toa_target_payload_post_comp
  {
    out << "toa_target_payload_post_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_target_payload_post_comp, out);
    out << ", ";
  }

  // member: toa_target_payload_pre_comp
  {
    out << "toa_target_payload_pre_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_target_payload_pre_comp, out);
    out << ", ";
  }

  // member: toa_stat_payload_secure_two_size
  {
    out << "toa_stat_payload_secure_two_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_two_size, out);
    out << ", ";
  }

  // member: toa_stat_payload_secure_one_upper
  {
    out << "toa_stat_payload_secure_one_upper: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_one_upper, out);
    out << ", ";
  }

  // member: toa_stat_payload_secure_one_lower
  {
    out << "toa_stat_payload_secure_one_lower: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_one_lower, out);
    out << ", ";
  }

  // member: toa_stat_payload_secure_one_size
  {
    out << "toa_stat_payload_secure_one_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_one_size, out);
    out << ", ";
  }

  // member: toa_stat_payload_secure_two_upper
  {
    out << "toa_stat_payload_secure_two_upper: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_two_upper, out);
    out << ", ";
  }

  // member: toa_stat_payload_secure_two_lower
  {
    out << "toa_stat_payload_secure_two_lower: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_two_lower, out);
    out << ", ";
  }

  // member: toa_send_cpm_live_payload
  {
    out << "toa_send_cpm_live_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_send_cpm_live_payload, out);
    out << ", ";
  }

  // member: toa_tool_bc_angle
  {
    out << "toa_tool_bc_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_tool_bc_angle, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TipoffModelTestPoints & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: toa_pfw_sec_latch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_sec_latch: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_latch, out);
    out << "\n";
  }

  // member: toa_pfw_sec_payload
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_sec_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_payload, out);
    out << "\n";
  }

  // member: toa_pfw_sec_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_sec_status: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_status, out);
    out << "\n";
  }

  // member: toa_pfw_sec_st_dev
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_sec_st_dev: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_st_dev, out);
    out << "\n";
  }

  // member: toa_target_payload_final
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_target_payload_final: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_target_payload_final, out);
    out << "\n";
  }

  // member: toa_target_payload_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_target_payload_status: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_target_payload_status, out);
    out << "\n";
  }

  // member: toa_pfw_nl_notch_mean_est
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_nl_notch_mean_est: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_nl_notch_mean_est, out);
    out << "\n";
  }

  // member: toa_pfw_nl_notch_st_dev_est
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_nl_notch_st_dev_est: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_nl_notch_st_dev_est, out);
    out << "\n";
  }

  // member: toa_lw_lpf_post
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_lw_lpf_post: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_lw_lpf_post, out);
    out << "\n";
  }

  // member: toa_payload_adjusted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_payload_adjusted: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_payload_adjusted, out);
    out << "\n";
  }

  // member: toa_send_payload_arb
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_send_payload_arb: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_send_payload_arb, out);
    out << "\n";
  }

  // member: toa_sfunc_in_grav_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_sfunc_in_grav_x: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_sfunc_in_grav_x, out);
    out << "\n";
  }

  // member: toa_sfunc_in_grav_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_sfunc_in_grav_y: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_sfunc_in_grav_y, out);
    out << "\n";
  }

  // member: toa_sfunc_in_lift_force
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_sfunc_in_lift_force: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_sfunc_in_lift_force, out);
    out << "\n";
  }

  // member: toa_sfunc_in_tilt_force
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_sfunc_in_tilt_force: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_sfunc_in_tilt_force, out);
    out << "\n";
  }

  // member: toa_sfunc_out_raw_mass_tonne
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_sfunc_out_raw_mass_tonne: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_sfunc_out_raw_mass_tonne, out);
    out << "\n";
  }

  // member: toa_app_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_app_number: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_app_number, out);
    out << "\n";
  }

  // member: toa_lift_bore_dia
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_lift_bore_dia: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_lift_bore_dia, out);
    out << "\n";
  }

  // member: toa_lift_rod_dia
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_lift_rod_dia: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_lift_rod_dia, out);
    out << "\n";
  }

  // member: toa_payload_anc_adjusted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_payload_anc_adjusted: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_payload_anc_adjusted, out);
    out << "\n";
  }

  // member: toa_payload_anc_zeroed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_payload_anc_zeroed: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_payload_anc_zeroed, out);
    out << "\n";
  }

  // member: toa_rated_payload
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_rated_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_rated_payload, out);
    out << "\n";
  }

  // member: toa_tilt_bore_dia
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_tilt_bore_dia: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_tilt_bore_dia, out);
    out << "\n";
  }

  // member: toa_tilt_num_cyl
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_tilt_num_cyl: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_tilt_num_cyl, out);
    out << "\n";
  }

  // member: toa_tilt_rod_dia
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_tilt_rod_dia: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_tilt_rod_dia, out);
    out << "\n";
  }

  // member: toa_tool_bc_length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_tool_bc_length: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_tool_bc_length, out);
    out << "\n";
  }

  // member: toa_imu_cal_pitch_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_imu_cal_pitch_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_cal_pitch_angle, out);
    out << "\n";
  }

  // member: toa_pfw_unsec_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_unsec_status: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_unsec_status, out);
    out << "\n";
  }

  // member: toa_pfw_unsec_bound_lower
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_unsec_bound_lower: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_unsec_bound_lower, out);
    out << "\n";
  }

  // member: toa_pfw_unsec_bound_upper
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_unsec_bound_upper: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_unsec_bound_upper, out);
    out << "\n";
  }

  // member: toa_lw_spill_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_lw_spill_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_lw_spill_rate, out);
    out << "\n";
  }

  // member: toa_lw_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_lw_status: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_lw_status, out);
    out << "\n";
  }

  // member: toa_raw_dist
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_raw_dist: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_raw_dist, out);
    out << "\n";
  }

  // member: toa_raw_payload
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_raw_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_raw_payload, out);
    out << "\n";
  }

  // member: toa_payload_zeroed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_payload_zeroed: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_payload_zeroed, out);
    out << "\n";
  }

  // member: toa_pfw_is_warm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_is_warm: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_is_warm, out);
    out << "\n";
  }

  // member: toa_pfw_sec_is_secure
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_sec_is_secure: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_is_secure, out);
    out << "\n";
  }

  // member: toa_pfw_sec_is_no_sliding
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_sec_is_no_sliding: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_is_no_sliding, out);
    out << "\n";
  }

  // member: toa_pfw_sec_is_no_collapsing
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_sec_is_no_collapsing: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_is_no_collapsing, out);
    out << "\n";
  }

  // member: toa_pfw_sec_is_racked
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_sec_is_racked: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_is_racked, out);
    out << "\n";
  }

  // member: toa_pfw_sec_min_bucket_ang
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_sec_min_bucket_ang: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_sec_min_bucket_ang, out);
    out << "\n";
  }

  // member: toa_pfw_mc_ok
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_mc_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_mc_ok, out);
    out << "\n";
  }

  // member: toa_pfw_mc_maybe_stalled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_mc_maybe_stalled: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_mc_maybe_stalled, out);
    out << "\n";
  }

  // member: toa_pfw_mc_maybe_rack_stall
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_mc_maybe_rack_stall: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_mc_maybe_rack_stall, out);
    out << "\n";
  }

  // member: toa_pfw_mc_maybe_grounded
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_mc_maybe_grounded: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_mc_maybe_grounded, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_notch_one_up
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_notch_one_up: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_one_up, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_notch_one_low
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_notch_one_low: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_one_low, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_notch_one_size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_notch_one_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_one_size, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_notch_two_up
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_notch_two_up: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_two_up, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_notch_two_low
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_notch_two_low: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_two_low, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_notch_two_size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_notch_two_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_notch_two_size, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_one_up
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_one_up: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_one_up, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_one_low
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_one_low: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_one_low, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_one_size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_one_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_one_size, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_two_up
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_two_up: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_two_up, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_two_low
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_two_low: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_two_low, out);
    out << "\n";
  }

  // member: toa_stat_payload_nl_two_size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_nl_two_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_nl_two_size, out);
    out << "\n";
  }

  // member: toa_pfw_nl_st_dev_est
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_nl_st_dev_est: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_nl_st_dev_est, out);
    out << "\n";
  }

  // member: toa_pfw_nl_mean_est
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_nl_mean_est: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_nl_mean_est, out);
    out << "\n";
  }

  // member: toa_pfw_payload_filt_final
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_payload_filt_final: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_payload_filt_final, out);
    out << "\n";
  }

  // member: toa_pfw_payload_notch_filt_final
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_payload_notch_filt_final: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_payload_notch_filt_final, out);
    out << "\n";
  }

  // member: toa_pfw_payload_notch_post
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_payload_notch_post: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_payload_notch_post, out);
    out << "\n";
  }

  // member: toa_pfw_latch_invalidate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_pfw_latch_invalidate: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_pfw_latch_invalidate, out);
    out << "\n";
  }

  // member: toa_imu_raw_eef_accl_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_imu_raw_eef_accl_x: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_raw_eef_accl_x, out);
    out << "\n";
  }

  // member: toa_imu_raw_eef_accl_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_imu_raw_eef_accl_y: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_raw_eef_accl_y, out);
    out << "\n";
  }

  // member: toa_imu_raw_eef_accl_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_imu_raw_eef_accl_z: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_raw_eef_accl_z, out);
    out << "\n";
  }

  // member: toa_imu_neef_grav_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_imu_neef_grav_x: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_neef_grav_x, out);
    out << "\n";
  }

  // member: toa_imu_neef_grav_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_imu_neef_grav_y: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_neef_grav_y, out);
    out << "\n";
  }

  // member: toa_imu_neef_grav_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_imu_neef_grav_z: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_neef_grav_z, out);
    out << "\n";
  }

  // member: toa_imu_neef_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_imu_neef_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_imu_neef_pitch, out);
    out << "\n";
  }

  // member: toa_target_comp_margin
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_target_comp_margin: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_target_comp_margin, out);
    out << "\n";
  }

  // member: toa_target_payload_post_comp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_target_payload_post_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_target_payload_post_comp, out);
    out << "\n";
  }

  // member: toa_target_payload_pre_comp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_target_payload_pre_comp: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_target_payload_pre_comp, out);
    out << "\n";
  }

  // member: toa_stat_payload_secure_two_size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_secure_two_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_two_size, out);
    out << "\n";
  }

  // member: toa_stat_payload_secure_one_upper
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_secure_one_upper: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_one_upper, out);
    out << "\n";
  }

  // member: toa_stat_payload_secure_one_lower
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_secure_one_lower: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_one_lower, out);
    out << "\n";
  }

  // member: toa_stat_payload_secure_one_size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_secure_one_size: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_one_size, out);
    out << "\n";
  }

  // member: toa_stat_payload_secure_two_upper
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_secure_two_upper: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_two_upper, out);
    out << "\n";
  }

  // member: toa_stat_payload_secure_two_lower
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_stat_payload_secure_two_lower: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_stat_payload_secure_two_lower, out);
    out << "\n";
  }

  // member: toa_send_cpm_live_payload
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_send_cpm_live_payload: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_send_cpm_live_payload, out);
    out << "\n";
  }

  // member: toa_tool_bc_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toa_tool_bc_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.toa_tool_bc_angle, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TipoffModelTestPoints & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::TipoffModelTestPoints & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::TipoffModelTestPoints & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::TipoffModelTestPoints>()
{
  return "weigh_app_interfaces::msg::TipoffModelTestPoints";
}

template<>
inline const char * name<weigh_app_interfaces::msg::TipoffModelTestPoints>()
{
  return "weigh_app_interfaces/msg/TipoffModelTestPoints";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::TipoffModelTestPoints>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::TipoffModelTestPoints>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::TipoffModelTestPoints>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__TRAITS_HPP_
