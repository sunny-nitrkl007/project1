// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/LoadRecordTimeStamp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_time_stamp.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/LoadRecordTimeStamp in the package job_mgr_interfaces.
/**
  * LpsSaLoadRecordTimeStamp
 */
typedef struct job_mgr_interfaces__msg__LoadRecordTimeStamp
{
  int64_t utc_time_ns;
  uint32_t shm_time;
} job_mgr_interfaces__msg__LoadRecordTimeStamp;

// Struct for a sequence of job_mgr_interfaces__msg__LoadRecordTimeStamp.
typedef struct job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence
{
  job_mgr_interfaces__msg__LoadRecordTimeStamp * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__STRUCT_H_
