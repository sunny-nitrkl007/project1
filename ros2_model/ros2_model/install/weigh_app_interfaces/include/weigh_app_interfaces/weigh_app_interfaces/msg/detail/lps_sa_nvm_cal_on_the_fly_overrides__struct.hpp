// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyOverrides.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_overrides.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'tilt_overrides'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_tilt_overrides__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyOverrides __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyOverrides __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaNvmCalOnTheFlyOverrides_
{
  using Type = LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator>;

  explicit LpsSaNvmCalOnTheFlyOverrides_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : tilt_overrides(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lps_cal_ovr_state = 0;
      this->lps_cal_app_inf_raise_cmd_lmt = 0;
      this->lps_cal_app_inf_lower_cmd_lmt = 0;
      this->lps_cal_app_inf_rack_cmd_lmt = 0;
      this->lps_cal_app_inf_dump_cmd_lmt = 0;
      this->lps_cal_app_inf_eng_spd_lmt = 0;
      this->lps_cal_app_inf_cal_ovr_active = false;
      this->lift_bottom_flag = false;
      this->lift_top_flag = false;
      this->cal_ovr_acknowledge = false;
      this->lift_valve_cmd_percent = 0.0f;
      this->lift_in_raise_detent = false;
      this->lift_in_lower_detent = false;
      this->lift_in_center = false;
      this->lift_faulted = false;
      this->lever_info_available = false;
    }
  }

  explicit LpsSaNvmCalOnTheFlyOverrides_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : tilt_overrides(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lps_cal_ovr_state = 0;
      this->lps_cal_app_inf_raise_cmd_lmt = 0;
      this->lps_cal_app_inf_lower_cmd_lmt = 0;
      this->lps_cal_app_inf_rack_cmd_lmt = 0;
      this->lps_cal_app_inf_dump_cmd_lmt = 0;
      this->lps_cal_app_inf_eng_spd_lmt = 0;
      this->lps_cal_app_inf_cal_ovr_active = false;
      this->lift_bottom_flag = false;
      this->lift_top_flag = false;
      this->cal_ovr_acknowledge = false;
      this->lift_valve_cmd_percent = 0.0f;
      this->lift_in_raise_detent = false;
      this->lift_in_lower_detent = false;
      this->lift_in_center = false;
      this->lift_faulted = false;
      this->lever_info_available = false;
    }
  }

  // field types and members
  using _lps_cal_ovr_state_type =
    uint8_t;
  _lps_cal_ovr_state_type lps_cal_ovr_state;
  using _lps_cal_app_inf_raise_cmd_lmt_type =
    int8_t;
  _lps_cal_app_inf_raise_cmd_lmt_type lps_cal_app_inf_raise_cmd_lmt;
  using _lps_cal_app_inf_lower_cmd_lmt_type =
    int8_t;
  _lps_cal_app_inf_lower_cmd_lmt_type lps_cal_app_inf_lower_cmd_lmt;
  using _lps_cal_app_inf_rack_cmd_lmt_type =
    int8_t;
  _lps_cal_app_inf_rack_cmd_lmt_type lps_cal_app_inf_rack_cmd_lmt;
  using _lps_cal_app_inf_dump_cmd_lmt_type =
    int8_t;
  _lps_cal_app_inf_dump_cmd_lmt_type lps_cal_app_inf_dump_cmd_lmt;
  using _lps_cal_app_inf_eng_spd_lmt_type =
    int16_t;
  _lps_cal_app_inf_eng_spd_lmt_type lps_cal_app_inf_eng_spd_lmt;
  using _lps_cal_app_inf_cal_ovr_active_type =
    bool;
  _lps_cal_app_inf_cal_ovr_active_type lps_cal_app_inf_cal_ovr_active;
  using _lift_bottom_flag_type =
    bool;
  _lift_bottom_flag_type lift_bottom_flag;
  using _lift_top_flag_type =
    bool;
  _lift_top_flag_type lift_top_flag;
  using _cal_ovr_acknowledge_type =
    bool;
  _cal_ovr_acknowledge_type cal_ovr_acknowledge;
  using _lift_valve_cmd_percent_type =
    float;
  _lift_valve_cmd_percent_type lift_valve_cmd_percent;
  using _lift_in_raise_detent_type =
    bool;
  _lift_in_raise_detent_type lift_in_raise_detent;
  using _lift_in_lower_detent_type =
    bool;
  _lift_in_lower_detent_type lift_in_lower_detent;
  using _lift_in_center_type =
    bool;
  _lift_in_center_type lift_in_center;
  using _lift_faulted_type =
    bool;
  _lift_faulted_type lift_faulted;
  using _lever_info_available_type =
    bool;
  _lever_info_available_type lever_info_available;
  using _tilt_overrides_type =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator>;
  _tilt_overrides_type tilt_overrides;

  // setters for named parameter idiom
  Type & set__lps_cal_ovr_state(
    const uint8_t & _arg)
  {
    this->lps_cal_ovr_state = _arg;
    return *this;
  }
  Type & set__lps_cal_app_inf_raise_cmd_lmt(
    const int8_t & _arg)
  {
    this->lps_cal_app_inf_raise_cmd_lmt = _arg;
    return *this;
  }
  Type & set__lps_cal_app_inf_lower_cmd_lmt(
    const int8_t & _arg)
  {
    this->lps_cal_app_inf_lower_cmd_lmt = _arg;
    return *this;
  }
  Type & set__lps_cal_app_inf_rack_cmd_lmt(
    const int8_t & _arg)
  {
    this->lps_cal_app_inf_rack_cmd_lmt = _arg;
    return *this;
  }
  Type & set__lps_cal_app_inf_dump_cmd_lmt(
    const int8_t & _arg)
  {
    this->lps_cal_app_inf_dump_cmd_lmt = _arg;
    return *this;
  }
  Type & set__lps_cal_app_inf_eng_spd_lmt(
    const int16_t & _arg)
  {
    this->lps_cal_app_inf_eng_spd_lmt = _arg;
    return *this;
  }
  Type & set__lps_cal_app_inf_cal_ovr_active(
    const bool & _arg)
  {
    this->lps_cal_app_inf_cal_ovr_active = _arg;
    return *this;
  }
  Type & set__lift_bottom_flag(
    const bool & _arg)
  {
    this->lift_bottom_flag = _arg;
    return *this;
  }
  Type & set__lift_top_flag(
    const bool & _arg)
  {
    this->lift_top_flag = _arg;
    return *this;
  }
  Type & set__cal_ovr_acknowledge(
    const bool & _arg)
  {
    this->cal_ovr_acknowledge = _arg;
    return *this;
  }
  Type & set__lift_valve_cmd_percent(
    const float & _arg)
  {
    this->lift_valve_cmd_percent = _arg;
    return *this;
  }
  Type & set__lift_in_raise_detent(
    const bool & _arg)
  {
    this->lift_in_raise_detent = _arg;
    return *this;
  }
  Type & set__lift_in_lower_detent(
    const bool & _arg)
  {
    this->lift_in_lower_detent = _arg;
    return *this;
  }
  Type & set__lift_in_center(
    const bool & _arg)
  {
    this->lift_in_center = _arg;
    return *this;
  }
  Type & set__lift_faulted(
    const bool & _arg)
  {
    this->lift_faulted = _arg;
    return *this;
  }
  Type & set__lever_info_available(
    const bool & _arg)
  {
    this->lever_info_available = _arg;
    return *this;
  }
  Type & set__tilt_overrides(
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides_<ContainerAllocator> & _arg)
  {
    this->tilt_overrides = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyOverrides
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyOverrides
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaNvmCalOnTheFlyOverrides_ & other) const
  {
    if (this->lps_cal_ovr_state != other.lps_cal_ovr_state) {
      return false;
    }
    if (this->lps_cal_app_inf_raise_cmd_lmt != other.lps_cal_app_inf_raise_cmd_lmt) {
      return false;
    }
    if (this->lps_cal_app_inf_lower_cmd_lmt != other.lps_cal_app_inf_lower_cmd_lmt) {
      return false;
    }
    if (this->lps_cal_app_inf_rack_cmd_lmt != other.lps_cal_app_inf_rack_cmd_lmt) {
      return false;
    }
    if (this->lps_cal_app_inf_dump_cmd_lmt != other.lps_cal_app_inf_dump_cmd_lmt) {
      return false;
    }
    if (this->lps_cal_app_inf_eng_spd_lmt != other.lps_cal_app_inf_eng_spd_lmt) {
      return false;
    }
    if (this->lps_cal_app_inf_cal_ovr_active != other.lps_cal_app_inf_cal_ovr_active) {
      return false;
    }
    if (this->lift_bottom_flag != other.lift_bottom_flag) {
      return false;
    }
    if (this->lift_top_flag != other.lift_top_flag) {
      return false;
    }
    if (this->cal_ovr_acknowledge != other.cal_ovr_acknowledge) {
      return false;
    }
    if (this->lift_valve_cmd_percent != other.lift_valve_cmd_percent) {
      return false;
    }
    if (this->lift_in_raise_detent != other.lift_in_raise_detent) {
      return false;
    }
    if (this->lift_in_lower_detent != other.lift_in_lower_detent) {
      return false;
    }
    if (this->lift_in_center != other.lift_in_center) {
      return false;
    }
    if (this->lift_faulted != other.lift_faulted) {
      return false;
    }
    if (this->lever_info_available != other.lever_info_available) {
      return false;
    }
    if (this->tilt_overrides != other.tilt_overrides) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaNvmCalOnTheFlyOverrides_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaNvmCalOnTheFlyOverrides_

// alias to use template instance with default allocator
using LpsSaNvmCalOnTheFlyOverrides =
  weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__STRUCT_HPP_
