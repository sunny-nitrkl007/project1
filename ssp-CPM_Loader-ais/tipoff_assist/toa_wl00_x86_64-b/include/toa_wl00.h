/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: toa_wl00.h
 **
 ** Real-Time Workshop code generated for Simulink model toa_wl00.
 **
 ** Model version                        : 1.44
 ** Real-Time Workshop file version      : 8.13 (R2017b) 24-Jul-2017
 ** TLC version                          : 8.13 (Jul 25 2017)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.6.1
 **
 ******************************************************************************/

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_toa_wl00_h_
#define RTW_HEADER_toa_wl00_h_
#include <math.h>
#include <string.h>
#ifndef toa_wl00_COMMON_INCLUDES_
# define toa_wl00_COMMON_INCLUDES_
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
#include "tipoff_assist_962_14A_Z_SL.h"
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
#endif                                 /* toa_wl00_COMMON_INCLUDES_ */

#include "toa_wl00_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "toa_wl00_variant.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->blockIO = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->dwork = (val))
#endif

/* Block states (auto storage) for system '<S157>/Filter' */
typedef struct {
  real32_T rawHist[3];                 /* '<S157>/Filter' */
  real32_T filtHist[3];                /* '<S157>/Filter' */
  real32_T alpha;                      /* '<S157>/Filter' */
  real32_T beta;                       /* '<S157>/Filter' */
  real32_T gamma;                      /* '<S157>/Filter' */
  uint8_t is_active_c24_tip_assist_lib_support;/* '<S157>/Filter' */
} rtDW_Filter_toa_wl00;

/* Block states (auto storage) for system '<S221>/MATLAB Function' */
typedef struct {
  real32_T lastMeanEst;                /* '<S221>/MATLAB Function' */
  real32_T lastVarianceEst;            /* '<S221>/MATLAB Function' */
  boolean_T lastMeanEst_not_empty;     /* '<S221>/MATLAB Function' */
} rtDW_MATLABFunction_toa_wl00_flu5;

