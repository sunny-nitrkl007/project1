/*******************************************************************************
** COPYRIGHT (C) 2009 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:  model_cal.c
DESCRIPTION:    Example generated model calibration for tests
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "model_cal.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Definitions
*******************************************************************************/

const model_c3_is1_t model_cal_c3_is1[2] =
{
    {
        model_cal_c3_is1[0].x1,
        model_cal_c3_is1[0].x1,
        model_cal_c3_is1[0].x1,
        {
            100,
            101,
            102,
            103,
            104
        }
    },
    {
        model_cal_c3_is1[1].x1,
        model_cal_c3_is1[1].x1,
        model_cal_c3_is1[1].x1,
        {
            200,
            201,
            202,
            203,
            204
        }
    }
};

const model_c4_is1_t model_cal_c4_is1[12] =
{
    {
        500
    },
    {
        501
    },
    {
        502
    },
    {
        503
    },
    {
        504
    },
    {
        505
    },
    {
        506
    },
    {
        507
    },
    {
        508
    },
    {
        509
    },
    {
        510
    },
    {
        512
    },
};


const model_c4_is2_t model_cal_c4_is2[12] =
{
    {
        10,
        11,
        12,
        -13,
        -14,
        -15,
    },
    {
        20,
        21,
        22,
        -23,
        -24,
        -25,
    },
    {
        30,
        31,
        32,
        -33,
        -34,
        -35,
    },
    {
        10,
        11,
        12,
        -13,
        -14,
        -15,
    },
    {
        20,
        21,
        22,
        -23,
        -24,
        -25,
    },
    {
        30,
        31,
        32,
        -33,
        -34,
        -35,
    },
    {
        10,
        11,
        12,
        -13,
        -14,
        -15,
    },
    {
        20,
        21,
        22,
        -23,
        -24,
        -25,
    },
    {
        30,
        31,
        32,
        -33,
        -34,
        -35,
    },
    {
        10,
        11,
        12,
        -13,
        -14,
        -15,
    },
    {
        20,
        21,
        22,
        -23,
        -24,
        -25,
    },
    {
        30,
        31,
        32,
        -33,
        -34,
        -35,
    },
};

static const sl_cal_variant_id_t component_ids[] =
{
    1000, /* component 0 */
    1001, /* component 1 */
    1002  /* component 2 */
};

static const sl_cal_variant_id_t variant_ids_component_0[] =
{
    10000, /* component 0, variant 0 */
    10001, /* component 0, variant 1 */
    10002, /* component 0, variant 1 */
    10003, /* component 0, variant 1 */
};

static const sl_cal_variant_id_t variant_ids_component_1[] =
{
    10100, /* component 1, variant 0 */
    10101, /* component 1, variant 1 */
};

static const sl_cal_variant_id_t variant_ids_component_2[] =
{
    10200, /* component 2, variant 0 */
    10201, /* component 2, variant 1 */
    10202, /* component 2, variant 2 */
};

static const sl_cal_variant_id_t variant_ids_component_3[] =
{
    10300, /* component 3, variant 0 */
    10301, /* component 3, variant 1 */
};

static const sl_cal_variant_id_t variant_ids_component_5[] =
{
    10500, /* component 5, variant 0 */
    10501, /* component 5, variant 1 */
};

static sl_cal_input_signal_ref_t input_signals[] =
{
    {
        variant_ids_component_0,
        &model_input_signals[0]
    },
    {
        variant_ids_component_1,
        &model_input_signals[1]
    },
    {
        variant_ids_component_2,
        &model_input_signals[2]
    }
};

static sl_cal_output_signal_ref_t output_signals[] =
{
    {
        5,
        variant_ids_component_5,
        &model_output_signals[0]
    },
    {
        3,
        variant_ids_component_3,
        &model_output_signals[1]
    }
};

static const uint_least8_t variant_counts[] =
{
    4, /* variant count for calibration component 0 (independent startup) */
    2, /* variant count for calibration component 1 (independent runtime) */
    3, /* variant count for calibration component 2 (independent runtime) */
    2, /* variant count for calibration component 3 (dependent startup) */
    12, /* variant count for calibration component 4 (dependent runtime) */
    2  /* variant count for calibration component 5 (dependent runtime) */
};

    /* calibration component 3 */
static const sl_cal_variant_index_constraints_t constraints_3[] =
{
    1, /* controlled by 1 other components */
    0, /* calibration component 0 */
    1, /* when calibration component 0=0 */
    0, /* when calibration component 0=1 */
    1, /* when calibration component 0=2 */
    1  /* when calibration component 0=3 */
}; 

    /* calibration component 4 */
static const sl_cal_variant_index_constraints_t constraints_4[] =
{
    2, /* controlled by 2 other components */
    1, 2, /* calibration component 1 and 2 */
    6,  /* when calibration component 1=0, and calibration component 2=0 */
    7,  /* when calibration component 1=0, and calibration component 2=1 */
    8,  /* when calibration component 1=0, and calibration component 2=2 */
    9,  /* when calibration component 1=1, and calibration component 2=0 */
    10, /* when calibration component 1=1, and calibration component 2=1 */
    11  /* when calibration component 1=1, and calibration component 2=2 */
}; 

    /* calibration component 5 */
