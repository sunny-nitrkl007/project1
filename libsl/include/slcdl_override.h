#ifndef SLCDL_OVERRIDE_H_
#define SLCDL_OVERRIDE_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains definitions needed for the cdl override component.

FILE NAME : slcdl_override.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>
#include "..\src\lib\sl_cdl\slcdl_override_private.h"

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/*MACRO:  SLCDL_OVERRIDE_REPORT_STATUS(slcdl_Override_t *OVERRIDE_PTR)
//BEFORE: SLCDL_OVERRIDE_PTR must point to a properly initialized structure
//        of type slcdl_Override_t.
//AFTER:  Returns an uint8_t value that indicates if the override for
//        this specific parameter is active or not.
//        Returns non-zero, if the override is active.
//        Returns zero, if the override is in-active.
*/
#define   SLCDL_OVERRIDE_REPORT_STATUS(OVERRIDE_PTR)                          \
                               ( ((OVERRIDE_PTR)->override_status != 0) &&    \
                                 ((OVERRIDE_PTR)->disallow_status == 0)       \
                               )


/*MACRO:  OVERRIDE_REPORT_DISALLOW_STATUS(slcdl_Override_t *OVERRIDE_PTR)
//BEFORE: This routine returns the current value of the override disallow
//        status.
//        OVERRIDE_PTR = pointer to a properly initialized structure
//                       of type slcdl_Override_t
//AFTER:  If non-zero is returned, the override has been forced inactive.
//             The actual override parameter(as is available over the data
//             link) will still be set until the override module main
//             routine has a chance to run and update the status.
//        If zero is returned, the override is not locked out.
//             It may go active at any time, or it might be active right now.
*/
#define   SLCDL_OVERRIDE_REPORT_DISALLOW_STATUS(OVERRIDE_PTR)                 \
                                           ( (OVERRIDE_PTR)->disallow_status )


/*MACRO:  SLCDL_OVERRIDE_UPDATE_DISALLOW_STATUS(slcdl_Override_t *OVERRIDE_PTR,
//                                        uint8_t  DISALLOW_STATUS
//                                       )
//BEFORE: This routine updates the override disallow status.
//        SLCDL_OVERRIDE_PTR = pointer to a properly initialized structure
//                       of type slcdl_Override_t
//        SLCDL_DISALLOW_STATUS = desired status of override disallow
//AFTER:  Returns DISALLOW_STATUS.
//        If DISALLOW_STATUS is non-zero, the override is forced inactive.
//             The actual override parameter(as is available over the data
//             link) will still be set until the override module main
//             routine has a chance to run and update the status.
//        If DISALLOW_STATUS is zero, the override is the same state that
//             it was before.
*/
#define   SLCDL_OVERRIDE_UPDATE_DISALLOW_STATUS(OVERRIDE_PTR,                 \
                                          DISALLOW_STATUS                     \
                                         )                                    \
                         ( (OVERRIDE_PTR)->disallow_status = DISALLOW_STATUS )


/*MACRO:  SLCDL_OVERRIDE_GET_U8_PARAMETER(uint8_t    U8_PARAMETER)
//BEFORE: This routine reads an unsigned  8-bit integer override parameter.
//        U8_PARAMETER  = unsigned  8-bit override data link parameter
//                        Assumes that it is defined according to the CAT
//                        data link standard(i.e. the highest bit indicates
//                        if the override is commanded on, and the other
//                        lower bits indicate the override value).
//AFTER:  Returns the value of the override parameter with all override
//        command information removed.
//        NOTE:  The user must check to see if the override is active
//               before using the value returned by this macro.
//               To determine if the override is active or not, the macro
//               SLCDL_OVERRIDE_REPORT_STATUS() must be used.
//               The value returned by this macro indicates the desired
//               override value(if the override is currently active).
*/
#define   SLCDL_OVERRIDE_GET_U8_PARAMETER(U8_PARAMETER)                       \
               ( ((uint8_t)U8_PARAMETER) & ~SLCDL_OVERRIDE_PARAMETER_U8_MASK )


/*MACRO:  SLCDL_OVERRIDE_GET_U16_PARAMETER(uint16_t  U16_PARAMETER)
//BEFORE: This routine reads an unsigned 16-bit integer override parameter.
//        U16_PARAMETER = unsigned 16-bit override data link parameter
//                        Assumes that it is defined according to the CAT
//                        data link standard(i.e. the highest bit indicates
//                        if the override is commanded on, and the other
//                        lower bits indicate the override value).
//AFTER:  Returns the value of the override parameter with all override
//        command information removed.
//        NOTE:  The user must check to see if the override is active
//               before using the value returned by this macro.
//               To determine if the override is active or not, the macro
//               SLCDL_OVERRIDE_REPORT_STATUS() must be used.
//               The value returned by this macro indicates the desired
//               override value(if the override is currently active).
*/
#define   SLCDL_OVERRIDE_GET_U16_PARAMETER(U16_PARAMETER)                     \
               ((uint16_t)( ((uint16_t)U16_PARAMETER) & ~SLCDL_OVERRIDE_PARAMETER_U16_MASK ))


