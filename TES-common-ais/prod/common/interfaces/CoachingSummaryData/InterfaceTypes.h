#ifndef _CoachingSummaryDataInterfaceTypes_h_
#define _CoachingSummaryDataInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "CoachingSummaryData.h"

typedef interfaces::baseTypes::InputInterface<CoachingSummaryData> CoachingSummaryDataInput;
typedef interfaces::baseTypes::OutputInterface<CoachingSummaryData> CoachingSummaryDataOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<CoachingSummaryDataInput>()
  {
    return "CoachingSummaryDataInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<CoachingSummaryDataOutput>()
  {
    return "CoachingSummaryDataOutput";
  }
}

#endif
