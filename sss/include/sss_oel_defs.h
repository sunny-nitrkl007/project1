#ifndef SSS_OEL_DEFS_H_
#define SSS_OEL_DEFS_H_

/*******************************************************************************
** COPYRIGHT (C) 2000 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillars proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME: sss_oel_defs.h
DESCRIPTION:
SSS subsystem task defines's.

*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations
*******************************************************************************/
#define SSS_OEL_USEC_TO_NSEC 1000

/* Define desired task period's, LSB = u32_l20 sec.
   --------------------------------------------------------------------------- */
#define SSS_PERIOD_U32_L20_0015MSEC 15729
#define SSS_PERIOD_U32_L20_0030MSEC 31457
#define SSS_PERIOD_U32_L20_0060MSEC 62915
#define SSS_PERIOD_U32_L20_0120MSEC 125829
#define SSS_PERIOD_U32_L20_0240MSEC 251658
#define SSS_PERIOD_U32_L20_0495MSEC 519045
#define SSS_PERIOD_U32_L20_1005MSEC 1055819
#define SSS_PERIOD_U32_L20_1995MSEC 2091909

/* this sss_period_none is created only for autostart init, the peroidic task assigned to
   doesn't mean the real periodic task */

#define SSS_PERIOD_NONE SSS_PERIOD_U32_L20_0015MSEC

/* Define task ID's.
   --------------------------------------------------------------------------- */
#define SSS_TID_0015MSEC 7
#define SSS_TID_0030MSEC 6
#define SSS_TID_0060MSEC 5
#define SSS_TID_0120MSEC 4
#define SSS_TID_0240MSEC 3
#define SSS_TID_0495MSEC 2
#define SSS_TID_1005MSEC 1
#define SSS_TID_1995MSEC 0

#define SSS_TID_BCKGND   254
#define SSS_TID_INIT     255

/* Define task ID's.
   !!!!!!!!!! NOT for new design !!!!!!!!!!
   --------------------------------------------------------------------------- */
#define SSS_TID_15MSEC SSS_TID_0015MSEC
#define SSS_TID_30MSEC SSS_TID_0030MSEC
#define SSS_TID_60MSEC SSS_TID_0060MSEC
#define SSS_TID_120MSEC SSS_TID_0120MSEC
#define SSS_TID_240MSEC SSS_TID_0240MSEC
#define SSS_TID_495MSEC SSS_TID_0495MSEC


/* Default subsystem task periods, LSB = 1 usec.
   !!!!!!!!!! NOT for new design !!!!!!!!!!
   -------------------------------------------------------------------------------- */

#define SSS_PERIOD_15MSEC SSS_PERIOD_U32_L20_0015MSEC
#define SSS_PERIOD_30MSEC SSS_PERIOD_U32_L20_0030MSEC
#define SSS_PERIOD_60MSEC SSS_PERIOD_U32_L20_0060MSEC
#define SSS_PERIOD_120MSEC SSS_PERIOD_U32_L20_0120MSEC
#define SSS_PERIOD_240MSEC SSS_PERIOD_U32_L20_0240MSEC
#define SSS_PERIOD_495MSEC SSS_PERIOD_U32_L20_0495MSEC
#define SSS_PERIOD_1005MSEC SSS_PERIOD_U32_L20_1005MSEC
#define SSS_PERIOD_1995MSEC SSS_PERIOD_U32_L20_1995MSEC
#define SSS_PERIOD_BCKGND   0 /*background task does not have any specific rate associated */


/* Subsystem initialization task create return status defines.
   --------------------------------------------------------------------------- */
#define SSS_INIT_OK 0			/* Subsystem init No error. */
#define SSS_INIT_ERR_MALLOC 3		/* Subsystem init memory allocation error. */

/* Method submit return status defines.
   --------------------------------------------------------------------------- */
#define SSS_SUBMIT_METHOD_OK 0		/* No error. */
#define SSS_SUBMIT_METHOD_ERR_TID 1     /* Subsystem Task ID not found. */
#define SSS_SUBMIT_METHOD_ERR_MALLOC 2	/* Method item memory allocation error. */

/* Method submit types.
   --------------------------------------------------------------------------- */
#define SSS_METHOD_ONESHOT 0
#define SSS_METHOD_PERIODIC 1

/* subsystem control types
   ------------------------------------------------------------------------------*/
#define SSS_SUBSYS_CONTROL_ELEM_TYPE_PACKD  0
#define SSS_SUBSYS_CONTROL_ELEM_TYPE_SUBSYS 1

#endif /* SSS_OEL_DEFS_H_ */
