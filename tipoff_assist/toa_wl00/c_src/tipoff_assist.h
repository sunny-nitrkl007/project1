/***********************************************************************
* DESCRIPTION :
*       Calculates the mass and distance of the tool pinned to a wheel
*       loader linkage and its payload.  Wraps individual model-linkage
*       combo files' functions.
*
*       Copyright Caterpillar, Inc. 2017-2019
*
***********************************************************************/


void toa_mass_and_dist_by_id(unsigned long int id, double tilt_force, double lift_force, double tilt_cyl_ext,
                             double arm_ang, double BC_len, double imu_x, double imu_y,
                             double *return_mass, double *return_dist);

void toa_tilt_sens_to_bucket_ang_by_id(unsigned long int id, double tilt_cyl_ext, double arm_ang, double BC_len,
                                       double hook_ang, double *return_tilt_sens_to_bucket_ang);
