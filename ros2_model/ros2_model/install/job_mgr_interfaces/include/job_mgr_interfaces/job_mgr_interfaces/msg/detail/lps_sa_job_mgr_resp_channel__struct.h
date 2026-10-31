// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/LpsSaJobMgrRespChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_job_mgr_resp_channel.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_RESP_CHANNEL__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_RESP_CHANNEL__STRUCT_H_

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

/// Struct defined in msg/LpsSaJobMgrRespChannel in the package job_mgr_interfaces.
/**
  * LpsSaJobMgrRespChannelStorage
 */
typedef struct job_mgr_interfaces__msg__LpsSaJobMgrRespChannel
{
  rosidl_runtime_c__String app_name;
  uint32_t app_request_id;
  int64_t time_point_ns;
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand command;
  bool success;
} job_mgr_interfaces__msg__LpsSaJobMgrRespChannel;

// Struct for a sequence of job_mgr_interfaces__msg__LpsSaJobMgrRespChannel.
typedef struct job_mgr_interfaces__msg__LpsSaJobMgrRespChannel__Sequence
{
  job_mgr_interfaces__msg__LpsSaJobMgrRespChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__LpsSaJobMgrRespChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_RESP_CHANNEL__STRUCT_H_
