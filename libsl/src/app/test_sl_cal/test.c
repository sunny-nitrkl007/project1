/*******************************************************************************
** COPYRIGHT (C) 2009 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:  test.c
DESCRIPTION:    Calibration runtine code tests
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "sl_cal.h"
#include "model_cal.h"
#include "std_t.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

typedef struct
{
    sl_cal_variant_id_t inputs[3];
    int cmd;
    bool_t status;
    sl_cal_variant_index_index_t indices[6];
    const void * pointers[3];
    sl_cal_variant_id_t outputs[2];
} control_test_t;

typedef struct
{
    sl_cal_variant_index_index_t indices[6];
    const sl_cal_variant_selection_t * selections;
    int selection_count;
    model_cal_mutable_t mutable_result;
} mutable_create_test_t;

typedef struct
{
    int cmd;
    bool_t status;
    sl_cal_variant_index_index_t component_index;
    sl_cal_variant_index_index_t variant_index;
    sl_cal_variant_index_index_t indices[6];
} deprecated_test_t;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Definitions
*******************************************************************************/

static const control_test_t tests[] =
{
        /*
         * test pre-init state
         */
    {
        {0, 0, 0},
        0,
        TRUE,
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0},
        {0, 0}
    },
        /*
         * test init state
         */
    {
        {0, 0, 0},
        1,
        TRUE,
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[0], &model_cal_c4_is2[0]},
        {0xFFFF, 0xFFFF}
    },
        /*
         * test sl_cal_select of 0 of 3 valid input signals
         */
    {
        {0, 0, 0},
        2,
        FALSE,
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[0], &model_cal_c4_is2[0]},
        {0xFFFF, 0xFFFF}
    },
        /*
         * test sl_cal_select of 2 of 3 valid input signals
         */
    {
        {10003, 10101, 3},
       2,
        FALSE,
        {3, 1, 0xFF, 0xFF, 0xFF, 0xFF},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[0], &model_cal_c4_is2[0]},
        {0xFFFF, 0xFFFF}
    },
        /*
         * test sl_cal_is_selected
         */
    {
       {10003, 10101, 3},
        4,
        FALSE,
        {3, 1, 0xFF, 0xFF, 0xFF, 0xFF},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[0], &model_cal_c4_is2[0]},
        {0xFFFF, 0xFFFF}
    },
        /*
         * test sl_cal_is_selected
         */
    {
       {10003, 10101, 3},
        5,
        FALSE,
        {3, 1, 0xFF, 0xFF, 0xFF, 0xFF},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[0], &model_cal_c4_is2[0]},
        {0xFFFF, 0xFFFF}
    },
        /*
         * test sl_cal_select of one valid and different input signals
         */
    {
        {10002, 10101, 10200},
        2,
        TRUE,
        {2, 1, 0, 1, 9, 0},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[9], &model_cal_c4_is2[9]},
        {10500, 10301}
    },
        /*
         * test sl_cal_is_selected
         */
    {
        {10002, 10101, 10200},
        4,
        TRUE,
        {2, 1, 0, 1, 9, 0},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[9], &model_cal_c4_is2[9]},
        {10500, 10301}
    },
        /*
         * test sl_cal_is_selected, check all
         * validate detection of wrong startup pointer
         */
    {
        {10002, 10101, 10200},
        5,
        FALSE,
        {2, 1, 0, 1, 9, 0},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[9], &model_cal_c4_is2[9]},
        {10500, 10301}
    },
        /*
         * test sl_cal_is_selected, check all
         * validate detection of wrong output
         */
    {
        {10002, 10101, 10200},
        5,
        FALSE,
        {2, 1, 0, 1, 9, 0},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[9], &model_cal_c4_is2[9]},
        {10500, 10300}
    },
        /*
         * test sl_cal_is_selected, check all
         * validate detection of corrupted independent startup index
         */
    {
        {10002, 10101, 10200},
        5,
        FALSE,
        {1, 1, 0, 1, 9, 0},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[9], &model_cal_c4_is2[9]},
        {10500, 10301}
    },
        /*
         * test sl_cal_is_selected, check all
         * validate detection of corrupted dependent index
         */
    {
        {10002, 10101, 10200},
        5,
        FALSE,
        {2, 1, 0, 0, 9, 0},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[9], &model_cal_c4_is2[9]},
        {10500, 10301}
    },
       /*
         * test sl_cal_is_selected, check all
         * THIS RESTORES THE POINTERS AND OUTPUT
         */
    {
        {10002, 10101, 10200},
        5,
        TRUE,
        {2, 1, 0, 1, 9, 0},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[9], &model_cal_c4_is2[9]},
        {10500, 10301}
    },
        /*
         * test sl_cal_select with startup input change, validate no change
         * reports success
         */
    {
        {10001, 10101, 10200},
        2,
        TRUE,
        {2, 1, 0, 1, 9, 0},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[9], &model_cal_c4_is2[9]},
        {10500, 10301}
    },
        /*
         * test sl_cal_is_selected
         */
    {
        {10002, 10101, 10200},
        4,
        TRUE,
        {2, 1, 0, 1, 9, 0},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[9], &model_cal_c4_is2[9]},
        {10500, 10301}
    },
        /*
         * test sl_cal_select with runtime input change
         * validate async changes
         * validate thread sync does not change
         * validate outputs do not change
         */
    {
        {10002, 10100, 10200},
        2,
        TRUE,
        {2, 0, 0, 1, 6, 1},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[9], &model_cal_c4_is2[6]},
        {10500, 10301}
    },
        /*
         * test sl_cal_update
         * validate thread sync changes
         * validate outputs do not change
         */
    {
        {10001, 10100, 10200},
        3,
        TRUE,
        {2, 0, 0, 1, 6, 1},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[6], &model_cal_c4_is2[6]},
        {10500, 10301}
    },
        /*
         * test sl_cal_select
         * validate startup inputs do not change
         * validate reports success
         */
    {
        {10003, 10100, 10200},
        2,
        TRUE,
        {2, 0, 0, 1, 6, 1},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[6], &model_cal_c4_is2[6]},
        {10500, 10301}
    },
        /*
         * test sl_cal_select
         * validate startup inputs do not change
         * validate reports success
         */
    {
        {5, 10100, 10200},
        2,
        TRUE,
        {2, 0, 0, 1, 6, 1},
        {&model_cal_c3_is1[1], &model_cal_c4_is1[6], &model_cal_c4_is2[6]},
        {10500, 10301}
    },
        /*
         * test re-init state
         */
    {
        {0, 0, 0},
        1,
        TRUE,
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[0], &model_cal_c4_is2[0]},
        {0xFFFF, 0xFFFF}
    },
        /*
         * test sl_cal_select 
         */
    {
        {10001, 10100, 10201},
        2,
        TRUE,
        {1, 0, 1, 0, 7, 1},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[7], &model_cal_c4_is2[7]},
        {10501, 10300}
    },
        /*
         * test re-init state
         */
    {
        {0, 0, 0},
        1,
        TRUE,
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[0], &model_cal_c4_is2[0]},
        {0xFFFF, 0xFFFF}
    },
        /*
         * test sl_cal_mutable_select with invalid input
         */
    {
        {21, 10100, 10201},
        6,
        FALSE,
        {0xFF, 0, 1, 0xFF, 0xFF, 0xFF},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[0], &model_cal_c4_is2[0]},
        {0xFFFF, 0xFFFF}
    },
        /*
         * test sl_cal_mutable_select
         * validate that 2 of 3 pointers are set to mutable
         */
    {
        {10001, 10100, 10201},
        6,
        TRUE,
        {1, 0, 1, 0, 7, 1},
        {&model_cal_mutable.c3_is1, &model_cal_c4_is1[7], &model_cal_mutable.c4_is2},
        {10501, 10300}
    },
        /*
         * test sl_cal_select
         * validate that mutable pointers do not change
         * validate that synchronized pointer does not change
         * validate that outputs do not change
         */
    {
        {10001, 10101, 10200},
        2,
        TRUE,
        {1, 1, 0, 0, 9, 0},
        {&model_cal_mutable.c3_is1, &model_cal_c4_is1[7], &model_cal_mutable.c4_is2},
        {10501, 10300}
    },
        /*
         * test sl_cal_update
         * validate that mutable pointers do not change
         * validate that non-mutable does change
         */
    {
        {10001, 10101, 10200},
        3,
        TRUE,
        {1, 1, 0, 0, 9, 0},
        {&model_cal_mutable.c3_is1, &model_cal_c4_is1[9], &model_cal_mutable.c4_is2},
        {10501, 10300}
    },
        /*
         * test re-init state
         */
    {
        {0, 0, 0},
        1,
        TRUE,
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[0], &model_cal_c4_is2[0]},
        {0xFFFF, 0xFFFF}
    },
        /*
         * test sl_cal_select 
         */
    {
        {10001, 10100, 10201},
        2,
        TRUE,
        {1, 0, 1, 0, 7, 1},
        {&model_cal_c3_is1[0], &model_cal_c4_is1[7], &model_cal_c4_is2[7]},
        {10501, 10300}
    },
};

