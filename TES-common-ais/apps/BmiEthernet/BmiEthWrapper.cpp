////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//
//
//  Abstract: Handle incoming ETH data link parameters.
//
////////////////////////////////////////////////////////

#include <boost/foreach.hpp>

#include <ais/task/Task.h>
#include <csf_eth_health_fault_mgr_ifc.h>
#include <csf_pgt_client.h>
#include <oel_pack.h>
#include <bmi/bmi_ethernet_util.h>

#include "BmiEthPidHndlr.h"
#include "BmiEthSpnHndlr.h"
#include "BmiEthCatExtIdHndlr.h"
#include "BmiEthDiag.h"
#include "BmiEthWrapper.h"

using namespace tes_common_ais;

csf_eth_health_report_ifc_t ReportIfcPtr = {   BmiEthDiag::CsfEthHealthNoComm,
											   BmiEthDiag::CsfEthHealthNoCommClear,
											   BmiEthDiag::CsfEthHealthConfigError,
											   BmiEthDiag::CsfEthHealthConfigErrorClear,
											   NULL,
											   NULL,
											   NULL};

BmiEthWrapper::BmiEthWrapper()
{
	AIS_LOG_NOTICE("BmiEthWrapper constructor.");
}

BmiEthWrapper::~BmiEthWrapper()
{
	AIS_LOG_NOTICE("BmiEthWrapper destructor.");
	ReleaseResource();
}

bool BmiEthWrapper::Initialize( const bmi_config_parser::BmiEthcfg_t& bmiEthCfgTbl,
								uint32_t PgtClientFid ,
								uint32_t PgtClientSessionTimeOut )
{
	AIS_LOG_NOTICE("BmiEthWrapper::Initialize");

	csf_eth_health_link_handle_t healthLinkHndl;
	csf_eth_health_client_handle_t healthClientHndl;
	csf_eth_health_peer_handle_t healthPeerHndl;
	uint_least8_t ethHealthError = 0xFF;
	uint_least8_t pgtError = 0xFF;
	csf_fit_error_t csfFitError = 0xFF;

	this->appEthCfgTbl = bmiEthCfgTbl;
	BmiEthDiag::SetEcmCfgTbl(appEthCfgTbl.EcmSrcCfg);

	if(!InitCSNSTables())
	{
		AIS_LOG_FATAL("Failed to initialize CSNS libraries.");
		return false;
	}

	//Initialize OEL
	AIS_LOG_NOTICE("commInitialize");
	commInitialize();
	sleep(2);

	uint8_t addRxParamSuccess = scl_pdb_add_rx_param_list(rxParamCfgCount, sclPdbParamTbl);
	if (addRxParamSuccess != SCL_PDB_SUCCESS)
	{
		switch (addRxParamSuccess)
		{
		case SCL_PDB_INVALID_CONFIG:
			AIS_LOG_FATAL("line(%d): Failed to add rx param list (Invalid Parameter configuration.)", __LINE__);
			break;
		case SCL_PDB_TABLE_FULL:
			AIS_LOG_FATAL("line(%d): Failed to add rx param list (Insufficient memory.)", __LINE__);
			break;
		case SCL_PDB_EXISTS_FOR_ANOTHER_ENTRY:
			AIS_LOG_FATAL("line(%d): Failed to add rx param list (Duplicate parameter found.)", __LINE__);
			break;
		case SCL_PDB_FAILED:
			AIS_LOG_FATAL("line(%d): Failed to add rx param list (Invalid Parameter configuration.)", __LINE__);
			break;
		default:
			AIS_LOG_FATAL("line(%d): Failed to add rx param list.", __LINE__);
			break;
		}

		return false;
	}

	//set local config
	LocalConfig.fid = PgtClientFid;
	LocalConfig.local_ip = bmi_ethernet_util::GetIpAddressInt();
	AIS_LOG_NOTICE("LocalConfig.local_ip %x", LocalConfig.local_ip);
	LocalConfig.local_ip_configured = TRUE;
	csf_fit_set_local_fid(&LocalConfig);

	//set remote config.
	for(uint32_t rmc = 0; rmc < remoteCfgCount; rmc++)
	{
		csfFitError = csf_fit_set_remote_fid(&RemoteCfgTbl[rmc]);
		AIS_LOG_NOTICE("csf_fit_set_remote resp %d fid 0x%08X", csfFitError, RemoteCfgTbl[rmc].fid);
	}

	AppEthHealthLinkConfig.no_comm_fault_ptr = &NoCommError;
	AppEthHealthLinkConfig.config_err_fault_ptr = &ConfigError;
	AppEthHealthClientConfig.fid = LocalConfig.fid;

	csf_eth_health_init();
	healthLinkHndl = csf_eth_health_add_link(&AppEthHealthLinkConfig);
	AIS_LOG_NOTICE("healthLinkHandle %d", healthLinkHndl);
	healthClientHndl = csf_eth_health_add_client(healthLinkHndl, &AppEthHealthClientConfig);
	AIS_LOG_NOTICE("healthClientHndl %d", healthClientHndl);

	//add peers.
	for(uint32_t pc = 0; pc < remoteCfgCount; pc++)
	{
		healthPeerHndl = csf_eth_health_add_peer(healthClientHndl, &HealthPeerCfgTbl[pc]);
		AIS_LOG_NOTICE("add_peer resp %d for fid 0x%08X", healthPeerHndl, HealthPeerCfgTbl[pc].fid);
	}

	/*Add report client 1 */
	if (csf_eth_health_link_add_report_client(healthLinkHndl, &ReportIfcPtr, (void *) &LocalConfig.fid ) == FALSE)
	{
		AIS_LOG_FATAL("\n line(%d): Adding report client fid 0x%08X is failed \n", __LINE__, LocalConfig.fid);
	}

	//Client SPL (Server Parameter List) configuration
	ClientSplCfgv2.num_param 		= rxParamCfgCount;
	ClientSplCfgv2.param_config 	= pgtClientParamCfgv2Tbl;
	ClientSplCfgv2.session_timeout 	= PgtClientSessionTimeOut; //Read from ruby file.
	ClientSplCfgv2.timeout_callback = NULL;

	csf_eth_health_spl_handle_t spl_handle = csf_eth_health_client_add_splv2(LocalConfig.fid,
									(csf_pgt_client_spl_configv2_t *)&ClientSplCfgv2,
									&ethHealthError,
									&pgtError);

	AIS_LOG_FATAL("Client(fid: fid 0x%08X) add pgt config resp %d health_error %d pgtError %d",
			LocalConfig.fid, spl_handle, ethHealthError, pgtError);

	if(!PrintPgtResponse(pgtError))
	{
		return false;
	}

	AIS_LOG_NOTICE("Initialization completed.");

	return true;
}

