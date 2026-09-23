/*******************************************************************************
** COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
********************************************************************************
** File name: demo_sim_model_if.c
** 
** Description: Public cycle segmentation interfaces.
*******************************************************************************/

#include <demo_sim_model_if.h>

/* Inputs */

float  pos_lift_desired = 0.f;
float  pos_lift_rate = 0.f;
float  pos_tilt_desired = 0.f;
float  pos_tilt_rate = 0.f;
float  payload_desired = 0.f;
float  payload_rate = 0.f;

/* Outputs */

float angle_lift_het = 0.f;
float pres_lift_re = 0.f;
float angle_lift = 0.f;
float angle_AFE = 0;
float angle_ABC_supplement = 0.f;
