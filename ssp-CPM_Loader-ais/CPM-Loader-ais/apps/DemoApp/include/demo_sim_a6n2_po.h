/******************************************************************************
 **          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 **         This work contains proprietary information, which may
 **         constitute a trade secret and/or be confidential.
 **-----------------------------------------------------------------------------
 ** File: demo_sim_a6n2_po.h
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
 ** This file contains the externs for the instance specific globals.  This
 ** information is unique to a particular instance of the package.
 **
 ** This allows a single package to be instantiated multiple times w/o
 ** modification of the underlying package code.
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_demo_sim_a6n2_po_h_
#define RTW_HEADER_demo_sim_a6n2_po_h_

/* Needed for work, config and/or demo_sim_a6n2_y_t structure */
#include <demo_sim_a6n2_Pack_types.h>

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/* Work structure */
extern demo_sim_a6n2_work_t demo_sim_a6n2_work;

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#ifdef __cplusplus

extern "C" {

#endif

  /* Initialization function */
  void demo_sim_a6n2_po_init(void);

  /* 0.02 second periodic function */
  void demo_sim_a6n2_po_0(void);

#ifdef __cplusplus

}
#endif
#endif                                 /* RTW_HEADER_demo_sim_a6n2_po_h_ */
