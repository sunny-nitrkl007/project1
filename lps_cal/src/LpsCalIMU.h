/*
 * LpsCalIMU.h
 *
 *  Created on: Oct 16, 2019
 *      Author: pf
 */

#ifndef LPSCALIMU_H_
#define LPSCALIMU_H_

#include <LpsCalPublic.h>
#include <imuCal.h>

typedef enum {
  LpsCalIMULower,
  LpsCalIMURaise
} LpsCalIMULiftDirection;

/* Initialize IMU cals */
void LpsCalIMUInit(boolean imu_cal_enabled_flag, const LpsCalIMUCfgData *const machine_properties);

/* Called every 20ms loop during the calibration to capture
 * data during a cal raise or lower.  Note that it will be
 * called during irrelevant parts of the calibration, but
 * then will be reset before the relevant parts of the
 * calibration. At the time that the imu_cal_pitch_offset_get()
 * function is called, the higher levels will assure that the
 * most recent two (raise and lower) data collections were the
 * full bucket slow cals and that the reset function was called
 * before them.  This is expected to be the last of the full
 * bucket slow raise and lower captures.
 */
void LpsCalIMUUpdate(
        LpsCalIMULiftDirection lift_dir,
        float lift_height,
        float tilt_he_press,
        float tilt_re_pressure,
        float lift_diff_pressure,
        LpsIMUData_t* imu_data,
        float lift_angle,
        float tilt_extension,
        float steering_angle );

/* Clears out the data collected by LpsCalIMUUpdate(),
 * for preparing for a new raise or lower capture. */
void LpsCalIMUResetData(LpsCalIMULiftDirection direction_to_reset);

/* Get pitch offset and lumped weight */
void LpsCalIMUDataGet(float *pitch_offset, float *lumped_weight);

/* Start computation for imuCal data outputs */
boolean LpsCalIMUDataCompute(void);

#endif /* LPSCALIMU_H_ */
