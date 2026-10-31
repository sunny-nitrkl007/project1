#ifndef _COACHINGTIPOUTPUT_H_
#define _COACHINGTIPOUTPUT_H_

#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_map>

#include <boost/math/special_functions/gamma.hpp>
#include <boost/serialization/set.hpp>

#include <ais/log/AisLogger.h>

#include "interfaces/JSON/jsonable.h"

// State IDs are partially defined in catdllib_sid_def.h using SID_ prefixes
using CoachingTipCategory_t = uint16_t;

// TODO: Replace with actual values
constexpr CoachingTipCategory_t SID_HAZARDOUS = 0x0928;
constexpr CoachingTipCategory_t SID_MACHINE_HEALTH = 0x0929;
constexpr CoachingTipCategory_t SID_OPERATING_EFFICIENCY = 0x092A;

inline const char* tipCategoryToCstr(CoachingTipCategory_t e)
{
    const std::unordered_map<CoachingTipCategory_t, const char*> EnumStrings {
        { SID_HAZARDOUS,            "Severe / Unsafe" },
        { SID_MACHINE_HEALTH,       "Machine Health" },
        { SID_OPERATING_EFFICIENCY, "Operating Efficiency" }
    };
    auto   it  = EnumStrings.find(e);
    return it == EnumStrings.end() ? "--" : it->second;
}

using TipTags_t = std::set<std::string>;

// Static tip specific information
struct CoachingTipOutputBase_t
{
    uint32_t tipNumber;
    std::string tipName;
    uint32_t tipPriority;
    std::string tipProductGroup;
    CoachingTipCategory_t tipCategory;
    TipTags_t tipTags;
    std::string tipVersion;
    float expectedOccurenceRatePerHour;
    float Threshold_0;
    float Threshold_25;
    float Threshold_50;
    float Threshold_75;
    std::string videoFileName;
    std::string imageFileName;
    float algorithmWmaInc;
    float algorithmWmaDec;
    float algorithmWmaLambda;
    float algorithmWmaMaxCount;

    CoachingTipOutputBase_t(uint32_t tipNumber,
                            const std::string& tipName,
                            uint32_t tipPriority,
                            const std::string& tipProductGroup,
                            CoachingTipCategory_t tipCategory,
                            const TipTags_t& tipTags,
                            const std::string& tipVersion,
                            float expectedOccurenceRatePerHour,
                            float Threshold_0,
                            float Threshold_25,
                            float Threshold_50,
                            float Threshold_75,
                            const std::string& videoFileName,
                            const std::string& imageFileName,
                            float algorithmWmaInc,
                            float algorithmWmaDec,
                            float algorithmWmaLambda,
                            float algorithmWmaMaxCount) :
        tipNumber{tipNumber},
        tipName{tipName},
        tipPriority{tipPriority},
        tipProductGroup{tipProductGroup},
        tipCategory{tipCategory},
        tipTags{tipTags},
        tipVersion{tipVersion},
        expectedOccurenceRatePerHour{expectedOccurenceRatePerHour},
        Threshold_0{Threshold_0},
        Threshold_25{Threshold_25},
        Threshold_50{Threshold_50},
        Threshold_75{Threshold_75},
        videoFileName{videoFileName},
        imageFileName{imageFileName},
        algorithmWmaInc{algorithmWmaInc},
        algorithmWmaDec{algorithmWmaDec},
        algorithmWmaLambda{algorithmWmaLambda},
        algorithmWmaMaxCount{algorithmWmaMaxCount}
        {}

    CoachingTipOutputBase_t(const CoachingTipOutputBase_t& rhs) :
        tipNumber{rhs.tipNumber},
        tipName{rhs.tipName},
        tipPriority{rhs.tipPriority},
        tipProductGroup{rhs.tipProductGroup},
        tipCategory{rhs.tipCategory},
        tipTags{rhs.tipTags},
        tipVersion{rhs.tipVersion},
        expectedOccurenceRatePerHour{rhs.expectedOccurenceRatePerHour},
        Threshold_0{rhs.Threshold_0},
        Threshold_25{rhs.Threshold_25},
        Threshold_50{rhs.Threshold_50},
        Threshold_75{rhs.Threshold_75},
        videoFileName{rhs.videoFileName},
        imageFileName{rhs.imageFileName},
        algorithmWmaInc{rhs.algorithmWmaInc},
        algorithmWmaDec{rhs.algorithmWmaDec},
        algorithmWmaLambda{rhs.algorithmWmaLambda},
        algorithmWmaMaxCount{rhs.algorithmWmaMaxCount}
        {}

