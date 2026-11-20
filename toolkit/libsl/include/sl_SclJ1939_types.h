#ifndef SL_SCLJ1939_TYPES_H_
#define SL_SCLJ1939_TYPES_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. 2007 ALL RIGHTS RESERVED
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains externs for the blocks defining the J1939 Cat PPGN
message handlers.  These are static handlers that don't change based on model
configuration.

FILE NAME : sl_SclJ1939_types.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>
#include <scl_j1939.h>
#include <oelSignal__Status.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/* J1939 Override Data Structure */
typedef struct
{
    bool_least_t  active;
    uint32_t disable;
    uint8_t length;
} sl_SclJ1939_MaOvData_t;


/* J1939 Override Context Structure */
typedef struct
{
    uint8_t *pdata;
    sl_SclJ1939_MaOvData_t *data;
    uint8_t length;
} sl_SclJ1939_MaOvContext_t;


/* J1939 SPN Transmit Structure */
typedef struct
{
    scl_j1939_tx_msg_t *tx_msg_entry;
    uint8_t msg_length;
    uint16_t num_param;
    scl_j1939_param_tx_config_t *param;
} sl_SclJ1939_TxSpnConfig_t;

/* J1939 SPN Receive Structure */
typedef struct sl_SclJ1939_RxSpnConfig_s
{
    scl_j1939_rx_msg_t const * rx_msg_entry;
    uint8_t msg_length;
    uint16_t num_param;
    scl_j1939_param_rx_config_t *param;
} sl_SclJ1939_RxSpnConfig_t;

/* J1939 SPN Receive Structure for Receiving with fullname */
typedef struct sl_SclJ1939_RxSpnConfig_s_FullName
{
    scl_j1939_rx_msg_t const * rx_msg_entry;
    uint8_t msg_length;
    uint16_t num_param;
	scl_j1939_name_filter_t *NameFilter;
    scl_j1939_param_rx_config_t *param;
} sl_SclJ1939_RxSpnConfig_t_FullName;

/* J1939 SPN Handler Context */
typedef struct SpnHdlrContext_s
{
    void *value;	
    oelSignal__Status____t *status;
    uint8_t length; /* Bytes */       
} sl_SclJ1939_SpnHdlrContext_t;

/* J1939 SPN Handler Context which contain Numbits 
 This structure is similar to sl_SclJ1939_SpnHdlrContext_t with bits information.*/
typedef struct SpnHdlrContext_s_WB
{
    void *value;	
    oelSignal__Status____t *status;
    uint8_t length; /* Bytes:(1 or 2 or 4) Depends on the wordlength of the datatype*/
    uint8_t NumBits; /* Bits: Depends on the no.of.bits selected in the bit pattern */    
} sl_SclJ1939_SpnHdlrContext_WB_t;

/* J1939 SPN Handler Context */
 //This structure is similar to sl_SclJ1939_SpnHdlrContext_t with additional field to hold raw value..*/
typedef struct SpnHdlrContext_s_Raw
{
    void *value;	
	void *raw_value;
    oelSignal__Status____t *status;
    uint8_t length; /* Bytes */       
} sl_SclJ1939_SpnHdlrContext_Raw_t;

/* define an "alias" for the SPN handler context structure for backwards
   compatiblity */
typedef sl_SclJ1939_SpnHdlrContext_t sl_SclJ1939_TxSpnHdlrContext_t;

typedef struct SpnHdlrContext__func_s
{
    void *value;	
    oelSignal__Status____t *status;
    uint8_t length; /* Bytes */
    void (*context_function)(void);
} sl_SclJ1939_SpnHdlrContext_func_t;


//sl_SclJ1939_SpnHdlrContext_func_Raw_t:
//This is structure is similar to sl_SclJ1939_SpnHdlrContext_func_t., added one additional field to hold the raw data value.
typedef struct SpnHdlrContext__func_s_Raw
{
    void *value;
	void *raw_value;
    oelSignal__Status____t *status;
    uint8_t length; /* Bytes */
    void (*context_function)(void);
} sl_SclJ1939_SpnHdlrContext_func_Raw_t;

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SL_SCLJ1939_TYPES_H_ */
