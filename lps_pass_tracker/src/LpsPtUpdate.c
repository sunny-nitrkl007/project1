/*******************************************************************************
** COPYRIGHT (C) 2005-2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar’s proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  weighmode.c
DESCRIPTION:

   This file contains the calibration routines used by PCS

*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <LpsCommonStructures.h>

#include "LpsPtPrivate.h"

static unsigned_32 wait_for_latch_bri_state(void);
static unsigned_32 wait_for_dump_ari_state(void);
static unsigned_32 tip_off_iri_state(void);

static unsigned_32 check_requests(void);
static unsigned_32 zero_func(void);
static unsigned_32 clear_func(void);
static unsigned_32 minus_one_func(void);
static unsigned_32 reweigh_func(void);
static unsigned_32 standby_func(void);
static unsigned_32 weighmode_func(void);
static unsigned_32 tipoff_on_func(void);
static unsigned_32 tipoff_off_func(void);
static unsigned_32 store_func(boolean);
static unsigned_32 manual_add_func(void);
static boolean is_manual_add_available(void);

static void pcs_cycle_close(float weight, unsigned_8 accuracy);

static void pcs_tip_off_toggle_mode(void);
static void pcs_tip_off_reset_toggle(void);

static void pcs_display_wt_update(void);

static void reset_output_data(void);
static void unlatch_current_bucket_weight(void);

static void dump_detect_capture_cyl_ext_reference(void);

LpsPtInputs_t lpsPtInputs;

LpsPtOutputs_t LpsPtUpdate(const LpsPtInputs_t* in)
{
    unsigned_32 newstate;

    lpsPtInputs = *in; // Why we are copying the entire thing instead of just referencing what was passed?

    /* reset output buffer */
    reset_output_data();

    { /* capture current weight and accuracy */
    	unsigned_8 accuracy = GET_ACCURACY(lpsPtInputs.calc_method);
    	if (LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE == accuracy)
    	{
    		float weight = pcs_bucket_get_current_weight(NULL);
        	pcs_bucket_set_current_weight(accuracy, weight);
        }
        else
        {
        	pcs_bucket_set_current_weight(accuracy, lpsPtInputs.current_weight);
        }
     }

    if ( lpsPtInputs.cpm_install_status == TRUE)
    {
        if (!(lpsPtInputs.cpm_is_calibrated))
        {
            store_func(FALSE);

            LpsPtWrkTbl.lpsPtoutputs.pt_current_state = UNCALIBRATED_MODE;
            LpsPtWrkTbl.lpsPtoutputs.display_bucket_weight_available = FALSE;
            return LpsPtWrkTbl.lpsPtoutputs;
        }

        /* Tend to Requests for mode change workstate is where we will do this activity */
        LpsPtWrkTbl.lpsPtoutputs.pt_current_state = check_requests();

        // Primary task switcher
        switch (LpsPtWrkTbl.lpsPtoutputs.pt_current_state)
        {
        case WAIT_FOR_LATCH_BRI:
            newstate = wait_for_latch_bri_state();
            break;

        case WAIT_FOR_DUMP_ARI:
            newstate = wait_for_dump_ari_state();
            break;

        case TIP_OFF_IRI:
            newstate = tip_off_iri_state();
            break;

        default:
            newstate = WAIT_FOR_LATCH_BRI;
            break;
        }

        /* save off the new state */
        LpsPtWrkTbl.lpsPtoutputs.pt_current_state = newstate;

        /*
         * Do we show the clear button or the minus one button?
         */
        if (pcs_truck_has_passes()) {
            // If there are passes, then only show the clear button if there is nothing to -1
            if (pcs_truck_is_pass_active() || pcs_truck_has_last_pass()) {
                LpsPtWrkTbl.lpsPtoutputs.show_clear_not_minus_one = FALSE;
            }
            else {
                LpsPtWrkTbl.lpsPtoutputs.show_clear_not_minus_one = TRUE;
            }
        }
        else {
            // Always show the -1 button if there are no passes.
            LpsPtWrkTbl.lpsPtoutputs.show_clear_not_minus_one = FALSE;
        }

        /*
         * Reset the tip-off toggle state any time we are not in tipoff
         */
        if (TIP_OFF_IRI != LpsPtWrkTbl.lpsPtoutputs.pt_current_state) {
            pcs_tip_off_reset_toggle();
            LpsPtWrkTbl.disable_auto_tipoff_exit = FALSE;
        }

        /*
         * If we are in tip-off, then indicate this through manual
         * tip button state.  If manually triggered tip-off is not
         * enabled, then this will not be shown in the UI anyway.
         */
        if (TIP_OFF_IRI == LpsPtWrkTbl.lpsPtoutputs.pt_current_state) {
            LpsPtWrkTbl.lpsPtoutputs.tip_off_active = TRUE;
        }
        else {
            LpsPtWrkTbl.lpsPtoutputs.tip_off_active = FALSE;
        }

        pcs_truck_display_update();
        pcs_display_wt_update();
        LpsPtWrkTbl.lpsPtoutputs.passcount = pcs_truck_display_get_pass_count();
        LpsPtWrkTbl.lpsPtoutputs.truck_weight = pcs_truck_display_get_weight();
        LpsPtWrkTbl.lpsPtoutputs.truck_pass_active = pcs_truck_is_pass_active();
        LpsPtWrkTbl.lpsPtoutputs.truck_start_weight = pcs_truck_get_start_weight();
    }

    /* capture the unlatch command, we do this to ensure that the next loop, the
     * current_bucket_weight_latched input is reset before it gets set again. If
     * it doesn't, atleast we waited for 1 loop for the reset to happen */
    LpsPtWrkTbl.prev_unlatch_cmd = LpsPtWrkTbl.lpsPtoutputs.unlatch_current_bucket_weight;

    LpsPtWrkTbl.previous_dig_detected = lpsPtInputs.dig_detected;

    LpsPtWrkTbl.lpsPtoutputs.manual_add_available = is_manual_add_available();

    return(LpsPtWrkTbl.lpsPtoutputs);
}

