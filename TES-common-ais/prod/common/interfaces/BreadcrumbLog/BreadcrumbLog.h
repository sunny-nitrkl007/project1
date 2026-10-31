#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <ais/log/AisLogger.h>
#include <interfaces/DataLinkData/GPSDataLinkParam.h>
#include "BreadcrumbTip.h"
#include "BreadcrumbSegment.h"
#include "BreadcrumbStatus.h"
#include "interfaces/JSON/jsonable.h"

#ifndef _BREADCRUMBLOG_H_
#define _BREADCRUMBLOG_H_

class BreadcrumbLogStorage : public jsonable
{
public:
    std::string operatorName;
    bool machineInSafeState;
    uint32_t maxDistanceMeters;
    uint32_t maxTimeSeconds;
    float elapsedTimeHrs;
    int64_t currentTimeSecondsSinceEpoch;
    int64_t resetTimeSecondsSinceEpoch{currentTimeSecondsSinceEpoch};
    std::vector<boost::shared_ptr<Breadcrumb>> breadcrumbs;
    GPSDataLinkParam::GpsPositionStatusType gpsStatus;
    float latitude;
    float longitude;
    uint32_t currentCycle;

    BreadcrumbLogStorage() :
        operatorName{},
        machineInSafeState{false},
        maxDistanceMeters{50},	// default to 50 meters
        maxTimeSeconds{60},		// default to 60 seconds
        elapsedTimeHrs{0.f},
        currentTimeSecondsSinceEpoch{std::time(NULL)},
        resetTimeSecondsSinceEpoch{currentTimeSecondsSinceEpoch},
        breadcrumbs{},
        gpsStatus{GPSDataLinkParam::GpsPositionStatusType::POSITION_TYPE_NOT_AVAILABLE},
        latitude{0.f},
        longitude{0.f},
        currentCycle{0},        // increments when 3x3 cycle ends, used by UI to show records for specific Cycle
        maxRecords{1000},
        cycleRateHrs{0.f},
        addRecordFlag{false}	// indicates if NVM needs to be written to, returned and reset in update(),   used by CoachingTask to save to NVM, updates to Log not expected to happen very often and won't burn out NVM
    {
    }

    ~BreadcrumbLogStorage() { }

    // Initialize cycleRate
    void setCycleRate(float cycleRate_hz)
    {
        cycleRateHrs = hzToHrs(cycleRate_hz);
    }

    // Initialize max records
    void setMaxRecords(size_t maxRecords)
    {
        this->maxRecords = maxRecords;

        // Trim breadcrumbs if maxRecords size changes
        while (breadcrumbs.size() > maxRecords)
        {
            breadcrumbs.pop_back();
        }
    }

    // GET maxRecords
    size_t getMaxRecords()
    {
        return this->maxRecords;
    }

    // SET max Time Seconds
    void setMaxTimeSeconds(size_t MaxTimeSeconds)
    {
        this->maxTimeSeconds = MaxTimeSeconds;
    }

    // GET max Time Seconds
    size_t getMaxTimeSeconds()
    {
        return this->maxTimeSeconds;
    }

    // Initialize max Distance Meters
    void setMaxDistanceMeters(size_t MaxDistanceMeters)
    {
        this->maxDistanceMeters = MaxDistanceMeters;
    }

    // GET max Distance Meters
    size_t getMaxDistanceMeters()
    {
        return this->maxDistanceMeters;
    }

    // Call every cycle
    // returns Flag to indicate if NVM should be written
    bool update()
    {
        elapsedTimeHrs += cycleRateHrs;
        currentTimeSecondsSinceEpoch = std::time(NULL);

        bool temp_addRecordFlag = addRecordFlag;
        addRecordFlag = false; // reset for next update()
        AIS_LOG_DEBUG("update(): %d", temp_addRecordFlag);

        return temp_addRecordFlag;   // indicates if NVM should be written
    }

    // Call at Key-On
    void keyOn()
    {
        addBreadcrumb(boost::make_shared<BreadcrumbSegment>(BreadcrumbSegment(gpsStatus, latitude, longitude, currentCycle, BreadcrumbSegment::Segment::KEY_ON_ENGINE_OFF)));
    }

    // Call at Key-Off
    void keyOff()
    {
        addBreadcrumb(boost::make_shared<BreadcrumbSegment>(BreadcrumbSegment(gpsStatus, latitude, longitude, currentCycle, BreadcrumbSegment::Segment::KEY_OFF_ENGINE_OFF)));
    }

    // Call at 
    void segmentChange(uint8_t segment)
    {
        addBreadcrumb(boost::make_shared<BreadcrumbSegment>(BreadcrumbSegment(gpsStatus, latitude, longitude, currentCycle, static_cast<BreadcrumbSegment::Segment>(segment))));
    }

    // Call when the UI issues a command
    void commandReceived(BreadcrumbStatus::Type commandType, uint32_t value = 0)
    {
        addBreadcrumb(boost::make_shared<BreadcrumbStatus>(BreadcrumbStatus(gpsStatus, latitude, longitude, currentCycle, commandType, value)));
        if (commandType == BreadcrumbStatus::Type::RESET)
        {
            // remove all records of type TIP (next two code statements)
            auto end = std::remove_if(breadcrumbs.begin(), breadcrumbs.end(),[](const boost::shared_ptr<Breadcrumb>& x){
                        return Breadcrumb::BreadcrumbType::TIP == x->type;
                                    });
        
            breadcrumbs.erase(end, breadcrumbs.end());

            // set RESET Time
            resetTimeSecondsSinceEpoch = std::time(NULL);
        }
        
    }

