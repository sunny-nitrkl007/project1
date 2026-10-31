// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaUIDisplayStateInterface.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_ui_display_state_interface.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE_INTERFACE__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE_INTERFACE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/lps_sa_ui_display_state_interface__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaUIDisplayStateInterface_state
{
public:
  Init_LpsSaUIDisplayStateInterface_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface state(::cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface>()
{
  return cpm_common_interfaces::msg::builder::Init_LpsSaUIDisplayStateInterface_state();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_UI_DISPLAY_STATE_INTERFACE__BUILDER_HPP_
