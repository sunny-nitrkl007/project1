/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 2001,2003 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
**
*
* FILE NAME: app_can_init.c
*
* DESCRIPTION: HAL CAN Interface to CCP & j1939 limited support version
*
* LANGUAGE: ANSI C
*
* FUNCTION LIST: app_can_init()
*
* HISTORY :
* 
*******************************************************************************/

/*******************************************************************************
***
***    Referenced Functions, Data, & Symbols
***    -- #Include's --
***
*******************************************************************************/
#ifndef __STD_TYPES_H__
#include <std_types.h>
#endif /* __STD_TYPES_H__ */

#ifndef __STRING_H__
#include <string.h>
#endif

#ifndef __UTIL_PROTO_H__
#include <util_proto.h>
#endif

#ifndef HAL_CAN_H
#include <hal_can.h>
#endif

#ifndef __APP_CAN_INIT_PROTO_H__
#include <app_can_init_proto.h>
#endif

/*******************************************************************************
***
***    Constants defined for this file
***    -- #Define's --
***
*******************************************************************************/

/* (TSEG1 + TSEG2 + 1) * TIMEQUANTA = bitrate */
#define TSEG1		    13
#define TSEG2		    2
#define SYNC_JMP_WIDTH	1
#define TIMEQUANTA_250	274878    /* Scaled 2^-40  -  This yields 250kb/s     */
#define TIMEQUANTA_500	137439    /* This yields 500kb/s                      */
#define CAN_SLOPE	    1	      /* Not used yet                             */
#define NUM_RX1		    1         /* 1 for CCP, 3 for j1939                   */
#define NUM_TX1		    1         /* 1 for CCP, 1 for j1939                   */
#define NUM_RX0		    5
#define NUM_TX0		    4
#define NUM_STAT	    1

#define FREE_ARRAY_SIZE	130		  /* Size of the tx and rx queue combined */
#define MAX_TX_UPDATES	5		  /* Number of CAN messages to process per loop */
#define MAX_RX_UPDATES	5		  /* Number of CAN messages tp process per loop */
/*******************************************************************************
***
***    Structure definitions for this file
***    -- typedefs --
***
*******************************************************************************/

/*******************************************************************************
***
***    Prototypes
***    
***
*******************************************************************************/
void app_hal_can_rx_hdlr(hal_can_port_t    port, 
                     	 hal_u16_t        object);

/*******************************************************************************
***
***    Internal Data for this file
***    -- Global Symbols --
***
*******************************************************************************/
hal_can_callback_t *app_can_rx_fn_ptr  = app_hal_can_rx_hdlr;

/**------------------------------------
** A pointer to an array of Mbuf
-------------------------------------*/
mbuf_hdr_t *mbuf_hdr_free_ary=NIL;

/**------------------------------------------------------
** Holds the address of the first and the last elements 
** of the respective queues.
-------------------------------------------------------*/
UTIL_Lnk_t mbuf_hdr_free_q,tx_buf_q,rx_buf_q;

/**------------------------------------------------------
** Set filter to look at only 0x400
-------------------------------------------------------*/
hal_can_filter_t filter1={ HAL_CAN_PACKET_STD_DATA_FRAME, 0xF0000000, 0x80000000};

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
<<<<<<<<<<<<                                             >>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<         Start of Code for this file         >>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<                                             >>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/*
 *****************************************************************************
 *
 *Name:         app_can_init
 *Description: 
 * This function checks if the CAN chip is supported and sets the number of
 * objects needed by the application. It then calls each component init
 * function, passing the appropriate object numbers.
 *
 *****************************************************************************
 */

