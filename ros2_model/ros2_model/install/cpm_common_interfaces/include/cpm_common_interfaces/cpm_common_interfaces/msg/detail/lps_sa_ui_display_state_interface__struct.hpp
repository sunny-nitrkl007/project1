// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaUIDisplayStateInterface.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_ui_display_state_interface.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE_INTERFACE__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE_INTERFACE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'state'
#include "cpm_common_interfaces/msg/detail/lps_sa_ui_display_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplayStateInterface __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplayStateInterface __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaUIDisplayStateInterface_
{
  using Type = LpsSaUIDisplayStateInterface_<ContainerAllocator>;

  explicit LpsSaUIDisplayStateInterface_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : state(_init)
  {
    (void)_init;
  }

  explicit LpsSaUIDisplayStateInterface_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : state(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _state_type =
    cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator>;
  _state_type state;

  // setters for named parameter idiom
  Type & set__state(
    const cpm_common_interfaces::msg::LpsSaUIDisplayState_<ContainerAllocator> & _arg)
  {
    this->state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplayStateInterface
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaUIDisplayStateInterface
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaUIDisplayStateInterface_ & other) const
  {
    if (this->state != other.state) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaUIDisplayStateInterface_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaUIDisplayStateInterface_

// alias to use template instance with default allocator
using LpsSaUIDisplayStateInterface =
  cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE_INTERFACE__STRUCT_HPP_