static unsigned_32 standby_func(void)
{
    pcs_truck_cancel_pass();
    unlatch_current_bucket_weight();

    // clear any reweigh warnings on entry to standby
    LpsPtWrkTbl.lpsPtoutputs.clear_reweigh_warning_status = TRUE;

    LpsPtWrkTbl.lpsPtoutputs.standby_active = TRUE;
    return WAIT_FOR_LATCH_BRI;
}

static unsigned_32 weighmode_func(void)
{
    if ((WAIT_FOR_DUMP_ARI == LpsPtWrkTbl.lpsPtoutputs.pt_current_state) ||
        (TIP_OFF_IRI == LpsPtWrkTbl.lpsPtoutputs.pt_current_state))
    {
        unlatch_current_bucket_weight();
    }

    // clear any reweigh warnings on entry back into weighmode from standby
    LpsPtWrkTbl.lpsPtoutputs.clear_reweigh_warning_status = TRUE;

    LpsPtWrkTbl.lpsPtoutputs.standby_active = FALSE;
    return WAIT_FOR_LATCH_BRI;
}

/*-------------------------------------------------------------------------------------------------------------**
** Function used when processing button requests. Display shows a Tipoff ON button when Tipoff is set to Manual
** and is currently in normal (weigh mode) operating mode.
**
** Returns: state machine state (wait for dump/wait for latch/tip off)
**
**-------------------------------------------------------------------------------------------------------------*/
static unsigned_32 tipoff_on_func(void)
{
    unsigned_32 state = LpsPtWrkTbl.lpsPtoutputs.pt_current_state;

    if (WAIT_FOR_LATCH_BRI == state) {
        state = reweigh_func();
    }

    if (WAIT_FOR_DUMP_ARI == state) {
        // Manual Tipoff - Tipoff ON
        // Prep for Tipoff state by capturing start weight
        pcs_bucket_capture_start_weight();
        unlatch_current_bucket_weight();
        state = TIP_OFF_IRI;
    }

    if (TIP_OFF_IRI == state) {
        // We made it to the tipoff state
        // We are deciding not to "automatically" keep the pass here.
        // even though the operator manually turned tip-off on.
        //pcs_truck_keep_pass();
        reweigh_func();
        LpsPtWrkTbl.disable_auto_tipoff_exit = TRUE;
    }

    return state;
}

