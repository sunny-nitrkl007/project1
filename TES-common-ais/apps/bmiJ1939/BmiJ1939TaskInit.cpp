////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939TaskInit
//
// File Name: BmiJ1939TaskInit.cpp
//
//  Abstract: Implementation of the class that builds
//            the tables used in the setup of
//            the OEL task (scl_j1939_control_task)
//            and does the hardware initialization.
//
////////////////////////////////////////////////////////

#include <algorithm> // std::sort
#include <utility>
#include "BmiJ1939TaskInit.h"
#include "BmiJ1939DataHandlers.h"

#ifndef BMIJ1939EXTIDHDLR_H
#include "BmiJ1939ExtIdHdlr.h"
#endif

#ifndef BMIJ1939RPTINF_H_
#include "BmiJ1939RptInf.h"
#endif

// The following macros are used to search the JSON attributes string for the individual attributes
#define PID_ATTR_PATTERN_SIGNED "signed"
#define PID_ATTR_PATTERN_DSI "dsi"
#define PID_ATTR_PATTERN_SWAP "swap"
#define COMLOST_DSI 0xFF11
// Declare the class static members
bool BmiJ1939TaskInit::m_CANInitialized = false;
BmiJ1939Config::PGNTableEntries_t *BmiJ1939TaskInit::m_pAppPgnTables = nullptr;
BmiJ1939Config::CDLPIDTableEntries_t *BmiJ1939TaskInit::m_pAppPidTables = nullptr;
BmiJ1939Config::CDLPIDTableEntries_t *BmiJ1939TaskInit::m_pAppAdtPidTables = nullptr;
const oel_rtos_resource_pi_vconfig_t BmiJ1939TaskInit::m_OelPriorityInversionVConfig = OEL_RTOS_RESOURCE_PI_VCONFIG();
const oel_rtos_resource_config_t *BmiJ1939TaskInit::m_OelResourceConfig = {OEL_BASE(&m_OelPriorityInversionVConfig)};
const scl_j1939_config_t BmiJ1939TaskInit::m_OelJ1939AppConfig = {OEL_BASE(&m_OelPriorityInversionVConfig), TRUE, TRUE};
BmiJ1939TaskInit::DsiEntry_t BmiJ1939TaskInit::m_DsiEntry;
std::mutex BmiJ1939TaskInit::m_LockDiagDataLink;

std::vector<scl_j1939_rx_msg_t> BmiJ1939TaskInit::m_EcmRxTable;

std::map<uint8_t, scl_health_j39_peer_t *> BmiJ1939TaskInit::m_PeerTable;

BmiJ1939TaskInit::J1939Table_t BmiJ1939TaskInit::m_J1939MasterTable = {1000, 1000};

const scl_health_j39_report_ifc_t BmiJ1939TaskInit::m_HealthJ39RptIfc =
    {
        BmiJ1939RptInf::flt_status_init,
        BmiJ1939RptInf::flt_stat_chnged,
        BmiJ1939RptInf::param_not_supported,
        BmiJ1939RptInf::no_comm,
        BmiJ1939RptInf::all_param_timedout,
        BmiJ1939RptInf::rmt_cannot_claim,
        BmiJ1939RptInf::adr_claim_tmout,
        BmiJ1939RptInf::local_cannot_clm_adr,
        BmiJ1939RptInf::no_comm_clear,
        BmiJ1939RptInf::no_comm_persistent_clear,
        BmiJ1939RptInf::peer_set_id,
        BmiJ1939RptInf::lock_applied
    };

const scl_health_j39_link_config_t BmiJ1939TaskInit::m_HealthLinkConfig =
    /* link 0 */
    {
        SCL_J1939_LINK_VER_0, // version
        {
            // no_comm_fault_config
            SCL_HEALTH_J39_TRIG_J1939,
            639, /* SPN */
            9    /* FMI */
        },
        {
            // config_err_fault_config
            SCL_HEALTH_J39_TRIG_J1939,
            639, /* SPN */
            14   /* FMI */
        },
        FALSE,                         // peer_fault_codes
        SCL_HEALTH_J39_LINK_TYPE_J1939 // type
};

const scl_health_j39_ecm_config_t BmiJ1939TaskInit::m_HealthEcmConfig =
    {
        SCL_HEALTH_J39_ECM_VER_0,
        10000 /* address claim timeout in ms */
};

