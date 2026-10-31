// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaUIDisplayState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_ui_display_state.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'settings'
#include "cpm_common_interfaces/msg/detail/lps_sa_ui_display_settings__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplayState __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplayState __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaUIDisplayState_
{
  using Type = LpsSaUIDisplayState_<ContainerAllocator>;

  explicit LpsSaUIDisplayState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : settings(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->service_mode_enable_code_entered = false;
      this->in_service_mode = false;
      this->in_verification_mode = false;
      this->heartbeat_count = 0ul;
      this->document_id = 0;
      this->weight_capacity = 0.0f;
      this->weight_decimal_precision = 0l;
      this->weight_interval = 0.0f;
    }
  }

  explicit LpsSaUIDisplayState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : settings(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->service_mode_enable_code_entered = false;
      this->in_service_mode = false;
      this->in_verification_mode = false;
      this->heartbeat_count = 0ul;
      this->document_id = 0;
      this->weight_capacity = 0.0f;
      this->weight_decimal_precision = 0l;
      this->weight_interval = 0.0f;
    }
  }

  // field types and members
  using _service_mode_enable_code_entered_type =
    bool;
  _service_mode_enable_code_entered_type service_mode_enable_code_entered;
  using _in_service_mode_type =
    bool;
  _in_service_mode_type in_service_mode;
  using _in_verification_mode_type =
    bool;
  _in_verification_mode_type in_verification_mode;
  using _heartbeat_count_type =
    uint32_t;
  _heartbeat_count_type heartbeat_count;
  using _document_id_type =
    uint16_t;
  _document_id_type document_id;
  using _weight_capacity_type =
    float;
  _weight_capacity_type weight_capacity;
  using _weight_decimal_precision_type =
    int32_t;
  _weight_decimal_precision_type weight_decimal_precision;
  using _weight_interval_type =
    float;
  _weight_interval_type weight_interval;
  using _settings_type =
    cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator>;
  _settings_type settings;

  // setters for named parameter idiom
  Type & set__service_mode_enable_code_entered(
    const bool & _arg)
  {
    this->service_mode_enable_code_entered = _arg;
    return *this;
  }
  Type & set__in_service_mode(
    const bool & _arg)
  {
    this->in_service_mode = _arg;
    return *this;
  }
  Type & set__in_verification_mode(
    const bool & _arg)
  {
    this->in_verification_mode = _arg;
    return *this;
  }
  Type & set__heartbeat_count(
    const uint32_t & _arg)
  {
    this->heartbeat_count = _arg;
    return *this;
  }
  Type & set__document_id(
    const uint16_t & _arg)
  {
    this->document_id = _arg;
    return *this;
  }
  Type & set__weight_capacity(
    const float & _arg)
  {
    this->weight_capacity = _arg;
    return *this;
  }
  Type & set__weight_decimal_precision(
    const int32_t & _arg)
  {
    this->weight_decimal_precision = _arg;
    return *this;
  }
  Type & set__weight_interval(
    const float & _arg)
  {
    this->weight_interval = _arg;
    return *this;
  }
  Type & set__settings(
    const cpm_common_interfaces::msg::LpsSaUIDisplaySettings_<ContainerAllocator> & _arg)
  {
    this->settings = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplayState
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplayState
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaUIDisplayState_ & other) const
  {
    if (this->service_mode_enable_code_entered != other.service_mode_enable_code_entered) {
      return false;
    }
    if (this->in_service_mode != other.in_service_mode) {
      return false;
    }
    if (this->in_verification_mode != other.in_verification_mode) {
      return false;
    }
    if (this->heartbeat_count != other.heartbeat_count) {
      return false;
    }
    if (this->document_id != other.document_id) {
      return false;
    }
    if (this->weight_capacity != other.weight_capacity) {
      return false;
    }
    if (this->weight_decimal_precision != other.weight_decimal_precision) {
      return false;
    }
    if (this->weight_interval != other.weight_interval) {
      return false;
    }
    if (this->settings != other.settings) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaUIDisplayState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaUIDisplayState_

// alias to use template instance with default allocator
using LpsSaUIDisplayState =
  cpm_common_interfaces::msg::LpsSaUIDisplayState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__STRUCT_HPP_