/* Block signals (auto storage) */
typedef struct {
  real_T toa_sfuncInRawTiltForce;      /* '<S81>/Copy' */
  real_T toa_sfuncInRawLiftForce;      /* '<S82>/Copy' */
  real_T toa_sfuncInRawTiltExt;        /* '<S83>/Copy' */
  real_T toa_sfuncInRawLiftAng;        /* '<S84>/Copy' */
  real_T toa_sfuncInRawBcLength;       /* '<S85>/Copy' */
  real_T toa_sfuncInRawGravX;          /* '<S93>/Copy' */
  real_T toa_sfuncInRawGravY;          /* '<S94>/Copy' */
  real_T toa_sfuncOutRawMass;          /* '<S89>/Copy' */
  real_T toa_imuNeefPitch;             /* '<S62>/Copy' */
  real_T toa_sfuncOutRawDist;          /* '<S77>/Copy' */
  real_T toa_targetCompMargin;         /* '<S119>/Copy' */
  real_T toa_targetPayloadPostComp;    /* '<S118>/Copy' */
  real_T toa_grav_angles[3];           /* '<S26>/euler angles from rot matrix' */
  real32_T toa_inTsTiltExt;            /* '<S131>/Copy' */
  real32_T toa_inTsLiftAngle;          /* '<S129>/Copy' */
  real32_T toa_inTsBc;                 /* '<S130>/Copy' */
  real32_T toa_inTsBcAng;              /* '<S132>/Copy' */
  real32_T toa_tiltSensitivity;        /* '<S15>/Copy' */
  real32_T toa_outTiltSensToBucket;    /* '<S22>/Copy' */
  real32_T toa_outTiltHePress;         /* '<S8>/Copy' */
  real32_T toa_tiltForce;              /* '<S18>/Copy' */
  real32_T toa_sfuncInTiltForce;       /* '<S88>/Copy' */
  real32_T toa_fcLiftForceRaw;         /* '<S74>/Copy' */
  real32_T toa_fcLiftForceComp;        /* '<S73>/Copy' */
  real32_T toa_liftForce;              /* '<S19>/Copy' */
  real32_T toa_sfuncInLiftForce;       /* '<S90>/Copy' */
  real32_T toa_sfuncInTiltExt;         /* '<S78>/Copy' */
  real32_T toa_sfuncInLiftAng;         /* '<S98>/Copy' */
  real32_T toa_sfuncInBcLength;        /* '<S95>/Copy' */
  real32_T toa_inImuAcclX;             /* '<S1>/Copy' */
  real32_T toa_inImuAcclY;             /* '<S2>/Copy' */
  real32_T toa_inImuAcclZ;             /* '<S3>/Copy' */
  real32_T toa_imu_eef_accl_vec_post_lpf[3];/* '<S57>/Data Type Conversion' */
  real32_T toa_sfuncInGravX;           /* '<S91>/Copy' */
  real32_T toa_sfuncInGravY;           /* '<S92>/Copy' */
  real32_T toa_sfuncOutRawMassTonne;   /* '<S79>/Copy' */
  real32_T toa_rawPayload;             /* '<S96>/Copy' */
  real32_T toa_payloadAncZeroed;       /* '<S86>/Copy' */
  real32_T toa_payloadAncAdjusted;     /* '<S87>/Copy' */
  real32_T toa_payloadZeroed;          /* '<S99>/Copy' */
  real32_T toa_payloadAdjusted;        /* '<S97>/Copy' */
  real32_T toa_pfwPayloadNotchPost;    /* '<S198>/Copy' */
  real32_T toa_pfwPayloadNotchFiltFinal;/* '<S197>/Copy' */
  real32_T toa_pfwSecPayload;          /* '<S136>/Copy' */
  real32_T toa_lwLpfPost;              /* '<S146>/Copy' */
  real32_T toa_sendPayloadArb;         /* '<S102>/Copy' */
  real32_T toa_targetPayloadPreComp;   /* '<S115>/Copy' */
  real32_T toa_targetPayloadFinal;     /* '<S113>/Copy' */
  real32_T toa_outPayloadArbNormError; /* '<S14>/Copy' */
  real32_T toa_pfwSecStDev;            /* '<S137>/Copy' */
  real32_T toa_outPfwPayloadNormStdev; /* '<S17>/Copy' */
  real32_T toa_outCpmPayloadNormError; /* '<S12>/Copy' */
  real32_T toa_lwSpillRate;            /* '<S147>/Copy' */
  real32_T toa_outSpillRateNorm;       /* '<S10>/Copy' */
  real32_T toa_outBucketPayloadTarget; /* '<S23>/Copy' */
  real32_T toa_statPayloadSecureTwoSize;/* '<S180>/Copy' */
  real32_T toa_sendCpmPfwSecSize;      /* '<S37>/Copy' */
  real32_T toa_sendCpmLivePayload;     /* '<S145>/Copy' */
  real32_T toa_outSendCpmPayload;      /* '<S6>/Copy' */
  real32_T toa_pfwNlNotchStDevEst;     /* '<S201>/Copy' */
  real32_T toa_pfwNlNotchMeanEst;      /* '<S170>/Copy' */
  real32_T toa_pfwUnsecBoundUpper;     /* '<S141>/Copy' */
  real32_T toa_outUnsecPayloadNormUp;  /* '<S24>/Copy' */
  real32_T toa_pfwUnsecBoundLower;     /* '<S140>/Copy' */
  real32_T toa_outUnsecPayloadNormLow; /* '<S7>/Copy' */
  real32_T toa_pfwSecMinBucketAng;     /* '<S195>/Copy' */
  real32_T toa_outMinSecBucketAng;     /* '<S13>/Copy' */
  real32_T toa_imuRawEefAcclX;         /* '<S39>/Copy' */
  real32_T toa_imuRawEefAcclY;         /* '<S40>/Copy' */
  real32_T toa_imuRawEefAcclZ;         /* '<S41>/Copy' */
  real32_T toa_imuNeefGravX;           /* '<S42>/Copy' */
  real32_T toa_imuNeefGravY;           /* '<S43>/Copy' */
  real32_T toa_imuNeefGravZ;           /* '<S44>/Copy' */
  real32_T toa_grav_neef_xy_mag;       /* '<S63>/Math Function1' */
  real32_T toa_rawDist;                /* '<S80>/Copy' */
  real32_T toa_statPayloadSecureTwoLower;/* '<S169>/Copy' */
  real32_T toa_statPayloadNlNotchOneUp;/* '<S171>/Copy' */
  real32_T toa_statPayloadNlNotchOneSize;/* '<S172>/Copy' */
  real32_T toa_statPayloadNlNotchTwoUp;/* '<S173>/Copy' */
  real32_T toa_statPayloadNlNotchTwoSize;/* '<S174>/Copy' */
  real32_T toa_statPayloadNlNotchTwoLow;/* '<S175>/Copy' */
  real32_T toa_pfwPayloadFiltFinal;    /* '<S199>/Copy' */
  real32_T toa_pfwNlStDevEst;          /* '<S184>/Copy' */
  real32_T toa_pfwNlMeanEst;           /* '<S183>/Copy' */
  real32_T toa_statPayloadNlOneUp;     /* '<S176>/Copy' */
  real32_T toa_statPayloadNlOneSize;   /* '<S177>/Copy' */
  real32_T toa_statPayloadNlTwoUp;     /* '<S178>/Copy' */
  real32_T toa_statPayloadNlTwoSize;   /* '<S179>/Copy' */
  real32_T toa_statPayloadNlTwoLow;    /* '<S181>/Copy' */
  real32_T toa_statPayloadNlOneLow;    /* '<S182>/Copy' */
  real32_T toa_statPayloadSecureOneUpper;/* '<S187>/Copy' */
  real32_T toa_statPayloadSecureOneLower;/* '<S188>/Copy' */
  real32_T toa_statPayloadSecureOneSize;/* '<S189>/Copy' */
  real32_T toa_statPayloadSecureTwoUpper;/* '<S190>/Copy' */
  real32_T toa_statPayloadNlNotchOneLow;/* '<S200>/Copy' */
  real32_T toa_grav_rotMatrix[9];      /* '<S26>/rotation matrix calc from two vectors' */
  real32_T toa_grav_rotAxis[3];        /* '<S26>/rotation matrix calc from two vectors' */
  real32_T toa_grav_angle;             /* '<S26>/rotation matrix calc from two vectors' */
  real32_T toa_imu_neef_accl_vec[3];   /* '<S26>/EEF vector to NEEF vector' */
  TipAssistSecPfwStatus_t toa_pfwSecStatus;/* '<S135>/Copy' */
  TipAssistSecPfwStatus_t toa_outPfwStat;/* '<S16>/Copy' */
  TipAssistLiveWeighStatus_t toa_lwStatus;/* '<S144>/Copy' */
  TipAssistUnsecPfwStatus_t toa_pfwUnsecStatus;/* '<S139>/Copy' */
  TipAssistUnsecPfwStatus_t toa_outUnsecPayloadStatus;/* '<S9>/Copy' */
  TipAssistAdvEcmError_t toa_outAdvErrorCode;/* '<S21>/Copy' */
  TipAssistPayloadType_t toa_sendPayloadType;/* '<S101>/Copy' */
  TipAssistSendCpmStatus_t toa_outSendCpmStatus;/* '<S20>/Copy' */
  uint8_t toa_outCpmAccu;              /* '<S11>/Copy' */
  boolean_T toa_pfwSecIsNoSliding;     /* '<S186>/Copy' */
  boolean_T toa_pfwSecIsNoCollapsing;  /* '<S194>/Copy' */
  boolean_T toa_pfwSecIsRacked;        /* '<S196>/Copy' */
  boolean_T toa_pfwLatchInvalidate;    /* '<S279>/Copy' */
  boolean_T toa_pfwMcMaybeRackStall;   /* '<S249>/Copy' */
  boolean_T toa_pfwMcMaybeStalled;     /* '<S250>/Copy' */
  boolean_T toa_pfwMcMaybeGrounded;    /* '<S251>/Copy' */
  boolean_T toa_isLiftValveCmd;        /* '<S193>/Copy' */
  boolean_T toa_isTiltValveCmd;        /* '<S192>/Copy' */
  boolean_T toa_is_not_tilt_valve_cmd; /* '<S260>/Logical Operator5' */
  boolean_T toa_tilt_timer_expired;    /* '<S273>/Compare' */
  boolean_T toa_tilt_timer_not_expired;/* '<S260>/Logical Operator4' */
  boolean_T toa_pfwMcOk;               /* '<S252>/Copy' */
  boolean_T toa_pfwIsWarm;             /* '<S191>/Copy' */
  boolean_T toa_pfwSecIsSecure;        /* '<S185>/Copy' */
  boolean_T toa_pfwSecLatch;           /* '<S138>/Copy' */
  boolean_T toa_targetPayloadStatus;   /* '<S114>/Copy' */
  boolean_T toa_sendCpmPfwIsPrecise;   /* '<S36>/Copy' */
} BlockIO_toa_wl00;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T UnitDelay1_DSTATE[3];       /* '<S56>/Unit Delay1' */
  real32_T UnitDelay1_DSTATE_mga0[3];  /* '<S57>/Unit Delay1' */
  real32_T Delay2_DSTATE;              /* '<S202>/Delay2' */
  real32_T UnitDelay_DSTATE;           /* '<S231>/Unit Delay' */
  real32_T UnitDelay1_DSTATE_fp5d;     /* '<S219>/Unit Delay1' */
  real32_T Delay_DSTATE;               /* '<S143>/Delay' */
  real32_T UnitDelay_DSTATE_hioq;      /* '<S214>/Unit Delay' */
  real32_T UnitDelay1_DSTATE_bcfn;     /* '<S154>/Unit Delay1' */
  real32_T UnitDelay_DSTATE_jlpe;      /* '<S215>/Unit Delay' */
  real32_T ResettableDelay_DSTATE;     /* '<S153>/Resettable Delay' */
  real32_T UnitDelay1_DSTATE_bo33;     /* '<S156>/Unit Delay1' */
  real32_T UnitDelay1_DSTATE_e2d2;     /* '<S155>/Unit Delay1' */
  real32_T lastSample;                 /* '<S226>/MATLAB Function' */
  real32_T lastSample_kln4;            /* '<S225>/MATLAB Function' */
  uint16_t Timer_DSTATE;               /* '<S267>/Timer' */
  uint16_t Timer_DSTATE_dme3;          /* '<S268>/Timer' */
  uint16_t Timer_DSTATE_jrr0;          /* '<S208>/Timer' */
  uint8_t UnitDelay_DSTATE_mvg5;       /* '<S58>/Unit Delay' */
  uint8_t UnitDelay_DSTATE_j5gs;       /* '<S60>/Unit Delay' */
  uint8_t UnitDelay_DSTATE_bw1s;       /* '<S280>/Unit Delay' */
  uint8_t UnitDelay_DSTATE_fdvn;       /* '<S163>/Unit Delay' */
  uint8_t UnitDelay_DSTATE_pigm;       /* '<S167>/Unit Delay' */
  uint8_t UnitDelay_DSTATE_kdv5;       /* '<S165>/Unit Delay' */
  boolean_T DelayInput1_DSTATE;        /* '<S213>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_prcl;   /* '<S205>/Delay Input1' */
  boolean_T UnitDelay_DSTATE_fett;     /* '<S266>/Unit Delay' */
  boolean_T Delay_DSTATE_obnz;         /* '<S257>/Delay' */
  boolean_T UnitDelay_DSTATE_nds1;     /* '<S216>/Unit Delay' */
  boolean_T DelayInput1_DSTATE_nzby;   /* '<S152>/Delay Input1' */
  int8_t Memory2_PreviousInput;        /* '<S283>/Memory 2' */
  int8_t Memory2_PreviousInput_i53e;   /* '<S232>/Memory 2' */
  int8_t Memory2_PreviousInput_pgwc;   /* '<S278>/Memory 2' */
  uint8_t Memory1_PreviousInput;       /* '<S283>/Memory 1' */
  uint8_t Memory1_PreviousInput_ddl0;  /* '<S232>/Memory 1' */
  uint8_t Memory1_PreviousInput_gnui;  /* '<S278>/Memory 1' */
  uint8_t icLoad;                      /* '<S153>/Resettable Delay' */
  boolean_T lastSample_not_empty;      /* '<S226>/MATLAB Function' */
  boolean_T lastSample_not_empty_m4ln; /* '<S225>/MATLAB Function' */
  rtDW_MATLABFunction_toa_wl00_flu5 sf_MATLABFunction_iawv;/* '<S222>/MATLAB Function' */
  rtDW_MATLABFunction_toa_wl00_flu5 sf_MATLABFunction_fw1r;/* '<S221>/MATLAB Function' */
  rtDW_Filter_toa_wl00 sf_Filter_ewyz; /* '<S245>/Filter' */
  rtDW_Filter_toa_wl00 sf_Filter_jasu; /* '<S244>/Filter' */
  rtDW_Filter_toa_wl00 sf_Filter;      /* '<S243>/Filter' */
  rtDW_Filter_toa_wl00 sf_Filter_n3ho; /* '<S239>/Filter' */
  rtDW_Filter_toa_wl00 sf_Filter_f5hh; /* '<S238>/Filter' */
  rtDW_Filter_toa_wl00 sf_Filter_ozu2; /* '<S237>/Filter' */
  rtDW_Filter_toa_wl00 sf_Filter_ifuw; /* '<S159>/Filter' */
  rtDW_Filter_toa_wl00 sf_Filter_c1cw; /* '<S158>/Filter' */
  rtDW_Filter_toa_wl00 sf_Filter_dsll; /* '<S157>/Filter' */
} D_Work_toa_wl00;

