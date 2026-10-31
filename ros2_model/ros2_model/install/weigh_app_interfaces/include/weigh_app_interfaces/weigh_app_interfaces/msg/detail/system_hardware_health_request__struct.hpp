// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/SystemHardwareHealthRequest.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/system_hardware_health_request.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_REQUEST__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_REQUEST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__SystemHardwareHealthRequest __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__SystemHardwareHealthRequest __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SystemHardwareHealthRequest_
{
  using Type = SystemHardwareHealthRequest_<ContainerAllocator>;

  explicit SystemHardwareHealthRequest_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit SystemHardwareHealthRequest_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__SystemHardwareHealthRequest
    std::shared_ptr<weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__SystemHardwareHealthRequest
    std::shared_ptr<weigh_app_interfaces::msg::SystemHardwareHealthRequest_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SystemHardwareHealthRequest_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const SystemHardwareHealthRequest_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SystemHardwareHealthRequest_

// alias to use template instance with default allocator
using SystemHardwareHealthRequest =
  weigh_app_interfaces::msg::SystemHardwareHealthRequest_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_REQUEST__STRUCT_HPP_
