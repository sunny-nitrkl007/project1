/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: LIBINFO_WL_00_PackMethods.c
 **
 ** Real-Time Workshop code generated for Simulink model LIBINFO_WL_00.
 **
 ** Model version                        : 1.118
 ** Real-Time Workshop file version      : 8.3 (R2012b) 20-Jul-2012
 ** TLC version                          : 8.3 (Jul 21 2012)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.3.3
 **
 ******************************************************************************/
/*
 ** This file contains the functions which provide a Package
 ** Architecture interface for the generated functions
 */

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#include <LIBINFO_WL_00.h>
#include <LIBINFO_WL_00_private.h>
#include <LIBINFO_WL_00_Pack_proto.h>
#include <sl_cal.h>
#include <applib_public.h>
#include <LIBINFO_WL_00_po.h>

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/* Run state enumeration */
enum {
  RS_NEVER_STARTED = 100,
  RS_HALT,
  RS_RUN,
  RS_WAIT_FOR_HALT
};

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/
static void LIBINFO_WL_00_ptr_mgmt( LIBINFO_WL_00_work_t *work, const
  LIBINFO_WL_00_config_t *config ) ;

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/

/******************************************************************************
   FUNCTION NAME         : LIBINFO_WL_00_method_update - 0.12 second
   DESCRIPTION           :

   PARAMETER DESCRIPTION :

   RETURN VALUE:
   void
 ******************************************************************************/
void LIBINFO_WL_00_method_update(
  LIBINFO_WL_00_work_t *work,
  const LIBINFO_WL_00_config_t *config
  )
{
  /* Update sl_cal state */
  LIBINFO_WL_00_ptr_mgmt(work,config);

  /* Verify model is in run state */
  if (RS_RUN == work->runState ) {
    /* Pre model step function code */

    /* Execute model step function. */
    LIBINFO_WL_00_step(
                       &(work->LIBINFO_WL_00_M),
                       &(work->BlockIO),
                       &(work->D_Work),
                       *(config->PackIF.u.ground_speed),
                       *(config->PackIF.u.payload_ratio),
                       *(config->PackIF.u.payload_ratio_raw),
                       *(config->PackIF.u.ext_force_normalized),
                       *(config->PackIF.u.lift_valve_cmd),
                       *(config->PackIF.u.tilt_valve_cmd),
                       *(config->PackIF.u.bucket_angle),
                       *(config->PackIF.u.lift_angle),
                       *(config->PackIF.u.desired_gear),
                       *(config->PackIF.u.engine_speed),
                       *(config->PackIF.u.tilt_lever_cmd),
                       *(config->PackIF.u.tilt_cyl_position),
                       *(config->PackIF.u.machine_idle),
                       *(config->PackIF.u.key_switch),
                       *(config->PackIF.u.real_time),
                       *(config->PackIF.u.fuel_high_res),
                       *(config->PackIF.u.fuel),
                       *(config->PackIF.u.fuel_rate),
                       *(config->PackIF.u.fuel_rate_ard),
                       *(config->PackIF.u.realTime_status),
                       *(config->PackIF.u.gps_latitude),
                       *(config->PackIF.u.gps_longitude),
                       *(config->PackIF.u.gps_lat_long_status),
                       *(config->PackIF.u.payload_weight),
                       *(config->PackIF.u.payloadCalcMethod),
                       *(config->PackIF.u.service_hour_meter),
                       *(config->PackIF.u.timezone_offset),
                       *(config->PackIF.u.payload_weight_status),
                       *(config->PackIF.u.payload_ratio_status),
                       *(config->PackIF.u.payload_ratio_raw_status),
                       *(config->PackIF.u.Impl_operation_status),
                       config->PackIF.y.commit_segment_record,
                       config->PackIF.y.segment_record_id,
                       config->PackIF.y.segment_rec_start_simTime,
                       config->PackIF.y.segment_rec_duration,
                       config->PackIF.y.segment_rec_distance,
                       config->PackIF.y.segment_rec_start_real_time,
                       config->PackIF.y.segment_rec_fuel_used,
                       config->PackIF.y.segment_rec_latitude,
                       config->PackIF.y.segment_rec_longitude,
                       config->PackIF.y.segment_rec_idle_time,
                       config->PackIF.y.segment_rec_hour_meter,
                       config->PackIF.y.segment_rec_payload,
                       config->PackIF.y.segment_rec_payload_calc_method,
                       config->PackIF.y.commit_rec_gps,
                       config->PackIF.y.segment_dig_state,
                       config->PackIF.y.segment_last_completed_id,
                       config->PackIF.y.segment_time_since_last_end,
                       config->PackIF.y.segment_sequence_number,
                       config->PackIF.y.keyswitch_override_flag,
                       config->PackIF.y.segment_active_segment_id);

    /* Get model outputs here */

    /* Post model step function code */
  }
}

/******************************************************************************
   FUNCTION NAME         : LIBINFO_WL_00_pack_init
   DESCRIPTION           :

   PARAMETER DESCRIPTION :

   RETURN VALUE:
   void
 ******************************************************************************/
void LIBINFO_WL_00_pack_init(
  LIBINFO_WL_00_work_t *work,
  const LIBINFO_WL_00_config_t *config
  )
{
  /* Initialize runState */
  work->runState = RS_NEVER_STARTED;

  /* Perform calibration set update/validation
   *   If all pointers are valid, this will also
   *   perform model initialization */
  LIBINFO_WL_00_ptr_mgmt(work,config);
}

