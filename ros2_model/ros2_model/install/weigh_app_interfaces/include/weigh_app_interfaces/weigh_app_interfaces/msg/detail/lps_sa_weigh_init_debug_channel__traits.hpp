// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaWeighInitDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_weigh_init_debug_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_weigh_init_debug_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaWeighInitDebugChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: exec_rate
  {
    out << "exec_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.exec_rate, out);
    out << ", ";
  }

  // member: cal_weight
  {
    out << "cal_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_weight, out);
    out << ", ";
  }

  // member: cal_status
  {
    out << "cal_status: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_status, out);
    out << ", ";
  }

  // member: cal_adjust
  {
    out << "cal_adjust: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_adjust, out);
    out << ", ";
  }

  // member: zero_weight
  {
    out << "zero_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_weight, out);
    out << ", ";
  }

  // member: dig_target_wt
  {
    out << "dig_target_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_target_wt, out);
    out << ", ";
  }

  // member: start_of_weigh
  {
    out << "start_of_weigh: ";
    rosidl_generator_traits::value_to_yaml(msg.start_of_weigh, out);
    out << ", ";
  }

  // member: tilt_comp_gain_scalar
  {
    out << "tilt_comp_gain_scalar: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_comp_gain_scalar, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaWeighInitDebugChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: exec_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "exec_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.exec_rate, out);
    out << "\n";
  }

  // member: cal_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_weight, out);
    out << "\n";
  }

  // member: cal_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_status: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_status, out);
    out << "\n";
  }

  // member: cal_adjust
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_adjust: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_adjust, out);
    out << "\n";
  }

  // member: zero_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zero_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_weight, out);
    out << "\n";
  }

  // member: dig_target_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dig_target_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.dig_target_wt, out);
    out << "\n";
  }

  // member: start_of_weigh
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start_of_weigh: ";
    rosidl_generator_traits::value_to_yaml(msg.start_of_weigh, out);
    out << "\n";
  }

  // member: tilt_comp_gain_scalar
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_comp_gain_scalar: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_comp_gain_scalar, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaWeighInitDebugChannel & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel>()
{
  return "weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel>()
{
  return "weigh_app_interfaces/msg/LpsSaWeighInitDebugChannel";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_INIT_DEBUG_CHANNEL__TRAITS_HPP_
