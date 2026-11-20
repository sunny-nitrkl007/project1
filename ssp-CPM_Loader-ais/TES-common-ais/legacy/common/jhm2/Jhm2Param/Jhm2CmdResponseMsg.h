///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2CmdResponseMsg.h
/// @author    strubjc
/// @date      Oct 20, 2015
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2CMDRESPONSEMSG_H_
#define JHM2CMDRESPONSEMSG_H_

#include <string>
#include <vector>
#include <std_types.h>
#include "Jhm2Param.h"


class Jhm2CmdResponseMsg: public Jhm2ParamMsg
{
  public:
    Jhm2CmdResponseMsg() {}
    ~Jhm2CmdResponseMsg() {}
};

#endif /* JHM2CMDRESPONSEMSG_H_ */
