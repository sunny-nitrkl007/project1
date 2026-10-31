// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/DataLinkData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/data_link_data.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/data_link_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_DataLinkData_params
{
public:
  Init_DataLinkData_params()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::job_mgr_interfaces::msg::DataLinkData params(::job_mgr_interfaces::msg::DataLinkData::_params_type arg)
  {
    msg_.params = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::DataLinkData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::DataLinkData>()
{
  return job_mgr_interfaces::msg::builder::Init_DataLinkData_params();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__BUILDER_HPP_
