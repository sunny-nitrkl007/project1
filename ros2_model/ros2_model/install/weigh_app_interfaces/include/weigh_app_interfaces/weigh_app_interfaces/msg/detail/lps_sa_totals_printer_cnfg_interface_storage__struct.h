// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaTotalsPrinterCnfgInterfaceStorage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_totals_printer_cnfg_interface_storage.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'config'
#include "weigh_app_interfaces/msg/detail/lps_sa_totals_printer_cnfg__struct.h"

/// Struct defined in msg/LpsSaTotalsPrinterCnfgInterfaceStorage in the package weigh_app_interfaces.
/**
  * LpsSaTotalsPrinterCnfgInterfaceStorage
 */
typedef struct weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfgInterfaceStorage
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg config;
} weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfgInterfaceStorage;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfgInterfaceStorage.
typedef struct weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfgInterfaceStorage__Sequence
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfgInterfaceStorage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfgInterfaceStorage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG_INTERFACE_STORAGE__STRUCT_H_
