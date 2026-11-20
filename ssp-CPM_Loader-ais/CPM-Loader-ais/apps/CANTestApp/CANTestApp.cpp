/*******************************************************************************
 ** @attention COPYRIGHT (C) 2013-2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
 **
 ** @file    CANTestApp.cpp
 **
 ** @brief   This reads the Machineinput Interface for poseTask
 *******************************************************************************/

/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/

#ifndef   CANTestApp_H_
#include "CANTestApp.h"
#endif
#include <CANBase/SocketCANBase.h>

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
	static CANTestApp thisTask( "CANTestApp" );
    return dynamic_cast<Task *>(&thisTask);
}

/******************************************************************************
FUNCTION NAME:CANTestApp constructor
DESCRIPTION: CANTestApp constructor for initializes an instance of its class
PARAMETER DESCRIPTION:  task name is passed
RETURN VALUE:  No return Value form constructor
*******************************************************************************/
CANTestApp::CANTestApp( const std::string& taskName ):
	Task( taskName ),
    CANBaseRx(),
    CANBaseTx()
{
}

/******************************************************************************
FUNCTION NAME:CANTestApp destructor
DESCRIPTION: CANTestApp destructor for deallocating an instance of its class
PARAMETER DESCRIPTION: No parameter
RETURN VALUE:   No return Value form destructor
*******************************************************************************/
CANTestApp::~CANTestApp( )
{
}

/******************************************************************************
FUNCTION NAME:initialize
DESCRIPTION: SCS channel is initialized
PARAMETER DESCRIPTION:  No parameter
RETURN VALUE:  Boolean
*******************************************************************************/
bool CANTestApp::initialize( )
{
	AIS_LOG_INFO( "CANTestApp::initialize" );

	ConfigSection cs = ConfigSection();
	cs.set<std::string>("dev", "can0");
	cs.set<int>("readTimeout_msec", 500);
    cs.set<bool>("enable_rxfilter", true);
    std::vector<unsigned int> fx_filter = {0x733,0x732};
    cs.set<std::vector<unsigned int>>("rxFilter", fx_filter);

    CANBaseRx.initialize(cs);
    CANBaseTx.initialize(cs);

	return true;
}

/******************************************************************************
FUNCTION NAME:executive
DESCRIPTION:   executive function is required to read strain gauge sensors value and publish the data to SCS channel
PARAMETER DESCRIPTION: No parameter
RETURN VALUE: Boolean
*******************************************************************************/
bool CANTestApp::executive( )
{
    /* checking whether CAN 2B port is configured with canBflag set in app_can_init.c
	once channel is configured CAN2BRead will read the data */

    //Test CAN 11bit Receive
    CanPacket RxCANPacket;
    while( CANBaseRx.getPacket(RxCANPacket) )
    {
        AIS_LOG_ERROR("%X, payload_ %02x%02x%02x%02x%02x%02x%02x%02x",RxCANPacket.msgId,
                RxCANPacket.payload_[0],
                RxCANPacket.payload_[1],
                RxCANPacket.payload_[2],
                RxCANPacket.payload_[3],
                RxCANPacket.payload_[4],
                RxCANPacket.payload_[5],
                RxCANPacket.payload_[6],
                RxCANPacket.payload_[7]);
    }

    //Test CAN 11bit Transmit
    CanPacket TxCANPacket;
    TxCANPacket.msgId = 0x732;
    TxCANPacket.extendedId = false;
    TxCANPacket.remoteFrame = false;
    TxCANPacket.errorFrame = false;
    TxCANPacket.length = 8;
    TxCANPacket.payload_[0] = 'a';
    TxCANPacket.payload_[1] = 'b';
    TxCANPacket.payload_[2] = 'c';
    TxCANPacket.payload_[3] = 'd';
    TxCANPacket.payload_[4] = 'e';
    TxCANPacket.payload_[5] = 'f';
    TxCANPacket.payload_[6] = 'g';
    TxCANPacket.payload_[7] = 'h';
    AIS_LOG_ERROR("%d",CANBaseTx.publishPacket(TxCANPacket, 10.0));

    return true;
}//End

/******************************************************************************
FUNCTION NAME: autonomyCleanup
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE: void
*******************************************************************************/
void CANTestApp::cleanup( )
{
	AIS_LOG_INFO( "CANTestApp::cleanup" );
}


