// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/FloatPair.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/float_pair.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_PAIR__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_PAIR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__FloatPair __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__FloatPair __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct FloatPair_
{
  using Type = FloatPair_<ContainerAllocator>;

  explicit FloatPair_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->first = 0.0f;
      this->second = 0.0f;
    }
  }

  explicit FloatPair_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->first = 0.0f;
      this->second = 0.0f;
    }
  }

  // field types and members
  using _first_type =
    float;
  _first_type first;
  using _second_type =
    float;
  _second_type second;

  // setters for named parameter idiom
  Type & set__first(
    const float & _arg)
  {
    this->first = _arg;
    return *this;
  }
  Type & set__second(
    const float & _arg)
  {
    this->second = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::FloatPair_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::FloatPair_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::FloatPair_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::FloatPair_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__FloatPair
    std::shared_ptr<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__FloatPair
    std::shared_ptr<cpm_common_interfaces::msg::FloatPair_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const FloatPair_ & other) const
  {
    if (this->first != other.first) {
      return false;
    }
    if (this->second != other.second) {
      return false;
    }
    return true;
  }
  bool operator!=(const FloatPair_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct FloatPair_

// alias to use template instance with default allocator
using FloatPair =
  cpm_common_interfaces::msg::FloatPair_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_PAIR__STRUCT_HPP_
