// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from job_mgr_interfaces:msg/LpsSaLoadRecordChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/lps_sa_load_record_channel.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__STRUCT_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'STORE_ACTION_AUTO'.
enum
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel__STORE_ACTION_AUTO = 0
};

/// Constant 'STORE_ACTION_EXTERNAL'.
enum
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel__STORE_ACTION_EXTERNAL = 1
};

/// Constant 'STORE_ACTION_UI'.
enum
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel__STORE_ACTION_UI = 2
};

/// Constant 'STORE_ACTION_TICKET_NOT_FOR_TRADE'.
enum
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel__STORE_ACTION_TICKET_NOT_FOR_TRADE = 3
};

/// Constant 'STORE_ACTION_TICKET_LEGAL_FOR_TRADE'.
enum
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel__STORE_ACTION_TICKET_LEGAL_FOR_TRADE = 4
};

/// Constant 'TARGET_TYPE_SINGLE'.
/**
  * LpsSaLoadRecordTargetType
 */
enum
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel__TARGET_TYPE_SINGLE = 0
};

/// Constant 'TARGET_TYPE_SPLIT'.
enum
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel__TARGET_TYPE_SPLIT = 1
};

/// Constant 'TARGET_TYPE_BATCH'.
enum
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel__TARGET_TYPE_BATCH = 2
};

/// Constant 'TARGET_TYPE_MIX'.
enum
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel__TARGET_TYPE_MIX = 3
};

/// Constant 'TARGET_TYPE_BLEND_LOADS'.
enum
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel__TARGET_TYPE_BLEND_LOADS = 4
};

/// Constant 'TARGET_TYPE_BLEND_WEIGHT'.
enum
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel__TARGET_TYPE_BLEND_WEIGHT = 5
};

// Include directives for member types
// Member 'subtotal'
// Member 'subtotals'
#include "job_mgr_interfaces/msg/detail/load_record_subtotal__struct.h"
// Member 'ticket_id'
// Member 'product_id'
// Member 'equipment_id'
// Member 'recipe_name'
#include "rosidl_runtime_c/string.h"
// Member 'store_time'
#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__struct.h"

/// Struct defined in msg/LpsSaLoadRecordChannel in the package job_mgr_interfaces.
/**
  * LpsSaLoadRecordStoreAction
 */
typedef struct job_mgr_interfaces__msg__LpsSaLoadRecordChannel
{
  /// LpsSaLoadRecordChannelStorage
  uint8_t store_action;
  job_mgr_interfaces__msg__LoadRecordSubtotal subtotal;
  job_mgr_interfaces__msg__LoadRecordSubtotal__Sequence subtotals;
  uint32_t ticket_number;
  rosidl_runtime_c__String ticket_id;
  rosidl_runtime_c__String product_id;
  rosidl_runtime_c__String equipment_id;
  float weight_interval;
  int32_t weight_decimal_precision;
  int32_t weight_units;
  rosidl_runtime_c__String recipe_name;
  uint8_t target_type;
  float total_target_weight;
  uint16_t current_subtotal_index;
  job_mgr_interfaces__msg__LoadRecordTimeStamp store_time;
} job_mgr_interfaces__msg__LpsSaLoadRecordChannel;

// Struct for a sequence of job_mgr_interfaces__msg__LpsSaLoadRecordChannel.
typedef struct job_mgr_interfaces__msg__LpsSaLoadRecordChannel__Sequence
{
  job_mgr_interfaces__msg__LpsSaLoadRecordChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} job_mgr_interfaces__msg__LpsSaLoadRecordChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LPS_SA_LOAD_RECORD_CHANNEL__STRUCT_H_
