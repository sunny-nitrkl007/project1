/******************************************************************************
**
*** 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%
*** %%
*** %% COPYRIGHT (C) 2013 CATERPILLAR INC. ALL RIGHTS RESERVED.
*** %%     This work contains proprietary information which may
*** %%     constitute a trade secret and/or be confidential.
*** %%     Copyright notice is precautionary only and does not
*** %%     imply publication.
*** %%
*** 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%
**
*** FILE:
***     bdt_lib.h
***
*** DESCRIPTION:
***     	   This is the BDT wrapper functions library include file
***
******************************************************************************/
/******************************************************************************
***
***    External function prototypes, data, & symbols
***    -- #Include's --
***
******************************************************************************/
#ifndef __BDT_LIB_H__
#define __BDT_LIB_H__

#ifndef STD_TYPES_H_
#include <std_types.h>
#endif

#ifndef BDT_PROTO_H_
#include <bdt_proto.h>
#endif


/******************************************************************************
***
***    Constants defined for this file
***    -- #Define's --
***
******************************************************************************/
/* This macro is used to initialize the BDT_Cnfg_t structure */
#define BDT_CONFIG_INIT(	NUMRXCON,  NUMTXCON,		\
							RXBUFSIZE, TXBUFSIZE,		\
							EXECPRDMS,	                \
							DTYPE_MAX_COUNT,			\
							DL_COUNT                )	\
{													    \
	(NUMRXCON),									        \
	(NUMTXCON),											\
	(RXBUFSIZE),										\
	(TXBUFSIZE),									    \
	(EXECPRDMS),                                        \
	(DTYPE_MAX_COUNT),									\
    (DL_COUNT),                         				\
}

/******************************************************************************
***
***    Data types defined for this file
***    -- Struct's, Typedef's, Enum's --
***
******************************************************************************/

typedef struct 
{

	unsigned_8	NumRxCon;		/* Max Number of Recieve Connections to process at a time */
	unsigned_8	NumTxCon;		/* Max Number of Transmit Connections to process at a time */
	unsigned_16	RxBufSize;		/* Max Recieve Buffer Size */
	unsigned_16 TxBufSize;		/* Max Transmit Buffer Size */
	unsigned_16 exec_prd_ms;	/* Execution Period (ms) */
	unsigned_16	dt_max_count;	/* Max Number of Application BDT Data Types */
	
	unsigned_8 dl_count;	    /* No.of DataLink Support */

} BDT_Cnfg_t;


/******************************************************************************
***
***    File scope functions defined for this file
***    -- Function Prototypes --
***
******************************************************************************/
void bdt_lib_init( BDT_Cnfg_t *c );
void bdt_lib_main( const BDT_Cnfg_t *c );

/******************************************************************************
***
***    File scope symbols defined for this file
***    -- Symbols --
***
******************************************************************************/

/******************************************************************************
***
***    Global data symbols defined in this file
***    -- Global Symbols --
***
******************************************************************************/



#endif /* __BDT_LIB_H__ */


