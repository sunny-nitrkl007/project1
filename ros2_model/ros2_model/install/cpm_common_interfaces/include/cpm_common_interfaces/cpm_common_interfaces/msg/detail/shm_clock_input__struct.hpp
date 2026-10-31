// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/ShmClockInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/shm_clock_input.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__ShmClockInput __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__ShmClockInput __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ShmClockInput_
{
  using Type = ShmClockInput_<ContainerAllocator>;

  explicit ShmClockInput_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->shm_sec = 0ul;
      this->utc_sec_us = 0ll;
      this->utc_offset_min = 0l;
      std::fill<typename std::array<uint8_t, 20>::iterator, uint8_t>(this->tzone_info.begin(), this->tzone_info.end(), 0);
    }
  }

  explicit ShmClockInput_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : tzone_info(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->shm_sec = 0ul;
      this->utc_sec_us = 0ll;
      this->utc_offset_min = 0l;
      std::fill<typename std::array<uint8_t, 20>::iterator, uint8_t>(this->tzone_info.begin(), this->tzone_info.end(), 0);
    }
  }

  // field types and members
  using _shm_sec_type =
    uint32_t;
  _shm_sec_type shm_sec;
  using _utc_sec_us_type =
    int64_t;
  _utc_sec_us_type utc_sec_us;
  using _utc_offset_min_type =
    int32_t;
  _utc_offset_min_type utc_offset_min;
  using _tzone_info_type =
    std::array<uint8_t, 20>;
  _tzone_info_type tzone_info;

  // setters for named parameter idiom
  Type & set__shm_sec(
    const uint32_t & _arg)
  {
    this->shm_sec = _arg;
    return *this;
  }
  Type & set__utc_sec_us(
    const int64_t & _arg)
  {
    this->utc_sec_us = _arg;
    return *this;
  }
  Type & set__utc_offset_min(
    const int32_t & _arg)
  {
    this->utc_offset_min = _arg;
    return *this;
  }
  Type & set__tzone_info(
    const std::array<uint8_t, 20> & _arg)
  {
    this->tzone_info = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__ShmClockInput
    std::shared_ptr<cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__ShmClockInput
    std::shared_ptr<cpm_common_interfaces::msg::ShmClockInput_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ShmClockInput_ & other) const
  {
    if (this->shm_sec != other.shm_sec) {
      return false;
    }
    if (this->utc_sec_us != other.utc_sec_us) {
      return false;
    }
    if (this->utc_offset_min != other.utc_offset_min) {
      return false;
    }
    if (this->tzone_info != other.tzone_info) {
      return false;
    }
    return true;
  }
  bool operator!=(const ShmClockInput_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ShmClockInput_

// alias to use template instance with default allocator
using ShmClockInput =
  cpm_common_interfaces::msg::ShmClockInput_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__STRUCT_HPP_
