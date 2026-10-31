// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from job_mgr_interfaces:msg/DataLinkData.idl
// generated code does not contain a copyright notice
#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "job_mgr_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "job_mgr_interfaces/msg/detail/data_link_data__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_job_mgr_interfaces
bool cdr_serialize_job_mgr_interfaces__msg__DataLinkData(
  const job_mgr_interfaces__msg__DataLinkData * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_job_mgr_interfaces
bool cdr_deserialize_job_mgr_interfaces__msg__DataLinkData(
  eprosima::fastcdr::Cdr &,
  job_mgr_interfaces__msg__DataLinkData * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_job_mgr_interfaces
size_t get_serialized_size_job_mgr_interfaces__msg__DataLinkData(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_job_mgr_interfaces
size_t max_serialized_size_job_mgr_interfaces__msg__DataLinkData(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_job_mgr_interfaces
bool cdr_serialize_key_job_mgr_interfaces__msg__DataLinkData(
  const job_mgr_interfaces__msg__DataLinkData * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_job_mgr_interfaces
size_t get_serialized_size_key_job_mgr_interfaces__msg__DataLinkData(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_job_mgr_interfaces
size_t max_serialized_size_key_job_mgr_interfaces__msg__DataLinkData(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_job_mgr_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, job_mgr_interfaces, msg, DataLinkData)();

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__DATA_LINK_DATA__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