/* Constant parameters (auto storage) */
typedef struct {
  /* Computed Parameter: IMUcsystoEEFcsysrotmat_Value
   * Referenced by: '<S26>/IMU csys to EEF csys rot mat'
   */
  real32_T IMUcsystoEEFcsysrotmat_Value[9];

  /* Computed Parameter: levelgravityaccel_Value
   * Referenced by: '<S26>/level gravity accel'
   */
  real32_T levelgravityaccel_Value[3];
} ConstParam_toa_wl00;

/* Real-time Model Data Structure */
struct tag_RTM_toa_wl00 {
  BlockIO_toa_wl00 *blockIO;
  D_Work_toa_wl00 *dwork;
  toa_wl00_catParameters_si_RAM_t * toa_wl00_catParameters_si_RAM_p;
};

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/* Constant parameters (auto storage) */
extern const ConstParam_toa_wl00 toa_wl00_ConstP;

/* Model entry point functions */
extern void toa_wl00_initialize(RT_MODEL_toa_wl00 *const toa_wl00_M, boolean_T
  *toa_wl00_U_Invalidate_Outputs, real32_T *toa_wl00_U_Lift_Valve_Command,
  real32_T *toa_wl00_U_Tilt_Valve_Command, real32_T *toa_wl00_U_Tilt_Extension,
  real32_T *toa_wl00_U_Lift_Angle, real32_T *toa_wl00_U_Lift_HE_Pressure,
  real32_T *toa_wl00_U_Lift_RE_Pressure, real32_T *toa_wl00_U_Tilt_HE_Pressure,
  real32_T *toa_wl00_U_Tilt_RE_Pressure, real32_T *toa_wl00_U_Steering_Angle,
  real32_T *toa_wl00_U_Tool_Mass, real32_T *toa_wl00_U_PCS_Truck_Target,
  real32_T *toa_wl00_U_PCS_Truck_Start_Weight, uint8_t
  *toa_wl00_U_PCS_Bucket_Current_Weight_Accuracy, real32_T
  *toa_wl00_U_PCS_Bucket_Current_Weight, uint8_t *toa_wl00_U_PCS_Tipoff_Mode,
  real32_T *toa_wl00_U_EEF_IMU_AccelX, real32_T *toa_wl00_U_EEF_IMU_AccelY,
  real32_T *toa_wl00_U_EEF_IMU_AccelZ, real32_T *toa_wl00_U_Zero_Offset,
  real32_T *toa_wl00_U_Simple_Cal_Factor, real32_T *toa_wl00_U_IMU_Pitch_Cal,
  real32_T *toa_wl00_U_Bucket_Angle, boolean_T *toa_wl00_U_Unlatch_Trigger,
  real32_T *toa_wl00_U_Anchor_Zero_Offset, real32_T *toa_wl00_U_Anchor_Factor,
  uint16_t *toa_wl00_U_CPM_Pass_Count, real32_T *toa_wl00_U_Lift_Norm_Angle,
  real32_T *toa_wl00_U_Lift_Norm_Length, real32_T *toa_wl00_U_Tilt_Norm_Angle,
  real32_T *toa_wl00_U_Tilt_Norm_Length, real32_T *toa_wl00_U_Friction_Mu,
  real32_T *toa_wl00_U_Friction_Offset, real32_T *toa_wl00_Y_Tilt_Sensitivity,
  real32_T *toa_wl00_Y_Tilt_HE_Pressure_Out, real32_T
  *toa_wl00_Y_Arbitrated_Payload_Norm_Error, uint8_t *toa_wl00_Y_Weigh_Status,
  real32_T *toa_wl00_Y_Payload_Norm_Stdev, uint8_t
  *toa_wl00_Y_PCS_Bucket_Current_Weight_Accuracy_Out, real32_T
  *toa_wl00_Y_PCS_Bucket_Current_Weight_Norm_Error_Out, uint8_t
  *toa_wl00_Y_Tipoff_Assist_Adv_Error_Code, real32_T *toa_wl00_Y_Spill_Rate_Norm,
  real32_T *toa_wl00_Y_Bucket_Payload_Target, real32_T
  *toa_wl00_Y_Payload_Send_To_CPM, uint8_t
  *toa_wl00_Y_Payload_Status_Send_To_CPM, real32_T
  *toa_wl00_Y_Unsecured_Payload_Upper_Bound_Norm, real32_T
  *toa_wl00_Y_Unsecured_Payload_Lower_Bound_Norm, uint8_t
  *toa_wl00_Y_Unsecured_PFW_Status, real32_T *toa_wl00_Y_Min_Secure_Bucket_Angle);
