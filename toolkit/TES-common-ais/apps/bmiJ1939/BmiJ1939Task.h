////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939Task
//
// File Name: BmiJ1939Task.h
//
//  Abstract: Declaration for the class that glues
//            the AIS platform task (BmiJ1939) and
//            the OEL task (scl_j1939_control_task).
//            The former sends out SCS objects to other
//            AIS apps, the latter is based on the
//            legacy libraries and is handling
//            the J1939 traffic.
//
////////////////////////////////////////////////////////

#ifndef BMIJ1939TASK_H_
#define BMIJ1939TASK_H_

#include <std_types.h>
#include <commTask/commTask.h>
#include "BmiJ1939Config.h"

extern "C"
{
   #include <oel_rtos_posix.h>
   #include <oel_rtos.h>
   #include <oel_rtos_sc.h>
   #include <oel_u.h>
   #include <oel_pack.h>
   #include <scl_j1939.h>
   #include <scl_pgb_j1939.h>
   #include <applib_private.h>
   #include <applib_public.h>
   #include <app_public.h>
}

class BmiJ1939Task: public commTask
{
public:
   BmiJ1939Task( void ) { }
   virtual ~BmiJ1939Task( void ) { }

   bool StartTask( const BmiJ1939Config& appConfig );
   void StopTask( void );

   // The following members are used by the OEL
   static void DummyFunction( void );
   static const real_32                         m_j1939TaskDelay_s;
   static const real_32                         m_j1939TaskPeriod_s;
   static const real_32                         m_j1939TaskWdStartDelay_s;
   static const real_32                         m_j1939TaskWatchdogDelay_s;
   static const unsigned_32                     m_j1939TaskPriority;
   static const int_8                           m_j1939TaskStackThreshold;
   static const unsigned_16                     m_j1939TaskStackSize;
   static const oel_rtos_init_object_t* const   m_OelInitListStartup[];
   static const oel_rtos_posix_task_config_t    m_OelTaskConfigTable;
   static unsigned_16 m_base_can_port;
   static unsigned_8 m_j1939_preferred_address;


private:
   static void OelJ1939TaskImplementation( void );
   static void OelStartupInit( const oel_rtos_init_object_t* never_used );

   static BmiJ1939Config::PGNTableEntries_t     m_appCfgPGNs;
   static BmiJ1939Config::CDLPIDTableEntries_t  m_appCfgPGBPIDs;
   static BmiJ1939Config::CDLPIDTableEntries_t  m_appCfgReadPIDs;
   static BmiJ1939Config::CDLPIDTableEntries_t  m_appCfgMapPIDs;
   static BmiJ1939Config::CDLPIDTableEntries_t  m_appCfgADTPIDs;
   static BmiJ1939Config::EXTIDTableEntries_t   m_appCfgEXTIDs;
   static bool                                  m_taskStarted;
   static volatile bool                         m_taskIsToStop;
   static oel_rtos_task_id_t                    m_OelJ1939ControlTaskId;
   static const oel_rtos_init_object_t          m_OelInitObjectStartup;
   static BmiJ1939Config::SclHealthPeerConfigTableEntries_t m_SclHealthPeerConfigTable;
};

#endif // BMIJ1939TASK_H_
