// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/OutputChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/output_channel.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'commands'
#include "job_mgr_interfaces/msg/detail/output_cmd__struct.h"

/// Struct defined in msg/OutputChannel in the package job_mgr_interfaces.
/**
  * OutputChannel
 */
typedef struct job_mgr_interfaces__msg__OutputChannel
{
  job_mgr_interfaces__msg__OutputCmd__Sequence commands;
} job_mgr_interfaces__msg__OutputChannel;

// Struct for a sequence of job_mgr_interfaces__msg__OutputChannel.
typedef struct job_mgr_interfaces__msg__OutputChannel__Sequence
{
  job_mgr_interfaces__msg__OutputChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__OutputChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__OUTPUT_CHANNEL__STRUCT_H_
