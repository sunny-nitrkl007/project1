#include <chrono>
#include "CoachingAppSpecificExample.h"
#include "dummyTip.h"
#include "octip_mach00_out.h"

///////////////////////////////////////////////////////////////////////////////
/// @Static member function that returns the instance of the application
/// coaching object
///////////////////////////////////////////////////////////////////////////////
CoachingAppSpecific* CoachingAppSpecific::getAppSpecific( task::Task& parent, 
                                                          CoachingSummaryData& coachingSummaryData,
                                                          Coaching3x3DataList& coaching3x3DataList   )
{
    static CoachingAppSpecificExample coachingAppSpecific(parent, coachingSummaryData, coaching3x3DataList);
    return &coachingAppSpecific;
}

///////////////////////////////////////////////////////////////////////////////
/// @Constructor
///////////////////////////////////////////////////////////////////////////////
CoachingAppSpecificExample::CoachingAppSpecificExample( task::Task& parent,
                                                        CoachingSummaryData& coachingSummaryData,
                                                        Coaching3x3DataList& coaching3x3DataList ) :
    CoachingAppSpecific{parent, coachingSummaryData, coaching3x3DataList}
{
    // NOTE: tipNumber and tipPriority must be unique
                                                     // tipNumber tipName  tipPriority          tipProductGroup   tipCategory                   tipTag                 tipVersion  expectedOccurenceRatePerHour   0%-Thresh  25%-Thresh  50%-Thresh   75%-Thresh   videoFileName
    coachingTipInfo.push_back(CoachingTipOutputBase_t(   1,    "TIP 1",  coachingTipInfo.size() + 1,  "AT",       SID_OPERATING_EFFICIENCY, TipTags_t{Cycle1Name, Cycle2Name},  "ver0",       1.0f,                        0.01f,           0.1f,     0.2f,        0.4f,    "Video_1.webm", "Image_1.png"));
    coachingTipInfo.push_back(CoachingTipOutputBase_t(   2,    "TIP 2",  coachingTipInfo.size() + 1,  "AT",       SID_OPERATING_EFFICIENCY, TipTags_t{Cycle1Name},              "ver0",       2.0f,                        0.01f,           0.1f,     0.2f,        0.4f,    "Video_2.webm", ""));
    coachingTipInfo.push_back(CoachingTipOutputBase_t(   3,    "TIP 3",  coachingTipInfo.size() + 1,  "AT",       SID_MACHINE_HEALTH,       TipTags_t{Cycle1Name, Cycle2Name},  "ver0",       3.0f,                        0.01f,           0.1f,     0.2f,        0.4f,    "Video_3.webm", ""));
    coachingTipInfo.push_back(CoachingTipOutputBase_t(   4,    "TIP 4",  coachingTipInfo.size() + 1,  "AT",       SID_MACHINE_HEALTH,       TipTags_t{Cycle1Name},              "ver0",       4.0f,                        0.01f,           0.1f,     0.2f,        0.4f,    "Video_4.webm", ""));
    coachingTipInfo.push_back(CoachingTipOutputBase_t(   5,    "TIP 5",  coachingTipInfo.size() + 1,  "AT",       SID_HAZARDOUS,            TipTags_t{Cycle1Name, Cycle2Name},  "ver0",       5.0f,                        0.01f,           0.1f,     0.2f,        0.4f,    "Video_5.webm", ""));
}

///////////////////////////////////////////////////////////////////////////////
/// @Initialize tip model
///////////////////////////////////////////////////////////////////////////////
bool CoachingAppSpecificExample::initialize()
{
    // If necessary, read from nvm 
    
    // Initialize model
    dummyTipInit();

    return true;
}

