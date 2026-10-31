// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/PartNumbers.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/part_numbers.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'product_id_num'
// Member 'equipment_id'
// Member 'sw_group_part_num'
// Member 'sw_group_release_date'
// Member 'sw_group_description'
// Member 'ecm_part_num'
// Member 'model_num'
// Member 'ecm_serial_num'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/PartNumbers in the package weigh_app_interfaces.
/**
  * PartNumbersStorage
 */
typedef struct weigh_app_interfaces__msg__PartNumbers
{
  rosidl_runtime_c__String product_id_num;
  rosidl_runtime_c__String equipment_id;
  rosidl_runtime_c__String sw_group_part_num;
  rosidl_runtime_c__String sw_group_release_date;
  rosidl_runtime_c__String sw_group_description;
  rosidl_runtime_c__String ecm_part_num;
  rosidl_runtime_c__String model_num;
  rosidl_runtime_c__String ecm_serial_num;
  bool product_id_num_set;
  bool sw_group_part_num_set;
  bool sw_group_release_date_set;
  bool sw_group_description_set;
  bool ecm_part_num_set;
  bool model_num_set;
  bool ecm_serial_num_set;
  bool equipment_id_set;
} weigh_app_interfaces__msg__PartNumbers;

// Struct for a sequence of weigh_app_interfaces__msg__PartNumbers.
typedef struct weigh_app_interfaces__msg__PartNumbers__Sequence
{
  weigh_app_interfaces__msg__PartNumbers * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__PartNumbers__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__PART_NUMBERS__STRUCT_H_
