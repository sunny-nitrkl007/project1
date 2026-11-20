/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsPtPublic.h
DESCRIPTION: Loader Payload System Pass Tracker public header file.

*******************************************************************************/
#ifndef __LPS_PT_PUBLIC_H__
#define __LPS_PT_PUBLIC_H__

#include <stdint.h>
#include <cat_std_types.h>

#include <LpsCommonStructures.h>

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
// Top Level
#define PCS_NOT_INIT        0x00000000
#define WEIGH_MODE          0x00000001
#define UNCALIBRATED_MODE   0x00000004

// Weigh Mode
#define WAIT_FOR_LATCH_BRI    0x00000011
#define WAIT_FOR_DUMP_ARI   0x00000021
#define TIP_OFF_IRI         0x00000031

// Tip-off Mode
#define TIP_OFF_MODE_PILE          0
#define TIP_OFF_MODE_TRUCK         1

// Tip-off Trigger
#define TIP_OFF_TRIGGER_AUTO       0
#define TIP_OFF_TRIGGER_MANUAL     1
#define TIP_OFF_TRIGGER_DISABLED   2

/*Zero Needed States */
#define PCS_ZERO_NOT_REQUIRED         0
#define PCS_ZERO_REQUIRED_TEMPCHANGE  1
#define PCS_ZERO_REQUIRED_TIMELIMIT   2

typedef struct
{
    unsigned_16 tip_off_mode;        /* Truck/Pile */
} LpsPtInit_t;

typedef struct
{
    boolean cpm_install_status;
    boolean cpm_is_calibrated;
    float pt_time_step_us;

    boolean weigh_range_is_weighing;
    unsigned_32 calc_method;
    float current_weight;
    boolean lift_stalled;
    boolean payload_latch_conditions_ok;    /* Need to know so that we can add pass to truck for reweigh while waiting for latch */
    boolean dump_state_is_partial_dump;
    boolean dump_state_is_full_dump;
    boolean current_bucket_weight_latched;
    boolean dig_detected;

    unsigned_16 tip_off_trigger;        /* Disabled, Auto, Manual */

    boolean tip_off_mode_request_status;
    unsigned_16 tip_off_mode;        /* Truck/Pile */

    boolean store_request_status;
    boolean reweigh_request_status;
    boolean zero_request_status;
    boolean minus_one_request_status;
    boolean clear_request_status;
    boolean tipoff_toggle_request_status;   /* PILE/TRUCK toggle */
    boolean standby_request_status;
    boolean change_mode_weigh;    /* exit standby or exit manual tip-off */
    boolean change_mode_excess; /* enter manual tip-off mode */
    unsigned_16 maximum_pass_count; // Will not allow pass count to exceed this value.
    boolean auto_store_enabled; // Will auto-store when the pass count gets to the maximum pass count.

    boolean manual_add_enabled;
    boolean manual_add_request;

} LpsPtInputs_t;


typedef struct
{
    boolean standby_active;
    unsigned_32 pt_current_state;
    boolean show_clear_not_minus_one;
    unsigned_16 tip_off_mode;
    boolean tip_off_active;

    struct {
        boolean store;
        boolean isAutoStore;
        boolean removePass;

        boolean clear;

        boolean addPass;
        float addPassWeight;
        LpsWeighBktWtAccuracy_t addPassAccuracy;
    } loadUpdate;

    boolean unlatch_current_bucket_weight;
    boolean dump_detect_capture_cyl_ext_reference;
    boolean clear_reweigh_warning_status;

    float display_bucket_weight;
    LpsWeighBktWtAccuracy_t display_bucket_weight_accuracy;
    boolean display_bucket_weight_available;
    unsigned_16 passcount;
    float truck_weight;
    float truck_start_weight;
    boolean truck_pass_active;
    unsigned_16 configured_tip_off_mode;
    boolean manual_add_available;

} LpsPtOutputs_t;



/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
#if defined (__cplusplus)
extern "C"
{
#endif

extern LpsPtOutputs_t LpsPtInit(const LpsPtInit_t* LpsPtInit);
extern LpsPtOutputs_t LpsPtUpdate(const LpsPtInputs_t* LpsPtInputs);

/*
 * Restores a truck, applying the currently active pass on top of this truck information.
 * This is used for multi-task selection where in process tasks (trucks) can be switched on the fly.
 */
extern void LpsPtRestoreTruck(float initialWeight, unsigned_16 initialPassCount, boolean haveLastPass, float lastPassWeight, unsigned_8 lastPassAccuracy);

#if defined (__cplusplus)
}
#endif

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
#endif /* #ifndef __LPS_PT_PUBLIC_H__ */
