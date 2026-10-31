/*******************************************************************************
 ** COPYRIGHT (C) 2009 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:  sl_ismdsp.h
DESCRIPTION:  Support the TI DSP on the A4:ISM


*******************************************************************************/
#ifndef SL_ISMDSP_H_
#define SL_ISMDSP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/
#include "std_t.h"

/*******************************************************************************
 ** -- #Define, Struct's, Typedef's, Enum's --
 *******************************************************************************/

/* Enumeration used to track the state of the DSP */
typedef enum
  {
    SL_ISMDSP_RESET_PREINIT,
    SL_ISMDSP_RESET_SEQ_START,
    SL_ISMDSP_RESET_SEQ_STEP2,
    SL_ISMDSP_RESET_SEQ_STOP,
    SL_ISMDSP_RESET_DELAY,
    SL_ISMDSP_RESET_DONE,
    SL_ISMDSP_RESET_FAIL
  };

/*******************************************************************************
 ** -- Function Prototypes --
 *******************************************************************************/

/*******************************************************************************
  FUNCTION NAME:    sl_ismdsp_reset
  DESCRIPTION:
    In the A4:ISM the DSP is slave to the MPC5xx, which controls the DSP's
    reset lines.  This function properly brings the DSP out of reset.  Others
    can check the state of the process through the global variable
    sl_ismdsp_reset_state.
    
  PARAMETER DESCRIPTION:
    loops_for_300ms_delay - number of calls to pause to ensure a 300ms delay
                            caller must calculate this based on the rate at
                            which this is called
  RETURN VALUE: none
  REENTRANCY: not reentrant
  GLOBALS USED: sl_ismdsp_reset_state
********************************************************************************/
void sl_ismdsp_reset(const uint_least16_t loops_for_300ms_delay);

/*******************************************************************************
 ** -- Data Definitions
 *******************************************************************************/

/* Global interface to read the current ISM reset state */
extern uint_least8_t sl_ismdsp_reset_state;

#ifdef __cplusplus
}
#endif
#endif /* SL_ISMDSP_H_ */
