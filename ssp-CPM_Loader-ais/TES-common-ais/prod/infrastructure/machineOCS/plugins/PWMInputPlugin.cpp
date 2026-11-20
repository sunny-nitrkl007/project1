///////////////////////////////////////////////////////////////////////////////
/// @file      PWMInputPlugin.cpp
/// @author
/// @date      10/05/2018
/// @brief     Implementation of PWM Input  Plugin
///
///
///
/// @attention Copyright (C) 2016
/// @attention Caterpillar Inc.
/// @attention All rights reserved
///////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <ais/PluginProcessor/PluginDefine.h>
#include "PWMInputPlugin.h"
#include "PWMInputTab.h"
#include "ais/task/Task.h"
#include "plugins/CommonDisplayFunctions.h"

#define INPUT_MIN 0
#define INPUT_MAX 2000000

using namespace task;
using namespace OCS;

/******************************************************************************
FUNCTION NAME:PWMInputPlugin constructor
DESCRIPTION: PWMInputPlugin constructor for initializes an instance of its class
PARAMETER DESCRIPTION: No parameter
RETURN VALUE:  No return Value from constructor
*******************************************************************************/
PWMInputPlugin::PWMInputPlugin(): Fl_Group(0, 0, 400, 1200, "PWMInputPlugin"),
      Widget()
{
pthread_mutex_init(&pwmInputMutex, NULL);
}

/******************************************************************************
FUNCTION NAME:PWMInputPlugin destructor
DESCRIPTION: PWMInputPlugin destructor for deallocating an instance of its class
PARAMETER DESCRIPTION:  no parameter
RETURN VALUE:  No return Value from destructor
*******************************************************************************/
PWMInputPlugin::~PWMInputPlugin()
{
   pthread_mutex_destroy(&pwmInputMutex);
}
/******************************************************************************
FUNCTION NAME: Initialize widget
DESCRIPTION: Initialize values
PARAMETER DESCRIPTION: no parameter
RETURN VALUE: bool : true
*******************************************************************************/
bool PWMInputPlugin::initializeWidget(const ConfigSection &cs)
{
   /*Initializing the scs interface */
   pwmInputChannelsOutput  = dynamic_cast<PwmInputChannelsOutput*>( InterfaceDb::fetch("PwmInputChannelsOutput") );
   if(pwmInputChannelsOutput == NULL)
   {
      AIS_LOG_ERROR("Failed to create PWMInputChannlesOutput");
      return false;
   }
   // Create the tab objects.

   make_PWMInputTab();
   add(g_pwm_input);
   add(g_pwm1_input);
   add(g_pwm2_input);
   add(g_pwm3_input);
   add(g_pwm4_input);

   // Initializing all the parameters to default value

   pwmInputChannel= {};
   std::string initValue ="0";
   g_actualTimeUs->value(initValue.c_str());
   g_DiffTime->value(initValue.c_str());
   g_ExecTime->value(initValue.c_str());
   g_Exp->value(initValue.c_str());

   g_pwm1_width->value(initValue.c_str());
   g_pwm1_period->value(initValue.c_str());
   g_pwm2_width->value(initValue.c_str());
   g_pwm2_period->value(initValue.c_str());
   g_pwm3_width->value(initValue.c_str());
   g_pwm3_period->value(initValue.c_str());
   g_pwm4_width->value(initValue.c_str());
   g_pwm4_period->value(initValue.c_str());

   return true;
}
/******************************************************************************
FUNCTION NAME: Update From Input
DESCRIPTION:  Read values from PWMInput Plugin field
PARAMETER DESCRIPTION: input : Inputs the value in Plugin field
RETURN VALUE: int : value
*******************************************************************************/
int PWMInputPlugin::UpdateFromInput(Fl_Input* input)
{
   int value;
   try
   {
      value = std::stoi(std::string(input->value()), nullptr);
   }
   catch(std::invalid_argument& e){
      value = 0;
   }
   catch(std::out_of_range& e){
      value = INT_MAX;
   }
  return value;
}
/******************************************************************************
FUNCTION NAME: Check Range
DESCRIPTION: Checks the minimum and maximum range values
PARAMETER DESCRIPTION: val : checks the value range for Period and Width
RETURN VALUE: int : value
*******************************************************************************/
int PWMInputPlugin::CheckRange(int val)
{
   int value;
   if(val < INPUT_MIN)
   {
      value = INPUT_MIN;
      AIS_LOG_ERROR("The value entered is out of minimum range");
   }
   else if(val > INPUT_MAX)
   {
      value = INPUT_MAX;
      AIS_LOG_ERROR("The value entered is out of maximum range");
   }
   else
   {
      value = val;
   }
   return value;
}

/******************************************************************************
FUNCTION NAME: executive
DESCRIPTION: Set the values to plugin and publish to scs
PARAMETER DESCRIPTION: no parameter
RETURN VALUE: bool : true
*******************************************************************************/
bool PWMInputPlugin::executive()
{

   PThreadLocker locker(&pwmInputMutex);

   pwmInputChannel.PwmData.ActualTimeUs = UpdateFromInput(g_actualTimeUs);
   pwmInputChannel.PwmData.DiffTime = UpdateFromInput(g_DiffTime);
   pwmInputChannel.PwmData.ExecTime = UpdateFromInput(g_ExecTime);
   pwmInputChannel.PwmData.Exp = UpdateFromInput(g_Exp);
   pwmInputChannel.PwmData.Width[0] =  CheckRange(UpdateFromInput(g_pwm1_width));
   pwmInputChannel.PwmData.Period[0] = CheckRange(UpdateFromInput(g_pwm1_period));
   pwmInputChannel.PwmData.Width[1] =  CheckRange(UpdateFromInput(g_pwm2_width));
   pwmInputChannel.PwmData.Period[1] = CheckRange(UpdateFromInput(g_pwm2_period));
   pwmInputChannel.PwmData.Width[2] =  CheckRange(UpdateFromInput(g_pwm3_width));
   pwmInputChannel.PwmData.Period[2] = CheckRange(UpdateFromInput(g_pwm3_period));
   pwmInputChannel.PwmData.Width[3] =  CheckRange(UpdateFromInput(g_pwm4_width));
   pwmInputChannel.PwmData.Period[3] = CheckRange(UpdateFromInput(g_pwm4_period));


   pwmInputChannelsOutput ->publish(pwmInputChannel);

   return true;
}
/******************************************************************************
FUNCTION NAME: Logger status call back
DESCRIPTION: Called whenever we receive a new Applanix Logger Status message
PARAMETER DESCRIPTION:  pwmInput is passed
RETURN VALUE:  void
*******************************************************************************/
void PWMInputPlugin::loggerStatusCallback(const PwmInputChannels &pwmInput)
{

  PThreadLocker locker(&pwmInputMutex);

  this->pwmInputChannel = pwmInput;
}

RegisterPlugin(PWMInputPlugin, interfaces::Interface, PWMInputPlugin);
