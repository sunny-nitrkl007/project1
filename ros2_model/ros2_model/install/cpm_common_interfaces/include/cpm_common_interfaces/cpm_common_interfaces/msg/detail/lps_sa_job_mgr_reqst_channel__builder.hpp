// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrReqstChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_reqst_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_reqst_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaJobMgrReqstChannel_requests
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_requests(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel requests(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_requests_type arg)
  {
    msg_.requests = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_data_subtotal_info
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_data_subtotal_info(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqstChannel_requests data_subtotal_info(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_data_subtotal_info_type arg)
  {
    msg_.data_subtotal_info = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_requests(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_data_total_target_weight
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_data_total_target_weight(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqstChannel_data_subtotal_info data_total_target_weight(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_data_total_target_weight_type arg)
  {
    msg_.data_total_target_weight = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_data_subtotal_info(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_data_subtotal_index
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_data_subtotal_index(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqstChannel_data_total_target_weight data_subtotal_index(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_data_subtotal_index_type arg)
  {
    msg_.data_subtotal_index = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_data_total_target_weight(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_data_target_type
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_data_target_type(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqstChannel_data_subtotal_index data_target_type(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_data_target_type_type arg)
  {
    msg_.data_target_type = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_data_subtotal_index(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_data_enabled
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_data_enabled(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqstChannel_data_target_type data_enabled(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_data_enabled_type arg)
  {
    msg_.data_enabled = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_data_target_type(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_data_task_number
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_data_task_number(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqstChannel_data_enabled data_task_number(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_data_task_number_type arg)
  {
    msg_.data_task_number = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_data_enabled(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_data_auto_store_pass_count
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_data_auto_store_pass_count(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqstChannel_data_task_number data_auto_store_pass_count(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_data_auto_store_pass_count_type arg)
  {
    msg_.data_auto_store_pass_count = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_data_task_number(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_data_tipoff_mode
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_data_tipoff_mode(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqstChannel_data_auto_store_pass_count data_tipoff_mode(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_data_tipoff_mode_type arg)
  {
    msg_.data_tipoff_mode = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_data_auto_store_pass_count(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_data_tipoff_trigger_type
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_data_tipoff_trigger_type(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqstChannel_data_tipoff_mode data_tipoff_trigger_type(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_data_tipoff_trigger_type_type arg)
  {
    msg_.data_tipoff_trigger_type = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_data_tipoff_mode(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_command
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_command(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqstChannel_data_tipoff_trigger_type command(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_data_tipoff_trigger_type(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_app_request_id
{
public:
  explicit Init_LpsSaJobMgrReqstChannel_app_request_id(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrReqstChannel_command app_request_id(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_app_request_id_type arg)
  {
    msg_.app_request_id = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_command(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

class Init_LpsSaJobMgrReqstChannel_app_name
{
public:
  Init_LpsSaJobMgrReqstChannel_app_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaJobMgrReqstChannel_app_request_id app_name(::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel::_app_name_type arg)
  {
    msg_.app_name = std::move(arg);
    return Init_LpsSaJobMgrReqstChannel_app_request_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>()
{
  return cpm_common_interfaces::msg::builder::Init_LpsSaJobMgrReqstChannel_app_name();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__BUILDER_HPP_
