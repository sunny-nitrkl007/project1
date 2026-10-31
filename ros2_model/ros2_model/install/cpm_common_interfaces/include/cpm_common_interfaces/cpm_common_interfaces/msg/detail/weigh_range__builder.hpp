// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/WeighRange.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/weigh_range.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_RANGE__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_RANGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/weigh_range__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_WeighRange_weigh_range_size
{
public:
  explicit Init_WeighRange_weigh_range_size(::cpm_common_interfaces::msg::WeighRange & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::WeighRange weigh_range_size(::cpm_common_interfaces::msg::WeighRange::_weigh_range_size_type arg)
  {
    msg_.weigh_range_size = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighRange msg_;
};

class Init_WeighRange_weigh_range_bottom
{
public:
  Init_WeighRange_weigh_range_bottom()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WeighRange_weigh_range_size weigh_range_bottom(::cpm_common_interfaces::msg::WeighRange::_weigh_range_bottom_type arg)
  {
    msg_.weigh_range_bottom = std::move(arg);
    return Init_WeighRange_weigh_range_size(msg_);
  }

private:
  ::cpm_common_interfaces::msg::WeighRange msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::WeighRange>()
{
  return cpm_common_interfaces::msg::builder::Init_WeighRange_weigh_range_bottom();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_RANGE__BUILDER_HPP_
