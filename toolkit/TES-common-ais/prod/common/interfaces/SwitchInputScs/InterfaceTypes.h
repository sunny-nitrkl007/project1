#ifndef _SwitchInputScsInterfaceTypes_h_
#define _SwitchInputScsInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "SwitchInputScs.h"

typedef interfaces::baseTypes::InputInterface<SwitchInputScs> SwitchInputScsInput;
typedef interfaces::baseTypes::OutputInterface<SwitchInputScs> SwitchInputScsOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<SwitchInputScsInput>()
  {
    return "SwitchInputScsInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<SwitchInputScsOutput>()
  {
    return "SwitchInputScsOutput";
  }
}

#endif