extern void toa_wl00_step(RT_MODEL_toa_wl00 *const toa_wl00_M, boolean_T
  toa_wl00_U_Invalidate_Outputs, real32_T toa_wl00_U_Lift_Valve_Command,
  real32_T toa_wl00_U_Tilt_Valve_Command, real32_T toa_wl00_U_Tilt_Extension,
  real32_T toa_wl00_U_Lift_Angle, real32_T toa_wl00_U_Lift_HE_Pressure, real32_T
  toa_wl00_U_Lift_RE_Pressure, real32_T toa_wl00_U_Tilt_HE_Pressure, real32_T
  toa_wl00_U_Tilt_RE_Pressure, real32_T toa_wl00_U_Steering_Angle, real32_T
  toa_wl00_U_Tool_Mass, real32_T toa_wl00_U_PCS_Truck_Target, real32_T
  toa_wl00_U_PCS_Truck_Start_Weight, uint8_t
  toa_wl00_U_PCS_Bucket_Current_Weight_Accuracy, real32_T
  toa_wl00_U_PCS_Bucket_Current_Weight, uint8_t toa_wl00_U_PCS_Tipoff_Mode,
  real32_T toa_wl00_U_EEF_IMU_AccelX, real32_T toa_wl00_U_EEF_IMU_AccelY,
  real32_T toa_wl00_U_EEF_IMU_AccelZ, real32_T toa_wl00_U_Zero_Offset, real32_T
  toa_wl00_U_Simple_Cal_Factor, real32_T toa_wl00_U_IMU_Pitch_Cal, real32_T
  toa_wl00_U_Bucket_Angle, boolean_T toa_wl00_U_Unlatch_Trigger, real32_T
  toa_wl00_U_Anchor_Zero_Offset, real32_T toa_wl00_U_Anchor_Factor, uint16_t
  toa_wl00_U_CPM_Pass_Count, real32_T toa_wl00_U_Lift_Norm_Angle, real32_T
  toa_wl00_U_Lift_Norm_Length, real32_T toa_wl00_U_Tilt_Norm_Angle, real32_T
  toa_wl00_U_Tilt_Norm_Length, real32_T toa_wl00_U_Friction_Mu, real32_T
  toa_wl00_U_Friction_Offset, real32_T *toa_wl00_Y_Tilt_Sensitivity, real32_T
  *toa_wl00_Y_Tilt_HE_Pressure_Out, real32_T
  *toa_wl00_Y_Arbitrated_Payload_Norm_Error, uint8_t *toa_wl00_Y_Weigh_Status,
  real32_T *toa_wl00_Y_Payload_Norm_Stdev, uint8_t
  *toa_wl00_Y_PCS_Bucket_Current_Weight_Accuracy_Out, real32_T
  *toa_wl00_Y_PCS_Bucket_Current_Weight_Norm_Error_Out, uint8_t
  *toa_wl00_Y_Tipoff_Assist_Adv_Error_Code, real32_T *toa_wl00_Y_Spill_Rate_Norm,
  real32_T *toa_wl00_Y_Bucket_Payload_Target, real32_T
  *toa_wl00_Y_Payload_Send_To_CPM, uint8_t
  *toa_wl00_Y_Payload_Status_Send_To_CPM, real32_T
  *toa_wl00_Y_Unsecured_Payload_Upper_Bound_Norm, real32_T
  *toa_wl00_Y_Unsecured_Payload_Lower_Bound_Norm, uint8_t
  *toa_wl00_Y_Unsecured_PFW_Status, real32_T *toa_wl00_Y_Min_Secure_Bucket_Angle);

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/

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
 * '<Root>' : 'toa_wl00'
 * '<S1>'   : 'toa_wl00/Apply Name'
 * '<S2>'   : 'toa_wl00/Apply Name2'
 * '<S3>'   : 'toa_wl00/Apply Name3'
 * '<S4>'   : 'toa_wl00/Package Instance'
 * '<S5>'   : 'toa_wl00/Tip-Off Assist Support Lib'
 * '<S6>'   : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name1'
 * '<S7>'   : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name10'
 * '<S8>'   : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name11'
 * '<S9>'   : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name12'
 * '<S10>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name13'
 * '<S11>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name14'
 * '<S12>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name15'
 * '<S13>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name16'
 * '<S14>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name19'
 * '<S15>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name2'
 * '<S16>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name20'
 * '<S17>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name21'
 * '<S18>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name3'
 * '<S19>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name4'
 * '<S20>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name5'
 * '<S21>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name6'
 * '<S22>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name7'
 * '<S23>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name8'
 * '<S24>'  : 'toa_wl00/Tip-Off Assist Support Lib/Apply Name9'
 * '<S25>'  : 'toa_wl00/Tip-Off Assist Support Lib/CPM Payload Send'
 * '<S26>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector'
 * '<S27>'  : 'toa_wl00/Tip-Off Assist Support Lib/Gravity Relevant Components'
 * '<S28>'  : 'toa_wl00/Tip-Off Assist Support Lib/Lift Cylinder Force'
 * '<S29>'  : 'toa_wl00/Tip-Off Assist Support Lib/Lift Friction Compensation'
 * '<S30>'  : 'toa_wl00/Tip-Off Assist Support Lib/Machine Properties'
 * '<S31>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload'
 * '<S32>'  : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement'
 * '<S33>'  : 'toa_wl00/Tip-Off Assist Support Lib/Tilt Cylinder Force'
 * '<S34>'  : 'toa_wl00/Tip-Off Assist Support Lib/Tilt Sensitivity to Bucket Angle'
 * '<S35>'  : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload'
 * '<S36>'  : 'toa_wl00/Tip-Off Assist Support Lib/CPM Payload Send/Apply Name1'
 * '<S37>'  : 'toa_wl00/Tip-Off Assist Support Lib/CPM Payload Send/Apply Name9'
 * '<S38>'  : 'toa_wl00/Tip-Off Assist Support Lib/CPM Payload Send/MATLAB Function'
 * '<S39>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Apply Name1'
 * '<S40>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Apply Name2'
 * '<S41>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Apply Name3'
 * '<S42>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Apply Name4'
 * '<S43>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Apply Name5'
 * '<S44>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Apply Name6'
 * '<S45>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Degrees to Radians'
 * '<S46>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/EEF vector to NEEF vector'
 * '<S47>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Override Pitch Cal for Development'
 * '<S48>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Rotation Matrix About Z'
 * '<S49>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/euler angles from rot matrix'
 * '<S50>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/imu lpf x1'
 * '<S51>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/normalize vector'
 * '<S52>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/rotation matrix calc from two vectors'
 * '<S53>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Override Pitch Cal for Development/library'
 * '<S54>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/Override Pitch Cal for Development/library/OV if mismatched'
 * '<S55>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/imu lpf x1/Filter Factor Calc'
 * '<S56>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/imu lpf x1/Single Pole Low Pass Filter'
 * '<S57>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/imu lpf x1/Single Pole Low Pass Filter1'
 * '<S58>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/imu lpf x1/Single Pole Low Pass Filter/NotFirstLoop'
 * '<S59>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/imu lpf x1/Single Pole Low Pass Filter/Reset'
 * '<S60>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/imu lpf x1/Single Pole Low Pass Filter1/NotFirstLoop'
 * '<S61>'  : 'toa_wl00/Tip-Off Assist Support Lib/EEF IMU to NEEF gravity vector/imu lpf x1/Single Pole Low Pass Filter1/Reset'
 * '<S62>'  : 'toa_wl00/Tip-Off Assist Support Lib/Gravity Relevant Components/Apply Name3'
 * '<S63>'  : 'toa_wl00/Tip-Off Assist Support Lib/Gravity Relevant Components/Magnitude'
 * '<S64>'  : 'toa_wl00/Tip-Off Assist Support Lib/Gravity Relevant Components/Override'
 * '<S65>'  : 'toa_wl00/Tip-Off Assist Support Lib/Gravity Relevant Components/Override1'
 * '<S66>'  : 'toa_wl00/Tip-Off Assist Support Lib/Gravity Relevant Components/Radians to Degrees'
 * '<S67>'  : 'toa_wl00/Tip-Off Assist Support Lib/Gravity Relevant Components/Override/library'
 * '<S68>'  : 'toa_wl00/Tip-Off Assist Support Lib/Gravity Relevant Components/Override/library/OV if mismatched'
 * '<S69>'  : 'toa_wl00/Tip-Off Assist Support Lib/Gravity Relevant Components/Override1/library'
 * '<S70>'  : 'toa_wl00/Tip-Off Assist Support Lib/Gravity Relevant Components/Override1/library/OV if mismatched'
 * '<S71>'  : 'toa_wl00/Tip-Off Assist Support Lib/Lift Cylinder Force/diameter to area'
 * '<S72>'  : 'toa_wl00/Tip-Off Assist Support Lib/Lift Cylinder Force/diameter to area1'
 * '<S73>'  : 'toa_wl00/Tip-Off Assist Support Lib/Lift Friction Compensation/Apply Name'
 * '<S74>'  : 'toa_wl00/Tip-Off Assist Support Lib/Lift Friction Compensation/Apply Name1'
 * '<S75>'  : 'toa_wl00/Tip-Off Assist Support Lib/Lift Friction Compensation/MATLAB Function'
 * '<S76>'  : 'toa_wl00/Tip-Off Assist Support Lib/Lift Friction Compensation/diameter to area'
 * '<S77>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name'
 * '<S78>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name1'
 * '<S79>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name10'
 * '<S80>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name11'
 * '<S81>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name12'
 * '<S82>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name13'
 * '<S83>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name14'
 * '<S84>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name15'
 * '<S85>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name16'
 * '<S86>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name17'
 * '<S87>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name18'
 * '<S88>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name19'
 * '<S89>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name2'
 * '<S90>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name20'
 * '<S91>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name21'
 * '<S92>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name23'
 * '<S93>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name3'
 * '<S94>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name4'
 * '<S95>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name5'
 * '<S96>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name6'
 * '<S97>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name7'
 * '<S98>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name8'
 * '<S99>'  : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Apply Name9'
 * '<S100>' : 'toa_wl00/Tip-Off Assist Support Lib/Non Bucket Payload/Degrees to Radians'
 * '<S101>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Apply Name1'
 * '<S102>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Apply Name4'
 * '<S103>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Arbitrated Payload Fit in Datalink Representation'
 * '<S104>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Bucket Target Payload'
 * '<S105>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Combine Errors'
 * '<S106>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Normalize Arbitrated Payload Error'
 * '<S107>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Normalize CPM Bucket Current Weight Error'
 * '<S108>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Normalize CPM Bucket Current Weight Error1'
 * '<S109>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Normalize CPM Bucket Current Weight Error2'
 * '<S110>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Normalize PFW Std. Dev.'
 * '<S111>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Normalize Spill Rate'
 * '<S112>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Payload Multiplexing'
 * '<S113>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Bucket Target Payload/Apply Name1'
 * '<S114>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Bucket Target Payload/Apply Name2'
 * '<S115>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Bucket Target Payload/Apply Name3'
 * '<S116>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Bucket Target Payload/Bad Status if 0'
 * '<S117>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Bucket Target Payload/Bucket Target Compensation'
 * '<S118>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Bucket Target Payload/Bucket Target Compensation/Apply Name1'
 * '<S119>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Bucket Target Payload/Bucket Target Compensation/Apply Name3'
 * '<S120>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Combine Errors/Compare To Constant'
 * '<S121>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Combine Errors/Compare To Constant1'
 * '<S122>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Combine Errors/Compare To Constant2'
 * '<S123>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Combine Errors/Compare To Constant3'
 * '<S124>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Combine Errors/Compare To Constant4'
 * '<S125>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Combine Errors/Compare To Constant5'
 * '<S126>' : 'toa_wl00/Tip-Off Assist Support Lib/Send to Implement/Combine Errors/Normalize Payload'
 * '<S127>' : 'toa_wl00/Tip-Off Assist Support Lib/Tilt Cylinder Force/diameter to area'
 * '<S128>' : 'toa_wl00/Tip-Off Assist Support Lib/Tilt Cylinder Force/diameter to area1'
 * '<S129>' : 'toa_wl00/Tip-Off Assist Support Lib/Tilt Sensitivity to Bucket Angle/Apply Name'
 * '<S130>' : 'toa_wl00/Tip-Off Assist Support Lib/Tilt Sensitivity to Bucket Angle/Apply Name1'
 * '<S131>' : 'toa_wl00/Tip-Off Assist Support Lib/Tilt Sensitivity to Bucket Angle/Apply Name2'
 * '<S132>' : 'toa_wl00/Tip-Off Assist Support Lib/Tilt Sensitivity to Bucket Angle/Apply Name3'
 * '<S133>' : 'toa_wl00/Tip-Off Assist Support Lib/Tilt Sensitivity to Bucket Angle/Degrees to Radians'
 * '<S134>' : 'toa_wl00/Tip-Off Assist Support Lib/Tilt Sensitivity to Bucket Angle/Degrees to Radians1'
 * '<S135>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Apply Name1'
 * '<S136>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Apply Name2'
 * '<S137>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Apply Name3'
 * '<S138>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Apply Name4'
 * '<S139>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Apply Name5'
 * '<S140>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Apply Name6'
 * '<S141>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Apply Name7'
 * '<S142>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh'
 * '<S143>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh'
 * '<S144>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Apply Name1'
 * '<S145>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Apply Name2'
 * '<S146>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Apply Name3'
 * '<S147>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Apply Name4'
 * '<S148>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/MATLAB Function'
 * '<S149>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/MATLAB Function1'
 * '<S150>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/MATLAB Function2'
 * '<S151>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Notch filter'
 * '<S152>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Reset when inputs become OK'
 * '<S153>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Resettable Discrete Derivative'
 * '<S154>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Single Pole Low Pass Filter'
 * '<S155>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Single Pole Low Pass Filter1'
 * '<S156>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Single Pole Low Pass Filter2'
 * '<S157>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Notch filter/NotchFilter'
 * '<S158>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Notch filter/NotchFilter1'
 * '<S159>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Notch filter/NotchFilter2'
 * '<S160>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Notch filter/NotchFilter/Filter'
 * '<S161>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Notch filter/NotchFilter1/Filter'
 * '<S162>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Notch filter/NotchFilter2/Filter'
 * '<S163>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Single Pole Low Pass Filter/NotFirstLoop'
 * '<S164>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Single Pole Low Pass Filter/Reset'
 * '<S165>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Single Pole Low Pass Filter1/NotFirstLoop'
 * '<S166>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Single Pole Low Pass Filter1/Reset'
 * '<S167>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Single Pole Low Pass Filter2/NotFirstLoop'
 * '<S168>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Live Weigh/Single Pole Low Pass Filter2/Reset'
 * '<S169>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name1'
 * '<S170>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name10'
 * '<S171>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name11'
 * '<S172>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name12'
 * '<S173>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name13'
 * '<S174>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name14'
 * '<S175>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name15'
 * '<S176>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name16'
 * '<S177>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name17'
 * '<S178>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name18'
 * '<S179>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name19'
 * '<S180>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name2'
 * '<S181>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name20'
 * '<S182>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name21'
 * '<S183>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name22'
 * '<S184>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name23'
 * '<S185>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name24'
 * '<S186>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name25'
 * '<S187>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name26'
 * '<S188>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name27'
 * '<S189>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name28'
 * '<S190>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name29'
 * '<S191>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name3'
 * '<S192>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name30'
 * '<S193>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name31'
 * '<S194>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name32'
 * '<S195>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name33'
 * '<S196>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name34'
 * '<S197>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name5'
 * '<S198>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name6'
 * '<S199>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name7'
 * '<S200>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name8'
 * '<S201>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Apply Name9'
 * '<S202>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Collapsing'
 * '<S203>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Compare To Zero'
 * '<S204>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Compare To Zero1'
 * '<S205>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Detect Decrease'
 * '<S206>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/DocBlock'
 * '<S207>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/MATLAB Function1'
 * '<S208>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Minimum Measurement Duration'
 * '<S209>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter'
 * '<S210>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter1'
 * '<S211>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions'
 * '<S212>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Racked'
 * '<S213>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Reset when inputs become OK'
 * '<S214>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Secure Latched Payload (resets to NaN)'
 * '<S215>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Secure Latched Standard Deviation (resets to inf)'
 * '<S216>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Secure Payload Latch State'
 * '<S217>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Secure Payload Status'
 * '<S218>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Secure Payload Unlatch Logic'
 * '<S219>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Single Pole Low Pass Filter1'
 * '<S220>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Sliding'
 * '<S221>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Statistics Estimation1'
 * '<S222>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Statistics Estimation2'
 * '<S223>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Sure dig is over'
 * '<S224>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Unsecure Payload Status'
 * '<S225>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Variance Anti-Noise Filter1'
 * '<S226>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Variance Anti-Noise Filter2'
 * '<S227>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Weighing Statistics, No Notch, No Latch'
 * '<S228>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Weighing Statistics, Notch, No Latch'
 * '<S229>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Weighing Statistics, Secure Latched'
 * '<S230>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Collapsing/Latched Point Hysteresis'
 * '<S231>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Collapsing/Minimum Angle For Current Load (resets to 99)'
 * '<S232>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Collapsing/Latched Point Hysteresis/Unit Delay External IC'
 * '<S233>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Minimum Measurement Duration/Compare To Zero'
 * '<S234>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Minimum Measurement Duration/Compare To Zero3'
 * '<S235>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Minimum Measurement Duration/Decrement Timer'
 * '<S236>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Minimum Measurement Duration/Enable Condition'
 * '<S237>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter/NotchFilter'
 * '<S238>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter/NotchFilter1'
 * '<S239>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter/NotchFilter2'
 * '<S240>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter/NotchFilter/Filter'
 * '<S241>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter/NotchFilter1/Filter'
 * '<S242>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter/NotchFilter2/Filter'
 * '<S243>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter1/NotchFilter'
 * '<S244>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter1/NotchFilter1'
 * '<S245>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter1/NotchFilter2'
 * '<S246>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter1/NotchFilter/Filter'
 * '<S247>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter1/NotchFilter1/Filter'
 * '<S248>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Notch filter1/NotchFilter2/Filter'
 * '<S249>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Apply Name1'
 * '<S250>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Apply Name2'
 * '<S251>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Apply Name3'
 * '<S252>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Apply Name4'
 * '<S253>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/End of Travel Detect'
 * '<S254>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/End of Travel Detect1'
 * '<S255>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/End of Travel Detect2'
 * '<S256>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/End of Travel Detect3'
 * '<S257>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/False to True Transition'
 * '<S258>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Ground Heuristic'
 * '<S259>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Rack Stall Detection'
 * '<S260>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Valve commands recently became zero'
 * '<S261>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/False to True Transition/Compare to Constant'
 * '<S262>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/False to True Transition/Compare to Constant1'
 * '<S263>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Rack Stall Detection/Dumping'
 * '<S264>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Rack Stall Detection/Lowering'
 * '<S265>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Rack Stall Detection/Racking'
 * '<S266>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Rack Stall Detection/Valve command history proves not rack stalled (resets to false)'
 * '<S267>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Valve commands recently became zero/Lift expired?'
 * '<S268>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Valve commands recently became zero/Tilt expired?'
 * '<S269>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Valve commands recently became zero/Lift expired?/Compare To Zero'
 * '<S270>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Valve commands recently became zero/Lift expired?/Compare To Zero3'
 * '<S271>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Valve commands recently became zero/Lift expired?/Decrement Timer'
 * '<S272>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Valve commands recently became zero/Lift expired?/Enable Condition'
 * '<S273>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Valve commands recently became zero/Tilt expired?/Compare To Zero'
 * '<S274>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Valve commands recently became zero/Tilt expired?/Compare To Zero3'
 * '<S275>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Valve commands recently became zero/Tilt expired?/Decrement Timer'
 * '<S276>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Pseudo-Frictionless Weigh Common Measurement Conditions/Valve commands recently became zero/Tilt expired?/Enable Condition'
 * '<S277>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Racked/Latched Point Hysteresis'
 * '<S278>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Racked/Latched Point Hysteresis/Unit Delay External IC'
 * '<S279>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Secure Payload Unlatch Logic/Apply Name1'
 * '<S280>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Single Pole Low Pass Filter1/NotFirstLoop'
 * '<S281>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Single Pole Low Pass Filter1/Reset'
 * '<S282>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Sliding/Latched Point Hysteresis'
 * '<S283>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Sliding/Latched Point Hysteresis/Unit Delay External IC'
 * '<S284>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Statistics Estimation1/MATLAB Function'
 * '<S285>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Statistics Estimation1/MATLAB Function1'
 * '<S286>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Statistics Estimation1/Two Sided St. Dev. from Bound'
 * '<S287>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Statistics Estimation2/MATLAB Function'
 * '<S288>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Statistics Estimation2/MATLAB Function1'
 * '<S289>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Statistics Estimation2/Two Sided St. Dev. from Bound'
 * '<S290>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Variance Anti-Noise Filter1/MATLAB Function'
 * '<S291>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Variance Anti-Noise Filter2/MATLAB Function'
 * '<S292>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Weighing Statistics, No Notch, No Latch/One Sided Confidence Limit'
 * '<S293>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Weighing Statistics, No Notch, No Latch/Two Sided Confidence Limit'
 * '<S294>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Weighing Statistics, Notch, No Latch/One Sided Confidence Limit'
 * '<S295>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Weighing Statistics, Notch, No Latch/Two Sided Confidence Limit'
 * '<S296>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Weighing Statistics, Secure Latched/One Sided Confidence Limit'
 * '<S297>' : 'toa_wl00/Tip-Off Assist Support Lib/Tip-Off Assist Payload/Pseudo-Frictionless Weigh/Weighing Statistics, Secure Latched/Two Sided Confidence Limit'
 */

/*-
 * Requirements for '<Root>': toa_wl00
 */
#endif                                 /* RTW_HEADER_toa_wl00_h_ */
