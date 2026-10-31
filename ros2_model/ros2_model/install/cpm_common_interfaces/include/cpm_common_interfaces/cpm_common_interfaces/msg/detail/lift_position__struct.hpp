// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LiftPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lift_position.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LiftPosition __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LiftPosition __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LiftPosition_
{
  using Type = LiftPosition_<ContainerAllocator>;

  explicit LiftPosition_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->angle = 0.0f;
      this->percent_angle = 0.0f;
      this->cylinder_length = 0.0f;
      this->percent_cylinder_length = 0.0f;
      this->cylinder_extension = 0.0f;
      this->status = 0l;
    }
  }

  explicit LiftPosition_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->angle = 0.0f;
      this->percent_angle = 0.0f;
      this->cylinder_length = 0.0f;
      this->percent_cylinder_length = 0.0f;
      this->cylinder_extension = 0.0f;
      this->status = 0l;
    }
  }

  // field types and members
  using _angle_type =
    float;
  _angle_type angle;
  using _percent_angle_type =
    float;
  _percent_angle_type percent_angle;
  using _cylinder_length_type =
    float;
  _cylinder_length_type cylinder_length;
  using _percent_cylinder_length_type =
    float;
  _percent_cylinder_length_type percent_cylinder_length;
  using _cylinder_extension_type =
    float;
  _cylinder_extension_type cylinder_extension;
  using _status_type =
    int32_t;
  _status_type status;

  // setters for named parameter idiom
  Type & set__angle(
    const float & _arg)
  {
    this->angle = _arg;
    return *this;
  }
  Type & set__percent_angle(
    const float & _arg)
  {
    this->percent_angle = _arg;
    return *this;
  }
  Type & set__cylinder_length(
    const float & _arg)
  {
    this->cylinder_length = _arg;
    return *this;
  }
  Type & set__percent_cylinder_length(
    const float & _arg)
  {
    this->percent_cylinder_length = _arg;
    return *this;
  }
  Type & set__cylinder_extension(
    const float & _arg)
  {
    this->cylinder_extension = _arg;
    return *this;
  }
  Type & set__status(
    const int32_t & _arg)
  {
    this->status = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LiftPosition
    std::shared_ptr<cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LiftPosition
    std::shared_ptr<cpm_common_interfaces::msg::LiftPosition_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LiftPosition_ & other) const
  {
    if (this->angle != other.angle) {
      return false;
    }
    if (this->percent_angle != other.percent_angle) {
      return false;
    }
    if (this->cylinder_length != other.cylinder_length) {
      return false;
    }
    if (this->percent_cylinder_length != other.percent_cylinder_length) {
      return false;
    }
    if (this->cylinder_extension != other.cylinder_extension) {
      return false;
    }
    if (this->status != other.status) {
      return false;
    }
    return true;
  }
  bool operator!=(const LiftPosition_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LiftPosition_

// alias to use template instance with default allocator
using LiftPosition =
  cpm_common_interfaces::msg::LiftPosition_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__STRUCT_HPP_
