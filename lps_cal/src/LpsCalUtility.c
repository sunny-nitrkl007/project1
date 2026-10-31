/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:
DESCRIPTION:
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef __LPS_COMMON_TYPE_DEF_H__
#include <LpsCommonTypeDef.h>
#endif

#ifndef CAL_MGR_H_
#include <cal_mgr.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCalAppPublic.h>
#endif

#ifndef CAL_STRUCT_H_
#include <cal_struct.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h>
#endif

#ifndef __LPS_COMMON_LOOKUP_TBL_UTILITY__
#include <LpsCommonLookUpTblUtility.h>
#endif

#ifndef __LPS_CAL_PUBLIC_H__
#include <LpsCalPublic.h>
#endif

#ifndef __LPS_CAL_PRIVATE_H__
#include "LpsCalPrivate.h"
#endif

#include <string.h>
#include <stdio.h> // For LpsCalPrint()
#include <time.h> // For LpsCalPrint()

#include <std_types.h> // TRUE and FALSE

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#define PRINT_TO_STD 1 /* Print to standard output in LpsCalDebugPrint()? True/False */

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

/******************************************************************************
FUNCTION NAME: LpsCalCopyCfgToWrkTbl
DESCRIPTION: Function copies config table to cal lib local config table.
PARAMETER DESCRIPTION:
RETURN VALUE:void
*******************************************************************************/
void LpsCalCopyCfgToWrkTbl(const LpsCalCfg_t* pCalCfg)
{
    LpsCalWrkTbl.Cfg = *pCalCfg;
}

/******************************************************************************
FUNCTION NAME: LpsCalCopyNvmToWrkTbl
DESCRIPTION:  Function copies nvm table to cal lib local nvm table.
PARAMETER DESCRIPTION:
RETURN VALUE: void
*******************************************************************************/
void LpsCalCopyNvmToWrkTbl(const LpsCalNvmTbl_t* pCalNvmTbl)
{
    LpsCalWrkTbl.Nvm = *pCalNvmTbl;
}

