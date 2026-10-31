// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/ProdMeasureSensorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/prod_measure_sensor_status.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__ProdMeasureSensorStatus __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__ProdMeasureSensorStatus __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ProdMeasureSensorStatus_
{
  using Type = ProdMeasureSensorStatus_<ContainerAllocator>;

  explicit ProdMeasureSensorStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lift_link_dc = 0.0f;
      this->lift_cyl_pos = 0.0f;
      this->lift_cyl_he_pres = 0.0f;
      this->lift_cyl_re_pres = 0.0f;
      this->tilt_sensor_config = 0;
      this->tilt_cyl_he_pres = 0.0f;
      this->tilt_cyl_re_pres = 0.0f;
      this->tilt_link_dc = 0.0f;
      this->hyd_oil_temp = 0.0f;
    }
  }

  explicit ProdMeasureSensorStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lift_link_dc = 0.0f;
      this->lift_cyl_pos = 0.0f;
      this->lift_cyl_he_pres = 0.0f;
      this->lift_cyl_re_pres = 0.0f;
      this->tilt_sensor_config = 0;
      this->tilt_cyl_he_pres = 0.0f;
      this->tilt_cyl_re_pres = 0.0f;
      this->tilt_link_dc = 0.0f;
      this->hyd_oil_temp = 0.0f;
    }
  }

  // field types and members
  using _lift_link_dc_type =
    float;
  _lift_link_dc_type lift_link_dc;
  using _lift_cyl_pos_type =
    float;
  _lift_cyl_pos_type lift_cyl_pos;
  using _lift_cyl_he_pres_type =
    float;
  _lift_cyl_he_pres_type lift_cyl_he_pres;
  using _lift_cyl_re_pres_type =
    float;
  _lift_cyl_re_pres_type lift_cyl_re_pres;
  using _tilt_sensor_config_type =
    uint16_t;
  _tilt_sensor_config_type tilt_sensor_config;
  using _tilt_cyl_he_pres_type =
    float;
  _tilt_cyl_he_pres_type tilt_cyl_he_pres;
  using _tilt_cyl_re_pres_type =
    float;
  _tilt_cyl_re_pres_type tilt_cyl_re_pres;
  using _tilt_link_dc_type =
    float;
  _tilt_link_dc_type tilt_link_dc;
  using _hyd_oil_temp_type =
    float;
  _hyd_oil_temp_type hyd_oil_temp;

  // setters for named parameter idiom
  Type & set__lift_link_dc(
    const float & _arg)
  {
    this->lift_link_dc = _arg;
    return *this;
  }
  Type & set__lift_cyl_pos(
    const float & _arg)
  {
    this->lift_cyl_pos = _arg;
    return *this;
  }
  Type & set__lift_cyl_he_pres(
    const float & _arg)
  {
    this->lift_cyl_he_pres = _arg;
    return *this;
  }
  Type & set__lift_cyl_re_pres(
    const float & _arg)
  {
    this->lift_cyl_re_pres = _arg;
    return *this;
  }
  Type & set__tilt_sensor_config(
    const uint16_t & _arg)
  {
    this->tilt_sensor_config = _arg;
    return *this;
  }
  Type & set__tilt_cyl_he_pres(
    const float & _arg)
  {
    this->tilt_cyl_he_pres = _arg;
    return *this;
  }
  Type & set__tilt_cyl_re_pres(
    const float & _arg)
  {
    this->tilt_cyl_re_pres = _arg;
    return *this;
  }
  Type & set__tilt_link_dc(
    const float & _arg)
  {
    this->tilt_link_dc = _arg;
    return *this;
  }
  Type & set__hyd_oil_temp(
    const float & _arg)
  {
    this->hyd_oil_temp = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t TILT_SENSOR_ROTARY_POSITION =
    451u;
  static constexpr uint16_t TILT_SENSOR_IN_CYLINDER_POSITION =
    452u;

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__ProdMeasureSensorStatus
    std::shared_ptr<cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__ProdMeasureSensorStatus
    std::shared_ptr<cpm_common_interfaces::msg::ProdMeasureSensorStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ProdMeasureSensorStatus_ & other) const
  {
    if (this->lift_link_dc != other.lift_link_dc) {
      return false;
    }
    if (this->lift_cyl_pos != other.lift_cyl_pos) {
      return false;
    }
    if (this->lift_cyl_he_pres != other.lift_cyl_he_pres) {
      return false;
    }
    if (this->lift_cyl_re_pres != other.lift_cyl_re_pres) {
      return false;
    }
    if (this->tilt_sensor_config != other.tilt_sensor_config) {
      return false;
    }
    if (this->tilt_cyl_he_pres != other.tilt_cyl_he_pres) {
      return false;
    }
    if (this->tilt_cyl_re_pres != other.tilt_cyl_re_pres) {
      return false;
    }
    if (this->tilt_link_dc != other.tilt_link_dc) {
      return false;
    }
    if (this->hyd_oil_temp != other.hyd_oil_temp) {
      return false;
    }
    return true;
  }
  bool operator!=(const ProdMeasureSensorStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ProdMeasureSensorStatus_

// alias to use template instance with default allocator
using ProdMeasureSensorStatus =
  cpm_common_interfaces::msg::ProdMeasureSensorStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ProdMeasureSensorStatus_<ContainerAllocator>::TILT_SENSOR_ROTARY_POSITION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ProdMeasureSensorStatus_<ContainerAllocator>::TILT_SENSOR_IN_CYLINDER_POSITION;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__STRUCT_HPP_
