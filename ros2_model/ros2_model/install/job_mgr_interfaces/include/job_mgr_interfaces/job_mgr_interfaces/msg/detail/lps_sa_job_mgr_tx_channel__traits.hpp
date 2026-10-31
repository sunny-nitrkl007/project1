// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from job_mgr_interfaces:msg/LpsSaJobMgrTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_job_mgr_tx_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__TRAITS_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "job_mgr_interfaces/msg/detail/lps_sa_job_mgr_tx_channel__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'truck_weight_accuracy'
// Member 'total_weight_accuracy'
#include "job_mgr_interfaces/msg/detail/weigh_bkt_wt_accuracy__traits.hpp"
// Member 'tip_off_trigger_type'
#include "cpm_common_interfaces/msg/detail/tip_off_trigger_type__traits.hpp"
// Member 'tip_off_state'
// Member 'tip_off_state_cfg'
#include "cpm_common_interfaces/msg/detail/tip_off_state__traits.hpp"
// Member 'standby_state'
#include "cpm_common_interfaces/msg/detail/standby_state__traits.hpp"
// Member 'disp_best_bkt_wt'
#include "job_mgr_interfaces/msg/detail/disp_best_bkt_wt__traits.hpp"
// Member 'simple_cal_data'
#include "job_mgr_interfaces/msg/detail/simple_cal_data__traits.hpp"

