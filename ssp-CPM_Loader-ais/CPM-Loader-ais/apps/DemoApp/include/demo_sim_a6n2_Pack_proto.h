/******************************************************************************
 **          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 **         This work contains proprietary information, which may
 **         constitute a trade secret and/or be confidential.
 **-----------------------------------------------------------------------------
 ** File: demo_sim_a6n2_Pack_proto.h
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
 ** This file declares the method functions for the package object
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_demo_sim_a6n2_Pack_proto_h_
#define RTW_HEADER_demo_sim_a6n2_Pack_proto_h_
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

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#ifdef __cplusplus

extern "C" {

#endif

  void demo_sim_a6n2_method_update(
    demo_sim_a6n2_work_t *work,
    const demo_sim_a6n2_config_t *config
    );
  void demo_sim_a6n2_pack_init(
    demo_sim_a6n2_work_t *work,
    const demo_sim_a6n2_config_t *config
    );

#ifdef __cplusplus

}
#endif
#endif                                 /* RTW_HEADER_demo_sim_a6n2_Pack_proto_h_ */
