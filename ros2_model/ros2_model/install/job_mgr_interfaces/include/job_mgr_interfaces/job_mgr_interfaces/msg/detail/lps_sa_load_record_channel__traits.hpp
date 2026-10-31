// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/LpsSaLoadRecordChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_load_record_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/lps_sa_load_record_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'subtotal'
// Member 'subtotals'
#include "job_mgr_interfaces/msg/detail/load_record_subtotal__traits.hpp"
// Member 'store_time'
#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaLoadRecordChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: store_action
  {
    out << "store_action: ";
    rosidl_generator_traits::value_to_yaml(msg.store_action, out);
    out << ", ";
  }

  // member: subtotal
  {
    out << "subtotal: ";
    to_flow_style_yaml(msg.subtotal, out);
    out << ", ";
  }

  // member: subtotals
  {
    if (msg.subtotals.size() == 0) {
      out << "subtotals: []";
    } else {
      out << "subtotals: [";
      size_t pending_items = msg.subtotals.size();
      for (auto item : msg.subtotals) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: ticket_number
  {
    out << "ticket_number: ";
    rosidl_generator_traits::value_to_yaml(msg.ticket_number, out);
    out << ", ";
  }

  // member: ticket_id
  {
    out << "ticket_id: ";
    rosidl_generator_traits::value_to_yaml(msg.ticket_id, out);
    out << ", ";
  }

  // member: product_id
  {
    out << "product_id: ";
    rosidl_generator_traits::value_to_yaml(msg.product_id, out);
    out << ", ";
  }

  // member: equipment_id
  {
    out << "equipment_id: ";
    rosidl_generator_traits::value_to_yaml(msg.equipment_id, out);
    out << ", ";
  }

  // member: weight_interval
  {
    out << "weight_interval: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_interval, out);
    out << ", ";
  }

  // member: weight_decimal_precision
  {
    out << "weight_decimal_precision: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_decimal_precision, out);
    out << ", ";
  }

  // member: weight_units
  {
    out << "weight_units: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_units, out);
    out << ", ";
  }

  // member: recipe_name
  {
    out << "recipe_name: ";
    rosidl_generator_traits::value_to_yaml(msg.recipe_name, out);
    out << ", ";
  }

  // member: target_type
  {
    out << "target_type: ";
    rosidl_generator_traits::value_to_yaml(msg.target_type, out);
    out << ", ";
  }

  // member: total_target_weight
  {
    out << "total_target_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.total_target_weight, out);
    out << ", ";
  }

  // member: current_subtotal_index
  {
    out << "current_subtotal_index: ";
    rosidl_generator_traits::value_to_yaml(msg.current_subtotal_index, out);
    out << ", ";
  }

  // member: store_time
  {
    out << "store_time: ";
    to_flow_style_yaml(msg.store_time, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaLoadRecordChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: store_action
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "store_action: ";
    rosidl_generator_traits::value_to_yaml(msg.store_action, out);
    out << "\n";
  }

  // member: subtotal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "subtotal:\n";
    to_block_style_yaml(msg.subtotal, out, indentation + 2);
  }

  // member: subtotals
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.subtotals.size() == 0) {
      out << "subtotals: []\n";
    } else {
      out << "subtotals:\n";
      for (auto item : msg.subtotals) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
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

  // member: ticket_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ticket_id: ";
    rosidl_generator_traits::value_to_yaml(msg.ticket_id, out);
    out << "\n";
  }

  // member: product_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "product_id: ";
    rosidl_generator_traits::value_to_yaml(msg.product_id, out);
    out << "\n";
  }

  // member: equipment_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "equipment_id: ";
    rosidl_generator_traits::value_to_yaml(msg.equipment_id, out);
    out << "\n";
  }

  // member: weight_interval
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weight_interval: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_interval, out);
    out << "\n";
  }

  // member: weight_decimal_precision
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weight_decimal_precision: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_decimal_precision, out);
    out << "\n";
  }

  // member: weight_units
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weight_units: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_units, out);
    out << "\n";
  }

  // member: recipe_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "recipe_name: ";
    rosidl_generator_traits::value_to_yaml(msg.recipe_name, out);
    out << "\n";
  }

  // member: target_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_type: ";
    rosidl_generator_traits::value_to_yaml(msg.target_type, out);
    out << "\n";
  }

  // member: total_target_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_target_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.total_target_weight, out);
    out << "\n";
  }

  // member: current_subtotal_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_subtotal_index: ";
    rosidl_generator_traits::value_to_yaml(msg.current_subtotal_index, out);
    out << "\n";
  }

  // member: store_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "store_time:\n";
    to_block_style_yaml(msg.store_time, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaLoadRecordChannel & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::LpsSaLoadRecordChannel & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>()
{
  return "job_mgr_interfaces::msg::LpsSaLoadRecordChannel";
}

template<>
inline const char * name<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>()
{
  return "job_mgr_interfaces/msg/LpsSaLoadRecordChannel";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__TRAITS_HPP_