/*-------------------------------------------------------------------------------------------------------------**
** Function used when processing button requests. Display shows a Tipoff OFF button when Tipoff is set to Manual
** and is currently in excess (tipoff) operating mode.
**
** Returns: state machine state (wait for dump/wait for latch/tip off)
**
**-------------------------------------------------------------------------------------------------------------*/
static unsigned_32 tipoff_off_func(void)
{
    unsigned_32 state = LpsPtWrkTbl.lpsPtoutputs.pt_current_state;

    // Only exit tip-off if we are in tip-off
    if (TIP_OFF_IRI == state) {
        if (TIP_OFF_MODE_TRUCK == LpsPtWrkTbl.lpsPtoutputs.tip_off_mode) {
            /*
             * Since we are closing without dumping all of the weight, we need
             * to only capture the difference that was put in the truck
             */
            unsigned_8 currentAccuracy, startAccuracy, accuracy;
            float currentWeight = pcs_bucket_get_current_weight(&currentAccuracy);
            float startWeight = pcs_bucket_get_start_weight(&startAccuracy);
            float weight = startWeight - currentWeight;
            accuracy = ((currentAccuracy <= startAccuracy) ? currentAccuracy : startAccuracy);
            pcs_cycle_close(weight, accuracy);
            unlatch_current_bucket_weight();
            state = WAIT_FOR_LATCH_BRI;
        }
        else { /* TIP_OFF_MODE_PILE */
            dump_detect_capture_cyl_ext_reference();
            state = WAIT_FOR_DUMP_ARI;
        }
    }

    LpsPtWrkTbl.disable_auto_tipoff_exit = FALSE;
    return state;
}

static unsigned_32 minus_one_func(void)
{
    if (pcs_truck_has_passes()) {
        if (pcs_truck_is_pass_active()) {
            pcs_truck_cancel_pass();
        }
        else {
            /*
             * Truck has passes but a pass is not active, which means we likely have a
             * last payload weight that was added.
             */
            if (pcs_truck_remove_last_pass()) {
                /*
                 * We have removed the last pass.
                 * Notify the application to remove the pass.
                 * We won't be able to remove another pass until a new pass is added.
                 */
                //LpsPtWrkTbl.lpsPtoutputs.loadUpdate.removePass = TRUE;
            }

            LpsPtWrkTbl.lpsPtoutputs.loadUpdate.removePass = TRUE;

        }

        unlatch_current_bucket_weight();
    }
    else {
        // no passes, let application manage minus-1 for split loads
        LpsPtWrkTbl.lpsPtoutputs.loadUpdate.removePass = TRUE;
    }

    return WAIT_FOR_LATCH_BRI;
}

static unsigned_32 store_func(boolean autoStore)
{
    if (pcs_truck_has_passes())
    {
        if (!autoStore)
        {
            /*
            ** We need to close out the current cycle if we are currently in one.
            */
            if (WAIT_FOR_DUMP_ARI == LpsPtWrkTbl.lpsPtoutputs.pt_current_state)
            {
                /* Store whatever they saw on the display */
                unsigned_8 accuracy;
                float weight = pcs_truck_get_current_pass_weight(&accuracy);
                pcs_truck_keep_pass();
                pcs_cycle_close(weight, accuracy);
            }
            /* If store was pressed while in tipoff (pile or truck), close and save the cycle */
            else if (TIP_OFF_IRI == LpsPtWrkTbl.lpsPtoutputs.pt_current_state)
            {
                if (TIP_OFF_MODE_PILE == LpsPtWrkTbl.lpsPtoutputs.tip_off_mode)
                {
                    /* Store the 'split' weight, which is potentially not the number shown on the display.
                        This is why the display 'pauses' the truck weight in this case.
                    */
                    unsigned_8 accuracy;
                    float weight = pcs_bucket_get_split_weight(&accuracy);
                    pcs_truck_keep_pass();
                    pcs_cycle_close(weight, accuracy);

                    // Needs to be done after the pass is updated
                    pcs_truck_display_pause_on_clear();
                }
                else /* TIP_OFF_MODE_TRUCK */
                {
                    /* Store whatever they saw on the display */
                    unsigned_8 accuracy;
                    float weight = pcs_truck_get_current_pass_weight(&accuracy);
                    pcs_truck_keep_pass();
                    pcs_cycle_close(weight, accuracy);
                }
            }
        }

        unlatch_current_bucket_weight();

        pcs_truck_clear();
    }

    // Notify the application of the store. Do this regardless of passes. This is
    // so that the application can close out a split load correctly even if a new
    // split load did not have any passes
    LpsPtWrkTbl.lpsPtoutputs.loadUpdate.store = TRUE;
    LpsPtWrkTbl.lpsPtoutputs.loadUpdate.isAutoStore = autoStore;

    return WAIT_FOR_LATCH_BRI;
}

