/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LEDOutput.cpp
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "OutputApp.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/*uncomment the below code to enable test in VM*/
//#define TEST_MODE
#ifdef TEST_MODE
#define GPIO_SINK1_FILE_LOC  "/home/pf/git/Output/sink1"
#define GPIO_SINK2_FILE_LOC  "/home/pf/git/Output/sink2"
#define GPIO_SINK3_FILE_LOC  "/home/pf/git/Output/sink3"
#else
#define GPIO_SINK1_FILE_LOC    "/sys/class/gpio/gpio86/value"
#define GPIO_SINK2_FILE_LOC    "/sys/class/gpio/gpio87/value"
#define GPIO_SINK3_FILE_LOC    "/sys/class/gpio/gpio88/value"
#endif

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

using namespace task;

AbstractTaskCore* task::getTaskImplementation(void)
{
   static OutputApp thisTask("OutputApp");
   return dynamic_cast<Task *>(&thisTask);
}

/******************************************************************************
FUNCTION NAME:Output constructor
DESCRIPTION: Output constructor for initializes an instance of its class
PARAMETER DESCRIPTION:  task name is passed
RETURN VALUE:  No return Value form constructor
*******************************************************************************/
OutputApp::OutputApp( const std::string& taskName ):
    Task( taskName ),
    OutputAppInput(NULL),
    Config{}
{
}

/******************************************************************************
FUNCTION NAME:Output destructorl
DESCRIPTION: Output destructor for deallocating an instance of its class
PARAMETER DESCRIPTION: No parameter
RETURN VALUE:   No return Value form destructor
*******************************************************************************/
OutputApp::~OutputApp( )
{
}

/******************************************************************************
FUNCTION NAME:UptdateOutputPortSinkFile
DESCRIPTION: Writes ON/OFF to lamps
PARAMETER DESCRIPTION:  portIndex: Port Number, portState: the state set to the port.
RETURN VALUE:  void
*******************************************************************************/

void OutputApp::UpdateOutputPortSinkFile( int portIndex, OutputChannel::State portState )
{
   std::string gpioPath;
   switch(portIndex){
      case OutputChannel::Port::OUTPUT_SINK_1:
         gpioPath = GPIO_SINK1_FILE_LOC;
         break;
      case OutputChannel::Port::OUTPUT_SINK_2:
         gpioPath = GPIO_SINK2_FILE_LOC;
         break;
      case OutputChannel::Port::OUTPUT_SINK_3:
         gpioPath = GPIO_SINK3_FILE_LOC;
         break;
      default:
         break;
   }
   FILE* gpioFile = fopen(gpioPath.c_str(), "w") ;
   if(gpioFile != NULL)
   {
      AIS_LOG_INFO("Val written to gpio %d = %d", portIndex, portState);
      fprintf(gpioFile,"%d",portState);
      Config[portIndex].PortCurrentState = portState;
   }
   else
   {
      AIS_LOG_WARN("Failed to open %s. \n",gpioPath.c_str());
   }
   fclose(gpioFile) ;
}

/******************************************************************************
FUNCTION NAME:initialize
DESCRIPTION: Initialize values
PARAMETER DESCRIPTION:  No parameter
RETURN VALUE:  Boolean
*******************************************************************************/
bool OutputApp::initialize( )
{

   /* Initialsing SCS interface */
   OutputAppInput = dynamic_cast<OutputChannelInput*>( InterfaceDb::fetch( "OutputChannelInput" ) );

   if( !OutputAppInput )
   {
      AIS_LOG_FATAL( "No OutputAppInput interface defined" );
      return false;
   }

   getTaskConfig().get( "cycleRate_hz", AppCycleRateHz);
   if( AppCycleRateHz%IDEAL_APP_CYCLE_RATE != 0 )
   {
      AIS_LOG_FATAL( "AppCycleRate cannot provide 250ms output." );
      return false;
   }
   AIS_LOG_INFO( "APP_CYCLE_RATE_HZ: %d", AppCycleRateHz );
   return true;
}

