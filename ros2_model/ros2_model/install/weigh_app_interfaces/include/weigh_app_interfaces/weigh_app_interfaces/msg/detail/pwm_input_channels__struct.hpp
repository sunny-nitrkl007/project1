// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/PwmInputChannels.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/pwm_input_channels.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__PwmInputChannels __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__PwmInputChannels __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PwmInputChannels_
{
  using Type = PwmInputChannels_<ContainerAllocator>;

  explicit PwmInputChannels_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit PwmInputChannels_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _period_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _period_type period;
  using _width_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _width_type width;
  using _switch_status_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _switch_status_type switch_status;
  using _timeout_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _timeout_type timeout;

  // setters for named parameter idiom
  Type & set__period(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->period = _arg;
    return *this;
  }
  Type & set__width(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->width = _arg;
    return *this;
  }
  Type & set__switch_status(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->switch_status = _arg;
    return *this;
  }
  Type & set__timeout(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->timeout = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__PwmInputChannels
    std::shared_ptr<weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__PwmInputChannels
    std::shared_ptr<weigh_app_interfaces::msg::PwmInputChannels_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PwmInputChannels_ & other) const
  {
    if (this->period != other.period) {
      return false;
    }
    if (this->width != other.width) {
      return false;
    }
    if (this->switch_status != other.switch_status) {
      return false;
    }
    if (this->timeout != other.timeout) {
      return false;
    }
    return true;
  }
  bool operator!=(const PwmInputChannels_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PwmInputChannels_

// alias to use template instance with default allocator
using PwmInputChannels =
  weigh_app_interfaces::msg::PwmInputChannels_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__STRUCT_HPP_
