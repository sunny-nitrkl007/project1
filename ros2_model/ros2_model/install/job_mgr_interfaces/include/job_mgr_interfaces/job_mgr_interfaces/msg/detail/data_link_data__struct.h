// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/DataLinkData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/data_link_data.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'params'
#include "job_mgr_interfaces/msg/detail/data_link_param__struct.h"

/// Struct defined in msg/DataLinkData in the package job_mgr_interfaces.
/**
  * DataLinkData
 */
typedef struct job_mgr_interfaces__msg__DataLinkData
{
  job_mgr_interfaces__msg__DataLinkParam__Sequence params;
} job_mgr_interfaces__msg__DataLinkData;

// Struct for a sequence of job_mgr_interfaces__msg__DataLinkData.
typedef struct job_mgr_interfaces__msg__DataLinkData__Sequence
{
  job_mgr_interfaces__msg__DataLinkData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__DataLinkData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__STRUCT_H_
