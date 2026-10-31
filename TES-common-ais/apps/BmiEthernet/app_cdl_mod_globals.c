/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 1994-1995 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
*** DESCRIPTION :
*** Declare the CDL global storage variables whose sizes are defined
*** by the application.
***
*** REQUIRED HEADER :
*** app_cdl_config.h
*** cdl2_proto.h
***
*** LANGUAGE :                  
***    ANSI C
***
*** COMPILE FLAGS :
***
*** METHOD:
*** Use identifiers defined by the application in app_cdl_config.h to
*** define the sizes of these global variables.
***
*** NOTES:
***
*** FUNCTIONS:
***
*** INTERRUPTS:
***
*******************************************************************************/

#include "app_cdl_config.h"
#include <cdl2_proto.h>
#include <cdl_struct.h>
#include <cdl_mod_struct.h>
#include <cdl_std_hdlr_struct.h>
#include "app_rtos_config.h"

/*******************************************************************************
***
***    Constants defined for this file
***    -- #Define's --
***
*******************************************************************************/
/* This defines the required number of report que entires to support each 
   reference entry made by a requestor ECM for ADT status reports
   */
#define CDL2_ADT_MAX_NUM_REPORT_ENTRIES (CDL2_ADT_MAX_NUM_REF_ENTRIES*CDL2_ADT_MAX_NUM_PENDING_REPORTS)

/*******************************************************************************
***
***    Data types defined for this file
***    -- Struct's, Typedef's, Enum's --
***
*******************************************************************************/

/*******************************************************************************
***
***    File scope functions defined for this file 
***    -- Function Prototypes --
***
*******************************************************************************/

/*******************************************************************************
***
***    File scope symbols defined for this file
***    -- Symbols --
***
*******************************************************************************/

/*************************************************************************/
/****************** The following is for CDL and CDL2 ********************/
/*************************************************************************/
const unsigned_16    cdl2_num_cmn_rx_pit = CDL_NUM_CMN_RX_PIT;
const cdl2_cmn_rx_pit_t    *cdl2_cmn_rx_pit[CDL_NUM_CMN_RX_PIT];

