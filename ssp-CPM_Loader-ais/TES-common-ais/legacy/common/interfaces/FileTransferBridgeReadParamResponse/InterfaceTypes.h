#ifndef _FileTransferBridgeReadParamResponseInterfaceTypes_h_
#define _FileTransferBridgeReadParamResponseInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "FileTransferBridgeReadParamResponse.h"

typedef interfaces::baseTypes::InputInterface<FileTransferBridgeReadParamResponse> FileTransferBridgeReadParamResponseInput;
typedef interfaces::baseTypes::OutputInterface<FileTransferBridgeReadParamResponse> FileTransferBridgeReadParamResponseOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<FileTransferBridgeReadParamResponseInput>()
  {
    return "FileTransferBridgeReadParamResponseInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<FileTransferBridgeReadParamResponseOutput>()
  {
    return "FileTransferBridgeReadParamResponseOutput";
  }
}

#endif
