/*******************************************************************************
 ** @attention COPYRIGHT (C) 2013-2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
 **
 ** @file    TireRevTestApp.h
 **
 ** @brief   This is the definition include file for the module.
 *******************************************************************************/
#ifndef TireRevTestApp_H_
#define TireRevTestApp_H_

/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/

#include <ais/task/Task.h>


#include <interfaces/CycleSeg/TxInterfaceOutputChannel.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/WidgetsDebugData/InterfaceTypes.h>

using namespace std;

/******************************************************************************/

/*******************************************************************************
 ** -- #Define, Struct's, Typedef's, Enum's --
 *******************************************************************************/
/* defines */

constexpr uint8_t DIGGING_ACTIVE                                           = 2;
constexpr uint8_t DIGGING_INACTIVE                                         = 0;

constexpr uint16_t GEAR_FORWARD                                            = 0x4000;
constexpr uint16_t GEAR_REVERSE                                            = 0x1000;
constexpr uint16_t GEAR_FAULT                                              = 0x8000;


/* class definition */
class TireRevTestApp: public task::Task
{
public:
	TireRevTestApp( const std::string& taskName );
	virtual ~TireRevTestApp( );
	virtual bool initialize( );
	virtual bool executive( );
	virtual void cleanup( );

protected:

private:
    CycleSegTxInterfaceOutputChannel *CycleSegTxInterfaceOutputChannel_;
    DataLinkDataOutput *DataLinkDataOutput_;
    DataLinkDataInput *DataLinkDataInput_;
    WidgetsDebugDataInput *WidgetsDebugDataInput_;


    int16_t GroundSpeed;
    uint16_t ActualGear;
    uint8_t digState;
    DataLinkData dlData;

    uint16_t travelingLoadedRevs;
    WidgetsDebugData widgetsDebugData;
    uint16_t lastTravelingLoadedRevs;
    WidgetsDebugData lastWidgetsDebugData;

    uint32_t executiveCounter;

    uint32_t AppCycleRateHz;

    void SendScsData();
    void GetScsData();

};

#endif /* TireRevTestApp_H_ */
