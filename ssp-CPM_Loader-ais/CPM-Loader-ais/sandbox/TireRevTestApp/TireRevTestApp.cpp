/*******************************************************************************
 ** @attention COPYRIGHT (C) 2013-2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
 **
 ** @file    TireRevTestApp.cpp
 **
 ** @brief   This reads the Machineinput Interface for poseTask
 *******************************************************************************/

/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/

#ifndef   TireRevTestApp_H_
#include "TireRevTestApp.h"
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
    static TireRevTestApp thisTask( "TireRevTestApp" );
    return dynamic_cast<Task *>(&thisTask);
}

/******************************************************************************
FUNCTION NAME:TireRevTestApp constructor
DESCRIPTION: TireRevTestApp constructor for initializes an instance of its class
PARAMETER DESCRIPTION:  task name is passed
RETURN VALUE:  No return Value form constructor
 *******************************************************************************/
TireRevTestApp::TireRevTestApp( const std::string& taskName ):
    Task( taskName ),
    CycleSegTxInterfaceOutputChannel_(NULL),
    DataLinkDataOutput_(NULL),
    DataLinkDataInput_(NULL),
    WidgetsDebugDataInput_(NULL),
    GroundSpeed(0),
    ActualGear(0),
    travelingLoadedRevs(0),
    executiveCounter(0)
{
}
/******************************************************************************
FUNCTION NAME:TireRevTestApp destructor
DESCRIPTION: TireRevTestApp destructor for deallocating an instance of its class
PARAMETER DESCRIPTION: No parameter
RETURN VALUE:   No return Value form destructor
 *******************************************************************************/
TireRevTestApp::~TireRevTestApp( )
{
}

/******************************************************************************
FUNCTION NAME:initialize
DESCRIPTION: SCS channel is initialized
PARAMETER DESCRIPTION:  No parameter
RETURN VALUE:  Boolean
 *******************************************************************************/