static unsigned_32 manual_add_func(void) {
    unsigned_32 state = LpsPtWrkTbl.lpsPtoutputs.pt_current_state;

    if (pcs_truck_is_pass_active()) {
        /*
         * We need to close out the current cycle if we are currently in one.
         */

        /* Store whatever they saw on the display */
        unsigned_8 accuracy;
        float weight = pcs_truck_get_current_pass_weight(&accuracy);
        pcs_truck_keep_pass();
        pcs_cycle_close(weight, accuracy);

        unlatch_current_bucket_weight();

        state = WAIT_FOR_LATCH_BRI;
    }
    else {
        // We don't have an active pass, try to recall previously active pass
        if (pcs_truck_recall_pass()) {
            // If we recalled a pass, tell the application about it
            unsigned_8 passAccuracy;
            LpsPtWrkTbl.lpsPtoutputs.loadUpdate.addPass = TRUE;
            LpsPtWrkTbl.lpsPtoutputs.loadUpdate.addPassWeight = pcs_truck_get_current_pass_weight(&passAccuracy);
            LpsPtWrkTbl.lpsPtoutputs.loadUpdate.addPassAccuracy = passAccuracy;

            unlatch_current_bucket_weight();
            state = WAIT_FOR_LATCH_BRI;
        }

        // Another design option here is to just treat this as a reweigh (new weight) instead of a recall (old weight).
    }

    return state;
}

static boolean is_manual_add_available(void) {
    boolean available;

    if (pcs_truck_is_pass_active()) {
        if (pcs_truck_is_keeping_pass()) {
            // We are already keeping the pass, manual add is not longer available/necessary.
            available = FALSE;
        }
        else {
            // We have a pass active and it has not been marked to keep yet, so the manual
            // add operation is available to that is can be marked to keep.
            available = TRUE;
        }
    }
    else {
        if (pcs_truck_has_recall_pass()) {
            // A pass is not active, but there is a pass available to recall with the manual
            // add operation, so manual add is available.
            available = TRUE;
        }
        else {
            // A pass is not active and there is nothing to recall, so the manual add
            // operation is not available.
            available = FALSE;
        }
    }

    return available;
}

/* Get a new zero value if all of the conditions are met */
static unsigned_32 zero_func(void)
{
    pcs_truck_cancel_pass();
    unlatch_current_bucket_weight();
    return WAIT_FOR_LATCH_BRI;
}

/*
 * Clears the current trucks information.
 */
static unsigned_32 clear_func(void)
{
    pcs_truck_clear();

    // Notify the application to clear the load
    LpsPtWrkTbl.lpsPtoutputs.loadUpdate.clear = TRUE;

    unlatch_current_bucket_weight();

    return WAIT_FOR_LATCH_BRI;
}