BmiJ1939TaskInit::HealthGroupTable_t BmiJ1939TaskInit::m_HealthGroups;
scl_pgb_j1939_t *BmiJ1939TaskInit::m_PgbHandle = nullptr;
scl_adt_j1939_link_handle_t BmiJ1939TaskInit::m_AdtHandle = SCL_ADT_J1939_INVALID_HANDLE;
scl_health_j39_link_t *BmiJ1939TaskInit::m_pHealthJ39Link = nullptr;
scl_health_j39_ecm_t *BmiJ1939TaskInit::m_pHealthEcm = nullptr;

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939TaskInit::AddrClaimStatus
// Description     : Address Management Address Claim Status callback. For now
//                   doesn't do anything.
// Return Type     : None
// Argument [in]   : scl_j1939_link_t Ph_link - Identifies the link being initialized,
//                   int_8 Pi8_ecm - The index into the address table associated
//                      with the ECM whose address status is being reported,
//                   SCL_J1939_AC_STATUS_CB_ENUM_t Pe_status: J1939_AC_STAT_CLAIMED - Successfully claimed Pu8_address,
//                                                            J1939_AC_STAT_LOST - Lost Pu8_ddress to a contending claim,
//                                                            J1939_AC_STAT_FAILED - Unable to claim an address.
//                   unsigned_8 Pu8_address - The address value associated with the status.
//                      In the case of J1939_AC_STAT_FAILED, Pu8_address is set to the preferred address
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939TaskInit::AddrClaimStatus(scl_j1939_link_t Ph_link, int_8 Pi8_ecm, SCL_J1939_AC_STATUS_CB_ENUM_t Pe_status, unsigned_8 Pu8_address)
{
   // Nothing to do here
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939TaskInit::InitializeJ1939
// Description     : Initializes J1939 interface and sets up J1939 tables
// Return Type     : None
// Argument [in]   : const int_16 taskPeriod_ms - J1939 task execution period in ms,
//                   BmiJ1939Config::PGNTableEntries_t* const pPgnTables -
//                      Pointer to the PGN tables obtained from JSON,
//                   BmiJ1939Config::CDLPIDTableEntries_t* const pPidTables -
//                      Pointer to the CDL PID tables obtained from JSON.
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939TaskInit::InitializeJ1939(const int_16 taskPeriod_ms,
                                       BmiJ1939Config::PGNTableEntries_t *const pPgnTables,
                                       BmiJ1939Config::CDLPIDTableEntries_t *const pPidTables,
                                       BmiJ1939Config::CDLPIDTableEntries_t *const pAdtPidTables,
                                       BmiJ1939Config::EXTIDTableEntries_t *const pExtIdTables,
                                       uint16_t base_can_port,
                                       uint8_t j1939_preferred_address,
                                       BmiJ1939Config::SclHealthPeerConfigTableEntries_t *const sclHealthPeerConfigTable)
{
   static volatile hal_canv3_port_t *P_port = HAL_CANV3_PORT_01;
   switch (base_can_port)
   {
   case 0:
      P_port = HAL_J1939V2_PORT_01; //HAL_CANV3_PORT_01;
      break;
   case 1:
      P_port = HAL_J1939V2_PORT_02; //HAL_CANV3_PORT_02;
      break;
#if defined(ARM64_GUEST)
   case 2:
      P_port = HAL_J1939V2_PORT_03; //HAL_CANV3_PORT_03;
      break;
#endif
   default:
      P_port = HAL_J1939V2_PORT_02; //HAL_CANV3_PORT_02;
      break;
   }
   AIS_LOG_NOTICE("Initializing J1939 interface...");
   m_pAppPgnTables = pPgnTables;
   m_pAppPidTables = pPidTables;
   m_pAppAdtPidTables = pAdtPidTables;

   if ((nullptr != m_pAppPgnTables) && ((nullptr != m_pAppPidTables) || (nullptr != m_pAppAdtPidTables) ||
                                        (nullptr != pExtIdTables)))
   {
      // Build the master table from the smaller tables
      BuildTables(m_DsiEntry, j1939_preferred_address);
      BmiJ1939ExtIdHdlr::BuildCatExtIdTables(pExtIdTables); // Build Table for Cat EXT ID's

      // Initialize hardware
      hal_canv3_port_set_resource(P_port, m_OelResourceConfig);
      (void)hal_canv3_pckt_prealloc_objects(P_port, m_J1939MasterTable.can_a_packet_object_max);
      (void)hal_canv3_preader_prealloc_objects(P_port, m_J1939MasterTable.can_a_preader_object_max);

      // Initialize J1939 library
      if (TRUE == scl_j1939_set_num_links(1)) // Set to maximum available ports (just CAN A)
      {
         Ph_Link_app = scl_j1939_establish_link(
             P_port, // hal_j1939v2 port
             &m_J1939MasterTable.can_a_address_table,
             m_J1939MasterTable.can_a_address_table_num,
             100,                 // number of mbufs
             40,                  // number of extentions
             4,                   // number of tpcbs
             21U,                 // Maximum Number Of Nodes On The Network [Including Virtual ECMs]
             AddrClaimStatus,     // addr status callback
             &m_OelJ1939AppConfig // OEL app config for J1939
         );

         scl_j1939_init_tasks(taskPeriod_ms);

         // Complete CAN initialization
         if (SCL_J1939_INVALID_LINK != Ph_Link_app)
         {
            m_CANInitialized = (TRUE == scl_j1939_set_ppgn_enable_table( // Proprietary messaging support
                                            Ph_Link_app,
                                            m_J1939MasterTable.can_a_ppgn_enable_num,
                                            &m_J1939MasterTable.can_a_ppgn_enable)) &&
                               (TRUE == scl_j1939_cmgr_init(Ph_Link_app, 7, 4)) && // Proprietary j1939 connection management is required for SCL PGN J1939
                               (TRUE == scl_rw_j1939_server_init(Ph_Link_app)) &&  // Initialize server for J1939 read/write protocol
                               (TRUE == scl_rw_j1939_client_init(Ph_Link_app)) &&  // Initialize CDL R/W protocol over J1939 for CAN A
                               InitializeCdlPgbOverJ1939(Ph_Link_app) &&           // Initialize CDL PID over J1939 protocol
                               InitializeCdlAdtOverJ1939(Ph_Link_app) &&           // Initialize ADT CDL PID's over J1939 protocol
                               InitJ1939Health(Ph_Link_app,                        // Initialize J1939 health
                                               P_port,
                                               sclHealthPeerConfigTable);

            //Connection Initialization CAT EXT ID's
            if (m_CANInitialized && (TRUE == BmiJ1939IDConnectionInit(Ph_Link_app)))
            {
               AIS_LOG_NOTICE("J1939 Initialization Success");
            }
         }
      }

      // Initialization done
      //scl_j1939_init_tasks(taskPeriod_ms);
   }

   AIS_LOG_NOTICE("...J1939 initialization outcome: %d", static_cast<int>(m_CANInitialized));
}

bool BmiJ1939TaskInit::InitJ1939Health(scl_j1939_link_t &J1939Link,
                                       volatile hal_canv3_port_t *LinkNum,
                                       BmiJ1939Config::SclHealthPeerConfigTableEntries_t *const sclHealthPeerConfigTable)
{
   scl_health_j39_error_t errorCode;

   // Called once at power-up after a link has been established.
   errorCode = scl_health_j39_init();
   if (errorCode != SCL_HEALTH_J39_SUCCESS)
   {
      AIS_LOG_FATAL("scl_health_j39_init failed with errorCode %u", errorCode);
      return false;
   }

   // Called to add each J1939 link to be diagnosed.
   m_pHealthJ39Link = scl_health_j39_add_link(J1939Link,
                                              &m_HealthLinkConfig,
                                              TRUE,
                                              &errorCode);

   if (errorCode != SCL_HEALTH_J39_SUCCESS)
   {
      AIS_LOG_FATAL("scl_health_j39_add_link failed with errorCode %u", errorCode);
      return false;
   }

   errorCode = scl_health_j39_link_set_pgb_ptr(m_pHealthJ39Link, m_PgbHandle);
   if (errorCode != SCL_HEALTH_J39_SUCCESS)
   {
      AIS_LOG_FATAL("scl_health_j39_link_set_pgb_ptr failed with errorCode %u", errorCode);
      return false;
   }

   errorCode = scl_health_j39_link_set_adt_handle(m_pHealthJ39Link, m_AdtHandle);
   if (errorCode != SCL_HEALTH_J39_SUCCESS)
   {
      AIS_LOG_FATAL("scl_health_j39_link_set_adt_handle failed with errorCode %u", errorCode);
      return false;
   }

   errorCode = scl_health_j39_link_add_report_client(m_pHealthJ39Link,
                                                     &m_HealthJ39RptIfc,
                                                     nullptr); //store link info in context ptr.

   if (errorCode != SCL_HEALTH_J39_SUCCESS)
   {
      AIS_LOG_FATAL("scl_health_j39_link_add_report_client failed with errorCode %u", errorCode);
      return false;
   }

   // Add the ecms to the link
   m_pHealthEcm = scl_health_j39_link_add_ecm(m_pHealthJ39Link,
                                              0,
                                              &m_HealthEcmConfig,
                                              TRUE,
                                              &errorCode);

   if (errorCode != SCL_HEALTH_J39_SUCCESS)
   {
      AIS_LOG_FATAL("scl_health_j39_link_add_ecm failed with errorCode %u", errorCode);
      return false;
   }

   // Create peer handle table
   for (uint32_t peerCount = 0; peerCount < sclHealthPeerConfigTable->size(); peerCount++)
   {
      AIS_LOG_NOTICE("Peer known 0x%x peer by address 0x%x Peer address 0x%x.",
                 sclHealthPeerConfigTable->at(peerCount).peerConfig.peer_known,
                 sclHealthPeerConfigTable->at(peerCount).peerConfig.peer_by_address,
                 sclHealthPeerConfigTable->at(peerCount).peerConfig.peer_address); //TODO change before checkin.

      scl_health_j39_peer_t *healthPeer = scl_health_j39_ecm_add_peer(m_pHealthEcm,
                                                                      &sclHealthPeerConfigTable->at(peerCount).peerConfig,
                                                                      TRUE,
                                                                      &errorCode);

      if (errorCode != SCL_HEALTH_J39_SUCCESS)
      {
         AIS_LOG_FATAL("scl_health_j39_ecm_add_peer failed with errorCode %u", errorCode);
         return false;
      }

      if (m_PeerTable.find(sclHealthPeerConfigTable->at(peerCount).peerConfig.peer_address) == m_PeerTable.end())
      {
         m_PeerTable.emplace(sclHealthPeerConfigTable->at(peerCount).peerConfig.peer_address, healthPeer);
         AIS_LOG_NOTICE("Peer address %x added to m_PeerTable.", sclHealthPeerConfigTable->at(peerCount).peerConfig.peer_address);
      }
   }

   AIS_LOG_INFO(" Adding PIDs to PGB group");
   // For each source address...
   for (auto &sourceAddressToRateMap : m_J1939MasterTable.pgb_rx_pid_tables)
   {
      // For each data broadcast rate group...
      for (auto &dataRateToPIDTable : sourceAddressToRateMap.second)
      {
         for (size_t count = 0; count < dataRateToPIDTable.second.pidConfigurationTable.size(); count++)
         {
            dataRateToPIDTable.second.pPidCfgTable.push_back(&dataRateToPIDTable.second.pidConfigurationTable[count]);
         }
         // For adding Pid Table info to PGB group
         auto peerPtr = GetPeerPtr(sourceAddressToRateMap.first);
         if (peerPtr == nullptr)
         {
            AIS_LOG_NOTICE("peerPtr not found for data rate %u coming from 0x%X", dataRateToPIDTable.first, sourceAddressToRateMap.first);
            return false;
         }
         HealthGroupKey_t groupKey{sourceAddressToRateMap.first, dataRateToPIDTable.first};
         if (m_HealthGroups.find(groupKey) != m_HealthGroups.end())
         {
            AIS_LOG_ERROR("Duplicate combination of data rate %u coming from 0x%X", dataRateToPIDTable.first, sourceAddressToRateMap.first);
            return false;
         }
         auto pGroup = scl_health_j39_peer_add_rx_grps(
             peerPtr,                                                // Peer pointer
             dataRateToPIDTable.second.pidConfigurationTable.size(), // Number of PID configurations in this PID group
             &dataRateToPIDTable.second.pPidCfgTable.front(),        // Table of PIDs to be received from the above ECM at this data rate
             dataRateToPIDTable.first,                               // Data rate for this PID group
             SCL_PGB_J1939_CALC_DFLT_TIMEOUT(100),                   // Data broadcast timeout
             0,                                                      // pgb comm delay
             TRUE,                                                   // start monitoring
             TRUE,                                                   // start communications
             &errorCode                                              // error code
         );

         if (SCL_HEALTH_J39_SUCCESS != errorCode)
         {
            AIS_LOG_ERROR("Failed to add PID group for data rate %u coming from 0x%X", dataRateToPIDTable.first, sourceAddressToRateMap.first);
            return false;
         }
         else
         {
            HealthGroupPair_t groupPair = {groupKey, pGroup};
            m_HealthGroups.insert(groupPair);
            AIS_LOG_NOTICE("Added PID group for data rate %u coming from 0x%X", dataRateToPIDTable.first, sourceAddressToRateMap.first);
         }
      }
   }

   AIS_LOG_INFO(" Adding PIDs to ADT group");
   // For each source address...
   uint32_t groupCount = 0;
   for (auto &sourceAddressMap : m_J1939MasterTable.adt_rx_pid_tablesMap)
   {
      // For each Group in particular Source Address
      for (auto &GroupTable : sourceAddressMap.second)
      {
         for (size_t count = 0; count < GroupTable.second.adtPidConfigTable.size(); count++)
         {
            GroupTable.second.adtPtrPidCfgTable.push_back(&GroupTable.second.adtPidConfigTable[count]);
         }

         AIS_LOG_DEBUG(" source address : 0X%x , No of PID's in the group : %d ", sourceAddressMap.first,
                   GroupTable.second.adtPidConfigTable.size());
         AIS_LOG_DEBUG(" PID : 0x%X , data_size : %d", GroupTable.second.adtPtrPidCfgTable.front()->pid,
                   GroupTable.second.adtPtrPidCfgTable.front()->data_size);

         scl_health_j39_peer_add_adt_rx_grps(
             GetPeerPtr(sourceAddressMap.first),           // Peer pointer
             GroupTable.second.adtPidConfigTable.size(),   // Number of PID configurations in this PID group
             &GroupTable.second.adtPtrPidCfgTable.front(), // points to the configured  group of PIDs to be received
             TRUE,                                         // dm13_support
             0,                                            // adt_comm_delay
             TRUE,                                         // start_mon
             TRUE,                                         // begin_comm
             &errorCode);

         if (SCL_HEALTH_J39_SUCCESS != errorCode)
         {
            AIS_LOG_ERROR("Failed to add PID to the group coming from 0x%x", sourceAddressMap.first);
            return false;
         }
         else
         {
            AIS_LOG_NOTICE(" Added to PID group coming from 0x%x with group ID %d", sourceAddressMap.first, groupCount); //how to get correct group id?
         }
      }
   }

   AIS_LOG_INFO(" Adding PGNs to health.");
   uint32_t pgnIndex = 0;
   BmiJ1939Config::PGNTableEntry_t *pgnTablePtr;

   for (auto &rxMsg : m_EcmRxTable)
   {
      //ignore source address 0xFF set in the PGN config.
      if (0xFF != rxMsg.Mu8_source_address)
      {
         pgnTablePtr = &m_pAppPgnTables->at(pgnIndex);

         // Add PGN for health monitoring.
         scl_health_j39_peer_add_rx_pgn(
             GetPeerPtr(rxMsg.Mu8_source_address), // Peer pointer
             pgnIndex,
             rxMsg.Mi16_lost_timeout,
             SCL_HEALTH_J39_MON_TYPE_TIME,
             NULL,
             pgnTablePtr->SpnList.size(),
             &pgnTablePtr->SpnList.front(), //TODO: This could be done cleaner by changing RxTable struct.
             TRUE,
             &errorCode);

         AIS_LOG_NOTICE("SID 0x%02X PGN %d SPN count %d, PGNTableEntry table index %d.",
                    rxMsg.Mu8_source_address, rxMsg.Mu32_pgn, pgnTablePtr->SpnList.size(), pgnIndex);

         if (SCL_HEALTH_J39_SUCCESS != errorCode)
         {
            AIS_LOG_ERROR("Failed to add PGN for health monitoring.");
            return false;
         }
         else
         {
            AIS_LOG_ERROR("Added PGN for health monitoring.");
         }

         // Print SPN read from config.
         for (const scl_health_j39_id_and_type_t &spn : pgnTablePtr->SpnList)
         {
            AIS_LOG_NOTICE("SPN %d", spn.id);
         }
      }
      else
      {
         AIS_LOG_NOTICE("No health monitoring for PGN %d (SID 0x%02X) PGNTableEntry Table index %d.",
                    rxMsg.Mu32_pgn, rxMsg.Mu8_source_address, pgnIndex);
      }

      pgnIndex++;
   }

   return true;
}

scl_health_j39_peer_t *BmiJ1939TaskInit::GetPeerPtr(uint8_t peerAddress)
{
   auto pos = m_PeerTable.find(peerAddress);
   if (pos != m_PeerTable.end())
   {
      return pos->second;
   }

   return nullptr;
}

///////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939TaskInit::BmiJ1939IDConnectionInit
// Description     : Initializes J1939 interface for CAT EXT-ID's and sets up tables
// Return Type     : bool
// Argument [in]   : scl_j1939_link_t Ph_link - Identifies the link being initialized
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////

bool BmiJ1939TaskInit::BmiJ1939IDConnectionInit(scl_j1939_link_t Ph_link)
{
	bool initSuccess = true;
   AIS_LOG_NOTICE("Initializing CAT EXT Id's");
	if (TRUE == scl_j1939_set_enable_global_ppgna(Ph_link, TRUE)) {
	    for (const auto& hdlr : BmiJ1939ExtIdHdlr::J1939ExtIdRxTable) {
	        if (TRUE == scl_j1939_cat_ppgn_id_install_command(Ph_link, &hdlr)) {
	            AIS_LOG_INFO("Install command success: %X", hdlr.command);
	        }
	        else {
	            AIS_LOG_ERROR("Install command Failed for CAT EXT ID: %X", hdlr.command);
	            initSuccess = false;
	        }
	    }
   }
	else {
	    initSuccess = false;
	}

	return initSuccess;
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939TaskInit::InitializeCdlPgbOverJ1939
// Description     : Initializes CAT DataLink PID Parameter Group
//                   Broadcast over J1939 interface
// Return Type     : bool - 'true' if successful, 'false' otherwise
// Argument [in]   : scl_j1939_link_t Ph_link - CAN link handle
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939TaskInit::InitializeCdlPgbOverJ1939(scl_j1939_link_t Ph_link)
{
   bool initSuccessful = false;
   AIS_LOG_INFO(" Initializing InitializeCdlPgbOverJ1939...");
   // Setup DM13 to support client stop/reinit of PGB broadcast
   if (FALSE == scl_j1939_set_max_dm13_clients(0, 0, PgbStopBroadcastAllowed) ||
       FALSE == scl_j1939_install_dm13(Ph_link, m_J1939MasterTable.pgb_virtual_ecm_cfg.ecm_idx))
   {
      AIS_LOG_ERROR("Failed to install DM13 service");
   }
   else
   {
      m_PgbHandle = scl_pgb_j1939_init(Ph_link);
      if (nullptr == m_PgbHandle)
      {
         AIS_LOG_ERROR("PGB init failed.");
      }
      else
      {
         if (TRUE == scl_pgb_j1939_add_ecm(m_PgbHandle, &m_J1939MasterTable.pgb_virtual_ecm_cfg))
         {
            initSuccessful = true;
         }
         else
         {
            AIS_LOG_ERROR("Failed to create a virtual ECM for PGB");
         }
      }
   }

   return initSuccessful;
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939TaskInit::InitializeCdlAdtOverJ1939
// Description     : Initializes CAT DataLink PID ADT
//                    over J1939 interface
// Return Type     : bool - 'true' if successful, 'false' otherwise
// Argument [in]   : scl_j1939_link_t Ph_link - CAN link handle
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939TaskInit::InitializeCdlAdtOverJ1939(scl_j1939_link_t Ph_link)
{
   bool initSuccess = false;
   AIS_LOG_INFO(" Initializing CdlAdtOverJ1939...");
   // Setup DM13 to support client stop/reinit of ADT broadcast
   if (FALSE == scl_j1939_set_max_dm13_clients(0, 0, AdtStopBroadcastAllowed) ||
       FALSE == scl_j1939_install_dm13(Ph_link, 0 /*ecm_idx*/))
   {
      AIS_LOG_ERROR("Failed to install DM13 service");
   }
   else
   {
      m_AdtHandle = scl_adt_j1939_link_init(Ph_link);
      if (SCL_ADT_J1939_INVALID_HANDLE == m_AdtHandle)
      {
         AIS_LOG_FATAL("ADT init failed.");
      }
      else
      {
         if (TRUE == scl_adt_j1939_link_add_ecm(m_AdtHandle, m_J1939MasterTable.pgb_virtual_ecm_cfg.ecm_idx))
         {
            initSuccess = true;
         }
         else
         {
            AIS_LOG_ERROR("Failed to create a virtual ECM for ADT");
         }
      }
   }
   return initSuccess;
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939TaskInit::PgbStopBroadcastAllowed
// Description     : Dummy callback function that always allows the stop
//                   of the PGB broadcast
// Return Type     : boolean_t - Always 'TRUE'
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
boolean_t BmiJ1939TaskInit::PgbStopBroadcastAllowed(void)
{
   return TRUE;
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939TaskInit::AdtStopBroadcastAllowed
// Description     : Dummy callback function that always allows the stop
//                   of the ADT broadcast
// Return Type     : boolean_t - Always 'TRUE'
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
boolean_t BmiJ1939TaskInit::AdtStopBroadcastAllowed(void)
{
   return TRUE;
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939TaskInit::SetDsiTableData
// Description     : Update the dsi code received for each PID in the dsi Table
// Return Type     : None
// Argument [in]   : void* pContextPtr - Pointer to the received callback context,
//                   uint_least16_t dsiCode - Data Status Indicator.
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939TaskInit::SetDsiTableData(BmiJ1939Config::CDLPIDTableEntry_t *pContextPtr, uint_least16_t dsi_Code)
{
   /*Iterate through map for each source address*/
   for (auto &mapItem : m_DsiEntry)
   {
      AIS_LOG_DEBUG("Source Address: 0x%X", mapItem.first);
      /*Update the dsi status received for each PID in the DSI Table*/
      for (auto &ItemToDsiEntry : mapItem.second)
      {
         if (ItemToDsiEntry.PID == pContextPtr->ParameterID)
         {
            ItemToDsiEntry.dsi = dsi_Code;
         }
         AIS_LOG_DEBUG("PID : 0x%X  dsi : 0x%X", ItemToDsiEntry.PID, ItemToDsiEntry.dsi);
      }
   }
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939TaskInit::GetFmiStatus
// Description     : Function to detect the Fmi status and update status to data link data
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939TaskInit::GetFmiStatus()
{
   // Claim mutex for the entire duration of this function
   std::lock_guard<std::mutex> scopeLock(m_LockDiagDataLink);

   unsigned_32 OverallDsiStatus;
   unsigned_16 CID;
   /* Iterate through map for each source address*/
   for (auto &mapItem : m_DsiEntry)
   {
      CID = 0;
      OverallDsiStatus = 0xFFFF;
      /*For each PID in the vector*/
      for (auto &ItemToPidSearch : mapItem.second)
      {
         //LOG_DEBUG("PID : 0x%X   dsi : 0x%X  cid : %d", ItemToPidSearch.PID, ItemToPidSearch.dsi, ItemToPidSearch.cid);
         CID = ItemToPidSearch.cid;
         OverallDsiStatus = (OverallDsiStatus & ItemToPidSearch.dsi);
      }

      //LOG_NOTICE("OverallDsiStatus : 0x%X for SA :  0x%X", OverallDsiStatus, mapItem.first);
      if (COMLOST_DSI == OverallDsiStatus)
      {
         //LOG_NOTICE("Activating FMI status for SA : 0x%X with cid : %d", mapItem.first, CID);
         BmiJ1939SCS::UpdateDiagStatus(CID, mapItem.first,
                                       DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI9,
                                       DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_ACTIVE);
      }
      else
      {
         //LOG_NOTICE("Deactivating Fmi status");
         BmiJ1939SCS::UpdateDiagStatus(CID, mapItem.first,
                                       DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI9,
                                       DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_INACTIVE);
      }
   }
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939TaskInit::BuildTables
// Description     : Build the tables required for the J1939 initialization
// Return Type     : None
// Argument [in]   : DsiEntry_t dsiEntry, uint8_t j1939_preferred_address
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939TaskInit::BuildTables(DsiEntry_t dsiEntry, uint8_t j1939_preferred_address)
{
   // Set the tables with the node name and address for the J1939 network for this ECM
   struct J1939NameAddress_s
   {
      unsigned_8 Mu8_industry_group;
      unsigned_8 Mu8_vehicle_system;
      unsigned_8 Mu8_vehicle_system_instance;
      unsigned_8 Mu8_function;
      unsigned_8 Mu8_function_instance;
      unsigned_8 Mu8_ecu_instance;
      unsigned_16 Mu16_manufacturer_code;
      unsigned_32 Mu32_identity_number;
      unsigned_8 Mu8_preferred_address;
   } static nameAndAddress = {
       // NAME
       0,                      // Industry Group
       0,                      // Vehicle System
       0,                      // Vehicle System Instance
       47,                     // Function
       1,                      // Function Instance
       0,                      // ECU Instance
       8,                      // Manufacturer Code
       0,                      // Identity Number
       j1939_preferred_address // Preferred Address

   };
   static unsigned_8 otherPreferredAddresses[] =
       {
           MONITOR_1_CAN_A_J1939_ADD,
           MONITOR_2_CAN_A_J1939_ADD,
           MONITOR_3_CAN_A_J1939_ADD,
           MONITOR_4_CAN_A_J1939_ADD,
           MONITOR_5_CAN_A_J1939_ADD,
           MONITOR_6_CAN_A_J1939_ADD,
           MONITOR_7_CAN_A_J1939_ADD};

   // Sort the handled PGNs in ascending order
   std::sort(m_pAppPgnTables->begin(), m_pAppPgnTables->end());

   // Build the PGN Rx table
   for (const auto &jsonPgnBlock : *m_pAppPgnTables)
   {
      AIS_LOG_INFO("jsonPgnBlock.ParameterGroupName : %s", jsonPgnBlock.ParameterGroupName.c_str());
      AIS_LOG_INFO("jsonPgnBlock.ParameterGroupNumber : 0x%X", jsonPgnBlock.ParameterGroupNumber);
      AIS_LOG_INFO("jsonPgnBlock.SourceAddress : 0x%X", jsonPgnBlock.SourceAddress);
      AIS_LOG_INFO("jsonPgnBlock.Priority :%d", jsonPgnBlock.Priority);
      AIS_LOG_INFO("jsonPgnBlock.Timeout_ms : %u", jsonPgnBlock.Timeout_ms);
      AIS_LOG_INFO("jsonPgnBlock.ControlBitField : %u", jsonPgnBlock.ControlBitField);
      AIS_LOG_INFO("jsonPgnBlock.MsgHandlerIndex : %u", jsonPgnBlock.MsgHandlerIndex);

      scl_j1939_rx_msg_t ecmRxEntry;

      // Has the source name been provided in JSON?
      if (!jsonPgnBlock.SourceName.empty())
      {
         ecmRxEntry.Mb_address_by_name = TRUE;
         jsonPgnBlock.SourceName.copy(reinterpret_cast<char *>(ecmRxEntry.Mau8_source_name), sizeof(ecmRxEntry.Mau8_source_name));
      }
      else
      {
         ecmRxEntry.Mb_address_by_name = FALSE;
      }
      ecmRxEntry.Mi16_lost_timeout = jsonPgnBlock.Timeout_ms;
      ecmRxEntry.Mpfn_parser = jsonPgnBlock.MsgHandlerIndex < BmiJ1939DataHandlers::GetNumPgnHandlers() ? BmiJ1939DataHandlers::m_pgnHandlers[jsonPgnBlock.MsgHandlerIndex] : &BmiJ1939DataHandlers::BmiJ1939PGNDefault;
      ecmRxEntry.Mu32_pgn = jsonPgnBlock.ParameterGroupNumber;
      ecmRxEntry.Mu8_init_cntrl = static_cast<unsigned_8>(jsonPgnBlock.ControlBitField);
      ecmRxEntry.Mu8_priority = jsonPgnBlock.Priority;
      ecmRxEntry.Mu8_source_address = static_cast<unsigned_8>(jsonPgnBlock.SourceAddress);

      m_EcmRxTable.push_back(ecmRxEntry);
   }

   // Build the J1939 CAN A address table
   m_J1939MasterTable.can_a_address_table =
       {
           // ECM J1939 Name
           &(nameAndAddress.Mu8_industry_group),
           &(nameAndAddress.Mu8_vehicle_system),
           &(nameAndAddress.Mu8_vehicle_system_instance),
           &(nameAndAddress.Mu8_function),
           &(nameAndAddress.Mu8_function_instance),
           &(nameAndAddress.Mu8_ecu_instance),
           &(nameAndAddress.Mu16_manufacturer_code),
           &(nameAndAddress.Mu32_identity_number),
           &(nameAndAddress.Mu8_preferred_address),

           // Address List To Try If ECM Cannot Claim Preferred Source Address
           sizeof(otherPreferredAddresses), /* Size */
           otherPreferredAddresses,         /*Pointer */
           TRUE,                            // Support Self-Configuration Of Source Address         [Yes]
           TRUE,                            // Enable Extended Addresses During Self-Configuration  [Yes]

           // Receive Message Table
           static_cast<unsigned_8>(m_EcmRxTable.size()),
           &m_EcmRxTable[0],
           //Transmit Message Table
           0,   /*Size     */
           NULL /*Pointer  */
       };

   m_J1939MasterTable.can_a_address_table_num = 1;

   // Build Proprietary PGN enable table
   //SCL_J1939_GLOBAL_ADDRESS - 0xFF
   m_J1939MasterTable.can_a_ppgn_enable =
   {
      //NOTE: Caterpillar Manufacturer code is 8. Hence this app
      //would receive PropA messages only from CAT ECMs.
      //CAT Ext ids.

      // Propriatary A (PDU1)
      SCL_J1939_GLOBAL_ADDRESS, // unsigned_8   Mu8_ppgn_a_address
      8,                        // unsigned_16  Mu16_ppgn_a_manuf_code

      //NOTE: When Mu8_ppgn_b_address set to GLOBAL ADDRESS and 
      //scl_j1939_config_t.Mb_enable_app_process_prop_b_msg set to TRUE
      //J1939 protocol ignores rest of the name fields.
      //PropB range of PGNs.

      // Propriatary B (PDU2)
      SCL_J1939_GLOBAL_ADDRESS, // unsigned_8  Mu8_ppgn_b_address
      0,                        // unsigned_8  Mu8_ppgn_b_industry_group
      0,                        // unsigned_8 Mu8_ppgn_b_vehicle_system
      0,                        // unsigned_8 Mu8_ppgn_b_vehicle_system_inst
      0,                        // unsigned_8  Mu8_ppgn_b_function
      0,                        // unsigned_8 Mu8_ppgn_b_function_inst
      0,                        // unsigned_8 Mu8_ppgn_b_ecu_inst
      0                         // prop_b_manuf_code
   };

   m_J1939MasterTable.can_a_ppgn_enable_num = 1;

   for (auto &jsonPidBlock : *m_pAppPidTables)
   {
      if (J1939_PGB_REQUEST == jsonPidBlock.RequestType)
      {
         // Create a table entry
         scl_pgb_j1939_rx_pid_config_t newTableEntry = {
             jsonPidBlock.ParameterID,                  // PID
             &BmiJ1939DataHandlers::BmiJ1939PIDDefault, // Received data handler callback function
             static_cast<void *>(&jsonPidBlock),        // Context for the callback function
             jsonPidBlock.DataSize};                    // Data size associated with the PID

         // Convert PID attributes string to lower case
         for (auto &eachChar : jsonPidBlock.Attributes)
         {
            eachChar = static_cast<char>(tolower(static_cast<unsigned_8>(eachChar)));
         }
         AIS_LOG_INFO("PID attributes string in lower case: %s", jsonPidBlock.Attributes.c_str());
         // Determine the flags from the attributes string
         newTableEntry.flags = ((std::string::npos != jsonPidBlock.Attributes.find(PID_ATTR_PATTERN_SIGNED)) ? SCL_PGB_J1939_RX_PID_SIGNED : SCL_PGB_J1939_RX_PID_UNSIGNED) |
                               ((std::string::npos != jsonPidBlock.Attributes.find(PID_ATTR_PATTERN_DSI)) ? SCL_PGB_J1939_RX_PID_DSI_AVAIL : SCL_PGB_J1939_RX_PID_DSI_NA) |
                               ((std::string::npos != jsonPidBlock.Attributes.find(PID_ATTR_PATTERN_SWAP)) ? SCL_PGB_J1939_RX_PID_SWAP_DATA : SCL_PGB_J1939_RX_PID_NO_SWAP);

         // Add this configuration table entry, creating new source address and/or request rate keys if necessary
         m_J1939MasterTable.pgb_rx_pid_tables[jsonPidBlock.SourceAddress][jsonPidBlock.RequestRate_ms].pidConfigurationTable.push_back(newTableEntry);
      }
   }
   unsigned_8 Data_Size = 0;
   unsigned_8 NumGroups = 0;

   for (auto &jsonAdtPidBlock : *m_pAppAdtPidTables)
   {
      AIS_LOG_INFO("jsonAdtPidBlock.ParameterID: 0x%X", jsonAdtPidBlock.ParameterID);
      AIS_LOG_INFO("jsonAdtPidBlock.ParameterName: %s", jsonAdtPidBlock.ParameterName.c_str());
      AIS_LOG_INFO("jsonAdtPidBlock.Attributes: %s", jsonAdtPidBlock.Attributes.c_str());
      AIS_LOG_INFO("jsonAdtPidBlock.SourceAddress: 0x%02X", jsonAdtPidBlock.SourceAddress);
      AIS_LOG_INFO("jsonAdtPidBlock.Timeout_ms: %u", jsonAdtPidBlock.Timeout_ms);
      AIS_LOG_INFO("jsonAdtPidBlock.RequestRate_ms: %u", jsonAdtPidBlock.RequestRate_ms);
      AIS_LOG_INFO("jsonAdtPidBlock.DataSize: %d", jsonAdtPidBlock.DataSize);

      std::map<unsigned_8, std::map<unsigned_8, ADTPidTable_t>>::iterator itr1;

      //PID DataSize should not be more than 4 bytes for ADT
      if (SCL_ADT_J1939_DATA_MAX_SIZE > jsonAdtPidBlock.DataSize)
      {
         // Create a ADT table entry
         scl_adt_j1939_client_grp_pid_config_t newAdtTableEntry = {
             jsonAdtPidBlock.ParameterID,               // PID
             &BmiJ1939DataHandlers::BmiJ1939ADTDefault, // Received data handler callback function
             static_cast<void *>(&jsonAdtPidBlock),     // Context for the callback function
             jsonAdtPidBlock.DataSize};

         // Convert PID attributes string to lower case
         for (auto &eachChar : jsonAdtPidBlock.Attributes)
         {
            eachChar = static_cast<char>(tolower(static_cast<unsigned_8>(eachChar)));
         }
         AIS_LOG_INFO("PID attributes string in lower case for ADT: %s", jsonAdtPidBlock.Attributes.c_str());
         // Determine the flags from the attributes string
         newAdtTableEntry.flags = ((std::string::npos != jsonAdtPidBlock.Attributes.find(PID_ATTR_PATTERN_SIGNED)) ? SCL_ADT_J1939_RX_PID_SIGNED : SCL_ADT_J1939_RX_PID_UNSIGNED) |
                                  ((std::string::npos != jsonAdtPidBlock.Attributes.find(PID_ATTR_PATTERN_DSI)) ? SCL_ADT_J1939_RX_PID_DSI_AVAIL : SCL_ADT_J1939_RX_PID_DSI_NA) |
                                  ((std::string::npos != jsonAdtPidBlock.Attributes.find(PID_ATTR_PATTERN_SWAP)) ? SCL_ADT_J1939_RX_PID_SWAP_DATA : SCL_ADT_J1939_RX_PID_NO_SWAP);

         itr1 = m_J1939MasterTable.adt_rx_pid_tablesMap.find(jsonAdtPidBlock.SourceAddress);
         if (itr1 != m_J1939MasterTable.adt_rx_pid_tablesMap.end())
         {

            Data_Size = Data_Size + jsonAdtPidBlock.DataSize;
            AIS_LOG_DEBUG("Data_Size = %d", Data_Size);
            if (Data_Size < SCL_ADT_J1939_DATA_MAX_SIZE)
            {
               AIS_LOG_DEBUG("Total Data_Size is less than 5bytes");

               // Add this configuration table entry, adding to the existing group
               m_J1939MasterTable.adt_rx_pid_tablesMap[jsonAdtPidBlock.SourceAddress][NumGroups].adtPidConfigTable.push_back(newAdtTableEntry);
            }
            else
            {
               AIS_LOG_DEBUG("Total Data_Size is greater than 5bytes");
               Data_Size = jsonAdtPidBlock.DataSize;
               NumGroups++;
               AIS_LOG_DEBUG("re-initialized Data_Size = %d, NumGroups = %d", Data_Size, NumGroups);

               // Add this configuration table entry, adding to the new group
               m_J1939MasterTable.adt_rx_pid_tablesMap[jsonAdtPidBlock.SourceAddress][NumGroups].adtPidConfigTable.push_back(newAdtTableEntry);
            }
         }
         else //insert new PID from different SA
         {
            Data_Size = jsonAdtPidBlock.DataSize;
            NumGroups = 0;
            AIS_LOG_DEBUG("Inserting new PID 0x%X with new SA as key %X", jsonAdtPidBlock.ParameterID, jsonAdtPidBlock.SourceAddress);

            // Add this configuration table entry, creating new source address
            m_J1939MasterTable.adt_rx_pid_tablesMap[jsonAdtPidBlock.SourceAddress][NumGroups].adtPidConfigTable.push_back(newAdtTableEntry);
         }
      }
      else
      {
         AIS_LOG_WARN("PID 0x%X Datasize configured %d which should not be more than 4 bytes for ADT", jsonAdtPidBlock.ParameterID, jsonAdtPidBlock.DataSize);
      }
   }

   //dsiTable Entries
   AIS_LOG_DEBUG("DSItable Entries:");
   for (auto &mapItem : m_DsiEntry)
   {
      AIS_LOG_DEBUG("source address : 0x%X ", mapItem.first);
      for (auto &ItemPrint : mapItem.second)
      {
         AIS_LOG_DEBUG(" PID  : 0x%X  DSI  : 0x%X  cid  : %d", ItemPrint.PID, ItemPrint.dsi, ItemPrint.cid);
      }
   }

   // Count the number of broadcast groups
   const unsigned_8 numOfConnections = static_cast<unsigned_8>(m_J1939MasterTable.pgb_rx_pid_tables.size()); // Number of supported source addresses

   unsigned_16 numGroups = 0;
   for (auto &sourceAddressToRateMap : m_J1939MasterTable.pgb_rx_pid_tables)
   {
      // Add the number of data broadcast rate groups for this source address
      numGroups += sourceAddressToRateMap.second.size();
   }
   AIS_LOG_NOTICE("PGB is configured to work with %u sources with a total of %u broadcast rate groups", numOfConnections, numGroups);

   // Build a table for the virtual ECM that will be handling PGB protocol
   m_J1939MasterTable.pgb_virtual_ecm_cfg =
       {
           0,   // [ecm_idx] Index of the virtual ECM that will be acting as a PGB client or server
           5,   // [num_rx_connections] Maximum number of inbound connections that this ECM will support at any given time
           0,   // [num_tx_connections] Maximum number of outbound connections that this ECM will support at any given time
           100, // [num_rx_groups] Maximum number of PGB protocol Rx groups that will be used by the client at any given time
           0,   // [num_tx_groups] Maximum number of PGB protocol Tx groups that will be used by the server at any given time
           0    // [num_bcasts] Maximum number of broadcast Tx groups supported by server at any given time (Tx groups grouped further by broadcast rate)
       };
}
