// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/TruckTicket.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/truck_ticket.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/truck_ticket__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TruckTicket & msg,
  std::ostream & out)
{
  out << "{";
  // member: num_copies
  {
    out << "num_copies: ";
    rosidl_generator_traits::value_to_yaml(msg.num_copies, out);
    out << ", ";
  }

  // member: header_enabled
  {
    out << "header_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.header_enabled, out);
    out << ", ";
  }

  // member: header_line1
  {
    out << "header_line1: ";
    rosidl_generator_traits::value_to_yaml(msg.header_line1, out);
    out << ", ";
  }

  // member: header_line2
  {
    out << "header_line2: ";
    rosidl_generator_traits::value_to_yaml(msg.header_line2, out);
    out << ", ";
  }

  // member: header_line3
  {
    out << "header_line3: ";
    rosidl_generator_traits::value_to_yaml(msg.header_line3, out);
    out << ", ";
  }

  // member: footer_line1
  {
    out << "footer_line1: ";
    rosidl_generator_traits::value_to_yaml(msg.footer_line1, out);
    out << ", ";
  }

  // member: bucket_weights_enabled
  {
    out << "bucket_weights_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_weights_enabled, out);
    out << ", ";
  }

  // member: truck_weight_enabled
  {
    out << "truck_weight_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_weight_enabled, out);
    out << ", ";
  }

  // member: truck_id_enabled
  {
    out << "truck_id_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_id_enabled, out);
    out << ", ";
  }

  // member: material_id_enabled
  {
    out << "material_id_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.material_id_enabled, out);
    out << ", ";
  }

  // member: store_time_enabled
  {
    out << "store_time_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.store_time_enabled, out);
    out << ", ";
  }

  // member: ticket_number
  {
    out << "ticket_number: ";
    rosidl_generator_traits::value_to_yaml(msg.ticket_number, out);
    out << ", ";
  }

  // member: retention_period
  {
    out << "retention_period: ";
    rosidl_generator_traits::value_to_yaml(msg.retention_period, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TruckTicket & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: num_copies
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_copies: ";
    rosidl_generator_traits::value_to_yaml(msg.num_copies, out);
    out << "\n";
  }

  // member: header_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.header_enabled, out);
    out << "\n";
  }

  // member: header_line1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header_line1: ";
    rosidl_generator_traits::value_to_yaml(msg.header_line1, out);
    out << "\n";
  }

  // member: header_line2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header_line2: ";
    rosidl_generator_traits::value_to_yaml(msg.header_line2, out);
    out << "\n";
  }

  // member: header_line3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header_line3: ";
    rosidl_generator_traits::value_to_yaml(msg.header_line3, out);
    out << "\n";
  }

  // member: footer_line1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "footer_line1: ";
    rosidl_generator_traits::value_to_yaml(msg.footer_line1, out);
    out << "\n";
  }

  // member: bucket_weights_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bucket_weights_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.bucket_weights_enabled, out);
    out << "\n";
  }

  // member: truck_weight_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_weight_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_weight_enabled, out);
    out << "\n";
  }

  // member: truck_id_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_id_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_id_enabled, out);
    out << "\n";
  }

  // member: material_id_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "material_id_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.material_id_enabled, out);
    out << "\n";
  }

  // member: store_time_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "store_time_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.store_time_enabled, out);
    out << "\n";
  }

  // member: ticket_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ticket_number: ";
    rosidl_generator_traits::value_to_yaml(msg.ticket_number, out);
    out << "\n";
  }

  // member: retention_period
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "retention_period: ";
    rosidl_generator_traits::value_to_yaml(msg.retention_period, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TruckTicket & msg, bool use_flow_style = false)
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
  const weigh_app_interfaces::msg::TruckTicket & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::TruckTicket & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::TruckTicket>()
{
  return "weigh_app_interfaces::msg::TruckTicket";
}

template<>
inline const char * name<weigh_app_interfaces::msg::TruckTicket>()
{
  return "weigh_app_interfaces/msg/TruckTicket";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::TruckTicket>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::TruckTicket>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<weigh_app_interfaces::msg::TruckTicket>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__TRAITS_HPP_
