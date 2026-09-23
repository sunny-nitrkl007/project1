#ifndef LPSSATOTALSMAPPED_H
#define LPSSATOTALSMAPPED_H

#include <cstdint>
#include <string>
#include <iostream>
#include <map>
#include <chrono>
#include <stdexcept>

#include <boost/filesystem.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/map.hpp>

#include <chrono/print.hpp>

#include <boost_helpers/boost_serialization_chrono.hpp>

#include "LpsSaTotalsPrinterInfo.h"

/*
 * Mapped Totals Storage
 */
struct LpsSaTotalsMappedStorage {
public:
    using Clock = std::chrono::system_clock;
    using TimePoint = Clock::time_point;

    class Total {
    public:
        Total() :
            loadCount(0),
            passCount(0),
            weightTonnes(0.0),
            lastUpdated(TimePoint::min()) {}

        uint32_t loadCount;
        uint32_t passCount;
        double weightTonnes;
        TimePoint lastUpdated;

        inline void reset() {
            loadCount = 0;
            passCount = 0;
            weightTonnes = 0.0;
            lastUpdated = TimePoint::min();
        }

        inline void update(uint32_t numLoads, uint32_t numPasses, float weight) {
            loadCount += numLoads;
            passCount += numPasses;
            weightTonnes += weight;
            lastUpdated = Clock::now();
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version) {
            ar & loadCount;
            ar & passCount;
            ar & weightTonnes;
            ar & lastUpdated;
        }
    };

    static constexpr std::size_t MaxNumberOfItems = 500;

    std::string printHeader;
    std::map<std::string, Total> totals;
    TimePoint resetTime;

    LpsSaTotalsMappedStorage(const std::string& printHeader_) :
        printHeader(printHeader_),
        totals(),
        resetTime(TimePoint::min()) {}

    LpsSaTotalsMappedStorage() : LpsSaTotalsMappedStorage("") {};

    virtual ~LpsSaTotalsMappedStorage() = default;

    inline void reset() {
        totals.clear();
        resetTime = Clock::now();
    }

    inline void reset(const std::string& itemName) {
        totals.erase(itemName);
        // We don't change the reset time when a single item is cleared.
    }

    inline void removeOldest() {
        const std::string* pOldestItemName = nullptr;
        TimePoint oldestTimePoint = TimePoint::max();

        // Find oldest material
        for (const auto& kv : totals) {
            if (kv.second.lastUpdated < oldestTimePoint) {
                pOldestItemName = &(kv.first);
                oldestTimePoint = kv.second.lastUpdated;
            }
        }

        // Remove the oldest material
        if (nullptr != pOldestItemName) totals.erase(*pOldestItemName);
    }

    inline void update(const std::string& itemName, uint32_t numLoads, uint32_t numPasses, float weight) {
        if (totals.size() >= MaxNumberOfItems) {
            try {
                totals.at(itemName).update(numLoads, numPasses, weight);
            }
            catch (const std::out_of_range& /*e*/) {
                removeOldest();
                totals[itemName].update(numLoads, numPasses, weight);
            }

        }
        else {
            totals[itemName].update(numLoads, numPasses, weight);
        }
    }

    bool load(const boost::filesystem::path& filePath);
    bool save(const boost::filesystem::path& filePath) const;

    bool publish(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo) const;
    bool print(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo) const;

    void toJson(std::ostream& os, const std::string& fileNameStem, const LpsSaTotalsPrinterInfo* pPrinterInfo = nullptr) const;
    void toAscii(std::ostream& os, const LpsSaTotalsPrinterInfo* pPrinterInfo = nullptr) const;

protected:
    virtual void header(std::ostream& os, const LpsSaTotalsPrinterInfo& printerInfo) const = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & totals;

        if (version > 0) {
            // Reset time was added in version 1
            ar & resetTime;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const LpsSaTotalsMappedStorage& o);
};

class LpsSaTotalsMapped : public LpsSaTotalsMappedStorage {
public:
    using LpsSaTotalsMappedStorage::LpsSaTotalsMappedStorage;

protected:
    void header(std::ostream& os, const LpsSaTotalsPrinterInfo& printerInfo) const override;
};

class LpsSaDailyTotalsMapped : public LpsSaTotalsMappedStorage {
public:
    using LpsSaTotalsMappedStorage::LpsSaTotalsMappedStorage;

protected:
    void header(std::ostream& os, const LpsSaTotalsPrinterInfo& printerInfo) const override;
};

BOOST_CLASS_VERSION(LpsSaTotalsMappedStorage, 1);
BOOST_CLASS_VERSION(LpsSaTotalsMappedStorage::Total, 0);

#endif // LPSSATOTALSMAP_H
