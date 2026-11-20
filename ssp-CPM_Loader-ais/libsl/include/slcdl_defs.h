#ifndef SLCDL_DEFS_H_
#define SLCDL_DEFS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains datatypes needed for the Simulink CDL blocks.

FILE NAME : slcdl_defs.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>
#include <cdl2_defs.h>


/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/* SLCDL_CALC_DSI
 *   Takes the supplied oelSignal__Status input and converts it to a value
 *   containing the equivalent DSI value.  DSI values are contained in a
 *   reserved area of a data value.
 *
 * Inputs:
 *   oel_stat - oelSignal__Status value to be converted in to a DSI value
 *   type - Type of data that is contained in the dest_data_ptr:
 *          CDL2_U8_DSI, CDL2_I8_DSI, CDL2_U16_DSI, CDL2_I16_DSI,
 *          CDL2_U32_DSI, CDL2_I32_DSI
 *
 * Outputs:
 *   dest_data_ptr - Pointer to data of the type specified by: type
 */
#define SLCDL_CALC_DSI(dest_data_ptr, oel_stat, type)                         \
{                                                                             \
    uint8_t limited_dsi;                                                   \
    limited_dsi = (uint8_t) (((oel_stat)-1) <= 31 ? ((oel_stat)-1) : 31);  \
    switch (type)                                                             \
    {                                                                         \
        case CDL2_U8_DSI:                                                     \
            *((uint8_t *) (dest_data_ptr)) =                               \
                (uint8_t) (UINT8_MAX - 31 + limited_dsi);             \
            break;                                                            \
        case CDL2_I8_DSI:                                                     \
            *((int8_t *) (dest_data_ptr)) =                                    \
                (int8_t) (INT8_MIN + limited_dsi);                            \
            break;                                                            \
        case CDL2_U16_DSI:                                                    \
            *((uint16_t *) (dest_data_ptr)) =                              \
                (uint16_t) (UINT16_MAX - 31 + limited_dsi);           \
            break;                                                            \
        case CDL2_I16_DSI:                                                    \
            *((int16_t *) (dest_data_ptr)) =                                   \
                (int16_t) (INT16_MIN + limited_dsi);                          \
            break;                                                            \
        case CDL2_U32_DSI:                                                    \
            *((uint32_t *) (dest_data_ptr)) =                              \
                (uint32_t) (UINT32_MAX - 31 + limited_dsi);           \
            break;                                                            \
        case CDL2_I32_DSI:                                                    \
            *((int32_t *) (dest_data_ptr)) =                                   \
                (int32_t) (INT32_MIN + limited_dsi);                          \
            break;                                                            \
        default:                                                              \
            /* Unhandled size */                                              \
            return 0;                                                         \
    }                                                                         \
}

/* SLCDL_LIMIT_DSI
 *   Takes the supplied oelSignal__Status input and converts it to a value
 *   containing the equivalent DSI value.  DSI values are contained in a
 *   reserved area of a data value.
 *
 * Inputs:
 *   oel_stat - oelSignal__Status value to be converted in to a DSI value
 *   type - Type of data that is contained in the dest_ptr:
 *          CDL2_U8_DSI, CDL2_I8_DSI, CDL2_U16_DSI, CDL2_I16_DSI,
 *          CDL2_U32_DSI, CDL2_I32_DSI
 *
 * Outputs:
 *   dest_ptr - Pointer to data of the type specified by: type
 */
#define SLCDL_LIMIT_DSI(dest_ptr, src_ptr, type)                              \
{                                                                             \
    switch (type)                                                             \
    {                                                                         \
        case CDL2_U8_DSI:                                                     \
            *((uint8_t *) (dest_ptr)) =                                    \
                *((uint8_t *) (src_ptr)) > (UINT8_MAX - 32) ?         \
                (UINT8_MAX - 32) : *((uint8_t *) (src_ptr));          \
            break;                                                            \
        case CDL2_I8_DSI:                                                     \
            *((int8_t *) (dest_ptr)) =                                         \
                *((int8_t *) (src_ptr)) < (INT8_MIN + 32) ?                   \
                (INT8_MIN + 32) : *((int8_t *) (src_ptr));                    \
            break;                                                            \
        case CDL2_U16_DSI:                                                    \
            *((uint16_t *) (dest_ptr)) =                                   \
                *((uint16_t *) (src_ptr)) > (UINT16_MAX - 32) ?       \
                (UINT16_MAX - 32) : *((uint16_t *) (src_ptr));        \
            break;                                                            \
        case CDL2_I16_DSI:                                                    \
            *((int16_t *) (dest_ptr)) =                                        \
                *((int16_t *) (src_ptr)) < (INT16_MIN + 32) ?                 \
                (INT16_MIN + 32) : *((int16_t *) (src_ptr));                  \
            break;                                                            \
        case CDL2_U32_DSI:                                                    \
            *((uint32_t *) (dest_ptr)) =                                   \
                *((uint32_t *) (src_ptr)) > (UINT32_MAX - 32) ?       \
                (UINT32_MAX - 32) : *((uint32_t *) (src_ptr));        \
            break;                                                            \
        case CDL2_I32_DSI:                                                    \
            *((int32_t *) (dest_ptr)) =                                        \
                *((int32_t *) (src_ptr)) < (INT32_MIN + 32) ?                 \
                (INT32_MIN + 32) : *((int32_t *) (src_ptr));                  \
            break;                                                            \
        default:                                                              \
            /* Unhandled size */                                              \
            return 0;                                                         \
    }                                                                         \
}

/*MACRO:  SLCDL_QUAL_DATA_READ_STORAGE(uint16_t  MAX_ENTRIES)
//     This macro is used to define the storage variables for the
//     CAT Data Link qualified data read module.
//     
//     The storage area must be defined by the application so the
//     library module will not have to hard-code the sizes.
//     
//     MAX_ENTRIES should be a constant expression that evaluates
//     to the largest number of qualified data reads that can exist in
//     this application.  The application should insure that this value is
//     large enough.
//     
//     This macro defines the storage areas, and initializes them to
//     the correct value.
*/
#define SLCDL_QUAL_DATA_READ_STORAGE(MAX_ENTRIES)                            \
                                                                             \
     /*CAT Data Link Qualified Read Parameter Entry Array                    \
     //    This array holds pointers to all of the qualified read            \
     //    parameters initialized by this ECM.                               \
     //                                                                      \
     //    IMPORTANT NOTE:                                                   \
     //         This should be defined by the application.                   \
     //         This is required so that the application                     \
     //         may customize the library.                                   \
     */                                                                      \
     slcdl_qual_data_array_t  slcdl_qual_read_array[MAX_ENTRIES];            \
                                                                             \
     /*CAT Data Link Qualified Read Maximum Number Of Entries                \
     //     This variable contains the maximum number of qualified           \
     //     reads that will ever be supported by this ECM.                   \
     //                                                                      \
     //    IMPORTANT NOTE:                                                   \
     //         This should be defined by the application.                   \
     //         This is required so that the application                     \
     //         may customize the library.                                   \
     */                                                                      \
     const uint16_t        slcdl_qual_read_max_entries =                  \
                                        ( sizeof slcdl_qual_read_array /     \
                                          sizeof(slcdl_qual_data_array_t)    \
                                        )

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SLCDL_DEFS_H_ */
