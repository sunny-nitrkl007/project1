
#include "../OutputAppTest/OutputAppTest.h"

using namespace task;

AbstractTaskCore* task::getTaskImplementation(void)
{
    static OutputAppTest thisTask("OutputAppTest");
    return dynamic_cast<Task *>(&thisTask);
}

OutputAppTest::OutputAppTest( const std::string& taskName ):
    Task( taskName ),
    outputChannelOutput( NULL ),
    outputChannel{},
    counter(0)
{

}

OutputAppTest::~OutputAppTest( )
{

}

bool OutputAppTest::initialize( )
{
    AIS_LOG_INFO( "OutputAppTest::initialize" );

    outputChannelOutput = dynamic_cast<OutputChannelOutput*>( InterfaceDb::fetch("OutputChannelOutput") );

    if ( !outputChannelOutput )
    {
        AIS_LOG_FATAL( "no outputChannelOutput interface not defined" );
        return false;
    }

    return true;
}

bool OutputAppTest::executive( )
{
    AIS_LOG_INFO( "executive" );//1 hz

    switch (counter)
    {
       case 0:
          AIS_LOG_NOTICE("****************Test Case 1: Test 4 Hz****************");
          AIS_LOG_NOTICE("****************Step 1: Flash port 1 every 250 ms for 2 seconds****************");
          AIS_LOG_NOTICE("Set Port 1 with Init State: on, Change Duration: 1, Duration: 8, Final State: off");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_1,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::ONE,
                8,
                OutputChannel::State::PORT_OFF);
          break;
       case 3:
          AIS_LOG_NOTICE("****************Test Case 2: Test 2 Hz****************");
          AIS_LOG_NOTICE("****************Step 1: Flash port 1 every 500 ms for 3 seconds****************");
          AIS_LOG_NOTICE("Set Port 1 with Init State: off, Change Duration: 2, Duration: 12, Final State: off");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_1,
                OutputChannel::State::PORT_OFF,
                OutputChannel::ChangeDuration::TWO,
                12,
                OutputChannel::State::PORT_OFF);
          break;
       case 8:
          AIS_LOG_NOTICE("****************Test Case 3: Test 1 Hz****************");
          AIS_LOG_NOTICE("****************Step 1: Flash port 1 every 1 s for 3 seconds****************");
          AIS_LOG_NOTICE("Set Port 1 with Init State: on, Change Duration: 4, Duration: 12, Final State: off");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_1,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::FOUR,
                12,
                OutputChannel::State::PORT_OFF);
          break;
       case 12:
          AIS_LOG_NOTICE("****************Test Case 4: New Command over write old Command on port 2****************");
          AIS_LOG_NOTICE("****************Step 1: Flash port 2 every 500 ms for 10 seconds****************");
          AIS_LOG_NOTICE("Set Port 2 with Init State: on, Change Duration: 2, Duration: 40, Final State: on ");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_2,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::TWO,
                40,
                OutputChannel::State::PORT_ON);
          break;
       case 13:
          AIS_LOG_NOTICE("****************Step 2: Flash port 2 every 1 s for 2 seconds****************");
          AIS_LOG_NOTICE("Set Port 2 with Init State: on, Change Duration: 4, Duration: 11, Final State: off");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_2,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::FOUR,
                11,
                OutputChannel::State::PORT_OFF);
          break;
       case 16:
          AIS_LOG_NOTICE("****************Test Case 5: Duration short than Flash Period****************");
          AIS_LOG_NOTICE("****************Step 1: Flash port 2 every 1 s for 250 ms****************");
          AIS_LOG_NOTICE("Set Port 2 with Init State: on, Change Duration: 4, Duration: 1, Final State: off ");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_2,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::FOUR,
                1,
                OutputChannel::State::PORT_OFF);
          break;
       case 17:
          AIS_LOG_NOTICE("****************Test Case 6: NO Flash****************");
          AIS_LOG_NOTICE("****************Step 1: No Flash port 3 for 2 seconds****************");
          AIS_LOG_NOTICE("Set Port 3 with Init State: on, Change Duration: None, Duration: 8, Final State: off ");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_3,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::NO_FLASH,
                8,
                OutputChannel::State::PORT_OFF);
          break;
       case 20:
          AIS_LOG_NOTICE("****************Test Case 7: Set Infinite with no flash****************");
          AIS_LOG_NOTICE("****************Step 1: Set port 3 for no flash for Infinite Duration****************");
          AIS_LOG_NOTICE("Set Port 3 with Init State: on, Change Duration: None, Duration: 0, Final State: off ");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_3,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::NO_FLASH,
                OutputChannel::DurationInfinite,
                OutputChannel::State::PORT_OFF);
          break;
       case 21:
          AIS_LOG_NOTICE("****************Test Case 8: Set Infinite with flash****************");
          AIS_LOG_NOTICE("****************Step 1: Flash port 1 every 500 ms for Infinite Duration****************");
          AIS_LOG_NOTICE("Set Port 1 with Init State: on, Change Duration: 2, Duration: 0, Final State: off ");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_1,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::TWO,
                OutputChannel::DurationInfinite,
                OutputChannel::State::PORT_OFF);
          break;
       case 30:
          AIS_LOG_NOTICE("****************Test Case 8: Set Infinite with flash****************");
          AIS_LOG_NOTICE("****************Step 1: Flash port 1 every 250 ms for Infinite Duration****************");
          AIS_LOG_NOTICE("****************        Flash port 2 every 500 ms for Infinite Duration****************");
          AIS_LOG_NOTICE("****************        Flash port 3  no flash    for Infinite Duration****************");
          AIS_LOG_NOTICE("Set Port 1 with Init State: on, Change Duration: 1, Duration: 0, Final State: off ");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_1,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::ONE,
                OutputChannel::DurationInfinite,
                OutputChannel::State::PORT_OFF);
          AIS_LOG_NOTICE("Set Port 2 with Init State: off, Change Duration: 2, Duration: 0, Final State: off ");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_2,
                OutputChannel::State::PORT_OFF,
                OutputChannel::ChangeDuration::TWO,
                OutputChannel::DurationInfinite,
                OutputChannel::State::PORT_OFF);
          AIS_LOG_NOTICE("Set Port 3 with Init State: on, Change Duration: None, Duration: 0, Final State: off ");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_3,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::NO_FLASH,
                OutputChannel::DurationInfinite,
                OutputChannel::State::PORT_OFF);
          break;
       case 33:
          AIS_LOG_NOTICE("****************Step 2: Flash port 1 every 500 ms for Infinite Duration****************");
          AIS_LOG_NOTICE("****************        Flash port 2 every 250 ms for Infinite Duration****************");
          AIS_LOG_NOTICE("****************        Flash port 3 every   1 s  for Infinite Duration****************");
          AIS_LOG_NOTICE("Set Port 1 with Init State: off, Change Duration: 1, Duration: 0, Final State: off ");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_1,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::TWO,
                OutputChannel::DurationInfinite,
                OutputChannel::State::PORT_OFF);
          AIS_LOG_NOTICE("Set Port 2 with Init State: on, Change Duration: 2, Duration: 0, Final State: off ");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_2,
                OutputChannel::State::PORT_OFF,
                OutputChannel::ChangeDuration::ONE,
                OutputChannel::DurationInfinite,
                OutputChannel::State::PORT_OFF);
          AIS_LOG_NOTICE("Set Port 3 with Init State: off, Change Duration: None, Duration: 0, Final State: off ");
          addNewCommand(OutputChannel::Port::OUTPUT_SINK_3,
                OutputChannel::State::PORT_ON,
                OutputChannel::ChangeDuration::FOUR,
                OutputChannel::DurationInfinite,
                OutputChannel::State::PORT_OFF);
          break;
    }
    publish();
    counter++;
    return true;
}

void OutputAppTest::addNewCommand(OutputChannel::Port port,
      OutputChannel::State initState,
      OutputChannel::ChangeDuration stateChangeDuration,
      uint32_t duration,
      OutputChannel::State finalState)
{
   OutputChannel::OutputCmd command;
   command.OutputPort = port;
   command.InitialState = initState;
   command.StateChangeDuration = stateChangeDuration;
   command.TotalDuration = duration;
   command.FinalState = finalState;
   outputChannel.AddOutputAppCmd(command);
}

void OutputAppTest::publish()
{
   if(!outputChannel.GetOutputAppCmds().empty())
   {
      outputChannelOutput->publish(outputChannel);
      outputChannel.ClearOutputAppCmds();
   }
}

void OutputAppTest::cleanup( )
{
    AIS_LOG_INFO( "OutputAppTest::cleanup" );


}
