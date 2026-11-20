#ifndef _CalMgrCmdRespInterfaceTypes_h_
#define _CalMgrCmdRespInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "CalMgrCmdResp.h"

typedef interfaces::baseTypes::InputInterface<CalMgrCmdResp> CalMgrCmdRespInput;
typedef interfaces::baseTypes::OutputInterface<CalMgrCmdResp> CalMgrCmdRespOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<CalMgrCmdRespInput>()
  {
    return "CalMgrCmdRespInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<CalMgrCmdRespOutput>()
  {
    return "CalMgrCmdRespOutput";
  }
}

#endif
