// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from job_mgr_interfaces:msg/LpsSaJobMgrTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_job_mgr_tx_channel.hpp"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__STRUCT_HPP_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'truck_weight_accuracy'
// Member 'total_weight_accuracy'
#include "job_mgr_interfaces/msg/detail/weigh_bkt_wt_accuracy__struct.hpp"
// Member 'tip_off_trigger_type'
#include "cpm_common_interfaces/msg/detail/tip_off_trigger_type__struct.hpp"
// Member 'tip_off_state'
// Member 'tip_off_state_cfg'
#include "cpm_common_interfaces/msg/detail/tip_off_state__struct.hpp"
// Member 'standby_state'
#include "cpm_common_interfaces/msg/detail/standby_state__struct.hpp"
// Member 'disp_best_bkt_wt'
#include "job_mgr_interfaces/msg/detail/disp_best_bkt_wt__struct.hpp"
// Member 'simple_cal_data'
#include "job_mgr_interfaces/msg/detail/simple_cal_data__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__job_mgr_interfaces__msg__LpsSaJobMgrTxChannel __attribute__((deprecated))
#else
# define DEPRECATED__job_mgr_interfaces__msg__LpsSaJobMgrTxChannel __declspec(deprecated)
#endif

namespace job_mgr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LpsSaJobMgrTxChannel_
{
  using Type = LpsSaJobMgrTxChannel_<ContainerAllocator>;

