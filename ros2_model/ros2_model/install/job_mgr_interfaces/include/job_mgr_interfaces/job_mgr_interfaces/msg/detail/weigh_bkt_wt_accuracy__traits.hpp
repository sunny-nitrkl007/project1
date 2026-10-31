// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/WeighBktWtAccuracy.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/weigh_bkt_wt_accuracy.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/weigh_bkt_wt_accuracy__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const WeighBktWtAccuracy & msg,
  std::ostream & out)
{
  out << "{";
  // member: value
  {
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const WeighBktWtAccuracy & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const WeighBktWtAccuracy & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::WeighBktWtAccuracy & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::WeighBktWtAccuracy & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::WeighBktWtAccuracy>()
{
  return "job_mgr_interfaces::msg::WeighBktWtAccuracy";
}

template<>
inline const char * name<job_mgr_interfaces::msg::WeighBktWtAccuracy>()
{
  return "job_mgr_interfaces/msg/WeighBktWtAccuracy";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::WeighBktWtAccuracy>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::WeighBktWtAccuracy>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<job_mgr_interfaces::msg::WeighBktWtAccuracy>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__TRAITS_HPP_
