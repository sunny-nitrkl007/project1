// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyTiltOverrides.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_tilt_overrides.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_tilt_overrides__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaNvmCalOnTheFlyTiltOverrides & msg,
  std::ostream & out)
{
  out << "{";
  // member: lps_cal_tilt_ovr_state
  {
    out << "lps_cal_tilt_ovr_state: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_tilt_ovr_state, out);
    out << ", ";
  }

  // member: tilt_noise_max
  {
    out << "tilt_noise_max: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_noise_max, out);
    out << ", ";
  }

  // member: tilt_noise_min
  {
    out << "tilt_noise_min: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_noise_min, out);
    out << ", ";
  }

  // member: desired_tilt_extmm
  {
    out << "desired_tilt_extmm: ";
    rosidl_generator_traits::value_to_yaml(msg.desired_tilt_extmm, out);
    out << ", ";
  }

  // member: count_of_samples
  {
    out << "count_of_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.count_of_samples, out);
    out << ", ";
  }

  // member: tilt_dump_cmd_ovr
  {
    out << "tilt_dump_cmd_ovr: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_dump_cmd_ovr, out);
    out << ", ";
  }

  // member: lps_cal_tilt_ovr_start_request
  {
    out << "lps_cal_tilt_ovr_start_request: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_tilt_ovr_start_request, out);
    out << ", ";
  }

  // member: cal_tilt_override_complete
  {
    out << "cal_tilt_override_complete: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_tilt_override_complete, out);
    out << ", ";
  }

  // member: cal_tilt_override_fail
  {
    out << "cal_tilt_override_fail: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_tilt_override_fail, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaNvmCalOnTheFlyTiltOverrides & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: lps_cal_tilt_ovr_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_cal_tilt_ovr_state: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_tilt_ovr_state, out);
    out << "\n";
  }

  // member: tilt_noise_max
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_noise_max: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_noise_max, out);
    out << "\n";
  }

  // member: tilt_noise_min
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_noise_min: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_noise_min, out);
    out << "\n";
  }

  // member: desired_tilt_extmm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "desired_tilt_extmm: ";
    rosidl_generator_traits::value_to_yaml(msg.desired_tilt_extmm, out);
    out << "\n";
  }

  // member: count_of_samples
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "count_of_samples: ";
    rosidl_generator_traits::value_to_yaml(msg.count_of_samples, out);
    out << "\n";
  }

  // member: tilt_dump_cmd_ovr
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_dump_cmd_ovr: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_dump_cmd_ovr, out);
    out << "\n";
  }

  // member: lps_cal_tilt_ovr_start_request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lps_cal_tilt_ovr_start_request: ";
    rosidl_generator_traits::value_to_yaml(msg.lps_cal_tilt_ovr_start_request, out);
    out << "\n";
  }

  // member: cal_tilt_override_complete
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_tilt_override_complete: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_tilt_override_complete, out);
    out << "\n";
  }

  // member: cal_tilt_override_fail
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_tilt_override_fail: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_tilt_override_fail, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaNvmCalOnTheFlyTiltOverrides & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides>()
{
  return "weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides>()
{
  return "weigh_app_interfaces/msg/LpsSaNvmCalOnTheFlyTiltOverrides";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyTiltOverrides>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__TRAITS_HPP_
