// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from cpm_common_interfaces:msg/AisJhm2TxChannel.idl
// generated code does not contain a copyright notice
#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "cpm_common_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "cpm_common_interfaces/msg/detail/ais_jhm2_tx_channel__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
bool cdr_serialize_cpm_common_interfaces__msg__AisJhm2TxChannel(
  const cpm_common_interfaces__msg__AisJhm2TxChannel * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
bool cdr_deserialize_cpm_common_interfaces__msg__AisJhm2TxChannel(
  eprosima::fastcdr::Cdr &,
  cpm_common_interfaces__msg__AisJhm2TxChannel * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t get_serialized_size_cpm_common_interfaces__msg__AisJhm2TxChannel(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t max_serialized_size_cpm_common_interfaces__msg__AisJhm2TxChannel(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
bool cdr_serialize_key_cpm_common_interfaces__msg__AisJhm2TxChannel(
  const cpm_common_interfaces__msg__AisJhm2TxChannel * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t get_serialized_size_key_cpm_common_interfaces__msg__AisJhm2TxChannel(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t max_serialized_size_key_cpm_common_interfaces__msg__AisJhm2TxChannel(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cpm_common_interfaces, msg, AisJhm2TxChannel)();

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
