// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/CalibrationRequest.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/calibration_request.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/calibration_request__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const CalibrationRequest & msg,
  std::ostream & out)
{
  out << "{";
  // member: src
  {
    out << "src: ";
    rosidl_generator_traits::value_to_yaml(msg.src, out);
    out << ", ";
  }

  // member: dest
  {
    out << "dest: ";
    rosidl_generator_traits::value_to_yaml(msg.dest, out);
    out << ", ";
  }

  // member: calibration_reqst_flag
  {
    out << "calibration_reqst_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.calibration_reqst_flag, out);
    out << ", ";
  }

  // member: calcmd
  {
    out << "calcmd: ";
    rosidl_generator_traits::value_to_yaml(msg.calcmd, out);
    out << ", ";
  }

  // member: cal_id
  {
    out << "cal_id: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_id, out);
    out << ", ";
  }

  // member: cal_iterm
  {
    if (msg.cal_iterm.size() == 0) {
      out << "cal_iterm: []";
    } else {
      out << "cal_iterm: [";
      size_t pending_items = msg.cal_iterm.size();
      for (auto item : msg.cal_iterm) {
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
  const CalibrationRequest & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: src
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "src: ";
    rosidl_generator_traits::value_to_yaml(msg.src, out);
    out << "\n";
  }

  // member: dest
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dest: ";
    rosidl_generator_traits::value_to_yaml(msg.dest, out);
    out << "\n";
  }

  // member: calibration_reqst_flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calibration_reqst_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.calibration_reqst_flag, out);
    out << "\n";
  }

  // member: calcmd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calcmd: ";
    rosidl_generator_traits::value_to_yaml(msg.calcmd, out);
    out << "\n";
  }

  // member: cal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_id: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_id, out);
    out << "\n";
  }

  // member: cal_iterm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.cal_iterm.size() == 0) {
      out << "cal_iterm: []\n";
    } else {
      out << "cal_iterm:\n";
      for (auto item : msg.cal_iterm) {
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

inline std::string to_yaml(const CalibrationRequest & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::CalibrationRequest & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::CalibrationRequest & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::CalibrationRequest>()
{
  return "weigh_app_interfaces::msg::CalibrationRequest";
}

template<>
inline const char * name<weigh_app_interfaces::msg::CalibrationRequest>()
{
  return "weigh_app_interfaces/msg/CalibrationRequest";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::CalibrationRequest>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::CalibrationRequest>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<weigh_app_interfaces::msg::CalibrationRequest>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__TRAITS_HPP_
