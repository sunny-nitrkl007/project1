////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiCdlDiag
//
// File Name: BmiCdlDiag.cpp
//
//  Abstract: Handle CDL data link Diagnostic Conditions.
//
////////////////////////////////////////////////////////

#include "BmiEthDiag.h"
#include <ais/task/Task.h>
#include <interfaces/DataLinkDataWrapper/DataLinkDataWrapper.h>

using namespace tes_common_ais;

std::vector<bmi_config_parser::BmiEthEcmCfg_t> BmiEthDiag::EcmCfgTbl;

void BmiEthDiag::CsfEthHealthNoComm( void * context,
		 	 	 	 	 	 	 	 const csf_eth_health_fault_config_t *faultConfig,
		 	 	 	 	 	 	 	 uint8_t  peerDescType,
		 	 	 	 	 	 	 	 uint32_t descId,
		 	 	 	 	 	 	 	 bool_least_t fidAvail,
		 	 	 	 	 	 	 	 uint32_t fid,
		 	 	 	 	 	 	 	 bool_least_t ipAddressAvail,
		 	 	 	 	 	 	 	 uint8_t ipAddressVersion,
		 	 	 	 	 	 	 	 uint32_t ipv4Address)
{
	 uint32_t *client = (uint32_t *)context;

	 AIS_LOG_NOTICE("FMI 9 reported to client fid : %x  for server fid: %x\n", *client, fid);

	 DataLinkDataWrapper::UpdateDlpDiagStatus(FindCidByFid(fid), fid,
			 	 	 	 	 	 	 DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI9,
	 								 DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_ACTIVE);
}

void BmiEthDiag::CsfEthHealthNoCommClear( void * context,
											const csf_eth_health_fault_config_t *faultConfig,
											uint8_t  peerDescType,
											uint32_t descId,
											bool_least_t fidAvail,
											uint32_t fid,
											bool_least_t ipAddressAvail,
											uint8_t ipAddressVersion,
											uint32_t ipv4Address)
{
	uint32_t *client = (uint32_t *)context;

	AIS_LOG_NOTICE("FMI 9 clear reported to client fid : %x  for server fid: %x \n", *client, fid);

	DataLinkDataWrapper::UpdateDlpDiagStatus(FindCidByFid(fid), fid,
									DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI9,
									DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_INACTIVE);
}

void BmiEthDiag::CsfEthHealthConfigError( void * context,
											 const csf_eth_health_fault_config_t *faultConfig,
											 uint8_t  peerDescType,
											 uint32_t descId,
											 bool_least_t fidAvail,
											 uint32_t fid,
											 bool_least_t ipAddressAvail,
											 uint8_t ipAddressVersion,
											 uint32_t ipv4Address)
{
	uint32_t *client = (uint32_t *)context;

	AIS_LOG_NOTICE(" FMI 14  reported to client fid : %x  for server fid: %x\n", *client, fid);

	DataLinkDataWrapper::UpdateDlpDiagStatus(FindCidByFid(fid), fid,
										DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI14,
										DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_ACTIVE);
}

void BmiEthDiag::CsfEthHealthConfigErrorClear( void * context,
												 const csf_eth_health_fault_config_t *faultConfig,
												 uint8_t  peerDescType,
												 uint32_t descId,
												 bool_least_t fidAvail,
												 uint32_t fid,
												 bool_least_t ipAddressAvail,
												 uint8_t ipAddressVersion,
												 uint32_t ipv4Address)
{
	uint32_t *client = (uint32_t *)context;

	AIS_LOG_NOTICE("FMI 14  cleared  reported to client fid : %x  for server fid: %x\n", *client, fid);

	DataLinkDataWrapper::UpdateDlpDiagStatus(FindCidByFid(fid), fid,
					DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI14,
					DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_INACTIVE);
}

uint16_t BmiEthDiag::FindCidByFid(uint32_t fid)
{
   for(bmi_config_parser::BmiEthEcmCfg_t &ecm : EcmCfgTbl)
   {
	   if(ecm.Fid == fid)
	   {
		   AIS_LOG_INFO("cid %d fid %x", ecm.Cid, fid);
		   return ecm.Cid;
	   }
   }

   return 0;
}