void app_can_init(void)
{
	/*---------------------------------------------------
	** Allocate memory of size two mbuf_hdr_t elements 
	----------------------------------------------------*/
	mbuf_hdr_free_ary = (mbuf_hdr_t*)util_malloc(FREE_ARRAY_SIZE * sizeof(mbuf_hdr_t));
	if(mbuf_hdr_free_ary == NIL)
	{
		return;
	}

	/*----------------------------------
	** Initialize the queues
	-----------------------------------*/
	util_que_init(&mbuf_hdr_free_q, mbuf_hdr_free_ary, 
	              FREE_ARRAY_SIZE, sizeof(mbuf_hdr_t));

	util_que_init(&rx_buf_q,NIL,0,0);

	util_que_init(&tx_buf_q,NIL ,0,0);

	/*------------------------------------------------------
 	** Initialize the HW parameters, Rx, Tx and status objects
	** as required for the user.
	---------------------------------------------------------*/
   	if(hal_can_query_supported(HAL_CAN_PORT_01))
  	{

		/*-----------------------------------------------
		** Set the CAN Port Timequanta.
		------------------------------------------------*/
		hal_can_set_timequanta(HAL_CAN_PORT_01, hal_can_query_timequanta(HAL_CAN_PORT_01, TIMEQUANTA_500));

		/*--------------------------------------------------
		** Set the CAN Port Bit timing.
		---------------------------------------------------*/
		hal_can_set_bittiming(HAL_CAN_PORT_01, TSEG1, TSEG2, SYNC_JMP_WIDTH);
	  
		/*--------------------------------------------------
		** Set the objects needed to support all protocols.
		---------------------------------------------------*/
		hal_can_set_rx_objects(HAL_CAN_PORT_01, NUM_RX1);
	  	hal_can_set_tx_objects(HAL_CAN_PORT_01, NUM_TX1);
	  	hal_can_set_status_objects (HAL_CAN_PORT_01, NUM_STAT);

		/*--------------------------------------------------
		** Set the filters for the Rx objects.
		--------------------------------------------------*/
		hal_can_set_rx_filter (PORT_ZERO, 0, filter1);

		/*--------------------------------------------------
		** Set the callback functions for the two Rx objects,
		** one Tx and one status objects.
		--------------------------------------------------*/
		hal_can_set_rx_callback(HAL_CAN_PORT_01, 0, app_can_rx_fn_ptr);
			   
		/*--------------------------------------------------
		** Apply the filters that were previously set by the 
		** application
		---------------------------------------------------*/
		hal_can_apply_rx_filters(HAL_CAN_PORT_01);

		/*--------------------------------------------------
		** Enable the CAN port
		--------------------------------------------------*/
		hal_can_enable_port(HAL_CAN_PORT_01);

		/*--------------------------------------------------
		** Initialize the status of each object
		--------------------------------------------------*/
		hal_can_set_rx_status(HAL_CAN_PORT_01, 0, HAL_CAN_RX_STATUS_ENABLED);
		
	}
	return;
}

/*
 *****************************************************************************
 *
 *Name:         app_can_rx_handler
 *Description: 
 * This function receives all incoming data packets.
 *
 *****************************************************************************
 */
void app_hal_can_rx_hdlr(hal_can_port_t    port, 
                     hal_u16_t        object)
{
	hal_can_packet_t		packet;
	mbuf_hdr_t				*mbuf_ptr;
	
	hal_can_get_rx_packet(port, object, &packet);

	/**----------------------------------------------
	** Get an Mbuf from the Mbuf free pool
	------------------------------------------------*/
	mbuf_ptr = (mbuf_hdr_t *)util_que_get(&mbuf_hdr_free_q);

	if(mbuf_ptr != NIL)
	{
		/**---------------------------------------------- 
		** Copy data from hal can object to Mbuf 
		------------------------------------------------*/
		mbuf_ptr->len = packet.length;
		mbuf_ptr->type = (packet.arbitration >> 21);
		memcpy(mbuf_ptr->data, packet.data, 8);

		/**------------------------------------------------
		** Put the Mbuf in the Rx queue 
		--------------------------------------------------*/
		util_que_put(&rx_buf_q,mbuf_ptr);
	
	}
	else
	{
		return;
	}
		
	/**------------------------------------------- 
	** Reset the status of the hal can Rx object. 
	---------------------------------------------*/
	hal_can_set_rx_status(port, object, HAL_CAN_RX_STATUS_ENABLED);

}

/*=======================================================
** FUNCTION NAME:	app_hal_can_tx_update
** 
** DESCRIPTION: This function gets an mbuf from tx_buf_q, and 
** then copies the message to  hal can tx object and put the 
** mbuf back to the mbuf_hdr_free_q.  
** 
** RETURNS: Return value is of type void.
=======================================================================**/
void app_hal_can_tx_update(void)
{
	
	hal_can_packet_t	hal_can_packet;
	mbuf_hdr_t		*mbuf_ptr;
	static boolean	tx_wait_flag = FALSE;
		
	/**-----------------------------------------
	** Make sure previous tx has been completed
	**---------------------------------------------*/
	if((HAL_CAN_TX_STATUS_COMPLETE == hal_can_get_tx_status(HAL_CAN_PORT_01,0)) ||
	   (FALSE == tx_wait_flag))
	{

		/* Message has completed clear flag */
		tx_wait_flag = FALSE;

		/**-----------------------------------------
		** Get an Mbuf from the Tx buf queue
		**---------------------------------------------*/
		if((mbuf_ptr = (mbuf_hdr_t*)util_que_get(&tx_buf_q))!= NIL)
		{
			/**-------------------------------------
			** Set frame type to standard data frame
			**-------------------------------------*/
			hal_can_packet.frame =HAL_CAN_PACKET_STD_DATA_FRAME;

			/**--------------------------------------------
			** Copy message from Mbuf to hal can packet
			**------------------------------------------- */
			hal_can_packet.length = (unsigned_8)mbuf_ptr->len;
			hal_can_packet.arbitration = (mbuf_ptr->type << 21);
			memcpy(hal_can_packet.data, mbuf_ptr->data, 8);		
			
			memset((unsigned_8*)mbuf_ptr, 0x00, sizeof(mbuf_hdr_t));
			/**-----------------------------------
			** Put the Mbuf back to the free q 
			**-----------------------------------*/
			util_que_put(&mbuf_hdr_free_q, mbuf_ptr);

			/**--------------------------------------
			** Set the hal can transmit message packet 
			**--------------------------------------*/
			hal_can_set_tx_packet(HAL_CAN_PORT_01, 0, &hal_can_packet);

			/**--------------------------------------
			** Set hal can tx object status 
			**------------------------------------*/
			hal_can_set_tx_status(HAL_CAN_PORT_01, 0, HAL_CAN_TX_STATUS_PENDING);
			
			/* This indicates we need to wait for this message to complete before 
			   sending the next message */
			tx_wait_flag = TRUE;  

		   /*	while(HAL_CAN_TX_STATUS_COMPLETE != hal_can_get_tx_status(HAL_CAN_PORT_01, 0));*/

		}
	}
}


