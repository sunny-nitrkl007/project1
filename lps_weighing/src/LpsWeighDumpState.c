/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:LpsWeighDumpState.c
DESCRIPTION: Used to find out the state of the bucket at that point, can be one of the following:

 LPS_WEIGHT_BKT_DUMP_STATE_UNKNOWN,
 LPS_WEIGHT_BKT_FULLY_RACKED,
 LPS_WEIGHT_BKT_NOT_RACKED_AND_NOT_DUMPED,
 LPS_WEIGHT_BKT_PARTIALLY_DUMPED,
 LPS_WEIGHT_BKT_FULLY_DUMPED

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

#ifndef __LPS_PUBLIC_H__
#include <LpsPublic.h> /*******************************************************/ 
                       /* Contains prototypes of interfaces and functions    */
                       /* which are exported to the application using the     */
                       /* library                                             */
                       /*******************************************************/
#endif

#include "LpsPrivate.h" /*******************************************************/ 
                        /* Contains prototypes of interfaces and functions    */
                        /* which are used within the payload computation       */
                        /* library                                             */
                        /*******************************************************/
/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
float_32 NewTiltExtThreshold = 0.0;
boolean ReferenceCaptured = FALSE;
unsigned_32 PrevPassCount = 0;

void LpsWeighDumpDetectInit(void)
{
    NewTiltExtThreshold = 0.0;
    ReferenceCaptured = FALSE;
    LpsWrk.DumpStateStatus = LPS_WEIGHT_BKT_DUMP_STATE_UNKNOWN;
}

LpsWeighBktDumpStat_t LpsWeighGetDumpState(void)
{
    return LpsWrk.DumpStateStatus;
}

void LpsWeighSetTiltExtensionThreshold()
{
    LpsUpdtTbl_t* updtTbl = LpsWrk.UpdtTbl;

    if ((LPS_STATUS_OK == updtTbl->BktAngle.Stat) &&
            (LPS_STATUS_OK == updtTbl->TiltCylLengthNorm.Stat)) {
        /* % cylinder movement for dumping */
        float_32 newThreshold = updtTbl->TiltCylLengthNorm.Val - (float_32)LPS_TILT_CYL_EXT_DUMP_DELTA;

        if (newThreshold > LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold) {
            NewTiltExtThreshold = LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold;
        }
        else if(newThreshold < LPS_TILT_EXT_FULL_DUMP_LIMIT) {
            NewTiltExtThreshold = LPS_TILT_EXT_FULL_DUMP_LIMIT;
        }
        else {
            NewTiltExtThreshold = newThreshold;
        }

        ReferenceCaptured = TRUE;
    }
    else {
        NewTiltExtThreshold = LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold;
        ReferenceCaptured = FALSE;
    }
}

/*    This function is used to check if the bucket is fully racked or not
    Returns TRUE if the bucket is FULLY racked, and    FALSE otherwise */
