#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/archive_exception.hpp>

// Rapid JSON
#include <ext/rapidjson/RapidJsonGuarded.h>

#include <ais/log/Logger.h>

#include <chrono/print.hpp>
#include <fileio/sha1_fstream.hpp>
#include <fileio/oflocker.hpp>

#include "LpsSaTotalsPrintUtils.h"
#include "LpsSaTotalsMaterial.h"

namespace pu = LpsSaTotalsPrintUtils;
namespace rj = rapidjson;
namespace fs = boost::filesystem;

/*
 * Load material totals from storage
 */
bool LpsSaTotalsMaterialStorage::load(const fs::path& filePath) {
    bool success = false;
    tes_common_ais::sha1_ifstream ifs{ true }; // two_copy
    ifs.open(filePath.string(), std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia >> *this;
            AIS_LOG_INFO("Loaded material totals from storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not deserialize material totals from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("Could not deserialize material totals from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (...) {
            AIS_LOG_ERROR("Could not deserialize material totals from storage, unexpected error.");
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                AIS_LOG_WARN("Material totals file was corrupt... fixed it.");
            }
            else {
                AIS_LOG_ERROR("Material totals file was corrupt... could not fix it.");
            }
        }
    }
    else {
        AIS_LOG_ERROR("Material totals could not be opened from storage.");
    }

    if (!success) {
        totals.clear();
        resetTime = TimePoint::min();
    }

    return success;
}

/*
 * Save material totals to storage
 */
bool LpsSaTotalsMaterialStorage::save(const fs::path& filePath) const {
    bool success = false;
    tes_common_ais::sha1_ofstream ofs{ true }; // two_copy
    ofs.open(filePath.string(), std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Read the file in
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa << *this;
            AIS_LOG_INFO("Saved material totals to storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not serialize material totals to storage.");
            AIS_LOG_ERROR(e.what());
        }

        ofs.close();
    }
    else {
        AIS_LOG_ERROR("Material totals could not be opened from storage.");
    }

    return success;
}

/*
 * Publish to file
 */
bool LpsSaTotalsMaterialStorage::publish(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo) const {
    bool success = false;

    { // Write to the file.
        tes_common_ais::OFlocker ofl(filePath);
        if (ofl) {
            toJson(ofl.ofstream(), &printerInfo);
            ofl.close();
            success = true;
            AIS_LOG_INFO("Material totals: published JSON file.");
        }
        else {
            AIS_LOG_ERROR("Material totals: file could not be opened and locked for publishing.");
        }
    }

    if (!success) {
        try {
            if (boost::filesystem::is_regular_file(filePath)) {
                boost::filesystem::remove(filePath);
                AIS_LOG_WARN("Material totals: file removed.");
            }
        }
        catch (const boost::filesystem::filesystem_error& e) {
            AIS_LOG_WARN("Material totals: file could not be removed.");
        }
    }

    return success;
}

/*
 * Print to file
 */
bool LpsSaTotalsMaterialStorage::print(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo) const {
    bool success = false;

    { // Write to the file.
        tes_common_ais::OFlocker ofl(filePath);
        if (ofl) {
            toAscii(ofl.ofstream(), &printerInfo);
            ofl.close();
            success = true;
            AIS_LOG_INFO("Material totals: printed ASCII file.");
        }
        else {
            AIS_LOG_ERROR("Material totals: file could not be opened and locked for publishing.");
        }
    }

    if (!success) {
        try {
            if (boost::filesystem::is_regular_file(filePath)) {
                boost::filesystem::remove(filePath);
                AIS_LOG_WARN("Material totals: file removed.");
            }
        }
        catch (const boost::filesystem::filesystem_error& e) {
            AIS_LOG_WARN("Material totals: file could not be removed.");
        }
    }

    return success;
}

/*
 * Convert to JSON
 */
