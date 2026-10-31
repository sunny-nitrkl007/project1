/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: SwitchInputApp.h
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <ais/task/Task.h>
#include <interfaces/SwitchInputScs/InterfaceTypes.h>

/*******************************************************************************
** -- #defines --
*******************************************************************************/

 

class SwitchInput: public task::Task
{
public:
    SwitchInput( const std::string& taskName );
    virtual ~SwitchInput( );
    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

protected:
private:
    int openDebounceCount_;
    int closedDebounceCount_;
    int counts_[NO_OF_STG_INPUTS];
    int previousStates_[NO_OF_STG_INPUTS];
    SwitchInputScs debouncedStates_;
    bool publishState_;
    SwitchInputScsOutput* switchInputScsOutput_;
};
