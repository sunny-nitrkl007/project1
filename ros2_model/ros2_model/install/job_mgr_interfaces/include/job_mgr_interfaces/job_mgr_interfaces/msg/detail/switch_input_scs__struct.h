// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/SwitchInputScs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/switch_input_scs.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'stg_values'
#include "job_mgr_interfaces/msg/detail/stg__struct.h"

/// Struct defined in msg/SwitchInputScs in the package job_mgr_interfaces.
/**
  * SwitchInputScsStorage
 */
typedef struct job_mgr_interfaces__msg__SwitchInputScs
{
  job_mgr_interfaces__msg__STG stg_values[4];
} job_mgr_interfaces__msg__SwitchInputScs;

// Struct for a sequence of job_mgr_interfaces__msg__SwitchInputScs.
typedef struct job_mgr_interfaces__msg__SwitchInputScs__Sequence
{
  job_mgr_interfaces__msg__SwitchInputScs * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__SwitchInputScs__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__SWITCH_INPUT_SCS__STRUCT_H_