static control_test_t result;


static bool_t run_test(
    const sl_cal_t * object,
    const control_test_t * test,
    control_test_t * result)
{
    
    {
        int i;
        for (i = 0; i < 3; i++)
        {
            model_input_signals[i] = test->inputs[i];
        }
    }
    
    switch (test->cmd)
    {
    case 0:
        result->status = TRUE;
        break;
    case 1:
        sl_cal_init(object);
        result->status = TRUE;
        break;
    case 2:
        result->status = sl_cal_select(object);
        break;
    case 3:
        sl_cal_update(object, &model_cal_thread_1);
        result->status = TRUE;
        break;
    case 4:
        result->status = sl_cal_is_selected(object, FALSE);
        break;
    case 5:
        /* selectively corrupt by copy from test to state */
        {
            int i;
            for (i = 0; i < 6; i++)
            {
                variant_index_tbl[i] = test->indices[i];
            }
        }
        model_cal_pointers.c3_is1 = test->pointers[0];
        model_cal_pointers.c4_is1 = test->pointers[1];
        model_cal_pointers.c4_is2 = test->pointers[2];
        {
            int i;
            for (i = 0; i < 2; i++)
            {
                model_output_signals[i] = test->outputs[i];
            }
        }
        result->status = sl_cal_is_selected(object, TRUE);
        break;
    case 6:
        result->status = sl_cal_mutable_select(object);
        break;
    }
    
    /*
     * read results
     */
    {
        int i;
        for (i = 0; i < 3; i++)
        {
            result->inputs[i] = model_input_signals[i];
        }
    }
    result->cmd = test->cmd;
    {
        int i;
        for (i = 0; i < 6; i++)
        {
            result->indices[i] = variant_index_tbl[i];
        }
    }
    result->pointers[0] = model_cal_pointers.c3_is1;
    result->pointers[1] = model_cal_pointers.c4_is1;
    result->pointers[2] = model_cal_pointers.c4_is2;
    {
        int i;
        for (i = 0; i < 2; i++)
        {
            result->outputs[i] = model_output_signals[i];
        }
    }

    return memcmp(test, result, sizeof(*test)) == 0;
}

