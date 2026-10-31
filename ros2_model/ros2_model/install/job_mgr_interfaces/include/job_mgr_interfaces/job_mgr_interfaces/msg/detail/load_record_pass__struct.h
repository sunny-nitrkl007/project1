// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/LoadRecordPass.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_pass.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'time'
#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__struct.h"

/// Struct defined in msg/LoadRecordPass in the package job_mgr_interfaces.
/**
  * LpsSaLoadRecordPass
 */
typedef struct job_mgr_interfaces__msg__LoadRecordPass
{
  float weight_tonnes;
  uint16_t calc_method;
  job_mgr_interfaces__msg__LoadRecordTimeStamp time;
} job_mgr_interfaces__msg__LoadRecordPass;

// Struct for a sequence of job_mgr_interfaces__msg__LoadRecordPass.
typedef struct job_mgr_interfaces__msg__LoadRecordPass__Sequence
{
  job_mgr_interfaces__msg__LoadRecordPass * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__LoadRecordPass__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_PASS__STRUCT_H_
