// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/AutonomyConditionDiagnosticsTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/autonomy_condition_diagnostics_tx_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/autonomy_condition_diagnostics_tx_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_AutonomyConditionDiagnosticsTxChannel_sea_list
{
public:
  explicit Init_AutonomyConditionDiagnosticsTxChannel_sea_list(::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel sea_list(::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel::_sea_list_type arg)
  {
    msg_.sea_list = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel msg_;
};

class Init_AutonomyConditionDiagnosticsTxChannel_product_link_ethernet_bad
{
public:
  explicit Init_AutonomyConditionDiagnosticsTxChannel_product_link_ethernet_bad(::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel & msg)
  : msg_(msg)
  {}
  Init_AutonomyConditionDiagnosticsTxChannel_sea_list product_link_ethernet_bad(::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel::_product_link_ethernet_bad_type arg)
  {
    msg_.product_link_ethernet_bad = std::move(arg);
    return Init_AutonomyConditionDiagnosticsTxChannel_sea_list(msg_);
  }

private:
  ::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel msg_;
};

class Init_AutonomyConditionDiagnosticsTxChannel_display_ethernet_bad
{
public:
  explicit Init_AutonomyConditionDiagnosticsTxChannel_display_ethernet_bad(::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel & msg)
  : msg_(msg)
  {}
  Init_AutonomyConditionDiagnosticsTxChannel_product_link_ethernet_bad display_ethernet_bad(::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel::_display_ethernet_bad_type arg)
  {
    msg_.display_ethernet_bad = std::move(arg);
    return Init_AutonomyConditionDiagnosticsTxChannel_product_link_ethernet_bad(msg_);
  }

private:
  ::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel msg_;
};

class Init_AutonomyConditionDiagnosticsTxChannel_time_point_ns
{
public:
  Init_AutonomyConditionDiagnosticsTxChannel_time_point_ns()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AutonomyConditionDiagnosticsTxChannel_display_ethernet_bad time_point_ns(::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel::_time_point_ns_type arg)
  {
    msg_.time_point_ns = std::move(arg);
    return Init_AutonomyConditionDiagnosticsTxChannel_display_ethernet_bad(msg_);
  }

private:
  ::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>()
{
  return cpm_common_interfaces::msg::builder::Init_AutonomyConditionDiagnosticsTxChannel_time_point_ns();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__BUILDER_HPP_
