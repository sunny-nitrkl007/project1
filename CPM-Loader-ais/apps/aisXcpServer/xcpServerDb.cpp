#include <iostream>

#include <ais/log/Logger.h>

#include "xcp_server/XCP.h"
#include "xcp_server/XCPServer.h"
#include "xcpServerDb_private.h"

static XCPServer_t * pXCP1_;
static XCPServer_t * pXCP2_;

/*
 * Should probably get some of this from task configuration.
 *  For example, the event period and UDP port should be configurable.
 */
static const XCPServer_Config_t XCP1UDPConfig = {
    XCP_XPORT_UDP,  // UDP or CAN
    60000,          // UDP Port
    0,              // Master CAN ID, set MSB of 32 bit to indicate 29 bit ID
    0,              // Slave CAN ID, set MSB of 32 bit to indicate 29 bit ID
    0,              // Broadcast CAN ID, set MSB of 32 bit to indicate 29 bit ID
    10,             // # DAQ lists (0-192)
    1,              // # ODTs per DAQ
    255,            // # ODT entries per ODT, must be < MAX_DTO - 1 and <= 255
    8,              // Max ODT entry size in bytes (1..255, 8 works for most implementations)
    255,            // MAX_CTO (8..255)
    1024,           // MAX_DTO (8..~1500 on UDP)
    1,              // Num Events (MAX_EVENTS)
    {
            { 1, XCP_EVENT_TU_10MS}, // EventID 0, 10 ms
            //{ 1, XCP_EVENT_TU_100MS}, // EventID 1, 100 ms
    },
};

static const XCPServer_Config_t XCP2UDPConfig = {
    XCP_XPORT_UDP,  // UDP or CAN
    60001,          // UDP Port
    0,              // Master CAN ID, set MSB of 32 bit to indicate 29 bit ID
    0,              // Slave CAN ID, set MSB of 32 bit to indicate 29 bit ID
    0,              // Broadcast CAN ID, set MSB of 32 bit to indicate 29 bit ID
    10,             // # DAQ lists (0-192)
    1,              // # ODTs per DAQ
    255,            // # ODT entries per ODT, must be < MAX_DTO - 1 and <= 255
    8,              // Max ODT entry size in bytes (1..255, 8 works for most implementations)
    255,            // MAX_CTO (8..255)
    1024,           // MAX_DTO (8..~1500 on UDP)
    1,              // Num Events (MAX_EVENTS)
    {
            { 1, XCP_EVENT_TU_10MS}, // EventID 0, 10 ms
    },
};

/*
 * xcpServerInit()
 */
bool xcpServerDbInit(xcp_server::ParameterDb& db)
{
    bool everything_ok = true;

    AIS_LOG_INFO("XCPServer::init");

    pXCP1_ = XCPServer_new();
    if (nullptr != pXCP1_) {
    	if (XCPServer_init(pXCP1_, &XCP1UDPConfig)) {
    		AIS_LOG_DEBUG("XCP1 Initialization successful.");

    		// Register the database with the server.
    		db.registerWithServer(pXCP1_);

    		AIS_LOG_DEBUG("XCP1 Database registered.");
    	} else {
    		AIS_LOG_FATAL("XCP1 XCPServer initialization failed.");
            everything_ok = false;
        }
    } else {
        AIS_LOG_FATAL("XCP1 XCPServer creation failed.");
        everything_ok = false;
    }

    pXCP2_ = XCPServer_new();
    if (nullptr != pXCP2_) {
        if (XCPServer_init(pXCP2_, &XCP2UDPConfig)) {
            AIS_LOG_DEBUG("XCP2 Initialization successful.");

            // Register the database with the server.
            db.registerWithServer(pXCP2_);

            AIS_LOG_DEBUG("XCP2 Database registered.");
        } else {
            AIS_LOG_FATAL("XCP2 XCPServer initialization failed.");
            everything_ok = false;
        }
    } else {
        AIS_LOG_FATAL("XCP2 XCPServer creation failed.");
        everything_ok = false;
    }


    return everything_ok;
}


bool xcpServerDbUpdate()
{
	AIS_LOG_INFO("XCPExampleServerTask::update");

    // Update the XCP server
    XCPServer_main(pXCP1_);
    XCPServer_procEvent(pXCP1_, 0);

    XCPServer_main(pXCP2_);
    XCPServer_procEvent(pXCP2_, 0);

    return true;
}

void xcpServerDbCleanup()
{
    AIS_LOG_INFO("XCPExampleServerTask::cleanup");

    // Cleanup the XCP server.
    if (nullptr != pXCP1_) {
        XCPServer_cleanup(pXCP1_);
        XCPServer_free(pXCP1_);
        pXCP1_ = nullptr;
    }

    if (nullptr != pXCP2_) {
        XCPServer_cleanup(pXCP2_);
        XCPServer_free(pXCP2_);
        pXCP2_ = nullptr;
    }
}

