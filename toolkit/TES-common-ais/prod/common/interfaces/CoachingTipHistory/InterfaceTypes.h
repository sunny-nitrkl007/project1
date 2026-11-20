#ifndef _CoachingTipHistoryInterfaceTypes_h_
#define _CoachingTipHistoryInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "CoachingTipHistory.h"

typedef interfaces::baseTypes::InputInterface<CoachingTipHistory> CoachingTipHistoryInput;
typedef interfaces::baseTypes::OutputInterface<CoachingTipHistory> CoachingTipHistoryOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<CoachingTipHistoryInput>()
  {
    return "CoachingTipHistoryInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<CoachingTipHistoryOutput>()
  {
    return "CoachingTipHistoryOutput";
  }
}

#endif
