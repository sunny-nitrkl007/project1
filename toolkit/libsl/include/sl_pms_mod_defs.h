#ifndef SL_PMS_MOD_DEFS_H_
#define SL_PMS_MOD_DEFS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains macros needed for the Simulink Programmable Monitoring
System (PMS) interface to the service tool.

FILE NAME : sl_pms_mod_defs.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/


#define SL_PMS_PARAM_MAX										255
#define SL_PMS_VERSION											1
#define SL_PMS_CHECKSUM_CONST								0xAA
#define SL_PMS_INVALID_PACKET_ID						0xFFFF
#define SL_PMS_SECURITY_READONLY						0
#define SL_PMS_HOUR_SCALE										10
#define SL_PMS_CDL_MAX_NUM_PACKET						12
#define SL_PMS_DEBOUNCE_TIME_SCALE					1000
#define SL_PMS_TATTLETALE_MAX								0x3F
#define SL_PSM_CDL_MAX_NUM_PACKET						12

/* PID Definitions */
#define	SL_PMS_CDL2_PID_VERSION_NUMBER			0xF330
#define	SL_PMS_CDL2_PID_PACKET_SELECTION		0xF46E
#define	SL_PMS_CDL2_PID_PACKETS_LIST				0xF805
#define	SL_PMS_CDL2_PID_ACTION_INFO					0xF808
#define	SL_PMS_CDL2_PID_ACTION_LIMITS				0xF809
#define	SL_PMS_CDL2_PID_ACTION_SECURITY			0xF854
#define	SL_PMS_CDL2_PID_ACTION_INFO_REQ			0xFC0A
#define	SL_PMS_CDL2_PID_ACTION_LIMITS_REQ		0xFC0B

/* Any Packet IDs greater than or equal to this value will
   not be transmitted over CDL. This allows for unofficial
   Packet IDs to be used with the event system. */
#define SL_PMS_PACKET_ID_MAX								0x00CF



#define SL_PMS_VERSION          						1


#define SL_PMS_SECURITY_ACCESS_READONLY			0 /* read only (also)
                                                 - this is used in monitoring action
                                                   security response. */



/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SL_PMS_MOD_DEFS_H_ */









