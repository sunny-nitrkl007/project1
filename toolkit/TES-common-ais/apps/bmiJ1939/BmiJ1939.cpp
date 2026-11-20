////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939
//
// File Name: BmiJ1939.cpp
//
//  Abstract: Definitions for the class handling Basic Machine
//            Interface J1939 protocols
//
////////////////////////////////////////////////////////
#include <thread>
#include <chrono>

#include "BmiJ1939.h"
#include "BmiJ1939Config.h"
using namespace task;
////////////////////////////////////////////////////////////////////////////
// Function        : task::getTaskImplementation
// Description     : Wrapper that creates an instance of the class implementing this app
// Return Type     : AbstractTaskCore* - Task attributes
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
task::AbstractTaskCore* task::getTaskImplementation( void )
{
   static BmiJ1939 thisTask( "BmiJ1939" );
   return dynamic_cast<task::Task*>( &thisTask );
}
BmiJ1939::BmiJ1939( const std::string& taskName ):
    task::Task( taskName ),
    AppRegList( taskName ),
    AppRegInput_( nullptr ),
    AppRegOutput_( nullptr )


{
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939::initialize
// Description     : Initialization function that is invoked from the AIS framework
//                   during the application start-up
// Return Type     : bool - 'true' if the initialization was successful, 'false' otherwise
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939::initialize( void )
{
    bool initSuccessful = false;
    uint32_t keyoffTime = 0;

    AppRegList.SetAppRegAttr(getTaskName());

	AppRegOutput_ = dynamic_cast<AppRegOutput*>( InterfaceDb::fetch("AppRegOutput") );
	AppRegInput_ = dynamic_cast<AppRegInput*>( InterfaceDb::fetch("AppRegInput") );
	if (!AppRegInput_)
	{
		AIS_LOG_FATAL("no AppRegInput_ interface defined");
		return false;
	}

	if (!AppRegOutput_)
	{
		AIS_LOG_FATAL("no AppRegOutput_ interface defined");
		return false;
	}

	ConfigSection rubyCfg = getTaskConfig();

	if ( !getTaskConfig().get( "CAN_port", m_J1939Task.m_base_can_port ) )
	{
	    m_J1939Task.m_base_can_port = CAN_PORT_1; //default
	}

	// Check for invalid port configuration
    if ( m_J1939Task.m_base_can_port > CAN_PORT_2 || m_J1939Task.m_base_can_port < CAN_PORT_0)
    {
        AIS_LOG_FATAL( "Invalid port configuration. Configure ports in the range (0-2)" );
        return false;
    }

    if(!(getTaskConfig().get("J1939_Preferred_Address", m_J1939Task.m_j1939_preferred_address)))
    {
        m_J1939Task.m_j1939_preferred_address = 0x81; //default Mu8_preferred_address
    }

    AIS_LOG_INFO("J1939_Preferred_Address : 0x%X " , m_J1939Task.m_j1939_preferred_address);

    // Check for invalid J1939 Source Address
    if ( m_J1939Task.m_j1939_preferred_address > VALID_ADDRESS_MAX || m_J1939Task.m_j1939_preferred_address < VALID_ADDRESS_MIN )
    {
        AIS_LOG_FATAL( "Invalid Source Address configuration. Configure Dynamic address range of 128 to 247($80 to $F7)" );
        return false;
    }

    if(!(getTaskConfig().get("BmiJ1939AppKeyoffTimeout", keyoffTime)))
	{
		keyoffTime = 0;
	}

	AIS_LOG_INFO("Key off Timeout : %u \n" , keyoffTime);
	AppRegList.SetKeyOffTimeOutMSec(keyoffTime);

    // Reading MachineSpecificConfig section is only for application
    if (!getTaskParser().getSection("MachineSpecificConfig", rubyCfg))
    {
        AIS_LOG_FATAL("Machine Specific Config section not found.");
        initSuccessful = false;
    }
    else
    {
        // Set to CAN1 or CAN 2 or CAN3 based on configured CAN Port
        DataLinkParamInfo::DlpDataLinkType_t dataLinkType;
        if (m_J1939Task.m_base_can_port == CAN_PORT_0)
        {
            AIS_LOG_INFO("Configured to use CAN1");
            dataLinkType = DataLinkParamInfo::DATA_LINK_PARAM_CAN1_1939;
        }
        else if (m_J1939Task.m_base_can_port == CAN_PORT_1)
        {
            AIS_LOG_INFO("Configured to use CAN2");
            dataLinkType = DataLinkParamInfo::DATA_LINK_PARAM_CAN2_1939;
        }
        else if (m_J1939Task.m_base_can_port == CAN_PORT_2)
        {
            AIS_LOG_INFO("Configured to use CAN3");
            dataLinkType = DataLinkParamInfo::DATA_LINK_PARAM_CAN3_1939;
        }
        else
        {
            AIS_LOG_FATAL("Unsupported CAN Port configured: %d", m_J1939Task.m_base_can_port);
            dataLinkType = DataLinkParamInfo::DATA_LINK_PARAM_CAN1_1939;
            initSuccessful = false;
        }

        // Parse application configuration first thing (done in BmiJ1939Config constructor)
        auto& appConfig = BmiJ1939Config::GetInstance();
        appConfig.Initialize(&rubyCfg, dataLinkType);
        if (appConfig.ConfigParsed())
        {
            AIS_LOG_INFO("application config parsing successful");
            // Initialize SCS interfaces and start the handler
            initSuccessful = BmiJ1939SCS::SCSInitJ1939(dataLinkType);

            // Last part of the initialization is to start J1939 handler
            initSuccessful &= m_J1939Task.StartTask(appConfig);

    #ifdef WRITE_AUTOMATION_DATA
            J1939_Aut.AutomationInitialise(appConfig);
    #endif
        }
        else
        {
            AIS_LOG_FATAL("Unable to parse the Json config file.");
            initSuccessful = false;
        }
    }

   return initSuccessful;
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939::executive
// Description     : Function that is invoked from the AIS framework
//                   periodically after a successful application initialization
// Return Type     : bool - 'true' if the cycle was successful, 'false' - if
//                      the application cycle has failed and the application
//                      requires a shutdown
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939::executive( void )
{
	//Get Fmi status and update to Data link data
	BmiJ1939TaskInit::GetFmiStatus();

	//Check for any timeout events for the Requested Cat Ext Id's
	BmiJ1939ExtIdHdlr::ExtIdTimeoutEventUpdate();

	// Send out any accumulated data
	BmiJ1939SCS::SendDataLinkData();

	//publish scs object
	
	if(AppRegInput_)
	{
	    UpdateRegistrations();
	}

   return true;
}

void BmiJ1939::UpdateRegistrations(void)
{
    if(AppRegInput_) {
        AppReg appRegInfo;

        while (AppRegInput_->get(appRegInfo)) {
            AIS_LOG_INFO("Register Req type: %d App Name: %s dest app name: %s state: %d -> RecvdAppName: %s \n",
                    appRegInfo.GetMsgType(), appRegInfo.GetAppName().c_str(),
                    appRegInfo.GetDestAppName().c_str(), appRegInfo.GetAppState(),
                    AppRegList.GetAppName().c_str());

            if((appRegInfo.GetMsgType() == AppRegStorage::APP_REG_REQ) && (appRegInfo.IsMsgAddressedToMe(AppRegList.GetAppName()))) {
                AppRegList.UpdateAppRegState(&appRegInfo);
                AIS_LOG_INFO("Update reg response %d", appRegInfo.GetRegStatus());
                AppRegOutput_->publish( appRegInfo );
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939::cleanup
// Description     : Cleanup function that is invoked from the AIS framework
//                   during the application shutdown
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939::cleanup( void )
{
  	// Initialize last update time
  	auto lastUpdateTime = std::chrono::steady_clock::now();

    float cycleRateHertz = static_cast<float>(getCycleRateHz());
    if (cycleRateHertz > 0) {
        uint32_t periodMicroseconds = static_cast<uint32_t>(1000000.f / cycleRateHertz);

        while (!AppRegList.IsAppRegListEmpty() && !AppRegList.IsKeyOffTimeOut()) {
            // Wait until it is time to run
            std::this_thread::sleep_until(lastUpdateTime + std::chrono::microseconds(periodMicroseconds));

            // Get the update time
            lastUpdateTime = std::chrono::steady_clock::now();

            // Update
            executive();
        }
    }

	if (AppRegList.IsKeyOffTimeOut())
	{
		AIS_LOG_INFO( "Timed out....exiting." );
	}

   m_J1939Task.StopTask();
}