///////////////////////////////////////////////////////////////////////////////
/// @Initialize/clear operator summary & 3x3 data
///////////////////////////////////////////////////////////////////////////////
bool CoachingAppSpecificExample::reset()
{
    AIS_LOG_INFO("Resetting Operator Stats");
    // Build Tip Data
    coachingSummaryData.clear();

    // Copy coachingTipInfo into the coachingSummaryData
    for (const auto& tipInfo : coachingTipInfo)
    {
        coachingSummaryData.coachingTipOutputList.push_back(CoachingTipOutput_t(tipInfo));
    }

    // Build 3x3 Data List
    coaching3x3DataList.clear();
    TipTags_t cycleNames{Cycle1Name, Cycle2Name};  // In this example, DIG contains tips 1-5, LOAD-N-CARRY contains tips 1,3,5
    for (const auto& cycleName : cycleNames)
    {
        Coaching3x3Data cycleData;
        cycleData.name = cycleName;
        cycleData.OpTipEnableState = true; 
        for (const auto& tip : coachingSummaryData.coachingTipOutputList)
        {
            if (tip.tipTags.find(cycleName) != tip.tipTags.end())
            {
                AIS_LOG_INFO("Tip number %u added to %s Coaching3x3Data", tip.tipNumber, cycleName.c_str());
                cycleData.tips.push_back(Coaching3x3TipData_t{tip.tipNumber, tip.tipName, tip.videoFileName, true});
            }
        }

        // Add to list
        coaching3x3DataList.push_back(cycleData);
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
/// @Read the inputs and pass to the model
///////////////////////////////////////////////////////////////////////////////
void CoachingAppSpecificExample::getAndSetInputs(DataLinkData& datalinkData)
{
    // TODO: Read datalinkData and set model inputs
    // Function could be called multiple times in one cycle with different datalinkData objects
}

///////////////////////////////////////////////////////////////////////////////
/// @Runs all model tips and returns a vector of their outputs (in tip order)
///////////////////////////////////////////////////////////////////////////////
std::vector<CoachingTipResult_t> CoachingAppSpecificExample::updateModelTips()
{
    std::vector<CoachingTipResult_t> tipResults;
    // Increment through tips
    for (const auto& tip : coachingSummaryData.coachingTipOutputList)
    {
        // Run model
        octip_tip_select = tip.tipNumber;
        dummyTipUpdate();

        // Store result
        CoachingTipResult_t tipResult{tip};
        tipResult.status = octip_mach00_out.status;
        tipResult.trigger = octip_mach00_out.trigger;
        tipResult.severity = octip_mach00_out.severity;
        for (size_t iStat = 0; iStat < static_cast<size_t>(octip_mach00_out.stat_data_sz); iStat++)
        {
            tipResult.stat.push_back(octip_mach00_out.stat_data[iStat]);
        }
        tipResults.push_back(tipResult);
        AIS_LOG_INFO("tipNumber: %d trigger: %d severity: %f", tipResult.tipOutput.tipNumber, tipResult.trigger, tipResult.severity);
    }
    return tipResults;
}

///////////////////////////////////////////////////////////////////////////////
/// @Read the inputs and determine if Machine is in a Safe mode to show Videos
///////////////////////////////////////////////////////////////////////////////
bool CoachingAppSpecificExample::isMachineInSafeState()
{
    // This is just test code to toggle the return value
    static uint8_t counter = 0;

    if (counter++ > 128)
    {
        return true;
    }
    else
    {
       return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @Read the inputs and determine if Machine is in a Safe mode to show Videos
///////////////////////////////////////////////////////////////////////////////
bool CoachingAppSpecificExample::isDiagnosticActiveFlag()
{
    // This is just test code to toggle the return value
    static uint8_t counter = 0;

    if (counter++ > 128)
    {
        return true;
    }
    else
    {
       return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @Returns if the requested cycleName is running
///////////////////////////////////////////////////////////////////////////////
bool CoachingAppSpecificExample::isCycleRunning(const std::string& cycleName)
{
    return true;    // maybe simulate where Cycle toogles on and off
}

///////////////////////////////////////////////////////////////////////////////
/// @Returns if the requested cycleName is ended
///////////////////////////////////////////////////////////////////////////////
bool CoachingAppSpecificExample::isCycleEnded(const std::string& cycleName)
{
    static uint32_t count1 = 0;
    static uint32_t count2 = 0;

    // As an example, cycle1 ends every 30 and cycle2 every 45 executive() loops
    if (cycleName.compare(Cycle1Name) == 0 && ++count1 >= 30)
    {
        count1 = 0;
        return true;
    }
    else if (cycleName.compare(Cycle2Name) == 0 && ++count2 >= 45)
    {
        count2 = 0;
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////
/// @Read the inputs and determine if Coaching is enabled
///////////////////////////////////////////////////////////////////////////////
CoachingStatus CoachingAppSpecificExample::getCoachingEnabledStatus()
{
    // This is just test code to toggle the return value
    static uint8_t counter = 0;

    if (counter++ > 128)
    {
        return CoachingStatus::ENABLED;
    }
    else
    {
        return CoachingStatus::DISABLED;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @Read the inputs and determine if Coaching is installed
///////////////////////////////////////////////////////////////////////////////
CoachingStatus CoachingAppSpecificExample::getCoachingInstalledStatus()
{
    // This is just test code to toggle the return value
    static uint8_t counter = 0;

    if (counter++ > 128)
    {
        return CoachingStatus::ENABLED;
    }
    else
    {
        return CoachingStatus::DISABLED;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @Cleanup
///////////////////////////////////////////////////////////////////////////////
void CoachingAppSpecificExample::cleanup()
{
    // If necessary, write to nvm 
}