static void print_result(
    char* msg,
    const control_test_t * test)
{
    int i;
    printf("%s", msg);
    for (i = 0; i < 3; i++)
    {
        printf("%5d ", test->inputs[i]);
    }
    printf("%1d ", test->cmd);
    printf("%1d ", test->status ? 1 : 0);
    for (i = 0; i < 6; i++)
    {
        printf("%3d ", test->indices[i]);
    }
    for (i = 0; i < 3; i++)
    {
        printf("%p ", test->pointers[i]);
    }
    for (i = 0; i < 2; i++)
    {
        printf("%5d ", test->outputs[i]);
    }
    printf("\n");
}

const sl_cal_variant_selection_t selections_1[] =
{
    {
        1001, /* component 1 */
        10101 /* component 1, variant 1 */
    }
};

const sl_cal_variant_selection_t selections_2[] =
{
    {
        1002,  /* component 2 */
        10200 /* component 2, variant 0 */
    },
    {
        1000, /* component 0 */
        10001 /* component 0, variant 1 */
    }
};

const sl_cal_variant_selection_t selections_3[] =
{
    {
        1001, /* component 1 */
        33 /* invalid */
    }
};

static const mutable_create_test_t mutable_create_tests[] =
{
    {
        {2, 0, 2, 0xFF, 0xFF, 0xFF},
        selections_1,
        1,
        {
            { /* c3_is1 = 1 */
                (const void*)&model_cal_mutable.external.c3_is1.x1ref1,
                (const void*)&model_cal_mutable.c3_is1.x1,
                (const void*)&model_cal_mutable.external.c3_is1.x1ref3,
                {
                    200,
                    201,
                    202,
                    203,
                    204
                }
            },
            { /* c4_is2 */
                0x12,
                0x3456,
                0x21436587,
                5,
                1,
                7,
            },
            {
                {
                    { /* x1ref1 */
                        200,
                        201,
                        202,
                        203,
                        204
                    },
                    { /* x1ref3 */
                        200,
                        201,
                        202,
                        203,
                        204,
                        0,
                        0,
                        0
                    },
                },
            },
        }
    },
    {   /* 2nd selection sets 0=1 -> 3=0 */
        {2, 0, 2, 0xFF, 0xFF, 0xFF},
        selections_2, 
        2,
        {
            {
                (const void*)&model_cal_mutable.external.c3_is1.x1ref1,
                (const void*)&model_cal_mutable.c3_is1.x1,
                (const void*)&model_cal_mutable.external.c3_is1.x1ref3,
                {
                    100,
                    101,
                    102,
                    103,
                    104
                }
            },
            { /* c4_is2 */
                0x12,
                0x3456,
                0x21436587,
                5,
                1,
                7,
            },
            {
                {
                    { /* x1ref1 */
                        100,
                        101,
                        102,
                        103,
                        104
                    },
                    { /* x1ref3 */
                        100,
                        101,
                        102,
                        103,
                        104,
                        0,
                        0,
                        0
                    },
                },
            },
        }
    },
    {   /* selection sets 0=3, invalid, old values retained */
        {2, 0, 2, 0xFF, 0xFF, 0xFF},
        selections_3,
        1,
        {
            { /* c3_is1 = 1 */
                (const void*)&model_cal_mutable.external.c3_is1.x1ref1,
                (const void*)&model_cal_mutable.c3_is1.x1,
                (const void*)&model_cal_mutable.external.c3_is1.x1ref3,
                {
                    100,
                    101,
                    102,
                    103,
                    104
                }
            },
            { /* c4_is2 */
                0x12,
                0x3456,
                0x21436587,
                5,
                1,
                7,
            },
            {
                {
                    { /* x1ref1 */
                        100,
                        101,
                        102,
                        103,
                        104
                    },
                    { /* x1ref3 */
                        100,
                        101,
                        102,
                        103,
                        104,
                        0,
                        0,
                        0
                    },
                },
            },
        }
    },
};

