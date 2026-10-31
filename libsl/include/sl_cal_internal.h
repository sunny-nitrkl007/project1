/*******************************************************************************
** COPYRIGHT (C) 2009 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:  sl_cal_internal.h
DESCRIPTION:  Calibration Component support


*******************************************************************************/
#ifndef SL_CAL_INTERNAL_H_
#define SL_CAL_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#include "std_t.h"
#include "sl_cal.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/*
 * variant index constraints type
 */
typedef uint_least8_t sl_cal_variant_index_constraints_t;


/*
 * mutable image value fix type
 *
 * mode byte or 1 byte of value where mode is:
 *  image type                (mask 0xF0)
 *  number of value bytes - 1 (mask 0x03)
 */
typedef uint_least8_t sl_cal_mutable_value_t;


/*
 * input signal reference type
 */
typedef struct {

    /*
     * variant ids for component
     */
    const sl_cal_variant_id_t * variant_ids;

    /*
     * pointer to signal
     */
    sl_cal_variant_id_t * signal_ptr;
} sl_cal_input_signal_ref_t;


/*
 * output signal reference type
 */
typedef struct {

    /*
     * index of controlling component
     */
    sl_cal_variant_index_index_t index;

    /*
     * variant ids for component
     */
    const sl_cal_variant_id_t * variant_ids;

    /*
     * pointer to signal
     */
    sl_cal_variant_id_t * signal_ptr;
} sl_cal_output_signal_ref_t;


/*
 * calibration instance reference type
 */
typedef struct {

    /*
     * index of controlling component (mask 0xFF000000)
     * size of a variant in the table (mask 0x00FFFFFF)
     */
    uint_least32_t index_and_size;

    /*
     * array of calibration component variant data
     */
    const void * variant_table;

    /*
     * software component pointer to variant data
     */
    const void ** variant_ptr;
} sl_cal_instance_ref_t;


/*
 * calibration state data
 */
typedef struct {

    /*
     * internal key to enable startup selections
     */
    uint_least32_t unlock_key;
} sl_cal_state_t;


/*
 * Calibration mutable
 */
typedef struct {

    /*
     * number of array references to image
     */
    uint_least16_t internal_array_count;

    /*
     * number of array references to copy of image
     */
    uint_least16_t external_array_count;

    /*
     * number of changed values
     */
    uint_least16_t value_change_count;

    /*
     * addresses within mutable image in following order:
     *   mutable image for each instance reference
     *   ref and image for each internal array
     *   ref, image and size for each external array
     *   address for each value change
     */
    void * const * image_addresses;

    /*
     * sizes for each external array
     */
    const uint_least32_t * sizes;

    /*
     * values
     */
    const sl_cal_mutable_value_t * values;

    /*
     * index of variant for each component
     * (non-state, local to sl_cal_mutable_create)
     */
    sl_cal_variant_index_index_t * variant_index_tbl;
} sl_cal_mutable_t;


/*
 * thread calibration type
 */
struct sl_cal_thread_cal_s {

    /*
     * start index in calibration instance reference table
     */
    uint_least16_t start;

    /*
     * number of calibration instance references
     */
    uint_least16_t count;
};


/*
 * Calibration top-level type
 */
struct sl_cal_s {

    /*
     * number of independent startup calibration components
     */
    uint_least8_t independent_startup_count;

    /*
     * number of independent runtime calibration components
     */
    uint_least8_t independent_runtime_count;

    /*
     * number of dependent startup calibration components
     */
    uint_least8_t dependent_startup_count;

    /*
     * number of dependent runtime calibration components
     */
    uint_least8_t dependent_runtime_count;

    /*
     * number of output signals
     */
    uint_least16_t output_count;

    /*
     * number of instance references
     */
    uint_least16_t instance_ref_count;

    /*
     * number of startup instance references
     */
    uint_least16_t startup_instance_ref_count;

    /*
     * number of asynchronous runtime instance references
     */
    uint_least16_t asynch_instance_ref_count;

    /*
     * number of variants for each component
     */
    const uint_least8_t * variant_count;

    /*
     * component id for each independent startup
     */
    const sl_cal_variant_id_t * component_ids;

    /*
     * input signals
     *   each independent startup
     *   each independent runtime
     */
    const sl_cal_input_signal_ref_t * input_signals;

    /*
     * output signals
     */
    const sl_cal_output_signal_ref_t * output_signals;

    /*
     * dependencies
     */
    const sl_cal_variant_index_constraints_t * const * constraints;

    /*
     * calibration instance reference table
     *   all startup
     *   all asynchronous
     *   each thread synchronous range
     */
    const sl_cal_instance_ref_t * instance_ref;

    /*
     * state (except indices)
     */
    sl_cal_state_t * state;
    
    /*
     * index of variant for each component
     *   each independent startup
     *   each independent runtime
     *   each dependent startup
     *   each dependent runtime
     */
    sl_cal_variant_index_index_t * variant_index_tbl;
    
    /*
     * mutable image (optional)
     */
    const sl_cal_mutable_t * mutable;
};



/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/



#ifdef __cplusplus
}
#endif
#endif /* SL_CAL_INTERNAL_H_ */

