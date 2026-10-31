// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalDataChannelDataDebug.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel_data_debug.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_data_channel_data_debug__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaNvmCalDataChannelDataDebug & msg,
  std::ostream & out)
{
  out << "{";
  // member: lift_full_lower_dc_inf_value
  {
    out << "lift_full_lower_dc_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_full_lower_dc_inf_value, out);
    out << ", ";
  }

  // member: lift_full_raise_dc_inf_value
  {
    out << "lift_full_raise_dc_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_full_raise_dc_inf_value, out);
    out << ", ";
  }

  // member: tilt_full_dump_dc_inf_value
  {
    out << "tilt_full_dump_dc_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_full_dump_dc_inf_value, out);
    out << ", ";
  }

  // member: tilt_full_rack_dc_inf_value
  {
    out << "tilt_full_rack_dc_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_full_rack_dc_inf_value, out);
    out << ", ";
  }

  // member: tilt_dump_stop_angle_inf_value
  {
    out << "tilt_dump_stop_angle_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_dump_stop_angle_inf_value, out);
    out << ", ";
  }

  // member: tilt_rack_stop_angle_inf_value
  {
    out << "tilt_rack_stop_angle_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_rack_stop_angle_inf_value, out);
    out << ", ";
  }

  // member: pcs_vel_slope
  {
    out << "pcs_vel_slope: ";
    rosidl_generator_traits::value_to_yaml(msg.pcs_vel_slope, out);
    out << ", ";
  }

  // member: pcs_cal_weight
  {
    out << "pcs_cal_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.pcs_cal_weight, out);
    out << ", ";
  }

  // member: zero_weight
  {
    out << "zero_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_weight, out);
    out << ", ";
  }

  // member: cal_adjust
  {
    out << "cal_adjust: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_adjust, out);
    out << ", ";
  }

  // member: temp_slope
  {
    out << "temp_slope: ";
    rosidl_generator_traits::value_to_yaml(msg.temp_slope, out);
    out << ", ";
  }

  // member: empty_temp
  {
    out << "empty_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_temp, out);
    out << ", ";
  }

  // member: full_temp
  {
    out << "full_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.full_temp, out);
    out << ", ";
  }

  // member: empty_bucket_weight_est
  {
    out << "empty_bucket_weight_est: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_bucket_weight_est, out);
    out << ", ";
  }

  // member: cal_adjust_temp
  {
    out << "cal_adjust_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_adjust_temp, out);
    out << ", ";
  }

  // member: hyd_oil_type_index
  {
    out << "hyd_oil_type_index: ";
    rosidl_generator_traits::value_to_yaml(msg.hyd_oil_type_index, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaNvmCalDataChannelDataDebug & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: lift_full_lower_dc_inf_value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_full_lower_dc_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_full_lower_dc_inf_value, out);
    out << "\n";
  }

  // member: lift_full_raise_dc_inf_value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_full_raise_dc_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_full_raise_dc_inf_value, out);
    out << "\n";
  }

  // member: tilt_full_dump_dc_inf_value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_full_dump_dc_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_full_dump_dc_inf_value, out);
    out << "\n";
  }

  // member: tilt_full_rack_dc_inf_value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_full_rack_dc_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_full_rack_dc_inf_value, out);
    out << "\n";
  }

  // member: tilt_dump_stop_angle_inf_value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_dump_stop_angle_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_dump_stop_angle_inf_value, out);
    out << "\n";
  }

  // member: tilt_rack_stop_angle_inf_value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_rack_stop_angle_inf_value: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_rack_stop_angle_inf_value, out);
    out << "\n";
  }

  // member: pcs_vel_slope
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pcs_vel_slope: ";
    rosidl_generator_traits::value_to_yaml(msg.pcs_vel_slope, out);
    out << "\n";
  }

  // member: pcs_cal_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pcs_cal_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.pcs_cal_weight, out);
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

  // member: cal_adjust
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_adjust: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_adjust, out);
    out << "\n";
  }

  // member: temp_slope
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "temp_slope: ";
    rosidl_generator_traits::value_to_yaml(msg.temp_slope, out);
    out << "\n";
  }

  // member: empty_temp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "empty_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_temp, out);
    out << "\n";
  }

  // member: full_temp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "full_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.full_temp, out);
    out << "\n";
  }

  // member: empty_bucket_weight_est
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "empty_bucket_weight_est: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_bucket_weight_est, out);
    out << "\n";
  }

  // member: cal_adjust_temp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_adjust_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_adjust_temp, out);
    out << "\n";
  }

  // member: hyd_oil_type_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hyd_oil_type_index: ";
    rosidl_generator_traits::value_to_yaml(msg.hyd_oil_type_index, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaNvmCalDataChannelDataDebug & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug>()
{
  return "weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug>()
{
  return "weigh_app_interfaces/msg/LpsSaNvmCalDataChannelDataDebug";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaNvmCalDataChannelDataDebug>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_DATA_CHANNEL_DATA_DEBUG__TRAITS_HPP_
