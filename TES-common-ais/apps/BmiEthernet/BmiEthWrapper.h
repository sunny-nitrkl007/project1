#ifndef BMIETHWRAPPER_H
#define BMIETHWRAPPER_H

#ifndef COMMTASK_H_
#include <commTask/commTask.h>
#endif

#include <interfaces/DataLinkData/InterfaceTypes.h>

#include "cdl2_struct.h"
#include "scl_pdb.h"
#include <csf_eth_health.h>
#include <csf_fit.h>
#include <bmi/bmi_ethernet_parser.h>

class BmiEthWrapper : public commTask
{
public:
    BmiEthWrapper();
    ~BmiEthWrapper();
    bool Initialize( const tes_common_ais::bmi_config_parser::BmiEthcfg_t& bmiEthCfgTbl, uint32_t PgtClientFid , uint32_t PgtClientSessionTimeOut);
    bool InitCSNSTables( void );
    uint32_t AddPIDsToConfig( uint32_t startIndex );
    uint32_t AddSPNsToConfig( uint32_t startIndex );
    uint32_t AddCatExtIdsToConfig ( uint32_t startIndex );
    void ReleaseResource ( void );
    bool PrintPgtResponse( uint8_t &pgtErr );

protected:

private:

    tes_common_ais::bmi_config_parser::BmiEthcfg_t    appEthCfgTbl;
    tes_common_ais::bmi_config_parser::RxPidConfigTable_t rxPidConfigTable;
    tes_common_ais::bmi_config_parser::RxSpnConfigTable_t rxSpnConfigTable;
    tes_common_ais::bmi_config_parser::RxCatExtIdConfigTable_t rxCatExtIdConfigTable;

    csf_eth_health_link_config_t AppEthHealthLinkConfig;
    csf_eth_health_client_config_t AppEthHealthClientConfig;
    uint_least8_t NoCommError = 1;
    uint_least8_t ConfigError = 2;
    csf_fit_local_config_t LocalConfig;

    csf_fit_remote_config_t *RemoteCfgTbl = nullptr;
    csf_eth_health_peer_config_t *HealthPeerCfgTbl = nullptr;
    scl_pdb_t *sclPdbParamTbl = nullptr;
    csf_pgt_client_param_config_t *pgtClientParamCfgv2Tbl = nullptr;
    csf_pgt_client_spl_configv2_t ClientSplCfgv2;
    uint32_t rxParamCfgCount = 0;
    uint32_t remoteCfgCount = 0;

};

#endif // BMICDLWRAPPER_H
