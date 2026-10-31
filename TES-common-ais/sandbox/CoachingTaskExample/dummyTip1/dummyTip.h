
#ifndef __DUMMY_TIP_H__
#define __DUMMY_TIP_H__
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdio.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

// Extern for debugging
extern unsigned int num1;
extern unsigned int count;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
#if defined (__cplusplus)
extern "C"
{
#endif

extern void dummyTipInit();
extern void dummyTipUpdate();

#if defined (__cplusplus)
}
#endif


#endif
