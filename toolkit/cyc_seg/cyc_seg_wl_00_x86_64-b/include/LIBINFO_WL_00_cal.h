/*******************************************************************************
** COPYRIGHT (C) 2018 CATERPILLAR INC. ALL RIGHTS RESERVED.
**------------------------------------------------------------------------------

**  FILE NAME:  LIBINFO_WL_00_cal.h
**  DESCRIPTION:  System calibration.
**
**    !!!!!  AUTO-GENERATED, DO NOT EDIT  !!!!!
**
**  Code Generator:  com.cat.e.tool.sa.code.SACodeGen
**  Code Generator Version:  0.2.0
**  Package:  CAT.E.Information_Manage.pkg_arch.wl_00
**  Name:  libinfo_wl_00.ysa
**  Path:  lib_info_products\cyc_seg_wl\wl_00\pkg_arch\ysa\libinfo_wl_00.ysa
**  Artifact GUID:  0b36c35d-ddb6-494c-b8b5-d9e50c8265e8
**  Description:  
**  Version:  0.0.0
*******************************************************************************/


#ifndef LIBINFO_WL_00_CAL_H_
#define LIBINFO_WL_00_CAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "sl_cal_internal.h"

#include "LIBINFO_WL_00_po.h"
#include "LIBINFO_WL_if.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/



/*******************************************************************************
** -- Data Definitions --
*******************************************************************************/



  /*
   * Synchronous Calibration for thread 120ms
   */

extern const sl_cal_thread_cal_t LIBINFO_WL_00_cal_thread_120ms;



  /*
   * Synchronous Calibration for thread 1s
   */

extern const sl_cal_thread_cal_t LIBINFO_WL_00_cal_thread_1s;



  /*
   * Synchronous Calibration for thread init
   */

extern const sl_cal_thread_cal_t LIBINFO_WL_00_cal_thread_init;



  /*
   * Calibration
   */

extern const sl_cal_t LIBINFO_WL_00_cal;





#ifdef __cplusplus
}
#endif
#endif /* LIBINFO_WL_00_CAL_H_ */
