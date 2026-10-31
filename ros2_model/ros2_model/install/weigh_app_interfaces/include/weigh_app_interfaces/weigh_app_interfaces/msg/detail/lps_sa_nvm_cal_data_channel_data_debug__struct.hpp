// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannelDataDebug.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel_data_debug.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataDebug __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataDebug __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaNvmCalDataChannelDataDebug_
{
  using Type = LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator>;

  explicit LpsSaNvmCalDataChannelDataDebug_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lift_full_lower_dc_inf_value = 0l;
      this->lift_full_raise_dc_inf_value = 0l;
      this->tilt_full_dump_dc_inf_value = 0l;
      this->tilt_full_rack_dc_inf_value = 0l;
      this->tilt_dump_stop_angle_inf_value = 0l;
      this->tilt_rack_stop_angle_inf_value = 0l;
      this->pcs_vel_slope = 0.0f;
      this->pcs_cal_weight = 0.0f;
      this->zero_weight = 0.0f;
      this->cal_adjust = 0.0f;
      this->temp_slope = 0.0f;
      this->empty_temp = 0.0f;
      this->full_temp = 0.0f;
      this->empty_bucket_weight_est = 0.0f;
      this->cal_adjust_temp = 0.0f;
      this->hyd_oil_type_index = 0l;
    }
  }

  explicit LpsSaNvmCalDataChannelDataDebug_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lift_full_lower_dc_inf_value = 0l;
      this->lift_full_raise_dc_inf_value = 0l;
      this->tilt_full_dump_dc_inf_value = 0l;
      this->tilt_full_rack_dc_inf_value = 0l;
      this->tilt_dump_stop_angle_inf_value = 0l;
      this->tilt_rack_stop_angle_inf_value = 0l;
      this->pcs_vel_slope = 0.0f;
      this->pcs_cal_weight = 0.0f;
      this->zero_weight = 0.0f;
      this->cal_adjust = 0.0f;
      this->temp_slope = 0.0f;
      this->empty_temp = 0.0f;
      this->full_temp = 0.0f;
      this->empty_bucket_weight_est = 0.0f;
      this->cal_adjust_temp = 0.0f;
      this->hyd_oil_type_index = 0l;
    }
  }

  // field types and members
  using _lift_full_lower_dc_inf_value_type =
    int32_t;
  _lift_full_lower_dc_inf_value_type lift_full_lower_dc_inf_value;
  using _lift_full_raise_dc_inf_value_type =
    int32_t;
  _lift_full_raise_dc_inf_value_type lift_full_raise_dc_inf_value;
  using _tilt_full_dump_dc_inf_value_type =
    int32_t;
  _tilt_full_dump_dc_inf_value_type tilt_full_dump_dc_inf_value;
  using _tilt_full_rack_dc_inf_value_type =
    int32_t;
  _tilt_full_rack_dc_inf_value_type tilt_full_rack_dc_inf_value;
  using _tilt_dump_stop_angle_inf_value_type =
    int32_t;
  _tilt_dump_stop_angle_inf_value_type tilt_dump_stop_angle_inf_value;
  using _tilt_rack_stop_angle_inf_value_type =
    int32_t;
  _tilt_rack_stop_angle_inf_value_type tilt_rack_stop_angle_inf_value;
  using _pcs_vel_slope_type =
    float;
  _pcs_vel_slope_type pcs_vel_slope;
  using _pcs_cal_weight_type =
    float;
  _pcs_cal_weight_type pcs_cal_weight;
  using _zero_weight_type =
    float;
  _zero_weight_type zero_weight;
  using _cal_adjust_type =
    float;
  _cal_adjust_type cal_adjust;
  using _temp_slope_type =
    float;
  _temp_slope_type temp_slope;
  using _empty_temp_type =
    float;
  _empty_temp_type empty_temp;
  using _full_temp_type =
    float;
  _full_temp_type full_temp;
  using _empty_bucket_weight_est_type =
    float;
  _empty_bucket_weight_est_type empty_bucket_weight_est;
  using _cal_adjust_temp_type =
    float;
  _cal_adjust_temp_type cal_adjust_temp;
  using _hyd_oil_type_index_type =
    int32_t;
  _hyd_oil_type_index_type hyd_oil_type_index;

  // setters for named parameter idiom
  Type & set__lift_full_lower_dc_inf_value(
    const int32_t & _arg)
  {
    this->lift_full_lower_dc_inf_value = _arg;
    return *this;
  }
  Type & set__lift_full_raise_dc_inf_value(
    const int32_t & _arg)
  {
    this->lift_full_raise_dc_inf_value = _arg;
    return *this;
  }
  Type & set__tilt_full_dump_dc_inf_value(
    const int32_t & _arg)
  {
    this->tilt_full_dump_dc_inf_value = _arg;
    return *this;
  }
  Type & set__tilt_full_rack_dc_inf_value(
    const int32_t & _arg)
  {
    this->tilt_full_rack_dc_inf_value = _arg;
    return *this;
  }
  Type & set__tilt_dump_stop_angle_inf_value(
    const int32_t & _arg)
  {
    this->tilt_dump_stop_angle_inf_value = _arg;
    return *this;
  }
  Type & set__tilt_rack_stop_angle_inf_value(
    const int32_t & _arg)
  {
    this->tilt_rack_stop_angle_inf_value = _arg;
    return *this;
  }
  Type & set__pcs_vel_slope(
    const float & _arg)
  {
    this->pcs_vel_slope = _arg;
    return *this;
  }
  Type & set__pcs_cal_weight(
    const float & _arg)
  {
    this->pcs_cal_weight = _arg;
    return *this;
  }
  Type & set__zero_weight(
    const float & _arg)
  {
    this->zero_weight = _arg;
    return *this;
  }
  Type & set__cal_adjust(
    const float & _arg)
  {
    this->cal_adjust = _arg;
    return *this;
  }
  Type & set__temp_slope(
    const float & _arg)
  {
    this->temp_slope = _arg;
    return *this;
  }
  Type & set__empty_temp(
    const float & _arg)
  {
    this->empty_temp = _arg;
    return *this;
  }
  Type & set__full_temp(
    const float & _arg)
  {
    this->full_temp = _arg;
    return *this;
  }
  Type & set__empty_bucket_weight_est(
    const float & _arg)
  {
    this->empty_bucket_weight_est = _arg;
    return *this;
  }
  Type & set__cal_adjust_temp(
    const float & _arg)
  {
    this->cal_adjust_temp = _arg;
    return *this;
  }
  Type & set__hyd_oil_type_index(
    const int32_t & _arg)
  {
    this->hyd_oil_type_index = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataDebug
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannelDataDebug
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaNvmCalDataChannelDataDebug_ & other) const
  {
    if (this->lift_full_lower_dc_inf_value != other.lift_full_lower_dc_inf_value) {
      return false;
    }
    if (this->lift_full_raise_dc_inf_value != other.lift_full_raise_dc_inf_value) {
      return false;
    }
    if (this->tilt_full_dump_dc_inf_value != other.tilt_full_dump_dc_inf_value) {
      return false;
    }
    if (this->tilt_full_rack_dc_inf_value != other.tilt_full_rack_dc_inf_value) {
      return false;
    }
    if (this->tilt_dump_stop_angle_inf_value != other.tilt_dump_stop_angle_inf_value) {
      return false;
    }
    if (this->tilt_rack_stop_angle_inf_value != other.tilt_rack_stop_angle_inf_value) {
      return false;
    }
    if (this->pcs_vel_slope != other.pcs_vel_slope) {
      return false;
    }
    if (this->pcs_cal_weight != other.pcs_cal_weight) {
      return false;
    }
    if (this->zero_weight != other.zero_weight) {
      return false;
    }
    if (this->cal_adjust != other.cal_adjust) {
      return false;
    }
    if (this->temp_slope != other.temp_slope) {
      return false;
    }
    if (this->empty_temp != other.empty_temp) {
      return false;
    }
    if (this->full_temp != other.full_temp) {
      return false;
    }
    if (this->empty_bucket_weight_est != other.empty_bucket_weight_est) {
      return false;
    }
    if (this->cal_adjust_temp != other.cal_adjust_temp) {
      return false;
    }
    if (this->hyd_oil_type_index != other.hyd_oil_type_index) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaNvmCalDataChannelDataDebug_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaNvmCalDataChannelDataDebug_

// alias to use template instance with default allocator
using LpsSaNvmCalDataChannelDataDebug =
  weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__STRUCT_HPP_
