/*****************************************************************************************************************
 Copyright 2016 Caterpillar Inc. All rights reserved.
------------------------------------------------------------------------------------------------------------------
File name: app_token_block0.c

Description: This file defines the application's code token block and corresponding file description block.

*****************************************************************************************************************/

/*****************************************************************************************************************
** -- #Include's --
*****************************************************************************************************************/
#include <hal_boot.h>
#include <oel_rtos.h>

/*****************************************************************************************************************
** -- Data Declarations --
*****************************************************************************************************************/

#ifdef BLOCK0_fl

HAL_BOOT_DEFINE_FDB_0(
    app_fdb,        /* name of file description block           */
    oel_sys_init,   /* application starting address             */
    1,              /* Enable unexpected reset checking        */
    1000,           /* max # unexpected resets before lockout   */
    0x40000000      /* 2^-30 S/bit for watchdog period          */
) ;

#else

HAL_BOOT_DEFINE_FDB_1(
    app_fdb,            /* name of the file description block       */
    oel_sys_init,       /* application starting address             */
    1,                  /* Enable unexpected reset checking        */
    1000,               /* max # unexpected resets before lockout   */
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

#elif __M32R__ 
#pragma SECTION C TOKEN_BLK

#elif defined (__CSMC__)
#pragma section const {app_token}

#elif defined (WIN32)
/* Application code token block */
boot_token_block_t app_token = 
{
   CODE_TOKEN,                   /* indicates application code */
   (void *)0x00000000, /* location of next possible token (not needed for WinCE) */
   (void *)0x00000000,   /* pointer to file description block (not needed for WinCE) */
   /* Initialize file data to FFs for now (will get set to app_filedata in hal_boot_init) */
   {
      0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   },
};
/* File data for application */
boot_filedata_t app_filedata = 
{
   /* extended file area number of this file (not needed for WinCE) */
   0x00000000,

   /* software part number of this file */
   { 10, "1234567-00", },

   /* software file identifier of this file */
   { 12, { 0x00, 0xAA, 0xBB, 0xCC, 0xDD, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, }, },

   /* service tool serial number (not needed for WinCE) */
   { 0, "", },

   /* datalink protocol used to program this file (not needed for WinCE) */
   BOOT_UNK,
};

#else
#pragma section app_token ".token" ".token" far-absolute
#pragma use_section app_token app_token
#endif /* __arm */

#endif /* __GNUC__ & __PPC__ */

#if (!defined(WIN32))
HAL_BOOT_DEFINE_TOKEN_BLOCK(app_token,app_fdb) ;
#endif