    // Needed for serialization
    CoachingTipOutputBase_t() = default;
};

// Forward declaration
struct CoachingTipOutput_t;

// Tip result data from model
struct CoachingTipResult_t
{
    static constexpr size_t MAX_STATS = 5;                  // Currently used only for xcp

    enum class opTipEnableStateEnum
    {
        NO_CHANGE,
        OPERATOR_DISABLED,
        OPERATOR_ENABLED,
        AUTO_ENABLED
    };

    enum class sysTipEnableStateEnum
    {
        NO_CHANGE,
        SYSTEM_DISABLED,
        SYSTEM_ENABLED,
        SYSTEM_PID_DISABLED,
        SYSTEM_PID_ENABLED,
        SYSTEM_OTA_DISABLED,
        SYSTEM_OTA_ENABLED
    };

    explicit CoachingTipResult_t(const CoachingTipOutput_t& tipOutput) :
        tipOutput(tipOutput),
        status{0},
        trigger{0},
        severity{0.0},
        poissonValue{0.0},
        opTipEnableStateStatus{opTipEnableStateEnum::NO_CHANGE},
        sysTipEnableStateStatus{sysTipEnableStateEnum::NO_CHANGE}

    {}

    const CoachingTipOutput_t& tipOutput;
    uint16_t status;
    uint32_t trigger;
    float severity;
    float poissonValue;
    opTipEnableStateEnum opTipEnableStateStatus;
    std::vector<float> stat;
    sysTipEnableStateEnum sysTipEnableStateStatus;
};


inline bool operator==(const CoachingTipOutputBase_t& lhs, const CoachingTipOutputBase_t& rhs)
{
    constexpr float F_EPSILON = 0.000001;

    return lhs.tipNumber == rhs.tipNumber && 
           lhs.tipName == rhs.tipName &&
           lhs.tipPriority == rhs.tipPriority &&
           lhs.tipProductGroup == rhs.tipProductGroup &&
           lhs.tipCategory == rhs.tipCategory &&
           lhs.tipTags == rhs.tipTags &&
           lhs.tipVersion == rhs.tipVersion &&
           fabs(lhs.expectedOccurenceRatePerHour - rhs.expectedOccurenceRatePerHour) < F_EPSILON &&
           fabs(lhs.Threshold_0 - rhs.Threshold_0) < F_EPSILON &&
           fabs(lhs.Threshold_25 - rhs.Threshold_25) < F_EPSILON &&
           fabs(lhs.Threshold_50 - rhs.Threshold_50) < F_EPSILON &&
           fabs(lhs.Threshold_75 - rhs.Threshold_75) < F_EPSILON &&
           lhs.videoFileName == rhs.videoFileName &&
           lhs.imageFileName == rhs.imageFileName &&
           lhs.algorithmWmaInc == rhs.algorithmWmaInc &&
           lhs.algorithmWmaDec == rhs.algorithmWmaDec &&
           lhs.algorithmWmaLambda == rhs.algorithmWmaLambda &&
           lhs.algorithmWmaMaxCount == rhs.algorithmWmaMaxCount;
}

inline bool operator!=(const CoachingTipOutputBase_t& lhs, const CoachingTipOutputBase_t& rhs)
{
    return !(lhs == rhs);
}

struct CoachingTipOutput_t : public CoachingTipOutputBase_t, public csvable
{
    static constexpr uint16_t TipStatusInit = 0xFFFF;

    enum class HaloPercent : uint8_t
    {
        PERCENT_0   = 0,
        PERCENT_25  = 25,
        PERCENT_50  = 50,
        PERCENT_75  = 75,
        PERCENT_100 = 100
    };

    static std::string toString(HaloPercent e)
    {
        const std::map<HaloPercent, const char*> EnumStrings {
            { HaloPercent::PERCENT_0,     "0%" },
            { HaloPercent::PERCENT_25,   "25%" },
            { HaloPercent::PERCENT_50,   "50%" },
            { HaloPercent::PERCENT_75,   "75%" },
            { HaloPercent::PERCENT_100, "100%" }
        };
        auto   it  = EnumStrings.find(e);
        return it == EnumStrings.end() ? "Out of range" : it->second;
    }

