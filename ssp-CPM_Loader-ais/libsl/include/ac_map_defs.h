#ifndef AC_MAP_DEFS_H_
#define AC_MAP_DEFS_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains various definitions used by the s-function code.
These definitions are not used by the embedded code.

FILE NAME : ac_map_defs.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>
#include <math.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
#define MAX_R64                      (1.7e+308)
#define MIN_R64                      (-1.7e+308)
#define MAX_R32                      (3.4e+038f)
#define MIN_R32                      (-3.4e+038f)
#define MIN_U8                       (0)
#define MAX_U8                       (255)
#define MIN_U16                      (0)
#define MAX_U16                      (65535)
#define MIN_U32                      (0)
#define MAX_U32                      (4294967295)
#define MIN_S8                       (-128)
#define MAX_S8                       (127)
#define MIN_S16                      (-32768)
#define MAX_S16                      (32767)
#define MIN_S32                      (-2147483648)
#define MAX_S32                      (2147483647)

#define AC_MAP_CLIP(x,min,max) ((x)<(min) ? (min) : (x)>(max) ? (max) : (x))

/******************************************************************************
** These macros clip the ratios for floating point data.  For floating point
** data the ratio must be in the range from [0,1].
******************************************************************************/
#define AC_MAP_CLIP_RATIO_R64(x) ((x)<0.0  ? 0.0  : (x)>1.0  ? 1.0  : (x))
#define AC_MAP_CLIP_RATIO_R32(x) ((x)<0.0f ? 0.0f : (x)>1.0f ? 1.0f : (x))

/******************************************************************************
** These macros clip the values to the extents of their respective word types.
** Floating point values are used for the min/max values because these macros
** are intended to work with an input value (x) as a double.
******************************************************************************/
#define AC_MAP_CLIP_R64(x) ((x)<MIN_R64 ? MIN_R64 : (x)>MAX_R64 ? MAX_R64 : (x))
#define AC_MAP_CLIP_R32(x) ((x)<MIN_R32 ? MIN_R32 : (x)>MAX_R32 ? MAX_R32 : (x))
#define AC_MAP_CLIP_S8(x)  ((x)<MIN_S8  ? MIN_S8  : (x)>MAX_S8  ? MAX_S8  : (x))
#define AC_MAP_CLIP_U8(x)  ((x)<MIN_U8  ? MIN_U8  : (x)>MAX_U8  ? MAX_U8  : (x))
#define AC_MAP_CLIP_S16(x) ((x)<MIN_S16 ? MIN_S16 : (x)>MAX_S16 ? MAX_S16 : (x))
#define AC_MAP_CLIP_U16(x) ((x)<MIN_U16 ? MIN_U16 : (x)>MAX_U16 ? MAX_U16 : (x))
#define AC_MAP_CLIP_S32(x) ((x)<MIN_S32 ? MIN_S32 : (x)>MAX_S32 ? MAX_S32 : (x))
#define AC_MAP_CLIP_U32(x) ((x)<MIN_U32 ? MIN_U32 : (x)>MAX_U32 ? MAX_U32 : (x))


/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/

#endif /* AC_MAP_DEFS_H_ */