bool BmiEthWrapper::PrintPgtResponse( uint8_t &pgtErr)
{
	bool PgtSuccess = false;
	switch(pgtErr)
	{
		case CSF_PGT_CLIENT_SUCCESS:
			PgtSuccess = true;
			AIS_LOG_INFO(" PGT configured successfully. ");
			break;
		case CSF_PGT_CLIENT_ERROR_INSUF_MEMORY:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Insufficient memory.)" );
			break;
		case CSF_PGT_CLIENT_ERROR_INVALID_PID_RECEIVE_HANDLER:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (RX handler is not proper.)" );
				break;
		case CSF_PGT_CLIENT_ERROR_PID_REQUESTED_PERIOD:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Invalid PID update period.)" );
				break;
		case CSF_PGT_CLIENT_ERROR_SERVER_CONFIG_LIMT:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Exceeds the CSF_PGT_CLIENT_MAX_SERVER_COUNT limit.)" );
				break;
		case CSF_PGT_CLIENT_ERROR_SESSION_CONFIG_LIMT:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Exceeds the CSF_PGT_CLIENT_MAX_SESSION_COUNT limit.)" );
				break;
		case CSF_PGT_CLIENT_ERROR_GRP_CONFIG_LIMT:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Exceeds the CSF_PGT_CLIENT_MAX_GRP_COUNT limit.)" );
				break;
		case CSF_PGT_CLIENT_ERROR_PID_CONFIG_LIMT:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Exceeds the CSF_PGT_CLIENT_MAX_PID_COUNT limit.)" );
				break;
		case CSF_PGT_CLIENT_ERROR_INVALID_SERVER_FID:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Invalid server FID.)" );
				break;
		case CSF_PGT_CLIENT_SERVER_FID_NOT_FOUND:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Server FID Not Found.)" );
				break;
		case CSF_PGT_CLIENT_INVALID_PID_CONFIG:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (PID config is NULL.)" );
				break;
		case CSF_PGT_CLIENT_ERROR_SPL_CONFIG_LIMT:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Exceeds the CSF_PGT_CLIENT_MAX_SPL_COUNT limit.)" );
				break;
		case CSF_PGT_CLIENT_ERROR_SPN_REQUESTED_PERIOD:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (SPN update period  Error.)" );
				break;
		case CSF_PGT_CLIENT_INVALID_PARAM_CONFIG:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Parameter configuration Error.)" );
				break;
		case CSF_PGT_CLIENT_ERROR_PARAM_NOT_FOUND_IN_PDB:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Parameter not found in PDB database)" );
				break;
		case CSF_PGT_CLIENT_ERROR_GRP_DATA_CONFIG_LIMT:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (Exceeds the Max Group data limit.)" );
				break;
		case CSF_PGT_CLIENT_ERROR_CAT_EXT_ID_REQUESTED_PERIOD:
			AIS_LOG_ERROR(" Failed to add version2 SPL to the PGT client (CAT_EXT_ID update period  Error.)" );
				break;
		default:
			AIS_LOG_ERROR(" PGT initialization failed. " );
				break;
	}

