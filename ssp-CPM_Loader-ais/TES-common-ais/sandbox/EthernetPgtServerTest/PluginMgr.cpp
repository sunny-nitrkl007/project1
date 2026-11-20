///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    PluginMgr.cpp
//
// @brief   Implements TaskPluginMgr::addPlugins()
///////////////////////////////////////////////////////////////////////////////
#include <plugins/EthernetPgtServer/EthernetPgtServer.h>

#include "EthernetPgtServerTest.h"
#include "src_app/app_rtos_config.h"
#include "EthernetPgtServerTestDataProducer.hpp"

void EthernetPgtServerTest::oelUpdate()
{
    AIS_LOG_INFO("Updating OEL Plugins");
    TaskPluginMgr::callOelUpdateFunctions(TaskInfo::OelTaskType::NA);
}

bool EthernetPgtServerTest::addPlugins()
{
    // Ethernet Pgt Server
    auto& ethernetPgtServer = addPlugin<EthernetPgtServer>();

    // Test Data producer
    addPlugin<EthernetPgtServerTestDataProducer>(ethernetPgtServer);

    // Output/Server plugins should be last
    movePluginToEnd(ethernetPgtServer);

    // Assign callback function
    appUpdateFunction = EthernetPgtServerTest::oelUpdate;

    // Return false if any plugins have faulted
    return addPluginsSuccessful();
}
