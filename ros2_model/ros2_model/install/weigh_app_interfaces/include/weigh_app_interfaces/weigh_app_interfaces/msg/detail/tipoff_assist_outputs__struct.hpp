// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/TipoffAssistOutputs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/tipoff_assist_outputs.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__TipoffAssistOutputs __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__TipoffAssistOutputs __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TipoffAssistOutputs_
{
  using Type = TipoffAssistOutputs_<ContainerAllocator>;

  explicit TipoffAssistOutputs_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tilt_sensitivity_out = 0.0f;
      this->tilt_pressure_out = 0.0f;
      this->arbitrated_payload_norm_error_out = 0.0f;
      this->weigh_status_out = 0;
      this->payload_norm_stdev_out = 0.0f;
      this->pcs_weight_accuracy_out = 0;
      this->current_weight_norm_error_out = 0.0f;
      this->error_code_out = 0;
      this->spill_rate_out = 0.0f;
      this->payload_send_to_cpm = 0.0f;
      this->payload_status_send_to_cpm = 0;
      this->bucket_payload_target = 0.0f;
      this->unsecured_payload_upper_bound_norm = 0.0f;
      this->unsecured_payload_lower_bound_norm = 0.0f;
      this->unsecured_pfw_status = 0;
      this->min_secure_bucket_angle = 0.0f;
    }
  }

  explicit TipoffAssistOutputs_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tilt_sensitivity_out = 0.0f;
      this->tilt_pressure_out = 0.0f;
      this->arbitrated_payload_norm_error_out = 0.0f;
      this->weigh_status_out = 0;
      this->payload_norm_stdev_out = 0.0f;
      this->pcs_weight_accuracy_out = 0;
      this->current_weight_norm_error_out = 0.0f;
      this->error_code_out = 0;
      this->spill_rate_out = 0.0f;
      this->payload_send_to_cpm = 0.0f;
      this->payload_status_send_to_cpm = 0;
      this->bucket_payload_target = 0.0f;
      this->unsecured_payload_upper_bound_norm = 0.0f;
      this->unsecured_payload_lower_bound_norm = 0.0f;
      this->unsecured_pfw_status = 0;
      this->min_secure_bucket_angle = 0.0f;
    }
  }

  // field types and members
  using _tilt_sensitivity_out_type =
    float;
  _tilt_sensitivity_out_type tilt_sensitivity_out;
  using _tilt_pressure_out_type =
    float;
  _tilt_pressure_out_type tilt_pressure_out;
  using _arbitrated_payload_norm_error_out_type =
    float;
  _arbitrated_payload_norm_error_out_type arbitrated_payload_norm_error_out;
  using _weigh_status_out_type =
    uint8_t;
  _weigh_status_out_type weigh_status_out;
  using _payload_norm_stdev_out_type =
    float;
  _payload_norm_stdev_out_type payload_norm_stdev_out;
  using _pcs_weight_accuracy_out_type =
    uint8_t;
  _pcs_weight_accuracy_out_type pcs_weight_accuracy_out;
  using _current_weight_norm_error_out_type =
    float;
  _current_weight_norm_error_out_type current_weight_norm_error_out;
  using _error_code_out_type =
    uint8_t;
  _error_code_out_type error_code_out;
  using _spill_rate_out_type =
    float;
  _spill_rate_out_type spill_rate_out;
  using _payload_send_to_cpm_type =
    float;
  _payload_send_to_cpm_type payload_send_to_cpm;
  using _payload_status_send_to_cpm_type =
    uint8_t;
  _payload_status_send_to_cpm_type payload_status_send_to_cpm;
  using _bucket_payload_target_type =
    float;
  _bucket_payload_target_type bucket_payload_target;
  using _unsecured_payload_upper_bound_norm_type =
    float;
  _unsecured_payload_upper_bound_norm_type unsecured_payload_upper_bound_norm;
  using _unsecured_payload_lower_bound_norm_type =
    float;
  _unsecured_payload_lower_bound_norm_type unsecured_payload_lower_bound_norm;
  using _unsecured_pfw_status_type =
    uint8_t;
  _unsecured_pfw_status_type unsecured_pfw_status;
  using _min_secure_bucket_angle_type =
    float;
  _min_secure_bucket_angle_type min_secure_bucket_angle;

  // setters for named parameter idiom
  Type & set__tilt_sensitivity_out(
    const float & _arg)
  {
    this->tilt_sensitivity_out = _arg;
    return *this;
  }
  Type & set__tilt_pressure_out(
    const float & _arg)
  {
    this->tilt_pressure_out = _arg;
    return *this;
  }
  Type & set__arbitrated_payload_norm_error_out(
    const float & _arg)
  {
    this->arbitrated_payload_norm_error_out = _arg;
    return *this;
  }
  Type & set__weigh_status_out(
    const uint8_t & _arg)
  {
    this->weigh_status_out = _arg;
    return *this;
  }
  Type & set__payload_norm_stdev_out(
    const float & _arg)
  {
    this->payload_norm_stdev_out = _arg;
    return *this;
  }
  Type & set__pcs_weight_accuracy_out(
    const uint8_t & _arg)
  {
    this->pcs_weight_accuracy_out = _arg;
    return *this;
  }
  Type & set__current_weight_norm_error_out(
    const float & _arg)
  {
    this->current_weight_norm_error_out = _arg;
    return *this;
  }
  Type & set__error_code_out(
    const uint8_t & _arg)
  {
    this->error_code_out = _arg;
    return *this;
  }
  Type & set__spill_rate_out(
    const float & _arg)
  {
    this->spill_rate_out = _arg;
    return *this;
  }
  Type & set__payload_send_to_cpm(
    const float & _arg)
  {
    this->payload_send_to_cpm = _arg;
    return *this;
  }
  Type & set__payload_status_send_to_cpm(
    const uint8_t & _arg)
  {
    this->payload_status_send_to_cpm = _arg;
    return *this;
  }
  Type & set__bucket_payload_target(
    const float & _arg)
  {
    this->bucket_payload_target = _arg;
    return *this;
  }
  Type & set__unsecured_payload_upper_bound_norm(
    const float & _arg)
  {
    this->unsecured_payload_upper_bound_norm = _arg;
    return *this;
  }
  Type & set__unsecured_payload_lower_bound_norm(
    const float & _arg)
  {
    this->unsecured_payload_lower_bound_norm = _arg;
    return *this;
  }
  Type & set__unsecured_pfw_status(
    const uint8_t & _arg)
  {
    this->unsecured_pfw_status = _arg;
    return *this;
  }
  Type & set__min_secure_bucket_angle(
    const float & _arg)
  {
    this->min_secure_bucket_angle = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__TipoffAssistOutputs
    std::shared_ptr<weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__TipoffAssistOutputs
    std::shared_ptr<weigh_app_interfaces::msg::TipoffAssistOutputs_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TipoffAssistOutputs_ & other) const
  {
    if (this->tilt_sensitivity_out != other.tilt_sensitivity_out) {
      return false;
    }
    if (this->tilt_pressure_out != other.tilt_pressure_out) {
      return false;
    }
    if (this->arbitrated_payload_norm_error_out != other.arbitrated_payload_norm_error_out) {
      return false;
    }
    if (this->weigh_status_out != other.weigh_status_out) {
      return false;
    }
    if (this->payload_norm_stdev_out != other.payload_norm_stdev_out) {
      return false;
    }
    if (this->pcs_weight_accuracy_out != other.pcs_weight_accuracy_out) {
      return false;
    }
    if (this->current_weight_norm_error_out != other.current_weight_norm_error_out) {
      return false;
    }
    if (this->error_code_out != other.error_code_out) {
      return false;
    }
    if (this->spill_rate_out != other.spill_rate_out) {
      return false;
    }
    if (this->payload_send_to_cpm != other.payload_send_to_cpm) {
      return false;
    }
    if (this->payload_status_send_to_cpm != other.payload_status_send_to_cpm) {
      return false;
    }
    if (this->bucket_payload_target != other.bucket_payload_target) {
      return false;
    }
    if (this->unsecured_payload_upper_bound_norm != other.unsecured_payload_upper_bound_norm) {
      return false;
    }
    if (this->unsecured_payload_lower_bound_norm != other.unsecured_payload_lower_bound_norm) {
      return false;
    }
    if (this->unsecured_pfw_status != other.unsecured_pfw_status) {
      return false;
    }
    if (this->min_secure_bucket_angle != other.min_secure_bucket_angle) {
      return false;
    }
    return true;
  }
  bool operator!=(const TipoffAssistOutputs_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TipoffAssistOutputs_

// alias to use template instance with default allocator
using TipoffAssistOutputs =
  weigh_app_interfaces::msg::TipoffAssistOutputs_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TIPOFF_ASSIST_OUTPUTS__STRUCT_HPP_
