#include <LpsCommonTypeDef.h>
#include <LpsCommonStructures.h>

#include "LpsPtPrivate.h"

#define PCS_TRUCK_DISPLAY_PAUSE_TIME (3.0)
//TODO remove from here
static float  time_step = 100.0/1000.0; /*seconds*/

typedef struct {

    boolean passActive;

    // There are two ways to handle "Keep Pass"
    // - Don't update the current pass until keep pass is TRUE (NOT USED)
    // - Update the current pass, but remove it when the pass is completed unless keep pass is TRUE
    boolean keepPass;
    float startWeight;
    unsigned_16 passCount;
    float weight;
    unsigned_8 currentPassAccuracy;

    boolean haveLastPass;
    float lastPassWeight;
    unsigned_8 lastPassAccuracy;

    boolean haveRecallPass;
    float recallPassWeight;
    unsigned_8 recallPassAccuracy;

    struct {
        boolean pauseOnClear;
        unsigned_16 pauseTimer;
        unsigned_16 passCount;
        float weight;
    } display;
    
} pcs_truck_t;

static pcs_truck_t pcs_truck_data = {0};

static void pcs_truck_display_refresh(void);

void pcs_truck_display_pause_on_clear(void) {
    pcs_truck_data.display.pauseOnClear = TRUE;
}

static void pcs_truck_display_refresh(void) {
    pcs_truck_data.display.passCount = pcs_truck_data.passCount;
    pcs_truck_data.display.weight = pcs_truck_data.weight;
    pcs_truck_data.display.pauseOnClear = FALSE;
    pcs_truck_data.display.pauseTimer = 0;
}

void pcs_truck_clear(void) {
    // Called on CLEAR and STORE
    pcs_truck_data.passActive = FALSE;
    pcs_truck_data.keepPass = FALSE;
    pcs_truck_data.passCount = 0;
    pcs_truck_data.weight = 0.0;
    pcs_truck_data.startWeight = 0.0;
    pcs_truck_data.currentPassAccuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;

    pcs_truck_data.haveLastPass = FALSE;
    pcs_truck_data.lastPassWeight = 0.f;
    pcs_truck_data.lastPassAccuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;

    pcs_truck_data.haveRecallPass = FALSE;
    pcs_truck_data.recallPassWeight = 0.f;
    pcs_truck_data.recallPassAccuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;

    if (pcs_truck_data.display.pauseOnClear) {
        pcs_truck_data.display.pauseTimer = (unsigned_16)(((float)PCS_TRUCK_DISPLAY_PAUSE_TIME) / time_step);
        pcs_truck_data.display.pauseOnClear = FALSE;
    }
    else {
        pcs_truck_display_refresh();
    }
}

void pcs_truck_keep_pass() {
    pcs_truck_data.keepPass = TRUE;
}

void pcs_truck_start_pass(float passWeight, unsigned_8 passAccuracy, boolean keepPass) {
    pcs_truck_data.keepPass = keepPass;
    if (pcs_truck_data.passActive) {
        pcs_truck_update_pass(passWeight, passAccuracy);
    }
    else {
        pcs_truck_data.passActive = TRUE;
        pcs_truck_data.startWeight = pcs_truck_data.weight;
        pcs_truck_data.passCount++;
        if (passWeight > 0) {
            pcs_truck_data.weight += passWeight;
        }
        pcs_truck_data.currentPassAccuracy = passAccuracy;
        pcs_truck_display_refresh();
    }

    // We just started a new pass, we can no longer recall the previously cancelled pass
    pcs_truck_data.haveRecallPass = FALSE;
    pcs_truck_data.recallPassWeight = 0.f;
    pcs_truck_data.recallPassAccuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;
}

/*
 * Called when the pass is complete (cycle closed)
 * Returns:
 *  TRUE - When the pass is kept
 *  FALSE - When the pass is thrown out
 */
