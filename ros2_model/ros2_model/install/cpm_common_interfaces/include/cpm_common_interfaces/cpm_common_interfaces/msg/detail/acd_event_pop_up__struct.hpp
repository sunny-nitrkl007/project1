// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/AcdEventPopUp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/acd_event_pop_up.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__AcdEventPopUp __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__AcdEventPopUp __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AcdEventPopUp_
{
  using Type = AcdEventPopUp_<ContainerAllocator>;

  explicit AcdEventPopUp_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->bits = 0ul;
    }
  }

  explicit AcdEventPopUp_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
  static constexpr uint8_t BATTERY_HIGH =
    28u;
  static constexpr uint8_t BATTERY_LOW =
    29u;
  static constexpr uint8_t PAYLOAD_LFT_NOT_SEALED =
    30u;
  static constexpr uint8_t OVERLOAD_LIMIT_EXCEEDED =
    31u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__AcdEventPopUp
    std::shared_ptr<cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__AcdEventPopUp
    std::shared_ptr<cpm_common_interfaces::msg::AcdEventPopUp_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AcdEventPopUp_ & other) const
  {
    if (this->bits != other.bits) {
      return false;
    }
    return true;
  }
  bool operator!=(const AcdEventPopUp_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AcdEventPopUp_

// alias to use template instance with default allocator
using AcdEventPopUp =
  cpm_common_interfaces::msg::AcdEventPopUp_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdEventPopUp_<ContainerAllocator>::BATTERY_HIGH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdEventPopUp_<ContainerAllocator>::BATTERY_LOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdEventPopUp_<ContainerAllocator>::PAYLOAD_LFT_NOT_SEALED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdEventPopUp_<ContainerAllocator>::OVERLOAD_LIMIT_EXCEEDED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__STRUCT_HPP_