return PgtSuccess;
}
bool BmiEthWrapper::InitCSNSTables ( void )
{
	/*** csf_fit_remote_config_t  & csf_eth_health_peer_config_t ***/
	remoteCfgCount = appEthCfgTbl.EcmSrcCfg.size();
	RemoteCfgTbl = new (std::nothrow) csf_fit_remote_config_t[remoteCfgCount];
	if (RemoteCfgTbl == nullptr)
	{
		// error assigning memory.
		AIS_LOG_FATAL("error assigning memory for remote config.");
		return false;
	}

	HealthPeerCfgTbl = new (std::nothrow) csf_eth_health_peer_config_t[remoteCfgCount];
	if (HealthPeerCfgTbl == nullptr)
	{
		AIS_LOG_FATAL("error assigning memory for peer config.");
		return false;
	}

	bmi_config_parser::BmiEthEcmCfg_t *ecmCfgPtr;
	AIS_LOG_NOTICE("appEthCfgTbl.EcmSrcCfg.size() %d", appEthCfgTbl.EcmSrcCfg.size());

	for (uint32_t iEcm = 0; iEcm < appEthCfgTbl.EcmSrcCfg.size(); iEcm++)
	{
		//remote config
		ecmCfgPtr = &appEthCfgTbl.EcmSrcCfg[iEcm];
		RemoteCfgTbl[iEcm].fid = ecmCfgPtr->Fid;
		RemoteCfgTbl[iEcm].remote_ip = ecmCfgPtr->IPAddress;
		RemoteCfgTbl[iEcm].remote_ip_configured = TRUE;

		//peer config
		HealthPeerCfgTbl[iEcm].fid = ecmCfgPtr->Fid;
	}

	/*************** scl_pdb_t & csf_pgt_client_param_config_t *****************/
	rxParamCfgCount = appEthCfgTbl.PidCfg.size() + appEthCfgTbl.SpnCfg.size() + appEthCfgTbl.ExtIdCfg.size();
	sclPdbParamTbl = new (std::nothrow) scl_pdb_t[rxParamCfgCount];
	if (sclPdbParamTbl == nullptr)
	{
		// error assigning memory.
		AIS_LOG_FATAL("error assigning memory for scl pdb config.");
		return false;
	}

	pgtClientParamCfgv2Tbl = new (std::nothrow) csf_pgt_client_param_config_t[rxParamCfgCount];
	if (pgtClientParamCfgv2Tbl == nullptr)
	{
		// error assigning memory.
		AIS_LOG_FATAL("error assigning memory for param configv2.");
		return false;
	}

	uint32_t currIndex = 0;
	AIS_LOG_NOTICE("(line: %d)Current param tbl index %d", __LINE__, currIndex);
	currIndex = AddPIDsToConfig(currIndex);
	AIS_LOG_NOTICE("(line: %d)Current param tbl index %d", __LINE__, currIndex);
	currIndex = AddSPNsToConfig(currIndex);
	AIS_LOG_NOTICE("(line: %d)Current param tbl index %d", __LINE__, currIndex);
	currIndex = AddCatExtIdsToConfig(currIndex);
	AIS_LOG_NOTICE("(line: %d)Current param tbl index %d", __LINE__, currIndex);

	return true;
}

