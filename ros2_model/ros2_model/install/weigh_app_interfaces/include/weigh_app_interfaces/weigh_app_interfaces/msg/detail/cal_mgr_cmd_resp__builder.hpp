// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from weigh_app_interfaces:msg/CalMgrCmdResp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/cal_mgr_cmd_resp.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__BUILDER_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "weigh_app_interfaces/msg/detail/cal_mgr_cmd_resp__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace weigh_app_interfaces
{

namespace msg
{

namespace builder
{

class Init_CalMgrCmdResp_calibration_resp
{
public:
  Init_CalMgrCmdResp_calibration_resp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::weigh_app_interfaces::msg::CalMgrCmdResp calibration_resp(::weigh_app_interfaces::msg::CalMgrCmdResp::_calibration_resp_type arg)
  {
    msg_.calibration_resp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::weigh_app_interfaces::msg::CalMgrCmdResp msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::weigh_app_interfaces::msg::CalMgrCmdResp>()
{
  return weigh_app_interfaces::msg::builder::Init_CalMgrCmdResp_calibration_resp();
}

}  // namespace weigh_app_interfaces

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__BUILDER_HPP_
