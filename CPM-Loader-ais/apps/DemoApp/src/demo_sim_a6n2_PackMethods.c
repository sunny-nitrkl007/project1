/******************************************************************************
 **          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 **         This work contains proprietary information, which may
 **         constitute a trade secret and/or be confidential.
 **-----------------------------------------------------------------------------
 ** File: demo_sim_a6n2_PackMethods.c
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
 ** This file contains the functions which provide a Package
 ** Architecture interface for the generated functions
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#include <demo_sim_a6n2.h>
#include <demo_sim_a6n2_private.h>
#include <demo_sim_a6n2_Pack_proto.h>
#include <demo_sim_a6n2_po.h>
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

/******************************************************************************
 * FUNCTION NAME         : demo_sim_a6n2_method_update - 0.02 second
 * DESCRIPTION           :
 *
 * PARAMETER DESCRIPTION :
 *
 * RETURN VALUE:
 * void
 ******************************************************************************/
void demo_sim_a6n2_method_update(
  demo_sim_a6n2_work_t *work,
  const demo_sim_a6n2_config_t *config
  )
{
  /* Pre model step function code */

  /* Execute model step function. */
  demo_sim_a6n2_step(
                     &(work->demo_sim_a6n2_M),
                     *(config->PackIF.u.pos_lift_desired),
                     *(config->PackIF.u.pos_lift_rate),
                     *(config->PackIF.u.pos_tilt_desired),
                     *(config->PackIF.u.pos_tilt_rate),
                     *(config->PackIF.u.payload_desired),
                     config->PackIF.y.pres_lift_he,
                     config->PackIF.y.angle_lift,
                     config->PackIF.y.angle_AFE,
                     config->PackIF.y.angle_ABC_supplement);

  /* Get model outputs here */

  /* Post model step function code */
}

/******************************************************************************
 * FUNCTION NAME         : demo_sim_a6n2_pack_init
 * DESCRIPTION           :
 *
 * PARAMETER DESCRIPTION :
 *
 * RETURN VALUE:
 * void
 ******************************************************************************/
void demo_sim_a6n2_pack_init(
  demo_sim_a6n2_work_t *work,
  const demo_sim_a6n2_config_t *config
  )
{
  /* Initialize the Model Structure (RTM) DWork */
  rtmSetRootDWork(&(work->demo_sim_a6n2_M),&(work->D_Work));

  /* Initialize the Model Structure (RTM) BlockIO */
  rtmSetBlockIO(&(work->demo_sim_a6n2_M),&(work->BlockIO));

  /* Execute Model Initializations */
  demo_sim_a6n2_initialize(
    &(work->demo_sim_a6n2_M),
    config->PackIF.y.pres_lift_re);

  /* Mark unused arguements */
  SL_UNUSED_PARAM(work);
  SL_UNUSED_PARAM(config);
}
