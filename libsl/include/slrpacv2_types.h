/******************************************************************************
*** FILE:
***	slrpacv2_types.h
***
*** COPYRIGHT NOTICE:
***	Copyright 2011.  Caterpillar Inc.  All Rights Reserved.
***
*** DESCRIPTION:
***	This is the definition include file for the Simulink defined enumeration type
***  RpacCmd_t (a pseudo enumeration)
******************************************************************************/
#ifndef SLRPACV2_TYPES_H_
#define SLRPACV2_TYPES_H_

enum {
  RpacCmd_t_Hold = 0,
  RpacCmd_t_Run = 1,
  RpacCmd_t_Stop = 2
};

/* Subclass of Simulink.IntEnumType, which Simulink thinks is always int32 */

#if defined (__CSMC__)
typedef signed long RpacCmd_t;
#else
typedef signed int RpacCmd_t;
#endif


#endif /* SLRPACV2_TYPES_H_ */
