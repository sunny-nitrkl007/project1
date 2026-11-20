/***********************************************************************************************************************
** COPYRIGHT (C) 2018 CATERPILLAR INC. ALL RIGHTS RESERVED.
** CATERPILLAR: CONFIDENTIAL YELLOW
************************************************************************************************************************
** FILE NAME: prod_core_packed_struct.h
** DESCRIPTION:
***********************************************************************************************************************/
#ifndef PROD_CORE_PACKED_STRUCT_H_
#define PROD_CORE_PACKED_STRUCT_H_

#if defined (__cplusplus)
extern "C"
{
#endif

/*******************************************************************************
** -- #Includes --
*******************************************************************************/
/*******************************************************************************
** -- #Defines, Structs, Typedefs, Enums --
*******************************************************************************/
#ifdef WIN32
    #define PROD_CORE_PACKED
    #define PROD_CORE_PRAGMA(X) _Pragma(#X)
    #define PROD_CORE_PRAGMA_PACK_PUSH(n)     PROD_CORE_PRAGMA(pack(push,n))
    #define PROD_CORE_PRAGMA_PACK_POP()       PROD_CORE_PRAGMA(pack(pop))
#else
    #define PROD_CORE_PACKED __attribute__((packed))
    #define PROD_CORE_PRAGMA_PACK_PUSH(n)
    #define PROD_CORE_PRAGMA_PACK_POP()
#endif
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

#if defined (__cplusplus)
}
#endif

#endif /* PROD_CORE_PACKED_STRUCT_H_ */
