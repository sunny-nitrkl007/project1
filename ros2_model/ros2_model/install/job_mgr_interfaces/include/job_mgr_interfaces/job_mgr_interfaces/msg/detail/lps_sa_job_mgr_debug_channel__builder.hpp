// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/LpsSaJobMgrDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_job_mgr_debug_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/lps_sa_job_mgr_debug_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaJobMgrDebugChannel_tipoff_assist_activation_count
{
public:
  explicit Init_LpsSaJobMgrDebugChannel_tipoff_assist_activation_count(::job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel tipoff_assist_activation_count(::job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel::_tipoff_assist_activation_count_type arg)
  {
    msg_.tipoff_assist_activation_count = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel msg_;
};

class Init_LpsSaJobMgrDebugChannel_current_state
{
public:
  Init_LpsSaJobMgrDebugChannel_current_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaJobMgrDebugChannel_tipoff_assist_activation_count current_state(::job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel::_current_state_type arg)
  {
    msg_.current_state = std::move(arg);
    return Init_LpsSaJobMgrDebugChannel_tipoff_assist_activation_count(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>()
{
  return job_mgr_interfaces::msg::builder::Init_LpsSaJobMgrDebugChannel_current_state();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__BUILDER_HPP_
