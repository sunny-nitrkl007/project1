/*******************************************************************************
** COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
** CATERPILLAR: CONFIDENTIAL YELLOW
--------------------------------------------------------------------------------
FILE NAME: WidgetApp.h
DESCRIPTION: header for WidgetApp
*******************************************************************************/
#ifndef WidgetApp_H
#define WidgetApp_H

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "tire_rev.h"
#include "dig_timer.h"
#include <ais/task/Task.h>

#include <interfaces/CycleSeg/TxInterfaceInputChannel.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/WidgetsDebugData/InterfaceTypes.h>


/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
constexpr uint32_t DEFAULT_LOADING_DISTANCE_THRESHOLD                         = 40;
constexpr uint16_t MILLISECONDS_IN_CENTISECONDS                               = 10;


/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

class WidgetApp: public task::Task
{
public:
   WidgetApp( const std::string& taskName );
    virtual ~WidgetApp( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

protected:
private:
    CycleSegTxInterfaceInputChannel *CycleSegTxInterfaceInputChannel_;
    DataLinkDataInput *DataLinkDataInput_;
    DataLinkDataOutput *DataLinkDataOutput_;
    WidgetsDebugDataOutput *WidgetsDebugDataOutput_;

    uint32_t tire_radius_mm;

    pcs_dig_state_t dig_state;
    GROUNDSPEED_INFO ground_speed_info;
    GEAR_INFO gear_info;

    tire_rev_distance_t tireRevDistance;
    tire_rev_rotations_t tireRevRotations;
    uint16_t travelingLoadedRevs;
    WidgetsDebugData widgetsDebugData;

    uint32_t digTimerTarget; // milliseconds
    uint16_t digTimeCurrent; // Resolution: 0.01 sec/bit
    DataLinkData dlData;
    DataLinkParam tireRevParam;
    DataLinkParam digTimeParam;

    void InitDataLinkData();
    void ReadDataLinkData();
    void ReadCycleSegData();
    void UpdateTireRev();
    void PublishDataLinkData();
    void PublishWidgetsDebugData();

    void UpdateDigTimer();
};

#endif
