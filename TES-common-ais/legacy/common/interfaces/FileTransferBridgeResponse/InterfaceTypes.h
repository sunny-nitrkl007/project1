#ifndef _FileTransferBridgeResponseInterfaceTypes_h_
#define _FileTransferBridgeResponseInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "FileTransferBridgeResponse.h"

typedef interfaces::baseTypes::InputInterface<FileTransferBridgeResponse> FileTransferBridgeResponseInput;
typedef interfaces::baseTypes::OutputInterface<FileTransferBridgeResponse> FileTransferBridgeResponseOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<FileTransferBridgeResponseInput>()
  {
    return "FileTransferBridgeResponseInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<FileTransferBridgeResponseOutput>()
  {
    return "FileTransferBridgeResponseOutput";
  }
}

#endif
