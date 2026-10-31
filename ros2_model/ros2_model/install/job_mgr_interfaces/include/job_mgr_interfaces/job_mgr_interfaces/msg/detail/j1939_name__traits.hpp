// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/J1939Name.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/j1939_name.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/j1939_name__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const J1939Name & msg,
  std::ostream & out)
{
  out << "{";
  // member: industry_group
  {
    out << "industry_group: ";
    rosidl_generator_traits::value_to_yaml(msg.industry_group, out);
    out << ", ";
  }

  // member: vehicle_system
  {
    out << "vehicle_system: ";
    rosidl_generator_traits::value_to_yaml(msg.vehicle_system, out);
    out << ", ";
  }

  // member: vehicle_system_instance
  {
    out << "vehicle_system_instance: ";
    rosidl_generator_traits::value_to_yaml(msg.vehicle_system_instance, out);
    out << ", ";
  }

  // member: function
  {
    out << "function: ";
    rosidl_generator_traits::value_to_yaml(msg.function, out);
    out << ", ";
  }

  // member: function_instance
  {
    out << "function_instance: ";
    rosidl_generator_traits::value_to_yaml(msg.function_instance, out);
    out << ", ";
  }

  // member: ecu_instance
  {
    out << "ecu_instance: ";
    rosidl_generator_traits::value_to_yaml(msg.ecu_instance, out);
    out << ", ";
  }

  // member: manufacturer_code
  {
    out << "manufacturer_code: ";
    rosidl_generator_traits::value_to_yaml(msg.manufacturer_code, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const J1939Name & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: industry_group
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "industry_group: ";
    rosidl_generator_traits::value_to_yaml(msg.industry_group, out);
    out << "\n";
  }

  // member: vehicle_system
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vehicle_system: ";
    rosidl_generator_traits::value_to_yaml(msg.vehicle_system, out);
    out << "\n";
  }

  // member: vehicle_system_instance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vehicle_system_instance: ";
    rosidl_generator_traits::value_to_yaml(msg.vehicle_system_instance, out);
    out << "\n";
  }

  // member: function
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "function: ";
    rosidl_generator_traits::value_to_yaml(msg.function, out);
    out << "\n";
  }

  // member: function_instance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "function_instance: ";
    rosidl_generator_traits::value_to_yaml(msg.function_instance, out);
    out << "\n";
  }

  // member: ecu_instance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ecu_instance: ";
    rosidl_generator_traits::value_to_yaml(msg.ecu_instance, out);
    out << "\n";
  }

  // member: manufacturer_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "manufacturer_code: ";
    rosidl_generator_traits::value_to_yaml(msg.manufacturer_code, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const J1939Name & msg, bool use_flow_style = false)
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

}  // namespace job_mgr_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use job_mgr_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const job_mgr_interfaces::msg::J1939Name & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::J1939Name & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::J1939Name>()
{
  return "job_mgr_interfaces::msg::J1939Name";
}

template<>
inline const char * name<job_mgr_interfaces::msg::J1939Name>()
{
  return "job_mgr_interfaces/msg/J1939Name";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::J1939Name>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::J1939Name>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<job_mgr_interfaces::msg::J1939Name>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__TRAITS_HPP_
