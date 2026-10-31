// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from weigh_app_interfaces:msg/DataLinkParam.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/data_link_param.hpp"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__TRAITS_HPP_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "weigh_app_interfaces/msg/detail/data_link_param__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace weigh_app_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const DataLinkParam & msg,
  std::ostream & out)
{
  out << "{";
  // member: identifier_type
  {
    out << "identifier_type: ";
    rosidl_generator_traits::value_to_yaml(msg.identifier_type, out);
    out << ", ";
  }

  // member: sid
  {
    out << "sid: ";
    rosidl_generator_traits::value_to_yaml(msg.sid, out);
    out << ", ";
  }

  // member: param_id
  {
    out << "param_id: ";
    rosidl_generator_traits::value_to_yaml(msg.param_id, out);
    out << ", ";
  }

  // member: units
  {
    out << "units: ";
    rosidl_generator_traits::value_to_yaml(msg.units, out);
    out << ", ";
  }

  // member: scaling
  {
    out << "scaling: ";
    rosidl_generator_traits::value_to_yaml(msg.scaling, out);
    out << ", ";
  }

  // member: offset
  {
    out << "offset: ";
    rosidl_generator_traits::value_to_yaml(msg.offset, out);
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

  // member: last_value_i16
  {
    out << "last_value_i16: ";
    rosidl_generator_traits::value_to_yaml(msg.last_value_i16, out);
    out << ", ";
  }

  // member: last_value_u16
  {
    out << "last_value_u16: ";
    rosidl_generator_traits::value_to_yaml(msg.last_value_u16, out);
    out << ", ";
  }

  // member: last_value_f32
  {
    out << "last_value_f32: ";
    rosidl_generator_traits::value_to_yaml(msg.last_value_f32, out);
    out << ", ";
  }

  // member: last_value_eng
  {
    out << "last_value_eng: ";
    rosidl_generator_traits::value_to_yaml(msg.last_value_eng, out);
    out << ", ";
  }

  // member: last_good_value_eng
  {
    out << "last_good_value_eng: ";
    rosidl_generator_traits::value_to_yaml(msg.last_good_value_eng, out);
    out << ", ";
  }

  // member: last_value_vector
  {
    if (msg.last_value_vector.size() == 0) {
      out << "last_value_vector: []";
    } else {
      out << "last_value_vector: [";
      size_t pending_items = msg.last_value_vector.size();
      for (auto item : msg.last_value_vector) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: var_param_block
  {
    if (msg.var_param_block.size() == 0) {
      out << "var_param_block: []";
    } else {
      out << "var_param_block: [";
      size_t pending_items = msg.var_param_block.size();
      for (auto item : msg.var_param_block) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: var_length_param_type
  {
    out << "var_length_param_type: ";
    rosidl_generator_traits::value_to_yaml(msg.var_length_param_type, out);
    out << ", ";
  }

  // member: var_length_param_dsi
  {
    out << "var_length_param_dsi: ";
    rosidl_generator_traits::value_to_yaml(msg.var_length_param_dsi, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DataLinkParam & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: identifier_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "identifier_type: ";
    rosidl_generator_traits::value_to_yaml(msg.identifier_type, out);
    out << "\n";
  }

  // member: sid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sid: ";
    rosidl_generator_traits::value_to_yaml(msg.sid, out);
    out << "\n";
  }

  // member: param_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "param_id: ";
    rosidl_generator_traits::value_to_yaml(msg.param_id, out);
    out << "\n";
  }

  // member: units
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "units: ";
    rosidl_generator_traits::value_to_yaml(msg.units, out);
    out << "\n";
  }

  // member: scaling
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "scaling: ";
    rosidl_generator_traits::value_to_yaml(msg.scaling, out);
    out << "\n";
  }

  // member: offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "offset: ";
    rosidl_generator_traits::value_to_yaml(msg.offset, out);
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

  // member: last_value_i16
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_value_i16: ";
    rosidl_generator_traits::value_to_yaml(msg.last_value_i16, out);
    out << "\n";
  }

  // member: last_value_u16
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_value_u16: ";
    rosidl_generator_traits::value_to_yaml(msg.last_value_u16, out);
    out << "\n";
  }

  // member: last_value_f32
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_value_f32: ";
    rosidl_generator_traits::value_to_yaml(msg.last_value_f32, out);
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

  // member: last_good_value_eng
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_good_value_eng: ";
    rosidl_generator_traits::value_to_yaml(msg.last_good_value_eng, out);
    out << "\n";
  }

  // member: last_value_vector
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.last_value_vector.size() == 0) {
      out << "last_value_vector: []\n";
    } else {
      out << "last_value_vector:\n";
      for (auto item : msg.last_value_vector) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: var_param_block
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.var_param_block.size() == 0) {
      out << "var_param_block: []\n";
    } else {
      out << "var_param_block:\n";
      for (auto item : msg.var_param_block) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: var_length_param_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "var_length_param_type: ";
    rosidl_generator_traits::value_to_yaml(msg.var_length_param_type, out);
    out << "\n";
  }

  // member: var_length_param_dsi
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "var_length_param_dsi: ";
    rosidl_generator_traits::value_to_yaml(msg.var_length_param_dsi, out);
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

}  // namespace weigh_app_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use weigh_app_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const weigh_app_interfaces::msg::DataLinkParam & msg,
  std::ostream & out, size_t indentation = 0)
{
  weigh_app_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use weigh_app_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const weigh_app_interfaces::msg::DataLinkParam & msg)
{
  return weigh_app_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<weigh_app_interfaces::msg::DataLinkParam>()
{
  return "weigh_app_interfaces::msg::DataLinkParam";
}

template<>
inline const char * name<weigh_app_interfaces::msg::DataLinkParam>()
{
  return "weigh_app_interfaces/msg/DataLinkParam";
}

template<>
struct has_fixed_size<weigh_app_interfaces::msg::DataLinkParam>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<weigh_app_interfaces::msg::DataLinkParam>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<weigh_app_interfaces::msg::DataLinkParam>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__TRAITS_HPP_
