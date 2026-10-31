// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from cpm_common_interfaces:msg/Payload.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/payload.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__FUNCTIONS_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__FUNCTIONS_H_

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

#include "cpm_common_interfaces/msg/detail/payload__struct.h"

/// Initialize msg/Payload message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cpm_common_interfaces__msg__Payload
 * )) before or use
 * cpm_common_interfaces__msg__Payload__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__Payload__init(cpm_common_interfaces__msg__Payload * msg);

/// Finalize msg/Payload message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__Payload__fini(cpm_common_interfaces__msg__Payload * msg);

/// Create msg/Payload message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cpm_common_interfaces__msg__Payload__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
cpm_common_interfaces__msg__Payload *
cpm_common_interfaces__msg__Payload__create(void);

/// Destroy msg/Payload message.
/**
 * It calls
 * cpm_common_interfaces__msg__Payload__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__Payload__destroy(cpm_common_interfaces__msg__Payload * msg);

/// Check for msg/Payload message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__Payload__are_equal(const cpm_common_interfaces__msg__Payload * lhs, const cpm_common_interfaces__msg__Payload * rhs);

/// Copy a msg/Payload message.
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
cpm_common_interfaces__msg__Payload__copy(
  const cpm_common_interfaces__msg__Payload * input,
  cpm_common_interfaces__msg__Payload * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_type_hash_t *
cpm_common_interfaces__msg__Payload__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_runtime_c__type_description__TypeDescription *
cpm_common_interfaces__msg__Payload__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_runtime_c__type_description__TypeSource *
cpm_common_interfaces__msg__Payload__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_runtime_c__type_description__TypeSource__Sequence *
cpm_common_interfaces__msg__Payload__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/Payload messages.
/**
 * It allocates the memory for the number of elements and calls
 * cpm_common_interfaces__msg__Payload__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__Payload__Sequence__init(cpm_common_interfaces__msg__Payload__Sequence * array, size_t size);

/// Finalize array of msg/Payload messages.
/**
 * It calls
 * cpm_common_interfaces__msg__Payload__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__Payload__Sequence__fini(cpm_common_interfaces__msg__Payload__Sequence * array);

/// Create array of msg/Payload messages.
/**
 * It allocates the memory for the array and calls
 * cpm_common_interfaces__msg__Payload__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
cpm_common_interfaces__msg__Payload__Sequence *
cpm_common_interfaces__msg__Payload__Sequence__create(size_t size);

/// Destroy array of msg/Payload messages.
/**
 * It calls
 * cpm_common_interfaces__msg__Payload__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__Payload__Sequence__destroy(cpm_common_interfaces__msg__Payload__Sequence * array);

/// Check for msg/Payload message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__Payload__Sequence__are_equal(const cpm_common_interfaces__msg__Payload__Sequence * lhs, const cpm_common_interfaces__msg__Payload__Sequence * rhs);

/// Copy an array of msg/Payload messages.
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
cpm_common_interfaces__msg__Payload__Sequence__copy(
  const cpm_common_interfaces__msg__Payload__Sequence * input,
  cpm_common_interfaces__msg__Payload__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__PAYLOAD__FUNCTIONS_H_
