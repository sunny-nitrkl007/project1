/*******************************************************************************
FILE NAME: main.cpp
DESCRIPTION:
    ais_task's own main() (ais/task/main.cpp, in the AIS SDK) calls
    task::getTaskImplementation() to obtain the task instance -- same
    pattern every other app in this tree uses (e.g. apps/CycleSeg/
    CycleSegApp.cpp). No main() is defined here; it's provided by the
    ais_task library this target links against (see CMakeLists.txt).
*******************************************************************************/
#include "cpm_scs_bridge/CpmScsBridgeApp.h"

task::AbstractTaskCore* task::getTaskImplementation(void) {
    static CpmScsBridgeApp thisTask("CpmScsBridge");
    return dynamic_cast<Task*>(&thisTask);
}