// The operator has made a request to reweigh.  As long as the last lift has not
// been cleared (because we are now in a new weigh cycle) or we have already pushed
// the reweigh button we will honor this request
static unsigned_32 reweigh_func(void)
{
    unsigned_32 state = LpsPtWrkTbl.lpsPtoutputs.pt_current_state;

    if (pcs_truck_is_pass_active()) {
        /* unlatch weight and set accuracy to low*/
        unlatch_current_bucket_weight();
        float weight = pcs_bucket_get_current_weight(NULL);
        pcs_bucket_set_current_weight(LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_LOW, weight);

        // We are deciding to not "automatically" keep the pass here
        // even though the operator manually hit the reweigh button.
        //pcs_truck_keep_pass();
    }
    else { /* WAIT_FOR_LATCH_BRI */
        if ((lpsPtInputs.payload_latch_conditions_ok) &&
                (pcs_truck_get_pass_count() < lpsPtInputs.maximum_pass_count)) {
            unsigned_8 accuracy;
            float weight;

            /* unlatch weight and set accuracy to low*/
            unlatch_current_bucket_weight();
            weight = pcs_bucket_get_current_weight(NULL);
            pcs_bucket_set_current_weight(LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_LOW, weight);

            pcs_bucket_capture_start_weight();
            dump_detect_capture_cyl_ext_reference();

            weight = pcs_bucket_get_start_weight(&accuracy);

            if (!(LpsPtWrkTbl.lpsPtoutputs.standby_active))
            {
                // Automatically keep this pass if manual add is disabled.
                // Otherwise, require a manual add operation to keep the pass.
                // (yes, even though they manually requested the reweigh)
                boolean keepPass = lpsPtInputs.manual_add_enabled ? FALSE : TRUE;
                pcs_truck_start_pass(weight, accuracy, keepPass);
            }

            state = WAIT_FOR_DUMP_ARI;
        }
        else {
            state = WAIT_FOR_LATCH_BRI;
        }
    }

    return state;
}

// Tend to requests from the operator
static unsigned_32 check_requests(void)
{
    unsigned_32 state = LpsPtWrkTbl.lpsPtoutputs.pt_current_state;

    // Handle tip-off mode change request
    if (lpsPtInputs.tip_off_mode_request_status) {
        LpsPtWrkTbl.lpsPtoutputs.tip_off_mode = lpsPtInputs.tip_off_mode;
        LpsPtWrkTbl.lpsPtoutputs.configured_tip_off_mode = lpsPtInputs.tip_off_mode;
    }


    if (LpsPtWrkTbl.lpsPtoutputs.standby_active) {
        /*
         * Standby is active
         */

        // Check for weigh mode request (exit standby)
        if (lpsPtInputs.change_mode_weigh) {
            state = weighmode_func();
        }

        // Check for manual add request
        else if (lpsPtInputs.manual_add_request) {
            // ignore manual add request if in standby, refer to us25198
        }

        // Check for a reweigh request
        else if (lpsPtInputs.reweigh_request_status) {
            state = reweigh_func();
        }

        // Check for enter manual tip-off request
        else if (lpsPtInputs.change_mode_excess) {
            state = weighmode_func();

            // If we made it into weigh mode, then enter tip-of
            if (WAIT_FOR_LATCH_BRI == state) {
                state = tipoff_on_func();
            }
        }
    }
    else {
        /*
         * Standby is not active
         */

        // Check for a store request
        //  Do not allow store if the maximum pass count is exceeded.
        if ((lpsPtInputs.store_request_status) &&
                ((pcs_truck_get_pass_count() <= lpsPtInputs.maximum_pass_count))) {
            state = store_func(FALSE);
        }

        // Check for manual add request
        else if (lpsPtInputs.manual_add_request) {
            state = manual_add_func();
        }

        // Check for a reweigh request
        else if (lpsPtInputs.reweigh_request_status) {
            state = reweigh_func();
        }

        // Check for a bucket zero request
        else if (lpsPtInputs.zero_request_status) {
            state = zero_func();
        }

        // Check for the "minus one" or "remove last pass" request
        else if (lpsPtInputs.minus_one_request_status) {
            state = minus_one_func();
        }

        // Check for a clear truck request
        else if (lpsPtInputs.clear_request_status) {
            state = clear_func();
        }

        // Check for toggle tip-off mode request
        else if (lpsPtInputs.tipoff_toggle_request_status) {
            pcs_tip_off_toggle_mode();
        }

        // Check for standby request
        else if (lpsPtInputs.standby_request_status) {
            state = standby_func();
        }

        // Check for exit manual tip-off request
        else if (lpsPtInputs.change_mode_weigh) {
            state = tipoff_off_func();
        }

        // Check for enter manual tip-off request
        else if (lpsPtInputs.change_mode_excess) {
            state = tipoff_on_func();
        }
    }

    return state;
}

