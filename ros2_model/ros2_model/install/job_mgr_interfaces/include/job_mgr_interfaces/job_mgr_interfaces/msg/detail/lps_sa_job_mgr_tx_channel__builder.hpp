// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from job_mgr_interfaces:msg/LpsSaJobMgrTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_job_mgr_tx_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__BUILDER_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "job_mgr_interfaces/msg/detail/lps_sa_job_mgr_tx_channel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace job_mgr_interfaces
{

namespace msg
{

namespace builder
{

class Init_LpsSaJobMgrTxChannel_target_passes
{
public:
  explicit Init_LpsSaJobMgrTxChannel_target_passes(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel target_passes(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_target_passes_type arg)
  {
    msg_.target_passes = std::move(arg);
    return std::move(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_icon_type
{
public:
  explicit Init_LpsSaJobMgrTxChannel_icon_type(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_target_passes icon_type(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_icon_type_type arg)
  {
    msg_.icon_type = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_target_passes(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_step_number
{
public:
  explicit Init_LpsSaJobMgrTxChannel_step_number(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_icon_type step_number(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_step_number_type arg)
  {
    msg_.step_number = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_icon_type(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_target_type
{
public:
  explicit Init_LpsSaJobMgrTxChannel_target_type(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_step_number target_type(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_target_type_type arg)
  {
    msg_.target_type = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_step_number(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_lft_disabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_lft_disabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_target_type lft_disabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_lft_disabled_type arg)
  {
    msg_.lft_disabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_target_type(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_split_mode_enabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_split_mode_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_lft_disabled split_mode_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_split_mode_enabled_type arg)
  {
    msg_.split_mode_enabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_lft_disabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_manual_add_available
{
public:
  explicit Init_LpsSaJobMgrTxChannel_manual_add_available(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_split_mode_enabled manual_add_available(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_manual_add_available_type arg)
  {
    msg_.manual_add_available = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_split_mode_enabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tipoff_assist_active_eid
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tipoff_assist_active_eid(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_manual_add_available tipoff_assist_active_eid(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tipoff_assist_active_eid_type arg)
  {
    msg_.tipoff_assist_active_eid = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_manual_add_available(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tipoff_assist_active
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tipoff_assist_active(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tipoff_assist_active_eid tipoff_assist_active(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tipoff_assist_active_type arg)
  {
    msg_.tipoff_assist_active = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tipoff_assist_active_eid(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tipoff_active
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tipoff_active(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tipoff_assist_active tipoff_active(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tipoff_active_type arg)
  {
    msg_.tipoff_active = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tipoff_assist_active(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_multi_task_count
{
public:
  explicit Init_LpsSaJobMgrTxChannel_multi_task_count(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tipoff_active multi_task_count(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_multi_task_count_type arg)
  {
    msg_.multi_task_count = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tipoff_active(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_multi_task_enabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_multi_task_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_multi_task_count multi_task_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_multi_task_enabled_type arg)
  {
    msg_.multi_task_enabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_multi_task_count(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_manual_add_enabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_manual_add_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_multi_task_enabled manual_add_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_manual_add_enabled_type arg)
  {
    msg_.manual_add_enabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_multi_task_enabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_auto_material_id_enabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_auto_material_id_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_manual_add_enabled auto_material_id_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_auto_material_id_enabled_type arg)
  {
    msg_.auto_material_id_enabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_manual_add_enabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_auto_truck_id_enabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_auto_truck_id_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_auto_material_id_enabled auto_truck_id_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_auto_truck_id_enabled_type arg)
  {
    msg_.auto_truck_id_enabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_auto_material_id_enabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_auto_store_pass_count
{
public:
  explicit Init_LpsSaJobMgrTxChannel_auto_store_pass_count(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_auto_truck_id_enabled auto_store_pass_count(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_auto_store_pass_count_type arg)
  {
    msg_.auto_store_pass_count = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_auto_truck_id_enabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_horn_store_state
{
public:
  explicit Init_LpsSaJobMgrTxChannel_horn_store_state(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_auto_store_pass_count horn_store_state(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_horn_store_state_type arg)
  {
    msg_.horn_store_state = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_auto_store_pass_count(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_req_pload_ctrl_sys_stat
{
public:
  explicit Init_LpsSaJobMgrTxChannel_req_pload_ctrl_sys_stat(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_horn_store_state req_pload_ctrl_sys_stat(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_req_pload_ctrl_sys_stat_type arg)
  {
    msg_.req_pload_ctrl_sys_stat = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_horn_store_state(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_store_rejected
{
public:
  explicit Init_LpsSaJobMgrTxChannel_store_rejected(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_req_pload_ctrl_sys_stat store_rejected(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_store_rejected_type arg)
  {
    msg_.store_rejected = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_req_pload_ctrl_sys_stat(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_store_count
{
public:
  explicit Init_LpsSaJobMgrTxChannel_store_count(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_store_rejected store_count(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_store_count_type arg)
  {
    msg_.store_count = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_store_rejected(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_simple_cal_data
{
public:
  explicit Init_LpsSaJobMgrTxChannel_simple_cal_data(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_store_count simple_cal_data(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_simple_cal_data_type arg)
  {
    msg_.simple_cal_data = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_store_count(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_disp_best_bkt_wt
{
public:
  explicit Init_LpsSaJobMgrTxChannel_disp_best_bkt_wt(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_simple_cal_data disp_best_bkt_wt(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_disp_best_bkt_wt_type arg)
  {
    msg_.disp_best_bkt_wt = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_simple_cal_data(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_clear_minus_one_enable_stat
{
public:
  explicit Init_LpsSaJobMgrTxChannel_clear_minus_one_enable_stat(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_disp_best_bkt_wt clear_minus_one_enable_stat(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_clear_minus_one_enable_stat_type arg)
  {
    msg_.clear_minus_one_enable_stat = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_disp_best_bkt_wt(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_standby_state
{
public:
  explicit Init_LpsSaJobMgrTxChannel_standby_state(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_clear_minus_one_enable_stat standby_state(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_standby_state_type arg)
  {
    msg_.standby_state = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_clear_minus_one_enable_stat(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_operation_mode
{
public:
  explicit Init_LpsSaJobMgrTxChannel_operation_mode(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_standby_state operation_mode(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_operation_mode_type arg)
  {
    msg_.operation_mode = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_standby_state(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tip_off_state_cfg
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tip_off_state_cfg(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_operation_mode tip_off_state_cfg(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tip_off_state_cfg_type arg)
  {
    msg_.tip_off_state_cfg = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_operation_mode(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tip_off_state
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tip_off_state(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tip_off_state_cfg tip_off_state(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tip_off_state_type arg)
  {
    msg_.tip_off_state = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tip_off_state_cfg(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tip_off_trigger_type
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tip_off_trigger_type(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tip_off_state tip_off_trigger_type(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tip_off_trigger_type_type arg)
  {
    msg_.tip_off_trigger_type = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tip_off_state(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_manual_tip_off_state
{
public:
  explicit Init_LpsSaJobMgrTxChannel_manual_tip_off_state(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tip_off_trigger_type manual_tip_off_state(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_manual_tip_off_state_type arg)
  {
    msg_.manual_tip_off_state = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tip_off_trigger_type(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tag4
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tag4(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_manual_tip_off_state tag4(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tag4_type arg)
  {
    msg_.tag4 = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_manual_tip_off_state(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_custom_list_name4
{
public:
  explicit Init_LpsSaJobMgrTxChannel_custom_list_name4(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tag4 custom_list_name4(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_custom_list_name4_type arg)
  {
    msg_.custom_list_name4 = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tag4(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tag4_enabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tag4_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_custom_list_name4 tag4_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tag4_enabled_type arg)
  {
    msg_.tag4_enabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_custom_list_name4(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tag3
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tag3(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tag4_enabled tag3(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tag3_type arg)
  {
    msg_.tag3 = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tag4_enabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_custom_list_name3
{
public:
  explicit Init_LpsSaJobMgrTxChannel_custom_list_name3(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tag3 custom_list_name3(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_custom_list_name3_type arg)
  {
    msg_.custom_list_name3 = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tag3(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tag3_enabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tag3_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_custom_list_name3 tag3_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tag3_enabled_type arg)
  {
    msg_.tag3_enabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_custom_list_name3(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tag2
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tag2(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tag3_enabled tag2(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tag2_type arg)
  {
    msg_.tag2 = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tag3_enabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_custom_list_name2
{
public:
  explicit Init_LpsSaJobMgrTxChannel_custom_list_name2(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tag2 custom_list_name2(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_custom_list_name2_type arg)
  {
    msg_.custom_list_name2 = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tag2(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tag2_enabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tag2_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_custom_list_name2 tag2_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tag2_enabled_type arg)
  {
    msg_.tag2_enabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_custom_list_name2(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tag1
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tag1(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tag2_enabled tag1(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tag1_type arg)
  {
    msg_.tag1 = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tag2_enabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_custom_list_name1
{
public:
  explicit Init_LpsSaJobMgrTxChannel_custom_list_name1(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tag1 custom_list_name1(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_custom_list_name1_type arg)
  {
    msg_.custom_list_name1 = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tag1(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_tag1_enabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_tag1_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_custom_list_name1 tag1_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_tag1_enabled_type arg)
  {
    msg_.tag1_enabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_custom_list_name1(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_material_list_enabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_material_list_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_tag1_enabled material_list_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_material_list_enabled_type arg)
  {
    msg_.material_list_enabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_tag1_enabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_truck_list_enabled
{
public:
  explicit Init_LpsSaJobMgrTxChannel_truck_list_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_material_list_enabled truck_list_enabled(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_truck_list_enabled_type arg)
  {
    msg_.truck_list_enabled = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_material_list_enabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_truck_target_weight
{
public:
  explicit Init_LpsSaJobMgrTxChannel_truck_target_weight(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_truck_list_enabled truck_target_weight(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_truck_target_weight_type arg)
  {
    msg_.truck_target_weight = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_truck_list_enabled(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_truck_name
{
public:
  explicit Init_LpsSaJobMgrTxChannel_truck_name(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_truck_target_weight truck_name(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_truck_name_type arg)
  {
    msg_.truck_name = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_truck_target_weight(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_truck_id
{
public:
  explicit Init_LpsSaJobMgrTxChannel_truck_id(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_truck_name truck_id(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_truck_id_type arg)
  {
    msg_.truck_id = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_truck_name(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_material_density
{
public:
  explicit Init_LpsSaJobMgrTxChannel_material_density(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_truck_id material_density(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_material_density_type arg)
  {
    msg_.material_density = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_truck_id(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_material_name
{
public:
  explicit Init_LpsSaJobMgrTxChannel_material_name(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_material_density material_name(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_material_name_type arg)
  {
    msg_.material_name = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_material_density(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_material_id
{
public:
  explicit Init_LpsSaJobMgrTxChannel_material_id(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_material_name material_id(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_material_id_type arg)
  {
    msg_.material_id = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_material_name(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_ticket_id
{
public:
  explicit Init_LpsSaJobMgrTxChannel_ticket_id(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_material_id ticket_id(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_ticket_id_type arg)
  {
    msg_.ticket_id = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_material_id(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_subtotal_count
{
public:
  explicit Init_LpsSaJobMgrTxChannel_subtotal_count(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_ticket_id subtotal_count(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_subtotal_count_type arg)
  {
    msg_.subtotal_count = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_ticket_id(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_total_weight_accuracy
{
public:
  explicit Init_LpsSaJobMgrTxChannel_total_weight_accuracy(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_subtotal_count total_weight_accuracy(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_total_weight_accuracy_type arg)
  {
    msg_.total_weight_accuracy = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_subtotal_count(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_total_weight
{
public:
  explicit Init_LpsSaJobMgrTxChannel_total_weight(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_total_weight_accuracy total_weight(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_total_weight_type arg)
  {
    msg_.total_weight = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_total_weight_accuracy(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_remaining_weight
{
public:
  explicit Init_LpsSaJobMgrTxChannel_remaining_weight(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_total_weight remaining_weight(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_remaining_weight_type arg)
  {
    msg_.remaining_weight = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_total_weight(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_truck_start_weight
{
public:
  explicit Init_LpsSaJobMgrTxChannel_truck_start_weight(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_remaining_weight truck_start_weight(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_truck_start_weight_type arg)
  {
    msg_.truck_start_weight = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_remaining_weight(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_truck_weight_accuracy
{
public:
  explicit Init_LpsSaJobMgrTxChannel_truck_weight_accuracy(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_truck_start_weight truck_weight_accuracy(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_truck_weight_accuracy_type arg)
  {
    msg_.truck_weight_accuracy = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_truck_start_weight(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_truck_weight
{
public:
  explicit Init_LpsSaJobMgrTxChannel_truck_weight(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_truck_weight_accuracy truck_weight(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_truck_weight_type arg)
  {
    msg_.truck_weight = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_truck_weight_accuracy(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_pass_count
{
public:
  explicit Init_LpsSaJobMgrTxChannel_pass_count(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_truck_weight pass_count(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_pass_count_type arg)
  {
    msg_.pass_count = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_truck_weight(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_task_number
{
public:
  explicit Init_LpsSaJobMgrTxChannel_task_number(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel & msg)
  : msg_(msg)
  {}
  Init_LpsSaJobMgrTxChannel_pass_count task_number(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_task_number_type arg)
  {
    msg_.task_number = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_pass_count(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

class Init_LpsSaJobMgrTxChannel_time_point_ns
{
public:
  Init_LpsSaJobMgrTxChannel_time_point_ns()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LpsSaJobMgrTxChannel_task_number time_point_ns(::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel::_time_point_ns_type arg)
  {
    msg_.time_point_ns = std::move(arg);
    return Init_LpsSaJobMgrTxChannel_task_number(msg_);
  }

private:
  ::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>()
{
  return job_mgr_interfaces::msg::builder::Init_LpsSaJobMgrTxChannel_time_point_ns();
}

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__BUILDER_HPP_
