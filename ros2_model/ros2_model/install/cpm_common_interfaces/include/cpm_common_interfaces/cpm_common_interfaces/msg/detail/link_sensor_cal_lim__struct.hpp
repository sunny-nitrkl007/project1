// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/LinkSensorCalLim.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/link_sensor_cal_lim.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__LinkSensorCalLim __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__LinkSensorCalLim __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LinkSensorCalLim_
{
  using Type = LinkSensorCalLim_<ContainerAllocator>;

  explicit LinkSensorCalLim_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lift_pos_sensor_dc = 0.0f;
      this->lift_pos_sensor_full_raise_dc = 0.0f;
      this->lift_pos_sensor_full_lower_dc = 0.0f;
      this->tilt_pos_sensor_dc = 0.0f;
      this->tilt_pos_sensor_full_rack_dc = 0.0f;
      this->tilt_pos_sensor_full_dump_dc = 0.0f;
    }
  }

  explicit LinkSensorCalLim_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lift_pos_sensor_dc = 0.0f;
      this->lift_pos_sensor_full_raise_dc = 0.0f;
      this->lift_pos_sensor_full_lower_dc = 0.0f;
      this->tilt_pos_sensor_dc = 0.0f;
      this->tilt_pos_sensor_full_rack_dc = 0.0f;
      this->tilt_pos_sensor_full_dump_dc = 0.0f;
    }
  }

  // field types and members
  using _lift_pos_sensor_dc_type =
    float;
  _lift_pos_sensor_dc_type lift_pos_sensor_dc;
  using _lift_pos_sensor_full_raise_dc_type =
    float;
  _lift_pos_sensor_full_raise_dc_type lift_pos_sensor_full_raise_dc;
  using _lift_pos_sensor_full_lower_dc_type =
    float;
  _lift_pos_sensor_full_lower_dc_type lift_pos_sensor_full_lower_dc;
  using _tilt_pos_sensor_dc_type =
    float;
  _tilt_pos_sensor_dc_type tilt_pos_sensor_dc;
  using _tilt_pos_sensor_full_rack_dc_type =
    float;
  _tilt_pos_sensor_full_rack_dc_type tilt_pos_sensor_full_rack_dc;
  using _tilt_pos_sensor_full_dump_dc_type =
    float;
  _tilt_pos_sensor_full_dump_dc_type tilt_pos_sensor_full_dump_dc;

  // setters for named parameter idiom
  Type & set__lift_pos_sensor_dc(
    const float & _arg)
  {
    this->lift_pos_sensor_dc = _arg;
    return *this;
  }
  Type & set__lift_pos_sensor_full_raise_dc(
    const float & _arg)
  {
    this->lift_pos_sensor_full_raise_dc = _arg;
    return *this;
  }
  Type & set__lift_pos_sensor_full_lower_dc(
    const float & _arg)
  {
    this->lift_pos_sensor_full_lower_dc = _arg;
    return *this;
  }
  Type & set__tilt_pos_sensor_dc(
    const float & _arg)
  {
    this->tilt_pos_sensor_dc = _arg;
    return *this;
  }
  Type & set__tilt_pos_sensor_full_rack_dc(
    const float & _arg)
  {
    this->tilt_pos_sensor_full_rack_dc = _arg;
    return *this;
  }
  Type & set__tilt_pos_sensor_full_dump_dc(
    const float & _arg)
  {
    this->tilt_pos_sensor_full_dump_dc = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__LinkSensorCalLim
    std::shared_ptr<cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__LinkSensorCalLim
    std::shared_ptr<cpm_common_interfaces::msg::LinkSensorCalLim_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LinkSensorCalLim_ & other) const
  {
    if (this->lift_pos_sensor_dc != other.lift_pos_sensor_dc) {
      return false;
    }
    if (this->lift_pos_sensor_full_raise_dc != other.lift_pos_sensor_full_raise_dc) {
      return false;
    }
    if (this->lift_pos_sensor_full_lower_dc != other.lift_pos_sensor_full_lower_dc) {
      return false;
    }
    if (this->tilt_pos_sensor_dc != other.tilt_pos_sensor_dc) {
      return false;
    }
    if (this->tilt_pos_sensor_full_rack_dc != other.tilt_pos_sensor_full_rack_dc) {
      return false;
    }
    if (this->tilt_pos_sensor_full_dump_dc != other.tilt_pos_sensor_full_dump_dc) {
      return false;
    }
    return true;
  }
  bool operator!=(const LinkSensorCalLim_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LinkSensorCalLim_

// alias to use template instance with default allocator
using LinkSensorCalLim =
  cpm_common_interfaces::msg::LinkSensorCalLim_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__STRUCT_HPP_