// We are above the weigh range and idle
static unsigned_32 wait_for_dump_ari_state(void)
{
    unsigned_32 state;

    if (LpsPtWrkTbl.lpsPtoutputs.standby_active)
    {
        if(lpsPtInputs.dump_state_is_partial_dump)
        {
            state = WAIT_FOR_LATCH_BRI;
            unlatch_current_bucket_weight();
        }

        else
        {
            pcs_bucket_capture_start_weight();
            state = WAIT_FOR_DUMP_ARI;
        }
    }
    /* Wait for Dump will transtion differently, based on Tipoff Triggers. See Manual Tipoff State Diagram */
    else if (lpsPtInputs.dump_state_is_partial_dump &&
            (TIP_OFF_TRIGGER_AUTO == lpsPtInputs.tip_off_trigger))
    {

        /* Bucket is partially dumped and trigger is Auto; go into tipoff. */
        pcs_bucket_capture_start_weight();
        LpsPtWrkTbl.disable_auto_tipoff_exit = FALSE;
        state = TIP_OFF_IRI;

        unlatch_current_bucket_weight();
    }
    else if (lpsPtInputs.dump_state_is_partial_dump &&
            ((TIP_OFF_TRIGGER_MANUAL == lpsPtInputs.tip_off_trigger) ||
                    (TIP_OFF_TRIGGER_DISABLED == lpsPtInputs.tip_off_trigger)))
    {

        /* Bucket is partially dumped and trigger is Manual or Disabled. Treat like a full dump. */
        unsigned_8 accuracy;
        float weight = pcs_bucket_get_start_weight(&accuracy);
        pcs_truck_update_pass(weight, accuracy);
        pcs_cycle_close(weight, accuracy);
        state = WAIT_FOR_LATCH_BRI;

        unlatch_current_bucket_weight();
    }
    else
    {
        unsigned_8 accuracy;
        float weight;
        pcs_bucket_capture_start_weight();
        weight = pcs_bucket_get_start_weight(&accuracy);
        pcs_truck_update_pass(weight, accuracy);
        state = WAIT_FOR_DUMP_ARI;
    }

    return(state);
}

// We are below the beginning of weigh (idle state)
// We can change out of this by rising into the weigh range
static unsigned_32 wait_for_latch_bri_state(void)
{
    unsigned_32 state;
    unsigned_8 accuracy;
    float weight = pcs_bucket_get_current_weight(&accuracy);

    /* TODO: (review needed) We are checking to see if we previously commanded to
     * unlatch the bucket weight,
     * if so, we should not be latched already again*/
    if ((lpsPtInputs.current_bucket_weight_latched) &&
            (!LpsPtWrkTbl.prev_unlatch_cmd) &&
            (accuracy >= LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED))
    {
        if (pcs_truck_get_pass_count() < lpsPtInputs.maximum_pass_count) {
            pcs_bucket_capture_start_weight();
            dump_detect_capture_cyl_ext_reference();

            if (!(LpsPtWrkTbl.lpsPtoutputs.standby_active))
            {
                // Automatically keep this pass if manual add is disabled.
                // Otherwise, require a manual add operation to keep the pass.
                boolean keepPass = lpsPtInputs.manual_add_enabled ? FALSE : TRUE;
                pcs_truck_start_pass(weight, accuracy, keepPass);
            }

            state = WAIT_FOR_DUMP_ARI;
        }
        else {
            // Stay here if we at the maximum pass count, we can't add any more.
            unlatch_current_bucket_weight();
            state = WAIT_FOR_LATCH_BRI;
        }
    }
    else
    {
        state = WAIT_FOR_LATCH_BRI;
    }

    return(state);
}

