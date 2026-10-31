// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/ShmClockInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/shm_clock_input.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/shm_clock_input__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ShmClockInput & msg,
  std::ostream & out)
{
  out << "{";
  // member: shm_sec
  {
    out << "shm_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.shm_sec, out);
    out << ", ";
  }

  // member: utc_sec_us
  {
    out << "utc_sec_us: ";
    rosidl_generator_traits::value_to_yaml(msg.utc_sec_us, out);
    out << ", ";
  }

  // member: utc_offset_min
  {
    out << "utc_offset_min: ";
    rosidl_generator_traits::value_to_yaml(msg.utc_offset_min, out);
    out << ", ";
  }

  // member: tzone_info
  {
    if (msg.tzone_info.size() == 0) {
      out << "tzone_info: []";
    } else {
      out << "tzone_info: [";
      size_t pending_items = msg.tzone_info.size();
      for (auto item : msg.tzone_info) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ShmClockInput & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: shm_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "shm_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.shm_sec, out);
    out << "\n";
  }

  // member: utc_sec_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "utc_sec_us: ";
    rosidl_generator_traits::value_to_yaml(msg.utc_sec_us, out);
    out << "\n";
  }

  // member: utc_offset_min
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "utc_offset_min: ";
    rosidl_generator_traits::value_to_yaml(msg.utc_offset_min, out);
    out << "\n";
  }

  // member: tzone_info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.tzone_info.size() == 0) {
      out << "tzone_info: []\n";
    } else {
      out << "tzone_info:\n";
      for (auto item : msg.tzone_info) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ShmClockInput & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::ShmClockInput & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::ShmClockInput & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::ShmClockInput>()
{
  return "cpm_common_interfaces::msg::ShmClockInput";
}

template<>
inline const char * name<cpm_common_interfaces::msg::ShmClockInput>()
{
  return "cpm_common_interfaces/msg/ShmClockInput";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::ShmClockInput>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::ShmClockInput>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cpm_common_interfaces::msg::ShmClockInput>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SHM_CLOCK_INPUT__TRAITS_HPP_
