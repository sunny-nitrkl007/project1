// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/LpsSaTotalsPrinterCnfg.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_totals_printer_cnfg.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'DATE_FORMAT_YYYY_MM_DD'.
enum
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__DATE_FORMAT_YYYY_MM_DD = 1648
};

/// Constant 'DATE_FORMAT_MM_DD_YYYY'.
enum
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__DATE_FORMAT_MM_DD_YYYY = 1649
};

/// Constant 'DATE_FORMAT_DD_MM_YYYY'.
enum
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__DATE_FORMAT_DD_MM_YYYY = 1650
};

/// Constant 'DATE_FORMAT_YY_MM_DD'.
enum
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__DATE_FORMAT_YY_MM_DD = 1651
};

/// Constant 'DATE_FORMAT_MM_DD_YY'.
enum
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__DATE_FORMAT_MM_DD_YY = 1652
};

/// Constant 'DATE_FORMAT_DD_MM_YY'.
enum
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__DATE_FORMAT_DD_MM_YY = 1653
};

/// Constant 'DATE_FORMAT_MM_DD'.
enum
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__DATE_FORMAT_MM_DD = 1654
};

/// Constant 'DATE_FORMAT_DD_MM'.
enum
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__DATE_FORMAT_DD_MM = 1655
};

/// Constant 'DATE_SEPARATOR_SLASH'.
/**
  * LpsSaTotalsPrinterCnfgDateSeparator
 */
enum
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__DATE_SEPARATOR_SLASH = 1656
};

/// Constant 'DATE_SEPARATOR_HYPHEN'.
enum
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__DATE_SEPARATOR_HYPHEN = 1657
};

// Include directives for member types
// Member 'truck_ticket'
#include "weigh_app_interfaces/msg/detail/truck_ticket__struct.h"
// Member 'truck_report'
#include "weigh_app_interfaces/msg/detail/truck_report__struct.h"
// Member 'material_report'
#include "weigh_app_interfaces/msg/detail/material_report__struct.h"
// Member 'udp_transfer_ip'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/LpsSaTotalsPrinterCnfg in the package weigh_app_interfaces.
/**
  * LpsSaTotalsPrinterCnfgDateFormat
 */
typedef struct weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg
{
  /// LpsSaTotalsPrinterCnfg
  bool installed;
  uint8_t leading_blank_lines;
  uint8_t trailing_blank_lines;
  uint16_t date_format;
  uint16_t date_separator;
  weigh_app_interfaces__msg__TruckTicket truck_ticket;
  weigh_app_interfaces__msg__TruckReport truck_report;
  weigh_app_interfaces__msg__MaterialReport material_report;
  rosidl_runtime_c__String udp_transfer_ip;
  uint32_t udp_transfer_port;
  bool udp_transfer_enabled;
} weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg;

// Struct for a sequence of weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg.
typedef struct weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__Sequence
{
  weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__LpsSaTotalsPrinterCnfg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_TOTALS_PRINTER_CNFG__STRUCT_H_
