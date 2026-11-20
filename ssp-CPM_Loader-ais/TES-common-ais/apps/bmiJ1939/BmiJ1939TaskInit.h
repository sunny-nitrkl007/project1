////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939TaskInit
//
// File Name: BmiJ1939TaskInit.h
//
//  Abstract: Declaration for the class that builds
//            the tables used in the setup of
//            the OEL task (scl_j1939_control_task)
//            and does the hardware initialization.
//
////////////////////////////////////////////////////////

#ifndef BMIJ1939TASKINIT_H_
#define BMIJ1939TASKINIT_H_
#include <mutex>           // std::mutex
#include <vector>          // std::vector
#include <map>             // std::map
#include <memory>          // std::shared_ptr
#include <unordered_map>
#include <std_types.h>
#include "BmiJ1939Config.h"
#include <scl_adt_j1939.h>
#include <scl_adt_j1939_alloc.h>
#include <scl_adt_j1939_tune.h>
#include <scl_health_j39.h>
#include <scl_health_j39_status.h>
#include <scl_health_j39_link.h>

extern "C"
{
   #include <oel_rtos_posix.h>
   #include <scl_j1939.h>
   #include <scl_rw_j1939.h>
   #include <scl_pgb_j1939.h>
   #include <cdl2_struct.h>
   #include <app_public.h>
}
extern scl_j1939_link_t Ph_Link_app;

class BmiJ1939TaskInit
{
public:
   static void InitializeJ1939( const int_16 taskPeriod_ms,
      BmiJ1939Config::PGNTableEntries_t* const pPgnTables,
      BmiJ1939Config::CDLPIDTableEntries_t* const pPidTables,
      BmiJ1939Config::CDLPIDTableEntries_t* const pAdtPidTables,
      BmiJ1939Config::EXTIDTableEntries_t* const pExtIdTables,
      uint16_t base_can_port,
      uint8_t j1939_preferred_address,
      BmiJ1939Config::SclHealthPeerConfigTableEntries_t *const sclHealthPeerConfigTable );

   static inline bool IsCANInitialized( void ) { return m_CANInitialized; }

   static void SetDsiTableData(BmiJ1939Config::CDLPIDTableEntry_t* pContextPtr, uint_least16_t dsiCode);
   static void GetFmiStatus();
   static std::map<uint8_t, scl_health_j39_peer_t*> Getm_PeerTable()
   {
      return m_PeerTable;
   }

private:
   typedef struct PIDTable_s
   {
      std::vector<scl_pgb_j1939_rx_pid_config_t>   pidConfigurationTable;
      std::vector<scl_pgb_j1939_rx_pid_cfg_ptr_t>  pPidCfgTable;  // scl_pgb_j1939 library requires us to store a pointer to each PID configuration above...
      unsigned_16                                  timeout_ms;    // Timeout used for this PID group; the timeout below the broadcast rate will be overruled to the default of 2.5 x rate

      PIDTable_s( void ): timeout_ms( NO_TIMEOUT ) { }
   } PIDTable_t;
   // J1939Table_t contains the lists of addresses that will be used for the CAN link.
   // Associated with each address are the PGNs that will be received and/or transmitted.

   typedef struct ADTPidTable_s
  	 {
  		std::vector<scl_adt_j1939_client_grp_pid_config_t>      adtPidConfigTable;
  		std::vector<scl_adt_j1939_client_grp_pid_config_ptr_t>  adtPtrPidCfgTable;
  	 } ADTPidTable_t;

