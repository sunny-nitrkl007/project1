// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/PwmInputChannels.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/pwm_input_channels.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'period'
// Member 'width'
// Member 'switch_status'
// Member 'timeout'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/PwmInputChannels in the package weigh_app_interfaces.
/**
  * PwmInputChannelsStorage::PwmData
 */
typedef struct weigh_app_interfaces__msg__PwmInputChannels
{
  rosidl_runtime_c__int32__Sequence period;
  rosidl_runtime_c__int32__Sequence width;
  rosidl_runtime_c__uint8__Sequence switch_status;
  rosidl_runtime_c__uint8__Sequence timeout;
} weigh_app_interfaces__msg__PwmInputChannels;

// Struct for a sequence of weigh_app_interfaces__msg__PwmInputChannels.
typedef struct weigh_app_interfaces__msg__PwmInputChannels__Sequence
{
  weigh_app_interfaces__msg__PwmInputChannels * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__PwmInputChannels__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__PWM_INPUT_CHANNELS__STRUCT_H_
