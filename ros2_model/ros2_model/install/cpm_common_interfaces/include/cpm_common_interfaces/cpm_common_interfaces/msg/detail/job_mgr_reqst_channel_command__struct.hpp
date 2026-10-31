// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/JobMgrReqstChannelCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/job_mgr_reqst_channel_command.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__JobMgrReqstChannelCommand __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__JobMgrReqstChannelCommand __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct JobMgrReqstChannelCommand_
{
  using Type = JobMgrReqstChannelCommand_<ContainerAllocator>;

  explicit JobMgrReqstChannelCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  explicit JobMgrReqstChannelCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
  static constexpr uint8_t ZERO =
    1u;
  static constexpr uint8_t MINUS_ONE =
    2u;
  static constexpr uint8_t CLEAR =
    3u;
  static constexpr uint8_t STORE =
    4u;
  static constexpr uint8_t REWEIGH =
    5u;
  static constexpr uint8_t MANUAL_ADD =
    6u;
  static constexpr uint8_t STANDBY_ACTIVATE =
    7u;
  static constexpr uint8_t STANDBY_DEACTIVATE =
    8u;
  static constexpr uint8_t TIPOFF_MODE_TOGGLE =
    9u;
  static constexpr uint8_t MANUAL_TIPOFF_ACTIVATE =
    10u;
  static constexpr uint8_t MANUAL_TIPOFF_DEACTIVATE =
    11u;
  static constexpr uint8_t WRITE_TIPOFF_TRIGGER_TYPE =
    12u;
  static constexpr uint8_t WRITE_TIPOFF_MODE =
    13u;
  static constexpr uint8_t WRITE_HORN_ON_STORE_ENABLED =
    14u;
  static constexpr uint8_t WRITE_AUTO_STORE_PASS_COUNT =
    15u;
  static constexpr uint8_t WRITE_AUTO_TRUCK_ID_ENABLED =
    16u;
  static constexpr uint8_t WRITE_AUTO_MATERIAL_ID_ENABLED =
    17u;
  static constexpr uint8_t WRITE_MANUAL_ADD_ENABLED =
    18u;
  static constexpr uint8_t WRITE_MULTI_TASK_ENABLED =
    19u;
  static constexpr uint8_t WRITE_MULTI_TASK_COUNT =
    20u;
  static constexpr uint8_t WRITE_SPLIT_MODE_ENABLED =
    21u;
  static constexpr uint8_t SELECT_TASK =
    22u;
  static constexpr uint8_t SELECT_NEXT_TASK =
    23u;
  static constexpr uint8_t SELECT_PREVIOUS_TASK =
    24u;
  static constexpr uint8_t WRITE_TRUCK_LIST_ENABLED =
    25u;
  static constexpr uint8_t WRITE_MATERIAL_LIST_ENABLED =
    26u;
  static constexpr uint8_t WRITE_TAG1_ENABLED =
    27u;
  static constexpr uint8_t WRITE_TAG2_ENABLED =
    28u;
  static constexpr uint8_t WRITE_TAG3_ENABLED =
    29u;
  static constexpr uint8_t WRITE_TAG4_ENABLED =
    30u;
  static constexpr uint8_t WRITE_PAYLOAD_NEXT_SUBTOTAL =
    31u;
  static constexpr uint8_t WRITE_LFT_DISABLED =
    32u;
  static constexpr uint8_t WRITE_TARGET_TYPE =
    33u;
  static constexpr uint8_t WRITE_TOTAL_TARGET_WEIGHT =
    34u;
  static constexpr uint8_t SELECT_SUBTOTAL =
    35u;
  static constexpr uint8_t PAYLOAD_DETAILS_FILE_REQUEST =
    36u;
  static constexpr uint8_t WRITE_SUBTOTAL_INFO =
    37u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__JobMgrReqstChannelCommand
    std::shared_ptr<cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__JobMgrReqstChannelCommand
    std::shared_ptr<cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const JobMgrReqstChannelCommand_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const JobMgrReqstChannelCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct JobMgrReqstChannelCommand_

// alias to use template instance with default allocator
using JobMgrReqstChannelCommand =
  cpm_common_interfaces::msg::JobMgrReqstChannelCommand_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::ZERO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::MINUS_ONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::CLEAR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::STORE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::REWEIGH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::MANUAL_ADD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::STANDBY_ACTIVATE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::STANDBY_DEACTIVATE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::TIPOFF_MODE_TOGGLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::MANUAL_TIPOFF_ACTIVATE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::MANUAL_TIPOFF_DEACTIVATE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_TIPOFF_TRIGGER_TYPE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_TIPOFF_MODE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_HORN_ON_STORE_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_AUTO_STORE_PASS_COUNT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_AUTO_TRUCK_ID_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_AUTO_MATERIAL_ID_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_MANUAL_ADD_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_MULTI_TASK_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_MULTI_TASK_COUNT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_SPLIT_MODE_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::SELECT_TASK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::SELECT_NEXT_TASK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::SELECT_PREVIOUS_TASK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_TRUCK_LIST_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_MATERIAL_LIST_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_TAG1_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_TAG2_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_TAG3_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_TAG4_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_PAYLOAD_NEXT_SUBTOTAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_LFT_DISABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_TARGET_TYPE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_TOTAL_TARGET_WEIGHT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::SELECT_SUBTOTAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::PAYLOAD_DETAILS_FILE_REQUEST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t JobMgrReqstChannelCommand_<ContainerAllocator>::WRITE_SUBTOTAL_INFO;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__STRUCT_HPP_
