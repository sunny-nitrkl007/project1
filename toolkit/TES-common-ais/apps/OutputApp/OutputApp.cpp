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
#include "ROS2Logger.hpp"

#include <cmath>
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

/******************************************************************************
FUNCTION NAME:Output constructor
DESCRIPTION: Output constructor for initializes an instance of its class
PARAMETER DESCRIPTION:  task name is passed
RETURN VALUE:  No return Value form constructor
*******************************************************************************/
OutputApp::OutputApp( const std::string& taskName ):
    ros2_wrapper::Ros2TaskWrapper(taskName),
    outputChannelRosIn_(nullptr),
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
   delete outputChannelRosIn_;
   outputChannelRosIn_ = nullptr;
}

/******************************************************************************
FUNCTION NAME:UptdateOutputPortSinkFile
DESCRIPTION: Writes ON/OFF to lamps
PARAMETER DESCRIPTION:  portIndex: Port Number, portState: the state set to the port.
RETURN VALUE:  void
*******************************************************************************/

void OutputApp::UpdateOutputPortSinkFile( int portIndex, uint8_t portState )
{
   std::string gpioPath;
   switch(portIndex){
      case 0:
         gpioPath = GPIO_SINK1_FILE_LOC;
         break;
      case 1:
         gpioPath = GPIO_SINK2_FILE_LOC;
         break;
      case 2:
         gpioPath = GPIO_SINK3_FILE_LOC;
         break;
      default:
         break;
   }
   FILE* gpioFile = fopen(gpioPath.c_str(), "w") ;
   if(gpioFile != NULL)
   {
      RCLCPP_INFO(get_logger(), "Val written to gpio %d = %d", portIndex, static_cast<int>(portState));
      fprintf(gpioFile,"%d",portState);
      Config[portIndex].PortCurrentState = portState;
   }
   else
   {
      RCLCPP_WARN(get_logger(), "Failed to open %s", gpioPath.c_str());
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
   declare_parameter<std::string>("logger_threshold", "error");
   std::string const loggerThreshold = get_parameter("logger_threshold").as_string();
   ROS2Logger::Instance().SetLogLevel(loggerThreshold);

   declare_parameter<double>("cycle_rate_hz", 4.0);
   const double cycleRateHz = get_parameter("cycle_rate_hz").as_double();
   if (!std::isfinite(cycleRateHz) || cycleRateHz < IDEAL_APP_CYCLE_RATE ||
       std::fmod(cycleRateHz, IDEAL_APP_CYCLE_RATE) != 0.0) {
      RCLCPP_FATAL(get_logger(), "cycle_rate_hz must be a positive multiple of 4 Hz");
      return false;
   }
   AppCycleRateHz = static_cast<uint32_t>(cycleRateHz);

   outputChannelRosIn_ = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::OutputChannel>(
         shared_from_this(), "output_channel");
   if (!outputChannelRosIn_) {
      RCLCPP_FATAL(get_logger(), "Failed to initialize output_channel ROS2 interface");
      return false;
   }
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
   RCLCPP_DEBUG(get_logger(), "Output executive cycle");

   ReadCommand();

   for( uint32_t portNumber=0; portNumber<OUTPUT_SINK_COUNT; portNumber++ )
   {
      if(true == Config[portNumber].NewCommandRcvd) //if we got new command: set Initial State
      {
         UpdateOutputPortSinkFile(portNumber, Config[portNumber].CmdInitState);
         RCLCPP_INFO(get_logger(), "Output port%d set to Initial state: %d", portNumber, Config[portNumber].CmdInitState);

         //Set IsInfinite based on Duration: if Duration is 0 (Infinite) set to false. else set to true
         Config[portNumber].IsInfinite = (DurationInfinite == Config[portNumber].Duration)? true: false;
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
            uint8_t portState = (Config[portNumber].PortCurrentState == PORT_OFF) ? PORT_ON : PORT_OFF;
            UpdateOutputPortSinkFile( portNumber, portState );
            RCLCPP_INFO(get_logger(), "Output port%d flash: set to: %d", portNumber, portState);
            Config[portNumber].CycleCount = Config[portNumber].CmdChangeDuration * (AppCycleRateHz/IDEAL_APP_CYCLE_RATE);
         }
         Config[portNumber].CycleCount--;
      }
      else //duration expired: set to final state, clear command Active. reset Period counter.
      {
         UpdateOutputPortSinkFile(portNumber,Config[portNumber].CmdFinalState);
         RCLCPP_INFO(get_logger(), "Output port%d set to Final state: %d", portNumber, Config[portNumber].CmdFinalState);
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
   for(uint32_t index= 0 ; index < OUTPUT_SINK_COUNT; index++)
   {
      outputString << "Port"<< index<< " State:" << Config[index].PortCurrentState
            <<" Duration: " << Config[index].Duration
            <<" Change Duration: "<<Config[index].CmdChangeDuration
            <<" Is infinite? " << Config[index].IsInfinite<<"\n";
#ifdef TEST_MODE
      OutputPortLog[index] << ((Config[index].PortCurrentState == PORT_OFF)? "_":"-");
#endif
   }
   RCLCPP_DEBUG(get_logger(), "%s", outputString.str().c_str());
}

/******************************************************************************
FUNCTION NAME: ReadCommand
DESCRIPTION:  Drain the output command topic
PARAMETER DESCRIPTION: No parameter
RETURN VALUE: void
*******************************************************************************/
void OutputApp::ReadCommand()
{
   job_mgr_interfaces::msg::OutputChannel rosOutputChannel;
   while (outputChannelRosIn_->get(rosOutputChannel))
   {
      RCLCPP_INFO(get_logger(), "Output App command received.");
      for (const auto& rosCommand : rosOutputChannel.commands)
      {
         if (rosCommand.total_duration < 0) {
            RCLCPP_ERROR(get_logger(), "Output command duration is negative: %d", rosCommand.total_duration);
            continue;
         }
         OutputCommand command{
            rosCommand.output_port,
            rosCommand.initial_state,
            rosCommand.state_change_duration,
            static_cast<uint32_t>(rosCommand.total_duration),
            rosCommand.final_state
         };
         if (ValidateCommandInfo(command))
         {
            RCLCPP_INFO(get_logger(), "Output App command received and verified. port: %d, Init State: %d, State Change Duration: %d, Total Duration: %u, FinalState: %d",
                  command.OutputPort,
                  command.InitialState,
                  command.StateChangeDuration,
                  command.TotalDuration,
                  command.FinalState );
            Config[command.OutputPort].CmdInitState = command.InitialState;
            Config[command.OutputPort].CmdFinalState = command.FinalState;
            Config[command.OutputPort].CmdChangeDuration = command.StateChangeDuration;
            Config[command.OutputPort].Duration = command.TotalDuration * (AppCycleRateHz/IDEAL_APP_CYCLE_RATE);
            Config[command.OutputPort].NewCommandRcvd = true;
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
bool OutputApp::ValidateCommandInfo(const OutputCommand& cmd)
{
   std::stringstream validationErrors;
   validationErrors.str( std::string() );
   validationErrors.clear();
   bool returnVal = true;

   //Check Port number is valid
   if(cmd.OutputPort >= OUTPUT_SINK_COUNT)
   {
      validationErrors << "OutputPort is out of bounds: " << cmd.OutputPort<< "\n";
      returnVal = false;
   }
   //Check Initial State is valid
   if( (cmd.InitialState != PORT_OFF) && (cmd.InitialState != PORT_ON))
   {
      validationErrors << "port" << cmd.OutputPort << " InitialState have invalid input: "<< cmd.InitialState;
      returnVal = false;
   }
   //Check State Change Duration is valid
   if( (cmd.StateChangeDuration != NO_FLASH) &&
         (cmd.StateChangeDuration != ONE)&&
         (cmd.StateChangeDuration != TWO)  &&
         (cmd.StateChangeDuration != FOUR)   )
   {
      validationErrors << "port" << cmd.OutputPort << " StateChangeDuration have invalid input: "<< cmd.StateChangeDuration;
      returnVal = false;
   }
   //Check Final State is valid
   if( (cmd.FinalState != PORT_OFF) && (cmd.FinalState != PORT_ON))
   {
      validationErrors << "port" << cmd.OutputPort << " FinalState have invalid input: "<< cmd.FinalState;
      returnVal = false;
   }

   if( true == returnVal)
   {
      RCLCPP_INFO(get_logger(), "Output App port%d command good.", cmd.OutputPort);
   }
   else
   {
      RCLCPP_ERROR(get_logger(), "%s", validationErrors.str().c_str());
   }
   return returnVal;
}

/******************************************************************************
FUNCTION NAME:cleanup
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:void
*******************************************************************************/
void OutputApp::startExecutiveTimer()
{
   createExecutiveTimer(AppCycleRateHz);
}

void OutputApp::cleanup( )
{
   RCLCPP_INFO(get_logger(), "Output cleanup");
   delete outputChannelRosIn_;
   outputChannelRosIn_ = nullptr;

#ifdef TEST_MODE
   for(uint32_t index= 0 ; index < OUTPUT_SINK_COUNT; index++)
   {
      RCLCPP_DEBUG(get_logger(), "%s", OutputPortLog[index].str().c_str());
   }
#endif
}

int main(int argc, char** argv)
{
   return ros2_wrapper::Ros2TaskWrapper::run<OutputApp>(argc, argv);
}
