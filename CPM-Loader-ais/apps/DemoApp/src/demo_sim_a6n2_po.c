/******************************************************************************
 **          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 **         This work contains proprietary information, which may
 **         constitute a trade secret and/or be confidential.
 **-----------------------------------------------------------------------------
 ** File: demo_sim_a6n2_po.c
 **
 ** Real-Time Workshop code generated for Simulink model demo_sim_a6n2.
 **
 ** Model version                        : 1.42
 ** Real-Time Workshop file version      : 8.13 (R2017b) 24-Jul-2017
 ** MATLAB Version                       : 9.3.0.948333 (R2017b) Update 9
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.6.5
 **
 ******************************************************************************/

/*
 ** This file contains the 'Package Object'.  This file (and any generated CAT
 ** map files) contain all information unique to a particular instance of the
 ** package.
 **
 ** This allows a single package to be instantiated multiple times w/o
 ** modification of the underlying package code.
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#include <demo_sim_a6n2_po.h>
#include <demo_sim_a6n2_Pack_proto.h>
#include <demo_sim_a6n2_Pack_types.h>
#include <demo_sim_a6n2_private.h>
#include <demo_sim_model_if.h>
#include <demo_sim_a6n2_types.h>
#include <demo_sim_a6n2_variant.h>

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/
demo_sim_a6n2_work_t demo_sim_a6n2_work;

/* Package config struct initialization: demo_sim_a6n2 */
static const demo_sim_a6n2_config_t demo_sim_a6n2_config = {
  {
    /* Package Interface. */
    {
      /* Inport mapping. */
      &pos_lift_desired,               /* 001  SrcHeader: demo_sim_model_if.h, demo_sim_model_if.h
                                          desired lift position */
      &pos_lift_rate,                  /* 002  SrcHeader: demo_sim_model_if.h, demo_sim_model_if.h
                                          desired lift position rate */
      &pos_tilt_desired,               /* 003  SrcHeader: demo_sim_model_if.h, demo_sim_model_if.h
                                          desired tilt position */
      &pos_tilt_rate,                  /* 004  SrcHeader: demo_sim_model_if.h, demo_sim_model_if.h
                                          desired tilt position rate */
      &payload_desired,                /* 005  SrcHeader: demo_sim_model_if.h, demo_sim_model_if.h
                                          desired payload */

      /*
         &payload_rate, 006  SrcHeader: demo_sim_model_if.h, demo_sim_model_if.h
         desired payload rate

       */
    },

    {
      /* Outport mapping. */
      &angle_lift_het,                 /* 001  SrcHeader: demo_sim_model_if.h
                                          pres lift he */
      &pres_lift_re,                   /* 002  SrcHeader: demo_sim_model_if.h
                                          pres lift re */
      &angle_lift,                     /* 003  SrcHeader: demo_sim_model_if.h
                                          angle lift */
      &angle_AFE,                      /* 004  SrcHeader: demo_sim_model_if.h
                                          angle AFE */
      &angle_ABC_supplement,           /* 005  SrcHeader: demo_sim_model_if.h
                                          Angle ABC supplement */
    }
  }
};

/* Initialization Function */
void demo_sim_a6n2_po_init(void)
{
  demo_sim_a6n2_pack_init( &demo_sim_a6n2_work, &demo_sim_a6n2_config );
}

/* 0.02 second periodic function */
void demo_sim_a6n2_po_0(void)
{
  demo_sim_a6n2_method_update( &demo_sim_a6n2_work, &demo_sim_a6n2_config );
}

/*Additional Definitions*/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
