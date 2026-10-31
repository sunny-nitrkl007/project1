// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/TipoffWeightAdjustData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/tipoff_weight_adjust_data.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/tipoff_weight_adjust_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_TipoffWeightAdjustData_reset
{
public:
  explicit Init_TipoffWeightAdjustData_reset(::cpm_common_interfaces::msg::TipoffWeightAdjustData & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::TipoffWeightAdjustData reset(::cpm_common_interfaces::msg::TipoffWeightAdjustData::_reset_type arg)
  {
    msg_.reset = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TipoffWeightAdjustData msg_;
};

class Init_TipoffWeightAdjustData_new_data_flag
{
public:
  explicit Init_TipoffWeightAdjustData_new_data_flag(::cpm_common_interfaces::msg::TipoffWeightAdjustData & msg)
  : msg_(msg)
  {}
  Init_TipoffWeightAdjustData_reset new_data_flag(::cpm_common_interfaces::msg::TipoffWeightAdjustData::_new_data_flag_type arg)
  {
    msg_.new_data_flag = std::move(arg);
    return Init_TipoffWeightAdjustData_reset(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TipoffWeightAdjustData msg_;
};

class Init_TipoffWeightAdjustData_weigh_range_weight2
{
public:
  explicit Init_TipoffWeightAdjustData_weigh_range_weight2(::cpm_common_interfaces::msg::TipoffWeightAdjustData & msg)
  : msg_(msg)
  {}
  Init_TipoffWeightAdjustData_new_data_flag weigh_range_weight2(::cpm_common_interfaces::msg::TipoffWeightAdjustData::_weigh_range_weight2_type arg)
  {
    msg_.weigh_range_weight2 = std::move(arg);
    return Init_TipoffWeightAdjustData_new_data_flag(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TipoffWeightAdjustData msg_;
};

class Init_TipoffWeightAdjustData_tip_off_weight2
{
public:
  explicit Init_TipoffWeightAdjustData_tip_off_weight2(::cpm_common_interfaces::msg::TipoffWeightAdjustData & msg)
  : msg_(msg)
  {}
  Init_TipoffWeightAdjustData_weigh_range_weight2 tip_off_weight2(::cpm_common_interfaces::msg::TipoffWeightAdjustData::_tip_off_weight2_type arg)
  {
    msg_.tip_off_weight2 = std::move(arg);
    return Init_TipoffWeightAdjustData_weigh_range_weight2(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TipoffWeightAdjustData msg_;
};

class Init_TipoffWeightAdjustData_weigh_range_weight1
{
public:
  explicit Init_TipoffWeightAdjustData_weigh_range_weight1(::cpm_common_interfaces::msg::TipoffWeightAdjustData & msg)
  : msg_(msg)
  {}
  Init_TipoffWeightAdjustData_tip_off_weight2 weigh_range_weight1(::cpm_common_interfaces::msg::TipoffWeightAdjustData::_weigh_range_weight1_type arg)
  {
    msg_.weigh_range_weight1 = std::move(arg);
    return Init_TipoffWeightAdjustData_tip_off_weight2(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TipoffWeightAdjustData msg_;
};

class Init_TipoffWeightAdjustData_tip_off_weight1
{
public:
  Init_TipoffWeightAdjustData_tip_off_weight1()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TipoffWeightAdjustData_weigh_range_weight1 tip_off_weight1(::cpm_common_interfaces::msg::TipoffWeightAdjustData::_tip_off_weight1_type arg)
  {
    msg_.tip_off_weight1 = std::move(arg);
    return Init_TipoffWeightAdjustData_weigh_range_weight1(msg_);
  }

private:
  ::cpm_common_interfaces::msg::TipoffWeightAdjustData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::TipoffWeightAdjustData>()
{
  return cpm_common_interfaces::msg::builder::Init_TipoffWeightAdjustData_tip_off_weight1();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__BUILDER_HPP_
