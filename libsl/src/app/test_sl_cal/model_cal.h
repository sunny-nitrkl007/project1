/*******************************************************************************
** COPYRIGHT (C) 2009 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:  model_cal.h
DESCRIPTION:  Example generated model calibration header for tests
*******************************************************************************/
#ifndef MODEL_CAL_H_
#define MODEL_CAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#include "sl_cal_internal.h"
#include "model.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/


typedef struct {
    model_c3_is1_t c3_is1;
    /* excluded model_c4_is1_t */
    model_c4_is2_t c4_is2;
    struct
    {
        struct
        {
            uint8_t x1ref1[5];
            uint8_t x1ref3[8];
        } c3_is1;
    } external;
} model_cal_mutable_t;

extern model_cal_mutable_t model_cal_mutable;

extern const sl_cal_thread_cal_t model_cal_thread_1;

extern const sl_cal_t model_cal;

/* Deprecated */
extern const sl_cal_variant_index_t model_cal_cal_variant_index;

/*
 * The following were added to support testing
 */
extern sl_cal_variant_index_index_t variant_index_tbl[6];
extern const model_c3_is1_t model_cal_c3_is1[];
extern const model_c4_is1_t model_cal_c4_is1[];
extern const model_c4_is2_t model_cal_c4_is2[];
    
#ifdef __cplusplus
}
#endif
#endif /* MODEL_CAL_H_ */

