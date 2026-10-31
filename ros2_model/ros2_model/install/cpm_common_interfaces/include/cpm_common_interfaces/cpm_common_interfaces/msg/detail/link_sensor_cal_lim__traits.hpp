// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/LinkSensorCalLim.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/link_sensor_cal_lim.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/link_sensor_cal_lim__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LinkSensorCalLim & msg,
  std::ostream & out)
{
  out << "{";
  // member: lift_pos_sensor_dc
  {
    out << "lift_pos_sensor_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_pos_sensor_dc, out);
    out << ", ";
  }

  // member: lift_pos_sensor_full_raise_dc
  {
    out << "lift_pos_sensor_full_raise_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_pos_sensor_full_raise_dc, out);
    out << ", ";
  }

  // member: lift_pos_sensor_full_lower_dc
  {
    out << "lift_pos_sensor_full_lower_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_pos_sensor_full_lower_dc, out);
    out << ", ";
  }

  // member: tilt_pos_sensor_dc
  {
    out << "tilt_pos_sensor_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_pos_sensor_dc, out);
    out << ", ";
  }

  // member: tilt_pos_sensor_full_rack_dc
  {
    out << "tilt_pos_sensor_full_rack_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_pos_sensor_full_rack_dc, out);
    out << ", ";
  }

  // member: tilt_pos_sensor_full_dump_dc
  {
    out << "tilt_pos_sensor_full_dump_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_pos_sensor_full_dump_dc, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LinkSensorCalLim & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: lift_pos_sensor_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_pos_sensor_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_pos_sensor_dc, out);
    out << "\n";
  }

  // member: lift_pos_sensor_full_raise_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_pos_sensor_full_raise_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_pos_sensor_full_raise_dc, out);
    out << "\n";
  }

  // member: lift_pos_sensor_full_lower_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_pos_sensor_full_lower_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_pos_sensor_full_lower_dc, out);
    out << "\n";
  }

  // member: tilt_pos_sensor_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_pos_sensor_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_pos_sensor_dc, out);
    out << "\n";
  }

  // member: tilt_pos_sensor_full_rack_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_pos_sensor_full_rack_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_pos_sensor_full_rack_dc, out);
    out << "\n";
  }

  // member: tilt_pos_sensor_full_dump_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_pos_sensor_full_dump_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_pos_sensor_full_dump_dc, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LinkSensorCalLim & msg, bool use_flow_style = false)
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

}  // namespace cpm_common_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cpm_common_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cpm_common_interfaces::msg::LinkSensorCalLim & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::LinkSensorCalLim & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::LinkSensorCalLim>()
{
  return "cpm_common_interfaces::msg::LinkSensorCalLim";
}

template<>
inline const char * name<cpm_common_interfaces::msg::LinkSensorCalLim>()
{
  return "cpm_common_interfaces/msg/LinkSensorCalLim";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::LinkSensorCalLim>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::LinkSensorCalLim>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cpm_common_interfaces::msg::LinkSensorCalLim>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LINK_SENSOR_CAL_LIM__TRAITS_HPP_
