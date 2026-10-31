// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/TruckReport.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/truck_report.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_REPORT__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_REPORT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/truck_report__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_TruckReport_reset_time_enabled
{
public:
  Init_TruckReport_reset_time_enabled()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::weigh_app_interfaces::msg::TruckReport reset_time_enabled(::weigh_app_interfaces::msg::TruckReport::_reset_time_enabled_type arg)
  {
    msg_.reset_time_enabled = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::TruckReport msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::TruckReport>()
{
  return weigh_app_interfaces::msg::builder::Init_TruckReport_reset_time_enabled();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_REPORT__BUILDER_HPP_
