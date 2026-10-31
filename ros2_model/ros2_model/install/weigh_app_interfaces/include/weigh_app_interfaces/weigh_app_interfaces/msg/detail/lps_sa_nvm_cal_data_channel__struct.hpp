// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'lps_sa_nvm_calibration_data_main'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel_data_main__struct.hpp"
// Member 'lps_sa_nvm_calibration_data_debug'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel_data_debug__struct.hpp"
// Member 'imu_cal_results'
#include "weigh_app_interfaces/msg/detail/lps_cal_imu_results__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannel __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannel __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaNvmCalDataChannel_
{
  using Type = LpsSaNvmCalDataChannel_<ContainerAllocator>;

  explicit LpsSaNvmCalDataChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : lps_sa_nvm_calibration_data_main(_init),
    lps_sa_nvm_calibration_data_debug(_init),
    imu_cal_results(_init)
  {
    (void)_init;
  }

  explicit LpsSaNvmCalDataChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : lps_sa_nvm_calibration_data_main(_alloc, _init),
    lps_sa_nvm_calibration_data_debug(_alloc, _init),
    imu_cal_results(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _lps_sa_nvm_calibration_data_main_type =
    weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator>;
  _lps_sa_nvm_calibration_data_main_type lps_sa_nvm_calibration_data_main;
  using _lps_sa_nvm_calibration_data_debug_type =
    weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator>;
  _lps_sa_nvm_calibration_data_debug_type lps_sa_nvm_calibration_data_debug;
  using _imu_cal_results_type =
    weigh_app_interfaces::msg::LpsCalIMUResults_<ContainerAllocator>;
  _imu_cal_results_type imu_cal_results;

  // setters for named parameter idiom
  Type & set__lps_sa_nvm_calibration_data_main(
    const weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain_<ContainerAllocator> & _arg)
  {
    this->lps_sa_nvm_calibration_data_main = _arg;
    return *this;
  }
  Type & set__lps_sa_nvm_calibration_data_debug(
    const weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug_<ContainerAllocator> & _arg)
  {
    this->lps_sa_nvm_calibration_data_debug = _arg;
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
    weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannel
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaNvmCalDataChannel
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaNvmCalDataChannel_ & other) const
  {
    if (this->lps_sa_nvm_calibration_data_main != other.lps_sa_nvm_calibration_data_main) {
      return false;
    }
    if (this->lps_sa_nvm_calibration_data_debug != other.lps_sa_nvm_calibration_data_debug) {
      return false;
    }
    if (this->imu_cal_results != other.imu_cal_results) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaNvmCalDataChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaNvmCalDataChannel_

// alias to use template instance with default allocator
using LpsSaNvmCalDataChannel =
  weigh_app_interfaces::msg::LpsSaNvmCalDataChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__STRUCT_HPP_
