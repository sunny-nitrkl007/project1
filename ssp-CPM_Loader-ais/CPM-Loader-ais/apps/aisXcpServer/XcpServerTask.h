/**
***************************************************************************
* @file XcpServerTask.h
*
* A simple task to use as an empty starting point
*
* Copyright 2010
*
* National Robotics Engineering Center, Carnegie Mellon University
* 10 40th Street, Pittsburgh, PA 15201
* www.rec.ri.cmu.edu
*
* Control Instructions (who can see this code): NREC Confidential.
* Not for public release unless permission granted by program manager.
*
* Usage Rights (who can use this code): Usage allowed for all NREC
* programs with permissions from author and program manager.
*
* This notice must appear in all copies of this file and its derivatives.
*
* Created under Program: ACRS
*
* History of Significant Contributions (don't put commit logs here):
* 2010-10-22 cbaker@rec.ri.cmu.edu  Created file.
***************************************************************************
*/

#ifndef XCPSERVERTASK_H_
#define XCPSERVERTASK_H_

#include <ais/task/Task.h>
//#include <ais/interfaces/Example/InterfaceTypes.h> // for ExampleInput

#include "XcpScsInputsDb.h"
#include "TipoffAssistLogging.hpp"

/**@brief A Do-Nothing Task as a starting point
 *
 */

class XcpServerTask: public task::Task {
public:
    // task::Task construction requires a task name
    XcpServerTask( const std::string& taskName );

    // ALWAYS virtual destructors for polymorphic classes
    virtual ~XcpServerTask( );

    // principal task::Task interface: all derivatives must implement these

    // called once, at startup, after comms are connected
    virtual bool initialize( );

    // called periodically, according to the task config file
    virtual bool executive( );

    // called on the first Ctrl-C for pre-exit cleanup
    virtual void cleanup( );

    XcpScsInputs m_xcpScsInputs;
    TipoffAssistLogging toaLogging;

private:

};

#endif
