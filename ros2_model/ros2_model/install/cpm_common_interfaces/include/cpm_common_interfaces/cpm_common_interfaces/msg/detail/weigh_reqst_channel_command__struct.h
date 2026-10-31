// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/WeighReqstChannelCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/weigh_reqst_channel_command.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_REQST_CHANNEL_COMMAND__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_REQST_CHANNEL_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'NONE'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__NONE = 0
};

/// Constant 'WRITE_OVERLOAD_WARNING_ENABLE'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_OVERLOAD_WARNING_ENABLE = 1
};

/// Constant 'WRITE_BUCKET_PAYLOAD_TARGET_WEIGHT'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_BUCKET_PAYLOAD_TARGET_WEIGHT = 2
};

/// Constant 'ZERO'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__ZERO = 3
};

/// Constant 'RESET_BEST_BUCKET_WEIGHT'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__RESET_BEST_BUCKET_WEIGHT = 4
};

/// Constant 'CAPTURE_CYLINDER_EXTENSION_REFERENCE'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__CAPTURE_CYLINDER_EXTENSION_REFERENCE = 5
};

/// Constant 'CLEAR_REWEIGH_WARNING'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__CLEAR_REWEIGH_WARNING = 6
};

/// Constant 'WRITE_WEIGH_RANGE'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_WEIGH_RANGE = 7
};

/// Constant 'WRITE_CALIBRATION_WEIGHT'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_CALIBRATION_WEIGHT = 8
};

/// Constant 'WRITE_MACHINE_PITCH_CAL_OFFSET'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_MACHINE_PITCH_CAL_OFFSET = 9
};

/// Constant 'WRITE_HYD_OIL_TEMP_ENABLE'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_HYD_OIL_TEMP_ENABLE = 10
};

/// Constant 'WRITE_AUDIBLE_WEIGHT_ENABLE'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_AUDIBLE_WEIGHT_ENABLE = 11
};

/// Constant 'WRITE_LFT_SEALED'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_LFT_SEALED = 12
};

/// Constant 'WRITE_LFT_SEALED_FLASH_ENABLE'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_LFT_SEALED_FLASH_ENABLE = 13
};

/// Constant 'WRITE_LIFT_POSITION_SENSOR_ID'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_LIFT_POSITION_SENSOR_ID = 14
};

/// Constant 'WRITE_TILT_POSITION_SENSOR_ID'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_TILT_POSITION_SENSOR_ID = 15
};

/// Constant 'WRITE_LIFT_HE_PRESSURE_SENSOR_ID'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_LIFT_HE_PRESSURE_SENSOR_ID = 16
};

/// Constant 'WRITE_LIFT_RE_PRESSURE_SENSOR_ID'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_LIFT_RE_PRESSURE_SENSOR_ID = 17
};

/// Constant 'WRITE_HYDRAULIC_OIL_TEMP_SENSOR_ID'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_HYDRAULIC_OIL_TEMP_SENSOR_ID = 18
};

/// Constant 'WRITE_PAYLOAD_OUT_OF_CAL'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_PAYLOAD_OUT_OF_CAL = 19
};

/// Constant 'NOTIFY_TICKET_NUMBER_WRITE'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__NOTIFY_TICKET_NUMBER_WRITE = 20
};

/// Constant 'PUBLISH_SERVICE_HISTORY'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__PUBLISH_SERVICE_HISTORY = 21
};

/// Constant 'WRITE_WORK_TOOL_ID'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_WORK_TOOL_ID = 22
};

/// Constant 'PUBLISH_LIFT_SENSOR_CALIBRATION'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__PUBLISH_LIFT_SENSOR_CALIBRATION = 23
};

/// Constant 'PUBLISH_TILT_SENSOR_CALIBRATION'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__PUBLISH_TILT_SENSOR_CALIBRATION = 24
};

/// Constant 'PUBLISH_WEIGH_CALIBRATION'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__PUBLISH_WEIGH_CALIBRATION = 25
};

/// Constant 'PUBLISH_WEIGH_CONFIGURATION'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__PUBLISH_WEIGH_CONFIGURATION = 26
};

/// Constant 'PUBLISH_RECENT_WEIGH_RESULTS'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__PUBLISH_RECENT_WEIGH_RESULTS = 27
};

/// Constant 'WRITE_REWEIGH_MAX_PITCH'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_REWEIGH_MAX_PITCH = 28
};

/// Constant 'WRITE_REWEIGH_MIN_PITCH'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_REWEIGH_MIN_PITCH = 29
};

/// Constant 'WRITE_REWEIGH_MAX_ABS_ROLL'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_REWEIGH_MAX_ABS_ROLL = 30
};

/// Constant 'WRITE_REWEIGH_MIN_LIFT_CYL_VEL'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_REWEIGH_MIN_LIFT_CYL_VEL = 31
};

/// Constant 'WRITE_ADVANCED_CALIBRATION_ADJUSTMENT'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_ADVANCED_CALIBRATION_ADJUSTMENT = 32
};

/// Constant 'RUN_TEST'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__RUN_TEST = 33
};

/// Constant 'RECORD_TEST'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__RECORD_TEST = 34
};

/// Constant 'WRITE_IMU_COMP_ENABLE'.
enum
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand__WRITE_IMU_COMP_ENABLE = 35
};

/// Struct defined in msg/WeighReqstChannelCommand in the package cpm_common_interfaces.
/**
  * LpsSaWeighReqstChannelStorage::Command
 */
typedef struct cpm_common_interfaces__msg__WeighReqstChannelCommand
{
  uint8_t value;
} cpm_common_interfaces__msg__WeighReqstChannelCommand;

// Struct for a sequence of cpm_common_interfaces__msg__WeighReqstChannelCommand.
typedef struct cpm_common_interfaces__msg__WeighReqstChannelCommand__Sequence
{
  cpm_common_interfaces__msg__WeighReqstChannelCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__WeighReqstChannelCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_REQST_CHANNEL_COMMAND__STRUCT_H_
