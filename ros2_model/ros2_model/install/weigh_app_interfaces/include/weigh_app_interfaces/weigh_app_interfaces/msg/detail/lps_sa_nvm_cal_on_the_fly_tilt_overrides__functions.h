// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from weigh_app_interfaces:msg/LpsSaNvmCalOnTheFlyTiltOverrides.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_tilt_overrides.h"


#ifndef WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__FUNCTIONS_H_
#define WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__FUNCTIONS_H_

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

#include "weigh_app_interfaces/msg/detail/lps_sa_nvm_cal_on_the_fly_tilt_overrides__struct.h"

/// Initialize msg/LpsSaNvmCalOnTheFlyTiltOverrides message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides
 * )) before or use
 * weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
bool
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__init(weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides * msg);

/// Finalize msg/LpsSaNvmCalOnTheFlyTiltOverrides message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
void
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__fini(weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides * msg);

/// Create msg/LpsSaNvmCalOnTheFlyTiltOverrides message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides *
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__create(void);

/// Destroy msg/LpsSaNvmCalOnTheFlyTiltOverrides message.
/**
 * It calls
 * weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
void
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__destroy(weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides * msg);

/// Check for msg/LpsSaNvmCalOnTheFlyTiltOverrides message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
bool
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__are_equal(const weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides * lhs, const weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides * rhs);

/// Copy a msg/LpsSaNvmCalOnTheFlyTiltOverrides message.
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
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__copy(
  const weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides * input,
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
const rosidl_type_hash_t *
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
const rosidl_runtime_c__type_description__TypeDescription *
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
const rosidl_runtime_c__type_description__TypeSource *
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
const rosidl_runtime_c__type_description__TypeSource__Sequence *
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/LpsSaNvmCalOnTheFlyTiltOverrides messages.
/**
 * It allocates the memory for the number of elements and calls
 * weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
bool
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence__init(weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence * array, size_t size);

/// Finalize array of msg/LpsSaNvmCalOnTheFlyTiltOverrides messages.
/**
 * It calls
 * weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
void
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence__fini(weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence * array);

/// Create array of msg/LpsSaNvmCalOnTheFlyTiltOverrides messages.
/**
 * It allocates the memory for the array and calls
 * weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence *
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence__create(size_t size);

/// Destroy array of msg/LpsSaNvmCalOnTheFlyTiltOverrides messages.
/**
 * It calls
 * weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
void
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence__destroy(weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence * array);

/// Check for msg/LpsSaNvmCalOnTheFlyTiltOverrides message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_weigh_app_interfaces
bool
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence__are_equal(const weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence * lhs, const weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence * rhs);

/// Copy an array of msg/LpsSaNvmCalOnTheFlyTiltOverrides messages.
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
weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence__copy(
  const weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence * input,
  weigh_app_interfaces__msg__LpsSaNvmCalOnTheFlyTiltOverrides__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // WEIGH_APP_INTERFACES__MSG__DETAIL__LPS_SA_NVM_CAL_ON_THE_FLY_TILT_OVERRIDES__FUNCTIONS_H_
