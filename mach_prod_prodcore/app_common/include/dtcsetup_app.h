/*******************************************************************************
** COPYRIGHT (C) 2012-2013 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:  dtcsetup_app.h
DESCRIPTION:
**  This is a definition include file for dtcsetup configurations at application
**  The include is a must at dtcsetup_config.c file.
*******************************************************************************/
#ifndef DTCSETUP_APP_H_
#define DTCSETUP_APP_H_

/*******************************************************************************
** -- #Include’s --
*******************************************************************************/

#ifndef   DTCSETUPLIB_PUBLIC_H_
#include <dtcsetuplib_public.h>
#endif

#ifndef   DTCSETUP_CDL_PUBLIC_H_
#include <dtcsetup_cdl_public.h>   /* if DTCSETUP_CDL_ENABLE */
#endif

#ifndef   DTCSETUP_PJ1939_PUBLIC_H_
#include <dtcsetup_pj1939_public.h>
#endif

/*Application Header File For J1939 Link*/
#ifndef   J1939_SETUP_PUBLIC_H_
#include <j1939setup_public.h>
#endif

/*Application Header File For NVM Id*/
#ifndef NV_PUBLIC_H_
#include <nv_public.h>
#endif

#include <event_private.h>
#include <diagnostic_private.h>

/*******************************************************************************
** -- #Define, Struct’s, Typedef’s, Enum’s --
*******************************************************************************/

/* Max number of all (diagnostic and event) faults that are possible be noticed
*/

#define DIAG_STORAGE        320

#define EVENT_STORAGE       100


#define DTCSETUP_NUM_POSSIBLE_MAX (DIAG_STORAGE + EVENT_STORAGE)


/*Configuration For NVM Storage*/

/*DTC Event/Diagnostic NVM Storage Area
**     This is the maximum number of all diagnostic and event codes
**     that can be stored in NVM.
*/
#define DTCSETUP_NUM_NVM_MAX  (20 + 20)

/*DTC Event/Diagnostic NVM Storage Size
**     Reserved space in NVM to store the desired number of diagnostics/events.
*/
#define DTCSETUP_NVSIZE       (DTCSETUP_NVM_SIZE(DTCSETUP_NUM_NVM_MAX))

/* Table message for EDDT transmit - number of possible ACTIVE faults.
*/
#define DTCSETUP_NUM_ACTIVE_MAX     DTCSETUP_NUM_NVM_MAX

/*Enable CAT Data Link EDDT*/
#define DTCSETUP_CDL_ENABLE      (1)

/*Enable Proprietary J1939 EDDT*/
#define DTCSETUP_PJ1939_ENABLE   (1)

/*Configuration For EDDT On CAN A*/
#define DTCSETUP_CAN1_LINK       (j1939setup_link_can_a)
#define DTCSETUP_CAN1_ECM_INDEX  (0)


#define DTCSETUP_OPR_ANNUN_ENABLE (1)
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations –
*******************************************************************************/

#endif /* DTCSETUP_APP_H_ */
