// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/DemoAppTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/demo_app_tx_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__DemoAppTxChannel __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__DemoAppTxChannel __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DemoAppTxChannel_
{
  using Type = DemoAppTxChannel_<ContainerAllocator>;

  explicit DemoAppTxChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->liftposition = 0.0f;
      this->liftposition_rate = 0.0f;
      this->tiltposition = 0.0f;
      this->tiltposition_rate = 0.0f;
      this->payload = 0.0f;
      this->payload_rate = 0.0f;
      this->dig = false;
      this->wrw = false;
      this->llw = false;
      this->dump = false;
      this->pdump = false;
      this->rack = false;
      this->carry = false;
      this->weight1 = 0.0f;
      this->pres_lift_he_demo = 0.0f;
      this->pres_lift_re_demo = 0.0f;
      this->angle_lift_demo = 0.0f;
      this->angle_afe_demo = 0.0f;
      this->angle_abc_demo = 0.0f;
    }
  }

  explicit DemoAppTxChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->liftposition = 0.0f;
      this->liftposition_rate = 0.0f;
      this->tiltposition = 0.0f;
      this->tiltposition_rate = 0.0f;
      this->payload = 0.0f;
      this->payload_rate = 0.0f;
      this->dig = false;
      this->wrw = false;
      this->llw = false;
      this->dump = false;
      this->pdump = false;
      this->rack = false;
      this->carry = false;
      this->weight1 = 0.0f;
      this->pres_lift_he_demo = 0.0f;
      this->pres_lift_re_demo = 0.0f;
      this->angle_lift_demo = 0.0f;
      this->angle_afe_demo = 0.0f;
      this->angle_abc_demo = 0.0f;
    }
  }

  // field types and members
  using _liftposition_type =
    float;
  _liftposition_type liftposition;
  using _liftposition_rate_type =
    float;
  _liftposition_rate_type liftposition_rate;
  using _tiltposition_type =
    float;
  _tiltposition_type tiltposition;
  using _tiltposition_rate_type =
    float;
  _tiltposition_rate_type tiltposition_rate;
  using _payload_type =
    float;
  _payload_type payload;
  using _payload_rate_type =
    float;
  _payload_rate_type payload_rate;
  using _dig_type =
    bool;
  _dig_type dig;
  using _wrw_type =
    bool;
  _wrw_type wrw;
  using _llw_type =
    bool;
  _llw_type llw;
  using _dump_type =
    bool;
  _dump_type dump;
  using _pdump_type =
    bool;
  _pdump_type pdump;
  using _rack_type =
    bool;
  _rack_type rack;
  using _carry_type =
    bool;
  _carry_type carry;
  using _weight1_type =
    float;
  _weight1_type weight1;
  using _pres_lift_he_demo_type =
    float;
  _pres_lift_he_demo_type pres_lift_he_demo;
  using _pres_lift_re_demo_type =
    float;
  _pres_lift_re_demo_type pres_lift_re_demo;
  using _angle_lift_demo_type =
    float;
  _angle_lift_demo_type angle_lift_demo;
  using _angle_afe_demo_type =
    float;
  _angle_afe_demo_type angle_afe_demo;
  using _angle_abc_demo_type =
    float;
  _angle_abc_demo_type angle_abc_demo;

  // setters for named parameter idiom
  Type & set__liftposition(
    const float & _arg)
  {
    this->liftposition = _arg;
    return *this;
  }
  Type & set__liftposition_rate(
    const float & _arg)
  {
    this->liftposition_rate = _arg;
    return *this;
  }
  Type & set__tiltposition(
    const float & _arg)
  {
    this->tiltposition = _arg;
    return *this;
  }
  Type & set__tiltposition_rate(
    const float & _arg)
  {
    this->tiltposition_rate = _arg;
    return *this;
  }
  Type & set__payload(
    const float & _arg)
  {
    this->payload = _arg;
    return *this;
  }
  Type & set__payload_rate(
    const float & _arg)
  {
    this->payload_rate = _arg;
    return *this;
  }
  Type & set__dig(
    const bool & _arg)
  {
    this->dig = _arg;
    return *this;
  }
  Type & set__wrw(
    const bool & _arg)
  {
    this->wrw = _arg;
    return *this;
  }
  Type & set__llw(
    const bool & _arg)
  {
    this->llw = _arg;
    return *this;
  }
  Type & set__dump(
    const bool & _arg)
  {
    this->dump = _arg;
    return *this;
  }
  Type & set__pdump(
    const bool & _arg)
  {
    this->pdump = _arg;
    return *this;
  }
  Type & set__rack(
    const bool & _arg)
  {
    this->rack = _arg;
    return *this;
  }
  Type & set__carry(
    const bool & _arg)
  {
    this->carry = _arg;
    return *this;
  }
  Type & set__weight1(
    const float & _arg)
  {
    this->weight1 = _arg;
    return *this;
  }
  Type & set__pres_lift_he_demo(
    const float & _arg)
  {
    this->pres_lift_he_demo = _arg;
    return *this;
  }
  Type & set__pres_lift_re_demo(
    const float & _arg)
  {
    this->pres_lift_re_demo = _arg;
    return *this;
  }
  Type & set__angle_lift_demo(
    const float & _arg)
  {
    this->angle_lift_demo = _arg;
    return *this;
  }
  Type & set__angle_afe_demo(
    const float & _arg)
  {
    this->angle_afe_demo = _arg;
    return *this;
  }
  Type & set__angle_abc_demo(
    const float & _arg)
  {
    this->angle_abc_demo = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__DemoAppTxChannel
    std::shared_ptr<weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__DemoAppTxChannel
    std::shared_ptr<weigh_app_interfaces::msg::DemoAppTxChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DemoAppTxChannel_ & other) const
  {
    if (this->liftposition != other.liftposition) {
      return false;
    }
    if (this->liftposition_rate != other.liftposition_rate) {
      return false;
    }
    if (this->tiltposition != other.tiltposition) {
      return false;
    }
    if (this->tiltposition_rate != other.tiltposition_rate) {
      return false;
    }
    if (this->payload != other.payload) {
      return false;
    }
    if (this->payload_rate != other.payload_rate) {
      return false;
    }
    if (this->dig != other.dig) {
      return false;
    }
    if (this->wrw != other.wrw) {
      return false;
    }
    if (this->llw != other.llw) {
      return false;
    }
    if (this->dump != other.dump) {
      return false;
    }
    if (this->pdump != other.pdump) {
      return false;
    }
    if (this->rack != other.rack) {
      return false;
    }
    if (this->carry != other.carry) {
      return false;
    }
    if (this->weight1 != other.weight1) {
      return false;
    }
    if (this->pres_lift_he_demo != other.pres_lift_he_demo) {
      return false;
    }
    if (this->pres_lift_re_demo != other.pres_lift_re_demo) {
      return false;
    }
    if (this->angle_lift_demo != other.angle_lift_demo) {
      return false;
    }
    if (this->angle_afe_demo != other.angle_afe_demo) {
      return false;
    }
    if (this->angle_abc_demo != other.angle_abc_demo) {
      return false;
    }
    return true;
  }
  bool operator!=(const DemoAppTxChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DemoAppTxChannel_

// alias to use template instance with default allocator
using DemoAppTxChannel =
  weigh_app_interfaces::msg::DemoAppTxChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__STRUCT_HPP_
