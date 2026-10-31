// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyStatusFlags.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_status_flags.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_status_flags__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaNvmCalOnTheFlyStatusFlags & msg,
  std::ostream & out)
{
  out << "{";
  // member: cal_in_progress
  {
    out << "cal_in_progress: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_in_progress, out);
    out << ", ";
  }

  // member: empty_bkt_cal_done
  {
    out << "empty_bkt_cal_done: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_bkt_cal_done, out);
    out << ", ";
  }

  // member: full_bkt_cal_done
  {
    out << "full_bkt_cal_done: ";
    rosidl_generator_traits::value_to_yaml(msg.full_bkt_cal_done, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaNvmCalOnTheFlyStatusFlags & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: cal_in_progress
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_in_progress: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_in_progress, out);
    out << "\n";
  }

  // member: empty_bkt_cal_done
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "empty_bkt_cal_done: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_bkt_cal_done, out);
    out << "\n";
  }

  // member: full_bkt_cal_done
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "full_bkt_cal_done: ";
    rosidl_generator_traits::value_to_yaml(msg.full_bkt_cal_done, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaNvmCalOnTheFlyStatusFlags & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags>()
{
  return "weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags>()
{
  return "weigh_app_interfaces/msg/LpsSaNvmCalOnTheFlyStatusFlags";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyStatusFlags>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_STATUS_FLAGS__TRAITS_HPP_
