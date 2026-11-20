#ifndef _DataLinkDataInterfaceTypes_h_
#define _DataLinkDataInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "DataLinkData.h"

typedef interfaces::baseTypes::InputInterface<DataLinkData> DataLinkDataInput;
typedef interfaces::baseTypes::OutputInterface<DataLinkData> DataLinkDataOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<DataLinkDataInput>()
  {
    return "DataLinkDataInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<DataLinkDataOutput>()
  {
    return "DataLinkDataOutput";
  }
}

#endif