    static constexpr float MinElapsedTimeHours = 2.0f;

    int64_t tipLastOccurenceTime;
    uint16_t tipStatus;
    int16_t tipTrigger;
    bool opTipEnableState;
    bool opTipEnableStatePrev;
    int64_t opTipEnableStateTimeSecondsSinceEpoch;
    bool sysTipEnableState;
    float lastSeverity;
    float maxSeverity;
    float minSeverity;
    float avgSeverity;
    float poissonValue;
    HaloPercent poissonValuePercent;
    float poissonValueSeverityWeighted;
    HaloPercent poissonValueSeverityWeightedPercent;
    std::vector<float> tipStat;
    uint32_t tipTriggerCount;
    uint32_t tipTriggerCountLifetime;
    uint32_t tipVideoViewCount;
    uint32_t tipVideoViewCountLifetime;
    bool badgeFlag;
    uint32_t badgeCount;
    uint32_t tipTextViewCount;
    uint32_t tipTextViewCountLifetime;
    bool tipTriggerFlagOnlyForTestingByUI;      // This Flag is used only by Testing UI-html to trigger tips so they can also be added Breadcrumb Log
    float algorithmWmaCurrentCount;          // Count of Triggers within the current Period
    float algorithmWmaRateLimitedTriggers;     // Cumulated Triggers over multiple Windows
    float algorithmWmaRateLimitedTriggersperhour;                // RawIncDec
    float algorithmWmaCurrentValue;             // current WMA value

    // Needed for serialization
    CoachingTipOutput_t() = default;
    
    // Create initialized tip
    explicit CoachingTipOutput_t(const CoachingTipOutputBase_t& base) :
        CoachingTipOutputBase_t{base},
        tipLastOccurenceTime{0},
        tipStatus{TipStatusInit},
        tipTrigger{0},
        opTipEnableState{true},
        opTipEnableStatePrev{true},
        opTipEnableStateTimeSecondsSinceEpoch{0},
        sysTipEnableState{true},
        lastSeverity{0},
        maxSeverity{0},
        minSeverity{0},
        avgSeverity{0},
        poissonValue{0},
        poissonValuePercent{HaloPercent::PERCENT_100},
        poissonValueSeverityWeighted{0},
        poissonValueSeverityWeightedPercent{HaloPercent::PERCENT_100},
        tipTriggerCount{0},
        tipTriggerCountLifetime{0},
        tipVideoViewCount{0},
        tipVideoViewCountLifetime{0},
        badgeFlag{false},
        badgeCount{0},
        tipTextViewCount{0},
        tipTextViewCountLifetime{0},
        tipTriggerFlagOnlyForTestingByUI{false},
        algorithmWmaCurrentCount{0},                // Count of Triggers within the current Period
        algorithmWmaRateLimitedTriggers{0},
        algorithmWmaRateLimitedTriggersperhour{0},
        algorithmWmaCurrentValue{0}                 // current WMA value
        {}

