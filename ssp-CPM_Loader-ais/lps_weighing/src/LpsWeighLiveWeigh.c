/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:LpsWeighLiveWeigh
DESCRIPTION: Calculates the live weight
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef __LPS_COMMON_TYPE_DEF_H__
#include <LpsCommonTypeDef.h> /* Contains type definitions of standard datatypes */
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h> /* Contains structures which are common between all LPS
                                  * system libraries
                  */
#endif

#ifndef  __LPS_COMMON_LOOKUP_TBL_UTILITY_H__
#include <LpsCommonLookUpTblUtility.h>
#endif

#ifndef __LPS_PUBLIC_H__
#include <LpsPublic.h> /*******************************************************/ 
                       /* Containes prototypes of interfaces and functions    */
                       /* which are exported to the application using the     */
                       /* library                                             */
                       /*******************************************************/
#endif

#include "LpsPrivate.h"

#ifndef __CPM_FILTER_H__
#include <cpm_filter.h> /* Contains the functions from CPM Filter library of MAAL */
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
/******************************************************************************
FUNCTION NAME:LpsLiveWeighInit
DESCRIPTION: Initializes the filter parameters used for Live Weigh calculation
PARAMETER DESCRIPTION: None
RETURN VALUE: None
*******************************************************************************/
void LpsLiveWeighInit()
{
    LpsInitTbl_t* pInitTbl = &LpsWrk.InitTbl;
    LpsWeighLiveWtCfg_t* pLiveWtCfg = &LpsWrk.InitTbl.MachSpecificCfg.LiveWeighConfig;
    LpsWeighLiveWeigh_t* pLiveWtTbl = &LpsWrk.LiveWeighTbl;

    cpm_filter_low_pass_filter_init(&pLiveWtTbl->SlowFilter, pLiveWtCfg->SlowFiltWtCf, pInitTbl->ExecRate);
    cpm_filter_low_pass_filter_init(&pLiveWtTbl->FastFilter, pLiveWtCfg->FastFiltWtCf, pInitTbl->ExecRate);

    pLiveWtTbl->UseFastFilter = TRUE;

    LpsWeighResetLiveWt();
}


/******************************************************************************
FUNCTION NAME:LpsLiveWeighCalc
DESCRIPTION: Band stop filtered weights are taken as input to this function. Then 
             it is passed through fast/slow low pass filters and then cal adjusted
             after doing the zero weight adjustment.
PARAMETER DESCRIPTION:None
RETURN VALUE: None
*******************************************************************************/
void LpsLiveWeighCalc(void)
{
    LpsWeighLiveWeigh_t* pLiveWtTbl = &LpsWrk.LiveWeighTbl;
    LpsStat_t rawStatus = LpsWrk.InputStatus.rawStatus;
    LpsStat_t debouncedStatus = LpsWrk.InputStatus.debouncedStatus;

    if (LPS_WEIGH_SYSTEM_UNCALIBRATED == LpsGetCalibStatus()) {
        rawStatus = LPS_STATUS_BAD;
        debouncedStatus = LPS_STATUS_BAD;
    }

    if (LPS_STATUS_OK == rawStatus) {
        float_32 estWt;

        /*
         * Bandstop filtering is done in LLW calculation to filter the pressure to
         * remove resonant frequencies caused by machine and tire mass resonance
         */
        {
            /* Handle the filtering of instantaneous weight estimate */
            static const float filter_threshold = 555.55; /* 2 kph in mm/s */
            float abs_ground_speed = LpsWrk.UpdtTbl->GroundSpeed;

            /* Update the fast filter */
            cpm_filter_low_pass_filter(&pLiveWtTbl->FastFilter, LpsWrk.InstWtLlwFilt);

            /* Take absolute value of ground speed */
            if (abs_ground_speed < 0) {
                abs_ground_speed *= (float)-1.0;
            }

            /* Determine which filter to use dependent upon ground speed */
            if (abs_ground_speed <= filter_threshold) {
                /* Use fast filter */
                pLiveWtTbl->UseFastFilter = TRUE;
            }
            else if (pLiveWtTbl->UseFastFilter) {
                /* We were using the fast filter, but are now using the slow filter
                              Reset the slow filter to pick up where fast filter left off.
                 */
                cpm_filter_low_pass_filter_reset(&pLiveWtTbl->SlowFilter, pLiveWtTbl->FastFilter.ystate);
                pLiveWtTbl->UseFastFilter = FALSE;
            }

            /* Update the slow filter */
            cpm_filter_low_pass_filter(&pLiveWtTbl->SlowFilter, LpsWrk.InstWtLlwFilt);

            /* Pick which filter output to use */
            if (pLiveWtTbl->UseFastFilter) {
                estWt = pLiveWtTbl->FastFilter.ystate;
            }
            else {
                estWt = pLiveWtTbl->SlowFilter.ystate;
            }
        }

        /* Apply zero and cal adjust, negative weights are possible */
        pLiveWtTbl->Wt = LpsZeroSpanAdjust(LpsAdvCalAdjust(estWt));
    
        if (LPS_STATUS_OK == debouncedStatus) {
            pLiveWtTbl->Stat = LPS_WEIGH_LIVE_WEIGH_STATUS_VALID;
        }
        else {
            pLiveWtTbl->Stat = LPS_WEIGH_LIVE_WEIGH_STATUS_INVALID;
        }
    }
    else if (LPS_STATUS_BAD == debouncedStatus) {
        cpm_filter_low_pass_filter_reset(&pLiveWtTbl->SlowFilter, 0);
        pLiveWtTbl->SlowFilter.init = FALSE;
        cpm_filter_low_pass_filter_reset(&pLiveWtTbl->FastFilter, 0);
        pLiveWtTbl->FastFilter.init = FALSE;
        pLiveWtTbl->UseFastFilter = TRUE;
        LpsWeighResetLiveWt();
    }
}

/******************************************************************************
FUNCTION NAME:LpsWeighResetLiveWt
DESCRIPTION: Reset the live weigh data to unlatch the current weight
PARAMETER DESCRIPTION: None
RETURN VALUE: None
*******************************************************************************/
void LpsWeighResetLiveWt(void)
{
    LpsWrk.LiveWeighTbl.Wt = 0.0;
    LpsWrk.LiveWeighTbl.Stat = LPS_WEIGH_LIVE_WEIGH_STATUS_INVALID;
}
