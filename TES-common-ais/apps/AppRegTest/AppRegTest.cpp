#include "AppRegTest.h"

using namespace task;

AppReg regInfo;
AppRegStorage::AppRegRet_t ret;
TimeStamp shutdownInitTime;

AbstractTaskCore* task::getTaskImplementation(void)
{
    static AppRegTest thisTask("AppRegTest");
    return dynamic_cast<Task *>(&thisTask);
}

AppRegTest::AppRegTest( const std::string& taskName ):
    Task( taskName ),
    AppRegInput_( NULL ),
    AppRegOutput_( NULL )
{
}

AppRegTest::~AppRegTest( )
{
}

bool AppRegTest::initialize( )
{
    AIS_LOG_INFO( "AppRegTest::initialize" );

    ShutdownRequested = false;
    AppRegistered = false;

    AppRegInput_ = dynamic_cast<AppRegInput*>( InterfaceDb::fetch( "AppRegInput" ) );
    AppRegOutput_ = dynamic_cast<AppRegOutput*>( InterfaceDb::fetch("AppRegOutput") );


    if (!AppRegInput_)
    {
        AIS_LOG_FATAL( "no AppRegInput_ interface defined" );
        return false;
    }

    if ( !AppRegOutput_ )
    {
        AIS_LOG_FATAL( "no AppRegOutput_ interface defined" );
        return false;
    }

    if(getTaskConfig().get("AppName", AppName))
    {
        AIS_LOG_INFO("AppName: %s", AppName.c_str());
    }
    else
    {
        AIS_LOG_INFO("Failed to read AppName: %s", AppName.c_str());
        return false;
    }

    if(getTaskConfig().get("DestAppName", DestAppName))
    {
        AIS_LOG_INFO("DestAppName: %s", DestAppName.c_str());
    }
    else
    {
        AIS_LOG_INFO("Failed to read DestAppName: %s", DestAppName.c_str());
        return false;
    }

    if(getTaskConfig().get("KeyOffTimeOutMsec", keyOffTimeOutMSec))
    {
        AIS_LOG_INFO("keyOffTimeOutMSec: %d",keyOffTimeOutMSec);
    }
    else
    {
        keyOffTimeOutMSec = 3000;
        AIS_LOG_INFO("Failed to read KeyOffTimeOutMsec from ruby file. Set default time out to %d MSec.", keyOffTimeOutMSec);
    }

    //Creating instance dynamically because AppName read from config file.
    RegInst = new AppRegStorage(AppName, keyOffTimeOutMSec);
    if(NULL == RegInst)
    {
        return false;
    }

    return true;
}

bool AppRegTest::executive( )
{
    AIS_LOG_INFO( "executive" );

    if(!AppRegistered)
    {
        regInfo.SetAppRegAttr(AppName, AppRegStorage::APP_REG_STATE_ACTIVE, DestAppName);
        AppRegOutput_->publish( regInfo );
        AIS_LOG_INFO("Reg req sent.");
    }

    UpdateRegistrations();

    //PrintRegistrations
    PrintAppRegistrations();

    // measure cycle rate and print out rate every 100 cycles
    static int cn = 0;
    cn++;
    static TimeStamp ts;
    TimeStamp last = ts;
    ts= localhostNow();
    double cr = (ts - last).toDouble();

    if ( cn % 5 == 1)
    {
        AIS_LOG_INFO( "cycle rate is %lf hertz\n", 1.0 / cr );
    }

    return true;
}

void AppRegTest::UpdateRegistrations(void)
{
    AIS_LOG_INFO( "AppRegTest::UpdateRegistrations" );

    if ( !AppRegOutput_ )
    {
        AIS_LOG_FATAL( "AppRegOutput_ interface is null upon calling from clean up." );
    }

    while (AppRegInput_->get(regInfo))
    {
        AIS_LOG_DEBUG("Register Req type %d App Name: %s Dest app Name: %s state: %d - appname: %s",
                  regInfo.GetMsgType(), regInfo.GetAppName().c_str(), regInfo.GetDestAppName().c_str(),
                  regInfo.GetAppState(), AppName.c_str());

        if(!regInfo.IsMsgAddressedToMe(this->AppName)) continue;

        if(regInfo.GetMsgType() == AppRegStorage::APP_REG_REQ)
        {
            RegInst->UpdateAppRegState(&regInfo);
            AIS_LOG_INFO("Update reg response %d", regInfo.GetRegStatus());
            AppRegOutput_->publish( regInfo );
        }
        else if(regInfo.GetMsgType() == AppRegStorage::APP_REG_RESP)  //use taskName instead of appName in real app.
        {
            if(regInfo.GetRegStatus() == AppRegStorage::APP_REG_APP_NAME_REGISTERED ||
                    regInfo.GetRegStatus() == AppRegStorage::APP_REG_APP_NAME_ALREADY_REGISTERED )
            {
                AppRegistered = true;
                AIS_LOG_INFO("AppName : %s registered status: %d.", AppName.c_str(), regInfo.GetRegStatus());
            }
        }
    }
}

void AppRegTest::PrintAppRegistrations(void)
{
    AIS_LOG_INFO("*************** %s Registrations (count: %d) *************", AppName.c_str(), RegInst->GetAppRegCount());
    for(std::string appName : RegInst->GetActiveAppNames())
    {
        AIS_LOG_INFO("App Name: %s", appName.c_str());
    }
}
// Tests
// 1. task with an executive thread at 100Hz, determine if timing is periodic as expected (.01s between cycles)
// 2. task with 100Hz thread, receiving from 3 interfaces, data published at 1Hz, 20Hz, 100Hz
// 3. publishing data from both callback methods and from executive method
// 4. interfaces with 1 and 10 deep queues
// 5. reading 1 at a time, versus draining queue in callback
// 6. reading data in executive versus in a callback

void AppRegTest::cleanup( )
{
    AIS_LOG_WARN( "AppRegTest::cleanup" );

    //unregister
    //if(AppRegistered)
    //{

    regInfo.SetAppRegAttr(AppName, AppRegStorage::APP_REG_STATE_INACTIVE, DestAppName);
    AppRegOutput_->publish( regInfo );

    AIS_LOG_INFO("Unregister Req type %d App Name: %s Dest app Name: %s state: %d",
             regInfo.GetMsgType(), regInfo.GetAppName().c_str(), regInfo.GetDestAppName().c_str(),
             regInfo.GetAppState());


    //}

    AIS_LOG_INFO( "while(!RegInst->IsKeyOffTimeOut()) %d   %d   %d", RegInst->IsKeyOffTimeOut(),
              RegInst->GetTimeDiffMSec(),
              RegInst->GetKeyOffTimeOutMSec());
    while(!RegInst->IsKeyOffTimeOut())
    {
        AIS_LOG_INFO("IsAppRegListEmpty %d  reg active count %d. Waiting %d : %d", RegInst->IsAppRegListEmpty(),
                 RegInst->GetAppRegCount(),
                 RegInst->GetTimeDiffMSec(),
                 keyOffTimeOutMSec);

        // This line can be above while loop. left inside while loop for above diag information if needed.
        if(RegInst->IsAppRegListEmpty())
        {
            AIS_LOG_INFO("No active registrations....exiting.");
            break;
        }

        UpdateRegistrations();
        PrintAppRegistrations();
        usleep(1000);
    }

    if(RegInst->GetTimeDiffMSec() >= keyOffTimeOutMSec)
    {
        AIS_LOG_INFO( "Timed out....exiting." );
    }

    delete RegInst;

    AIS_LOG_INFO( "AppRegTest is shutdown." );
}
