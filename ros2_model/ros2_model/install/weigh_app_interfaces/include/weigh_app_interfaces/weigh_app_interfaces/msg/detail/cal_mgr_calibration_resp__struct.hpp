// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/CalMgrCalibrationResp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/cal_mgr_calibration_resp.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__CalMgrCalibrationResp __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__CalMgrCalibrationResp __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CalMgrCalibrationResp_
{
  using Type = CalMgrCalibrationResp_<ContainerAllocator>;

  explicit CalMgrCalibrationResp_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->resp_code = 0;
      this->cal_resp = 0;
      this->step_no = 0;
      this->error = 0;
      this->warning = 0;
      this->enable_qual_read = false;
    }
  }

  explicit CalMgrCalibrationResp_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->resp_code = 0;
      this->cal_resp = 0;
      this->step_no = 0;
      this->error = 0;
      this->warning = 0;
      this->enable_qual_read = false;
    }
  }

  // field types and members
  using _resp_code_type =
    uint8_t;
  _resp_code_type resp_code;
  using _cal_resp_type =
    uint8_t;
  _cal_resp_type cal_resp;
  using _step_no_type =
    uint8_t;
  _step_no_type step_no;
  using _error_type =
    uint16_t;
  _error_type error;
  using _warning_type =
    uint16_t;
  _warning_type warning;
  using _enable_qual_read_type =
    bool;
  _enable_qual_read_type enable_qual_read;

  // setters for named parameter idiom
  Type & set__resp_code(
    const uint8_t & _arg)
  {
    this->resp_code = _arg;
    return *this;
  }
  Type & set__cal_resp(
    const uint8_t & _arg)
  {
    this->cal_resp = _arg;
    return *this;
  }
  Type & set__step_no(
    const uint8_t & _arg)
  {
    this->step_no = _arg;
    return *this;
  }
  Type & set__error(
    const uint16_t & _arg)
  {
    this->error = _arg;
    return *this;
  }
  Type & set__warning(
    const uint16_t & _arg)
  {
    this->warning = _arg;
    return *this;
  }
  Type & set__enable_qual_read(
    const bool & _arg)
  {
    this->enable_qual_read = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t RESP_CAL_SUCCESS =
    0u;
  static constexpr uint8_t RESP_CAL_FAIL =
    1u;
  static constexpr uint8_t RESP_CAL_UNKNOWN =
    2u;

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__CalMgrCalibrationResp
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__CalMgrCalibrationResp
    std::shared_ptr<weigh_app_interfaces::msg::CalMgrCalibrationResp_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CalMgrCalibrationResp_ & other) const
  {
    if (this->resp_code != other.resp_code) {
      return false;
    }
    if (this->cal_resp != other.cal_resp) {
      return false;
    }
    if (this->step_no != other.step_no) {
      return false;
    }
    if (this->error != other.error) {
      return false;
    }
    if (this->warning != other.warning) {
      return false;
    }
    if (this->enable_qual_read != other.enable_qual_read) {
      return false;
    }
    return true;
  }
  bool operator!=(const CalMgrCalibrationResp_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CalMgrCalibrationResp_

// alias to use template instance with default allocator
using CalMgrCalibrationResp =
  weigh_app_interfaces::msg::CalMgrCalibrationResp_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t CalMgrCalibrationResp_<ContainerAllocator>::RESP_CAL_SUCCESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t CalMgrCalibrationResp_<ContainerAllocator>::RESP_CAL_FAIL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t CalMgrCalibrationResp_<ContainerAllocator>::RESP_CAL_UNKNOWN;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__STRUCT_HPP_
