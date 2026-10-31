// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannelDataMain.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel_data_main.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataMain __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataMain __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaNvmCalDataChannelDataMain_
{
  using Type = LpsSaNvmCalDataChannelDataMain_<ContainerAllocator>;

  explicit LpsSaNvmCalDataChannelDataMain_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 11>::iterator, float>(this->raise_slow_empty_lift_heights.begin(), this->raise_slow_empty_lift_heights.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->raise_slow_empty_pressures.begin(), this->raise_slow_empty_pressures.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->lower_slow_empty_lift_heights.begin(), this->lower_slow_empty_lift_heights.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->lower_slow_empty_pressures.begin(), this->lower_slow_empty_pressures.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->raise_slow_full_lift_heights.begin(), this->raise_slow_full_lift_heights.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->raise_slow_full_pressures.begin(), this->raise_slow_full_pressures.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->lower_slow_full_lift_heights.begin(), this->lower_slow_full_lift_heights.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->lower_slow_full_pressures.begin(), this->lower_slow_full_pressures.end(), 0.0f);
      this->raise_speed_empty_slow = 0.0f;
      this->raise_speed_empty_fast = 0.0f;
      this->raise_fast_delta_p_empty = 0.0f;
      this->raise_speed_full_slow = 0.0f;
      this->raise_speed_full_fast = 0.0f;
      this->raise_fast_delta_p_full = 0.0f;
    }
  }

  explicit LpsSaNvmCalDataChannelDataMain_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : raise_slow_empty_lift_heights(_alloc),
    raise_slow_empty_pressures(_alloc),
    lower_slow_empty_lift_heights(_alloc),
    lower_slow_empty_pressures(_alloc),
    raise_slow_full_lift_heights(_alloc),
    raise_slow_full_pressures(_alloc),
    lower_slow_full_lift_heights(_alloc),
    lower_slow_full_pressures(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<float, 11>::iterator, float>(this->raise_slow_empty_lift_heights.begin(), this->raise_slow_empty_lift_heights.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->raise_slow_empty_pressures.begin(), this->raise_slow_empty_pressures.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->lower_slow_empty_lift_heights.begin(), this->lower_slow_empty_lift_heights.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->lower_slow_empty_pressures.begin(), this->lower_slow_empty_pressures.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->raise_slow_full_lift_heights.begin(), this->raise_slow_full_lift_heights.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->raise_slow_full_pressures.begin(), this->raise_slow_full_pressures.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->lower_slow_full_lift_heights.begin(), this->lower_slow_full_lift_heights.end(), 0.0f);
      std::fill<typename std::array<float, 11>::iterator, float>(this->lower_slow_full_pressures.begin(), this->lower_slow_full_pressures.end(), 0.0f);
      this->raise_speed_empty_slow = 0.0f;
      this->raise_speed_empty_fast = 0.0f;
      this->raise_fast_delta_p_empty = 0.0f;
      this->raise_speed_full_slow = 0.0f;
      this->raise_speed_full_fast = 0.0f;
      this->raise_fast_delta_p_full = 0.0f;
    }
  }

  // field types and members
  using _raise_slow_empty_lift_heights_type =
    std::array<float, 11>;
  _raise_slow_empty_lift_heights_type raise_slow_empty_lift_heights;
  using _raise_slow_empty_pressures_type =
    std::array<float, 11>;
  _raise_slow_empty_pressures_type raise_slow_empty_pressures;
  using _lower_slow_empty_lift_heights_type =
    std::array<float, 11>;
  _lower_slow_empty_lift_heights_type lower_slow_empty_lift_heights;
  using _lower_slow_empty_pressures_type =
    std::array<float, 11>;
  _lower_slow_empty_pressures_type lower_slow_empty_pressures;
  using _raise_slow_full_lift_heights_type =
    std::array<float, 11>;
  _raise_slow_full_lift_heights_type raise_slow_full_lift_heights;
  using _raise_slow_full_pressures_type =
    std::array<float, 11>;
  _raise_slow_full_pressures_type raise_slow_full_pressures;
  using _lower_slow_full_lift_heights_type =
    std::array<float, 11>;
  _lower_slow_full_lift_heights_type lower_slow_full_lift_heights;
  using _lower_slow_full_pressures_type =
    std::array<float, 11>;
  _lower_slow_full_pressures_type lower_slow_full_pressures;
  using _raise_speed_empty_slow_type =
    float;
  _raise_speed_empty_slow_type raise_speed_empty_slow;
  using _raise_speed_empty_fast_type =
    float;
  _raise_speed_empty_fast_type raise_speed_empty_fast;
  using _raise_fast_delta_p_empty_type =
    float;
  _raise_fast_delta_p_empty_type raise_fast_delta_p_empty;
  using _raise_speed_full_slow_type =
    float;
  _raise_speed_full_slow_type raise_speed_full_slow;
  using _raise_speed_full_fast_type =
    float;
  _raise_speed_full_fast_type raise_speed_full_fast;
  using _raise_fast_delta_p_full_type =
    float;
  _raise_fast_delta_p_full_type raise_fast_delta_p_full;

  // setters for named parameter idiom
  Type & set__raise_slow_empty_lift_heights(
    const std::array<float, 11> & _arg)
  {
    this->raise_slow_empty_lift_heights = _arg;
    return *this;
  }
  Type & set__raise_slow_empty_pressures(
    const std::array<float, 11> & _arg)
  {
    this->raise_slow_empty_pressures = _arg;
    return *this;
  }
  Type & set__lower_slow_empty_lift_heights(
    const std::array<float, 11> & _arg)
  {
    this->lower_slow_empty_lift_heights = _arg;
    return *this;
  }
  Type & set__lower_slow_empty_pressures(
    const std::array<float, 11> & _arg)
  {
    this->lower_slow_empty_pressures = _arg;
    return *this;
  }
  Type & set__raise_slow_full_lift_heights(
    const std::array<float, 11> & _arg)
  {
    this->raise_slow_full_lift_heights = _arg;
    return *this;
  }
  Type & set__raise_slow_full_pressures(
    const std::array<float, 11> & _arg)
  {
    this->raise_slow_full_pressures = _arg;
    return *this;
  }
  Type & set__lower_slow_full_lift_heights(
    const std::array<float, 11> & _arg)
  {
    this->lower_slow_full_lift_heights = _arg;
    return *this;
  }
  Type & set__lower_slow_full_pressures(
    const std::array<float, 11> & _arg)
  {
    this->lower_slow_full_pressures = _arg;
    return *this;
  }
  Type & set__raise_speed_empty_slow(
    const float & _arg)
  {
    this->raise_speed_empty_slow = _arg;
    return *this;
  }
  Type & set__raise_speed_empty_fast(
    const float & _arg)
  {
    this->raise_speed_empty_fast = _arg;
    return *this;
  }
  Type & set__raise_fast_delta_p_empty(
    const float & _arg)
  {
    this->raise_fast_delta_p_empty = _arg;
    return *this;
  }
  Type & set__raise_speed_full_slow(
    const float & _arg)
  {
    this->raise_speed_full_slow = _arg;
    return *this;
  }
  Type & set__raise_speed_full_fast(
    const float & _arg)
  {
    this->raise_speed_full_fast = _arg;
    return *this;
  }
  Type & set__raise_fast_delta_p_full(
    const float & _arg)
  {
    this->raise_fast_delta_p_full = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataMain
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataMain
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaNvmCalDataChannelDataMain_ & other) const
  {
    if (this->raise_slow_empty_lift_heights != other.raise_slow_empty_lift_heights) {
      return false;
    }
    if (this->raise_slow_empty_pressures != other.raise_slow_empty_pressures) {
      return false;
    }
    if (this->lower_slow_empty_lift_heights != other.lower_slow_empty_lift_heights) {
      return false;
    }
    if (this->lower_slow_empty_pressures != other.lower_slow_empty_pressures) {
      return false;
    }
    if (this->raise_slow_full_lift_heights != other.raise_slow_full_lift_heights) {
      return false;
    }
    if (this->raise_slow_full_pressures != other.raise_slow_full_pressures) {
      return false;
    }
    if (this->lower_slow_full_lift_heights != other.lower_slow_full_lift_heights) {
      return false;
    }
    if (this->lower_slow_full_pressures != other.lower_slow_full_pressures) {
      return false;
    }
    if (this->raise_speed_empty_slow != other.raise_speed_empty_slow) {
      return false;
    }
    if (this->raise_speed_empty_fast != other.raise_speed_empty_fast) {
      return false;
    }
    if (this->raise_fast_delta_p_empty != other.raise_fast_delta_p_empty) {
      return false;
    }
    if (this->raise_speed_full_slow != other.raise_speed_full_slow) {
      return false;
    }
    if (this->raise_speed_full_fast != other.raise_speed_full_fast) {
      return false;
    }
    if (this->raise_fast_delta_p_full != other.raise_fast_delta_p_full) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaNvmCalDataChannelDataMain_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaNvmCalDataChannelDataMain_

// alias to use template instance with default allocator
using LpsSaNvmCalDataChannelDataMain =
  weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_MAIN__STRUCT_HPP_
