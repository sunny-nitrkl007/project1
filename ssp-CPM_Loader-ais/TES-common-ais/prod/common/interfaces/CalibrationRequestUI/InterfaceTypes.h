#ifndef _CalibrationRequestUIInterfaceTypes_h_
#define _CalibrationRequesUItInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "CalibrationRequestUI.h"

typedef interfaces::baseTypes::InputInterface<CalibrationRequestUI> CalibrationRequestUIInput;
typedef interfaces::baseTypes::OutputInterface<CalibrationRequestUI> CalibrationRequestUIOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<CalibrationRequestUIInput>()
  {
    return "CalibrationRequestUIInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<CalibrationRequestUIOutput>()
  {
    return "CalibrationRequestUIOutput";
  }
}

#endif
