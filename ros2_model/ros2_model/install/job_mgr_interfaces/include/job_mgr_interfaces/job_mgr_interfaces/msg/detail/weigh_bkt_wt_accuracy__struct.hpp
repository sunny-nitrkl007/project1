// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/WeighBktWtAccuracy.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/weigh_bkt_wt_accuracy.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__WeighBktWtAccuracy __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__WeighBktWtAccuracy __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WeighBktWtAccuracy_
{
  using Type = WeighBktWtAccuracy_<ContainerAllocator>;

  explicit WeighBktWtAccuracy_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  explicit WeighBktWtAccuracy_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  // field types and members
  using _value_type =
    uint8_t;
  _value_type value;

  // setters for named parameter idiom
  Type & set__value(
    const uint8_t & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t NONE =
    0u;
  static constexpr uint8_t LOW =
    1u;
  static constexpr uint8_t MED =
    2u;
  static constexpr uint8_t HIGH =
    3u;

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__WeighBktWtAccuracy
    std::shared_ptr<job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__WeighBktWtAccuracy
    std::shared_ptr<job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WeighBktWtAccuracy_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const WeighBktWtAccuracy_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WeighBktWtAccuracy_

// alias to use template instance with default allocator
using WeighBktWtAccuracy =
  job_mgr_interfaces::msg::WeighBktWtAccuracy_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighBktWtAccuracy_<ContainerAllocator>::NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighBktWtAccuracy_<ContainerAllocator>::LOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighBktWtAccuracy_<ContainerAllocator>::MED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighBktWtAccuracy_<ContainerAllocator>::HIGH;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__STRUCT_HPP_
