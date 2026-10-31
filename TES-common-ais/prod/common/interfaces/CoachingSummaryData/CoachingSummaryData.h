#include <boost/serialization/vector.hpp>
#include <ais/serialization/Datum.h> // For Boost serialization
#include <ais/serialization/csvable.h>
#include <xcp_server/db/XCPServerDb.hpp>
#include "CoachingTipOutput.h"
#ifndef _COACHINGSUMMARYDATA_H_
#define _COACHINGSUMMARYDATA_H_


using namespace xcp_server;

class CoachingSummaryDataStorage : public csvable, public xcpable, public jsonable
{
public:
    static constexpr int SECONDS_PER_WEEK = 604800;        /// amount of seconds in One week
    static constexpr char const* DEFAULT_VID_PATH = "/CPM/videos";

    std::string operatorName;
    bool machineInSafeState;
    uint16_t countOfPercent_0;
    uint16_t countOfPercent_25;
    uint16_t countOfPercent_50;
    uint16_t countOfPercent_75;
    uint16_t countOfPercent_100;
    float elapsedTimeHrs;                     // used by POISSON for its calulation
    float cycleRateHrs;
    int64_t currentTimeSecondsSinceEpoch;     // needed by UI to calc the time difference
    int64_t tipAutoEnableTimeSeconds;         // time before tips are automatically enabled, NVM in CoachingTipHistory
    int64_t resetTimeSecondsSinceEpoch;       // time stamp when RESET happened
    bool displayRequired;                     // Maps to $D1199D - Operator Coaching Tip Summary Display Requirement Status
    int64_t displayRequiredTimeSeconds;       // Number of seconds displayRequired is set to true when a tip drops out of PERCENT_100
    int64_t tipRedSecondsSinceEpoch;          // time stamp when Tip drops out of PERCENT_100
    std::string videoPath;
    uint16_t countOfBadges;                   // current count of the number of Tips with the badgeFlag set, for ACD to send to Display
    uint32_t displayPageId;                   // UI current WebPage ID
    float algorithmWmaWindowHrs;              // Seconds per period to evlauate WMA-Algorithm, configurable by .rb
    float algorithmWmaWindowHrsElapsedTime;  // Seconds per period Counter
    bool algorithmIsPoisson;                  // True = POISSON,  false = WMA


    std::vector<CoachingTipOutput_t> coachingTipOutputList;

    // Initialize values in constructor
    CoachingSummaryDataStorage():
        operatorName{0},
        machineInSafeState{true},
        countOfPercent_0{0},
        countOfPercent_25{0},
        countOfPercent_50{0},
        countOfPercent_75{0},
        countOfPercent_100{0},
        elapsedTimeHrs{0},
        cycleRateHrs{0},
        currentTimeSecondsSinceEpoch{std::time(NULL)},
        tipAutoEnableTimeSeconds{SECONDS_PER_WEEK},
        resetTimeSecondsSinceEpoch{std::time(NULL)},
        displayRequired{false},
        displayRequiredTimeSeconds{},
        tipRedSecondsSinceEpoch{0},
        videoPath{DEFAULT_VID_PATH},
        countOfBadges{0},
        displayPageId{0},
        algorithmWmaWindowHrs{0},
        algorithmWmaWindowHrsElapsedTime{0},
        algorithmIsPoisson{true}
        {}

    // Initialize timers.
    void setCycleRate(float cycleRate_hz)
    {
        cycleRateHrs = hzToHrs(cycleRate_hz) ;
    }

    // Returns a % of how much is "Blue" rounded to nearest integer
    uint16_t getProgressIndicatorPercentageInt()
    {
        // Only enabled tips are used in calculation
        uint32_t tipCount = 0, blueCount = 0;
        for (CoachingTipOutput_t tip : coachingTipOutputList)
        {
            if (tip.sysTipEnableState && tip.opTipEnableState)
            {
                tipCount++;
                if (tip.poissonValuePercent == CoachingTipOutput_t::HaloPercent::PERCENT_100)
                {
                    blueCount++;
                }
            }
        }
        // Return 100% if all tips are disabled
        return tipCount == 0 ? 100 : static_cast<uint16_t>(static_cast<double>(blueCount) / tipCount * 100.0 + 0.5);
    }

    // Returns a # of Tips that have their BadgeFlag set
    uint16_t getBadgeCountInt()
    {
        return countOfBadges;
    }

