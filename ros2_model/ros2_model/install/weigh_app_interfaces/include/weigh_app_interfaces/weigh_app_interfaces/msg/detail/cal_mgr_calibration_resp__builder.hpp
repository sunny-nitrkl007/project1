// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/CalMgrCalibrationResp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/cal_mgr_calibration_resp.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/cal_mgr_calibration_resp__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_CalMgrCalibrationResp_enable_qual_read
{
public:
  explicit Init_CalMgrCalibrationResp_enable_qual_read(::weigh_app_interfaces::msg::CalMgrCalibrationResp & msg)
  : msg_(msg)
  {}
  ::weigh_app_interfaces::msg::CalMgrCalibrationResp enable_qual_read(::weigh_app_interfaces::msg::CalMgrCalibrationResp::_enable_qual_read_type arg)
  {
    msg_.enable_qual_read = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalMgrCalibrationResp msg_;
};

class Init_CalMgrCalibrationResp_warning
{
public:
  explicit Init_CalMgrCalibrationResp_warning(::weigh_app_interfaces::msg::CalMgrCalibrationResp & msg)
  : msg_(msg)
  {}
  Init_CalMgrCalibrationResp_enable_qual_read warning(::weigh_app_interfaces::msg::CalMgrCalibrationResp::_warning_type arg)
  {
    msg_.warning = std::move(arg);
    return Init_CalMgrCalibrationResp_enable_qual_read(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalMgrCalibrationResp msg_;
};

class Init_CalMgrCalibrationResp_error
{
public:
  explicit Init_CalMgrCalibrationResp_error(::weigh_app_interfaces::msg::CalMgrCalibrationResp & msg)
  : msg_(msg)
  {}
  Init_CalMgrCalibrationResp_warning error(::weigh_app_interfaces::msg::CalMgrCalibrationResp::_error_type arg)
  {
    msg_.error = std::move(arg);
    return Init_CalMgrCalibrationResp_warning(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalMgrCalibrationResp msg_;
};

class Init_CalMgrCalibrationResp_step_no
{
public:
  explicit Init_CalMgrCalibrationResp_step_no(::weigh_app_interfaces::msg::CalMgrCalibrationResp & msg)
  : msg_(msg)
  {}
  Init_CalMgrCalibrationResp_error step_no(::weigh_app_interfaces::msg::CalMgrCalibrationResp::_step_no_type arg)
  {
    msg_.step_no = std::move(arg);
    return Init_CalMgrCalibrationResp_error(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalMgrCalibrationResp msg_;
};

class Init_CalMgrCalibrationResp_cal_resp
{
public:
  explicit Init_CalMgrCalibrationResp_cal_resp(::weigh_app_interfaces::msg::CalMgrCalibrationResp & msg)
  : msg_(msg)
  {}
  Init_CalMgrCalibrationResp_step_no cal_resp(::weigh_app_interfaces::msg::CalMgrCalibrationResp::_cal_resp_type arg)
  {
    msg_.cal_resp = std::move(arg);
    return Init_CalMgrCalibrationResp_step_no(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalMgrCalibrationResp msg_;
};

class Init_CalMgrCalibrationResp_resp_code
{
public:
  Init_CalMgrCalibrationResp_resp_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CalMgrCalibrationResp_cal_resp resp_code(::weigh_app_interfaces::msg::CalMgrCalibrationResp::_resp_code_type arg)
  {
    msg_.resp_code = std::move(arg);
    return Init_CalMgrCalibrationResp_cal_resp(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalMgrCalibrationResp msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::CalMgrCalibrationResp>()
{
  return weigh_app_interfaces::msg::builder::Init_CalMgrCalibrationResp_resp_code();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__BUILDER_HPP_
