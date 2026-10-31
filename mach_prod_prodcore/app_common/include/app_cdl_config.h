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
***	CDL configuration file defines the sizes for certain CDL global 
***	storage areas.
***
*** LANGUAGE :
***    ANSI C
***
*** NOTES:
***	The original version of this file contains what I believe to be
***	ample allocations for the various storage areas.  These sizes
***	can be increased or reduced.
***
*** MACRO LIST:
***
*******************************************************************************/
#ifndef __APP_CDL_CONFIG_H__
#define __APP_CDL_CONFIG_H__

/*************************************************************************/
/****************** The following is for CDL and CDL2 ********************/
/*************************************************************************/
/* NOTE:  Both of these 2 definitions are used by the new (CDL2) and original
(CDL) datalink packages. */

/* Define the number of receive buffers that can be held by the interrupt
   routines for main level processing.  To assure adequate storage for 
   incoming traffic, allocate 1.25 buffers for each millisecond in the
   maximum period between calls to the cdl_receive routine ( including worst 
   latency ), then add two to allow for unfilled buffers at the start and 
   end of the loop time.
   */
/* Called from 20ms task which has a 40ms watchdog
   40 * 1.25 + 2 = 52
   */
#define	CDL_NUM_RXB 52

/* Define the number of allocatable transmit buffers to be managed by
   the CDL module.  This does not affect the number of buffers that can 
   be queued for transmit at one time. 
   */
#define	CDL_NUM_TXB 50


/*************************************************************************/
/****************** The following is for CDL *****************************/
/*************************************************************************/
/* NOTE:  Set the following 3 definitions to 1 if the new datalink package (CDL2)
is used. */

/* Define the number CDL parameters that can be defined for reception */
#define CDL_NUM_RX_PIT 1

/* Define the number CDL parameters that can be defined for transmission */
#define CDL_NUM_TX_PIT 1

/* Define the number of queued receive parameter storage blocks.  These are 
   used by the general queued receive parameter handler.  
   */
#define CDL_NUM_QRPSB 1


/*************************************************************************/
/****************** The following is for CDL2 ****************************/
/*************************************************************************/
/* NOTE:  Set all of the remaing definitions to 1 if the original datalink package
(CDL) is used. */

/* The following TX definitions determine the sizes of the individual transmit tables.
These determine the number of different parameter types that are available to other
modules on the datalink. */
#define CDL2_NUM_TX_PIT 100
#define CDL2_SUBLIST_D0_NUM_TX_PIT 30
#define CDL2_SUBLIST_D1_NUM_TX_PIT 40
#define CDL2_SUBLIST_D2_NUM_TX_PIT 1
#define CDL2_SUBLIST_D3_NUM_TX_PIT 1
#define CDL2_SUBLIST_F916_NUM_TX_PIT 1

/* This defines the size of the receive pit.  Set this to the number of
parameters that this module will be receiving. */
#define CDL2_NUM_RX_PIT 40
/* This defines the size of the receive data pit.  Set this to the number of
parameters that will be requested from other modules. */
#define CDL2_NUM_RX_DATA_PIT 40
/* This defines the number of ECMs from which the application is requesting data. */
#define CDL2_NUM_RX_DATA_PIT_MID_TABLE 2

/* The following WR definitions determine the sizes of the individual write tables. */
#define CDL2_NUM_WR_PIT 35
#define CDL2_SUBLIST_D0_NUM_WR_PIT 20
#define CDL2_SUBLIST_D1_NUM_WR_PIT 20
#define CDL2_SUBLIST_D2_NUM_WR_PIT 1
#define CDL2_SUBLIST_D3_NUM_WR_PIT 1
#define CDL2_SUBLIST_F916_NUM_WR_PIT 1

/* Define the number of queued receive parameter storage blocks.  These are 
   used by the general queued receive parameter handler.  
   */
#define CDL2_NUM_QRPSB 50

/* Define the maximum number of supported standard broadcast message requests
to this ecm. */
#define CDL2_SPB_MSG_MAX 8

/* Define the maximum number of supported group broadcast message requests
to this ecm. */
#define CDL2_PGB_MSG_MAX 8

/* Define the number of cdl2_transmit buffers.
   NOTE:  This must be at least 10 if you are using the CDL2 event interface
   software and the CBS system (using cdl2_cbs_ginit related).  This must be
   at least 5 if you are only using the CBS system.
   Make larger than 10 (or 5) if your application uses the cdl2_transmit function.
   cdl2_transmit is a shared resource between the cdl2 datalink software and
   the application. */
#define CDL2_TRANSMIT_BUF_SIZE   10

/*****************************************************************************
   This constant sets the max number of ECMs you will able to make parameter
   requests to.  If you set this large enough, you can add ECMs later by simply
   updating you config.  If this number is too small, you will have to allocate
   more memory when you expand your config to include more ECMs.  There is only
   one ECM entry required to support all requests related to that ECM.
   
   Note: If the number is too small for your config, CBS will fail during 
         the ginit.
   
   Memory Cost: 46 bytes per CBS ECM Status entry
-----------------------------------------------------------------------------*/
#define CDL2_CBS_MAX_NUM_ECM            5


