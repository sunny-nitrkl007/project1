// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/LpsSaWeighTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/lps_sa_weigh_tx_channel.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'TOA_ANCHOR_UNCHANGED'.
enum
{
  cpm_common_interfaces__msg__LpsSaWeighTxChannel__TOA_ANCHOR_UNCHANGED = 0
};

/// Constant 'TOA_ANCHOR_RESET'.
enum
{
  cpm_common_interfaces__msg__LpsSaWeighTxChannel__TOA_ANCHOR_RESET = 1
};

/// Constant 'TOA_ANCHOR_ACCEPTED'.
enum
{
  cpm_common_interfaces__msg__LpsSaWeighTxChannel__TOA_ANCHOR_ACCEPTED = 2
};

/// Constant 'TOA_ANCHOR_REJECTED'.
enum
{
  cpm_common_interfaces__msg__LpsSaWeighTxChannel__TOA_ANCHOR_REJECTED = 3
};

/// Constant 'TEST_INACTIVE'.
/**
  * TestStatus_t
 */
enum
{
  cpm_common_interfaces__msg__LpsSaWeighTxChannel__TEST_INACTIVE = 0
};

/// Constant 'TEST_TESTING'.
enum
{
  cpm_common_interfaces__msg__LpsSaWeighTxChannel__TEST_TESTING = 1
};

/// Constant 'TEST_RECORDING'.
enum
{
  cpm_common_interfaces__msg__LpsSaWeighTxChannel__TEST_RECORDING = 2
};

/// Constant 'TEST_FAILED'.
enum
{
  cpm_common_interfaces__msg__LpsSaWeighTxChannel__TEST_FAILED = 3
};

// Include directives for member types
// Member 'payload'
#include "cpm_common_interfaces/msg/detail/payload__struct.h"
// Member 'lft_seal_status'
#include "cpm_common_interfaces/msg/detail/lft_seal_status__struct.h"
// Member 'lift_position_sensor_id'
// Member 'tilt_position_sensor_id'
// Member 'lift_head_end_pressure_sensor_id'
// Member 'lift_rod_end_pressure_sensor_id'
// Member 'hydraulic_oil_temperature_sensor_id'
// Member 'imu_sensor_id'
// Member 'implement_serial_num'
// Member 'work_tool_id'
#include "rosidl_runtime_c/string.h"
// Member 'lift_position'
#include "cpm_common_interfaces/msg/detail/lift_position__struct.h"
// Member 'lift_cyl_vel'
// Member 'lift_valve_command'
// Member 'tilt_valve_command'
#include "cpm_common_interfaces/msg/detail/float_io__struct.h"
// Member 'tilt_position'
#include "cpm_common_interfaces/msg/detail/tilt_position__struct.h"
// Member 'weigh_range'
#include "cpm_common_interfaces/msg/detail/weigh_range__struct.h"
// Member 'event_state'
#include "cpm_common_interfaces/msg/detail/acd_event_pop_up__struct.h"
// Member 'diag_state'
#include "cpm_common_interfaces/msg/detail/acd_diag_pop_up__struct.h"
// Member 'info_state'
#include "cpm_common_interfaces/msg/detail/acd_info_pop_up__struct.h"
// Member 'pid_data'
#include "cpm_common_interfaces/msg/detail/weigh_pid_data__struct.h"

/// Struct defined in msg/LpsSaWeighTxChannel in the package cpm_common_interfaces.
/**
  * ToaAnchorStatus_t
 */
typedef struct cpm_common_interfaces__msg__LpsSaWeighTxChannel
{
  /// LpsSaWeighTxChannelStorage
  int64_t time_point_ns;
  int32_t dig_stat;
  int32_t cal_stat;
  int32_t dump_stat;
  float best_bkt_wt_in_tonnes;
  uint16_t warmup_lifts_required;
  uint16_t payload_calc_meth;
  bool bkt_wt_latched_flag;
  bool latch_conditions_met;
  bool zero_available;
  cpm_common_interfaces__msg__Payload payload;
  cpm_common_interfaces__msg__LftSealStatus lft_seal_status;
  bool flash_enabled;
  rosidl_runtime_c__String lift_position_sensor_id;
  rosidl_runtime_c__String tilt_position_sensor_id;
  rosidl_runtime_c__String lift_head_end_pressure_sensor_id;
  rosidl_runtime_c__String lift_rod_end_pressure_sensor_id;
  rosidl_runtime_c__String hydraulic_oil_temperature_sensor_id;
  rosidl_runtime_c__String imu_sensor_id;
  rosidl_runtime_c__String implement_serial_num;
  rosidl_runtime_c__String work_tool_id;
  cpm_common_interfaces__msg__LiftPosition lift_position;
  cpm_common_interfaces__msg__FloatIO lift_cyl_vel;
  cpm_common_interfaces__msg__TiltPosition tilt_position;
  cpm_common_interfaces__msg__WeighRange weigh_range;
  int32_t indicator;
  float cal_wt;
  bool lift_stalled;
  cpm_common_interfaces__msg__FloatIO lift_valve_command;
  cpm_common_interfaces__msg__FloatIO tilt_valve_command;
  cpm_common_interfaces__msg__AcdEventPopUp event_state;
  cpm_common_interfaces__msg__AcdDiagPopUp diag_state;
  cpm_common_interfaces__msg__AcdInfoPopUp info_state;
  bool show_exclamation_point;
  bool excessive_pitch;
  bool bucket_fully_racked;
  float zero_weight;
  float simple_cal_adjust;
  int16_t engine_speed_rpm;
  cpm_common_interfaces__msg__WeighPidData pid_data;
  bool can11_message_timeout_flag;
  float toa_anchored_zero_offset;
  float toa_anchored_factor;
  uint8_t toa_anchor_status;
  bool payload_cal_in_progress;
  uint8_t test_status;
} cpm_common_interfaces__msg__LpsSaWeighTxChannel;

// Struct for a sequence of cpm_common_interfaces__msg__LpsSaWeighTxChannel.
typedef struct cpm_common_interfaces__msg__LpsSaWeighTxChannel__Sequence
{
  cpm_common_interfaces__msg__LpsSaWeighTxChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__LpsSaWeighTxChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__LPS_SA_WEIGH_TX_CHANNEL__STRUCT_H_
