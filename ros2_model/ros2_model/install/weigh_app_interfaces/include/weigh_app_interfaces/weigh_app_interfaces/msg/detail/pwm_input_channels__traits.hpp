// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/PwmInputChannels.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/pwm_input_channels.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/pwm_input_channels__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const PwmInputChannels & msg,
  std::ostream & out)
{
  out << "{";
  // member: period
  {
    if (msg.period.size() == 0) {
      out << "period: []";
    } else {
      out << "period: [";
      size_t pending_items = msg.period.size();
      for (auto item : msg.period) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: width
  {
    if (msg.width.size() == 0) {
      out << "width: []";
    } else {
      out << "width: [";
      size_t pending_items = msg.width.size();
      for (auto item : msg.width) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: switch_status
  {
    if (msg.switch_status.size() == 0) {
      out << "switch_status: []";
    } else {
      out << "switch_status: [";
      size_t pending_items = msg.switch_status.size();
      for (auto item : msg.switch_status) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: timeout
  {
    if (msg.timeout.size() == 0) {
      out << "timeout: []";
    } else {
      out << "timeout: [";
      size_t pending_items = msg.timeout.size();
      for (auto item : msg.timeout) {
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
  const PwmInputChannels & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: period
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.period.size() == 0) {
      out << "period: []\n";
    } else {
      out << "period:\n";
      for (auto item : msg.period) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.width.size() == 0) {
      out << "width: []\n";
    } else {
      out << "width:\n";
      for (auto item : msg.width) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: switch_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.switch_status.size() == 0) {
      out << "switch_status: []\n";
    } else {
      out << "switch_status:\n";
      for (auto item : msg.switch_status) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: timeout
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.timeout.size() == 0) {
      out << "timeout: []\n";
    } else {
      out << "timeout:\n";
      for (auto item : msg.timeout) {
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

inline std::string to_yaml(const PwmInputChannels & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::PwmInputChannels & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::PwmInputChannels & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::PwmInputChannels>()
{
  return "weigh_app_interfaces::msg::PwmInputChannels";
}

template<>
inline const char * name<weigh_app_interfaces::msg::PwmInputChannels>()
{
  return "weigh_app_interfaces/msg/PwmInputChannels";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::PwmInputChannels>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::PwmInputChannels>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<weigh_app_interfaces::msg::PwmInputChannels>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__TRAITS_HPP_
