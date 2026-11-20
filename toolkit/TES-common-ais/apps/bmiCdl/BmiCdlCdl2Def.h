#ifndef BMICDLCDL2DEF_H
#define BMICDLCDL2DEF_H

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef CDL2_PROTO_H_
#include <cdl2_proto.h>
#endif

#include <stdint.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include "BmiCdlWrapper.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#define BMI_CDL_DATA_STATUS_OK 0

#define BMI_CDL_MAX_NUM_PARAMETERS 34
#define BMI_CDL_MAX_NUM_ECM        5

typedef struct
{
    cdl2_cbs_header_t Header;
    cdl2_cbs_parm_table_t     CbsParamTbl[BMI_CDL_MAX_NUM_PARAMETERS]; //cdl2_cbs_parm_table_t  CbsParamTbl[BMI_CDL_MAX_NUM_PARAMETERS];
} BmiCdlCdl2CbsParmApp_t;

typedef struct
{
    cdl2_cbs_header_t Header;
    cdl2_cbs_ecm_table_t  table[BMI_CDL_MAX_NUM_ECM];
} BmiCdlCdl2CbsEcmApp_t;

typedef enum
{
   CDL2_I8  = 0,
   CDL2_U8,
   CDL2_I16, // = 2
   CDL2_U16, 
   CDL2_Binary, // = 4
   CDL2_VAR,
} ParmDataType_t;

//BmiCdl config tables.
typedef struct
{
	float Scaling;
	float Offset;
	DataLinkParamInfo::DlpUnits_t Units;
	uint8_t VarLengthDataType;
}BmiCdlConvTbl_t;

typedef struct
{
	cdl2_cbs_parm_table_t CbsParamTbl; //cdl2_cbs_parm_table_t CbsParamTbl;
	BmiCdlConvTbl_t		  ConvTbl;
   std::string  parmName;
}BmiCdlParamCfg_t;

typedef struct
{
    cdl2_cbs_header_t Header;
    BmiCdlParamCfg_t ParamCfgTbl[BMI_CDL_MAX_NUM_PARAMETERS];
} BmiCdlAppCfg_t;
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
extern const cdl2_cbs_system_cfg_t BmiCdlCbsSysTbl;
extern BmiCdlCdl2CbsEcmApp_t BmiCdlCbsEcmTbl;
extern BmiCdlCdl2CbsParmApp_t* BmiCdlCbsParamTbl;
extern cdl2_cbs_input_tbl_t  BmiCdlPidDataTbl;
extern BmiCdlAppCfg_t  BmiCdlAppCfgTbl;
extern BmiCdlWrapper CdlWrapper;

#endif /* #ifndef BMICDLCDL2DEF_H */