   typedef struct J1939Table_s
   {
      size_t                                       can_a_packet_object_max;         // Max number of packets for packet objects
      size_t                                       can_a_preader_object_max;        // Max number of packet readers for packet objects
      scl_j1939_addr_tbl_t                         can_a_address_table;             // Table of addresses for CAN A
      unsigned_16                                  can_a_address_table_num;         // Number of entries in the table above
      scl_j1939_ppgn_enable_t                      can_a_ppgn_enable;               // Proprietary PGN acceptable addresses for CAN A
      unsigned_16                                  can_a_ppgn_enable_num;           // Number of entries in the table above
      scl_pgb_j1939_ecm_config_t                   pgb_virtual_ecm_cfg;             // Virtual ECM configuration table pointer
      std::map< unsigned_8, std::map<unsigned_16, PIDTable_t> > pgb_rx_pid_tables;  // CDL PID configuration tables for J1939 PGB: 1 PID group per request rate per J1939 source

       // CDL PID configuration tables for J1939 ADT
      std::map< unsigned_8, std::map< unsigned_8, ADTPidTable_t >> adt_rx_pid_tablesMap; //SA,NumGroups,ADT Table

   } J1939Table_t;

   typedef struct DSITable_s
   {
      unsigned_32 PID;
      unsigned_32 dsi;
      unsigned_16 cid;
   } DSITable_t;

   typedef std::vector<DSITable_t> DsiTable_t;
   typedef std::map<unsigned_32, DsiTable_t> DsiEntry_t;

   BmiJ1939TaskInit( void ) { }
   virtual ~BmiJ1939TaskInit( void ) { }
   static void AddrClaimStatus( scl_j1939_link_t Ph_link, int_8 Pi8_ecm, SCL_J1939_AC_STATUS_CB_ENUM_t Pe_status, unsigned_8 Pu8_address );
   static bool InitializeCdlPgbOverJ1939( scl_j1939_link_t Ph_link);
   static boolean_t PgbStopBroadcastAllowed( void );
   static void BuildTables(DsiEntry_t dsiEntry, uint8_t j1939_preferred_address);

   static bool InitializeCdlAdtOverJ1939( scl_j1939_link_t Ph_link );
   static boolean_t AdtStopBroadcastAllowed( void );
   static bool BmiJ1939IDConnectionInit( scl_j1939_link_t Ph_link );
   
   static bool InitJ1939Health(scl_j1939_link_t &J1939Link,
                              volatile hal_canv3_port_t *LinkNum,
                              BmiJ1939Config::SclHealthPeerConfigTableEntries_t *const sclHealthPeerConfigTable);
   static scl_health_j39_peer_t * GetPeerPtr(uint8_t peerAddress);


   static bool                                        m_CANInitialized;
   static BmiJ1939Config::PGNTableEntries_t*          m_pAppPgnTables;
   static BmiJ1939Config::CDLPIDTableEntries_t*       m_pAppPidTables;
   static BmiJ1939Config::CDLPIDTableEntries_t*       m_pAppAdtPidTables;
   static const oel_rtos_resource_pi_vconfig_t        m_OelPriorityInversionVConfig;
   static const oel_rtos_resource_config_t*           m_OelResourceConfig;
   static const scl_j1939_config_t                    m_OelJ1939AppConfig;
   static DsiEntry_t                                  m_DsiEntry;
   static std::mutex                                  m_LockDiagDataLink;
   static J1939Table_t                                m_J1939MasterTable;

   static scl_pgb_j1939_t*                            m_PgbHandle;
   static scl_adt_j1939_link_handle_t                 m_AdtHandle;
   static std::vector<scl_j1939_rx_msg_t>             m_EcmRxTable;

   // scl_health_j39
   static const scl_health_j39_link_config_t          m_HealthLinkConfig;
   static const scl_health_j39_ecm_config_t           m_HealthEcmConfig;
   static const scl_health_j39_report_ifc_t           m_HealthJ39RptIfc;
   static std::map<uint8_t, scl_health_j39_peer_t*>   m_PeerTable;

   using HealthGroupKey_t = std::pair<unsigned_8, unsigned_16>;
   using HealthGroupPair_t = std::pair<HealthGroupKey_t, scl_health_j39_grp_t*>;
   using HealthGroupTable_t = std::unordered_map<HealthGroupKey_t, scl_health_j39_grp_t*, boost::hash<HealthGroupKey_t>>;
   static HealthGroupTable_t                          m_HealthGroups;

   static scl_health_j39_link_t*                      m_pHealthJ39Link;
   static scl_health_j39_ecm_t*                       m_pHealthEcm;
};

#endif // BMIJ1939TASKINIT_H_
