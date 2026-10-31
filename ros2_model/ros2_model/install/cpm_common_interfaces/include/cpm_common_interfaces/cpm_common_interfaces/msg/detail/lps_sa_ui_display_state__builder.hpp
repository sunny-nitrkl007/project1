// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaUIDisplayState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_ui_display_state.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/lps_sa_ui_display_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaUIDisplayState_settings
{
public:
  explicit Init_LpsSaUIDisplayState_settings(::cpm_common_interfaces::msg::LpsSaUIDisplayState & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::LpsSaUIDisplayState settings(::cpm_common_interfaces::msg::LpsSaUIDisplayState::_settings_type arg)
  {
    msg_.settings = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplayState msg_;
};

class Init_LpsSaUIDisplayState_weight_interval
{
public:
  explicit Init_LpsSaUIDisplayState_weight_interval(::cpm_common_interfaces::msg::LpsSaUIDisplayState & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplayState_settings weight_interval(::cpm_common_interfaces::msg::LpsSaUIDisplayState::_weight_interval_type arg)
  {
    msg_.weight_interval = std::move(arg);
    return Init_LpsSaUIDisplayState_settings(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplayState msg_;
};

class Init_LpsSaUIDisplayState_weight_decimal_precision
{
public:
  explicit Init_LpsSaUIDisplayState_weight_decimal_precision(::cpm_common_interfaces::msg::LpsSaUIDisplayState & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplayState_weight_interval weight_decimal_precision(::cpm_common_interfaces::msg::LpsSaUIDisplayState::_weight_decimal_precision_type arg)
  {
    msg_.weight_decimal_precision = std::move(arg);
    return Init_LpsSaUIDisplayState_weight_interval(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplayState msg_;
};

class Init_LpsSaUIDisplayState_weight_capacity
{
public:
  explicit Init_LpsSaUIDisplayState_weight_capacity(::cpm_common_interfaces::msg::LpsSaUIDisplayState & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplayState_weight_decimal_precision weight_capacity(::cpm_common_interfaces::msg::LpsSaUIDisplayState::_weight_capacity_type arg)
  {
    msg_.weight_capacity = std::move(arg);
    return Init_LpsSaUIDisplayState_weight_decimal_precision(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplayState msg_;
};

class Init_LpsSaUIDisplayState_document_id
{
public:
  explicit Init_LpsSaUIDisplayState_document_id(::cpm_common_interfaces::msg::LpsSaUIDisplayState & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplayState_weight_capacity document_id(::cpm_common_interfaces::msg::LpsSaUIDisplayState::_document_id_type arg)
  {
    msg_.document_id = std::move(arg);
    return Init_LpsSaUIDisplayState_weight_capacity(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplayState msg_;
};

class Init_LpsSaUIDisplayState_heartbeat_count
{
public:
  explicit Init_LpsSaUIDisplayState_heartbeat_count(::cpm_common_interfaces::msg::LpsSaUIDisplayState & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplayState_document_id heartbeat_count(::cpm_common_interfaces::msg::LpsSaUIDisplayState::_heartbeat_count_type arg)
  {
    msg_.heartbeat_count = std::move(arg);
    return Init_LpsSaUIDisplayState_document_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplayState msg_;
};

class Init_LpsSaUIDisplayState_in_verification_mode
{
public:
  explicit Init_LpsSaUIDisplayState_in_verification_mode(::cpm_common_interfaces::msg::LpsSaUIDisplayState & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplayState_heartbeat_count in_verification_mode(::cpm_common_interfaces::msg::LpsSaUIDisplayState::_in_verification_mode_type arg)
  {
    msg_.in_verification_mode = std::move(arg);
    return Init_LpsSaUIDisplayState_heartbeat_count(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplayState msg_;
};

class Init_LpsSaUIDisplayState_in_service_mode
{
public:
  explicit Init_LpsSaUIDisplayState_in_service_mode(::cpm_common_interfaces::msg::LpsSaUIDisplayState & msg)
  : msg_(msg)
  {}
  Init_LpsSaUIDisplayState_in_verification_mode in_service_mode(::cpm_common_interfaces::msg::LpsSaUIDisplayState::_in_service_mode_type arg)
  {
    msg_.in_service_mode = std::move(arg);
    return Init_LpsSaUIDisplayState_in_verification_mode(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplayState msg_;
};

class Init_LpsSaUIDisplayState_service_mode_enable_code_entered
{
public:
  Init_LpsSaUIDisplayState_service_mode_enable_code_entered()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaUIDisplayState_in_service_mode service_mode_enable_code_entered(::cpm_common_interfaces::msg::LpsSaUIDisplayState::_service_mode_enable_code_entered_type arg)
  {
    msg_.service_mode_enable_code_entered = std::move(arg);
    return Init_LpsSaUIDisplayState_in_service_mode(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplayState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LpsSaUIDisplayState>()
{
  return cpm_common_interfaces::msg::builder::Init_LpsSaUIDisplayState_service_mode_enable_code_entered();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE__BUILDER_HPP_
