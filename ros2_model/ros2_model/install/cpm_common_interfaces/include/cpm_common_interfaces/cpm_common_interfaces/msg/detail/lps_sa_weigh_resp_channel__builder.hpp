// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaWeighRespChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_resp_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__BUILDER_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cpm_common_interfaces/msg/detail/lps_sa_weigh_resp_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cpm_common_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaWeighRespChannel_arg1
{
public:
  explicit Init_LpsSaWeighRespChannel_arg1(::cpm_common_interfaces::msg::LpsSaWeighRespChannel & msg)
  : msg_(msg)
  {}
  ::cpm_common_interfaces::msg::LpsSaWeighRespChannel arg1(::cpm_common_interfaces::msg::LpsSaWeighRespChannel::_arg1_type arg)
  {
    msg_.arg1 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighRespChannel msg_;
};

class Init_LpsSaWeighRespChannel_success
{
public:
  explicit Init_LpsSaWeighRespChannel_success(::cpm_common_interfaces::msg::LpsSaWeighRespChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighRespChannel_arg1 success(::cpm_common_interfaces::msg::LpsSaWeighRespChannel::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_LpsSaWeighRespChannel_arg1(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighRespChannel msg_;
};

class Init_LpsSaWeighRespChannel_command
{
public:
  explicit Init_LpsSaWeighRespChannel_command(::cpm_common_interfaces::msg::LpsSaWeighRespChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighRespChannel_success command(::cpm_common_interfaces::msg::LpsSaWeighRespChannel::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_LpsSaWeighRespChannel_success(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighRespChannel msg_;
};

class Init_LpsSaWeighRespChannel_time_point_ns
{
public:
  explicit Init_LpsSaWeighRespChannel_time_point_ns(::cpm_common_interfaces::msg::LpsSaWeighRespChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighRespChannel_command time_point_ns(::cpm_common_interfaces::msg::LpsSaWeighRespChannel::_time_point_ns_type arg)
  {
    msg_.time_point_ns = std::move(arg);
    return Init_LpsSaWeighRespChannel_command(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighRespChannel msg_;
};

class Init_LpsSaWeighRespChannel_app_request_id
{
public:
  explicit Init_LpsSaWeighRespChannel_app_request_id(::cpm_common_interfaces::msg::LpsSaWeighRespChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaWeighRespChannel_time_point_ns app_request_id(::cpm_common_interfaces::msg::LpsSaWeighRespChannel::_app_request_id_type arg)
  {
    msg_.app_request_id = std::move(arg);
    return Init_LpsSaWeighRespChannel_time_point_ns(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighRespChannel msg_;
};

class Init_LpsSaWeighRespChannel_app_name
{
public:
  Init_LpsSaWeighRespChannel_app_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaWeighRespChannel_app_request_id app_name(::cpm_common_interfaces::msg::LpsSaWeighRespChannel::_app_name_type arg)
  {
    msg_.app_name = std::move(arg);
    return Init_LpsSaWeighRespChannel_app_request_id(msg_);
  }

private:
  ::cpm_common_interfaces::msg::LpsSaWeighRespChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cpm_common_interfaces::msg::LpsSaWeighRespChannel>()
{
  return cpm_common_interfaces::msg::builder::Init_LpsSaWeighRespChannel_app_name();
}

}  // namespace cpm_common_interfaces

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_RESP_CHANNEL__BUILDER_HPP_
