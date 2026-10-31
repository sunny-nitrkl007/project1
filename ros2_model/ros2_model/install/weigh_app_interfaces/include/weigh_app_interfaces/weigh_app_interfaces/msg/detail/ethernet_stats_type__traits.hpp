// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/EthernetStatsType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ethernet_stats_type.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/ethernet_stats_type__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const EthernetStatsType & msg,
  std::ostream & out)
{
  out << "{";
  // member: eth_interface_name
  {
    out << "eth_interface_name: ";
    rosidl_generator_traits::value_to_yaml(msg.eth_interface_name, out);
    out << ", ";
  }

  // member: tx_kbps
  {
    out << "tx_kbps: ";
    rosidl_generator_traits::value_to_yaml(msg.tx_kbps, out);
    out << ", ";
  }

  // member: rx_kbps
  {
    out << "rx_kbps: ";
    rosidl_generator_traits::value_to_yaml(msg.rx_kbps, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EthernetStatsType & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: eth_interface_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "eth_interface_name: ";
    rosidl_generator_traits::value_to_yaml(msg.eth_interface_name, out);
    out << "\n";
  }

  // member: tx_kbps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tx_kbps: ";
    rosidl_generator_traits::value_to_yaml(msg.tx_kbps, out);
    out << "\n";
  }

  // member: rx_kbps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rx_kbps: ";
    rosidl_generator_traits::value_to_yaml(msg.rx_kbps, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EthernetStatsType & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace weigh_app_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use weigh_app_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const weigh_app_interfaces::msg::EthernetStatsType & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::EthernetStatsType & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::EthernetStatsType>()
{
  return "weigh_app_interfaces::msg::EthernetStatsType";
}

template<>
inline const char * name<weigh_app_interfaces::msg::EthernetStatsType>()
{
  return "weigh_app_interfaces/msg/EthernetStatsType";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::EthernetStatsType>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::EthernetStatsType>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<weigh_app_interfaces::msg::EthernetStatsType>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__TRAITS_HPP_
