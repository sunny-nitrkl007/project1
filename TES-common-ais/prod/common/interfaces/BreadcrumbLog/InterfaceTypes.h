#ifndef _BreadcrumbLogInterfaceTypes_h_
#define _BreadcrumbLogInterfaceTypes_h_

#include <ais/interfaces/baseTypes/InputInterface.h>
#include <ais/interfaces/baseTypes/OutputInterface.h>
#include "BreadcrumbLog.h"

typedef interfaces::baseTypes::InputInterface<BreadcrumbLog> BreadcrumbLogInput;
typedef interfaces::baseTypes::OutputInterface<BreadcrumbLog> BreadcrumbLogOutput;

namespace interfaces
{
  template<>
  inline std::string getDefaultInterfaceName<BreadcrumbLogInput>()
  {
    return "BreadcrumbLogInput";
  }

  template<>
  inline std::string getDefaultInterfaceName<BreadcrumbLogOutput>()
  {
    return "BreadcrumbLogOutput";
  }
}

#endif
