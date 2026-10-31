// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/J1939Name.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/j1939_name.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/J1939Name in the package job_mgr_interfaces.
/**
  * J1939_NAME_t
 */
typedef struct job_mgr_interfaces__msg__J1939Name
{
  uint8_t industry_group;
  uint8_t vehicle_system;
  uint8_t vehicle_system_instance;
  uint8_t function;
  uint8_t function_instance;
  uint8_t ecu_instance;
  uint16_t manufacturer_code;
} job_mgr_interfaces__msg__J1939Name;

// Struct for a sequence of job_mgr_interfaces__msg__J1939Name.
typedef struct job_mgr_interfaces__msg__J1939Name__Sequence
{
  job_mgr_interfaces__msg__J1939Name * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__J1939Name__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__J1939_NAME__STRUCT_H_
