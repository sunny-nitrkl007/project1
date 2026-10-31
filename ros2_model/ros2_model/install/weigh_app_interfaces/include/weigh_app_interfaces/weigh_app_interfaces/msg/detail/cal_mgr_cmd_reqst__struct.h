// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/CalMgrCmdReqst.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/cal_mgr_cmd_reqst.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_REQST__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_REQST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'calibration_request'
#include "weigh_app_interfaces/msg/detail/calibration_request__struct.h"

/// Struct defined in msg/CalMgrCmdReqst in the package weigh_app_interfaces.
/**
  * CalMgrCmdReqst
 */
typedef struct weigh_app_interfaces__msg__CalMgrCmdReqst
{
  weigh_app_interfaces__msg__CalibrationRequest calibration_request;
} weigh_app_interfaces__msg__CalMgrCmdReqst;

// Struct for a sequence of weigh_app_interfaces__msg__CalMgrCmdReqst.
typedef struct weigh_app_interfaces__msg__CalMgrCmdReqst__Sequence
{
  weigh_app_interfaces__msg__CalMgrCmdReqst * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__CalMgrCmdReqst__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_REQST__STRUCT_H_
