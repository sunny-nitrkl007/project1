// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyDataChannel.idl
// generated code does not contain a copyright notice
#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "weigh_app_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_data_channel__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_weigh_app_interfaces
bool cdr_serialize_weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel(
  const weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_weigh_app_interfaces
bool cdr_deserialize_weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel(
  eprosima::fastcdr::Cdr &,
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_weigh_app_interfaces
size_t get_serialized_size_weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_weigh_app_interfaces
size_t max_serialized_size_weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_weigh_app_interfaces
bool cdr_serialize_key_weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel(
  const weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_weigh_app_interfaces
size_t get_serialized_size_key_weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_weigh_app_interfaces
size_t max_serialized_size_key_weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyDataChannel(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_weigh_app_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, weigh_app_interfaces, msg, LpsSaNvmCalOnTheFlyDataChannel)();

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_DATA_CHANNEL__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
