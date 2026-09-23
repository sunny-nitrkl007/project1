/*******************************************************************************
 ***
 *** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 *** %%                                                                        %%
 *** %%  COPYRIGHT (C) 2013-2016 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
 *** %%      This work contains proprietary information which may              %%
 *** %%      constitute a trade secret and/or be confidential.                 %%
 *** %%                                                                        %%
 *** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 **
 *
 * FILE NAME: app_can_init.c
 *
 * DESCRIPTION: HAL CAN Interface to j1939 limited support version
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
#ifndef __APP_CAN_INIT_H__
#include "app_can_init.h"
#endif

#ifndef   STD_TYPES_H_
#include <std_types.h>
#endif

#include <hal_canv3_client.h>

#include <oel_rtos_posix.h>
boolean canBflag = FALSE;
static const oel_rtos_resource_pi_vconfig_t resource_hal_canv3_vconfig = OEL_RTOS_RESOURCE_PI_VCONFIG();

const oel_rtos_resource_config_t *app_hal_canv3_resource_config = OEL_BASE(&resource_hal_canv3_vconfig);


static const oel_rtos_resource_pi_vconfig_t app_scl_j1939_semaphore_vconfig = OEL_RTOS_RESOURCE_PI_VCONFIG();


const scl_j1939_config_t app_scl_j1939_config =
{
            OEL_BASE(&app_scl_j1939_semaphore_vconfig),
            TRUE,
            FALSE
};
/* Stores the j1939 link information
// This is stored here because we need
// to change the tx msg control byte
// from within retarder main
 */
scl_j1939_link_t Ph_Link_app;


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


/*HAL CAN V3 Packet & Packet Reader Heap Limits
//     This operation pre-allocates memory in heap for the number of
//     packet objects and packet reader objects allowed.
//
//     It also limits the memory that can be allocated to this amount.
//
//     If we don't do this, then the HAL CANV3 layer will continue to
//     allocate memory every time a new packet occurs.  This can cause
//     us to use all of the available heap space during times when
//     we would rather the packets just be lost (e.g. initialization).
//
//     The pools of packets are used for transmit as well as receive.
//
//     Each time a packet comes in, a packet reader is associated with
//     that packet for each HAL CANV3 client that exists in the system.
//     For this application, here is a list of the clients:
//       *  SCL J1939 (Port A/B) (Extended Ids Only)
//       *  SCL CCP              (Extended Ids Only)
//       *  Network Module       (Standard Ids Only)
//       *  Bridge (Port A/B)    (Extended Ids Only)
//     We need to provide a packet reader for the worst case.  But
//     there is filtering available in the HALCANV3 port update function, so
//     some packets will never get attached to the client, if the client
//     does not care about it.
//
//     Here is a rough estimate of the limits required:
//                   +--------+--------+--------+--------+
//                   |    Transmit     |    Receive      |
//                   | 29-bit | 11-bit | 29-bit | 11-bit |
//          +--------+--------+--------+--------+--------+
//          | Port A |    6   |    0   |    6   |    0   |
//          | Port B |    1   |    0   |    4   |    1   |
//          +--------+--------+--------+--------+--------+
//     If we assume that all of these messages go out every
//     loop (they don't), and we use an outrageous safety
//     factor (times 2), then we come up with the values below.
//
//     We also need to provide a little margin for transmit messages
//     during initialization.  The address claimed message can get
//     choked out if all of the packets get used up because of the
//     other stuff on the link.  Reserve 20 packets for this (usually 10
//     pre-allocation errors end up occuring).  Note that we don't need
//     Packet Readers for these packets, as they are only used for transmit.
 */


/*SCL J1939 Maximum Number Of Nodes
//     This operation reserves memory for the J1939 Name/Address Table.
//     In order for the address claim process to work properly, there
//     needs to be space reserved in this list so that the worst case
//     number of nodes can be stored.  
//
 */

#define SCL_J1939_MAX_PORTA_NODE_NUMBER  ( 2+18 )
#define SCL_J1939_MAX_PORTB_NODE_NUMBER  ( 2+18 )

volatile hal_canv3_port_t* P_port;


/* DM13 app callback to verify whether it is safe to stop broadcast */
boolean_t app_j1939_is_sbcast_allowed_cb(void)
{
   return TRUE;
}


void app_can_init(void)
{

    //bool_t can_init = TRUE;
    bool_t portAtch = FALSE;


    switch(base_can_port)
    {
    case 0:

        P_port = HAL_CANV3_PORT_01;//HAL_J1939V2_PORT_01;
        break;
    case 1:
        P_port = HAL_CANV3_PORT_02;//HAL_J1939V2_PORT_02;
        break;
    default:
        P_port = HAL_CANV3_PORT_02;//HAL_J1939V2_PORT_02;
        break;
    }


    boolean a = hal_canv3_port_init( HAL_CANV3_PORT_02 );
    printf("Initialized CAN B port %d\n",a);
    hal_canv3_port_set_resource(
            P_port,
            app_hal_canv3_resource_config);

    /*This operation pre-allocates memory in heap for the number of
   //packet objects specified.
   //
   //It also limits the memory that can be allocated to this amount.
   //
   //If we don't do this, then the HAL CANV3 layer will continue to
   //allocate memory every time a new packet occurs.  This can cause
   //us to use all of the available heap space during times when
   //we would rather the packets just be lost (e.g. initialization).
   //
   //This pool of packets are used for transmit as well as receive.
     */

    hal_canv3_pckt_prealloc_objects(P_port, 150);

    /*This operation pre-allocates memory in heap for the number of
   //packet reader objects specified.
   //
   //It also limits the memory that can be allocated to this amount.
   //
   //If we don't do this, then the HAL CANV3 layer will continue to
   //allocate memory every time a new packet occurs.  This can cause
   //us to use all of the available heap space during times when
   //we would rather the packets just be lost (e.g. initialization).
   //
   //Each time a packet comes in, a packet reader is associated with
   //that packet for each HAL CANV3 client that exists in the system.
     */

    hal_canv3_preader_prealloc_objects(P_port, 180);

    //printf("preader prealloc_objects CLIENT VAL :%d\n",client);

    client = hal_canv3_client_create();
    if(client != NULL)
    printf("client\n");
    hal_canv3_client_init(client);

    //uint_least8_t app_hal_canv3_owner;
    hal_canv3_port_attach_client2(HAL_CANV3_PORT_02, client);

    portAtch = hal_canv3_port_acquire_owner(HAL_CANV3_PORT_02, &app_hal_canv3_owner);
    printf("after acq owner:%d\n",portAtch);

    //hal_canv3_port_close(HAL_CANV3_PORT_02, &app_hal_canv3_owner);
    portAtch = hal_canv3_port_set_btrt(HAL_CANV3_PORT_02, &app_hal_canv3_owner,250000);
    printf("after set btrt: %d\n",portAtch);
    hal_canv3_port_open(HAL_CANV3_PORT_02, &app_hal_canv3_owner);
    hal_canv3_port_set_slew(HAL_CANV3_PORT_02,HAL_CANV3_PORT_HIGH_SPEED);


    canBflag = TRUE;


    return;
}

