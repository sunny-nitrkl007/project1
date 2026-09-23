/*******************************************************************************
 ** COPYRIGHT (C) 2000 CATERPILLAR INC. ALL RIGHTS RESERVED.
 ** CATERPILLAR: CONFIDENTIAL YELLOW
--------------------------------------------------------------------------------
FILE NAME: WidgetApp.cpp
DESCRIPTION: Implementation for WidgetApp
 *******************************************************************************/

/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/
#include "WidgetApp.h"
#include "BMI_CDL_PID.h"
#include <time.h>
#include <catdllib_fid_def.h>

using namespace task;

AbstractTaskCore* task::getTaskImplementation(void)
{
    static WidgetApp thisTask("WidgetApp");
    return dynamic_cast<Task *>(&thisTask);
}

WidgetApp::WidgetApp( const std::string& taskName ):
    Task(taskName),
    CycleSegTxInterfaceInputChannel_(nullptr),
    DataLinkDataInput_(nullptr),
    DataLinkDataOutput_(nullptr),
    WidgetsDebugDataOutput_(nullptr),
    tire_radius_mm(0),
    dig_state(PCS_DIG_UNKNOWN),
    ground_speed_info({0.0,PCS_DATA_STATUS_BAD}),
    gear_info({0,PCS_DATA_STATUS_BAD}),
    tireRevDistance(),
    tireRevRotations(),
    travelingLoadedRevs(0),
    widgetsDebugData(),
    digTimerTarget(0),
    digTimeCurrent(0)
{
}

WidgetApp::~WidgetApp( )
{
}

bool WidgetApp::initialize( )
{
    AIS_LOG_NOTICE( "TireRevApp::initialize" );

    if (!task::InterfaceDb::bind("CycleSegTxInterfaceInputChannel", CycleSegTxInterfaceInputChannel_) ||
        !task::InterfaceDb::bind("DataLinkDataInput", DataLinkDataInput_) ||
        !task::InterfaceDb::bind("DataLinkDataOutput", DataLinkDataOutput_) ||
        !task::InterfaceDb::bind("WidgetsDebugDataOutput", WidgetsDebugDataOutput_))
    {
        return false;
    }

    dig_timer_init();

    tire_rev_init();
    tire_rev_set_loading_distance_threshold(DEFAULT_LOADING_DISTANCE_THRESHOLD);

    InitDataLinkData();

    return true;
}

bool WidgetApp::executive( )
{
    AIS_LOG_INFO( "TireRevApp::executive" );

    ReadDataLinkData();
    ReadCycleSegData();
    UpdateTireRev();
    UpdateDigTimer();
    PublishWidgetsDebugData();
    PublishDataLinkData();
    return true;
}

void WidgetApp::UpdateTireRev()
{
    tire_rev_update(dig_state, &ground_speed_info, &gear_info);
    AIS_LOG_NOTICE("dig_state %d, ground_speed %f, gear_info 0x%X",dig_state, ground_speed_info.speed, gear_info.gear);

    tire_rev_get_distance(&tireRevDistance);
    tire_rev_get_rotations(&tireRevRotations, tire_radius_mm);
    travelingLoadedRevs = static_cast<uint16_t>((tireRevRotations.forward+tireRevRotations.reverse) *100);
    AIS_LOG_NOTICE("travelingLoadedRevs = %d",travelingLoadedRevs);
}

void WidgetApp::UpdateDigTimer()
{
    dig_timer_update(dig_state);

    digTimeCurrent = static_cast<uint16_t>(dig_timer_get_current() / MILLISECONDS_IN_CENTISECONDS);
}

void WidgetApp::InitDataLinkData()
{
    tireRevParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_INT);
    tireRevParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
    tireRevParam.SetParamId(TRAVEL_LOADED_WHEEL_REVOLUTIONS_PID);
    tireRevParam.SetParameterType(CDL2_U16_DSI);
    tireRevParam.SetSid(0xFF);

    /*
     * This does not match the actual datalink parameter encoding.
     * This application pre-scales the data to 0.01 revolutions/bit
     */
    tireRevParam.SetScaling(1.0);
    tireRevParam.SetOffset(0);

    dlData.AddDataLinkParam(tireRevParam);

    digTimeParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_INT);
    digTimeParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
    digTimeParam.SetParamId(PAYLOAD_CYCLE_CURRENT_DIG_TIME_PID);
    digTimeParam.SetParameterType(CDL2_U16_DSI);
    digTimeParam.SetSid(0xFF);

    /*
     * This does not match the actual datalink parameter encoding.
     * This application pre-scales the data to 0.01 sec/bit
     */
    digTimeParam.SetScaling(1.0);
    digTimeParam.SetOffset(0);

    dlData.AddDataLinkParam(digTimeParam);
}

