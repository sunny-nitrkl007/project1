// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from weigh_app_interfaces:msg/CoreUsage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/core_usage.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__FUNCTIONS_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__FUNCTIONS_H_

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
#include "weigh_app_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "weigh_app_interfaces/msg/detail/core_usage__struct.h"

/// Initialize msg/CoreUsage message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * weigh_app_interfaces__msg__CoreUsage
 * )) before or use
 * weigh_app_interfaces__msg__CoreUsage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
bool
weigh_app_interfaces__msg__CoreUsage__init(weigh_app_interfaces__msg__CoreUsage * msg);

/// Finalize msg/CoreUsage message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
void
weigh_app_interfaces__msg__CoreUsage__fini(weigh_app_interfaces__msg__CoreUsage * msg);

/// Create msg/CoreUsage message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * weigh_app_interfaces__msg__CoreUsage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
weigh_app_interfaces__msg__CoreUsage *
weigh_app_interfaces__msg__CoreUsage__create(void);

/// Destroy msg/CoreUsage message.
/**
 * It calls
 * weigh_app_interfaces__msg__CoreUsage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
void
weigh_app_interfaces__msg__CoreUsage__destroy(weigh_app_interfaces__msg__CoreUsage * msg);

/// Check for msg/CoreUsage message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
bool
weigh_app_interfaces__msg__CoreUsage__are_equal(const weigh_app_interfaces__msg__CoreUsage * lhs, const weigh_app_interfaces__msg__CoreUsage * rhs);

/// Copy a msg/CoreUsage message.
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
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
bool
weigh_app_interfaces__msg__CoreUsage__copy(
  const weigh_app_interfaces__msg__CoreUsage * input,
  weigh_app_interfaces__msg__CoreUsage * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
const rosidl_type_hash_t *
weigh_app_interfaces__msg__CoreUsage__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
const rosidl_runtime_c__type_description__TypeDescription *
weigh_app_interfaces__msg__CoreUsage__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
const rosidl_runtime_c__type_description__TypeSource *
weigh_app_interfaces__msg__CoreUsage__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
const rosidl_runtime_c__type_description__TypeSource__Sequence *
weigh_app_interfaces__msg__CoreUsage__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/CoreUsage messages.
/**
 * It allocates the memory for the number of elements and calls
 * weigh_app_interfaces__msg__CoreUsage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
bool
weigh_app_interfaces__msg__CoreUsage__Sequence__init(weigh_app_interfaces__msg__CoreUsage__Sequence * array, size_t size);

/// Finalize array of msg/CoreUsage messages.
/**
 * It calls
 * weigh_app_interfaces__msg__CoreUsage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
void
weigh_app_interfaces__msg__CoreUsage__Sequence__fini(weigh_app_interfaces__msg__CoreUsage__Sequence * array);

/// Create array of msg/CoreUsage messages.
/**
 * It allocates the memory for the array and calls
 * weigh_app_interfaces__msg__CoreUsage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
weigh_app_interfaces__msg__CoreUsage__Sequence *
weigh_app_interfaces__msg__CoreUsage__Sequence__create(size_t size);

/// Destroy array of msg/CoreUsage messages.
/**
 * It calls
 * weigh_app_interfaces__msg__CoreUsage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
void
weigh_app_interfaces__msg__CoreUsage__Sequence__destroy(weigh_app_interfaces__msg__CoreUsage__Sequence * array);

/// Check for msg/CoreUsage message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
bool
weigh_app_interfaces__msg__CoreUsage__Sequence__are_equal(const weigh_app_interfaces__msg__CoreUsage__Sequence * lhs, const weigh_app_interfaces__msg__CoreUsage__Sequence * rhs);

/// Copy an array of msg/CoreUsage messages.
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
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
bool
weigh_app_interfaces__msg__CoreUsage__Sequence__copy(
  const weigh_app_interfaces__msg__CoreUsage__Sequence * input,
  weigh_app_interfaces__msg__CoreUsage__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__CORE_USAGE__FUNCTIONS_H_
