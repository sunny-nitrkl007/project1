// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/AutonomyConditionDiagnosticsTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/autonomy_condition_diagnostics_tx_channel.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'sea_list'
#include "cpm_common_interfaces/msg/detail/sea__struct.h"

/// Struct defined in msg/AutonomyConditionDiagnosticsTxChannel in the package cpm_common_interfaces.
/**
  * AutonomyConditionDiagnosticsTxInterfaceStorage
 */
typedef struct cpm_common_interfaces__msg__AutonomyConditionDiagnosticsTxChannel
{
  int64_t time_point_ns;
  bool display_ethernet_bad;
  bool product_link_ethernet_bad;
  cpm_common_interfaces__msg__SEA__Sequence sea_list;
} cpm_common_interfaces__msg__AutonomyConditionDiagnosticsTxChannel;

// Struct for a sequence of cpm_common_interfaces__msg__AutonomyConditionDiagnosticsTxChannel.
typedef struct cpm_common_interfaces__msg__AutonomyConditionDiagnosticsTxChannel__Sequence
{
  cpm_common_interfaces__msg__AutonomyConditionDiagnosticsTxChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__AutonomyConditionDiagnosticsTxChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__AUTONOMY_CONDITION_DIAGNOSTICS_TX_CHANNEL__STRUCT_H_
