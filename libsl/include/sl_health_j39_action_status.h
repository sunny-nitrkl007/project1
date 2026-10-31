#ifndef SL_HEALTH_J39_ACTION_STATUS_H_
#define SL_HEALTH_J39_ACTION_STATUS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains datatypes needed for the J1939 Peer Health Block support

FILE NAME : sl_health_j39_action_status.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>
/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
enum
{
   SL_HEALTH_J39_START = 1,
   SL_HEALTH_J39_STOP,
   SL_HEALTH_J39_PAUSE,
   SL_HEALTH_J39_RESUME
};

typedef uint_least8_t sl_health_j39_action_t;


/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SL_HEALTH_J39_ACTION_STATUS_H_ */
