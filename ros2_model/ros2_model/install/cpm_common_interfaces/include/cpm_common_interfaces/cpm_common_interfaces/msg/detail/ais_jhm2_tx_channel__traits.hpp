// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/AisJhm2TxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/ais_jhm2_tx_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/ais_jhm2_tx_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'simplecal_data'
#include "cpm_common_interfaces/msg/detail/simple_cal_data_t__traits.hpp"
// Member 'tipoff_weight_adjust_data'
#include "cpm_common_interfaces/msg/detail/tipoff_weight_adjust_data__traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const AisJhm2TxChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: simplecal_data
  {
    out << "simplecal_data: ";
    to_flow_style_yaml(msg.simplecal_data, out);
    out << ", ";
  }

  // member: tipoff_weight_adjust_data
  {
    out << "tipoff_weight_adjust_data: ";
    to_flow_style_yaml(msg.tipoff_weight_adjust_data, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AisJhm2TxChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: simplecal_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "simplecal_data:\n";
    to_block_style_yaml(msg.simplecal_data, out, indentation + 2);
  }

  // member: tipoff_weight_adjust_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tipoff_weight_adjust_data:\n";
    to_block_style_yaml(msg.tipoff_weight_adjust_data, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AisJhm2TxChannel & msg, bool use_flow_style = false)
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

}  // namespace cpm_common_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cpm_common_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cpm_common_interfaces::msg::AisJhm2TxChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::AisJhm2TxChannel & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::AisJhm2TxChannel>()
{
  return "cpm_common_interfaces::msg::AisJhm2TxChannel";
}

template<>
inline const char * name<cpm_common_interfaces::msg::AisJhm2TxChannel>()
{
  return "cpm_common_interfaces/msg/AisJhm2TxChannel";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::AisJhm2TxChannel>
  : std::integral_constant<bool, has_fixed_size<cpm_common_interfaces::msg::SimpleCalDataT>::value && has_fixed_size<cpm_common_interfaces::msg::TipoffWeightAdjustData>::value> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::AisJhm2TxChannel>
  : std::integral_constant<bool, has_bounded_size<cpm_common_interfaces::msg::SimpleCalDataT>::value && has_bounded_size<cpm_common_interfaces::msg::TipoffWeightAdjustData>::value> {};

template<>
struct is_message<cpm_common_interfaces::msg::AisJhm2TxChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__TRAITS_HPP_