void LpsSaTotalsMaterialStorage::toJson(std::ostream& os, const LpsSaTotalsPrinterInfo* pPrinterInfo) const {
    rj::StringBuffer sb;
    rj::Writer<rj::StringBuffer> writer(sb);

    writer.SetMaxDecimalPlaces(3);
    writer.StartObject();

    // File Name
    writer.Key("fileName");
    writer.String("MaterialTotals");

    // Start Date
    writer.Key("startDate");
    if (resetTime > TimePoint::min()) {
        const LpsSaTotalsPrinterInfo& printerInfo = (nullptr == pPrinterInfo) ? defaultPrinterInfo : *pPrinterInfo;
        writer.String(tes_common_ais::putLocalTime(resetTime, printerInfo.dateFormatString()));
    }
    else {
        writer.String("");
    }

    // Totals
    writer.Key("totals");
    writer.StartArray();
    for (const auto& kv : totals) {
        writer.StartObject();
        writer.Key("name");
        writer.String(kv.first);
        writer.Key("weight");
        writer.Double(kv.second.weightTonnes);
        writer.EndObject();
    }
    writer.EndArray();

    writer.EndObject();

    if (writer.IsComplete()) {
        os << sb.GetString();
    }
}

/*
 * Print to ASCII based on printer settings.
 */
void LpsSaTotalsMaterialStorage::toAscii(std::ostream& os, const LpsSaTotalsPrinterInfo* pPrinterInfo) const {
    using tes_common_ais::putLocalTime;

    const LpsSaTotalsPrinterInfo& printerInfo = (nullptr == pPrinterInfo) ? defaultPrinterInfo : *pPrinterInfo;

    uint8_t leadingBlankLines = std::min(printerInfo.config.leadingBlankLines, uint8_t(3));
    uint8_t trailingBlankLines = std::min(printerInfo.config.trailingBlankLines, uint8_t(3));
    bool resetTimeEnabled = printerInfo.config.materialReport.resetTimeEnabled;

    // Leading blank lines
    for (uint8_t ii = 0; ii < leadingBlankLines; ++ii) {
        os << "\n";
    }

    { // Report title
        std::string str("REPORT BY MATERIAL");
        pu::centerString(str, 36);
        os << str << "\n";
    }

    // Date info
    if (resetTimeEnabled) {
        os << "Date Range\n";
        if (resetTime > TimePoint::min()) {
            os << "  Start: " << putLocalTime(resetTime, printerInfo.dateTimeFormatString()) << "\n";
        }
        else {
            os << "  Start: --:-- ---------\n";
        }

        TimePoint now = Clock::now();
        os <<     "    End: " << putLocalTime(now, printerInfo.dateTimeFormatString()) << "\n";
    }
    else {
        TimePoint now = Clock::now();
        os << "Reported: " << putLocalTime(now, printerInfo.dateTimeFormatString()) << "\n";
    }

    // Blank line
    os << "\n";

    // Total loaded weight and load count
    std::string totalWeightStr;
    std::string totalLoadCountStr;
    {
        double totalWeight = 0.0;
        uint32_t totalLoadCount = 0;

        for (const auto& kv : totals) {
            totalWeight += kv.second.weightTonnes;
            totalLoadCount += kv.second.loadCount;
        }

        totalWeightStr = printerInfo.weightToString(totalWeight);
        totalLoadCountStr = pu::uintToString(totalLoadCount);
    }

    os << "Total Loaded: " << totalWeightStr << " " << printerInfo.weightUnitsString() << "\n";
    os << "Number of Loads: " << totalLoadCountStr << "\n";

    // Blank line
    os << "\n";

    { // Column headers
        std::string str1("Material");
        std::string str2(printerInfo.weightUnitsString());
        pu::rightPadString(str1, 36 - str2.length());
        os << str1 << str2 << "\n";
    }

    uint32_t ii = 1;
    for (const auto& kv : totals) {
        // Material                      tonnes
        // #000 Material Name ABCDEF fffffff.ff

        std::string iiStr = pu::uintToString(ii, 3, '0');

        std::string nameStr = kv.first;
        pu::rightPadString(nameStr, 20); // Maximum 20 characters

        std::string weightStr = printerInfo.weightToString(kv.second.weightTonnes, 10);

        os << "#" << iiStr << " " << nameStr << " " << weightStr << "\n";

        ++ii;
    }

    // Trailing blank lines
    for (uint8_t ii = 0; ii < trailingBlankLines; ++ii) {
        os << "\n";
    }
}

/*
 * Make material totals printable to text.
 */
std::ostream& operator<<(std::ostream& os, const LpsSaTotalsMaterialStorage& o) {
    o.toAscii(os);
    return os;
}
