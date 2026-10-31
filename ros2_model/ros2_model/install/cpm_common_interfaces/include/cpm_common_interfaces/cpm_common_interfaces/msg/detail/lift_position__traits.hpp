// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/LiftPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lift_position.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/lift_position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LiftPosition & msg,
  std::ostream & out)
{
  out << "{";
  // member: angle
  {
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
    out << ", ";
  }

  // member: percent_angle
  {
    out << "percent_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.percent_angle, out);
    out << ", ";
  }

  // member: cylinder_length
  {
    out << "cylinder_length: ";
    rosidl_generator_traits::value_to_yaml(msg.cylinder_length, out);
    out << ", ";
  }

  // member: percent_cylinder_length
  {
    out << "percent_cylinder_length: ";
    rosidl_generator_traits::value_to_yaml(msg.percent_cylinder_length, out);
    out << ", ";
  }

  // member: cylinder_extension
  {
    out << "cylinder_extension: ";
    rosidl_generator_traits::value_to_yaml(msg.cylinder_extension, out);
    out << ", ";
  }

  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LiftPosition & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
    out << "\n";
  }

  // member: percent_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "percent_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.percent_angle, out);
    out << "\n";
  }

  // member: cylinder_length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cylinder_length: ";
    rosidl_generator_traits::value_to_yaml(msg.cylinder_length, out);
    out << "\n";
  }

  // member: percent_cylinder_length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "percent_cylinder_length: ";
    rosidl_generator_traits::value_to_yaml(msg.percent_cylinder_length, out);
    out << "\n";
  }

  // member: cylinder_extension
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cylinder_extension: ";
    rosidl_generator_traits::value_to_yaml(msg.cylinder_extension, out);
    out << "\n";
  }

  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LiftPosition & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::LiftPosition & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::LiftPosition & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::LiftPosition>()
{
  return "cpm_common_interfaces::msg::LiftPosition";
}

template<>
inline const char * name<cpm_common_interfaces::msg::LiftPosition>()
{
  return "cpm_common_interfaces/msg/LiftPosition";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::LiftPosition>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::LiftPosition>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cpm_common_interfaces::msg::LiftPosition>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LIFT_POSITION__TRAITS_HPP_
