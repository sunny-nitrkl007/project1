// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyDataChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_data_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'lps_sa_nvm_calibration_data_on_the_fly'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_data_on_the_fly__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaNvmCalOnTheFlyDataChannel_
{
  using Type = LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator>;

  explicit LpsSaNvmCalOnTheFlyDataChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : lps_sa_nvm_calibration_data_on_the_fly(_init)
  {
    (void)_init;
  }

  explicit LpsSaNvmCalOnTheFlyDataChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : lps_sa_nvm_calibration_data_on_the_fly(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _lps_sa_nvm_calibration_data_on_the_fly_type =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator>;
  _lps_sa_nvm_calibration_data_on_the_fly_type lps_sa_nvm_calibration_data_on_the_fly;

  // setters for named parameter idiom
  Type & set__lps_sa_nvm_calibration_data_on_the_fly(
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly_<ContainerAllocator> & _arg)
  {
    this->lps_sa_nvm_calibration_data_on_the_fly = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaNvmCalOnTheFlyDataChannel_ & other) const
  {
    if (this->lps_sa_nvm_calibration_data_on_the_fly != other.lps_sa_nvm_calibration_data_on_the_fly) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaNvmCalOnTheFlyDataChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaNvmCalOnTheFlyDataChannel_

// alias to use template instance with default allocator
using LpsSaNvmCalOnTheFlyDataChannel =
  weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__STRUCT_HPP_
