/******************************************************************************************************************
 Copyright 2012 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: scl_adt_j1939_tune.h

Description:
******************************************************************************************************************/
#ifndef SCL_ADT_J1939_TUNE_H_
#define SCL_ADT_J1939_TUNE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define SCL_ADT_J1939_MAX_LINK_COUNT    10
#define SCL_ADT_J1939_MAX_ECM_COUNT     10
#define SCL_ADT_J1939_MAX_SERVER_COUNT  15
#define SCL_ADT_J1939_MAX_SERVER_GRP_COUNT 50
#define SCL_ADT_J1939_MAX_CLIENT_COUNT 15
#define SCL_ADT_J1939_MAX_CLIENT_GRP_COUNT 50

/*  FIFO will consume 7*(SCL_ADT_J1939_MAX_SRV_GRP_FIFO + 1) bytes of memory. 
    Let us assume if FIFO size is 6 and 5 PIDs are updating very frequently(every 10 or 20 ms), 
    FIFO overflow may occur. So there may not be enough space for the upcoming
    updates. Hence Configure FIFO size considering PID update rate for each client*/
#define SCL_ADT_J1939_MAX_SRV_GRP_FIFO 6

#ifdef __cplusplus
}
#endif
#endif /* #ifndef SCL_ADT_J1939_TUNE_H_ */
