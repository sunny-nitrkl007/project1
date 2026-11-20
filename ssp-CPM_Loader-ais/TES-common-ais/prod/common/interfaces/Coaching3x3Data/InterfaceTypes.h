#ifndef _Coaching3x3DataInterfaceTypes_h_
#define _Coaching3x3DataInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "Coaching3x3Data.h"

typedef interfaces::baseTypes::InputInterface<Coaching3x3Data> Coaching3x3DataInput;
typedef interfaces::baseTypes::OutputInterface<Coaching3x3Data> Coaching3x3DataOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<Coaching3x3DataInput>()
  {
    return "Coaching3x3DataInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<Coaching3x3DataOutput>()
  {
    return "Coaching3x3DataOutput";
  }
}

#endif
