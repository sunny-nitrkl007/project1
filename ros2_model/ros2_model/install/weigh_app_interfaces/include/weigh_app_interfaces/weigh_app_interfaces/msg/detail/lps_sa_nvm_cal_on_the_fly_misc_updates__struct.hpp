// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyMiscUpdates.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_misc_updates.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyMiscUpdates __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyMiscUpdates __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaNvmCalOnTheFlyMiscUpdates_
{
  using Type = LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator>;

  explicit LpsSaNvmCalOnTheFlyMiscUpdates_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lift_he_pres_stat = 0l;
      this->lift_re_pres_stat = 0l;
      this->lift_cyl_length_norm_stat = 0l;
      this->hyd_oil_temp_stat = 0l;
      this->lift_cyl_vel_stat = 0l;
      this->tilt_cyl_length_norm_stat = 0l;
      this->bkt_angle_stat = 0l;
      this->lift_lever_info_lever_info_available = false;
      this->lift_lever_info_faulted = false;
    }
  }

  explicit LpsSaNvmCalOnTheFlyMiscUpdates_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lift_he_pres_stat = 0l;
      this->lift_re_pres_stat = 0l;
      this->lift_cyl_length_norm_stat = 0l;
      this->hyd_oil_temp_stat = 0l;
      this->lift_cyl_vel_stat = 0l;
      this->tilt_cyl_length_norm_stat = 0l;
      this->bkt_angle_stat = 0l;
      this->lift_lever_info_lever_info_available = false;
      this->lift_lever_info_faulted = false;
    }
  }

  // field types and members
  using _lift_he_pres_stat_type =
    int32_t;
  _lift_he_pres_stat_type lift_he_pres_stat;
  using _lift_re_pres_stat_type =
    int32_t;
  _lift_re_pres_stat_type lift_re_pres_stat;
  using _lift_cyl_length_norm_stat_type =
    int32_t;
  _lift_cyl_length_norm_stat_type lift_cyl_length_norm_stat;
  using _hyd_oil_temp_stat_type =
    int32_t;
  _hyd_oil_temp_stat_type hyd_oil_temp_stat;
  using _lift_cyl_vel_stat_type =
    int32_t;
  _lift_cyl_vel_stat_type lift_cyl_vel_stat;
  using _tilt_cyl_length_norm_stat_type =
    int32_t;
  _tilt_cyl_length_norm_stat_type tilt_cyl_length_norm_stat;
  using _bkt_angle_stat_type =
    int32_t;
  _bkt_angle_stat_type bkt_angle_stat;
  using _lift_lever_info_lever_info_available_type =
    bool;
  _lift_lever_info_lever_info_available_type lift_lever_info_lever_info_available;
  using _lift_lever_info_faulted_type =
    bool;
  _lift_lever_info_faulted_type lift_lever_info_faulted;

  // setters for named parameter idiom
  Type & set__lift_he_pres_stat(
    const int32_t & _arg)
  {
    this->lift_he_pres_stat = _arg;
    return *this;
  }
  Type & set__lift_re_pres_stat(
    const int32_t & _arg)
  {
    this->lift_re_pres_stat = _arg;
    return *this;
  }
  Type & set__lift_cyl_length_norm_stat(
    const int32_t & _arg)
  {
    this->lift_cyl_length_norm_stat = _arg;
    return *this;
  }
  Type & set__hyd_oil_temp_stat(
    const int32_t & _arg)
  {
    this->hyd_oil_temp_stat = _arg;
    return *this;
  }
  Type & set__lift_cyl_vel_stat(
    const int32_t & _arg)
  {
    this->lift_cyl_vel_stat = _arg;
    return *this;
  }
  Type & set__tilt_cyl_length_norm_stat(
    const int32_t & _arg)
  {
    this->tilt_cyl_length_norm_stat = _arg;
    return *this;
  }
  Type & set__bkt_angle_stat(
    const int32_t & _arg)
  {
    this->bkt_angle_stat = _arg;
    return *this;
  }
  Type & set__lift_lever_info_lever_info_available(
    const bool & _arg)
  {
    this->lift_lever_info_lever_info_available = _arg;
    return *this;
  }
  Type & set__lift_lever_info_faulted(
    const bool & _arg)
  {
    this->lift_lever_info_faulted = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyMiscUpdates
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyMiscUpdates
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaNvmCalOnTheFlyMiscUpdates_ & other) const
  {
    if (this->lift_he_pres_stat != other.lift_he_pres_stat) {
      return false;
    }
    if (this->lift_re_pres_stat != other.lift_re_pres_stat) {
      return false;
    }
    if (this->lift_cyl_length_norm_stat != other.lift_cyl_length_norm_stat) {
      return false;
    }
    if (this->hyd_oil_temp_stat != other.hyd_oil_temp_stat) {
      return false;
    }
    if (this->lift_cyl_vel_stat != other.lift_cyl_vel_stat) {
      return false;
    }
    if (this->tilt_cyl_length_norm_stat != other.tilt_cyl_length_norm_stat) {
      return false;
    }
    if (this->bkt_angle_stat != other.bkt_angle_stat) {
      return false;
    }
    if (this->lift_lever_info_lever_info_available != other.lift_lever_info_lever_info_available) {
      return false;
    }
    if (this->lift_lever_info_faulted != other.lift_lever_info_faulted) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaNvmCalOnTheFlyMiscUpdates_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaNvmCalOnTheFlyMiscUpdates_

// alias to use template instance with default allocator
using LpsSaNvmCalOnTheFlyMiscUpdates =
  weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__STRUCT_HPP_
