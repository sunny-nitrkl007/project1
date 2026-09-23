/**
***************************************************************************
* @file XcpServerTask.cpp
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
#include <unistd.h>

#include <boost/filesystem.hpp>

#include <ais/interfaces/baseTypes/ChannelInterface.h>

#include "xcp_server/XCPServer.h"
#include "xcpServerDb_private.h"

#include "XcpServerTask.h"

namespace fs = boost::filesystem;
using namespace task;

#define XCP_SERVER_APP_LOG_ROOT (R"(/opt/appdata/CPM/debug)")

#define XCP_SERVER_APP_TOA_LOG_PATH (R"(/opt/appdata/CPM/debug/toa_log.csv)")

// 12 TOA per hour, 10 hours, 80 bytes per TOA = 9600 bytes per shift
#define XCP_SERVER_APP_TOA_LOG_MAX_SIZE (10000)
//#define XCP_SERVER_APP_TOA_LOG_MAX_SIZE (300)

static void makeAppLogRoot()
{
    boost::system::error_code ec;

    // Make sure the directory exists
    fs::create_directories(XCP_SERVER_APP_LOG_ROOT, ec);

    if (ec) {
        AIS_LOG_ERROR("Cannot create %s directory for logging.", XCP_SERVER_APP_LOG_ROOT);
    }
}

// Tasks are singletons within any one process: this is the singleton accessor
AbstractTaskCore* task::getTaskImplementation(void)
{
    // it is important to realize that the quoted string controls the name of the
    // default configuration file.  In this case, the use of "XcpServerTask" means that
    // there must be a file named "XcpServerTask.rb" in the config directory for this
    // task to successfully start up.
    static XcpServerTask thisTask("XcpServerTask");
    return &thisTask;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Constructs an instance of this class.
///
///////////////////////////////////////////////////////////////////////////////
XcpServerTask::XcpServerTask(const std::string &taskName) :
        Task(taskName),
        m_xcpScsInputs(),
        toaLogging()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys this class
///
///////////////////////////////////////////////////////////////////////////////
XcpServerTask::~XcpServerTask()
{
}

bool XcpServerTask::initialize()
{
    AIS_LOG_NOTICE("Hello from %s",getTaskName().c_str() );

    ConfigSection cs;
    if ( !getTaskParser().getSection("ScsRxTimeouts", cs) )
    {
        AIS_LOG_FATAL( "Couldn't find ScsRxTimeouts Config Section in rb file" );
        return false;
    }
    m_xcpScsInputs.initReadInterface( cs );

    xcpServerDbInit(m_xcpScsInputs.db);

    makeAppLogRoot();

    toaLogging.init(XCP_SERVER_APP_TOA_LOG_PATH, XCP_SERVER_APP_TOA_LOG_MAX_SIZE);

    return true; // false causes the application to bail
}

bool XcpServerTask::executive()
{
    AIS_LOG_NOTICE("%s: executive  (pid: %d)", getTaskName().c_str(), getpid());

    // this is where you do periodic work
    xcpServerDbUpdate();

    m_xcpScsInputs.update();

    toaLogging.update(
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.tipoffAssistActive,
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.tipoffAssistActiveEid,
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.TruckStartWeight,
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.truckTargetWeight,
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.DispBestBktWt.val,
            m_xcpScsInputs.m_lpsSaJobMgrTxChannel.DispBestBktWt.isOk,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.m_TipoffInputs.tilt_valve_cmd,
            m_xcpScsInputs.m_lpsSaWeighTxChannel.LiftPosition.angle,
            m_xcpScsInputs.m_lpsSaWeighTxChannel.TiltPosition.bucketAngle,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.m_TipoffOutputs.weigh_status_out,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.m_TipoffOutputs.arbitrated_payload_norm_error_out,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.m_TipoffOutputs.payload_norm_stdev_out,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.m_TipoffOutputs.unsecured_PFW_status,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.m_TipoffOutputs.unsecured_payload_upper_bound_norm,
            m_xcpScsInputs.m_lpsSaWeighDebugChannel.m_TipoffOutputs.unsecured_payload_lower_bound_norm);

    return true; // false again causes the application to bail
}

void XcpServerTask::cleanup()
{
    AIS_LOG_NOTICE("%s: cleanup  (pid: %d)", getTaskName().c_str(), getpid());

    // this is where you would clean up your allocated resources (if any)
    xcpServerDbCleanup();

    return; // you can't really fail to "clean up"
}
