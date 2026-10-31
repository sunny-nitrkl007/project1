// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaWeighDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_weigh_debug_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'inst_wt_raw'
#include "cpm_common_interfaces/msg/detail/float_io__struct.hpp"
// Member 'tipoff_inputs'
#include "weigh_app_interfaces/msg/detail/tipoff_assist_inputs__struct.hpp"
// Member 'tipoff_outputs'
#include "weigh_app_interfaces/msg/detail/tipoff_assist_outputs__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaWeighDebugChannel __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaWeighDebugChannel __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaWeighDebugChannel_
{
  using Type = LpsSaWeighDebugChannel_<ContainerAllocator>;

  explicit LpsSaWeighDebugChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : inst_wt_raw(_init),
    tipoff_inputs(_init),
    tipoff_outputs(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->reweigh_warn = 0;
      this->debug_lift_cyl_he_period = 0l;
      this->debug_lift_cyl_he_width = 0l;
      this->debug_lift_cyl_he_dc = 0.0f;
      this->debug_lift_cyl_he_press = 0.0f;
      this->debug_lift_cyl_he_press_status = 0l;
      this->debug_lift_cyl_re_period = 0l;
      this->debug_lift_cyl_re_width = 0l;
      this->debug_lift_cyl_re_dc = 0.0f;
      this->debug_lift_cyl_re_press = 0.0f;
      this->debug_lift_cyl_re_press_status = 0l;
      this->debug_tilt_cyl_he_period = 0l;
      this->debug_tilt_cyl_he_width = 0l;
      this->debug_tilt_cyl_he_dc = 0.0f;
      this->debug_tilt_cyl_he_press = 0.0f;
      this->debug_tilt_cyl_he_press_status = 0l;
      this->debug_tilt_cyl_re_period = 0l;
      this->debug_tilt_cyl_re_width = 0l;
      this->debug_tilt_cyl_re_dc = 0.0f;
      this->debug_tilt_cyl_re_press = 0.0f;
      this->debug_tilt_cyl_re_press_status = 0l;
      this->debug_lift_cyl_period = 0l;
      this->debug_lift_cyl_width = 0l;
      this->debug_lift_cyl_dc = 0.0f;
      this->debug_lift_cyl_raw_ext = 0.0f;
      this->debug_lift_cyl_filt_ext = 0.0f;
      this->debug_lift_cyl_norm_len = 0.0f;
      this->debug_lift_cyl_vel = 0.0f;
      this->debug_lift_angle = 0.0f;
      this->debug_lift_ang_vel = 0.0f;
      this->debug_lift_position_status = 0l;
      this->debug_tilt_cyl_period = 0l;
      this->debug_tilt_cyl_width = 0l;
      this->debug_tilt_cyl_dc = 0.0f;
      this->debug_tilt_cyl_raw_len = 0.0f;
      this->debug_tilt_cyl_norm_len = 0.0f;
      this->debug_tilt_cyl_vel = 0.0f;
      this->debug_tilt_angle = 0.0f;
      this->debug_tilt_angle_abc = 0.0f;
      this->debug_tilt_position_status = 0l;
      this->debug_bucket_angle = 0.0f;
      this->debug_bucket_angle_status = 0l;
      this->debug_hyd_oil_temp = 0.0f;
      this->debug_hyd_oil_temp_status = 0l;
      this->debug_requested_gear = 0;
      this->debug_requested_gear_status = 0l;
      this->debug_weigh_updt_loader_bkt_payld_trgt_wt = 0.0f;
      this->debug_weigh_updt_clock_keyon_sec = 0ul;
      this->debug_weigh_updt_pass_count = 0ul;
      this->best_bkt_wt_payload_calc_meth = 0.0f;
      this->best_bkt_wt_wt = 0.0f;
      this->best_bkt_wt_tipoff_live_weight_in_use = false;
      this->cyl_flow_const_lift_he_flow_const = 0.0f;
      this->cyl_flow_const_lift_re_to_he_flow_ratio = 0.0f;
      this->dig_detect_data_dig_detected = false;
      this->dig_detect_data_dig_duration = 0.0f;
      this->dig_detect_data_dig_started = false;
      this->dig_detect_data_dig_state = 0;
      this->dig_detect_data_wt_stabilized = false;
      this->dump_wt_change_data_dump_cumulative_wt_change = 0.0f;
      this->inst_wt_der = 0.0f;
      this->inst_wt_filt = 0.0f;
      this->inst_wt_llw_filt = 0.0f;
      this->inst_wt_raw_pre_tilt_comp = 0.0f;
      this->inst_wt_raw_post_tilt_comp = 0.0f;
      this->lift_cyl_pressure = 0.0f;
      this->lift_cyl_pressure_v0 = 0.0f;
      this->lift_cyl_pressure_imu_adjusted = 0.0f;
      this->live_weigh_tbl_stat = 0;
      this->live_weigh_tbl_wt = 0.0f;
      this->live_weigh_tbl_use_fast_filter = false;
      this->low_lift_wt_wt = 0.0f;
      this->low_lift_wt_confidence = 0.0f;
      this->low_lift_wt_confidence_est = 0.0f;
      this->low_lift_wt_confidence_timer = 0.0f;
      this->low_lift_wt_last_input = 0.0f;
      this->low_lift_wt_mean_est = 0.0f;
      this->low_lift_wt_mean_est_comp = 0.0f;
      this->low_lift_wt_stat = 0;
      this->low_lift_wt_stdev_est = 0.0f;
      this->low_lift_wt_variance_est = 0.0f;
      this->dump_state_status = 0;
      this->lps_stall_detect_lift_stalled = false;
      this->linkage_movement_lift = 0.0f;
      this->linkage_movement_tilt = 0.0f;
      this->wrw_tbl_wk_tbl_result_weight_ave_raw = 0.0f;
      this->wrw_tbl_wk_tbl_result_weight_ave = 0.0f;
      this->wrw_tbl_op_tbl_wt = 0.0f;
      this->wrw_tbl_op_tbl_warning = false;
      this->wrw_tbl_op_tbl_indicator = 0l;
      this->wrw_tbl_op_tbl_status = 0;
      this->wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp = 0.0f;
      this->wrw_tbl_wk_tbl_been_below_range = false;
      this->zero_adj_tbl_zero_adj_status = 0;
      this->overload_warn_tbl_bucket_load_factor = 0.0f;
      this->overload_warn_tbl_dig_reverse_flag = false;
      this->overload_warn_tbl_in_overload_range = false;
      this->overload_warn_tbl_level = 0;
      this->overload_warn_tbl_prev_dig_state = 0;
      this->lift_position_filt_length = 0.0f;
      this->lift_position_filt_velocity = 0.0f;
      this->lift_position_filt_angle = 0.0f;
      this->chassis_imu_gravity_x = 0.0f;
      this->chassis_imu_gravity_y = 0.0f;
      this->chassis_imu_gravity_z = 0.0f;
      this->chassis_imu_velocity_x = 0.0f;
      this->chassis_imu_velocity_y = 0.0f;
      this->chassis_imu_velocity_z = 0.0f;
      this->chassis_imu_bias_mag_jerk = 0.0f;
      this->chassis_imu_bias_mag_ang_accel = 0.0f;
      this->chassis_imu_bias_max_ang_vel = 0.0f;
      this->chassis_imu_bias_ang_vel_x = 0.0f;
      this->chassis_imu_bias_ang_vel_y = 0.0f;
      this->chassis_imu_bias_ang_vel_z = 0.0f;
      this->chassis_imu_pitch = 0.0f;
      this->chassis_imu_roll = 0.0f;
      this->chassis_imu_sensor_lin_acc_status = 0;
      this->chassis_imu_sensor_ang_vel_status = 0;
      this->chassis_imu_lin_acc_x = 0.0f;
      this->chassis_imu_lin_acc_y = 0.0f;
      this->chassis_imu_lin_acc_z = 0.0f;
      this->chassis_imu_ang_vel_x = 0.0f;
      this->chassis_imu_ang_vel_y = 0.0f;
      this->chassis_imu_ang_vel_z = 0.0f;
    }
  }

  explicit LpsSaWeighDebugChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : inst_wt_raw(_alloc, _init),
    tipoff_inputs(_alloc, _init),
    tipoff_outputs(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->reweigh_warn = 0;
      this->debug_lift_cyl_he_period = 0l;
      this->debug_lift_cyl_he_width = 0l;
      this->debug_lift_cyl_he_dc = 0.0f;
      this->debug_lift_cyl_he_press = 0.0f;
      this->debug_lift_cyl_he_press_status = 0l;
      this->debug_lift_cyl_re_period = 0l;
      this->debug_lift_cyl_re_width = 0l;
      this->debug_lift_cyl_re_dc = 0.0f;
      this->debug_lift_cyl_re_press = 0.0f;
      this->debug_lift_cyl_re_press_status = 0l;
      this->debug_tilt_cyl_he_period = 0l;
      this->debug_tilt_cyl_he_width = 0l;
      this->debug_tilt_cyl_he_dc = 0.0f;
      this->debug_tilt_cyl_he_press = 0.0f;
      this->debug_tilt_cyl_he_press_status = 0l;
      this->debug_tilt_cyl_re_period = 0l;
      this->debug_tilt_cyl_re_width = 0l;
      this->debug_tilt_cyl_re_dc = 0.0f;
      this->debug_tilt_cyl_re_press = 0.0f;
      this->debug_tilt_cyl_re_press_status = 0l;
      this->debug_lift_cyl_period = 0l;
      this->debug_lift_cyl_width = 0l;
      this->debug_lift_cyl_dc = 0.0f;
      this->debug_lift_cyl_raw_ext = 0.0f;
      this->debug_lift_cyl_filt_ext = 0.0f;
      this->debug_lift_cyl_norm_len = 0.0f;
      this->debug_lift_cyl_vel = 0.0f;
      this->debug_lift_angle = 0.0f;
      this->debug_lift_ang_vel = 0.0f;
      this->debug_lift_position_status = 0l;
      this->debug_tilt_cyl_period = 0l;
      this->debug_tilt_cyl_width = 0l;
      this->debug_tilt_cyl_dc = 0.0f;
      this->debug_tilt_cyl_raw_len = 0.0f;
      this->debug_tilt_cyl_norm_len = 0.0f;
      this->debug_tilt_cyl_vel = 0.0f;
      this->debug_tilt_angle = 0.0f;
      this->debug_tilt_angle_abc = 0.0f;
      this->debug_tilt_position_status = 0l;
      this->debug_bucket_angle = 0.0f;
      this->debug_bucket_angle_status = 0l;
      this->debug_hyd_oil_temp = 0.0f;
      this->debug_hyd_oil_temp_status = 0l;
      this->debug_requested_gear = 0;
      this->debug_requested_gear_status = 0l;
      this->debug_weigh_updt_loader_bkt_payld_trgt_wt = 0.0f;
      this->debug_weigh_updt_clock_keyon_sec = 0ul;
      this->debug_weigh_updt_pass_count = 0ul;
      this->best_bkt_wt_payload_calc_meth = 0.0f;
      this->best_bkt_wt_wt = 0.0f;
      this->best_bkt_wt_tipoff_live_weight_in_use = false;
      this->cyl_flow_const_lift_he_flow_const = 0.0f;
      this->cyl_flow_const_lift_re_to_he_flow_ratio = 0.0f;
      this->dig_detect_data_dig_detected = false;
      this->dig_detect_data_dig_duration = 0.0f;
      this->dig_detect_data_dig_started = false;
      this->dig_detect_data_dig_state = 0;
      this->dig_detect_data_wt_stabilized = false;
      this->dump_wt_change_data_dump_cumulative_wt_change = 0.0f;
      this->inst_wt_der = 0.0f;
      this->inst_wt_filt = 0.0f;
      this->inst_wt_llw_filt = 0.0f;
      this->inst_wt_raw_pre_tilt_comp = 0.0f;
      this->inst_wt_raw_post_tilt_comp = 0.0f;
      this->lift_cyl_pressure = 0.0f;
      this->lift_cyl_pressure_v0 = 0.0f;
      this->lift_cyl_pressure_imu_adjusted = 0.0f;
      this->live_weigh_tbl_stat = 0;
      this->live_weigh_tbl_wt = 0.0f;
      this->live_weigh_tbl_use_fast_filter = false;
      this->low_lift_wt_wt = 0.0f;
      this->low_lift_wt_confidence = 0.0f;
      this->low_lift_wt_confidence_est = 0.0f;
      this->low_lift_wt_confidence_timer = 0.0f;
      this->low_lift_wt_last_input = 0.0f;
      this->low_lift_wt_mean_est = 0.0f;
      this->low_lift_wt_mean_est_comp = 0.0f;
      this->low_lift_wt_stat = 0;
      this->low_lift_wt_stdev_est = 0.0f;
      this->low_lift_wt_variance_est = 0.0f;
      this->dump_state_status = 0;
      this->lps_stall_detect_lift_stalled = false;
      this->linkage_movement_lift = 0.0f;
      this->linkage_movement_tilt = 0.0f;
      this->wrw_tbl_wk_tbl_result_weight_ave_raw = 0.0f;
      this->wrw_tbl_wk_tbl_result_weight_ave = 0.0f;
      this->wrw_tbl_op_tbl_wt = 0.0f;
      this->wrw_tbl_op_tbl_warning = false;
      this->wrw_tbl_op_tbl_indicator = 0l;
      this->wrw_tbl_op_tbl_status = 0;
      this->wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp = 0.0f;
      this->wrw_tbl_wk_tbl_been_below_range = false;
      this->zero_adj_tbl_zero_adj_status = 0;
      this->overload_warn_tbl_bucket_load_factor = 0.0f;
      this->overload_warn_tbl_dig_reverse_flag = false;
      this->overload_warn_tbl_in_overload_range = false;
      this->overload_warn_tbl_level = 0;
      this->overload_warn_tbl_prev_dig_state = 0;
      this->lift_position_filt_length = 0.0f;
      this->lift_position_filt_velocity = 0.0f;
      this->lift_position_filt_angle = 0.0f;
      this->chassis_imu_gravity_x = 0.0f;
      this->chassis_imu_gravity_y = 0.0f;
      this->chassis_imu_gravity_z = 0.0f;
      this->chassis_imu_velocity_x = 0.0f;
      this->chassis_imu_velocity_y = 0.0f;
      this->chassis_imu_velocity_z = 0.0f;
      this->chassis_imu_bias_mag_jerk = 0.0f;
      this->chassis_imu_bias_mag_ang_accel = 0.0f;
      this->chassis_imu_bias_max_ang_vel = 0.0f;
      this->chassis_imu_bias_ang_vel_x = 0.0f;
      this->chassis_imu_bias_ang_vel_y = 0.0f;
      this->chassis_imu_bias_ang_vel_z = 0.0f;
      this->chassis_imu_pitch = 0.0f;
      this->chassis_imu_roll = 0.0f;
      this->chassis_imu_sensor_lin_acc_status = 0;
      this->chassis_imu_sensor_ang_vel_status = 0;
      this->chassis_imu_lin_acc_x = 0.0f;
      this->chassis_imu_lin_acc_y = 0.0f;
      this->chassis_imu_lin_acc_z = 0.0f;
      this->chassis_imu_ang_vel_x = 0.0f;
      this->chassis_imu_ang_vel_y = 0.0f;
      this->chassis_imu_ang_vel_z = 0.0f;
    }
  }

  // field types and members
  using _reweigh_warn_type =
    uint16_t;
  _reweigh_warn_type reweigh_warn;
  using _debug_lift_cyl_he_period_type =
    int32_t;
  _debug_lift_cyl_he_period_type debug_lift_cyl_he_period;
  using _debug_lift_cyl_he_width_type =
    int32_t;
  _debug_lift_cyl_he_width_type debug_lift_cyl_he_width;
  using _debug_lift_cyl_he_dc_type =
    float;
  _debug_lift_cyl_he_dc_type debug_lift_cyl_he_dc;
  using _debug_lift_cyl_he_press_type =
    float;
  _debug_lift_cyl_he_press_type debug_lift_cyl_he_press;
  using _debug_lift_cyl_he_press_status_type =
    int32_t;
  _debug_lift_cyl_he_press_status_type debug_lift_cyl_he_press_status;
  using _debug_lift_cyl_re_period_type =
    int32_t;
  _debug_lift_cyl_re_period_type debug_lift_cyl_re_period;
  using _debug_lift_cyl_re_width_type =
    int32_t;
  _debug_lift_cyl_re_width_type debug_lift_cyl_re_width;
  using _debug_lift_cyl_re_dc_type =
    float;
  _debug_lift_cyl_re_dc_type debug_lift_cyl_re_dc;
  using _debug_lift_cyl_re_press_type =
    float;
  _debug_lift_cyl_re_press_type debug_lift_cyl_re_press;
  using _debug_lift_cyl_re_press_status_type =
    int32_t;
  _debug_lift_cyl_re_press_status_type debug_lift_cyl_re_press_status;
  using _debug_tilt_cyl_he_period_type =
    int32_t;
  _debug_tilt_cyl_he_period_type debug_tilt_cyl_he_period;
  using _debug_tilt_cyl_he_width_type =
    int32_t;
  _debug_tilt_cyl_he_width_type debug_tilt_cyl_he_width;
  using _debug_tilt_cyl_he_dc_type =
    float;
  _debug_tilt_cyl_he_dc_type debug_tilt_cyl_he_dc;
  using _debug_tilt_cyl_he_press_type =
    float;
  _debug_tilt_cyl_he_press_type debug_tilt_cyl_he_press;
  using _debug_tilt_cyl_he_press_status_type =
    int32_t;
  _debug_tilt_cyl_he_press_status_type debug_tilt_cyl_he_press_status;
  using _debug_tilt_cyl_re_period_type =
    int32_t;
  _debug_tilt_cyl_re_period_type debug_tilt_cyl_re_period;
  using _debug_tilt_cyl_re_width_type =
    int32_t;
  _debug_tilt_cyl_re_width_type debug_tilt_cyl_re_width;
  using _debug_tilt_cyl_re_dc_type =
    float;
  _debug_tilt_cyl_re_dc_type debug_tilt_cyl_re_dc;
  using _debug_tilt_cyl_re_press_type =
    float;
  _debug_tilt_cyl_re_press_type debug_tilt_cyl_re_press;
  using _debug_tilt_cyl_re_press_status_type =
    int32_t;
  _debug_tilt_cyl_re_press_status_type debug_tilt_cyl_re_press_status;
  using _debug_lift_cyl_period_type =
    int32_t;
  _debug_lift_cyl_period_type debug_lift_cyl_period;
  using _debug_lift_cyl_width_type =
    int32_t;
  _debug_lift_cyl_width_type debug_lift_cyl_width;
  using _debug_lift_cyl_dc_type =
    float;
  _debug_lift_cyl_dc_type debug_lift_cyl_dc;
  using _debug_lift_cyl_raw_ext_type =
    float;
  _debug_lift_cyl_raw_ext_type debug_lift_cyl_raw_ext;
  using _debug_lift_cyl_filt_ext_type =
    float;
  _debug_lift_cyl_filt_ext_type debug_lift_cyl_filt_ext;
  using _debug_lift_cyl_norm_len_type =
    float;
  _debug_lift_cyl_norm_len_type debug_lift_cyl_norm_len;
  using _debug_lift_cyl_vel_type =
    float;
  _debug_lift_cyl_vel_type debug_lift_cyl_vel;
  using _debug_lift_angle_type =
    float;
  _debug_lift_angle_type debug_lift_angle;
  using _debug_lift_ang_vel_type =
    float;
  _debug_lift_ang_vel_type debug_lift_ang_vel;
  using _debug_lift_position_status_type =
    int32_t;
  _debug_lift_position_status_type debug_lift_position_status;
  using _debug_tilt_cyl_period_type =
    int32_t;
  _debug_tilt_cyl_period_type debug_tilt_cyl_period;
  using _debug_tilt_cyl_width_type =
    int32_t;
  _debug_tilt_cyl_width_type debug_tilt_cyl_width;
  using _debug_tilt_cyl_dc_type =
    float;
  _debug_tilt_cyl_dc_type debug_tilt_cyl_dc;
  using _debug_tilt_cyl_raw_len_type =
    float;
  _debug_tilt_cyl_raw_len_type debug_tilt_cyl_raw_len;
  using _debug_tilt_cyl_norm_len_type =
    float;
  _debug_tilt_cyl_norm_len_type debug_tilt_cyl_norm_len;
  using _debug_tilt_cyl_vel_type =
    float;
  _debug_tilt_cyl_vel_type debug_tilt_cyl_vel;
  using _debug_tilt_angle_type =
    float;
  _debug_tilt_angle_type debug_tilt_angle;
  using _debug_tilt_angle_abc_type =
    float;
  _debug_tilt_angle_abc_type debug_tilt_angle_abc;
  using _debug_tilt_position_status_type =
    int32_t;
  _debug_tilt_position_status_type debug_tilt_position_status;
  using _debug_bucket_angle_type =
    float;
  _debug_bucket_angle_type debug_bucket_angle;
  using _debug_bucket_angle_status_type =
    int32_t;
  _debug_bucket_angle_status_type debug_bucket_angle_status;
  using _debug_hyd_oil_temp_type =
    float;
  _debug_hyd_oil_temp_type debug_hyd_oil_temp;
  using _debug_hyd_oil_temp_status_type =
    int32_t;
  _debug_hyd_oil_temp_status_type debug_hyd_oil_temp_status;
  using _debug_requested_gear_type =
    uint16_t;
  _debug_requested_gear_type debug_requested_gear;
  using _debug_requested_gear_status_type =
    int32_t;
  _debug_requested_gear_status_type debug_requested_gear_status;
  using _debug_weigh_updt_loader_bkt_payld_trgt_wt_type =
    float;
  _debug_weigh_updt_loader_bkt_payld_trgt_wt_type debug_weigh_updt_loader_bkt_payld_trgt_wt;
  using _debug_weigh_updt_clock_keyon_sec_type =
    uint32_t;
  _debug_weigh_updt_clock_keyon_sec_type debug_weigh_updt_clock_keyon_sec;
  using _debug_weigh_updt_pass_count_type =
    uint32_t;
  _debug_weigh_updt_pass_count_type debug_weigh_updt_pass_count;
  using _best_bkt_wt_payload_calc_meth_type =
    float;
  _best_bkt_wt_payload_calc_meth_type best_bkt_wt_payload_calc_meth;
  using _best_bkt_wt_wt_type =
    float;
  _best_bkt_wt_wt_type best_bkt_wt_wt;
  using _best_bkt_wt_tipoff_live_weight_in_use_type =
    bool;
  _best_bkt_wt_tipoff_live_weight_in_use_type best_bkt_wt_tipoff_live_weight_in_use;
  using _cyl_flow_const_lift_he_flow_const_type =
    float;
  _cyl_flow_const_lift_he_flow_const_type cyl_flow_const_lift_he_flow_const;
  using _cyl_flow_const_lift_re_to_he_flow_ratio_type =
    float;
  _cyl_flow_const_lift_re_to_he_flow_ratio_type cyl_flow_const_lift_re_to_he_flow_ratio;
  using _dig_detect_data_dig_detected_type =
    bool;
  _dig_detect_data_dig_detected_type dig_detect_data_dig_detected;
  using _dig_detect_data_dig_duration_type =
    float;
  _dig_detect_data_dig_duration_type dig_detect_data_dig_duration;
  using _dig_detect_data_dig_started_type =
    bool;
  _dig_detect_data_dig_started_type dig_detect_data_dig_started;
  using _dig_detect_data_dig_state_type =
    uint8_t;
  _dig_detect_data_dig_state_type dig_detect_data_dig_state;
  using _dig_detect_data_wt_stabilized_type =
    bool;
  _dig_detect_data_wt_stabilized_type dig_detect_data_wt_stabilized;
  using _dump_wt_change_data_dump_cumulative_wt_change_type =
    float;
  _dump_wt_change_data_dump_cumulative_wt_change_type dump_wt_change_data_dump_cumulative_wt_change;
  using _inst_wt_der_type =
    float;
  _inst_wt_der_type inst_wt_der;
  using _inst_wt_filt_type =
    float;
  _inst_wt_filt_type inst_wt_filt;
  using _inst_wt_llw_filt_type =
    float;
  _inst_wt_llw_filt_type inst_wt_llw_filt;
  using _inst_wt_raw_type =
    cpm_common_interfaces::msg::FloatIO_<ContainerAllocator>;
  _inst_wt_raw_type inst_wt_raw;
  using _inst_wt_raw_pre_tilt_comp_type =
    float;
  _inst_wt_raw_pre_tilt_comp_type inst_wt_raw_pre_tilt_comp;
  using _inst_wt_raw_post_tilt_comp_type =
    float;
  _inst_wt_raw_post_tilt_comp_type inst_wt_raw_post_tilt_comp;
  using _lift_cyl_pressure_type =
    float;
  _lift_cyl_pressure_type lift_cyl_pressure;
  using _lift_cyl_pressure_v0_type =
    float;
  _lift_cyl_pressure_v0_type lift_cyl_pressure_v0;
  using _lift_cyl_pressure_imu_adjusted_type =
    float;
  _lift_cyl_pressure_imu_adjusted_type lift_cyl_pressure_imu_adjusted;
  using _live_weigh_tbl_stat_type =
    uint8_t;
  _live_weigh_tbl_stat_type live_weigh_tbl_stat;
  using _live_weigh_tbl_wt_type =
    float;
  _live_weigh_tbl_wt_type live_weigh_tbl_wt;
  using _live_weigh_tbl_use_fast_filter_type =
    bool;
  _live_weigh_tbl_use_fast_filter_type live_weigh_tbl_use_fast_filter;
  using _low_lift_wt_wt_type =
    float;
  _low_lift_wt_wt_type low_lift_wt_wt;
  using _low_lift_wt_confidence_type =
    float;
  _low_lift_wt_confidence_type low_lift_wt_confidence;
  using _low_lift_wt_confidence_est_type =
    float;
  _low_lift_wt_confidence_est_type low_lift_wt_confidence_est;
  using _low_lift_wt_confidence_timer_type =
    float;
  _low_lift_wt_confidence_timer_type low_lift_wt_confidence_timer;
  using _low_lift_wt_last_input_type =
    float;
  _low_lift_wt_last_input_type low_lift_wt_last_input;
  using _low_lift_wt_mean_est_type =
    float;
  _low_lift_wt_mean_est_type low_lift_wt_mean_est;
  using _low_lift_wt_mean_est_comp_type =
    float;
  _low_lift_wt_mean_est_comp_type low_lift_wt_mean_est_comp;
  using _low_lift_wt_stat_type =
    uint8_t;
  _low_lift_wt_stat_type low_lift_wt_stat;
  using _low_lift_wt_stdev_est_type =
    float;
  _low_lift_wt_stdev_est_type low_lift_wt_stdev_est;
  using _low_lift_wt_variance_est_type =
    float;
  _low_lift_wt_variance_est_type low_lift_wt_variance_est;
  using _dump_state_status_type =
    uint8_t;
  _dump_state_status_type dump_state_status;
  using _lps_stall_detect_lift_stalled_type =
    bool;
  _lps_stall_detect_lift_stalled_type lps_stall_detect_lift_stalled;
  using _linkage_movement_lift_type =
    float;
  _linkage_movement_lift_type linkage_movement_lift;
  using _linkage_movement_tilt_type =
    float;
  _linkage_movement_tilt_type linkage_movement_tilt;
  using _wrw_tbl_wk_tbl_result_weight_ave_raw_type =
    float;
  _wrw_tbl_wk_tbl_result_weight_ave_raw_type wrw_tbl_wk_tbl_result_weight_ave_raw;
  using _wrw_tbl_wk_tbl_result_weight_ave_type =
    float;
  _wrw_tbl_wk_tbl_result_weight_ave_type wrw_tbl_wk_tbl_result_weight_ave;
  using _wrw_tbl_op_tbl_wt_type =
    float;
  _wrw_tbl_op_tbl_wt_type wrw_tbl_op_tbl_wt;
  using _wrw_tbl_op_tbl_warning_type =
    bool;
  _wrw_tbl_op_tbl_warning_type wrw_tbl_op_tbl_warning;
  using _wrw_tbl_op_tbl_indicator_type =
    int32_t;
  _wrw_tbl_op_tbl_indicator_type wrw_tbl_op_tbl_indicator;
  using _wrw_tbl_op_tbl_status_type =
    uint8_t;
  _wrw_tbl_op_tbl_status_type wrw_tbl_op_tbl_status;
  using _wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp_type =
    float;
  _wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp_type wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp;
  using _wrw_tbl_wk_tbl_been_below_range_type =
    bool;
  _wrw_tbl_wk_tbl_been_below_range_type wrw_tbl_wk_tbl_been_below_range;
  using _zero_adj_tbl_zero_adj_status_type =
    uint8_t;
  _zero_adj_tbl_zero_adj_status_type zero_adj_tbl_zero_adj_status;
  using _overload_warn_tbl_bucket_load_factor_type =
    float;
  _overload_warn_tbl_bucket_load_factor_type overload_warn_tbl_bucket_load_factor;
  using _overload_warn_tbl_dig_reverse_flag_type =
    bool;
  _overload_warn_tbl_dig_reverse_flag_type overload_warn_tbl_dig_reverse_flag;
  using _overload_warn_tbl_in_overload_range_type =
    bool;
  _overload_warn_tbl_in_overload_range_type overload_warn_tbl_in_overload_range;
  using _overload_warn_tbl_level_type =
    uint8_t;
  _overload_warn_tbl_level_type overload_warn_tbl_level;
  using _overload_warn_tbl_prev_dig_state_type =
    uint8_t;
  _overload_warn_tbl_prev_dig_state_type overload_warn_tbl_prev_dig_state;
  using _lift_position_filt_length_type =
    float;
  _lift_position_filt_length_type lift_position_filt_length;
  using _lift_position_filt_velocity_type =
    float;
  _lift_position_filt_velocity_type lift_position_filt_velocity;
  using _lift_position_filt_angle_type =
    float;
  _lift_position_filt_angle_type lift_position_filt_angle;
  using _tipoff_inputs_type =
    weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator>;
  _tipoff_inputs_type tipoff_inputs;
  using _tipoff_outputs_type =
    weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator>;
  _tipoff_outputs_type tipoff_outputs;
  using _chassis_imu_gravity_x_type =
    float;
  _chassis_imu_gravity_x_type chassis_imu_gravity_x;
  using _chassis_imu_gravity_y_type =
    float;
  _chassis_imu_gravity_y_type chassis_imu_gravity_y;
  using _chassis_imu_gravity_z_type =
    float;
  _chassis_imu_gravity_z_type chassis_imu_gravity_z;
  using _chassis_imu_velocity_x_type =
    float;
  _chassis_imu_velocity_x_type chassis_imu_velocity_x;
  using _chassis_imu_velocity_y_type =
    float;
  _chassis_imu_velocity_y_type chassis_imu_velocity_y;
  using _chassis_imu_velocity_z_type =
    float;
  _chassis_imu_velocity_z_type chassis_imu_velocity_z;
  using _chassis_imu_bias_mag_jerk_type =
    float;
  _chassis_imu_bias_mag_jerk_type chassis_imu_bias_mag_jerk;
  using _chassis_imu_bias_mag_ang_accel_type =
    float;
  _chassis_imu_bias_mag_ang_accel_type chassis_imu_bias_mag_ang_accel;
  using _chassis_imu_bias_max_ang_vel_type =
    float;
  _chassis_imu_bias_max_ang_vel_type chassis_imu_bias_max_ang_vel;
  using _chassis_imu_bias_ang_vel_x_type =
    float;
  _chassis_imu_bias_ang_vel_x_type chassis_imu_bias_ang_vel_x;
  using _chassis_imu_bias_ang_vel_y_type =
    float;
  _chassis_imu_bias_ang_vel_y_type chassis_imu_bias_ang_vel_y;
  using _chassis_imu_bias_ang_vel_z_type =
    float;
  _chassis_imu_bias_ang_vel_z_type chassis_imu_bias_ang_vel_z;
  using _chassis_imu_pitch_type =
    float;
  _chassis_imu_pitch_type chassis_imu_pitch;
  using _chassis_imu_roll_type =
    float;
  _chassis_imu_roll_type chassis_imu_roll;
  using _chassis_imu_sensor_lin_acc_status_type =
    uint8_t;
  _chassis_imu_sensor_lin_acc_status_type chassis_imu_sensor_lin_acc_status;
  using _chassis_imu_sensor_ang_vel_status_type =
    uint8_t;
  _chassis_imu_sensor_ang_vel_status_type chassis_imu_sensor_ang_vel_status;
  using _chassis_imu_lin_acc_x_type =
    float;
  _chassis_imu_lin_acc_x_type chassis_imu_lin_acc_x;
  using _chassis_imu_lin_acc_y_type =
    float;
  _chassis_imu_lin_acc_y_type chassis_imu_lin_acc_y;
  using _chassis_imu_lin_acc_z_type =
    float;
  _chassis_imu_lin_acc_z_type chassis_imu_lin_acc_z;
  using _chassis_imu_ang_vel_x_type =
    float;
  _chassis_imu_ang_vel_x_type chassis_imu_ang_vel_x;
  using _chassis_imu_ang_vel_y_type =
    float;
  _chassis_imu_ang_vel_y_type chassis_imu_ang_vel_y;
  using _chassis_imu_ang_vel_z_type =
    float;
  _chassis_imu_ang_vel_z_type chassis_imu_ang_vel_z;

  // setters for named parameter idiom
  Type & set__reweigh_warn(
    const uint16_t & _arg)
  {
    this->reweigh_warn = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_he_period(
    const int32_t & _arg)
  {
    this->debug_lift_cyl_he_period = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_he_width(
    const int32_t & _arg)
  {
    this->debug_lift_cyl_he_width = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_he_dc(
    const float & _arg)
  {
    this->debug_lift_cyl_he_dc = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_he_press(
    const float & _arg)
  {
    this->debug_lift_cyl_he_press = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_he_press_status(
    const int32_t & _arg)
  {
    this->debug_lift_cyl_he_press_status = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_re_period(
    const int32_t & _arg)
  {
    this->debug_lift_cyl_re_period = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_re_width(
    const int32_t & _arg)
  {
    this->debug_lift_cyl_re_width = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_re_dc(
    const float & _arg)
  {
    this->debug_lift_cyl_re_dc = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_re_press(
    const float & _arg)
  {
    this->debug_lift_cyl_re_press = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_re_press_status(
    const int32_t & _arg)
  {
    this->debug_lift_cyl_re_press_status = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_he_period(
    const int32_t & _arg)
  {
    this->debug_tilt_cyl_he_period = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_he_width(
    const int32_t & _arg)
  {
    this->debug_tilt_cyl_he_width = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_he_dc(
    const float & _arg)
  {
    this->debug_tilt_cyl_he_dc = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_he_press(
    const float & _arg)
  {
    this->debug_tilt_cyl_he_press = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_he_press_status(
    const int32_t & _arg)
  {
    this->debug_tilt_cyl_he_press_status = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_re_period(
    const int32_t & _arg)
  {
    this->debug_tilt_cyl_re_period = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_re_width(
    const int32_t & _arg)
  {
    this->debug_tilt_cyl_re_width = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_re_dc(
    const float & _arg)
  {
    this->debug_tilt_cyl_re_dc = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_re_press(
    const float & _arg)
  {
    this->debug_tilt_cyl_re_press = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_re_press_status(
    const int32_t & _arg)
  {
    this->debug_tilt_cyl_re_press_status = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_period(
    const int32_t & _arg)
  {
    this->debug_lift_cyl_period = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_width(
    const int32_t & _arg)
  {
    this->debug_lift_cyl_width = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_dc(
    const float & _arg)
  {
    this->debug_lift_cyl_dc = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_raw_ext(
    const float & _arg)
  {
    this->debug_lift_cyl_raw_ext = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_filt_ext(
    const float & _arg)
  {
    this->debug_lift_cyl_filt_ext = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_norm_len(
    const float & _arg)
  {
    this->debug_lift_cyl_norm_len = _arg;
    return *this;
  }
  Type & set__debug_lift_cyl_vel(
    const float & _arg)
  {
    this->debug_lift_cyl_vel = _arg;
    return *this;
  }
  Type & set__debug_lift_angle(
    const float & _arg)
  {
    this->debug_lift_angle = _arg;
    return *this;
  }
  Type & set__debug_lift_ang_vel(
    const float & _arg)
  {
    this->debug_lift_ang_vel = _arg;
    return *this;
  }
  Type & set__debug_lift_position_status(
    const int32_t & _arg)
  {
    this->debug_lift_position_status = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_period(
    const int32_t & _arg)
  {
    this->debug_tilt_cyl_period = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_width(
    const int32_t & _arg)
  {
    this->debug_tilt_cyl_width = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_dc(
    const float & _arg)
  {
    this->debug_tilt_cyl_dc = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_raw_len(
    const float & _arg)
  {
    this->debug_tilt_cyl_raw_len = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_norm_len(
    const float & _arg)
  {
    this->debug_tilt_cyl_norm_len = _arg;
    return *this;
  }
  Type & set__debug_tilt_cyl_vel(
    const float & _arg)
  {
    this->debug_tilt_cyl_vel = _arg;
    return *this;
  }
  Type & set__debug_tilt_angle(
    const float & _arg)
  {
    this->debug_tilt_angle = _arg;
    return *this;
  }
  Type & set__debug_tilt_angle_abc(
    const float & _arg)
  {
    this->debug_tilt_angle_abc = _arg;
    return *this;
  }
  Type & set__debug_tilt_position_status(
    const int32_t & _arg)
  {
    this->debug_tilt_position_status = _arg;
    return *this;
  }
  Type & set__debug_bucket_angle(
    const float & _arg)
  {
    this->debug_bucket_angle = _arg;
    return *this;
  }
  Type & set__debug_bucket_angle_status(
    const int32_t & _arg)
  {
    this->debug_bucket_angle_status = _arg;
    return *this;
  }
  Type & set__debug_hyd_oil_temp(
    const float & _arg)
  {
    this->debug_hyd_oil_temp = _arg;
    return *this;
  }
  Type & set__debug_hyd_oil_temp_status(
    const int32_t & _arg)
  {
    this->debug_hyd_oil_temp_status = _arg;
    return *this;
  }
  Type & set__debug_requested_gear(
    const uint16_t & _arg)
  {
    this->debug_requested_gear = _arg;
    return *this;
  }
  Type & set__debug_requested_gear_status(
    const int32_t & _arg)
  {
    this->debug_requested_gear_status = _arg;
    return *this;
  }
  Type & set__debug_weigh_updt_loader_bkt_payld_trgt_wt(
    const float & _arg)
  {
    this->debug_weigh_updt_loader_bkt_payld_trgt_wt = _arg;
    return *this;
  }
  Type & set__debug_weigh_updt_clock_keyon_sec(
    const uint32_t & _arg)
  {
    this->debug_weigh_updt_clock_keyon_sec = _arg;
    return *this;
  }
  Type & set__debug_weigh_updt_pass_count(
    const uint32_t & _arg)
  {
    this->debug_weigh_updt_pass_count = _arg;
    return *this;
  }
  Type & set__best_bkt_wt_payload_calc_meth(
    const float & _arg)
  {
    this->best_bkt_wt_payload_calc_meth = _arg;
    return *this;
  }
  Type & set__best_bkt_wt_wt(
    const float & _arg)
  {
    this->best_bkt_wt_wt = _arg;
    return *this;
  }
  Type & set__best_bkt_wt_tipoff_live_weight_in_use(
    const bool & _arg)
  {
    this->best_bkt_wt_tipoff_live_weight_in_use = _arg;
    return *this;
  }
  Type & set__cyl_flow_const_lift_he_flow_const(
    const float & _arg)
  {
    this->cyl_flow_const_lift_he_flow_const = _arg;
    return *this;
  }
  Type & set__cyl_flow_const_lift_re_to_he_flow_ratio(
    const float & _arg)
  {
    this->cyl_flow_const_lift_re_to_he_flow_ratio = _arg;
    return *this;
  }
  Type & set__dig_detect_data_dig_detected(
    const bool & _arg)
  {
    this->dig_detect_data_dig_detected = _arg;
    return *this;
  }
  Type & set__dig_detect_data_dig_duration(
    const float & _arg)
  {
    this->dig_detect_data_dig_duration = _arg;
    return *this;
  }
  Type & set__dig_detect_data_dig_started(
    const bool & _arg)
  {
    this->dig_detect_data_dig_started = _arg;
    return *this;
  }
  Type & set__dig_detect_data_dig_state(
    const uint8_t & _arg)
  {
    this->dig_detect_data_dig_state = _arg;
    return *this;
  }
  Type & set__dig_detect_data_wt_stabilized(
    const bool & _arg)
  {
    this->dig_detect_data_wt_stabilized = _arg;
    return *this;
  }
  Type & set__dump_wt_change_data_dump_cumulative_wt_change(
    const float & _arg)
  {
    this->dump_wt_change_data_dump_cumulative_wt_change = _arg;
    return *this;
  }
  Type & set__inst_wt_der(
    const float & _arg)
  {
    this->inst_wt_der = _arg;
    return *this;
  }
  Type & set__inst_wt_filt(
    const float & _arg)
  {
    this->inst_wt_filt = _arg;
    return *this;
  }
  Type & set__inst_wt_llw_filt(
    const float & _arg)
  {
    this->inst_wt_llw_filt = _arg;
    return *this;
  }
  Type & set__inst_wt_raw(
    const cpm_common_interfaces::msg::FloatIO_<ContainerAllocator> & _arg)
  {
    this->inst_wt_raw = _arg;
    return *this;
  }
  Type & set__inst_wt_raw_pre_tilt_comp(
    const float & _arg)
  {
    this->inst_wt_raw_pre_tilt_comp = _arg;
    return *this;
  }
  Type & set__inst_wt_raw_post_tilt_comp(
    const float & _arg)
  {
    this->inst_wt_raw_post_tilt_comp = _arg;
    return *this;
  }
  Type & set__lift_cyl_pressure(
    const float & _arg)
  {
    this->lift_cyl_pressure = _arg;
    return *this;
  }
  Type & set__lift_cyl_pressure_v0(
    const float & _arg)
  {
    this->lift_cyl_pressure_v0 = _arg;
    return *this;
  }
  Type & set__lift_cyl_pressure_imu_adjusted(
    const float & _arg)
  {
    this->lift_cyl_pressure_imu_adjusted = _arg;
    return *this;
  }
  Type & set__live_weigh_tbl_stat(
    const uint8_t & _arg)
  {
    this->live_weigh_tbl_stat = _arg;
    return *this;
  }
  Type & set__live_weigh_tbl_wt(
    const float & _arg)
  {
    this->live_weigh_tbl_wt = _arg;
    return *this;
  }
  Type & set__live_weigh_tbl_use_fast_filter(
    const bool & _arg)
  {
    this->live_weigh_tbl_use_fast_filter = _arg;
    return *this;
  }
  Type & set__low_lift_wt_wt(
    const float & _arg)
  {
    this->low_lift_wt_wt = _arg;
    return *this;
  }
  Type & set__low_lift_wt_confidence(
    const float & _arg)
  {
    this->low_lift_wt_confidence = _arg;
    return *this;
  }
  Type & set__low_lift_wt_confidence_est(
    const float & _arg)
  {
    this->low_lift_wt_confidence_est = _arg;
    return *this;
  }
  Type & set__low_lift_wt_confidence_timer(
    const float & _arg)
  {
    this->low_lift_wt_confidence_timer = _arg;
    return *this;
  }
  Type & set__low_lift_wt_last_input(
    const float & _arg)
  {
    this->low_lift_wt_last_input = _arg;
    return *this;
  }
  Type & set__low_lift_wt_mean_est(
    const float & _arg)
  {
    this->low_lift_wt_mean_est = _arg;
    return *this;
  }
  Type & set__low_lift_wt_mean_est_comp(
    const float & _arg)
  {
    this->low_lift_wt_mean_est_comp = _arg;
    return *this;
  }
  Type & set__low_lift_wt_stat(
    const uint8_t & _arg)
  {
    this->low_lift_wt_stat = _arg;
    return *this;
  }
  Type & set__low_lift_wt_stdev_est(
    const float & _arg)
  {
    this->low_lift_wt_stdev_est = _arg;
    return *this;
  }
  Type & set__low_lift_wt_variance_est(
    const float & _arg)
  {
    this->low_lift_wt_variance_est = _arg;
    return *this;
  }
  Type & set__dump_state_status(
    const uint8_t & _arg)
  {
    this->dump_state_status = _arg;
    return *this;
  }
  Type & set__lps_stall_detect_lift_stalled(
    const bool & _arg)
  {
    this->lps_stall_detect_lift_stalled = _arg;
    return *this;
  }
  Type & set__linkage_movement_lift(
    const float & _arg)
  {
    this->linkage_movement_lift = _arg;
    return *this;
  }
  Type & set__linkage_movement_tilt(
    const float & _arg)
  {
    this->linkage_movement_tilt = _arg;
    return *this;
  }
  Type & set__wrw_tbl_wk_tbl_result_weight_ave_raw(
    const float & _arg)
  {
    this->wrw_tbl_wk_tbl_result_weight_ave_raw = _arg;
    return *this;
  }
  Type & set__wrw_tbl_wk_tbl_result_weight_ave(
    const float & _arg)
  {
    this->wrw_tbl_wk_tbl_result_weight_ave = _arg;
    return *this;
  }
  Type & set__wrw_tbl_op_tbl_wt(
    const float & _arg)
  {
    this->wrw_tbl_op_tbl_wt = _arg;
    return *this;
  }
  Type & set__wrw_tbl_op_tbl_warning(
    const bool & _arg)
  {
    this->wrw_tbl_op_tbl_warning = _arg;
    return *this;
  }
  Type & set__wrw_tbl_op_tbl_indicator(
    const int32_t & _arg)
  {
    this->wrw_tbl_op_tbl_indicator = _arg;
    return *this;
  }
  Type & set__wrw_tbl_op_tbl_status(
    const uint8_t & _arg)
  {
    this->wrw_tbl_op_tbl_status = _arg;
    return *this;
  }
  Type & set__wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp(
    const float & _arg)
  {
    this->wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp = _arg;
    return *this;
  }
  Type & set__wrw_tbl_wk_tbl_been_below_range(
    const bool & _arg)
  {
    this->wrw_tbl_wk_tbl_been_below_range = _arg;
    return *this;
  }
  Type & set__zero_adj_tbl_zero_adj_status(
    const uint8_t & _arg)
  {
    this->zero_adj_tbl_zero_adj_status = _arg;
    return *this;
  }
  Type & set__overload_warn_tbl_bucket_load_factor(
    const float & _arg)
  {
    this->overload_warn_tbl_bucket_load_factor = _arg;
    return *this;
  }
  Type & set__overload_warn_tbl_dig_reverse_flag(
    const bool & _arg)
  {
    this->overload_warn_tbl_dig_reverse_flag = _arg;
    return *this;
  }
  Type & set__overload_warn_tbl_in_overload_range(
    const bool & _arg)
  {
    this->overload_warn_tbl_in_overload_range = _arg;
    return *this;
  }
  Type & set__overload_warn_tbl_level(
    const uint8_t & _arg)
  {
    this->overload_warn_tbl_level = _arg;
    return *this;
  }
  Type & set__overload_warn_tbl_prev_dig_state(
    const uint8_t & _arg)
  {
    this->overload_warn_tbl_prev_dig_state = _arg;
    return *this;
  }
  Type & set__lift_position_filt_length(
    const float & _arg)
  {
    this->lift_position_filt_length = _arg;
    return *this;
  }
  Type & set__lift_position_filt_velocity(
    const float & _arg)
  {
    this->lift_position_filt_velocity = _arg;
    return *this;
  }
  Type & set__lift_position_filt_angle(
    const float & _arg)
  {
    this->lift_position_filt_angle = _arg;
    return *this;
  }
  Type & set__tipoff_inputs(
    const weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator> & _arg)
  {
    this->tipoff_inputs = _arg;
    return *this;
  }
  Type & set__tipoff_outputs(
    const weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator> & _arg)
  {
    this->tipoff_outputs = _arg;
    return *this;
  }
  Type & set__chassis_imu_gravity_x(
    const float & _arg)
  {
    this->chassis_imu_gravity_x = _arg;
    return *this;
  }
  Type & set__chassis_imu_gravity_y(
    const float & _arg)
  {
    this->chassis_imu_gravity_y = _arg;
    return *this;
  }
  Type & set__chassis_imu_gravity_z(
    const float & _arg)
  {
    this->chassis_imu_gravity_z = _arg;
    return *this;
  }
  Type & set__chassis_imu_velocity_x(
    const float & _arg)
  {
    this->chassis_imu_velocity_x = _arg;
    return *this;
  }
  Type & set__chassis_imu_velocity_y(
    const float & _arg)
  {
    this->chassis_imu_velocity_y = _arg;
    return *this;
  }
  Type & set__chassis_imu_velocity_z(
    const float & _arg)
  {
    this->chassis_imu_velocity_z = _arg;
    return *this;
  }
  Type & set__chassis_imu_bias_mag_jerk(
    const float & _arg)
  {
    this->chassis_imu_bias_mag_jerk = _arg;
    return *this;
  }
  Type & set__chassis_imu_bias_mag_ang_accel(
    const float & _arg)
  {
    this->chassis_imu_bias_mag_ang_accel = _arg;
    return *this;
  }
  Type & set__chassis_imu_bias_max_ang_vel(
    const float & _arg)
  {
    this->chassis_imu_bias_max_ang_vel = _arg;
    return *this;
  }
  Type & set__chassis_imu_bias_ang_vel_x(
    const float & _arg)
  {
    this->chassis_imu_bias_ang_vel_x = _arg;
    return *this;
  }
  Type & set__chassis_imu_bias_ang_vel_y(
    const float & _arg)
  {
    this->chassis_imu_bias_ang_vel_y = _arg;
    return *this;
  }
  Type & set__chassis_imu_bias_ang_vel_z(
    const float & _arg)
  {
    this->chassis_imu_bias_ang_vel_z = _arg;
    return *this;
  }
  Type & set__chassis_imu_pitch(
    const float & _arg)
  {
    this->chassis_imu_pitch = _arg;
    return *this;
  }
  Type & set__chassis_imu_roll(
    const float & _arg)
  {
    this->chassis_imu_roll = _arg;
    return *this;
  }
  Type & set__chassis_imu_sensor_lin_acc_status(
    const uint8_t & _arg)
  {
    this->chassis_imu_sensor_lin_acc_status = _arg;
    return *this;
  }
  Type & set__chassis_imu_sensor_ang_vel_status(
    const uint8_t & _arg)
  {
    this->chassis_imu_sensor_ang_vel_status = _arg;
    return *this;
  }
  Type & set__chassis_imu_lin_acc_x(
    const float & _arg)
  {
    this->chassis_imu_lin_acc_x = _arg;
    return *this;
  }
  Type & set__chassis_imu_lin_acc_y(
    const float & _arg)
  {
    this->chassis_imu_lin_acc_y = _arg;
    return *this;
  }
  Type & set__chassis_imu_lin_acc_z(
    const float & _arg)
  {
    this->chassis_imu_lin_acc_z = _arg;
    return *this;
  }
  Type & set__chassis_imu_ang_vel_x(
    const float & _arg)
  {
    this->chassis_imu_ang_vel_x = _arg;
    return *this;
  }
  Type & set__chassis_imu_ang_vel_y(
    const float & _arg)
  {
    this->chassis_imu_ang_vel_y = _arg;
    return *this;
  }
  Type & set__chassis_imu_ang_vel_z(
    const float & _arg)
  {
    this->chassis_imu_ang_vel_z = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaWeighDebugChannel
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaWeighDebugChannel
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaWeighDebugChannel_ & other) const
  {
    if (this->reweigh_warn != other.reweigh_warn) {
      return false;
    }
    if (this->debug_lift_cyl_he_period != other.debug_lift_cyl_he_period) {
      return false;
    }
    if (this->debug_lift_cyl_he_width != other.debug_lift_cyl_he_width) {
      return false;
    }
    if (this->debug_lift_cyl_he_dc != other.debug_lift_cyl_he_dc) {
      return false;
    }
    if (this->debug_lift_cyl_he_press != other.debug_lift_cyl_he_press) {
      return false;
    }
    if (this->debug_lift_cyl_he_press_status != other.debug_lift_cyl_he_press_status) {
      return false;
    }
    if (this->debug_lift_cyl_re_period != other.debug_lift_cyl_re_period) {
      return false;
    }
    if (this->debug_lift_cyl_re_width != other.debug_lift_cyl_re_width) {
      return false;
    }
    if (this->debug_lift_cyl_re_dc != other.debug_lift_cyl_re_dc) {
      return false;
    }
    if (this->debug_lift_cyl_re_press != other.debug_lift_cyl_re_press) {
      return false;
    }
    if (this->debug_lift_cyl_re_press_status != other.debug_lift_cyl_re_press_status) {
      return false;
    }
    if (this->debug_tilt_cyl_he_period != other.debug_tilt_cyl_he_period) {
      return false;
    }
    if (this->debug_tilt_cyl_he_width != other.debug_tilt_cyl_he_width) {
      return false;
    }
    if (this->debug_tilt_cyl_he_dc != other.debug_tilt_cyl_he_dc) {
      return false;
    }
    if (this->debug_tilt_cyl_he_press != other.debug_tilt_cyl_he_press) {
      return false;
    }
    if (this->debug_tilt_cyl_he_press_status != other.debug_tilt_cyl_he_press_status) {
      return false;
    }
    if (this->debug_tilt_cyl_re_period != other.debug_tilt_cyl_re_period) {
      return false;
    }
    if (this->debug_tilt_cyl_re_width != other.debug_tilt_cyl_re_width) {
      return false;
    }
    if (this->debug_tilt_cyl_re_dc != other.debug_tilt_cyl_re_dc) {
      return false;
    }
    if (this->debug_tilt_cyl_re_press != other.debug_tilt_cyl_re_press) {
      return false;
    }
    if (this->debug_tilt_cyl_re_press_status != other.debug_tilt_cyl_re_press_status) {
      return false;
    }
    if (this->debug_lift_cyl_period != other.debug_lift_cyl_period) {
      return false;
    }
    if (this->debug_lift_cyl_width != other.debug_lift_cyl_width) {
      return false;
    }
    if (this->debug_lift_cyl_dc != other.debug_lift_cyl_dc) {
      return false;
    }
    if (this->debug_lift_cyl_raw_ext != other.debug_lift_cyl_raw_ext) {
      return false;
    }
    if (this->debug_lift_cyl_filt_ext != other.debug_lift_cyl_filt_ext) {
      return false;
    }
    if (this->debug_lift_cyl_norm_len != other.debug_lift_cyl_norm_len) {
      return false;
    }
    if (this->debug_lift_cyl_vel != other.debug_lift_cyl_vel) {
      return false;
    }
    if (this->debug_lift_angle != other.debug_lift_angle) {
      return false;
    }
    if (this->debug_lift_ang_vel != other.debug_lift_ang_vel) {
      return false;
    }
    if (this->debug_lift_position_status != other.debug_lift_position_status) {
      return false;
    }
    if (this->debug_tilt_cyl_period != other.debug_tilt_cyl_period) {
      return false;
    }
    if (this->debug_tilt_cyl_width != other.debug_tilt_cyl_width) {
      return false;
    }
    if (this->debug_tilt_cyl_dc != other.debug_tilt_cyl_dc) {
      return false;
    }
    if (this->debug_tilt_cyl_raw_len != other.debug_tilt_cyl_raw_len) {
      return false;
    }
    if (this->debug_tilt_cyl_norm_len != other.debug_tilt_cyl_norm_len) {
      return false;
    }
    if (this->debug_tilt_cyl_vel != other.debug_tilt_cyl_vel) {
      return false;
    }
    if (this->debug_tilt_angle != other.debug_tilt_angle) {
      return false;
    }
    if (this->debug_tilt_angle_abc != other.debug_tilt_angle_abc) {
      return false;
    }
    if (this->debug_tilt_position_status != other.debug_tilt_position_status) {
      return false;
    }
    if (this->debug_bucket_angle != other.debug_bucket_angle) {
      return false;
    }
    if (this->debug_bucket_angle_status != other.debug_bucket_angle_status) {
      return false;
    }
    if (this->debug_hyd_oil_temp != other.debug_hyd_oil_temp) {
      return false;
    }
    if (this->debug_hyd_oil_temp_status != other.debug_hyd_oil_temp_status) {
      return false;
    }
    if (this->debug_requested_gear != other.debug_requested_gear) {
      return false;
    }
    if (this->debug_requested_gear_status != other.debug_requested_gear_status) {
      return false;
    }
    if (this->debug_weigh_updt_loader_bkt_payld_trgt_wt != other.debug_weigh_updt_loader_bkt_payld_trgt_wt) {
      return false;
    }
    if (this->debug_weigh_updt_clock_keyon_sec != other.debug_weigh_updt_clock_keyon_sec) {
      return false;
    }
    if (this->debug_weigh_updt_pass_count != other.debug_weigh_updt_pass_count) {
      return false;
    }
    if (this->best_bkt_wt_payload_calc_meth != other.best_bkt_wt_payload_calc_meth) {
      return false;
    }
    if (this->best_bkt_wt_wt != other.best_bkt_wt_wt) {
      return false;
    }
    if (this->best_bkt_wt_tipoff_live_weight_in_use != other.best_bkt_wt_tipoff_live_weight_in_use) {
      return false;
    }
    if (this->cyl_flow_const_lift_he_flow_const != other.cyl_flow_const_lift_he_flow_const) {
      return false;
    }
    if (this->cyl_flow_const_lift_re_to_he_flow_ratio != other.cyl_flow_const_lift_re_to_he_flow_ratio) {
      return false;
    }
    if (this->dig_detect_data_dig_detected != other.dig_detect_data_dig_detected) {
      return false;
    }
    if (this->dig_detect_data_dig_duration != other.dig_detect_data_dig_duration) {
      return false;
    }
    if (this->dig_detect_data_dig_started != other.dig_detect_data_dig_started) {
      return false;
    }
    if (this->dig_detect_data_dig_state != other.dig_detect_data_dig_state) {
      return false;
    }
    if (this->dig_detect_data_wt_stabilized != other.dig_detect_data_wt_stabilized) {
      return false;
    }
    if (this->dump_wt_change_data_dump_cumulative_wt_change != other.dump_wt_change_data_dump_cumulative_wt_change) {
      return false;
    }
    if (this->inst_wt_der != other.inst_wt_der) {
      return false;
    }
    if (this->inst_wt_filt != other.inst_wt_filt) {
      return false;
    }
    if (this->inst_wt_llw_filt != other.inst_wt_llw_filt) {
      return false;
    }
    if (this->inst_wt_raw != other.inst_wt_raw) {
      return false;
    }
    if (this->inst_wt_raw_pre_tilt_comp != other.inst_wt_raw_pre_tilt_comp) {
      return false;
    }
    if (this->inst_wt_raw_post_tilt_comp != other.inst_wt_raw_post_tilt_comp) {
      return false;
    }
    if (this->lift_cyl_pressure != other.lift_cyl_pressure) {
      return false;
    }
    if (this->lift_cyl_pressure_v0 != other.lift_cyl_pressure_v0) {
      return false;
    }
    if (this->lift_cyl_pressure_imu_adjusted != other.lift_cyl_pressure_imu_adjusted) {
      return false;
    }
    if (this->live_weigh_tbl_stat != other.live_weigh_tbl_stat) {
      return false;
    }
    if (this->live_weigh_tbl_wt != other.live_weigh_tbl_wt) {
      return false;
    }
    if (this->live_weigh_tbl_use_fast_filter != other.live_weigh_tbl_use_fast_filter) {
      return false;
    }
    if (this->low_lift_wt_wt != other.low_lift_wt_wt) {
      return false;
    }
    if (this->low_lift_wt_confidence != other.low_lift_wt_confidence) {
      return false;
    }
    if (this->low_lift_wt_confidence_est != other.low_lift_wt_confidence_est) {
      return false;
    }
    if (this->low_lift_wt_confidence_timer != other.low_lift_wt_confidence_timer) {
      return false;
    }
    if (this->low_lift_wt_last_input != other.low_lift_wt_last_input) {
      return false;
    }
    if (this->low_lift_wt_mean_est != other.low_lift_wt_mean_est) {
      return false;
    }
    if (this->low_lift_wt_mean_est_comp != other.low_lift_wt_mean_est_comp) {
      return false;
    }
    if (this->low_lift_wt_stat != other.low_lift_wt_stat) {
      return false;
    }
    if (this->low_lift_wt_stdev_est != other.low_lift_wt_stdev_est) {
      return false;
    }
    if (this->low_lift_wt_variance_est != other.low_lift_wt_variance_est) {
      return false;
    }
    if (this->dump_state_status != other.dump_state_status) {
      return false;
    }
    if (this->lps_stall_detect_lift_stalled != other.lps_stall_detect_lift_stalled) {
      return false;
    }
    if (this->linkage_movement_lift != other.linkage_movement_lift) {
      return false;
    }
    if (this->linkage_movement_tilt != other.linkage_movement_tilt) {
      return false;
    }
    if (this->wrw_tbl_wk_tbl_result_weight_ave_raw != other.wrw_tbl_wk_tbl_result_weight_ave_raw) {
      return false;
    }
    if (this->wrw_tbl_wk_tbl_result_weight_ave != other.wrw_tbl_wk_tbl_result_weight_ave) {
      return false;
    }
    if (this->wrw_tbl_op_tbl_wt != other.wrw_tbl_op_tbl_wt) {
      return false;
    }
    if (this->wrw_tbl_op_tbl_warning != other.wrw_tbl_op_tbl_warning) {
      return false;
    }
    if (this->wrw_tbl_op_tbl_indicator != other.wrw_tbl_op_tbl_indicator) {
      return false;
    }
    if (this->wrw_tbl_op_tbl_status != other.wrw_tbl_op_tbl_status) {
      return false;
    }
    if (this->wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp != other.wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp) {
      return false;
    }
    if (this->wrw_tbl_wk_tbl_been_below_range != other.wrw_tbl_wk_tbl_been_below_range) {
      return false;
    }
    if (this->zero_adj_tbl_zero_adj_status != other.zero_adj_tbl_zero_adj_status) {
      return false;
    }
    if (this->overload_warn_tbl_bucket_load_factor != other.overload_warn_tbl_bucket_load_factor) {
      return false;
    }
    if (this->overload_warn_tbl_dig_reverse_flag != other.overload_warn_tbl_dig_reverse_flag) {
      return false;
    }
    if (this->overload_warn_tbl_in_overload_range != other.overload_warn_tbl_in_overload_range) {
      return false;
    }
    if (this->overload_warn_tbl_level != other.overload_warn_tbl_level) {
      return false;
    }
    if (this->overload_warn_tbl_prev_dig_state != other.overload_warn_tbl_prev_dig_state) {
      return false;
    }
    if (this->lift_position_filt_length != other.lift_position_filt_length) {
      return false;
    }
    if (this->lift_position_filt_velocity != other.lift_position_filt_velocity) {
      return false;
    }
    if (this->lift_position_filt_angle != other.lift_position_filt_angle) {
      return false;
    }
    if (this->tipoff_inputs != other.tipoff_inputs) {
      return false;
    }
    if (this->tipoff_outputs != other.tipoff_outputs) {
      return false;
    }
    if (this->chassis_imu_gravity_x != other.chassis_imu_gravity_x) {
      return false;
    }
    if (this->chassis_imu_gravity_y != other.chassis_imu_gravity_y) {
      return false;
    }
    if (this->chassis_imu_gravity_z != other.chassis_imu_gravity_z) {
      return false;
    }
    if (this->chassis_imu_velocity_x != other.chassis_imu_velocity_x) {
      return false;
    }
    if (this->chassis_imu_velocity_y != other.chassis_imu_velocity_y) {
      return false;
    }
    if (this->chassis_imu_velocity_z != other.chassis_imu_velocity_z) {
      return false;
    }
    if (this->chassis_imu_bias_mag_jerk != other.chassis_imu_bias_mag_jerk) {
      return false;
    }
    if (this->chassis_imu_bias_mag_ang_accel != other.chassis_imu_bias_mag_ang_accel) {
      return false;
    }
    if (this->chassis_imu_bias_max_ang_vel != other.chassis_imu_bias_max_ang_vel) {
      return false;
    }
    if (this->chassis_imu_bias_ang_vel_x != other.chassis_imu_bias_ang_vel_x) {
      return false;
    }
    if (this->chassis_imu_bias_ang_vel_y != other.chassis_imu_bias_ang_vel_y) {
      return false;
    }
    if (this->chassis_imu_bias_ang_vel_z != other.chassis_imu_bias_ang_vel_z) {
      return false;
    }
    if (this->chassis_imu_pitch != other.chassis_imu_pitch) {
      return false;
    }
    if (this->chassis_imu_roll != other.chassis_imu_roll) {
      return false;
    }
    if (this->chassis_imu_sensor_lin_acc_status != other.chassis_imu_sensor_lin_acc_status) {
      return false;
    }
    if (this->chassis_imu_sensor_ang_vel_status != other.chassis_imu_sensor_ang_vel_status) {
      return false;
    }
    if (this->chassis_imu_lin_acc_x != other.chassis_imu_lin_acc_x) {
      return false;
    }
    if (this->chassis_imu_lin_acc_y != other.chassis_imu_lin_acc_y) {
      return false;
    }
    if (this->chassis_imu_lin_acc_z != other.chassis_imu_lin_acc_z) {
      return false;
    }
    if (this->chassis_imu_ang_vel_x != other.chassis_imu_ang_vel_x) {
      return false;
    }
    if (this->chassis_imu_ang_vel_y != other.chassis_imu_ang_vel_y) {
      return false;
    }
    if (this->chassis_imu_ang_vel_z != other.chassis_imu_ang_vel_z) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaWeighDebugChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaWeighDebugChannel_

// alias to use template instance with default allocator
using LpsSaWeighDebugChannel =
  weigh_app_interfaces::msg::LpsSaWeighDebugChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_DEBUG_CHANNEL__STRUCT_HPP_
