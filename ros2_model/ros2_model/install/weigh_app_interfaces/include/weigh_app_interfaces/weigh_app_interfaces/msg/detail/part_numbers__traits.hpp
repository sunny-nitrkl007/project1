// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/PartNumbers.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/part_numbers.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/part_numbers__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const PartNumbers & msg,
  std::ostream & out)
{
  out << "{";
  // member: product_id_num
  {
    out << "product_id_num: ";
    rosidl_generator_traits::value_to_yaml(msg.product_id_num, out);
    out << ", ";
  }

  // member: equipment_id
  {
    out << "equipment_id: ";
    rosidl_generator_traits::value_to_yaml(msg.equipment_id, out);
    out << ", ";
  }

  // member: sw_group_part_num
  {
    out << "sw_group_part_num: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_part_num, out);
    out << ", ";
  }

  // member: sw_group_release_date
  {
    out << "sw_group_release_date: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_release_date, out);
    out << ", ";
  }

  // member: sw_group_description
  {
    out << "sw_group_description: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_description, out);
    out << ", ";
  }

  // member: ecm_part_num
  {
    out << "ecm_part_num: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_part_num, out);
    out << ", ";
  }

  // member: model_num
  {
    out << "model_num: ";
    rosidl_generator_traits::value_to_yaml(msg.model_num, out);
    out << ", ";
  }

  // member: ecm_serial_num
  {
    out << "ecm_serial_num: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_serial_num, out);
    out << ", ";
  }

  // member: product_id_num_set
  {
    out << "product_id_num_set: ";
    rosidl_generator_traits::value_to_yaml(msg.product_id_num_set, out);
    out << ", ";
  }

  // member: sw_group_part_num_set
  {
    out << "sw_group_part_num_set: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_part_num_set, out);
    out << ", ";
  }

  // member: sw_group_release_date_set
  {
    out << "sw_group_release_date_set: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_release_date_set, out);
    out << ", ";
  }

  // member: sw_group_description_set
  {
    out << "sw_group_description_set: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_description_set, out);
    out << ", ";
  }

  // member: ecm_part_num_set
  {
    out << "ecm_part_num_set: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_part_num_set, out);
    out << ", ";
  }

  // member: model_num_set
  {
    out << "model_num_set: ";
    rosidl_generator_traits::value_to_yaml(msg.model_num_set, out);
    out << ", ";
  }

  // member: ecm_serial_num_set
  {
    out << "ecm_serial_num_set: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_serial_num_set, out);
    out << ", ";
  }

  // member: equipment_id_set
  {
    out << "equipment_id_set: ";
    rosidl_generator_traits::value_to_yaml(msg.equipment_id_set, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PartNumbers & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: product_id_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "product_id_num: ";
    rosidl_generator_traits::value_to_yaml(msg.product_id_num, out);
    out << "\n";
  }

  // member: equipment_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "equipment_id: ";
    rosidl_generator_traits::value_to_yaml(msg.equipment_id, out);
    out << "\n";
  }

  // member: sw_group_part_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sw_group_part_num: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_part_num, out);
    out << "\n";
  }

  // member: sw_group_release_date
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sw_group_release_date: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_release_date, out);
    out << "\n";
  }

  // member: sw_group_description
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sw_group_description: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_description, out);
    out << "\n";
  }

  // member: ecm_part_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ecm_part_num: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_part_num, out);
    out << "\n";
  }

  // member: model_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "model_num: ";
    rosidl_generator_traits::value_to_yaml(msg.model_num, out);
    out << "\n";
  }

  // member: ecm_serial_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ecm_serial_num: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_serial_num, out);
    out << "\n";
  }

  // member: product_id_num_set
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "product_id_num_set: ";
    rosidl_generator_traits::value_to_yaml(msg.product_id_num_set, out);
    out << "\n";
  }

  // member: sw_group_part_num_set
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sw_group_part_num_set: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_part_num_set, out);
    out << "\n";
  }

  // member: sw_group_release_date_set
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sw_group_release_date_set: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_release_date_set, out);
    out << "\n";
  }

  // member: sw_group_description_set
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sw_group_description_set: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_group_description_set, out);
    out << "\n";
  }

  // member: ecm_part_num_set
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ecm_part_num_set: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_part_num_set, out);
    out << "\n";
  }

  // member: model_num_set
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "model_num_set: ";
    rosidl_generator_traits::value_to_yaml(msg.model_num_set, out);
    out << "\n";
  }

  // member: ecm_serial_num_set
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ecm_serial_num_set: ";
    rosidl_generator_traits::value_to_yaml(msg.ecm_serial_num_set, out);
    out << "\n";
  }

  // member: equipment_id_set
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "equipment_id_set: ";
    rosidl_generator_traits::value_to_yaml(msg.equipment_id_set, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PartNumbers & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::PartNumbers & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::PartNumbers & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::PartNumbers>()
{
  return "weigh_app_interfaces::msg::PartNumbers";
}

template<>
inline const char * name<weigh_app_interfaces::msg::PartNumbers>()
{
  return "weigh_app_interfaces/msg/PartNumbers";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::PartNumbers>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::PartNumbers>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<weigh_app_interfaces::msg::PartNumbers>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__TRAITS_HPP_
