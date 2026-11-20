////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939Task
//
// File Name: BmiJ1939Task.cpp
//
//  Abstract: Implementation of the class that glues
//            the AIS platform task (BmiJ1939) and
//            the OEL task (scl_j1939_control_task).
//            The former sends out SCS objects to other
//            AIS apps, the latter is based on the
//            legacy libraries and is handling
//            the J1939 traffic.
//
////////////////////////////////////////////////////////

#include <ais/log/AisLogger.h>
#include <mc_rtos/mc_rtos_config.h>
#include "BmiJ1939Task.h"
#include "BmiJ1939TaskInit.h"
#include "BmiJ1939Read.h"
#include "BmiJ1939Map.h"
#ifndef BMIJ1939EXTIDHDLR_H
#include "BmiJ1939ExtIdHdlr.h"
#endif
#ifndef BMIJ1939RESTRICTEDREAD_H
#include "BmiJ1939RestrictedRead.h"
#endif

// extern "C" const ApplicationGet_t application_get_table;

static oel_rtos_action_t app_wdog_handler_noop;

static oel_rtos_timer_alarm_handler_t app_wdog_alarm_handler_noop = {
    &app_wdog_handler_noop
};

// App wdog handler to do nothing
static void app_wdog_handler_noop(oel_rtos_action_object_t* oel_rtos_action_object) {
    (void)oel_rtos_action_object;
}

// The following table is used by OEL libraries for system configuration
oel_rtos_posix_config_t app_oel_rtos_posix_config =
      OEL_RTOS_POSIX_CONFIG(
            1,                                                                            // NUMBER_OF_TASKS
            &BmiJ1939Task::m_OelTaskConfigTable,                                          // TASK_CONFIG
            NULL,                                                                         // PRE_IRQ_INIT
            BmiJ1939Task::m_OelInitListStartup,                                           // STARTUP_INIT
            OEL_RTOS_SECONDS_DBL_TO_U32_L20( BmiJ1939Task::m_j1939TaskWdStartDelay_s ),   // WDOG_STARTUP_DELAY
            NULL,                                                                         // WDOG_HANDLER
            BmiJ1939Task::DummyFunction,                                                  // WDOG_STROBE
            TRUE,                                                                         // STACK_CHECK_ENABLE
            static_cast<const unsigned_8>( BmiJ1939Task::m_j1939TaskStackThreshold ),     // SYS_STACK_THRESHOLD
            NULL,                                                                         // STACK_HANDLER
            TRUE,                                                                         // DEBUG
            OEL_RTOS_SECONDS_DBL_TO_U64_L32( BmiJ1939Task::m_j1939TaskPeriod_s ) );       // TICK_PERIOD

// The following table is used by OEL system configuration table above to setup the OEL task
const oel_rtos_posix_task_config_t BmiJ1939Task::m_OelTaskConfigTable = OEL_RTOS_POSIX_TASK_CONFIG_I1(
      &m_OelJ1939ControlTaskId,                                                  // RTOS_TASK_ID_PTR
      OEL_RTOS_SECONDS_DBL_TO_U32_L20( m_j1939TaskDelay_s ),                     // DELAY
      OEL_RTOS_SECONDS_DBL_TO_U32_L20( m_j1939TaskPeriod_s ),                    // PERIOD
      OEL_RTOS_SECONDS_DBL_TO_U32_L20( m_j1939TaskWatchdogDelay_s ),             // WDOG_DELAY
      &app_wdog_alarm_handler_noop,                                              // WDOG_HANDLER
      static_cast<const unsigned_8>( m_j1939TaskStackThreshold ),                // TASK_STACK_THRESHOLD
      const_cast<char*>( "scl_j1939_control_task" ),                             // NAME
      OelJ1939TaskImplementation,                                                // ENTRY
      m_j1939TaskStackSize,                                                      // STACK_SIZE
      m_j1939TaskPriority,                                                       // PRIORITY
      SCHED_FIFO);                                                               // SCHEDULING POLICY

// Declare the rest of the class static data members
const real_32 BmiJ1939Task::m_j1939TaskDelay_s = 0.0;
const real_32 BmiJ1939Task::m_j1939TaskPeriod_s = 0.01;
const real_32 BmiJ1939Task::m_j1939TaskWdStartDelay_s = 0.1;
const real_32 BmiJ1939Task::m_j1939TaskWatchdogDelay_s = m_j1939TaskPeriod_s + m_j1939TaskWdStartDelay_s;
const unsigned_32 BmiJ1939Task::m_j1939TaskPriority = MC_RTOS_TASK_J1939_PRIORITY;
const int_8 BmiJ1939Task::m_j1939TaskStackThreshold = 80;
const unsigned_16 BmiJ1939Task::m_j1939TaskStackSize = 2000;
const oel_rtos_init_object_t* const BmiJ1939Task::m_OelInitListStartup[] = { &m_OelInitObjectStartup, NULL };
BmiJ1939Config::PGNTableEntries_t BmiJ1939Task::m_appCfgPGNs;
BmiJ1939Config::CDLPIDTableEntries_t BmiJ1939Task::m_appCfgPGBPIDs;
BmiJ1939Config::CDLPIDTableEntries_t BmiJ1939Task::m_appCfgReadPIDs;
BmiJ1939Config::CDLPIDTableEntries_t BmiJ1939Task::m_appCfgMapPIDs;
BmiJ1939Config::CDLPIDTableEntries_t BmiJ1939Task::m_appCfgADTPIDs;
BmiJ1939Config::EXTIDTableEntries_t BmiJ1939Task::m_appCfgEXTIDs;
BmiJ1939Config::SclHealthPeerConfigTableEntries_t BmiJ1939Task::m_SclHealthPeerConfigTable;

