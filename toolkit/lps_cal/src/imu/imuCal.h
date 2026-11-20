/*
 * File: imuCal.h
 *
 * Code generated for Simulink model 'imuCal'.
 *
 * Model version                  : 1.16
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Tue Feb  8 15:38:09 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_imuCal_h_
#define RTW_HEADER_imuCal_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef imuCal_COMMON_INCLUDES_
# define imuCal_COMMON_INCLUDES_
#include <stdio.h>
#include "rtwtypes.h"
#include "tipoff_assist.h"
#include "tipoff_assist_950_14A_HL.h"
#include "tipoff_assist_950_14A_LOG.h"
#include "tipoff_assist_950_14A_STD.h"
#include "tipoff_assist_950_14A_Z_HL.h"
#include "tipoff_assist_950_14A_Z_LOG.h"
#include "tipoff_assist_950_14A_Z_STD.h"
#include "tipoff_assist_962_14A_HL.h"
#include "tipoff_assist_962_14A_LOG.h"
#include "tipoff_assist_962_14A_STD.h"
#include "tipoff_assist_962_14A_Z_HL.h"
#include "tipoff_assist_962_14A_Z_STD.h"
#include "tipoff_assist_966_14A_HL.h"
#include "tipoff_assist_966_14A_LOG.h"
#include "tipoff_assist_966_14A_STD.h"
#include "tipoff_assist_972_14A_HL.h"
#include "tipoff_assist_972_14A_SL.h"
#include "tipoff_assist_972_14A_STD.h"
#include "tipoff_assist_980_14A_BLK.h"
#include "tipoff_assist_980_14A_HL.h"
#include "tipoff_assist_980_14A_HVY.h"
#include "tipoff_assist_980_14A_LOG.h"
#include "tipoff_assist_980_14A_STD.h"
#include "tipoff_assist_982_14A_HL.h"
#include "tipoff_assist_982_14A_LOG.h"
#include "tipoff_assist_982_14A_STD.h"
#endif                                 /* imuCal_COMMON_INCLUDES_ */

#include "imuCal_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<S6>/Filter' */
typedef struct {
  real32_T rawHist[3];                 /* '<S6>/Filter' */
  real32_T filtHist[3];                /* '<S6>/Filter' */
  real32_T alpha;                      /* '<S6>/Filter' */
  real32_T beta;                       /* '<S6>/Filter' */
  real32_T gamma;                      /* '<S6>/Filter' */
  uint8_T is_active_c2_lib_imuCal;     /* '<S6>/Filter' */
} DW_Filter_imuCal_T;

/* model data, for system '<S6>/Filter' */
typedef struct {
  DW_Filter_imuCal_T dwork;
} self_Filter_imuCal_T;