    ///////////////////////////////////////////////////////////////////////////////
    /// @Resets tip data while retaining reset/disabled flags
    ///////////////////////////////////////////////////////////////////////////////
    void resetStats()
    {
        tipLastOccurenceTime = 0;
        tipStatus = TipStatusInit;
        tipTrigger = 0;
        lastSeverity = 0;
        maxSeverity = 0;
        minSeverity = 0;
        avgSeverity = 0;
        poissonValue = 0;
        poissonValuePercent = HaloPercent::PERCENT_100;
        poissonValueSeverityWeighted = 0;
        poissonValueSeverityWeightedPercent = HaloPercent::PERCENT_100;
        tipTriggerCount = 0;
        tipVideoViewCount = 0;
        tipTextViewCount = 0;
        badgeFlag = false;
        tipTriggerFlagOnlyForTestingByUI = false;
        algorithmWmaCurrentCount = 0;                // Count of Triggers within the current Period
        algorithmWmaRateLimitedTriggers = 0;
        algorithmWmaRateLimitedTriggersperhour = 0;
        algorithmWmaCurrentValue = 0;                // current WMA value
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @Return current Poisson Percent
    ///////////////////////////////////////////////////////////////////////////////
    HaloPercent getPoissonValuePercent() const { return poissonValuePercent; }

    ///////////////////////////////////////////////////////////////////////////////
    /// @Calculates Summary TIP,
    /// @Return bool for displayRequired...  PID $D1199D Operator Coaching Tip Summary Display Requirement Statu
    ///////////////////////////////////////////////////////////////////////////////
    bool updateTip(CoachingTipResult_t& tipResult, float elapsedTimeHours, int64_t currentTimeSecondsSinceEpoch, int64_t tipAutoEnableTimeSeconds, bool algorithmWmaFlag, float algorithmWmaWindowElsapsedTimeHrs, bool algorithmIsPoisson)
    {
        HaloPercent poissonValuePercentPrev;                // used to help with BADGE behavior
        bool displayRequired = false;               // return value, default to false

        poissonValuePercentPrev = poissonValuePercent;       // needed for Badge behavior

        if(tipTriggerFlagOnlyForTestingByUI)	    // over-ride the tipResult with severity 0.5, this allows it to be added to breadcrumb log
        {
            tipResult.trigger = 1;
            tipResult.severity = 0.5;
            tipTriggerFlagOnlyForTestingByUI = false;
        }

        if(tipResult.trigger > 0)
        {
            if(tipResult.severity > 0.0f)
            {
                AIS_LOG_DEBUG("Output: %u %i %f \n", tipNumber, tipResult.trigger, tipResult.severity);
            }

            uint32_t prev_triggerCount = tipTriggerCount;
            tipTrigger = 1;
            tipTriggerCount++;
            tipTriggerCountLifetime++;
            lastSeverity = static_cast<float>(tipResult.severity);
            maxSeverity = (maxSeverity > tipResult.severity) ? maxSeverity : tipResult.severity;
            minSeverity = (maxSeverity < tipResult.severity) ? maxSeverity : tipResult.severity;
            avgSeverity = ((avgSeverity * prev_triggerCount) + tipResult.severity) / tipTriggerCount;
            tipLastOccurenceTime = currentTimeSecondsSinceEpoch;

            algorithmWmaCurrentCount += 1.0f;
        }
        else
        {
           tipTrigger = 0;
        }

        // Check for opTipEnableState on/off
        if((false == opTipEnableState) && ( (currentTimeSecondsSinceEpoch - opTipEnableStateTimeSecondsSinceEpoch) >= tipAutoEnableTimeSeconds))
        {
            opTipEnableState = true;
            tipResult.opTipEnableStateStatus = CoachingTipResult_t::opTipEnableStateEnum::AUTO_ENABLED;
        }
        else if (!opTipEnableState && opTipEnableStatePrev)
        {
            tipResult.opTipEnableStateStatus = CoachingTipResult_t::opTipEnableStateEnum::OPERATOR_DISABLED;
        }
        else if (opTipEnableState && !opTipEnableStatePrev)
        {
            tipResult.opTipEnableStateStatus = CoachingTipResult_t::opTipEnableStateEnum::OPERATOR_ENABLED;
        }
        else
        {
            tipResult.opTipEnableStateStatus = CoachingTipResult_t::opTipEnableStateEnum::NO_CHANGE;
        }
        opTipEnableStatePrev = opTipEnableState;

        if(elapsedTimeHours < MinElapsedTimeHours)
        {
            elapsedTimeHours = MinElapsedTimeHours;
        }

        if (algorithmWmaFlag)  // execute WMA algorithm
        {
            float actualCount = algorithmWmaCurrentCount;
            if (algorithmWmaCurrentCount > algorithmWmaMaxCount) {algorithmWmaCurrentCount = algorithmWmaMaxCount;} // don't go past MAX
            float adjust = (algorithmWmaCurrentCount > algorithmWmaRateLimitedTriggers) ? algorithmWmaInc : algorithmWmaDec;
            algorithmWmaRateLimitedTriggers += adjust * algorithmWmaWindowElsapsedTimeHrs;
            if (algorithmWmaRateLimitedTriggers < 0) {algorithmWmaRateLimitedTriggers = 0.0f;} // can't go negative
            if (algorithmWmaRateLimitedTriggers > algorithmWmaMaxCount) {algorithmWmaRateLimitedTriggers = algorithmWmaMaxCount;} // can't go past MAX
            algorithmWmaRateLimitedTriggersperhour = algorithmWmaRateLimitedTriggers / algorithmWmaWindowElsapsedTimeHrs;  // scale to per-hour.... 3600 seconds per hour 
            algorithmWmaCurrentValue = (( (1-algorithmWmaLambda) * algorithmWmaCurrentValue) + (algorithmWmaLambda * algorithmWmaRateLimitedTriggersperhour));
            AIS_LOG_INFO("Tip:%d Cnt:%f-%f Adj:%f Trg:%f Hrs:%f Wma:%f", tipNumber, actualCount, algorithmWmaCurrentCount, adjust, algorithmWmaRateLimitedTriggers, algorithmWmaRateLimitedTriggersperhour, algorithmWmaCurrentValue);
            algorithmWmaCurrentCount = 0.0f;   // reset since window ended

            // check the BADGE behavior
            if (!algorithmIsPoisson)    // it's WMA
            {
                poissonValuePercent = CalculatePercentWma(algorithmWmaCurrentValue);
            }
        }

        // Calculate poisson value and percent
        poissonValue = CalculatePoissonValue(tipTriggerCount, elapsedTimeHours, expectedOccurenceRatePerHour);
        // this is the poisson using AvgTrigger/Hour
        poissonValueSeverityWeighted = CalculatePoissonValue((avgSeverity * elapsedTimeHours), elapsedTimeHours, expectedOccurenceRatePerHour);
        // check the BADGE behavior
        if (algorithmIsPoisson)    // it's POISSON
        {
            poissonValuePercent = CalculatePercentPoisson(poissonValue);
        }

        // check BADGE behavior
        if (poissonValuePercentPrev != poissonValuePercent)
        {
            // badgeFlag == FALSE AND Prev > Current,  we are DESCREASING
            if ((!badgeFlag) && (poissonValuePercentPrev > poissonValuePercent))
            {
                displayRequired = true;     // set the RETURN value
                badgeFlag = true;	        // set Flag
                badgeCount++;	            // increment Counter
            }

            // badgeFlag == TRUE AND Current > Prev,  we are INCREASING
            if ((badgeFlag) && (poissonValuePercent > poissonValuePercentPrev))
            {
                badgeFlag = false;	        // clear Flag
            }
        }

        // Set status
        tipStatus = tipResult.status;

        // Copy application specific statistical information
        tipStat = tipResult.stat;

        // check if Tip is disabled by Application Specific Reason
        switch (tipResult.sysTipEnableStateStatus)
        {
            case CoachingTipResult_t::sysTipEnableStateEnum::SYSTEM_DISABLED:
            case CoachingTipResult_t::sysTipEnableStateEnum::SYSTEM_PID_DISABLED:
            case CoachingTipResult_t::sysTipEnableStateEnum::SYSTEM_OTA_DISABLED:
            {
                sysTipEnableState = false;
                break;
            }
            default:
            {
                sysTipEnableState = true;
                break;
            }
        }

        AIS_LOG_DEBUG("tip:%d sysTip:%d displayRequired:%d", tipNumber, tipResult.sysTipEnableStateStatus, displayRequired);

        return displayRequired;
    }

    void toJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const std::string& videoPath) const
    {
        writer.StartObject();
        writer.Key("name"), writer.String(tipName);
        writer.Key("productGroup"), writer.String(tipProductGroup);
        writer.Key("tipCategory"), writer.Uint(tipCategory);
        writer.Key("tipCategoryName"), writer.String(tipCategoryToCstr(tipCategory));
        writer.Key("revision"), writer.String(tipVersion);
        writer.Key("number"), writer.Uint(tipNumber);
        writer.Key("priority"), writer.Uint(tipPriority);
        if (!videoFileName.empty())   	// only have "videoUrl" if configured with associated video
        {
            writer.Key("videoUrl"), writer.String(videoPath + '/' + videoFileName);
        }
        if (!imageFileName.empty())   	// only have "imageUrl" if configured with associated image
        {
            writer.Key("imageUrl"), writer.String(videoPath + '/' + imageFileName);
        }
        writer.Key("expectedOccurenceRatePerHour"), writer.Double(expectedOccurenceRatePerHour);

        writer.Key("tags");
        writer.StartArray();
        for (auto tag : tipTags)
        {
            writer.String(tag);
        }
        writer.EndArray();

        writer.Key("tipStatus"), writer.Uint(tipStatus);
        writer.Key("trigger"), writer.Int(tipTrigger);
        writer.Key("opTipEnableState"), writer.tBool(opTipEnableState);
        writer.Key("opTipEnableStateTimeSecondsSinceEpoch"), writer.Int64(opTipEnableStateTimeSecondsSinceEpoch);
        writer.Key("sysTipEnableState"), writer.tBool(sysTipEnableState);
        writer.Key("lastSeverity"), writer.Double(lastSeverity);
        writer.Key("maxSeverity"), writer.Double(maxSeverity);
        writer.Key("minSeverity"), writer.Double(minSeverity);
        writer.Key("avgSeverity"), writer.Double(avgSeverity);
        writer.Key("Threshold_0"), writer.Double(Threshold_0);
        writer.Key("Threshold_25"), writer.Double(Threshold_25);
        writer.Key("Threshold_50"), writer.Double(Threshold_50);
        writer.Key("Threshold_75"), writer.Double(Threshold_75);
        writer.Key("poissonValue"), writer.Double(poissonValue);
        writer.Key("poissonValueSeverityWeighted"), writer.Double(poissonValueSeverityWeighted);
        writer.Key("algorithmWmaInc"), writer.Double(algorithmWmaInc);
        writer.Key("algorithmWmaDec"), writer.Double(algorithmWmaDec);
        writer.Key("algorithmWmaLambda"), writer.Double(algorithmWmaLambda);
        writer.Key("algorithmWmaMaxCount"), writer.Double(algorithmWmaMaxCount);
        writer.Key("algorithmWmaCurrentCount"), writer.Double(algorithmWmaCurrentCount);
        writer.Key("algorithmWmaRateLimitedTriggers"), writer.Double(algorithmWmaRateLimitedTriggers);
        writer.Key("algorithmWmaRateLimitedTriggersperhour"), writer.Double(algorithmWmaRateLimitedTriggersperhour);
        writer.Key("algorithmWmaCurrentValue"), writer.Double(algorithmWmaCurrentValue);
        writer.Key("poissonValuePercent"), writer.String(toString(poissonValuePercent));    // needed for UI compatability 
        writer.Key("triggerCount"), writer.Uint(tipTriggerCount);
        writer.Key("triggerCountLifetime"), writer.Uint(tipTriggerCountLifetime);
        writer.Key("tipVideoViewCount"), writer.Uint(tipVideoViewCount);
        writer.Key("tipVideoViewCountLifetime"), writer.Uint(tipVideoViewCountLifetime);
        writer.Key("lastOccurenceTime"), writer.Int64(tipLastOccurenceTime);
        writer.Key("badgeFlag"), writer.tBool(badgeFlag);
        writer.Key("badgeCount"), writer.Uint(badgeCount);
        writer.Key("tipTextViewCount"), writer.Uint(tipTextViewCount);
        writer.Key("tipTextViewCountLifetime"), writer.Uint(tipTextViewCountLifetime);

        writer.Key("lastOccurencePositionData_10bytes");
        writer.StartArray();
        writer.String("N/A");
        writer.EndArray();

        writer.Key("lastOccurenceSMH"), writer.String("N/A");

        writer.Key("stats");
        writer.StartArray();
        for (auto stat : tipStat)
        {
            writer.Double(stat);
        }
        writer.EndArray();

        writer.EndObject();
    }

