// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/Diagnostic.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/diagnostic.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'description'
#include "rosidl_runtime_c/string.h"
// Member 'jname'
#include "job_mgr_interfaces/msg/detail/j1939_name__struct.h"

/// Struct defined in msg/Diagnostic in the package job_mgr_interfaces.
/**
  * Diagnostic
 */
typedef struct job_mgr_interfaces__msg__Diagnostic
{
  uint16_t id;
  uint16_t cid;
  uint8_t fmi;
  uint8_t wci;
  uint8_t annunc_value;
  rosidl_runtime_c__String description;
  uint16_t subsystem;
  int64_t gps_time_sec_us;
  uint32_t service_hour_meter_sec;
  uint16_t occurrence_count;
  uint8_t category;
  uint8_t status;
  bool last_occurrence_set;
  uint16_t last_occ_duration;
  uint32_t pid;
  uint32_t worst_case_val;
  uint32_t event_trig_val;
  job_mgr_interfaces__msg__J1939Name jname;
} job_mgr_interfaces__msg__Diagnostic;

// Struct for a sequence of job_mgr_interfaces__msg__Diagnostic.
typedef struct job_mgr_interfaces__msg__Diagnostic__Sequence
{
  job_mgr_interfaces__msg__Diagnostic * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__Diagnostic__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DIAGNOSTIC__STRUCT_H_
