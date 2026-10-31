// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrReqst.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_reqst.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrReqst __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrReqst __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaJobMgrReqst_
{
  using Type = LpsSaJobMgrReqst_<ContainerAllocator>;

  explicit LpsSaJobMgrReqst_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = 0;
      this->arg1 = "";
      this->arg2 = 0.0f;
      this->arg3 = 0ul;
      this->arg4 = "";
    }
  }

  explicit LpsSaJobMgrReqst_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : arg1(_alloc),
    arg4(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = 0;
      this->arg1 = "";
      this->arg2 = 0.0f;
      this->arg3 = 0ul;
      this->arg4 = "";
    }
  }

  // field types and members
  using _command_type =
    uint8_t;
  _command_type command;
  using _arg1_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _arg1_type arg1;
  using _arg2_type =
    float;
  _arg2_type arg2;
  using _arg3_type =
    uint32_t;
  _arg3_type arg3;
  using _arg4_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _arg4_type arg4;

  // setters for named parameter idiom
  Type & set__command(
    const uint8_t & _arg)
  {
    this->command = _arg;
    return *this;
  }
  Type & set__arg1(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->arg1 = _arg;
    return *this;
  }
  Type & set__arg2(
    const float & _arg)
  {
    this->arg2 = _arg;
    return *this;
  }
  Type & set__arg3(
    const uint32_t & _arg)
  {
    this->arg3 = _arg;
    return *this;
  }
  Type & set__arg4(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->arg4 = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t WRITE_MATERIAL_ID =
    0u;
  static constexpr uint8_t WRITE_MATERIAL_NAME =
    1u;
  static constexpr uint8_t WRITE_MATERIAL_DENSITY =
    2u;
  static constexpr uint8_t WRITE_TRUCK_ID =
    3u;
  static constexpr uint8_t WRITE_TRUCK_NAME =
    4u;
  static constexpr uint8_t WRITE_TRUCK_TARGET_WEIGHT =
    5u;
  static constexpr uint8_t WRITE_TAG1 =
    6u;
  static constexpr uint8_t WRITE_TAG2 =
    7u;
  static constexpr uint8_t WRITE_TAG3 =
    8u;
  static constexpr uint8_t WRITE_TAG4 =
    9u;
  static constexpr uint8_t NONE =
    10u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrReqst
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LpsSaJobMgrReqst
    std::shared_ptr<cpm_common_interfaces::msg::LpsSaJobMgrReqst_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaJobMgrReqst_ & other) const
  {
    if (this->command != other.command) {
      return false;
    }
    if (this->arg1 != other.arg1) {
      return false;
    }
    if (this->arg2 != other.arg2) {
      return false;
    }
    if (this->arg3 != other.arg3) {
      return false;
    }
    if (this->arg4 != other.arg4) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaJobMgrReqst_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaJobMgrReqst_

// alias to use template instance with default allocator
using LpsSaJobMgrReqst =
  cpm_common_interfaces::msg::LpsSaJobMgrReqst_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrReqst_<ContainerAllocator>::WRITE_MATERIAL_ID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrReqst_<ContainerAllocator>::WRITE_MATERIAL_NAME;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrReqst_<ContainerAllocator>::WRITE_MATERIAL_DENSITY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrReqst_<ContainerAllocator>::WRITE_TRUCK_ID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrReqst_<ContainerAllocator>::WRITE_TRUCK_NAME;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrReqst_<ContainerAllocator>::WRITE_TRUCK_TARGET_WEIGHT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrReqst_<ContainerAllocator>::WRITE_TAG1;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrReqst_<ContainerAllocator>::WRITE_TAG2;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrReqst_<ContainerAllocator>::WRITE_TAG3;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrReqst_<ContainerAllocator>::WRITE_TAG4;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrReqst_<ContainerAllocator>::NONE;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__STRUCT_HPP_
