// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/CalibrationRequest.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/calibration_request.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/calibration_request__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_CalibrationRequest_cal_iterm
{
public:
  explicit Init_CalibrationRequest_cal_iterm(::weigh_app_interfaces::msg::CalibrationRequest & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::CalibrationRequest cal_iterm(::weigh_app_interfaces::msg::CalibrationRequest::_cal_iterm_type arg)
  {
    msg_.cal_iterm = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalibrationRequest msg_;
};

class Init_CalibrationRequest_cal_id
{
public:
  explicit Init_CalibrationRequest_cal_id(::weigh_app_interfaces::msg::CalibrationRequest & msg)
  : msg_(msg)
  {}
  Init_CalibrationRequest_cal_iterm cal_id(::weigh_app_interfaces::msg::CalibrationRequest::_cal_id_type arg)
  {
    msg_.cal_id = std::move(arg);
    return Init_CalibrationRequest_cal_iterm(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalibrationRequest msg_;
};

class Init_CalibrationRequest_calcmd
{
public:
  explicit Init_CalibrationRequest_calcmd(::weigh_app_interfaces::msg::CalibrationRequest & msg)
  : msg_(msg)
  {}
  Init_CalibrationRequest_cal_id calcmd(::weigh_app_interfaces::msg::CalibrationRequest::_calcmd_type arg)
  {
    msg_.calcmd = std::move(arg);
    return Init_CalibrationRequest_cal_id(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalibrationRequest msg_;
};

class Init_CalibrationRequest_calibration_reqst_flag
{
public:
  explicit Init_CalibrationRequest_calibration_reqst_flag(::weigh_app_interfaces::msg::CalibrationRequest & msg)
  : msg_(msg)
  {}
  Init_CalibrationRequest_calcmd calibration_reqst_flag(::weigh_app_interfaces::msg::CalibrationRequest::_calibration_reqst_flag_type arg)
  {
    msg_.calibration_reqst_flag = std::move(arg);
    return Init_CalibrationRequest_calcmd(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalibrationRequest msg_;
};

class Init_CalibrationRequest_dest
{
public:
  explicit Init_CalibrationRequest_dest(::weigh_app_interfaces::msg::CalibrationRequest & msg)
  : msg_(msg)
  {}
  Init_CalibrationRequest_calibration_reqst_flag dest(::weigh_app_interfaces::msg::CalibrationRequest::_dest_type arg)
  {
    msg_.dest = std::move(arg);
    return Init_CalibrationRequest_calibration_reqst_flag(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalibrationRequest msg_;
};

class Init_CalibrationRequest_src
{
public:
  Init_CalibrationRequest_src()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CalibrationRequest_dest src(::weigh_app_interfaces::msg::CalibrationRequest::_src_type arg)
  {
    msg_.src = std::move(arg);
    return Init_CalibrationRequest_dest(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalibrationRequest msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::CalibrationRequest>()
{
  return weigh_app_interfaces::msg::builder::Init_CalibrationRequest_src();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__BUILDER_HPP_