    // Moves items from tipResults to Coaching_OutputDataList
    void updateTips(std::vector<CoachingTipResult_t>& tipResults)
    {
        bool algorithmWmaFlag = false;
        clearCounters();    // clear countOfPercent_0..100, AND countOfBadges
        elapsedTimeHrs += cycleRateHrs;
        algorithmWmaWindowHrsElapsedTime += cycleRateHrs;   // adjust to seconds
        currentTimeSecondsSinceEpoch = std::time(NULL);

        if (algorithmWmaWindowHrsElapsedTime >= algorithmWmaWindowHrs)
        {
            algorithmWmaWindowHrsElapsedTime = 0.0f;             // reset Window counter
            algorithmWmaFlag = true;
        }
        //LOG_ALERT("C:%f  W:%f, cRh:%f", algorithmWmaWindowHrsElapsedTime, algorithmWmaWindowHrs, cycleRateHrs);

        for (auto &tipResult : tipResults)
        {
            // Find the entry in coachingTipOutputList with the same tipNumber
            auto it = std::find_if(coachingTipOutputList.begin(), coachingTipOutputList.end(), 
                [tipResult](const CoachingTipOutput_t& x) { return x.tipNumber == tipResult.tipOutput.tipNumber; });

            if (it == coachingTipOutputList.end())
            {
                AIS_LOG_ERROR("Tip Number %d not found", tipResult.tipOutput.tipNumber);
                return;
            }

            // Update the tip and increment the percent counts
            if (it->updateTip(tipResult, elapsedTimeHrs, currentTimeSecondsSinceEpoch, tipAutoEnableTimeSeconds, algorithmWmaFlag, algorithmWmaWindowHrs, algorithmIsPoisson))
            {
                displayRequired = true;            
                tipRedSecondsSinceEpoch = currentTimeSecondsSinceEpoch;                
            }

            tipResult.poissonValue = it->poissonValue;   // add calculated poisson value to the breadcrumblog

            switch (it->getPoissonValuePercent())
            {
                case CoachingTipOutput_t::HaloPercent::PERCENT_0:
                    countOfPercent_0++;
                    break;

                case CoachingTipOutput_t::HaloPercent::PERCENT_25:
                    countOfPercent_25++;
                    break;

                case CoachingTipOutput_t::HaloPercent::PERCENT_50:
                    countOfPercent_50++;
                    break;

                case CoachingTipOutput_t::HaloPercent::PERCENT_75:
                    countOfPercent_75++;
                    break;

                case CoachingTipOutput_t::HaloPercent::PERCENT_100:
                    countOfPercent_100++;
                    break;

                default:
                    break;
            }

            if (it->sysTipEnableState && it->opTipEnableState && it->badgeFlag)
            {
                countOfBadges++;            // update badge count
            }

            AIS_LOG_DEBUG("tip#: %d badgeFlag:%d  countOfBadges:%d", it->tipNumber, it->badgeFlag, countOfBadges);

        }   // end of   "for (auto &tipResult : tipResults)"

        // Check if tip display requirement time has expired
        if (displayRequired && (currentTimeSecondsSinceEpoch - tipRedSecondsSinceEpoch > displayRequiredTimeSeconds))
        {
            displayRequired = false;
        }        
    }

    // Get Tip Auto Enable Time 
    int64_t getTipAutoEnableTime()
    {
        return tipAutoEnableTimeSeconds;
    }

    // Set Tip Auto Enable Time 
    void setTipAutoEnableTime(int64_t tipAutoEnableTime)
    {
        tipAutoEnableTimeSeconds = tipAutoEnableTime;
    }

    // Set Tip On/Off for the provided tipNumber. 
    void setOpTipOnOff(bool tipOn, uint32_t tipNumber)
    {
        // Find the entry in coachingTipOutputList with the same tipNumber
        auto tip = findTipByNumber(tipNumber);
        if (tip != nullptr)
        {
            tip->opTipEnableState = tipOn;
            tip->opTipEnableStateTimeSecondsSinceEpoch = std::time(NULL);
        }
    }

    // Set Tip Show/Hide for the provided tipNumber. 
    void setSysTipShowHide(bool showTip, uint32_t tipNumber)
    {
        // Find the entry in coachingTipOutputList with the same tipNumber
        auto tip = findTipByNumber(tipNumber);
        if (tip != nullptr)
        {
            tip->sysTipEnableState = showTip;
        }
    }