// We are in Tip Off Weigh Mode
static unsigned_32 tip_off_iri_state(void)
{
    unsigned_32 state;

    /* Determine Current Tip-Off Mode */
    if (LpsPtWrkTbl.lpsPtoutputs.standby_active)
    {
        /* It should not be possible to get here, but we have to do something */
        unlatch_current_bucket_weight();
        state = WAIT_FOR_LATCH_BRI;
    }
    else if ((lpsPtInputs.tip_off_trigger == TIP_OFF_TRIGGER_DISABLED) &&
            (!LpsPtWrkTbl.disable_auto_tipoff_exit))
    {
        /* Tip-off was disabled mid-tip-off, treat like dump */
        unsigned_8 accuracy;
        float weight = pcs_bucket_get_start_weight(&accuracy);
        pcs_cycle_close(weight, accuracy);
        unlatch_current_bucket_weight();
        state = WAIT_FOR_LATCH_BRI;
    }
    else
    {
        /* We are still in tip-off */

        boolean new_dig_detected = FALSE;

        // Has a new dig been detected?
        if (lpsPtInputs.dig_detected && !LpsPtWrkTbl.previous_dig_detected) {
            new_dig_detected = TRUE;
        }

        /*Tip Auto with Full Dump only will trigger the state machine to go to
              Wait for Latch*/
        if (lpsPtInputs.dump_state_is_full_dump &&
                (!LpsPtWrkTbl.disable_auto_tipoff_exit) &&
                (TIP_OFF_TRIGGER_AUTO == lpsPtInputs.tip_off_trigger))
        {
            unsigned_8 accuracy;
            float weight;

            if (TIP_OFF_MODE_TRUCK == LpsPtWrkTbl.lpsPtoutputs.tip_off_mode)
            {
                weight = pcs_bucket_get_start_weight(&accuracy);
            }
            else /* TIP_OFF_MODE_PILE */
            {
                weight = pcs_bucket_get_split_weight(&accuracy);
            }

            pcs_cycle_close(weight, accuracy);
            unlatch_current_bucket_weight();
            state = WAIT_FOR_LATCH_BRI;
        }
        else if (new_dig_detected &&
                (!LpsPtWrkTbl.disable_auto_tipoff_exit) &&
                (TIP_OFF_TRIGGER_AUTO == lpsPtInputs.tip_off_trigger))
        {
            unsigned_8 accuracy;
            float weight = pcs_bucket_get_start_weight(&accuracy);
            pcs_cycle_close(weight, accuracy);
            unlatch_current_bucket_weight();
            state = WAIT_FOR_LATCH_BRI;
        }
        else if (lpsPtInputs.dump_state_is_partial_dump)
        {
            unsigned_8 currentAccuracy;
            float currentWeight = pcs_bucket_get_current_weight(&currentAccuracy);
            if (currentAccuracy > LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE)
            {
                unsigned_8 accuracy;
                float weightToTruck;

                if (TIP_OFF_MODE_TRUCK == LpsPtWrkTbl.lpsPtoutputs.tip_off_mode)
                {
                    unsigned_8 startAccuracy;
                    weightToTruck = pcs_bucket_get_start_weight(&startAccuracy) - currentWeight;
                    accuracy = ((currentAccuracy <= startAccuracy) ? currentAccuracy : startAccuracy);
                }
                else /* TIP_OFF_MODE_PILE */
                {
                    weightToTruck = currentWeight;
                    accuracy = currentAccuracy;
                }

                pcs_truck_update_pass(weightToTruck, accuracy);
            }

            unlatch_current_bucket_weight();
            state = TIP_OFF_IRI;
        }
        else /* Racked */
        {
            unsigned_8 currentAccuracy;
            pcs_bucket_get_current_weight(&currentAccuracy);
            if (currentAccuracy > LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE)
            {
                unsigned_8 accuracy;
                float weightToTruck;

                pcs_bucket_capture_split_weight();

                if (TIP_OFF_MODE_TRUCK == LpsPtWrkTbl.lpsPtoutputs.tip_off_mode)
                {
                    unsigned_8 startAccuracy;
                    unsigned_8 splitAccuracy;

                    weightToTruck = pcs_bucket_get_start_weight(&startAccuracy) - pcs_bucket_get_split_weight(&splitAccuracy);

                    accuracy = ((splitAccuracy <= startAccuracy) ? splitAccuracy : startAccuracy);
                }
                else /* TIP_OFF_MODE_PILE */
                {
                    weightToTruck = pcs_bucket_get_split_weight(&accuracy);
                }

                pcs_truck_update_pass(weightToTruck, accuracy);
            }

            state = TIP_OFF_IRI;
        }
    }

    return state;
}

