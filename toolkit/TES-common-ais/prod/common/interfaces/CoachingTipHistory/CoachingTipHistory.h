#include <algorithm>
#include <mutex>
#include <numeric>
#include <time.h>

#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>

#include <oel_pack.h>

#include <ais/config/ConfigSection.h>
#include <ais/serialization/Datum.h> // For Boost serialization
#include <ais/serialization/csvable.h>
#include <ais/serialization/csvable.h>
#include <bdt/bdtUtils.h>
#include <taskPlugins/interfaces/BdtManagerInterface.h>

#include <interfaces/CoachingSummaryData/CoachingTipOutput.h>
#include <interfaces/DataLinkData/GPSDataLinkParam.h>
#include <xcp_server/db/XCPServerDb.hpp>

#ifndef _COACHINGTIPHISTORY_H_
#define _COACHINGTIPHISTORY_H_

using namespace xcp_server;

// State IDs are partially defined in catdllib_sid_def.h using SID_ prefixes
using GpsQualityType_t = uint16_t;
constexpr GpsQualityType_t SID_NO_FIX = 0x01AB;
constexpr GpsQualityType_t SID_GPS_FIX = 0x01AC;
constexpr GpsQualityType_t SID_DIFFERENTIAL_GPS_FIX = 0x01AD;
constexpr GpsQualityType_t SID_FLOATING_REAL_TIME_KINEMATIC = 0x01AE;
constexpr GpsQualityType_t SID_FIXED_REAL_TIME_KINEMATIC = 0x01AF;
constexpr GpsQualityType_t SID_DUAL_FREQUENCY_DIFFERENTIAL_GPS_FIX = 0x01E3;

// Abstract class with accessor functions
class CoachingTipHistoryInterface {
public:
    virtual double getLongitude() const = 0;
    virtual double getLatitude() const = 0;
    virtual GpsQualityType_t getGpsQualityType() const = 0;
    virtual uint32_t getShmSec() const = 0;
};

class CoachingTipHistoryStorage : public CoachingTipHistoryInterface, public csvable, public xcpable, public jsonable
{
public:
    static constexpr int SECONDS_PER_WEEK = 604800;        /// amount of seconds in One week
    static constexpr uint16_t BdtParamCount = 8;        // removed Operator Name from PSR report
    static constexpr uint8_t GidAsciiDefaultDelimiter = 0x2A;

    CoachingTipHistoryStorage():
        pActiveOperatorIdHistory{nullptr},
        maxSavedOperators{15},
        maxRecords{1000},
        operatorExpirationDays{180},
        longitude{0.0},
        latitude{0.0},
        gpsQualityType{SID_NO_FIX},
        shmSec{0},
        tipAutoEnableTimeSeconds{SECONDS_PER_WEEK}
    {}

