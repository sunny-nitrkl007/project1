#ifndef _OutputChannelInterfaceTypes_h_
#define _OutputChannelInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "OutputChannel.h"

typedef interfaces::baseTypes::InputInterface<OutputChannel> OutputChannelInput;
typedef interfaces::baseTypes::OutputInterface<OutputChannel> OutputChannelOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<OutputChannelInput>()
  {
    return "OutputChannelInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<OutputChannelOutput>()
  {
    return "OutputChannelOutput";
  }
}

#endif
