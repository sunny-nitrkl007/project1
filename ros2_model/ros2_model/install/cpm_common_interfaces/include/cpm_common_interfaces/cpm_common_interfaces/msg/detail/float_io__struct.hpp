// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/FloatIO.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/float_io.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_IO__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_IO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__FloatIO __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__FloatIO __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct FloatIO_
{
  using Type = FloatIO_<ContainerAllocator>;

  explicit FloatIO_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stat = 0l;
      this->val = 0.0f;
    }
  }

  explicit FloatIO_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stat = 0l;
      this->val = 0.0f;
    }
  }

  // field types and members
  using _stat_type =
    int32_t;
  _stat_type stat;
  using _val_type =
    float;
  _val_type val;

  // setters for named parameter idiom
  Type & set__stat(
    const int32_t & _arg)
  {
    this->stat = _arg;
    return *this;
  }
  Type & set__val(
    const float & _arg)
  {
    this->val = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::FloatIO_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::FloatIO_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::FloatIO_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::FloatIO_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::FloatIO_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::FloatIO_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::FloatIO_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::FloatIO_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::FloatIO_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::FloatIO_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__FloatIO
    std::shared_ptr<cpm_common_interfaces::msg::FloatIO_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__FloatIO
    std::shared_ptr<cpm_common_interfaces::msg::FloatIO_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const FloatIO_ & other) const
  {
    if (this->stat != other.stat) {
      return false;
    }
    if (this->val != other.val) {
      return false;
    }
    return true;
  }
  bool operator!=(const FloatIO_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct FloatIO_

// alias to use template instance with default allocator
using FloatIO =
  cpm_common_interfaces::msg::FloatIO_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_IO__STRUCT_HPP_