    template <class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
        ar & tipName;
        ar & tipProductGroup;
        ar & tipNumber;
        ar & tipVersion;
        ar & tipLastOccurenceTime;
        ar & tipStatus;
        ar & tipTrigger;
        ar & opTipEnableState;
        ar & opTipEnableStatePrev;
        ar & opTipEnableStateTimeSecondsSinceEpoch;
        ar & sysTipEnableState;
        ar & lastSeverity;
        ar & maxSeverity;
        ar & minSeverity;
        ar & avgSeverity;
        ar & poissonValue;
        ar & Threshold_0;
        ar & Threshold_25;
        ar & Threshold_50;
        ar & Threshold_75;
        ar & poissonValuePercent;
        ar & poissonValueSeverityWeighted;
        ar & poissonValueSeverityWeightedPercent;
        ar & tipStat;
        ar & tipTriggerCount;
        ar & tipVideoViewCount;
        ar & tipTags;
        ar & expectedOccurenceRatePerHour;
        ar & videoFileName;
        ar & badgeFlag;
        ar & badgeCount;
        ar & tipTextViewCount;
        ar & tipTriggerFlagOnlyForTestingByUI;

        if (version >=2)
        {
            ar & imageFileName;
        }

        if (version >= 3)
        {
            ar & tipPriority;
            ar & tipCategory;
            ar & tipTriggerCountLifetime;
            ar & tipVideoViewCountLifetime;
            ar & tipTextViewCountLifetime;
        }

