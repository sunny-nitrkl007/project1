// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/CalMgrCalibrationResp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/cal_mgr_calibration_resp.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/cal_mgr_calibration_resp__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const CalMgrCalibrationResp & msg,
  std::ostream & out)
{
  out << "{";
  // member: resp_code
  {
    out << "resp_code: ";
    rosidl_generator_traits::value_to_yaml(msg.resp_code, out);
    out << ", ";
  }

  // member: cal_resp
  {
    out << "cal_resp: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_resp, out);
    out << ", ";
  }

  // member: step_no
  {
    out << "step_no: ";
    rosidl_generator_traits::value_to_yaml(msg.step_no, out);
    out << ", ";
  }

  // member: error
  {
    out << "error: ";
    rosidl_generator_traits::value_to_yaml(msg.error, out);
    out << ", ";
  }

  // member: warning
  {
    out << "warning: ";
    rosidl_generator_traits::value_to_yaml(msg.warning, out);
    out << ", ";
  }

  // member: enable_qual_read
  {
    out << "enable_qual_read: ";
    rosidl_generator_traits::value_to_yaml(msg.enable_qual_read, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CalMgrCalibrationResp & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: resp_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "resp_code: ";
    rosidl_generator_traits::value_to_yaml(msg.resp_code, out);
    out << "\n";
  }

  // member: cal_resp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_resp: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_resp, out);
    out << "\n";
  }

  // member: step_no
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "step_no: ";
    rosidl_generator_traits::value_to_yaml(msg.step_no, out);
    out << "\n";
  }

  // member: error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error: ";
    rosidl_generator_traits::value_to_yaml(msg.error, out);
    out << "\n";
  }

  // member: warning
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "warning: ";
    rosidl_generator_traits::value_to_yaml(msg.warning, out);
    out << "\n";
  }

  // member: enable_qual_read
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enable_qual_read: ";
    rosidl_generator_traits::value_to_yaml(msg.enable_qual_read, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CalMgrCalibrationResp & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::CalMgrCalibrationResp & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::CalMgrCalibrationResp & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::CalMgrCalibrationResp>()
{
  return "weigh_app_interfaces::msg::CalMgrCalibrationResp";
}

template<>
inline const char * name<weigh_app_interfaces::msg::CalMgrCalibrationResp>()
{
  return "weigh_app_interfaces/msg/CalMgrCalibrationResp";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::CalMgrCalibrationResp>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::CalMgrCalibrationResp>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::CalMgrCalibrationResp>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__TRAITS_HPP_
