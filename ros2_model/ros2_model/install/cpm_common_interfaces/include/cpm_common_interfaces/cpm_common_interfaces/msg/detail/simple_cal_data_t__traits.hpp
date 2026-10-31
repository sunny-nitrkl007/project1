// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/SimpleCalDataT.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/simple_cal_data_t.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/simple_cal_data_t__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SimpleCalDataT & msg,
  std::ostream & out)
{
  out << "{";
  // member: time_stamp
  {
    out << "time_stamp: ";
    rosidl_generator_traits::value_to_yaml(msg.time_stamp, out);
    out << ", ";
  }

  // member: adjtruckweight
  {
    out << "adjtruckweight: ";
    rosidl_generator_traits::value_to_yaml(msg.adjtruckweight, out);
    out << ", ";
  }

  // member: zeroed_truck_wt
  {
    out << "zeroed_truck_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.zeroed_truck_wt, out);
    out << ", ";
  }

  // member: new_data_flag
  {
    out << "new_data_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.new_data_flag, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SimpleCalDataT & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: time_stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_stamp: ";
    rosidl_generator_traits::value_to_yaml(msg.time_stamp, out);
    out << "\n";
  }

  // member: adjtruckweight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "adjtruckweight: ";
    rosidl_generator_traits::value_to_yaml(msg.adjtruckweight, out);
    out << "\n";
  }

  // member: zeroed_truck_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zeroed_truck_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.zeroed_truck_wt, out);
    out << "\n";
  }

  // member: new_data_flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "new_data_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.new_data_flag, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SimpleCalDataT & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::SimpleCalDataT & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::SimpleCalDataT & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::SimpleCalDataT>()
{
  return "cpm_common_interfaces::msg::SimpleCalDataT";
}

template<>
inline const char * name<cpm_common_interfaces::msg::SimpleCalDataT>()
{
  return "cpm_common_interfaces/msg/SimpleCalDataT";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::SimpleCalDataT>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::SimpleCalDataT>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cpm_common_interfaces::msg::SimpleCalDataT>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__TRAITS_HPP_