static void pcs_cycle_close(float weight, unsigned_8 accuracy) {
    if (pcs_truck_complete_pass(weight, accuracy)) {
        unsigned_8 passAccuracy;
        LpsPtWrkTbl.lpsPtoutputs.loadUpdate.addPass = TRUE;
        LpsPtWrkTbl.lpsPtoutputs.loadUpdate.addPassWeight = pcs_truck_get_current_pass_weight(&passAccuracy);
        LpsPtWrkTbl.lpsPtoutputs.loadUpdate.addPassAccuracy = passAccuracy;
    }

    // If we have hit max pass counts, and are not currently auto storing, force one
    // only do this if auto store is enabled (> 0)
    if ((lpsPtInputs.auto_store_enabled > 0) &&
            (pcs_truck_get_pass_count() >= lpsPtInputs.maximum_pass_count)) {
        store_func(TRUE);
    }
}


static void pcs_tip_off_toggle_mode(void) {
    // Only allow toggling the tipoff mode if we are in tipoff
    if (TIP_OFF_IRI == LpsPtWrkTbl.lpsPtoutputs.pt_current_state) {
        /* switch truck/pile mode to the other mode */
        if (TIP_OFF_MODE_TRUCK == LpsPtWrkTbl.lpsPtoutputs.tip_off_mode) {
            LpsPtWrkTbl.lpsPtoutputs.tip_off_mode = TIP_OFF_MODE_PILE;
        }
        else {
            LpsPtWrkTbl.lpsPtoutputs.tip_off_mode = TIP_OFF_MODE_TRUCK;
        }
    }
}

static void pcs_tip_off_reset_toggle(void) {
    LpsPtWrkTbl.lpsPtoutputs.tip_off_mode = LpsPtWrkTbl.lpsPtoutputs.configured_tip_off_mode;
}

void reset_output_data(void)
{
    /* reset one-time output flags */
    memset(&LpsPtWrkTbl.lpsPtoutputs.loadUpdate, 0, sizeof(LpsPtWrkTbl.lpsPtoutputs.loadUpdate));
    LpsPtWrkTbl.lpsPtoutputs.unlatch_current_bucket_weight = FALSE;
    LpsPtWrkTbl.lpsPtoutputs.clear_reweigh_warning_status = FALSE;
    LpsPtWrkTbl.lpsPtoutputs.dump_detect_capture_cyl_ext_reference = FALSE;
    LpsPtWrkTbl.lpsPtoutputs.display_bucket_weight_available = FALSE;
}

static void pcs_display_wt_update(void)
{
    unsigned_8 accuracy;
    float weight = pcs_bucket_get_current_weight(&accuracy);
    LpsPtWrkTbl.lpsPtoutputs.display_bucket_weight = weight;
    LpsPtWrkTbl.lpsPtoutputs.display_bucket_weight_accuracy = accuracy;

    if (WAIT_FOR_LATCH_BRI == LpsPtWrkTbl.lpsPtoutputs.pt_current_state) {
        LpsPtWrkTbl.lpsPtoutputs.display_bucket_weight_available = FALSE;
    }
    else if ((accuracy <= LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_LOW) && (TRUE == lpsPtInputs.lift_stalled)) {
        LpsPtWrkTbl.lpsPtoutputs.display_bucket_weight_available = FALSE;
    }
    else if (LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE == accuracy) {
        LpsPtWrkTbl.lpsPtoutputs.display_bucket_weight_available = FALSE;
    }
    else {
        LpsPtWrkTbl.lpsPtoutputs.display_bucket_weight_available = TRUE;
    }
}

static void unlatch_current_bucket_weight()
{
    LpsPtWrkTbl.lpsPtoutputs.unlatch_current_bucket_weight = TRUE;

    /* wait for bucket weight to be latched after the weighing app processes the
     * unlatch cmd
     */
    lpsPtInputs.current_bucket_weight_latched = FALSE;

    return;
}

static void dump_detect_capture_cyl_ext_reference(void) {
    // We are going to recapture the dump detection cylinder extension reference
    // and, until it is handled, we will assume we are not partial or full dump.
    LpsPtWrkTbl.lpsPtoutputs.dump_detect_capture_cyl_ext_reference = TRUE;
    lpsPtInputs.dump_state_is_partial_dump = FALSE;
    lpsPtInputs.dump_state_is_full_dump = FALSE;
}
