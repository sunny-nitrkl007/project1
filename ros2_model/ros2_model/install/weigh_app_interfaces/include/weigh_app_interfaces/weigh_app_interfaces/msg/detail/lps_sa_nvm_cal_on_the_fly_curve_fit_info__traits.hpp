// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyCurveFitInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_curve_fit_info.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_curve_fit_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'imu_cal_results'
#include "weigh_app_interfaces/msg/detail/lps_cal_imu_results__traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaNvmCalOnTheFlyCurveFitInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: hyd_oil_temp_met
  {
    out << "hyd_oil_temp_met: ";
    rosidl_generator_traits::value_to_yaml(msg.hyd_oil_temp_met, out);
    out << ", ";
  }

  // member: enforce_raise_detent
  {
    out << "enforce_raise_detent: ";
    rosidl_generator_traits::value_to_yaml(msg.enforce_raise_detent, out);
    out << ", ";
  }

  // member: enforce_lower_detent
  {
    out << "enforce_lower_detent: ";
    rosidl_generator_traits::value_to_yaml(msg.enforce_lower_detent, out);
    out << ", ";
  }

  // member: raise_fast_vel_done
  {
    out << "raise_fast_vel_done: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_fast_vel_done, out);
    out << ", ";
  }

  // member: raise_slow_fit_done
  {
    out << "raise_slow_fit_done: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_slow_fit_done, out);
    out << ", ";
  }

  // member: raise_fast_fit_done
  {
    out << "raise_fast_fit_done: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_fast_fit_done, out);
    out << ", ";
  }

  // member: lower_slow_fit_done
  {
    out << "lower_slow_fit_done: ";
    rosidl_generator_traits::value_to_yaml(msg.lower_slow_fit_done, out);
    out << ", ";
  }

  // member: internal_step
  {
    out << "internal_step: ";
    rosidl_generator_traits::value_to_yaml(msg.internal_step, out);
    out << ", ";
  }

  // member: raise_num_points
  {
    out << "raise_num_points: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_num_points, out);
    out << ", ";
  }

  // member: lower_num_points
  {
    out << "lower_num_points: ";
    rosidl_generator_traits::value_to_yaml(msg.lower_num_points, out);
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
  const LpsSaNvmCalOnTheFlyCurveFitInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: hyd_oil_temp_met
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hyd_oil_temp_met: ";
    rosidl_generator_traits::value_to_yaml(msg.hyd_oil_temp_met, out);
    out << "\n";
  }

  // member: enforce_raise_detent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enforce_raise_detent: ";
    rosidl_generator_traits::value_to_yaml(msg.enforce_raise_detent, out);
    out << "\n";
  }

  // member: enforce_lower_detent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enforce_lower_detent: ";
    rosidl_generator_traits::value_to_yaml(msg.enforce_lower_detent, out);
    out << "\n";
  }

  // member: raise_fast_vel_done
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raise_fast_vel_done: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_fast_vel_done, out);
    out << "\n";
  }

  // member: raise_slow_fit_done
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raise_slow_fit_done: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_slow_fit_done, out);
    out << "\n";
  }

  // member: raise_fast_fit_done
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raise_fast_fit_done: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_fast_fit_done, out);
    out << "\n";
  }

  // member: lower_slow_fit_done
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lower_slow_fit_done: ";
    rosidl_generator_traits::value_to_yaml(msg.lower_slow_fit_done, out);
    out << "\n";
  }

  // member: internal_step
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "internal_step: ";
    rosidl_generator_traits::value_to_yaml(msg.internal_step, out);
    out << "\n";
  }

  // member: raise_num_points
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raise_num_points: ";
    rosidl_generator_traits::value_to_yaml(msg.raise_num_points, out);
    out << "\n";
  }

  // member: lower_num_points
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lower_num_points: ";
    rosidl_generator_traits::value_to_yaml(msg.lower_num_points, out);
    out << "\n";
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

inline std::string to_yaml(const LpsSaNvmCalOnTheFlyCurveFitInfo & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo>()
{
  return "weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo>()
{
  return "weigh_app_interfaces/msg/LpsSaNvmCalOnTheFlyCurveFitInfo";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo>
  : std::integral_constant<bool, has_fixed_size<weigh_app_interfaces::msg::LpsCalIMUResults>::value> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo>
  : std::integral_constant<bool, has_bounded_size<weigh_app_interfaces::msg::LpsCalIMUResults>::value> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyCurveFitInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_CURVE_FIT_INFO__TRAITS_HPP_
