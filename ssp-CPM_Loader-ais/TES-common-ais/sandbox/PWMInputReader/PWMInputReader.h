/*******************************************************************************
 ** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
 --------------------------------------------------------------------------------
 FILE NAME: PWMInputReader.h
 DESCRIPTION:
 *******************************************************************************/
#ifndef _PWMINPUTREADER_H_
#define _PWMINPUTREADER_H_
/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/
#include "interfaces/PwmInputChannels/InterfaceTypes.h"
#include <ais/task/Task.h>

/*******************************************************************************
 ** -- #defines --
 *******************************************************************************/
class PWMInputReader : public task ::Task
{
public:
   PWMInputReader();
   PWMInputReader(const std::string& taskName );
   virtual ~PWMInputReader();
   virtual bool initialize();
   virtual bool executive();
   void cleanup(void);

private:
   PwmInputChannelsInput* pwmInputChannelsInput_;
   uint32_t count =0;
};

#endif /* _PWMINPUTREADER_H_ */
