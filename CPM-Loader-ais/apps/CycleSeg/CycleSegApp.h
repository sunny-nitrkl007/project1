#ifndef CYCLESEGAPP_H
#define CYCLESEGAPP_H

#include <string>
#include <chrono>
#include <unordered_map>

#include <ais/task/Task.h>

#include <interfaces/AppReg/InterfaceTypes.h>
#include <interfaces/AutonomyConditionDiagnostics/TxInterfaceInputChannel.h>

#include "CycleSegInput.h"
#include "CycleSegOutput.h"

/*
 * Cycle Segmentation App
 */
class CycleSegApp: public task::Task
{
public:
    CycleSegApp(const std::string& taskName);
    virtual ~CycleSegApp();

    virtual bool initialize();
    virtual bool executive();
    virtual void cleanup();

protected:

private:
    bool modelInitialized_;

    CycleSegInput input_;
    CycleSegOutput output_;

    AppRegInput* appRegInputChannel_;
    AppRegOutput* appRegOutputChannel_;
    AutonomyConditionDiagnosticsTxInterfaceInputChannel* autonomyConditionDiagnosticsTxInputChannel_;
    std::unordered_map<std::string, bool> appRegMap_;
    uint32_t appRegUpdateCount_;
    bool enableWriteVp3Record;
};


#endif
