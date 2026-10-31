// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/CalMgrCalibrationResp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/cal_mgr_calibration_resp.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'RESP_CAL_SUCCESS'.
enum
{
  weigh_app_interfaces__msg__CalMgrCalibrationResp__RESP_CAL_SUCCESS = 0
};

/// Constant 'RESP_CAL_FAIL'.
enum
{
  weigh_app_interfaces__msg__CalMgrCalibrationResp__RESP_CAL_FAIL = 1
};

/// Constant 'RESP_CAL_UNKNOWN'.
enum
{
  weigh_app_interfaces__msg__CalMgrCalibrationResp__RESP_CAL_UNKNOWN = 2
};

/// Struct defined in msg/CalMgrCalibrationResp in the package weigh_app_interfaces.
/**
  * CalRespCode_t
 */
typedef struct weigh_app_interfaces__msg__CalMgrCalibrationResp
{
  /// CalMgrCmdResp::CalibrationResp
  uint8_t resp_code;
  uint8_t cal_resp;
  uint8_t step_no;
  uint16_t error;
  uint16_t warning;
  bool enable_qual_read;
} weigh_app_interfaces__msg__CalMgrCalibrationResp;

// Struct for a sequence of weigh_app_interfaces__msg__CalMgrCalibrationResp.
typedef struct weigh_app_interfaces__msg__CalMgrCalibrationResp__Sequence
{
  weigh_app_interfaces__msg__CalMgrCalibrationResp * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__CalMgrCalibrationResp__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CAL_MGR_CALIBRATION_RESP__STRUCT_H_
