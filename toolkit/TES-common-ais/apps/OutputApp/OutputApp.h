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
#include <job_mgr_interfaces/msg/output_channel.hpp>
#include "ros2wrapper/RosInputInterface.h"
#include "ros2wrapper/Ros2TaskWrapper.h"
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
   static constexpr uint8_t OUTPUT_SINK_COUNT = 3;
   static constexpr uint8_t PORT_OFF = 0;
   static constexpr uint8_t PORT_ON = 1;
   static constexpr uint8_t NO_FLASH = 0;
   static constexpr uint8_t ONE = 1;
   static constexpr uint8_t TWO = 2;
   static constexpr uint8_t FOUR = 4;
   static constexpr uint32_t DurationInfinite = 0;

   struct OutputCommand
   {
      uint8_t OutputPort;
      uint8_t InitialState;
      uint8_t StateChangeDuration;
      uint32_t TotalDuration;
      uint8_t FinalState;
   };

   void UpdateOutputPortSinkFile( int portIndex, uint8_t portState );
   void ReadCommand( void );
   void PrintCurrentPortState( void );
   bool ValidateCommandInfo(const OutputCommand& cmd);

   struct OutputConfig
   {
      uint8_t CmdInitState;
      uint8_t CmdFinalState;
      uint8_t CmdChangeDuration;
      uint32_t Duration;  // duration 0 is infinite
      uint8_t CycleCount; // possible value: 1 (250 ms), 2 (500 ms), 4 (1 s), 100(no flash)
      uint8_t PortCurrentState;
      bool NewCommandRcvd;
      bool CommandActive;
      bool IsInfinite;
   };

   uint32_t counter = 0;
   const uint8_t OUTPUT_NO_FLASH = 100;
   const uint8_t IDEAL_APP_CYCLE_RATE = 4;

   uint32_t AppCycleRateHz;
   ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::OutputChannel>* outputChannelRosIn_;
   OutputConfig Config[OUTPUT_SINK_COUNT];
   std::stringstream OutputPortLog[OUTPUT_SINK_COUNT];
};
