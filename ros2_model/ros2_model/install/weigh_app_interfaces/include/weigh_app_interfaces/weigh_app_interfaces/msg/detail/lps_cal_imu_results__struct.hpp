// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsCalIMUResults.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_cal_imu_results.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsCalIMUResults __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsCalIMUResults __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsCalIMUResults_
{
  using Type = LpsCalIMUResults_<ContainerAllocator>;

  explicit LpsCalIMUResults_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->full_slow_imu_offset_temp1 = 0.0f;
      this->full_slow_imu_offset_temp2 = 0.0f;
      this->full_slow_imu_offset_temp3 = 0.0f;
      this->full_slow_lumped_weight_temp1 = 0.0f;
      this->full_slow_lumped_weight_temp2 = 0.0f;
      this->full_slow_lumped_weight_temp3 = 0.0f;
      this->empty_slow_imu_offset_temp1 = 0.0f;
      this->empty_slow_imu_offset_temp2 = 0.0f;
      this->empty_slow_imu_offset_temp3 = 0.0f;
      this->empty_slow_lumped_weight_temp1 = 0.0f;
      this->empty_slow_lumped_weight_temp2 = 0.0f;
      this->empty_slow_lumped_weight_temp3 = 0.0f;
      this->full_slow_imu_offset_final = 0.0f;
      this->empty_slow_imu_offset_final = 0.0f;
      this->full_slow_lumped_weight_final = 0.0f;
      this->empty_slow_lumped_weight_final = 0.0f;
    }
  }

  explicit LpsCalIMUResults_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->full_slow_imu_offset_temp1 = 0.0f;
      this->full_slow_imu_offset_temp2 = 0.0f;
      this->full_slow_imu_offset_temp3 = 0.0f;
      this->full_slow_lumped_weight_temp1 = 0.0f;
      this->full_slow_lumped_weight_temp2 = 0.0f;
      this->full_slow_lumped_weight_temp3 = 0.0f;
      this->empty_slow_imu_offset_temp1 = 0.0f;
      this->empty_slow_imu_offset_temp2 = 0.0f;
      this->empty_slow_imu_offset_temp3 = 0.0f;
      this->empty_slow_lumped_weight_temp1 = 0.0f;
      this->empty_slow_lumped_weight_temp2 = 0.0f;
      this->empty_slow_lumped_weight_temp3 = 0.0f;
      this->full_slow_imu_offset_final = 0.0f;
      this->empty_slow_imu_offset_final = 0.0f;
      this->full_slow_lumped_weight_final = 0.0f;
      this->empty_slow_lumped_weight_final = 0.0f;
    }
  }

  // field types and members
  using _full_slow_imu_offset_temp1_type =
    float;
  _full_slow_imu_offset_temp1_type full_slow_imu_offset_temp1;
  using _full_slow_imu_offset_temp2_type =
    float;
  _full_slow_imu_offset_temp2_type full_slow_imu_offset_temp2;
  using _full_slow_imu_offset_temp3_type =
    float;
  _full_slow_imu_offset_temp3_type full_slow_imu_offset_temp3;
  using _full_slow_lumped_weight_temp1_type =
    float;
  _full_slow_lumped_weight_temp1_type full_slow_lumped_weight_temp1;
  using _full_slow_lumped_weight_temp2_type =
    float;
  _full_slow_lumped_weight_temp2_type full_slow_lumped_weight_temp2;
  using _full_slow_lumped_weight_temp3_type =
    float;
  _full_slow_lumped_weight_temp3_type full_slow_lumped_weight_temp3;
  using _empty_slow_imu_offset_temp1_type =
    float;
  _empty_slow_imu_offset_temp1_type empty_slow_imu_offset_temp1;
  using _empty_slow_imu_offset_temp2_type =
    float;
  _empty_slow_imu_offset_temp2_type empty_slow_imu_offset_temp2;
  using _empty_slow_imu_offset_temp3_type =
    float;
  _empty_slow_imu_offset_temp3_type empty_slow_imu_offset_temp3;
  using _empty_slow_lumped_weight_temp1_type =
    float;
  _empty_slow_lumped_weight_temp1_type empty_slow_lumped_weight_temp1;
  using _empty_slow_lumped_weight_temp2_type =
    float;
  _empty_slow_lumped_weight_temp2_type empty_slow_lumped_weight_temp2;
  using _empty_slow_lumped_weight_temp3_type =
    float;
  _empty_slow_lumped_weight_temp3_type empty_slow_lumped_weight_temp3;
  using _full_slow_imu_offset_final_type =
    float;
  _full_slow_imu_offset_final_type full_slow_imu_offset_final;
  using _empty_slow_imu_offset_final_type =
    float;
  _empty_slow_imu_offset_final_type empty_slow_imu_offset_final;
  using _full_slow_lumped_weight_final_type =
    float;
  _full_slow_lumped_weight_final_type full_slow_lumped_weight_final;
  using _empty_slow_lumped_weight_final_type =
    float;
  _empty_slow_lumped_weight_final_type empty_slow_lumped_weight_final;

  // setters for named parameter idiom
  Type & set__full_slow_imu_offset_temp1(
    const float & _arg)
  {
    this->full_slow_imu_offset_temp1 = _arg;
    return *this;
  }
  Type & set__full_slow_imu_offset_temp2(
    const float & _arg)
  {
    this->full_slow_imu_offset_temp2 = _arg;
    return *this;
  }
  Type & set__full_slow_imu_offset_temp3(
    const float & _arg)
  {
    this->full_slow_imu_offset_temp3 = _arg;
    return *this;
  }
  Type & set__full_slow_lumped_weight_temp1(
    const float & _arg)
  {
    this->full_slow_lumped_weight_temp1 = _arg;
    return *this;
  }
  Type & set__full_slow_lumped_weight_temp2(
    const float & _arg)
  {
    this->full_slow_lumped_weight_temp2 = _arg;
    return *this;
  }
  Type & set__full_slow_lumped_weight_temp3(
    const float & _arg)
  {
    this->full_slow_lumped_weight_temp3 = _arg;
    return *this;
  }
  Type & set__empty_slow_imu_offset_temp1(
    const float & _arg)
  {
    this->empty_slow_imu_offset_temp1 = _arg;
    return *this;
  }
  Type & set__empty_slow_imu_offset_temp2(
    const float & _arg)
  {
    this->empty_slow_imu_offset_temp2 = _arg;
    return *this;
  }
  Type & set__empty_slow_imu_offset_temp3(
    const float & _arg)
  {
    this->empty_slow_imu_offset_temp3 = _arg;
    return *this;
  }
  Type & set__empty_slow_lumped_weight_temp1(
    const float & _arg)
  {
    this->empty_slow_lumped_weight_temp1 = _arg;
    return *this;
  }
  Type & set__empty_slow_lumped_weight_temp2(
    const float & _arg)
  {
    this->empty_slow_lumped_weight_temp2 = _arg;
    return *this;
  }
  Type & set__empty_slow_lumped_weight_temp3(
    const float & _arg)
  {
    this->empty_slow_lumped_weight_temp3 = _arg;
    return *this;
  }
  Type & set__full_slow_imu_offset_final(
    const float & _arg)
  {
    this->full_slow_imu_offset_final = _arg;
    return *this;
  }
  Type & set__empty_slow_imu_offset_final(
    const float & _arg)
  {
    this->empty_slow_imu_offset_final = _arg;
    return *this;
  }
  Type & set__full_slow_lumped_weight_final(
    const float & _arg)
  {
    this->full_slow_lumped_weight_final = _arg;
    return *this;
  }
  Type & set__empty_slow_lumped_weight_final(
    const float & _arg)
  {
    this->empty_slow_lumped_weight_final = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsCalIMUResults
    std::shared_ptr<weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsCalIMUResults
    std::shared_ptr<weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsCalIMUResults_ & other) const
  {
    if (this->full_slow_imu_offset_temp1 != other.full_slow_imu_offset_temp1) {
      return false;
    }
    if (this->full_slow_imu_offset_temp2 != other.full_slow_imu_offset_temp2) {
      return false;
    }
    if (this->full_slow_imu_offset_temp3 != other.full_slow_imu_offset_temp3) {
      return false;
    }
    if (this->full_slow_lumped_weight_temp1 != other.full_slow_lumped_weight_temp1) {
      return false;
    }
    if (this->full_slow_lumped_weight_temp2 != other.full_slow_lumped_weight_temp2) {
      return false;
    }
    if (this->full_slow_lumped_weight_temp3 != other.full_slow_lumped_weight_temp3) {
      return false;
    }
    if (this->empty_slow_imu_offset_temp1 != other.empty_slow_imu_offset_temp1) {
      return false;
    }
    if (this->empty_slow_imu_offset_temp2 != other.empty_slow_imu_offset_temp2) {
      return false;
    }
    if (this->empty_slow_imu_offset_temp3 != other.empty_slow_imu_offset_temp3) {
      return false;
    }
    if (this->empty_slow_lumped_weight_temp1 != other.empty_slow_lumped_weight_temp1) {
      return false;
    }
    if (this->empty_slow_lumped_weight_temp2 != other.empty_slow_lumped_weight_temp2) {
      return false;
    }
    if (this->empty_slow_lumped_weight_temp3 != other.empty_slow_lumped_weight_temp3) {
      return false;
    }
    if (this->full_slow_imu_offset_final != other.full_slow_imu_offset_final) {
      return false;
    }
    if (this->empty_slow_imu_offset_final != other.empty_slow_imu_offset_final) {
      return false;
    }
    if (this->full_slow_lumped_weight_final != other.full_slow_lumped_weight_final) {
      return false;
    }
    if (this->empty_slow_lumped_weight_final != other.empty_slow_lumped_weight_final) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsCalIMUResults_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsCalIMUResults_

// alias to use template instance with default allocator
using LpsCalIMUResults =
  weigh_app_interfaces::msg::LpsCalIMUResults_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__STRUCT_HPP_
