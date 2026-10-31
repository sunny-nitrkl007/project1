// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/LpsSaJobMgrDebugChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_job_mgr_debug_channel.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LpsSaJobMgrDebugChannel in the package job_mgr_interfaces.
/**
  * LpsSaJobMgrDebugChannelStorage
 */
typedef struct job_mgr_interfaces__msg__LpsSaJobMgrDebugChannel
{
  uint32_t current_state;
  uint32_t tipoff_assist_activation_count;
} job_mgr_interfaces__msg__LpsSaJobMgrDebugChannel;

// Struct for a sequence of job_mgr_interfaces__msg__LpsSaJobMgrDebugChannel.
typedef struct job_mgr_interfaces__msg__LpsSaJobMgrDebugChannel__Sequence
{
  job_mgr_interfaces__msg__LpsSaJobMgrDebugChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__LpsSaJobMgrDebugChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_DEBUG_CHANNEL__STRUCT_H_
