// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyDataChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_data_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_data_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'lps_sa_nvm_calibration_data_on_the_fly'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_data_on_the_fly__traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaNvmCalOnTheFlyDataChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: lps_sa_nvm_calibration_data_on_the_fly
  {
    out << "lps_sa_nvm_calibration_data_on_the_fly: ";
    to_flow_style_yaml(msg.lps_sa_nvm_calibration_data_on_the_fly, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaNvmCalOnTheFlyDataChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: lps_sa_nvm_calibration_data_on_the_fly
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_sa_nvm_calibration_data_on_the_fly:\n";
    to_block_style_yaml(msg.lps_sa_nvm_calibration_data_on_the_fly, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaNvmCalOnTheFlyDataChannel & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel>()
{
  return "weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel>()
{
  return "weigh_app_interfaces/msg/LpsSaNvmCalOnTheFlyDataChannel";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel>
  : std::integral_constant<bool, has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly>::value> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel>
  : std::integral_constant<bool, has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly>::value> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__TRAITS_HPP_
