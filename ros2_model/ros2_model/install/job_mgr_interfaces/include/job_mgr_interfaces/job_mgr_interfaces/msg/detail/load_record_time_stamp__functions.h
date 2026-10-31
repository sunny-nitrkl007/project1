// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from job_mgr_interfaces:msg/LoadRecordTimeStamp.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "job_mgr_interfaces/msg/load_record_time_stamp.h"


#ifndef JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__FUNCTIONS_H_
#define JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__FUNCTIONS_H_

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
#include "job_mgr_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "job_mgr_interfaces/msg/detail/load_record_time_stamp__struct.h"

/// Initialize msg/LoadRecordTimeStamp message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * job_mgr_interfaces__msg__LoadRecordTimeStamp
 * )) before or use
 * job_mgr_interfaces__msg__LoadRecordTimeStamp__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
bool
job_mgr_interfaces__msg__LoadRecordTimeStamp__init(job_mgr_interfaces__msg__LoadRecordTimeStamp * msg);

/// Finalize msg/LoadRecordTimeStamp message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
void
job_mgr_interfaces__msg__LoadRecordTimeStamp__fini(job_mgr_interfaces__msg__LoadRecordTimeStamp * msg);

/// Create msg/LoadRecordTimeStamp message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * job_mgr_interfaces__msg__LoadRecordTimeStamp__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
job_mgr_interfaces__msg__LoadRecordTimeStamp *
job_mgr_interfaces__msg__LoadRecordTimeStamp__create(void);

/// Destroy msg/LoadRecordTimeStamp message.
/**
 * It calls
 * job_mgr_interfaces__msg__LoadRecordTimeStamp__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
void
job_mgr_interfaces__msg__LoadRecordTimeStamp__destroy(job_mgr_interfaces__msg__LoadRecordTimeStamp * msg);

/// Check for msg/LoadRecordTimeStamp message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
bool
job_mgr_interfaces__msg__LoadRecordTimeStamp__are_equal(const job_mgr_interfaces__msg__LoadRecordTimeStamp * lhs, const job_mgr_interfaces__msg__LoadRecordTimeStamp * rhs);

/// Copy a msg/LoadRecordTimeStamp message.
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
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
bool
job_mgr_interfaces__msg__LoadRecordTimeStamp__copy(
  const job_mgr_interfaces__msg__LoadRecordTimeStamp * input,
  job_mgr_interfaces__msg__LoadRecordTimeStamp * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
const rosidl_type_hash_t *
job_mgr_interfaces__msg__LoadRecordTimeStamp__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
const rosidl_runtime_c__type_description__TypeDescription *
job_mgr_interfaces__msg__LoadRecordTimeStamp__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
const rosidl_runtime_c__type_description__TypeSource *
job_mgr_interfaces__msg__LoadRecordTimeStamp__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
const rosidl_runtime_c__type_description__TypeSource__Sequence *
job_mgr_interfaces__msg__LoadRecordTimeStamp__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/LoadRecordTimeStamp messages.
/**
 * It allocates the memory for the number of elements and calls
 * job_mgr_interfaces__msg__LoadRecordTimeStamp__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
bool
job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence__init(job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence * array, size_t size);

/// Finalize array of msg/LoadRecordTimeStamp messages.
/**
 * It calls
 * job_mgr_interfaces__msg__LoadRecordTimeStamp__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
void
job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence__fini(job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence * array);

/// Create array of msg/LoadRecordTimeStamp messages.
/**
 * It allocates the memory for the array and calls
 * job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence *
job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence__create(size_t size);

/// Destroy array of msg/LoadRecordTimeStamp messages.
/**
 * It calls
 * job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
void
job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence__destroy(job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence * array);

/// Check for msg/LoadRecordTimeStamp message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
bool
job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence__are_equal(const job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence * lhs, const job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence * rhs);

/// Copy an array of msg/LoadRecordTimeStamp messages.
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
ROSIDL_GENERATOR_C_PUBLIC_job_mgr_interfaces
bool
job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence__copy(
  const job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence * input,
  job_mgr_interfaces__msg__LoadRecordTimeStamp__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // JOB_MGR_INTERFACES__MSG__DETAIL__LOAD_RECORD_TIME_STAMP__FUNCTIONS_H_
