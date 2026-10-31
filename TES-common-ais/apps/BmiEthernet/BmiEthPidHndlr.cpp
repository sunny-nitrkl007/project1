#include <string.h>

#include <ais/task/Task.h>

#include "interfaces/DataLinkData/InterfaceTypes.h"
#include <interfaces/DataLinkDataWrapper/DataLinkDataWrapper.h>
#include <bmi/bmi_ethernet_parser.h>
#include "BmiEthPidHndlr.h"

using namespace std;
using namespace tes_common_ais;

#define BMI_ETH_DATA_STATUS_OK  0

BmiEthPidHndlr::BmiEthPidHndlr()
{

}

BmiEthPidHndlr::~BmiEthPidHndlr()
{

}

int16_t BmiEthPidHndlr::AppCsfPgtClientPidRxHndlrv2(uint8_t datalinkType,
													uint8_t datalinkInstance,
													uint32_t srcId,
													uint32_t destId,
													void* datalinkInfo,
													uint8_t* data,
													uint8_t dataLen ,
													const cdl2_cmn_rx_pit_t  *pidConfig,
													uint16_t dsiCode)
{
	dsiCode = (dsiCode & 0xFF);
	DataLinkParam dlParameter;
	dlParameter.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_ETH);
	std::vector<unsigned_8> paramData;

	if (nullptr == pidConfig)
	{
		AIS_LOG_FATAL("Failed parse param info from PID rx handler.");
	}

	bmi_config_parser::BmiEthPidCfgTbl_t pidCfg = (*((bmi_config_parser::BmiEthPidCfgTbl_t*) pidConfig->pie));

	AIS_LOG_NOTICE("pid_config->data_ID 0x%X dsi_code %u  sId : 0x%X  dId : 0x%X data type: %u",
			pidConfig->data_ID, dsiCode, srcId, destId, pidCfg.ParameterType);

	printf("pid_config->data_ID 0x%X dsi_code %u", pidConfig->data_ID, dsiCode);

	dlParameter.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
	VarLengthDataLinkParamPool::VarLengthParamType varLengthParamType = VarLengthDataLinkParamPool::NOT_APPLICABLE;
	dlParameter.SetParamId(pidConfig->data_ID);
	dlParameter.SetSid(  pidCfg.SourceFid );//Here Sid is nothing but Fid, should get from config table

   if ( nullptr != data )
   {
	   switch(dataLen)
	   {
	   case 1:
		   	   unsigned_8 tempValue8;
		       OEL_UNPACK_BE_8_NO_INCR( data, tempValue8 );
		       paramData.assign(reinterpret_cast<unsigned_8 *>( &tempValue8 ),
		               reinterpret_cast<unsigned_8 *>( &tempValue8 ) + sizeof( tempValue8 ) ); //save temp value into paramData
		   	   break;
	   case 2:
		   	   unsigned_16 tempValue16;
		       OEL_UNPACK_BE_16_NO_INCR(data, tempValue16);
		       paramData.assign( reinterpret_cast<unsigned_8 *>( &tempValue16 ),
		               reinterpret_cast<unsigned_8 *>( &tempValue16 ) + sizeof( tempValue16 ) ); //save temp value into paramData
			   break;
	   case 4:
		   	   unsigned_32 tempValue32;
		       OEL_UNPACK_BE_32_NO_INCR( data, tempValue32 );
		       paramData.assign(reinterpret_cast<unsigned_8 *>( &tempValue32 ),
		               reinterpret_cast<unsigned_8 *>( &tempValue32 ) + sizeof( tempValue32 ) ); //save temp value into paramData
		       break;
	   default:

		   	   //possibly variable length.
			   AIS_LOG_NOTICE("************* No handler defined for variable length *************");
			   break;
	   }
   }

   if ( VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType )
   {
	  dlParameter.SetLastValue(paramData, dsiCode);
   }
  else if (VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
  {
	 // for special pid like F5D9 swapping is needed for normal data
	 if (BMI_ETH_DATA_STATUS_OK == dsiCode)
	 {
		std::reverse( paramData.begin(), paramData.end() );
		dlParameter.SetLastValue( paramData, dsiCode);
	 }
  }
   else
   {
	  if (BMI_ETH_DATA_STATUS_OK == dsiCode)
	   {
		   dlParameter.SetVarLengthParamType(varLengthParamType);
		   dlParameter.SetVarLengthParamValue(data, dataLen, dsiCode);
	   }
	  else {
	      dlParameter.SetVarLengthParamValue(nullptr, 0, dsiCode);
	  }
   }

   if (false == DataLinkDataWrapper::UpdateDataLinkData( dlParameter ))
   {
       return (uint_least16_t)0;
   }

   if ( BMI_ETH_DATA_STATUS_OK == dsiCode )
   {
		if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType ||
						 VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
		{
			  AIS_LOG_INFO("pidData	 0x%X   %u", dlParameter.GetLastValue<unsigned_32>(), dlParameter.GetLastValue<unsigned_32>() );
		}
		else
		{
		  const unsigned_8* varParamBlock = dlParameter.GetVarParamBlock();
		  const unsigned_8 varParamBlockSize = dlParameter.GetVarParamBlockLength();
		  AIS_LOG_INFO("varParamBlockSize : %u",varParamBlockSize);
		  for (int i = 0; i < varParamBlockSize; i++)
		  {
			 AIS_LOG_INFO("pidData[%2d]     0x%X", i, varParamBlock[i]);
		  }
		}
   }
   else // if dsiCode not 0
   {
	  AIS_LOG_WARN("pid 0x%X, dataLen %u, dsiCode 0x%X", dlParameter.GetParamId(), dataLen, dsiCode);

	   if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType ||
		   VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
	   {
		  AIS_LOG_WARN("pidData 0x%X   %u", dlParameter.GetLastValue<unsigned_32>(), dlParameter.GetLastValue<unsigned_32>());
	   }

   }

   return (uint_least16_t)0;
}
