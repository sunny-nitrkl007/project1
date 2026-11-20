/*******************************************************************************
** COPYRIGHT (C) 2002 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar’s proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  std_t_gcc_cygwin.h
DESCRIPTION:  standard types

   Except for text and existing library functions these should be used for
   all variables and as primitives for new types.

   NOTES:
   
   These definitions are compiler and target specific.  This defines portable
   types but the definitions are NOT portable.
   
   The int and uint types correspond to ISO/IEC 9899:1999 C.  For compilers
   that support this newer standard, all of these types should be defined
   here by a nested include of the standard header <stdint.h>.

   Where possible, the limits should be defined in terms of the standard limits
   from <limits.h>.

*******************************************************************************/
#ifndef STD_T_GCC_CYGWIN_H_
#define STD_T_GCC_CYGWIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#ifdef __cplusplus
#ifndef CSTDDEF_
#  include <cstddef>
#endif
#else
#ifndef STDDEF_H_
#  include <stddef.h>
#endif
#endif

#ifndef LIMITS_H_
#include <limits.h>
#endif

#include <stdint.h>

#include <sys/types.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

            /*
            BIG_ENDIAN or LITTLE_ENDIAN - BIG_ENDIAN is defined if most
            significant bytes are stored at lower addresses and LITTLE_ENDIAN
            if least significant bytes are at lower addresses.
            */

/* #define LITTLE_ENDIAN */


            /*
            RIGHT_SHIFT_NEGATIVE_IS_DIVIDE - Defined if right shift of a
            negative integer is equivalent to a divide by 2.  If undefined,
            either use division or shift the absolute value.
            */

#define RIGHT_SHIFT_NEGATIVE_IS_DIVIDE


            /*
            ATOMIC_MAX_SIZE - Maximum integer size in bits that can be transferred
            to or from memory as an atomic operation.
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

#define  TRUE  1
#define FALSE  0

typedef int bool_t;
typedef char bool_least_t;


            /*
            int_leastN_t - smallest signed integer types with at least N bit
            
            uint_leastN_t - smallest unsigned integer types with at least N bits
            
            int_fastN_t - fastest signed integer types with at least N bit
            
            uint_fastN_t - fastest unsigned integer types with at least N bits
            
            intN_t - signed integer types with exactly N bit (read NOTES!!!)
            
            uintN_t - unsigned integer types with exactly N bits (read NOTES!!!)
                        
            NOTES:

            optional types - The intN_t, uintN_t and all 64 bit types may not be
            available on all targets.  The corresponding limits will only be
            defined if it is available.  Portable code must test and use conditional
            code to handle unavailability of a type.

            portability - the non-64 bit, int_leastN_t, uint_leastN_t, int_fastN_t,
            and uint_fastN_t are available on all targets and are the preferred types.
            The intN_t and uintN_t are only necessary for modulo arithmatic and mapping
            to device or data link message structure.  These are inherintly non-portable
            and conditional code should be used to handle inplementation dependent
            variation.

            down-casting - A type cast must be used when assigning to any type that COULD
            have a more limited numeric range on any target.  Other constraints or checking
            may be necessary to ensure that significant bits are not lost.  Type cast the
            following assignments:

               any int or uint to smaller N value
               any uint to int of same N value
               any int_fast_N_t to int_leastN_T or intN_t of same N
               any uint_fast_N_t to uint_leastN_T or uintN_t of same N

            If available, the intN_t will be identical to int_leastN_t and uintN_t will
            be identical to uint_leastN_t.  No casting is necessary between these types
            with the same N value.
            */


#ifdef __cplusplus
}
#endif
#endif /* STD_T_GCC_CYGWIN_H_ */
