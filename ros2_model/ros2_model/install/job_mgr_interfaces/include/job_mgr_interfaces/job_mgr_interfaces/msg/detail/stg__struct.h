// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/STG.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/stg.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__STG__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__STG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'OPEN'.
enum
{
  job_mgr_interfaces__msg__STG__OPEN = 0
};

/// Constant 'CLOSED'.
enum
{
  job_mgr_interfaces__msg__STG__CLOSED = 1
};

/// Constant 'UNKNOWN'.
enum
{
  job_mgr_interfaces__msg__STG__UNKNOWN = 2
};

/// Struct defined in msg/STG in the package job_mgr_interfaces.
/**
  * STG
 */
typedef struct job_mgr_interfaces__msg__STG
{
  uint8_t value;
} job_mgr_interfaces__msg__STG;

// Struct for a sequence of job_mgr_interfaces__msg__STG.
typedef struct job_mgr_interfaces__msg__STG__Sequence
{
  job_mgr_interfaces__msg__STG * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__STG__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__STG__STRUCT_H_
