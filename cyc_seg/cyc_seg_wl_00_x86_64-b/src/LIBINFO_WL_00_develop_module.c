/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: LIBINFO_WL_00_develop_module.c
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
 ** This file contains the develop copy function for lib_machine's develop
 ** module.  This file contains information unique to a particular instance
 ** of the package, allowing a single package to be instantiated multiple
 ** times w/o modification of the underlying package code.
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#include <LIBINFO_WL_00_po.h>
#include <sl_unused_param_macro.h>

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
uint_least16_t LIBINFO_WL_00_DevelopCopyFcn(uint_least16_t des_id, uint_least8_t
  *unused)
{
  /* Local variables */
  bool_t ok;
  sl_cal_variant_selection_t varSelect[1];

  /* Mark unused arguments */
  SL_UNUSED_PARAM(unused);

  /* Setup sl_cal selection for items that differ from the current state. */
  varSelect[0].component_id = 1U;
  varSelect[0].variant_id = des_id;

  /* Copy the data */
  ok = sl_cal_mutable_create(&(LIBINFO_WL_00_cal), 1, varSelect);

  /* Return the appropriate result */
  return((uint_least16_t)ok);
}
