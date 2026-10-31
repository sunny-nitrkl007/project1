/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:
DESCRIPTION:
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef __LPS_COMMON_TYPE_DEF_H__
#include <LpsCommonTypeDef.h> /* Contains type definitions of standard datatypes */
#endif

#ifndef CAL_MGR_H_
#include <cal_mgr.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCalAppPublic.h> /* Contains type definitions of standard datatypes */
#endif

#ifndef CAL_STRUCT_H_
#include <cal_struct.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h> /* Contains type definitions of standard datatypes */
#endif

#ifndef __LPS_CAL_PUBLIC_H__
#include <LpsCalPublic.h>
#endif

#ifndef __LPS_CAL_PRIVATE_H__
#include "LpsCalPrivate.h"
#endif

#include <std_types.h> // TRUE and FALSE

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/



/******************************************************************************
FUNCTION NAME:LpsCalUpdate
DESCRIPTION: Updates cal config.
PARAMETER DESCRIPTION:
LpsCalUpdate - wrapper send updated information based on the task rate.
RETURN VALUE:LpsCalInitErrorTypes_t
*******************************************************************************/
LpsCalUpdtErrorTypes_t LpsCalUpdate(const LpsCalUpdate_t* pLpsCalUpdate)
{
	boolean *pCalEnabled = LpsCalWrkTbl.Cfg.CalEnableFlg;

	LpsCalWrkTbl.UpdateErr = LPS_CAL_UPDT_UNKNOWN_ERROR;

	if ((NULL != pCalEnabled) && (FALSE == *pCalEnabled))
	{
		LpsCalWrkTbl.UpdateErr =  LPS_CAL_UPDT_CAL_NOT_SUPPORTED;
		return LpsCalWrkTbl.UpdateErr;
	}

	if(LPS_CAL_INIT_SUCCESS != LpsCalWrkTbl.InitErr)
	{
		LpsCalWrkTbl.UpdateErr =  LPS_CAL_UPDT_CAL_INIT_FUNC_FAIL;
		return LpsCalWrkTbl.UpdateErr; //LpsCalWrkTbl.InitErr should have actual error info.
	}

	LpsCalCopyUpdateToWrkTbl(pLpsCalUpdate);

	LpsCalRunUpdate();

	LpsCalPrint(LPSCAL_LOG_WAYPOINT, "cal lib update success.");

	LpsCalWrkTbl.UpdateErr = LPS_CAL_UPDT_SUCCESS;
	return LpsCalWrkTbl.UpdateErr;
}
