// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/WeighReqstChannelCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/weigh_reqst_channel_command.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_REQST_CHANNEL_COMMAND__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_REQST_CHANNEL_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__WeighReqstChannelCommand __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__WeighReqstChannelCommand __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WeighReqstChannelCommand_
{
  using Type = WeighReqstChannelCommand_<ContainerAllocator>;

  explicit WeighReqstChannelCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  explicit WeighReqstChannelCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
  static constexpr uint8_t WRITE_OVERLOAD_WARNING_ENABLE =
    1u;
  static constexpr uint8_t WRITE_BUCKET_PAYLOAD_TARGET_WEIGHT =
    2u;
  static constexpr uint8_t ZERO =
    3u;
  static constexpr uint8_t RESET_BEST_BUCKET_WEIGHT =
    4u;
  static constexpr uint8_t CAPTURE_CYLINDER_EXTENSION_REFERENCE =
    5u;
  static constexpr uint8_t CLEAR_REWEIGH_WARNING =
    6u;
  static constexpr uint8_t WRITE_WEIGH_RANGE =
    7u;
  static constexpr uint8_t WRITE_CALIBRATION_WEIGHT =
    8u;
  static constexpr uint8_t WRITE_MACHINE_PITCH_CAL_OFFSET =
    9u;
  static constexpr uint8_t WRITE_HYD_OIL_TEMP_ENABLE =
    10u;
  static constexpr uint8_t WRITE_AUDIBLE_WEIGHT_ENABLE =
    11u;
  static constexpr uint8_t WRITE_LFT_SEALED =
    12u;
  static constexpr uint8_t WRITE_LFT_SEALED_FLASH_ENABLE =
    13u;
  static constexpr uint8_t WRITE_LIFT_POSITION_SENSOR_ID =
    14u;
  static constexpr uint8_t WRITE_TILT_POSITION_SENSOR_ID =
    15u;
  static constexpr uint8_t WRITE_LIFT_HE_PRESSURE_SENSOR_ID =
    16u;
  static constexpr uint8_t WRITE_LIFT_RE_PRESSURE_SENSOR_ID =
    17u;
  static constexpr uint8_t WRITE_HYDRAULIC_OIL_TEMP_SENSOR_ID =
    18u;
  static constexpr uint8_t WRITE_PAYLOAD_OUT_OF_CAL =
    19u;
  static constexpr uint8_t NOTIFY_TICKET_NUMBER_WRITE =
    20u;
  static constexpr uint8_t PUBLISH_SERVICE_HISTORY =
    21u;
  static constexpr uint8_t WRITE_WORK_TOOL_ID =
    22u;
  static constexpr uint8_t PUBLISH_LIFT_SENSOR_CALIBRATION =
    23u;
  static constexpr uint8_t PUBLISH_TILT_SENSOR_CALIBRATION =
    24u;
  static constexpr uint8_t PUBLISH_WEIGH_CALIBRATION =
    25u;
  static constexpr uint8_t PUBLISH_WEIGH_CONFIGURATION =
    26u;
  static constexpr uint8_t PUBLISH_RECENT_WEIGH_RESULTS =
    27u;
  static constexpr uint8_t WRITE_REWEIGH_MAX_PITCH =
    28u;
  static constexpr uint8_t WRITE_REWEIGH_MIN_PITCH =
    29u;
  static constexpr uint8_t WRITE_REWEIGH_MAX_ABS_ROLL =
    30u;
  static constexpr uint8_t WRITE_REWEIGH_MIN_LIFT_CYL_VEL =
    31u;
  static constexpr uint8_t WRITE_ADVANCED_CALIBRATION_ADJUSTMENT =
    32u;
  static constexpr uint8_t RUN_TEST =
    33u;
  static constexpr uint8_t RECORD_TEST =
    34u;
  static constexpr uint8_t WRITE_IMU_COMP_ENABLE =
    35u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__WeighReqstChannelCommand
    std::shared_ptr<cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__WeighReqstChannelCommand
    std::shared_ptr<cpm_common_interfaces::msg::WeighReqstChannelCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WeighReqstChannelCommand_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const WeighReqstChannelCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WeighReqstChannelCommand_

// alias to use template instance with default allocator
using WeighReqstChannelCommand =
  cpm_common_interfaces::msg::WeighReqstChannelCommand_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_OVERLOAD_WARNING_ENABLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_BUCKET_PAYLOAD_TARGET_WEIGHT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::ZERO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::RESET_BEST_BUCKET_WEIGHT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::CAPTURE_CYLINDER_EXTENSION_REFERENCE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::CLEAR_REWEIGH_WARNING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_WEIGH_RANGE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_CALIBRATION_WEIGHT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_MACHINE_PITCH_CAL_OFFSET;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_HYD_OIL_TEMP_ENABLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_AUDIBLE_WEIGHT_ENABLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_LFT_SEALED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_LFT_SEALED_FLASH_ENABLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_LIFT_POSITION_SENSOR_ID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_TILT_POSITION_SENSOR_ID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_LIFT_HE_PRESSURE_SENSOR_ID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_LIFT_RE_PRESSURE_SENSOR_ID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_HYDRAULIC_OIL_TEMP_SENSOR_ID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_PAYLOAD_OUT_OF_CAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::NOTIFY_TICKET_NUMBER_WRITE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::PUBLISH_SERVICE_HISTORY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_WORK_TOOL_ID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::PUBLISH_LIFT_SENSOR_CALIBRATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::PUBLISH_TILT_SENSOR_CALIBRATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::PUBLISH_WEIGH_CALIBRATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::PUBLISH_WEIGH_CONFIGURATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::PUBLISH_RECENT_WEIGH_RESULTS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_REWEIGH_MAX_PITCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_REWEIGH_MIN_PITCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_REWEIGH_MAX_ABS_ROLL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_REWEIGH_MIN_LIFT_CYL_VEL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_ADVANCED_CALIBRATION_ADJUSTMENT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::RUN_TEST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::RECORD_TEST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t WeighReqstChannelCommand_<ContainerAllocator>::WRITE_IMU_COMP_ENABLE;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_REQST_CHANNEL_COMMAND__STRUCT_HPP_
