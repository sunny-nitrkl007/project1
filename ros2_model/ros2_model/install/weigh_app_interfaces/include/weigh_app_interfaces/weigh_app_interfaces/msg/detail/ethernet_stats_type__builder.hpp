// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/EthernetStatsType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ethernet_stats_type.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/ethernet_stats_type__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_EthernetStatsType_rx_kbps
{
public:
  explicit Init_EthernetStatsType_rx_kbps(::weigh_app_interfaces::msg::EthernetStatsType & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::EthernetStatsType rx_kbps(::weigh_app_interfaces::msg::EthernetStatsType::_rx_kbps_type arg)
  {
    msg_.rx_kbps = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::EthernetStatsType msg_;
};

class Init_EthernetStatsType_tx_kbps
{
public:
  explicit Init_EthernetStatsType_tx_kbps(::weigh_app_interfaces::msg::EthernetStatsType & msg)
  : msg_(msg)
  {}
  Init_EthernetStatsType_rx_kbps tx_kbps(::weigh_app_interfaces::msg::EthernetStatsType::_tx_kbps_type arg)
  {
    msg_.tx_kbps = std::move(arg);
    return Init_EthernetStatsType_rx_kbps(msg_);
  }

private:
  ::weigh_app_interfaces::msg::EthernetStatsType msg_;
};

class Init_EthernetStatsType_eth_interface_name
{
public:
  Init_EthernetStatsType_eth_interface_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EthernetStatsType_tx_kbps eth_interface_name(::weigh_app_interfaces::msg::EthernetStatsType::_eth_interface_name_type arg)
  {
    msg_.eth_interface_name = std::move(arg);
    return Init_EthernetStatsType_tx_kbps(msg_);
  }

private:
  ::weigh_app_interfaces::msg::EthernetStatsType msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::EthernetStatsType>()
{
  return weigh_app_interfaces::msg::builder::Init_EthernetStatsType_eth_interface_name();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__BUILDER_HPP_
