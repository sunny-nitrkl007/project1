#ifndef SLCAL_MNGR_TYPES_H_
#define SLCAL_MNGR_TYPES_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains datatypes needed for the Simulink Calibration/Service test blocks.

FILE NAME : sl_cal_mngr_types.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>
#include <cal_defs.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
typedef enum CAL_HSIG CAL_HSIG;

/* ===== Signals passed to the application's calibration hook function ==== */
enum SL_COSM_STATUS {
    SL_CAL_ACTIVE=1,
    SL_CAL_BUSY_EXE=8,
    SL_CAL_ECM_ABORT=26,
	SL_CAL_ECM_DONE=27
};
typedef enum SL_COSM_STATUS SL_COSM_STATUS;


/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SLCAL_MNGR_TYPES_H_ */
