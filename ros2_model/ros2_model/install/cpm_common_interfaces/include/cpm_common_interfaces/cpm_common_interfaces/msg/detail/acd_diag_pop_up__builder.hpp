// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/AcdDiagPopUp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/acd_diag_pop_up.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_DIAG_POP_UP__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_DIAG_POP_UP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/acd_diag_pop_up__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_AcdDiagPopUp_bits
{
public:
  Init_AcdDiagPopUp_bits()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cpm_common_interfaces::msg::AcdDiagPopUp bits(::cpm_common_interfaces::msg::AcdDiagPopUp::_bits_type arg)
  {
    msg_.bits = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::AcdDiagPopUp msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::AcdDiagPopUp>()
{
  return cpm_common_interfaces::msg::builder::Init_AcdDiagPopUp_bits();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_DIAG_POP_UP__BUILDER_HPP_