/* Block signals (auto storage) */
typedef struct {
  real_T toa_grav_angles[3];           /* '<S14>/euler angles from rot matrix' */
  real_T toa_sfuncInRawTiltForce;      /* '<S36>/Copy' */
  real_T toa_sfuncInRawLiftForce;      /* '<S37>/Copy' */
  real_T toa_sfuncInRawTiltExt;        /* '<S38>/Copy' */
  real_T toa_sfuncInRawLiftAng;        /* '<S39>/Copy' */
  real_T toa_sfuncInRawBcLength;       /* '<S40>/Copy' */
  real_T toa_sfuncInRawGravX;          /* '<S42>/Copy' */
  real_T toa_sfuncInRawGravY;          /* '<S43>/Copy' */
  real_T toa_sfuncOutRawMass;          /* '<S41>/Copy' */
  real_T toa_sfuncOutRawDist;          /* '<S34>/Copy' */
  real32_T toa_imu_eef_accl_vec[3];    /* '<S14>/apply calibration' */
  real32_T toa_grav_neef_vec[3];       /* '<S14>/convert "proper acceleration" to gravity' */
  real32_T toa_grav_rotMatrix[9];      /* '<S14>/rotation matrix calc from two vectors' */
  real32_T toa_grav_rotAxis[3];        /* '<S14>/rotation matrix calc from two vectors' */
  real32_T toa_imu_neef_accl_vec[3];   /* '<S14>/EEF vector to NEEF vector' */
  real32_T NEW_BUFFER[2750];
  real32_T searchLowerWeight[2750];
  real32_T weights[2750];
  real32_T phaselessTemp[2750];
  real32_T toa_tiltForce;              /* '<S12>/Copy' */
  real32_T toa_sfuncInTiltForce;       /* '<S17>/Multiply' */
  real32_T toa_liftForce;              /* '<S13>/Copy' */
  real32_T toa_sfuncInLiftForce;       /* '<S17>/Multiply1' */
  real32_T toa_sfuncInTiltExt;         /* '<S35>/Copy' */
  real32_T toa_sfuncInLiftAng;         /* '<S45>/Copy' */
  real32_T toa_sfuncInBcLength;        /* '<S44>/Copy' */
  real32_T toa_sfuncInGravX;           /* '<S17>/Signal Conversion1' */
  real32_T toa_sfuncInGravY;           /* '<S17>/Signal Conversion' */
  real32_T toa_sfuncOutRawMassTonne;   /* '<S17>/grams to tonnes' */
  real32_T toa_rawPayload;             /* '<S17>/Tool Mass Offset' */
  real32_T toa_payloadZeroed;          /* '<S17>/Apply Zero' */
  real32_T toa_payloadAdjusted;        /* '<S17>/Apply Scale Factor' */
  real32_T toa_grav_neef_xy_mag;       /* '<S25>/Math Function1' */
  real32_T toa_grav_neef_pitch_ang;    /* '<S15>/Trigonometric Function' */
  real32_T toa_rawDist;                /* '<S17>/Data Type Conversion7' */
  real32_T toa_grav_angle;             /* '<S14>/rotation matrix calc from two vectors' */
  real32_T filtered;                   /* '<S8>/Filter' */
  real32_T filtered_i;                 /* '<S7>/Filter' */
  real32_T filtered_j;                 /* '<S6>/Filter' */
} B_imuCal_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T lowerLaSlopePointsIdxs[51];   /* '<S1>/imuCal' */
  real_T raiseLaSlopePointsIdxs[51];   /* '<S1>/imuCal' */
  real_T lowerBufferIdx;               /* '<S1>/imuCal' */
  real_T lowerLaSlopePointsIdx;        /* '<S1>/imuCal' */
  real_T raiseBufferIdx;               /* '<S1>/imuCal' */
  real_T raiseLaSlopePointsIdx;        /* '<S1>/imuCal' */
  real32_T lowerBufTiltHePress[2750];  /* '<S1>/imuCal' */
  real32_T lowerBufTiltRePress[2750];  /* '<S1>/imuCal' */
  real32_T lowerBufLiftPress[2750];    /* '<S1>/imuCal' */
  real32_T lowerBufImuX[2750];         /* '<S1>/imuCal' */
  real32_T lowerBufImuY[2750];         /* '<S1>/imuCal' */
  real32_T lowerBufImuZ[2750];         /* '<S1>/imuCal' */
  real32_T lowerBufLiftAngle[2750];    /* '<S1>/imuCal' */
  real32_T lowerBufTiltExt[2750];      /* '<S1>/imuCal' */
  real32_T lowerBufSteerAngle[2750];   /* '<S1>/imuCal' */
  real32_T raiseBufTiltHePress[2750];  /* '<S1>/imuCal' */
  real32_T raiseBufTiltRePress[2750];  /* '<S1>/imuCal' */
  real32_T raiseBufLiftPress[2750];    /* '<S1>/imuCal' */
  real32_T raiseBufImuX[2750];         /* '<S1>/imuCal' */
  real32_T raiseBufImuY[2750];         /* '<S1>/imuCal' */
  real32_T raiseBufImuZ[2750];         /* '<S1>/imuCal' */
  real32_T raiseBufLiftAngle[2750];    /* '<S1>/imuCal' */
  real32_T raiseBufTiltExt[2750];      /* '<S1>/imuCal' */
  real32_T raiseBufSteerAngle[2750];   /* '<S1>/imuCal' */
  boolean_T initialized_not_empty;     /* '<S1>/imuCal' */
  boolean_T lowerStarted;              /* '<S1>/imuCal' */
  boolean_T lowerDone;                 /* '<S1>/imuCal' */
  boolean_T lowerFailed;               /* '<S1>/imuCal' */
  boolean_T lowerLaSlopePointsDone;    /* '<S1>/imuCal' */
  boolean_T raiseStarted;              /* '<S1>/imuCal' */
  boolean_T raiseDone;                 /* '<S1>/imuCal' */
  boolean_T raiseFailed;               /* '<S1>/imuCal' */
  boolean_T raiseLaSlopePointsDone;    /* '<S1>/imuCal' */
} DW_imuCal_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const real32_T MathFunction;         /* '<S33>/Math Function' */
  const real32_T Multiply2;            /* '<S33>/Multiply2' */
  const boolean_T RelationalOperator;  /* '<S31>/Relational Operator' */
  const boolean_T RelationalOperator_n;/* '<S29>/Relational Operator' */
} ConstB_imuCal_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T resetLowerFlag;               /* '<Root>/resetLowerFlag' */
  real_T resetRaiseFlag;               /* '<Root>/resetRaiseFlag' */
  real_T calDirectionFlag;             /* '<Root>/calDirectionFlag' */
  real_T getPitchOffsetFlag;           /* '<Root>/getPitchOffsetFlag' */
  real_T liftHeight;                   /* '<Root>/liftHeight' */
  real_T tiltHePress;                  /* '<Root>/tiltHePress' */
  real_T tiltRePress;                  /* '<Root>/tiltRePress' */
  real_T liftPress;                    /* '<Root>/liftPress' */
  real_T imuX;                         /* '<Root>/imuX' */
  real_T imuY;                         /* '<Root>/imuY' */
  real_T imuZ;                         /* '<Root>/imuZ' */
  real_T liftAngle;                    /* '<Root>/liftAngle' */
  real_T tiltExt;                      /* '<Root>/tiltExt' */
  real_T steerAngle;                   /* '<Root>/steerAngle' */
  uint32_T toa_appNumber;              /* '<Root>/toa_appNumber' */
  real32_T toa_tiltBoreDia;            /* '<Root>/toa_tiltBoreDia' */
  real32_T toa_tiltRodDia;             /* '<Root>/toa_tiltRodDia' */
  real32_T toa_liftBoreDia;            /* '<Root>/toa_liftBoreDia' */
  uint8_T toa_tiltNumCyl;              /* '<Root>/toa_tiltNumCyl' */
  real32_T toa_toolBcLength;           /* '<Root>/toa_toolBcLength' */
} ExtU_imuCal_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real32_T pitchOffset;                /* '<Root>/pitchOffset' */
  real32_T lumpedWeight;               /* '<Root>/lumpedWeight' */
} ExtY_imuCal_T;

