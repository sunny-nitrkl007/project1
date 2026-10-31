// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyDataOnTheFly.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_data_on_the_fly.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_data_on_the_fly__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'status_flags'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_status_flags__traits.hpp"
// Member 'curve_info'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_curve_fit_info__traits.hpp"
// Member 'cal_updates'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_misc_updates__traits.hpp"
// Member 'cal_overrides'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_overrides__traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaNvmCalOnTheFlyDataOnTheFly & msg,
  std::ostream & out)
{
  out << "{";
  // member: status_flags
  {
    out << "status_flags: ";
    to_flow_style_yaml(msg.status_flags, out);
    out << ", ";
  }

  // member: curve_info
  {
    out << "curve_info: ";
    to_flow_style_yaml(msg.curve_info, out);
    out << ", ";
  }

  // member: cal_updates
  {
    out << "cal_updates: ";
    to_flow_style_yaml(msg.cal_updates, out);
    out << ", ";
  }

  // member: cal_overrides
  {
    out << "cal_overrides: ";
    to_flow_style_yaml(msg.cal_overrides, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaNvmCalOnTheFlyDataOnTheFly & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status_flags
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status_flags:\n";
    to_block_style_yaml(msg.status_flags, out, indentation + 2);
  }

  // member: curve_info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "curve_info:\n";
    to_block_style_yaml(msg.curve_info, out, indentation + 2);
  }

  // member: cal_updates
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_updates:\n";
    to_block_style_yaml(msg.cal_updates, out, indentation + 2);
  }

  // member: cal_overrides
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_overrides:\n";
    to_block_style_yaml(msg.cal_overrides, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaNvmCalOnTheFlyDataOnTheFly & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly>()
{
  return "weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly>()
{
  return "weigh_app_interfaces/msg/LpsSaNvmCalOnTheFlyDataOnTheFly";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly>
  : std::integral_constant<bool, has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo>::value && has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates>::value && has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides>::value && has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags>::value> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly>
  : std::integral_constant<bool, has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo>::value && has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates>::value && has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides>::value && has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags>::value> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataOnTheFly>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_ON_THE_FLY__TRAITS_HPP_
