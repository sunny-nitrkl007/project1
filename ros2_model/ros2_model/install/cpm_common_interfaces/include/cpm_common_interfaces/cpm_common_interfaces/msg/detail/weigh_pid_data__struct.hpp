// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/WeighPidData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/weigh_pid_data.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'prod_measure_sensor_status'
#include "cpm_common_interfaces/msg/detail/prod_measure_sensor_status__struct.hpp"
// Member 'link_sensor_cal_lim'
#include "cpm_common_interfaces/msg/detail/link_sensor_cal_lim__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__WeighPidData __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__WeighPidData __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WeighPidData_
{
  using Type = WeighPidData_<ContainerAllocator>;

  explicit WeighPidData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : prod_measure_sensor_status(_init),
    link_sensor_cal_lim(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pload_sys_zero_stat = 0;
      this->ldr_payload_stat = 0;
      this->overload_warning_enabled = false;
      this->loader_bkt_pload_tgt_wt = 0.0f;
      this->loader_bkt_pload_tgt_wt_per = 0.0f;
      this->pload_sys_zero_req_stat = 0;
      this->pload_sys_cal_wt_entry_req_stat = 0;
      this->last_pload_wt = 0.0f;
      this->prod_measure_weigh_status = 0;
      this->bkt_payload_data = 0;
      this->qr_hyd_oil_temp_min_c = 0;
      this->qr_lift_cyl_vel_min_mm_sec = 0;
      this->qr_lift_cyl_vel_max_mm_sec = 0;
      this->machine_rear_lateral_acceleration = 0;
      this->machine_rear_longitudinal_acceleration = 0;
      this->machine_rear_vertical_acceleration = 0;
      this->machine_pitch = 0;
      this->machine_slope = 0;
      this->machine_rear_roll = 0;
      this->machine_rear_side_slope = 0;
      this->machine_roll = 0;
      this->machine_side_slope = 0;
      this->tipoff_pitch_cal_offset = 0.0f;
      this->hyd_oil_temp_enabled = false;
      this->audible_weight_enabled = false;
      this->audible_weight_command = 0;
    }
  }

  explicit WeighPidData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : prod_measure_sensor_status(_alloc, _init),
    link_sensor_cal_lim(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pload_sys_zero_stat = 0;
      this->ldr_payload_stat = 0;
      this->overload_warning_enabled = false;
      this->loader_bkt_pload_tgt_wt = 0.0f;
      this->loader_bkt_pload_tgt_wt_per = 0.0f;
      this->pload_sys_zero_req_stat = 0;
      this->pload_sys_cal_wt_entry_req_stat = 0;
      this->last_pload_wt = 0.0f;
      this->prod_measure_weigh_status = 0;
      this->bkt_payload_data = 0;
      this->qr_hyd_oil_temp_min_c = 0;
      this->qr_lift_cyl_vel_min_mm_sec = 0;
      this->qr_lift_cyl_vel_max_mm_sec = 0;
      this->machine_rear_lateral_acceleration = 0;
      this->machine_rear_longitudinal_acceleration = 0;
      this->machine_rear_vertical_acceleration = 0;
      this->machine_pitch = 0;
      this->machine_slope = 0;
      this->machine_rear_roll = 0;
      this->machine_rear_side_slope = 0;
      this->machine_roll = 0;
      this->machine_side_slope = 0;
      this->tipoff_pitch_cal_offset = 0.0f;
      this->hyd_oil_temp_enabled = false;
      this->audible_weight_enabled = false;
      this->audible_weight_command = 0;
    }
  }

  // field types and members
  using _pload_sys_zero_stat_type =
    uint16_t;
  _pload_sys_zero_stat_type pload_sys_zero_stat;
  using _ldr_payload_stat_type =
    uint16_t;
  _ldr_payload_stat_type ldr_payload_stat;
  using _overload_warning_enabled_type =
    bool;
  _overload_warning_enabled_type overload_warning_enabled;
  using _prod_measure_sensor_status_type =
    cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator>;
  _prod_measure_sensor_status_type prod_measure_sensor_status;
  using _link_sensor_cal_lim_type =
    cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator>;
  _link_sensor_cal_lim_type link_sensor_cal_lim;
  using _loader_bkt_pload_tgt_wt_type =
    float;
  _loader_bkt_pload_tgt_wt_type loader_bkt_pload_tgt_wt;
  using _loader_bkt_pload_tgt_wt_per_type =
    float;
  _loader_bkt_pload_tgt_wt_per_type loader_bkt_pload_tgt_wt_per;
  using _pload_sys_zero_req_stat_type =
    uint16_t;
  _pload_sys_zero_req_stat_type pload_sys_zero_req_stat;
  using _pload_sys_cal_wt_entry_req_stat_type =
    uint16_t;
  _pload_sys_cal_wt_entry_req_stat_type pload_sys_cal_wt_entry_req_stat;
  using _last_pload_wt_type =
    float;
  _last_pload_wt_type last_pload_wt;
  using _prod_measure_weigh_status_type =
    uint16_t;
  _prod_measure_weigh_status_type prod_measure_weigh_status;
  using _bkt_payload_data_type =
    uint8_t;
  _bkt_payload_data_type bkt_payload_data;
  using _qr_hyd_oil_temp_min_c_type =
    int16_t;
  _qr_hyd_oil_temp_min_c_type qr_hyd_oil_temp_min_c;
  using _qr_lift_cyl_vel_min_mm_sec_type =
    int16_t;
  _qr_lift_cyl_vel_min_mm_sec_type qr_lift_cyl_vel_min_mm_sec;
  using _qr_lift_cyl_vel_max_mm_sec_type =
    int16_t;
  _qr_lift_cyl_vel_max_mm_sec_type qr_lift_cyl_vel_max_mm_sec;
  using _machine_rear_lateral_acceleration_type =
    int16_t;
  _machine_rear_lateral_acceleration_type machine_rear_lateral_acceleration;
  using _machine_rear_longitudinal_acceleration_type =
    int16_t;
  _machine_rear_longitudinal_acceleration_type machine_rear_longitudinal_acceleration;
  using _machine_rear_vertical_acceleration_type =
    int16_t;
  _machine_rear_vertical_acceleration_type machine_rear_vertical_acceleration;
  using _machine_pitch_type =
    int16_t;
  _machine_pitch_type machine_pitch;
  using _machine_slope_type =
    int16_t;
  _machine_slope_type machine_slope;
  using _machine_rear_roll_type =
    int16_t;
  _machine_rear_roll_type machine_rear_roll;
  using _machine_rear_side_slope_type =
    int16_t;
  _machine_rear_side_slope_type machine_rear_side_slope;
  using _machine_roll_type =
    int16_t;
  _machine_roll_type machine_roll;
  using _machine_side_slope_type =
    int16_t;
  _machine_side_slope_type machine_side_slope;
  using _tipoff_pitch_cal_offset_type =
    float;
  _tipoff_pitch_cal_offset_type tipoff_pitch_cal_offset;
  using _hyd_oil_temp_enabled_type =
    bool;
  _hyd_oil_temp_enabled_type hyd_oil_temp_enabled;
  using _audible_weight_enabled_type =
    bool;
  _audible_weight_enabled_type audible_weight_enabled;
  using _audible_weight_command_type =
    uint16_t;
  _audible_weight_command_type audible_weight_command;

  // setters for named parameter idiom
  Type & set__pload_sys_zero_stat(
    const uint16_t & _arg)
  {
    this->pload_sys_zero_stat = _arg;
    return *this;
  }
  Type & set__ldr_payload_stat(
    const uint16_t & _arg)
  {
    this->ldr_payload_stat = _arg;
    return *this;
  }
  Type & set__overload_warning_enabled(
    const bool & _arg)
  {
    this->overload_warning_enabled = _arg;
    return *this;
  }
  Type & set__prod_measure_sensor_status(
    const cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator> & _arg)
  {
    this->prod_measure_sensor_status = _arg;
    return *this;
  }
  Type & set__link_sensor_cal_lim(
    const cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator> & _arg)
  {
    this->link_sensor_cal_lim = _arg;
    return *this;
  }
  Type & set__loader_bkt_pload_tgt_wt(
    const float & _arg)
  {
    this->loader_bkt_pload_tgt_wt = _arg;
    return *this;
  }
  Type & set__loader_bkt_pload_tgt_wt_per(
    const float & _arg)
  {
    this->loader_bkt_pload_tgt_wt_per = _arg;
    return *this;
  }
  Type & set__pload_sys_zero_req_stat(
    const uint16_t & _arg)
  {
    this->pload_sys_zero_req_stat = _arg;
    return *this;
  }
  Type & set__pload_sys_cal_wt_entry_req_stat(
    const uint16_t & _arg)
  {
    this->pload_sys_cal_wt_entry_req_stat = _arg;
    return *this;
  }
  Type & set__last_pload_wt(
    const float & _arg)
  {
    this->last_pload_wt = _arg;
    return *this;
  }
  Type & set__prod_measure_weigh_status(
    const uint16_t & _arg)
  {
    this->prod_measure_weigh_status = _arg;
    return *this;
  }
  Type & set__bkt_payload_data(
    const uint8_t & _arg)
  {
    this->bkt_payload_data = _arg;
    return *this;
  }
  Type & set__qr_hyd_oil_temp_min_c(
    const int16_t & _arg)
  {
    this->qr_hyd_oil_temp_min_c = _arg;
    return *this;
  }
  Type & set__qr_lift_cyl_vel_min_mm_sec(
    const int16_t & _arg)
  {
    this->qr_lift_cyl_vel_min_mm_sec = _arg;
    return *this;
  }
  Type & set__qr_lift_cyl_vel_max_mm_sec(
    const int16_t & _arg)
  {
    this->qr_lift_cyl_vel_max_mm_sec = _arg;
    return *this;
  }
  Type & set__machine_rear_lateral_acceleration(
    const int16_t & _arg)
  {
    this->machine_rear_lateral_acceleration = _arg;
    return *this;
  }
  Type & set__machine_rear_longitudinal_acceleration(
    const int16_t & _arg)
  {
    this->machine_rear_longitudinal_acceleration = _arg;
    return *this;
  }
  Type & set__machine_rear_vertical_acceleration(
    const int16_t & _arg)
  {
    this->machine_rear_vertical_acceleration = _arg;
    return *this;
  }
  Type & set__machine_pitch(
    const int16_t & _arg)
  {
    this->machine_pitch = _arg;
    return *this;
  }
  Type & set__machine_slope(
    const int16_t & _arg)
  {
    this->machine_slope = _arg;
    return *this;
  }
  Type & set__machine_rear_roll(
    const int16_t & _arg)
  {
    this->machine_rear_roll = _arg;
    return *this;
  }
  Type & set__machine_rear_side_slope(
    const int16_t & _arg)
  {
    this->machine_rear_side_slope = _arg;
    return *this;
  }
  Type & set__machine_roll(
    const int16_t & _arg)
  {
    this->machine_roll = _arg;
    return *this;
  }
  Type & set__machine_side_slope(
    const int16_t & _arg)
  {
    this->machine_side_slope = _arg;
    return *this;
  }
  Type & set__tipoff_pitch_cal_offset(
    const float & _arg)
  {
    this->tipoff_pitch_cal_offset = _arg;
    return *this;
  }
  Type & set__hyd_oil_temp_enabled(
    const bool & _arg)
  {
    this->hyd_oil_temp_enabled = _arg;
    return *this;
  }
  Type & set__audible_weight_enabled(
    const bool & _arg)
  {
    this->audible_weight_enabled = _arg;
    return *this;
  }
  Type & set__audible_weight_command(
    const uint16_t & _arg)
  {
    this->audible_weight_command = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t ZERO_STAT_ZEROED =
    916u;
  static constexpr uint16_t ZERO_STAT_NOT_ZEROED =
    917u;
  static constexpr uint16_t CAL_WT_ENTRY_REQUIRED =
    26u;
  static constexpr uint16_t CAL_WT_ENTRY_NOT_REQUIRED =
    27u;
  static constexpr uint16_t WEIGH_STATUS_BIT_LOWER_STALL =
    7u;
  static constexpr uint16_t WEIGH_STATUS_BIT_RAISE_STALL =
    8u;
  static constexpr uint16_t WEIGH_STATUS_BIT_INSUFFICIENT_DATA =
    9u;
  static constexpr uint16_t WEIGH_STATUS_BIT_REWEIGH_PRESSURE_CHANGING =
    10u;
  static constexpr uint16_t WEIGH_STATUS_BIT_REWEIGH_INCONSISTENT =
    11u;
  static constexpr uint16_t WEIGH_STATUS_BIT_REWEIGH_SPEED_CHANGING =
    12u;
  static constexpr uint16_t WEIGH_STATUS_BIT_REWEIGH_NOT_RACKED_EXCESSIVE_PITCH =
    13u;
  static constexpr uint16_t WEIGH_STATUS_BIT_REWEIGH_STOPPED_IN_RANGE =
    14u;
  static constexpr uint16_t WEIGH_STATUS_BIT_REWEIGH_LIFT_TOO_SLOW =
    15u;
  static constexpr uint8_t BKT_PAYLOAD_NOT_AVAILABLE =
    0u;
  static constexpr uint8_t BKT_PAYLOAD_AVAILABLE =
    1u;
  static constexpr uint8_t BKT_PAYLOAD_STORED =
    2u;
  static constexpr uint8_t BKT_PAYLOAD_NOT_INSTALLED =
    244u;
  static constexpr uint16_t TONE_NONE =
    0u;
  static constexpr uint16_t TONE_CONFIRMATION =
    2u;
  static constexpr uint16_t TONE_ATTENTION =
    6u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__WeighPidData
    std::shared_ptr<cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__WeighPidData
    std::shared_ptr<cpm_common_interfaces::msg::WeighPidData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WeighPidData_ & other) const
  {
    if (this->pload_sys_zero_stat != other.pload_sys_zero_stat) {
      return false;
    }
    if (this->ldr_payload_stat != other.ldr_payload_stat) {
      return false;
    }
    if (this->overload_warning_enabled != other.overload_warning_enabled) {
      return false;
    }
    if (this->prod_measure_sensor_status != other.prod_measure_sensor_status) {
      return false;
    }
    if (this->link_sensor_cal_lim != other.link_sensor_cal_lim) {
      return false;
    }
    if (this->loader_bkt_pload_tgt_wt != other.loader_bkt_pload_tgt_wt) {
      return false;
    }
    if (this->loader_bkt_pload_tgt_wt_per != other.loader_bkt_pload_tgt_wt_per) {
      return false;
    }
    if (this->pload_sys_zero_req_stat != other.pload_sys_zero_req_stat) {
      return false;
    }
    if (this->pload_sys_cal_wt_entry_req_stat != other.pload_sys_cal_wt_entry_req_stat) {
      return false;
    }
    if (this->last_pload_wt != other.last_pload_wt) {
      return false;
    }
    if (this->prod_measure_weigh_status != other.prod_measure_weigh_status) {
      return false;
    }
    if (this->bkt_payload_data != other.bkt_payload_data) {
      return false;
    }
    if (this->qr_hyd_oil_temp_min_c != other.qr_hyd_oil_temp_min_c) {
      return false;
    }
    if (this->qr_lift_cyl_vel_min_mm_sec != other.qr_lift_cyl_vel_min_mm_sec) {
      return false;
    }
    if (this->qr_lift_cyl_vel_max_mm_sec != other.qr_lift_cyl_vel_max_mm_sec) {
      return false;
    }
    if (this->machine_rear_lateral_acceleration != other.machine_rear_lateral_acceleration) {
      return false;
    }
    if (this->machine_rear_longitudinal_acceleration != other.machine_rear_longitudinal_acceleration) {
      return false;
    }
    if (this->machine_rear_vertical_acceleration != other.machine_rear_vertical_acceleration) {
      return false;
    }
    if (this->machine_pitch != other.machine_pitch) {
      return false;
    }
    if (this->machine_slope != other.machine_slope) {
      return false;
    }
    if (this->machine_rear_roll != other.machine_rear_roll) {
      return false;
    }
    if (this->machine_rear_side_slope != other.machine_rear_side_slope) {
      return false;
    }
    if (this->machine_roll != other.machine_roll) {
      return false;
    }
    if (this->machine_side_slope != other.machine_side_slope) {
      return false;
    }
    if (this->tipoff_pitch_cal_offset != other.tipoff_pitch_cal_offset) {
      return false;
    }
    if (this->hyd_oil_temp_enabled != other.hyd_oil_temp_enabled) {
      return false;
    }
    if (this->audible_weight_enabled != other.audible_weight_enabled) {
      return false;
    }
    if (this->audible_weight_command != other.audible_weight_command) {
      return false;
    }
    return true;
  }
  bool operator!=(const WeighPidData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WeighPidData_

// alias to use template instance with default allocator
using WeighPidData =
  cpm_common_interfaces::msg::WeighPidData_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::ZERO_STAT_ZEROED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::ZERO_STAT_NOT_ZEROED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::CAL_WT_ENTRY_REQUIRED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::CAL_WT_ENTRY_NOT_REQUIRED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::WEIGH_STATUS_BIT_LOWER_STALL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::WEIGH_STATUS_BIT_RAISE_STALL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::WEIGH_STATUS_BIT_INSUFFICIENT_DATA;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::WEIGH_STATUS_BIT_REWEIGH_PRESSURE_CHANGING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::WEIGH_STATUS_BIT_REWEIGH_INCONSISTENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::WEIGH_STATUS_BIT_REWEIGH_SPEED_CHANGING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::WEIGH_STATUS_BIT_REWEIGH_NOT_RACKED_EXCESSIVE_PITCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::WEIGH_STATUS_BIT_REWEIGH_STOPPED_IN_RANGE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::WEIGH_STATUS_BIT_REWEIGH_LIFT_TOO_SLOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighPidData_<ContainerAllocator>::BKT_PAYLOAD_NOT_AVAILABLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighPidData_<ContainerAllocator>::BKT_PAYLOAD_AVAILABLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighPidData_<ContainerAllocator>::BKT_PAYLOAD_STORED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighPidData_<ContainerAllocator>::BKT_PAYLOAD_NOT_INSTALLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::TONE_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::TONE_CONFIRMATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t WeighPidData_<ContainerAllocator>::TONE_ATTENTION;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__STRUCT_HPP_
