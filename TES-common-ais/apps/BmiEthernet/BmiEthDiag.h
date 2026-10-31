////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiCdlDiag
//
// File Name: BmiCdlDiag.h
//
//  Abstract: Handle CDL data link Diagnostic Conditions.
//
////////////////////////////////////////////////////////

#ifndef BMIETHDIAG_H
#define BMIETHDIAG_H

#include <commTask/commTask.h>
#include <csf_eth_health_report_ifc.h>

#include <bmi/bmi_ethernet_parser.h>
#include <interfaces/DataLinkData/DataLinkData.h>

class BmiEthDiag
{
public:
	BmiEthDiag() = delete;
   ~BmiEthDiag() = delete;
   static void CsfEthHealthNoComm(	void * context,
	 	 	 	 	 	 	 	 	const csf_eth_health_fault_config_t *faultConfig,
	 	 	 	 	 	 	 	 	uint8_t  peerDescType,
	 	 	 	 	 	 	 	 	uint32_t descId,
	 	 	 	 	 	 	 	 	bool_least_t fidAvail,
	 	 	 	 	 	 	 	 	uint32_t fid,
	 	 	 	 	 	 	 	 	bool_least_t ipAddressAvail,
	 	 	 	 	 	 	 	 	uint8_t ipAddressVersion,
	 	 	 	 	 	 	 	 	uint32_t ipv4Address);

   static void CsfEthHealthNoCommClear( void * context,
									const csf_eth_health_fault_config_t *faultConfig,
									uint8_t  peerDescType,
									uint32_t descId,
									bool_least_t fidAvail,
									uint32_t fid,
									bool_least_t ipAddressAvail,
									uint8_t ipAddressVersion,
									uint32_t ipv4Address);

   static void CsfEthHealthConfigError( void * context,
									const csf_eth_health_fault_config_t *faultConfig,
									uint8_t  peerDescType,
									uint32_t descId,
									bool_least_t fidAvail,
									uint32_t fid,
									bool_least_t ipAddressAvail,
									uint8_t ipAddressVersion,
									uint32_t ipv4Address);

   static void CsfEthHealthConfigErrorClear(void * context,
									const csf_eth_health_fault_config_t *faultConfig,
									uint8_t  peerDescType,
									uint32_t descId,
									bool_least_t fidAvail,
									uint32_t fid,
									bool_least_t ipAddressAvail,
									uint8_t ipAddressVersion,
									uint32_t ipv4Address);


   static uint16_t FindCidByFid(uint32_t fid);

   static void SetEcmCfgTbl(std::vector<tes_common_ais::bmi_config_parser::BmiEthEcmCfg_t > &EcmSrcCfg) {	EcmCfgTbl = EcmSrcCfg;}

protected:

private:
   static std::vector<tes_common_ais::bmi_config_parser::BmiEthEcmCfg_t> EcmCfgTbl;

};

#endif // BMIETHDIAG_H
