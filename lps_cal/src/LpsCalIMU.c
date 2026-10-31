/*
 * LpsCalIMU.c
 *
 *  Created on: Oct 16, 2019
 *      Author: pf
 */
#include "LpsCalIMU.h"
#include <rtwtypes.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

static void LpsCalIMUResetInputs(void);
static void LpsCalIMUCopyMachineProperties(void);

static RT_MODEL_imuCal_T imuCal_M_;
static RT_MODEL_imuCal_T *const imuCal_M = &imuCal_M_;/* Real-time model */
static ExtU_imuCal_T imuCal_U;         /* External inputs */
static ExtY_imuCal_T imuCal_Y;         /* External outputs */
static const ExtU_imuCal_T imuCal_U_Empty = {0};  /* zero initialized empty struct  */
static boolean LpsCalIMUEnableFlag = false;

static const LpsCalIMUCfgData* LpsCalIMUCfgDataPtr;

static int imuCalComputeInProgress = 0;
static int imuCalComputeStarted = 0;
static float imuCalPitchOffset = 0.f;
static float imuCalLumpedWeight = 0.f;

void *threadComputeCal(void *vargp)
{
    /* Call the update function */
    imuCal_fcn_call(imuCal_M);

    // save off the data
    imuCalPitchOffset = imuCal_Y.pitchOffset;
    imuCalLumpedWeight = imuCal_Y.lumpedWeight;

    imuCalComputeInProgress = 0;

    pthread_exit(NULL);

    return NULL;
}

static void LpsCalIMUResetInputs(void)
{
    imuCal_U = imuCal_U_Empty;
    LpsCalIMUCopyMachineProperties();
    return;
}

static void LpsCalIMUCopyMachineProperties(void) {
    if (LpsCalIMUCfgDataPtr) {
        imuCal_U.toa_appNumber = LpsCalIMUCfgDataPtr->internal_msn;
        imuCal_U.toa_liftBoreDia = LpsCalIMUCfgDataPtr->lift_bore_diameter;
        imuCal_U.toa_tiltBoreDia = LpsCalIMUCfgDataPtr->tilt_bore_diameter;
        imuCal_U.toa_tiltNumCyl = LpsCalIMUCfgDataPtr->num_of_tilt_cylinders;
        imuCal_U.toa_tiltRodDia = LpsCalIMUCfgDataPtr->tilt_rod_diameter;
        imuCal_U.toa_toolBcLength = LpsCalIMUCfgDataPtr->tool_bc_length;
    }
}

void LpsCalIMUInit(boolean imu_cal_enabled_flag, const LpsCalIMUCfgData *const cfg_data)
{
    /* return if imu calibrations disabled */
    LpsCalIMUEnableFlag = imu_cal_enabled_flag;
    if (!LpsCalIMUEnableFlag) {
        return;
    }

    /* Initialize the machine property pointer */
    LpsCalIMUCfgDataPtr = cfg_data;

    /* Reset inputs */
    LpsCalIMUResetInputs();

    /* Pack model data into RTM */
    imuCal_M->inputs = &imuCal_U;
    imuCal_M->outputs = &imuCal_Y;

    /* Initialize model */
    imuCal_initialize(imuCal_M);
}

void LpsCalIMUUpdate(
        LpsCalIMULiftDirection lift_dir,
        float lift_height,
        float tilt_he_press,
        float tilt_re_pressure,
        float lift_diff_pressure,
        LpsIMUData_t* imu_data,
        float lift_angle,
        float tilt_extension,
        float steering_angle )
{
    /* return if disabled */
    if (!LpsCalIMUEnableFlag) {
        return;
    }

    /* Reset inputs */
    LpsCalIMUResetInputs();

    /* Set inputs here: */
    if (LpsCalIMULower == lift_dir){
        imuCal_U.calDirectionFlag = 1;
    }
    else if (LpsCalIMURaise == lift_dir) {
        imuCal_U.calDirectionFlag = 0;
    }
    else {
        /* invalid direction */
        return;
    }

    imuCal_U.imuX = imu_data->LinAcc[0];
    imuCal_U.imuY = imu_data->LinAcc[1];
    imuCal_U.imuZ = imu_data->LinAcc[2];
    imuCal_U.liftAngle = lift_angle;
    imuCal_U.liftHeight = lift_height;
    imuCal_U.liftPress = lift_diff_pressure;
    imuCal_U.steerAngle = steering_angle;
    imuCal_U.tiltExt = tilt_extension;
    imuCal_U.tiltHePress = tilt_he_press;
    imuCal_U.tiltRePress = tilt_re_pressure;

    /* Call the update function */
    imuCal_fcn_call(imuCal_M);

    return;
}

void LpsCalIMUResetData(LpsCalIMULiftDirection direction_to_reset)
{
    /* return if disabled or compute in progress */
    if (!LpsCalIMUEnableFlag || imuCalComputeInProgress) {
        return;
    }

    /* Reset inputs */
    LpsCalIMUResetInputs();

    /* Set the reset flag for lower or raise */
    if (LpsCalIMULower == direction_to_reset) {
        imuCal_U.resetLowerFlag = 1;
    }
    else if (LpsCalIMURaise == direction_to_reset) {
        imuCal_U.resetRaiseFlag = 1;
    }
    else {
        /* invalid reset argument */
        return;
    }

    /* Call the update function */
    imuCal_fcn_call(imuCal_M);

    return;
}

void LpsCalIMUDataGet(float *pitch_offset, float *lumped_weight)
{
    /* check for null ptr or if computation is in progress */
    if (!pitch_offset || !lumped_weight ){
        return;
    }

    /* return 0's if disabled */
    if (!LpsCalIMUEnableFlag) {
        *pitch_offset = 0;
        *lumped_weight = 0;
        return;
    }

    /* Return the IMU cal ofset and lumped weight */
    *pitch_offset = imuCalPitchOffset;
    *lumped_weight = imuCalLumpedWeight;

    return;
}

/******************************************************************************
FUNCTION NAME: LpsCalIMUDataCompute
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE: true - if compute is done or not available, false if not done
*******************************************************************************/
boolean LpsCalIMUDataCompute()
{
    pthread_t thread_id;

    /* return true if disabled */
    if (!LpsCalIMUEnableFlag) {
        return true;
    }

    /* return false if started and in progress */
    if (imuCalComputeStarted) {
        if (imuCalComputeInProgress) {
            return false;
        }
        else {
            /* Compute is started and not in progress - it is complete, reset start */
            imuCalComputeStarted = 0;
            return true;
        }
    }

    /* Reset inputs */
    LpsCalIMUResetInputs();

    /* Set flag to get IMU offset */
    imuCal_U.getPitchOffsetFlag = 1;

    // create thread to compute
    imuCalComputeInProgress = 1;
    imuCalComputeStarted = 1;
    pthread_create(&thread_id, NULL, threadComputeCal, NULL);

    return false;
}
