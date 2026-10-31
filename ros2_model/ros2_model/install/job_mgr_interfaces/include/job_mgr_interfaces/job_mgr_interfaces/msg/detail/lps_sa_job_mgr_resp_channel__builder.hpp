// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/LpsSaJobMgrRespChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_job_mgr_resp_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_RESP_CHANNEL__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_RESP_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/lps_sa_job_mgr_resp_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaJobMgrRespChannel_success
{
public:
  explicit Init_LpsSaJobMgrRespChannel_success(::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel success(::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel msg_;
};

class Init_LpsSaJobMgrRespChannel_command
{
public:
  explicit Init_LpsSaJobMgrRespChannel_command(::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrRespChannel_success command(::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_LpsSaJobMgrRespChannel_success(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel msg_;
};

class Init_LpsSaJobMgrRespChannel_time_point_ns
{
public:
  explicit Init_LpsSaJobMgrRespChannel_time_point_ns(::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrRespChannel_command time_point_ns(::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel::_time_point_ns_type arg)
  {
    msg_.time_point_ns = std::move(arg);
    return Init_LpsSaJobMgrRespChannel_command(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel msg_;
};

class Init_LpsSaJobMgrRespChannel_app_request_id
{
public:
  explicit Init_LpsSaJobMgrRespChannel_app_request_id(::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrRespChannel_time_point_ns app_request_id(::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel::_app_request_id_type arg)
  {
    msg_.app_request_id = std::move(arg);
    return Init_LpsSaJobMgrRespChannel_time_point_ns(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel msg_;
};

class Init_LpsSaJobMgrRespChannel_app_name
{
public:
  Init_LpsSaJobMgrRespChannel_app_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaJobMgrRespChannel_app_request_id app_name(::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel::_app_name_type arg)
  {
    msg_.app_name = std::move(arg);
    return Init_LpsSaJobMgrRespChannel_app_request_id(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>()
{
  return job_mgr_interfaces::msg::builder::Init_LpsSaJobMgrRespChannel_app_name();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_RESP_CHANNEL__BUILDER_HPP_
