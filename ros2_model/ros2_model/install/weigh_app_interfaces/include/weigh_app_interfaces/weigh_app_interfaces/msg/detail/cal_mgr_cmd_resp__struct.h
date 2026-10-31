// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/CalMgrCmdResp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/cal_mgr_cmd_resp.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'calibration_resp'
#include "weigh_app_interfaces/msg/detail/cal_mgr_calibration_resp__struct.h"

/// Struct defined in msg/CalMgrCmdResp in the package weigh_app_interfaces.
/**
  * CalMgrCmdResp
 */
typedef struct weigh_app_interfaces__msg__CalMgrCmdResp
{
  weigh_app_interfaces__msg__CalMgrCalibrationResp calibration_resp;
} weigh_app_interfaces__msg__CalMgrCmdResp;

// Struct for a sequence of weigh_app_interfaces__msg__CalMgrCmdResp.
typedef struct weigh_app_interfaces__msg__CalMgrCmdResp__Sequence
{
  weigh_app_interfaces__msg__CalMgrCmdResp * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__CalMgrCmdResp__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CMD_RESP__STRUCT_H_
