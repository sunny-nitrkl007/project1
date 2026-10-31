// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/TruckTicket.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/truck_ticket.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'header_line1'
// Member 'header_line2'
// Member 'header_line3'
// Member 'footer_line1'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/TruckTicket in the package weigh_app_interfaces.
/**
  * LpsSaTotalsPrinterCnfg::TruckTicket
 */
typedef struct weigh_app_interfaces__msg__TruckTicket
{
  uint8_t num_copies;
  bool header_enabled;
  rosidl_runtime_c__String header_line1;
  rosidl_runtime_c__String header_line2;
  rosidl_runtime_c__String header_line3;
  rosidl_runtime_c__String footer_line1;
  bool bucket_weights_enabled;
  bool truck_weight_enabled;
  bool truck_id_enabled;
  bool material_id_enabled;
  bool store_time_enabled;
  uint32_t ticket_number;
  uint16_t retention_period;
} weigh_app_interfaces__msg__TruckTicket;

// Struct for a sequence of weigh_app_interfaces__msg__TruckTicket.
typedef struct weigh_app_interfaces__msg__TruckTicket__Sequence
{
  weigh_app_interfaces__msg__TruckTicket * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__TruckTicket__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__TRUCK_TICKET__STRUCT_H_
