#ifndef _VP3RecordInterfaceTypes_h_
#define _VP3RecordInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "VP3Record.h"

typedef interfaces::baseTypes::InputInterface<VP3Record> VP3RecordInput;
typedef interfaces::baseTypes::OutputInterface<VP3Record> VP3RecordOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<VP3RecordInput>()
  {
    return "VP3RecordInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<VP3RecordOutput>()
  {
    return "VP3RecordOutput";
  }
}

#endif