/******************************************************************************
FUNCTION NAME:executive
DESCRIPTION:  Open driver files and write values to it. Values 0 and 1 are written alternatively
           every second.
PARAMETER DESCRIPTION: No parameter
RETURN VALUE: Boolean
*******************************************************************************/
bool OutputApp::executive( )
{
   AIS_LOG_INFO( "Output::executive" );

   ReadCommand();

   for( uint32_t portNumber=0; portNumber<OutputChannel::Port::OUTPUT_SINK_COUNT; portNumber++ )
   {
      if(true == Config[portNumber].NewCommandRcvd) //if we got new command: set Initial State
      {
         UpdateOutputPortSinkFile(portNumber, Config[portNumber].CmdInitState);
         AIS_LOG_INFO("Output port%d set to Initial state: %d", portNumber, Config[portNumber].CmdInitState);

         //Set IsInfinite based on Duration: if Duration is 0 (Infinite) set to false. else set to true
         Config[portNumber].IsInfinite = (OutputChannel::DurationInfinite == Config[portNumber].Duration)? true: false;
         Config[portNumber].CommandActive = true;
         switch( Config[portNumber].CmdChangeDuration )//Set Period from ChangeDuration possible value: 1 (250 ms), 2 (500 ms), 4 (1 s)
         {
            case ONE:
            case TWO:
            case FOUR:
               Config[portNumber].CycleCount = Config[portNumber].CmdChangeDuration * (AppCycleRateHz/IDEAL_APP_CYCLE_RATE);
               break;
            case NO_FLASH:
            default:
               Config[portNumber].CycleCount = OUTPUT_NO_FLASH; // 100(no flash)
               break;
         }
         Config[portNumber].NewCommandRcvd = false;
      }
      //if no command active skip following process
      if( false == Config[portNumber].CommandActive ) continue;

      //Check duration Time remaining or infinite set.
      if( (Config[portNumber].Duration > 0)|| Config[portNumber].IsInfinite )
      {
         if(!Config[portNumber].IsInfinite)
         {
            Config[portNumber].Duration--;
         }
         //If no flash, skip following process
         if( OUTPUT_NO_FLASH == Config[portNumber].CycleCount ) continue;

         //Check flash period
         if( 0 == Config[portNumber].CycleCount ) //flash period not expired.
         {
            OutputChannel::State portState = (Config[portNumber].PortCurrentState==OutputChannel::State::PORT_OFF)?
                  OutputChannel::State::PORT_ON:OutputChannel::State::PORT_OFF;
            UpdateOutputPortSinkFile( portNumber, portState );
            AIS_LOG_INFO("Output port%d flash: set to: %d", portNumber, portState);
            Config[portNumber].CycleCount = Config[portNumber].CmdChangeDuration * (AppCycleRateHz/IDEAL_APP_CYCLE_RATE);
         }
         Config[portNumber].CycleCount--;
      }
      else //duration expired: set to final state, clear command Active. reset Period counter.
      {
         UpdateOutputPortSinkFile(portNumber,Config[portNumber].CmdFinalState);
         AIS_LOG_INFO("Output port%d set to Final state: %d", portNumber, Config[portNumber].CmdFinalState);
         Config[portNumber].CommandActive = false;
         Config[portNumber].CycleCount = 0;
      }
   }

   PrintCurrentPortState();
   counter++;
   return true;
}

/******************************************************************************
FUNCTION NAME: PrintCurrentPortState
DESCRIPTION:  Print current state for port and it's duration counts
PARAMETER DESCRIPTION: No parameter
RETURN VALUE: void
*******************************************************************************/
void OutputApp::PrintCurrentPortState()
{
   std::stringstream outputString;
   outputString.str( std::string() );
   outputString.clear();
   outputString << "Counter: "<< counter<<"\n";
   for(uint32_t index= 0 ; index < OutputChannel::Port::OUTPUT_SINK_COUNT; index++)
   {
      outputString << "Port"<< index<< " State:" << Config[index].PortCurrentState
            <<" Duration: " << Config[index].Duration
            <<" Change Duration: "<<Config[index].CmdChangeDuration
            <<" Is infinite? " << Config[index].IsInfinite<<"\n";
#ifdef TEST_MODE
      OutputPortLog[index] << ((Config[index].PortCurrentState == OutputChannel::State::PORT_OFF)? "_":"-");
#endif
   }
   AIS_LOG_DEBUG( outputString.str() );
}

