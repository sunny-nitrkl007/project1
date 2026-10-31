// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaTotalsPrinterCnfgInterfaceStorage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_totals_printer_cnfg_interface_storage.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_totals_printer_cnfg_interface_storage__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'config'
#include "weigh_app_interfaces/msg/detail/lps_sa_totals_printer_cnfg__traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaTotalsPrinterCnfgInterfaceStorage & msg,
  std::ostream & out)
{
  out << "{";
  // member: config
  {
    out << "config: ";
    to_flow_style_yaml(msg.config, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaTotalsPrinterCnfgInterfaceStorage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: config
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "config:\n";
    to_block_style_yaml(msg.config, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaTotalsPrinterCnfgInterfaceStorage & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage>()
{
  return "weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage>()
{
  return "weigh_app_interfaces/msg/LpsSaTotalsPrinterCnfgInterfaceStorage";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage>
  : std::integral_constant<bool, has_fixed_size<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg>::value> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage>
  : std::integral_constant<bool, has_bounded_size<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg>::value> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__TRAITS_HPP_
