// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/OutputCmd.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/output_cmd.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/OutputCmd in the package job_mgr_interfaces.
/**
  * OutputChannel::OutputCmd
 */
typedef struct job_mgr_interfaces__msg__OutputCmd
{
  uint8_t output_port;
  uint8_t initial_state;
  uint8_t state_change_duration;
  uint8_t final_state;
  int32_t total_duration;
} job_mgr_interfaces__msg__OutputCmd;

// Struct for a sequence of job_mgr_interfaces__msg__OutputCmd.
typedef struct job_mgr_interfaces__msg__OutputCmd__Sequence
{
  job_mgr_interfaces__msg__OutputCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__OutputCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CMD__STRUCT_H_
