// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cpm_common_interfaces:msg/AisJhm2TxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/ais_jhm2_tx_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__STRUCT_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'simplecal_data'
#include "cpm_common_interfaces/msg/detail/simple_cal_data_t__struct.hpp"
// Member 'tipoff_weight_adjust_data'
#include "cpm_common_interfaces/msg/detail/tipoff_weight_adjust_data__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cpm_common_interfaces__msg__AisJhm2TxChannel __attribute__((deprecated))
#else
# define DEPRECATED__cpm_common_interfaces__msg__AisJhm2TxChannel __declspec(deprecated)
#endif

namespace cpm_common_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AisJhm2TxChannel_
{
  using Type = AisJhm2TxChannel_<ContainerAllocator>;

  explicit AisJhm2TxChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : simplecal_data(_init),
    tipoff_weight_adjust_data(_init)
  {
    (void)_init;
  }

  explicit AisJhm2TxChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : simplecal_data(_alloc, _init),
    tipoff_weight_adjust_data(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _simplecal_data_type =
    cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator>;
  _simplecal_data_type simplecal_data;
  using _tipoff_weight_adjust_data_type =
    cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator>;
  _tipoff_weight_adjust_data_type tipoff_weight_adjust_data;

  // setters for named parameter idiom
  Type & set__simplecal_data(
    const cpm_common_interfaces::msg::SimpleCalDataT_<ContainerAllocator> & _arg)
  {
    this->simplecal_data = _arg;
    return *this;
  }
  Type & set__tipoff_weight_adjust_data(
    const cpm_common_interfaces::msg::TipoffWeightAdjustData_<ContainerAllocator> & _arg)
  {
    this->tipoff_weight_adjust_data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cpm_common_interfaces__msg__AisJhm2TxChannel
    std::shared_ptr<cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cpm_common_interfaces__msg__AisJhm2TxChannel
    std::shared_ptr<cpm_common_interfaces::msg::AisJhm2TxChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AisJhm2TxChannel_ & other) const
  {
    if (this->simplecal_data != other.simplecal_data) {
      return false;
    }
    if (this->tipoff_weight_adjust_data != other.tipoff_weight_adjust_data) {
      return false;
    }
    return true;
  }
  bool operator!=(const AisJhm2TxChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AisJhm2TxChannel_

// alias to use template instance with default allocator
using AisJhm2TxChannel =
  cpm_common_interfaces::msg::AisJhm2TxChannel_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__STRUCT_HPP_
