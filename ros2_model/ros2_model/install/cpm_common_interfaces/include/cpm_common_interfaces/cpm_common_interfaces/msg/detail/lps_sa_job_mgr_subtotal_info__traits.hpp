// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrSubtotalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_subtotal_info.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_subtotal_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaJobMgrSubtotalInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: subtotal_command
  {
    out << "subtotal_command: ";
    rosidl_generator_traits::value_to_yaml(msg.subtotal_command, out);
    out << ", ";
  }

  // member: current_step_number
  {
    out << "current_step_number: ";
    rosidl_generator_traits::value_to_yaml(msg.current_step_number, out);
    out << ", ";
  }

  // member: new_step_number
  {
    out << "new_step_number: ";
    rosidl_generator_traits::value_to_yaml(msg.new_step_number, out);
    out << ", ";
  }

  // member: target_weight
  {
    out << "target_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.target_weight, out);
    out << ", ";
  }

  // member: target_proportion
  {
    out << "target_proportion: ";
    rosidl_generator_traits::value_to_yaml(msg.target_proportion, out);
    out << ", ";
  }

  // member: target_passes
  {
    out << "target_passes: ";
    rosidl_generator_traits::value_to_yaml(msg.target_passes, out);
    out << ", ";
  }

  // member: material_id
  {
    out << "material_id: ";
    rosidl_generator_traits::value_to_yaml(msg.material_id, out);
    out << ", ";
  }

  // member: material_name
  {
    out << "material_name: ";
    rosidl_generator_traits::value_to_yaml(msg.material_name, out);
    out << ", ";
  }

  // member: material_density
  {
    out << "material_density: ";
    rosidl_generator_traits::value_to_yaml(msg.material_density, out);
    out << ", ";
  }

  // member: icon_type
  {
    out << "icon_type: ";
    rosidl_generator_traits::value_to_yaml(msg.icon_type, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaJobMgrSubtotalInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: subtotal_command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "subtotal_command: ";
    rosidl_generator_traits::value_to_yaml(msg.subtotal_command, out);
    out << "\n";
  }

  // member: current_step_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_step_number: ";
    rosidl_generator_traits::value_to_yaml(msg.current_step_number, out);
    out << "\n";
  }

  // member: new_step_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "new_step_number: ";
    rosidl_generator_traits::value_to_yaml(msg.new_step_number, out);
    out << "\n";
  }

  // member: target_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.target_weight, out);
    out << "\n";
  }

  // member: target_proportion
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_proportion: ";
    rosidl_generator_traits::value_to_yaml(msg.target_proportion, out);
    out << "\n";
  }

  // member: target_passes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_passes: ";
    rosidl_generator_traits::value_to_yaml(msg.target_passes, out);
    out << "\n";
  }

  // member: material_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "material_id: ";
    rosidl_generator_traits::value_to_yaml(msg.material_id, out);
    out << "\n";
  }

  // member: material_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "material_name: ";
    rosidl_generator_traits::value_to_yaml(msg.material_name, out);
    out << "\n";
  }

  // member: material_density
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "material_density: ";
    rosidl_generator_traits::value_to_yaml(msg.material_density, out);
    out << "\n";
  }

  // member: icon_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "icon_type: ";
    rosidl_generator_traits::value_to_yaml(msg.icon_type, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaJobMgrSubtotalInfo & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo>()
{
  return "cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo";
}

template<>
inline const char * name<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo>()
{
  return "cpm_common_interfaces/msg/LpsSaJobMgrSubtotalInfo";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cpm_common_interfaces::msg::LpsSaJobMgrSubtotalInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__TRAITS_HPP_
