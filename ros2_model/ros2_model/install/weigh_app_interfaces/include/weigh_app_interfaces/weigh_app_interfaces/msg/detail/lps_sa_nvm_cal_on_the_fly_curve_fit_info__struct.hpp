// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyCurveFitInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_curve_fit_info.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'imu_cal_results'
#include "weigh_app_interfaces/msg/detail/lps_cal_imu_results__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyCurveFitInfo __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyCurveFitInfo __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaNvmCalOnTheFlyCurveFitInfo_
{
  using Type = LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator>;

  explicit LpsSaNvmCalOnTheFlyCurveFitInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : imu_cal_results(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->hyd_oil_temp_met = false;
      this->enforce_raise_detent = false;
      this->enforce_lower_detent = false;
      this->raise_fast_vel_done = false;
      this->raise_slow_fit_done = false;
      this->raise_fast_fit_done = false;
      this->lower_slow_fit_done = false;
      this->internal_step = 0;
      this->raise_num_points = 0;
      this->lower_num_points = 0;
    }
  }

  explicit LpsSaNvmCalOnTheFlyCurveFitInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : imu_cal_results(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->hyd_oil_temp_met = false;
      this->enforce_raise_detent = false;
      this->enforce_lower_detent = false;
      this->raise_fast_vel_done = false;
      this->raise_slow_fit_done = false;
      this->raise_fast_fit_done = false;
      this->lower_slow_fit_done = false;
      this->internal_step = 0;
      this->raise_num_points = 0;
      this->lower_num_points = 0;
    }
  }

  // field types and members
  using _hyd_oil_temp_met_type =
    bool;
  _hyd_oil_temp_met_type hyd_oil_temp_met;
  using _enforce_raise_detent_type =
    bool;
  _enforce_raise_detent_type enforce_raise_detent;
  using _enforce_lower_detent_type =
    bool;
  _enforce_lower_detent_type enforce_lower_detent;
  using _raise_fast_vel_done_type =
    bool;
  _raise_fast_vel_done_type raise_fast_vel_done;
  using _raise_slow_fit_done_type =
    bool;
  _raise_slow_fit_done_type raise_slow_fit_done;
  using _raise_fast_fit_done_type =
    bool;
  _raise_fast_fit_done_type raise_fast_fit_done;
  using _lower_slow_fit_done_type =
    bool;
  _lower_slow_fit_done_type lower_slow_fit_done;
  using _internal_step_type =
    uint8_t;
  _internal_step_type internal_step;
  using _raise_num_points_type =
    uint16_t;
  _raise_num_points_type raise_num_points;
  using _lower_num_points_type =
    uint16_t;
  _lower_num_points_type lower_num_points;
  using _imu_cal_results_type =
    weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator>;
  _imu_cal_results_type imu_cal_results;

  // setters for named parameter idiom
  Type & set__hyd_oil_temp_met(
    const bool & _arg)
  {
    this->hyd_oil_temp_met = _arg;
    return *this;
  }
  Type & set__enforce_raise_detent(
    const bool & _arg)
  {
    this->enforce_raise_detent = _arg;
    return *this;
  }
  Type & set__enforce_lower_detent(
    const bool & _arg)
  {
    this->enforce_lower_detent = _arg;
    return *this;
  }
  Type & set__raise_fast_vel_done(
    const bool & _arg)
  {
    this->raise_fast_vel_done = _arg;
    return *this;
  }
  Type & set__raise_slow_fit_done(
    const bool & _arg)
  {
    this->raise_slow_fit_done = _arg;
    return *this;
  }
  Type & set__raise_fast_fit_done(
    const bool & _arg)
  {
    this->raise_fast_fit_done = _arg;
    return *this;
  }
  Type & set__lower_slow_fit_done(
    const bool & _arg)
  {
    this->lower_slow_fit_done = _arg;
    return *this;
  }
  Type & set__internal_step(
    const uint8_t & _arg)
  {
    this->internal_step = _arg;
    return *this;
  }
  Type & set__raise_num_points(
    const uint16_t & _arg)
  {
    this->raise_num_points = _arg;
    return *this;
  }
  Type & set__lower_num_points(
    const uint16_t & _arg)
  {
    this->lower_num_points = _arg;
    return *this;
  }
  Type & set__imu_cal_results(
    const weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator> & _arg)
  {
    this->imu_cal_results = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyCurveFitInfo
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyCurveFitInfo
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaNvmCalOnTheFlyCurveFitInfo_ & other) const
  {
    if (this->hyd_oil_temp_met != other.hyd_oil_temp_met) {
      return false;
    }
    if (this->enforce_raise_detent != other.enforce_raise_detent) {
      return false;
    }
    if (this->enforce_lower_detent != other.enforce_lower_detent) {
      return false;
    }
    if (this->raise_fast_vel_done != other.raise_fast_vel_done) {
      return false;
    }
    if (this->raise_slow_fit_done != other.raise_slow_fit_done) {
      return false;
    }
    if (this->raise_fast_fit_done != other.raise_fast_fit_done) {
      return false;
    }
    if (this->lower_slow_fit_done != other.lower_slow_fit_done) {
      return false;
    }
    if (this->internal_step != other.internal_step) {
      return false;
    }
    if (this->raise_num_points != other.raise_num_points) {
      return false;
    }
    if (this->lower_num_points != other.lower_num_points) {
      return false;
    }
    if (this->imu_cal_results != other.imu_cal_results) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaNvmCalOnTheFlyCurveFitInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaNvmCalOnTheFlyCurveFitInfo_

// alias to use template instance with default allocator
using LpsSaNvmCalOnTheFlyCurveFitInfo =
  weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__STRUCT_HPP_
