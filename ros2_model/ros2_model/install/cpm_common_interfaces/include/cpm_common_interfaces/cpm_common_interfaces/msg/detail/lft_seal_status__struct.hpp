// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LftSealStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lft_seal_status.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LftSealStatus __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LftSealStatus __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LftSealStatus_
{
  using Type = LftSealStatus_<ContainerAllocator>;

  explicit LftSealStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sealed = false;
      this->seal_time_ns = 0ll;
      this->seal_id = 0ul;
    }
  }

  explicit LftSealStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sealed = false;
      this->seal_time_ns = 0ll;
      this->seal_id = 0ul;
    }
  }

  // field types and members
  using _sealed_type =
    bool;
  _sealed_type sealed;
  using _seal_time_ns_type =
    int64_t;
  _seal_time_ns_type seal_time_ns;
  using _seal_id_type =
    uint32_t;
  _seal_id_type seal_id;

  // setters for named parameter idiom
  Type & set__sealed(
    const bool & _arg)
  {
    this->sealed = _arg;
    return *this;
  }
  Type & set__seal_time_ns(
    const int64_t & _arg)
  {
    this->seal_time_ns = _arg;
    return *this;
  }
  Type & set__seal_id(
    const uint32_t & _arg)
  {
    this->seal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LftSealStatus
    std::shared_ptr<cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LftSealStatus
    std::shared_ptr<cpm_common_interfaces::msg::LftSealStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LftSealStatus_ & other) const
  {
    if (this->sealed != other.sealed) {
      return false;
    }
    if (this->seal_time_ns != other.seal_time_ns) {
      return false;
    }
    if (this->seal_id != other.seal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const LftSealStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LftSealStatus_

// alias to use template instance with default allocator
using LftSealStatus =
  cpm_common_interfaces::msg::LftSealStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__STRUCT_HPP_
