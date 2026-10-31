// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/SimpleCalDataT.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/simple_cal_data_t.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/simple_cal_data_t__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_SimpleCalDataT_new_data_flag
{
public:
  explicit Init_SimpleCalDataT_new_data_flag(::cpm_common_interfaces::msg::SimpleCalDataT & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::SimpleCalDataT new_data_flag(::cpm_common_interfaces::msg::SimpleCalDataT::_new_data_flag_type arg)
  {
    msg_.new_data_flag = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::SimpleCalDataT msg_;
};

class Init_SimpleCalDataT_zeroed_truck_wt
{
public:
  explicit Init_SimpleCalDataT_zeroed_truck_wt(::cpm_common_interfaces::msg::SimpleCalDataT & msg)
  : msg_(msg)
  {}
  Init_SimpleCalDataT_new_data_flag zeroed_truck_wt(::cpm_common_interfaces::msg::SimpleCalDataT::_zeroed_truck_wt_type arg)
  {
    msg_.zeroed_truck_wt = std::move(arg);
    return Init_SimpleCalDataT_new_data_flag(msg_);
  }

private:
  ::cpm_common_interfaces::msg::SimpleCalDataT msg_;
};

class Init_SimpleCalDataT_adjtruckweight
{
public:
  explicit Init_SimpleCalDataT_adjtruckweight(::cpm_common_interfaces::msg::SimpleCalDataT & msg)
  : msg_(msg)
  {}
  Init_SimpleCalDataT_zeroed_truck_wt adjtruckweight(::cpm_common_interfaces::msg::SimpleCalDataT::_adjtruckweight_type arg)
  {
    msg_.adjtruckweight = std::move(arg);
    return Init_SimpleCalDataT_zeroed_truck_wt(msg_);
  }

private:
  ::cpm_common_interfaces::msg::SimpleCalDataT msg_;
};

class Init_SimpleCalDataT_time_stamp
{
public:
  Init_SimpleCalDataT_time_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SimpleCalDataT_adjtruckweight time_stamp(::cpm_common_interfaces::msg::SimpleCalDataT::_time_stamp_type arg)
  {
    msg_.time_stamp = std::move(arg);
    return Init_SimpleCalDataT_adjtruckweight(msg_);
  }

private:
  ::cpm_common_interfaces::msg::SimpleCalDataT msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::SimpleCalDataT>()
{
  return cpm_common_interfaces::msg::builder::Init_SimpleCalDataT_time_stamp();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__BUILDER_HPP_
