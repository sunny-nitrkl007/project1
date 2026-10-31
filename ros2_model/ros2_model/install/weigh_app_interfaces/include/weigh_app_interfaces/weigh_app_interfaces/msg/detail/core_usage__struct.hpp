// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/CoreUsage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/core_usage.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__CoreUsage __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__CoreUsage __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CoreUsage_
{
  using Type = CoreUsage_<ContainerAllocator>;

  explicit CoreUsage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cpu_usage_percent = 0.0;
      this->cpu_io_wait_percent = 0.0;
      this->cpu_irq_percent = 0.0;
    }
  }

  explicit CoreUsage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cpu_usage_percent = 0.0;
      this->cpu_io_wait_percent = 0.0;
      this->cpu_irq_percent = 0.0;
    }
  }

  // field types and members
  using _cpu_usage_percent_type =
    double;
  _cpu_usage_percent_type cpu_usage_percent;
  using _cpu_io_wait_percent_type =
    double;
  _cpu_io_wait_percent_type cpu_io_wait_percent;
  using _cpu_irq_percent_type =
    double;
  _cpu_irq_percent_type cpu_irq_percent;

  // setters for named parameter idiom
  Type & set__cpu_usage_percent(
    const double & _arg)
  {
    this->cpu_usage_percent = _arg;
    return *this;
  }
  Type & set__cpu_io_wait_percent(
    const double & _arg)
  {
    this->cpu_io_wait_percent = _arg;
    return *this;
  }
  Type & set__cpu_irq_percent(
    const double & _arg)
  {
    this->cpu_irq_percent = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__CoreUsage
    std::shared_ptr<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__CoreUsage
    std::shared_ptr<weigh_app_interfaces::msg::CoreUsage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CoreUsage_ & other) const
  {
    if (this->cpu_usage_percent != other.cpu_usage_percent) {
      return false;
    }
    if (this->cpu_io_wait_percent != other.cpu_io_wait_percent) {
      return false;
    }
    if (this->cpu_irq_percent != other.cpu_irq_percent) {
      return false;
    }
    return true;
  }
  bool operator!=(const CoreUsage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CoreUsage_

// alias to use template instance with default allocator
using CoreUsage =
  weigh_app_interfaces::msg::CoreUsage_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__STRUCT_HPP_
