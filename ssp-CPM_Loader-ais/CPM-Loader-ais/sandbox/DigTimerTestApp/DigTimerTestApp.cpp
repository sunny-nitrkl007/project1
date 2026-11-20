/*******************************************************************************
 ** @attention COPYRIGHT (C) 2013-2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
 **
 ** @file    DigTimerTestApp.cpp
 **
 ** @brief   This reads the Machineinput Interface for poseTask
 *******************************************************************************/

/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/

#ifndef   DigTimerTestApp_H_
#include "DigTimerTestApp.h"
#endif

#include "BMI_CDL_PID.h"

/*******************************************************************************
 ** -- #Define, Struct's, Typedef's, Enum's --
 *******************************************************************************/

/*******************************************************************************
 ** -- Function Prototypes --
 *******************************************************************************/

/*******************************************************************************
 ** -- Symbols --
 *******************************************************************************/

using namespace task;

/*******************************************************************************
 ** -- Start of code for this file --
 *******************************************************************************/

AbstractTaskCore* task::getTaskImplementation(void)
{
    static DigTimerTestApp thisTask( "DigTimerTestApp" );
    return dynamic_cast<Task *>(&thisTask);
}

/******************************************************************************
FUNCTION NAME:DigTimerTestApp constructor
DESCRIPTION: DigTimerTestApp constructor for initializes an instance of its class
PARAMETER DESCRIPTION:  task name is passed
RETURN VALUE:  No return Value form constructor
 *******************************************************************************/
DigTimerTestApp::DigTimerTestApp( const std::string& taskName ):
    Task( taskName ),
    CycleSegTxInterfaceOutputChannel_(NULL),
    DataLinkDataInput_(NULL),
    digTimeCurrent(0),
    executiveCounter(0)
{
}
/******************************************************************************
FUNCTION NAME:DigTimerTestApp destructor
DESCRIPTION: DigTimerTestApp destructor for deallocating an instance of its class
PARAMETER DESCRIPTION: No parameter
RETURN VALUE:   No return Value form destructor
 *******************************************************************************/
DigTimerTestApp::~DigTimerTestApp( )
{
}

/******************************************************************************
FUNCTION NAME:initialize
DESCRIPTION: SCS channel is initialized
PARAMETER DESCRIPTION:  No parameter
RETURN VALUE:  Boolean
 *******************************************************************************/
bool DigTimerTestApp::initialize( )
{
    AIS_LOG_INFO( "DigTimerTestApp::initialize" );

    if (!task::InterfaceDb::bind("CycleSegTxInterfaceOutputChannel", CycleSegTxInterfaceOutputChannel_) ||
        !task::InterfaceDb::bind("DataLinkDataInput", DataLinkDataInput_))
    {
        return false;
    }

    getTaskConfig().get( "cycleRate_hz", AppCycleRateHz);
    AIS_LOG_NOTICE( "APP_CYCLE_RATE_HZ: %d", AppCycleRateHz );

    return true;
}

/******************************************************************************
FUNCTION NAME:executive
DESCRIPTION:   executive function is required to read strain gauge sensors value and publish the data to SCS channel
PARAMETER DESCRIPTION: No parameter
RETURN VALUE: Boolean
 *******************************************************************************/
bool DigTimerTestApp::executive( )
{
    GetScsData();

    if (executiveCounter <= (AppCycleRateHz * 2))
    {
        if(executiveCounter == 1)
        {
            AIS_LOG_ERROR("*******************digState = DIGGING_INACTIVE*******************");
        }
        digState = DIGGING_INACTIVE;
        SendScsData();
    }
    else if (executiveCounter <= (AppCycleRateHz * 4))
    {
        if(executiveCounter == ((AppCycleRateHz * 2) + 1))
        {
        AIS_LOG_ERROR("*******************digState = DIGGING_TENTATIVE*******************");
        }
        digState = DIGGING_TENTATIVE;
        SendScsData();
    }
    else if (executiveCounter <= (AppCycleRateHz * 6))
    {
        if(executiveCounter == ((AppCycleRateHz * 4) + 1))
        {
        AIS_LOG_ERROR("*******************digState = DIGGING_ACTIVE*******************");
        }
        digState = DIGGING_ACTIVE;
        SendScsData();
    }
    else if (executiveCounter <= (AppCycleRateHz * 8))
    {
        if(executiveCounter == ((AppCycleRateHz * 6) + 1))
        {
        AIS_LOG_ERROR("*******************digState = DIGGING_TENTATIVE*******************");
        }
        digState = DIGGING_TENTATIVE;
        SendScsData();
    }
    else if (executiveCounter <= (AppCycleRateHz * 10))
    {
        if(executiveCounter == ((AppCycleRateHz * 8) + 1))
        {
        AIS_LOG_ERROR("*******************digState = DIGGING_INACTIVE*******************");
        }
        digState = DIGGING_INACTIVE;
        SendScsData();
    }
    else if (executiveCounter <= (AppCycleRateHz * 12))
    {
        if(executiveCounter == ((AppCycleRateHz * 10) + 1))
        {
        AIS_LOG_ERROR("*******************digState = DIGGING_ACTIVE*******************");
        }
        digState = DIGGING_ACTIVE;
        SendScsData();
    }
    else if (executiveCounter < (AppCycleRateHz * 14))
    {
        if(executiveCounter == ((AppCycleRateHz * 12) + 1))
        {
        AIS_LOG_ERROR("*******************digState = DIGGING_INACTIVE*******************");
        }
        digState = DIGGING_INACTIVE;
        SendScsData();
    }
    else{
        executiveCounter = 0;
        SendScsData();
    }

    executiveCounter++;
    return true;
}

void DigTimerTestApp::SendScsData()
{
    CycleSegTxInterface CycleSegData;
    CycleSegData.digState =digState;
    CycleSegTxInterfaceOutputChannel_->publish(CycleSegData);

    AIS_LOG_ERROR("digTimeCurrent = %d, digState = %d Counter = %d", digTimeCurrent, digState, executiveCounter);
}

void DigTimerTestApp::GetScsData()
{

    DataLinkData dlData;
    while (DataLinkDataInput_->get(dlData)) {
        for (auto& dlParam : dlData.GetParams())
        {
            auto paramId = dlParam.GetParamId();

            switch (paramId) {
                case PAYLOAD_CYCLE_CURRENT_DIG_TIME_PID:
                    if(( dlParam.GetLastValueDsi() == 0 ) || ( dlParam.GetLastValueDsi() == 1 ))
                    {
                        digTimeCurrent = dlParam.GetLastGoodValue<uint16_t>();
                    }
                    break;
            }
        }
    }

}


/******************************************************************************
FUNCTION NAME: autonomyCleanup
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE: void
 *******************************************************************************/
void DigTimerTestApp::cleanup( )
{
    AIS_LOG_INFO( "DigTimerTestApp::cleanup" );
}


