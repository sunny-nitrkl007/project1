// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/ReadyToFlashStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ready_to_flash_status.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__ReadyToFlashStatus __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__ReadyToFlashStatus __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ReadyToFlashStatus_
{
  using Type = ReadyToFlashStatus_<ContainerAllocator>;

  explicit ReadyToFlashStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->task_name = "";
      this->host_name = "";
      this->ready_code = 0;
    }
  }

  explicit ReadyToFlashStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : task_name(_alloc),
    host_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->task_name = "";
      this->host_name = "";
      this->ready_code = 0;
    }
  }

  // field types and members
  using _task_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _task_name_type task_name;
  using _host_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _host_name_type host_name;
  using _ready_code_type =
    int16_t;
  _ready_code_type ready_code;

  // setters for named parameter idiom
  Type & set__task_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->task_name = _arg;
    return *this;
  }
  Type & set__host_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->host_name = _arg;
    return *this;
  }
  Type & set__ready_code(
    const int16_t & _arg)
  {
    this->ready_code = _arg;
    return *this;
  }

  // constant declarations
  static constexpr int16_t APP_READY_CODE_NOT_SET =
    -1;
  static constexpr int16_t APP_READY_CODE_OK_TO_FLASH =
    0;
  static constexpr int16_t APP_READY_CODE_ENGINE_SPEED_DETECTED =
    1;
  static constexpr int16_t APP_READY_CODE_IMPLEMENT_NOT_LOCKED =
    2;
  static constexpr int16_t APP_READY_CODE_UNABLE_TO_FLASH =
    3;
  static constexpr int16_t APP_READY_CODE_BOX_NOT_FLASHABLE =
    4;
  static constexpr int16_t APP_READY_CODE_TORQUE_CONVERTER_SPEED_DETECTED =
    5;
  static constexpr int16_t APP_READY_CODE_SYSTEM_VOLTAGE_TOO_LOW =
    6;
  static constexpr int16_t APP_READY_CODE_DIRECTION_SWITCH_NOT_IN_NEUTRAL =
    7;
  static constexpr int16_t APP_READY_CODE_PARKING_BRAKE_NOT_SET =
    8;
  static constexpr int16_t APP_READY_CODE_MODE_SWITCH_NOT_IN_STOP =
    9;
  static constexpr int16_t APP_READY_CODE_TRANSMISSION_NOT_IN_NEUTRAL =
    10;
  static constexpr int16_t APP_READY_CODE_HYDRAULIC_SYSTEM_ENABLED =
    11;
  static constexpr int16_t APP_READY_CODE_NOT_EQUIVALENT_PREMIUM_SOFTWARE =
    12;
  static constexpr int16_t APP_READY_CODE_ECM_BUSY =
    13;
  static constexpr int16_t APP_READY_CODE_DEVELOPMENT_SOFTWARE =
    14;
  static constexpr int16_t APP_READY_CODE_SUBSYSTEM_FLASH_IN_PROGRESS =
    15;
  static constexpr int16_t APP_READY_CODE_MACHINE_SPEED_DETECTED =
    16;
  static constexpr int16_t APP_READY_CODE_HIGH_VOLTAGE_SYSTEM_ENERGIZED =
    17;
  static constexpr int16_t APP_READY_CODE_CANNOT_FLASH_ON_THIS_PORT =
    18;
  static constexpr int16_t APP_READY_CODE_PAYLOAL_LEGAL_FOR_TRADE_IS_SEALED =
    22;

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__ReadyToFlashStatus
    std::shared_ptr<weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__ReadyToFlashStatus
    std::shared_ptr<weigh_app_interfaces::msg::ReadyToFlashStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ReadyToFlashStatus_ & other) const
  {
    if (this->task_name != other.task_name) {
      return false;
    }
    if (this->host_name != other.host_name) {
      return false;
    }
    if (this->ready_code != other.ready_code) {
      return false;
    }
    return true;
  }
  bool operator!=(const ReadyToFlashStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ReadyToFlashStatus_

// alias to use template instance with default allocator
using ReadyToFlashStatus =
  weigh_app_interfaces::msg::ReadyToFlashStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_NOT_SET;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_OK_TO_FLASH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_ENGINE_SPEED_DETECTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_IMPLEMENT_NOT_LOCKED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_UNABLE_TO_FLASH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_BOX_NOT_FLASHABLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_TORQUE_CONVERTER_SPEED_DETECTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_SYSTEM_VOLTAGE_TOO_LOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_DIRECTION_SWITCH_NOT_IN_NEUTRAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_PARKING_BRAKE_NOT_SET;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_MODE_SWITCH_NOT_IN_STOP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_TRANSMISSION_NOT_IN_NEUTRAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_HYDRAULIC_SYSTEM_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_NOT_EQUIVALENT_PREMIUM_SOFTWARE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_ECM_BUSY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_DEVELOPMENT_SOFTWARE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_SUBSYSTEM_FLASH_IN_PROGRESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_MACHINE_SPEED_DETECTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_HIGH_VOLTAGE_SYSTEM_ENERGIZED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_CANNOT_FLASH_ON_THIS_PORT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int16_t ReadyToFlashStatus_<ContainerAllocator>::APP_READY_CODE_PAYLOAL_LEGAL_FOR_TRADE_IS_SEALED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__STRUCT_HPP_
