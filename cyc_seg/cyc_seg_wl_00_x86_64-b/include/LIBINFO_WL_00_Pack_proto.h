/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: LIBINFO_WL_00_Pack_proto.h
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
 ** This file declares the method functions for the package object
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_LIBINFO_WL_00_Pack_proto_h_
#define RTW_HEADER_LIBINFO_WL_00_Pack_proto_h_
#include <LIBINFO_WL_00_Pack_types.h>

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
#ifdef __cplusplus

extern "C" {

#endif

  void LIBINFO_WL_00_method_update(
    LIBINFO_WL_00_work_t *work,
    const LIBINFO_WL_00_config_t *config
    );
  void LIBINFO_WL_00_pack_init(
    LIBINFO_WL_00_work_t *work,
    const LIBINFO_WL_00_config_t *config
    );

#ifdef __cplusplus

}
#endif
#endif                                 /* RTW_HEADER_LIBINFO_WL_00_Pack_proto_h_ */
