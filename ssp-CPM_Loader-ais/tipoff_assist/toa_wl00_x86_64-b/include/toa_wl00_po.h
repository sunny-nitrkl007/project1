/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: toa_wl00_po.h
 **
 ** Real-Time Workshop code generated for Simulink model toa_wl00.
 **
 ** Model version                        : 1.44
 ** Real-Time Workshop file version      : 8.13 (R2017b) 24-Jul-2017
 ** TLC version                          : 8.13 (Jul 25 2017)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.6.1
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
#ifndef RTW_HEADER_toa_wl00_po_h_
#define RTW_HEADER_toa_wl00_po_h_

/* Needed for work, config and/or toa_wl00_y_t structure */
#include <toa_wl00_Pack_types.h>

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
extern toa_wl00_work_t toa_wl00_work;

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#ifdef __cplusplus

extern "C" {

#endif

  /* Initialization function */
  void toa_wl00_po_init(void);

  /* 0.02 second periodic function */
  void toa_wl00_po_0(void);

#ifdef __cplusplus

}
#endif
#endif                                 /* RTW_HEADER_toa_wl00_po_h_ */
