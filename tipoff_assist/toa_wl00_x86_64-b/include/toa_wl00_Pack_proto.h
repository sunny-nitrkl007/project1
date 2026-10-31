/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: toa_wl00_Pack_proto.h
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
 ** This file declares the method functions for the package object
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_toa_wl00_Pack_proto_h_
#define RTW_HEADER_toa_wl00_Pack_proto_h_
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

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#ifdef __cplusplus

extern "C" {

#endif

  void toa_wl00_method_update (
    toa_wl00_work_t *work,
    const toa_wl00_config_t *config
    );
  void toa_wl00_pack_init(
    toa_wl00_work_t *work,
    const toa_wl00_config_t *config
    );

#ifdef __cplusplus

}
#endif
#endif                                 /* RTW_HEADER_toa_wl00_Pack_proto_h_ */
