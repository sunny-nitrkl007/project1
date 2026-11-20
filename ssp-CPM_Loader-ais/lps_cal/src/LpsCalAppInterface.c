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
#include <LpsCommonTypeDef.h>
#endif

#ifndef CAL_MGR_H_
#include <cal_mgr.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCalAppPublic.h>
#endif

#ifndef CAL_STRUCT_H_
#include <cal_struct.h>
#endif

#ifndef __LPS_COMMON_STRUCTURES_H__
#include <LpsCommonStructures.h>
#endif

#ifndef __LPS_COMMON_LOOKUP_TBL_UTILITY__
#include <LpsCommonLookUpTblUtility.h>
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
FUNCTION NAME: LpsCalAppInfGetCalOvActiveAndCmdLmts
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsCalAppInfGetCalOvActiveAndCmdLmts(LpsCalAppInfCmdLmt_t *CmdLmts)
{
	CmdLmts->CalOvrActive = LpsCalAppInfCalOvActive();
	CmdLmts->RaiseCmdLmt  = LpsCalAppInfGetRaiseCmdLmt();
	CmdLmts->LowerCmdLmt  = LpsCalAppInfGetLowerCmdLmt();
	CmdLmts->RackCmd   = LpsCalAppInfGetRackCmd();
	CmdLmts->DumpCmd   = LpsCalAppInfGetDumpCmd();
	CmdLmts->EngSpdLmt 	  = LpsCalAppInfGetEngSpdLmt();

	return;
}

/******************************************************************************
FUNCTION NAME: LpsCalAppInfCalOvActive
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
boolean LpsCalAppInfCalOvActive()
{
	LpsCalOv_t *pCalOv = &LpsCalWrkTbl.Ov;
    return pCalOv->LpsCalAppInfCalOvrActive;
}


/******************************************************************************
FUNCTION NAME: LpsCalAppInfGetRaiseCmdLmt
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
signed_8 LpsCalAppInfGetRaiseCmdLmt()
{
	LpsCalOv_t *pCalOv = &LpsCalWrkTbl.Ov;

    signed_8 raiseCommandLimit;
    if (TRUE == pCalOv->LpsCalAppInfCalOvrActive)
    {
        raiseCommandLimit = pCalOv->LpsCalAppInfRaiseCmdLmt;
    }
    else
    {
        raiseCommandLimit = LPS_CAL_APP_MAX_RAISE_CMD;
    }
    return raiseCommandLimit;
}

/******************************************************************************
FUNCTION NAME: LpsCalAppInfGetLowerCmdLmt
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
signed_8 LpsCalAppInfGetLowerCmdLmt()
{
    signed_8 lowerCommandLimit;
	LpsCalOv_t *pCalOv = &LpsCalWrkTbl.Ov;

    if (TRUE == pCalOv->LpsCalAppInfCalOvrActive)
    {
        lowerCommandLimit = pCalOv->LpsCalAppInfLowerCmdLmt;
    }
    else
    {
        lowerCommandLimit = LPS_CAL_APP_MAX_LOWER_CMD;
    }
    return lowerCommandLimit;
}

/******************************************************************************
FUNCTION NAME: LpsCalAppInfGetRackCmd
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
signed_8 LpsCalAppInfGetRackCmd()
{
    signed_16 rackCommand;
	LpsCalOv_t *pCalOv = &LpsCalWrkTbl.Ov;

    if (TRUE == pCalOv->LpsCalAppInfCalOvrActive)
    {
        rackCommand = pCalOv->LpsCalAppInfRackCmd;
    }
    else
    {
        rackCommand = LPS_CAL_APP_MIN_RACK_CMD;
    }
    return rackCommand;
}

/******************************************************************************
FUNCTION NAME: LpsCalAppInfGetRackCmd
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
signed_8 LpsCalAppInfGetDumpCmd()
{
    signed_8 dumpCommand;
	LpsCalOv_t *pCalOv = &LpsCalWrkTbl.Ov;

    if (TRUE == pCalOv->LpsCalAppInfCalOvrActive)
    {
        dumpCommand = pCalOv->LpsCalAppInfDumpCmd;
    }
    else
    {
        dumpCommand = LPS_CAL_APP_MIN_DUMP_CMD;
    }
    return dumpCommand;
}

/******************************************************************************
FUNCTION NAME: LpsCalAppInfGetEngSpdLmt
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
signed_16 LpsCalAppInfGetEngSpdLmt()
{
    signed_16 engineSpeedLimit;
	LpsCalOv_t *pCalOv = &LpsCalWrkTbl.Ov;

    if (TRUE == pCalOv->LpsCalAppInfCalOvrActive)
    {
        engineSpeedLimit = pCalOv->LpsCalAppInfEngSpdLmt;
    }
    else
    {
        engineSpeedLimit = LPS_CAL_APP_MAX_ENG_SPD*(1UL<<3);
    }

    return engineSpeedLimit;
}


