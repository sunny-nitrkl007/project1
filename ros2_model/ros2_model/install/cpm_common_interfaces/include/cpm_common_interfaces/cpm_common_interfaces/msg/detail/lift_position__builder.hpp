// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LiftPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lift_position.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/lift_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LiftPosition_status
{
public:
  explicit Init_LiftPosition_status(::cpm_common_interfaces::msg::LiftPosition & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::LiftPosition status(::cpm_common_interfaces::msg::LiftPosition::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LiftPosition msg_;
};

class Init_LiftPosition_cylinder_extension
{
public:
  explicit Init_LiftPosition_cylinder_extension(::cpm_common_interfaces::msg::LiftPosition & msg)
  : msg_(msg)
  {}
  Init_LiftPosition_status cylinder_extension(::cpm_common_interfaces::msg::LiftPosition::_cylinder_extension_type arg)
  {
    msg_.cylinder_extension = std::move(arg);
    return Init_LiftPosition_status(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LiftPosition msg_;
};

class Init_LiftPosition_percent_cylinder_length
{
public:
  explicit Init_LiftPosition_percent_cylinder_length(::cpm_common_interfaces::msg::LiftPosition & msg)
  : msg_(msg)
  {}
  Init_LiftPosition_cylinder_extension percent_cylinder_length(::cpm_common_interfaces::msg::LiftPosition::_percent_cylinder_length_type arg)
  {
    msg_.percent_cylinder_length = std::move(arg);
    return Init_LiftPosition_cylinder_extension(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LiftPosition msg_;
};

class Init_LiftPosition_cylinder_length
{
public:
  explicit Init_LiftPosition_cylinder_length(::cpm_common_interfaces::msg::LiftPosition & msg)
  : msg_(msg)
  {}
  Init_LiftPosition_percent_cylinder_length cylinder_length(::cpm_common_interfaces::msg::LiftPosition::_cylinder_length_type arg)
  {
    msg_.cylinder_length = std::move(arg);
    return Init_LiftPosition_percent_cylinder_length(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LiftPosition msg_;
};

class Init_LiftPosition_percent_angle
{
public:
  explicit Init_LiftPosition_percent_angle(::cpm_common_interfaces::msg::LiftPosition & msg)
  : msg_(msg)
  {}
  Init_LiftPosition_cylinder_length percent_angle(::cpm_common_interfaces::msg::LiftPosition::_percent_angle_type arg)
  {
    msg_.percent_angle = std::move(arg);
    return Init_LiftPosition_cylinder_length(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LiftPosition msg_;
};

class Init_LiftPosition_angle
{
public:
  Init_LiftPosition_angle()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LiftPosition_percent_angle angle(::cpm_common_interfaces::msg::LiftPosition::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return Init_LiftPosition_percent_angle(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LiftPosition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LiftPosition>()
{
  return cpm_common_interfaces::msg::builder::Init_LiftPosition_angle();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__BUILDER_HPP_
