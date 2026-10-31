/******************************************************************************
**           COPYRIGHT (C) 1999-2005 CATERPILLAR INC. ALL RIGHTS RESERVED.
**            This work contains Caterpillar's proprietary information, which
**            may constitute a trade secret and/or be confidential.  Copyright
**            notice is precautionary only and does not imply publication.
-------------------------------------------------------------------------------
FILE NAME:      app_token_block0.c
DESCRIPTION:    This file defines the application's code token block and
                corresponding file description block.

Vamsi Putumbaka modified this file on 02/01/05 to enable unexpected reset 
checking.
******************************************************************************/

/******************************************************************************
** -- #Include's --
******************************************************************************/

#include <hal_boot.h>
#include <oel_rtos.h>
#include <platform_declaration.h>

/******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
******************************************************************************/


/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


/******************************************************************************
** --                            A5M4V1
******************************************************************************/


#ifdef A5M4V1
#ifdef BLOCK0_fl

HAL_BOOT_DEFINE_FDB_0(
    app_fdb,        /* name of file description block           */
    oel_sys_init,   /* application starting address             */
    1,              /* Enable unexpected reset checking        */
    10,             /* max # unexpected resets before lockout   */
    0x40000000      /* 2^-30 S/bit for watchdog period          */
) ;

#else

HAL_BOOT_DEFINE_FDB_1(
    app_fdb,            /* name of the file description block       */
    oel_sys_init,       /* application starting address             */
    1,                  /* Enable unexpected reset checking        */
    10,                 /* max # unexpected resets before lockout   */
    0x40000000,         /* 2^-30 S/bit for watchdog period          */
    0x0001              /* CAT After-Market ID                      */
) ;

#endif

/*
** The following pragmas force the application code token into the .token
** segment.  Then, the application code token will appear at the beginning 
** of the file area (as it must.)
*/
#if defined(__GNUC__) && defined(__PPC__)
/*
GCC uses data attributes to place data into a section.
The SECTION_TOKENBLOCK must only be defined when using GCC.
*/
#define SECTION_TOKENBLOCK __attribute__ ((section (".token")))

#else /* Not GCC for PPC. */

#ifdef __arm
#pragma arm section code = ".token", rodata = ".token"
#elif defined (__CSMC__)
#pragma section const {app_token}
#else
#pragma section app_token ".token" ".token" far-absolute
#pragma use_section app_token app_token
#endif /* __arm */

#endif /* __GNUC__ & __PPC__ */

HAL_BOOT_DEFINE_TOKEN_BLOCK(app_token,app_fdb) ;
#endif




/******************************************************************************
** --                            A4M1V2
******************************************************************************/


#ifdef A4M1V2

#include <boot_brc_defs.h>

/******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
******************************************************************************/

/* UNCOMMENT THIS LINE IF YOU WANT TO USE boot_file_description_block0_t
   description block type, otherwise you get boot_file_description_block1_t
   which includes aftermarket id content. */
#define BLOCK0_fl


#ifdef BLOCK0_fl

HAL_BOOT_DEFINE_FDB_0(
    app_fdb,        						/* name of file description block           */
    oel_sys_init,   						/* application starting address             */
    BOOT_BRC_ENABLE_UNEXPECTED_RST_CHK,     /* disable unexpected reset checking        */
    10,           							/* max # unexpected resets before lockout   */
    0x40000000      						/* 2^-30 S/bit for watchdog period          */
) ;

#else

HAL_BOOT_DEFINE_FDB_1(
    app_fdb,            					/* name of the file description block       */
    oel_sys_init,       					/* application starting address             */
    BOOT_BRC_ENABLE_UNEXPECTED_RST_CHK,     /* disable unexpected reset checking        */
    10,               						/* max # unexpected resets before lockout   */
    0x40000000,         					/* 2^-30 S/bit for watchdog period          */
    0x0001              					/* CAT After-Market ID                      */
) ;

#endif

/*
** The following pragmas force the application code token into the .token
** segment.  Then, the application code token will appear at the beginning 
** of the file area (as it must.)
*/
#pragma section app_token ".token" ".token" far-absolute
#pragma use_section app_token app_token

HAL_BOOT_DEFINE_TOKEN_BLOCK(app_token,*(void*)&app_fdb) ;

#endif
