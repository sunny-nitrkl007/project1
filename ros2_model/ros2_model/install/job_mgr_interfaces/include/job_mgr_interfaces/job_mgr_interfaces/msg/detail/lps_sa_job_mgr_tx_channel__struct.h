// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/LpsSaJobMgrTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_job_mgr_tx_channel.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'MAN_TIP_OFF_AVAILABLE'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__MAN_TIP_OFF_AVAILABLE = 0
};

/// Constant 'MAN_TIP_OFF_UNAVAILABLE'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__MAN_TIP_OFF_UNAVAILABLE = 1
};

/// Constant 'MAN_TIP_OFF_ACTIVE'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__MAN_TIP_OFF_ACTIVE = 2
};

/// Constant 'MAN_TIP_OFF_INACTIVE'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__MAN_TIP_OFF_INACTIVE = 3
};

/// Constant 'OP_MODE_UNCALIBRATED'.
/**
  * LpsSaJobMgrOperationMode_t
 */
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__OP_MODE_UNCALIBRATED = 838
};

/// Constant 'OP_MODE_WEIGH'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__OP_MODE_WEIGH = 9
};

/// Constant 'OP_MODE_STANDBY'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__OP_MODE_STANDBY = 175
};

/// Constant 'OP_MODE_EXCESS'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__OP_MODE_EXCESS = 846
};

/// Constant 'CLEAR_BTN_ENABLED'.
/**
  * LpsSaJobMgrClearMinusOneEnableStat_t
 */
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__CLEAR_BTN_ENABLED = 0
};

/// Constant 'MINUS_ONE_BTN_ENABLED'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__MINUS_ONE_BTN_ENABLED = 1
};

/// Constant 'CTRL_STAT_NONE'.
/**
  * ReqPloadCtrlSysStat_t
 */
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__CTRL_STAT_NONE = 58
};

/// Constant 'CTRL_STAT_CLEAR'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__CTRL_STAT_CLEAR = 551
};

/// Constant 'CTRL_STAT_REWEIGH'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__CTRL_STAT_REWEIGH = 763
};

/// Constant 'CTRL_STAT_ZERO'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__CTRL_STAT_ZERO = 862
};

/// Constant 'CTRL_STAT_STORE'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__CTRL_STAT_STORE = 863
};

/// Constant 'CTRL_STAT_TIPOFFTOGGLE'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__CTRL_STAT_TIPOFFTOGGLE = 1438
};

/// Constant 'CTRL_STAT_MINUS_ONE'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__CTRL_STAT_MINUS_ONE = 1584
};

/// Constant 'HORN_SOUND'.
/**
  * StorePloadHornStat_t
 */
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__HORN_SOUND = 794
};

/// Constant 'HORN_NOT_SOUND'.
enum
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__HORN_NOT_SOUND = 795
};

// Include directives for member types
// Member 'truck_weight_accuracy'
// Member 'total_weight_accuracy'
#include "job_mgr_interfaces/msg/detail/weigh_bkt_wt_accuracy__struct.h"
// Member 'ticket_id'
// Member 'material_name'
// Member 'truck_name'
// Member 'custom_list_name1'
// Member 'tag1'
// Member 'custom_list_name2'
// Member 'tag2'
// Member 'custom_list_name3'
// Member 'tag3'
// Member 'custom_list_name4'
// Member 'tag4'
#include "rosidl_runtime_c/string.h"
// Member 'tip_off_trigger_type'
#include "cpm_common_interfaces/msg/detail/tip_off_trigger_type__struct.h"
// Member 'tip_off_state'
// Member 'tip_off_state_cfg'
#include "cpm_common_interfaces/msg/detail/tip_off_state__struct.h"
// Member 'standby_state'
#include "cpm_common_interfaces/msg/detail/standby_state__struct.h"
// Member 'disp_best_bkt_wt'
#include "job_mgr_interfaces/msg/detail/disp_best_bkt_wt__struct.h"
// Member 'simple_cal_data'
#include "job_mgr_interfaces/msg/detail/simple_cal_data__struct.h"

/// Struct defined in msg/LpsSaJobMgrTxChannel in the package job_mgr_interfaces.
/**
  * LpsSaJobMgrManualTipOffState_t
 */
typedef struct job_mgr_interfaces__msg__LpsSaJobMgrTxChannel
{
  /// LpsSaJobMgrTxChannelStorage
  int64_t time_point_ns;
  uint8_t task_number;
  uint16_t pass_count;
  float truck_weight;
  job_mgr_interfaces__msg__WeighBktWtAccuracy truck_weight_accuracy;
  float truck_start_weight;
  float remaining_weight;
  float total_weight;
  job_mgr_interfaces__msg__WeighBktWtAccuracy total_weight_accuracy;
  uint32_t subtotal_count;
  rosidl_runtime_c__String ticket_id;
  uint32_t material_id;
  rosidl_runtime_c__String material_name;
  float material_density;
  uint32_t truck_id;
  rosidl_runtime_c__String truck_name;
  float truck_target_weight;
  bool truck_list_enabled;
  bool material_list_enabled;
  bool tag1_enabled;
  rosidl_runtime_c__String custom_list_name1;
  rosidl_runtime_c__String tag1;
  bool tag2_enabled;
  rosidl_runtime_c__String custom_list_name2;
  rosidl_runtime_c__String tag2;
  bool tag3_enabled;
  rosidl_runtime_c__String custom_list_name3;
  rosidl_runtime_c__String tag3;
  bool tag4_enabled;
  rosidl_runtime_c__String custom_list_name4;
  rosidl_runtime_c__String tag4;
  uint8_t manual_tip_off_state;
  cpm_common_interfaces__msg__TipOffTriggerType tip_off_trigger_type;
  cpm_common_interfaces__msg__TipOffState tip_off_state;
  cpm_common_interfaces__msg__TipOffState tip_off_state_cfg;
  uint16_t operation_mode;
  cpm_common_interfaces__msg__StandbyState standby_state;
  uint8_t clear_minus_one_enable_stat;
  job_mgr_interfaces__msg__DispBestBktWt disp_best_bkt_wt;
  job_mgr_interfaces__msg__SimpleCalData__Sequence simple_cal_data;
  uint32_t store_count;
  bool store_rejected;
  uint16_t req_pload_ctrl_sys_stat;
  uint16_t horn_store_state;
  uint16_t auto_store_pass_count;
  bool auto_truck_id_enabled;
  bool auto_material_id_enabled;
  bool manual_add_enabled;
  bool multi_task_enabled;
  uint8_t multi_task_count;
  bool tipoff_active;
  bool tipoff_assist_active;
  uint16_t tipoff_assist_active_eid;
  bool manual_add_available;
  bool split_mode_enabled;
  bool lft_disabled;
  uint8_t target_type;
  uint16_t step_number;
  uint8_t icon_type;
  uint16_t target_passes;
} job_mgr_interfaces__msg__LpsSaJobMgrTxChannel;

// Struct for a sequence of job_mgr_interfaces__msg__LpsSaJobMgrTxChannel.
typedef struct job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__Sequence
{
  job_mgr_interfaces__msg__LpsSaJobMgrTxChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__LpsSaJobMgrTxChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_TX_CHANNEL__STRUCT_H_
