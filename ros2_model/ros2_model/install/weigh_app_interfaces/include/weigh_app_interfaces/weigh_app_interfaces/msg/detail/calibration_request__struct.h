// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/CalibrationRequest.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/calibration_request.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'cal_iterm'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/CalibrationRequest in the package weigh_app_interfaces.
/**
  * CalMgrCmdReqst::CalibrationRequest
 */
typedef struct weigh_app_interfaces__msg__CalibrationRequest
{
  uint16_t src;
  uint16_t dest;
  bool calibration_reqst_flag;
  uint8_t calcmd;
  uint16_t cal_id;
  rosidl_runtime_c__uint32__Sequence cal_iterm;
} weigh_app_interfaces__msg__CalibrationRequest;

// Struct for a sequence of weigh_app_interfaces__msg__CalibrationRequest.
typedef struct weigh_app_interfaces__msg__CalibrationRequest__Sequence
{
  weigh_app_interfaces__msg__CalibrationRequest * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__CalibrationRequest__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CALIBRATION_REQUEST__STRUCT_H_
