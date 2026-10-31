// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/WeighPidData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/weigh_pid_data.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'ZERO_STAT_ZEROED'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__ZERO_STAT_ZEROED = 916
};

/// Constant 'ZERO_STAT_NOT_ZEROED'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__ZERO_STAT_NOT_ZEROED = 917
};

/// Constant 'CAL_WT_ENTRY_REQUIRED'.
/**
  * PloadSysCalWtEntryReqStat_t
 */
enum
{
  cpm_common_interfaces__msg__WeighPidData__CAL_WT_ENTRY_REQUIRED = 26
};

/// Constant 'CAL_WT_ENTRY_NOT_REQUIRED'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__CAL_WT_ENTRY_NOT_REQUIRED = 27
};

/// Constant 'WEIGH_STATUS_BIT_LOWER_STALL'.
/**
  * ACDWeighStatus::type
 */
enum
{
  cpm_common_interfaces__msg__WeighPidData__WEIGH_STATUS_BIT_LOWER_STALL = 7
};

/// Constant 'WEIGH_STATUS_BIT_RAISE_STALL'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__WEIGH_STATUS_BIT_RAISE_STALL = 8
};

/// Constant 'WEIGH_STATUS_BIT_INSUFFICIENT_DATA'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__WEIGH_STATUS_BIT_INSUFFICIENT_DATA = 9
};

/// Constant 'WEIGH_STATUS_BIT_REWEIGH_PRESSURE_CHANGING'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__WEIGH_STATUS_BIT_REWEIGH_PRESSURE_CHANGING = 10
};

/// Constant 'WEIGH_STATUS_BIT_REWEIGH_INCONSISTENT'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__WEIGH_STATUS_BIT_REWEIGH_INCONSISTENT = 11
};

/// Constant 'WEIGH_STATUS_BIT_REWEIGH_SPEED_CHANGING'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__WEIGH_STATUS_BIT_REWEIGH_SPEED_CHANGING = 12
};

/// Constant 'WEIGH_STATUS_BIT_REWEIGH_NOT_RACKED_EXCESSIVE_PITCH'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__WEIGH_STATUS_BIT_REWEIGH_NOT_RACKED_EXCESSIVE_PITCH = 13
};

/// Constant 'WEIGH_STATUS_BIT_REWEIGH_STOPPED_IN_RANGE'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__WEIGH_STATUS_BIT_REWEIGH_STOPPED_IN_RANGE = 14
};

/// Constant 'WEIGH_STATUS_BIT_REWEIGH_LIFT_TOO_SLOW'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__WEIGH_STATUS_BIT_REWEIGH_LIFT_TOO_SLOW = 15
};

/// Constant 'BKT_PAYLOAD_NOT_AVAILABLE'.
/**
  * BktPayloadData_t
 */
enum
{
  cpm_common_interfaces__msg__WeighPidData__BKT_PAYLOAD_NOT_AVAILABLE = 0
};

/// Constant 'BKT_PAYLOAD_AVAILABLE'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__BKT_PAYLOAD_AVAILABLE = 1
};

/// Constant 'BKT_PAYLOAD_STORED'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__BKT_PAYLOAD_STORED = 2
};

/// Constant 'BKT_PAYLOAD_NOT_INSTALLED'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__BKT_PAYLOAD_NOT_INSTALLED = 244
};

/// Constant 'TONE_NONE'.
/**
  * AudibleAnnunciationPriority_t
 */
enum
{
  cpm_common_interfaces__msg__WeighPidData__TONE_NONE = 0
};

/// Constant 'TONE_CONFIRMATION'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__TONE_CONFIRMATION = 2
};

/// Constant 'TONE_ATTENTION'.
enum
{
  cpm_common_interfaces__msg__WeighPidData__TONE_ATTENTION = 6
};

// Include directives for member types
// Member 'prod_measure_sensor_status'
#include "cpm_common_interfaces/msg/detail/prod_measure_sensor_status__struct.h"
// Member 'link_sensor_cal_lim'
#include "cpm_common_interfaces/msg/detail/link_sensor_cal_lim__struct.h"

/// Struct defined in msg/WeighPidData in the package cpm_common_interfaces.
/**
  * PloadSysZeroStat_t
 */
typedef struct cpm_common_interfaces__msg__WeighPidData
{
  /// WeighPidData_t
  uint16_t pload_sys_zero_stat;
  uint16_t ldr_payload_stat;
  bool overload_warning_enabled;
  cpm_common_interfaces__msg__ProdMeasureSensorStatus prod_measure_sensor_status;
  cpm_common_interfaces__msg__LinkSensorCalLim link_sensor_cal_lim;
  float loader_bkt_pload_tgt_wt;
  float loader_bkt_pload_tgt_wt_per;
  uint16_t pload_sys_zero_req_stat;
  uint16_t pload_sys_cal_wt_entry_req_stat;
  float last_pload_wt;
  uint16_t prod_measure_weigh_status;
  uint8_t bkt_payload_data;
  int16_t qr_hyd_oil_temp_min_c;
  int16_t qr_lift_cyl_vel_min_mm_sec;
  int16_t qr_lift_cyl_vel_max_mm_sec;
  int16_t machine_rear_lateral_acceleration;
  int16_t machine_rear_longitudinal_acceleration;
  int16_t machine_rear_vertical_acceleration;
  int16_t machine_pitch;
  int16_t machine_slope;
  int16_t machine_rear_roll;
  int16_t machine_rear_side_slope;
  int16_t machine_roll;
  int16_t machine_side_slope;
  float tipoff_pitch_cal_offset;
  bool hyd_oil_temp_enabled;
  bool audible_weight_enabled;
  uint16_t audible_weight_command;
} cpm_common_interfaces__msg__WeighPidData;

// Struct for a sequence of cpm_common_interfaces__msg__WeighPidData.
typedef struct cpm_common_interfaces__msg__WeighPidData__Sequence
{
  cpm_common_interfaces__msg__WeighPidData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__WeighPidData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__WEIGH_PID_DATA__STRUCT_H_
