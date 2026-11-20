/******************************************************************************
 **          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 **         This work contains proprietary information, which may
 **         constitute a trade secret and/or be confidential.
 **-----------------------------------------------------------------------------
 ** File: demo_sim_a6n2_Pack_types.h
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
 ** This file contains the type definitions for the package object data structures
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_demo_sim_a6n2_Pack_types_h_
#define RTW_HEADER_demo_sim_a6n2_Pack_types_h_
#include <demo_sim_a6n2.h>

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/* Package Interface inport mapping: demo_sim_a6n2 */
typedef struct _demo_sim_a6n2_PackIF_u
{
  real32_T *pos_lift_desired;
  real32_T *pos_lift_rate;
  real32_T *pos_tilt_desired;
  real32_T *pos_tilt_rate;
  real32_T *payload_desired;
} demo_sim_a6n2_PackIF_u_t;

/* Package Interface outport mapping: demo_sim_a6n2 */
typedef struct _demo_sim_a6n2_PackIF_y
{
  real32_T *pres_lift_he;
  real32_T *pres_lift_re;
  real32_T *angle_lift;
  real32_T *angle_AFE;
  real32_T *angle_ABC_supplement;
} demo_sim_a6n2_PackIF_y_t;

/* Package Interface inport/outport mapping: demo_sim_a6n2 */
typedef struct _demo_sim_a6n2_PackIF
{
  demo_sim_a6n2_PackIF_u_t u;
  demo_sim_a6n2_PackIF_y_t y;
} demo_sim_a6n2_PackIF_t;

/* Package work definition: demo_sim_a6n2 */
typedef struct {
  RT_MODEL_demo_sim_a6n2 demo_sim_a6n2_M;
  D_Work_demo_sim_a6n2 D_Work;
  BlockIO_demo_sim_a6n2 BlockIO;
} demo_sim_a6n2_work_t;

/* Package config struct definition: demo_sim_a6n2 */
typedef struct {
  demo_sim_a6n2_PackIF_t PackIF;
} demo_sim_a6n2_config_t;

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#endif                                 /* RTW_HEADER_demo_sim_a6n2_Pack_types_h_ */
