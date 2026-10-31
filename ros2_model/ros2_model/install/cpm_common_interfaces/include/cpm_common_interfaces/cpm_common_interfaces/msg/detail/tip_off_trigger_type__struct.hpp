// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/TipOffTriggerType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/tip_off_trigger_type.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_TRIGGER_TYPE__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_TRIGGER_TYPE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__TipOffTriggerType __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__TipOffTriggerType __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TipOffTriggerType_
{
  using Type = TipOffTriggerType_<ContainerAllocator>;

  explicit TipOffTriggerType_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  explicit TipOffTriggerType_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  // field types and members
  using _value_type =
    uint8_t;
  _value_type value;

  // setters for named parameter idiom
  Type & set__value(
    const uint8_t & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t AUTO =
    0u;
  static constexpr uint8_t MANUAL =
    1u;
  static constexpr uint8_t DISABLED =
    2u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__TipOffTriggerType
    std::shared_ptr<cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__TipOffTriggerType
    std::shared_ptr<cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TipOffTriggerType_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const TipOffTriggerType_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TipOffTriggerType_

// alias to use template instance with default allocator
using TipOffTriggerType =
  cpm_common_interfaces::msg::TipOffTriggerType_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TipOffTriggerType_<ContainerAllocator>::AUTO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TipOffTriggerType_<ContainerAllocator>::MANUAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TipOffTriggerType_<ContainerAllocator>::DISABLED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__TIP_OFF_TRIGGER_TYPE__STRUCT_HPP_
