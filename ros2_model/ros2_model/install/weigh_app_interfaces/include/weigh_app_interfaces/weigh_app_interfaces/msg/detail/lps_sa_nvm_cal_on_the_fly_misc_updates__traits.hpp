// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyMiscUpdates.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_misc_updates.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_misc_updates__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaNvmCalOnTheFlyMiscUpdates & msg,
  std::ostream & out)
{
  out << "{";
  // member: lift_he_pres_stat
  {
    out << "lift_he_pres_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_he_pres_stat, out);
    out << ", ";
  }

  // member: lift_re_pres_stat
  {
    out << "lift_re_pres_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_re_pres_stat, out);
    out << ", ";
  }

  // member: lift_cyl_length_norm_stat
  {
    out << "lift_cyl_length_norm_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_length_norm_stat, out);
    out << ", ";
  }

  // member: hyd_oil_temp_stat
  {
    out << "hyd_oil_temp_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.hyd_oil_temp_stat, out);
    out << ", ";
  }

  // member: lift_cyl_vel_stat
  {
    out << "lift_cyl_vel_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_vel_stat, out);
    out << ", ";
  }

  // member: tilt_cyl_length_norm_stat
  {
    out << "tilt_cyl_length_norm_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_cyl_length_norm_stat, out);
    out << ", ";
  }

  // member: bkt_angle_stat
  {
    out << "bkt_angle_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.bkt_angle_stat, out);
    out << ", ";
  }

  // member: lift_lever_info_lever_info_available
  {
    out << "lift_lever_info_lever_info_available: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_lever_info_lever_info_available, out);
    out << ", ";
  }

  // member: lift_lever_info_faulted
  {
    out << "lift_lever_info_faulted: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_lever_info_faulted, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaNvmCalOnTheFlyMiscUpdates & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: lift_he_pres_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_he_pres_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_he_pres_stat, out);
    out << "\n";
  }

  // member: lift_re_pres_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_re_pres_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_re_pres_stat, out);
    out << "\n";
  }

  // member: lift_cyl_length_norm_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_cyl_length_norm_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_length_norm_stat, out);
    out << "\n";
  }

  // member: hyd_oil_temp_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hyd_oil_temp_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.hyd_oil_temp_stat, out);
    out << "\n";
  }

  // member: lift_cyl_vel_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_cyl_vel_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_vel_stat, out);
    out << "\n";
  }

  // member: tilt_cyl_length_norm_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_cyl_length_norm_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_cyl_length_norm_stat, out);
    out << "\n";
  }

  // member: bkt_angle_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bkt_angle_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.bkt_angle_stat, out);
    out << "\n";
  }

  // member: lift_lever_info_lever_info_available
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_lever_info_lever_info_available: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_lever_info_lever_info_available, out);
    out << "\n";
  }

  // member: lift_lever_info_faulted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_lever_info_faulted: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_lever_info_faulted, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaNvmCalOnTheFlyMiscUpdates & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates>()
{
  return "weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates>()
{
  return "weigh_app_interfaces/msg/LpsSaNvmCalOnTheFlyMiscUpdates";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyMiscUpdates>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_MISC_UPDATES__TRAITS_HPP_