    // Clear the log for the current operator
    void clear()
    {
        machineInSafeState = true;
        elapsedTimeHrs = 0.0f;
        currentTimeSecondsSinceEpoch = std::time(NULL);
        resetTimeSecondsSinceEpoch = resetTimeSecondsSinceEpoch;
        breadcrumbs.clear();
    }

    void setGpsStatus(const GPSDataLinkParam& gpsParam)
    {
        gpsStatus = gpsParam.GetGpsStatus();
        latitude = gpsParam.GetGpsLatitude(false);
        longitude = gpsParam.GetGpsLongitude(true);
        AIS_LOG_INFO("GPS status: %s, latitude: %f, longitude: %f", GPSDataLinkParam::toString(gpsStatus).c_str(), latitude, longitude);
    }

    // 3x3 cycle has ended, increment cycle
    void incrementCycle(const std::string& cycleName, uint8_t cycleId)
    {
        addBreadcrumb(boost::make_shared<BreadcrumbStatus>(BreadcrumbStatus(gpsStatus, latitude, longitude, currentCycle, BreadcrumbStatus::Type::CYCLE_END, cycleId)));
        currentCycle++;
        AIS_LOG_INFO("Cycle Ended:%d-%s starting new Cycle:%d", cycleId, cycleName.c_str(), currentCycle);
    }

    void updateTipResults(std::vector<CoachingTipResult_t>& tipResults)
    {
        for (auto& tipResult : tipResults)
        {
            if (tipResult.trigger)
            {
                    addBreadcrumb(boost::make_shared<BreadcrumbTip>(BreadcrumbTip(gpsStatus, latitude, longitude, currentCycle, tipResult)));
            }

            switch (tipResult.opTipEnableStateStatus)
            {
                case CoachingTipResult_t::opTipEnableStateEnum::OPERATOR_DISABLED:
                    addBreadcrumb(boost::make_shared<BreadcrumbStatus>(BreadcrumbStatus(gpsStatus, latitude, longitude, currentCycle, BreadcrumbStatus::Type::TIP_OFF_OPERATOR, tipResult.tipOutput.tipNumber)));
                    break;
                case CoachingTipResult_t::opTipEnableStateEnum::OPERATOR_ENABLED:
                    addBreadcrumb(boost::make_shared<BreadcrumbStatus>(BreadcrumbStatus(gpsStatus, latitude, longitude, currentCycle, BreadcrumbStatus::Type::TIP_ON_OPERATOR, tipResult.tipOutput.tipNumber)));
                    break;
                case CoachingTipResult_t::opTipEnableStateEnum::AUTO_ENABLED:
                    addBreadcrumb(boost::make_shared<BreadcrumbStatus>(BreadcrumbStatus(gpsStatus, latitude, longitude, currentCycle, BreadcrumbStatus::Type::TIP_ON_AUTOENABLE, tipResult.tipOutput.tipNumber)));
                    break;    
                default:
                    break;
            }
        }
    }

    // Move the breadcrumb to the container up to a maximum size of maxRecords
    void addBreadcrumb(boost::shared_ptr<Breadcrumb>&& pBreadcrumb)
    {
        breadcrumbs.insert(breadcrumbs.begin(), std::move(pBreadcrumb));
        if (breadcrumbs.size() > maxRecords)
        {
            breadcrumbs.pop_back();
        }
        addRecordFlag = true;
        AIS_LOG_DEBUG("update(): %d", addRecordFlag);
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        // Each class derived from Breadcrumb must registered
        ar.template register_type<BreadcrumbTip>();
        ar.template register_type<BreadcrumbSegment>();
        ar.template register_type<BreadcrumbStatus>();

        ar & operatorName;
        ar & machineInSafeState;
        ar & maxDistanceMeters;
        ar & maxTimeSeconds;
        ar & elapsedTimeHrs;
        ar & currentTimeSecondsSinceEpoch;
        ar & resetTimeSecondsSinceEpoch;
        ar & breadcrumbs;
        ar & maxRecords;
        ar & gpsStatus;
        ar & latitude;
        ar & longitude;

        if (version >=2)
        {
            ar & currentCycle;
        }
    }

    void toJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const override
    {
        writer.StartObject();
        writer.Key("operatorName"), writer.String(operatorName);
        writer.Key("machineInSafeState"), writer.tBool(machineInSafeState);
        writer.Key("maxNumRecords"), writer.Uint(maxRecords);
        writer.Key("maxDistanceMeters"), writer.Uint(maxDistanceMeters);
        writer.Key("maxTimeSeconds"), writer.Uint(maxTimeSeconds);
        writer.Key("elapsedTimeHrs"), writer.Double(elapsedTimeHrs);
        writer.Key("currentTimeSecondsSinceEpoch"), writer.Int64(currentTimeSecondsSinceEpoch);
        writer.Key("resetTimeSecondsSinceEpoch"), writer.Int64(resetTimeSecondsSinceEpoch);
        writer.Key("gpsStatus"), writer.String(GPSDataLinkParam::toString(gpsStatus));
        writer.Key("latitude"), writer.Double(latitude);
        writer.Key("longitude"), writer.Double(longitude);
        writer.Key("currentCycle"), writer.Uint(currentCycle);

        writer.Key("LogRecords");
        writer.StartArray();
        for (const auto& pBreadcrumb : breadcrumbs)
        {
            pBreadcrumb->toJson(writer);
        }
        writer.EndArray();

        writer.EndObject();
    }
private:
    static inline float hzToHrs(float cycleRate_hz) { return 1 / cycleRate_hz / 3600; }   // 3600 seconds per hour

    size_t maxRecords;
    float cycleRateHrs;
    bool addRecordFlag;
};

typedef Datum<BreadcrumbLogStorage> BreadcrumbLog;

BOOST_CLASS_VERSION(BreadcrumbLogStorage, 2);
#endif
