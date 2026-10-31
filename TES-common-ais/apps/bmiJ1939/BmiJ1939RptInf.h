////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939RptInf
//
// File Name: BmiJ1939RptInf.h
//
//  Abstract:
//
////////////////////////////////////////////////////////

#ifndef BMIJ1939RPTINF_H_
#define BMIJ1939RPTINF_H_

#include <scl_health_j39_report_ifc.h>

class BmiJ1939RptInf
{

public:
   BmiJ1939RptInf() = delete;
   ~BmiJ1939RptInf() = delete;

   /* Report interface */
   static void flt_status_init(
       void *context,
       const scl_health_j39_fault_config_t *fault_config,
       bool_least_t faulted);

   static void flt_stat_chnged(
       void *context,
       const scl_health_j39_fault_config_t *fault_config,
       bool_least_t faulted);

   static void param_not_supported(
       void *context,
       const scl_health_j39_fault_config_t *fault_config,
       scl_health_j39_peer_id_and_type_t peer_id,
       bool_least_t address_valid,
       uint_least8_t address,
       bool_least_t name_valid,
       const uint_least8_t *name,
       scl_health_j39_param_type_t param_type,
       uint_least32_t param_id);

   static void no_comm(
       void * context,
       const scl_health_j39_fault_config_t *fault_config,
       scl_health_j39_peer_id_and_type_t peer_id,
       bool_least_t address_valid,
       uint_least8_t address,
       bool_least_t name_valid,
       const uint_least8_t * name,
       bool_least_t param_available,
       scl_health_j39_param_type_t param_type,
       uint_least32_t param_id);

   static void all_param_timedout(
       void *context,
       const scl_health_j39_fault_config_t *fault_config,
       scl_health_j39_peer_id_and_type_t peer_id,
       bool_least_t address_valid,
       uint_least8_t address,
       bool_least_t name_valid,
       const uint_least8_t *name,
       bool_least_t all_param_timedout);

   static void rmt_cannot_claim(
       void *context,
       const scl_health_j39_fault_config_t *fault_config,
       scl_health_j39_peer_id_and_type_t peer_id,
       const uint_least8_t *name);

   static void adr_claim_tmout(
       void *context,
       const scl_health_j39_fault_config_t *fault_config);

   static void local_cannot_clm_adr(
       void *context,
       const scl_health_j39_fault_config_t *fault_config);

   static void no_comm_clear(
       void *context,
       const scl_health_j39_fault_config_t *fault_config,
       scl_health_j39_peer_id_and_type_t peer_id,
       bool_least_t address_valid,
       uint_least8_t address,
       bool_least_t name_valid,
       const uint_least8_t *name);

   static void no_comm_persistent_clear(
       void *context,
       const scl_health_j39_fault_config_t *fault_config,
       scl_health_j39_peer_id_and_type_t peer_id,
       bool_least_t address_valid,
       uint_least8_t address,
       bool_least_t name_valid,
       const uint_least8_t *name);

    static void peer_set_id(
        void * context,
        scl_health_j39_peer_id_and_type_t old_id,
        scl_health_j39_peer_id_and_type_t new_id);

    static void lock_applied(
        void * context);
};

#endif // BMIJ1939RPTINF_H_
