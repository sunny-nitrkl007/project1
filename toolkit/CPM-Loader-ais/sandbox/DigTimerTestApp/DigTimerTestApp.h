/*******************************************************************************
 ** @attention COPYRIGHT (C) 2013-2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
 **
 ** @file    DigTimerTestApp.h
 **
 ** @brief   This is the definition include file for the module.
 *******************************************************************************/
#ifndef DigTimerTestApp_H_
#define DigTimerTestApp_H_

/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/

#include <ais/task/Task.h>


#include <interfaces/CycleSeg/TxInterfaceOutputChannel.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>

using namespace std;

/******************************************************************************/

/*******************************************************************************
 ** -- #Define, Struct's, Typedef's, Enum's --
 *******************************************************************************/
/* defines */

constexpr uint8_t DIGGING_INACTIVE                                         = 0;
constexpr uint8_t DIGGING_TENTATIVE                                        = 1;
constexpr uint8_t DIGGING_ACTIVE                                           = 2;

constexpr uint16_t GEAR_FORWARD                                            = 0x4000;
constexpr uint16_t GEAR_REVERSE                                            = 0x1000;
constexpr uint16_t GEAR_FAULT                                              = 0x8000;


/* class definition */
class DigTimerTestApp: public task::Task
{
public:
	DigTimerTestApp( const std::string& taskName );
	virtual ~DigTimerTestApp( );
	virtual bool initialize( );
	virtual bool executive( );
	virtual void cleanup( );

protected:

private:
    CycleSegTxInterfaceOutputChannel *CycleSegTxInterfaceOutputChannel_;
    DataLinkDataInput *DataLinkDataInput_;

    uint8_t digState;
    uint16_t digTimeCurrent;
    uint32_t executiveCounter;
    DataLinkData dlData;

    uint32_t AppCycleRateHz;

    void SendScsData();
    void GetScsData();

};

#endif /* DigTimerTestApp_H_ */
