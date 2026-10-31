// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyTiltOverrides.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_tilt_overrides.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaNvmCalOnTheFlyTiltOverrides_
{
  using Type = LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator>;

  explicit LpsSaNvmCalOnTheFlyTiltOverrides_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lps_cal_tilt_ovr_state = 0;
      this->tilt_noise_max = 0.0f;
      this->tilt_noise_min = 0.0f;
      this->desired_tilt_extmm = 0.0f;
      this->count_of_samples = 0;
      this->tilt_dump_cmd_ovr = 0.0f;
      this->lps_cal_tilt_ovr_start_request = false;
      this->cal_tilt_override_complete = false;
      this->cal_tilt_override_fail = false;
    }
  }

  explicit LpsSaNvmCalOnTheFlyTiltOverrides_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lps_cal_tilt_ovr_state = 0;
      this->tilt_noise_max = 0.0f;
      this->tilt_noise_min = 0.0f;
      this->desired_tilt_extmm = 0.0f;
      this->count_of_samples = 0;
      this->tilt_dump_cmd_ovr = 0.0f;
      this->lps_cal_tilt_ovr_start_request = false;
      this->cal_tilt_override_complete = false;
      this->cal_tilt_override_fail = false;
    }
  }

  // field types and members
  using _lps_cal_tilt_ovr_state_type =
    uint8_t;
  _lps_cal_tilt_ovr_state_type lps_cal_tilt_ovr_state;
  using _tilt_noise_max_type =
    float;
  _tilt_noise_max_type tilt_noise_max;
  using _tilt_noise_min_type =
    float;
  _tilt_noise_min_type tilt_noise_min;
  using _desired_tilt_extmm_type =
    float;
  _desired_tilt_extmm_type desired_tilt_extmm;
  using _count_of_samples_type =
    uint8_t;
  _count_of_samples_type count_of_samples;
  using _tilt_dump_cmd_ovr_type =
    float;
  _tilt_dump_cmd_ovr_type tilt_dump_cmd_ovr;
  using _lps_cal_tilt_ovr_start_request_type =
    bool;
  _lps_cal_tilt_ovr_start_request_type lps_cal_tilt_ovr_start_request;
  using _cal_tilt_override_complete_type =
    bool;
  _cal_tilt_override_complete_type cal_tilt_override_complete;
  using _cal_tilt_override_fail_type =
    bool;
  _cal_tilt_override_fail_type cal_tilt_override_fail;

  // setters for named parameter idiom
  Type & set__lps_cal_tilt_ovr_state(
    const uint8_t & _arg)
  {
    this->lps_cal_tilt_ovr_state = _arg;
    return *this;
  }
  Type & set__tilt_noise_max(
    const float & _arg)
  {
    this->tilt_noise_max = _arg;
    return *this;
  }
  Type & set__tilt_noise_min(
    const float & _arg)
  {
    this->tilt_noise_min = _arg;
    return *this;
  }
  Type & set__desired_tilt_extmm(
    const float & _arg)
  {
    this->desired_tilt_extmm = _arg;
    return *this;
  }
  Type & set__count_of_samples(
    const uint8_t & _arg)
  {
    this->count_of_samples = _arg;
    return *this;
  }
  Type & set__tilt_dump_cmd_ovr(
    const float & _arg)
  {
    this->tilt_dump_cmd_ovr = _arg;
    return *this;
  }
  Type & set__lps_cal_tilt_ovr_start_request(
    const bool & _arg)
  {
    this->lps_cal_tilt_ovr_start_request = _arg;
    return *this;
  }
  Type & set__cal_tilt_override_complete(
    const bool & _arg)
  {
    this->cal_tilt_override_complete = _arg;
    return *this;
  }
  Type & set__cal_tilt_override_fail(
    const bool & _arg)
  {
    this->cal_tilt_override_fail = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaNvmCalOnTheFlyTiltOverrides_ & other) const
  {
    if (this->lps_cal_tilt_ovr_state != other.lps_cal_tilt_ovr_state) {
      return false;
    }
    if (this->tilt_noise_max != other.tilt_noise_max) {
      return false;
    }
    if (this->tilt_noise_min != other.tilt_noise_min) {
      return false;
    }
    if (this->desired_tilt_extmm != other.desired_tilt_extmm) {
      return false;
    }
    if (this->count_of_samples != other.count_of_samples) {
      return false;
    }
    if (this->tilt_dump_cmd_ovr != other.tilt_dump_cmd_ovr) {
      return false;
    }
    if (this->lps_cal_tilt_ovr_start_request != other.lps_cal_tilt_ovr_start_request) {
      return false;
    }
    if (this->cal_tilt_override_complete != other.cal_tilt_override_complete) {
      return false;
    }
    if (this->cal_tilt_override_fail != other.cal_tilt_override_fail) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaNvmCalOnTheFlyTiltOverrides_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaNvmCalOnTheFlyTiltOverrides_

// alias to use template instance with default allocator
using LpsSaNvmCalOnTheFlyTiltOverrides =
  weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__STRUCT_HPP_
