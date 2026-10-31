#ifndef _FileTransferBridgeIndicationInterfaceTypes_h_
#define _FileTransferBridgeIndicationInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "FileTransferBridgeIndication.h"

typedef interfaces::baseTypes::InputInterface<FileTransferBridgeIndication> FileTransferBridgeIndicationInput;
typedef interfaces::baseTypes::OutputInterface<FileTransferBridgeIndication> FileTransferBridgeIndicationOutput;

namespace interfaces
{
   template<>
   inline std::string getDefaultInterfaceName<FileTransferBridgeIndicationInput>()
   {
      return "FileTransferBridgeIndicationInput";
   }

   template<>
   inline std::string getDefaultInterfaceName<FileTransferBridgeIndicationOutput>()
   {
      return "FileTransferBridgeIndicationOutput";
   }
}

#endif
