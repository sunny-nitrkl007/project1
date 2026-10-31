/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LEDOutput.cpp
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "SwitchInputApp.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

/* WARNING: reading all 4 switch inputs takes longer than 20ms(loop time), so reading
 * only Store switch for right now*/
/*#define STG1_FILE_LOC     "/sys/class/tty/ttyS2/switch/sw_stg_1"
#define STG2_FILE_LOC     "/sys/class/tty/ttyS2/switch/sw_stg_2"
#define STG3_FILE_LOC     "/sys/class/tty/ttyS2/switch/sw_stg_3"*/
#define STG4_FILE_LOC     "/sys/class/tty/ttyS2/switch/sw_stg_4"


FILE* sw_stg_file_ptrs[NO_OF_STG_INPUTS];            // sysfs file pointers for all STG driver files.


/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
using namespace task;

AbstractTaskCore* task::getTaskImplementation(void)
{
    static SwitchInput thisTask("SwitchInput");
    return dynamic_cast<Task *>(&thisTask);
}

/******************************************************************************
FUNCTION NAME:SwitchInput constructor
DESCRIPTION: SwitchInput constructor for initializes an instance of its class     
PARAMETER DESCRIPTION:  task name is passed
RETURN VALUE:  No return Value form constructor           
*******************************************************************************/
SwitchInput::SwitchInput(const std::string& taskName) :
    Task(taskName),
    openDebounceCount_(0),
    closedDebounceCount_(0),
    counts_{0, 0, 0, 0},
    previousStates_{STG::UNKNOWN, STG::UNKNOWN, STG::UNKNOWN, STG::UNKNOWN},
    debouncedStates_(),
    publishState_(true),
    switchInputScsOutput_(nullptr)
{
}

/******************************************************************************
FUNCTION NAME:SwitchInput destructorl
DESCRIPTION: SwitchInput destructor for deallocating an instance of its class
PARAMETER DESCRIPTION: No parameter
RETURN VALUE:   No return Value form destructor           
*******************************************************************************/
SwitchInput::~SwitchInput()
{
}

/******************************************************************************
FUNCTION NAME:initialize
DESCRIPTION: SCS channel and PWM input buffer library is initialize
PARAMETER DESCRIPTION:  No parameter
RETURN VALUE:  Boolean           
*******************************************************************************/
bool SwitchInput::initialize()
{
    bool everythingOk = true;

    if (!(task::InterfaceDb::bind("SwitchInputScsOutput", switchInputScsOutput_))) {
        everythingOk = false;
    }

    { // Read config
        ConfigSection& cs = getTaskConfig();

        if (!cs.get("OpenDebounceCount", openDebounceCount_)) {
            if (!cs.get("DebounceCount", openDebounceCount_)) {
                AIS_LOG_ERROR("Cannot find OpenDebounceCount or DebounceCount config.");
                everythingOk = false;
            }
        }

        if (!cs.get("ClosedDebounceCount", closedDebounceCount_)) {
            if (!cs.get("DebounceCount", closedDebounceCount_)) {
                AIS_LOG_ERROR("Cannot find ClosedDebounceCount or DebounceCount config.");
                everythingOk = false;
            }
        }

        AIS_LOG_INFO("OpenDebounceCount = %d", openDebounceCount_);
        AIS_LOG_INFO("ClosedDebounceCount = %d", closedDebounceCount_);
    }

    return everythingOk;
}

/******************************************************************************
FUNCTION NAME:executive
DESCRIPTION:   executive function is required to publish the data to SCS channel
PARAMETER DESCRIPTION: No parameter
RETURN VALUE: Boolean            
*******************************************************************************/
bool SwitchInput::executive()
{
    /*
     * WARNING: reading all 4 switch inputs takes longer than 20ms(loop time), so reading
     * only Store switch for right now
     */
    int currentStates[NO_OF_STG_INPUTS] = {STG::UNKNOWN, STG::UNKNOWN, STG::UNKNOWN, STG::UNKNOWN};

    { // Read switch inputs
        FILE* fh = fopen(STG4_FILE_LOC, "r");
        if (nullptr != fh) {
            if (!fscanf(fh, "%d", &currentStates[3])) {
                AIS_LOG_ERROR("Failed to read %s", STG4_FILE_LOC);
            }
            fclose(fh);
        }
    }

    // Debounce the switch inputs
    for (int ii = 0; ii < NO_OF_STG_INPUTS; ++ii) {
        int currentState = currentStates[ii];

        if (currentState != previousStates_[ii]) {
            // Something changed, reset the counter
            counts_[ii] = 0;
            previousStates_[ii] = currentState;
        }
        else if (counts_[ii] < INT_MAX) {
            // Same state as last time, increment count.
            ++counts_[ii];
        }


        if (currentState == debouncedStates_.get_STG_value(ii)) {
            // Already debounced
        }
        else if ((currentState == STG::OPEN) && (counts_[ii] >= openDebounceCount_)) {
            // Debounced to the OPEN state
            debouncedStates_.set_STG_value(ii, STG::OPEN);
            publishState_ = true;
        }
        else if ((currentState == STG::CLOSED) && (counts_[ii] >= closedDebounceCount_)) {
            // Debounced to the CLOSED state
            debouncedStates_.set_STG_value(ii, STG::CLOSED);
            publishState_ = true;
        }
    }

    if ((publishState_) && (nullptr != switchInputScsOutput_)) {
        AIS_LOG_INFO("Publishing switch states: %d, %d, %d, %d",
                debouncedStates_.get_STG_value(0), debouncedStates_.get_STG_value(1),
                debouncedStates_.get_STG_value(2), debouncedStates_.get_STG_value(3));
        switchInputScsOutput_->publish(debouncedStates_);
        publishState_ = false;
    }

    return true;  
}

/******************************************************************************
FUNCTION NAME:cleanup
DESCRIPTION:      
PARAMETER DESCRIPTION:                        
RETURN VALUE:void             
*******************************************************************************/
void SwitchInput::cleanup( )
{
    AIS_LOG_INFO("SwitchInput::cleanup");
}
