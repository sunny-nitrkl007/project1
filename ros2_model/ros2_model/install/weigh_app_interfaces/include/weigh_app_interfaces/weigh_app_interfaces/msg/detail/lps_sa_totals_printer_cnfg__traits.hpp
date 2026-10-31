// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaTotalsPrinterCnfg.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_totals_printer_cnfg.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_totals_printer_cnfg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'truck_ticket'
#include "weigh_app_interfaces/msg/detail/truck_ticket__traits.hpp"
// Member 'truck_report'
#include "weigh_app_interfaces/msg/detail/truck_report__traits.hpp"
// Member 'material_report'
#include "weigh_app_interfaces/msg/detail/material_report__traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaTotalsPrinterCnfg & msg,
  std::ostream & out)
{
  out << "{";
  // member: installed
  {
    out << "installed: ";
    rosidl_generator_traits::value_to_yaml(msg.installed, out);
    out << ", ";
  }

  // member: leading_blank_lines
  {
    out << "leading_blank_lines: ";
    rosidl_generator_traits::value_to_yaml(msg.leading_blank_lines, out);
    out << ", ";
  }

  // member: trailing_blank_lines
  {
    out << "trailing_blank_lines: ";
    rosidl_generator_traits::value_to_yaml(msg.trailing_blank_lines, out);
    out << ", ";
  }

  // member: date_format
  {
    out << "date_format: ";
    rosidl_generator_traits::value_to_yaml(msg.date_format, out);
    out << ", ";
  }

  // member: date_separator
  {
    out << "date_separator: ";
    rosidl_generator_traits::value_to_yaml(msg.date_separator, out);
    out << ", ";
  }

  // member: truck_ticket
  {
    out << "truck_ticket: ";
    to_flow_style_yaml(msg.truck_ticket, out);
    out << ", ";
  }

  // member: truck_report
  {
    out << "truck_report: ";
    to_flow_style_yaml(msg.truck_report, out);
    out << ", ";
  }

  // member: material_report
  {
    out << "material_report: ";
    to_flow_style_yaml(msg.material_report, out);
    out << ", ";
  }

  // member: udp_transfer_ip
  {
    out << "udp_transfer_ip: ";
    rosidl_generator_traits::value_to_yaml(msg.udp_transfer_ip, out);
    out << ", ";
  }

  // member: udp_transfer_port
  {
    out << "udp_transfer_port: ";
    rosidl_generator_traits::value_to_yaml(msg.udp_transfer_port, out);
    out << ", ";
  }

  // member: udp_transfer_enabled
  {
    out << "udp_transfer_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.udp_transfer_enabled, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaTotalsPrinterCnfg & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: installed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "installed: ";
    rosidl_generator_traits::value_to_yaml(msg.installed, out);
    out << "\n";
  }

  // member: leading_blank_lines
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "leading_blank_lines: ";
    rosidl_generator_traits::value_to_yaml(msg.leading_blank_lines, out);
    out << "\n";
  }

  // member: trailing_blank_lines
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "trailing_blank_lines: ";
    rosidl_generator_traits::value_to_yaml(msg.trailing_blank_lines, out);
    out << "\n";
  }

  // member: date_format
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "date_format: ";
    rosidl_generator_traits::value_to_yaml(msg.date_format, out);
    out << "\n";
  }

  // member: date_separator
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "date_separator: ";
    rosidl_generator_traits::value_to_yaml(msg.date_separator, out);
    out << "\n";
  }

  // member: truck_ticket
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_ticket:\n";
    to_block_style_yaml(msg.truck_ticket, out, indentation + 2);
  }

  // member: truck_report
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_report:\n";
    to_block_style_yaml(msg.truck_report, out, indentation + 2);
  }

  // member: material_report
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "material_report:\n";
    to_block_style_yaml(msg.material_report, out, indentation + 2);
  }

  // member: udp_transfer_ip
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "udp_transfer_ip: ";
    rosidl_generator_traits::value_to_yaml(msg.udp_transfer_ip, out);
    out << "\n";
  }

  // member: udp_transfer_port
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "udp_transfer_port: ";
    rosidl_generator_traits::value_to_yaml(msg.udp_transfer_port, out);
    out << "\n";
  }

  // member: udp_transfer_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "udp_transfer_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.udp_transfer_enabled, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaTotalsPrinterCnfg & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg>()
{
  return "weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg>()
{
  return "weigh_app_interfaces/msg/LpsSaTotalsPrinterCnfg";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__TRAITS_HPP_
