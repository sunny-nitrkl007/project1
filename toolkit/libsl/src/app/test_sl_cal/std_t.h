/*******************************************************************************
** COPYRIGHT (C) 2002-2006 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar’s proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  std_t.h
DESCRIPTION:  standard types

   Except for text and existing library functions these should be used for
   all variables and as primitives for new types.

   NOTES:
   
   These definitions are compiler and target specific.  This defines portable
   types but the definitions are NOT portable.  Based on compiler pre-defined
   macros, this includes the specific header for the compiler and target.
   This header and the standard type names should be used for all targets.

*******************************************************************************/
#ifndef STD_T_H_
#define STD_T_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

            /*
            NULL - C and C++ specify that NULL is defined in standard headers
            <stddef.h> and <cstddef> respectively.  The C++ definition can
            differ from the C definition and is implementation specific.
            To avoid eclipsing the standard definition, it MUST be defined
            by including the standard definition.
            */

#ifdef __cplusplus
#ifndef CSTDDEF_
#  include <cstddef>
#endif
#else
#ifndef STDDEF_H_
#  include <stddef.h>
#endif
#endif

#if defined(_MRI) && defined(_CPU32)
#ifndef STD_T_MRI_CPU32_H_
#  include <std_t_mri_cpu32.h>
#endif
#elif defined(__DCC__) && defined(__ppc)
#ifndef STD_T_DIAB_PPC_H_
#  include <std_t_diab_ppc.h>
#endif
#elif defined(__M32R__)
#ifndef STD_T_CC32R_M32R_H_
#  include <std_t_cc32r_m32r.h>
#endif
#elif defined(__GNUC__) && defined(__PPC__)
#ifndef STD_T_GCC_PPC_H_
#  include <std_t_gcc_ppc.h>
#endif
#elif defined(__GNUC__) && defined(__ARM_ARCH_4T__)
#ifndef STD_T_GCC_ARM_H_
#  include <std_t_gcc_arm.h>
#endif

/* Standard types for gcc on a WIN32-based platform. */
#elif defined(__GNUC__) && defined(__WIN32__)
#  include <std_t_gcc_win32.h>

/* Standard types for gcc on a CYGWIN-based platform. */
#elif defined(__GNUC__) && defined(__CYGWIN__)
#  include <std_t_gcc_cygwin.h>

#elif defined(__arm) && defined(__TARGET_ARCH_4T)
#  include <std_t_rvct_arm.h>

/* Standard type for VCC on WIN32-based platform. */
#elif defined(WIN32)
#  include "std_t_vcc_win32.h"

/* Standard type for VCC on WIN32-based platform. */
#elif defined(__CCS__)
#  include <std_t_ccs_dsp.h>


#else
#  error std_t.h standard types not defined for this target
#endif


#ifdef __cplusplus
}
#endif
#endif /* STD_T_H_ */
