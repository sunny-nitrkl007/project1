// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/EcmVersionInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ecm_version_info.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/ecm_version_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_EcmVersionInfo_mac1
{
public:
  explicit Init_EcmVersionInfo_mac1(::weigh_app_interfaces::msg::EcmVersionInfo & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::EcmVersionInfo mac1(::weigh_app_interfaces::msg::EcmVersionInfo::_mac1_type arg)
  {
    msg_.mac1 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::EcmVersionInfo msg_;
};

class Init_EcmVersionInfo_mac0
{
public:
  explicit Init_EcmVersionInfo_mac0(::weigh_app_interfaces::msg::EcmVersionInfo & msg)
  : msg_(msg)
  {}
  Init_EcmVersionInfo_mac1 mac0(::weigh_app_interfaces::msg::EcmVersionInfo::_mac0_type arg)
  {
    msg_.mac0 = std::move(arg);
    return Init_EcmVersionInfo_mac1(msg_);
  }

private:
  ::weigh_app_interfaces::msg::EcmVersionInfo msg_;
};

class Init_EcmVersionInfo_dom
{
public:
  explicit Init_EcmVersionInfo_dom(::weigh_app_interfaces::msg::EcmVersionInfo & msg)
  : msg_(msg)
  {}
  Init_EcmVersionInfo_mac0 dom(::weigh_app_interfaces::msg::EcmVersionInfo::_dom_type arg)
  {
    msg_.dom = std::move(arg);
    return Init_EcmVersionInfo_mac0(msg_);
  }

private:
  ::weigh_app_interfaces::msg::EcmVersionInfo msg_;
};

class Init_EcmVersionInfo_part_num
{
public:
  explicit Init_EcmVersionInfo_part_num(::weigh_app_interfaces::msg::EcmVersionInfo & msg)
  : msg_(msg)
  {}
  Init_EcmVersionInfo_dom part_num(::weigh_app_interfaces::msg::EcmVersionInfo::_part_num_type arg)
  {
    msg_.part_num = std::move(arg);
    return Init_EcmVersionInfo_dom(msg_);
  }

private:
  ::weigh_app_interfaces::msg::EcmVersionInfo msg_;
};

class Init_EcmVersionInfo_serial_num
{
public:
  Init_EcmVersionInfo_serial_num()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EcmVersionInfo_part_num serial_num(::weigh_app_interfaces::msg::EcmVersionInfo::_serial_num_type arg)
  {
    msg_.serial_num = std::move(arg);
    return Init_EcmVersionInfo_part_num(msg_);
  }

private:
  ::weigh_app_interfaces::msg::EcmVersionInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::EcmVersionInfo>()
{
  return weigh_app_interfaces::msg::builder::Init_EcmVersionInfo_serial_num();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__ECM_VERSION_INFO__BUILDER_HPP_
