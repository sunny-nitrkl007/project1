// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from cpm_common_interfaces:msg/SimpleCalDataT.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cpm_common_interfaces/msg/simple_cal_data_t.h"


#ifndef CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__FUNCTIONS_H_
#define CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__FUNCTIONS_H_

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

#include "cpm_common_interfaces/msg/detail/simple_cal_data_t__struct.h"

/// Initialize msg/SimpleCalDataT message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cpm_common_interfaces__msg__SimpleCalDataT
 * )) before or use
 * cpm_common_interfaces__msg__SimpleCalDataT__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__SimpleCalDataT__init(cpm_common_interfaces__msg__SimpleCalDataT * msg);

/// Finalize msg/SimpleCalDataT message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__SimpleCalDataT__fini(cpm_common_interfaces__msg__SimpleCalDataT * msg);

/// Create msg/SimpleCalDataT message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cpm_common_interfaces__msg__SimpleCalDataT__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
cpm_common_interfaces__msg__SimpleCalDataT *
cpm_common_interfaces__msg__SimpleCalDataT__create(void);

/// Destroy msg/SimpleCalDataT message.
/**
 * It calls
 * cpm_common_interfaces__msg__SimpleCalDataT__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__SimpleCalDataT__destroy(cpm_common_interfaces__msg__SimpleCalDataT * msg);

/// Check for msg/SimpleCalDataT message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__SimpleCalDataT__are_equal(const cpm_common_interfaces__msg__SimpleCalDataT * lhs, const cpm_common_interfaces__msg__SimpleCalDataT * rhs);

/// Copy a msg/SimpleCalDataT message.
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
cpm_common_interfaces__msg__SimpleCalDataT__copy(
  const cpm_common_interfaces__msg__SimpleCalDataT * input,
  cpm_common_interfaces__msg__SimpleCalDataT * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_type_hash_t *
cpm_common_interfaces__msg__SimpleCalDataT__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_runtime_c__type_description__TypeDescription *
cpm_common_interfaces__msg__SimpleCalDataT__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_runtime_c__type_description__TypeSource *
cpm_common_interfaces__msg__SimpleCalDataT__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
const rosidl_runtime_c__type_description__TypeSource__Sequence *
cpm_common_interfaces__msg__SimpleCalDataT__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/SimpleCalDataT messages.
/**
 * It allocates the memory for the number of elements and calls
 * cpm_common_interfaces__msg__SimpleCalDataT__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__SimpleCalDataT__Sequence__init(cpm_common_interfaces__msg__SimpleCalDataT__Sequence * array, size_t size);

/// Finalize array of msg/SimpleCalDataT messages.
/**
 * It calls
 * cpm_common_interfaces__msg__SimpleCalDataT__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__SimpleCalDataT__Sequence__fini(cpm_common_interfaces__msg__SimpleCalDataT__Sequence * array);

/// Create array of msg/SimpleCalDataT messages.
/**
 * It allocates the memory for the array and calls
 * cpm_common_interfaces__msg__SimpleCalDataT__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
cpm_common_interfaces__msg__SimpleCalDataT__Sequence *
cpm_common_interfaces__msg__SimpleCalDataT__Sequence__create(size_t size);

/// Destroy array of msg/SimpleCalDataT messages.
/**
 * It calls
 * cpm_common_interfaces__msg__SimpleCalDataT__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
void
cpm_common_interfaces__msg__SimpleCalDataT__Sequence__destroy(cpm_common_interfaces__msg__SimpleCalDataT__Sequence * array);

/// Check for msg/SimpleCalDataT message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cpm_common_interfaces
bool
cpm_common_interfaces__msg__SimpleCalDataT__Sequence__are_equal(const cpm_common_interfaces__msg__SimpleCalDataT__Sequence * lhs, const cpm_common_interfaces__msg__SimpleCalDataT__Sequence * rhs);

/// Copy an array of msg/SimpleCalDataT messages.
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
cpm_common_interfaces__msg__SimpleCalDataT__Sequence__copy(
  const cpm_common_interfaces__msg__SimpleCalDataT__Sequence * input,
  cpm_common_interfaces__msg__SimpleCalDataT__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // CPM_COMMON_INTERFACES__MSG__DETAIL__SIMPLE_CAL_DATA_T__FUNCTIONS_H_