bool TireRevTestApp::initialize( )
{
    AIS_LOG_INFO( "TireRevTestApp::initialize" );

    if (!task::InterfaceDb::bind("CycleSegTxInterfaceOutputChannel", CycleSegTxInterfaceOutputChannel_) ||
        !task::InterfaceDb::bind("DataLinkDataOutput", DataLinkDataOutput_) ||
        !task::InterfaceDb::bind("DataLinkDataInput", DataLinkDataInput_) ||
        !task::InterfaceDb::bind("WidgetsDebugDataInput", WidgetsDebugDataInput_))
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
bool TireRevTestApp::executive( )
{

    GetScsData();
    if (executiveCounter <= (AppCycleRateHz * 1))
    {
        if(executiveCounter == 1)
        {
            AIS_LOG_ERROR("***************TEST 1 START***************");
            AIS_LOG_ERROR("Verify that the initial value of both distances after key on is DSI.");
            if( widgetsDebugData.getDistance().Status ==1 )
            {
                AIS_LOG_ERROR("***************PASS***************");
            }
            else
            {
                AIS_LOG_ERROR("************************************************************FAIL***************");
            }
        }
    }
    else if (executiveCounter <= (AppCycleRateHz * 2))
    {
        if(executiveCounter == (AppCycleRateHz * 1) + 1 )
        {
            AIS_LOG_ERROR("***************TEST 2 START***************");
            AIS_LOG_ERROR("When dig state is confirmed, both distances show DSI.");
        }
        GroundSpeed = 0;
        ActualGear = GEAR_FORWARD;
        digState = DIGGING_ACTIVE;
        SendScsData();

        if(executiveCounter == (AppCycleRateHz * 1) + 2)
        {
            if( widgetsDebugData.getDistance().Status ==1 )
            {
                AIS_LOG_ERROR("***************PASS***************");
            }
            else
            {
                AIS_LOG_ERROR("************************************************************FAIL***************");
            }
        }
    }
    else if (executiveCounter <= (AppCycleRateHz * 5))
    {
        if(executiveCounter == (AppCycleRateHz * 2) + 1 )
        {
            AIS_LOG_ERROR("***************TEST 3 START***************");
            AIS_LOG_ERROR("Given that dig state has been confirmed, as soon as the operator desired direction is reverse AND the ground speed is < 0, then both distances are initialized to 0.");
        }
        GroundSpeed = -3000;
        ActualGear = GEAR_REVERSE;
        digState = DIGGING_INACTIVE;
        SendScsData();
        if(executiveCounter == (AppCycleRateHz * 2) + 2)
        {
            if( (widgetsDebugData.getDistance().Status == 0) &&
                    (widgetsDebugData.getDistance().ForwardMm == 0) &&
                    (lastWidgetsDebugData.getDistance().ReverseMm < widgetsDebugData.getDistance().ReverseMm) )
            {
                AIS_LOG_ERROR("***************PASS***************");
            }
            else
            {
                AIS_LOG_ERROR("************************************************************FAIL***************");
            }
        }
    }
    else if (executiveCounter <= (AppCycleRateHz * 10))
    {
        if(executiveCounter == (AppCycleRateHz * 5) + 1 )
        {
            AIS_LOG_ERROR("***************TEST 4 START***************");
            AIS_LOG_ERROR("Given that the feature is actively accumulating reverse direction, when the direction changes to forward AND ground speed > 0, then reverse direction stops accumulating and forward begins.");
        }
        GroundSpeed = 3000;
        ActualGear = GEAR_FORWARD;
        digState = DIGGING_INACTIVE;
        SendScsData();
        if(executiveCounter == (AppCycleRateHz * 5) + 3)
        {
            if( (widgetsDebugData.getDistance().Status ==0) &&
                    (lastWidgetsDebugData.getDistance().ForwardMm < widgetsDebugData.getDistance().ForwardMm) &&
                    (lastWidgetsDebugData.getDistance().ReverseMm == widgetsDebugData.getDistance().ReverseMm) )
            {
                AIS_LOG_ERROR("***************PASS***************");
            }
            else
            {
                AIS_LOG_ERROR("************************************************************FAIL***************");
            }
        }
    }
    else if (executiveCounter <= (AppCycleRateHz * 15))
    {
        if(executiveCounter == (AppCycleRateHz * 10) + 1 )
        {
            AIS_LOG_ERROR("***************TEST 5 START***************");
            AIS_LOG_ERROR("Given that the feature is actively accumulating forward direction, when the direction changes to reverse AND ground speed < 0, then forward direction stops accumulating and both distances remain frozen.");
        }
        GroundSpeed = -3000;
        ActualGear = GEAR_REVERSE;
        digState = DIGGING_INACTIVE;
        SendScsData();
        if(executiveCounter == (AppCycleRateHz * 10) + 2)
        {
            if( (widgetsDebugData.getDistance().Status ==0) &&
                    (lastWidgetsDebugData.getDistance().ForwardMm == widgetsDebugData.getDistance().ForwardMm) &&
                    (lastWidgetsDebugData.getDistance().ReverseMm == widgetsDebugData.getDistance().ReverseMm) )
            {
                AIS_LOG_ERROR("***************PASS***************");
            }
            else
            {
                AIS_LOG_ERROR("************************************************************FAIL***************");
            }
        }
    }
    else if (executiveCounter <= (AppCycleRateHz * 20))
    {
        GroundSpeed = 3000;
        ActualGear = GEAR_FORWARD;
        digState = DIGGING_INACTIVE;
        SendScsData();
    }
    else if (executiveCounter <= (AppCycleRateHz * 25))
    {
        if(executiveCounter == (AppCycleRateHz * 20) + 1 )
        {
            AIS_LOG_ERROR("***************TEST 6 START***************");
            AIS_LOG_ERROR("Given that both distances are frozen with valid values, when a dig is encountered, then both distances show DSI.");
        }
        GroundSpeed = 0;
        ActualGear = GEAR_FORWARD;
        digState = DIGGING_ACTIVE;
        SendScsData();
        if(executiveCounter == (AppCycleRateHz * 20) + 2)
        {
            if( (widgetsDebugData.getDistance().Status ==1) &&
                    (0 == widgetsDebugData.getDistance().ForwardMm) &&
                    (0 == widgetsDebugData.getDistance().ReverseMm) )
            {
                AIS_LOG_ERROR("***************PASS***************");
            }
            else
            {
                AIS_LOG_ERROR("************************************************************FAIL***************");
            }
        }
    }
    else if (executiveCounter <= (AppCycleRateHz * 28))
    {
        if(executiveCounter == (AppCycleRateHz * 25) + 1 )
        {
            AIS_LOG_ERROR("***************TEST 7 START***************");
            AIS_LOG_ERROR("Given that at we are in the forward portion of the tire rev cycle, if the sum of of the two distances is > 40 m, then both distances show DSI.");
        }
        GroundSpeed = -10000;
        ActualGear = GEAR_REVERSE;
        digState = DIGGING_INACTIVE;
        SendScsData();
    }
    else if (executiveCounter <= (AppCycleRateHz * 34))
    {
        GroundSpeed = 2000;
        ActualGear = GEAR_FORWARD;
        digState = DIGGING_INACTIVE;
        SendScsData();
        if(executiveCounter == (AppCycleRateHz * 33)+1 )
        {
            if( (widgetsDebugData.getDistance().Status == 1) &&
                    (0 == widgetsDebugData.getDistance().ForwardMm) &&
                    (0 == widgetsDebugData.getDistance().ReverseMm) &&
                    (40000 > (lastWidgetsDebugData.getDistance().ReverseMm + lastWidgetsDebugData.getDistance().ReverseMm)) )
            {
                AIS_LOG_ERROR("***************PASS***************");
            }
            else
            {
                AIS_LOG_ERROR("************************************************************FAIL***************");
            }
        }
    }
    else{
        executiveCounter = 10;
        SendScsData();
    }
    if( (lastWidgetsDebugData.getDistance().ForwardMm == widgetsDebugData.getDistance().ForwardMm) &&
            (lastWidgetsDebugData.getDistance().ReverseMm < widgetsDebugData.getDistance().ReverseMm) )
    {
        AIS_LOG_ERROR("Accumulating reverse direction.");
    }
    else if( (lastWidgetsDebugData.getDistance().ForwardMm < widgetsDebugData.getDistance().ForwardMm) &&
            (lastWidgetsDebugData.getDistance().ReverseMm == widgetsDebugData.getDistance().ReverseMm) )
    {
        AIS_LOG_ERROR("Accumulating forward direction.");
    }
    executiveCounter++;
    return true;
}//End

void TireRevTestApp::SendScsData()
{

    DataLinkParam dlpSpeed, dlpGear;

    dlpSpeed.SetParamId(GROUND_SPEED_AND_DIRECTION_PID);
    dlpSpeed.SetSid(0x37);
    dlpSpeed.SetScaling(1.0);
    dlpSpeed.SetOffset(0);
    dlpSpeed.SetUnits(static_cast<DataLinkParamInfo::DlpUnits_t>(0));
    std::vector<unsigned_8> dlpSpeedValue;
    dlpSpeedValue.assign(reinterpret_cast<unsigned_8*>( &GroundSpeed ), reinterpret_cast<unsigned_8*>( &GroundSpeed ) + sizeof ( decltype( GroundSpeed )));
    //AIS_LOG_ERROR("dlpSpeedValue", dlpSpeedValue);
    dlpSpeed.SetLastValue(dlpSpeedValue, 0);
        AIS_LOG_NOTICE("GROUND_SPEED_DIRECTION_PID: ParamId:%X, Param value:%d",
            dlpSpeed.GetParamId(),dlpSpeed.GetLastValue<int16_t>());

    dlpGear.SetParamId(ACTUAL_GEAR_PID);
    dlpGear.SetSid(0x37);
    dlpGear.SetScaling(1.0);
    dlpGear.SetOffset(0);
    dlpGear.SetUnits(static_cast<DataLinkParamInfo::DlpUnits_t>(0));

    std::vector<unsigned_8> dlpGearValue;
    dlpGearValue.assign(reinterpret_cast<unsigned_8*>( &ActualGear ), reinterpret_cast<unsigned_8*>( &ActualGear ) + sizeof ( decltype( ActualGear )));
    dlpGear.SetLastValue(dlpGearValue, 0);
    AIS_LOG_NOTICE("ACTUAL_GEAR_PID: ParamId:%X, Param value:%d",
            dlpGear.GetParamId(),dlpGear.GetLastValue<uint16_t>());

    dlData.AddDataLinkParam(dlpSpeed);
    dlData.AddDataLinkParam(dlpGear);
    dlData.UpdateDataLinkParam(dlpSpeed);
    dlData.UpdateDataLinkParam(dlpGear);
    DataLinkDataOutput_->publish(dlData);

    CycleSegTxInterface CycleSegData;
    CycleSegData.digState =digState;
    CycleSegTxInterfaceOutputChannel_->publish(CycleSegData);

}

void TireRevTestApp::GetScsData()
{
    lastWidgetsDebugData = widgetsDebugData;
    lastTravelingLoadedRevs = travelingLoadedRevs;

    DataLinkData dlData;
    while (DataLinkDataInput_->get(dlData)) {
        for (auto& dlParam : dlData.GetParams())
        {
            auto paramId = dlParam.GetParamId();

            switch (paramId) {
                case TRAVEL_LOADED_WHEEL_REVOLUTIONS_PID:
                    if(( dlParam.GetLastValueDsi() == 0 ) || ( dlParam.GetLastValueDsi() == 1 ))
                    {
                        travelingLoadedRevs = dlParam.GetLastGoodValue<uint16_t>();
                    }
                    break;
            }
        }
    }

    while (WidgetsDebugDataInput_->get(widgetsDebugData)) {
    }

    AIS_LOG_ERROR("Forward (mm) = %d, Reverse (mm) = %d, DSI = %d, travelingLoadedRevs = %d, Counter = %d",
            widgetsDebugData.getDistance().ForwardMm,
            widgetsDebugData.getDistance().ReverseMm,
            widgetsDebugData.getDistance().Status,
            travelingLoadedRevs,
            executiveCounter);
}


/******************************************************************************
FUNCTION NAME: autonomyCleanup
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE: void
 *******************************************************************************/
void TireRevTestApp::cleanup( )
{
    AIS_LOG_INFO( "TireRevTestApp::cleanup" );
}


