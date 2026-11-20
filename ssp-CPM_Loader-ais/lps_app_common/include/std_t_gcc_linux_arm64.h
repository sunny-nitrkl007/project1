/*******************************************************************************
Copyright 2021 Caterpillar Inc.  All rights reserved.
--------------------------------------------------------------------------------

Filename:   std_t_gcc_linux_x86_64.h
Language:   C89
Template:   1.1.0

Summary
   Except for text and existing library functions these should be used for
   all variables and as primitives for new types.

Portability
   These definitions are compiler and target specific.  This defines portable
   types but the definitions are NOT portable.
   
   The int and uint types correspond to ISO/IEC 9899:1999 C.  For compilers
   that support this newer standard, all of these types should be defined
   here by a nested include of the standard header <stdint.h>.

   Where possible, the limits should be defined in terms of the standard limits
   from <limits.h>.

*******************************************************************************/

#ifndef STD_T_GCC_LINUX_X86_64_H_
#define STD_T_GCC_LINUX_X86_64_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <limits.h>
#include <stdint.h>

            /*
            BIG_ENDIAN or LITTLE_ENDIAN - BIG_ENDIAN is defined if most
            significant bytes are stored at lower addresses and LITTLE_ENDIAN
            if least significant bytes are at lower addresses.
            */

#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN
#endif 

            /*
            RIGHT_SHIFT_NEGATIVE_IS_DIVIDE - Defined if right shift of a
            negative integer is equivalent to a divide by 2.  If undefined,
            either use division or shift the absolute value.
            */

#define RIGHT_SHIFT_NEGATIVE_IS_DIVIDE


            /*
            ATOMIC_MAX_SIZE - Maximum integer size in bits that can be 
            transferred to or from memory as an atomic operation.
            */

#define ATOMIC_MAX_SIZE 32


            /*
            TRUE - symolic value for true

            FALSE - symbolic value for false

            bool_t - the type yielded by logical operators (i.e. int) 

            bool_least_t - the smallest integral type for storing a boolean
            value.
            
            NOTE: Since this is smaller than a bool_t, a typecast should
            be used in assignments to this type.  It is directly defined as
            a char because an int8_t may not be supported and an int_least8_t
            may be larger than a char on implementations that do not support
            a signed char.  Similarly for uint.  For this reason it is directly
            defined as a char and it is implementation dependent whether it is
            signed or unsigned. 
            */

#ifndef TRUE
#define	TRUE	1
#endif /* TRUE */
#ifndef FALSE
#define FALSE	0
#endif /* FALSE */
typedef int bool_t;
typedef char bool_least_t;

#ifdef __cplusplus
}
#endif

#endif
