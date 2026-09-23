/*******************************************************************************
** COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
*****************************************************************************
File name: demo_sim_model_if.h

Description: PWM Inputs for A6N2.
*******************************************************************************/

#ifndef DEMO_SIM_MODEL_IF_H__
#define DEMO_SIM_MODEL_IF_H__

/*Target Where The File std_types.h Is Provided By Caterpillar
**     For this target, there is no AUTOSAR content, so there is
**     no conflict.
*/
#include <stdint.h>
#include <stdbool.h>
//#include <std_types.h>
//#include <cat_std_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------------- */
/* Inputs */
/* --------------------------------------------------------------------- */

extern float pos_lift_desired;

extern float  pos_lift_rate;


extern float  pos_tilt_desired;


extern float  pos_tilt_rate;

extern float  payload_desired;


extern float  payload_rate;
/* --------------------------------------------------------------------- */
/* Outputs */
/* --------------------------------------------------------------------- */

extern float angle_lift_het;

extern float pres_lift_re;

extern float angle_lift;

extern float angle_AFE;

extern float angle_ABC_supplement;


#ifdef __cplusplus
}
#endif
#endif 
