// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from weigh_app_interfaces:msg/DemoAppTxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/demo_app_tx_channel.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__STRUCT_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/DemoAppTxChannel in the package weigh_app_interfaces.
/**
  * DemoAppTxChannelStorage
 */
typedef struct weigh_app_interfaces__msg__DemoAppTxChannel
{
  float liftposition;
  float liftposition_rate;
  float tiltposition;
  float tiltposition_rate;
  float payload;
  float payload_rate;
  bool dig;
  bool wrw;
  bool llw;
  bool dump;
  bool pdump;
  bool rack;
  bool carry;
  float weight1;
  float pres_lift_he_demo;
  float pres_lift_re_demo;
  float angle_lift_demo;
  float angle_afe_demo;
  float angle_abc_demo;
} weigh_app_interfaces__msg__DemoAppTxChannel;

// Struct for a sequence of weigh_app_interfaces__msg__DemoAppTxChannel.
typedef struct weigh_app_interfaces__msg__DemoAppTxChannel__Sequence
{
  weigh_app_interfaces__msg__DemoAppTxChannel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} weigh_app_interfaces__msg__DemoAppTxChannel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__DEMO_APP_TX_CHANNEL__STRUCT_H_
