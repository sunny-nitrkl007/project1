// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrReqstChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_reqst_channel.hpp"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__TRAITS_HPP_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_reqst_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'command'
#include "cpm_common_interfaces/msg/detail/job_mgr_reqst_channel_command__traits.hpp"
// Member 'data_tipoff_trigger_type'
#include "cpm_common_interfaces/msg/detail/tip_off_trigger_type__traits.hpp"
// Member 'data_tipoff_mode'
#include "cpm_common_interfaces/msg/detail/tip_off_state__traits.hpp"
// Member 'data_subtotal_info'
#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_subtotal_info__traits.hpp"
// Member 'requests'
#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_reqst__traits.hpp"

namespace cpm_common_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaJobMgrReqstChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: app_name
  {
    out << "app_name: ";
    rosidl_generator_traits::value_to_yaml(msg.app_name, out);
    out << ", ";
  }

  // member: app_request_id
  {
    out << "app_request_id: ";
    rosidl_generator_traits::value_to_yaml(msg.app_request_id, out);
    out << ", ";
  }

  // member: command
  {
    out << "command: ";
    to_flow_style_yaml(msg.command, out);
    out << ", ";
  }

  // member: data_tipoff_trigger_type
  {
    out << "data_tipoff_trigger_type: ";
    to_flow_style_yaml(msg.data_tipoff_trigger_type, out);
    out << ", ";
  }

  // member: data_tipoff_mode
  {
    out << "data_tipoff_mode: ";
    to_flow_style_yaml(msg.data_tipoff_mode, out);
    out << ", ";
  }

  // member: data_auto_store_pass_count
  {
    out << "data_auto_store_pass_count: ";
    rosidl_generator_traits::value_to_yaml(msg.data_auto_store_pass_count, out);
    out << ", ";
  }

  // member: data_task_number
  {
    out << "data_task_number: ";
    rosidl_generator_traits::value_to_yaml(msg.data_task_number, out);
    out << ", ";
  }

  // member: data_enabled
  {
    out << "data_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.data_enabled, out);
    out << ", ";
  }

  // member: data_target_type
  {
    out << "data_target_type: ";
    rosidl_generator_traits::value_to_yaml(msg.data_target_type, out);
    out << ", ";
  }

  // member: data_subtotal_index
  {
    out << "data_subtotal_index: ";
    rosidl_generator_traits::value_to_yaml(msg.data_subtotal_index, out);
    out << ", ";
  }

  // member: data_total_target_weight
  {
    out << "data_total_target_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.data_total_target_weight, out);
    out << ", ";
  }

  // member: data_subtotal_info
  {
    out << "data_subtotal_info: ";
    to_flow_style_yaml(msg.data_subtotal_info, out);
    out << ", ";
  }

  // member: requests
  {
    if (msg.requests.size() == 0) {
      out << "requests: []";
    } else {
      out << "requests: [";
      size_t pending_items = msg.requests.size();
      for (auto item : msg.requests) {
        to_flow_style_yaml(item, out);
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
  const LpsSaJobMgrReqstChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: app_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "app_name: ";
    rosidl_generator_traits::value_to_yaml(msg.app_name, out);
    out << "\n";
  }

  // member: app_request_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "app_request_id: ";
    rosidl_generator_traits::value_to_yaml(msg.app_request_id, out);
    out << "\n";
  }

  // member: command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command:\n";
    to_block_style_yaml(msg.command, out, indentation + 2);
  }

  // member: data_tipoff_trigger_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_tipoff_trigger_type:\n";
    to_block_style_yaml(msg.data_tipoff_trigger_type, out, indentation + 2);
  }

  // member: data_tipoff_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_tipoff_mode:\n";
    to_block_style_yaml(msg.data_tipoff_mode, out, indentation + 2);
  }

  // member: data_auto_store_pass_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_auto_store_pass_count: ";
    rosidl_generator_traits::value_to_yaml(msg.data_auto_store_pass_count, out);
    out << "\n";
  }

  // member: data_task_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_task_number: ";
    rosidl_generator_traits::value_to_yaml(msg.data_task_number, out);
    out << "\n";
  }

  // member: data_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.data_enabled, out);
    out << "\n";
  }

  // member: data_target_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_target_type: ";
    rosidl_generator_traits::value_to_yaml(msg.data_target_type, out);
    out << "\n";
  }

  // member: data_subtotal_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_subtotal_index: ";
    rosidl_generator_traits::value_to_yaml(msg.data_subtotal_index, out);
    out << "\n";
  }

  // member: data_total_target_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_total_target_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.data_total_target_weight, out);
    out << "\n";
  }

  // member: data_subtotal_info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_subtotal_info:\n";
    to_block_style_yaml(msg.data_subtotal_info, out, indentation + 2);
  }

  // member: requests
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.requests.size() == 0) {
      out << "requests: []\n";
    } else {
      out << "requests:\n";
      for (auto item : msg.requests) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaJobMgrReqstChannel & msg, bool use_flow_style = false)
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
  const cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  cpm_common_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cpm_common_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel & msg)
{
  return cpm_common_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>()
{
  return "cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel";
}

template<>
inline const char * name<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>()
{
  return "cpm_common_interfaces/msg/LpsSaJobMgrReqstChannel";
}

template<>
struct has_fixed_size<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__TRAITS_HPP_
