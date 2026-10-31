/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 2010 CATERPILLAR INC.   ALL RIGHTS RESERVED.            %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
*** $Source:  $
***
*** $Author: $
***
*** $Locker:  $
***
*** $Date: $
***
*** $Revision: $
***
*** $State: $
***
*** $Header: $
***
*** $Log: $
***
*** DESCRIPTION : Calibration definitions
***
*** REQUIRED HEADER :
***
*** LANGUAGE :                  
***    ANSI C
***
*** COMPILE FLAGS :
***
*** METHOD:
***
*** NOTES:
***
*** GLOBALS USED:
***
*** FUNCTIONS CALLED:
***
*******************************************************************************/

#ifndef CAL_DEFS_H_
#define CAL_DEFS_H_
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/* ===== Maximum Buffer size for errors and warnings stored ===== */
#define CAL_MAX_ERRORS (9)


/* ===== Calibration return code ===== */
#define CAL_SUCCESS (0)
#define CAL_FAIL    (1)

/* ===== CDL receive handle message data offsets ================ */
#define CAL_MSG_RX_ID_OFFSET      (0) /* Id             */
#define CAL_MSG_RX_HS_OFFSET      (2) /* Handshake      */
#define CAL_MSG_RX_CB_OFFSET      (3) /* Control bytes  */
#define CAL_MSG_RX_ACT_OFFSET     (4) /* Action         */
#define CAL_MSG_RX_ACT_CMD_OFFSET (6) /* Action command */

/* ========== Calibration Action Commands for display types =============== */

/* Represents No Display */
#define CAL_ACTCMD_NODISP    (0x0000)

/* Represents EMS Display type */
#define CAL_ACTCMD_EMSDISP 	 (0x0001)

/* ===== Unused ID in calibration or service table ===== */
#define CAL_UNUSED_ID    (0)

/* =================== Calibration Codes For Managing Errors & Warnings === */
#define CAL_ERR_WARN_ADDED    (0)  /* Successful Added                      */
#define CAL_ERR_WARN_DUP      (1)  /* Already in list Active - Duplicate    */
#define CAL_ERR_WARN_NO_SPACE (2)  /* No space left in list to store info   */
#define CAL_ERR_WARN_SUCCESS  (0)  /* Successful                            */
#define CAL_ERR_WARN_FAIL     (1)  /* Failure                               */

/* ===== Calibration Error / Warning ID's ===== */
#define CAL_EW_ECM_FLT_ID   0x0001    /* ECM Fault                           */
#define CAL_EW_ACT_DIAG_ID  0x0002    /* Active Diagnostic Present           */
#define CAL_EW_DACT_CAL_ID  0x0003    /* Different Cal is active on this ECM */
#define CAL_EW_OEA_CAL_ID   0x0004    /* Other ECM has this cal active       */
#define CAL_EW_ILCK_LST_ID  0x0005    /* Calibration interlock lost          */
#define CAL_EW_SVC_ABRT_ID  0x0006    /* Service tool / monitor abort        */
#define CAL_EW_DSP_NSPT_ID  0x0007    /* Display not supported               */
#define CAL_EW_DSP_UAVL_ID  0x0008    /* Display unavailable                 */
#define CAL_EW_ECM_ABRT_ID  0x0009    /* ECM Abort                           */
#define CAL_EW_CAL_FAIL_ID  0x000A    /* Calibration failure                 */
#define CAL_EW_CAL_NSPT_ID  0x000B    /* Calibration not suppported          */
#define CAL_EW_INV_ACT_ID   0x0102    /*Invalid or unsupported command/Action*/

/* ===== PID's ===== */
#define CAL_CMD_PID        (0xF840)   /* Calibration command   */
#define CAL_RSP_PID        (0xF841)   /* Calibration response  */
#define CAL_SRV_CMD_PID    (0xF847)   /* Service mode command  */
#define CAL_SRC_RSP_PID    (0xF848)   /* Service mode response */
#define CAL_LSC_HOURS_PID		(0xF856)	/* Last Successful Calibration Operating Hours */
#define CAL_LSC_SELECT_CAL_PID	(0xD00289)	/* Last Successful Calibration ID Selector */

/* ===== Calibration Status Handler Commands ===== */
#define CAL_PUSH_STATUS    (1)
#define CAL_PULL_STATUS    (2)

/* ===== Signals passed to the application's calibration hook function ==== */
enum CAL_HSIG {
    CAL_HSIG_INIT,        /* Sent once going from Idle to Enabled     */
    CAL_HSIG_START,       /* Sent once going from Enabled to Run      */
    CAL_HSIG_RUN,         /* Sent once per loop while in Run          */
    CAL_HSIG_SHUTDOWN,    /* Sent once per loop while in Shutdown     */
    CAL_HSIG_CLEANUP,     /* Sent once when going to idle state       */
    CAL_HSIG_WAIT,        /* Sent while waiting to start              */
    CAL_HSIG_ABORT = -1   /* Sent once going from Run to Shutdown if
                             ecm asked to abort                       */
};

#define SRV_TEST_MODE_ACTIVE       (0x01) /*Service Mode is active state*/
#define SRV_TEST_MODE_NOT_ACTIVE   (0x00) /*Service Mode is Not active state*/
#define CAL_MODE_ACTIVE            (0x01) /*Calibration mode is active */
#define CAL_MODE_NOT_ACTIVE        (0x00) /*Calibration mode is not active state*/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* CAL_DEFS_H_ */
