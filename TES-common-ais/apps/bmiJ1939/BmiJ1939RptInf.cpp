////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939RptInf
//
// File Name: BmiJ1939RptInf.cpp
//
//  Abstract:
//
////////////////////////////////////////////////////////

#include <ais/log/AisLogger.h>

#include "BmiJ1939RptInf.h"
#include "BmiJ1939Config.h"

/* Report interface */
//over all faults. not used.
void BmiJ1939RptInf::flt_status_init(
    void *context,
    const scl_health_j39_fault_config_t *fault_config,
    bool_least_t faulted)
{
   (void)context;
   (void)fault_config;
   (void)faulted;

   AIS_LOG_NOTICE("Diag: flt_status_init faulted 0x%x." , faulted);
}

//over all faults. not used.
void BmiJ1939RptInf::flt_stat_chnged(
    void *context,
    const scl_health_j39_fault_config_t *fault_config,
    bool_least_t faulted)
{
   (void)context;
   (void)faulted;
   (void)fault_config;

   AIS_LOG_NOTICE("Diag: flt_stat_chnged faulted 0x%x." , faulted);
}

//FMI 14
//address - for each node receive a callback.
void BmiJ1939RptInf::param_not_supported(
    void *context,
    const scl_health_j39_fault_config_t *fault_config,
    scl_health_j39_peer_id_and_type_t peer_id,
    bool_least_t address_valid,
    uint_least8_t address,
    bool_least_t name_valid,
    const uint_least8_t *name,
    scl_health_j39_param_type_t param_type,
    uint_least32_t param_id)
{
   (void)context;
   (void)fault_config;
   (void)peer_id;
   (void)address_valid;
   (void)address;
   (void)name_valid;
   (void)name;
   (void)param_type;
   (void)param_id;

   auto cid = BmiJ1939Config::GetCidFromSid(address);
   BmiJ1939SCS::UpdateDiagStatus(cid, address,
                                 DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI14,
                                 DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_ACTIVE);
   AIS_LOG_NOTICE("Diag: FMI14 param_not_supported address 0x%02X cid %u param_id 0x%x" , 
                     address, cid, param_id);
}

//FMI 9
void BmiJ1939RptInf::no_comm(
    void * context,
   const scl_health_j39_fault_config_t *fault_config,
   scl_health_j39_peer_id_and_type_t peer_id,
   bool_least_t address_valid,
   uint_least8_t address,
   bool_least_t name_valid,
   const uint_least8_t * name,
   bool_least_t param_available,
   scl_health_j39_param_type_t param_type,
   uint_least32_t param_id)
{
   (void)context;
   (void)fault_config;
   (void)peer_id;
   (void)address_valid;
   (void)address;
   (void)name_valid;
   (void)name;
   (void)param_type;
   (void)param_id;

   auto cid = BmiJ1939Config::GetCidFromSid(address);
   BmiJ1939SCS::UpdateDiagStatus(cid, address,
                                 DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI9,
                                 DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_ACTIVE);
   AIS_LOG_NOTICE("Diag: FMI9 no_comm address 0x%02X cid %u param_id 0x%x." , 
                     address, cid, param_id);
}

//FMI 9
void BmiJ1939RptInf::all_param_timedout(
    void *context,
    const scl_health_j39_fault_config_t *fault_config,
    scl_health_j39_peer_id_and_type_t peer_id,
    bool_least_t address_valid,
    uint_least8_t address,
    bool_least_t name_valid,
    const uint_least8_t *name,
    bool_least_t all_param_timedout)
{

   (void)context;
   (void)fault_config;
   (void)peer_id;
   (void)address_valid;
   (void)address;
   (void)name_valid;
   (void)name;
   (void)all_param_timedout;


   if(all_param_timedout)
   {
      auto cid = BmiJ1939Config::GetCidFromSid(address);
   
      BmiJ1939SCS::UpdateDiagStatus(cid, address,
                                    DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI9,
                                    DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_ACTIVE);
      
      AIS_LOG_NOTICE("Diag: FMI9 all_param_timedout address 0x%02X cid %u status: %d" , 
                                    address, cid, all_param_timedout);

   }
   else
   {
      AIS_LOG_NOTICE("Diag: all_param_timedout 0x%02X status %d." , address, all_param_timedout);      
   }
}

//FMI 14
void BmiJ1939RptInf::rmt_cannot_claim(
    void *context,
    const scl_health_j39_fault_config_t *fault_config,
    scl_health_j39_peer_id_and_type_t peer_id,
    const uint_least8_t *name)
{
   (void)context;
   (void)fault_config;
   (void)peer_id;
   (void)name;

   AIS_LOG_NOTICE("Diag: FMI14 rmt_cannot_claim.");
}

//FMI 9 - against self node.
void BmiJ1939RptInf::adr_claim_tmout(
    void *context,
    const scl_health_j39_fault_config_t *fault_config)
{
   (void)context;
   (void)fault_config;

   AIS_LOG_NOTICE("Diag: FMI9 adr_claim_tmout.");
}

//FMI 14 - against self node.
void BmiJ1939RptInf::local_cannot_clm_adr(
    void *context,
    const scl_health_j39_fault_config_t *fault_config)
{
   (void)context;
   (void)fault_config;

   AIS_LOG_NOTICE("Diag: FMI9 local_cannot_clm_adr");
}

//FMI 9 clear
void BmiJ1939RptInf::no_comm_clear(
    void *context,
    const scl_health_j39_fault_config_t *fault_config,
    scl_health_j39_peer_id_and_type_t peer_id,
    bool_least_t address_valid,
    uint_least8_t address,
    bool_least_t name_valid,
    const uint_least8_t *name)
{
   (void)context;
   (void)fault_config;
   (void)peer_id;
   (void)address_valid;
   (void)address;
   (void)name_valid;
   (void)name;

   auto cid = BmiJ1939Config::GetCidFromSid(address);
   BmiJ1939SCS::UpdateDiagStatus(cid, address,
                                 DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI9,
                                 DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_INACTIVE);
   AIS_LOG_NOTICE("Diag: FMI9 no_comm_clear address 0x%02X cid %u" , 
                     address, cid);
}

//Not used.
void BmiJ1939RptInf::no_comm_persistent_clear(
    void *context,
    const scl_health_j39_fault_config_t *fault_config,
    scl_health_j39_peer_id_and_type_t peer_id,
    bool_least_t address_valid,
    uint_least8_t address,
    bool_least_t name_valid,
    const uint_least8_t *name)
{
   (void)context;
   (void)fault_config;
   (void)peer_id;
   (void)address_valid;
   (void)address;
   (void)name_valid;
   (void)name;

   AIS_LOG_NOTICE("Diag: no_comm_persistent_clear address 0x%x." , address);
}


void BmiJ1939RptInf::peer_set_id(
   void * context,
   scl_health_j39_peer_id_and_type_t old_id,
   scl_health_j39_peer_id_and_type_t new_id)
{
   (void)context;
   (void)old_id;
   (void)new_id;

   AIS_LOG_NOTICE("Diag: peer_set_id");
}


void BmiJ1939RptInf::lock_applied(
   void * context)
{
   (void)context;

   AIS_LOG_NOTICE("Diag: lock_applied");
}

