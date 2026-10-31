// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/Payload.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/payload.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/payload__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_Payload_payload_ratio_status
{
public:
  explicit Init_Payload_payload_ratio_status(::cpm_common_interfaces::msg::Payload & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::Payload payload_ratio_status(::cpm_common_interfaces::msg::Payload::_payload_ratio_status_type arg)
  {
    msg_.payload_ratio_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::Payload msg_;
};

class Init_Payload_payload_ratio
{
public:
  explicit Init_Payload_payload_ratio(::cpm_common_interfaces::msg::Payload & msg)
  : msg_(msg)
  {}
  Init_Payload_payload_ratio_status payload_ratio(::cpm_common_interfaces::msg::Payload::_payload_ratio_type arg)
  {
    msg_.payload_ratio = std::move(arg);
    return Init_Payload_payload_ratio_status(msg_);
  }

private:
  ::cpm_common_interfaces::msg::Payload msg_;
};

class Init_Payload_payload_ratio_raw
{
public:
  Init_Payload_payload_ratio_raw()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Payload_payload_ratio payload_ratio_raw(::cpm_common_interfaces::msg::Payload::_payload_ratio_raw_type arg)
  {
    msg_.payload_ratio_raw = std::move(arg);
    return Init_Payload_payload_ratio(msg_);
  }

private:
  ::cpm_common_interfaces::msg::Payload msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::Payload>()
{
  return cpm_common_interfaces::msg::builder::Init_Payload_payload_ratio_raw();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__BUILDER_HPP_
