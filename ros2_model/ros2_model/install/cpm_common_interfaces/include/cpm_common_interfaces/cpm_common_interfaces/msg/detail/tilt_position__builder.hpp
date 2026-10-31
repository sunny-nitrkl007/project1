// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/TiltPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/tilt_position.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__TILT_POSITION__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__TILT_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/tilt_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_TiltPosition_status
{
public:
  explicit Init_TiltPosition_status(::cpm_common_interfaces::msg::TiltPosition & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::TiltPosition status(::cpm_common_interfaces::msg::TiltPosition::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TiltPosition msg_;
};

class Init_TiltPosition_bucket_angle
{
public:
  explicit Init_TiltPosition_bucket_angle(::cpm_common_interfaces::msg::TiltPosition & msg)
  : msg_(msg)
  {}
  Init_TiltPosition_status bucket_angle(::cpm_common_interfaces::msg::TiltPosition::_bucket_angle_type arg)
  {
    msg_.bucket_angle = std::move(arg);
    return Init_TiltPosition_status(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TiltPosition msg_;
};

class Init_TiltPosition_cylinder_extension
{
public:
  explicit Init_TiltPosition_cylinder_extension(::cpm_common_interfaces::msg::TiltPosition & msg)
  : msg_(msg)
  {}
  Init_TiltPosition_bucket_angle cylinder_extension(::cpm_common_interfaces::msg::TiltPosition::_cylinder_extension_type arg)
  {
    msg_.cylinder_extension = std::move(arg);
    return Init_TiltPosition_bucket_angle(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TiltPosition msg_;
};

class Init_TiltPosition_percent_cylinder_length
{
public:
  explicit Init_TiltPosition_percent_cylinder_length(::cpm_common_interfaces::msg::TiltPosition & msg)
  : msg_(msg)
  {}
  Init_TiltPosition_cylinder_extension percent_cylinder_length(::cpm_common_interfaces::msg::TiltPosition::_percent_cylinder_length_type arg)
  {
    msg_.percent_cylinder_length = std::move(arg);
    return Init_TiltPosition_cylinder_extension(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TiltPosition msg_;
};

class Init_TiltPosition_cylinder_length
{
public:
  explicit Init_TiltPosition_cylinder_length(::cpm_common_interfaces::msg::TiltPosition & msg)
  : msg_(msg)
  {}
  Init_TiltPosition_percent_cylinder_length cylinder_length(::cpm_common_interfaces::msg::TiltPosition::_cylinder_length_type arg)
  {
    msg_.cylinder_length = std::move(arg);
    return Init_TiltPosition_percent_cylinder_length(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TiltPosition msg_;
};

class Init_TiltPosition_percent_angle
{
public:
  explicit Init_TiltPosition_percent_angle(::cpm_common_interfaces::msg::TiltPosition & msg)
  : msg_(msg)
  {}
  Init_TiltPosition_cylinder_length percent_angle(::cpm_common_interfaces::msg::TiltPosition::_percent_angle_type arg)
  {
    msg_.percent_angle = std::move(arg);
    return Init_TiltPosition_cylinder_length(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TiltPosition msg_;
};

class Init_TiltPosition_angle
{
public:
  Init_TiltPosition_angle()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TiltPosition_percent_angle angle(::cpm_common_interfaces::msg::TiltPosition::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return Init_TiltPosition_percent_angle(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TiltPosition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::TiltPosition>()
{
  return cpm_common_interfaces::msg::builder::Init_TiltPosition_angle();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__TILT_POSITION__BUILDER_HPP_
