// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyOverrides.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_overrides.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_overrides__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'tilt_overrides'
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_tilt_overrides__traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaNvmCalOnTheFlyOverrides & msg,
  std::ostream & out)
{
  out << "{";
  // member: lps_cal_ovr_state
  {
    out << "lps_cal_ovr_state: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_ovr_state, out);
    out << ", ";
  }

  // member: lps_cal_app_inf_raise_cmd_lmt
  {
    out << "lps_cal_app_inf_raise_cmd_lmt: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_raise_cmd_lmt, out);
    out << ", ";
  }

  // member: lps_cal_app_inf_lower_cmd_lmt
  {
    out << "lps_cal_app_inf_lower_cmd_lmt: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_lower_cmd_lmt, out);
    out << ", ";
  }

  // member: lps_cal_app_inf_rack_cmd_lmt
  {
    out << "lps_cal_app_inf_rack_cmd_lmt: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_rack_cmd_lmt, out);
    out << ", ";
  }

  // member: lps_cal_app_inf_dump_cmd_lmt
  {
    out << "lps_cal_app_inf_dump_cmd_lmt: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_dump_cmd_lmt, out);
    out << ", ";
  }

  // member: lps_cal_app_inf_eng_spd_lmt
  {
    out << "lps_cal_app_inf_eng_spd_lmt: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_eng_spd_lmt, out);
    out << ", ";
  }

  // member: lps_cal_app_inf_cal_ovr_active
  {
    out << "lps_cal_app_inf_cal_ovr_active: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_cal_ovr_active, out);
    out << ", ";
  }

  // member: lift_bottom_flag
  {
    out << "lift_bottom_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_bottom_flag, out);
    out << ", ";
  }

  // member: lift_top_flag
  {
    out << "lift_top_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_top_flag, out);
    out << ", ";
  }

  // member: cal_ovr_acknowledge
  {
    out << "cal_ovr_acknowledge: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_ovr_acknowledge, out);
    out << ", ";
  }

  // member: lift_valve_cmd_percent
  {
    out << "lift_valve_cmd_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_valve_cmd_percent, out);
    out << ", ";
  }

  // member: lift_in_raise_detent
  {
    out << "lift_in_raise_detent: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_in_raise_detent, out);
    out << ", ";
  }

  // member: lift_in_lower_detent
  {
    out << "lift_in_lower_detent: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_in_lower_detent, out);
    out << ", ";
  }

  // member: lift_in_center
  {
    out << "lift_in_center: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_in_center, out);
    out << ", ";
  }

  // member: lift_faulted
  {
    out << "lift_faulted: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_faulted, out);
    out << ", ";
  }

  // member: lever_info_available
  {
    out << "lever_info_available: ";
    rosidl_generator_traits::value_to_yaml(msg.lever_info_available, out);
    out << ", ";
  }

  // member: tilt_overrides
  {
    out << "tilt_overrides: ";
    to_flow_style_yaml(msg.tilt_overrides, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaNvmCalOnTheFlyOverrides & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: lps_cal_ovr_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_cal_ovr_state: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_ovr_state, out);
    out << "\n";
  }

  // member: lps_cal_app_inf_raise_cmd_lmt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_cal_app_inf_raise_cmd_lmt: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_raise_cmd_lmt, out);
    out << "\n";
  }

  // member: lps_cal_app_inf_lower_cmd_lmt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_cal_app_inf_lower_cmd_lmt: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_lower_cmd_lmt, out);
    out << "\n";
  }

  // member: lps_cal_app_inf_rack_cmd_lmt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_cal_app_inf_rack_cmd_lmt: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_rack_cmd_lmt, out);
    out << "\n";
  }

  // member: lps_cal_app_inf_dump_cmd_lmt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_cal_app_inf_dump_cmd_lmt: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_dump_cmd_lmt, out);
    out << "\n";
  }

  // member: lps_cal_app_inf_eng_spd_lmt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_cal_app_inf_eng_spd_lmt: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_eng_spd_lmt, out);
    out << "\n";
  }

  // member: lps_cal_app_inf_cal_ovr_active
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_cal_app_inf_cal_ovr_active: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_app_inf_cal_ovr_active, out);
    out << "\n";
  }

  // member: lift_bottom_flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_bottom_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_bottom_flag, out);
    out << "\n";
  }

  // member: lift_top_flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_top_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_top_flag, out);
    out << "\n";
  }

  // member: cal_ovr_acknowledge
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_ovr_acknowledge: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_ovr_acknowledge, out);
    out << "\n";
  }

  // member: lift_valve_cmd_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_valve_cmd_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_valve_cmd_percent, out);
    out << "\n";
  }

  // member: lift_in_raise_detent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_in_raise_detent: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_in_raise_detent, out);
    out << "\n";
  }

  // member: lift_in_lower_detent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_in_lower_detent: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_in_lower_detent, out);
    out << "\n";
  }

  // member: lift_in_center
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_in_center: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_in_center, out);
    out << "\n";
  }

  // member: lift_faulted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_faulted: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_faulted, out);
    out << "\n";
  }

  // member: lever_info_available
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lever_info_available: ";
    rosidl_generator_traits::value_to_yaml(msg.lever_info_available, out);
    out << "\n";
  }

  // member: tilt_overrides
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_overrides:\n";
    to_block_style_yaml(msg.tilt_overrides, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaNvmCalOnTheFlyOverrides & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides>()
{
  return "weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides>()
{
  return "weigh_app_interfaces/msg/LpsSaNvmCalOnTheFlyOverrides";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides>
  : std::integral_constant<bool, has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides>::value> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides>
  : std::integral_constant<bool, has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides>::value> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyOverrides>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_OVERRIDES__TRAITS_HPP_
