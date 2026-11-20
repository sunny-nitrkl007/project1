/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LPSCommonTypeDef.h
DESCRIPTION:
*******************************************************************************/
#ifndef __LPS_COMMON_TYPE_DEF_H__
#define __LPS_COMMON_TYPE_DEF_H__
/*******************************************************************************
** -- #Include's --
*******************************************************************************/

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

#ifndef NULL
	#define NULL  ( (void *) 0)
#endif

typedef unsigned short unsigned_16;
typedef signed short signed_16;
typedef unsigned int unsigned_32;
//typedef unsigned long long unsigned_64;
typedef signed int signed_32;
typedef signed long long signed_64;
typedef unsigned char unsigned_8;
typedef signed char signed_8;
typedef char boolean; // Conflict with cat_std_types.h which defines it as 'char' instead of 'unsigned char'
typedef float float_32;
typedef double double_64;
#endif /* #ifndef __LPS_COMMON_TYPE_DEF_H__ */