/*=======================================================
** FUNCTION NAME:	app_get_rx_can_message
** 
** DESCRIPTION: This function gets an mbuf from rx_buf_q, and 
** then copies the message to  hal can tx object and put the 
** mbuf back to the mbuf_hdr_free_q.  
** 
** RETURNS: Return value is of type void.
=======================================================================**/
int_32 app_get_rx_can_message(char *	packet)
{
	mbuf_hdr_t			*mbuf_ptr;
	int_32				ret;
   	
	/**-----------------------------------------
	** Get an Mbuf from the Rx buf queue
	**---------------------------------------------*/
	if((mbuf_ptr = (mbuf_hdr_t*)util_que_get(&rx_buf_q))!= NIL)
	{
		/**--------------------------------------------
		** Copy message from Mbuf to application data
		**------------------------------------------- */
		/*packet->length =  (unsigned_8)mbuf_ptr->len;
		packet->arbitration = (mbuf_ptr->type << 21);*/
		memcpy((unsigned_8*)packet, mbuf_ptr->data, 8);
		
		/**-----------------------------------
		** Put the Mbuf back to the free q 
		**-----------------------------------*/
		util_que_put(&mbuf_hdr_free_q, mbuf_ptr);

		ret = 0;

	}
	else
	{
		ret = -1;
	}
	return(ret);
		
}

boolean app_wait_rx_can_message(void)
{
	if(util_que_get(&rx_buf_q) == NIL)
	{
		return(TRUE);
	}
	else
	{
		return(FALSE);
	}
}

/******************************************************************************
FUNCTION NAME:  app_can_tx_callback_fn()

DESCRIPTION:	This is am application callback funciton which takes a buffer
				of characters and puts them into the CAN transmit queue.	 

METHOD:		The bytes of data/character can be placed into each CAN message.  If
			there are less then 8 bytes remaining pad the message with zero's. 

REENTRANCY:	None. 

NOTES: 	This will primary be call from inside the PCS library.

GLOBALS USED: 	UTIL_Lnk_t tx_buf_q - CAN tx queue buffer.
				UTIL_Lnk_t mbuf_hdr_free_q - CAN free memory queue buffer.

PARAMETER DESCRIPTION:	unsigned_8 * log - pointer to ascii character array.
						usnigned_32	 size - size of character array. 

RETURN VALUE:	-1 is unsuccesful, 0 is succesful 

*******************************************************************************/
int_32  app_can_tx_callback_fn(char * log, unsigned_32 size)
{
	mbuf_hdr_t	*mbuf_ptr;
   
	if((log == NIL) || (size == 0))
	{
		return -1;
	}

	
	while(size > 0)
	{
		
		mbuf_ptr = (mbuf_hdr_t *)util_que_get(&mbuf_hdr_free_q);
		if(mbuf_ptr == NIL)
		{
			return -1;
		}

		mbuf_ptr->len = 8;
		mbuf_ptr->type = 0x300;

		if(size < 8)
		{
			memcpy(mbuf_ptr->data, (unsigned_8*)log, size);	/* write only the amount we have */
			memset(&mbuf_ptr->data[size], 0x00, 8 - size);
			log += size;
			size -= size;
			
		}
		else
		{
			memcpy(mbuf_ptr->data, (unsigned_8*)log, 8);
			log += 8;
			size -= 8;
		}
		
		/* Stuff message into the CAN transmit queue */	
		util_que_put(&tx_buf_q, mbuf_ptr);
		
	}
	
	return 0;
}
		
