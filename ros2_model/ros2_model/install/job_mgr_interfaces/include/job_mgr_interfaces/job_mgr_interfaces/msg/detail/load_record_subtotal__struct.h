// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/LoadRecordSubtotal.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_subtotal.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'start_time'
// Member 'end_time'
#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__struct.h"
// Member 'truck_name'
// Member 'material_name'
// Member 'custom_list_name1'
// Member 'custom_list_name2'
// Member 'custom_list_name3'
// Member 'custom_list_name4'
// Member 'tag1'
// Member 'tag2'
// Member 'tag3'
// Member 'tag4'
#include "rosidl_runtime_c/string.h"
// Member 'passes'
#include "job_mgr_interfaces/msg/detail/load_record_pass__struct.h"
// Member 'accuracy'
#include "job_mgr_interfaces/msg/detail/weigh_bkt_wt_accuracy__struct.h"

/// Struct defined in msg/LoadRecordSubtotal in the package job_mgr_interfaces.
/**
  * LpsSaLoadRecordSubtotal
 */
typedef struct job_mgr_interfaces__msg__LoadRecordSubtotal
{
  job_mgr_interfaces__msg__LoadRecordTimeStamp start_time;
  job_mgr_interfaces__msg__LoadRecordTimeStamp end_time;
  uint32_t truck_id;
  rosidl_runtime_c__String truck_name;
  float truck_target_weight_tonnes;
  uint16_t target_proportion;
  uint16_t target_passes;
  uint32_t material_id;
  rosidl_runtime_c__String material_name;
  float material_density;
  rosidl_runtime_c__String custom_list_name1;
  rosidl_runtime_c__String custom_list_name2;
  rosidl_runtime_c__String custom_list_name3;
  rosidl_runtime_c__String custom_list_name4;
  rosidl_runtime_c__String tag1;
  rosidl_runtime_c__String tag2;
  rosidl_runtime_c__String tag3;
  rosidl_runtime_c__String tag4;
  uint8_t icon_type;
  float zero_weight;
  float cal_adjust;
  job_mgr_interfaces__msg__LoadRecordPass__Sequence passes;
  float weight_tonnes;
  job_mgr_interfaces__msg__WeighBktWtAccuracy accuracy;
} job_mgr_interfaces__msg__LoadRecordSubtotal;

// Struct for a sequence of job_mgr_interfaces__msg__LoadRecordSubtotal.
typedef struct job_mgr_interfaces__msg__LoadRecordSubtotal__Sequence
{
  job_mgr_interfaces__msg__LoadRecordSubtotal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__LoadRecordSubtotal__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_SUBTOTAL__STRUCT_H_
