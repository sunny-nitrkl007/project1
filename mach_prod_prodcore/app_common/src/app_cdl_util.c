/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                       %%
*** %%  COPYRIGHT (C) 1994-1995 CATERPILLAR INC.   ALL RIGHTS RESERVED.      %%
*** %%      This work contains proprietary information which may             %%
*** %%      constitute a trade secret and/or be confidential.                %%
*** %%                                                                       %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
*
* DESCRIPTION : This file contains several utility functions defined by the
*               application.  These utilities allow the core software to 
*               report system events, report data link connection status, and
*               look-up application pointers at run time.
*
* LANGUAGE :  ANSI C
*
* PORTABILITY ISSUES :  This software was introduced with core 1.15.  
*                       The cdl2_xx CAT data link layer upgrade requires these
*                       application utility functions.
*
* FUNCTIONS:
*	app_connect_func
*	app_periodic_func
*	app_get_fnc_ptr
*	app_get_data_ptr
*	app_activate_system_event
*	app_deactivate_system_event
*	app_clear_all_events
*	app_inf_sys_event_proc
*	app_inf_data_event_proc
*	app_inf_sys_evt_summary
*	app_inf_data_evt_summary
*
*******************************************************************************/
/*******************************************************************************
***
***    Referenced Functions, Data, & Symbols
***    -- #Include's --
***
*******************************************************************************/
#include <std_types.h>
#include <com_proto.h>
#include <app_util_proto.h>

#include <cdl2_proto.h>
#include <app_globals.h>

/*******************************************************************************
***
***    Constants defined for this file
***    -- #Define's --
***
*******************************************************************************/
unsigned_8 catdl_sleeping_mid = 0x00; 

/*******************************************************************************
***
***    Data types defined for this file
***    -- Struct's, Typedef's, Enum's --
***
*******************************************************************************/

/*******************************************************************************
***
***    Internal Functions defined in this file
***    -- Function Prototypes --
***
*******************************************************************************/

/*******************************************************************************
***
***    Internal Data for this file
***    -- Global Symbols --
***
*******************************************************************************/

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
<<<<<<<<<<<<                                             >>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<         Start of Code for this file         >>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<                                             >>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/



/******************************************************************************
 *
 * FUNCTION NAME: app_connect_func
 *
 * DESCRIPTION: This utility is provided by the application to allow the core
 *              data link layer software to report the connect status of a 
 *              configured ECM.
 *
 *              Reports are made for: Active, Sleeping, Lost Connection, and
 *                                    No Response
 *
 *              NOTE: This specific function is not called by name, it is 
 *                    installed by the application.  The application may define
 *                    one function for all ECMs or a unique function for each.
 *
 * INPUTS: unsigned_8 mid
 *          - MID of the ECM with connect status change
 *
 *         util_app_connect_status_t status
 *          - Connect status of the ECM
 *
 * RETURNS: <none> 
 *
 *-----------------------------------------------------------------------------*/
void app_connect_func( unsigned_8 mid, unsigned_8 status)
{
	
	if (status == CBS_ECM_SLEEPING)
     {
          /*indicate that this ECM is sleeping
          //
          //Note that I do not check to see if some other ECM was sleeping
          //before setting this variable.  This is not a problem, because
          //only one ECM can be flash programmed at a time.
          */
          catdl_sleeping_mid = mid;
     }
     else if (mid == catdl_sleeping_mid)
     {
          /*indicate that this ECM is NOT sleeping
          //
          //If the ECM was sleeping, and we get any non-sleeping status
          //update, then we need to indicate that the ECM is no longer
          //sleeping.
          */
          catdl_sleeping_mid = 0x00;
     }

	 cdl2_test_connect_called = TRUE;   
	 
     return;
}


/******************************************************************************
 *
 * FUNCTION NAME: app_periodic_func
 *
 * DESCRIPTION: This utility is provided by the application to allow the core
 *              data link layer software to periodically call the application
 *              function as long as the connection is maintained to the 
 *              configured ECM.
 *
 *              NOTE: This specific function is not called by name, it is 
 *                    installed by the application.  The application may define
 *                    one function for all ECMs or a unique function for each.
 *
 * INPUTS: unsigned_8 mid
 *          - MID of the ECM with connect status change
 *
 * RETURNS: <none> 
 *
 *-----------------------------------------------------------------------------*/
void app_periodic_func( unsigned_8 mid)
{
  (void)mid;
  cdl2_test_periodic_count++;
}




/******************************************************************************
 *
 * FUNCTION NAME: app_get_fnc_ptr
 *
 * DESCRIPTION: This utility is provided by the application to allow the core
 *              software to look-up a function pointer address at run time.  
 *              This is needed for core configuration table which allow the
 *              application to provide function pointers or function ID's in
 *              configuration tables.  In this second case, this utility allows
 *              the core to resolve the ID into a function pointer.
 *
 * INPUTS: unsigned_32 functionid
 *          - 32-bit ID assigned by the application for function pointer look-up
 *
 * RETURNS: <none>
 *
 *-----------------------------------------------------------------------------*/
