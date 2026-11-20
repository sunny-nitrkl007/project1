#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/archive_exception.hpp>

#include <ais/log/Logger.h>

#include <chrono/print.hpp>
#include <fileio/sha1_fstream.hpp>
#include <fileio/oflocker.hpp>

#include "LpsSaTotalsPrinterInfo.h"
#include "LpsSaTotalsLoadHistory.h"

namespace pu = LpsSaTotalsPrintUtils;
namespace fs = boost::filesystem;

/*
 * Load load history from storage
 */
bool LpsSaTotalsLoadHistoryStorage::load(const fs::path& filePath) {
    bool success = false;
    tes_common_ais::sha1_ifstream ifs{ true }; // two_copy
    ifs.open(filePath.string(), std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia >> *this;
            AIS_LOG_INFO("Loaded load history from storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not deserialize load history from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("Could not deserialize load history from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (...) {
            AIS_LOG_ERROR("Could not deserialize load history from storage, unexpected error.");
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                AIS_LOG_WARN("Load history file was corrupt... fixed it.");
            }
            else {
                AIS_LOG_ERROR("Load history file was corrupt... could not fix it.");
            }
        }
    }
    else {
        AIS_LOG_ERROR("Load history could not be opened from storage.");
    }

    if (!success) {
        loads.clear();
        resetTime = TimePoint::min();
    }

    return success;
}

/*
 * Save load history to storage
 */
bool LpsSaTotalsLoadHistoryStorage::save(const fs::path& filePath) const {
    bool success = false;
    tes_common_ais::sha1_ofstream ofs{ true }; // two_copy
    ofs.open(filePath.string(), std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Read the file in
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa << *this;
            AIS_LOG_INFO("Saved load history to storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not serialize load history to storage.");
            AIS_LOG_ERROR(e.what());
        }

        ofs.close();
    }
    else {
        AIS_LOG_ERROR("Load history could not be opened from storage.");
    }

    return success;
}

/*
 * Print to file
 */
bool LpsSaTotalsLoadHistoryStorage::print(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo, bool daily ) const {
    bool success = false;

    { // Write to the file.
        tes_common_ais::OFlocker ofl(filePath);
        if (ofl) {
            toAscii(ofl.ofstream(), &printerInfo, daily);
            ofl.close();
            success = true;
            AIS_LOG_INFO("Load history: printed ASCII file.");
        }
        else {
            AIS_LOG_ERROR("Load history: file could not be opened and locked for publishing.");
        }
    }

    if (!success) {
        try {
            if (boost::filesystem::is_regular_file(filePath)) {
                boost::filesystem::remove(filePath);
                AIS_LOG_WARN("Load history: file removed.");
            }
        }
        catch (const boost::filesystem::filesystem_error& e) {
            AIS_LOG_WARN("Load history: file could not be removed.");
        }
    }

    return success;
}

/*
 * Print to ASCII based on printer settings.
 */
void LpsSaTotalsLoadHistoryStorage::toAscii(std::ostream& os, const LpsSaTotalsPrinterInfo* pPrinterInfo, bool daily) const {
    using tes_common_ais::putLocalTime;
    const LpsSaTotalsPrinterInfo& printerInfo = (nullptr == pPrinterInfo) ? defaultPrinterInfo : *pPrinterInfo;

    uint8_t leadingBlankLines = std::min(printerInfo.config.leadingBlankLines, uint8_t(3));
    uint8_t trailingBlankLines = std::min(printerInfo.config.trailingBlankLines, uint8_t(3));
    bool resetTimeEnabled = printerInfo.config.truckReport.resetTimeEnabled;

    // Leading blank lines
    for (uint8_t ii = 0; ii < leadingBlankLines; ++ii) {
        os << "\n";
    }

    { // Report title
        std::string title("REPORT BY TRUCK");

        if (daily) {
            title = "DAILY REPORT BY TRUCK";
        }

        pu::centerString(title, 36);
        os << title << "\n";
    }

    // Date info
    if (daily) {
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
    else if (resetTimeEnabled) {
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

    // Total loaded weight
    std::string totalWeightStr;
    {
        double totalWeight = 0.0;

        for (const auto& load : loads) {
            totalWeight += load.weightTonnes;
        }

        totalWeightStr = printerInfo.weightToString(totalWeight);
    }
    os << "Total Loaded: " << totalWeightStr << " " << printerInfo.weightUnitsString() << "\n";

    // Number of loads
    os << "Number of Loads: " << pu::uintToString(loads.size()) << "\n";

    // Blank line
    os << "\n";

    // Create units string padded to 8 characters
    std::string unitsStr = printerInfo.weightUnitsString();
    pu::leftPadString(unitsStr, 8);


    // Column headers
    // Time - HH:MM       - 5 Characters
    //                      1 Space
    // Date - DDMMM       - 5 Characters
    //                      2 Spaces
    // Weight - %5.2f     - 8 Characters Max
    //                      2 Spaces
    // Passes - uint      - 3 Characters Max
    //                      2 Spaces
    // Material Id - uint - 3 Characters Max
    //                      2 Spaces
    // Truck Id - uint    - 3 Characters Max
    //                      ----------------
    //                      36 Characters
    os << "                        Truck Id __ \n";
    os << "                Material Id __     |\n";
    os << "                Passes __     |    |\n";
    os << "Time  Date   " <<  unitsStr  << "    |    |    |\n";
    //    "HH:MM DD-MM  #####.##  ###  ###  ###\n"

    for (const auto& load : loads) {
        // Get weight
        std::string weightStr = printerInfo.weightToString(load.weightTonnes, 8);

        // Get passes
        std::string passesStr = pu::uintToString(load.passCount, 3);

        // Get material id
        std::string materialIdStr = pu::uintToString(load.materialId, 3);

        // Get truck id
        std::string truckIdStr = pu::uintToString(load.truckId, 3);

        os << putLocalTime(load.storeTime, printerInfo.dateTimeFormatStringShort()) << "  ";
        os << weightStr << "  ";
        os << passesStr << "  ";
        os << materialIdStr << "  ";
        os << truckIdStr << "\n";
    }

    // Blank Line:
    os << "\n";

    // Truck ID   - 3 Characters Max
    //              2 spaces
    // Truck Name - 31 Characters(36-3-2 = 31)
    os << " ID  Truck Name" << "\n";

    { // Build truck name map.
    	std::map<uint32_t, std::string> tempMap;
    	for (const auto& load : loads) {
    		tempMap.emplace(load.truckId, load.truckName);
    	}
    	for (auto& x: tempMap) {
    		os << pu::uintToString(x.first, 3) << "  " << x.second << "\n";
    	}
    }

    // Blank Line:
    os << "\n";

    // Material ID   - 3 Characters Max
    //                 2 spaces
    // Material Name - 31 Characters(36-3-2 = 31)
    os << " ID  Material Name" << "\n";

    { // Build material name map.
    	std::map<uint32_t, std::string> tempMap;
        for (const auto& load : loads) {
        	tempMap.emplace(load.materialId, load.materialName);
        }
        for (auto& x: tempMap) {
        	os << pu::uintToString(x.first, 3) << "  " << x.second << "\n";
        }
    }

    // Trailing blank lines
    for (uint8_t ii = 0; ii < trailingBlankLines; ++ii) {
        os << "\n";
    }
}

/*
 * Make load history printable to text.
 */
std::ostream& operator<<(std::ostream& os, const LpsSaTotalsLoadHistoryStorage& o) {
    o.toAscii(os);
    return os;
}