  explicit LpsSaJobMgrTxChannel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : truck_weight_accuracy(_init),
    total_weight_accuracy(_init),
    tip_off_trigger_type(_init),
    tip_off_state(_init),
    tip_off_state_cfg(_init),
    standby_state(_init),
    disp_best_bkt_wt(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_point_ns = 0ll;
      this->task_number = 0;
      this->pass_count = 0;
      this->truck_weight = 0.0f;
      this->truck_start_weight = 0.0f;
      this->remaining_weight = 0.0f;
      this->total_weight = 0.0f;
      this->subtotal_count = 0ul;
      this->ticket_id = "";
      this->material_id = 0ul;
      this->material_name = "";
      this->material_density = 0.0f;
      this->truck_id = 0ul;
      this->truck_name = "";
      this->truck_target_weight = 0.0f;
      this->truck_list_enabled = false;
      this->material_list_enabled = false;
      this->tag1_enabled = false;
      this->custom_list_name1 = "";
      this->tag1 = "";
      this->tag2_enabled = false;
      this->custom_list_name2 = "";
      this->tag2 = "";
      this->tag3_enabled = false;
      this->custom_list_name3 = "";
      this->tag3 = "";
      this->tag4_enabled = false;
      this->custom_list_name4 = "";
      this->tag4 = "";
      this->manual_tip_off_state = 0;
      this->operation_mode = 0;
      this->clear_minus_one_enable_stat = 0;
      this->store_count = 0ul;
      this->store_rejected = false;
      this->req_pload_ctrl_sys_stat = 0;
      this->horn_store_state = 0;
      this->auto_store_pass_count = 0;
      this->auto_truck_id_enabled = false;
      this->auto_material_id_enabled = false;
      this->manual_add_enabled = false;
      this->multi_task_enabled = false;
      this->multi_task_count = 0;
      this->tipoff_active = false;
      this->tipoff_assist_active = false;
      this->tipoff_assist_active_eid = 0;
      this->manual_add_available = false;
      this->split_mode_enabled = false;
      this->lft_disabled = false;
      this->target_type = 0;
      this->step_number = 0;
      this->icon_type = 0;
      this->target_passes = 0;
    }
  }

  explicit LpsSaJobMgrTxChannel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : truck_weight_accuracy(_alloc, _init),
    total_weight_accuracy(_alloc, _init),
    ticket_id(_alloc),
    material_name(_alloc),
    truck_name(_alloc),
    custom_list_name1(_alloc),
    tag1(_alloc),
    custom_list_name2(_alloc),
    tag2(_alloc),
    custom_list_name3(_alloc),
    tag3(_alloc),
    custom_list_name4(_alloc),
    tag4(_alloc),
    tip_off_trigger_type(_alloc, _init),
    tip_off_state(_alloc, _init),
    tip_off_state_cfg(_alloc, _init),
    standby_state(_alloc, _init),
    disp_best_bkt_wt(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->time_point_ns = 0ll;
      this->task_number = 0;
      this->pass_count = 0;
      this->truck_weight = 0.0f;
      this->truck_start_weight = 0.0f;
      this->remaining_weight = 0.0f;
      this->total_weight = 0.0f;
      this->subtotal_count = 0ul;
      this->ticket_id = "";
      this->material_id = 0ul;
      this->material_name = "";
      this->material_density = 0.0f;
      this->truck_id = 0ul;
      this->truck_name = "";
      this->truck_target_weight = 0.0f;
      this->truck_list_enabled = false;
      this->material_list_enabled = false;
      this->tag1_enabled = false;
      this->custom_list_name1 = "";
      this->tag1 = "";
      this->tag2_enabled = false;
      this->custom_list_name2 = "";
      this->tag2 = "";
      this->tag3_enabled = false;
      this->custom_list_name3 = "";
      this->tag3 = "";
      this->tag4_enabled = false;
      this->custom_list_name4 = "";
      this->tag4 = "";
      this->manual_tip_off_state = 0;
      this->operation_mode = 0;
      this->clear_minus_one_enable_stat = 0;
      this->store_count = 0ul;
      this->store_rejected = false;
      this->req_pload_ctrl_sys_stat = 0;
      this->horn_store_state = 0;
      this->auto_store_pass_count = 0;
      this->auto_truck_id_enabled = false;
      this->auto_material_id_enabled = false;
      this->manual_add_enabled = false;
      this->multi_task_enabled = false;
      this->multi_task_count = 0;
      this->tipoff_active = false;
      this->tipoff_assist_active = false;
      this->tipoff_assist_active_eid = 0;
      this->manual_add_available = false;
      this->split_mode_enabled = false;
      this->lft_disabled = false;
      this->target_type = 0;
      this->step_number = 0;
      this->icon_type = 0;
      this->target_passes = 0;
    }
  }

  // field types and members
  using _time_point_ns_type =
    int64_t;
  _time_point_ns_type time_point_ns;
  using _task_number_type =
    uint8_t;
  _task_number_type task_number;
  using _pass_count_type =
    uint16_t;
  _pass_count_type pass_count;
  using _truck_weight_type =
    float;
  _truck_weight_type truck_weight;
  using _truck_weight_accuracy_type =
    job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator>;
  _truck_weight_accuracy_type truck_weight_accuracy;
  using _truck_start_weight_type =
    float;
  _truck_start_weight_type truck_start_weight;
  using _remaining_weight_type =
    float;
  _remaining_weight_type remaining_weight;
  using _total_weight_type =
    float;
  _total_weight_type total_weight;
  using _total_weight_accuracy_type =
    job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator>;
  _total_weight_accuracy_type total_weight_accuracy;
  using _subtotal_count_type =
    uint32_t;
  _subtotal_count_type subtotal_count;
  using _ticket_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _ticket_id_type ticket_id;
  using _material_id_type =
    uint32_t;
  _material_id_type material_id;
  using _material_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _material_name_type material_name;
  using _material_density_type =
    float;
  _material_density_type material_density;
  using _truck_id_type =
    uint32_t;
  _truck_id_type truck_id;
  using _truck_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _truck_name_type truck_name;
  using _truck_target_weight_type =
    float;
  _truck_target_weight_type truck_target_weight;
  using _truck_list_enabled_type =
    bool;
  _truck_list_enabled_type truck_list_enabled;
  using _material_list_enabled_type =
    bool;
  _material_list_enabled_type material_list_enabled;
  using _tag1_enabled_type =
    bool;
  _tag1_enabled_type tag1_enabled;
  using _custom_list_name1_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _custom_list_name1_type custom_list_name1;
  using _tag1_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tag1_type tag1;
  using _tag2_enabled_type =
    bool;
  _tag2_enabled_type tag2_enabled;
  using _custom_list_name2_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _custom_list_name2_type custom_list_name2;
  using _tag2_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tag2_type tag2;
  using _tag3_enabled_type =
    bool;
  _tag3_enabled_type tag3_enabled;
  using _custom_list_name3_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _custom_list_name3_type custom_list_name3;
  using _tag3_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tag3_type tag3;
  using _tag4_enabled_type =
    bool;
  _tag4_enabled_type tag4_enabled;
  using _custom_list_name4_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _custom_list_name4_type custom_list_name4;
  using _tag4_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tag4_type tag4;
  using _manual_tip_off_state_type =
    uint8_t;
  _manual_tip_off_state_type manual_tip_off_state;
  using _tip_off_trigger_type_type =
    cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator>;
  _tip_off_trigger_type_type tip_off_trigger_type;
  using _tip_off_state_type =
    cpm_common_interfaces::msg::TipOffState_<ContainerAllocator>;
  _tip_off_state_type tip_off_state;
  using _tip_off_state_cfg_type =
    cpm_common_interfaces::msg::TipOffState_<ContainerAllocator>;
  _tip_off_state_cfg_type tip_off_state_cfg;
  using _operation_mode_type =
    uint16_t;
  _operation_mode_type operation_mode;
  using _standby_state_type =
    cpm_common_interfaces::msg::StandbyState_<ContainerAllocator>;
  _standby_state_type standby_state;
  using _clear_minus_one_enable_stat_type =
    uint8_t;
  _clear_minus_one_enable_stat_type clear_minus_one_enable_stat;
  using _disp_best_bkt_wt_type =
    job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator>;
  _disp_best_bkt_wt_type disp_best_bkt_wt;
  using _simple_cal_data_type =
    std::vector<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator>>>;
  _simple_cal_data_type simple_cal_data;
  using _store_count_type =
    uint32_t;
  _store_count_type store_count;
  using _store_rejected_type =
    bool;
  _store_rejected_type store_rejected;
  using _req_pload_ctrl_sys_stat_type =
    uint16_t;
  _req_pload_ctrl_sys_stat_type req_pload_ctrl_sys_stat;
  using _horn_store_state_type =
    uint16_t;
  _horn_store_state_type horn_store_state;
  using _auto_store_pass_count_type =
    uint16_t;
  _auto_store_pass_count_type auto_store_pass_count;
  using _auto_truck_id_enabled_type =
    bool;
  _auto_truck_id_enabled_type auto_truck_id_enabled;
  using _auto_material_id_enabled_type =
    bool;
  _auto_material_id_enabled_type auto_material_id_enabled;
  using _manual_add_enabled_type =
    bool;
  _manual_add_enabled_type manual_add_enabled;
  using _multi_task_enabled_type =
    bool;
  _multi_task_enabled_type multi_task_enabled;
  using _multi_task_count_type =
    uint8_t;
  _multi_task_count_type multi_task_count;
  using _tipoff_active_type =
    bool;
  _tipoff_active_type tipoff_active;
  using _tipoff_assist_active_type =
    bool;
  _tipoff_assist_active_type tipoff_assist_active;
  using _tipoff_assist_active_eid_type =
    uint16_t;
  _tipoff_assist_active_eid_type tipoff_assist_active_eid;
  using _manual_add_available_type =
    bool;
  _manual_add_available_type manual_add_available;
  using _split_mode_enabled_type =
    bool;
  _split_mode_enabled_type split_mode_enabled;
  using _lft_disabled_type =
    bool;
  _lft_disabled_type lft_disabled;
  using _target_type_type =
    uint8_t;
  _target_type_type target_type;
  using _step_number_type =
    uint16_t;
  _step_number_type step_number;
  using _icon_type_type =
    uint8_t;
  _icon_type_type icon_type;
  using _target_passes_type =
    uint16_t;
  _target_passes_type target_passes;

  // setters for named parameter idiom
  Type & set__time_point_ns(
    const int64_t & _arg)
  {
    this->time_point_ns = _arg;
    return *this;
  }
  Type & set__task_number(
    const uint8_t & _arg)
  {
    this->task_number = _arg;
    return *this;
  }
  Type & set__pass_count(
    const uint16_t & _arg)
  {
    this->pass_count = _arg;
    return *this;
  }
  Type & set__truck_weight(
    const float & _arg)
  {
    this->truck_weight = _arg;
    return *this;
  }
  Type & set__truck_weight_accuracy(
    const job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator> & _arg)
  {
    this->truck_weight_accuracy = _arg;
    return *this;
  }
  Type & set__truck_start_weight(
    const float & _arg)
  {
    this->truck_start_weight = _arg;
    return *this;
  }
  Type & set__remaining_weight(
    const float & _arg)
  {
    this->remaining_weight = _arg;
    return *this;
  }
  Type & set__total_weight(
    const float & _arg)
  {
    this->total_weight = _arg;
    return *this;
  }
  Type & set__total_weight_accuracy(
    const job_mgr_interfaces::msg::WeighBktWtAccuracy_<ContainerAllocator> & _arg)
  {
    this->total_weight_accuracy = _arg;
    return *this;
  }
  Type & set__subtotal_count(
    const uint32_t & _arg)
  {
    this->subtotal_count = _arg;
    return *this;
  }
  Type & set__ticket_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->ticket_id = _arg;
    return *this;
  }
  Type & set__material_id(
    const uint32_t & _arg)
  {
    this->material_id = _arg;
    return *this;
  }
  Type & set__material_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->material_name = _arg;
    return *this;
  }
  Type & set__material_density(
    const float & _arg)
  {
    this->material_density = _arg;
    return *this;
  }
  Type & set__truck_id(
    const uint32_t & _arg)
  {
    this->truck_id = _arg;
    return *this;
  }
  Type & set__truck_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->truck_name = _arg;
    return *this;
  }
  Type & set__truck_target_weight(
    const float & _arg)
  {
    this->truck_target_weight = _arg;
    return *this;
  }
  Type & set__truck_list_enabled(
    const bool & _arg)
  {
    this->truck_list_enabled = _arg;
    return *this;
  }
  Type & set__material_list_enabled(
    const bool & _arg)
  {
    this->material_list_enabled = _arg;
    return *this;
  }
  Type & set__tag1_enabled(
    const bool & _arg)
  {
    this->tag1_enabled = _arg;
    return *this;
  }
  Type & set__custom_list_name1(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->custom_list_name1 = _arg;
    return *this;
  }
  Type & set__tag1(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tag1 = _arg;
    return *this;
  }
  Type & set__tag2_enabled(
    const bool & _arg)
  {
    this->tag2_enabled = _arg;
    return *this;
  }
  Type & set__custom_list_name2(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->custom_list_name2 = _arg;
    return *this;
  }
  Type & set__tag2(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tag2 = _arg;
    return *this;
  }
  Type & set__tag3_enabled(
    const bool & _arg)
  {
    this->tag3_enabled = _arg;
    return *this;
  }
  Type & set__custom_list_name3(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->custom_list_name3 = _arg;
    return *this;
  }
  Type & set__tag3(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tag3 = _arg;
    return *this;
  }
  Type & set__tag4_enabled(
    const bool & _arg)
  {
    this->tag4_enabled = _arg;
    return *this;
  }
  Type & set__custom_list_name4(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->custom_list_name4 = _arg;
    return *this;
  }
  Type & set__tag4(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tag4 = _arg;
    return *this;
  }
  Type & set__manual_tip_off_state(
    const uint8_t & _arg)
  {
    this->manual_tip_off_state = _arg;
    return *this;
  }
  Type & set__tip_off_trigger_type(
    const cpm_common_interfaces::msg::TipOffTriggerType_<ContainerAllocator> & _arg)
  {
    this->tip_off_trigger_type = _arg;
    return *this;
  }
  Type & set__tip_off_state(
    const cpm_common_interfaces::msg::TipOffState_<ContainerAllocator> & _arg)
  {
    this->tip_off_state = _arg;
    return *this;
  }
  Type & set__tip_off_state_cfg(
    const cpm_common_interfaces::msg::TipOffState_<ContainerAllocator> & _arg)
  {
    this->tip_off_state_cfg = _arg;
    return *this;
  }
  Type & set__operation_mode(
    const uint16_t & _arg)
  {
    this->operation_mode = _arg;
    return *this;
  }
  Type & set__standby_state(
    const cpm_common_interfaces::msg::StandbyState_<ContainerAllocator> & _arg)
  {
    this->standby_state = _arg;
    return *this;
  }
  Type & set__clear_minus_one_enable_stat(
    const uint8_t & _arg)
  {
    this->clear_minus_one_enable_stat = _arg;
    return *this;
  }
  Type & set__disp_best_bkt_wt(
    const job_mgr_interfaces::msg::DispBestBktWt_<ContainerAllocator> & _arg)
  {
    this->disp_best_bkt_wt = _arg;
    return *this;
  }
  Type & set__simple_cal_data(
    const std::vector<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<job_mgr_interfaces::msg::SimpleCalData_<ContainerAllocator>>> & _arg)
  {
    this->simple_cal_data = _arg;
    return *this;
  }
  Type & set__store_count(
    const uint32_t & _arg)
  {
    this->store_count = _arg;
    return *this;
  }
  Type & set__store_rejected(
    const bool & _arg)
  {
    this->store_rejected = _arg;
    return *this;
  }
  Type & set__req_pload_ctrl_sys_stat(
    const uint16_t & _arg)
  {
    this->req_pload_ctrl_sys_stat = _arg;
    return *this;
  }
  Type & set__horn_store_state(
    const uint16_t & _arg)
  {
    this->horn_store_state = _arg;
    return *this;
  }
  Type & set__auto_store_pass_count(
    const uint16_t & _arg)
  {
    this->auto_store_pass_count = _arg;
    return *this;
  }
  Type & set__auto_truck_id_enabled(
    const bool & _arg)
  {
    this->auto_truck_id_enabled = _arg;
    return *this;
  }
  Type & set__auto_material_id_enabled(
    const bool & _arg)
  {
    this->auto_material_id_enabled = _arg;
    return *this;
  }
  Type & set__manual_add_enabled(
    const bool & _arg)
  {
    this->manual_add_enabled = _arg;
    return *this;
  }
  Type & set__multi_task_enabled(
    const bool & _arg)
  {
    this->multi_task_enabled = _arg;
    return *this;
  }
  Type & set__multi_task_count(
    const uint8_t & _arg)
  {
    this->multi_task_count = _arg;
    return *this;
  }
  Type & set__tipoff_active(
    const bool & _arg)
  {
    this->tipoff_active = _arg;
    return *this;
  }
  Type & set__tipoff_assist_active(
    const bool & _arg)
  {
    this->tipoff_assist_active = _arg;
    return *this;
  }
  Type & set__tipoff_assist_active_eid(
    const uint16_t & _arg)
  {
    this->tipoff_assist_active_eid = _arg;
    return *this;
  }
  Type & set__manual_add_available(
    const bool & _arg)
  {
    this->manual_add_available = _arg;
    return *this;
  }
  Type & set__split_mode_enabled(
    const bool & _arg)
  {
    this->split_mode_enabled = _arg;
    return *this;
  }
  Type & set__lft_disabled(
    const bool & _arg)
  {
    this->lft_disabled = _arg;
    return *this;
  }
  Type & set__target_type(
    const uint8_t & _arg)
  {
    this->target_type = _arg;
    return *this;
  }
  Type & set__step_number(
    const uint16_t & _arg)
  {
    this->step_number = _arg;
    return *this;
  }
  Type & set__icon_type(
    const uint8_t & _arg)
  {
    this->icon_type = _arg;
    return *this;
  }
  Type & set__target_passes(
    const uint16_t & _arg)
  {
    this->target_passes = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t MAN_TIP_OFF_AVAILABLE =
    0u;
  static constexpr uint8_t MAN_TIP_OFF_UNAVAILABLE =
    1u;
  static constexpr uint8_t MAN_TIP_OFF_ACTIVE =
    2u;
  static constexpr uint8_t MAN_TIP_OFF_INACTIVE =
    3u;
  static constexpr uint16_t OP_MODE_UNCALIBRATED =
    838u;
  static constexpr uint16_t OP_MODE_WEIGH =
    9u;
  static constexpr uint16_t OP_MODE_STANDBY =
    175u;
  static constexpr uint16_t OP_MODE_EXCESS =
    846u;
  static constexpr uint8_t CLEAR_BTN_ENABLED =
    0u;
  static constexpr uint8_t MINUS_ONE_BTN_ENABLED =
    1u;
  static constexpr uint16_t CTRL_STAT_NONE =
    58u;
  static constexpr uint16_t CTRL_STAT_CLEAR =
    551u;
  static constexpr uint16_t CTRL_STAT_REWEIGH =
    763u;
  static constexpr uint16_t CTRL_STAT_ZERO =
    862u;
  static constexpr uint16_t CTRL_STAT_STORE =
    863u;
  static constexpr uint16_t CTRL_STAT_TIPOFFTOGGLE =
    1438u;
  static constexpr uint16_t CTRL_STAT_MINUS_ONE =
    1584u;
  static constexpr uint16_t HORN_SOUND =
    794u;
  static constexpr uint16_t HORN_NOT_SOUND =
    795u;

  // pointer types
  using RawPtr =
    job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator> *;
  using ConstRawPtr =
    const job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__job_mgr_interfaces__msg__LpsSaJobMgrTxChannel
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__job_mgr_interfaces__msg__LpsSaJobMgrTxChannel
    std::shared_ptr<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LpsSaJobMgrTxChannel_ & other) const
  {
    if (this->time_point_ns != other.time_point_ns) {
      return false;
    }
    if (this->task_number != other.task_number) {
      return false;
    }
    if (this->pass_count != other.pass_count) {
      return false;
    }
    if (this->truck_weight != other.truck_weight) {
      return false;
    }
    if (this->truck_weight_accuracy != other.truck_weight_accuracy) {
      return false;
    }
    if (this->truck_start_weight != other.truck_start_weight) {
      return false;
    }
    if (this->remaining_weight != other.remaining_weight) {
      return false;
    }
    if (this->total_weight != other.total_weight) {
      return false;
    }
    if (this->total_weight_accuracy != other.total_weight_accuracy) {
      return false;
    }
    if (this->subtotal_count != other.subtotal_count) {
      return false;
    }
    if (this->ticket_id != other.ticket_id) {
      return false;
    }
    if (this->material_id != other.material_id) {
      return false;
    }
    if (this->material_name != other.material_name) {
      return false;
    }
    if (this->material_density != other.material_density) {
      return false;
    }
    if (this->truck_id != other.truck_id) {
      return false;
    }
    if (this->truck_name != other.truck_name) {
      return false;
    }
    if (this->truck_target_weight != other.truck_target_weight) {
      return false;
    }
    if (this->truck_list_enabled != other.truck_list_enabled) {
      return false;
    }
    if (this->material_list_enabled != other.material_list_enabled) {
      return false;
    }
    if (this->tag1_enabled != other.tag1_enabled) {
      return false;
    }
    if (this->custom_list_name1 != other.custom_list_name1) {
      return false;
    }
    if (this->tag1 != other.tag1) {
      return false;
    }
    if (this->tag2_enabled != other.tag2_enabled) {
      return false;
    }
    if (this->custom_list_name2 != other.custom_list_name2) {
      return false;
    }
    if (this->tag2 != other.tag2) {
      return false;
    }
    if (this->tag3_enabled != other.tag3_enabled) {
      return false;
    }
    if (this->custom_list_name3 != other.custom_list_name3) {
      return false;
    }
    if (this->tag3 != other.tag3) {
      return false;
    }
    if (this->tag4_enabled != other.tag4_enabled) {
      return false;
    }
    if (this->custom_list_name4 != other.custom_list_name4) {
      return false;
    }
    if (this->tag4 != other.tag4) {
      return false;
    }
    if (this->manual_tip_off_state != other.manual_tip_off_state) {
      return false;
    }
    if (this->tip_off_trigger_type != other.tip_off_trigger_type) {
      return false;
    }
    if (this->tip_off_state != other.tip_off_state) {
      return false;
    }
    if (this->tip_off_state_cfg != other.tip_off_state_cfg) {
      return false;
    }
    if (this->operation_mode != other.operation_mode) {
      return false;
    }
    if (this->standby_state != other.standby_state) {
      return false;
    }
    if (this->clear_minus_one_enable_stat != other.clear_minus_one_enable_stat) {
      return false;
    }
    if (this->disp_best_bkt_wt != other.disp_best_bkt_wt) {
      return false;
    }
    if (this->simple_cal_data != other.simple_cal_data) {
      return false;
    }
    if (this->store_count != other.store_count) {
      return false;
    }
    if (this->store_rejected != other.store_rejected) {
      return false;
    }
    if (this->req_pload_ctrl_sys_stat != other.req_pload_ctrl_sys_stat) {
      return false;
    }
    if (this->horn_store_state != other.horn_store_state) {
      return false;
    }
    if (this->auto_store_pass_count != other.auto_store_pass_count) {
      return false;
    }
    if (this->auto_truck_id_enabled != other.auto_truck_id_enabled) {
      return false;
    }
    if (this->auto_material_id_enabled != other.auto_material_id_enabled) {
      return false;
    }
    if (this->manual_add_enabled != other.manual_add_enabled) {
      return false;
    }
    if (this->multi_task_enabled != other.multi_task_enabled) {
      return false;
    }
    if (this->multi_task_count != other.multi_task_count) {
      return false;
    }
    if (this->tipoff_active != other.tipoff_active) {
      return false;
    }
    if (this->tipoff_assist_active != other.tipoff_assist_active) {
      return false;
    }
    if (this->tipoff_assist_active_eid != other.tipoff_assist_active_eid) {
      return false;
    }
    if (this->manual_add_available != other.manual_add_available) {
      return false;
    }
    if (this->split_mode_enabled != other.split_mode_enabled) {
      return false;
    }
    if (this->lft_disabled != other.lft_disabled) {
      return false;
    }
    if (this->target_type != other.target_type) {
      return false;
    }
    if (this->step_number != other.step_number) {
      return false;
    }
    if (this->icon_type != other.icon_type) {
      return false;
    }
    if (this->target_passes != other.target_passes) {
      return false;
    }
    return true;
  }
  bool operator!=(const LpsSaJobMgrTxChannel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LpsSaJobMgrTxChannel_

// alias to use template instance with default allocator
using LpsSaJobMgrTxChannel =
  job_mgr_interfaces::msg::LpsSaJobMgrTxChannel_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrTxChannel_<ContainerAllocator>::MAN_TIP_OFF_AVAILABLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrTxChannel_<ContainerAllocator>::MAN_TIP_OFF_UNAVAILABLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrTxChannel_<ContainerAllocator>::MAN_TIP_OFF_ACTIVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrTxChannel_<ContainerAllocator>::MAN_TIP_OFF_INACTIVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::OP_MODE_UNCALIBRATED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::OP_MODE_WEIGH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::OP_MODE_STANDBY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::OP_MODE_EXCESS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrTxChannel_<ContainerAllocator>::CLEAR_BTN_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LpsSaJobMgrTxChannel_<ContainerAllocator>::MINUS_ONE_BTN_ENABLED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::CTRL_STAT_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::CTRL_STAT_CLEAR;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::CTRL_STAT_REWEIGH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::CTRL_STAT_ZERO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::CTRL_STAT_STORE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::CTRL_STAT_TIPOFFTOGGLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::CTRL_STAT_MINUS_ONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::HORN_SOUND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t LpsSaJobMgrTxChannel_<ContainerAllocator>::HORN_NOT_SOUND;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace job_mgr_interfaces

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__STRUCT_HPP_
