#ifndef _AppRegInterfaceTypes_h_
#define _AppRegInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "AppReg.h"

typedef interfaces::baseTypes::InputInterface<AppReg> AppRegInput;
typedef interfaces::baseTypes::OutputInterface<AppReg> AppRegOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<AppRegInput>()
  {
    return "AppRegInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<AppRegOutput>()
  {
    return "AppRegOutput";
  }
}

#endif
