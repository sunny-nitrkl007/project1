/*******************************************************************************
 ** @attention COPYRIGHT (C) 2013-2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
 **
 ** @file    CANTestApp.h
 **
 ** @brief   This is the definition include file for the module.
 *******************************************************************************/
#ifndef CANTestApp_H_
#define CANTestApp_H_

/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/

#include <ais/task/Task.h>
#include <std_types.h>
#include <commTask/commTask.h>
#include <string.h>
#include <util/DebounceAssistant.h>
#include "src_CAN/app_can_init.h"
#include <CANBase/SocketCANBase.h>


// standard c++ includes
#include <iostream>
#include <memory>
#include <string>
#include <thread>

using namespace std;

/******************************************************************************/

/*******************************************************************************
 ** -- #Define, Struct's, Typedef's, Enum's --
 *******************************************************************************/
/* defines */

/* class definition */
class CANTestApp: public task::Task
{
public:
	CANTestApp( const std::string& taskName );
	virtual ~CANTestApp( );
	virtual bool initialize( );
	virtual bool executive( );
	void CANTestAppTx();
	virtual void cleanup( );

protected:

private:
    void CAN2BRead();
    void CAN2BWrite();
    void CAN2PortClose();
    void SensorResetCommand();
    SocketCANBase CANBaseRx;
    SocketCANBase CANBaseTx;

};

#endif /* CANTestApp_H_ */
