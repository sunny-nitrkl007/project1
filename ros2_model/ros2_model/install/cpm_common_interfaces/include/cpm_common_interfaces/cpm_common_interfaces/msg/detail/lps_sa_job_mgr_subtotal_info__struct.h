// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrSubtotalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_subtotal_info.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'subtotal_command'
// Member 'material_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/LpsSaJobMgrSubtotalInfo in the package cpm_common_interfaces.
/**
  * LpsSaJobMgrReqstChannelStorage::LpsSaJobMgrSubtotalInfo_t
 */
typedef struct cpm_common_interfaces__msg__LpsSaJobMgrSubtotalInfo
{
  rosidl_runtime_c__String subtotal_command;
  uint16_t current_step_number;
  uint16_t new_step_number;
  float target_weight;
  uint16_t target_proportion;
  uint16_t target_passes;
  uint32_t material_id;
  rosidl_runtime_c__String material_name;
  float material_density;
  uint8_t icon_type;
} cpm_common_interfaces__msg__LpsSaJobMgrSubtotalInfo;

// Struct for a sequence of cpm_common_interfaces__msg__LpsSaJobMgrSubtotalInfo.
typedef struct cpm_common_interfaces__msg__LpsSaJobMgrSubtotalInfo__Sequence
{
  cpm_common_interfaces__msg__LpsSaJobMgrSubtotalInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LpsSaJobMgrSubtotalInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_SUBTOTAL_INFO__STRUCT_H_