void *app_get_fnc_ptr( unsigned_32 functionid)
{   
   if ( functionid == 1 )
   {
      return( (void *)app_connect_func);
   }
   else if ( functionid == 0xFF)
   {
      return( NIL );
   }
   else
   {
       return( (void *)app_periodic_func);
   }
}


int_32 app_dummy_data[100];
/******************************************************************************
 *
 * FUNCTION NAME: app_get_data_ptr
 *
 * DESCRIPTION: This utility is provided by the application to allow the core
 *              software to look-up a data pointer address at run time.  
 *              This is needed for core configuration table which allow the
 *              application to provide data pointers or data ID's in
 *              configuration tables.  In this second case, this utility allows
 *              the core to resolve the ID into a data address pointer.
 *
 * INPUTS: unsigned_32 dataid
 *          - 32-bit ID assigned by the application for data pointer look-up
 *
 * RETURNS: <none>
 *
 *-----------------------------------------------------------------------------*/
void *app_get_data_ptr( unsigned_32 dataid)
{   
   if ( dataid == 0xFF)
      return( NIL );
   else 
      return( (void *)app_dummy_data);
}

/******************************************************************************
 *
 * FUNCTION NAME: app_activate_system_event
 *
 * DESCRIPTION: This utility is provided by the application to allow the core
 *              software to report activation of a failure to the application's 
 *              event system.
 *
 * INPUTS: unsigned_16 cid
 *          - Component Identifer for the failure
 *
 *         unsigned_8 fmi
 *          - Failure Mode ID for the detected failure
 *
 * RETURNS: <none> 
 *
 *-----------------------------------------------------------------------------*/
void app_activate_system_event( unsigned_16 cid, unsigned_8 fmi)
{
   unsigned_8 buffer[32];
   unsigned_8 *buf_ptr;
   
   buf_ptr = &buffer[0];
   *buf_ptr++=0x7;
   *buf_ptr++=0x99;
   *buf_ptr++=0xAA;
   *buf_ptr++=0x04;
   *buf_ptr++=0xEA;
   *buf_ptr++=(unsigned_8)(cid>>8);
   *buf_ptr++=(unsigned_8)cid;
   *buf_ptr=fmi;
    
   cdl2_transmit( buffer );
}


/******************************************************************************
 *
 * FUNCTION NAME: app_deactivate_system_event
 *
 * DESCRIPTION: This utility is provided by the application to allow the core
 *              software to report deactivation of a failure to the application's 
 *              event system.
 *
 * INPUTS: unsigned_16 cid
 *          - Component Identifer for the failure
 *
 *         unsigned_8 fmi
 *          - Failure Mode ID for the detected failure
 *
 * RETURNS: <none> 
 *
 *-----------------------------------------------------------------------------*/
void app_deactivate_system_event( unsigned_16 cid, unsigned_8 fmi)
{
   unsigned_8 buffer[32];
   unsigned_8 *buf_ptr;
   
   buf_ptr = &buffer[0];
   *buf_ptr++=0x7;
   *buf_ptr++=0x99;
   *buf_ptr++=0xAA;
   *buf_ptr++=0x04;
   *buf_ptr++=0xED;
   *buf_ptr++=(unsigned_8)(cid>>8);
   *buf_ptr++=(unsigned_8)cid;
   *buf_ptr=fmi;
    
   cdl2_transmit( buffer );
}

/******************************************************************************
 *
 * FUNCTION NAME: app_clear_all_events
 *
 * DESCRIPTION: Initializes all control parameters used by the application to 
 *              manage the information request and report process across one
 *              or more data links
 *
 * INPUTS: <none>
 *
 * RETURNS: TRUE  - Success, all logged system and data events for all MIDS 
 *                           have been cleared
 *          FALSE - Failure, the logged events could not be cleared
 *
 *-----------------------------------------------------------------------------*/
boolean_t app_clear_all_events(void)
{
   static boolean_t for_testing_only_status = FALSE;
   boolean_t clearing_status;
   
   if ( for_testing_only_status == FALSE )
      for_testing_only_status = TRUE;
   else
      for_testing_only_status = FALSE;
   
   /* -------------------------------------------------------------
      Application puts function calls here to clear all logged 
      events.  The results of the clearing request is returned.
      
      TRUE  = Logged events clearing succeeded.
      FALSE = Logged events clearing failed
      ------------------------------------------------------------- */  
   clearing_status = for_testing_only_status;
   
   return(clearing_status);
}
