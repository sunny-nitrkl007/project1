// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/ProdMeasureSensorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/prod_measure_sensor_status.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/prod_measure_sensor_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ProdMeasureSensorStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: lift_link_dc
  {
    out << "lift_link_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_link_dc, out);
    out << ", ";
  }

  // member: lift_cyl_pos
  {
    out << "lift_cyl_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_pos, out);
    out << ", ";
  }

  // member: lift_cyl_he_pres
  {
    out << "lift_cyl_he_pres: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_he_pres, out);
    out << ", ";
  }

  // member: lift_cyl_re_pres
  {
    out << "lift_cyl_re_pres: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_re_pres, out);
    out << ", ";
  }

  // member: tilt_sensor_config
  {
    out << "tilt_sensor_config: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_sensor_config, out);
    out << ", ";
  }

  // member: tilt_cyl_he_pres
  {
    out << "tilt_cyl_he_pres: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_cyl_he_pres, out);
    out << ", ";
  }

  // member: tilt_cyl_re_pres
  {
    out << "tilt_cyl_re_pres: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_cyl_re_pres, out);
    out << ", ";
  }

  // member: tilt_link_dc
  {
    out << "tilt_link_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_link_dc, out);
    out << ", ";
  }

  // member: hyd_oil_temp
  {
    out << "hyd_oil_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.hyd_oil_temp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ProdMeasureSensorStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: lift_link_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_link_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_link_dc, out);
    out << "\n";
  }

  // member: lift_cyl_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_cyl_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_pos, out);
    out << "\n";
  }

  // member: lift_cyl_he_pres
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_cyl_he_pres: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_he_pres, out);
    out << "\n";
  }

  // member: lift_cyl_re_pres
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lift_cyl_re_pres: ";
    rosidl_generator_traits::value_to_yaml(msg.lift_cyl_re_pres, out);
    out << "\n";
  }

  // member: tilt_sensor_config
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_sensor_config: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_sensor_config, out);
    out << "\n";
  }

  // member: tilt_cyl_he_pres
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_cyl_he_pres: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_cyl_he_pres, out);
    out << "\n";
  }

  // member: tilt_cyl_re_pres
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_cyl_re_pres: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_cyl_re_pres, out);
    out << "\n";
  }

  // member: tilt_link_dc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_link_dc: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_link_dc, out);
    out << "\n";
  }

  // member: hyd_oil_temp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hyd_oil_temp: ";
    rosidl_generator_traits::value_to_yaml(msg.hyd_oil_temp, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ProdMeasureSensorStatus & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::ProdMeasureSensorStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::ProdMeasureSensorStatus & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::ProdMeasureSensorStatus>()
{
  return "cpm_common_interfaces::msg::ProdMeasureSensorStatus";
}

template<>
inline const char * name<cpm_common_interfaces::msg::ProdMeasureSensorStatus>()
{
  return "cpm_common_interfaces/msg/ProdMeasureSensorStatus";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::ProdMeasureSensorStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::ProdMeasureSensorStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cpm_common_interfaces::msg::ProdMeasureSensorStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__TRAITS_HPP_
