#ifndef _PwmInputChannelsInterfaceTypes_h_
#define _PwmInputChannelsInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "PwmInputChannels.h"

typedef interfaces::baseTypes::InputInterface<PwmInputChannels> PwmInputChannelsInput;
typedef interfaces::baseTypes::OutputInterface<PwmInputChannels> PwmInputChannelsOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<PwmInputChannelsInput>()
  {
    return "PwmInputChannelsInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<PwmInputChannelsOutput>()
  {
    return "PwmInputChannelsOutput";
  }
}

#endif
