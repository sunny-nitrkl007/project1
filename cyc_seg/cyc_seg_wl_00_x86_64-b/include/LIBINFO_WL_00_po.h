/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: LIBINFO_WL_00_po.h
 **
 ** Real-Time Workshop code generated for Simulink model LIBINFO_WL_00.
 **
 ** Model version                        : 1.118
 ** Real-Time Workshop file version      : 8.3 (R2012b) 20-Jul-2012
 ** TLC version                          : 8.3 (Jul 21 2012)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.3.3
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
#ifndef RTW_HEADER_LIBINFO_WL_00_po_h_
#define RTW_HEADER_LIBINFO_WL_00_po_h_

/* Needed for standard types in function prototype */
#include <std_t.h>

/* Needed for work, config and/or LIBINFO_WL_00_y_t structure */
#include <LIBINFO_WL_00_Pack_types.h>

/* Needed for sl_cal_t object provided by System Architect */
#include <sl_cal.h>

/* Needed for others defining data structures */
#include <LIBINFO_WL_00_variant.h>

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
extern LIBINFO_WL_00_work_t LIBINFO_WL_00_work;

/* sl_cal_t object defined by System Architect */
extern const sl_cal_t LIBINFO_WL_00_cal;

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/

/* lib_machine develop module copy function */
uint_least16_t LIBINFO_WL_00_DevelopCopyFcn(uint_least16_t des_id, uint_least8_t
  *unused) ;

/* Initialization function */
void LIBINFO_WL_00_po_init(void);

/* 0.12 second periodic function */
void LIBINFO_WL_00_po_0(void);

#endif                                 /* RTW_HEADER_LIBINFO_WL_00_po_h_ */
