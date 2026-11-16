/*******************************************************************************
 ** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
 --------------------------------------------------------------------------------
 FILE NAME: LEDOutput.h
 DESCRIPTION:
 *******************************************************************************/

/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/
#include <cstdint>
#include <sstream>
#include <string>
#include <interfaces/OutputChannel/OutputChannel.h>
#include <job_mgr_interfaces/msg/output_channel.hpp>
#include <ros2wrapper/RosInputInterface.h>
#include <ros2wrapper/Ros2TaskWrapper.h>
/*******************************************************************************
 ** -- #defines --
 *******************************************************************************/

class OutputApp: public ros2_wrapper::Ros2TaskWrapper
{
public:
   OutputApp( const std::string& taskName );
   ~OutputApp() override;
   bool initialize() override;
   bool executive() override;
   void cleanup() override;
   void startExecutiveTimer() override;
protected:
private:
   void UpdateOutputPortSinkFile( int portIndex, OutputChannel::State portState );
   void ReadCommand( void );
   void PrintCurrentPortState( void );
   bool ValidateCommandInfo(OutputChannel::OutputCmd cmd);

   struct OutputConfig
   {
      OutputChannel::State CmdInitState;
      OutputChannel::State CmdFinalState;
      OutputChannel::ChangeDuration CmdChangeDuration;
      uint32_t Duration;  // duration 0 is infinite
      uint8_t CycleCount; // possible value: 1 (250 ms), 2 (500 ms), 4 (1 s), 100(no flash)
      OutputChannel::State PortCurrentState;
      bool NewCommandRcvd;
      bool CommandActive;
      bool IsInfinite;
   };

   uint32_t counter = 0;
   const uint8_t OUTPUT_NO_FLASH = 100;
   const uint8_t IDEAL_APP_CYCLE_RATE = 4;

   uint32_t AppCycleRateHz;
   ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::OutputChannel>* outputChannelRosIn_;
   OutputConfig Config[OutputChannel::Port::OUTPUT_SINK_COUNT];
   std::stringstream OutputPortLog[OutputChannel::Port::OUTPUT_SINK_COUNT];
};
