// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/AutonomyConditionDiagnosticsTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/autonomy_condition_diagnostics_tx_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/autonomy_condition_diagnostics_tx_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'sea_list'
#include "cpm_common_interfaces/msg/detail/sea__traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const AutonomyConditionDiagnosticsTxChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: time_point_ns
  {
    out << "time_point_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.time_point_ns, out);
    out << ", ";
  }

  // member: display_ethernet_bad
  {
    out << "display_ethernet_bad: ";
    rosidl_generator_traits::value_to_yaml(msg.display_ethernet_bad, out);
    out << ", ";
  }

  // member: product_link_ethernet_bad
  {
    out << "product_link_ethernet_bad: ";
    rosidl_generator_traits::value_to_yaml(msg.product_link_ethernet_bad, out);
    out << ", ";
  }

  // member: sea_list
  {
    if (msg.sea_list.size() == 0) {
      out << "sea_list: []";
    } else {
      out << "sea_list: [";
      size_t pending_items = msg.sea_list.size();
      for (auto item : msg.sea_list) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AutonomyConditionDiagnosticsTxChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: time_point_ns
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_point_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.time_point_ns, out);
    out << "\n";
  }

  // member: display_ethernet_bad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "display_ethernet_bad: ";
    rosidl_generator_traits::value_to_yaml(msg.display_ethernet_bad, out);
    out << "\n";
  }

  // member: product_link_ethernet_bad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "product_link_ethernet_bad: ";
    rosidl_generator_traits::value_to_yaml(msg.product_link_ethernet_bad, out);
    out << "\n";
  }

  // member: sea_list
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.sea_list.size() == 0) {
      out << "sea_list: []\n";
    } else {
      out << "sea_list:\n";
      for (auto item : msg.sea_list) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AutonomyConditionDiagnosticsTxChannel & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>()
{
  return "cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel";
}

template<>
inline const char * name<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>()
{
  return "cpm_common_interfaces/msg/AutonomyConditionDiagnosticsTxChannel";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__TRAITS_HPP_
