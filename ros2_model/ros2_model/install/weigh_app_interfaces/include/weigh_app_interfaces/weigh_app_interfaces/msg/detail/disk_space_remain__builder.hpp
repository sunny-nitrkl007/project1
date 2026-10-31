// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/DiskSpaceRemain.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/disk_space_remain.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DISK_SPACE_REMAIN__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DISK_SPACE_REMAIN__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/disk_space_remain__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_DiskSpaceRemain_percent_use
{
public:
  explicit Init_DiskSpaceRemain_percent_use(::weigh_app_interfaces::msg::DiskSpaceRemain & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::DiskSpaceRemain percent_use(::weigh_app_interfaces::msg::DiskSpaceRemain::_percent_use_type arg)
  {
    msg_.percent_use = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DiskSpaceRemain msg_;
};

class Init_DiskSpaceRemain_avail_kb
{
public:
  explicit Init_DiskSpaceRemain_avail_kb(::weigh_app_interfaces::msg::DiskSpaceRemain & msg)
  : msg_(msg)
  {}
  Init_DiskSpaceRemain_percent_use avail_kb(::weigh_app_interfaces::msg::DiskSpaceRemain::_avail_kb_type arg)
  {
    msg_.avail_kb = std::move(arg);
    return Init_DiskSpaceRemain_percent_use(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DiskSpaceRemain msg_;
};

class Init_DiskSpaceRemain_filesystem
{
public:
  Init_DiskSpaceRemain_filesystem()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DiskSpaceRemain_avail_kb filesystem(::weigh_app_interfaces::msg::DiskSpaceRemain::_filesystem_type arg)
  {
    msg_.filesystem = std::move(arg);
    return Init_DiskSpaceRemain_avail_kb(msg_);
  }

private:
  ::weigh_app_interfaces::msg::DiskSpaceRemain msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::DiskSpaceRemain>()
{
  return weigh_app_interfaces::msg::builder::Init_DiskSpaceRemain_filesystem();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DISK_SPACE_REMAIN__BUILDER_HPP_
