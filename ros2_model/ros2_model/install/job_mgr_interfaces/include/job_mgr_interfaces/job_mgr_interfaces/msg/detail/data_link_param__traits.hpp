// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/DataLinkParam.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/data_link_param.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/data_link_param__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const DataLinkParam & msg,
  std::ostream & out)
{
  out << "{";
  // member: param_id
  {
    out << "param_id: ";
    rosidl_generator_traits::value_to_yaml(msg.param_id, out);
    out << ", ";
  }

  // member: identifier_type
  {
    out << "identifier_type: ";
    rosidl_generator_traits::value_to_yaml(msg.identifier_type, out);
    out << ", ";
  }

  // member: pid_data_received
  {
    out << "pid_data_received: ";
    rosidl_generator_traits::value_to_yaml(msg.pid_data_received, out);
    out << ", ";
  }

  // member: last_value_dsi
  {
    out << "last_value_dsi: ";
    rosidl_generator_traits::value_to_yaml(msg.last_value_dsi, out);
    out << ", ";
  }

  // member: last_good_value_u8
  {
    out << "last_good_value_u8: ";
    rosidl_generator_traits::value_to_yaml(msg.last_good_value_u8, out);
    out << ", ";
  }

  // member: last_good_value_u16
  {
    out << "last_good_value_u16: ";
    rosidl_generator_traits::value_to_yaml(msg.last_good_value_u16, out);
    out << ", ";
  }

  // member: last_value_eng
  {
    out << "last_value_eng: ";
    rosidl_generator_traits::value_to_yaml(msg.last_value_eng, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DataLinkParam & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: param_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "param_id: ";
    rosidl_generator_traits::value_to_yaml(msg.param_id, out);
    out << "\n";
  }

  // member: identifier_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "identifier_type: ";
    rosidl_generator_traits::value_to_yaml(msg.identifier_type, out);
    out << "\n";
  }

  // member: pid_data_received
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pid_data_received: ";
    rosidl_generator_traits::value_to_yaml(msg.pid_data_received, out);
    out << "\n";
  }

  // member: last_value_dsi
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_value_dsi: ";
    rosidl_generator_traits::value_to_yaml(msg.last_value_dsi, out);
    out << "\n";
  }

  // member: last_good_value_u8
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_good_value_u8: ";
    rosidl_generator_traits::value_to_yaml(msg.last_good_value_u8, out);
    out << "\n";
  }

  // member: last_good_value_u16
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_good_value_u16: ";
    rosidl_generator_traits::value_to_yaml(msg.last_good_value_u16, out);
    out << "\n";
  }

  // member: last_value_eng
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_value_eng: ";
    rosidl_generator_traits::value_to_yaml(msg.last_value_eng, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DataLinkParam & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::DataLinkParam & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::DataLinkParam & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::DataLinkParam>()
{
  return "job_mgr_interfaces::msg::DataLinkParam";
}

template<>
inline const char * name<job_mgr_interfaces::msg::DataLinkParam>()
{
  return "job_mgr_interfaces/msg/DataLinkParam";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::DataLinkParam>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::DataLinkParam>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<job_mgr_interfaces::msg::DataLinkParam>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__TRAITS_HPP_
