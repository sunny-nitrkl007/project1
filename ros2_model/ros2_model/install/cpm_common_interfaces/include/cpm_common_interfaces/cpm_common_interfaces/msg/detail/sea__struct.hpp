// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/SEA.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/sea.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SEA__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SEA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__SEA __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__SEA __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SEA_
{
  using Type = SEA_<ContainerAllocator>;

  explicit SEA_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->free_count = 0;
      this->reason_code = 0;
      this->status = 0;
    }
  }

  explicit SEA_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->free_count = 0;
      this->reason_code = 0;
      this->status = 0;
    }
  }

  // field types and members
  using _free_count_type =
    uint16_t;
  _free_count_type free_count;
  using _reason_code_type =
    uint16_t;
  _reason_code_type reason_code;
  using _status_type =
    uint16_t;
  _status_type status;

  // setters for named parameter idiom
  Type & set__free_count(
    const uint16_t & _arg)
  {
    this->free_count = _arg;
    return *this;
  }
  Type & set__reason_code(
    const uint16_t & _arg)
  {
    this->reason_code = _arg;
    return *this;
  }
  Type & set__status(
    const uint16_t & _arg)
  {
    this->status = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t STATUS_UNKNOWN =
    0u;
  static constexpr uint16_t STATUS_NOT_INSTALLED =
    1u;
  static constexpr uint16_t STATUS_INSTALLED =
    2u;
  static constexpr uint16_t STATUS_ENABLED =
    3u;
  static constexpr uint16_t STATUS_TEMP_INSTALLED =
    4u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::SEA_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::SEA_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::SEA_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::SEA_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::SEA_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::SEA_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::SEA_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::SEA_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::SEA_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::SEA_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__SEA
    std::shared_ptr<cpm_common_interfaces::msg::SEA_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__SEA
    std::shared_ptr<cpm_common_interfaces::msg::SEA_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SEA_ & other) const
  {
    if (this->free_count != other.free_count) {
      return false;
    }
    if (this->reason_code != other.reason_code) {
      return false;
    }
    if (this->status != other.status) {
      return false;
    }
    return true;
  }
  bool operator!=(const SEA_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SEA_

// alias to use template instance with default allocator
using SEA =
  cpm_common_interfaces::msg::SEA_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t SEA_<ContainerAllocator>::STATUS_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t SEA_<ContainerAllocator>::STATUS_NOT_INSTALLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t SEA_<ContainerAllocator>::STATUS_INSTALLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t SEA_<ContainerAllocator>::STATUS_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t SEA_<ContainerAllocator>::STATUS_TEMP_INSTALLED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SEA__STRUCT_HPP_
