// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/SimpleCalData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/simple_cal_data.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/simple_cal_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SimpleCalData & msg,
  std::ostream & out)
{
  out << "{";
  // member: time_stamp
  {
    out << "time_stamp: ";
    rosidl_generator_traits::value_to_yaml(msg.time_stamp, out);
    out << ", ";
  }

  // member: truck_wt
  {
    out << "truck_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_wt, out);
    out << ", ";
  }

  // member: zeroed_truck_wt
  {
    out << "zeroed_truck_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.zeroed_truck_wt, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SimpleCalData & msg,
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

  // member: truck_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_wt: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_wt, out);
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SimpleCalData & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::SimpleCalData & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::SimpleCalData & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::SimpleCalData>()
{
  return "job_mgr_interfaces::msg::SimpleCalData";
}

template<>
inline const char * name<job_mgr_interfaces::msg::SimpleCalData>()
{
  return "job_mgr_interfaces/msg/SimpleCalData";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::SimpleCalData>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::SimpleCalData>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<job_mgr_interfaces::msg::SimpleCalData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__TRAITS_HPP_
