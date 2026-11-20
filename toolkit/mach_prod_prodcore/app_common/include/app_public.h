/******************************************************************************
*** FILE:
*** app_public.h
***
*** COPYRIGHT NOTICE:
*** Copyright 2014.  Caterpillar Inc.  All Rights Reserved.
*** This work contains Caterpillar's proprietary information which
*** may constitute a trade secret and/or be confidential.  Copyright
*** notice is precautionary only and does not imply publication.
***
*** DESCRIPTION:
*** This is the definition include file for the application module.
*** All of the contents in this file are intended for other tasks/modules
*** to use.
******************************************************************************/
#ifndef APP_PUBLIC_H_
#define APP_PUBLIC_H_

#ifndef SCL_BLK_COMPOSITE_H_
#include <scl_blk_composite.h>
#endif

#ifndef HAL_TIME_H_
#include <hal_time.h>
#endif

#ifndef INTERFACE_H_
#include <interface.h>
#endif

#define MG_TRANS_120_02  12002


#define GENERIC_APP   UNKNOWN2U  /* Invalid Harness Code  */
#define GENERIC_APP_1 0x00AF  /* Generic Application 1 */
#define GENERIC_APP_2 0x00AD  /* Generic Application 2 */

/*Application Module Loop Time In Seconds*/
#define APP_LPTIM   0.040
/*****************************************************************************/
/*****                   EH Array Size Utility Macros                    *****/

/*MACRO:  EH_ARRAY_ENTRIES(ARRAY_VARIABLE_NAME)
**BEFORE: Returns the number of entries in an array of any type of
**        structures.
**
**        ARRAY_VARIABLE_NAME
**             An array variable which (in the scope of this macro invocation)
**             the number of entries are known.
**
**             For example, the following is legal
**                  extern int_16 array[42];
**                  ...
**                  unsigned_8 size = EH_ARRAY_ENTRIES(array);
**
**             while the following is not
**
**                  extern int_16 array[];
**                  ...
**                  unsigned_8 size = EH_ARRAY_ENTRIES(array);
**             .
**
**AFTER:  Returns a constant expression that represents the
**        number of entries in the array.
*/
#define EH_ARRAY_ENTRIES(ARRAY_VARIABLE_NAME)                                \
                                         (  sizeof (ARRAY_VARIABLE_NAME) /   \
                                            sizeof (ARRAY_VARIABLE_NAME[0])  \
                                         )



#define MAX_1X_TIME_REFERENCE_INDEX 1000


















extern const scl_blk_composite_t app_features_8x_obj;
extern const scl_blk_composite_t app_features_4x_obj;
extern const scl_blk_composite_t app_features_2x_obj;
extern const scl_blk_composite_t app_features_1x_obj;

/* Feature Object structure */
typedef struct
{
    /* Must be 1st member */
    scl_blk_t base;

    /* Inputs */
    struct
    {
        /* Run this feature */
        bool_least_t* p_run;
    } in;

    /* Outputs */
    struct
    {
        /* Confidence Percentage */
        scl_blk_qu16_signal_t* p_output;
    } out;

    /* Configuration (NONE) */
    /* Workspace (NONE)*/

} FeatureObj_t;


/*****************************************************************************/

#endif /* APP_PUBLIC_H_ */
