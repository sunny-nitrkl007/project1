// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/AcdDiagPopUp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/acd_diag_pop_up.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_DIAG_POP_UP__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_DIAG_POP_UP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__AcdDiagPopUp __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__AcdDiagPopUp __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AcdDiagPopUp_
{
  using Type = AcdDiagPopUp_<ContainerAllocator>;

  explicit AcdDiagPopUp_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->bits = 0ul;
    }
  }

  explicit AcdDiagPopUp_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->bits = 0ul;
    }
  }

  // field types and members
  using _bits_type =
    uint32_t;
  _bits_type bits;

  // setters for named parameter idiom
  Type & set__bits(
    const uint32_t & _arg)
  {
    this->bits = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t TILT_RE_FREQ_ABNORMAL =
    8u;
  static constexpr uint8_t TILT_RE_VOLTAGE_BELOW_NORMAL =
    9u;
  static constexpr uint8_t TILT_RE_VOLTAGE_ABOVE_NORMAL =
    10u;
  static constexpr uint8_t TILT_HE_FREQ_ABNORMAL =
    11u;
  static constexpr uint8_t TILT_HE_VOLTAGE_BELOW_NORMAL =
    12u;
  static constexpr uint8_t TILT_HE_VOLTAGE_ABOVE_NORMAL =
    13u;
  static constexpr uint8_t HYDRAULIC_OIL_TEMP_BAD =
    14u;
  static constexpr uint8_t MACHINE_MODEL_NOT_SET =
    15u;
  static constexpr uint8_t PAYLOAD_SYSTEM_NOT_INSTALLED =
    16u;
  static constexpr uint8_t PAYLOAD_SYSTEM_OUT_OF_CAL =
    17u;
  static constexpr uint8_t LIFT_RE_FREQ_ABNORMAL =
    18u;
  static constexpr uint8_t LIFT_RE_VOLTAGE_BELOW_NORMAL =
    19u;
  static constexpr uint8_t LIFT_RE_VOLTAGE_ABOVE_NORMAL =
    20u;
  static constexpr uint8_t LIFT_HE_FREQ_ABNORMAL =
    21u;
  static constexpr uint8_t LIFT_HE_VOLTAGE_BELOW_NORMAL =
    22u;
  static constexpr uint8_t LIFT_HE_VOLTAGE_ABOVE_NORMAL =
    23u;
  static constexpr uint8_t LIFT_LINK_OUT_OF_CAL =
    24u;
  static constexpr uint8_t LIFT_LINK_FREQ_ABNORMAL =
    25u;
  static constexpr uint8_t LIFT_LINK_VOLTAGE_BELOW_NORMAL =
    26u;
  static constexpr uint8_t LIFT_LINK_VOLTAGE_ABOVE_NORMAL =
    27u;
  static constexpr uint8_t TILT_LINK_OUT_OF_CAL =
    28u;
  static constexpr uint8_t TILT_LINK_FREQ_ABNORMAL =
    29u;
  static constexpr uint8_t TILT_LINK_VOLTAGE_BELOW_NORMAL =
    30u;
  static constexpr uint8_t TILT_LINK_VOLTAGE_ABOVE_NORMAL =
    31u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__AcdDiagPopUp
    std::shared_ptr<cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__AcdDiagPopUp
    std::shared_ptr<cpm_common_interfaces::msg::AcdDiagPopUp_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AcdDiagPopUp_ & other) const
  {
    if (this->bits != other.bits) {
      return false;
    }
    return true;
  }
  bool operator!=(const AcdDiagPopUp_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AcdDiagPopUp_

// alias to use template instance with default allocator
using AcdDiagPopUp =
  cpm_common_interfaces::msg::AcdDiagPopUp_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::TILT_RE_FREQ_ABNORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::TILT_RE_VOLTAGE_BELOW_NORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::TILT_RE_VOLTAGE_ABOVE_NORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::TILT_HE_FREQ_ABNORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::TILT_HE_VOLTAGE_BELOW_NORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::TILT_HE_VOLTAGE_ABOVE_NORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::HYDRAULIC_OIL_TEMP_BAD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::MACHINE_MODEL_NOT_SET;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::PAYLOAD_SYSTEM_NOT_INSTALLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::PAYLOAD_SYSTEM_OUT_OF_CAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::LIFT_RE_FREQ_ABNORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::LIFT_RE_VOLTAGE_BELOW_NORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::LIFT_RE_VOLTAGE_ABOVE_NORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::LIFT_HE_FREQ_ABNORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::LIFT_HE_VOLTAGE_BELOW_NORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::LIFT_HE_VOLTAGE_ABOVE_NORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::LIFT_LINK_OUT_OF_CAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::LIFT_LINK_FREQ_ABNORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::LIFT_LINK_VOLTAGE_BELOW_NORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::LIFT_LINK_VOLTAGE_ABOVE_NORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::TILT_LINK_OUT_OF_CAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::TILT_LINK_FREQ_ABNORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::TILT_LINK_VOLTAGE_BELOW_NORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AcdDiagPopUp_<ContainerAllocator>::TILT_LINK_VOLTAGE_ABOVE_NORMAL;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_DIAG_POP_UP__STRUCT_HPP_
