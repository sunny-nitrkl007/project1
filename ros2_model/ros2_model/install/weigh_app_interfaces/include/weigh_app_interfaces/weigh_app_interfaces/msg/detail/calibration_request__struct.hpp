// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/CalibrationRequest.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/calibration_request.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__CalibrationRequest __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__CalibrationRequest __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CalibrationRequest_
{
  using Type = CalibrationRequest_<ContainerAllocator>;

  explicit CalibrationRequest_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->src = 0;
      this->dest = 0;
      this->calibration_reqst_flag = false;
      this->calcmd = 0;
      this->cal_id = 0;
    }
  }

  explicit CalibrationRequest_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->src = 0;
      this->dest = 0;
      this->calibration_reqst_flag = false;
      this->calcmd = 0;
      this->cal_id = 0;
    }
  }

  // field types and members
  using _src_type =
    uint16_t;
  _src_type src;
  using _dest_type =
    uint16_t;
  _dest_type dest;
  using _calibration_reqst_flag_type =
    bool;
  _calibration_reqst_flag_type calibration_reqst_flag;
  using _calcmd_type =
    uint8_t;
  _calcmd_type calcmd;
  using _cal_id_type =
    uint16_t;
  _cal_id_type cal_id;
  using _cal_iterm_type =
    std::vector<uint32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint32_t>>;
  _cal_iterm_type cal_iterm;

  // setters for named parameter idiom
  Type & set__src(
    const uint16_t & _arg)
  {
    this->src = _arg;
    return *this;
  }
  Type & set__dest(
    const uint16_t & _arg)
  {
    this->dest = _arg;
    return *this;
  }
  Type & set__calibration_reqst_flag(
    const bool & _arg)
  {
    this->calibration_reqst_flag = _arg;
    return *this;
  }
  Type & set__calcmd(
    const uint8_t & _arg)
  {
    this->calcmd = _arg;
    return *this;
  }
  Type & set__cal_id(
    const uint16_t & _arg)
  {
    this->cal_id = _arg;
    return *this;
  }
  Type & set__cal_iterm(
    const std::vector<uint32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint32_t>> & _arg)
  {
    this->cal_iterm = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__CalibrationRequest
    std::shared_ptr<weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__CalibrationRequest
    std::shared_ptr<weigh_app_interfaces::msg::CalibrationRequest_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CalibrationRequest_ & other) const
  {
    if (this->src != other.src) {
      return false;
    }
    if (this->dest != other.dest) {
      return false;
    }
    if (this->calibration_reqst_flag != other.calibration_reqst_flag) {
      return false;
    }
    if (this->calcmd != other.calcmd) {
      return false;
    }
    if (this->cal_id != other.cal_id) {
      return false;
    }
    if (this->cal_iterm != other.cal_iterm) {
      return false;
    }
    return true;
  }
  bool operator!=(const CalibrationRequest_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CalibrationRequest_

// alias to use template instance with default allocator
using CalibrationRequest =
  weigh_app_interfaces::msg::CalibrationRequest_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__STRUCT_HPP_
