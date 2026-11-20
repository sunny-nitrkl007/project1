#ifndef _CreateFileRequestInterfaceTypes_h_
#define _CreateFileRequestInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "CreateFileRequest.h"

typedef interfaces::baseTypes::InputInterface<CreateFileRequest> CreateFileRequestInput;
typedef interfaces::baseTypes::OutputInterface<CreateFileRequest> CreateFileRequestOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<CreateFileRequestInput>()
  {
    return "CreateFileRequestInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<CreateFileRequestOutput>()
  {
    return "CreateFileRequestOutput";
  }
}

#endif
