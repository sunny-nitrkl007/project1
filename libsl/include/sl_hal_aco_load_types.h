#ifndef Sl_HAL_ACO_LOAD_TYPES_H_
#define Sl_HAL_ACO_LOAD_TYPES_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains datatypes needed for the setting up of dynamic load types for ACO drivers in HAL.

FILE NAME : sl_hal_aco_load_types.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/

typedef enum {
	SL_FILTER_30Hz_LOW_PASS = 0,
    SL_FILTER_60Hz_LOW_PASS = 1,
    SL_FILTER_90Hz_LOW_PASS = 2
} sl_hal_filter_select_t;

typedef enum {
	SL_CAT_1_ACTUATION_PROPORTIONAL = 0,
    SL_CAT_1_ACTUATION_ON_OFF = 1,
    SL_CAT_1_ACTUATION_ON_OFF_LAMP = 2,
	SL_CAT_1_ACTUATION_ON_OFF_PASSIVE = 3
} sl_hal_actuation_ctrl_t;

typedef enum {
	SL_CAT_1_SUPPLY_VOLTAGE_12V = 0,
	SL_CAT_1_SUPPLY_VOLTAGE_24V = 1
} sl_hal_load_supply_voltage_t;

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/

#endif /* Sl_HAL_ACO_LOAD_TYPES_H_ */
