// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/SystemHardwareHealthStorage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/system_hardware_health_storage.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'source_system'
// Member 'core_temperatures_c'
// Member 'ecm_sw_version'
// Member 'software_group_part_number'
// Member 'software_group_description'
// Member 'software_group_release_date'
// Member 'ecm_os_version'
#include "rosidl_runtime_c/string.h"
// Member 'list_of_remaining_disk_space'
#include "weigh_app_interfaces/msg/detail/disk_space_remain__struct.h"
// Member 'ecm_hw_version'
#include "weigh_app_interfaces/msg/detail/ecm_version_info__struct.h"
// Member 'list_of_ethernet_stats'
#include "weigh_app_interfaces/msg/detail/ethernet_stats_type__struct.h"
// Member 'per_core_cpu_data'
#include "weigh_app_interfaces/msg/detail/core_usage__struct.h"

/// Struct defined in msg/SystemHardwareHealthStorage in the package weigh_app_interfaces.
/**
  * SystemHardwareHealthStorage
 */
typedef struct weigh_app_interfaces__msg__SystemHardwareHealthStorage
{
  rosidl_runtime_c__String source_system;
  uint32_t total_system_memory_kb;
  uint32_t available_system_memory_kb;
  weigh_app_interfaces__msg__DiskSpaceRemain__Sequence list_of_remaining_disk_space;
  double system_up_time_sec;
  double load_avg1min;
  double load_avg5min;
  double load_avg15min;
  rosidl_runtime_c__String__Sequence core_temperatures_c;
  rosidl_runtime_c__String ecm_sw_version;
  rosidl_runtime_c__String software_group_part_number;
  rosidl_runtime_c__String software_group_description;
  rosidl_runtime_c__String software_group_release_date;
  weigh_app_interfaces__msg__EcmVersionInfo ecm_hw_version;
  double eth0_tx_kbs;
  double eth0_rx_kbs;
  double eth1_tx_kbs;
  double eth1_rx_kbs;
  weigh_app_interfaces__msg__EthernetStatsType__Sequence list_of_ethernet_stats;
  double system_cpu_usage_percent;
  double system_cpu_io_wait_percent;
  double system_cpu_irq_percent;
  rosidl_runtime_c__String ecm_os_version;
  weigh_app_interfaces__msg__CoreUsage__Sequence per_core_cpu_data;
  double battery_voltage;
} weigh_app_interfaces__msg__SystemHardwareHealthStorage;

// Struct for a sequence of weigh_app_interfaces__msg__SystemHardwareHealthStorage.
typedef struct weigh_app_interfaces__msg__SystemHardwareHealthStorage__Sequence
{
  weigh_app_interfaces__msg__SystemHardwareHealthStorage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__SystemHardwareHealthStorage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__SYSTEM_HARDWARE_HEALTH_STORAGE__STRUCT_H_
