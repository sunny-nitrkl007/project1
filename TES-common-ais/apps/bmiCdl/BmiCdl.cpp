#include <thread>
#include <chrono>

#ifndef BMICDLCDL2DEF_H
#include "BmiCdlCdl2Def.h"
#endif

#ifndef BMICDLUTIL_H
#include "BmiCdlUtil.h"
#endif

#ifndef BMICDL_H
#include "BmiCdl.h"
#endif

using namespace task;

BmiCdlWrapper CdlWrapper;
BmiCdlCdl2CbsParmApp_t* BmiCdlCbsParamTbl;

AbstractTaskCore* task::getTaskImplementation(void)
{
	static BmiCdl thisTask("BmiCdl");
	return dynamic_cast<Task *>(&thisTask);
}

BmiCdl::BmiCdl(const std::string& taskName) :
	Task(taskName),  
	AppRegList( taskName ),
	AppRegInput_( nullptr ),
	AppRegOutput_( nullptr ),
	DataLinkDataOutput_( nullptr)
{

}

BmiCdl::~BmiCdl()
{
}

bool BmiCdl::initialize()
{
    uint32_t keyoffTime = 0;
	AIS_LOG_INFO("BmiCdl::initialize");

    AppRegList.SetAppRegAttr(getTaskName());

	DataLinkDataOutput_ = dynamic_cast<DataLinkDataOutput*>(InterfaceDb::fetch("DataLinkDataOutput"));
	AppRegOutput_ = dynamic_cast<AppRegOutput*>( InterfaceDb::fetch("AppRegOutput") );
	AppRegInput_ = dynamic_cast<AppRegInput*>( InterfaceDb::fetch("AppRegInput") );

	if (!DataLinkDataOutput_)
	{
		AIS_LOG_FATAL("no DataLinkDataOutput_ interface defined");
		return false;
	}
	
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
	
	if(!(getTaskConfig().get("BmiCdlAppKeyoffTimeout", keyoffTime)))
	{
		keyoffTime = 0;
	}
	printf("Key off Timeout : %u \n" , keyoffTime);
	AppRegList.SetKeyOffTimeOutMSec(keyoffTime);

	ConfigSection rubyCfg = getTaskConfig();
	Cfg.ParseConfig(&rubyCfg);
	ReqRateSec = (float)(1.0 / Cfg.CycleRateHz);

#ifndef NON_SPECIFIC_MACHINE_CONFIG // Disable for testing

	// Reading MachineSpecificConfig section is only for application
	if(!getTaskParser().getSection("MachineSpecificConfig", rubyCfg))
	{
		AIS_LOG_FATAL("Machine Specific Config section not found.");
		return false;
	}
	else
	{
		if(!Cfg.ReadJsonFilePath(&rubyCfg)) 
		{
			AIS_LOG_FATAL("Failed to read JSON config file path from ruby file.");
			return false;
		}
	}

#else

	// this is for common apps bmiCdl testing only
	
	if(!Cfg.ReadJsonFilePath(&rubyCfg)) 
	{
		AIS_LOG_FATAL("Failed to read JSON config file path from ruby file.");
		return false;
	}

#endif

	if (!Cfg.ReadConfigJsonFile())
	{
		AIS_LOG_FATAL("Unable to open JSON file or it's not constructed properly");
		return false;
	}

	if (!Cfg.ValidateTables())
	{
		AIS_LOG_FATAL("Parm or ECM table didn't follow the rules, check JSON file.");
		return false;
	}

	//Find number of elements in table.
	uint16_t numParams = BmiCdlAppCfgTbl.Header.num_table_entries;

	//Create param table.
	BmiCdlCbsParamTbl = new BmiCdlCdl2CbsParmApp_t[numParams];
	BmiCdlCbsParamTbl->Header = BmiCdlAppCfgTbl.Header;
	const BmiCdlParamCfg_t* paramCfgPtr = NULL;

	for (uint16_t indx = 0; indx < numParams; indx++)
	{
		paramCfgPtr = &BmiCdlAppCfgTbl.ParamCfgTbl[indx];
		BmiCdlCbsParamTbl->CbsParamTbl[indx] = paramCfgPtr->CbsParamTbl;
	}



	CdlWrapper.Initialize();

	return true;
}

bool BmiCdl::executive()
{
	AIS_LOG_DEBUG("executive");

	//Publish CDL Data
	if (Cfg.publishDatalinkData) {
	    CdlWrapper.PublishCdlData(DataLinkDataOutput_);
	}

	if(AppRegInput_)
	{
 		UpdateRegistrations();
	}
	// measure cycle rate and print out rate every 100 cycles
	static int cn = 0;
	cn++;
	static TimeStamp ts;
	TimeStamp last = ts;
	ts = localhostNow();
	double cr = (ts - last).toDouble();

	if (cn % 5 == 1)
	{
		AIS_LOG_DEBUG("cycle rate is %lf hertz\n", 1.0 / cr);
	}
	
	return true;
}

void BmiCdl::UpdateRegistrations(void)
{
    AIS_LOG_INFO( "AppRegTest::UpdateRegistrations" );

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

// Tests
// 1. task with an executive thread at 100Hz, determine if timing is periodic as expected (.01s between cycles)
// 2. task with 100Hz thread, receiving from 3 interfaces, data published at 1Hz, 20Hz, 100Hz
// 3. publishing data from both callback methods and from executive method
// 4. interfaces with 1 and 10 deep queues
// 5. reading 1 at a time, versus draining queue in callback
// 6. reading data in executive versus in a callback

void BmiCdl::cleanup()
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
	
	AIS_LOG_INFO("BmiCdl::cleanup");

	//delete[] BmiCdlCbsParamTbl;
}