static void print_mutable_image(
    const model_cal_mutable_t * image_ptr)
{
    int i;

    printf("%p ", image_ptr->c3_is1.x1ref1);
    printf("%p ", image_ptr->c3_is1.x1ref2);
    printf("%p ", image_ptr->c3_is1.x1ref3);
    for (i = 0; i < 5; i++)
    {
        printf("%4d ", image_ptr->c3_is1.x1[i]);
    }
    printf("%x ", image_ptr->c4_is2.vu8);
    printf("%x ", image_ptr->c4_is2.vu16);
    printf("%x ", (unsigned)image_ptr->c4_is2.vu32);
    printf("%x ", image_ptr->c4_is2.vs8);
    printf("%x ", image_ptr->c4_is2.vs16);
    printf("%x ", (unsigned)image_ptr->c4_is2.vs32);
    for (i = 0; i < 5; i++)
    {
        printf("%4d ", image_ptr->external.c3_is1.x1ref1[i]);
    }
    for (i = 0; i < 8; i++)
    {
        printf("%4d ", image_ptr->external.c3_is1.x1ref3[i]);
    }
    printf("\n");
}
    
static bool_t run_mutable_create_test(
    const sl_cal_t * object,
    const mutable_create_test_t * test)
{
    /* directly set the active indices */
     {
        int i;
        for (i = 0; i < 6; i++)
        {
            variant_index_tbl[i] = test->indices[i];
        }
    }
   bool_t status = sl_cal_mutable_create(object,
        test->selection_count, test->selections);

    bool_t pass =  memcmp(&test->mutable_result, &model_cal_mutable,
        sizeof(model_cal_mutable)) == 0;

    printf("\n%s   status %d \n", pass ? "pass" : "fail", status ? 1 : 0);
    print_mutable_image(&test->mutable_result);
    print_mutable_image(&model_cal_mutable);

    return pass;
}

