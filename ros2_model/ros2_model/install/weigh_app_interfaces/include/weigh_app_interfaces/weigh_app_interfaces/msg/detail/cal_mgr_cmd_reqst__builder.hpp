// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/CalMgrCmdReqst.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/cal_mgr_cmd_reqst.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_REQST__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_REQST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/cal_mgr_cmd_reqst__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_CalMgrCmdReqst_calibration_request
{
public:
  Init_CalMgrCmdReqst_calibration_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::weigh_app_interfaces::msg::CalMgrCmdReqst calibration_request(::weigh_app_interfaces::msg::CalMgrCmdReqst::_calibration_request_type arg)
  {
    msg_.calibration_request = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalMgrCmdReqst msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::CalMgrCmdReqst>()
{
  return weigh_app_interfaces::msg::builder::Init_CalMgrCmdReqst_calibration_request();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_REQST__BUILDER_HPP_