boolean pcs_truck_complete_pass(float passWeight, unsigned_8 passAccuracy) {
    boolean passKept;

    if (pcs_truck_data.passActive) {
        // Update the pass with the given weight
        pcs_truck_update_pass(passWeight, passAccuracy);

        if (pcs_truck_data.keepPass) {
            // Keep the pass, but reset the keep pass flag
            unsigned_8 lastPassAccuracy;
            pcs_truck_data.haveLastPass = TRUE;
            pcs_truck_data.lastPassWeight = pcs_truck_get_current_pass_weight(&lastPassAccuracy);
            pcs_truck_data.lastPassAccuracy = lastPassAccuracy;

            pcs_truck_data.keepPass = FALSE;

            passKept = TRUE;
        }
        else {
            // Before we throw away this pass, remember what it is so that we can recall it.
            unsigned_8 recallPassAccuracy;
            pcs_truck_data.haveRecallPass = TRUE;
            pcs_truck_data.recallPassWeight = pcs_truck_get_current_pass_weight(&recallPassAccuracy);
            pcs_truck_data.recallPassAccuracy = recallPassAccuracy;

            // Throw away the pass, we didn't want to keep it
            pcs_truck_cancel_pass();
            passKept = FALSE;
        }

        pcs_truck_data.passActive = FALSE;
    }
    else {
        passKept = FALSE;
    }

    return passKept;
}

boolean pcs_truck_recall_pass(void) {
    boolean passRecalled;

    if (!pcs_truck_data.passActive && pcs_truck_data.haveRecallPass) {
        // Update the truck information
        pcs_truck_data.startWeight = pcs_truck_data.weight;
        pcs_truck_data.passCount++;
        if (pcs_truck_data.recallPassWeight > 0) {
            pcs_truck_data.weight += pcs_truck_data.recallPassWeight;
        }
        pcs_truck_data.currentPassAccuracy = pcs_truck_data.recallPassAccuracy;

        // Set last weight and clear out recall weight
        pcs_truck_data.haveLastPass = TRUE;
        pcs_truck_data.lastPassWeight = pcs_truck_data.recallPassWeight;
        pcs_truck_data.lastPassAccuracy = pcs_truck_data.recallPassAccuracy;

        pcs_truck_data.haveRecallPass = FALSE;
        pcs_truck_data.recallPassWeight = 0.f;
        pcs_truck_data.recallPassAccuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;

        pcs_truck_display_refresh();
        passRecalled = TRUE;
    }
    else {
        passRecalled = FALSE;
    }

    return passRecalled;
}

void pcs_truck_cancel_pass(void) {
    pcs_truck_data.keepPass = FALSE;
    if (pcs_truck_data.passActive) {
        if (pcs_truck_data.passCount > 1) {
            pcs_truck_data.passCount--;
            pcs_truck_data.weight = pcs_truck_data.startWeight;
        }
        else {
            pcs_truck_data.passCount = 0;
            pcs_truck_data.weight = 0.0;
            pcs_truck_data.startWeight = 0.0;
        }
        pcs_truck_data.currentPassAccuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;
        pcs_truck_display_refresh();

        pcs_truck_data.passActive = FALSE;
    }
}

boolean pcs_truck_remove_last_pass() {
    boolean passRemoved;

    // First, cancel the pass, if it is active
    pcs_truck_cancel_pass();

    // Then, if we have a last pass, remove it.
    if (pcs_truck_data.haveLastPass) {
        if (pcs_truck_data.passCount > 1) {
            pcs_truck_data.passCount--;
            if (pcs_truck_data.lastPassWeight > 0.f) {
                pcs_truck_data.weight -= pcs_truck_data.lastPassWeight;
            }
            pcs_truck_data.startWeight = pcs_truck_data.weight;
        }
        else {
            pcs_truck_data.passCount = 0;
            pcs_truck_data.weight = 0.0;
            pcs_truck_data.startWeight = 0.0;
        }

        // Here we can have the ability to recall the weight just removed
        pcs_truck_data.haveRecallPass = TRUE;
        pcs_truck_data.recallPassWeight = pcs_truck_data.lastPassWeight;
        pcs_truck_data.recallPassAccuracy = pcs_truck_data.lastPassAccuracy;

        pcs_truck_data.haveLastPass = FALSE;
        pcs_truck_data.lastPassWeight = 0.f;
        pcs_truck_data.lastPassAccuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;

        pcs_truck_data.currentPassAccuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;
        pcs_truck_display_refresh();

        passRemoved = TRUE;
    }
    else {
        passRemoved = FALSE;
    }

    return passRemoved;
}

