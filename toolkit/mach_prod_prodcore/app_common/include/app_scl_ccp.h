/******************************************************************************
**
*** ***************************************************************************
*** *
*** * COPYRIGHT (C) 2005 CATERPILLAR INC. ALL RIGHTS RESERVED.
*** *     This work contains proprietary information which may
*** *     constitute a trade secret and/or be confidential.
*** *     Copyright notice is precautionary only and does not
*** *     imply publication.
*** *
*** ***************************************************************************
**
*** FILE:
***     app_scl_ccp.h
***
*** DESCRIPTION:
***
***
***
******************************************************************************/

#ifndef APP_SCL_CCP_H_
#define APP_SCL_CCP_H_

/******************************************************************************
***
***    External function prototypes, data, & symbols
***    -- #Include's --
***
******************************************************************************/

/******************************************************************************
***
***    Constants defined for this file
***    -- #Define's --
***
******************************************************************************/

/******************************************************************************
***
***    Enumerations/Unions/Macros for this file
***    -- enum/union --
***
******************************************************************************/

/******************************************************************************
***
***    Structure Definitions for this file
***    -- typedefs --
***
******************************************************************************/

/******************************************************************************
***
***    File scope functions defined for this file
***    -- Function Prototypes --
***
******************************************************************************/
/* Place this call in app_post_irq_init after hal_init and j1939_init
*/
void app_scl_ccp_init(void);

/* Place this call in task_1x
*/
void app_scl_ccp_update(void);

/******************************************************************************
***
***    Global data symbols defined in this file
***    -- extern data type definitions --
***
******************************************************************************/

#endif /*APP_SCL_CCP_H_*/

