#include <thread>
#include <chrono>

#include <commTask/commTask.h>
#include <ais/task/Task.h>
#include <interfaces/DataLinkDataWrapper/DataLinkDataWrapper.h>
#include "BmiEthWrapper.h"
#include <bmi/bmi_ethernet_parser.h>
#include <bmi/bmi_ethernet_parser.h>
#include "BmiEth.h"

using namespace task;
using namespace tes_common_ais;

////////////////////////////////////////////////////////////////////////////
// Function        : task::getTaskImplementation
// Description     : Wrapper that creates an instance of the class implementing this app
// Return Type     : AbstractTaskCore* - Task attributes
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
AbstractTaskCore* task::getTaskImplementation(void)
{
   static BmiEth thisTask("BmiEthernet");
   return dynamic_cast<Task *>(&thisTask);
}

BmiEth::BmiEth( const std::string& taskName ):
                      Task( taskName ),
					  AppRegList( taskName ),
					  AppRegInput_( nullptr ),
					  AppRegOutput_( nullptr )
{
}

BmiEth::~BmiEth( )
{
}

bool BmiEth::initialize()
{

	bool initSuccess = false;
	uint32_t keyoffTime = 0;
	AIS_LOG_NOTICE("BmiEthernet::initialize");

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

	if(!(getTaskConfig().get("BmiEthAppKeyoffTimeout", keyoffTime)))
	{
		keyoffTime = 0;
	}
	AIS_LOG_INFO("Key off Timeout : %u \n" , keyoffTime);

	if(!(getTaskConfig().get("PgtClientFid", pgtClientFidA6N2)))
	{
		pgtClientFidA6N2 = 0;
	}

	if(!(getTaskConfig().get("ClientSessionTimeOut", ClientSessionTimeout)))
	{
		ClientSessionTimeout = 0;
	}

	// Reading MachineSpecificConfig section for Application
	ConfigSection rubyCfg = getTaskConfig();

	if (!getTaskParser().getSection("MachineSpecificConfig", rubyCfg))
	{
		AIS_LOG_FATAL("Machine Specific Config section not found.");
		initSuccess = false;
	}
	else
	{
		// Parse application configuration first thing
		bmi_config_parser::BmiEthcfg_t bmiEthCfgTbl;
		std::string filename;
		if (!rubyCfg.get("BMI_ETH_CONFIG_JSON_FILE_PATH", filename))
		{
			AIS_LOG_ERROR("Unable to find '%s' parameter in .rb", filename.c_str());
		}
		else if (bmi_config_parser::ParseJSONFile(filename, bmiEthCfgTbl))
		{
			AIS_LOG_INFO("application config parsing successful.");

			bmi_config_parser::PrintConfigTables(bmiEthCfgTbl);

			// Initialize SCS interfaces and start the handler, Initialize BmiEthernet.
			if( AddToDataLinkDataWrapper(bmiEthCfgTbl) && DataLinkDataWrapper::Initialize() && EthWrapper.Initialize(bmiEthCfgTbl, pgtClientFidA6N2, ClientSessionTimeout) )
			{
				AIS_LOG_INFO("application Initialization successful");
				initSuccess = true;
			}
			else
			{
				AIS_LOG_FATAL("Unable to Initialize Ethernet Application");
				initSuccess = false;
			}

		}
		else
		{
			AIS_LOG_FATAL("Unable to parse the Json config file");
			initSuccess = false;
			//Are we logging proper error messages when app failed to initialize?
		}
	}

	return initSuccess;
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiEth::executive
// Description     : Function that is invoked from the AIS framework
//                   periodically after a successful application initialization
// Return Type     : bool - 'true' if the cycle was successful, 'false' - if
//                   the application cycle has failed and the application
//                   requires a shutdown
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiEth::executive( )
{
	AIS_LOG_DEBUG("BmiEthernet::executive");

	//Send out any accumulated data
	DataLinkDataWrapper::SendDataLinkData();
	
	UpdateRegistrations();	

	return true;
}

void BmiEth::UpdateRegistrations(void)
{
	AIS_LOG_DEBUG( "AppRegTest::UpdateRegistrations" );
	
    if(AppRegInput_)
    {
		AppReg appRegInfo;

		while (AppRegInput_->get(appRegInfo))
		{
			AIS_LOG_INFO("Register Req type: %d App Name: %s dest app name: %s state: %d -> RecvdAppName: %s \n",
					appRegInfo.GetMsgType(), appRegInfo.GetAppName().c_str(),
					appRegInfo.GetDestAppName().c_str(), appRegInfo.GetAppState(),
					AppRegList.GetAppName().c_str());

			if(!appRegInfo.IsMsgAddressedToMe(AppRegList.GetAppName()))
				continue;

			if(appRegInfo.GetMsgType() == AppRegStorage::APP_REG_REQ)
			{
				AppRegList.UpdateAppRegState(&appRegInfo);
				AIS_LOG_INFO("Update reg response %d", appRegInfo.GetRegStatus());
				AppRegOutput_->publish( appRegInfo );
			}
		}
    }

}
// Tests
// 1. task with an executive thread at 100Hz, determine if timing is periodic as expected (.01s between cycles)
// 2. task with 100Hz thread, receiving from 3 interfaces, data published at 1Hz, 20Hz, 100Hz
// 3. publishing data from both callback methods and from executive method
// 4. interfaces with 1 and 10 deep queues
// 5. reading 1 at a time, versus draining queue in callback
// 6. reading data in executive versus in a callback

////////////////////////////////////////////////////////////////////////////
// Function        : BmiEth::cleanup
// Description     : Cleanup function that is invoked from the AIS framework
//                   during the application shutdown
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiEth::cleanup( )
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

   	if(AppRegList.IsKeyOffTimeOut())
   	{
   		AIS_LOG_INFO( "Timed out....exiting." );
   	}

   	AIS_LOG_NOTICE( "BmiEthernet::cleanup" );

}
