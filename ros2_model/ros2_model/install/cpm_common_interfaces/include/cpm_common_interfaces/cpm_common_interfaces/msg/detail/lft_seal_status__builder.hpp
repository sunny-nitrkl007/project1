// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LftSealStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lft_seal_status.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/lft_seal_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LftSealStatus_seal_id
{
public:
  explicit Init_LftSealStatus_seal_id(::cpm_common_interfaces::msg::LftSealStatus & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::LftSealStatus seal_id(::cpm_common_interfaces::msg::LftSealStatus::_seal_id_type arg)
  {
    msg_.seal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LftSealStatus msg_;
};

class Init_LftSealStatus_seal_time_ns
{
public:
  explicit Init_LftSealStatus_seal_time_ns(::cpm_common_interfaces::msg::LftSealStatus & msg)
  : msg_(msg)
  {}
  Init_LftSealStatus_seal_id seal_time_ns(::cpm_common_interfaces::msg::LftSealStatus::_seal_time_ns_type arg)
  {
    msg_.seal_time_ns = std::move(arg);
    return Init_LftSealStatus_seal_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LftSealStatus msg_;
};

class Init_LftSealStatus_sealed
{
public:
  Init_LftSealStatus_sealed()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LftSealStatus_seal_time_ns sealed(::cpm_common_interfaces::msg::LftSealStatus::_sealed_type arg)
  {
    msg_.sealed = std::move(arg);
    return Init_LftSealStatus_seal_time_ns(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LftSealStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LftSealStatus>()
{
  return cpm_common_interfaces::msg::builder::Init_LftSealStatus_sealed();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LFT_SEAL_STATUS__BUILDER_HPP_
