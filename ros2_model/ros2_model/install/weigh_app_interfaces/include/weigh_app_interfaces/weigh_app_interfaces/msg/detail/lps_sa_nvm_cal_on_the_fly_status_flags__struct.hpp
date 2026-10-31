// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyStatusFlags.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_status_flags.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyStatusFlags __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyStatusFlags __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaNvmCalOnTheFlyStatusFlags_
{
  using Type = LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator>;

  explicit LpsSaNvmCalOnTheFlyStatusFlags_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cal_in_progress = false;
      this->empty_bkt_cal_done = false;
      this->full_bkt_cal_done = false;
    }
  }

  explicit LpsSaNvmCalOnTheFlyStatusFlags_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cal_in_progress = false;
      this->empty_bkt_cal_done = false;
      this->full_bkt_cal_done = false;
    }
  }

  // field types and members
  using _cal_in_progress_type =
    bool;
  _cal_in_progress_type cal_in_progress;
  using _empty_bkt_cal_done_type =
    bool;
  _empty_bkt_cal_done_type empty_bkt_cal_done;
  using _full_bkt_cal_done_type =
    bool;
  _full_bkt_cal_done_type full_bkt_cal_done;

  // setters for named parameter idiom
  Type & set__cal_in_progress(
    const bool & _arg)
  {
    this->cal_in_progress = _arg;
    return *this;
  }
  Type & set__empty_bkt_cal_done(
    const bool & _arg)
  {
    this->empty_bkt_cal_done = _arg;
    return *this;
  }
  Type & set__full_bkt_cal_done(
    const bool & _arg)
  {
    this->full_bkt_cal_done = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyStatusFlags
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyStatusFlags
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaNvmCalOnTheFlyStatusFlags_ & other) const
  {
    if (this->cal_in_progress != other.cal_in_progress) {
      return false;
    }
    if (this->empty_bkt_cal_done != other.empty_bkt_cal_done) {
      return false;
    }
    if (this->full_bkt_cal_done != other.full_bkt_cal_done) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaNvmCalOnTheFlyStatusFlags_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaNvmCalOnTheFlyStatusFlags_

// alias to use template instance with default allocator
using LpsSaNvmCalOnTheFlyStatusFlags =
  weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__STRUCT_HPP_