/*****************************************************************************
   This constant is for allocating the memory used to support PGB requests.
   Each PGB request require at least on reftag (good for multiple parameters) 
   and one parm entry per parameter.  If you are using a large number of rates,
   you will use up more reference tags.  If you use a standard rate for most 
   parameters, you will require fewer reference tags (since parameters are 
   grouped).  
   
   Note: A size error is not detectable during ginit.  A failure will occur
         during run time and CBS will not complete the connection with the ECM.
	 
   Memory Cost: 8 bytes per PGB Reftag Request entry
-----------------------------------------------------------------------------*/
#define CDL2_PGB_MAX_NUM_REFTAG         10


/*****************************************************************************
   One parameter table entry is required for each of your PGB requested 
   parameters.  If the number is large enough, you can add new requests to you 
   config without any errors.  If the number is too small, adding more config 
   entrys will require you to allocate more memory.  
   
   Note: If the number is too small for your config, CBS will fail during 
         the ginit.
   
   Memory Cost: 6 bytes per PGB Parameter Request entry
-----------------------------------------------------------------------------*/
#define CDL2_PGB_MAX_NUM_REQ_PARM       25


/*****************************************************************************
   One request parameter entry is required for each of your ADT requested 
   parameters.  If the number is large enough, you can add new requests to you 
   config without any errors.  If the number is too small, adding more config 
   entrys will require you to allocate more memory.  
   
   Note: If the number is too small for your config, CBS will fail during 
         the ginit.
   
   Memory Cost: 6 bytes per ADT Parameter Request entry
-----------------------------------------------------------------------------*/
#define CDL2_ADT_MAX_NUM_REQ_PARM       10


/*****************************************************************************
   This constant sets the max number of ECMs that will be able to make ADT 
   requests to you.  You should set this number large enough to support all 
   ECM's and PC Tools that may simultaneously request asynchronous updates 
   from your ECM.  One ECM entry is required for one or more requests.  If the
   number is too small, a request will be rejected with a "no buffers" error
   to the requesting ECM.  
      
   Memory Cost: 52 bytes per ADT Requestor ECM table entry
-----------------------------------------------------------------------------*/
#define CDL2_ADT_MAX_NUM_REQUESTOR      3


/*****************************************************************************
   This constant is for allocating the memory used to support ADT requests to
   your ECM.  Each requestable data element will require one data status entry
   to guarantee the data is available to any ECM or PC tool.  This constant is
   independent of the number of ECMs which request the same data since all
   requests share the same data status entry.  If this number is less than the
   parameters you could make available to ECMs and PC Tools then some requestor
   will get a "no buffers" error when trying to access the data.  
	 
   Memory Cost: 24 bytes per ADT Requestor Data Status entry
-----------------------------------------------------------------------------*/
#define CDL2_ADT_MAX_NUM_DATA_STATUS    10


/*****************************************************************************
   Each ADT requested parameter requires three lists to support the transaction.
   This symbol is used to set all three lists which must be maintained with 
   correct size proportional to each other.  The first list is a reference 
   entry to relate the data status to the appropriate report que.  The second 
   list provides each requested parameter with a buffer for pending reports.
   The third list is maintained to allow each Requestor ECM (or Tool) to access
   references owned by it to clear all or clear a specific request entries.  
   
   This number should be large enough to support all the ADT transactions you
   will maintain at one time.  If the number is too small some requestor
   will get a "no buffers" error when trying to access data.  
   
   Memory Cost: 78 bytes per ADT Requestor Ref/RefUsed/Report entry (3 lists)
-----------------------------------------------------------------------------*/
#define CDL2_ADT_MAX_NUM_REF_ENTRIES     20   


/*****************************************************************************
   This constant sets the max number of active read requests that can be 
   enabled at one time.  If the application attempts to activate too many
   read polling requests, the return from the call will indicate failure.
      
   This number should be large enough to support all read polling data updates
   you will maintain at one time.  If the number is too small some active 
   requests will be rejeceted when trying to enable read polling.  
   
   Memory Cost: 32 bytes per Read Poll Request entry
-----------------------------------------------------------------------------*/
#define CDL2_CBS_MAX_READ_POLL_ENTRIES   1

/*****************************************************************************
   This constant sets the max number of requests that the core can post from 
   the data link handlers to the application for data access.  If the number 
   is too small, requests will not be passed to the core.  This would cause the 
   service tool (or monitor) to rerequest the information.  
   
   The queue size should be sized appropriately for the number of requests 
   (and number of data links) your application information task will service.   
      
   Memory Cost: 26 bytes (per input entry)
-----------------------------------------------------------------------------*/
#define COM_INF_INPUT_QUE_SIZE            10

#endif /* __APP_CDL_CONFIG_H__ */
