#include <algorithm>
#include <iterator>
#include <numeric>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/vector.hpp>
#include <ais/log/AisLogger.h>
#include <ais/serialization/Datum.h> // For Boost serialization
#include "interfaces/CoachingSummaryData/CoachingTipOutput.h"
#include "interfaces/JSON/jsonable.h"

#ifndef _COACHING3X3DATA_H_
#define _COACHING3X3DATA_H_

struct Coaching3x3TipData_t : public csvable
{
    // Size of the queue sent to the UI
    static constexpr size_t SeverityQueueSize = 10;

    // Number of previous cycles used to calculate the total severity
    static constexpr size_t TotalSeverityCycles = 4;

    uint32_t number;
    std::string tipName;
    std::string videoFileName;
    bool OpTipEnableState;
    bool SysTipEnableState;
    float totalSeverity;
    float currentSeverity;
    std::deque<float> severityHistory;

    // Needed for serialization
    Coaching3x3TipData_t() = default;

    Coaching3x3TipData_t(uint32_t number, const std::string& tipName, const std::string& videoFileName, bool sysTipEnableState = true) :
        number{number},
        tipName{tipName},
        videoFileName{videoFileName},
        OpTipEnableState{true},
        SysTipEnableState{sysTipEnableState},
        totalSeverity{0.0f},
        currentSeverity{0.0f}
    {
        severityHistory.assign(SeverityQueueSize, 0.0f);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @Resets tip data
    ///////////////////////////////////////////////////////////////////////////////
    void resetStats()
    {
        totalSeverity = 0.0f;
        currentSeverity = 0.0f;
        severityHistory.assign(SeverityQueueSize, 0.0f);
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        ar & number;
        ar & tipName;
        ar & videoFileName;
        ar & OpTipEnableState;
        ar & SysTipEnableState;
        ar & totalSeverity;
        ar & currentSeverity;
        ar & severityHistory;
    }

    void toCsv(CsvOutStream& out) const 
    {
        out("number", number);
        out("tipName", tipName);
        out("videoFileName", videoFileName);
        out("OpTipEnableState", OpTipEnableState);
        out("SysTipEnableState", SysTipEnableState);
        out("totalSeverity", totalSeverity);
        out("currentSeverity", currentSeverity);
        for (size_t i = 0; i < severityHistory.size(); ++i)
        {
            out("severityHistory[" + std::to_string(i) + "]", severityHistory[i]);
        }
    }

    // Capture maximum severity when a tip triggers and recalcuate accumulated values
    void update(float severity, bool tipTriggered, bool cycleEnded)
     {
        // If a tip triggers, store severity if it exceeds the value for the current cycle
        if (tipTriggered && (severity > currentSeverity))
        {
            currentSeverity = severity;
        }

        // If cycle has ended, store severity only if a tip triggered at the same time
        if (cycleEnded)
        {
            severityHistory.push_front(currentSeverity);
            severityHistory.pop_back();
            accumulateSeverity();
            currentSeverity = 0.0f;
        }
    }

    void toJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const std::string& videoPath) const
    {
        writer.StartObject();
        writer.Key("number"), writer.Uint(number);
        writer.Key("tipName"), writer.String(tipName);
        writer.Key("videoUrl"), writer.String(videoPath + '/' + videoFileName);
        writer.Key("SysTipEnableState"), writer.tBool(SysTipEnableState);
        writer.Key("OpTipEnableState"), writer.tBool(OpTipEnableState);
        writer.Key("totalSeverity"), writer.Double(totalSeverity);
        writer.Key("currentSeverity"), writer.Double(currentSeverity);

        writer.Key("previousCycles");
        writer.StartArray();
        for (auto& severity : severityHistory)
        {
            writer.Double(severity);
        }
        
        writer.EndArray();
        writer.EndObject();
    }

private:
    inline void accumulateSeverity()
    {   
        // if first TotalSeverityCycles elements are 0.0f then totalSeverity = 0.0f
        if (0.0f == accumulate(severityHistory.begin(), std::next(severityHistory.begin(), TotalSeverityCycles), 0.0f))
        {
            totalSeverity = 0.0f;
        }
        else
        {
            totalSeverity = accumulate(severityHistory.begin(), severityHistory.end(), 0.0f); 
        }
    }
};

class Coaching3x3DataStorage : public csvable, public jsonable
{
public:
    static constexpr char const* DEFAULT_VID_PATH = "/CPM/videos";

    std::string name;
    bool OpTipEnableState;
    std::string operatorName;
    bool machineInSafeState;
    int64_t lastOccurenceTime;
    uint32_t count;
    bool isActive;
    int64_t currentTimeSecondsSinceEpoch;   // needed by UI to calc the time difference
    std::string videoPath;

    std::vector<Coaching3x3TipData_t> tips;

    Coaching3x3DataStorage() :
        name{},
        OpTipEnableState{true},
        operatorName{},
        machineInSafeState{false},
        lastOccurenceTime{0},
        count{0},
        isActive{false},
        currentTimeSecondsSinceEpoch{0},
        videoPath{DEFAULT_VID_PATH},
        tips{}
        {}

