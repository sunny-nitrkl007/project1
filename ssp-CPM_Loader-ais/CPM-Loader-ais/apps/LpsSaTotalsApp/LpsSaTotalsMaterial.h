#ifndef LPSSATOTALSMATERIAL_H
#define LPSSATOTALSMATERIAL_H

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
 * Material Totals Storage
 */
struct LpsSaTotalsMaterialStorage {
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

    std::map<std::string, Total> totals;
    TimePoint resetTime;

    LpsSaTotalsMaterialStorage() :
        totals(), resetTime(TimePoint::min()) {}

    inline void reset() {
        totals.clear();
        resetTime = Clock::now();
    }

    inline void reset(const std::string& materialName) {
        totals.erase(materialName);
        // We don't change the reset time when a single material is cleared.
    }

    inline void removeOldest() {
        const std::string* pOldestMaterialName = nullptr;
        TimePoint oldestTimePoint = TimePoint::max();

        // Find oldest material
        for (const auto& kv : totals) {
            if (kv.second.lastUpdated < oldestTimePoint) {
                pOldestMaterialName = &(kv.first);
                oldestTimePoint = kv.second.lastUpdated;
            }
        }

        // Remove the oldest material
        if (nullptr != pOldestMaterialName) totals.erase(*pOldestMaterialName);
    }

    inline void update(const std::string& materialName, uint32_t numLoads, uint32_t numPasses, float weight) {
        if (totals.size() >= 500) {
            try {
                totals.at(materialName).update(numLoads, numPasses, weight);
            }
            catch (const std::out_of_range& /*e*/) {
                removeOldest();
                totals[materialName].update(numLoads, numPasses, weight);
            }

        }
        else {
            totals[materialName].update(numLoads, numPasses, weight);
        }
    }

    bool load(const boost::filesystem::path& filePath);
    bool save(const boost::filesystem::path& filePath) const;

    bool publish(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo) const;
    bool print(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo) const;

    void toJson(std::ostream& os, const LpsSaTotalsPrinterInfo* pPrinterInfo = nullptr) const;
    void toAscii(std::ostream& os, const LpsSaTotalsPrinterInfo* pPrinterInfo = nullptr) const;

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

    friend std::ostream& operator<<(std::ostream& os, const LpsSaTotalsMaterialStorage& o);
};

BOOST_CLASS_VERSION(LpsSaTotalsMaterialStorage, 1);
BOOST_CLASS_VERSION(LpsSaTotalsMaterialStorage::Total, 0);

#endif // LPSSATOTALSMATERIAL_H
