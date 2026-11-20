#ifndef SL_PMS_DEFS_H_
#define SL_PMS_DEFS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains macros needed for the Simulink Programmable Monitoring
System (PMS) interface to the service tool.

FILE NAME : sl_pms_defs.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/


/* general function return values */
#define SL_PMS_OK													0
#define SL_PMS_ERROR											1

/* security level */
#define SL_PMS_SECURITY_LEVEL_0   				0 /* No security */
#define SL_PMS_SECURITY_LEVEL_1   				1 /* CAT svtool accessible */
#define SL_PMS_SECURITY_LEVEL_2   				2 /* customer password protection */
#define SL_PMS_SECURITY_LEVEL_3   				3 /* factory password protection */
#define SL_PMS_SECURITY_LEVEL_4   				4 /* read only */

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SL_PMS_DEFS_H_ */
