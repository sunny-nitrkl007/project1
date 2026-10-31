/*******************************************************************************
** COPYRIGHT (C) 2009 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:  model.h
DESCRIPTION:  Example generated model header for tests
*******************************************************************************/
#ifndef MODEL_H_
#define MODEL_H_

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

typedef struct
{
    const uint8_t * x1ref1;
    const uint8_t * x1ref2;
    const uint8_t * x1ref3;
    const uint8_t x1[5];
} model_c3_is1_t;

typedef struct
{
    int gain;
} model_c4_is1_t;

typedef struct
{
    int8_t vu8;
    int16_t vu16;
    int32_t vu32;
    uint8_t vs8;
    uint16_t vs16;
    uint32_t vs32;
} model_c4_is2_t;

typedef struct
{
    const model_c3_is1_t * c3_is1;
    const model_c4_is1_t * c4_is1;
    const model_c4_is2_t * c4_is2;
} model_cal_pointers_t;

extern sl_cal_variant_id_t model_input_signals[3];

extern sl_cal_variant_id_t model_output_signals[2];

extern model_cal_pointers_t model_cal_pointers;


    
#ifdef __cplusplus
}
#endif
#endif /* MODEL_H_ */
