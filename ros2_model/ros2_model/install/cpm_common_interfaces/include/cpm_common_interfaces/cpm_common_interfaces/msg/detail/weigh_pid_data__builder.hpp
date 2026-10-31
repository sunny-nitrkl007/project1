// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/WeighPidData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/weigh_pid_data.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/weigh_pid_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_WeighPidData_audible_weight_command
{
public:
  explicit Init_WeighPidData_audible_weight_command(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::WeighPidData audible_weight_command(::cpm_common_interfaces::msg::WeighPidData::_audible_weight_command_type arg)
  {
    msg_.audible_weight_command = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_audible_weight_enabled
{
public:
  explicit Init_WeighPidData_audible_weight_enabled(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_audible_weight_command audible_weight_enabled(::cpm_common_interfaces::msg::WeighPidData::_audible_weight_enabled_type arg)
  {
    msg_.audible_weight_enabled = std::move(arg);
    return Init_WeighPidData_audible_weight_command(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_hyd_oil_temp_enabled
{
public:
  explicit Init_WeighPidData_hyd_oil_temp_enabled(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_audible_weight_enabled hyd_oil_temp_enabled(::cpm_common_interfaces::msg::WeighPidData::_hyd_oil_temp_enabled_type arg)
  {
    msg_.hyd_oil_temp_enabled = std::move(arg);
    return Init_WeighPidData_audible_weight_enabled(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_tipoff_pitch_cal_offset
{
public:
  explicit Init_WeighPidData_tipoff_pitch_cal_offset(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_hyd_oil_temp_enabled tipoff_pitch_cal_offset(::cpm_common_interfaces::msg::WeighPidData::_tipoff_pitch_cal_offset_type arg)
  {
    msg_.tipoff_pitch_cal_offset = std::move(arg);
    return Init_WeighPidData_hyd_oil_temp_enabled(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_machine_side_slope
{
public:
  explicit Init_WeighPidData_machine_side_slope(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_tipoff_pitch_cal_offset machine_side_slope(::cpm_common_interfaces::msg::WeighPidData::_machine_side_slope_type arg)
  {
    msg_.machine_side_slope = std::move(arg);
    return Init_WeighPidData_tipoff_pitch_cal_offset(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_machine_roll
{
public:
  explicit Init_WeighPidData_machine_roll(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_machine_side_slope machine_roll(::cpm_common_interfaces::msg::WeighPidData::_machine_roll_type arg)
  {
    msg_.machine_roll = std::move(arg);
    return Init_WeighPidData_machine_side_slope(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_machine_rear_side_slope
{
public:
  explicit Init_WeighPidData_machine_rear_side_slope(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_machine_roll machine_rear_side_slope(::cpm_common_interfaces::msg::WeighPidData::_machine_rear_side_slope_type arg)
  {
    msg_.machine_rear_side_slope = std::move(arg);
    return Init_WeighPidData_machine_roll(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_machine_rear_roll
{
public:
  explicit Init_WeighPidData_machine_rear_roll(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_machine_rear_side_slope machine_rear_roll(::cpm_common_interfaces::msg::WeighPidData::_machine_rear_roll_type arg)
  {
    msg_.machine_rear_roll = std::move(arg);
    return Init_WeighPidData_machine_rear_side_slope(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_machine_slope
{
public:
  explicit Init_WeighPidData_machine_slope(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_machine_rear_roll machine_slope(::cpm_common_interfaces::msg::WeighPidData::_machine_slope_type arg)
  {
    msg_.machine_slope = std::move(arg);
    return Init_WeighPidData_machine_rear_roll(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_machine_pitch
{
public:
  explicit Init_WeighPidData_machine_pitch(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_machine_slope machine_pitch(::cpm_common_interfaces::msg::WeighPidData::_machine_pitch_type arg)
  {
    msg_.machine_pitch = std::move(arg);
    return Init_WeighPidData_machine_slope(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_machine_rear_vertical_acceleration
{
public:
  explicit Init_WeighPidData_machine_rear_vertical_acceleration(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_machine_pitch machine_rear_vertical_acceleration(::cpm_common_interfaces::msg::WeighPidData::_machine_rear_vertical_acceleration_type arg)
  {
    msg_.machine_rear_vertical_acceleration = std::move(arg);
    return Init_WeighPidData_machine_pitch(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_machine_rear_longitudinal_acceleration
{
public:
  explicit Init_WeighPidData_machine_rear_longitudinal_acceleration(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_machine_rear_vertical_acceleration machine_rear_longitudinal_acceleration(::cpm_common_interfaces::msg::WeighPidData::_machine_rear_longitudinal_acceleration_type arg)
  {
    msg_.machine_rear_longitudinal_acceleration = std::move(arg);
    return Init_WeighPidData_machine_rear_vertical_acceleration(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_machine_rear_lateral_acceleration
{
public:
  explicit Init_WeighPidData_machine_rear_lateral_acceleration(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_machine_rear_longitudinal_acceleration machine_rear_lateral_acceleration(::cpm_common_interfaces::msg::WeighPidData::_machine_rear_lateral_acceleration_type arg)
  {
    msg_.machine_rear_lateral_acceleration = std::move(arg);
    return Init_WeighPidData_machine_rear_longitudinal_acceleration(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_qr_lift_cyl_vel_max_mm_sec
{
public:
  explicit Init_WeighPidData_qr_lift_cyl_vel_max_mm_sec(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_machine_rear_lateral_acceleration qr_lift_cyl_vel_max_mm_sec(::cpm_common_interfaces::msg::WeighPidData::_qr_lift_cyl_vel_max_mm_sec_type arg)
  {
    msg_.qr_lift_cyl_vel_max_mm_sec = std::move(arg);
    return Init_WeighPidData_machine_rear_lateral_acceleration(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_qr_lift_cyl_vel_min_mm_sec
{
public:
  explicit Init_WeighPidData_qr_lift_cyl_vel_min_mm_sec(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_qr_lift_cyl_vel_max_mm_sec qr_lift_cyl_vel_min_mm_sec(::cpm_common_interfaces::msg::WeighPidData::_qr_lift_cyl_vel_min_mm_sec_type arg)
  {
    msg_.qr_lift_cyl_vel_min_mm_sec = std::move(arg);
    return Init_WeighPidData_qr_lift_cyl_vel_max_mm_sec(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_qr_hyd_oil_temp_min_c
{
public:
  explicit Init_WeighPidData_qr_hyd_oil_temp_min_c(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_qr_lift_cyl_vel_min_mm_sec qr_hyd_oil_temp_min_c(::cpm_common_interfaces::msg::WeighPidData::_qr_hyd_oil_temp_min_c_type arg)
  {
    msg_.qr_hyd_oil_temp_min_c = std::move(arg);
    return Init_WeighPidData_qr_lift_cyl_vel_min_mm_sec(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_bkt_payload_data
{
public:
  explicit Init_WeighPidData_bkt_payload_data(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_qr_hyd_oil_temp_min_c bkt_payload_data(::cpm_common_interfaces::msg::WeighPidData::_bkt_payload_data_type arg)
  {
    msg_.bkt_payload_data = std::move(arg);
    return Init_WeighPidData_qr_hyd_oil_temp_min_c(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_prod_measure_weigh_status
{
public:
  explicit Init_WeighPidData_prod_measure_weigh_status(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_bkt_payload_data prod_measure_weigh_status(::cpm_common_interfaces::msg::WeighPidData::_prod_measure_weigh_status_type arg)
  {
    msg_.prod_measure_weigh_status = std::move(arg);
    return Init_WeighPidData_bkt_payload_data(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_last_pload_wt
{
public:
  explicit Init_WeighPidData_last_pload_wt(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_prod_measure_weigh_status last_pload_wt(::cpm_common_interfaces::msg::WeighPidData::_last_pload_wt_type arg)
  {
    msg_.last_pload_wt = std::move(arg);
    return Init_WeighPidData_prod_measure_weigh_status(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_pload_sys_cal_wt_entry_req_stat
{
public:
  explicit Init_WeighPidData_pload_sys_cal_wt_entry_req_stat(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_last_pload_wt pload_sys_cal_wt_entry_req_stat(::cpm_common_interfaces::msg::WeighPidData::_pload_sys_cal_wt_entry_req_stat_type arg)
  {
    msg_.pload_sys_cal_wt_entry_req_stat = std::move(arg);
    return Init_WeighPidData_last_pload_wt(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_pload_sys_zero_req_stat
{
public:
  explicit Init_WeighPidData_pload_sys_zero_req_stat(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_pload_sys_cal_wt_entry_req_stat pload_sys_zero_req_stat(::cpm_common_interfaces::msg::WeighPidData::_pload_sys_zero_req_stat_type arg)
  {
    msg_.pload_sys_zero_req_stat = std::move(arg);
    return Init_WeighPidData_pload_sys_cal_wt_entry_req_stat(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_loader_bkt_pload_tgt_wt_per
{
public:
  explicit Init_WeighPidData_loader_bkt_pload_tgt_wt_per(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_pload_sys_zero_req_stat loader_bkt_pload_tgt_wt_per(::cpm_common_interfaces::msg::WeighPidData::_loader_bkt_pload_tgt_wt_per_type arg)
  {
    msg_.loader_bkt_pload_tgt_wt_per = std::move(arg);
    return Init_WeighPidData_pload_sys_zero_req_stat(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_loader_bkt_pload_tgt_wt
{
public:
  explicit Init_WeighPidData_loader_bkt_pload_tgt_wt(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_loader_bkt_pload_tgt_wt_per loader_bkt_pload_tgt_wt(::cpm_common_interfaces::msg::WeighPidData::_loader_bkt_pload_tgt_wt_type arg)
  {
    msg_.loader_bkt_pload_tgt_wt = std::move(arg);
    return Init_WeighPidData_loader_bkt_pload_tgt_wt_per(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_link_sensor_cal_lim
{
public:
  explicit Init_WeighPidData_link_sensor_cal_lim(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_loader_bkt_pload_tgt_wt link_sensor_cal_lim(::cpm_common_interfaces::msg::WeighPidData::_link_sensor_cal_lim_type arg)
  {
    msg_.link_sensor_cal_lim = std::move(arg);
    return Init_WeighPidData_loader_bkt_pload_tgt_wt(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_prod_measure_sensor_status
{
public:
  explicit Init_WeighPidData_prod_measure_sensor_status(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_link_sensor_cal_lim prod_measure_sensor_status(::cpm_common_interfaces::msg::WeighPidData::_prod_measure_sensor_status_type arg)
  {
    msg_.prod_measure_sensor_status = std::move(arg);
    return Init_WeighPidData_link_sensor_cal_lim(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_overload_warning_enabled
{
public:
  explicit Init_WeighPidData_overload_warning_enabled(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_prod_measure_sensor_status overload_warning_enabled(::cpm_common_interfaces::msg::WeighPidData::_overload_warning_enabled_type arg)
  {
    msg_.overload_warning_enabled = std::move(arg);
    return Init_WeighPidData_prod_measure_sensor_status(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_ldr_payload_stat
{
public:
  explicit Init_WeighPidData_ldr_payload_stat(::cpm_common_interfaces::msg::WeighPidData & msg)
  : msg_(msg)
  {}
  Init_WeighPidData_overload_warning_enabled ldr_payload_stat(::cpm_common_interfaces::msg::WeighPidData::_ldr_payload_stat_type arg)
  {
    msg_.ldr_payload_stat = std::move(arg);
    return Init_WeighPidData_overload_warning_enabled(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

class Init_WeighPidData_pload_sys_zero_stat
{
public:
  Init_WeighPidData_pload_sys_zero_stat()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WeighPidData_ldr_payload_stat pload_sys_zero_stat(::cpm_common_interfaces::msg::WeighPidData::_pload_sys_zero_stat_type arg)
  {
    msg_.pload_sys_zero_stat = std::move(arg);
    return Init_WeighPidData_ldr_payload_stat(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighPidData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::WeighPidData>()
{
  return cpm_common_interfaces::msg::builder::Init_WeighPidData_pload_sys_zero_stat();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__BUILDER_HPP_
