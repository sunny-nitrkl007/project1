// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/Payload.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/payload.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__Payload __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__Payload __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Payload_
{
  using Type = Payload_<ContainerAllocator>;

  explicit Payload_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->payload_ratio_raw = 0.0f;
      this->payload_ratio = 0.0f;
      this->payload_ratio_status = 0l;
    }
  }

  explicit Payload_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->payload_ratio_raw = 0.0f;
      this->payload_ratio = 0.0f;
      this->payload_ratio_status = 0l;
    }
  }

  // field types and members
  using _payload_ratio_raw_type =
    float;
  _payload_ratio_raw_type payload_ratio_raw;
  using _payload_ratio_type =
    float;
  _payload_ratio_type payload_ratio;
  using _payload_ratio_status_type =
    int32_t;
  _payload_ratio_status_type payload_ratio_status;

  // setters for named parameter idiom
  Type & set__payload_ratio_raw(
    const float & _arg)
  {
    this->payload_ratio_raw = _arg;
    return *this;
  }
  Type & set__payload_ratio(
    const float & _arg)
  {
    this->payload_ratio = _arg;
    return *this;
  }
  Type & set__payload_ratio_status(
    const int32_t & _arg)
  {
    this->payload_ratio_status = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::Payload_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::Payload_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::Payload_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::Payload_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::Payload_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::Payload_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::Payload_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::Payload_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::Payload_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::Payload_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__Payload
    std::shared_ptr<cpm_common_interfaces::msg::Payload_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__Payload
    std::shared_ptr<cpm_common_interfaces::msg::Payload_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Payload_ & other) const
  {
    if (this->payload_ratio_raw != other.payload_ratio_raw) {
      return false;
    }
    if (this->payload_ratio != other.payload_ratio) {
      return false;
    }
    if (this->payload_ratio_status != other.payload_ratio_status) {
      return false;
    }
    return true;
  }
  bool operator!=(const Payload_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Payload_

// alias to use template instance with default allocator
using Payload =
  cpm_common_interfaces::msg::Payload_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__STRUCT_HPP_