    ///////////////////////////////////////////////////////////////////////////////
    /// @Resets tip data
    ///////////////////////////////////////////////////////////////////////////////
    void resetStats()
    {
        lastOccurenceTime = 0;
        for (Coaching3x3TipData_t& tip : tips)
        {
            tip.resetStats();
        }
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        ar & name;
        ar & OpTipEnableState;
        ar & operatorName;
        ar & machineInSafeState;
        ar & lastOccurenceTime;
        ar & count;
        ar & isActive;
        ar & currentTimeSecondsSinceEpoch;
        ar & tips;
    }

    void toCsv(CsvOutStream& out) const 
    {
        out("name", name);
        out("OpTipEnableState", OpTipEnableState);
        out("operatorName", operatorName);
        out("machineInSafeState", machineInSafeState);
        out("lastOccurenceTime", lastOccurenceTime);
        out("count", count);
        out("isActive", isActive);
        out("currentTimeSecondsSinceEpoch", currentTimeSecondsSinceEpoch);
        out("videoPath", videoPath);

        for (auto tip : tips)
        {
            tip.toCsv(out);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @Accumulate severity of last 10 tries and store 3 most severe
    ///////////////////////////////////////////////////////////////////////////////
    void update(const std::vector<CoachingTipOutput_t>& coachingTipOutputList, bool cycleRunning, bool cycleEnded)
    {
        // always update currentTime
        currentTimeSecondsSinceEpoch = std::time(NULL);

        // Iterate through all tips
        if (cycleRunning || cycleEnded)
        {
            for (auto &tip : tips)
            {
                // Find the entry in coachingTipOutputList with the same tipNumber
                auto it = std::find_if(coachingTipOutputList.begin(), coachingTipOutputList.end(), 
                    [tip](const CoachingTipOutput_t& x) { return x.tipNumber == tip.number; });

                // Should never evaluate to false, coachingTipOutputList contains all tipNumbers
                if (it != coachingTipOutputList.end())
                {
                    bool tipTriggered = (it->tipTrigger == 1);
                    tip.update(it->lastSeverity, tipTriggered, cycleEnded);

                    // check if Tip is Turned Off by Operator or System
                    tip.SysTipEnableState = it->sysTipEnableState;
                    tip.OpTipEnableState  = it->opTipEnableState;
                }
            }
        }
        // Increment cycle counter
        if (cycleEnded)
        {
            count++;
            lastOccurenceTime = currentTimeSecondsSinceEpoch;
        }
    }

    // Set Tip On/Off for the provided tipNumber. 
    void setOpTipOnOff(bool tipOn, uint32_t tipNumber)
    {
        // Find the entry in tips with the same tipNumber
        auto tip = findTipByNumber(tipNumber);
        if (tip != nullptr)
        {
            tip->OpTipEnableState = tipOn;
        }
    }

    // Set Tip Show/Hide for the provided tipNumber. 
    void setSysTipShowHide(bool showTip, uint32_t tipNumber)
    {
        // Find the entry in coachingTipOutputList with the same tipNumber
        auto tip = findTipByNumber(tipNumber);
        if (tip != nullptr)
        {
            tip->OpTipEnableState = showTip;
        }
    }

    void toJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const override
    {
        writer.StartObject();
        writer.Key("name"), writer.String(name);
        writer.Key("OpTipEnableState"), writer.tBool(OpTipEnableState);
        writer.Key("operatorName"), writer.String(operatorName);
        writer.Key("machineInSafeState"), writer.tBool(machineInSafeState);
        writer.Key("lastOccurenceTime"), writer.Int64(lastOccurenceTime);
        writer.Key("count"), writer.Uint(count);
        writer.Key("isActive"), writer.tBool(isActive);
        writer.Key("currentTimeSecondsSinceEpoch"), writer.Int64(currentTimeSecondsSinceEpoch);

        writer.Key("tips");
        writer.StartArray();
        for (auto& tip : tips)
        {
            tip.toJson(writer, videoPath);
        }
        
        writer.EndArray();
        writer.EndObject();
    }

private:
    Coaching3x3TipData_t *findTipByNumber(uint32_t tipNumber)
    {
        // Find the entry in tips with the same tipNumber
        auto it = std::find_if(tips.begin(), tips.end(),
                               [tipNumber](const Coaching3x3TipData_t &x) { return x.number == tipNumber; });

        if (it == tips.end())
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

typedef Datum<Coaching3x3DataStorage> Coaching3x3Data;

class Coaching3x3DataList : public jsonable
{
public:
    using iterator = std::vector<Coaching3x3Data>::iterator;
    using const_iterator = std::vector<Coaching3x3Data>::const_iterator;

    iterator begin() { return list.begin(); }
    iterator end() { return list.end(); }
    const_iterator begin() const { return list.begin(); }
    const_iterator end() const { return list.end(); }

    inline bool empty() { return list.empty(); }
    inline void clear() { list.clear(); }
    inline void push_back(Coaching3x3Data& data) { list.push_back(data); }

    // Resets tip data
    void resetStats()
    {
        for (Coaching3x3Data& data : list)
        {
            data.resetStats();
        }
    }

    void toJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const override
    {
        for (auto & data : list)
        {
            data.toJson(writer);
        }
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        ar & list;
    }

private:
    std::vector<Coaching3x3Data> list;
};

BOOST_CLASS_VERSION(Coaching3x3TipData_t, 1);
BOOST_CLASS_VERSION(Coaching3x3DataStorage, 1);
BOOST_CLASS_VERSION(Coaching3x3DataList, 1);

#endif
