// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from cpm_common_interfaces:msg/AisJhm2TxChannel.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/ais_jhm2_tx_channel.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__FUNCTIONS_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "cpm_common_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "cpm_common_interfaces/msg/detail/ais_jhm2_tx_channel__struct.h"

/// Initialize msg/AisJhm2TxChannel message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cpm_common_interfaces__msg__AisJhm2TxChannel
 * )) before or use
 * cpm_common_interfaces__msg__AisJhm2TxChannel__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__AisJhm2TxChannel__init(cpm_common_interfaces__msg__AisJhm2TxChannel * msg);

/// Finalize msg/AisJhm2TxChannel message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__AisJhm2TxChannel__fini(cpm_common_interfaces__msg__AisJhm2TxChannel * msg);

/// Create msg/AisJhm2TxChannel message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cpm_common_interfaces__msg__AisJhm2TxChannel__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
cpm_common_interfaces__msg__AisJhm2TxChannel *
cpm_common_interfaces__msg__AisJhm2TxChannel__create(void);

/// Destroy msg/AisJhm2TxChannel message.
/**
 * It calls
 * cpm_common_interfaces__msg__AisJhm2TxChannel__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__AisJhm2TxChannel__destroy(cpm_common_interfaces__msg__AisJhm2TxChannel * msg);

/// Check for msg/AisJhm2TxChannel message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__AisJhm2TxChannel__are_equal(const cpm_common_interfaces__msg__AisJhm2TxChannel * lhs, const cpm_common_interfaces__msg__AisJhm2TxChannel * rhs);

/// Copy a msg/AisJhm2TxChannel message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__AisJhm2TxChannel__copy(
  const cpm_common_interfaces__msg__AisJhm2TxChannel * input,
  cpm_common_interfaces__msg__AisJhm2TxChannel * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_type_hash_t *
cpm_common_interfaces__msg__AisJhm2TxChannel__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_runtime_c__type_description__TypeDescription *
cpm_common_interfaces__msg__AisJhm2TxChannel__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_runtime_c__type_description__TypeSource *
cpm_common_interfaces__msg__AisJhm2TxChannel__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_runtime_c__type_description__TypeSource__Sequence *
cpm_common_interfaces__msg__AisJhm2TxChannel__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/AisJhm2TxChannel messages.
/**
 * It allocates the memory for the number of elements and calls
 * cpm_common_interfaces__msg__AisJhm2TxChannel__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence__init(cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence * array, size_t size);

/// Finalize array of msg/AisJhm2TxChannel messages.
/**
 * It calls
 * cpm_common_interfaces__msg__AisJhm2TxChannel__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence__fini(cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence * array);

/// Create array of msg/AisJhm2TxChannel messages.
/**
 * It allocates the memory for the array and calls
 * cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence *
cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence__create(size_t size);

/// Destroy array of msg/AisJhm2TxChannel messages.
/**
 * It calls
 * cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence__destroy(cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence * array);

/// Check for msg/AisJhm2TxChannel message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence__are_equal(const cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence * lhs, const cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence * rhs);

/// Copy an array of msg/AisJhm2TxChannel messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence__copy(
  const cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence * input,
  cpm_common_interfaces__msg__AisJhm2TxChannel__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__AIS_JHM2_TX_CHANNEL__FUNCTIONS_H_
