// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/DataLinkData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/data_link_data.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/data_link_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_DataLinkData_params
{
public:
  Init_DataLinkData_params()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::weigh_app_interfaces::msg::DataLinkData params(::weigh_app_interfaces::msg::DataLinkData::_params_type arg)
  {
    msg_.params = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DataLinkData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::DataLinkData>()
{
  return weigh_app_interfaces::msg::builder::Init_DataLinkData_params();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__BUILDER_HPP_