        if (version >= 4)
        {
            ar & algorithmWmaInc;
            ar & algorithmWmaDec;
            ar & algorithmWmaLambda;
            ar & algorithmWmaMaxCount;
            ar & algorithmWmaCurrentCount;
            ar & algorithmWmaRateLimitedTriggers;
            ar & algorithmWmaRateLimitedTriggersperhour;
            ar & algorithmWmaCurrentValue;
        }
    }

    void toCsv(CsvOutStream& out) const override
    {
    }

private:
   ///////////////////////////////////////////////////////////////////////////////
    /// @Calculates Poisson value.
    ///////////////////////////////////////////////////////////////////////////////
    float CalculatePoissonValue(uint16_t count, float elapsedTimeHours, float expectedRatePerHour)
    {
        float expectedCount = elapsedTimeHours * expectedRatePerHour;
        float score;

        /* The statistics question we are trying to answer is:
            *  Given the expected rate, how likely is it to observe a rate
            *  as fast, or faster, than what we have observed?
            *
            * The score is the complement cumulative Poisson distribution.
            *
            * In Microsoft Excel, it looks like this:
            *  1 - POISSON.DIST(count, elapsedTimeHours * expectedRatePerHour, TRUE)
            *
            * The Cumulative Distribution Function (CDF) of the Poisson distribution
            *  is related to the gamma function.  Specifically, the normalized upper
            *  incomplete gamma function.
            *  PoissonCDF = UpperIncompleteGamma (Count + 1, ExpectedCount) / Gamma(Count + 1)
            *  1 - PoissonCDF = 1 - UpperIncompleteGamma / Gamma = LowerIncompleteGamma / Gamma
            *  NormalizedLowerIncompleteGamma = LowerIncompleteGamma / Gamma
            *  1 - PoissonCDF = NormalizedLowerIncompleteGamma(Count + 1, ExpectedCount)
            *
            */
        if (expectedCount > 0.f)
        {
            try
            {
                score = static_cast<float>(boost::math::gamma_p(count, expectedCount));
            }
            catch (const std::domain_error &de)
            {
                score = 1.f;
            }
        }
        else if (expectedCount == 0.f)
        {
            if (count > 0)
            {
                score = 0.f;
            }
            else
            {
                score = 1.f;
            }
        }
        else
        {
            score = 1.f;
        }

        return score;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @Calculates Poisson percent.
    ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
    HaloPercent CalculatePercentPoisson(float poissonVal)
    {
        if(poissonVal <= Threshold_0)
        {
            return HaloPercent::PERCENT_0;
        }
        else if((poissonVal > Threshold_0) && (poissonVal <= Threshold_25))
        {
            return HaloPercent::PERCENT_25;
        }
        else if((poissonVal > Threshold_25) && (poissonVal <= Threshold_50))
        {
            return HaloPercent::PERCENT_50;
        }
        else if((poissonVal > Threshold_50) && (poissonVal <= Threshold_75))
        {
            return HaloPercent::PERCENT_75;
        }
        else
        {
            return HaloPercent::PERCENT_100;
        }
    }

    HaloPercent CalculatePercentWma(float WmaCurrentValue)
    {
        if(WmaCurrentValue < Threshold_75)
        {
            return HaloPercent::PERCENT_100;
        }
        else if((WmaCurrentValue >= Threshold_75) && (WmaCurrentValue < Threshold_50))
        {
            return HaloPercent::PERCENT_75;
        }
        else if((WmaCurrentValue >= Threshold_50) && (WmaCurrentValue < Threshold_25))
        {
            return HaloPercent::PERCENT_50;
        }
        else if((WmaCurrentValue >= Threshold_25) && (WmaCurrentValue < Threshold_0))
        {
            return HaloPercent::PERCENT_25;
        }
        else
        {
            return HaloPercent::PERCENT_0;
        }
    }
};

BOOST_CLASS_VERSION(CoachingTipOutput_t, 4);

#endif