    // Increment the tipVideoViewCount for the provided tipNumber
    void setTutorialViewed(uint32_t tipNumber)
    {
        // Find the entry in coachingTipOutputList with the same tipNumber
        auto tip = findTipByNumber(tipNumber);
        if (tip != nullptr)
        {
            tip->tipVideoViewCount++;
            tip->tipVideoViewCountLifetime++;
        }
    }

    // Increment the tipTextViewCount & clear the badgeFlag for the provided tipNumber
    void setTipViewed(uint32_t tipNumber)
    {
        displayPageId = tipNumber;  // Track Display-Page ID to XCP

        // Find the entry in coachingTipOutputList with the same tipNumber
        auto tip = findTipByNumber(tipNumber);
        if (tip != nullptr)
        {
            tip->tipTextViewCount++;
            tip->tipTextViewCountLifetime++;
            tip->badgeFlag = false;
        }
    }

    // Increment the tipTriggerCount for testing purposes ONLY
    void setTipIncrement(uint32_t tipNumber)
    {
        // Find the entry in coachingTipOutputList with the same tipNumber
        auto tip = findTipByNumber(tipNumber);
        if (tip != nullptr)
        {
            tip->tipTriggerFlagOnlyForTestingByUI = true;
        }
    }
    // Decrement the tipTriggerCount for testing purposes ONLY
    void setTipDecrement(uint32_t tipNumber)
    {
        // Find the entry in coachingTipOutputList with the same tipNumber
        auto tip = findTipByNumber(tipNumber);
        if ((tip != nullptr) && (tip->tipTriggerCount > 0))
        {
            tip->tipTriggerCount--;
            tip->tipTriggerCountLifetime--;
        }
    }

    // Resets tip data while retaining reset/disabled flags
    void resetStats()
    {
        elapsedTimeHrs = 0.0f;
        algorithmWmaWindowHrsElapsedTime = 0.0f;
        resetTimeSecondsSinceEpoch = std::time(NULL);      // time stamp when RESET happened

        clearCounters();
        for (CoachingTipOutput_t& tip : coachingTipOutputList)
        {
            tip.resetStats();
        }
    }

    // Clears all tips
    void clear()
    {
        machineInSafeState = true;          // default to TRUE for now
        elapsedTimeHrs = 0.0f;
        algorithmWmaWindowHrsElapsedTime = 0.0f;
        currentTimeSecondsSinceEpoch = 0;   // needed by UI to calc the time difference
        resetTimeSecondsSinceEpoch = std::time(NULL);      // time stamp when RESET happened
        displayRequired = false;

        clearCounters();
        coachingTipOutputList.clear();
    }

    void clearCounters()
    {
        countOfPercent_0    = 0;
        countOfPercent_25   = 0;
        countOfPercent_50   = 0;
        countOfPercent_75   = 0;
        countOfPercent_100  = 0;
        countOfBadges       = 0;
    }

    void toJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const override
    {
        writer.StartObject();
        writer.Key("operatorName"), writer.String(operatorName);
        writer.Key("machineInSafeState"), writer.tBool(machineInSafeState);
        writer.Key("countOfPercent_0"), writer.Uint(countOfPercent_0);
        writer.Key("countOfPercent_25"), writer.Uint(countOfPercent_25);
        writer.Key("countOfPercent_50"), writer.Uint(countOfPercent_50);
        writer.Key("countOfPercent_75"), writer.Uint(countOfPercent_75);
        writer.Key("countOfPercent_100"), writer.Uint(countOfPercent_100);
        writer.Key("elapsedTimeHrs"), writer.Double(elapsedTimeHrs);
        writer.Key("currentTimeSecondsSinceEpoch"), writer.Int64(currentTimeSecondsSinceEpoch);
        writer.Key("tipAutoEnableTimeSeconds"), writer.Int64(tipAutoEnableTimeSeconds);
        writer.Key("resetTimeSecondsSinceEpoch"), writer.Int64(resetTimeSecondsSinceEpoch);
        writer.Key("displayRequired"), writer.tBool(displayRequired);
        writer.Key("countOfBadges"), writer.Uint(countOfBadges);
        writer.Key("displayPageId"), writer.Uint(displayPageId);
        writer.Key("algorithmWmaWindowHrs"), writer.Double(algorithmWmaWindowHrs);
        writer.Key("algorithmWmaWindowHrsElapsedTime"), writer.Double(algorithmWmaWindowHrsElapsedTime);
        writer.Key("algorithmIsPoisson"), algorithmIsPoisson ? writer.String("POISSON") : writer.String("WMA") ;

        writer.Key("tips");
        writer.StartArray();
        for (auto& coachingTipOutput : coachingTipOutputList)
        {
            coachingTipOutput.toJson(writer, videoPath);
        }
        
        writer.EndArray();
        writer.EndObject();
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        /* Archive Fields Here */
        ar & operatorName;
        ar & machineInSafeState;
        ar & countOfPercent_0;
        ar & countOfPercent_25;
        ar & countOfPercent_50;
        ar & countOfPercent_75;
        ar & countOfPercent_100;
        ar & elapsedTimeHrs;
        ar & currentTimeSecondsSinceEpoch;
        ar & tipAutoEnableTimeSeconds;
        ar & resetTimeSecondsSinceEpoch;
        ar & coachingTipOutputList;
        ar & displayRequired;
        ar & countOfBadges;

        if (version >=2)
        {
            ar & displayPageId;
        }

        if (version >=3)
        {
            ar & algorithmWmaWindowHrs;
            ar & algorithmWmaWindowHrsElapsedTime;
            ar & algorithmIsPoisson;
        }
    }