boolean LpsWeighFullRackDetect()
{
    LpsUpdtTbl_t* updtTbl = LpsWrk.UpdtTbl;

    if ((LPS_STATUS_OK == updtTbl->BktAngle.Stat) &&
            (LPS_STATUS_OK == updtTbl->TiltCylLengthNorm.Stat) &&
            (LPS_STATUS_OK == updtTbl->TiltAngleABCPercent.Stat)) {
        /* Full Rack
                                   (BucketAngle > PartialDumpBktAngle)
                                             ---- OR ----
                    (((Cylinder% > X) || (ABC% > Y)) && (BucketAngle > FullRackBktAngle))
        */
        if (updtTbl->BktAngle.Val > LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.PartDumpBktAngleThreshold) {
            return TRUE;
        }
        else if (((updtTbl->TiltCylLengthNorm.Val > LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold) ||
                (updtTbl->TiltAngleABCPercent.Val > LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltAngleABCThreshold)) &&
                (updtTbl->BktAngle.Val > LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.FullRackBktAngleThreshold)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        return FALSE;
    }
}

boolean LpsWeighFullRackDetectStrict()
{
    LpsUpdtTbl_t* updtTbl = LpsWrk.UpdtTbl;

    if (NULL == updtTbl) {
        return TRUE;
    }

    if (!LpsWeighFullRackDetect()) {
        return FALSE;
    }
    else if (updtTbl->LegalForTradeInstalled) {
        /* Legal for Trade has a more strict definition of fully racked. */
        if (LPS_STATUS_OK == updtTbl->TiltCylLengthNorm.Stat) {
            if ((updtTbl->TiltCylLengthNorm.Val > LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThresholdStrict) &&
                    (updtTbl->TiltCylLengthNorm.Val > LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold)) {
                return TRUE;
            }
            else {
                return FALSE;
            }
        }
        else {
            return FALSE;
        }
    }
    else {
        return TRUE;
    }

}

/*    This function is used to check if the bucket is fully dumped or not
    Returns TRUE if the bucket is FULLY dumped, and    FALSE otherwise */
boolean LpsWeighFullDumpDetect(void)
{
    LpsUpdtTbl_t* updtTbl = LpsWrk.UpdtTbl;
    float_32 tiltCylThreshold;

    if (ReferenceCaptured) {
        tiltCylThreshold = NewTiltExtThreshold;
    }
    else {
        tiltCylThreshold = LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold;
    }

    if ((LPS_STATUS_OK == updtTbl->BktAngle.Stat) &&
            (LPS_STATUS_OK == updtTbl->TiltCylLengthNorm.Stat) &&
            (LPS_STATUS_OK == updtTbl->TiltAngleABCPercent.Stat)) {
        if ((updtTbl->TiltCylLengthNorm.Val <= tiltCylThreshold) &&
                (updtTbl->TiltAngleABCPercent.Val <= LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltAngleABCThreshold) &&
                (updtTbl->BktAngle.Val <= LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.FullDumpBktAngleThreshold)) {
            return TRUE;
        }
        else if ((updtTbl->TiltCylLengthNorm.Val <= LPS_TILT_EXT_FULL_DUMP_LIMIT) ||
                (updtTbl->TiltAngleABCPercent.Val <= PCS_TILT_ANG_ABC_PCT_FULL_DUMP_LIMIT)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        return FALSE;
    }
}

/*    This function is used to check if the bucket is partially dumped or not
    Returns TRUE if the bucket is PARTIALLY dumped, and    FALSE otherwise */
boolean LpsWeighPartialDumpDetect(void)
{
    float_32 tiltCylThreshold;
    LpsUpdtTbl_t* updtTbl = LpsWrk.UpdtTbl;

    if (ReferenceCaptured) {
        tiltCylThreshold = NewTiltExtThreshold;
    }
    else {
        tiltCylThreshold = LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold;
    }

    if ((LPS_STATUS_OK == updtTbl->BktAngle.Stat) &&
            (LPS_STATUS_OK == updtTbl->TiltCylLengthNorm.Stat) &&
            (LPS_STATUS_OK == updtTbl->TiltAngleABCPercent.Stat)) {
        if ((updtTbl->BktAngle.Val <= LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.PartDumpBktAngleThreshold) &&
                (updtTbl->TiltAngleABCPercent.Val <= LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltAngleABCThreshold) &&
                (updtTbl->TiltCylLengthNorm.Val <= tiltCylThreshold)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        return FALSE;
    }
}

void LpsWeighDumpDetectUpdate()
{
    LpsWeighBktDumpStat_t dumpState;
    LpsUpdtTbl_t* updtTbl = LpsWrk.UpdtTbl;

    if ((LPS_STATUS_OK == updtTbl->BktAngle.Stat) &&
            (LPS_STATUS_OK == updtTbl->TiltCylLengthNorm.Stat)) {
        /*
         * This check is to make sure that the bucket has transitioned from Wait for Latch
         * to Wait for Dump. Since PassCount is incremented at the exact time where the transition
         * of states happen, it is enough if we check if the PassCount has incremented over each loop.
         */
        if (updtTbl->PassCount > PrevPassCount) {
            LpsWeighSetTiltExtensionThreshold();
            PrevPassCount = updtTbl->PassCount;
        }

        if (ReferenceCaptured) {
            if ((updtTbl->TiltCylLengthNorm.Val - LPS_TILT_CYL_EXT_DUMP_DELTA) > NewTiltExtThreshold) {
                LpsWeighSetTiltExtensionThreshold();
            }
        }

        if (LpsWeighFullRackDetect()) {
            dumpState = LPS_WEIGHT_BKT_FULLY_RACKED;
        }
        else if (LpsWeighFullDumpDetect()) {
            dumpState = LPS_WEIGHT_BKT_FULLY_DUMPED;

            NewTiltExtThreshold = LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold;
            ReferenceCaptured = FALSE;
        }
        else if (LpsWeighPartialDumpDetect()) {
            dumpState = LPS_WEIGHT_BKT_PARTIALLY_DUMPED;

            NewTiltExtThreshold = LpsWrk.InitTbl.MachSpecificCfg.DumpConfig.TiltCylExtThreshold;
            ReferenceCaptured = FALSE;
        }
        else {
            dumpState = LPS_WEIGHT_BKT_NOT_RACKED_AND_NOT_DUMPED;
        }
    }
    else {
        dumpState = LPS_WEIGHT_BKT_DUMP_STATE_UNKNOWN;
    }

    LpsWrk.DumpStateStatus = dumpState;
}