/******************************************************************************
FUNCTION NAME: ReadCommand
DESCRIPTION:  Read latest command from Scs
PARAMETER DESCRIPTION: No parameter
RETURN VALUE: void
*******************************************************************************/
void OutputApp::ReadCommand()
{
   //Get all Commands for each output port from scs interfaces.
   OutputChannel outputChannel;
   while (OutputAppInput->get(outputChannel))
   {
      AIS_LOG_INFO( "Output App command received." );
      for(auto cmd:outputChannel.GetOutputAppCmds())//iterate through command vector
      {
         //Check Command if valid or not, only handle when it is valid.
         if(ValidateCommandInfo(cmd))
         {
            AIS_LOG_INFO( "Output App command received and verified. port: %d, Init State: %d, State Change Duration: %d, Total Duration: %d, FinalState: %d",
                  cmd.OutputPort,
                  cmd.InitialState,
                  cmd.StateChangeDuration,
                  cmd.TotalDuration,
                  cmd.FinalState );
            //Save commands and set New Command Received to true;
            Config[cmd.OutputPort].CmdInitState = cmd.InitialState;
            Config[cmd.OutputPort].CmdFinalState = cmd.FinalState;
            Config[cmd.OutputPort].CmdChangeDuration = cmd.StateChangeDuration;
            Config[cmd.OutputPort].Duration = cmd.TotalDuration * (AppCycleRateHz/IDEAL_APP_CYCLE_RATE);
            Config[cmd.OutputPort].NewCommandRcvd = true;
         }
      }
   }
}

/******************************************************************************
FUNCTION NAME: ValidateCommandInfo
DESCRIPTION:  Check port commands make sure no out of bounds or invalid inputs
PARAMETER DESCRIPTION: cmd: Command for each port
RETURN VALUE: Boolean: true: Command values are good, false: Command have bad value
*******************************************************************************/
bool OutputApp::ValidateCommandInfo(OutputChannel::OutputCmd cmd)
{
   std::stringstream validationErrors;
   validationErrors.str( std::string() );
   validationErrors.clear();
   bool returnVal = true;

   //Check Port number is valid
   if((cmd.OutputPort < OutputChannel::Port::OUTPUT_SINK_1) || (cmd.OutputPort >= OutputChannel::Port::OUTPUT_SINK_COUNT))
   {
      validationErrors << "OutputPort is out of bounds: " << cmd.OutputPort<< "\n";
      returnVal = false;
   }
   //Check Initial State is valid
   if( (cmd.InitialState != OutputChannel::State::PORT_OFF) && (cmd.InitialState != OutputChannel::State::PORT_ON))
   {
      validationErrors << "port" << cmd.OutputPort << " InitialState have invalid input: "<< cmd.InitialState;
      returnVal = false;
   }
   //Check State Change Duration is valid
   if( (cmd.StateChangeDuration != OutputChannel::ChangeDuration::NO_FLASH) &&
         (cmd.StateChangeDuration != OutputChannel::ChangeDuration::ONE)&&
         (cmd.StateChangeDuration != OutputChannel::ChangeDuration::TWO)  &&
         (cmd.StateChangeDuration != OutputChannel::ChangeDuration::FOUR)   )
   {
      validationErrors << "port" << cmd.OutputPort << " StateChangeDuration have invalid input: "<< cmd.StateChangeDuration;
      returnVal = false;
   }
   //Check Final State is valid
   if( (cmd.FinalState != OutputChannel::State::PORT_OFF) && (cmd.FinalState != OutputChannel::State::PORT_ON))
   {
      validationErrors << "port" << cmd.OutputPort << " FinalState have invalid input: "<< cmd.FinalState;
      returnVal = false;
   }

   if( true == returnVal)
   {
      AIS_LOG_INFO( "Output App port%d command good.", cmd.OutputPort );
   }
   else
   {
      AIS_LOG_ERROR( validationErrors.str() );
   }
   return returnVal;
}

/******************************************************************************
FUNCTION NAME:cleanup
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:void
*******************************************************************************/
void OutputApp::cleanup( )
{
   AIS_LOG_INFO( "Output::cleanup" );

#ifdef TEST_MODE
   for(uint32_t index= 0 ; index < OutputChannel::Port::OUTPUT_SINK_COUNT; index++)
   {
      AIS_LOG_DEBUG( OutputPortLog[index].str() );
   }
#endif
}