uint32_t BmiEthWrapper::AddPIDsToConfig( uint32_t startIndex )
{
	GetRxPidConfigTable(appEthCfgTbl, rxPidConfigTable);
	uint32_t currIndex = startIndex;

	for (uint32_t iPid = startIndex; iPid < appEthCfgTbl.PidCfg.size(); iPid++)
	{
		auto& pidCfg = appEthCfgTbl.PidCfg[iPid];
		auto& rxPidCfg = rxPidConfigTable[pidCfg.data_ID];

		sclPdbParamTbl[currIndex].param_type = SCL_PDB_CDL_PARAM;
		rxPidCfg.rx_hdlr = ((cdl2_cmn_rx_hdlr_t *) &(BmiEthPidHndlr::AppCsfPgtClientPidRxHndlrv2));
		rxPidCfg.pie = (void *) &appEthCfgTbl.PidCfg[iPid];
		sclPdbParamTbl[currIndex].config = &rxPidCfg;

		pgtClientParamCfgv2Tbl[currIndex].server_fid = pidCfg.SourceFid;
		pgtClientParamCfgv2Tbl[currIndex].param_id = pidCfg.data_ID;
		pgtClientParamCfgv2Tbl[currIndex].req_period = pidCfg.RequestPeriod;
		pgtClientParamCfgv2Tbl[currIndex].param_type = SCL_PDB_CDL_PARAM;
		pgtClientParamCfgv2Tbl[currIndex].diag_support = pidCfg.DiagSupport;

		AIS_LOG_NOTICE("sclPdbParamTbl[%d].param_type %d", currIndex, sclPdbParamTbl[currIndex].param_type);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].server_fid %x", currIndex, pgtClientParamCfgv2Tbl[currIndex].server_fid);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].param_id %x", currIndex, pgtClientParamCfgv2Tbl[currIndex].param_id);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].req_period %d", currIndex, pgtClientParamCfgv2Tbl[currIndex].req_period);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].param_type %d", currIndex, pgtClientParamCfgv2Tbl[currIndex].param_type);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].diag_support %d", currIndex, pgtClientParamCfgv2Tbl[currIndex].diag_support);

		currIndex++;
	}

	return currIndex;
}

uint32_t BmiEthWrapper::AddSPNsToConfig ( uint32_t startIndex )
{
	GetRxSpnConfigTable(appEthCfgTbl, rxSpnConfigTable);
	uint32_t currIndex = startIndex;

	for (uint32_t iSpn = 0; iSpn < appEthCfgTbl.SpnCfg.size(); iSpn++)
	{
		auto& spnCfg = appEthCfgTbl.SpnCfg[iSpn];
		auto& rxSpnCfg = rxSpnConfigTable[spnCfg.spn];

		sclPdbParamTbl[currIndex].param_type = SCL_PDB_SPN_PARAM;
		rxSpnCfg.rx_hdlr = (scl_pdb_spn_rx_hdlr_t*) &(BmiEthSpnHndlr::AppCsfPgtClientSpnRxHdlr);
		sclPdbParamTbl[currIndex].config = &rxSpnCfg;

		AIS_LOG_NOTICE("rxSpnCfg.spn %x", rxSpnCfg.spn);
		AIS_LOG_NOTICE("rxSpnCfg.size_in_bits %d", rxSpnCfg.size_in_bits);
// ENM 		AIS_LOG_NOTICE("rxSpnCfg.status_conv %d", rxSpnCfg.status_conv);
// ENM 		AIS_LOG_NOTICE("rxSpnCfg.byte_order %d", rxSpnCfg.byte_order);

		pgtClientParamCfgv2Tbl[currIndex].server_fid = spnCfg.SourceFid;
		pgtClientParamCfgv2Tbl[currIndex].param_id = spnCfg.spn;
		pgtClientParamCfgv2Tbl[currIndex].req_period = spnCfg.RequestPeriod;
		pgtClientParamCfgv2Tbl[currIndex].param_type = SCL_PDB_SPN_PARAM;
		pgtClientParamCfgv2Tbl[currIndex].diag_support = spnCfg.DiagSupport;

		AIS_LOG_NOTICE("sclPdbParamTbl[%d].param_type %d", currIndex, sclPdbParamTbl[currIndex].param_type);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].server_fid %x", currIndex, pgtClientParamCfgv2Tbl[currIndex].server_fid);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].param_id %x", currIndex, pgtClientParamCfgv2Tbl[currIndex].param_id);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].req_period %d", currIndex, pgtClientParamCfgv2Tbl[currIndex].req_period);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].param_type %d", currIndex, pgtClientParamCfgv2Tbl[currIndex].param_type);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].diag_support %d", currIndex, pgtClientParamCfgv2Tbl[currIndex].diag_support);

		currIndex++;
	}

	return currIndex;
}