/*MACRO:  SLCDL_OVERRIDE_GET_U32_PARAMETER(uint32_t  U32_PARAMETER)
//BEFORE: This routine reads an unsigned 32-bit integer override parameter.
//        U32_PARAMETER = unsigned 32-bit override data link parameter
//                        Assumes that it is defined according to the CAT
//                        data link standard(i.e. the highest bit indicates
//                        if the override is commanded on, and the other
//                        lower bits indicate the override value).
//AFTER:  Returns the value of the override parameter with all override
//        command information removed.
//        NOTE:  The user must check to see if the override is active
//               before using the value returned by this macro.
//               To determine if the override is active or not, the macro
//               SLCDL_OVERRIDE_REPORT_STATUS() must be used.
//               The value returned by this macro indicates the desired
//               override value(if the override is currently active).
*/
#define   SLCDL_OVERRIDE_GET_U32_PARAMETER(U32_PARAMETER)                     \
               ( ((uint32_t)U32_PARAMETER) & ~SLCDL_OVERRIDE_PARAMETER_U32_MASK )


/*MACRO:  uint8_t SLCDL_OVERRIDE_INTERLOCK_MID()
//BEFORE: This routine returns the Override Interlock MID.
//AFTER:  Returns the the MID of the module that last wrote to
//        the override interlock.
*/
#define  SLCDL_OVERRIDE_INTERLOCK_MID                                        \
                           (                                                 \
                             (slcdl_override_interlock_status == SLCDL_OVERRIDE_ENABLED) \
                             ?                                               \
                             slcdl_override_interlock_mid : 0                      \
                           )

/*MACRO:  SLCDL_OVERRIDE_STORAGE(uint16_t MAX_OVERRIDES)
//     This macro is used to define the storage variables for the
//     override module.
//
//     The storage area must be defined by the application so the
//     library module will not have to hard-code the sizes.
//
//     MAX_OVERRIDES should be a constant expression that evaluates to the
//     largest number of overrides that can exist in this application.
//     The application should insure that this value is large enough.
//
//     This macro defines the storage areas, and initializes them to
//     the correct value.
*/
#define SLCDL_OVERRIDE_STORAGE(MAX_OVERRIDES)                                 \
                                                                              \
     /*Override Table                                                         \
     //     This array of structures is used to store information about       \
     //     every possible override that could be used in the application.    \
     //     Each element in this array points to the override information     \
     //     for this parameter.                                               \
     */                                                                       \
     slcdl_OverrideEntry_t  slcdl_override_table[MAX_OVERRIDES];              \
                                                                              \
     /*Override Table Maximum Number Of Entries                               \
     //     This is the largest number of overrides that can be               \
     //     serviced by the override module.                                  \
     //     This is an upper limit on the number of possible overrides in     \
     //     the whole application.                                            \
     //     This number should be at least as big as the total number of      \
     //     overrides your control box could ever have.  You might want       \
     //     to set it just a little bit bigger, to allow room for expansion.  \
     */                                                                       \
     uint16_t slcdl_override_table_max_entries = (                         \
                                                sizeof slcdl_override_table / \
                                                sizeof(slcdl_OverrideEntry_t) \
                                              )

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/
void
slcdl_override_add_entry(register slcdl_OverrideConstants_t const *override_constants_ptr);
/*BEFORE: This function is used to make an override be under the control
//        of the override module.
//        override_constants_ptr should be a pointer to a properly
//             initialized OverrideConstants_t structure.
//        override_constants_ptr->pid
//             The PID of the parameter to override.
//        override_constants_ptr->tx_handler
//             Pointer to the read handler function for this
//             override parameter.
//             This handler should be able to use the data contained
//             in override_constants_ptr->tx_pie to send the parameter
//             out on the data link.
//        override_constants_ptr->tx_pie
//             Transmit parameter information entry.
//             override_constants_ptr->tx_pie.len
//                  Length of the parameter data.
//             override_constants_ptr->tx_pie.pdata
//                  Pointer to the parameter data.
//        override_constants_ptr->wr_handler
//             Pointer to the write handler function for this
//             override parameter.
//             This handler should be able to use the data contained
//             in override_constants_ptr->wr_pie to check to see if
//             the override is allowed to be active, and copy data from
//             the internal link area to the override parameter.
//        override_constants_ptr->wr_pie
//             Write parameter information entry.
//             override_constants_ptr->wr_pie.len
//                  Length of the parameter data.
//             override_constants_ptr->wr_pie.pdata
//                  Pointer to the parameter data.
//             override_constants_ptr->wr_pie.override_ptr
//                  Pointer to an un-initialized or an initialized
//                  override.
//AFTER:  Adds support for the indicated override.  Tells the
//        override module about this specific override, and places it
//        under control of the override module.
//        If the structure pointed to by
//             override_constants_ptr->wr_pie.override_ptr was previously
//             initialized, then the function returns without changing
//             anything.
//        If there is not room for another entry in the override module,
//             then the function will return.  The structure pointed to
//             by override_constants_ptr->wr_pie.override_ptr will be
//             forced to the uninitialized state.
//        Otherwise, support for this override will be completed.
//             The structure pointed to by
//             override_constants_ptr->wr_pie.override_ptr will be
//             initialized, and may now be used by the caller to
//             determine the state of the override.
*/
/*****************************************************************************/



/*****************************************************************************/
/*****                 Module Public Function Prototypes                 *****/
void
slcdl_override_init(void);
/*BEFORE: Assumes that static variables, global variables, and the operating
//        system have all been initialized.  However, tasking has not started
//        yet, and interrupts are still disabled.
//        This routine should only be called one time upon powerup.
//AFTER:  The override module powerup initializations have been completed.
*/

void
slcdl_override_main(void);
/*BEFORE: Assumes that the module initialization function has
//        already been called before this routine executes.
//        This routine should be called periodically by the calling task.
//AFTER:  The activities of the override module have been serviced
//        for this loop.
*/
/*****************************************************************************/



/******************************************************************************
** -- Data Declarations --
******************************************************************************/

#endif /* SLCDL_OVERRIDE_H_ */


