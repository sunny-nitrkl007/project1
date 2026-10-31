#ifndef _PartNumbersInterfaceTypes_h_
#define _PartNumbersInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "PartNumbers.h"

typedef interfaces::baseTypes::InputInterface<PartNumbers> PartNumbersInput;
typedef interfaces::baseTypes::OutputInterface<PartNumbers> PartNumbersOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<PartNumbersInput>()
  {
    return "PartNumbersInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<PartNumbersOutput>()
  {
    return "PartNumbersOutput";
  }
}

#endif