/* Self model data, for system '<Root>' */
struct tag_RTM_imuCal_T {
  const char_T * volatile errorStatus;
  ExtU_imuCal_T *inputs;
  ExtY_imuCal_T *outputs;
  self_Filter_imuCal_T sf_Filter_d;
  self_Filter_imuCal_T sf_Filter_c;
  self_Filter_imuCal_T sf_Filter;
  DW_imuCal_T dwork;
  B_imuCal_T blockIO;
};

extern const ConstB_imuCal_T imuCal_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void imuCal_initialize(RT_MODEL_imuCal_T *const imuCal_M);
extern void imuCal_terminate(RT_MODEL_imuCal_T *const imuCal_M);

/* Exported entry point functions */
extern void imuCal_fcn_call(RT_MODEL_imuCal_T *const imuCal_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/Data Type Duplicate' : Unused code path elimination
 * Block '<S8>/Data Type Duplicate' : Unused code path elimination
 * Block '<S26>/OV Enable' : Unused code path elimination
 * Block '<S26>/OV False Val' : Unused code path elimination
 * Block '<S26>/OV Lower Limit' : Unused code path elimination
 * Block '<S26>/OV True Val' : Unused code path elimination
 * Block '<S26>/OV Upper Limit' : Unused code path elimination
 * Block '<S27>/OV Enable' : Unused code path elimination
 * Block '<S27>/OV False Val' : Unused code path elimination
 * Block '<S27>/OV Lower Limit' : Unused code path elimination
 * Block '<S27>/OV True Val' : Unused code path elimination
 * Block '<S27>/OV Upper Limit' : Unused code path elimination
 * Block '<S6>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S7>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S8>/Data Type Conversion1' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'imuCal'
 * '<S1>'   : 'imuCal/imuCal Subsystem'
 * '<S2>'   : 'imuCal/imuCal Subsystem/Notch Filter Simulink Function'
 * '<S3>'   : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function'
 * '<S4>'   : 'imuCal/imuCal Subsystem/imuCal'
 * '<S5>'   : 'imuCal/imuCal Subsystem/Notch Filter Simulink Function/Notch filter'
 * '<S6>'   : 'imuCal/imuCal Subsystem/Notch Filter Simulink Function/Notch filter/NotchFilter'
 * '<S7>'   : 'imuCal/imuCal Subsystem/Notch Filter Simulink Function/Notch filter/NotchFilter3'
 * '<S8>'   : 'imuCal/imuCal Subsystem/Notch Filter Simulink Function/Notch filter/NotchFilter4'
 * '<S9>'   : 'imuCal/imuCal Subsystem/Notch Filter Simulink Function/Notch filter/NotchFilter/Filter'
 * '<S10>'  : 'imuCal/imuCal Subsystem/Notch Filter Simulink Function/Notch filter/NotchFilter3/Filter'
 * '<S11>'  : 'imuCal/imuCal Subsystem/Notch Filter Simulink Function/Notch filter/NotchFilter4/Filter'
 * '<S12>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Apply Name3'
 * '<S13>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Apply Name4'
 * '<S14>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/EEF IMU to NEEF gravity vector'
 * '<S15>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Gravity Relevant Components'
 * '<S16>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Lift Cylinder Force'
 * '<S17>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload'
 * '<S18>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Tilt Cylinder Force'
 * '<S19>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/EEF IMU to NEEF gravity vector/Degrees to Radians'
 * '<S20>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/EEF IMU to NEEF gravity vector/EEF vector to NEEF vector'
 * '<S21>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/EEF IMU to NEEF gravity vector/Rotation Matrix About Z'
 * '<S22>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/EEF IMU to NEEF gravity vector/euler angles from rot matrix'
 * '<S23>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/EEF IMU to NEEF gravity vector/normalize vector'
 * '<S24>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/EEF IMU to NEEF gravity vector/rotation matrix calc from two vectors'
 * '<S25>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Gravity Relevant Components/Magnitude'
 * '<S26>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Gravity Relevant Components/Override'
 * '<S27>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Gravity Relevant Components/Override1'
 * '<S28>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Gravity Relevant Components/Override/library'
 * '<S29>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Gravity Relevant Components/Override/library/OV if mismatched'
 * '<S30>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Gravity Relevant Components/Override1/library'
 * '<S31>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Gravity Relevant Components/Override1/library/OV if mismatched'
 * '<S32>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Lift Cylinder Force/diameter to area'
 * '<S33>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Lift Cylinder Force/diameter to area1'
 * '<S34>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name'
 * '<S35>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name1'
 * '<S36>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name12'
 * '<S37>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name13'
 * '<S38>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name14'
 * '<S39>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name15'
 * '<S40>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name16'
 * '<S41>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name2'
 * '<S42>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name3'
 * '<S43>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name4'
 * '<S44>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name5'
 * '<S45>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Apply Name8'
 * '<S46>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Non Bucket Payload/Degrees to Radians'
 * '<S47>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Tilt Cylinder Force/diameter to area'
 * '<S48>'  : 'imuCal/imuCal Subsystem/TOA Weight Simulink Function/Tilt Cylinder Force/diameter to area1'
 */
#endif                                 /* RTW_HEADER_imuCal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
