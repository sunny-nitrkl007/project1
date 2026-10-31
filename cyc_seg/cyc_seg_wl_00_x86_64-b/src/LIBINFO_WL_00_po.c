/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: LIBINFO_WL_00_po.c
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
#include <LIBINFO_WL_00_po.h>
#include <LIBINFO_WL_00_Pack_proto.h>
#include <LIBINFO_WL_00_Pack_types.h>
#include <LIBINFO_WL_00_private.h>
#include <LIBINFO_WL_if.h>

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/
LIBINFO_WL_00_work_t LIBINFO_WL_00_work;

/* Package config struct initialization: LIBINFO_WL_00 */
static const LIBINFO_WL_00_config_t LIBINFO_WL_00_config = {
  {
    /* Package Interface. */
    {
      /* Inport mapping. */
      &LIBPROD_ground_spd_kph,         /* 001  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          Ground Speed (kph) */
      &LIBPROD_payload_ratio,          /* 002  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          ratio */
      &LIBPROD_payload_ratio_raw,      /* 003  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          ratio */
      &LIBPROD_extForceNormalized,     /* 004  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          kN */
      &LIBPROD_lift_valve_cmd,         /* 005  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          % */
      &LIBPROD_tilt_valve_cmd,         /* 006  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          % */
      &LIBPROD_bucket_angle,           /* 007  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          degrees */
      &LIBPROD_lift_angle,             /* 008  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          degrees */
      &LIBPROD_desired_gear,           /* 009  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          current transmission gear with Direction */
      &LIBPROD_engine_spd_rpm,         /* 010  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          Engine speed (rpm) */
      &LIBPROD_tilt_lever_cmd,         /* 011  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          % */
      &LIBPROD_tilt_cyl_pos,           /* 012  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          mm */
      &LIBPROD_machine_idle_status,    /* 013  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          Datalink state definition */
      &LIBPROD_keyswitch_state,        /* 014  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          non-zero is ON */
      &LIBPROD_real_time,              /* 015  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          days */
      &LIBPROD_total_fuel_high_res,    /* 016  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          gallons */
      &LIBPROD_total_fuel_low_res,     /* 017  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          gallons */
      &LIBPROD_fuel_rate,              /* 018  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          l/hr */
      &LIBPROD_ARD_fuel_rate,          /* 019  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          l/sec */
      &LIBPROD_realTime_status,        /* 020  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          boolean */
      &LIBPROD_GPS_latitude,           /* 021  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          degrees */
      &LIBPROD_GPS_longitude,          /* 022  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          degrees */
      &LIBPROD_GPS_status,             /* 023  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          boolean */
      &LIBPROD_payload_weight,         /* 024  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          tonnes */
      &LIBPROD_payload_calc_method,    /* 025  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          low to high payload calculation method */
      &LIBPROD_service_hour_meter,     /* 026  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          seconds */
      &LIBPROD_timezone_offset,        /* 027  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          mins */
      &LIBPROD_payload_weight_status,  /* 028  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          boolean */
      &LIBPROD_payload_ratio_status,   /* 029  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          ratio */
      &LIBPROD_payload_ratio_raw_status,/* 030  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                           ratio */
      &LIBPROD_impl_operation_status,  /* 031  SrcHeader: LIBINFO_WL_if.h, LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          Datalink state definition */
    },

    {
      /* Outport mapping. */
      &commit_segment_record,          /* 001  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          boolean */
      &segment_record_id,              /* 002  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          Segment_ID */
      &segment_rec_start_simTime,      /* 003  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          Seconds */
      &segment_rec_duration,           /* 004  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          Seconds */
      &segment_rec_distance,           /* 005  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          km */
      &segment_rec_start_real_time,    /* 006  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          days since epoch */
      &segment_rec_fuel_used,          /* 007  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          liters */
      &segment_rec_latitude,           /* 008  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          degrees */
      &segment_rec_longitude,          /* 009  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          degrees */
      &segment_rec_idle_time,          /* 010  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          seconds */
      &segment_rec_hour_meter,         /* 011  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          seconds */
      &segment_rec_payload,            /* 012  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          tonnes */
      &segment_rec_payload_calc_method,/* 013  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          segment record payload calculation method */
      &commit_rec_gps,                 /* 014  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          boolean */
      &segment_dig_state,              /* 015  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          dig state */
      &segment_last_completed_id,      /* 016  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          last completed segment id */
      &segment_time_since_last_end,    /* 017  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          seconds */
      &segment_sequence_number,        /* 018  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          segment sequence number */
      &keyswitch_override_flag,        /* 019  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          Keyswitch Override Flag */
      &segment_active_segment_id,      /* 020  SrcHeader: LIBINFO_WL_if.h SrcFile: LIBINFO_WL_00_signals.m
                                          Active Segment_ID */
    }
  },
  &(LIBINFO_WL_00_cal)
};

/* Initialization Function */
void LIBINFO_WL_00_po_init(void)
{
  LIBINFO_WL_00_pack_init( &LIBINFO_WL_00_work, &LIBINFO_WL_00_config );
}

/* 0.12 second periodic function */
void LIBINFO_WL_00_po_0(void)
{
  LIBINFO_WL_00_method_update( &LIBINFO_WL_00_work, &LIBINFO_WL_00_config );
}

/*Additional Definitions*/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
