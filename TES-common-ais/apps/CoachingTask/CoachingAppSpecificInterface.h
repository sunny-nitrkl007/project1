#ifndef _COACHINGAPPSPECIFICINTERFACE_H_
#define _COACHINGAPPSPECIFICINTERFACE_H_

#include <vector>
#include <ais/task/Task.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/CoachingSummaryData/InterfaceTypes.h>
#include <interfaces/Coaching3x3Data/InterfaceTypes.h>

enum class CoachingStatus
{
    UNKNOWN,
    ENABLED,
    DISABLED,
    FAULTED
};

const uint32_t TRUCK_SEG_PID = 0xF191;      // two PIDs used for Segment ID, $F191 by Trucks, $D0272F by other Machines
const uint8_t  SEG_ENUM_OFFSET = 0x80;      // The $F191 values are adjusted from $D0272F so only one combined list is used.

class CoachingAppSpecific {
public:
    // Forbid the use of the default constructor
    CoachingAppSpecific() = delete;
    virtual ~CoachingAppSpecific() {}

    // Get a pointer to the implementation specific object.  This function is defined in the CPM project
    static CoachingAppSpecific* getAppSpecific( task::Task& parent,
                                                CoachingSummaryData& coachingSummaryData,
                                                Coaching3x3DataList& coaching3x3DataList );

    // Call once at key on to set up scs channels, initialize tip model, 
    // read from config, read from nvm if needed
    virtual bool initialize() = 0;

    // Build real time tip data
    virtual bool reset() = 0;

    // Write to nvm if needed
    virtual void cleanup() = 0;

    // Set model inputs from DataLinkData.  function could be called multiple times in one cycle with different DataLinkData objects
    virtual void getAndSetInputs(DataLinkData& dataLinkData) = 0;

    // Runs all model tips and returns a vector of their outputs (in tip order)
    virtual std::vector<CoachingTipResult_t> updateModelTips() = 0;

    // Returns true if the machine is in a safe state to use the UI
    virtual bool isMachineInSafeState() { return machineInSafeState; };

    // Returns true if the machine is in a datalink diagnostic state to use the UI
    virtual bool isDiagnosticActiveFlag() { return diagnosticActiveFlag; };

    // Returns true if the provided cycleName is currently running
    virtual bool isCycleRunning(const std::string& cycleName) = 0;

    // Returns true if the provided cycleName has just ended
    virtual bool isCycleEnded(const std::string& cycleName) = 0;

    // Sets the current Segment
    void setCurrentSegment(uint32_t pid, uint8_t value)
    { 
        if (TRUCK_SEG_PID == pid)
        {
            coachingSegmentStatusNew = (value + SEG_ENUM_OFFSET);
        }
        else
        {
            coachingSegmentStatusNew = value;
        }
        AIS_LOG_INFO("setCurrentSegment() PID:%x  Value:%x",pid, value);
    }

    // Returns true if there is a new currentSegment
    bool getCurrentSegment(uint8_t &currentSegment)
    {
        currentSegment = coachingSegmentStatusNew;
        bool temp = !(coachingSegmentStatusNew == coachingSegmentStatus);
        coachingSegmentStatus = coachingSegmentStatusNew; 
        return temp;
    }

    // Returns status if coaching is enabled
    virtual CoachingStatus getCoachingEnabledStatus() { return coachingEnabledStatus; };
 
    // Returns status if coaching is installed
    virtual CoachingStatus getCoachingInstalledStatus() { return coachingInstalledStatus; };

    // Returns status if coaching is installed
    virtual CoachingStatus getCoachingTempInstalledStatus() { return coachingTempInstalledStatus; };

    // Returns status if coaching is installed
    virtual uint16_t getCoachingTempTime() { return coachingTempTime; };

    // Returns false if the coaching data if the static tip information doesn't match exactly
    bool isLoadedDataValid()
    {
        if (coachingSummaryData.coachingTipOutputList.size() == coachingTipInfo.size())
        {
            for (size_t i = 0; i < coachingTipInfo.size(); ++i)
            {
                if (coachingSummaryData.coachingTipOutputList[i] != coachingTipInfo[i])
                {
                    AIS_LOG_ERROR("Tip Number %u does not match", coachingTipInfo[i].tipNumber);
                    auto& exp = coachingTipInfo[i];
                    auto& act = coachingSummaryData.coachingTipOutputList[i];
                    std::string tipTagsExp, tipTagsAct;
                    for (auto tipTag : exp.tipTags)
                    {
                        tipTagsExp += " " + tipTag;
                    }
                    for (auto tipTag : act.tipTags)
                    {
                        tipTagsAct += " " + tipTag;
                    }
                    AIS_LOG_ALERT("exp: %u, %s,[%s], %s, %s, %f, %f, %f, %f, %f, %s, %s, %f, %f, %f, %d", exp.tipNumber, exp.tipName.c_str(), tipTagsExp.c_str(), exp.tipProductGroup.c_str(), exp.tipVersion.c_str(), exp.expectedOccurenceRatePerHour, exp.Threshold_0,  exp.Threshold_25, exp.Threshold_50,  exp.Threshold_75, exp.videoFileName.c_str(), exp.imageFileName.c_str(), exp.algorithmWmaInc, exp.algorithmWmaDec, exp.algorithmWmaLambda, exp.algorithmWmaMaxCount);
                    AIS_LOG_ALERT("act: %u, %s,[%s], %s, %s, %f, %f, %f, %f, %f, %s, %s, %f, %f, %f, %d", act.tipNumber, act.tipName.c_str(), tipTagsAct.c_str(), act.tipProductGroup.c_str(), act.tipVersion.c_str(), act.expectedOccurenceRatePerHour, act.Threshold_0,  act.Threshold_25, act.Threshold_50,  act.Threshold_75, act.videoFileName.c_str(), act.imageFileName.c_str(), act.algorithmWmaInc, act.algorithmWmaDec, act.algorithmWmaLambda, act.algorithmWmaMaxCount);

                    return false;
                }
            }
            return true;
        }
        AIS_LOG_ERROR("Number of Tips do not match (exp: %u act: %u)", coachingTipInfo.size(), coachingSummaryData.coachingTipOutputList.size());
        return false;
    }

protected:
    CoachingAppSpecific( task::Task& parent, CoachingSummaryData& coachingSummaryData, Coaching3x3DataList& coaching3x3DataList ) :
        parent(parent),
        coachingSummaryData(coachingSummaryData),
        coaching3x3DataList(coaching3x3DataList),
        machineInSafeState{false},
        diagnosticActiveFlag{false},
        coachingEnabledStatus{CoachingStatus::UNKNOWN},
        coachingInstalledStatus{CoachingStatus::UNKNOWN},
        coachingTempInstalledStatus{CoachingStatus::UNKNOWN},
        coachingTempTime{0},                // default to 0 to 0 minutes
        coachingSegmentStatusNew{0xFF},     // default to 0xFF to indicate not set
        coachingSegmentStatus{0xFF}        	// default to 0xFF to indicate not set
        {}

    task::Task& parent;
    CoachingSummaryData& coachingSummaryData;
    Coaching3x3DataList& coaching3x3DataList;
    std::vector<CoachingTipOutputBase_t> coachingTipInfo;
    bool machineInSafeState;
    bool diagnosticActiveFlag;
    CoachingStatus coachingEnabledStatus;
    CoachingStatus coachingInstalledStatus;
    CoachingStatus coachingTempInstalledStatus;
    uint16_t coachingTempTime;
    uint8_t coachingSegmentStatusNew;
    uint8_t coachingSegmentStatus;
};

#endif
