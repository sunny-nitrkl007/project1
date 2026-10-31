// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrReqstChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_reqst_channel.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'app_name'
#include "rosidl_runtime_c/string.h"
// Member 'command'
#include "cpm_common_interfaces/msg/detail/job_mgr_reqst_channel_command__struct.h"
// Member 'data_tipoff_trigger_type'
#include "cpm_common_interfaces/msg/detail/tip_off_trigger_type__struct.h"
// Member 'data_tipoff_mode'
#include "cpm_common_interfaces/msg/detail/tip_off_state__struct.h"
// Member 'data_subtotal_info'
#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_subtotal_info__struct.h"
// Member 'requests'
#include "cpm_common_interfaces/msg/detail/lps_sa_job_mgr_reqst__struct.h"

/// Struct defined in msg/LpsSaJobMgrReqstChannel in the package cpm_common_interfaces.
/**
  * LpsSaJobMgrReqstChannelStorage
 */
typedef struct cpm_common_interfaces__msg__LpsSaJobMgrReqstChannel
{
  rosidl_runtime_c__String app_name;
  uint32_t app_request_id;
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand command;
  cpm_common_interfaces__msg__TipOffTriggerType data_tipoff_trigger_type;
  cpm_common_interfaces__msg__TipOffState data_tipoff_mode;
  uint16_t data_auto_store_pass_count;
  uint8_t data_task_number;
  bool data_enabled;
  uint8_t data_target_type;
  uint16_t data_subtotal_index;
  float data_total_target_weight;
  cpm_common_interfaces__msg__LpsSaJobMgrSubtotalInfo data_subtotal_info;
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__Sequence requests;
} cpm_common_interfaces__msg__LpsSaJobMgrReqstChannel;

// Struct for a sequence of cpm_common_interfaces__msg__LpsSaJobMgrReqstChannel.
typedef struct cpm_common_interfaces__msg__LpsSaJobMgrReqstChannel__Sequence
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqstChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LpsSaJobMgrReqstChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST_CHANNEL__STRUCT_H_
