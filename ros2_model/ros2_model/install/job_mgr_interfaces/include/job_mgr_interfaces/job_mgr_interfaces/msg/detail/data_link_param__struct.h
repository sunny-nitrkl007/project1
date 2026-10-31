// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/DataLinkParam.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/data_link_param.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/DataLinkParam in the package job_mgr_interfaces.
/**
  * DataLinkParam
 */
typedef struct job_mgr_interfaces__msg__DataLinkParam
{
  uint32_t param_id;
  uint8_t identifier_type;
  bool pid_data_received;
  uint16_t last_value_dsi;
  uint8_t last_good_value_u8;
  uint16_t last_good_value_u16;
  double last_value_eng;
} job_mgr_interfaces__msg__DataLinkParam;

// Struct for a sequence of job_mgr_interfaces__msg__DataLinkParam.
typedef struct job_mgr_interfaces__msg__DataLinkParam__Sequence
{
  job_mgr_interfaces__msg__DataLinkParam * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__DataLinkParam__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_H_
