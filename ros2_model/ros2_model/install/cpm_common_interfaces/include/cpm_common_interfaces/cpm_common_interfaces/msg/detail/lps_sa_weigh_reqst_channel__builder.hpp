// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaWeighReqstChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_reqst_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/lps_sa_weigh_reqst_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaWeighReqstChannel_arg_map
{
public:
  explicit Init_LpsSaWeighReqstChannel_arg_map(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::LpsSaWeighReqstChannel arg_map(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel::_arg_map_type arg)
  {
    msg_.arg_map = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighReqstChannel msg_;
};

class Init_LpsSaWeighReqstChannel_arg_u
{
public:
  explicit Init_LpsSaWeighReqstChannel_arg_u(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighReqstChannel_arg_map arg_u(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel::_arg_u_type arg)
  {
    msg_.arg_u = std::move(arg);
    return Init_LpsSaWeighReqstChannel_arg_map(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighReqstChannel msg_;
};

class Init_LpsSaWeighReqstChannel_arg_s
{
public:
  explicit Init_LpsSaWeighReqstChannel_arg_s(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighReqstChannel_arg_u arg_s(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel::_arg_s_type arg)
  {
    msg_.arg_s = std::move(arg);
    return Init_LpsSaWeighReqstChannel_arg_u(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighReqstChannel msg_;
};

class Init_LpsSaWeighReqstChannel_arg_f2
{
public:
  explicit Init_LpsSaWeighReqstChannel_arg_f2(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighReqstChannel_arg_s arg_f2(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel::_arg_f2_type arg)
  {
    msg_.arg_f2 = std::move(arg);
    return Init_LpsSaWeighReqstChannel_arg_s(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighReqstChannel msg_;
};

class Init_LpsSaWeighReqstChannel_arg_f1
{
public:
  explicit Init_LpsSaWeighReqstChannel_arg_f1(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighReqstChannel_arg_f2 arg_f1(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel::_arg_f1_type arg)
  {
    msg_.arg_f1 = std::move(arg);
    return Init_LpsSaWeighReqstChannel_arg_f2(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighReqstChannel msg_;
};

class Init_LpsSaWeighReqstChannel_arg_b
{
public:
  explicit Init_LpsSaWeighReqstChannel_arg_b(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighReqstChannel_arg_f1 arg_b(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel::_arg_b_type arg)
  {
    msg_.arg_b = std::move(arg);
    return Init_LpsSaWeighReqstChannel_arg_f1(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighReqstChannel msg_;
};

class Init_LpsSaWeighReqstChannel_command
{
public:
  explicit Init_LpsSaWeighReqstChannel_command(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighReqstChannel_arg_b command(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_LpsSaWeighReqstChannel_arg_b(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighReqstChannel msg_;
};

class Init_LpsSaWeighReqstChannel_app_request_id
{
public:
  explicit Init_LpsSaWeighReqstChannel_app_request_id(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighReqstChannel_command app_request_id(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel::_app_request_id_type arg)
  {
    msg_.app_request_id = std::move(arg);
    return Init_LpsSaWeighReqstChannel_command(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighReqstChannel msg_;
};

class Init_LpsSaWeighReqstChannel_app_name
{
public:
  Init_LpsSaWeighReqstChannel_app_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaWeighReqstChannel_app_request_id app_name(::cpm_common_interfaces::msg::LpsSaWeighReqstChannel::_app_name_type arg)
  {
    msg_.app_name = std::move(arg);
    return Init_LpsSaWeighReqstChannel_app_request_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighReqstChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LpsSaWeighReqstChannel>()
{
  return cpm_common_interfaces::msg::builder::Init_LpsSaWeighReqstChannel_app_name();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_REQST_CHANNEL__BUILDER_HPP_
