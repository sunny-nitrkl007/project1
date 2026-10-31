// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/LoadRecordSubtotal.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_subtotal.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/load_record_subtotal__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'start_time'
// Member 'end_time'
#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__traits.hpp"
// Member 'passes'
#include "job_mgr_interfaces/msg/detail/load_record_pass__traits.hpp"
// Member 'accuracy'
#include "job_mgr_interfaces/msg/detail/weigh_bkt_wt_accuracy__traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LoadRecordSubtotal & msg,
  std::ostream & out)
{
  out << "{";
  // member: start_time
  {
    out << "start_time: ";
    to_flow_style_yaml(msg.start_time, out);
    out << ", ";
  }

  // member: end_time
  {
    out << "end_time: ";
    to_flow_style_yaml(msg.end_time, out);
    out << ", ";
  }

  // member: truck_id
  {
    out << "truck_id: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_id, out);
    out << ", ";
  }

  // member: truck_name
  {
    out << "truck_name: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_name, out);
    out << ", ";
  }

  // member: truck_target_weight_tonnes
  {
    out << "truck_target_weight_tonnes: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_target_weight_tonnes, out);
    out << ", ";
  }

  // member: target_proportion
  {
    out << "target_proportion: ";
    rosidl_generator_traits::value_to_yaml(msg.target_proportion, out);
    out << ", ";
  }

  // member: target_passes
  {
    out << "target_passes: ";
    rosidl_generator_traits::value_to_yaml(msg.target_passes, out);
    out << ", ";
  }

  // member: material_id
  {
    out << "material_id: ";
    rosidl_generator_traits::value_to_yaml(msg.material_id, out);
    out << ", ";
  }

  // member: material_name
  {
    out << "material_name: ";
    rosidl_generator_traits::value_to_yaml(msg.material_name, out);
    out << ", ";
  }

  // member: material_density
  {
    out << "material_density: ";
    rosidl_generator_traits::value_to_yaml(msg.material_density, out);
    out << ", ";
  }

  // member: custom_list_name1
  {
    out << "custom_list_name1: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name1, out);
    out << ", ";
  }

  // member: custom_list_name2
  {
    out << "custom_list_name2: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name2, out);
    out << ", ";
  }

  // member: custom_list_name3
  {
    out << "custom_list_name3: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name3, out);
    out << ", ";
  }

  // member: custom_list_name4
  {
    out << "custom_list_name4: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name4, out);
    out << ", ";
  }

  // member: tag1
  {
    out << "tag1: ";
    rosidl_generator_traits::value_to_yaml(msg.tag1, out);
    out << ", ";
  }

  // member: tag2
  {
    out << "tag2: ";
    rosidl_generator_traits::value_to_yaml(msg.tag2, out);
    out << ", ";
  }

  // member: tag3
  {
    out << "tag3: ";
    rosidl_generator_traits::value_to_yaml(msg.tag3, out);
    out << ", ";
  }

  // member: tag4
  {
    out << "tag4: ";
    rosidl_generator_traits::value_to_yaml(msg.tag4, out);
    out << ", ";
  }

  // member: icon_type
  {
    out << "icon_type: ";
    rosidl_generator_traits::value_to_yaml(msg.icon_type, out);
    out << ", ";
  }

  // member: zero_weight
  {
    out << "zero_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_weight, out);
    out << ", ";
  }

  // member: cal_adjust
  {
    out << "cal_adjust: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_adjust, out);
    out << ", ";
  }

  // member: passes
  {
    if (msg.passes.size() == 0) {
      out << "passes: []";
    } else {
      out << "passes: [";
      size_t pending_items = msg.passes.size();
      for (auto item : msg.passes) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: weight_tonnes
  {
    out << "weight_tonnes: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_tonnes, out);
    out << ", ";
  }

  // member: accuracy
  {
    out << "accuracy: ";
    to_flow_style_yaml(msg.accuracy, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LoadRecordSubtotal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: start_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start_time:\n";
    to_block_style_yaml(msg.start_time, out, indentation + 2);
  }

  // member: end_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "end_time:\n";
    to_block_style_yaml(msg.end_time, out, indentation + 2);
  }

  // member: truck_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_id: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_id, out);
    out << "\n";
  }

  // member: truck_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_name: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_name, out);
    out << "\n";
  }

  // member: truck_target_weight_tonnes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_target_weight_tonnes: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_target_weight_tonnes, out);
    out << "\n";
  }

  // member: target_proportion
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_proportion: ";
    rosidl_generator_traits::value_to_yaml(msg.target_proportion, out);
    out << "\n";
  }

  // member: target_passes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_passes: ";
    rosidl_generator_traits::value_to_yaml(msg.target_passes, out);
    out << "\n";
  }

  // member: material_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "material_id: ";
    rosidl_generator_traits::value_to_yaml(msg.material_id, out);
    out << "\n";
  }

  // member: material_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "material_name: ";
    rosidl_generator_traits::value_to_yaml(msg.material_name, out);
    out << "\n";
  }

  // member: material_density
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "material_density: ";
    rosidl_generator_traits::value_to_yaml(msg.material_density, out);
    out << "\n";
  }

  // member: custom_list_name1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "custom_list_name1: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name1, out);
    out << "\n";
  }

  // member: custom_list_name2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "custom_list_name2: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name2, out);
    out << "\n";
  }

  // member: custom_list_name3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "custom_list_name3: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name3, out);
    out << "\n";
  }

  // member: custom_list_name4
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "custom_list_name4: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name4, out);
    out << "\n";
  }

  // member: tag1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag1: ";
    rosidl_generator_traits::value_to_yaml(msg.tag1, out);
    out << "\n";
  }

  // member: tag2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag2: ";
    rosidl_generator_traits::value_to_yaml(msg.tag2, out);
    out << "\n";
  }

  // member: tag3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag3: ";
    rosidl_generator_traits::value_to_yaml(msg.tag3, out);
    out << "\n";
  }

  // member: tag4
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag4: ";
    rosidl_generator_traits::value_to_yaml(msg.tag4, out);
    out << "\n";
  }

  // member: icon_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "icon_type: ";
    rosidl_generator_traits::value_to_yaml(msg.icon_type, out);
    out << "\n";
  }

  // member: zero_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zero_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.zero_weight, out);
    out << "\n";
  }

  // member: cal_adjust
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cal_adjust: ";
    rosidl_generator_traits::value_to_yaml(msg.cal_adjust, out);
    out << "\n";
  }

  // member: passes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.passes.size() == 0) {
      out << "passes: []\n";
    } else {
      out << "passes:\n";
      for (auto item : msg.passes) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: weight_tonnes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "weight_tonnes: ";
    rosidl_generator_traits::value_to_yaml(msg.weight_tonnes, out);
    out << "\n";
  }

  // member: accuracy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accuracy:\n";
    to_block_style_yaml(msg.accuracy, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LoadRecordSubtotal & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::LoadRecordSubtotal & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::LoadRecordSubtotal & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::LoadRecordSubtotal>()
{
  return "job_mgr_interfaces::msg::LoadRecordSubtotal";
}

template<>
inline const char * name<job_mgr_interfaces::msg::LoadRecordSubtotal>()
{
  return "job_mgr_interfaces/msg/LoadRecordSubtotal";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::LoadRecordSubtotal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::LoadRecordSubtotal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<job_mgr_interfaces::msg::LoadRecordSubtotal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__TRAITS_HPP_
