// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/TruckReport.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/truck_report.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_REPORT__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_REPORT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__TruckReport __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__TruckReport __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TruckReport_
{
  using Type = TruckReport_<ContainerAllocator>;

  explicit TruckReport_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->reset_time_enabled = false;
    }
  }

  explicit TruckReport_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->reset_time_enabled = false;
    }
  }

  // field types and members
  using _reset_time_enabled_type =
    bool;
  _reset_time_enabled_type reset_time_enabled;

  // setters for named parameter idiom
  Type & set__reset_time_enabled(
    const bool & _arg)
  {
    this->reset_time_enabled = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::TruckReport_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::TruckReport_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::TruckReport_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::TruckReport_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::TruckReport_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::TruckReport_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::TruckReport_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::TruckReport_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::TruckReport_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::TruckReport_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__TruckReport
    std::shared_ptr<weigh_app_interfaces::msg::TruckReport_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__TruckReport
    std::shared_ptr<weigh_app_interfaces::msg::TruckReport_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TruckReport_ & other) const
  {
    if (this->reset_time_enabled != other.reset_time_enabled) {
      return false;
    }
    return true;
  }
  bool operator!=(const TruckReport_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TruckReport_

// alias to use template instance with default allocator
using TruckReport =
  weigh_app_interfaces::msg::TruckReport_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_REPORT__STRUCT_HPP_