static const deprecated_test_t deprecated_tests[] =
{
        /*
         * test init
         */
    {
        0,
        TRUE,
        0,
        2,
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    },
        /*
         * test set input 0
         */
    {
        1,
        FALSE,
        0,
        2,
        {2, 0xFF, 0xFF, 1, 0xFF, 0xFF},
    },
        /*
         * test set input 1
         */
    {
        1,
        FALSE,
        1,
        1,
        {2, 1, 0xFF, 1, 0xFF, 0},
    },
        /*
         * test set input 2
         */
    {
        1,
        TRUE,
        2,
        0,
        {2, 1, 0, 1, 9, 0},
    },
        /*
         * test init (repeat all tests)
         */
    {
        0,
        TRUE,
        0,
        2,
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    },
        /*
         * test set input 0
         */
    {
        1,
        FALSE,
        0,
        2,
        {2, 0xFF, 0xFF, 1, 0xFF, 0xFF},
    },
        /*
         * test set input 1
         */
    {
        1,
        FALSE,
        1,
        1,
        {2, 1, 0xFF, 1, 0xFF, 0},
    },
        /*
         * test set input 2
         */
    {
        1,
        TRUE,
        2,
        0,
        {2, 1, 0, 1, 9, 0},
    },
};

deprecated_test_t deprecated_result;

static bool_t run_deprecated_test(
    const sl_cal_variant_index_t * deprecated_object,
    const deprecated_test_t * test,
    deprecated_test_t * result)
{
    
    switch (test->cmd)
    {
    case 0:
        sl_cal_variant_index_init(deprecated_object);
        result->status = TRUE;
        break;
    case 1:
        result->status = sl_cal_variant_index_set(deprecated_object,
            test->component_index,
            test->variant_index);
        break;
    }

    /*
     * read results
     */
    result->cmd = test->cmd;
    result->component_index = test->component_index;
    result->variant_index= test->variant_index;
    {
        int i;
        for (i = 0; i < 6; i++)
        {
            result->indices[i] = sl_cal_variant_index_get(deprecated_object, i);
        }
    }

    return memcmp(test, result, sizeof(*test)) == 0;
}

static void print_deprecated_result(
    char* msg,
    const deprecated_test_t * test)
{
    int i;
    printf("%s", msg);
    printf("%1d ", test->cmd);
    printf("%1d ", test->status ? 1 : 0);
    printf("%3d ", test->component_index);
    printf("%3d ", test->variant_index);
   for (i = 0; i < 6; i++)
    {
        printf("%3d ", test->indices[i]);
    }
    printf("\n");
}


int main(int argc, char** argv) {
    int fail_count = 0;
    int i;
    for (i = 0; i < sizeof(tests)/sizeof(*tests); i++)
    {
        bool_t success = run_test(&model_cal, &tests[i], &result);
        if (success)
        {
            print_result("pass ", &result);
        }
        else
        {
            print_result("test ", &tests[i]);
            print_result("fail ", &result);
            fail_count++;
        }
        printf("\n");
    }
    for (i = 0; i < sizeof(mutable_create_tests)/sizeof(*mutable_create_tests); i++)
    {
        bool_t success = run_mutable_create_test(&model_cal, &mutable_create_tests[i]);
        if (!success)
        {
            fail_count++;
        }
        printf("\n");
    }
    for (i = 0; i < sizeof(deprecated_tests)/sizeof(*deprecated_tests); i++)
    {
        bool_t success = run_deprecated_test(&model_cal_cal_variant_index,
            &deprecated_tests[i], &deprecated_result);
        if (success)
        {
            print_deprecated_result("pass ", &deprecated_result);
        }
        else
        {
            print_deprecated_result("test ", &deprecated_tests[i]);
            print_deprecated_result("fail ", &deprecated_result);
            fail_count++;
        }
        printf("\n");
    }
    printf("\n\n%d tests failed\n\n", fail_count);
    return fail_count > 0;
}


