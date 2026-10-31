// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaTotalsPrinterCnfg.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_totals_printer_cnfg.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_totals_printer_cnfg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaTotalsPrinterCnfg_udp_transfer_enabled
{
public:
  explicit Init_LpsSaTotalsPrinterCnfg_udp_transfer_enabled(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg udp_transfer_enabled(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg::_udp_transfer_enabled_type arg)
  {
    msg_.udp_transfer_enabled = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg msg_;
};

class Init_LpsSaTotalsPrinterCnfg_udp_transfer_port
{
public:
  explicit Init_LpsSaTotalsPrinterCnfg_udp_transfer_port(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg)
  : msg_(msg)
  {}
  Init_LpsSaTotalsPrinterCnfg_udp_transfer_enabled udp_transfer_port(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg::_udp_transfer_port_type arg)
  {
    msg_.udp_transfer_port = std::move(arg);
    return Init_LpsSaTotalsPrinterCnfg_udp_transfer_enabled(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg msg_;
};

class Init_LpsSaTotalsPrinterCnfg_udp_transfer_ip
{
public:
  explicit Init_LpsSaTotalsPrinterCnfg_udp_transfer_ip(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg)
  : msg_(msg)
  {}
  Init_LpsSaTotalsPrinterCnfg_udp_transfer_port udp_transfer_ip(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg::_udp_transfer_ip_type arg)
  {
    msg_.udp_transfer_ip = std::move(arg);
    return Init_LpsSaTotalsPrinterCnfg_udp_transfer_port(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg msg_;
};

class Init_LpsSaTotalsPrinterCnfg_material_report
{
public:
  explicit Init_LpsSaTotalsPrinterCnfg_material_report(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg)
  : msg_(msg)
  {}
  Init_LpsSaTotalsPrinterCnfg_udp_transfer_ip material_report(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg::_material_report_type arg)
  {
    msg_.material_report = std::move(arg);
    return Init_LpsSaTotalsPrinterCnfg_udp_transfer_ip(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg msg_;
};

class Init_LpsSaTotalsPrinterCnfg_truck_report
{
public:
  explicit Init_LpsSaTotalsPrinterCnfg_truck_report(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg)
  : msg_(msg)
  {}
  Init_LpsSaTotalsPrinterCnfg_material_report truck_report(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg::_truck_report_type arg)
  {
    msg_.truck_report = std::move(arg);
    return Init_LpsSaTotalsPrinterCnfg_material_report(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg msg_;
};

class Init_LpsSaTotalsPrinterCnfg_truck_ticket
{
public:
  explicit Init_LpsSaTotalsPrinterCnfg_truck_ticket(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg)
  : msg_(msg)
  {}
  Init_LpsSaTotalsPrinterCnfg_truck_report truck_ticket(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg::_truck_ticket_type arg)
  {
    msg_.truck_ticket = std::move(arg);
    return Init_LpsSaTotalsPrinterCnfg_truck_report(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg msg_;
};

class Init_LpsSaTotalsPrinterCnfg_date_separator
{
public:
  explicit Init_LpsSaTotalsPrinterCnfg_date_separator(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg)
  : msg_(msg)
  {}
  Init_LpsSaTotalsPrinterCnfg_truck_ticket date_separator(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg::_date_separator_type arg)
  {
    msg_.date_separator = std::move(arg);
    return Init_LpsSaTotalsPrinterCnfg_truck_ticket(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg msg_;
};

class Init_LpsSaTotalsPrinterCnfg_date_format
{
public:
  explicit Init_LpsSaTotalsPrinterCnfg_date_format(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg)
  : msg_(msg)
  {}
  Init_LpsSaTotalsPrinterCnfg_date_separator date_format(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg::_date_format_type arg)
  {
    msg_.date_format = std::move(arg);
    return Init_LpsSaTotalsPrinterCnfg_date_separator(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg msg_;
};

class Init_LpsSaTotalsPrinterCnfg_trailing_blank_lines
{
public:
  explicit Init_LpsSaTotalsPrinterCnfg_trailing_blank_lines(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg)
  : msg_(msg)
  {}
  Init_LpsSaTotalsPrinterCnfg_date_format trailing_blank_lines(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg::_trailing_blank_lines_type arg)
  {
    msg_.trailing_blank_lines = std::move(arg);
    return Init_LpsSaTotalsPrinterCnfg_date_format(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg msg_;
};

class Init_LpsSaTotalsPrinterCnfg_leading_blank_lines
{
public:
  explicit Init_LpsSaTotalsPrinterCnfg_leading_blank_lines(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg & msg)
  : msg_(msg)
  {}
  Init_LpsSaTotalsPrinterCnfg_trailing_blank_lines leading_blank_lines(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg::_leading_blank_lines_type arg)
  {
    msg_.leading_blank_lines = std::move(arg);
    return Init_LpsSaTotalsPrinterCnfg_trailing_blank_lines(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg msg_;
};

class Init_LpsSaTotalsPrinterCnfg_installed
{
public:
  Init_LpsSaTotalsPrinterCnfg_installed()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaTotalsPrinterCnfg_leading_blank_lines installed(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg::_installed_type arg)
  {
    msg_.installed = std::move(arg);
    return Init_LpsSaTotalsPrinterCnfg_leading_blank_lines(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfg>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaTotalsPrinterCnfg_installed();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__BUILDER_HPP_