    void initialize(ConfigSection& config)
    {
        config.get("maxSavedOperators", maxSavedOperators);
        config.get("coachingTipHistoryMaxRecords", maxRecords);
        config.get("operatorExpirationDays", operatorExpirationDays);
        AIS_LOG_INFO("initialize: maxSavedOperators=%u maxRecords=%u operatorExpirationDays=%u", maxSavedOperators, maxRecords, operatorExpirationDays);
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

    const void setActiveOperatorId(const std::string& operatorId)
    {
        AIS_LOG_INFO("new opID:%s  Size:%d/%d  Records:%d/%d", operatorId.c_str(), operatorIdHistories.size(), maxSavedOperators, getRecordCount(), maxRecords);

        // if no Tips Trigger records, then remove current entry from List
        if ((nullptr != pActiveOperatorIdHistory) && (0 == pActiveOperatorIdHistory->getRecordCount()))    // if no Tip records, then delete
        {
            AIS_LOG_INFO("No Tips: opID:%s  record Count:%d", pActiveOperatorIdHistory->operatorId.c_str(), pActiveOperatorIdHistory->getRecordCount());
            operatorIdHistories.pop_front();
        }

        // Search for Operator ID
        auto itListEntry = std::find_if(operatorIdHistories.begin(), operatorIdHistories.end(), 
            [operatorId] (const OperatorIdHistory& listEntry) { return listEntry.operatorId == operatorId; });
        if (itListEntry != operatorIdHistories.end())
        {
            pActiveOperatorIdHistory = &(*itListEntry);
            // Re-Sort operatorIdHistories by timeSpecSec since oldest is removed for Max Operators or Max Records
            operatorIdHistories.sort([](const OperatorIdHistory& a, const OperatorIdHistory& b) { return a.timeSpecSec > b.timeSpecSec; });
        }
        else
        {
            // New Operator ID, add to list
            operatorIdHistories.emplace_front(operatorId);
            pActiveOperatorIdHistory = &operatorIdHistories.front();

            // Remove oldest entry if max operators have been exceeded
            if (operatorIdHistories.size() > maxSavedOperators)
            {
                AIS_LOG_INFO("REMOVE opID:%s  record Count:%d", operatorIdHistories.back().operatorId.c_str(), operatorIdHistories.back().getRecordCount());
                operatorIdHistories.pop_back();
            }
        }
        pActiveOperatorIdHistory->setActive();

        for (auto const& listEntry : operatorIdHistories)
        {
            AIS_LOG_INFO("opID:%s   %d", listEntry.operatorId.c_str(), listEntry.getRecordCount());
        }
    }

    void setGpsStatus(const GPSDataLinkParam& gpsParam)
    {
        // long/lat should be scaled from -/+180 and -/+90, repectively
        longitude = gpsParam.GetGpsLongitude(false);
        latitude = gpsParam.GetGpsLatitude(false);
        gpsQualityType = gpsParam.GetGpsStatus() == GPSDataLinkParam::GpsPositionStatusType::POSITION_VALID ? SID_GPS_FIX : SID_NO_FIX;
    }

    void setShmSec(uint32_t shmSec)
    {
        this->shmSec = shmSec;
    }

    // Returns true if Tip History has been updated, false otherwise
    bool updateTipResults(const std::vector<CoachingTipResult_t>& tipResults)
    {
        bool changed = false;

        // Check History size at key-on
        static bool firstTime{true};
        if (firstTime)
        {
            firstTime = false;
            checkTipHistory();      // always check this
            if (pActiveOperatorIdHistory == nullptr)
            {
                AIS_LOG_ERROR("updateTipResults called without an active Operator ID");
                return false;
            }
            changed = true;
        }

        for (auto& tipResult : tipResults)
        {
            // Store if tip triggered and progress is <= 75% Threshold
            if ((tipResult.trigger > 0) && (tipResult.tipOutput.getPoissonValuePercent() != CoachingTipOutput_t::HaloPercent::PERCENT_100) && tipResult.sysTipEnableStateStatus == CoachingTipResult_t::sysTipEnableStateEnum::SYSTEM_ENABLED)
            {
                pActiveOperatorIdHistory->triggerTip(tipResult, *this);
                allOperatorTipHistories.triggerTip(tipResult, *this);
                changed = true;
                AIS_LOG_INFO("num:%d-%s", tipResult.tipOutput.tipNumber, tipResult.tipOutput.tipName.c_str());
            }
        }

        // If Tip History changed, check the max number of records
        if (changed)
        {
            checkRecordCount();
        }
        return changed;
    }

    uint16_t getRecordCount() const
    {
        return std::accumulate(operatorIdHistories.begin(), operatorIdHistories.end(), 0,
            [] (uint16_t numRecords, const OperatorIdHistory& operatorIdHistory) { return numRecords + operatorIdHistory.getRecordCount(); });
    }
    
// CoachingTipHistoryInterface
    double getLongitude() const override { return longitude; }
    double getLatitude() const override { return latitude; }
    GpsQualityType_t getGpsQualityType() const override { return gpsQualityType; }
    uint32_t getShmSec() const override { return shmSec; }

// BDT Manager Interface Callback
    void appendSubFile(bdt::BlockData_t& blockData, BdtManagerInterface::SubFileCount_t& subFileCount)
    {
        auto initialSize = static_cast<uint16_t>(blockData.size());

        // Sort operatorIdHistories by Operator Id
        operatorIdHistories.sort([](const OperatorIdHistory& a, const OperatorIdHistory& b) { return a.operatorId < b.operatorId; });

        // Hard coded for now
        // ET requires text field be ASCII delimited (*/0x2A in this case)
        static const bdt::BlockData_t AsciiVarSubData{0x2A};
        static const bdt::BlockData_t StateListedVarSubData{0x05};

        static const bdt::gid::Metadata OperatorIdNameMetadata{
            0x000003FA,
            bdt::gid::DsiType::NOT_SUPPORTED,
            bdt::gid::DataOrder::MSB_FIRST,
            bdt::gid::DataLengthType::VARIABLE_LENGTH_DELIMITED,
            0xFFFF,
            bdt::gid::DataType::ASCII,
            AsciiVarSubData
        };

        static const bdt::gid::Metadata TipIdNameMetadata{
            0x0000078E,
            bdt::gid::DsiType::NOT_SUPPORTED,
            bdt::gid::DataOrder::MSB_FIRST,
            bdt::gid::DataLengthType::VARIABLE_LENGTH_DELIMITED,
            0xFFFF,
            bdt::gid::DataType::ASCII,
            AsciiVarSubData
        };

        static const bdt::gid::Metadata TipCategoryMetadata{
            0x0000078D,
            bdt::gid::DsiType::NOT_SUPPORTED,
            bdt::gid::DataOrder::MSB_FIRST,
            bdt::gid::DataLengthType::FIXED_LENGTH,
            16,
            bdt::gid::DataType::STATE_LISTED,
            StateListedVarSubData
        };

        static const bdt::BlockData_t TotalTripTriggerCountVarSubData{0x00, 0x56};
        static const bdt::gid::Metadata TotalTripTriggerCountMetadata{
            0x0000072E,
            bdt::gid::DsiType::NOT_SUPPORTED,
            bdt::gid::DataOrder::LSB_FIRST,
            bdt::gid::DataLengthType::FIXED_LENGTH,
            32,
            bdt::gid::DataType::SCALED_UNSIGNED_ZERO_OFFSET,
            TotalTripTriggerCountVarSubData
        };

        static const bdt::BlockData_t DateTimeVarSubData{0x01, 0x07};
        static const bdt::gid::Metadata DateTimeMetadata{
            0x00000316,
            bdt::gid::DsiType::NOT_SUPPORTED,
            bdt::gid::DataOrder::MSB_FIRST,
            bdt::gid::DataLengthType::FIXED_LENGTH,
            64,
            bdt::gid::DataType::DATE_AND_TIME,
            DateTimeVarSubData
        };

        static const bdt::BlockData_t TotalOperatingHoursVarSubData{0x16, 0x0F};
        static const bdt::gid::Metadata TotalOperatingHoursMetadata{
            0x00000075,
            bdt::gid::DsiType::NOT_SUPPORTED,
            bdt::gid::DataOrder::LSB_FIRST,
            bdt::gid::DataLengthType::FIXED_LENGTH,
            32,
            bdt::gid::DataType::SCALED_UNSIGNED_ZERO_OFFSET,
            TotalOperatingHoursVarSubData
        };

        static const bdt::BlockData_t LatLongVarSubData{0x1E, 0x0A};
        static const bdt::gid::Metadata LatitudeMetadata{
            0x0000072F,
            bdt::gid::DsiType::LARGEST_VALUES_32,
            bdt::gid::DataOrder::LSB_FIRST,
            bdt::gid::DataLengthType::FIXED_LENGTH,
            32,
            bdt::gid::DataType::SCALED_SIGNED_ZERO_OFFSET,
            LatLongVarSubData
        };
        static const bdt::gid::Metadata LongitudeMetadata{
            0x00000730,
            bdt::gid::DsiType::LARGEST_VALUES_32,
            bdt::gid::DataOrder::LSB_FIRST,
            bdt::gid::DataLengthType::FIXED_LENGTH,
            32,
            bdt::gid::DataType::SCALED_SIGNED_ZERO_OFFSET,
            LatLongVarSubData
        };

        static const bdt::BlockData_t GpsQualityTypeVarSubData{0x05};
        static const bdt::gid::Metadata GpsQualityTypeMetadata{
            0x000005E2,
            bdt::gid::DsiType::NOT_SUPPORTED,
            bdt::gid::DataOrder::MSB_FIRST,
            bdt::gid::DataLengthType::FIXED_LENGTH,
            16,
            bdt::gid::DataType::STATE_LISTED,
            StateListedVarSubData
        };
        const bdt::BlockData_t BlockDataHeader{0xCA, 0x11, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x0F, 0x01, 0x00, 0x00, 0x03, 0x11, 0x00, 0x02, 
                                                                                           //  ^^^^^^^^^^ total size of the blockData
                              0x40, 0x25, 0x00, 0x00,
                              0x48, 0x69, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
                                                               // ^^^^^^^^^^ number of subfiles
                              0x40, 0x26}; // Encoding, skip Visbility for now
        // Reserve space for block data, assume max length of strings
        constexpr auto EncodingBlockLength = 108;
        constexpr auto RecordPrefixLength = 4;
        constexpr auto OperatorIdNameMaxLength = 12;
        constexpr auto TipNameMaxLength = 50;
        constexpr auto FixedDataLength = 28;
        auto numRecords = getRecordCount();
        blockData.reserve(blockData.size() + BlockDataHeader.size() + EncodingBlockLength + numRecords * (RecordPrefixLength + OperatorIdNameMaxLength + TipNameMaxLength + FixedDataLength));
        AIS_LOG_DEBUG("Reserving 0x%02X bytes for blockData for %u records", blockData.capacity(), numRecords);

        // Add Header
        blockData.insert(blockData.end(), BlockDataHeader.begin(), BlockDataHeader.end());

        // Add Parameter count
        blockData.push_back((BdtParamCount & 0xFF00) >> 8);
        blockData.push_back((BdtParamCount & 0x00FF));

        // Add Encoding Block
        //bdt::gid::appendEncodingBlock(OperatorIdNameMetadata, blockData); // removed OperatorName from PSR
        // OperatorTipHistory
        bdt::gid::appendEncodingBlock(TipIdNameMetadata, blockData);
        bdt::gid::appendEncodingBlock(TipCategoryMetadata, blockData);
        // TriggeredTipData
        bdt::gid::appendEncodingBlock(TotalTripTriggerCountMetadata, blockData);
        bdt::gid::appendEncodingBlock(DateTimeMetadata, blockData);
        bdt::gid::appendEncodingBlock(TotalOperatingHoursMetadata, blockData);
        bdt::gid::appendEncodingBlock(LatitudeMetadata, blockData);
        bdt::gid::appendEncodingBlock(LongitudeMetadata, blockData);
        bdt::gid::appendEncodingBlock(GpsQualityTypeMetadata, blockData);

        // Add records
        uint16_t recordCount{0};
//        for (auto& operatorIdHistory : operatorIdHistories)   No OperatorName, only report allOperatorTipHistories
//        {
            for (auto& operatorTipHistory : allOperatorTipHistories.operatorTipHistories)
            {
                for (auto& tip : operatorTipHistory.triggeredTips)
                {
                    recordCount++;
                    // Record header
                    blockData.push_back(0x40);
                    blockData.push_back(0x21);
                    blockData.push_back((recordCount & 0xFF00) >> 8);
                    blockData.push_back((recordCount & 0x00FF));
                    // Operator ID + delimiter
                    //blockData.insert(blockData.end(), allOperatorTipHistories.operatorId.begin(), allOperatorTipHistories.operatorId.end());
                    uint8_t asciiDelimiter{GidAsciiDefaultDelimiter};
                    //blockData.push_back(asciiDelimiter);
                    // Tip Name + delimiter
                    blockData.insert(blockData.end(), operatorTipHistory.name.begin(), operatorTipHistory.name.end());
                    blockData.push_back(asciiDelimiter);
                    // Tip Category & Trigger Count
                    blockData.resize(blockData.size() + 6);
                    auto pData = &blockData.back() - (6 - 1);
                    OEL_PACK_BE_16(pData, operatorTipHistory.category);
                    // Tip Trigger Count
                    OEL_PACK_LE_32(pData, tip.totalTriggerCount);
                    // Date/Time
                    tm dateTime;
                    localtime_r(&tip.timeSpec.tv_sec, &dateTime);
                    if (!bdt::gid::appendTimeStamp(dateTime, DateTimeMetadata, blockData))
                    {
                        AIS_LOG_ERROR("Unsupported Date/Time format");
                    }
                    // Total Operating Hours, Latitude, Longitude, GPS Quality Type
                    blockData.resize(blockData.size() + 14);
                    pData = &blockData.back() - (14 - 1);
                    OEL_PACK_LE_32(pData, tip.shmSec);
                    uint32_t latConv = static_cast<uint32_t>(tip.latitude * 1E7);
                    OEL_PACK_LE_32(pData, latConv);
                    uint32_t longConv = static_cast<uint32_t>(tip.longitude * 1E7);
                    OEL_PACK_LE_32(pData, longConv);
                    OEL_PACK_BE_16(pData, tip.gpsQualityType);
                    AIS_LOG_DEBUG("TipName=%s shmSec=%u gpsQualityType=0x%X latitude=%f latConv=0x%X longitude=%f longConv=0x%X", operatorTipHistory.name.c_str(), tip.shmSec, tip.gpsQualityType, latitude, latConv, longitude, longConv);
                }
            }
//        }
        // Store size and record count information
        auto recordSize = blockData.size() - initialSize;
        uint16_t blockSizeIndex{static_cast<uint16_t>(bdt::ApplicationHistoryBlockSizeIndex + initialSize)};
        blockData[blockSizeIndex++] = (recordSize & 0xFF00) >> 8;
        blockData[blockSizeIndex  ] = (recordSize & 0x00FF);

        // Number of Subfiles is encoding block ($4026) + record count ($4021)
        auto recordSubFileCount = 1 + recordCount;
        uint16_t subFileCountIndex{static_cast<uint16_t>(bdt::ApplicationHistorySubFileCountIndex + initialSize)};
        blockData[subFileCountIndex++] = (recordSubFileCount & 0xFF00) >> 8;
        blockData[subFileCountIndex  ] = (recordSubFileCount & 0x00FF);

        // Increment Total $CA11 subfile count
        subFileCount++;
        AIS_LOG_DEBUG("Reserving 0x%02X bytes for blockData for %u records", blockData.capacity(), numRecords);
    }

// csvable
    void toCsv(CsvOutStream& out) const override
    {
    }

// xcpable
    uint32_t toXcp(ParameterDb& db, uint32_t startAddr) const override
    {
        uint32_t baseAddr = startAddr & 0xFFFF0000;
        uint32_t offset = startAddr & 0x0000FFFF;
        // DB_PUSH_ADDR(countOfPercent_0);                                                       // startAddr + 1

        // Return the next free address
        return baseAddr | offset;
    }

// jsonable
    void toJson(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const override
    {
        // writer.StartObject();
        // writer.Key("operatorId"), writer.String(operatorId);

        // writer.Key("tips");
        // writer.StartArray();
        // for (auto& coachingTipOutput : coachingTipOutputList)
        // {
        //     coachingTipOutput.toJson(writer, videoPath);
        // }
        
        // writer.EndArray();
        // writer.EndObject();
    }

private:

    struct TriggeredTipData
    {
        TriggeredTipData(const TriggeredTipData* pTriggeredTipDataPrevious, const CoachingTipHistoryInterface& coachingTipHistory) :
            totalTriggerCount{pTriggeredTipDataPrevious == nullptr ? 1 : pTriggeredTipDataPrevious->totalTriggerCount + 1},
            shmSec{coachingTipHistory.getShmSec()},
            latitude{coachingTipHistory.getLatitude()},
            longitude{coachingTipHistory.getLongitude()},
            gpsQualityType{coachingTipHistory.getGpsQualityType()}
        {
            auto clockResult = clock_gettime(CLOCK_REALTIME, &timeSpec);
            if (clockResult != 0)
            {
                AIS_LOG_WARN("clock_gettime failed with errorCode %u", clockResult);
            }
            AIS_LOG_DEBUG("shmSec=%u gpsQualityType=%u latitude=%f longitude=%f", shmSec, gpsQualityType, latitude, longitude);
        }

        TriggeredTipData() = default;

        template <class Archive>
        void serialize(Archive& ar, unsigned int version)
        {
            /* Archive Fields Here */
            ar & totalTriggerCount;
            ar & timeSpec.tv_sec;
            ar & timeSpec.tv_nsec;
            ar & shmSec;
            ar & latitude;
            ar & longitude;
            ar & gpsQualityType;
        }

        uint32_t totalTriggerCount;
        timespec timeSpec;
        uint32_t shmSec; // Service Hour Meter/Total Operating Hours in units of seconds
        double latitude;
        double longitude;
        GpsQualityType_t gpsQualityType;
    };


    // tipEntrys are sorted oldest -> newest
    struct OperatorTipHistory
    {
        static constexpr size_t MaxTipEntries = 3;

        explicit OperatorTipHistory(const CoachingTipResult_t& tipResult) :
            name{tipResult.tipOutput.tipName},
            priority{tipResult.tipOutput.tipPriority},
            category{tipResult.tipOutput.tipCategory}
        {
        }

        OperatorTipHistory() = default;

        void triggerTip(const CoachingTipHistoryInterface& coachingTipHistory)
        {
            auto pTriggeredTipDataPrevious = triggeredTips.empty() ? nullptr : &triggeredTips.front();
            triggeredTips.emplace_front(pTriggeredTipDataPrevious, coachingTipHistory);

            // Remove oldest entry if max tips have been exceeded
            if (triggeredTips.size() > MaxTipEntries)
            {
                triggeredTips.pop_back();
            }
        }

        // Returns number of remaining TriggeredTipData
        size_t deleteOldestRecord()
        {
            AIS_LOG_DEBUG("OperatorTipHistory::deleteOldestRecord() oldest records for %s", name.c_str());

            if (!triggeredTips.empty())
            {
                triggeredTips.pop_back();
            }
            return triggeredTips.size();
        }

        uint16_t getRecordCount() const { return triggeredTips.size(); }

        template <class Archive>
        void serialize(Archive& ar, unsigned int version)
        {
            /* Archive Fields Here */
            ar & name;
            ar & priority;
            ar & category;
            ar & triggeredTips;
        }

        std::string name;
        uint32_t priority;
        CoachingTipCategory_t category;
        std::list<TriggeredTipData> triggeredTips;
    };


    // List of tips for an OperatorId
    // operatorTipHistories are sorted by priority, lower number = higher prioirty
    struct OperatorIdHistory
    {
        explicit OperatorIdHistory(const std::string& operatorId) :
            operatorId{operatorId}
        {}

        OperatorIdHistory() = default;

        void setActive()
        {
            timespec timeSpec;
            auto clockResult = clock_gettime(CLOCK_REALTIME, &timeSpec);
            if (clockResult != 0)
            {
                AIS_LOG_WARN("clock_gettime failed with errorCode %u", clockResult);
            }
            timeSpecSec = timeSpec.tv_sec;
        }

        __time_t getLastActiveTimeSpecSec() const { return timeSpecSec; }

        uint16_t getRecordCount() const
        {
            return std::accumulate(operatorTipHistories.begin(), operatorTipHistories.end(), 0,
                [] (uint16_t numRecords, const OperatorTipHistory& tips) { return numRecords + tips.getRecordCount(); });
        }

        void triggerTip(const CoachingTipResult_t& tipResult, const CoachingTipHistoryInterface& coachingTipHistory)
        {
            auto it = operatorTipHistories.begin();
            while (it != operatorTipHistories.end())
            {
                // Tip Found
                if (it->priority == tipResult.tipOutput.tipPriority)
                {
                    AIS_LOG_INFO("Tip %d-%s triggered for OperatorId %s", it->priority, it->name.c_str(), operatorId.c_str());
                    it->triggerTip(coachingTipHistory);
                    return;
                }
                // Insert Tip in priority order
                else if (it->priority > tipResult.tipOutput.tipPriority)
                {
                    break;
                }
                ++it;
            }
            it = operatorTipHistories.emplace(it, tipResult);
            AIS_LOG_INFO("New Tip %s triggered for OperatorId %s", it->name.c_str(), operatorId.c_str());
            it->triggerTip(coachingTipHistory);
        }

        // Returns number of remaining OperatorTipHistory
        size_t deleteOldestRecord()
        {
            AIS_LOG_DEBUG("OperatorIdHistory::deleteOldestRecord() size:%d, Name:%s", operatorTipHistories.size(), operatorId.c_str());
            if (!operatorTipHistories.empty())
            {
                if (operatorTipHistories.back().deleteOldestRecord() == 0)
                {
                    operatorTipHistories.pop_back();
                }
            }
            return operatorTipHistories.size();
        }

        std::string operatorId;
        __time_t timeSpecSec; // Timestamp for the last time the operator logged on
        std::list<OperatorTipHistory> operatorTipHistories;

        template <class Archive>
        void serialize(Archive& ar, unsigned int version)
        {
            /* Archive Fields Here */
            ar & operatorId;
            ar & timeSpecSec;
            ar & operatorTipHistories;
        }
    };

    // Called once at key-on to prune old records
    void checkTipHistory()
    {
        // Check for expired operators
        timespec timeSpec;
        auto clockResult = clock_gettime(CLOCK_REALTIME, &timeSpec);
        if (clockResult != 0)
        {
            AIS_LOG_WARN("clock_gettime failed with errorCode %u", clockResult);
        }
        else
        {
            uint32_t expirationSec = operatorExpirationDays * 24 * 60 * 60;
            auto timeSpecSecLimit = timeSpec.tv_sec - expirationSec;
            // Search in reverse (oldest -> newest)
            while(!operatorIdHistories.empty())
            {
                auto& oldestHistory = operatorIdHistories.back();
                auto timeSpecSec = oldestHistory.getLastActiveTimeSpecSec();
                AIS_LOG_INFO("Operator %s: timeSpecSec=%u expirationSec=%u timeSpecSecLimit=%u ", oldestHistory.operatorId.c_str(), timeSpecSec, expirationSec, timeSpecSecLimit);
                // If oldest operator has not expired, stop searching
                if (timeSpecSec >= timeSpecSecLimit)
                {
                    break;
                }
                // Delete oldest operator
                AIS_LOG_NOTICE("Deleting operator %s", oldestHistory.operatorId.c_str());
                operatorIdHistories.pop_back();
            }
        }

        // Check if max records has been exceeded
        checkRecordCount();
    }

    // Check if max records has been exceeded
    void checkRecordCount()
    {
        auto numRecords = getRecordCount();
        for (; numRecords > maxRecords; numRecords--)
        {
            AIS_LOG_DEBUG("checkRecordCount:%s numRecords=%u maxRecords=%u", operatorIdHistories.back().operatorId.c_str(), numRecords, maxRecords);
            // Delete Oldest Record, removing OperatorIdHistory if empty
            if (operatorIdHistories.back().deleteOldestRecord() == 0)
            {
                AIS_LOG_DEBUG("remove OpId:%s checkRecordCount: numRecords=%u maxRecords=%u", operatorIdHistories.back().operatorId.c_str(), numRecords, maxRecords);
                operatorIdHistories.pop_back();
            }
        }
    }

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, unsigned int version)
    {
        /* Archive Fields Here */
        ar & operatorIdHistories;
        ar & allOperatorTipHistories;

        if (version >=2)
        {
            ar & tipAutoEnableTimeSeconds;
        }
    }

// CoachingTipHistory members
    std::list<OperatorIdHistory> operatorIdHistories;
    OperatorIdHistory* pActiveOperatorIdHistory;
    OperatorIdHistory allOperatorTipHistories;  // used for PSR report

    // Current state information, not serialized
    size_t maxSavedOperators;
    size_t maxRecords;
    uint16_t operatorExpirationDays;
    double longitude;
    double latitude;
    GpsQualityType_t gpsQualityType;
    uint32_t shmSec;
    int64_t tipAutoEnableTimeSeconds;         // time before tips are automatically enabled, NVM in CoachingTipHistory

};

typedef Datum<CoachingTipHistoryStorage> CoachingTipHistory;

BOOST_CLASS_VERSION(CoachingTipHistoryStorage, 2);

#endif
