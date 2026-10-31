///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2020CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    CoachingTipHistoryTest.cpp
//
// @brief   CoachingTipHistoryTest
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- #Includes --
///////////////////////////////////////////////////////////////////////////////

#include <interfaces/CoachingSummaryData/CoachingSummaryData.h>
#include <interfaces/CoachingTipHistory/CoachingTipHistory.h>

#include "CoachingTipHistoryTest.h"

///////////////////////////////////////////////////////////////////////////////
// -- #Define, Structs, Typedef', Enums --
///////////////////////////////////////////////////////////////////////////////

using namespace task;

static const std::string Cycle1Name = "DIG";
static const std::string Cycle2Name = "LOAD-N-CARRY";

///////////////////////////////////////////////////////////////////////////////
// -- Symbols --
///////////////////////////////////////////////////////////////////////////////

VarLengthDataLinkParam::VarLengthParamBlock_t gpsParamValue;
static GPSDataLinkParam gpsParam{gpsParamValue};
static CoachingTipHistory tipHistory;
static std::vector<CoachingTipOutputBase_t> coachingTipInfo;
static std::vector<CoachingTipResult_t> tipResults;
static CoachingSummaryData coachingSummaryData;

///////////////////////////////////////////////////////////////////////////////
// -- Start of code for this file --
///////////////////////////////////////////////////////////////////////////////

AbstractTaskCore* task::getTaskImplementation(void)
{
    static CoachingTipHistoryTest thisTask("CoachingTipHistoryTest");
    return dynamic_cast<Task *>(&thisTask);
}


CoachingTipHistoryTest::CoachingTipHistoryTest(const std::string& taskName ):
    Task{taskName},
    m_pCoachingTipHistoryOutput{nullptr}
{
}


CoachingTipHistoryTest::~CoachingTipHistoryTest()
{
}


bool CoachingTipHistoryTest::initialize()
{   
    if (!task::InterfaceDb::bind("CoachingTipHistoryOutput", m_pCoachingTipHistoryOutput))
    {
        return false;
    }
    // NOTE: tipNumber and tipPriority must be unique
                                                     // tipNumber tipName  tipPriority          tipProductGroup   tipCategory               tipTag                               tipVersion  expectedOccurenceRatePerHour   0%-Thresh  25%-Thresh  50%-Thresh   75%-Thresh   videoFileName
    coachingTipInfo.push_back(CoachingTipOutputBase_t(   1,    "TIP 1",  coachingTipInfo.size() + 1,  "AT",       SID_OPERATING_EFFICIENCY, TipTags_t{Cycle1Name, Cycle2Name},  "ver0",       1.0f,                        0.01f,           0.1f,     0.2f,        0.4f,    "Video_1.webm", "Image_1.png", 0.1f, 0.2f, 0.35f, 1));
    coachingTipInfo.push_back(CoachingTipOutputBase_t(   2,    "TIP 2",  coachingTipInfo.size() + 1,  "AT",       SID_OPERATING_EFFICIENCY, TipTags_t{Cycle1Name},              "ver0",       2.0f,                        0.01f,           0.1f,     0.2f,        0.4f,    "Video_2.webm", "", 0.1f, 0.2f, 0.35f, 1));
    coachingTipInfo.push_back(CoachingTipOutputBase_t(   3,    "TIP 3",  coachingTipInfo.size() + 1,  "AT",       SID_MACHINE_HEALTH,       TipTags_t{Cycle1Name, Cycle2Name},  "ver0",       3.0f,                        0.01f,           0.1f,     0.2f,        0.4f,    "Video_3.webm", "", 0.1f, 0.2f, 0.35f, 1));
    coachingTipInfo.push_back(CoachingTipOutputBase_t(   4,    "TIP 4",  coachingTipInfo.size() + 1,  "AT",       SID_MACHINE_HEALTH,       TipTags_t{Cycle1Name},              "ver0",       4.0f,                        0.01f,           0.1f,     0.2f,        0.4f,    "Video_4.webm", "", 0.1f, 0.2f, 0.35f, 1));
    coachingTipInfo.push_back(CoachingTipOutputBase_t(   5,    "TIP 5",  coachingTipInfo.size() + 1,  "AT",       SID_HAZARDOUS,            TipTags_t{Cycle1Name, Cycle2Name},  "ver0",       5.0f,                        0.01f,           0.1f,     0.2f,        0.4f,    "Video_5.webm", "", 0.1f, 0.2f, 0.35f, 1));

    // Copy coachingTipInfo into the coachingSummaryData
    for (const auto& tipInfo : coachingTipInfo)
    {
        coachingSummaryData.coachingTipOutputList.emplace_back(tipInfo);
    }

    // Create Tip Results and initialize to not triggered
    for (const auto& tip : coachingSummaryData.coachingTipOutputList)
    {
        tipResults.emplace_back(tip);
        tipResults.back().trigger = 0;
        tipResults.back().severity = 0;
    }

    tipHistory.initialize(getTaskConfig());

    return true;
}


bool CoachingTipHistoryTest::executive()
{
    static uint32_t count{0};
    switch (count++)
    {
    case 0:
    {
        tipHistory.setActiveOperatorId("Edward");
        gpsParam.SetGpsLatitude(-5.5, false);
        gpsParam.SetGpsLongitude(100.50, false);
        gpsParam.SetGpsStatus(GPSDataLinkParam::GpsPositionStatusType::POSITION_VALID);
        tipHistory.setShmSec(12345);
        coachingSummaryData.setTipIncrement(1);
        break;
    }
    case 1:
    {
        coachingSummaryData.setTipIncrement(1);
        break;
    }
    case 2:
    {
        coachingSummaryData.setTipIncrement(2);
        break;
    }
    case 3:
    {
        tipHistory.setActiveOperatorId("Jonathan");
        gpsParam.SetGpsLatitude(40.0, false);
        gpsParam.SetGpsLongitude(10.0, false);
        coachingSummaryData.setTipIncrement(3);
        break;
    }
    case 4:
    {
        coachingSummaryData.setTipIncrement(2);
        break;
    }
    case 5:
    {
        coachingSummaryData.setTipIncrement(2);
        break;
    }
    case 6:
    {
        coachingSummaryData.setTipIncrement(2);
        break;
    }
    case 7:
    {
        coachingSummaryData.setTipIncrement(2);
        break;
    }
    default:
        count--;
    }

    coachingSummaryData.updateTips(tipResults);
    tipHistory.setGpsStatus(gpsParam);
    tipHistory.updateTipResults(tipResults);
    bdt::BlockData_t blockData;
    BdtManagerInterface::SubFileCount_t subFileCount;
    tipHistory.appendSubFile(blockData, subFileCount);
    bdt::printBlockData(blockData);
    m_pCoachingTipHistoryOutput->publish(tipHistory);

    // Reset tipResult triggers
    for (auto& tipResult : tipResults)
    {
        tipResult.trigger = 0;
        tipResult.severity = 0;
    }
    return true;
}


void CoachingTipHistoryTest::cleanup( )
{
}
