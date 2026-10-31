// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/WeighRange.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/weigh_range.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_RANGE__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_RANGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__WeighRange __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__WeighRange __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WeighRange_
{
  using Type = WeighRange_<ContainerAllocator>;

  explicit WeighRange_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->weigh_range_bottom = 0.0f;
      this->weigh_range_size = 0.0f;
    }
  }

  explicit WeighRange_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->weigh_range_bottom = 0.0f;
      this->weigh_range_size = 0.0f;
    }
  }

  // field types and members
  using _weigh_range_bottom_type =
    float;
  _weigh_range_bottom_type weigh_range_bottom;
  using _weigh_range_size_type =
    float;
  _weigh_range_size_type weigh_range_size;

  // setters for named parameter idiom
  Type & set__weigh_range_bottom(
    const float & _arg)
  {
    this->weigh_range_bottom = _arg;
    return *this;
  }
  Type & set__weigh_range_size(
    const float & _arg)
  {
    this->weigh_range_size = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::WeighRange_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::WeighRange_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::WeighRange_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::WeighRange_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::WeighRange_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::WeighRange_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::WeighRange_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::WeighRange_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::WeighRange_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::WeighRange_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__WeighRange
    std::shared_ptr<cpm_common_interfaces::msg::WeighRange_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__WeighRange
    std::shared_ptr<cpm_common_interfaces::msg::WeighRange_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WeighRange_ & other) const
  {
    if (this->weigh_range_bottom != other.weigh_range_bottom) {
      return false;
    }
    if (this->weigh_range_size != other.weigh_range_size) {
      return false;
    }
    return true;
  }
  bool operator!=(const WeighRange_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WeighRange_

// alias to use template instance with default allocator
using WeighRange =
  cpm_common_interfaces::msg::WeighRange_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_RANGE__STRUCT_HPP_
