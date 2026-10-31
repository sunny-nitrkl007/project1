// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/DataLinkParam.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/data_link_param.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'IDENTIFIER_TYPE_PID'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__IDENTIFIER_TYPE_PID = 0
};

/// Constant 'IDENTIFIER_TYPE_PUBLIC_PGN'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__IDENTIFIER_TYPE_PUBLIC_PGN = 1
};

/// Constant 'IDENTIFIER_TYPE_CAT_EXT'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__IDENTIFIER_TYPE_CAT_EXT = 2
};

/// Constant 'IDENTIFIER_TYPE_PROP_A_PGN'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__IDENTIFIER_TYPE_PROP_A_PGN = 3
};

/// Constant 'IDENTIFIER_TYPE_SPN'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__IDENTIFIER_TYPE_SPN = 4
};

/// Constant 'UNITS_NO_UNIT'.
/**
  * DataLinkParamInfo::DlpUnits_t
 */
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_NO_UNIT = 0
};

/// Constant 'UNITS_KPA'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_KPA = 1
};

/// Constant 'UNITS_KPA2'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_KPA2 = 2
};

/// Constant 'UNITS_DEG_C'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_DEG_C = 3
};

/// Constant 'UNITS_KM_PER_HR'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_KM_PER_HR = 4
};

/// Constant 'UNITS_RPM'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_RPM = 5
};

/// Constant 'UNITS_VOLTS'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_VOLTS = 6
};

/// Constant 'UNITS_LITERS'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_LITERS = 7
};

/// Constant 'UNITS_PERCENT'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_PERCENT = 8
};

/// Constant 'UNITS_LTRS_PER_HR'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_LTRS_PER_HR = 9
};

/// Constant 'UNITS_DEG'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_DEG = 10
};

/// Constant 'UNITS_MM'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_MM = 11
};

/// Constant 'UNITS_MM2'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_MM2 = 12
};

/// Constant 'UNITS_PULSES_PER_KM'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_PULSES_PER_KM = 13
};

/// Constant 'UNITS_KW'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_KW = 14
};

/// Constant 'UNITS_HRS'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_HRS = 15
};

/// Constant 'UNITS_SEC'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_SEC = 16
};

/// Constant 'UNITS_MS'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_MS = 17
};

/// Constant 'UNITS_NM'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_NM = 18
};

/// Constant 'UNITS_MIN'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_MIN = 19
};

/// Constant 'UNITS_RPM_PER_SEC'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_RPM_PER_SEC = 20
};

/// Constant 'UNITS_METERS_PER_SEC'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_METERS_PER_SEC = 21
};

/// Constant 'UNITS_HZ'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_HZ = 22
};

/// Constant 'UNITS_AMPS'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_AMPS = 23
};

/// Constant 'UNITS_NM3_PER_HOUR'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_NM3_PER_HOUR = 24
};

/// Constant 'UNITS_MJ_PER_NM3'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_MJ_PER_NM3 = 25
};

/// Constant 'UNITS_OHMS'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_OHMS = 26
};

/// Constant 'UNITS_METERS_PER_SEC2'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_METERS_PER_SEC2 = 27
};

/// Constant 'UNITS_KG_PER_HR'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__UNITS_KG_PER_HR = 28
};

/// Constant 'VAR_LENGTH_PARAM_TYPE_NOT_APPLICABLE'.
/**
  * VarLengthDataLinkParamFactory::VarLengthParamType
 */
enum
{
  weigh_app_interfaces__msg__DataLinkParam__VAR_LENGTH_PARAM_TYPE_NOT_APPLICABLE = 0
};

/// Constant 'VAR_LENGTH_PARAM_TYPE_GPS'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__VAR_LENGTH_PARAM_TYPE_GPS = 1
};

/// Constant 'VAR_LENGTH_PARAM_TYPE_SPL_PID_REV_DATA_BYTE_ORDER'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__VAR_LENGTH_PARAM_TYPE_SPL_PID_REV_DATA_BYTE_ORDER = 2
};

/// Constant 'VAR_LENGTH_PARAM_TYPE_TIME_ZONE'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__VAR_LENGTH_PARAM_TYPE_TIME_ZONE = 3
};

/// Constant 'VAR_LENGTH_PARAM_TYPE_PRODUCT_ID'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__VAR_LENGTH_PARAM_TYPE_PRODUCT_ID = 4
};

/// Constant 'VAR_LENGTH_PARAM_TYPE_PGN'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__VAR_LENGTH_PARAM_TYPE_PGN = 5
};

/// Constant 'VAR_LENGTH_PARAM_TYPE_SPN'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__VAR_LENGTH_PARAM_TYPE_SPN = 6
};

/// Constant 'VAR_LENGTH_PARAM_TYPE_SECURITY_SYSTEM_CURRENT_KEY'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__VAR_LENGTH_PARAM_TYPE_SECURITY_SYSTEM_CURRENT_KEY = 7
};

/// Constant 'VAR_LENGTH_PARAM_TYPE_SECURITY_SYSTEM_CURRENT_SECURITY_ID'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__VAR_LENGTH_PARAM_TYPE_SECURITY_SYSTEM_CURRENT_SECURITY_ID = 8
};

/// Constant 'VAR_LENGTH_PARAM_TYPE_UNSUPPORTED'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__VAR_LENGTH_PARAM_TYPE_UNSUPPORTED = 9
};

/// Constant 'VAR_LENGTH_PARAM_TYPE_CAT_EXT'.
enum
{
  weigh_app_interfaces__msg__DataLinkParam__VAR_LENGTH_PARAM_TYPE_CAT_EXT = 10
};

// Include directives for member types
// Member 'last_value_vector'
// Member 'var_param_block'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/DataLinkParam in the package weigh_app_interfaces.
/**
  * DataLinkParamInfo::DlpParamIdentifierType_t
 */
typedef struct weigh_app_interfaces__msg__DataLinkParam
{
  /// DataLinkParam
  uint8_t identifier_type;
  uint32_t sid;
  uint32_t param_id;
  uint8_t units;
  float scaling;
  float offset;
  bool pid_data_received;
  uint16_t last_value_dsi;
  int16_t last_value_i16;
  uint16_t last_value_u16;
  float last_value_f32;
  double last_value_eng;
  double last_good_value_eng;
  rosidl_runtime_c__uint8__Sequence last_value_vector;
  rosidl_runtime_c__uint8__Sequence var_param_block;
  uint8_t var_length_param_type;
  uint16_t var_length_param_dsi;
} weigh_app_interfaces__msg__DataLinkParam;

// Struct for a sequence of weigh_app_interfaces__msg__DataLinkParam.
typedef struct weigh_app_interfaces__msg__DataLinkParam__Sequence
{
  weigh_app_interfaces__msg__DataLinkParam * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__DataLinkParam__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DATA_LINK_PARAM__STRUCT_H_
