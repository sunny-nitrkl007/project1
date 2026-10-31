/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 2001 - 2011 CATERPILLAR INC.   ALL RIGHTS RESERVED.     %%
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
*** DESCRIPTION : Calibration structures
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

#ifndef CAL_STRUCT_H_
#define CAL_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#ifndef STD_TYPES_H_
#include <cat_std_types.h>
#endif
#ifndef CAL_DEFS_H_
#include <cal_defs.h>
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/


/* Last Cal./Srv. Status */
typedef struct CAL_LSTAT_T {

    /* Non-Volatile Memory handler                                          */
    unsigned_8 (*cal_stat_hdlr)(unsigned_8, struct CAL_LSTAT_T *);

    unsigned_16 wId;                      /* Calibration/Service Mode ID    */
    unsigned_8  bstatus;                  /* Status value at last cal       */
    unsigned_32 lHourMeter;               /* Hour meter value at last cal.  */
    unsigned_8  bErrors;                  /* Number of actual errors saved  */
    unsigned_16 wError[CAL_MAX_ERRORS];   /* Error/Warning List             */

} cal_last_stat_t;

#define CAL_LAST_STAT_SZ (sizeof(cal_last_stat_t))


/* Setup Entry */
typedef struct {
    unsigned_8  *bpState;        /* Byte Pointer to State           */
    unsigned_8   bStateVal;      /* State Value                     */
    unsigned_32 *lpIterm;        /* Long Pointer to Iterm           */
    unsigned_32  lItermBit;      /* I-Term Bit                      */
    unsigned_8   bPolarity;      /* I-Term Bit Polarity             */
    unsigned_32 *lpContFlag;     /* Long Pointer to Continue Flag   */
    unsigned_32  lContFlagBit;   /* Continue Flag I-Term Bit        */
    unsigned_8   bStepNum;       /* Step Number                     */
} cal_setup_tbl_entry_t;


/* Flow Entry */
typedef struct {
    unsigned_8 *bpState;         /* Byte Pointer to State  */
    unsigned_8 bStateVal;        /* State Value            */
    unsigned_8 bStepNum;         /* Step Number            */
} cal_flow_tbl_entry_t;



/* Calibration/Service Mode Entry */
typedef struct {

    unsigned_16 wId;                     /* Calibration/Service Mode ID */
     const cal_setup_tbl_entry_t *pSetupTable;  /* Pointer to Setup Table      */
     const cal_flow_tbl_entry_t *pFlowTable;    /* Pointer to Flow Table       */

    /* Function Pointer to User Defined Hook Function */
    void (*pFunc)(enum CAL_HSIG signal, void *pData);

    void *pData;                     /* Pointer to User Defined Data       */
    cal_last_stat_t *pLastCalStat;   /* Pointer to Last Calibration Status */

} cal_step_tbl_entry_t;


/* App-defined cal interface structure */
typedef struct {

    unsigned_32 exec_prd_ms;       /* Period(ms) app calls cal_interface_main */

    cal_step_tbl_entry_t *cal_tbl; /* Location of calibration table           */
    unsigned_16    cal_tbl_size;   /* Size of calibration table               */

    cal_step_tbl_entry_t *srv_tbl; /* Location of service mode table          */
    unsigned_16 srv_tbl_size;      /* Size of service mode table              */

} cal_interface_init_t;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* CAL_STRUCT_H_ */
