
#include "hornOnStoreTest.h"

#include <time.h>

using namespace task;

AbstractTaskCore* task::getTaskImplementation(void)
{
    static hornOnStoreTest thisTask("hornOnStoreTest");
    return dynamic_cast<Task *>(&thisTask);
}

hornOnStoreTest::hornOnStoreTest( const std::string& taskName ):
    Task( taskName ),
    SwitchInputScsOutput_(NULL),
    LpsSaJobMgrTxChannelInput_(NULL),
    LpsSaJobMgrReqstChannelOutput_(NULL),
    OutputChannelInput_( NULL )
{

}

hornOnStoreTest::~hornOnStoreTest( )
{
}

bool hornOnStoreTest::initialize( )
{
    AIS_LOG_INFO( "hornOnStoreTest::initialize" );

    SwitchInputScsOutput_ = dynamic_cast<SwitchInputScsOutput*>( InterfaceDb::fetch("SwitchInputScsOutput") );
    LpsSaJobMgrTxChannelInput_ = dynamic_cast<LpsSaJobMgrTxChannelInput*>( InterfaceDb::fetch("LpsSaJobMgrTxChannelInput") );
    LpsSaJobMgrReqstChannelOutput_ = dynamic_cast<LpsSaJobMgrReqstChannelOutput*>( InterfaceDb::fetch("LpsSaJobMgrReqstChannelOutput") );
    OutputChannelInput_ = dynamic_cast<OutputChannelInput*>( InterfaceDb::fetch("OutputChannelInput") );

    if ( !SwitchInputScsOutput_ )
    {
        AIS_LOG_FATAL( "no SwitchInputScsOutput_ interface not defined" );
        return false;
    }
    if ( !LpsSaJobMgrTxChannelInput_ )
    {
        AIS_LOG_FATAL( "no LpsSaJobMgrTxChannelInput_ interface not defined" );
        return false;
    }
    if ( !LpsSaJobMgrReqstChannelOutput_ )
    {
        AIS_LOG_FATAL( "no LpsSaJobMgrReqstChannelOutput_ interface not defined" );
        return false;
    }
    if ( !OutputChannelInput_ )
    {
        AIS_LOG_FATAL( "no OutputChannelInput_ interface not defined" );
        return false;
    }
    return true;
}

bool hornOnStoreTest::executive( )
{
    if( counter == 1 )
    {
       AIS_LOG_NOTICE("************************************Test 1: External Store when Horn Disable");
       SendHornEnableDisable(false);
       AIS_LOG_NOTICE("Horn Store Disable");
    }

    if( counter == 20 )
    {
       SetExternalStore(1);
       AIS_LOG_NOTICE("External Store Button pressed");
    }
    if( counter == 22 )
    {
       SetExternalStore(0);
       AIS_LOG_NOTICE("External Store Button released");
    }


    if( counter == 51 )
    {
       AIS_LOG_NOTICE("************************************Test 2: UI Store when Horn Disable");
       SendHornEnableDisable(false);
       AIS_LOG_NOTICE("Horn Store Disable");
    }

    if( counter == 70 )
    {
       SetUIStore();
       AIS_LOG_NOTICE("UI Store Button pressed");
    }


     if( counter == 101 )
     {
        AIS_LOG_NOTICE("************************************Test 3: External Store when Horn Enable");
        SendHornEnableDisable(true);
        AIS_LOG_NOTICE("Horn Store Enable");
     }

     if( counter == 120 )
     {
        SetExternalStore(1);
        AIS_LOG_NOTICE("External Store Button pressed");
     }
     if( counter == 122 )
     {
        SetExternalStore(0);
        AIS_LOG_NOTICE("External Store Button released");
     }


     if( counter == 151 )
     {
        AIS_LOG_NOTICE("************************************Test 4: UI Store when Horn Enable");
        SendHornEnableDisable(true);
        AIS_LOG_NOTICE("Horn Store Enable");
     }

     if( counter == 170 )
     {
        SetUIStore();
        AIS_LOG_NOTICE("UI Store Button pressed");
     }


    counter++;

    CheckScs();

    return true;
}


void hornOnStoreTest::CheckScs( )
{
   LpsSaJobMgrTxChannel lpsSaJobMgrTxChannel;

   while(LpsSaJobMgrTxChannelInput_->get( lpsSaJobMgrTxChannel ))
   {
      if(lpsSaJobMgrTxChannel.HornStoreState != lastLpsSaJobMgrTxChannel.HornStoreState)
      {
         AIS_LOG_NOTICE("Horn Store State Updated: %d", lpsSaJobMgrTxChannel.HornStoreState);
      }
      lastLpsSaJobMgrTxChannel = lpsSaJobMgrTxChannel;
   }

}

void hornOnStoreTest::SendHornEnableDisable( bool HornStoreState)
{
   LpsSaJobMgrReqstChannel jobMgrReqst;
   jobMgrReqst.HornStoreStateReqst.ReqstFlag = true;
   jobMgrReqst.HornStoreStateReqst.Enable = HornStoreState;
   LpsSaJobMgrReqstChannelOutput_->publish(jobMgrReqst);
}

void hornOnStoreTest::SetExternalStore( int pressed)
{
   SwitchInputScs switchInput;
   switchInput.set_STG_value(3, pressed);
   SwitchInputScsOutput_->publish(switchInput);
}

void hornOnStoreTest::SetUIStore()
{
   LpsSaJobMgrReqstChannel jobMgrReqst;
   jobMgrReqst.StoreReqst = true;
   LpsSaJobMgrReqstChannelOutput_->publish(jobMgrReqst);
}

void hornOnStoreTest::cleanup( )
{
    AIS_LOG_INFO( "hornOnStoreTest::cleanup" );

}
