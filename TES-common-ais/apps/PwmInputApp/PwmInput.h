/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: PwmInput.h
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/

#ifndef TESTTASK_H
#define TESTTASK_H
#define DEBUG

#define REALTIME_PRIORITY_ONE   1
#define MAX_SAMPLES             1
#define PWM_PASS                0
#define MAX_CH                  4       
#define CONVERT_HZ_TO_MILLISEC(X) ((1.0/(float)X) * 1000.0)
#include <ais/task/Task.h>
#include <interfaces/PwmInputChannels/InterfaceTypes.h>
#include <interfaces/AppReg/InterfaceTypes.h>

class PwmInput: public task::Task
{
public:
    PwmInput( const std::string& taskName );
    virtual ~PwmInput( );
    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );
    static  void* publishScsCh(void*);

protected:
private:
   AppRegStorage AppRegList;
   AppRegInput *AppRegInput_; 
   AppRegOutput                  *AppRegOutput_;
   void UpdateRegistrations(void);


};

#endif
