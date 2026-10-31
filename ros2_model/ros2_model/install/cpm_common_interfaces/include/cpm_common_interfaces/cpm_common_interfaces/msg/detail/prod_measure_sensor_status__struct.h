// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cpm_common_interfaces:msg/ProdMeasureSensorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/prod_measure_sensor_status.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__STRUCT_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'TILT_SENSOR_ROTARY_POSITION'.
enum
{
  cpm_common_interfaces__msg__ProdMeasureSensorStatus__TILT_SENSOR_ROTARY_POSITION = 451
};

/// Constant 'TILT_SENSOR_IN_CYLINDER_POSITION'.
enum
{
  cpm_common_interfaces__msg__ProdMeasureSensorStatus__TILT_SENSOR_IN_CYLINDER_POSITION = 452
};

/// Struct defined in msg/ProdMeasureSensorStatus in the package cpm_common_interfaces.
/**
  * TiltSensorConfig_t
 */
typedef struct cpm_common_interfaces__msg__ProdMeasureSensorStatus
{
  /// ProdMeasureSensorStatus_t
  float lift_link_dc;
  float lift_cyl_pos;
  float lift_cyl_he_pres;
  float lift_cyl_re_pres;
  uint16_t tilt_sensor_config;
  float tilt_cyl_he_pres;
  float tilt_cyl_re_pres;
  float tilt_link_dc;
  float hyd_oil_temp;
} cpm_common_interfaces__msg__ProdMeasureSensorStatus;

// Struct for a sequence of cpm_common_interfaces__msg__ProdMeasureSensorStatus.
typedef struct cpm_common_interfaces__msg__ProdMeasureSensorStatus__Sequence
{
  cpm_common_interfaces__msg__ProdMeasureSensorStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cpm_common_interfaces__msg__ProdMeasureSensorStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__PROD_MEASURE_SENSOR_STATUS__STRUCT_H_
