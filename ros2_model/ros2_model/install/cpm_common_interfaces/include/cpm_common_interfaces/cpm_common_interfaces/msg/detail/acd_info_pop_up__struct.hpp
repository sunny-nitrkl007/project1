// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/AcdInfoPopUp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/acd_info_pop_up.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_INFO_POP_UP__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_INFO_POP_UP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__AcdInfoPopUp __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__AcdInfoPopUp __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AcdInfoPopUp_
{
  using Type = AcdInfoPopUp_<ContainerAllocator>;

  explicit AcdInfoPopUp_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->bits = 0ul;
    }
  }

  explicit AcdInfoPopUp_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->bits = 0ul;
    }
  }

  // field types and members
  using _bits_type =
    uint32_t;
  _bits_type bits;

  // setters for named parameter idiom
  Type & set__bits(
    const uint32_t & _arg)
  {
    this->bits = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t PAYLOAD_TOO_HEAVY_TO_ZERO =
    0u;
  static constexpr uint8_t PAYLOAD_NOT_ZEROED =
    1u;
  static constexpr uint8_t PAYLOAD_CAL_ACCEPTED =
    2u;
  static constexpr uint8_t PAYLOAD_ZERO_ACCEPTED =
    3u;
  static constexpr uint8_t PAYLOAD_REWEIGH_LIFT_TOO_SLOW =
    4u;
  static constexpr uint8_t PAYLOAD_REWEIGH_STOPPED_IN_RANGE =
    5u;
  static constexpr uint8_t PAYLOAD_REWEIGH_NOT_RACKED =
    6u;
  static constexpr uint8_t PAYLOAD_REWEIGH_SPEED_CHANGING =
    7u;
  static constexpr uint8_t PAYLOAD_REWEIGH_INCONSISTENT =
    8u;
  static constexpr uint8_t PAYLOAD_REWEIGH_PRESSURE_CHANGING =
    9u;
  static constexpr uint8_t PAYLOAD_REWEIGH_EXCESSIVE_PITCH =
    10u;
  static constexpr uint8_t PAYLOAD_REWEIGH_WARMUP_LIFT =
    11u;
  static constexpr uint8_t PAYLOAD_RAISE_STALL =
    12u;
  static constexpr uint8_t PAYLOAD_LOWER_STALL =
    13u;
  static constexpr uint8_t PAYLOAD_CAL_WT_ENTRY_REQUIRED =
    14u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__AcdInfoPopUp
    std::shared_ptr<cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__AcdInfoPopUp
    std::shared_ptr<cpm_common_interfaces::msg::AcdInfoPopUp_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AcdInfoPopUp_ & other) const
  {
    if (this->bits != other.bits) {
      return false;
    }
    return true;
  }
  bool operator!=(const AcdInfoPopUp_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AcdInfoPopUp_

// alias to use template instance with default allocator
using AcdInfoPopUp =
  cpm_common_interfaces::msg::AcdInfoPopUp_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_TOO_HEAVY_TO_ZERO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_NOT_ZEROED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_CAL_ACCEPTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_ZERO_ACCEPTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_REWEIGH_LIFT_TOO_SLOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_REWEIGH_STOPPED_IN_RANGE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_REWEIGH_NOT_RACKED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_REWEIGH_SPEED_CHANGING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_REWEIGH_INCONSISTENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_REWEIGH_PRESSURE_CHANGING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_REWEIGH_EXCESSIVE_PITCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_REWEIGH_WARMUP_LIFT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_RAISE_STALL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_LOWER_STALL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdInfoPopUp_<ContainerAllocator>::PAYLOAD_CAL_WT_ENTRY_REQUIRED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_INFO_POP_UP__STRUCT_HPP_
