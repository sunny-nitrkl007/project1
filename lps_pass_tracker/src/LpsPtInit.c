/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsInit.c
DESCRIPTION: This file provides the initialization routines for the application software
            for LPS Pass Tracker library.
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <LpsCommonTypeDef.h>
#include <LpsPtPublic.h>

#include "LpsPtPrivate.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
static void LpsPtInitOutputs(const LpsPtInit_t* lpsPtInit);

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
LpsPtWrkTbl_t LpsPtWrkTbl;
 
/******************************************************************************
FUNCTION NAME: LpsPassTrackerInit
DESCRIPTION:             
PARAMETER DESCRIPTION: Pass tracker init function. Call init
*  function before calling update.                      
RETURN VALUE: none
*******************************************************************************/
LpsPtOutputs_t LpsPtInit(const LpsPtInit_t* lpsPtInit) {

    // Initialize Truck
    pcs_truck_init(0.f, 0, FALSE, 0.f, LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE);

    LpsPtInitOutputs(lpsPtInit);

    LpsPtWrkTbl.prev_unlatch_cmd = FALSE;
    LpsPtWrkTbl.disable_auto_tipoff_exit = FALSE;
    LpsPtWrkTbl.previous_dig_detected = FALSE;

    return LpsPtWrkTbl.lpsPtoutputs;
}

void LpsPtRestoreTruck(float initialWeight, unsigned_16 initialPassCount, boolean haveLastPass, float lastPassWeight, unsigned_8 lastPassAccuracy) {
    // Just forward this request on to the private "pcs_truck" object.
    pcs_truck_restore(initialWeight, initialPassCount, haveLastPass, lastPassWeight, lastPassAccuracy);
}

static void LpsPtInitOutputs(const LpsPtInit_t* lpsPtInit) {

    LpsPtWrkTbl.lpsPtoutputs.standby_active = FALSE;

    LpsPtWrkTbl.lpsPtoutputs.pt_current_state = WAIT_FOR_LATCH_BRI;

    // Initialize to show -1, will get updated.
    LpsPtWrkTbl.lpsPtoutputs.show_clear_not_minus_one = FALSE;

    /* restore tip-off settings */
    if (lpsPtInit->tip_off_mode == TIP_OFF_MODE_PILE || lpsPtInit->tip_off_mode == TIP_OFF_MODE_TRUCK)
    {
        LpsPtWrkTbl.lpsPtoutputs.tip_off_mode = lpsPtInit->tip_off_mode;
    }
    else
    {
        LpsPtWrkTbl.lpsPtoutputs.tip_off_mode = TIP_OFF_MODE_PILE;
    }

    LpsPtWrkTbl.lpsPtoutputs.tip_off_active = FALSE;

    LpsPtWrkTbl.lpsPtoutputs.loadUpdate.store = FALSE;
    LpsPtWrkTbl.lpsPtoutputs.loadUpdate.isAutoStore = FALSE;
    LpsPtWrkTbl.lpsPtoutputs.loadUpdate.removePass = FALSE;
    LpsPtWrkTbl.lpsPtoutputs.loadUpdate.clear = FALSE;
    LpsPtWrkTbl.lpsPtoutputs.loadUpdate.addPass = FALSE;
    LpsPtWrkTbl.lpsPtoutputs.loadUpdate.addPassWeight = 0.f;
    LpsPtWrkTbl.lpsPtoutputs.loadUpdate.addPassAccuracy = 0;

    LpsPtWrkTbl.lpsPtoutputs.unlatch_current_bucket_weight = FALSE;
    LpsPtWrkTbl.lpsPtoutputs.dump_detect_capture_cyl_ext_reference = FALSE;
    LpsPtWrkTbl.lpsPtoutputs.clear_reweigh_warning_status = FALSE;

    LpsPtWrkTbl.lpsPtoutputs.display_bucket_weight = 0.f;
    LpsPtWrkTbl.lpsPtoutputs.display_bucket_weight_accuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;
    LpsPtWrkTbl.lpsPtoutputs.display_bucket_weight_available = FALSE;
    LpsPtWrkTbl.lpsPtoutputs.passcount = pcs_truck_get_pass_count();
    LpsPtWrkTbl.lpsPtoutputs.truck_weight = pcs_truck_get_weight();
    LpsPtWrkTbl.lpsPtoutputs.truck_pass_active = pcs_truck_is_pass_active();
    LpsPtWrkTbl.lpsPtoutputs.truck_start_weight = pcs_truck_get_start_weight();

    LpsPtWrkTbl.lpsPtoutputs.configured_tip_off_mode = LpsPtWrkTbl.lpsPtoutputs.tip_off_mode;
    LpsPtWrkTbl.lpsPtoutputs.manual_add_available = FALSE;
}
