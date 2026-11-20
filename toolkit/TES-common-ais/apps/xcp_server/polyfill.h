/*******************************************************************************
** COPYRIGHT (C) 2005,2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar's proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  polyfill.h
DESCRIPTION:
*******************************************************************************/
#ifndef POLYFILL_H_
#define POLYFILL_H_

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#ifndef BOOL
typedef int BOOL; // boolean
#endif

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#ifndef NULL
    #define NULL 0
#endif

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* POLYFILL_H_ */
