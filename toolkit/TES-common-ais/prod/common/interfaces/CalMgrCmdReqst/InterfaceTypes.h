#ifndef _CalMgrCmdReqstInterfaceTypes_h_
#define _CalMgrCmdReqstInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "CalMgrCmdReqst.h"

typedef interfaces::baseTypes::InputInterface<CalMgrCmdReqst> CalMgrCmdReqstInput;
typedef interfaces::baseTypes::OutputInterface<CalMgrCmdReqst> CalMgrCmdReqstOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<CalMgrCmdReqstInput>()
  {
    return "CalMgrCmdReqstInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<CalMgrCmdReqstOutput>()
  {
    return "CalMgrCmdReqstOutput";
  }
}

#endif