void WidgetApp::ReadDataLinkData()
{
    DataLinkData dlData;
    while (DataLinkDataInput_->get(dlData)) {
        for (auto& dlParam : dlData.GetParams())
        {
            auto paramId = dlParam.GetParamId();

            switch (paramId) {
                case GROUND_SPEED_AND_DIRECTION_PID:
                    ground_speed_info.speed = dlParam.GetLastGoodValue<int16_t>();
                    ground_speed_info.data_status = (dlParam.GetLastValueDsi() == BMI_CDL_DATA_STATUS_OK) ? PCS_DATA_STATUS_OK : PCS_DATA_STATUS_BAD;
                    break;
                case DIRECTION_SWITCH_POSITION:
                    if (dlParam.GetLastValueDsi() == BMI_CDL_DATA_STATUS_OK) {
                        gear_info.gear_status = PCS_DATA_STATUS_OK;
                        uint8_t data = dlParam.GetLastValue<uint8_t>();
                        if (0x01 == data) {
                            /* Forward */
                            gear_info.gear = 0x4000; /* forward, see PID 0xF5D7*/
                        }
                        else if (0x00 == data) {
                            /* Reverse */
                            gear_info.gear = 0x1000; /* reverse, see PID 0xF5D7*/
                        }
                        else if (0x02 == data) {
                            /* Neutral */
                            gear_info.gear = 0x2000; /* neutral, see PID 0xF5D7*/
                        }
                        else if (IS_KNOWN1U(data)) {
                            /* Not Faulted, but not FNR either */
                            gear_info.gear = 0x0000; /* other, see PID 0xF5D7*/
                        }
                        else {
                            /* DSI */
                            gear_info.gear = 0x8000; /* fault, see PID 0xF5D7*/
                        }
                    }
                    else {
                        gear_info.gear = 0x8000; /* fault, see PID 0xF5D7*/
                        gear_info.gear_status = PCS_DATA_STATUS_BAD;
                    }
                    break;
                case TIRE_ROLLING_RADIUS_PID:
                    if(dlParam.GetLastValueDsi() == BMI_CDL_DATA_STATUS_OK)
                    {
                        tire_radius_mm = dlParam.GetLastGoodValue<uint16_t>();
                    }
                    break;
            }
        }
    }
}

void WidgetApp::ReadCycleSegData()
{
    CycleSegTxInterface CycleSegData;
    while (CycleSegTxInterfaceInputChannel_->get(CycleSegData)) {
        switch ( CycleSegData.digState )//0 = Inactive, 1 = Tentative, 2 = Active
        {
            case 0:
                dig_state = PCS_NOT_DIGGING;
                break;
            case 1:
                dig_state = PCS_TENTATIVE_DIGGING;
                break;
            case 2:
                dig_state = PCS_DIGGING;
                break;
            default:
                dig_state = PCS_DIG_UNKNOWN;
                break;
        }
    }
}

void WidgetApp::PublishWidgetsDebugData()
{
    WidgetsDebugData::TireRevDistances distancesData;
    distancesData.ForwardMm = tireRevDistance.forward_mm;
    distancesData.ReverseMm = tireRevDistance.reverse_mm;
    distancesData.Status = tireRevDistance.status;
    widgetsDebugData.setDistance(distancesData);

    WidgetsDebugData::TireRevRotations rotationData;
    rotationData.Forward = tireRevRotations.forward;
    rotationData.Reverse = tireRevRotations.reverse;
    rotationData.Status = tireRevRotations.status;
    widgetsDebugData.setRotation(rotationData);

    widgetsDebugData.setDigTimeCurrent(digTimeCurrent);
    widgetsDebugData.setTravelingLoadedRevs(travelingLoadedRevs);
    widgetsDebugData.setDigState(dig_state);
    widgetsDebugData.setGroundSpeedInfo(ground_speed_info);
    widgetsDebugData.setGearInfo(gear_info);

    AIS_LOG_NOTICE("forward_mm:%d, reverse_mm:%d, status:%d",tireRevDistance.forward_mm, tireRevDistance.reverse_mm, tireRevDistance.status);
    WidgetsDebugDataOutput_->publish(widgetsDebugData);
}

void WidgetApp::PublishDataLinkData()
{
    std::vector<unsigned_8> value;

    // Sets the value as a vector of bytes in the native byte order
    value.assign(reinterpret_cast<unsigned_8*>( &travelingLoadedRevs ),
            reinterpret_cast<unsigned_8*>( &travelingLoadedRevs ) + sizeof ( decltype( travelingLoadedRevs )));
    tireRevParam.SetLastValue(value, (tireRevRotations.status == TIRE_REV_OK) ? BMI_CDL_DATA_STATUS_OK : CDL2_DSI_CONDITIONS_NOT_MET );
    dlData.UpdateDataLinkParam(tireRevParam);

    // Sets the value as a vector of bytes in the native byte order
    value.assign(reinterpret_cast<unsigned_8*>( &digTimeCurrent ),
            reinterpret_cast<unsigned_8*>( &digTimeCurrent ) + sizeof ( decltype( digTimeCurrent )));
    digTimeParam.SetLastValue(value, (digTimeCurrent == 0) ? CDL2_DSI_CONDITIONS_NOT_MET : BMI_CDL_DATA_STATUS_OK);
    dlData.UpdateDataLinkParam(digTimeParam);

    DataLinkDataOutput_->publish(dlData);

    // Clear historical data after publishing
    dlData.HandleDataLinkDataMap();
    dlData.ClearDlpDiagInfo();
}

void WidgetApp::cleanup( )
{
    AIS_LOG_INFO( "TireRevApp::cleanup" );

}
