// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/DispBestBktWt.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/disp_best_bkt_wt.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DISP_BEST_BKT_WT__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DISP_BEST_BKT_WT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/DispBestBktWt in the package job_mgr_interfaces.
/**
  * Wire equivalent of DispBestBktWt_t.
  * Source: CPM-Loader-ais/prod/common/interfaces/LpsSaJobMgrTxChannel/LpsSaJobMgrTxChannel.h:62-65
  *   typedef struct {
  *       float val;
  *       bool isOk;
  *   } DispBestBktWt_t;
 */
typedef struct job_mgr_interfaces__msg__DispBestBktWt
{
  float val;
  bool is_ok;
} job_mgr_interfaces__msg__DispBestBktWt;

// Struct for a sequence of job_mgr_interfaces__msg__DispBestBktWt.
typedef struct job_mgr_interfaces__msg__DispBestBktWt__Sequence
{
  job_mgr_interfaces__msg__DispBestBktWt * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__DispBestBktWt__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DISP_BEST_BKT_WT__STRUCT_H_