/******************************************************************************
   FUNCTION NAME         : LIBINFO_WL_00_ptr_mgmt
   DESCRIPTION           :

   PARAMETER DESCRIPTION :

   RETURN VALUE:
   void
 ******************************************************************************/
/* Pointer update function */
static void LIBINFO_WL_00_ptr_mgmt( LIBINFO_WL_00_work_t *work, const
  LIBINFO_WL_00_config_t *config )
{
  /* Temporary state */
  bool_t isStable;
  bool_t isOK;

  /* Loop until reach end-state */
  do {
    isStable = TRUE;
    switch (work->runState) {
     case RS_NEVER_STARTED:
      /* Initialize sl_cal state */
      sl_cal_init(config->variantObj);

      /* Initialize develop state */
      MODULE_NO_RUN(&(work->applibState),0);

      /* Move onto the next state this loop */
      work->runState = RS_HALT;
      isStable = false;
      break;

     case RS_HALT:
      /* Update sl_cal state and initialize all pointers */
      isOK = (MODULE_RUN_FOR_DEVELOP_COMMAND(&(work->applibState))) ?
        sl_cal_mutable_select(config->variantObj) : sl_cal_select
        (config->variantObj);
      if (isOK ) {
        /* Model initialization */
        {
          /* Execute Model Initializations */
          LIBINFO_WL_00_initialize(
            &(work->LIBINFO_WL_00_M),
            &(work->BlockIO),
            &(work->D_Work),
                                   (config->PackIF.u.ground_speed),
                                   (config->PackIF.u.payload_ratio),
                                   (config->PackIF.u.payload_ratio_raw),
                                   (config->PackIF.u.ext_force_normalized),
                                   (config->PackIF.u.lift_valve_cmd),
                                   (config->PackIF.u.tilt_valve_cmd),
                                   (config->PackIF.u.bucket_angle),
                                   (config->PackIF.u.lift_angle),
                                   (config->PackIF.u.desired_gear),
                                   (config->PackIF.u.engine_speed),
                                   (config->PackIF.u.tilt_lever_cmd),
                                   (config->PackIF.u.tilt_cyl_position),
                                   (config->PackIF.u.machine_idle),
                                   (config->PackIF.u.key_switch),
                                   (config->PackIF.u.real_time),
                                   (config->PackIF.u.fuel_high_res),
                                   (config->PackIF.u.fuel),
                                   (config->PackIF.u.fuel_rate),
                                   (config->PackIF.u.fuel_rate_ard),
                                   (config->PackIF.u.realTime_status),
                                   (config->PackIF.u.gps_latitude),
                                   (config->PackIF.u.gps_longitude),
                                   (config->PackIF.u.gps_lat_long_status),
                                   (config->PackIF.u.payload_weight),
                                   (config->PackIF.u.payloadCalcMethod),
                                   (config->PackIF.u.service_hour_meter),
                                   (config->PackIF.u.timezone_offset),
                                   (config->PackIF.u.payload_weight_status),
                                   (config->PackIF.u.payload_ratio_status),
                                   (config->PackIF.u.payload_ratio_raw_status),
                                   (config->PackIF.u.Impl_operation_status),
            config->PackIF.y.commit_segment_record,
            config->PackIF.y.segment_record_id,
            config->PackIF.y.segment_rec_start_simTime,
            config->PackIF.y.segment_rec_duration,
            config->PackIF.y.segment_rec_distance,
            config->PackIF.y.segment_rec_start_real_time,
            config->PackIF.y.segment_rec_fuel_used,
            config->PackIF.y.segment_rec_latitude,
            config->PackIF.y.segment_rec_longitude,
            config->PackIF.y.segment_rec_idle_time,
            config->PackIF.y.segment_rec_hour_meter,
            config->PackIF.y.segment_rec_payload,
            config->PackIF.y.segment_rec_payload_calc_method,
            config->PackIF.y.commit_rec_gps,
            config->PackIF.y.segment_dig_state,
            config->PackIF.y.segment_last_completed_id,
            config->PackIF.y.segment_time_since_last_end,
            config->PackIF.y.segment_sequence_number,
            config->PackIF.y.keyswitch_override_flag,
            config->PackIF.y.segment_active_segment_id);
        }

        /* Update run state */
        MODULE_RUN(&(work->applibState),0);

        /* Enter run state now, but don't process its info until next loop */
        work->runState = RS_RUN;
      }
      break;

     case RS_RUN:
      if (MODULE_RUN_FOR_DEVELOP_CHANGE(&(work->applibState)) ||
          !sl_cal_is_selected(config->variantObj,FALSE) ) {
        /* Update develop state */
        MODULE_NO_RUN(&(work->applibState),0);

        /* Move to waiting for halt in preparation of re-initializing */
        work->runState = RS_WAIT_FOR_HALT;
        isStable = FALSE;
      }
      break;

     case RS_WAIT_FOR_HALT:
      {
        /* Move onto the next state this loop */
        work->runState = RS_NEVER_STARTED;
        isStable = false;
      }
      break;

     default:
      /* Restart if unknown */
      work->runState = RS_NEVER_STARTED;
      isStable = false;
    }                                  /* End switch(work->runState) */
  } while (!isStable);
}                                      /* End of LIBINFO_WL_00_ptr_mgmt() */
