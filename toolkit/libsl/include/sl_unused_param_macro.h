#ifndef SL_UNUSED_PARAM_MACRO_H_
#define SL_UNUSED_PARAM_MACRO_H_
/******************************************************************************
** COPYRIGHT (C) 2008 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar's proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains a macro which touches an unused function argument in a
compiler dependent way to avoid warnings.  This is done for functions with
fixed interfaces, so the developer can inform the compiler & maintainers
that they deliberately did not use the argument.

FILE NAME : sl_unused_param_macro.h

******************************************************************************/


/* The following macro tree is copied from
 *   \lib_oel\oel\include\std_t.h
 * That is probably a good place to look if
 * you need to add another compiler
 */
#if defined(_MRI) && defined(_CPU32)
/*   A3 MRI compiler */
#  define SL_UNUSED_PARAM(x)  /* do nothing */
#elif defined(__DCC__) && defined(__ppc)
/*   A4 diab compiler */
#  define SL_UNUSED_PARAM(x)  (void)(x)
#elif defined(__M32R__)
/*   B4/B5 cc32r compiler */
#  define SL_UNUSED_PARAM(x)  /* do nothing */
#elif defined(__GNUC__) && defined(__PPC__)
/*   gcc for the PPC */
#  define SL_UNUSED_PARAM(x)  /* do nothing */
#elif defined(__GNUC__) && defined(__ARM_ARCH_4T__)
/*   gcc for ARM */
#  define SL_UNUSED_PARAM(x)  /* do nothing */
#elif defined(__GNUC__) && defined(__WIN32__)
/*   gcc for win32 */
#  define SL_UNUSED_PARAM(x)  /* do nothing */
#elif defined(__arm) && defined(__TARGET_ARCH_4T)
/*   A5:M1/A5:M2 rvct compiler */
#  define SL_UNUSED_PARAM(x)  /* do nothing */
#elif defined(_MSC_VER)
/*   MSVC for win32 */
#  define SL_UNUSED_PARAM(x)  (x)
#elif defined(__LCC__)
/*   LCC for win32 */
#  define SL_UNUSED_PARAM(x)  /* do nothing */
#elif defined(__CCS__)
/*   Code Composer Studio for DSP */
#  define SL_UNUSED_PARAM(x)  /* do nothing */
#else
/*   Other */
#  define SL_UNUSED_PARAM(x)  /* do nothing */
#endif


#endif /* SL_UNUSED_PARAM_MACRO_H_ */
