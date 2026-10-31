// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/SimpleCalData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/simple_cal_data.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'time_stamp'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/SimpleCalData in the package job_mgr_interfaces.
/**
  * SimpleCalData_t
 */
typedef struct job_mgr_interfaces__msg__SimpleCalData
{
  rosidl_runtime_c__String time_stamp;
  float truck_wt;
  float zeroed_truck_wt;
} job_mgr_interfaces__msg__SimpleCalData;

// Struct for a sequence of job_mgr_interfaces__msg__SimpleCalData.
typedef struct job_mgr_interfaces__msg__SimpleCalData__Sequence
{
  job_mgr_interfaces__msg__SimpleCalData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__SimpleCalData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA__STRUCT_H_
