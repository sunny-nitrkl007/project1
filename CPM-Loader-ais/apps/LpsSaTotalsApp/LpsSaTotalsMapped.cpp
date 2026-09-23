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
#include "LpsSaTotalsMapped.h"

namespace pu = LpsSaTotalsPrintUtils;
namespace rj = rapidjson;
namespace fs = boost::filesystem;

/*
 * Load material totals from storage
 */
bool LpsSaTotalsMappedStorage::load(const fs::path& filePath) {
    bool success = false;
    tes_common_ais::sha1_ifstream ifs{ true }; // two_copy
    ifs.open(filePath.string(), std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia >> *this;
            AIS_LOG_INFO("Loaded %s from storage.", filePath.filename().c_str());
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not deserialize %s from storage.", filePath.filename().c_str());
            AIS_LOG_ERROR(e.what());
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("Could not deserialize %s from storage.", filePath.filename().c_str());
            AIS_LOG_ERROR(e.what());
        }
        catch (...) {
            AIS_LOG_ERROR("Could not deserialize %s from storage, unexpected error.", filePath.filename().c_str());
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                AIS_LOG_WARN("%s file was corrupt... fixed it.", filePath.filename().c_str());
            }
            else {
                AIS_LOG_ERROR("%s file was corrupt... could not fix it.", filePath.filename().c_str());
            }
        }
    }
    else {
        AIS_LOG_ERROR("%s could not be opened from storage.", filePath.filename().c_str());
    }

    if (!success) {
        totals.clear();
        resetTime = TimePoint::min();
    }

    return success;
}

/*
 * Save map totals to storage
 */
bool LpsSaTotalsMappedStorage::save(const fs::path& filePath) const {
    bool success = false;
    tes_common_ais::sha1_ofstream ofs{ true }; // two_copy
    ofs.open(filePath.string(), std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Read the file in
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa << *this;
            AIS_LOG_INFO("Saved %s to storage.", filePath.filename().c_str());
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not serialize %s to storage.", filePath.filename().c_str());
            AIS_LOG_ERROR(e.what());
        }

        ofs.close();
    }
    else {
        AIS_LOG_ERROR("%s could not be opened from storage.", filePath.filename().c_str());
    }

    return success;
}

/*
 * Publish to file
 */
bool LpsSaTotalsMappedStorage::publish(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo) const {
    bool success = false;

    { // Write to the file.
        tes_common_ais::OFlocker ofl(filePath);
        if (ofl) {
            toJson(ofl.ofstream(), filePath.stem().string(), &printerInfo);
            ofl.close();
            success = true;
            AIS_LOG_INFO("%s: published JSON file.", filePath.filename().c_str());
        }
        else {
            AIS_LOG_ERROR("%s: file could not be opened and locked for publishing.", filePath.filename().c_str());
        }
    }

    if (!success) {
        try {
            if (boost::filesystem::is_regular_file(filePath)) {
                boost::filesystem::remove(filePath);
                AIS_LOG_WARN("%s: file removed.", filePath.filename().c_str());
            }
        }
        catch (const boost::filesystem::filesystem_error& e) {
            AIS_LOG_WARN("%s: file could not be removed.", filePath.filename().c_str());
        }
    }

    return success;
}

/*
 * Print to file
 */
bool LpsSaTotalsMappedStorage::print(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo) const {
    bool success = false;

    { // Write to the file.
        tes_common_ais::OFlocker ofl(filePath);
        if (ofl) {
            toAscii(ofl.ofstream(), &printerInfo);
            ofl.close();
            success = true;
            AIS_LOG_INFO("%s: printed ASCII file.", filePath.filename().c_str());
        }
        else {
            AIS_LOG_ERROR("%s: file could not be opened and locked for publishing.", filePath.filename().c_str());
        }
    }

    if (!success) {
        try {
            if (boost::filesystem::is_regular_file(filePath)) {
                boost::filesystem::remove(filePath);
                AIS_LOG_WARN("%s: file removed.", filePath.filename().c_str());
            }
        }
        catch (const boost::filesystem::filesystem_error& e) {
            AIS_LOG_WARN("%s: file could not be removed.", filePath.filename().c_str());
        }
    }

    return success;
}

/*
 * Convert to JSON
 */
void LpsSaTotalsMappedStorage::toJson(std::ostream& os, const std::string& fileNameStem, const LpsSaTotalsPrinterInfo* pPrinterInfo) const {
    rj::StringBuffer sb;
    rj::Writer<rj::StringBuffer> writer(sb);

    writer.SetMaxDecimalPlaces(3);
    writer.StartObject();

    // File Name
    writer.Key("fileName");
    writer.String(fileNameStem);

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
void LpsSaTotalsMappedStorage::toAscii(std::ostream& os, const LpsSaTotalsPrinterInfo* pPrinterInfo) const {
    const LpsSaTotalsPrinterInfo& printerInfo = (nullptr == pPrinterInfo) ? defaultPrinterInfo : *pPrinterInfo;

    uint8_t leadingBlankLines = std::min(printerInfo.config.leadingBlankLines, uint8_t(3));
    uint8_t trailingBlankLines = std::min(printerInfo.config.trailingBlankLines, uint8_t(3));

    // Leading blank lines
    for (uint8_t ii = 0; ii < leadingBlankLines; ++ii) {
        os << "\n";
    }

    // Fill in report header information
    header(os, printerInfo);

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
        std::string str1(printHeader);
        std::string str2(printerInfo.weightUnitsString());
        pu::rightPadString(str1, 36 - str2.length());
        os << str1 << str2 << "\n";
    }

    uint32_t ii = 1;
    for (const auto& kv : totals) {
        // Item                          tonnes
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

void LpsSaTotalsMapped::header(std::ostream& os, const LpsSaTotalsPrinterInfo& printerInfo) const {
    using tes_common_ais::putLocalTime;

    bool resetTimeEnabled = printerInfo.config.materialReport.resetTimeEnabled; // Just use this setting here

    { // Report title
        std::string temp = "REPORT BY " + printHeader;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        std::string str(temp);
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
}

void LpsSaDailyTotalsMapped::header(std::ostream& os, const LpsSaTotalsPrinterInfo& printerInfo) const {
    using tes_common_ais::putLocalTime;

    { // Report title
        std::string temp = "DAILY REPORT BY " + printHeader;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        std::string str(temp);
        pu::centerString(str, 36);
        os << str << "\n";
    }

    // Date info
    os << "Date: ";
    if (resetTime > TimePoint::min()) {
        os << putLocalTime(resetTime, printerInfo.dateFormatString()) << "\n";
    }
    else {
        os << "---------\n";
    }

    TimePoint now = Clock::now();
    os << "Reported: " << putLocalTime(now, printerInfo.dateTimeFormatString()) << "\n";
}

/*
 * Make map totals printable to text.
 */
std::ostream& operator<<(std::ostream& os, const LpsSaTotalsMappedStorage& o) {
    o.toAscii(os);
    return os;
}
