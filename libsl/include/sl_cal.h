/*******************************************************************************
** COPYRIGHT (C) 2009 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:  sl_cal.h
DESCRIPTION:  Calibration Component support


*******************************************************************************/
#ifndef SL_CAL_H_
#define SL_CAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#include "std_t.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

#define SL_CAL_UNDEFINED_ID UINT_LEAST16_MAX


/*
 * index of variant type
 */
typedef uint_least8_t sl_cal_variant_index_index_t;


/*
 * variant id type
 */
typedef uint_least16_t sl_cal_variant_id_t;


/*
 * thread calibration type
 */
struct sl_cal_thread_cal_s;
typedef struct sl_cal_thread_cal_s sl_cal_thread_cal_t;


/*
 * Calibration top-level type
 */
struct sl_cal_s;
typedef struct sl_cal_s sl_cal_t;


/*
 * variant selection type
 */
typedef struct {

    /*
     * id of a component
     */
    sl_cal_variant_id_t component_id;

    /*
     * id of a variant in the component
     */
    sl_cal_variant_id_t variant_id;
} sl_cal_variant_selection_t;


/*
 * variant index control type
 *
 * DEPRECATED
 */
typedef struct {
    const sl_cal_t * object;
} sl_cal_variant_index_t;


/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

void sl_cal_init(
    const sl_cal_t * object);

bool_t sl_cal_select(
    const sl_cal_t * object);

bool_t sl_cal_mutable_select(
    const sl_cal_t * object);

void sl_cal_update(
    const sl_cal_t * object,
    const sl_cal_thread_cal_t * thread_cal);

bool_t sl_cal_is_selected(
    const sl_cal_t * object,
    bool_t check_state);

bool_t sl_cal_mutable_create(
    const sl_cal_t * object,
    int selection_count,
    const sl_cal_variant_selection_t * selections);
    
/*
 * Deprecated
 */
int sl_cal_variant_index_get(
    const sl_cal_variant_index_t * deprecated_object,
    int component_index);

/*
 * Deprecated
 */
void sl_cal_variant_index_init(
    const sl_cal_variant_index_t * deprecated_object);

/*
 * Deprecated
 */
bool_t sl_cal_variant_index_set(
    const sl_cal_variant_index_t * deprecated_object,
    int component_index,
    int variant_index);


#ifdef __cplusplus
}
#endif
#endif /* SL_CAL_H_ */