    void toCsv(CsvOutStream& out) const override
    {
        
    }

    uint32_t toXcp(ParameterDb& db, uint32_t startAddr) const override
    {
        uint32_t baseAddr = startAddr & 0xFFFF0000;
        uint32_t offset = startAddr & 0x0000FFFF;
                                                                                              // startAddr + 0 is countOfScsObjects
        DB_PUSH_ADDR(countOfPercent_0);                                                       // startAddr + 1
        DB_PUSH_ADDR(countOfPercent_25);                                                      // startAddr + 2
        DB_PUSH_ADDR(countOfPercent_50);                                                      // startAddr + 3
        DB_PUSH_ADDR(static_cast<uint8_t>(machineInSafeState));                               // startAddr + 4
        DB_PUSH_ADDR(elapsedTimeHrs);                                                         // startAddr + 5 // for current operator
        auto secondsSinceReset = (currentTimeSecondsSinceEpoch - resetTimeSecondsSinceEpoch);                  // seconds since last reset.. for current operator
        DB_PUSH_ADDR(static_cast<uint32_t>(secondsSinceReset));                               // startAddr + 6
        DB_PUSH_ADDR(static_cast<uint8_t>(displayRequired));                                  // startAddr + 7

        char name[8]={0};            // initialize to all ZERO
        strncpy ( name, operatorName.c_str(), 8 );
        DB_PUSH_ADDR(static_cast<uint32_t>(DB_PACK_32(name[0], name[1], name[2], name[3])));  // startAddr + 8
        DB_PUSH_ADDR(static_cast<uint32_t>(DB_PACK_32(name[4], name[5], name[6], name[7])));  // startAddr + 9
        DB_PUSH_ADDR(countOfPercent_75);                                                      // startAddr + 10
        DB_PUSH_ADDR(countOfPercent_100);                                                     // startAddr + 11
        DB_PUSH_ADDR(countOfBadges);                                                          // startAddr + 12
        DB_PUSH_ADDR(displayPageId);                                                          // startAddr + 13
        DB_PUSH_ADDR(algorithmWmaWindowHrs);                                                  // startAddr + 14
        DB_PUSH_ADDR(algorithmWmaWindowHrsElapsedTime);                                      // startAddr + 15
        DB_PUSH_ADDR(algorithmIsPoisson);                                                     // startAddr + 16

        // Iterate through Tips in TipNumber Order, since Tips have been ordered into Priority Order 
        uint32_t tipMax = coachingTipOutputList.size();
        for (uint32_t i=1; i<=tipMax; i++)  // tips start at 1 not 0.. need adjustment
        {
            auto tip = findTipByNumberConst(i);
            if (tip == nullptr)
            {
                AIS_LOG_ERROR("unknown Tip number:%d", i);
                continue;
            } 

            offset = 0;
            DB_INCR_ADDR(baseAddr);
            DB_PUSH_ADDR(tip->tipNumber);                                                //0
            DB_PUSH_ADDR(tip->lastSeverity);                                             //1
            DB_PUSH_ADDR(tip->avgSeverity);                                              //2
            DB_PUSH_ADDR(tip->maxSeverity);                                              //3
            DB_PUSH_ADDR(tip->minSeverity);                                              //4
            DB_PUSH_ADDR(tip->poissonValue);                                             //5
            DB_PUSH_ADDR(static_cast<uint8_t>(tip->poissonValuePercent));                //6   NOTE: used by new WMA algorithm
            DB_PUSH_ADDR(tip->poissonValueSeverityWeighted);                             //7
            DB_PUSH_ADDR(static_cast<uint8_t>(tip->poissonValueSeverityWeightedPercent));//8
            DB_PUSH_ADDR(tip->tipTrigger);                                               //9
            DB_PUSH_ADDR(tip->tipTriggerCount);                                          //A
            DB_PUSH_ADDR(static_cast<float>(tip->Threshold_0));                          //B
            DB_PUSH_ADDR(static_cast<float>(tip->Threshold_25));                         //C
            DB_PUSH_ADDR(static_cast<float>(tip->expectedOccurenceRatePerHour));         //D
            DB_PUSH_ADDR(static_cast<uint8_t>(tip->opTipEnableState));                   //E
            DB_PUSH_ADDR(static_cast<uint8_t>(tip->sysTipEnableState));                  //F
            // Make sure tipStat is always the same size
            auto tipStatCopy = tip->tipStat;
            tipStatCopy.resize(CoachingTipResult_t::MAX_STATS, 0.f);
            DB_PUSH_ADDR_CONTAINER(tipStatCopy);                                        //10..11..12..13..14
            DB_PUSH_ADDR(static_cast<uint8_t>(tip->tipStatus));                          //15
            DB_PUSH_ADDR(tip->tipVideoViewCount);                                        //16
            DB_PUSH_ADDR(static_cast<float>(tip->Threshold_50));                         //17
            DB_PUSH_ADDR(static_cast<float>(tip->Threshold_75));                         //18
            DB_PUSH_ADDR(static_cast<uint8_t>(tip->badgeFlag));                          //19
            DB_PUSH_ADDR(static_cast<uint32_t>(tip->badgeCount));                        //1A
            DB_PUSH_ADDR(static_cast<uint32_t>(tip->tipTextViewCount));                  //1B
            DB_PUSH_ADDR(static_cast<float>(tip->algorithmWmaInc));                      //1C
            DB_PUSH_ADDR(static_cast<float>(tip->algorithmWmaDec));                      //1D
            DB_PUSH_ADDR(static_cast<float>(tip->algorithmWmaLambda));                   //1E
            DB_PUSH_ADDR(static_cast<uint32_t>(tip->algorithmWmaMaxCount));              //1F
            DB_PUSH_ADDR(static_cast<uint32_t>(tip->algorithmWmaCurrentCount));          //20
            DB_PUSH_ADDR(static_cast<float>(tip->algorithmWmaRateLimitedTriggers));      //21
            DB_PUSH_ADDR(static_cast<float>(tip->algorithmWmaRateLimitedTriggersperhour));//22
            DB_PUSH_ADDR(static_cast<float>(tip->algorithmWmaCurrentValue));             //23

        }

        // Return the next free address
        return baseAddr | offset;
    }

private:
    static inline float hzToHrs(float cycleRate_hz) { return 1 / cycleRate_hz / 3600; }   // 3600 seconds per hour

    CoachingTipOutput_t *findTipByNumber(uint32_t tipNumber)
    {
        return const_cast<CoachingTipOutput_t*>(findTipByNumberConst(tipNumber));
    }

    const CoachingTipOutput_t *findTipByNumberConst(uint32_t tipNumber) const
    {
        // Find the entry in coachingTipOutputList with the same tipNumber
        auto it = std::find_if(coachingTipOutputList.begin(), coachingTipOutputList.end(),
                               [tipNumber](const CoachingTipOutput_t &x) { return x.tipNumber == tipNumber; });

        if (it == coachingTipOutputList.end())
        {
            AIS_LOG_ERROR("Tip Number %u not found", tipNumber);
            return nullptr;
        }
        else
        {
            return &(*it);
        }
    }
};

typedef Datum<CoachingSummaryDataStorage> CoachingSummaryData;

BOOST_CLASS_VERSION(CoachingSummaryDataStorage, 3);
#endif

