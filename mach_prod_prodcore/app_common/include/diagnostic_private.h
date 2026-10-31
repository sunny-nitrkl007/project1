/******************************************************************************
*******************************************************************************
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%
*** %% COPYRIGHT (C) 2001-2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
*** %%     This work contains proprietary information which may constitute
*** %%     a trade secret and/or be confidential.  Copyright notice is
*** %%     precautionary only and does not imply publication.
*** %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
***  diagnostic_private.h
***
***  DESCRIPTION:
***     This is the private include file for the diagnostic module.
***     The contents of this file are intended only for the diagnostic
***     routines to use.
***
***     IMPORTANT NOTE:  The general application does not require the
***                      detailed information that is shown in this file.
***                      However, since C does not support data hiding very
***                      well, I have separated the C++ "private"
***                      definitions/structures/variables/prototypes and
***                      placed them in this file.
***
*******************************************************************************
******************************************************************************/

#ifndef DIAGNOSTIC_PRIVATE_H_
#define DIAGNOSTIC_PRIVATE_H_


/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#ifndef DIAGNOSTICLIB_PUBLIC_H_
#include <diagnosticlib_public.h>
#endif



/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/*Diagnostic Log Number
//     This is the number of entries reserved in the non-volatile log
//     to store diagnostic information.
*/
#define DIAGNOSTIC_NV_LOG_SIZE 40

/*Diagnostic Queue ID
//     This is the ID used for the queue to pass event activate/deactivate
//     information.
*/
#define DIAGNOSTIC_QUEUE_ID 1

/*Diagnostic Number
//     This is the maximum number of diagnostics that will be initialized.
*/
#define DIAG_NUM 260

/*Diagnostic Debounce Number
//     This is the maximum number of diagnostics that use the info lib's
//     debounce.
*/
#define DIAG_DEB_NUM 30

/*Diagnostic SHM size
//     Size of the SHM to be stored in the LOG, must be either 16 or 32
*/

#define DIAG_SHM 32

/*Diagnostic Queue Size
//     This is the maximum number of entries within the queue.  This value
//     sets up the number of events that can change state between successive
//     updates.
*/
#define DIAGNOSTIC_QUEUE_SIZE 35

/*Diagnosic Memory Usage
//     This is how much memory the info lib will need to allocate to
//     handle the desired number of diagnostics.
*/
#define DIAG_MEM_SIZE (DIAGNOSTIC_RUNTIME_MEM_SIZE(DIAG_NUM,DIAG_DEB_NUM))

/*Diagnostic Cache Usage
//     This is the size of the cache needed for non-volatile memory.
//     If you are letting the info lib handle the initializing and
//     writing of non-volatile memory ( which I recommend unless you
//     you want to use BBRAM ) then this number needes to be added
//     to DIAG_MEM_SIZE.
*/
#define DIAG_CACHE_SIZE ((DIAGNOSTIC_CACHE_MEM_SIZE(DIAGNOSTIC_NV_LOG_SIZE,DIAG_SHM)) \
                             + LOG_SIZEOF_NVM_SIGN )


#endif /* DIAGNOSTIC_PRIVATE_H_ */
