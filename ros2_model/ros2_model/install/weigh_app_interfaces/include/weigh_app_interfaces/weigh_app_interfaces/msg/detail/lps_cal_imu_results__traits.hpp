// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/LpsCalIMUResults.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_cal_imu_results.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/lps_cal_imu_results__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsCalIMUResults & msg,
  std::ostream & out)
{
  out << "{";
  // member: full_slow_imu_offset_temp1
  {
    out << "full_slow_imu_offset_temp1: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_imu_offset_temp1, out);
    out << ", ";
  }

  // member: full_slow_imu_offset_temp2
  {
    out << "full_slow_imu_offset_temp2: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_imu_offset_temp2, out);
    out << ", ";
  }

  // member: full_slow_imu_offset_temp3
  {
    out << "full_slow_imu_offset_temp3: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_imu_offset_temp3, out);
    out << ", ";
  }

  // member: full_slow_lumped_weight_temp1
  {
    out << "full_slow_lumped_weight_temp1: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_lumped_weight_temp1, out);
    out << ", ";
  }

  // member: full_slow_lumped_weight_temp2
  {
    out << "full_slow_lumped_weight_temp2: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_lumped_weight_temp2, out);
    out << ", ";
  }

  // member: full_slow_lumped_weight_temp3
  {
    out << "full_slow_lumped_weight_temp3: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_lumped_weight_temp3, out);
    out << ", ";
  }

  // member: empty_slow_imu_offset_temp1
  {
    out << "empty_slow_imu_offset_temp1: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_imu_offset_temp1, out);
    out << ", ";
  }

  // member: empty_slow_imu_offset_temp2
  {
    out << "empty_slow_imu_offset_temp2: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_imu_offset_temp2, out);
    out << ", ";
  }

  // member: empty_slow_imu_offset_temp3
  {
    out << "empty_slow_imu_offset_temp3: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_imu_offset_temp3, out);
    out << ", ";
  }

  // member: empty_slow_lumped_weight_temp1
  {
    out << "empty_slow_lumped_weight_temp1: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_lumped_weight_temp1, out);
    out << ", ";
  }

  // member: empty_slow_lumped_weight_temp2
  {
    out << "empty_slow_lumped_weight_temp2: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_lumped_weight_temp2, out);
    out << ", ";
  }

  // member: empty_slow_lumped_weight_temp3
  {
    out << "empty_slow_lumped_weight_temp3: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_lumped_weight_temp3, out);
    out << ", ";
  }

  // member: full_slow_imu_offset_final
  {
    out << "full_slow_imu_offset_final: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_imu_offset_final, out);
    out << ", ";
  }

  // member: empty_slow_imu_offset_final
  {
    out << "empty_slow_imu_offset_final: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_imu_offset_final, out);
    out << ", ";
  }

  // member: full_slow_lumped_weight_final
  {
    out << "full_slow_lumped_weight_final: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_lumped_weight_final, out);
    out << ", ";
  }

  // member: empty_slow_lumped_weight_final
  {
    out << "empty_slow_lumped_weight_final: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_lumped_weight_final, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsCalIMUResults & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: full_slow_imu_offset_temp1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "full_slow_imu_offset_temp1: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_imu_offset_temp1, out);
    out << "\n";
  }

  // member: full_slow_imu_offset_temp2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "full_slow_imu_offset_temp2: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_imu_offset_temp2, out);
    out << "\n";
  }

  // member: full_slow_imu_offset_temp3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "full_slow_imu_offset_temp3: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_imu_offset_temp3, out);
    out << "\n";
  }

  // member: full_slow_lumped_weight_temp1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "full_slow_lumped_weight_temp1: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_lumped_weight_temp1, out);
    out << "\n";
  }

  // member: full_slow_lumped_weight_temp2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "full_slow_lumped_weight_temp2: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_lumped_weight_temp2, out);
    out << "\n";
  }

  // member: full_slow_lumped_weight_temp3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "full_slow_lumped_weight_temp3: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_lumped_weight_temp3, out);
    out << "\n";
  }

  // member: empty_slow_imu_offset_temp1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "empty_slow_imu_offset_temp1: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_imu_offset_temp1, out);
    out << "\n";
  }

  // member: empty_slow_imu_offset_temp2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "empty_slow_imu_offset_temp2: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_imu_offset_temp2, out);
    out << "\n";
  }

  // member: empty_slow_imu_offset_temp3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "empty_slow_imu_offset_temp3: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_imu_offset_temp3, out);
    out << "\n";
  }

  // member: empty_slow_lumped_weight_temp1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "empty_slow_lumped_weight_temp1: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_lumped_weight_temp1, out);
    out << "\n";
  }

  // member: empty_slow_lumped_weight_temp2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "empty_slow_lumped_weight_temp2: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_lumped_weight_temp2, out);
    out << "\n";
  }

  // member: empty_slow_lumped_weight_temp3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "empty_slow_lumped_weight_temp3: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_lumped_weight_temp3, out);
    out << "\n";
  }

  // member: full_slow_imu_offset_final
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "full_slow_imu_offset_final: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_imu_offset_final, out);
    out << "\n";
  }

  // member: empty_slow_imu_offset_final
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "empty_slow_imu_offset_final: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_imu_offset_final, out);
    out << "\n";
  }

  // member: full_slow_lumped_weight_final
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "full_slow_lumped_weight_final: ";
    rosidl_generator_traits::value_to_yaml(msg.full_slow_lumped_weight_final, out);
    out << "\n";
  }

  // member: empty_slow_lumped_weight_final
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "empty_slow_lumped_weight_final: ";
    rosidl_generator_traits::value_to_yaml(msg.empty_slow_lumped_weight_final, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsCalIMUResults & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::LpsCalIMUResults & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::LpsCalIMUResults & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::LpsCalIMUResults>()
{
  return "weigh_app_interfaces::msg::LpsCalIMUResults";
}

template<>
inline const char * name<weigh_app_interfaces::msg::LpsCalIMUResults>()
{
  return "weigh_app_interfaces/msg/LpsCalIMUResults";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::LpsCalIMUResults>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::LpsCalIMUResults>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::LpsCalIMUResults>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_CAL_IMU_RESULTS__TRAITS_HPP_
