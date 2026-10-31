/******************************************************************************
*** COPYRIGHT (C) 2010-2010 CATERPILLAR INC.   ALL RIGHTS RESERVED.
***
*** FILE:
***     comdlsleep_tables.h
***
*** DESCRIPTION:
***     This is the definition include file for the
***     Communication Data Link Sleep Logic.
***     All of the contents in this file are intended for other tasks/modules
***     to use.
***
***     IMPORTANT NOTE:  All global variables should be considered read-only
***                      by any external module that accesses them.
***                      It is forbidden for any routines besides those
***                      local to this module to alter these variables.
***
*** HISTORY:
*** Change 00  2010-08-05 (hoadlck)
***     Created.
******************************************************************************/
#ifndef COMDLSLEEP_TABLES_H_
#define COMDLSLEEP_TABLES_H_

#ifndef   COMDLSLEEP_PUBLIC_H_
#include <comdlsleep_public.h>
#endif
#ifndef   WRAPIT_PUBLIC_H_
#include <wrapit_public.h>
#endif


/*****************************************************************************/
/*****                              Logic                                *****/

/*Communication Data Link Sleep Table 00
//     This table is used for the following applications:
//          All
*/
extern const comdlsleep_cnfg_t      comdlsleep_table_00;
/*****************************************************************************/


/*****************************************************************************/
/*****                Module Public Constant Definitions                 *****/

/*Communication Data Link Sleep Module Loop Time In Nano-Seconds      */
#define COMDLSLEEP_NS_LPTIM     20000000

/*Communication Data Link Sleep Module Loop Time In Milli-Seconds     */
#define COMDLSLEEP_MS_LPTIM     (COMDLSLEEP_NS_LPTIM/1000000.0)

/*Communication Data Link Sleep Module Loop Time In Seconds           */
#define COMDLSLEEP_LPTIM        (COMDLSLEEP_NS_LPTIM/1000000000.0)

/*Communication Data Link Sleep Module Loop Time In Seconds * 2^20    */
#define COMDLSLEEP_HAL_LPTIM    ( (unsigned_32)(COMDLSLEEP_LPTIM*(1UL<<20)) )


/*MACRO:  unsigned_16 COMDLSLEEP_TIME(double  SETTING)
//BEFORE: Communication Data Link Sleep Time conversion macro from double
//        floating point expression to 16-bit unsigned value.
//
//        SETTING = a constant floating point expression that
//                  represents an time in seconds.
//
//                  SETTING cannot be a variable.
//                  The allowed range is as follows:
//                       SETTING >= 0.0  AND  SETTING <= 1310.7s
//AFTER:  Returns a constant expression that represents the
//        converted value as an unsigned_16 integer.
//        The input value has been rounded to give the closest possible
//        result to the specified SETTING input.
*/
#define COMDLSLEEP_TIME(SETTING)                                         \
        CONVERT_CONSTANT_DOUBLE_TO_16U_SCALE(SETTING, COMDLSLEEP_LPTIM)
/*****************************************************************************/

#endif /* COMDLSLEEP_TABLES_H_ */
