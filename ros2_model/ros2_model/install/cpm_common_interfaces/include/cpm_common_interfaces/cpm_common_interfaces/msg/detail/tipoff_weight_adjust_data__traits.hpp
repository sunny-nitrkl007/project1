// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/TipoffWeightAdjustData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/tipoff_weight_adjust_data.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/tipoff_weight_adjust_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TipoffWeightAdjustData & msg,
  std::ostream & out)
{
  out << "{";
  // member: tip_off_weight1
  {
    out << "tip_off_weight1: ";
    rosidl_generator_traits::value_to_yaml(msg.tip_off_weight1, out);
    out << ", ";
  }

  // member: weigh_range_weight1
  {
    out << "weigh_range_weight1: ";
    rosidl_generator_traits::value_to_yaml(msg.weigh_range_weight1, out);
    out << ", ";
  }

  // member: tip_off_weight2
  {
    out << "tip_off_weight2: ";
    rosidl_generator_traits::value_to_yaml(msg.tip_off_weight2, out);
    out << ", ";
  }

  // member: weigh_range_weight2
  {
    out << "weigh_range_weight2: ";
    rosidl_generator_traits::value_to_yaml(msg.weigh_range_weight2, out);
    out << ", ";
  }

  // member: new_data_flag
  {
    out << "new_data_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.new_data_flag, out);
    out << ", ";
  }

  // member: reset
  {
    out << "reset: ";
    rosidl_generator_traits::value_to_yaml(msg.reset, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TipoffWeightAdjustData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: tip_off_weight1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tip_off_weight1: ";
    rosidl_generator_traits::value_to_yaml(msg.tip_off_weight1, out);
    out << "\n";
  }

  // member: weigh_range_weight1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weigh_range_weight1: ";
    rosidl_generator_traits::value_to_yaml(msg.weigh_range_weight1, out);
    out << "\n";
  }

  // member: tip_off_weight2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tip_off_weight2: ";
    rosidl_generator_traits::value_to_yaml(msg.tip_off_weight2, out);
    out << "\n";
  }

  // member: weigh_range_weight2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weigh_range_weight2: ";
    rosidl_generator_traits::value_to_yaml(msg.weigh_range_weight2, out);
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

  // member: reset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reset: ";
    rosidl_generator_traits::value_to_yaml(msg.reset, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TipoffWeightAdjustData & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::TipoffWeightAdjustData & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::TipoffWeightAdjustData & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::TipoffWeightAdjustData>()
{
  return "cpm_common_interfaces::msg::TipoffWeightAdjustData";
}

template<>
inline const char * name<cpm_common_interfaces::msg::TipoffWeightAdjustData>()
{
  return "cpm_common_interfaces/msg/TipoffWeightAdjustData";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::TipoffWeightAdjustData>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::TipoffWeightAdjustData>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cpm_common_interfaces::msg::TipoffWeightAdjustData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__TIPOFF_WEIGHT_ADJUST_DATA__TRAITS_HPP_
