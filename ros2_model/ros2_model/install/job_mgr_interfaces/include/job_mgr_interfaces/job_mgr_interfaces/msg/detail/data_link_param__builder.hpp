// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/DataLinkParam.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/data_link_param.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/data_link_param__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_DataLinkParam_last_value_eng
{
public:
  explicit Init_DataLinkParam_last_value_eng(::job_mgr_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::DataLinkParam last_value_eng(::job_mgr_interfaces::msg::DataLinkParam::_last_value_eng_type arg)
  {
    msg_.last_value_eng = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_last_good_value_u16
{
public:
  explicit Init_DataLinkParam_last_good_value_u16(::job_mgr_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_last_value_eng last_good_value_u16(::job_mgr_interfaces::msg::DataLinkParam::_last_good_value_u16_type arg)
  {
    msg_.last_good_value_u16 = std::move(arg);
    return Init_DataLinkParam_last_value_eng(msg_);
  }

private:
  ::job_mgr_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_last_good_value_u8
{
public:
  explicit Init_DataLinkParam_last_good_value_u8(::job_mgr_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_last_good_value_u16 last_good_value_u8(::job_mgr_interfaces::msg::DataLinkParam::_last_good_value_u8_type arg)
  {
    msg_.last_good_value_u8 = std::move(arg);
    return Init_DataLinkParam_last_good_value_u16(msg_);
  }

private:
  ::job_mgr_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_last_value_dsi
{
public:
  explicit Init_DataLinkParam_last_value_dsi(::job_mgr_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_last_good_value_u8 last_value_dsi(::job_mgr_interfaces::msg::DataLinkParam::_last_value_dsi_type arg)
  {
    msg_.last_value_dsi = std::move(arg);
    return Init_DataLinkParam_last_good_value_u8(msg_);
  }

private:
  ::job_mgr_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_pid_data_received
{
public:
  explicit Init_DataLinkParam_pid_data_received(::job_mgr_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_last_value_dsi pid_data_received(::job_mgr_interfaces::msg::DataLinkParam::_pid_data_received_type arg)
  {
    msg_.pid_data_received = std::move(arg);
    return Init_DataLinkParam_last_value_dsi(msg_);
  }

private:
  ::job_mgr_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_identifier_type
{
public:
  explicit Init_DataLinkParam_identifier_type(::job_mgr_interfaces::msg::DataLinkParam & msg)
  : msg_(msg)
  {}
  Init_DataLinkParam_pid_data_received identifier_type(::job_mgr_interfaces::msg::DataLinkParam::_identifier_type_type arg)
  {
    msg_.identifier_type = std::move(arg);
    return Init_DataLinkParam_pid_data_received(msg_);
  }

private:
  ::job_mgr_interfaces::msg::DataLinkParam msg_;
};

class Init_DataLinkParam_param_id
{
public:
  Init_DataLinkParam_param_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DataLinkParam_identifier_type param_id(::job_mgr_interfaces::msg::DataLinkParam::_param_id_type arg)
  {
    msg_.param_id = std::move(arg);
    return Init_DataLinkParam_identifier_type(msg_);
  }

private:
  ::job_mgr_interfaces::msg::DataLinkParam msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::DataLinkParam>()
{
  return job_mgr_interfaces::msg::builder::Init_DataLinkParam_param_id();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__BUILDER_HPP_
