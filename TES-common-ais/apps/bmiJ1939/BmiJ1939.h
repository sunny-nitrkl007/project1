////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939
//
// File Name: BmiJ1939.h
//
//  Abstract: Declaration of the class handling Basic Machine
//            Interface J1939 protocols, includes:
//             - AIS task framework
//             - OEL task framework
//             - Methods implementing both the main AIS task
//               and the hardware interface layer through OEL task
//
////////////////////////////////////////////////////////

#ifndef BMIJ1939_H_
#define BMIJ1939_H_

#include <string>          // std::string
#include <memory>          // std::unique_ptr
#include <ais/task/Task.h>
#include "BmiJ1939Task.h"
#include "BmiJ1939SCS.h"
#include "BmiJ1939TaskInit.h"
#ifndef BMIJ1939EXTIDHDLR_H
#include "BmiJ1939ExtIdHdlr.h"
#endif
#include <interfaces/AppReg/InterfaceTypes.h>
#ifdef WRITE_AUTOMATION_DATA
#include "BmiJ1939Automation.h"
#endif

const uint8_t CAN_PORT_0 = 0;
const uint8_t CAN_PORT_1 = 1;
const uint8_t CAN_PORT_2 = 2;

const uint8_t VALID_ADDRESS_MIN = 0x80;
const uint8_t VALID_ADDRESS_MAX = 0xF7;

class BmiJ1939: public task::Task
{
public:
   BmiJ1939( const std::string& taskName );
   virtual ~BmiJ1939( void ) { }

   virtual bool initialize( void );
   virtual bool executive( void );
   virtual void cleanup( void );
   void UpdateRegistrations();
#ifdef WRITE_AUTOMATION_DATA
   static BmiJ1939Automation J1939_Aut;
#endif

private:
   BmiJ1939Task                     m_J1939Task;
    AppRegStorage AppRegList;
    AppRegInput *AppRegInput_;
    AppRegOutput  *AppRegOutput_;
};

#endif // BMIJ1939_H_
