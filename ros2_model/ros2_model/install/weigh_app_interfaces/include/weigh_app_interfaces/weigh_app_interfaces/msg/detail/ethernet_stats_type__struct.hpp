// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from weigh_app_interfaces:msg/EthernetStatsType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ethernet_stats_type.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__STRUCT_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__weigh_app_interfaces__msg__EthernetStatsType __attribute__((deprecated))
#else
# define DEPRECATED__weigh_app_interfaces__msg__EthernetStatsType __declspec(deprecated)
#endif

namespace weigh_app_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EthernetStatsType_
{
  using Type = EthernetStatsType_<ContainerAllocator>;

  explicit EthernetStatsType_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->eth_interface_name = "";
      this->tx_kbps = 0.0;
      this->rx_kbps = 0.0;
    }
  }

  explicit EthernetStatsType_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : eth_interface_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->eth_interface_name = "";
      this->tx_kbps = 0.0;
      this->rx_kbps = 0.0;
    }
  }

  // field types and members
  using _eth_interface_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _eth_interface_name_type eth_interface_name;
  using _tx_kbps_type =
    double;
  _tx_kbps_type tx_kbps;
  using _rx_kbps_type =
    double;
  _rx_kbps_type rx_kbps;

  // setters for named parameter idiom
  Type & set__eth_interface_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->eth_interface_name = _arg;
    return *this;
  }
  Type & set__tx_kbps(
    const double & _arg)
  {
    this->tx_kbps = _arg;
    return *this;
  }
  Type & set__rx_kbps(
    const double & _arg)
  {
    this->rx_kbps = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator> *;
  using ConstRawPtr =
    const weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__weigh_app_interfaces__msg__EthernetStatsType
    std::shared_ptr<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__weigh_app_interfaces__msg__EthernetStatsType
    std::shared_ptr<weigh_app_interfaces::msg::EthernetStatsType_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EthernetStatsType_ & other) const
  {
    if (this->eth_interface_name != other.eth_interface_name) {
      return false;
    }
    if (this->tx_kbps != other.tx_kbps) {
      return false;
    }
    if (this->rx_kbps != other.rx_kbps) {
      return false;
    }
    return true;
  }
  bool operator!=(const EthernetStatsType_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EthernetStatsType_

// alias to use template instance with default allocator
using EthernetStatsType =
  weigh_app_interfaces::msg::EthernetStatsType_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__STRUCT_HPP_
