#ifndef SL_SOCKET_TYPES_H_
#define SL_SOCKET_TYPES_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains datatypes needed for the Treck socket library apis used.

FILE NAME : sl_socket_types.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/

/* ===== Treck Error codes ==== */
enum socket_error_status_t {
    SL_TM_ENOERROR = 0,
    SL_TM_EBADF = 209,
    SL_TM_EINVAL = 222,
	SL_TM_EWOULDBLOCK = 235,
	SL_TM_EMSGSIZE = 240,
	SL_TM_ENOBUFS = 255,
	SL_TM_EHOSTUNREACH = 265
};
typedef enum socket_error_status_t socket_error_status_t;


/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SL_SOCKET_TYPES_H_ */
