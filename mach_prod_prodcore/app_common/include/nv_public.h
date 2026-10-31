/******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                       %%
*** %% COPYRIGHT (C) 2001 - 2014 CATERPILLAR INC. ALL RIGHTS RESERVED.       %%
*** %%                                                                       %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***  FILE NAME:
***     nv_public.h
***
***  DESCRIPTION:
***     This is the definition include file for the non-volatile module.
***     All of the contents in this file are intended for other tasks/modules
***     to use.
***
***     IMPORTANT NOTE:  All global variables should be considered read-only
***                      by any external module that accesses them.
***                      It is forbidden for any routines besides those
***                      local to this module to alter these variables.
***
******************************************************************************/

#ifndef NV_PUBLIC_H_
#define NV_PUBLIC_H_


/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#ifndef NVLIB_PUBLIC_H_
#include <nvlib_public.h>
#endif


/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/*Non-Volatile Application Type
//     This value indicates the type of software that is running
//     on the ECM.
*/

enum
{
     APPLICATION_PROGRAM_NVID            = (NVM_MIN_APP_DATA_ID + 1),
     EQUIPMENT_ID_NVID,
     MACHINE_SN_NVID,
     PRODUCT_ID_NVID,     
     SYNCLK_SMALL_CHANGE_NVID,
     SYNCLK_SIGNIFICANT_CHANGE_NVID,
     TOTAL_TATTLETALE_NVID,
     DTCSETUP_NVID,
     DEVELOPMENT_MODULE_NVID,
     SAMPLE_DEVELOP_NVID,
     RSTINFO_COREDUMP_OELUK_NVID,
     RSTINFO_COREDUMP2_OELUK_NVID,
     /*Implement subsystem NVIDs start at NVM_MIN_APP_DATA_ID + 10000 */
     /*Hystat    subsystem NVIDs start at NVM_MIN_APP_DATA_ID + 30000 */

     NVID_EEPROM_UNUSED                  = (NVM_MAX_APP_DATA_ID - 0)
};

/*****************************************************************************/
/*****                Non-Volatile Validation Utility                    *****/

#define NV_OK              0x00   /* NV Table OK                           */
#define NV_APP_NUM_ERROR   0x01   /* NV Table Application Number Mismatch  */
#define NV_SIGNATURE_ERROR 0x02   /* NV Table Signature Mismatch */
#define NV_VERSION_ERROR   0x04   /* NV Table Version Mismatch             */
#define NV_SIZE_ERROR      0x08   /* NV Table Size Mismatch                */
#define NV_CHECKSUM_ERROR  0x10   /* NV Table Checksum Mismatch            */

typedef struct
{
    unsigned_16 app_num;
    unsigned_16 version;
    unsigned_16 size;
} NVTableHeader_t;

typedef struct
{
    unsigned_16 checksum;
} NVTableFooter_t;

typedef struct
{
    union
    {
        unsigned_8  val;
        struct {
            unsigned_8           : 3;
            unsigned_8 cs        : 1;
            unsigned_8 size      : 1;
            unsigned_8 version   : 1;
            unsigned_8 signature : 1;
            unsigned_8 app_num   : 1;
        } bit;
    } error;
    unsigned_16 app_num;
    unsigned_16 version;
    unsigned_16 size;
    unsigned_16 checksum;
} NVTableValidate_t;

extern void nv_validate_tbl(unsigned_8 const * tbl_ptr,
                            NVTableValidate_t * validate_tbl_ptr
                           );

extern void nv_validate_checksum_only(unsigned_8 const * tbl_ptr,
                                      NVTableValidate_t * validate_tbl_ptr
                                     );


#endif /* NV_PUBLIC_H_ */
