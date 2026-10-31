/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: CoachingTaskTest.cpp
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "CoachingTaskTest.h"

#include <unistd.h>
#include "ais/task/Task.h"
#include <time.h>

using namespace task;

AbstractTaskCore* task::getTaskImplementation(void)
{
    static CoachingTaskTest thisTask("CoachingTaskTest");
    return dynamic_cast<Task *>(&thisTask);
}
/******************************************************************************
FUNCTION NAME:CoachingTaskTest constructor
DESCRIPTION: PWMInput constructor for initializes an instance of its class
PARAMETER DESCRIPTION:  task name is passed
RETURN VALUE:  No return Value from constructor
*******************************************************************************/
CoachingTaskTest::CoachingTaskTest(const std::string& taskName ):
       Task {taskName},
       coachingSummaryDataInput{nullptr},
       coaching3x3DataInput{nullptr},
       dataLinkDataOutput{nullptr}
{
}
/******************************************************************************
FUNCTION NAME:CoachingTaskTest destructor
DESCRIPTION: CoachingTaskTest destructor for deallocating an instance of its class
PARAMETER DESCRIPTION:  no parameter
RETURN VALUE:  No return Value from destructor
*******************************************************************************/
CoachingTaskTest::~CoachingTaskTest()
{
}

/******************************************************************************
FUNCTION NAME: Initialize widget
DESCRIPTION: Initialize values
PARAMETER DESCRIPTION: no parameter
RETURN VALUE: bool : true
*******************************************************************************/
bool CoachingTaskTest::initialize()
{
    if (!task::InterfaceDb::bind("CoachingSummaryDataInput", coachingSummaryDataInput) ||
        !task::InterfaceDb::bind("Coaching3x3DataInput", coaching3x3DataInput) ||
        !task::InterfaceDb::bind("DataLinkDataOutput", dataLinkDataOutput))
    {
        return false;
    }
    auto config = getTaskConfig();

    DataLinkParam dlParam;
    dlParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_INT);
    dlParam.SetParamId(SecuritySystemCurrentSecurityIDParam::CatExtId);
    dlParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT);
    dlParam.SetParameterType(CDL2_VAR_NO_DSI);
    dlParam.SetSid(0xFF);
    dlParam.SetScaling(1);
    dlParam.SetOffset(0);
    dlParam.SetVarLengthParamValue(nullptr, 0, 0); // Set DSI without changing LastValue
    dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::CAT_EXT);
    SecuritySystemCurrentSecurityIDParam securityIdParam(dlParam);
    securityIdParam.setID(10);

    // Read operatorName from ruby config
    std::string operatorName = "Default";
    config.get("operatorName", operatorName);
    securityIdParam.setIDDescription(operatorName);
    bool success = dataLinkData.AddDataLinkParam(dlParam);

    return success;
}
/******************************************************************************
FUNCTION NAME: executive
DESCRIPTION: Read the values from scs and print the values
PARAMETER DESCRIPTION: no parameter
RETURN VALUE: bool : true
*******************************************************************************/
bool CoachingTaskTest::executive()
{
    CoachingSummaryData coachingSummaryData;
    while(coachingSummaryDataInput->get(coachingSummaryData))
    {
        AIS_LOG_FATAL("CoachingSummaryData - Percent_0: %u, Percent_25: %u, Percent_50: %u, Percent_75: %u, Percent_100: %u", coachingSummaryData.countOfPercent_0, coachingSummaryData.countOfPercent_25, coachingSummaryData.countOfPercent_50, coachingSummaryData.countOfPercent_75, coachingSummaryData.countOfPercent_100);
        for (auto &tipOutput : coachingSummaryData.coachingTipOutputList)
        {
            if (tipOutput.tipStat.size() > 1)
            {
                AIS_LOG_FATAL("CoachingSummaryData - tipNumber: %u, trigger: %u, lastSeverity: %f, stat1: %f, stat2: %f", tipOutput.tipNumber, tipOutput.tipTrigger, tipOutput.lastSeverity, tipOutput.tipStat[0], tipOutput.tipStat[1]);
            }
        }
    }

    Coaching3x3Data coaching3x3Data;
    while(coaching3x3DataInput->get(coaching3x3Data))
    {
        AIS_LOG_FATAL("Coaching3x3Data - Name: %s, Count: %u", coaching3x3Data.name.c_str(), coaching3x3Data.count);
        for (auto &tip : coaching3x3Data.tips)
        {
            AIS_LOG_FATAL("Coaching3x3Data - number: %u, OpTipEnableState: %u, currentSeverity: %f, totalSeverity: %f", tip.number, tip.OpTipEnableState, tip.currentSeverity, tip.totalSeverity);
            AIS_LOG_FATAL("severity %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f", tip.severityHistory[0], tip.severityHistory[1], tip.severityHistory[2], tip.severityHistory[3], tip.severityHistory[4], tip.severityHistory[5], tip.severityHistory[6], tip.severityHistory[7], tip.severityHistory[8], tip.severityHistory[9]);
        }
    }
    dataLinkDataOutput->publish(dataLinkData);

    return true;
}
/******************************************************************************
FUNCTION NAME: Cleanup
DESCRIPTION:
PARAMETER DESCRIPTION: no parameter
RETURN VALUE: void
*******************************************************************************/
void CoachingTaskTest::cleanup( )
{
}
