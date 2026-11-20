/*******************************************************************************
** COPYRIGHT (C) 2002-2013 CATERPILLAR INC. ALL RIGHTS RESERVED.
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
#elif defined (_DSx86_32) || defined (_DS1006)
 /* _DSx86_32 - The dSPACE SCALEXIO environment detection
  * DS_PLATFORM_SMART and DS_PLATFORM_SMARTHIL are also defined in this case
  * _DS1006   - Standard type for compiler used by dSPACE system
  *   __GNUC__, __linux__, and __i386 are also defined in this case */
#  include <dsstd.h>
#  define LITTLE_ENDIAN
#elif defined(__DCC__) && defined(__ppc) && (__VERSION_NUMBER__ >= 5900)
#    ifndef STD_T_DIAB_PPC_59_H_
#      include <std_t_diab_ppc_59.h>
#    endif
#elif defined(__DCC__) && defined(__ppc)
#ifndef STD_T_DIAB_PPC_H_
#  include <std_t_diab_ppc.h>
#endif
#elif defined(__M32R__)
#ifndef STD_T_CC32R_M32R_H_
#  include <std_t_cc32r_m32r.h>
#endif
#elif defined(__GNUC__) && defined(__linux__) && defined(__i386)
#  include <std_t_gcc_linux_i386.h>
#elif defined(__GNUC__) && defined(__linux__) && defined(__x86_64)
#  include <std_t_gcc_linux_x86_64.h>
#elif defined(__GNUC__) && defined(__linux__) && defined(__arm__)
#  include <std_t_gcc_linux_arm.h>
#elif defined(__GNUC__) && defined(__linux__) && defined(__ARM_ARCH_ISA_A64)
#  include <std_t_gcc_linux_arm64.h>
#elif defined(__GNUC__) && defined(__PPC__)
#ifndef STD_T_GCC_PPC_H_
#  include <std_t_gcc_ppc.h>
#endif
#elif defined(__GNUC__) && defined(__ARM_ARCH_4T__)
#ifndef STD_T_GCC_ARM_H_
#  include <std_t_gcc_arm.h>
#endif


#elif defined(__GNUC__) && defined(__WIN64__)
#  include <std_t_gcc_win64.h>

/* Standard types for gcc on a WIN32-based platform. */
#elif defined(__GNUC__) && (defined(__WIN32__) || defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_6M__))
#  include <std_t_gcc_win32.h>

#elif defined(__arm) && defined(__TARGET_ARCH_4T)
#  include <std_t_rvct_arm.h>

#elif defined(__TARGET_CPU_CORTEX_M3) && defined(__ARMCC_VERSION)
#  include <std_t_rvct_arm.h>

/* LCC Compiler that ships with MATLAB */
#elif defined(__LCC__)
#  include <std_t_lcc_win32.h>

/* Standard type for VCC on WIN32-based platform using environment flags. */
#elif defined(WIN32) || defined (WINCE)
#  include <std_t_vcc_win32.h>

/* Standard type for Microsoft Visual C Compiler 2008 and earlier, if not covered above */
#elif defined(_MSC_VER) && (_MSC_VER < 1600)
#if   defined(_WIN64)
#  include <std_t_vcc_win64.h>
#else
#  include <std_t_vcc_win32.h>
#endif

/* Standard type for Microsoft Visual C Compiler 2010 and later, if not covered above */
#elif defined(_MSC_VER) && (_MSC_VER >= 1600)
#if   defined(_WIN64)
#  include <std_t_vcc99_win64.h>
#else
#  include <std_t_vcc99_win32.h>
#endif

/* Standard type for ti on tms320f28xx-based platform. */
#elif defined(__TI_COMPILER_VERSION__) && defined(__TMS320F28XX__)
#  include <std_t_ti_tms320f28xx.h>

/* Standard types for Cosmic on MC9S12XE-based platform with a CPU12 core. */
#elif defined (__CSMC__)
   #include <std_t_cosmic_mc9s12xe_cpu12.h>

#elif defined (__ghs__)
#  ifdef __i386
#     include <std_t_ghs_i386.h>
#  endif
#  ifdef __ARM__
#     include <std_t_ghs_arm.h>
#  endif
#  ifdef __PowerPC__
#     include <std_t_ghs_ppc.h>
#  endif

#else
#  error std_t.h standard types not defined for this target
#endif


#ifdef __cplusplus
}
#endif
#endif /* STD_T_H_ */
