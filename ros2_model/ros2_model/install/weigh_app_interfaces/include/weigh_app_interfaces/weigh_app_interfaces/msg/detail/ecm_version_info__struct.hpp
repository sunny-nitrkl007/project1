// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/EcmVersionInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ecm_version_info.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__EcmVersionInfo __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__EcmVersionInfo __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EcmVersionInfo_
{
  using Type = EcmVersionInfo_<ContainerAllocator>;

  explicit EcmVersionInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->serial_num = "";
      this->part_num = "";
      this->dom = "";
      this->mac0 = "";
      this->mac1 = "";
    }
  }

  explicit EcmVersionInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : serial_num(_alloc),
    part_num(_alloc),
    dom(_alloc),
    mac0(_alloc),
    mac1(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->serial_num = "";
      this->part_num = "";
      this->dom = "";
      this->mac0 = "";
      this->mac1 = "";
    }
  }

  // field types and members
  using _serial_num_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _serial_num_type serial_num;
  using _part_num_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _part_num_type part_num;
  using _dom_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _dom_type dom;
  using _mac0_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mac0_type mac0;
  using _mac1_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mac1_type mac1;

  // setters for named parameter idiom
  Type & set__serial_num(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->serial_num = _arg;
    return *this;
  }
  Type & set__part_num(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->part_num = _arg;
    return *this;
  }
  Type & set__dom(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->dom = _arg;
    return *this;
  }
  Type & set__mac0(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mac0 = _arg;
    return *this;
  }
  Type & set__mac1(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mac1 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__EcmVersionInfo
    std::shared_ptr<weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__EcmVersionInfo
    std::shared_ptr<weigh_app_interfaces::msg::EcmVersionInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EcmVersionInfo_ & other) const
  {
    if (this->serial_num != other.serial_num) {
      return false;
    }
    if (this->part_num != other.part_num) {
      return false;
    }
    if (this->dom != other.dom) {
      return false;
    }
    if (this->mac0 != other.mac0) {
      return false;
    }
    if (this->mac1 != other.mac1) {
      return false;
    }
    return true;
  }
  bool operator!=(const EcmVersionInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EcmVersionInfo_

// alias to use template instance with default allocator
using EcmVersionInfo =
  weigh_app_interfaces::msg::EcmVersionInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__STRUCT_HPP_
