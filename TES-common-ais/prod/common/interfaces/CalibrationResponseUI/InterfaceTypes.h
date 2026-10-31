#ifndef _CalibrationResponseUIInterfaceTypes_h_
#define _CalibrationResponseUIInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "CalibrationResponseUI.h"

typedef interfaces::baseTypes::InputInterface<CalibrationResponseUI> CalibrationResponseUIInput;
typedef interfaces::baseTypes::OutputInterface<CalibrationResponseUI> CalibrationResponseUIOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<CalibrationResponseUIInput>()
  {
    return "CalibrationResponseUIInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<CalibrationResponseUIOutput>()
  {
    return "CalibrationResponseUIOutput";
  }
}

#endif
