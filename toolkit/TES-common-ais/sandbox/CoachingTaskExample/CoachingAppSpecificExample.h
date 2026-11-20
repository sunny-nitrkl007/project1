#ifndef _COACHINGAPPSPECIFICEXAMPLE_H_
#define _COACHINGAPPSPECIFICEXAMPLE_H_

#include <CoachingAppSpecificInterface.h>
#include "octip_mach00_out.h"

// Application specific, must include initialize() and serialize()
struct DigCycleData_t {

    uint32_t segmentRecId;
    uint32_t previousDigState;
    uint64_t previousTime;
    float previousVehicleSpeed;
    float distance_m;

    void initialize()
    {
        segmentRecId = 0;
        previousDigState = 0;
        previousTime = 0;
        previousVehicleSpeed = 0.0;
        distance_m = 0.0;
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned int version) 
    {
        ar & segmentRecId;
        ar & previousDigState;
        ar & previousTime;
        ar & previousVehicleSpeed;
        ar & distance_m;
    }
};

class CoachingAppSpecificExample : public CoachingAppSpecific {
public:
    // Default constructor is disallowed so that parent configuration can be read
    CoachingAppSpecificExample() = delete;
    CoachingAppSpecificExample( task::Task& parent,
                                CoachingSummaryData& coachingSummaryData,
                                Coaching3x3DataList& coaching3x3DataList );

    // Call once at key on to set up scs channels, initialize tip model, 
    // read from config, read from nvm if needed
    bool initialize() override;

    // initialize/clear real time tip data
    bool reset() override;

    // Write to nvm if needed
    void cleanup() override;
    
    // Set model inputs from datalinkData.  function could be called multiple times in one cycle with different datalinkData objects
    void getAndSetInputs(DataLinkData& datalinkData) override;

    // Runs all model tips and returns a vector of their outputs (in tip order) 
    std::vector<CoachingTipResult_t> updateModelTips() override;

    // Returns true if the provided cycleName is currently running
    bool isMachineInSafeState() override;

    // Returns true if the provided cycleName is currently running
    bool isDiagnosticActiveFlag() override;

    // Returns true if the provided cycleName is currently running
    bool isCycleRunning(const std::string& cycleName) override;

    // Returns true if the provided cycleName has just ended
    bool isCycleEnded(const std::string& cycleName) override;

    // Returns status if coaching is enabled
    CoachingStatus getCoachingEnabledStatus() override;

    // Returns status if coaching is installed
    CoachingStatus getCoachingInstalledStatus() override;

private:
    // Implementation specific members
    static constexpr size_t TipCount = 5;

    const std::string Cycle1Name = "DIG";
    const std::string Cycle2Name = "LOAD-N-CARRY";

    void digCycle();
};

#endif
