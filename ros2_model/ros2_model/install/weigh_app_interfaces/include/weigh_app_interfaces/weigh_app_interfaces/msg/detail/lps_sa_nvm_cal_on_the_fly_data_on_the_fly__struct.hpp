// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyDataOnTheFly.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_data_on_the_fly.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'status_flags'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_status_flags__struct.hpp"
// Member 'curve_info'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_curve_fit_info__struct.hpp"
// Member 'cal_updates'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_misc_updates__struct.hpp"
// Member 'cal_overrides'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_overrides__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataOnTheFly __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataOnTheFly __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaNvmCalOnTheFlyDataOnTheFly_
{
  using Type = LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator>;

  explicit LpsSaNvmCalOnTheFlyDataOnTheFly_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : status_flags(_init),
    curve_info(_init),
    cal_updates(_init),
    cal_overrides(_init)
  {
    (void)_init;
  }

  explicit LpsSaNvmCalOnTheFlyDataOnTheFly_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : status_flags(_alloc, _init),
    curve_info(_alloc, _init),
    cal_updates(_alloc, _init),
    cal_overrides(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _status_flags_type =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator>;
  _status_flags_type status_flags;
  using _curve_info_type =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator>;
  _curve_info_type curve_info;
  using _cal_updates_type =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator>;
  _cal_updates_type cal_updates;
  using _cal_overrides_type =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator>;
  _cal_overrides_type cal_overrides;

  // setters for named parameter idiom
  Type & set__status_flags(
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator> & _arg)
  {
    this->status_flags = _arg;
    return *this;
  }
  Type & set__curve_info(
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo_<ContainerAllocator> & _arg)
  {
    this->curve_info = _arg;
    return *this;
  }
  Type & set__cal_updates(
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates_<ContainerAllocator> & _arg)
  {
    this->cal_updates = _arg;
    return *this;
  }
  Type & set__cal_overrides(
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides_<ContainerAllocator> & _arg)
  {
    this->cal_overrides = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataOnTheFly
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataOnTheFly
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaNvmCalOnTheFlyDataOnTheFly_ & other) const
  {
    if (this->status_flags != other.status_flags) {
      return false;
    }
    if (this->curve_info != other.curve_info) {
      return false;
    }
    if (this->cal_updates != other.cal_updates) {
      return false;
    }
    if (this->cal_overrides != other.cal_overrides) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaNvmCalOnTheFlyDataOnTheFly_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaNvmCalOnTheFlyDataOnTheFly_

// alias to use template instance with default allocator
using LpsSaNvmCalOnTheFlyDataOnTheFly =
  weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__STRUCT_HPP_
