/***********************************************************************
* DESCRIPTION :
*       Calculates the mass and distance of the tool pinned to a wheel
*       loader linkage and its payload. Calculation is efficient due
*       to reuse of common sub expressions.
*
*       Copyright Caterpillar, Inc. 2017-2022
*
* GENERATED :
*       2022-03-17T18:51:43-05:00 by non_bucket_cpm
*
***********************************************************************/
#ifndef _TIPOFF_ASSIST_962_14A_HL_H_
#define _TIPOFF_ASSIST_962_14A_HL_H_

void mass_and_dist_962_14A_HL(double tilt_force, double lift_force, double lever_ang, double arm_ang, double BC_len,
                   double imu_x, double imu_y, double *return_mass, double *return_dist);

void tilt_sens_to_bucket_ang_962_14A_HL(
    double tilt_cyl_ext, double arm_ang, double BC_len, double hook_ang,
    double *return_tilt_sens_to_bucket_ang
);

double lever_ang_from_tilt_cyl_ext_962_14A_HL(double tilt_cyl_ext, double arm_ang);

double bucket_ang_from_tilt_cyl_ext_962_14A_HL(double tilt_cyl_ext, double arm_ang, double BC_len, double hook_ang);

#endif
