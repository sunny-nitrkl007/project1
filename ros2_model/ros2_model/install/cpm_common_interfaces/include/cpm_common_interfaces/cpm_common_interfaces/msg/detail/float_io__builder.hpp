// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/FloatIO.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/float_io.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_IO__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_IO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/float_io__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_FloatIO_val
{
public:
  explicit Init_FloatIO_val(::cpm_common_interfaces::msg::FloatIO & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::FloatIO val(::cpm_common_interfaces::msg::FloatIO::_val_type arg)
  {
    msg_.val = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::FloatIO msg_;
};

class Init_FloatIO_stat
{
public:
  Init_FloatIO_stat()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FloatIO_val stat(::cpm_common_interfaces::msg::FloatIO::_stat_type arg)
  {
    msg_.stat = std::move(arg);
    return Init_FloatIO_val(msg_);
  }

private:
  ::cpm_common_interfaces::msg::FloatIO msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::FloatIO>()
{
  return cpm_common_interfaces::msg::builder::Init_FloatIO_stat();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__FLOAT_IO__BUILDER_HPP_
