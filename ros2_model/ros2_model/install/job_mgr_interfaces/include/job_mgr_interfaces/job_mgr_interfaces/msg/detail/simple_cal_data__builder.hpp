// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/SimpleCalData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/simple_cal_data.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/simple_cal_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_SimpleCalData_zeroed_truck_wt
{
public:
  explicit Init_SimpleCalData_zeroed_truck_wt(::job_mgr_interfaces::msg::SimpleCalData & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::SimpleCalData zeroed_truck_wt(::job_mgr_interfaces::msg::SimpleCalData::_zeroed_truck_wt_type arg)
  {
    msg_.zeroed_truck_wt = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::SimpleCalData msg_;
};

class Init_SimpleCalData_truck_wt
{
public:
  explicit Init_SimpleCalData_truck_wt(::job_mgr_interfaces::msg::SimpleCalData & msg)
  : msg_(msg)
  {}
  Init_SimpleCalData_zeroed_truck_wt truck_wt(::job_mgr_interfaces::msg::SimpleCalData::_truck_wt_type arg)
  {
    msg_.truck_wt = std::move(arg);
    return Init_SimpleCalData_zeroed_truck_wt(msg_);
  }

private:
  ::job_mgr_interfaces::msg::SimpleCalData msg_;
};

class Init_SimpleCalData_time_stamp
{
public:
  Init_SimpleCalData_time_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SimpleCalData_truck_wt time_stamp(::job_mgr_interfaces::msg::SimpleCalData::_time_stamp_type arg)
  {
    msg_.time_stamp = std::move(arg);
    return Init_SimpleCalData_truck_wt(msg_);
  }

private:
  ::job_mgr_interfaces::msg::SimpleCalData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::SimpleCalData>()
{
  return job_mgr_interfaces::msg::builder::Init_SimpleCalData_time_stamp();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__BUILDER_HPP_
