// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/FloatPair.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/float_pair.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_PAIR__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_PAIR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/float_pair__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_FloatPair_second
{
public:
  explicit Init_FloatPair_second(::cpm_common_interfaces::msg::FloatPair & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::FloatPair second(::cpm_common_interfaces::msg::FloatPair::_second_type arg)
  {
    msg_.second = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::FloatPair msg_;
};

class Init_FloatPair_first
{
public:
  Init_FloatPair_first()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FloatPair_second first(::cpm_common_interfaces::msg::FloatPair::_first_type arg)
  {
    msg_.first = std::move(arg);
    return Init_FloatPair_second(msg_);
  }

private:
  ::cpm_common_interfaces::msg::FloatPair msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::FloatPair>()
{
  return cpm_common_interfaces::msg::builder::Init_FloatPair_first();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_PAIR__BUILDER_HPP_
