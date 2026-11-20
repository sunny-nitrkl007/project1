////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939DataHandlers
//
// File Name: BmiJ1939DataHandlers.h
//
//  Abstract: Declaration for the class that handles
//            incoming data over J1939 for the OEL task
//            (scl_j1939_control_task)
//
////////////////////////////////////////////////////////

#ifndef BMIJ1939DATA_H_
#define BMIJ1939DATA_H_
#include <vector>          // std::vector
#include <map>             // std::map
#include "BmiJ1939SCS.h"
#include <scl_adt_j1939.h>
#include <scl_adt_j1939_alloc.h>
#include <scl_adt_j1939_tune.h>

extern "C"
{
   #include <scl_j1939.h>
   #include <scl_pgb_j1939.h>
}

class BmiJ1939DataHandlers
{
public:
   // Callback functions for incoming PIDs
   static scl_pgb_j1939_event_clbk_t BmiJ1939PIDEvents;
   static scl_pgb_j1939_rx_pid_hdlr_t BmiJ1939PIDDefault;

   // Callback functions for incoming PGNs
   static scl_j1939_rx_mpfn_parser_t BmiJ1939PGNDefault;

   //callback function for incoming ADT PID's
   static scl_adt_j1939_client_grp_pid_hdlr_t BmiJ1939ADTDefault;
   static scl_adt_j1939_event_clbk_t BmiJ1939AdtPIDEvents;

   static const scl_j1939_rx_mpfn_parser_t* m_pgnHandlers[];
   static unsigned_16 GetNumPgnHandlers( void );

private:
   BmiJ1939DataHandlers( void ) { }
   virtual ~BmiJ1939DataHandlers( void ) { }

};

#endif // BMIJ1939DATA_H_
