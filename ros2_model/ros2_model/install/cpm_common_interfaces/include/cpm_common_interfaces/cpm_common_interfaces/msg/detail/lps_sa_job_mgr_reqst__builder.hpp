// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrReqst.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_reqst.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_reqst__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaJobMgrReqst_arg4
{
public:
  explicit Init_LpsSaJobMgrReqst_arg4(::cpm_common_interfaces::msg::LpsSaJobMgrReqst & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqst arg4(::cpm_common_interfaces::msg::LpsSaJobMgrReqst::_arg4_type arg)
  {
    msg_.arg4 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqst msg_;
};

class Init_LpsSaJobMgrReqst_arg3
{
public:
  explicit Init_LpsSaJobMgrReqst_arg3(::cpm_common_interfaces::msg::LpsSaJobMgrReqst & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqst_arg4 arg3(::cpm_common_interfaces::msg::LpsSaJobMgrReqst::_arg3_type arg)
  {
    msg_.arg3 = std::move(arg);
    return Init_LpsSaJobMgrReqst_arg4(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqst msg_;
};

class Init_LpsSaJobMgrReqst_arg2
{
public:
  explicit Init_LpsSaJobMgrReqst_arg2(::cpm_common_interfaces::msg::LpsSaJobMgrReqst & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqst_arg3 arg2(::cpm_common_interfaces::msg::LpsSaJobMgrReqst::_arg2_type arg)
  {
    msg_.arg2 = std::move(arg);
    return Init_LpsSaJobMgrReqst_arg3(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqst msg_;
};

class Init_LpsSaJobMgrReqst_arg1
{
public:
  explicit Init_LpsSaJobMgrReqst_arg1(::cpm_common_interfaces::msg::LpsSaJobMgrReqst & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqst_arg2 arg1(::cpm_common_interfaces::msg::LpsSaJobMgrReqst::_arg1_type arg)
  {
    msg_.arg1 = std::move(arg);
    return Init_LpsSaJobMgrReqst_arg2(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqst msg_;
};

class Init_LpsSaJobMgrReqst_command
{
public:
  Init_LpsSaJobMgrReqst_command()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaJobMgrReqst_arg1 command(::cpm_common_interfaces::msg::LpsSaJobMgrReqst::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_LpsSaJobMgrReqst_arg1(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqst msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LpsSaJobMgrReqst>()
{
  return cpm_common_interfaces::msg::builder::Init_LpsSaJobMgrReqst_command();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__BUILDER_HPP_