void pcs_truck_update_pass(float passWeight, unsigned_8 passAccuracy) {
    if (pcs_truck_data.passActive) {
        if (passWeight > 0) {
            pcs_truck_data.weight = pcs_truck_data.startWeight + passWeight;
        }
        else {
            pcs_truck_data.weight = pcs_truck_data.startWeight;
        }
        pcs_truck_data.currentPassAccuracy = passAccuracy;
        pcs_truck_display_refresh();
    }
}

float pcs_truck_get_current_pass_weight(unsigned_8* accuracy) {
    if (NULL != accuracy) {
        *accuracy = pcs_truck_data.currentPassAccuracy;
    }
    return pcs_truck_data.weight - pcs_truck_data.startWeight;
}

void pcs_truck_init(float initialWeight, unsigned_16 initialPassCount, boolean haveLastPass, float lastPassWeight, unsigned_8 lastPassAccuracy) {
    pcs_truck_data.passActive = FALSE;
    pcs_truck_data.keepPass = FALSE;
    pcs_truck_data.currentPassAccuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;

    pcs_truck_data.haveRecallPass = FALSE;
    pcs_truck_data.recallPassWeight = 0.f;
    pcs_truck_data.recallPassAccuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;

    pcs_truck_restore(initialWeight, initialPassCount, haveLastPass, lastPassWeight, lastPassAccuracy);
}

void pcs_truck_restore(float initialWeight, unsigned_16 initialPassCount, boolean haveLastPass, float lastPassWeight, unsigned_8 lastPassAccuracy) {
    if (pcs_truck_data.passActive) {
        pcs_truck_data.weight = initialWeight + pcs_truck_get_current_pass_weight(NULL);
        pcs_truck_data.passCount = initialPassCount + 1;
    }
    else {
        pcs_truck_data.weight = initialWeight;
        pcs_truck_data.passCount = initialPassCount;
    }

    pcs_truck_data.startWeight = initialWeight;

    if (initialPassCount > 0) {
        pcs_truck_data.haveLastPass = haveLastPass;
        pcs_truck_data.lastPassWeight = lastPassWeight;
        pcs_truck_data.lastPassAccuracy = lastPassAccuracy;
    }
    else {
        pcs_truck_data.haveLastPass = FALSE;
        pcs_truck_data.lastPassWeight = 0.f;
        pcs_truck_data.lastPassAccuracy = LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE;
    }

    pcs_truck_display_refresh();
}

void pcs_truck_display_update(void) {
    if (pcs_truck_data.display.pauseTimer > 0) {
        pcs_truck_data.display.pauseTimer--;
    }
    else {
        pcs_truck_display_refresh();
    }
}

boolean pcs_truck_has_passes(void) {
	boolean hasPasses;
    if (pcs_truck_data.passCount > 0) {
        hasPasses = TRUE;
    }
    else {
        hasPasses = FALSE;
    }
    return hasPasses;
}

boolean pcs_truck_is_pass_active(void) {
    return pcs_truck_data.passActive;
}

boolean pcs_truck_is_keeping_pass(void) {
    return pcs_truck_data.keepPass;
}

boolean pcs_truck_has_recall_pass(void) {
    return pcs_truck_data.haveRecallPass;
}

boolean pcs_truck_has_last_pass(void) {
    return pcs_truck_data.haveLastPass;
}

unsigned_16 pcs_truck_get_pass_count(void) {
    return pcs_truck_data.passCount;
}

float pcs_truck_get_weight(void) {
    return pcs_truck_data.weight;
}

float pcs_truck_get_start_weight(void) {
    if (pcs_truck_data.passActive) {
        /*
         * If the pass is active, then the start weight for the pass has been
         * captured and we can return it.
         */
        return pcs_truck_data.startWeight;
    }
    else {
        /*
         * If the pass is not active, then the start weight is just the current
         * truck weight.
         */
        return pcs_truck_data.weight;
    }
}

unsigned_16 pcs_truck_display_get_pass_count(void) {
    return pcs_truck_data.display.passCount;
}

float pcs_truck_display_get_weight(void) {
    return pcs_truck_data.display.weight;
}
