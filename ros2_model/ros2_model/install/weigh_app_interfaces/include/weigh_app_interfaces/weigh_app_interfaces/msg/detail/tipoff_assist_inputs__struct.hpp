// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/TipoffAssistInputs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_assist_inputs.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__TipoffAssistInputs __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__TipoffAssistInputs __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TipoffAssistInputs_
{
  using Type = TipoffAssistInputs_<ContainerAllocator>;

  explicit TipoffAssistInputs_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->input_status = 0;
      this->invalidate_outputs = false;
      this->lift_valve_cmd = 0.0f;
      this->tilt_valve_cmd = 0.0f;
      this->tilt_extension = 0.0f;
      this->lift_angle = 0.0f;
      this->lift_he_pressure = 0.0f;
      this->lift_re_pressure = 0.0f;
      this->tilt_he_pressure = 0.0f;
      this->tilt_re_pressure = 0.0f;
      this->eef_imu_accel_x = 0.0f;
      this->eef_imu_accel_y = 0.0f;
      this->eef_imu_accel_z = 0.0f;
      this->steering_angle = 0.0f;
      this->tool_mass = 0.0f;
      this->truck_target_wt = 0.0f;
      this->truck_start_weight = 0.0f;
      this->bucket_current_weight_accuracy = 0;
      this->bucket_current_weight = 0.0f;
      this->tipoff_mode = 0;
      this->zero_offset = 0.0f;
      this->simple_cal_factor = 0.0f;
      this->mach_pitch_cal_offset = 0.0f;
      this->unlatch_trigger = false;
      this->bucket_angle = 0.0f;
      this->anchor_zero_offset = 0.0f;
      this->anchor_factor = 0.0f;
      this->pass_count = 0;
      this->lift_norm_angle = 0.0f;
      this->lift_norm_length = 0.0f;
      this->tilt_norm_angle = 0.0f;
      this->tilt_norm_length = 0.0f;
      this->friction_mu = 0.0f;
      this->friction_offset = 0.0f;
    }
  }

  explicit TipoffAssistInputs_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->input_status = 0;
      this->invalidate_outputs = false;
      this->lift_valve_cmd = 0.0f;
      this->tilt_valve_cmd = 0.0f;
      this->tilt_extension = 0.0f;
      this->lift_angle = 0.0f;
      this->lift_he_pressure = 0.0f;
      this->lift_re_pressure = 0.0f;
      this->tilt_he_pressure = 0.0f;
      this->tilt_re_pressure = 0.0f;
      this->eef_imu_accel_x = 0.0f;
      this->eef_imu_accel_y = 0.0f;
      this->eef_imu_accel_z = 0.0f;
      this->steering_angle = 0.0f;
      this->tool_mass = 0.0f;
      this->truck_target_wt = 0.0f;
      this->truck_start_weight = 0.0f;
      this->bucket_current_weight_accuracy = 0;
      this->bucket_current_weight = 0.0f;
      this->tipoff_mode = 0;
      this->zero_offset = 0.0f;
      this->simple_cal_factor = 0.0f;
      this->mach_pitch_cal_offset = 0.0f;
      this->unlatch_trigger = false;
      this->bucket_angle = 0.0f;
      this->anchor_zero_offset = 0.0f;
      this->anchor_factor = 0.0f;
      this->pass_count = 0;
      this->lift_norm_angle = 0.0f;
      this->lift_norm_length = 0.0f;
      this->tilt_norm_angle = 0.0f;
      this->tilt_norm_length = 0.0f;
      this->friction_mu = 0.0f;
      this->friction_offset = 0.0f;
    }
  }

  // field types and members
  using _input_status_type =
    uint16_t;
  _input_status_type input_status;
  using _invalidate_outputs_type =
    bool;
  _invalidate_outputs_type invalidate_outputs;
  using _lift_valve_cmd_type =
    float;
  _lift_valve_cmd_type lift_valve_cmd;
  using _tilt_valve_cmd_type =
    float;
  _tilt_valve_cmd_type tilt_valve_cmd;
  using _tilt_extension_type =
    float;
  _tilt_extension_type tilt_extension;
  using _lift_angle_type =
    float;
  _lift_angle_type lift_angle;
  using _lift_he_pressure_type =
    float;
  _lift_he_pressure_type lift_he_pressure;
  using _lift_re_pressure_type =
    float;
  _lift_re_pressure_type lift_re_pressure;
  using _tilt_he_pressure_type =
    float;
  _tilt_he_pressure_type tilt_he_pressure;
  using _tilt_re_pressure_type =
    float;
  _tilt_re_pressure_type tilt_re_pressure;
  using _eef_imu_accel_x_type =
    float;
  _eef_imu_accel_x_type eef_imu_accel_x;
  using _eef_imu_accel_y_type =
    float;
  _eef_imu_accel_y_type eef_imu_accel_y;
  using _eef_imu_accel_z_type =
    float;
  _eef_imu_accel_z_type eef_imu_accel_z;
  using _steering_angle_type =
    float;
  _steering_angle_type steering_angle;
  using _tool_mass_type =
    float;
  _tool_mass_type tool_mass;
  using _truck_target_wt_type =
    float;
  _truck_target_wt_type truck_target_wt;
  using _truck_start_weight_type =
    float;
  _truck_start_weight_type truck_start_weight;
  using _bucket_current_weight_accuracy_type =
    uint8_t;
  _bucket_current_weight_accuracy_type bucket_current_weight_accuracy;
  using _bucket_current_weight_type =
    float;
  _bucket_current_weight_type bucket_current_weight;
  using _tipoff_mode_type =
    uint8_t;
  _tipoff_mode_type tipoff_mode;
  using _zero_offset_type =
    float;
  _zero_offset_type zero_offset;
  using _simple_cal_factor_type =
    float;
  _simple_cal_factor_type simple_cal_factor;
  using _mach_pitch_cal_offset_type =
    float;
  _mach_pitch_cal_offset_type mach_pitch_cal_offset;
  using _unlatch_trigger_type =
    bool;
  _unlatch_trigger_type unlatch_trigger;
  using _bucket_angle_type =
    float;
  _bucket_angle_type bucket_angle;
  using _anchor_zero_offset_type =
    float;
  _anchor_zero_offset_type anchor_zero_offset;
  using _anchor_factor_type =
    float;
  _anchor_factor_type anchor_factor;
  using _pass_count_type =
    uint16_t;
  _pass_count_type pass_count;
  using _lift_norm_angle_type =
    float;
  _lift_norm_angle_type lift_norm_angle;
  using _lift_norm_length_type =
    float;
  _lift_norm_length_type lift_norm_length;
  using _tilt_norm_angle_type =
    float;
  _tilt_norm_angle_type tilt_norm_angle;
  using _tilt_norm_length_type =
    float;
  _tilt_norm_length_type tilt_norm_length;
  using _friction_mu_type =
    float;
  _friction_mu_type friction_mu;
  using _friction_offset_type =
    float;
  _friction_offset_type friction_offset;

  // setters for named parameter idiom
  Type & set__input_status(
    const uint16_t & _arg)
  {
    this->input_status = _arg;
    return *this;
  }
  Type & set__invalidate_outputs(
    const bool & _arg)
  {
    this->invalidate_outputs = _arg;
    return *this;
  }
  Type & set__lift_valve_cmd(
    const float & _arg)
  {
    this->lift_valve_cmd = _arg;
    return *this;
  }
  Type & set__tilt_valve_cmd(
    const float & _arg)
  {
    this->tilt_valve_cmd = _arg;
    return *this;
  }
  Type & set__tilt_extension(
    const float & _arg)
  {
    this->tilt_extension = _arg;
    return *this;
  }
  Type & set__lift_angle(
    const float & _arg)
  {
    this->lift_angle = _arg;
    return *this;
  }
  Type & set__lift_he_pressure(
    const float & _arg)
  {
    this->lift_he_pressure = _arg;
    return *this;
  }
  Type & set__lift_re_pressure(
    const float & _arg)
  {
    this->lift_re_pressure = _arg;
    return *this;
  }
  Type & set__tilt_he_pressure(
    const float & _arg)
  {
    this->tilt_he_pressure = _arg;
    return *this;
  }
  Type & set__tilt_re_pressure(
    const float & _arg)
  {
    this->tilt_re_pressure = _arg;
    return *this;
  }
  Type & set__eef_imu_accel_x(
    const float & _arg)
  {
    this->eef_imu_accel_x = _arg;
    return *this;
  }
  Type & set__eef_imu_accel_y(
    const float & _arg)
  {
    this->eef_imu_accel_y = _arg;
    return *this;
  }
  Type & set__eef_imu_accel_z(
    const float & _arg)
  {
    this->eef_imu_accel_z = _arg;
    return *this;
  }
  Type & set__steering_angle(
    const float & _arg)
  {
    this->steering_angle = _arg;
    return *this;
  }
  Type & set__tool_mass(
    const float & _arg)
  {
    this->tool_mass = _arg;
    return *this;
  }
  Type & set__truck_target_wt(
    const float & _arg)
  {
    this->truck_target_wt = _arg;
    return *this;
  }
  Type & set__truck_start_weight(
    const float & _arg)
  {
    this->truck_start_weight = _arg;
    return *this;
  }
  Type & set__bucket_current_weight_accuracy(
    const uint8_t & _arg)
  {
    this->bucket_current_weight_accuracy = _arg;
    return *this;
  }
  Type & set__bucket_current_weight(
    const float & _arg)
  {
    this->bucket_current_weight = _arg;
    return *this;
  }
  Type & set__tipoff_mode(
    const uint8_t & _arg)
  {
    this->tipoff_mode = _arg;
    return *this;
  }
  Type & set__zero_offset(
    const float & _arg)
  {
    this->zero_offset = _arg;
    return *this;
  }
  Type & set__simple_cal_factor(
    const float & _arg)
  {
    this->simple_cal_factor = _arg;
    return *this;
  }
  Type & set__mach_pitch_cal_offset(
    const float & _arg)
  {
    this->mach_pitch_cal_offset = _arg;
    return *this;
  }
  Type & set__unlatch_trigger(
    const bool & _arg)
  {
    this->unlatch_trigger = _arg;
    return *this;
  }
  Type & set__bucket_angle(
    const float & _arg)
  {
    this->bucket_angle = _arg;
    return *this;
  }
  Type & set__anchor_zero_offset(
    const float & _arg)
  {
    this->anchor_zero_offset = _arg;
    return *this;
  }
  Type & set__anchor_factor(
    const float & _arg)
  {
    this->anchor_factor = _arg;
    return *this;
  }
  Type & set__pass_count(
    const uint16_t & _arg)
  {
    this->pass_count = _arg;
    return *this;
  }
  Type & set__lift_norm_angle(
    const float & _arg)
  {
    this->lift_norm_angle = _arg;
    return *this;
  }
  Type & set__lift_norm_length(
    const float & _arg)
  {
    this->lift_norm_length = _arg;
    return *this;
  }
  Type & set__tilt_norm_angle(
    const float & _arg)
  {
    this->tilt_norm_angle = _arg;
    return *this;
  }
  Type & set__tilt_norm_length(
    const float & _arg)
  {
    this->tilt_norm_length = _arg;
    return *this;
  }
  Type & set__friction_mu(
    const float & _arg)
  {
    this->friction_mu = _arg;
    return *this;
  }
  Type & set__friction_offset(
    const float & _arg)
  {
    this->friction_offset = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__TipoffAssistInputs
    std::shared_ptr<weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__TipoffAssistInputs
    std::shared_ptr<weigh_app_interfaces::msg::TipoffAssistInputs_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TipoffAssistInputs_ & other) const
  {
    if (this->input_status != other.input_status) {
      return false;
    }
    if (this->invalidate_outputs != other.invalidate_outputs) {
      return false;
    }
    if (this->lift_valve_cmd != other.lift_valve_cmd) {
      return false;
    }
    if (this->tilt_valve_cmd != other.tilt_valve_cmd) {
      return false;
    }
    if (this->tilt_extension != other.tilt_extension) {
      return false;
    }
    if (this->lift_angle != other.lift_angle) {
      return false;
    }
    if (this->lift_he_pressure != other.lift_he_pressure) {
      return false;
    }
    if (this->lift_re_pressure != other.lift_re_pressure) {
      return false;
    }
    if (this->tilt_he_pressure != other.tilt_he_pressure) {
      return false;
    }
    if (this->tilt_re_pressure != other.tilt_re_pressure) {
      return false;
    }
    if (this->eef_imu_accel_x != other.eef_imu_accel_x) {
      return false;
    }
    if (this->eef_imu_accel_y != other.eef_imu_accel_y) {
      return false;
    }
    if (this->eef_imu_accel_z != other.eef_imu_accel_z) {
      return false;
    }
    if (this->steering_angle != other.steering_angle) {
      return false;
    }
    if (this->tool_mass != other.tool_mass) {
      return false;
    }
    if (this->truck_target_wt != other.truck_target_wt) {
      return false;
    }
    if (this->truck_start_weight != other.truck_start_weight) {
      return false;
    }
    if (this->bucket_current_weight_accuracy != other.bucket_current_weight_accuracy) {
      return false;
    }
    if (this->bucket_current_weight != other.bucket_current_weight) {
      return false;
    }
    if (this->tipoff_mode != other.tipoff_mode) {
      return false;
    }
    if (this->zero_offset != other.zero_offset) {
      return false;
    }
    if (this->simple_cal_factor != other.simple_cal_factor) {
      return false;
    }
    if (this->mach_pitch_cal_offset != other.mach_pitch_cal_offset) {
      return false;
    }
    if (this->unlatch_trigger != other.unlatch_trigger) {
      return false;
    }
    if (this->bucket_angle != other.bucket_angle) {
      return false;
    }
    if (this->anchor_zero_offset != other.anchor_zero_offset) {
      return false;
    }
    if (this->anchor_factor != other.anchor_factor) {
      return false;
    }
    if (this->pass_count != other.pass_count) {
      return false;
    }
    if (this->lift_norm_angle != other.lift_norm_angle) {
      return false;
    }
    if (this->lift_norm_length != other.lift_norm_length) {
      return false;
    }
    if (this->tilt_norm_angle != other.tilt_norm_angle) {
      return false;
    }
    if (this->tilt_norm_length != other.tilt_norm_length) {
      return false;
    }
    if (this->friction_mu != other.friction_mu) {
      return false;
    }
    if (this->friction_offset != other.friction_offset) {
      return false;
    }
    return true;
  }
  bool operator!=(const TipoffAssistInputs_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TipoffAssistInputs_

// alias to use template instance with default allocator
using TipoffAssistInputs =
  weigh_app_interfaces::msg::TipoffAssistInputs_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_INPUTS__STRUCT_HPP_
