// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/TipoffModelTestPoints.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_model_test_points.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__TipoffModelTestPoints __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__TipoffModelTestPoints __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TipoffModelTestPoints_
{
  using Type = TipoffModelTestPoints_<ContainerAllocator>;

  explicit TipoffModelTestPoints_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->toa_pfw_sec_latch = false;
      this->toa_pfw_sec_payload = 0.0f;
      this->toa_pfw_sec_status = 0;
      this->toa_pfw_sec_st_dev = 0.0f;
      this->toa_target_payload_final = 0.0f;
      this->toa_target_payload_status = false;
      this->toa_pfw_nl_notch_mean_est = 0.0f;
      this->toa_pfw_nl_notch_st_dev_est = 0.0f;
      this->toa_lw_lpf_post = 0.0f;
      this->toa_payload_adjusted = 0.0f;
      this->toa_send_payload_arb = 0.0f;
      this->toa_sfunc_in_grav_x = 0.0f;
      this->toa_sfunc_in_grav_y = 0.0f;
      this->toa_sfunc_in_lift_force = 0.0f;
      this->toa_sfunc_in_tilt_force = 0.0f;
      this->toa_sfunc_out_raw_mass_tonne = 0.0f;
      this->toa_app_number = 0ul;
      this->toa_lift_bore_dia = 0.0f;
      this->toa_lift_rod_dia = 0.0f;
      this->toa_payload_anc_adjusted = 0.0f;
      this->toa_payload_anc_zeroed = 0.0f;
      this->toa_rated_payload = 0.0f;
      this->toa_tilt_bore_dia = 0.0f;
      this->toa_tilt_num_cyl = 0;
      this->toa_tilt_rod_dia = 0.0f;
      this->toa_tool_bc_length = 0.0f;
      this->toa_imu_cal_pitch_angle = 0.0f;
      this->toa_pfw_unsec_status = 0;
      this->toa_pfw_unsec_bound_lower = 0.0f;
      this->toa_pfw_unsec_bound_upper = 0.0f;
      this->toa_lw_spill_rate = 0.0f;
      this->toa_lw_status = 0;
      this->toa_raw_dist = 0.0f;
      this->toa_raw_payload = 0.0f;
      this->toa_payload_zeroed = 0.0f;
      this->toa_pfw_is_warm = false;
      this->toa_pfw_sec_is_secure = false;
      this->toa_pfw_sec_is_no_sliding = false;
      this->toa_pfw_sec_is_no_collapsing = false;
      this->toa_pfw_sec_is_racked = false;
      this->toa_pfw_sec_min_bucket_ang = 0.0f;
      this->toa_pfw_mc_ok = false;
      this->toa_pfw_mc_maybe_stalled = false;
      this->toa_pfw_mc_maybe_rack_stall = false;
      this->toa_pfw_mc_maybe_grounded = false;
      this->toa_stat_payload_nl_notch_one_up = 0.0f;
      this->toa_stat_payload_nl_notch_one_low = 0.0f;
      this->toa_stat_payload_nl_notch_one_size = 0.0f;
      this->toa_stat_payload_nl_notch_two_up = 0.0f;
      this->toa_stat_payload_nl_notch_two_low = 0.0f;
      this->toa_stat_payload_nl_notch_two_size = 0.0f;
      this->toa_stat_payload_nl_one_up = 0.0f;
      this->toa_stat_payload_nl_one_low = 0.0f;
      this->toa_stat_payload_nl_one_size = 0.0f;
      this->toa_stat_payload_nl_two_up = 0.0f;
      this->toa_stat_payload_nl_two_low = 0.0f;
      this->toa_stat_payload_nl_two_size = 0.0f;
      this->toa_pfw_nl_st_dev_est = 0.0f;
      this->toa_pfw_nl_mean_est = 0.0f;
      this->toa_pfw_payload_filt_final = 0.0f;
      this->toa_pfw_payload_notch_filt_final = 0.0f;
      this->toa_pfw_payload_notch_post = 0.0f;
      this->toa_pfw_latch_invalidate = false;
      this->toa_imu_raw_eef_accl_x = 0.0f;
      this->toa_imu_raw_eef_accl_y = 0.0f;
      this->toa_imu_raw_eef_accl_z = 0.0f;
      this->toa_imu_neef_grav_x = 0.0f;
      this->toa_imu_neef_grav_y = 0.0f;
      this->toa_imu_neef_grav_z = 0.0f;
      this->toa_imu_neef_pitch = 0.0f;
      this->toa_target_comp_margin = 0.0f;
      this->toa_target_payload_post_comp = 0.0f;
      this->toa_target_payload_pre_comp = 0.0f;
      this->toa_stat_payload_secure_two_size = 0.0f;
      this->toa_stat_payload_secure_one_upper = 0.0f;
      this->toa_stat_payload_secure_one_lower = 0.0f;
      this->toa_stat_payload_secure_one_size = 0.0f;
      this->toa_stat_payload_secure_two_upper = 0.0f;
      this->toa_stat_payload_secure_two_lower = 0.0f;
      this->toa_send_cpm_live_payload = 0.0f;
      this->toa_tool_bc_angle = 0.0f;
    }
  }

  explicit TipoffModelTestPoints_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->toa_pfw_sec_latch = false;
      this->toa_pfw_sec_payload = 0.0f;
      this->toa_pfw_sec_status = 0;
      this->toa_pfw_sec_st_dev = 0.0f;
      this->toa_target_payload_final = 0.0f;
      this->toa_target_payload_status = false;
      this->toa_pfw_nl_notch_mean_est = 0.0f;
      this->toa_pfw_nl_notch_st_dev_est = 0.0f;
      this->toa_lw_lpf_post = 0.0f;
      this->toa_payload_adjusted = 0.0f;
      this->toa_send_payload_arb = 0.0f;
      this->toa_sfunc_in_grav_x = 0.0f;
      this->toa_sfunc_in_grav_y = 0.0f;
      this->toa_sfunc_in_lift_force = 0.0f;
      this->toa_sfunc_in_tilt_force = 0.0f;
      this->toa_sfunc_out_raw_mass_tonne = 0.0f;
      this->toa_app_number = 0ul;
      this->toa_lift_bore_dia = 0.0f;
      this->toa_lift_rod_dia = 0.0f;
      this->toa_payload_anc_adjusted = 0.0f;
      this->toa_payload_anc_zeroed = 0.0f;
      this->toa_rated_payload = 0.0f;
      this->toa_tilt_bore_dia = 0.0f;
      this->toa_tilt_num_cyl = 0;
      this->toa_tilt_rod_dia = 0.0f;
      this->toa_tool_bc_length = 0.0f;
      this->toa_imu_cal_pitch_angle = 0.0f;
      this->toa_pfw_unsec_status = 0;
      this->toa_pfw_unsec_bound_lower = 0.0f;
      this->toa_pfw_unsec_bound_upper = 0.0f;
      this->toa_lw_spill_rate = 0.0f;
      this->toa_lw_status = 0;
      this->toa_raw_dist = 0.0f;
      this->toa_raw_payload = 0.0f;
      this->toa_payload_zeroed = 0.0f;
      this->toa_pfw_is_warm = false;
      this->toa_pfw_sec_is_secure = false;
      this->toa_pfw_sec_is_no_sliding = false;
      this->toa_pfw_sec_is_no_collapsing = false;
      this->toa_pfw_sec_is_racked = false;
      this->toa_pfw_sec_min_bucket_ang = 0.0f;
      this->toa_pfw_mc_ok = false;
      this->toa_pfw_mc_maybe_stalled = false;
      this->toa_pfw_mc_maybe_rack_stall = false;
      this->toa_pfw_mc_maybe_grounded = false;
      this->toa_stat_payload_nl_notch_one_up = 0.0f;
      this->toa_stat_payload_nl_notch_one_low = 0.0f;
      this->toa_stat_payload_nl_notch_one_size = 0.0f;
      this->toa_stat_payload_nl_notch_two_up = 0.0f;
      this->toa_stat_payload_nl_notch_two_low = 0.0f;
      this->toa_stat_payload_nl_notch_two_size = 0.0f;
      this->toa_stat_payload_nl_one_up = 0.0f;
      this->toa_stat_payload_nl_one_low = 0.0f;
      this->toa_stat_payload_nl_one_size = 0.0f;
      this->toa_stat_payload_nl_two_up = 0.0f;
      this->toa_stat_payload_nl_two_low = 0.0f;
      this->toa_stat_payload_nl_two_size = 0.0f;
      this->toa_pfw_nl_st_dev_est = 0.0f;
      this->toa_pfw_nl_mean_est = 0.0f;
      this->toa_pfw_payload_filt_final = 0.0f;
      this->toa_pfw_payload_notch_filt_final = 0.0f;
      this->toa_pfw_payload_notch_post = 0.0f;
      this->toa_pfw_latch_invalidate = false;
      this->toa_imu_raw_eef_accl_x = 0.0f;
      this->toa_imu_raw_eef_accl_y = 0.0f;
      this->toa_imu_raw_eef_accl_z = 0.0f;
      this->toa_imu_neef_grav_x = 0.0f;
      this->toa_imu_neef_grav_y = 0.0f;
      this->toa_imu_neef_grav_z = 0.0f;
      this->toa_imu_neef_pitch = 0.0f;
      this->toa_target_comp_margin = 0.0f;
      this->toa_target_payload_post_comp = 0.0f;
      this->toa_target_payload_pre_comp = 0.0f;
      this->toa_stat_payload_secure_two_size = 0.0f;
      this->toa_stat_payload_secure_one_upper = 0.0f;
      this->toa_stat_payload_secure_one_lower = 0.0f;
      this->toa_stat_payload_secure_one_size = 0.0f;
      this->toa_stat_payload_secure_two_upper = 0.0f;
      this->toa_stat_payload_secure_two_lower = 0.0f;
      this->toa_send_cpm_live_payload = 0.0f;
      this->toa_tool_bc_angle = 0.0f;
    }
  }

  // field types and members
  using _toa_pfw_sec_latch_type =
    bool;
  _toa_pfw_sec_latch_type toa_pfw_sec_latch;
  using _toa_pfw_sec_payload_type =
    float;
  _toa_pfw_sec_payload_type toa_pfw_sec_payload;
  using _toa_pfw_sec_status_type =
    uint8_t;
  _toa_pfw_sec_status_type toa_pfw_sec_status;
  using _toa_pfw_sec_st_dev_type =
    float;
  _toa_pfw_sec_st_dev_type toa_pfw_sec_st_dev;
  using _toa_target_payload_final_type =
    float;
  _toa_target_payload_final_type toa_target_payload_final;
  using _toa_target_payload_status_type =
    bool;
  _toa_target_payload_status_type toa_target_payload_status;
  using _toa_pfw_nl_notch_mean_est_type =
    float;
  _toa_pfw_nl_notch_mean_est_type toa_pfw_nl_notch_mean_est;
  using _toa_pfw_nl_notch_st_dev_est_type =
    float;
  _toa_pfw_nl_notch_st_dev_est_type toa_pfw_nl_notch_st_dev_est;
  using _toa_lw_lpf_post_type =
    float;
  _toa_lw_lpf_post_type toa_lw_lpf_post;
  using _toa_payload_adjusted_type =
    float;
  _toa_payload_adjusted_type toa_payload_adjusted;
  using _toa_send_payload_arb_type =
    float;
  _toa_send_payload_arb_type toa_send_payload_arb;
  using _toa_sfunc_in_grav_x_type =
    float;
  _toa_sfunc_in_grav_x_type toa_sfunc_in_grav_x;
  using _toa_sfunc_in_grav_y_type =
    float;
  _toa_sfunc_in_grav_y_type toa_sfunc_in_grav_y;
  using _toa_sfunc_in_lift_force_type =
    float;
  _toa_sfunc_in_lift_force_type toa_sfunc_in_lift_force;
  using _toa_sfunc_in_tilt_force_type =
    float;
  _toa_sfunc_in_tilt_force_type toa_sfunc_in_tilt_force;
  using _toa_sfunc_out_raw_mass_tonne_type =
    float;
  _toa_sfunc_out_raw_mass_tonne_type toa_sfunc_out_raw_mass_tonne;
  using _toa_app_number_type =
    uint32_t;
  _toa_app_number_type toa_app_number;
  using _toa_lift_bore_dia_type =
    float;
  _toa_lift_bore_dia_type toa_lift_bore_dia;
  using _toa_lift_rod_dia_type =
    float;
  _toa_lift_rod_dia_type toa_lift_rod_dia;
  using _toa_payload_anc_adjusted_type =
    float;
  _toa_payload_anc_adjusted_type toa_payload_anc_adjusted;
  using _toa_payload_anc_zeroed_type =
    float;
  _toa_payload_anc_zeroed_type toa_payload_anc_zeroed;
  using _toa_rated_payload_type =
    float;
  _toa_rated_payload_type toa_rated_payload;
  using _toa_tilt_bore_dia_type =
    float;
  _toa_tilt_bore_dia_type toa_tilt_bore_dia;
  using _toa_tilt_num_cyl_type =
    uint8_t;
  _toa_tilt_num_cyl_type toa_tilt_num_cyl;
  using _toa_tilt_rod_dia_type =
    float;
  _toa_tilt_rod_dia_type toa_tilt_rod_dia;
  using _toa_tool_bc_length_type =
    float;
  _toa_tool_bc_length_type toa_tool_bc_length;
  using _toa_imu_cal_pitch_angle_type =
    float;
  _toa_imu_cal_pitch_angle_type toa_imu_cal_pitch_angle;
  using _toa_pfw_unsec_status_type =
    uint8_t;
  _toa_pfw_unsec_status_type toa_pfw_unsec_status;
  using _toa_pfw_unsec_bound_lower_type =
    float;
  _toa_pfw_unsec_bound_lower_type toa_pfw_unsec_bound_lower;
  using _toa_pfw_unsec_bound_upper_type =
    float;
  _toa_pfw_unsec_bound_upper_type toa_pfw_unsec_bound_upper;
  using _toa_lw_spill_rate_type =
    float;
  _toa_lw_spill_rate_type toa_lw_spill_rate;
  using _toa_lw_status_type =
    uint8_t;
  _toa_lw_status_type toa_lw_status;
  using _toa_raw_dist_type =
    float;
  _toa_raw_dist_type toa_raw_dist;
  using _toa_raw_payload_type =
    float;
  _toa_raw_payload_type toa_raw_payload;
  using _toa_payload_zeroed_type =
    float;
  _toa_payload_zeroed_type toa_payload_zeroed;
  using _toa_pfw_is_warm_type =
    bool;
  _toa_pfw_is_warm_type toa_pfw_is_warm;
  using _toa_pfw_sec_is_secure_type =
    bool;
  _toa_pfw_sec_is_secure_type toa_pfw_sec_is_secure;
  using _toa_pfw_sec_is_no_sliding_type =
    bool;
  _toa_pfw_sec_is_no_sliding_type toa_pfw_sec_is_no_sliding;
  using _toa_pfw_sec_is_no_collapsing_type =
    bool;
  _toa_pfw_sec_is_no_collapsing_type toa_pfw_sec_is_no_collapsing;
  using _toa_pfw_sec_is_racked_type =
    bool;
  _toa_pfw_sec_is_racked_type toa_pfw_sec_is_racked;
  using _toa_pfw_sec_min_bucket_ang_type =
    float;
  _toa_pfw_sec_min_bucket_ang_type toa_pfw_sec_min_bucket_ang;
  using _toa_pfw_mc_ok_type =
    bool;
  _toa_pfw_mc_ok_type toa_pfw_mc_ok;
  using _toa_pfw_mc_maybe_stalled_type =
    bool;
  _toa_pfw_mc_maybe_stalled_type toa_pfw_mc_maybe_stalled;
  using _toa_pfw_mc_maybe_rack_stall_type =
    bool;
  _toa_pfw_mc_maybe_rack_stall_type toa_pfw_mc_maybe_rack_stall;
  using _toa_pfw_mc_maybe_grounded_type =
    bool;
  _toa_pfw_mc_maybe_grounded_type toa_pfw_mc_maybe_grounded;
  using _toa_stat_payload_nl_notch_one_up_type =
    float;
  _toa_stat_payload_nl_notch_one_up_type toa_stat_payload_nl_notch_one_up;
  using _toa_stat_payload_nl_notch_one_low_type =
    float;
  _toa_stat_payload_nl_notch_one_low_type toa_stat_payload_nl_notch_one_low;
  using _toa_stat_payload_nl_notch_one_size_type =
    float;
  _toa_stat_payload_nl_notch_one_size_type toa_stat_payload_nl_notch_one_size;
  using _toa_stat_payload_nl_notch_two_up_type =
    float;
  _toa_stat_payload_nl_notch_two_up_type toa_stat_payload_nl_notch_two_up;
  using _toa_stat_payload_nl_notch_two_low_type =
    float;
  _toa_stat_payload_nl_notch_two_low_type toa_stat_payload_nl_notch_two_low;
  using _toa_stat_payload_nl_notch_two_size_type =
    float;
  _toa_stat_payload_nl_notch_two_size_type toa_stat_payload_nl_notch_two_size;
  using _toa_stat_payload_nl_one_up_type =
    float;
  _toa_stat_payload_nl_one_up_type toa_stat_payload_nl_one_up;
  using _toa_stat_payload_nl_one_low_type =
    float;
  _toa_stat_payload_nl_one_low_type toa_stat_payload_nl_one_low;
  using _toa_stat_payload_nl_one_size_type =
    float;
  _toa_stat_payload_nl_one_size_type toa_stat_payload_nl_one_size;
  using _toa_stat_payload_nl_two_up_type =
    float;
  _toa_stat_payload_nl_two_up_type toa_stat_payload_nl_two_up;
  using _toa_stat_payload_nl_two_low_type =
    float;
  _toa_stat_payload_nl_two_low_type toa_stat_payload_nl_two_low;
  using _toa_stat_payload_nl_two_size_type =
    float;
  _toa_stat_payload_nl_two_size_type toa_stat_payload_nl_two_size;
  using _toa_pfw_nl_st_dev_est_type =
    float;
  _toa_pfw_nl_st_dev_est_type toa_pfw_nl_st_dev_est;
  using _toa_pfw_nl_mean_est_type =
    float;
  _toa_pfw_nl_mean_est_type toa_pfw_nl_mean_est;
  using _toa_pfw_payload_filt_final_type =
    float;
  _toa_pfw_payload_filt_final_type toa_pfw_payload_filt_final;
  using _toa_pfw_payload_notch_filt_final_type =
    float;
  _toa_pfw_payload_notch_filt_final_type toa_pfw_payload_notch_filt_final;
  using _toa_pfw_payload_notch_post_type =
    float;
  _toa_pfw_payload_notch_post_type toa_pfw_payload_notch_post;
  using _toa_pfw_latch_invalidate_type =
    bool;
  _toa_pfw_latch_invalidate_type toa_pfw_latch_invalidate;
  using _toa_imu_raw_eef_accl_x_type =
    float;
  _toa_imu_raw_eef_accl_x_type toa_imu_raw_eef_accl_x;
  using _toa_imu_raw_eef_accl_y_type =
    float;
  _toa_imu_raw_eef_accl_y_type toa_imu_raw_eef_accl_y;
  using _toa_imu_raw_eef_accl_z_type =
    float;
  _toa_imu_raw_eef_accl_z_type toa_imu_raw_eef_accl_z;
  using _toa_imu_neef_grav_x_type =
    float;
  _toa_imu_neef_grav_x_type toa_imu_neef_grav_x;
  using _toa_imu_neef_grav_y_type =
    float;
  _toa_imu_neef_grav_y_type toa_imu_neef_grav_y;
  using _toa_imu_neef_grav_z_type =
    float;
  _toa_imu_neef_grav_z_type toa_imu_neef_grav_z;
  using _toa_imu_neef_pitch_type =
    float;
  _toa_imu_neef_pitch_type toa_imu_neef_pitch;
  using _toa_target_comp_margin_type =
    float;
  _toa_target_comp_margin_type toa_target_comp_margin;
  using _toa_target_payload_post_comp_type =
    float;
  _toa_target_payload_post_comp_type toa_target_payload_post_comp;
  using _toa_target_payload_pre_comp_type =
    float;
  _toa_target_payload_pre_comp_type toa_target_payload_pre_comp;
  using _toa_stat_payload_secure_two_size_type =
    float;
  _toa_stat_payload_secure_two_size_type toa_stat_payload_secure_two_size;
  using _toa_stat_payload_secure_one_upper_type =
    float;
  _toa_stat_payload_secure_one_upper_type toa_stat_payload_secure_one_upper;
  using _toa_stat_payload_secure_one_lower_type =
    float;
  _toa_stat_payload_secure_one_lower_type toa_stat_payload_secure_one_lower;
  using _toa_stat_payload_secure_one_size_type =
    float;
  _toa_stat_payload_secure_one_size_type toa_stat_payload_secure_one_size;
  using _toa_stat_payload_secure_two_upper_type =
    float;
  _toa_stat_payload_secure_two_upper_type toa_stat_payload_secure_two_upper;
  using _toa_stat_payload_secure_two_lower_type =
    float;
  _toa_stat_payload_secure_two_lower_type toa_stat_payload_secure_two_lower;
  using _toa_send_cpm_live_payload_type =
    float;
  _toa_send_cpm_live_payload_type toa_send_cpm_live_payload;
  using _toa_tool_bc_angle_type =
    float;
  _toa_tool_bc_angle_type toa_tool_bc_angle;

  // setters for named parameter idiom
  Type & set__toa_pfw_sec_latch(
    const bool & _arg)
  {
    this->toa_pfw_sec_latch = _arg;
    return *this;
  }
  Type & set__toa_pfw_sec_payload(
    const float & _arg)
  {
    this->toa_pfw_sec_payload = _arg;
    return *this;
  }
  Type & set__toa_pfw_sec_status(
    const uint8_t & _arg)
  {
    this->toa_pfw_sec_status = _arg;
    return *this;
  }
  Type & set__toa_pfw_sec_st_dev(
    const float & _arg)
  {
    this->toa_pfw_sec_st_dev = _arg;
    return *this;
  }
  Type & set__toa_target_payload_final(
    const float & _arg)
  {
    this->toa_target_payload_final = _arg;
    return *this;
  }
  Type & set__toa_target_payload_status(
    const bool & _arg)
  {
    this->toa_target_payload_status = _arg;
    return *this;
  }
  Type & set__toa_pfw_nl_notch_mean_est(
    const float & _arg)
  {
    this->toa_pfw_nl_notch_mean_est = _arg;
    return *this;
  }
  Type & set__toa_pfw_nl_notch_st_dev_est(
    const float & _arg)
  {
    this->toa_pfw_nl_notch_st_dev_est = _arg;
    return *this;
  }
  Type & set__toa_lw_lpf_post(
    const float & _arg)
  {
    this->toa_lw_lpf_post = _arg;
    return *this;
  }
  Type & set__toa_payload_adjusted(
    const float & _arg)
  {
    this->toa_payload_adjusted = _arg;
    return *this;
  }
  Type & set__toa_send_payload_arb(
    const float & _arg)
  {
    this->toa_send_payload_arb = _arg;
    return *this;
  }
  Type & set__toa_sfunc_in_grav_x(
    const float & _arg)
  {
    this->toa_sfunc_in_grav_x = _arg;
    return *this;
  }
  Type & set__toa_sfunc_in_grav_y(
    const float & _arg)
  {
    this->toa_sfunc_in_grav_y = _arg;
    return *this;
  }
  Type & set__toa_sfunc_in_lift_force(
    const float & _arg)
  {
    this->toa_sfunc_in_lift_force = _arg;
    return *this;
  }
  Type & set__toa_sfunc_in_tilt_force(
    const float & _arg)
  {
    this->toa_sfunc_in_tilt_force = _arg;
    return *this;
  }
  Type & set__toa_sfunc_out_raw_mass_tonne(
    const float & _arg)
  {
    this->toa_sfunc_out_raw_mass_tonne = _arg;
    return *this;
  }
  Type & set__toa_app_number(
    const uint32_t & _arg)
  {
    this->toa_app_number = _arg;
    return *this;
  }
  Type & set__toa_lift_bore_dia(
    const float & _arg)
  {
    this->toa_lift_bore_dia = _arg;
    return *this;
  }
  Type & set__toa_lift_rod_dia(
    const float & _arg)
  {
    this->toa_lift_rod_dia = _arg;
    return *this;
  }
  Type & set__toa_payload_anc_adjusted(
    const float & _arg)
  {
    this->toa_payload_anc_adjusted = _arg;
    return *this;
  }
  Type & set__toa_payload_anc_zeroed(
    const float & _arg)
  {
    this->toa_payload_anc_zeroed = _arg;
    return *this;
  }
  Type & set__toa_rated_payload(
    const float & _arg)
  {
    this->toa_rated_payload = _arg;
    return *this;
  }
  Type & set__toa_tilt_bore_dia(
    const float & _arg)
  {
    this->toa_tilt_bore_dia = _arg;
    return *this;
  }
  Type & set__toa_tilt_num_cyl(
    const uint8_t & _arg)
  {
    this->toa_tilt_num_cyl = _arg;
    return *this;
  }
  Type & set__toa_tilt_rod_dia(
    const float & _arg)
  {
    this->toa_tilt_rod_dia = _arg;
    return *this;
  }
  Type & set__toa_tool_bc_length(
    const float & _arg)
  {
    this->toa_tool_bc_length = _arg;
    return *this;
  }
  Type & set__toa_imu_cal_pitch_angle(
    const float & _arg)
  {
    this->toa_imu_cal_pitch_angle = _arg;
    return *this;
  }
  Type & set__toa_pfw_unsec_status(
    const uint8_t & _arg)
  {
    this->toa_pfw_unsec_status = _arg;
    return *this;
  }
  Type & set__toa_pfw_unsec_bound_lower(
    const float & _arg)
  {
    this->toa_pfw_unsec_bound_lower = _arg;
    return *this;
  }
  Type & set__toa_pfw_unsec_bound_upper(
    const float & _arg)
  {
    this->toa_pfw_unsec_bound_upper = _arg;
    return *this;
  }
  Type & set__toa_lw_spill_rate(
    const float & _arg)
  {
    this->toa_lw_spill_rate = _arg;
    return *this;
  }
  Type & set__toa_lw_status(
    const uint8_t & _arg)
  {
    this->toa_lw_status = _arg;
    return *this;
  }
  Type & set__toa_raw_dist(
    const float & _arg)
  {
    this->toa_raw_dist = _arg;
    return *this;
  }
  Type & set__toa_raw_payload(
    const float & _arg)
  {
    this->toa_raw_payload = _arg;
    return *this;
  }
  Type & set__toa_payload_zeroed(
    const float & _arg)
  {
    this->toa_payload_zeroed = _arg;
    return *this;
  }
  Type & set__toa_pfw_is_warm(
    const bool & _arg)
  {
    this->toa_pfw_is_warm = _arg;
    return *this;
  }
  Type & set__toa_pfw_sec_is_secure(
    const bool & _arg)
  {
    this->toa_pfw_sec_is_secure = _arg;
    return *this;
  }
  Type & set__toa_pfw_sec_is_no_sliding(
    const bool & _arg)
  {
    this->toa_pfw_sec_is_no_sliding = _arg;
    return *this;
  }
  Type & set__toa_pfw_sec_is_no_collapsing(
    const bool & _arg)
  {
    this->toa_pfw_sec_is_no_collapsing = _arg;
    return *this;
  }
  Type & set__toa_pfw_sec_is_racked(
    const bool & _arg)
  {
    this->toa_pfw_sec_is_racked = _arg;
    return *this;
  }
  Type & set__toa_pfw_sec_min_bucket_ang(
    const float & _arg)
  {
    this->toa_pfw_sec_min_bucket_ang = _arg;
    return *this;
  }
  Type & set__toa_pfw_mc_ok(
    const bool & _arg)
  {
    this->toa_pfw_mc_ok = _arg;
    return *this;
  }
  Type & set__toa_pfw_mc_maybe_stalled(
    const bool & _arg)
  {
    this->toa_pfw_mc_maybe_stalled = _arg;
    return *this;
  }
  Type & set__toa_pfw_mc_maybe_rack_stall(
    const bool & _arg)
  {
    this->toa_pfw_mc_maybe_rack_stall = _arg;
    return *this;
  }
  Type & set__toa_pfw_mc_maybe_grounded(
    const bool & _arg)
  {
    this->toa_pfw_mc_maybe_grounded = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_notch_one_up(
    const float & _arg)
  {
    this->toa_stat_payload_nl_notch_one_up = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_notch_one_low(
    const float & _arg)
  {
    this->toa_stat_payload_nl_notch_one_low = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_notch_one_size(
    const float & _arg)
  {
    this->toa_stat_payload_nl_notch_one_size = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_notch_two_up(
    const float & _arg)
  {
    this->toa_stat_payload_nl_notch_two_up = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_notch_two_low(
    const float & _arg)
  {
    this->toa_stat_payload_nl_notch_two_low = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_notch_two_size(
    const float & _arg)
  {
    this->toa_stat_payload_nl_notch_two_size = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_one_up(
    const float & _arg)
  {
    this->toa_stat_payload_nl_one_up = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_one_low(
    const float & _arg)
  {
    this->toa_stat_payload_nl_one_low = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_one_size(
    const float & _arg)
  {
    this->toa_stat_payload_nl_one_size = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_two_up(
    const float & _arg)
  {
    this->toa_stat_payload_nl_two_up = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_two_low(
    const float & _arg)
  {
    this->toa_stat_payload_nl_two_low = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_nl_two_size(
    const float & _arg)
  {
    this->toa_stat_payload_nl_two_size = _arg;
    return *this;
  }
  Type & set__toa_pfw_nl_st_dev_est(
    const float & _arg)
  {
    this->toa_pfw_nl_st_dev_est = _arg;
    return *this;
  }
  Type & set__toa_pfw_nl_mean_est(
    const float & _arg)
  {
    this->toa_pfw_nl_mean_est = _arg;
    return *this;
  }
  Type & set__toa_pfw_payload_filt_final(
    const float & _arg)
  {
    this->toa_pfw_payload_filt_final = _arg;
    return *this;
  }
  Type & set__toa_pfw_payload_notch_filt_final(
    const float & _arg)
  {
    this->toa_pfw_payload_notch_filt_final = _arg;
    return *this;
  }
  Type & set__toa_pfw_payload_notch_post(
    const float & _arg)
  {
    this->toa_pfw_payload_notch_post = _arg;
    return *this;
  }
  Type & set__toa_pfw_latch_invalidate(
    const bool & _arg)
  {
    this->toa_pfw_latch_invalidate = _arg;
    return *this;
  }
  Type & set__toa_imu_raw_eef_accl_x(
    const float & _arg)
  {
    this->toa_imu_raw_eef_accl_x = _arg;
    return *this;
  }
  Type & set__toa_imu_raw_eef_accl_y(
    const float & _arg)
  {
    this->toa_imu_raw_eef_accl_y = _arg;
    return *this;
  }
  Type & set__toa_imu_raw_eef_accl_z(
    const float & _arg)
  {
    this->toa_imu_raw_eef_accl_z = _arg;
    return *this;
  }
  Type & set__toa_imu_neef_grav_x(
    const float & _arg)
  {
    this->toa_imu_neef_grav_x = _arg;
    return *this;
  }
  Type & set__toa_imu_neef_grav_y(
    const float & _arg)
  {
    this->toa_imu_neef_grav_y = _arg;
    return *this;
  }
  Type & set__toa_imu_neef_grav_z(
    const float & _arg)
  {
    this->toa_imu_neef_grav_z = _arg;
    return *this;
  }
  Type & set__toa_imu_neef_pitch(
    const float & _arg)
  {
    this->toa_imu_neef_pitch = _arg;
    return *this;
  }
  Type & set__toa_target_comp_margin(
    const float & _arg)
  {
    this->toa_target_comp_margin = _arg;
    return *this;
  }
  Type & set__toa_target_payload_post_comp(
    const float & _arg)
  {
    this->toa_target_payload_post_comp = _arg;
    return *this;
  }
  Type & set__toa_target_payload_pre_comp(
    const float & _arg)
  {
    this->toa_target_payload_pre_comp = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_secure_two_size(
    const float & _arg)
  {
    this->toa_stat_payload_secure_two_size = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_secure_one_upper(
    const float & _arg)
  {
    this->toa_stat_payload_secure_one_upper = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_secure_one_lower(
    const float & _arg)
  {
    this->toa_stat_payload_secure_one_lower = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_secure_one_size(
    const float & _arg)
  {
    this->toa_stat_payload_secure_one_size = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_secure_two_upper(
    const float & _arg)
  {
    this->toa_stat_payload_secure_two_upper = _arg;
    return *this;
  }
  Type & set__toa_stat_payload_secure_two_lower(
    const float & _arg)
  {
    this->toa_stat_payload_secure_two_lower = _arg;
    return *this;
  }
  Type & set__toa_send_cpm_live_payload(
    const float & _arg)
  {
    this->toa_send_cpm_live_payload = _arg;
    return *this;
  }
  Type & set__toa_tool_bc_angle(
    const float & _arg)
  {
    this->toa_tool_bc_angle = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__TipoffModelTestPoints
    std::shared_ptr<weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__TipoffModelTestPoints
    std::shared_ptr<weigh_app_interfaces::msg::TipoffModelTestPoints_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TipoffModelTestPoints_ & other) const
  {
    if (this->toa_pfw_sec_latch != other.toa_pfw_sec_latch) {
      return false;
    }
    if (this->toa_pfw_sec_payload != other.toa_pfw_sec_payload) {
      return false;
    }
    if (this->toa_pfw_sec_status != other.toa_pfw_sec_status) {
      return false;
    }
    if (this->toa_pfw_sec_st_dev != other.toa_pfw_sec_st_dev) {
      return false;
    }
    if (this->toa_target_payload_final != other.toa_target_payload_final) {
      return false;
    }
    if (this->toa_target_payload_status != other.toa_target_payload_status) {
      return false;
    }
    if (this->toa_pfw_nl_notch_mean_est != other.toa_pfw_nl_notch_mean_est) {
      return false;
    }
    if (this->toa_pfw_nl_notch_st_dev_est != other.toa_pfw_nl_notch_st_dev_est) {
      return false;
    }
    if (this->toa_lw_lpf_post != other.toa_lw_lpf_post) {
      return false;
    }
    if (this->toa_payload_adjusted != other.toa_payload_adjusted) {
      return false;
    }
    if (this->toa_send_payload_arb != other.toa_send_payload_arb) {
      return false;
    }
    if (this->toa_sfunc_in_grav_x != other.toa_sfunc_in_grav_x) {
      return false;
    }
    if (this->toa_sfunc_in_grav_y != other.toa_sfunc_in_grav_y) {
      return false;
    }
    if (this->toa_sfunc_in_lift_force != other.toa_sfunc_in_lift_force) {
      return false;
    }
    if (this->toa_sfunc_in_tilt_force != other.toa_sfunc_in_tilt_force) {
      return false;
    }
    if (this->toa_sfunc_out_raw_mass_tonne != other.toa_sfunc_out_raw_mass_tonne) {
      return false;
    }
    if (this->toa_app_number != other.toa_app_number) {
      return false;
    }
    if (this->toa_lift_bore_dia != other.toa_lift_bore_dia) {
      return false;
    }
    if (this->toa_lift_rod_dia != other.toa_lift_rod_dia) {
      return false;
    }
    if (this->toa_payload_anc_adjusted != other.toa_payload_anc_adjusted) {
      return false;
    }
    if (this->toa_payload_anc_zeroed != other.toa_payload_anc_zeroed) {
      return false;
    }
    if (this->toa_rated_payload != other.toa_rated_payload) {
      return false;
    }
    if (this->toa_tilt_bore_dia != other.toa_tilt_bore_dia) {
      return false;
    }
    if (this->toa_tilt_num_cyl != other.toa_tilt_num_cyl) {
      return false;
    }
    if (this->toa_tilt_rod_dia != other.toa_tilt_rod_dia) {
      return false;
    }
    if (this->toa_tool_bc_length != other.toa_tool_bc_length) {
      return false;
    }
    if (this->toa_imu_cal_pitch_angle != other.toa_imu_cal_pitch_angle) {
      return false;
    }
    if (this->toa_pfw_unsec_status != other.toa_pfw_unsec_status) {
      return false;
    }
    if (this->toa_pfw_unsec_bound_lower != other.toa_pfw_unsec_bound_lower) {
      return false;
    }
    if (this->toa_pfw_unsec_bound_upper != other.toa_pfw_unsec_bound_upper) {
      return false;
    }
    if (this->toa_lw_spill_rate != other.toa_lw_spill_rate) {
      return false;
    }
    if (this->toa_lw_status != other.toa_lw_status) {
      return false;
    }
    if (this->toa_raw_dist != other.toa_raw_dist) {
      return false;
    }
    if (this->toa_raw_payload != other.toa_raw_payload) {
      return false;
    }
    if (this->toa_payload_zeroed != other.toa_payload_zeroed) {
      return false;
    }
    if (this->toa_pfw_is_warm != other.toa_pfw_is_warm) {
      return false;
    }
    if (this->toa_pfw_sec_is_secure != other.toa_pfw_sec_is_secure) {
      return false;
    }
    if (this->toa_pfw_sec_is_no_sliding != other.toa_pfw_sec_is_no_sliding) {
      return false;
    }
    if (this->toa_pfw_sec_is_no_collapsing != other.toa_pfw_sec_is_no_collapsing) {
      return false;
    }
    if (this->toa_pfw_sec_is_racked != other.toa_pfw_sec_is_racked) {
      return false;
    }
    if (this->toa_pfw_sec_min_bucket_ang != other.toa_pfw_sec_min_bucket_ang) {
      return false;
    }
    if (this->toa_pfw_mc_ok != other.toa_pfw_mc_ok) {
      return false;
    }
    if (this->toa_pfw_mc_maybe_stalled != other.toa_pfw_mc_maybe_stalled) {
      return false;
    }
    if (this->toa_pfw_mc_maybe_rack_stall != other.toa_pfw_mc_maybe_rack_stall) {
      return false;
    }
    if (this->toa_pfw_mc_maybe_grounded != other.toa_pfw_mc_maybe_grounded) {
      return false;
    }
    if (this->toa_stat_payload_nl_notch_one_up != other.toa_stat_payload_nl_notch_one_up) {
      return false;
    }
    if (this->toa_stat_payload_nl_notch_one_low != other.toa_stat_payload_nl_notch_one_low) {
      return false;
    }
    if (this->toa_stat_payload_nl_notch_one_size != other.toa_stat_payload_nl_notch_one_size) {
      return false;
    }
    if (this->toa_stat_payload_nl_notch_two_up != other.toa_stat_payload_nl_notch_two_up) {
      return false;
    }
    if (this->toa_stat_payload_nl_notch_two_low != other.toa_stat_payload_nl_notch_two_low) {
      return false;
    }
    if (this->toa_stat_payload_nl_notch_two_size != other.toa_stat_payload_nl_notch_two_size) {
      return false;
    }
    if (this->toa_stat_payload_nl_one_up != other.toa_stat_payload_nl_one_up) {
      return false;
    }
    if (this->toa_stat_payload_nl_one_low != other.toa_stat_payload_nl_one_low) {
      return false;
    }
    if (this->toa_stat_payload_nl_one_size != other.toa_stat_payload_nl_one_size) {
      return false;
    }
    if (this->toa_stat_payload_nl_two_up != other.toa_stat_payload_nl_two_up) {
      return false;
    }
    if (this->toa_stat_payload_nl_two_low != other.toa_stat_payload_nl_two_low) {
      return false;
    }
    if (this->toa_stat_payload_nl_two_size != other.toa_stat_payload_nl_two_size) {
      return false;
    }
    if (this->toa_pfw_nl_st_dev_est != other.toa_pfw_nl_st_dev_est) {
      return false;
    }
    if (this->toa_pfw_nl_mean_est != other.toa_pfw_nl_mean_est) {
      return false;
    }
    if (this->toa_pfw_payload_filt_final != other.toa_pfw_payload_filt_final) {
      return false;
    }
    if (this->toa_pfw_payload_notch_filt_final != other.toa_pfw_payload_notch_filt_final) {
      return false;
    }
    if (this->toa_pfw_payload_notch_post != other.toa_pfw_payload_notch_post) {
      return false;
    }
    if (this->toa_pfw_latch_invalidate != other.toa_pfw_latch_invalidate) {
      return false;
    }
    if (this->toa_imu_raw_eef_accl_x != other.toa_imu_raw_eef_accl_x) {
      return false;
    }
    if (this->toa_imu_raw_eef_accl_y != other.toa_imu_raw_eef_accl_y) {
      return false;
    }
    if (this->toa_imu_raw_eef_accl_z != other.toa_imu_raw_eef_accl_z) {
      return false;
    }
    if (this->toa_imu_neef_grav_x != other.toa_imu_neef_grav_x) {
      return false;
    }
    if (this->toa_imu_neef_grav_y != other.toa_imu_neef_grav_y) {
      return false;
    }
    if (this->toa_imu_neef_grav_z != other.toa_imu_neef_grav_z) {
      return false;
    }
    if (this->toa_imu_neef_pitch != other.toa_imu_neef_pitch) {
      return false;
    }
    if (this->toa_target_comp_margin != other.toa_target_comp_margin) {
      return false;
    }
    if (this->toa_target_payload_post_comp != other.toa_target_payload_post_comp) {
      return false;
    }
    if (this->toa_target_payload_pre_comp != other.toa_target_payload_pre_comp) {
      return false;
    }
    if (this->toa_stat_payload_secure_two_size != other.toa_stat_payload_secure_two_size) {
      return false;
    }
    if (this->toa_stat_payload_secure_one_upper != other.toa_stat_payload_secure_one_upper) {
      return false;
    }
    if (this->toa_stat_payload_secure_one_lower != other.toa_stat_payload_secure_one_lower) {
      return false;
    }
    if (this->toa_stat_payload_secure_one_size != other.toa_stat_payload_secure_one_size) {
      return false;
    }
    if (this->toa_stat_payload_secure_two_upper != other.toa_stat_payload_secure_two_upper) {
      return false;
    }
    if (this->toa_stat_payload_secure_two_lower != other.toa_stat_payload_secure_two_lower) {
      return false;
    }
    if (this->toa_send_cpm_live_payload != other.toa_send_cpm_live_payload) {
      return false;
    }
    if (this->toa_tool_bc_angle != other.toa_tool_bc_angle) {
      return false;
    }
    return true;
  }
  bool operator!=(const TipoffModelTestPoints_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TipoffModelTestPoints_

// alias to use template instance with default allocator
using TipoffModelTestPoints =
  weigh_app_interfaces::msg::TipoffModelTestPoints_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_MODEL_TEST_POINTS__STRUCT_HPP_
