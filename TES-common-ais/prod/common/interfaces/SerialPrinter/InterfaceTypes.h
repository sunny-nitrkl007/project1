#ifndef _SerialPrinterInterfaceTypes_h_
#define _SerialPrinterInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "SerialPrinter.h"

typedef interfaces::baseTypes::InputInterface<SerialPrinter> SerialPrinterInput;
typedef interfaces::baseTypes::OutputInterface<SerialPrinter> SerialPrinterOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<SerialPrinterInput>()
  {
    return "SerialPrinterInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<SerialPrinterOutput>()
  {
    return "SerialPrinterOutput";
  }
}

#endif
