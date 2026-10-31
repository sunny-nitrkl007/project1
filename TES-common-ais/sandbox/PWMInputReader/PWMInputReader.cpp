/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: PWMInputReader.cpp
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "../../sandbox/PWMInputReader/PWMInputReader.h"

#include <unistd.h>
#include "ais/task/Task.h"
#include <time.h>

using namespace task;

AbstractTaskCore* task::getTaskImplementation(void)
{
    static PWMInputReader thisTask("PWMInputReader");
    return dynamic_cast<Task *>(&thisTask);
}
/******************************************************************************
FUNCTION NAME:PWMInputReader constructor
DESCRIPTION: PWMInput constructor for initializes an instance of its class
PARAMETER DESCRIPTION:  task name is passed
RETURN VALUE:  No return Value from constructor
*******************************************************************************/
PWMInputReader::PWMInputReader(const std::string& taskName ):
       Task (taskName),
       pwmInputChannelsInput_(NULL)
{
}
/******************************************************************************
FUNCTION NAME:PWMInputReader destructor
DESCRIPTION: PWMInputReader destructor for deallocating an instance of its class
PARAMETER DESCRIPTION:  no parameter
RETURN VALUE:  No return Value from destructor
*******************************************************************************/
PWMInputReader::~PWMInputReader()
{
}
/******************************************************************************
FUNCTION NAME: Initialize widget
DESCRIPTION: Initialize values
PARAMETER DESCRIPTION: no parameter
RETURN VALUE: bool : true
*******************************************************************************/
bool PWMInputReader::initialize()
{
   AIS_LOG_INFO("PWMInputReader::Initialize");
   pwmInputChannelsInput_ = dynamic_cast<PwmInputChannelsInput*>( InterfaceDb::fetch("PwmInputChannelsInput"));

  if( !pwmInputChannelsInput_ )
  {
     AIS_LOG_FATAL(" The interface for PWM input channels not defined ");
     return false;
  }
  return true;
}
/******************************************************************************
FUNCTION NAME: executive
DESCRIPTION: Read the values from scs and print the values
PARAMETER DESCRIPTION: no parameter
RETURN VALUE: bool : true
*******************************************************************************/
bool PWMInputReader::executive()
{
  PwmInputChannels pwmInputChannel;
  while(pwmInputChannelsInput_ -> get(pwmInputChannel))
  {

     count++;
     AIS_LOG_INFO(" ************** The Reader has successfully read the data ************* ");

     // Print the values that are read from scs objects
     AIS_LOG_INFO("Print the actual time values %ld",pwmInputChannel.PwmData.ActualTimeUs);
     AIS_LOG_INFO("Print the Exec time values %d",pwmInputChannel.PwmData.ExecTime);
     AIS_LOG_INFO("Print the Diff time values %d",pwmInputChannel.PwmData.DiffTime);
     AIS_LOG_INFO("Print the Exp values %d",pwmInputChannel.PwmData.Exp);
     AIS_LOG_INFO("Print the Period[0] values %d",pwmInputChannel.PwmData.Period[0]);
     AIS_LOG_INFO("Print the Width[0] values %d",pwmInputChannel.PwmData.Width[0]);
     AIS_LOG_INFO("Print the Period[1] values %d",pwmInputChannel.PwmData.Period[1]);
     AIS_LOG_INFO("Print the Width[1] values %d",pwmInputChannel.PwmData.Width[1]);
     AIS_LOG_INFO("Print the Period[2] values %d",pwmInputChannel.PwmData.Period[2]);
     AIS_LOG_INFO("Print the Width[2] values %d",pwmInputChannel.PwmData.Width[2]);
     AIS_LOG_INFO("Print the Period[3] values %d",pwmInputChannel.PwmData.Period[3]);
     AIS_LOG_INFO("Print the Width[3] values %d",pwmInputChannel.PwmData.Width[3]);

  }
  return true;
}
/******************************************************************************
FUNCTION NAME: Cleanup
DESCRIPTION:
PARAMETER DESCRIPTION: no parameter
RETURN VALUE: void
*******************************************************************************/
void PWMInputReader::cleanup( )
{
    AIS_LOG_INFO( "PWMInputReader::cleanup" );

}
