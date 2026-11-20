/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: toa_wl00_po.c
 **
 ** Real-Time Workshop code generated for Simulink model toa_wl00.
 **
 ** Model version                        : 1.44
 ** Real-Time Workshop file version      : 8.13 (R2017b) 24-Jul-2017
 ** TLC version                          : 8.13 (Jul 25 2017)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.6.1
 **
 ******************************************************************************/
/*
 ** This file contains the 'Package Object'.  This file (and any generated CAT
 ** map files) contain all information unique to a particular instance of the
 ** package.
 **
 ** This allows a single package to be instantiated multiple times w/o
 ** modification of the underlying package code.
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#include <toa_wl00_po.h>
#include <toa_wl00_Pack_proto.h>
#include <toa_wl00_Pack_types.h>
#include <toa_wl00_private.h>
#include <toa_wl00_model_if.h>

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/
toa_wl00_work_t toa_wl00_work;

/* Package config struct initialization: toa_wl00 */
static const toa_wl00_config_t toa_wl00_config = {
  {
    /* Package Interface. */
    {
      /* Inport mapping. */
      &TOA_invalidate_outputs,         /* 001  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          invalidate outputs */
      &TOA_lift_valve_cmd,             /* 002  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          lift valve cmd */
      &TOA_tilt_valve_cmd,             /* 003  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          tilt valve cmd */
      &TOA_tilt_extension,             /* 004  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          tilt extension */
      &TOA_lift_angle,                 /* 005  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          lift angle */
      &TOA_lift_he_pressure,           /* 006  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          lift he pressure */
      &TOA_lift_re_pressure,           /* 007  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          lift re pressure */
      &TOA_tilt_he_pressure,           /* 008  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          tilt he pressure */
      &TOA_tilt_re_pressure,           /* 009  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          tilt re pressure */
      &TOA_steering_angle,             /* 010  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          Steering Angle */
      &TOA_tool_mass,                  /* 011  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          tool mass */
      &TOA_truck_target_wt,            /* 012  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          pcs truck target */
      &TOA_truck_start_weight,         /* 013  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          pcs truck start weight */
      &TOA_bucket_current_weight_accuracy,/* 014  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                             pcs bucket current weight accuracy */
      &TOA_bucket_current_weight,      /* 015  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          pcs bucket current weight */
      &TOA_tipoff_mode,                /* 016  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          tipoff mode */
      &TOA_eef_imu_accelX,             /* 017  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          EEF IMU Acceleration X */
      &TOA_eef_imu_accelY,             /* 018  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          EEF IMU Acceleration Y */
      &TOA_eef_imu_accelZ,             /* 019  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          EEF IMU Acceleration Z */
      &TOA_zero_offset,                /* 020  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          zero offset weight */
      &TOA_simple_cal_factor,          /* 021  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          simple cal adjust factor */
      &TOA_imu_pitch_cal,              /* 022  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          IMU placement error correction angle */
      &TOA_bucket_angle,               /* 023  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          Bucket_Angle */
      &TOA_unlatch_trigger,            /* 024  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          Unlatch_Trigger */
      &TOA_anchor_zero_offset,         /* 025  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          Anchor Zero Offset */
      &TOA_anchor_factor,              /* 026  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          Anchor Factor */
      &TOA_Pass_Count,                 /* 027  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          CPM Pass Count */
      &TOA_Lift_Norm_Angle,            /* 028  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          Lift_Norm_Angle */
      &TOA_Lift_Norm_Length,           /* 029  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          Lift_Norm_Length */
      &TOA_Tilt_Norm_Angle,            /* 030  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          Tilt_Norm_Angle */
      &TOA_Tilt_Norm_Length,           /* 031  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          Tilt_Norm_Length */
      &TOA_Friction_Mu,                /* 032  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          Friction_Mu */
      &TOA_Friction_Offset,            /* 033  SrcHeader: toa_wl00_model_if.h, toa_wl00_model_if.h
                                          Friction_Offset */
    },

    {
      /* Outport mapping. */
      &TOA_tilt_sensitivity_out,       /* 001  SrcHeader: toa_wl00_model_if.h
                                          tilt sensitivity */
      &TOA_tilt_pressure_out,          /* 002  SrcHeader: toa_wl00_model_if.h
                                          tilt he pressure out */
      &TOA_arbitrated_payload_norm_error_out,/* 003  SrcHeader: toa_wl00_model_if.h
                                                Arbitrated_Payload_Norm_Error */
      &TOA_weigh_status_out,           /* 004  SrcHeader: toa_wl00_model_if.h
                                          Weigh_Status */
      &TOA_payload_norm_stdev_out,     /* 005  SrcHeader: toa_wl00_model_if.h
                                          Payload_Norm_Stdev */
      &TOA_pcs_weight_accuracy_out,    /* 006  SrcHeader: toa_wl00_model_if.h
                                          PCS_Bucket_Current_Weight_Accuracy_Out */
      &TOA_current_weight_norm_error_out,/* 007  SrcHeader: toa_wl00_model_if.h
                                            PCS_Bucket_Current_Weight_Norm_Error_Out */
      &TOA_error_code_out,             /* 008  SrcHeader: toa_wl00_model_if.h
                                          Tipoff_Assist_Adv_Error_Code */
      &TOA_spill_rate_out,             /* 009  SrcHeader: toa_wl00_model_if.h
                                          Spill_Rate_Norm */
      &TOA_bucket_payload_target,      /* 010  SrcHeader: toa_wl00_model_if.h
                                          Bucket Payload Target */
      &TOA_payload_send_to_CPM,        /* 011  SrcHeader: toa_wl00_model_if.h
                                          Payload_Send_To_CPM */
      &TOA_payload_status_send_to_CPM, /* 012  SrcHeader: toa_wl00_model_if.h
                                          Payload_Status_Send_To_CPM */
      &TOA_unsecured_payload_upper_bound_norm,/* 013  SrcHeader: toa_wl00_model_if.h
                                                 Unsecured_Payload_Upper_Bound_Norm */
      &TOA_unsecured_payload_lower_bound_norm,/* 014  SrcHeader: toa_wl00_model_if.h
                                                 Unsecured_Payload_Lower_Bound_Norm  */
      &TOA_unsecured_PFW_status,       /* 015  SrcHeader: toa_wl00_model_if.h
                                          Unsecured_PFW_Status */
      &TOA_min_secure_bucket_angle,    /* 016  SrcHeader: toa_wl00_model_if.h
                                          Min_Secure_Bucket_Angle */
    }
  }
};

/* Initialization Function */
void toa_wl00_po_init(void)
{
  toa_wl00_pack_init( &toa_wl00_work, &toa_wl00_config );
}

/* 0.02 second periodic function */
void toa_wl00_po_0(void)
{
  toa_wl00_method_update( &toa_wl00_work, &toa_wl00_config );
}

/*Additional Definitions*/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
