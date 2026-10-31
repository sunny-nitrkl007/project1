// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/EthernetStatsType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ethernet_stats_type.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'eth_interface_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/EthernetStatsType in the package weigh_app_interfaces.
/**
  * EthernetStatsType
 */
typedef struct weigh_app_interfaces__msg__EthernetStatsType
{
  rosidl_runtime_c__String eth_interface_name;
  double tx_kbps;
  double rx_kbps;
} weigh_app_interfaces__msg__EthernetStatsType;

// Struct for a sequence of weigh_app_interfaces__msg__EthernetStatsType.
typedef struct weigh_app_interfaces__msg__EthernetStatsType__Sequence
{
  weigh_app_interfaces__msg__EthernetStatsType * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__EthernetStatsType__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__ETHERNET_STATS_TYPE__STRUCT_H_
