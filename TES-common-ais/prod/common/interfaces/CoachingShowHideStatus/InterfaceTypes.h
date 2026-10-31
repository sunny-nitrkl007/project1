#ifndef _CoachingShowHideStatusInterfaceTypes_h_
#define _CoachingShowHideStatusInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "CoachingShowHideStatus.h"

typedef interfaces::baseTypes::InputInterface<CoachingShowHideStatus> CoachingShowHideStatusInput;
typedef interfaces::baseTypes::OutputInterface<CoachingShowHideStatus> CoachingShowHideStatusOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<CoachingShowHideStatusInput>()
  {
    return "CoachingShowHideStatusInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<CoachingShowHideStatusOutput>()
  {
    return "CoachingShowHideStatusOutput";
  }
}

#endif