namespace job_mgr_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LpsSaJobMgrTxChannel & msg,
  std::ostream & out)
{
  out << "{";
  // member: time_point_ns
  {
    out << "time_point_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.time_point_ns, out);
    out << ", ";
  }

  // member: task_number
  {
    out << "task_number: ";
    rosidl_generator_traits::value_to_yaml(msg.task_number, out);
    out << ", ";
  }

  // member: pass_count
  {
    out << "pass_count: ";
    rosidl_generator_traits::value_to_yaml(msg.pass_count, out);
    out << ", ";
  }

  // member: truck_weight
  {
    out << "truck_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_weight, out);
    out << ", ";
  }

  // member: truck_weight_accuracy
  {
    out << "truck_weight_accuracy: ";
    to_flow_style_yaml(msg.truck_weight_accuracy, out);
    out << ", ";
  }

  // member: truck_start_weight
  {
    out << "truck_start_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_start_weight, out);
    out << ", ";
  }

  // member: remaining_weight
  {
    out << "remaining_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.remaining_weight, out);
    out << ", ";
  }

  // member: total_weight
  {
    out << "total_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.total_weight, out);
    out << ", ";
  }

  // member: total_weight_accuracy
  {
    out << "total_weight_accuracy: ";
    to_flow_style_yaml(msg.total_weight_accuracy, out);
    out << ", ";
  }

  // member: subtotal_count
  {
    out << "subtotal_count: ";
    rosidl_generator_traits::value_to_yaml(msg.subtotal_count, out);
    out << ", ";
  }

  // member: ticket_id
  {
    out << "ticket_id: ";
    rosidl_generator_traits::value_to_yaml(msg.ticket_id, out);
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

  // member: truck_target_weight
  {
    out << "truck_target_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_target_weight, out);
    out << ", ";
  }

  // member: truck_list_enabled
  {
    out << "truck_list_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_list_enabled, out);
    out << ", ";
  }

  // member: material_list_enabled
  {
    out << "material_list_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.material_list_enabled, out);
    out << ", ";
  }

  // member: tag1_enabled
  {
    out << "tag1_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.tag1_enabled, out);
    out << ", ";
  }

  // member: custom_list_name1
  {
    out << "custom_list_name1: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name1, out);
    out << ", ";
  }

  // member: tag1
  {
    out << "tag1: ";
    rosidl_generator_traits::value_to_yaml(msg.tag1, out);
    out << ", ";
  }

  // member: tag2_enabled
  {
    out << "tag2_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.tag2_enabled, out);
    out << ", ";
  }

  // member: custom_list_name2
  {
    out << "custom_list_name2: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name2, out);
    out << ", ";
  }

  // member: tag2
  {
    out << "tag2: ";
    rosidl_generator_traits::value_to_yaml(msg.tag2, out);
    out << ", ";
  }

  // member: tag3_enabled
  {
    out << "tag3_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.tag3_enabled, out);
    out << ", ";
  }

  // member: custom_list_name3
  {
    out << "custom_list_name3: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name3, out);
    out << ", ";
  }

  // member: tag3
  {
    out << "tag3: ";
    rosidl_generator_traits::value_to_yaml(msg.tag3, out);
    out << ", ";
  }

  // member: tag4_enabled
  {
    out << "tag4_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.tag4_enabled, out);
    out << ", ";
  }

  // member: custom_list_name4
  {
    out << "custom_list_name4: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_list_name4, out);
    out << ", ";
  }

  // member: tag4
  {
    out << "tag4: ";
    rosidl_generator_traits::value_to_yaml(msg.tag4, out);
    out << ", ";
  }

  // member: manual_tip_off_state
  {
    out << "manual_tip_off_state: ";
    rosidl_generator_traits::value_to_yaml(msg.manual_tip_off_state, out);
    out << ", ";
  }

  // member: tip_off_trigger_type
  {
    out << "tip_off_trigger_type: ";
    to_flow_style_yaml(msg.tip_off_trigger_type, out);
    out << ", ";
  }

  // member: tip_off_state
  {
    out << "tip_off_state: ";
    to_flow_style_yaml(msg.tip_off_state, out);
    out << ", ";
  }

  // member: tip_off_state_cfg
  {
    out << "tip_off_state_cfg: ";
    to_flow_style_yaml(msg.tip_off_state_cfg, out);
    out << ", ";
  }

  // member: operation_mode
  {
    out << "operation_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.operation_mode, out);
    out << ", ";
  }

  // member: standby_state
  {
    out << "standby_state: ";
    to_flow_style_yaml(msg.standby_state, out);
    out << ", ";
  }

  // member: clear_minus_one_enable_stat
  {
    out << "clear_minus_one_enable_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.clear_minus_one_enable_stat, out);
    out << ", ";
  }

  // member: disp_best_bkt_wt
  {
    out << "disp_best_bkt_wt: ";
    to_flow_style_yaml(msg.disp_best_bkt_wt, out);
    out << ", ";
  }

  // member: simple_cal_data
  {
    if (msg.simple_cal_data.size() == 0) {
      out << "simple_cal_data: []";
    } else {
      out << "simple_cal_data: [";
      size_t pending_items = msg.simple_cal_data.size();
      for (auto item : msg.simple_cal_data) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: store_count
  {
    out << "store_count: ";
    rosidl_generator_traits::value_to_yaml(msg.store_count, out);
    out << ", ";
  }

  // member: store_rejected
  {
    out << "store_rejected: ";
    rosidl_generator_traits::value_to_yaml(msg.store_rejected, out);
    out << ", ";
  }

  // member: req_pload_ctrl_sys_stat
  {
    out << "req_pload_ctrl_sys_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.req_pload_ctrl_sys_stat, out);
    out << ", ";
  }

  // member: horn_store_state
  {
    out << "horn_store_state: ";
    rosidl_generator_traits::value_to_yaml(msg.horn_store_state, out);
    out << ", ";
  }

  // member: auto_store_pass_count
  {
    out << "auto_store_pass_count: ";
    rosidl_generator_traits::value_to_yaml(msg.auto_store_pass_count, out);
    out << ", ";
  }

  // member: auto_truck_id_enabled
  {
    out << "auto_truck_id_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.auto_truck_id_enabled, out);
    out << ", ";
  }

  // member: auto_material_id_enabled
  {
    out << "auto_material_id_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.auto_material_id_enabled, out);
    out << ", ";
  }

  // member: manual_add_enabled
  {
    out << "manual_add_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.manual_add_enabled, out);
    out << ", ";
  }

  // member: multi_task_enabled
  {
    out << "multi_task_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.multi_task_enabled, out);
    out << ", ";
  }

  // member: multi_task_count
  {
    out << "multi_task_count: ";
    rosidl_generator_traits::value_to_yaml(msg.multi_task_count, out);
    out << ", ";
  }

  // member: tipoff_active
  {
    out << "tipoff_active: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_active, out);
    out << ", ";
  }

  // member: tipoff_assist_active
  {
    out << "tipoff_assist_active: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_assist_active, out);
    out << ", ";
  }

  // member: tipoff_assist_active_eid
  {
    out << "tipoff_assist_active_eid: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_assist_active_eid, out);
    out << ", ";
  }

  // member: manual_add_available
  {
    out << "manual_add_available: ";
    rosidl_generator_traits::value_to_yaml(msg.manual_add_available, out);
    out << ", ";
  }

  // member: split_mode_enabled
  {
    out << "split_mode_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.split_mode_enabled, out);
    out << ", ";
  }

  // member: lft_disabled
  {
    out << "lft_disabled: ";
    rosidl_generator_traits::value_to_yaml(msg.lft_disabled, out);
    out << ", ";
  }

  // member: target_type
  {
    out << "target_type: ";
    rosidl_generator_traits::value_to_yaml(msg.target_type, out);
    out << ", ";
  }

  // member: step_number
  {
    out << "step_number: ";
    rosidl_generator_traits::value_to_yaml(msg.step_number, out);
    out << ", ";
  }

  // member: icon_type
  {
    out << "icon_type: ";
    rosidl_generator_traits::value_to_yaml(msg.icon_type, out);
    out << ", ";
  }

  // member: target_passes
  {
    out << "target_passes: ";
    rosidl_generator_traits::value_to_yaml(msg.target_passes, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LpsSaJobMgrTxChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: time_point_ns
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_point_ns: ";
    rosidl_generator_traits::value_to_yaml(msg.time_point_ns, out);
    out << "\n";
  }

  // member: task_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_number: ";
    rosidl_generator_traits::value_to_yaml(msg.task_number, out);
    out << "\n";
  }

  // member: pass_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pass_count: ";
    rosidl_generator_traits::value_to_yaml(msg.pass_count, out);
    out << "\n";
  }

  // member: truck_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_weight, out);
    out << "\n";
  }

  // member: truck_weight_accuracy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_weight_accuracy:\n";
    to_block_style_yaml(msg.truck_weight_accuracy, out, indentation + 2);
  }

  // member: truck_start_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_start_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_start_weight, out);
    out << "\n";
  }

  // member: remaining_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "remaining_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.remaining_weight, out);
    out << "\n";
  }

  // member: total_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.total_weight, out);
    out << "\n";
  }

  // member: total_weight_accuracy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_weight_accuracy:\n";
    to_block_style_yaml(msg.total_weight_accuracy, out, indentation + 2);
  }

  // member: subtotal_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "subtotal_count: ";
    rosidl_generator_traits::value_to_yaml(msg.subtotal_count, out);
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

  // member: truck_target_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_target_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_target_weight, out);
    out << "\n";
  }

  // member: truck_list_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "truck_list_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.truck_list_enabled, out);
    out << "\n";
  }

  // member: material_list_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "material_list_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.material_list_enabled, out);
    out << "\n";
  }

  // member: tag1_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag1_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.tag1_enabled, out);
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

  // member: tag1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag1: ";
    rosidl_generator_traits::value_to_yaml(msg.tag1, out);
    out << "\n";
  }

  // member: tag2_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag2_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.tag2_enabled, out);
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

  // member: tag2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag2: ";
    rosidl_generator_traits::value_to_yaml(msg.tag2, out);
    out << "\n";
  }

  // member: tag3_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag3_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.tag3_enabled, out);
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

  // member: tag3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag3: ";
    rosidl_generator_traits::value_to_yaml(msg.tag3, out);
    out << "\n";
  }

  // member: tag4_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag4_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.tag4_enabled, out);
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

  // member: tag4
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag4: ";
    rosidl_generator_traits::value_to_yaml(msg.tag4, out);
    out << "\n";
  }

  // member: manual_tip_off_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "manual_tip_off_state: ";
    rosidl_generator_traits::value_to_yaml(msg.manual_tip_off_state, out);
    out << "\n";
  }

  // member: tip_off_trigger_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tip_off_trigger_type:\n";
    to_block_style_yaml(msg.tip_off_trigger_type, out, indentation + 2);
  }

  // member: tip_off_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tip_off_state:\n";
    to_block_style_yaml(msg.tip_off_state, out, indentation + 2);
  }

  // member: tip_off_state_cfg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tip_off_state_cfg:\n";
    to_block_style_yaml(msg.tip_off_state_cfg, out, indentation + 2);
  }

  // member: operation_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "operation_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.operation_mode, out);
    out << "\n";
  }

  // member: standby_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "standby_state:\n";
    to_block_style_yaml(msg.standby_state, out, indentation + 2);
  }

  // member: clear_minus_one_enable_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "clear_minus_one_enable_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.clear_minus_one_enable_stat, out);
    out << "\n";
  }

  // member: disp_best_bkt_wt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "disp_best_bkt_wt:\n";
    to_block_style_yaml(msg.disp_best_bkt_wt, out, indentation + 2);
  }

  // member: simple_cal_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.simple_cal_data.size() == 0) {
      out << "simple_cal_data: []\n";
    } else {
      out << "simple_cal_data:\n";
      for (auto item : msg.simple_cal_data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: store_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "store_count: ";
    rosidl_generator_traits::value_to_yaml(msg.store_count, out);
    out << "\n";
  }

  // member: store_rejected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "store_rejected: ";
    rosidl_generator_traits::value_to_yaml(msg.store_rejected, out);
    out << "\n";
  }

  // member: req_pload_ctrl_sys_stat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "req_pload_ctrl_sys_stat: ";
    rosidl_generator_traits::value_to_yaml(msg.req_pload_ctrl_sys_stat, out);
    out << "\n";
  }

  // member: horn_store_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "horn_store_state: ";
    rosidl_generator_traits::value_to_yaml(msg.horn_store_state, out);
    out << "\n";
  }

  // member: auto_store_pass_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "auto_store_pass_count: ";
    rosidl_generator_traits::value_to_yaml(msg.auto_store_pass_count, out);
    out << "\n";
  }

  // member: auto_truck_id_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "auto_truck_id_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.auto_truck_id_enabled, out);
    out << "\n";
  }

  // member: auto_material_id_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "auto_material_id_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.auto_material_id_enabled, out);
    out << "\n";
  }

  // member: manual_add_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "manual_add_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.manual_add_enabled, out);
    out << "\n";
  }

  // member: multi_task_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "multi_task_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.multi_task_enabled, out);
    out << "\n";
  }

  // member: multi_task_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "multi_task_count: ";
    rosidl_generator_traits::value_to_yaml(msg.multi_task_count, out);
    out << "\n";
  }

  // member: tipoff_active
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tipoff_active: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_active, out);
    out << "\n";
  }

  // member: tipoff_assist_active
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tipoff_assist_active: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_assist_active, out);
    out << "\n";
  }

  // member: tipoff_assist_active_eid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tipoff_assist_active_eid: ";
    rosidl_generator_traits::value_to_yaml(msg.tipoff_assist_active_eid, out);
    out << "\n";
  }

  // member: manual_add_available
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "manual_add_available: ";
    rosidl_generator_traits::value_to_yaml(msg.manual_add_available, out);
    out << "\n";
  }

  // member: split_mode_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "split_mode_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.split_mode_enabled, out);
    out << "\n";
  }

  // member: lft_disabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lft_disabled: ";
    rosidl_generator_traits::value_to_yaml(msg.lft_disabled, out);
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

  // member: step_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "step_number: ";
    rosidl_generator_traits::value_to_yaml(msg.step_number, out);
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

  // member: target_passes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_passes: ";
    rosidl_generator_traits::value_to_yaml(msg.target_passes, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LpsSaJobMgrTxChannel & msg, bool use_flow_style = false)
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
  const job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg,
  std::ostream & out, size_t indentation = 0)
{
  job_mgr_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use job_mgr_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
{
  return job_mgr_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>()
{
  return "job_mgr_interfaces::msg::LpsSaJobMgrTxChannel";
}

template<>
inline const char * name<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>()
{
  return "job_mgr_interfaces/msg/LpsSaJobMgrTxChannel";
}

template<>
struct has_fixed_size<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__TRAITS_HPP_
