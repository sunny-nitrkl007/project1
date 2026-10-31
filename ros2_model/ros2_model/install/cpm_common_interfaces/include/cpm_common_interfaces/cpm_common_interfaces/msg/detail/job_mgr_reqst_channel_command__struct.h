// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/JobMgrReqstChannelCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/job_mgr_reqst_channel_command.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__STRUCT_H_

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
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__NONE = 0
};

/// Constant 'ZERO'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__ZERO = 1
};

/// Constant 'MINUS_ONE'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__MINUS_ONE = 2
};

/// Constant 'CLEAR'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__CLEAR = 3
};

/// Constant 'STORE'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__STORE = 4
};

/// Constant 'REWEIGH'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__REWEIGH = 5
};

/// Constant 'MANUAL_ADD'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__MANUAL_ADD = 6
};

/// Constant 'STANDBY_ACTIVATE'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__STANDBY_ACTIVATE = 7
};

/// Constant 'STANDBY_DEACTIVATE'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__STANDBY_DEACTIVATE = 8
};

/// Constant 'TIPOFF_MODE_TOGGLE'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__TIPOFF_MODE_TOGGLE = 9
};

/// Constant 'MANUAL_TIPOFF_ACTIVATE'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__MANUAL_TIPOFF_ACTIVATE = 10
};

/// Constant 'MANUAL_TIPOFF_DEACTIVATE'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__MANUAL_TIPOFF_DEACTIVATE = 11
};

/// Constant 'WRITE_TIPOFF_TRIGGER_TYPE'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_TIPOFF_TRIGGER_TYPE = 12
};

/// Constant 'WRITE_TIPOFF_MODE'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_TIPOFF_MODE = 13
};

/// Constant 'WRITE_HORN_ON_STORE_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_HORN_ON_STORE_ENABLED = 14
};

/// Constant 'WRITE_AUTO_STORE_PASS_COUNT'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_AUTO_STORE_PASS_COUNT = 15
};

/// Constant 'WRITE_AUTO_TRUCK_ID_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_AUTO_TRUCK_ID_ENABLED = 16
};

/// Constant 'WRITE_AUTO_MATERIAL_ID_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_AUTO_MATERIAL_ID_ENABLED = 17
};

/// Constant 'WRITE_MANUAL_ADD_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_MANUAL_ADD_ENABLED = 18
};

/// Constant 'WRITE_MULTI_TASK_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_MULTI_TASK_ENABLED = 19
};

/// Constant 'WRITE_MULTI_TASK_COUNT'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_MULTI_TASK_COUNT = 20
};

/// Constant 'WRITE_SPLIT_MODE_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_SPLIT_MODE_ENABLED = 21
};

/// Constant 'SELECT_TASK'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__SELECT_TASK = 22
};

/// Constant 'SELECT_NEXT_TASK'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__SELECT_NEXT_TASK = 23
};

/// Constant 'SELECT_PREVIOUS_TASK'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__SELECT_PREVIOUS_TASK = 24
};

/// Constant 'WRITE_TRUCK_LIST_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_TRUCK_LIST_ENABLED = 25
};

/// Constant 'WRITE_MATERIAL_LIST_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_MATERIAL_LIST_ENABLED = 26
};

/// Constant 'WRITE_TAG1_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_TAG1_ENABLED = 27
};

/// Constant 'WRITE_TAG2_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_TAG2_ENABLED = 28
};

/// Constant 'WRITE_TAG3_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_TAG3_ENABLED = 29
};

/// Constant 'WRITE_TAG4_ENABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_TAG4_ENABLED = 30
};

/// Constant 'WRITE_PAYLOAD_NEXT_SUBTOTAL'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_PAYLOAD_NEXT_SUBTOTAL = 31
};

/// Constant 'WRITE_LFT_DISABLED'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_LFT_DISABLED = 32
};

/// Constant 'WRITE_TARGET_TYPE'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_TARGET_TYPE = 33
};

/// Constant 'WRITE_TOTAL_TARGET_WEIGHT'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_TOTAL_TARGET_WEIGHT = 34
};

/// Constant 'SELECT_SUBTOTAL'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__SELECT_SUBTOTAL = 35
};

/// Constant 'PAYLOAD_DETAILS_FILE_REQUEST'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__PAYLOAD_DETAILS_FILE_REQUEST = 36
};

/// Constant 'WRITE_SUBTOTAL_INFO'.
enum
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand__WRITE_SUBTOTAL_INFO = 37
};

/// Struct defined in msg/JobMgrReqstChannelCommand in the package cpm_common_interfaces.
/**
  * LpsSaJobMgrReqstChannelStorage::Command
 */
typedef struct cpm_common_interfaces__msg__JobMgrReqstChannelCommand
{
  uint8_t value;
} cpm_common_interfaces__msg__JobMgrReqstChannelCommand;

// Struct for a sequence of cpm_common_interfaces__msg__JobMgrReqstChannelCommand.
typedef struct cpm_common_interfaces__msg__JobMgrReqstChannelCommand__Sequence
{
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__JobMgrReqstChannelCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__STRUCT_H_
