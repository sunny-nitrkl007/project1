// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaWeighInitDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_weigh_init_debug_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaWeighInitDebugChannel __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__LpsSaWeighInitDebugChannel __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaWeighInitDebugChannel_
{
  using Type = LpsSaWeighInitDebugChannel_<ContainerAllocator>;

  explicit LpsSaWeighInitDebugChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->exec_rate = 0.0f;
      this->cal_weight = 0.0f;
      this->cal_status = 0ul;
      this->cal_adjust = 0.0f;
      this->zero_weight = 0.0f;
      this->dig_target_wt = 0.0f;
      this->start_of_weigh = 0.0f;
      this->tilt_comp_gain_scalar = 0.0f;
    }
  }

  explicit LpsSaWeighInitDebugChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->exec_rate = 0.0f;
      this->cal_weight = 0.0f;
      this->cal_status = 0ul;
      this->cal_adjust = 0.0f;
      this->zero_weight = 0.0f;
      this->dig_target_wt = 0.0f;
      this->start_of_weigh = 0.0f;
      this->tilt_comp_gain_scalar = 0.0f;
    }
  }

  // field types and members
  using _exec_rate_type =
    float;
  _exec_rate_type exec_rate;
  using _cal_weight_type =
    float;
  _cal_weight_type cal_weight;
  using _cal_status_type =
    uint32_t;
  _cal_status_type cal_status;
  using _cal_adjust_type =
    float;
  _cal_adjust_type cal_adjust;
  using _zero_weight_type =
    float;
  _zero_weight_type zero_weight;
  using _dig_target_wt_type =
    float;
  _dig_target_wt_type dig_target_wt;
  using _start_of_weigh_type =
    float;
  _start_of_weigh_type start_of_weigh;
  using _tilt_comp_gain_scalar_type =
    float;
  _tilt_comp_gain_scalar_type tilt_comp_gain_scalar;

  // setters for named parameter idiom
  Type & set__exec_rate(
    const float & _arg)
  {
    this->exec_rate = _arg;
    return *this;
  }
  Type & set__cal_weight(
    const float & _arg)
  {
    this->cal_weight = _arg;
    return *this;
  }
  Type & set__cal_status(
    const uint32_t & _arg)
  {
    this->cal_status = _arg;
    return *this;
  }
  Type & set__cal_adjust(
    const float & _arg)
  {
    this->cal_adjust = _arg;
    return *this;
  }
  Type & set__zero_weight(
    const float & _arg)
  {
    this->zero_weight = _arg;
    return *this;
  }
  Type & set__dig_target_wt(
    const float & _arg)
  {
    this->dig_target_wt = _arg;
    return *this;
  }
  Type & set__start_of_weigh(
    const float & _arg)
  {
    this->start_of_weigh = _arg;
    return *this;
  }
  Type & set__tilt_comp_gain_scalar(
    const float & _arg)
  {
    this->tilt_comp_gain_scalar = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaWeighInitDebugChannel
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__LpsSaWeighInitDebugChannel
    std::shared_ptr<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaWeighInitDebugChannel_ & other) const
  {
    if (this->exec_rate != other.exec_rate) {
      return false;
    }
    if (this->cal_weight != other.cal_weight) {
      return false;
    }
    if (this->cal_status != other.cal_status) {
      return false;
    }
    if (this->cal_adjust != other.cal_adjust) {
      return false;
    }
    if (this->zero_weight != other.zero_weight) {
      return false;
    }
    if (this->dig_target_wt != other.dig_target_wt) {
      return false;
    }
    if (this->start_of_weigh != other.start_of_weigh) {
      return false;
    }
    if (this->tilt_comp_gain_scalar != other.tilt_comp_gain_scalar) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaWeighInitDebugChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaWeighInitDebugChannel_

// alias to use template instance with default allocator
using LpsSaWeighInitDebugChannel =
  weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__STRUCT_HPP_
