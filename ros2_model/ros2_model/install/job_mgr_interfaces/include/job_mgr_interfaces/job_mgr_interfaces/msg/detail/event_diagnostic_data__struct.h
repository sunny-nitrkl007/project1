// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/EventDiagnosticData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/event_diagnostic_data.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'dnsname'
// Member 'source'
#include "rosidl_runtime_c/string.h"
// Member 'active_diagnostics'
#include "job_mgr_interfaces/msg/detail/diagnostic__struct.h"

/// Struct defined in msg/EventDiagnosticData in the package job_mgr_interfaces.
/**
  * EventDiagnosticDataStorage
 */
typedef struct job_mgr_interfaces__msg__EventDiagnosticData
{
  rosidl_runtime_c__String dnsname;
  job_mgr_interfaces__msg__Diagnostic__Sequence active_diagnostics;
  uint32_t payload_crc;
  int64_t payload_last_update_time_us;
  uint8_t highest_warning_level;
  uint8_t highest_annunciation_level;
  rosidl_runtime_c__String source;
} job_mgr_interfaces__msg__EventDiagnosticData;

// Struct for a sequence of job_mgr_interfaces__msg__EventDiagnosticData.
typedef struct job_mgr_interfaces__msg__EventDiagnosticData__Sequence
{
  job_mgr_interfaces__msg__EventDiagnosticData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__EventDiagnosticData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__EVENT_DIAGNOSTIC_DATA__STRUCT_H_