uint32_t BmiEthWrapper::AddCatExtIdsToConfig ( uint32_t startIndex )
{
	GetRxCatExtIdConfigTable(appEthCfgTbl, rxCatExtIdConfigTable);
	uint32_t currIndex = startIndex;

	for (uint32_t iCatExtId = 0; iCatExtId < appEthCfgTbl.ExtIdCfg.size(); iCatExtId++)
	{
		auto& catExtIdCfg = appEthCfgTbl.ExtIdCfg[iCatExtId];
		auto& rxCatExtIdCfg = rxCatExtIdConfigTable[catExtIdCfg.cat_ext_id];

		sclPdbParamTbl[currIndex].param_type = SCL_PDB_CAT_EXT_ID;
		rxCatExtIdCfg.rx_hdlr = (scl_pdb_cat_ext_id_rx_hdlr_t*) &(BmiEthCatExtIdHndlr::AppCsfPgtClientCatExtIdRxHdlr);
		sclPdbParamTbl[currIndex].config = &rxCatExtIdCfg;

		AIS_LOG_NOTICE("rxCatExtIdCfg.cat_ext_id %x", rxCatExtIdCfg.cat_ext_id);
		AIS_LOG_NOTICE("rxCatExtIdCfg.data_size %d", rxCatExtIdCfg.data_size);

		pgtClientParamCfgv2Tbl[currIndex].server_fid = catExtIdCfg.SourceFid;
		pgtClientParamCfgv2Tbl[currIndex].param_id = catExtIdCfg.cat_ext_id;
		pgtClientParamCfgv2Tbl[currIndex].req_period = catExtIdCfg.RequestPeriod;
		pgtClientParamCfgv2Tbl[currIndex].param_type = SCL_PDB_CAT_EXT_ID;
		pgtClientParamCfgv2Tbl[currIndex].diag_support = catExtIdCfg.DiagSupport;

		AIS_LOG_NOTICE("sclPdbParamTbl[%d].param_type %d", currIndex, sclPdbParamTbl[currIndex].param_type);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].server_fid %x", currIndex, pgtClientParamCfgv2Tbl[currIndex].server_fid);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].param_id %x", currIndex, pgtClientParamCfgv2Tbl[currIndex].param_id);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].req_period %d", currIndex, pgtClientParamCfgv2Tbl[currIndex].req_period);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].param_type %d", currIndex, pgtClientParamCfgv2Tbl[currIndex].param_type);
		AIS_LOG_NOTICE("pgtClientParamCfgv2Tbl[%d].diag_support %d", currIndex, pgtClientParamCfgv2Tbl[currIndex].diag_support);

		currIndex++;
	}

	return currIndex;
}

void BmiEthWrapper::ReleaseResource ( void )
{
	AIS_LOG_NOTICE("Cleaning up resource.");

	if (nullptr != RemoteCfgTbl)
	{
		delete[] RemoteCfgTbl;
		RemoteCfgTbl = nullptr;
	}
	if (nullptr != HealthPeerCfgTbl)
	{
		delete[] HealthPeerCfgTbl;
		HealthPeerCfgTbl = nullptr;
	}
	if (nullptr != sclPdbParamTbl)
	{
		delete[] sclPdbParamTbl;
		sclPdbParamTbl = nullptr;
	}
	if (nullptr != pgtClientParamCfgv2Tbl)
	{
		delete[] pgtClientParamCfgv2Tbl;
		pgtClientParamCfgv2Tbl = nullptr;
	}
}
