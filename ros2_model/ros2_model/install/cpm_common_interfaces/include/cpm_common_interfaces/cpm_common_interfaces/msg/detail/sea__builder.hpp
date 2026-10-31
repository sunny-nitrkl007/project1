// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/SEA.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/sea.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SEA__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SEA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/sea__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_SEA_status
{
public:
  explicit Init_SEA_status(::cpm_common_interfaces::msg::SEA & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::SEA status(::cpm_common_interfaces::msg::SEA::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::SEA msg_;
};

class Init_SEA_reason_code
{
public:
  explicit Init_SEA_reason_code(::cpm_common_interfaces::msg::SEA & msg)
  : msg_(msg)
  {}
  Init_SEA_status reason_code(::cpm_common_interfaces::msg::SEA::_reason_code_type arg)
  {
    msg_.reason_code = std::move(arg);
    return Init_SEA_status(msg_);
  }

private:
  ::cpm_common_interfaces::msg::SEA msg_;
};

class Init_SEA_free_count
{
public:
  Init_SEA_free_count()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SEA_reason_code free_count(::cpm_common_interfaces::msg::SEA::_free_count_type arg)
  {
    msg_.free_count = std::move(arg);
    return Init_SEA_reason_code(msg_);
  }

private:
  ::cpm_common_interfaces::msg::SEA msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::SEA>()
{
  return cpm_common_interfaces::msg::builder::Init_SEA_free_count();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SEA__BUILDER_HPP_
