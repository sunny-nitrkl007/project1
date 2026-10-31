// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaTotalsPrinterCnfgInterfaceStorage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_totals_printer_cnfg_interface_storage.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/lps_sa_totals_printer_cnfg_interface_storage__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaTotalsPrinterCnfgInterfaceStorage_config
{
public:
  Init_LpsSaTotalsPrinterCnfgInterfaceStorage_config()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage config(::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage::_config_type arg)
  {
    msg_.config = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::LpsSaTotalsPrinterCnfgInterfaceStorage>()
{
  return weigh_app_interfaces::msg::builder::Init_LpsSaTotalsPrinterCnfgInterfaceStorage_config();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__BUILDER_HPP_
