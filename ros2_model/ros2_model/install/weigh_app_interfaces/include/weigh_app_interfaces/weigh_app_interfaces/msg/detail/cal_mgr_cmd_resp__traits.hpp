// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/CalMgrCmdResp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/cal_mgr_cmd_resp.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/cal_mgr_cmd_resp__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'calibration_resp'
#include "weigh_app_interfaces/msg/detail/cal_mgr_calibration_resp__traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const CalMgrCmdResp & msg,
  std::ostream & out)
{
  out << "{";
  // member: calibration_resp
  {
    out << "calibration_resp: ";
    to_flow_style_yaml(msg.calibration_resp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CalMgrCmdResp & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: calibration_resp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calibration_resp:\n";
    to_block_style_yaml(msg.calibration_resp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CalMgrCmdResp & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace weigh_app_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use weigh_app_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const weigh_app_interfaces::msg::CalMgrCmdResp & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::CalMgrCmdResp & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::CalMgrCmdResp>()
{
  return "weigh_app_interfaces::msg::CalMgrCmdResp";
}

template<>
inline const char * name<weigh_app_interfaces::msg::CalMgrCmdResp>()
{
  return "weigh_app_interfaces/msg/CalMgrCmdResp";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::CalMgrCmdResp>
  : std::integral_constant<bool, has_fixed_size<weigh_app_interfaces::msg::CalMgrCalibrationResp>::value> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::CalMgrCmdResp>
  : std::integral_constant<bool, has_bounded_size<weigh_app_interfaces::msg::CalMgrCalibrationResp>::value> {};

template<>
struct is_message<weigh_app_interfaces::msg::CalMgrCmdResp>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__TRAITS_HPP_
