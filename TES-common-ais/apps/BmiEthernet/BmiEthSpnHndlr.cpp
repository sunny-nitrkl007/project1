#include <string.h>

#ifndef Task_h
#include <ais/task/Task.h>
#endif

#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/DataLinkDataWrapper/DataLinkDataWrapper.h>

#ifndef BMIETHUTIL_H
#include <bmi/bmi_ethernet_parser.h>
#endif

#ifndef BMIETHPIDHNDLR_H
#include "BmiEthSpnHndlr.h"
#endif

using namespace std;

#define BMI_ETH_DATA_STATUS_OK  0

BmiEthSpnHndlr::BmiEthSpnHndlr()
{

}

BmiEthSpnHndlr::~BmiEthSpnHndlr()
{

}

void BmiEthSpnHndlr::AppCsfPgtClientSpnRxHdlr(uint8_t datalinkType,
    							uint8_t datalinkInstance,
    							uint32_t srcId,
    							uint32_t destId,
    							void* datalinkInfo,
    							uint8_t* data,
    							uint16_t dataSize,
    							uint8_t* rawData,
    							const struct scl_pdb_spn_rx_config_s* spnConfig,
    							scl_pdb_param_status_t dataStatus)
{

	AIS_LOG_NOTICE("spn_config->spn %d data_status %d data_size %d", spnConfig->spn, dataStatus, dataSize);
	AIS_LOG_NOTICE("srcId %X  destId %X", srcId, destId);

	DataLinkParam dlParam;
	dlParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_ETH);
	dlParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_SPN);
	dlParam.SetParamId(spnConfig->spn);
	dlParam.SetSid( destId  ); //Here destId is nothing but Fid of the Configured ECM

   if ( nullptr != data )
   {
	dlParam.SetVarLengthParamType( VarLengthDataLinkParamPool::SPN );
	dlParam.SetVarLengthParamValue( data, dataSize, dataStatus );
   }

   if(SCL_PDB_PARAM_STAT_VALID == dataStatus)
   {
	const unsigned_8* varParamBlock = dlParam.GetVarParamBlock();
	const unsigned_8 varParamBlockSize = dlParam.GetVarParamBlockLength();
	for (int i = 0; i < varParamBlockSize; i++)
	{
	  AIS_LOG_INFO("spnData[%2d]    %x", i, varParamBlock[i]);
	}
   }

   (void)DataLinkDataWrapper::UpdateDataLinkData( dlParam );

}
