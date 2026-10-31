// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/DemoAppTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/demo_app_tx_channel.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/demo_app_tx_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const DemoAppTxChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: liftposition
  {
    out << "liftposition: ";
    rosidl_generator_traits::value_to_yaml(msg.liftposition, out);
    out << ", ";
  }

  // member: liftposition_rate
  {
    out << "liftposition_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.liftposition_rate, out);
    out << ", ";
  }

  // member: tiltposition
  {
    out << "tiltposition: ";
    rosidl_generator_traits::value_to_yaml(msg.tiltposition, out);
    out << ", ";
  }

  // member: tiltposition_rate
  {
    out << "tiltposition_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.tiltposition_rate, out);
    out << ", ";
  }

  // member: payload
  {
    out << "payload: ";
    rosidl_generator_traits::value_to_yaml(msg.payload, out);
    out << ", ";
  }

  // member: payload_rate
  {
    out << "payload_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_rate, out);
    out << ", ";
  }

  // member: dig
  {
    out << "dig: ";
    rosidl_generator_traits::value_to_yaml(msg.dig, out);
    out << ", ";
  }

  // member: wrw
  {
    out << "wrw: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw, out);
    out << ", ";
  }

  // member: llw
  {
    out << "llw: ";
    rosidl_generator_traits::value_to_yaml(msg.llw, out);
    out << ", ";
  }

  // member: dump
  {
    out << "dump: ";
    rosidl_generator_traits::value_to_yaml(msg.dump, out);
    out << ", ";
  }

  // member: pdump
  {
    out << "pdump: ";
    rosidl_generator_traits::value_to_yaml(msg.pdump, out);
    out << ", ";
  }

  // member: rack
  {
    out << "rack: ";
    rosidl_generator_traits::value_to_yaml(msg.rack, out);
    out << ", ";
  }

  // member: carry
  {
    out << "carry: ";
    rosidl_generator_traits::value_to_yaml(msg.carry, out);
    out << ", ";
  }

  // member: weight1
  {
    out << "weight1: ";
    rosidl_generator_traits::value_to_yaml(msg.weight1, out);
    out << ", ";
  }

  // member: pres_lift_he_demo
  {
    out << "pres_lift_he_demo: ";
    rosidl_generator_traits::value_to_yaml(msg.pres_lift_he_demo, out);
    out << ", ";
  }

  // member: pres_lift_re_demo
  {
    out << "pres_lift_re_demo: ";
    rosidl_generator_traits::value_to_yaml(msg.pres_lift_re_demo, out);
    out << ", ";
  }

  // member: angle_lift_demo
  {
    out << "angle_lift_demo: ";
    rosidl_generator_traits::value_to_yaml(msg.angle_lift_demo, out);
    out << ", ";
  }

  // member: angle_afe_demo
  {
    out << "angle_afe_demo: ";
    rosidl_generator_traits::value_to_yaml(msg.angle_afe_demo, out);
    out << ", ";
  }

  // member: angle_abc_demo
  {
    out << "angle_abc_demo: ";
    rosidl_generator_traits::value_to_yaml(msg.angle_abc_demo, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DemoAppTxChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: liftposition
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "liftposition: ";
    rosidl_generator_traits::value_to_yaml(msg.liftposition, out);
    out << "\n";
  }

  // member: liftposition_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "liftposition_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.liftposition_rate, out);
    out << "\n";
  }

  // member: tiltposition
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tiltposition: ";
    rosidl_generator_traits::value_to_yaml(msg.tiltposition, out);
    out << "\n";
  }

  // member: tiltposition_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tiltposition_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.tiltposition_rate, out);
    out << "\n";
  }

  // member: payload
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload: ";
    rosidl_generator_traits::value_to_yaml(msg.payload, out);
    out << "\n";
  }

  // member: payload_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "payload_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.payload_rate, out);
    out << "\n";
  }

  // member: dig
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dig: ";
    rosidl_generator_traits::value_to_yaml(msg.dig, out);
    out << "\n";
  }

  // member: wrw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wrw: ";
    rosidl_generator_traits::value_to_yaml(msg.wrw, out);
    out << "\n";
  }

  // member: llw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "llw: ";
    rosidl_generator_traits::value_to_yaml(msg.llw, out);
    out << "\n";
  }

  // member: dump
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dump: ";
    rosidl_generator_traits::value_to_yaml(msg.dump, out);
    out << "\n";
  }

  // member: pdump
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pdump: ";
    rosidl_generator_traits::value_to_yaml(msg.pdump, out);
    out << "\n";
  }

  // member: rack
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rack: ";
    rosidl_generator_traits::value_to_yaml(msg.rack, out);
    out << "\n";
  }

  // member: carry
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "carry: ";
    rosidl_generator_traits::value_to_yaml(msg.carry, out);
    out << "\n";
  }

  // member: weight1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weight1: ";
    rosidl_generator_traits::value_to_yaml(msg.weight1, out);
    out << "\n";
  }

  // member: pres_lift_he_demo
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pres_lift_he_demo: ";
    rosidl_generator_traits::value_to_yaml(msg.pres_lift_he_demo, out);
    out << "\n";
  }

  // member: pres_lift_re_demo
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pres_lift_re_demo: ";
    rosidl_generator_traits::value_to_yaml(msg.pres_lift_re_demo, out);
    out << "\n";
  }

  // member: angle_lift_demo
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angle_lift_demo: ";
    rosidl_generator_traits::value_to_yaml(msg.angle_lift_demo, out);
    out << "\n";
  }

  // member: angle_afe_demo
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angle_afe_demo: ";
    rosidl_generator_traits::value_to_yaml(msg.angle_afe_demo, out);
    out << "\n";
  }

  // member: angle_abc_demo
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angle_abc_demo: ";
    rosidl_generator_traits::value_to_yaml(msg.angle_abc_demo, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DemoAppTxChannel & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::DemoAppTxChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::DemoAppTxChannel & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::DemoAppTxChannel>()
{
  return "weigh_app_interfaces::msg::DemoAppTxChannel";
}

template<>
inline const char * name<weigh_app_interfaces::msg::DemoAppTxChannel>()
{
  return "weigh_app_interfaces/msg/DemoAppTxChannel";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::DemoAppTxChannel>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::DemoAppTxChannel>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<weigh_app_interfaces::msg::DemoAppTxChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__TRAITS_HPP_
