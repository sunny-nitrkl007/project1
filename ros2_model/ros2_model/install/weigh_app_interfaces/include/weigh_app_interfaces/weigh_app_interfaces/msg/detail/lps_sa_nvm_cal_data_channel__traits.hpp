// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'lps_sa_nvm_calibration_data_main'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel_data_main__traits.hpp"
// Member 'lps_sa_nvm_calibration_data_debug'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel_data_debug__traits.hpp"
// Member 'imu_cal_results'
#include "weigh_app_interfaces/msg/detail/lps_cal_imu_results__traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaNvmCalDataChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: lps_sa_nvm_calibration_data_main
  {
    out << "lps_sa_nvm_calibration_data_main: ";
    to_flow_style_yaml(msg.lps_sa_nvm_calibration_data_main, out);
    out << ", ";
  }

  // member: lps_sa_nvm_calibration_data_debug
  {
    out << "lps_sa_nvm_calibration_data_debug: ";
    to_flow_style_yaml(msg.lps_sa_nvm_calibration_data_debug, out);
    out << ", ";
  }

  // member: imu_cal_results
  {
    out << "imu_cal_results: ";
    to_flow_style_yaml(msg.imu_cal_results, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaNvmCalDataChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: lps_sa_nvm_calibration_data_main
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_sa_nvm_calibration_data_main:\n";
    to_block_style_yaml(msg.lps_sa_nvm_calibration_data_main, out, indentation + 2);
  }

  // member: lps_sa_nvm_calibration_data_debug
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_sa_nvm_calibration_data_debug:\n";
    to_block_style_yaml(msg.lps_sa_nvm_calibration_data_debug, out, indentation + 2);
  }

  // member: imu_cal_results
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "imu_cal_results:\n";
    to_block_style_yaml(msg.imu_cal_results, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaNvmCalDataChannel & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaNvmCalDataChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaNvmCalDataChannel & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel>()
{
  return "weigh_app_interfaces::msg::LpsSaNvmCalDataChannel";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel>()
{
  return "weigh_app_interfaces/msg/LpsSaNvmCalDataChannel";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel>
  : std::integral_constant<bool, has_fixed_size<weigh_app_interfaces::msg::LpsCalIMUResults>::value && has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug>::value && has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain>::value> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel>
  : std::integral_constant<bool, has_bounded_size<weigh_app_interfaces::msg::LpsCalIMUResults>::value && has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug>::value && has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataMain>::value> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL__TRAITS_HPP_