static const sl_cal_variant_index_constraints_t constraints_5[] =
{
    1, /* controlled by 1 other components */
    1, /* calibration component 1 */
    1, /* when calibration component 1=0 */
    0  /* when calibration component 1=1 */
}; 

static const sl_cal_variant_index_constraints_t * const constraints[] =
{
    constraints_3,
    constraints_4,
    constraints_5
};

#define INDEX_AND_SIZE(INDEX, SIZE) ((INDEX << 24) | SIZE)

static const sl_cal_instance_ref_t instance_refs[] =
{
    /* startup */
    {
        INDEX_AND_SIZE(3, sizeof(model_c3_is1_t)),
        model_cal_c3_is1,                            /* variant table */
        (const void **)&model_cal_pointers.c3_is1    /* variant pointer */
    },
    /* asynchronous */
    {
        INDEX_AND_SIZE(4, sizeof(model_c4_is2_t)),
        model_cal_c4_is2,                            /* variant table */
        (const void **)&model_cal_pointers.c4_is2    /* variant pointer */
    },
    /* thread 1 synchronous */
    {
        INDEX_AND_SIZE(4, sizeof(model_c4_is1_t)),
        model_cal_c4_is1,                            /* variant table */
        (const void **)&model_cal_pointers.c4_is1    /* variant pointer */
    }
};

model_cal_mutable_t model_cal_mutable;

static void * const addresses[] = {

    /* mutable image for each instance reference */
    &model_cal_mutable.c3_is1,
    &model_cal_mutable.c4_is2,
    NULL,
    
    /* ref and image for each internal array */
    &model_cal_mutable.c3_is1.x1ref2,
    &model_cal_mutable.c3_is1.x1,
    
    /* ref, image and size for each external array */
    &model_cal_mutable.c3_is1.x1ref1,
    &model_cal_mutable.external.c3_is1.x1ref1,
    &model_cal_mutable.c3_is1.x1ref3,
    &model_cal_mutable.external.c3_is1.x1ref3,

    /* address for each value change */
    &model_cal_mutable.c4_is2.vu8,
    &model_cal_mutable.c4_is2.vu16,
    &model_cal_mutable.c4_is2.vu32,
    &model_cal_mutable.c4_is2.vs8,
    &model_cal_mutable.c4_is2.vs16,
    &model_cal_mutable.c4_is2.vs32,
};

static const uint_least32_t sizes[] =
{
    sizeof(model_cal_mutable.c3_is1.x1),
    sizeof(model_cal_mutable.c3_is1.x1)
};

static const sl_cal_mutable_value_t values[] =
{

    0x00 | 0x00 | 0x00 | 0x00,
    0x12,

    0x00 | 0x10 | 0x00 | 0x01,
    0x34,
    0x56,

    0x00 | 0x20 | 0x00 | 0x03,
    0x21,
    0x43,
    0x65,
    0x87,

    0x80 | 0x00 | 0x00 | 0x00,
    0x05,

    0x80 | 0x10 | 0x08 | 0x00,
    0x01,

    0x80 | 0x20 | 0x00 | 0x00,
    0x07
};


static sl_cal_variant_index_index_t mutable_variant_index_tbl[6];

static const sl_cal_mutable_t mutable = 
{
    1, /* number of array references to image */
    2, /* number of array references to copy of image */
    6, /* number of changed values */
    addresses, /* addresses */
    sizes, /* sizes */
    values, /* fixed values */
    mutable_variant_index_tbl /* index of variant for each component */
};

static sl_cal_state_t state;

/* non-static for testing  */
/* static */ sl_cal_variant_index_index_t variant_index_tbl[6];

const sl_cal_t model_cal =
{
    1, /* number of independent startup calibration components */
    2, /* number of independent runtime calibration components */
    1, /* number of dependent startup calibration components */
    2, /* number of dependent runtime calibration components */
    2, /* number of output signals */
    3, /* number of instance references */
    1, /* number of startup instance references */
    1, /* number of asynchronous runtime instance references */
    variant_counts, /* number of variants for each component */
    component_ids, /* component id for each independent startup */
    input_signals, /* input signals */
    output_signals, /* output signals */
    constraints, /* dependencies */
    instance_refs, /* calibration instance reference table */
    &state, /* state (except indices) */
    variant_index_tbl, /* index of variant for each component */
    &mutable /* mutable */
};

const sl_cal_thread_cal_t model_cal_thread_1 =
{
    2,
    1
};

/* Deprecated */

const sl_cal_t model_cal_for_deprecated =
{
    1, /* number of independent startup calibration components */
    2, /* number of independent runtime calibration components */
    1, /* number of dependent startup calibration components */
    2, /* number of dependent runtime calibration components */
    0, /* number of output signals */
    0, /* number of instance references */
    0, /* number of startup instance references */
    0, /* number of asynchronous runtime instance references */
    variant_counts, /* number of variants for each component */
    NULL, /* component id for each independent startup */
    NULL, /* input signals */
    NULL, /* output signals */
    constraints, /* dependencies */
    NULL, /* calibration instance reference table */
    &state, /* state (except indices) */
    variant_index_tbl, /* index of variant for each component */
    NULL /* mutable */
};

const sl_cal_variant_index_t model_cal_cal_variant_index =
{
  &(model_cal_for_deprecated)   /* calibration data */
};