/******************************************************************************
FUNCTION NAME: LpsCalCopyUpdateToWrkTbl
DESCRIPTION: Function copies update table to cal lib local update table.
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalCopyUpdateToWrkTbl(const LpsCalUpdate_t* pLpsCalUpdate)
{
    LpsCalWrkTbl.Update = *pLpsCalUpdate;
}

/******************************************************************************
FUNCTION NAME: LpsCalResetWrkTbl
DESCRIPTION: Resets calibration work table.
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalResetWrkTbl(void)
{
	memset(&LpsCalWrkTbl, 0, sizeof(LpsCalWrkTbl_t));
}

/******************************************************************************
FUNCTION NAME: LpsCalResetCurveFitInfo
DESCRIPTION: Resets calibration work table.
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalResetCurveFitInfo(void)
{
	memset(&LpsCalWrkTbl.CurveFitInfo, 0, sizeof(LpsCalCurveFitInfo_t));
}

/******************************************************************************
FUNCTION NAME: LpsCalSetWrkTblDefaults
DESCRIPTION: Function set calibration library defaults.
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
LpsCalInitErrorTypes_t LpsCalSetWrkTblDefaults(void)
{
	LpsCalOv_t *pCalov = &LpsCalWrkTbl.Ov;
	LpsCalCfg_t *pCalCfg = &LpsCalWrkTbl.Cfg;
	LpsCalInfo_t *pCalInfo = &LpsCalWrkTbl.Info;
	LpsCalNvmTbl_t *pCalNvm = &LpsCalWrkTbl.Nvm;
	LpsCalStatus_t *pCalStatus = &LpsCalWrkTbl.Status;

	LpsCalWrkTbl.InitErr = LPS_CAL_INIT_UNKNOWN_ERROR;

	pCalStatus->CalInProgress = FALSE;
	pCalStatus->EmptyBktCalDone = FALSE;
	pCalStatus->FullBktCalDone = FALSE;

	pCalInfo->CalRaiseStatus = 0xFF;
	pCalInfo->CalLowerStatus = 0xFF;
	pCalInfo->OffRackEndIndex = 0;
	pCalInfo->CalTopOfCalLiftHt = (float_32)LPS_CAL_TOP_OF_CAL;
	pCalInfo->CalBottomOfCalLiftHt = (float_32)LPS_CAL_BOTTOM_OF_CAL;
	memcpy(LpsCalWrkTbl.Info.LpsCalPositionsDefault, LpsCalPositionsDefaultVals, sizeof(LpsCalPositionsDefaultVals));
	pCalInfo->LpsCalOvrStartRequest = FALSE;
	pCalInfo->LpsCalOvrStopRequest = FALSE;
	pCalInfo->CalRaiseActive = FALSE;
	pCalInfo->CalRaiseComplete = FALSE;
	pCalInfo->CalLowerActive = FALSE;
	pCalInfo->CalLowerComplete = FALSE;
	pCalInfo->CalTiltOverrideComplete = FALSE;
	pCalInfo->CalTiltOverrideFail = FALSE;

	pCalov->LpsCalOvrState = LPS_CAL_OVR_STATE_INACTIVE;
	pCalov->LpsCalAppInfRaiseCmdLmt = LPS_CAL_APP_MAX_RAISE_CMD;
	pCalov->LpsCalAppInfLowerCmdLmt = LPS_CAL_APP_MAX_LOWER_CMD;
	pCalov->LpsCalAppInfRackCmd = LPS_CAL_APP_MIN_RACK_CMD;
	pCalov->LpsCalAppInfDumpCmd = LPS_CAL_APP_MIN_DUMP_CMD;
	pCalov->LpsCalAppInfEngSpdLmt = LPS_CAL_APP_MAX_ENG_SPD*(1UL<<3);
	pCalov->LpsCalAppInfCalOvrActive = FALSE;
	pCalov->LiftBottomFlag = FALSE;
	pCalov->LiftTopFlag = FALSE;
	pCalov->LpsCalTiltOv.CountOfSamples = 0;
	pCalov->LpsCalTiltOv.DesiredTiltExtmm = 0;
    pCalov->LpsCalTiltOv.LpsCalTiltOvrStartRequest = FALSE;
    pCalov->LpsCalTiltOv.LpsCalTiltOvrState = LPS_CAL_OVR_STATE_INACTIVE;
    pCalov->LpsCalTiltOv.LpsCalTiltOvrStopRequest = FALSE;
    pCalov->LpsCalTiltOv.TiltDumpCmdOvr = 0;
    pCalov->LpsCalTiltOv.TiltNoiseMax = 0;
    pCalov->LpsCalTiltOv.TiltNoiseMin = 0;

	LpsCalWrkTbl.EmptyWtCal.lHourMeter = pCalNvm->ShmEmptyMain;
    LpsCalWrkTbl.FullWtCal.lHourMeter = pCalNvm->ShmFullMain;
    LpsCalWrkTbl.EmptyWtCal.cal_stat_hdlr = LpsCalLstatEmptyWtHndlr;
    LpsCalWrkTbl.FullWtCal.cal_stat_hdlr  = LpsCalLstatFullWtHndlr;
    LpsCalWrkTbl.EmptyWtCal.bErrors = 0;
    LpsCalWrkTbl.FullWtCal.bErrors = 0;
    LpsCalWrkTbl.EmptyWtCal.bstatus = LPS_CAL_CALINFO_CAL_SUCCESS_WITHOUT_ERR;
    LpsCalWrkTbl.FullWtCal.bstatus = LPS_CAL_CALINFO_CAL_SUCCESS_WITHOUT_ERR;
    memset(LpsCalWrkTbl.EmptyWtCal.wError, 0x00, LPS_CAL_CALINFO_ERROR_LIST_SZ);
    memset(LpsCalWrkTbl.FullWtCal.wError, 0x00, LPS_CAL_CALINFO_ERROR_LIST_SZ);
    LpsCalWrkTbl.EnableQualRead = FALSE;

    if ((pCalCfg->ExecPeriodSec < LPS_CAL_TASK_PERIOD_MIN_SEC) || (pCalCfg->ExecPeriodSec > LPS_CAL_TASK_PERIOD_MAX_SEC))
    {
		LpsCalWrkTbl.InitErr =  LPS_CAL_INVALID_TIME_STEP;
        return LpsCalWrkTbl.InitErr;
    }

	LpsCalWrkTbl.InitErr = LPS_CAL_INIT_SUCCESS;
	return LpsCalWrkTbl.InitErr;
}

/* This function sends a passed formatted C-string (msg + ...) to the log file and a standard output if enabled by PRINT_TO_STD macro */
void LpsCalPrint( LpsCalPrintLogLevel_t logLevel, char *msg, ... )
{
   static boolean isLogFileNamed = FALSE;
   static char thisSessionLogFilename[60];

   if (LPSCAL_LOG_NOTHING == currentLogLevel) {
       return;
   }

   /* Log only if the current log level is set to at least the requested logLevel */
   if ( ((int)logLevel) >= ((int)currentLogLevel) ) /* lpscurrentLogLevel is to be set in LpsCalInit() */
   {
      va_list vargs;
      FILE* logFileHandle = NULL;

      /* Print to Standard output first (if enabled) */
#if PRINT_TO_STD
      va_start(vargs, msg);
      vprintf(msg, vargs);
      printf("\n"); /* In case the end-of-line was forgotten in msg */
      va_end(vargs);
#endif

      /* Open or create the log file */
      if (!isLogFileNamed)
      {
         /* Get local time */
         time_t rawTime;
         struct tm * timeinfo;
         time ( &rawTime );
         timeinfo = localtime ( &rawTime );

         /* Create the log file name */
         sprintf(thisSessionLogFilename, "/tmp/LpsCal_%d%02d%02d_%02d%02d%02d.log",timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
                                                                                   timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
         isLogFileNamed = TRUE;
      }

      /* Print to the log file if the log file can be opened */
      logFileHandle = fopen(thisSessionLogFilename, "a");
      if (NULL != logFileHandle)
      {
         va_start(vargs, msg);
         vfprintf(logFileHandle, msg, vargs);
         fprintf(logFileHandle, "\n"); /* In case the end-of-line was forgotten in msg */
         va_end(vargs);

         fclose(logFileHandle);
      }
   }
}
