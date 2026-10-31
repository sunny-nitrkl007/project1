// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/ReadyToFlashStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/ready_to_flash_status.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'APP_READY_CODE_NOT_SET'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_NOT_SET = -1
};

/// Constant 'APP_READY_CODE_OK_TO_FLASH'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_OK_TO_FLASH = 0
};

/// Constant 'APP_READY_CODE_ENGINE_SPEED_DETECTED'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_ENGINE_SPEED_DETECTED = 1
};

/// Constant 'APP_READY_CODE_IMPLEMENT_NOT_LOCKED'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_IMPLEMENT_NOT_LOCKED = 2
};

/// Constant 'APP_READY_CODE_UNABLE_TO_FLASH'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_UNABLE_TO_FLASH = 3
};

/// Constant 'APP_READY_CODE_BOX_NOT_FLASHABLE'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_BOX_NOT_FLASHABLE = 4
};

/// Constant 'APP_READY_CODE_TORQUE_CONVERTER_SPEED_DETECTED'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_TORQUE_CONVERTER_SPEED_DETECTED = 5
};

/// Constant 'APP_READY_CODE_SYSTEM_VOLTAGE_TOO_LOW'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_SYSTEM_VOLTAGE_TOO_LOW = 6
};

/// Constant 'APP_READY_CODE_DIRECTION_SWITCH_NOT_IN_NEUTRAL'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_DIRECTION_SWITCH_NOT_IN_NEUTRAL = 7
};

/// Constant 'APP_READY_CODE_PARKING_BRAKE_NOT_SET'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_PARKING_BRAKE_NOT_SET = 8
};

/// Constant 'APP_READY_CODE_MODE_SWITCH_NOT_IN_STOP'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_MODE_SWITCH_NOT_IN_STOP = 9
};

/// Constant 'APP_READY_CODE_TRANSMISSION_NOT_IN_NEUTRAL'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_TRANSMISSION_NOT_IN_NEUTRAL = 10
};

/// Constant 'APP_READY_CODE_HYDRAULIC_SYSTEM_ENABLED'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_HYDRAULIC_SYSTEM_ENABLED = 11
};

/// Constant 'APP_READY_CODE_NOT_EQUIVALENT_PREMIUM_SOFTWARE'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_NOT_EQUIVALENT_PREMIUM_SOFTWARE = 12
};

/// Constant 'APP_READY_CODE_ECM_BUSY'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_ECM_BUSY = 13
};

/// Constant 'APP_READY_CODE_DEVELOPMENT_SOFTWARE'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_DEVELOPMENT_SOFTWARE = 14
};

/// Constant 'APP_READY_CODE_SUBSYSTEM_FLASH_IN_PROGRESS'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_SUBSYSTEM_FLASH_IN_PROGRESS = 15
};

/// Constant 'APP_READY_CODE_MACHINE_SPEED_DETECTED'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_MACHINE_SPEED_DETECTED = 16
};

/// Constant 'APP_READY_CODE_HIGH_VOLTAGE_SYSTEM_ENERGIZED'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_HIGH_VOLTAGE_SYSTEM_ENERGIZED = 17
};

/// Constant 'APP_READY_CODE_CANNOT_FLASH_ON_THIS_PORT'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_CANNOT_FLASH_ON_THIS_PORT = 18
};

/// Constant 'APP_READY_CODE_PAYLOAL_LEGAL_FOR_TRADE_IS_SEALED'.
enum
{
  weigh_app_interfaces__msg__ReadyToFlashStatus__APP_READY_CODE_PAYLOAL_LEGAL_FOR_TRADE_IS_SEALED = 22
};

// Include directives for member types
// Member 'task_name'
// Member 'host_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ReadyToFlashStatus in the package weigh_app_interfaces.
/**
  * rpa_application_ready_code_e
 */
typedef struct weigh_app_interfaces__msg__ReadyToFlashStatus
{
  /// ReadyToFlashStatusStorage
  rosidl_runtime_c__String task_name;
  rosidl_runtime_c__String host_name;
  int16_t ready_code;
} weigh_app_interfaces__msg__ReadyToFlashStatus;

// Struct for a sequence of weigh_app_interfaces__msg__ReadyToFlashStatus.
typedef struct weigh_app_interfaces__msg__ReadyToFlashStatus__Sequence
{
  weigh_app_interfaces__msg__ReadyToFlashStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__ReadyToFlashStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__READY_TO_FLASH_STATUS__STRUCT_H_
