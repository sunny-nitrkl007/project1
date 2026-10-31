// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/WeighBktWtAccuracy.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/weigh_bkt_wt_accuracy.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'NONE'.
enum
{
  job_mgr_interfaces__msg__WeighBktWtAccuracy__NONE = 0
};

/// Constant 'LOW'.
enum
{
  job_mgr_interfaces__msg__WeighBktWtAccuracy__LOW = 1
};

/// Constant 'MED'.
enum
{
  job_mgr_interfaces__msg__WeighBktWtAccuracy__MED = 2
};

/// Constant 'HIGH'.
enum
{
  job_mgr_interfaces__msg__WeighBktWtAccuracy__HIGH = 3
};

/// Struct defined in msg/WeighBktWtAccuracy in the package job_mgr_interfaces.
/**
  * LpsWeighBktWtAccuracy_t
 */
typedef struct job_mgr_interfaces__msg__WeighBktWtAccuracy
{
  uint8_t value;
} job_mgr_interfaces__msg__WeighBktWtAccuracy;

// Struct for a sequence of job_mgr_interfaces__msg__WeighBktWtAccuracy.
typedef struct job_mgr_interfaces__msg__WeighBktWtAccuracy__Sequence
{
  job_mgr_interfaces__msg__WeighBktWtAccuracy * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__WeighBktWtAccuracy__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__WEIGH_BKT_WT_ACCURACY__STRUCT_H_
