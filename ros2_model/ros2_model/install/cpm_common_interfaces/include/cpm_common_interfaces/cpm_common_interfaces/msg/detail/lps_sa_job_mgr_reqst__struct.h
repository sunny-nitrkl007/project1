// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LpsSaJobMgrReqst.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_job_mgr_reqst.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'WRITE_MATERIAL_ID'.
enum
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__WRITE_MATERIAL_ID = 0
};

/// Constant 'WRITE_MATERIAL_NAME'.
enum
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__WRITE_MATERIAL_NAME = 1
};

/// Constant 'WRITE_MATERIAL_DENSITY'.
enum
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__WRITE_MATERIAL_DENSITY = 2
};

/// Constant 'WRITE_TRUCK_ID'.
enum
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__WRITE_TRUCK_ID = 3
};

/// Constant 'WRITE_TRUCK_NAME'.
enum
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__WRITE_TRUCK_NAME = 4
};

/// Constant 'WRITE_TRUCK_TARGET_WEIGHT'.
enum
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__WRITE_TRUCK_TARGET_WEIGHT = 5
};

/// Constant 'WRITE_TAG1'.
enum
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__WRITE_TAG1 = 6
};

/// Constant 'WRITE_TAG2'.
enum
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__WRITE_TAG2 = 7
};

/// Constant 'WRITE_TAG3'.
enum
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__WRITE_TAG3 = 8
};

/// Constant 'WRITE_TAG4'.
enum
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__WRITE_TAG4 = 9
};

/// Constant 'NONE'.
enum
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst__NONE = 10
};

// Include directives for member types
// Member 'arg1'
// Member 'arg4'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/LpsSaJobMgrReqst in the package cpm_common_interfaces.
/**
  * LpsSaJobMgrReqstCommand
 */
typedef struct cpm_common_interfaces__msg__LpsSaJobMgrReqst
{
  /// LpsSaJobMgrReqst
  uint8_t command;
  rosidl_runtime_c__String arg1;
  float arg2;
  uint32_t arg3;
  rosidl_runtime_c__String arg4;
} cpm_common_interfaces__msg__LpsSaJobMgrReqst;

// Struct for a sequence of cpm_common_interfaces__msg__LpsSaJobMgrReqst.
typedef struct cpm_common_interfaces__msg__LpsSaJobMgrReqst__Sequence
{
  cpm_common_interfaces__msg__LpsSaJobMgrReqst * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LpsSaJobMgrReqst__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_JOB_MGR_REQST__STRUCT_H_
