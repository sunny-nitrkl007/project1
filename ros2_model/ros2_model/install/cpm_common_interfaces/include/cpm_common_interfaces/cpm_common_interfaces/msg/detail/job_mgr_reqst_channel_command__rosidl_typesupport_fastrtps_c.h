// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from cpm_common_interfaces:msg/JobMgrReqstChannelCommand.idl
// generated code does not contain a copyright notice
#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "cpm_common_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "cpm_common_interfaces/msg/detail/job_mgr_reqst_channel_command__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
bool cdr_serialize_cpm_common_interfaces__msg__JobMgrReqstChannelCommand(
  const cpm_common_interfaces__msg__JobMgrReqstChannelCommand * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
bool cdr_deserialize_cpm_common_interfaces__msg__JobMgrReqstChannelCommand(
  eprosima::fastcdr::Cdr &,
  cpm_common_interfaces__msg__JobMgrReqstChannelCommand * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t get_serialized_size_cpm_common_interfaces__msg__JobMgrReqstChannelCommand(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t max_serialized_size_cpm_common_interfaces__msg__JobMgrReqstChannelCommand(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
bool cdr_serialize_key_cpm_common_interfaces__msg__JobMgrReqstChannelCommand(
  const cpm_common_interfaces__msg__JobMgrReqstChannelCommand * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t get_serialized_size_key_cpm_common_interfaces__msg__JobMgrReqstChannelCommand(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
size_t max_serialized_size_key_cpm_common_interfaces__msg__JobMgrReqstChannelCommand(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cpm_common_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cpm_common_interfaces, msg, JobMgrReqstChannelCommand)();

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__JOB_MGR_REQST_CHANNEL_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
