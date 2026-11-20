#ifndef _FileTransferBridgeRequestInterfaceTypes_h_
#define _FileTransferBridgeRequestInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "FileTransferBridgeRequest.h"

typedef interfaces::baseTypes::InputInterface<FileTransferBridgeRequest> FileTransferBridgeRequestInput;
typedef interfaces::baseTypes::OutputInterface<FileTransferBridgeRequest> FileTransferBridgeRequestOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<FileTransferBridgeRequestInput>()
  {
    return "FileTransferBridgeRequestInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<FileTransferBridgeRequestOutput>()
  {
    return "FileTransferBridgeRequestOutput";
  }
}

#endif
