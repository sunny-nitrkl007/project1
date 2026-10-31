// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from cpm_common_interfaces:msg/AcdEventPopUp.idl
// generated code does not contain a copyright notice
#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "cpm_common_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "cpm_common_interfaces/msg/detail/acd_event_pop_up__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
bool cdr_serialize_cpm_common_interfaces__msg__AcdEventPopUp(
  const cpm_common_interfaces__msg__AcdEventPopUp * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
bool cdr_deserialize_cpm_common_interfaces__msg__AcdEventPopUp(
  eprosima::fastcdr::Cdr &,
  cpm_common_interfaces__msg__AcdEventPopUp * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t get_serialized_size_cpm_common_interfaces__msg__AcdEventPopUp(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t max_serialized_size_cpm_common_interfaces__msg__AcdEventPopUp(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
bool cdr_serialize_key_cpm_common_interfaces__msg__AcdEventPopUp(
  const cpm_common_interfaces__msg__AcdEventPopUp * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t get_serialized_size_key_cpm_common_interfaces__msg__AcdEventPopUp(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t max_serialized_size_key_cpm_common_interfaces__msg__AcdEventPopUp(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cpm_common_interfaces, msg, AcdEventPopUp)();

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__ACD_EVENT_POP_UP__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
