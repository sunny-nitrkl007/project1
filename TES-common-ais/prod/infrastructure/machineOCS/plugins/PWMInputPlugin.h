/*******************************************************************************
 ** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
 --------------------------------------------------------------------------------
 FILE NAME: PWMInputPlugin.h
 DESCRIPTION:
 *******************************************************************************/
#ifndef _PWMINPUTPLUGIN_H_
#define _PWMINPUTPLUGIN_H_
/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/
#include "MachineOCS.h"
#include "plugins/Widget.h"
#include "plugins/Executable.h"
#include "interfaces/PwmInputChannels/InterfaceTypes.h"

/*******************************************************************************
 ** -- #defines --
 *******************************************************************************/
namespace OCS
{
class PWMInputPlugin : public Fl_Group, public Widget, public Executable
{
public:
   PWMInputPlugin();
   virtual ~PWMInputPlugin();

   virtual bool initializeWidget(const ConfigSection &cs);
   virtual bool executive(void);
   int UpdateFromInput(Fl_Input* input);
   int CheckRange(int val);
private:
   pthread_mutex_t pwmInputMutex;
   PwmInputChannels pwmInputChannel;
   PwmInputChannelsOutput   *pwmInputChannelsOutput ;

   void loggerStatusCallback(const PwmInputChannels &pwmInput);
};
}

#endif /* _PWMINPUTPLUGIN_H_ */