bool BmiJ1939Task::m_taskStarted = false;
volatile bool BmiJ1939Task::m_taskIsToStop = false;
oel_rtos_task_id_t BmiJ1939Task::m_OelJ1939ControlTaskId;
const oel_rtos_init_object_t BmiJ1939Task::m_OelInitObjectStartup = { &OelStartupInit };
unsigned_16 BmiJ1939Task::m_base_can_port = 0;
unsigned_8 BmiJ1939Task::m_j1939_preferred_address = 0;

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Task::StartTask
// Description     : Called by the BMI-J1939 AIS task to start the
//                   OEL task handling J1939 interface.
//                   Meant to be invoked only once per process life time.
// Return Type     : bool - 'true' if started successfully, 'false' otherwise
// Argument [in]   : const BmiJ1939Config& appConfig - Application configuration
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939Task::StartTask( const BmiJ1939Config& appConfig )
{
   bool taskStarted = false;
   m_appCfgPGNs = appConfig.GetConfiguredPGNs();
   m_appCfgPGBPIDs = appConfig.GetConfiguredPGBPIDs();
   m_appCfgReadPIDs = appConfig.GetConfiguredReadPIDs();
   m_appCfgMapPIDs = appConfig.GetConfiguredMapPIDs();
   m_appCfgADTPIDs = appConfig.GetConfiguredADTPIDs();
   m_appCfgEXTIDs = appConfig.GetConfiguredEXTIDs();
   m_SclHealthPeerConfigTable = appConfig.GetSclHealthPeerConfigTable();

   if ( !m_taskStarted )
   {
      // Fire up the OEL task
      m_taskStarted = true;
      commInitialize();

      taskStarted = true;
   }
   else
   {
      AIS_LOG_ERROR( "J1939 task has been already previously started" );
   }

   return taskStarted;
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Task::StopTask
// Description     : Function that forces the J1939 task loop to exit.
//                   There's no coming back out of this one.
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939Task::StopTask( void )
{
   m_taskIsToStop = true;
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Task::DummyFunction
// Description     : This function does nothing and is used as a dummy callback
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939Task::DummyFunction( void )
{
   // Nothing to do here
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Task::OelStartupInit
// Description     : OEL system start-up initialization function
// Return Type     : None
// Argument [in]   : const oel_rtos_init_object_t* never_used - Object to initialize
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939Task::OelStartupInit( const oel_rtos_init_object_t* never_used )
{
   // "Touch" argument to avoid compiler warning
   (void)never_used;
   uint32_t j1939TaskPeriod_ms = 0;
   j1939TaskPeriod_ms = m_j1939TaskPeriod_s * 1000;
   oel_u_init( NULL );
   // application_get_table.fc_init();
   BmiJ1939TaskInit::InitializeJ1939(j1939TaskPeriod_ms, 
                                       &m_appCfgPGNs, 
                                       &m_appCfgPGBPIDs, 
                                       &m_appCfgADTPIDs,
                                       &m_appCfgEXTIDs, 
                                       m_base_can_port, 
                                       m_j1939_preferred_address, 
                                       &m_SclHealthPeerConfigTable);

   if ( BmiJ1939TaskInit::IsCANInitialized() )
      {

	   /*For adding PID info to Rx pit for Read poll */
	   BmiJ1939Read::ReadReqInitJ1939( &m_appCfgReadPIDs ,j1939TaskPeriod_ms);

	   /*Map Initialization*/
	   BmiJ1939Map::MapInitJ1939( &m_appCfgMapPIDs, j1939TaskPeriod_ms);

      }
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Task::OelJ1939TaskImplementation
// Description     : This function implements a task (thread) that handles
//                   incoming J1939 data
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939Task::OelJ1939TaskImplementation( void )
{
   oel_rtos_task_context_t my_task_context;

   // Perform rtos startup initialization and grab the task context
   oel_rtos_startup_init();
   oel_rtos_task_get_context( &my_task_context );

   // Task's periodic main loop
   while ( !m_taskIsToStop )
   {
      // Wait for synchronizing event
      oel_rtos_event_pend( my_task_context, OEL_RTOS_TIME_EVENT, NULL );

      if ( BmiJ1939TaskInit::IsCANInitialized() )
      {
    	  /*Sending Read request for CAT EXT ID's*/
    	  BmiJ1939ExtIdHdlr::SendCatExtIdRequest( &m_appCfgEXTIDs );
    	  /*For Sending Read request*/
    	  BmiJ1939Read::ReadReqUpdateJ1939( &m_appCfgReadPIDs );

    	  /*Map Request Update*/
    	  BmiJ1939Map::MapReqUpdateJ1939( &m_appCfgMapPIDs );

    	  // Check for any J1939 messages
         scl_j1939_periodic_ctrl_task();


      }
   }
}
