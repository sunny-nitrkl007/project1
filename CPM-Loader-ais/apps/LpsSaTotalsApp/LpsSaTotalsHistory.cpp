/*
 * LpsSaTotalsHistory.cpp
 *
 *  Created on: May 17, 2022
 *      Author: pf
 */
#include <algorithm>

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

#include "LpsSaTotalsPrinterInfo.h"
#include "LpsSaTotalsPrintUtils.h"
#include "LpsSaTotalsHistory.h"

namespace pu = LpsSaTotalsPrintUtils;
namespace rj = rapidjson;
namespace fs = boost::filesystem;

static std::string makeFileName(const std::string& productId, const std::chrono::system_clock::time_point& utcTime);

static std::string fixTicketId(const std::string& ticketId_);
static bool isTicketIdValid(const std::string& ticketId_);
static uint32_t getTicketNumberFromTicketId(const std::string& ticketId_);

static std::chrono::system_clock::time_point parseDateFromFileName(const std::string& fileName, std::tm* pTmStruct = nullptr);

static int addTicketsToJson(rj::Writer<rj::StringBuffer>& writer, const LpsSaTotalsHistoryStorage& loadHistory,
        const std::chrono::system_clock::time_point& startUtcTime, const std::chrono::system_clock::time_point& endUtcTime,
        const LpsSaTotalsPrinterInfo& printerInfo);

/*
 * Load totals history from storage
 */
bool LpsSaTotalsHistoryStorage::load(const fs::path& filePath) {
    bool success = false;
    tes_common_ais::sha1_ifstream ifs{ false }; // one copy
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
        loads.clear();
    }

    return success;
}

/*
 * Save totals history to storage
 */
bool LpsSaTotalsHistoryStorage::save(const fs::path& filePath) const {
    bool success = false;
    tes_common_ais::sha1_ofstream ofs{ false }; // one copy
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
 * Convert to CSV
 */
void LpsSaTotalsHistoryStorage::toCsv(std::ostream& os, const LpsSaTotalsPrinterInfo& printerInfo) const {

    { // Reported time
        auto now = std::chrono::system_clock::now();
        os << "Reported (UTC)," << tes_common_ais::putTime(now, "%F %T") << "\n";
    }

    os << "Time (UTC),";
    os << "Time (local),";
    os << "Ticket Number,";
    os << "Total Passes,";
    os << "Total Weight (" << printerInfo.weightUnitsString() << "),";
    os << "Material,";
    os << "Truck,";
    os << "Custom 1,";
    os << "Custom 2,";
    os << "Custom 3,";
    os << "Custom 4,";
    os << "Target Weight (" << printerInfo.weightUnitsString() << "),";
    os << "Pass Weights (" << printerInfo.weightUnitsString() << ")\n";

    for (const auto& load : loads) {
        auto subtotalCount = load.subtotalCount();
        for (decltype(load.subtotalCount()) ii = 1; ii <= subtotalCount; ++ii) {
            const auto& subtotal = load.getSubtotalByIndex(ii);

            // End Time (UTC)
            os << tes_common_ais::putTime(subtotal.endTime.utcTime, "%F %T") << ",";

            // End Time (local)
            os << tes_common_ais::putLocalTime(subtotal.endTime.utcTime, "%F %T") << ",";

            // Ticket Number
            os << pu::uintToString(load.ticketNumber()) << ",";

            // Total Passes
            os << pu::uintToString(subtotal.passCount()) << ",";

            // Total Weight
            os << printerInfo.weightToString(subtotal.weightTonnes()) << ",";

            // Material Name
            if (pu::stringContains(subtotal.materialName, ',')) {
                os << R"(")" << pu::stringReplaceAll(subtotal.materialName, R"(")", R"("")") << R"(",)";
            }
            else {
                os << subtotal.materialName << ",";
            }

            // Truck Name
            if (pu::stringContains(subtotal.truckName, ',')) {
                os << R"(")" << pu::stringReplaceAll(subtotal.truckName, R"(")", R"("")") << R"(",)";
            }
            else {
                os << subtotal.truckName << ",";
            }

            { // Custom Tag 1
                std::string custom1 = (!subtotal.customListName1.empty()) ? (subtotal.customListName1 + ": " + subtotal.tag1) : subtotal.tag1;
                if (pu::stringContains(custom1, ',')) {
                    os << R"(")" << pu::stringReplaceAll(custom1, R"(")", R"("")") << R"(",)";
                }
                else {
                    os << custom1 << ",";
                }
            }

            { // Custom Tag 2
                std::string custom2 = (!subtotal.customListName2.empty()) ? (subtotal.customListName2 + ": " + subtotal.tag2) : subtotal.tag2;
                if (pu::stringContains(custom2, ',')) {
                    os << R"(")" << pu::stringReplaceAll(custom2, R"(")", R"("")") << R"(",)";
                }
                else {
                    os << custom2 << ",";
                }
            }

            { // Custom Tag 3
                std::string custom3 = (!subtotal.customListName3.empty()) ? (subtotal.customListName3 + ": " + subtotal.tag3) : subtotal.tag3;
                if (pu::stringContains(custom3, ',')) {
                    os << R"(")" << pu::stringReplaceAll(custom3, R"(")", R"("")") << R"(",)";
                }
                else {
                    os << custom3 << ",";
                }
            }

            { // Custom Tag 4
                std::string custom4 = (!subtotal.customListName4.empty()) ? (subtotal.customListName4 + ": " + subtotal.tag4) : subtotal.tag4;
                if (pu::stringContains(custom4, ',')) {
                    os << R"(")" << pu::stringReplaceAll(custom4, R"(")", R"("")") << R"(")"; // No comma here.
                }
                else {
                    os << custom4 << ",";
                }
            }

            // Target Weight
            os << printerInfo.weightToString(subtotal.truckTargetWeightTonnes); // No comma here.

            // Pass Weights
            for (const auto& pass : subtotal.passes()) {
                os << "," << printerInfo.weightToString(pass.weightTonnes);
            }

            os << "\n";
        }
    }
}

bool LpsSaTotalsHistoryManager::addLoad(const LpsSaLoadRecordChannelStorage& loadRecord) {
    bool success = false;

    // Make space for more data and 2 new files.  We may not need it all.
    if (updateStorageSpace(MIN_RESERVED_STORAGE_SIZE_BYTES, FILES_PER_DAY)) {
        // This is the end time of the last subtotal
        auto utcTime = loadRecord.getCurrentSubtotal().endTime.utcTime;

        /*
        { // For testing, we are going to back date
            static int backDateDays = 366*7;

            utcTime -= std::chrono::duration<int, std::ratio<86400>>(backDateDays);

            if (backDateDays > 0) {
                --backDateDays;
            }
        }
        */

        // Create the file path
        boost::filesystem::path filePath = storagePath_ / makeFileName(loadRecord.productId(), utcTime);

        // Load the existing file, add the new load record, save the file.
        LpsSaTotalsHistoryStorage loadHistory;
        loadHistory.load(filePath);
        loadHistory.loads.push_back(loadRecord);
        loadHistory.save(filePath);
        success = true;
    }

    fileNameCache_.clear();

    return success;
}

bool LpsSaTotalsHistoryManager::updateStorageSpace(long newFileSize, uint16_t newFileCount) {
    std::clock_t startCpuTime = std::clock();
    auto startTime = std::chrono::high_resolution_clock::now();

    // Using a multimap here just in case multiple files have the same
    // modification time.  This case was seen during testing when all
    // files were created at once.
    typedef std::multimap<std::time_t, std::pair<std::string, long> > FileMap;
    FileMap fileMap;
    long totalSize = 0;

    if (newFileSize <= 0) {
        newFileSize = 0;
    }

    try { // Index the storage directory
        struct stat fstat;
        for (boost::filesystem::directory_iterator it(storagePath_); it != boost::filesystem::directory_iterator(); ++it) {
            try {
                const boost::filesystem::directory_entry& de = *it;
                if (boost::filesystem::is_regular_file(de.status())) {
                    if (stat(de.path().c_str(), &fstat) >= 0) {
                        fileMap.emplace(fstat.st_mtim.tv_sec, FileMap::mapped_type(de.path().filename().string(), fstat.st_size));
                        totalSize += fstat.st_size;
                    }
                    else {
                        AIS_LOG_WARN("Cannot get file size of %s", de.path().c_str());
                    }
                }
                else {
                    AIS_LOG_NOTICE("%s is not a regular file", de.path().c_str());
                }
            }
            catch (const boost::filesystem::filesystem_error& e) {
                AIS_LOG_ERROR(e.what());
            }
        }
    }
    catch (const boost::filesystem::filesystem_error& e) {
        AIS_LOG_ERROR(e.what());
        percentStorageUsed_ = 100.f;
        return false;
    }

    auto numFiles = fileMap.size() + newFileCount;
    auto maxFiles = maxStorageFiles_;
    AIS_LOG_NOTICE("Need to store %d files, maximum is %d", numFiles, maxFiles);

    { // Remove files until we have enough space.
        FileMap::const_iterator it = fileMap.cbegin();
        FileMap::const_iterator endIt = fileMap.cend();
        while (numFiles > maxFiles) {
            if (it == endIt) {
                // No more files to delete
                break;
            }

            try {
                // Delete the file
                boost::filesystem::remove(storagePath_ / it->second.first);
                totalSize -= it->second.second;
                --numFiles;
                AIS_LOG_NOTICE("Deleted file %s, %d files, %ji bytes remaining", it->second.first.c_str(), numFiles, totalSize);
            }
            catch (const boost::filesystem::filesystem_error& e) {
                AIS_LOG_ERROR(e.what());
            }

            ++it;
        }
    }

    std::clock_t endCpuTime = std::clock();
    auto endTime = std::chrono::high_resolution_clock::now();

    { // Log the time it took
        double elapsedCpuTime = 1000.0 * (endCpuTime - startCpuTime) / CLOCKS_PER_SEC;
        AIS_LOG_NOTICE("Took %f milliseconds of CPU time to make space for new files.", elapsedCpuTime);

        double elapsedTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
        AIS_LOG_NOTICE("Took %f milliseconds of wall clock time to make space to new files.", elapsedTime);
    }

    // Log the space capacity and availability, calculate used space.
    auto storageUsed = totalSize + newFileSize;
    auto storageAvailable = maxStorageSize_;

    try {
        boost::filesystem::space_info s = boost::filesystem::space(storagePath_);
        AIS_LOG_NOTICE("Storage capacity: %ju", s.capacity);
        AIS_LOG_NOTICE("Storage free: %ju", s.free);
        AIS_LOG_NOTICE("Storage available: %ju", s.available);
        storageAvailable = std::min(storageAvailable, long(s.available) + storageUsed);
    }
    catch (const boost::filesystem::filesystem_error& e) {
        AIS_LOG_ERROR(e.what());
    }

    AIS_LOG_NOTICE("Need to use %ji bytes, maximum is %ji", storageUsed, storageAvailable);

    bool haveSpace;

    if (numFiles > maxFiles) {
        AIS_LOG_ERROR("Limit reached for maximum number of files, %d.", maxFiles);
        haveSpace = false;
    }
    else if (storageUsed > storageAvailable) {
        AIS_LOG_ERROR("Limit reached for maximum amount of memory, %ji", storageAvailable);
        haveSpace = false;
    }
    else {
        haveSpace = true;
    }

    // How much memory is available for the next load.
    percentStorageUsed_ = 100.f * float(storageUsed + MIN_RESERVED_STORAGE_SIZE_BYTES) / float(storageAvailable);
    AIS_LOG_NOTICE("Percent Storage Used: %f", percentStorageUsed_);

    return haveSpace;
}

bool LpsSaTotalsHistoryManager::publishTicketHistory(const boost::filesystem::path& destFilePath,
        const LpsSaTotalsPrinterInfo& printerInfo,
        const std::string& productId,
        const std::string& localDate, int direction) const {

    if (fileNameCache_.empty()) {
        // Fill up the cache...
        for (Iterator it = iteratorAll(); it != it.end(); ++it) {
            fileNameCache_.push_back(it.getPath().filename().string());
        }

        // Sort the filename list for searching later
        std::sort(fileNameCache_.begin(), fileNameCache_.end());
    }

    std::tm tmLocal;
    if (localDate.length() > 0) {
        if (!tes_common_ais::parseDateISO8601(localDate, tmLocal)) {
            AIS_LOG_ERROR("Could not local date: %s", localDate.c_str());
            return false; // Failed!
        }
    }
    else {
        // Get today
        auto now = std::chrono::system_clock::now();
        if (!tes_common_ais::getLocalCalendarTimeFromTimePoint(now, tmLocal)) {
            AIS_LOG_ERROR("Could not get local calendar time.");
            return false; // Failed!
        }
    }

    // Go to the beginning of the day.
    tmLocal.tm_hour = 0;
    tmLocal.tm_min = 0;
    tmLocal.tm_sec = 0;

    // Move the the next or previous day.
    if (direction > 0) {
        tmLocal.tm_mday += 1;
    }
    else if (direction < 0) {
        tmLocal.tm_mday -= 1;
    }

    tmLocal.tm_isdst = -1; // Determine if DST was in effect when converting time point
    auto startUtcTime = tes_common_ais::getTimePointFromLocalCalendarTime(tmLocal);

    if (startUtcTime <= startUtcTime.min()) {
        AIS_LOG_ERROR("Unable to find start time.");
        return false; // Failed!
    }

    // Increment by one day on the local calendar
    std::tm tmLocalNext = tmLocal;
    tmLocalNext.tm_mday += 1;
    tmLocalNext.tm_isdst = -1; // Determine if DST was in effect when converting time point
    auto endUtcTime = tes_common_ais::getTimePointFromLocalCalendarTime(tmLocalNext);

    if (endUtcTime <= endUtcTime.min()) {
        AIS_LOG_ERROR("Unable to find end time.");
        return false; // Failed!
    }

    rj::StringBuffer sb;
    rj::Writer<rj::StringBuffer> writer(sb);

    writer.SetMaxDecimalPlaces(3);
    writer.StartObject();

    // File Name
    writer.Key("fileName");
    writer.String("TicketHistory");

    // Tickets
    writer.Key("tickets");
    writer.StartArray();

    bool nextAvailable;
    bool previousAvailable;
    bool alreadySkippedDays = false;
    LpsSaTotalsHistoryStorage loadHistory;

    decltype(fileNameCache_)::const_iterator startIter;
    decltype(fileNameCache_)::const_iterator endIter;

    // Loop through each file and load it, then loop through each ticket and serialize it into the json.
    do {
        bool foundSome = false;
        nextAvailable = false;
        previousAvailable = false;

        // Create the start and end file names from the current product id and the time range
        auto startFileName = makeFileName(productId, startUtcTime);
        auto endFileName = makeFileName(productId, endUtcTime);

        // Returns an iterator to the first element not less than the given value
        startIter = std::lower_bound(fileNameCache_.cbegin(), fileNameCache_.cend(), startFileName);

        // Returns an iterator to the first element greater than a certain value
        endIter = std::upper_bound(startIter, fileNameCache_.cend(), endFileName);

        for (auto it = startIter; it != endIter; ++it) {
            // Create the file path
            boost::filesystem::path srcFilePath = storagePath_ / *it;

            // Load the existing file.
            if (loadHistory.load(srcFilePath)) {
                if (addTicketsToJson(writer, loadHistory, startUtcTime, endUtcTime, printerInfo) > 0) {
                    foundSome = true;
                }

                if (!loadHistory.loads.empty()) {
                    const auto& firstStoreTime = loadHistory.loads.front().getCurrentSubtotal().endTime.utcTime;
                    if (firstStoreTime < startUtcTime) {
                        previousAvailable = true;
                    }

                    const auto& lastStoreTime = loadHistory.loads.back().getCurrentSubtotal().endTime.utcTime;
                    if (lastStoreTime >= endUtcTime) {
                        nextAvailable = true;
                    }
                }
            }
            else {
                AIS_LOG_ERROR("Couldn't load %s", srcFilePath.c_str());
            }
        }

        if (foundSome) {
            // We are done, we found the records.
            break;
        }
        else {
            // We didn't find anything, should be keep looking
            if (direction > 0) {
                // Keep looking forward
                if (nextAvailable) {
                    // Go to the next day
                    tmLocal = tmLocalNext;
                    startUtcTime = endUtcTime;

                    tmLocalNext.tm_mday += 1;
                    tmLocalNext.tm_isdst = -1; // Determine if DST was in effect when converting time point
                    endUtcTime = tes_common_ais::getTimePointFromLocalCalendarTime(tmLocalNext);
                }
                else if (alreadySkippedDays) {
                    // We already skipped days in search of the next day, don't do it again
                    AIS_LOG_ERROR("Skipped to next day and still didn't find anything.");
                    break;
                }
                else if (endIter != fileNameCache_.cend()) {
                    // Go forward one file and see what day that is.
                    // This is the next file that has not yet been examined.
                    std::string nextFileName = *endIter;

                    if (0 == nextFileName.rfind(productId, 0)) {
                        // It is relevant data from this machine (product id)
                        // Get the UTC timepoint that represents the beginning of the day covered by this file.
                        auto tp = parseDateFromFileName(nextFileName);

                        if ((tp > tp.min()) &&
                                (tp > startUtcTime) && // Make sure we are advancing in time
                                (tes_common_ais::getLocalCalendarTimeFromTimePoint(tp, tmLocal))) {

                            /*
                             * Finding the earliest local day in the file
                             *  startUtcTime <= start of file (<= tp)
                             *  endUtcTime > start of file (> tp)
                             */

                            // Go to the beginning of the local day, this will definitely be <= the start of the file
                            tmLocal.tm_hour = 0;
                            tmLocal.tm_min = 0;
                            tmLocal.tm_sec = 0;
                            tmLocal.tm_isdst = -1; // Determine if DST was in effect when converting time point
                            startUtcTime = tes_common_ais::getTimePointFromLocalCalendarTime(tmLocal);

                            // Go to the next day, this will very likely be > the start of the file, but on very
                            // rare cases might not be due to daylight saving time where the day is > 24 hours long.
                            tmLocalNext = tmLocal;
                            tmLocalNext.tm_mday += 1;
                            tmLocalNext.tm_isdst = -1; // Determine if DST was in effect when converting time point
                            endUtcTime = tes_common_ais::getTimePointFromLocalCalendarTime(tmLocalNext);

                            // If the end time is <= the start of the file, then advance to the next day.
                            if (endUtcTime <= tp) {
                                tmLocal = tmLocalNext;
                                startUtcTime = endUtcTime;

                                tmLocalNext.tm_mday += 1;
                                tmLocalNext.tm_isdst = -1; // Determine if DST was in effect when converting time point
                                endUtcTime = tes_common_ais::getTimePointFromLocalCalendarTime(tmLocalNext);
                            }

                            // To avoid a potential never ending loop, only this still part once.
                            alreadySkippedDays = true;
                        }
                        else {
                            // Could not parse the date from the filename
                            AIS_LOG_ERROR("Problem with file name: %s", nextFileName.c_str());
                            break;
                        }
                    }
                    else {
                        // File is not from the current machine
                        AIS_LOG_ERROR("Problem with file name: %s", nextFileName.c_str());
                        break;
                    }
                }
                else {
                    // We can't keep looking, this is it.
                    break;
                }
            }
            else if (direction < 0) {
                // Keep looking backward
                if (previousAvailable) {
                    // Go to the previous day
                    tmLocalNext = tmLocal;
                    endUtcTime = startUtcTime;

                    tmLocal.tm_mday -= 1;
                    tmLocal.tm_isdst = -1; // Determine if DST was in effect when converting time point
                    startUtcTime = tes_common_ais::getTimePointFromLocalCalendarTime(tmLocal);
                }
                else if (alreadySkippedDays) {
                    // We already skipped days in search of the previous day, don't do it again
                    AIS_LOG_ERROR("Skipped to previous day and still didn't find anything.");
                    break;
                }
                else if (startIter != fileNameCache_.cbegin()) {
                    // Go back one file and see what day that is
                    // This is the previous file that has not yet been examined
                    std::string previousFileName = *std::prev(startIter);

                    if (0 == previousFileName.rfind(productId, 0)) {
                        // It is relevant data from this machine (product id)
                        // Get the UTC timepoint that represents the beginning of the day covered by this file.
                        std::tm tmTmp;
                        auto tp = parseDateFromFileName(previousFileName, &tmTmp);
                        decltype(tp) tpNext;

                        if (tp > tp.min()) {
                            // Find start of the next possible file
                            tmTmp.tm_mday += 1;
                            tpNext = tes_common_ais::getTimePointFromCalendarTime(tmTmp);
                        }
                        else {
                            tpNext = tpNext.min();
                        }

                        if ((tpNext > tpNext.min()) &&
                                (tpNext < endUtcTime) && // Make sure we are going back in time
                                (tes_common_ais::getLocalCalendarTimeFromTimePoint(tpNext, tmLocal))) {

                            /*
                             * Finding the last local day in the file
                             *  startUtcTime <= end of file (< tpNext)
                             *  endUtcTime > end of file (>= tpNext)
                             */

                            // Go to the beginning of the local day, this will definitely be <= the start of the next file
                            // It could be > the end of this file and we will need to back up another file.
                            tmLocal.tm_hour = 0;
                            tmLocal.tm_min = 0;
                            tmLocal.tm_sec = 0;
                            tmLocal.tm_isdst = -1; // Determine if DST was in effect when converting time point
                            startUtcTime = tes_common_ais::getTimePointFromLocalCalendarTime(tmLocal);

                            // Go to the next day, this will be > the end of the file.
                            tmLocalNext = tmLocal;
                            tmLocalNext.tm_mday += 1;
                            tmLocalNext.tm_isdst = -1; // Determine if DST was in effect when converting time point
                            endUtcTime = tes_common_ais::getTimePointFromLocalCalendarTime(tmLocalNext);

                            // If the start time is >= the start of the next file, then back up a day.
                            if (startUtcTime >= tpNext) {
                                tmLocalNext = tmLocal;
                                endUtcTime = startUtcTime;

                                tmLocal.tm_mday -= 1;
                                tmLocal.tm_isdst = -1; // Determine if DST was in effect when converting time point
                                startUtcTime = tes_common_ais::getTimePointFromLocalCalendarTime(tmLocal);
                            }

                            // To avoid a potential never ending loop, only this still part once.
                            alreadySkippedDays = true;
                        }
                        else {
                            // Could not parse the date from the filename
                            AIS_LOG_ERROR("Problem with file name: %s", previousFileName.c_str());
                            break;
                        }
                    }
                    else {
                        // File is not from the current machine
                        AIS_LOG_ERROR("Problem with file name: %s", previousFileName.c_str());
                        break;
                    }
                }
                else {
                    // We can't keep looking, this is it.
                    break;
                }
            }
            else {
                // We can't keep looking, this is it.
                break;
            }
        }
    } while (true);

    writer.EndArray();

    // Populate the "localDate" and "displayDate" based on where we ended up.
    writer.Key("localDate");
    writer.String(tes_common_ais::putTime(tmLocal, "%F"));

    writer.Key("displayDate");
    writer.String(tes_common_ais::putTime(tmLocal, printerInfo.dateFormatString()));

    // There is nothing next available in the files we have looked at, but are there any more files?
    if ((!nextAvailable) &&
            (endIter != fileNameCache_.cend()) &&
            (0 == endIter->rfind(productId, 0))) {
        nextAvailable = true;
    }

    writer.Key("nextAvailable");
    writer.tBool(nextAvailable);

    // There is nothing previously available in the files we have looked at, but are there any more files?
    if ((!previousAvailable) &&
            (startIter != fileNameCache_.cbegin()) &&
            (0 == std::prev(startIter)->rfind(productId, 0))) {
        previousAvailable = true;
    }

    writer.Key("previousAvailable");
    writer.tBool(previousAvailable);

    writer.EndObject();

    if (writer.IsComplete()) {
        // Serialize it!
        bool success = false;

        { // Write to the file.
            tes_common_ais::OFlocker ofl(destFilePath);
            if (ofl) {
                ofl.ofstream() << sb.GetString();
                ofl.close();
                success = true;
                AIS_LOG_INFO("Published JSON file %s", destFilePath.c_str());
            }
            else {
                AIS_LOG_ERROR("File could not be opened and locked for publishing %s", destFilePath.c_str());
            }
        }

        if (!success) {
            try {
                if (fs::is_regular_file(destFilePath)) {
                    fs::remove(destFilePath);
                    AIS_LOG_WARN("File removed %s", destFilePath.c_str());
                }
            }
            catch (const fs::filesystem_error& e) {
                AIS_LOG_WARN("File could not be removed %s", destFilePath.c_str());
            }
        }

        return success;
    }

    return false;
}

bool LpsSaTotalsHistoryManager::publishTicketDetails(const boost::filesystem::path& destFilePath,
        const LpsSaTotalsPrinterInfo& printerInfo,
        const std::string& productId,
        const std::string& ticketId_) const {
    rj::StringBuffer sb;
    rj::Writer<rj::StringBuffer> writer(sb);

    writer.SetMaxDecimalPlaces(3);
    writer.StartObject();

    // File Name
    writer.Key("fileName");
    writer.String("TicketDetails");

    // If the ticket id doesn't contain all of the hyphens, add them
    auto ticketId = fixTicketId(ticketId_);

    // Ticket Id
    writer.Key("ticketId");
    writer.String(ticketId);

    // Details
    writer.Key("details");
    writer.StartObject();

    // Text
    if (isTicketIdValid(ticketId)) {
        // Parse the ticket number from the ticket id
        auto ticketNumber = getTicketNumberFromTicketId(ticketId);

        // Parse the day from the ticket id
        auto tp = tes_common_ais::parseDateTime(ticketId, "%y-%m-%d-%H-%M-%S", 17);

        if ((tp > tp.min()) && (ticketNumber < UINT32_MAX)) {
            auto srcFileName = makeFileName(productId, tp);
            auto srcFilePath = storagePath_ / srcFileName;
            LpsSaTotalsHistoryStorage loadHistory;
            if (loadHistory.load(srcFilePath)) {
                for (const auto& load : loadHistory.loads) {
                    if ((load.ticketNumber() == ticketNumber) && (load.ticketId() == ticketId)) {
                        writer.Key("text");
                        writer.StartArray();
                        printerInfo.loadRecordToAscii(load, [&writer](const std::string& line) {
                            writer.String(line);
                        });
                        writer.EndArray();
                        break;
                    }
                }
            }
        }
        else {
            if (tp <= tp.min()) {
                AIS_LOG_ERROR("Cannot parse date/time from ticket id %s", ticketId.c_str());
            }

            if (ticketNumber < 0) {
                AIS_LOG_ERROR("Cannot parse ticket number from ticket id %s", ticketId.c_str());
            }
        }
    }
    else {
        AIS_LOG_ERROR("Unexpected length ticket id %s", ticketId.c_str());
    }

    writer.EndObject(); // details
    writer.EndObject();

    if (writer.IsComplete()) {
        // Serialize it!
        bool success = false;

        { // Write to the file.
            tes_common_ais::OFlocker ofl(destFilePath);
            if (ofl) {
                ofl.ofstream() << sb.GetString();
                ofl.close();
                success = true;
                AIS_LOG_INFO("Published JSON file for %s.", ticketId.c_str());
            }
            else {
                AIS_LOG_ERROR("File could not be opened and locked for publishing %s", destFilePath.c_str());
            }
        }

        if (!success) {
            try {
                if (fs::is_regular_file(destFilePath)) {
                    fs::remove(destFilePath);
                    AIS_LOG_WARN("File removed %s", destFilePath.c_str());
                }
            }
            catch (const fs::filesystem_error& e) {
                AIS_LOG_WARN("File could not be removed %s", destFilePath.c_str());
            }
        }

        return success;
    }

    AIS_LOG_ERROR("JSON Writer not complete.");
    return false;
}

bool LpsSaTotalsHistoryManager::printTicket(const boost::filesystem::path& destFilePath,
        const LpsSaTotalsPrinterInfo& printerInfo,
        const std::string& productId,
        const std::string& ticketId_) const {

    bool success = false;

    // If the ticket id doesn't contain all of the hyphens, add them
    auto ticketId = fixTicketId(ticketId_);

    if (isTicketIdValid(ticketId)) {
        // Parse the ticket number from the ticket id
        auto ticketNumber = getTicketNumberFromTicketId(ticketId);

        // Parse the day from the ticket id
        auto tp = tes_common_ais::parseDateTime(ticketId, "%y-%m-%d-%H-%M-%S", 17);

        if ((tp > tp.min()) && (ticketNumber < UINT32_MAX)) {
            auto srcFileName = makeFileName(productId, tp);
            auto srcFilePath = storagePath_ / srcFileName;
            LpsSaTotalsHistoryStorage loadHistory;
            if (loadHistory.load(srcFilePath)) {
                for (const auto& load : loadHistory.loads) {
                    if ((load.ticketNumber() == ticketNumber) && (load.ticketId() == ticketId)) {
                        // Write to the file
                        tes_common_ais::OFlocker ofl(destFilePath);
                        if (ofl) {
                            printerInfo.loadRecordToAscii(load, ofl.ofstream());
                            ofl.close();
                            success = true;
                            AIS_LOG_INFO("Printed ASCII file for ticket id %s", ticketId.c_str());
                            break;
                        }
                        else {
                            AIS_LOG_ERROR("File could not be opened and locked for writing.");
                        }
                    }
                }
            }
        }
        else {
            if (tp <= tp.min()) {
                AIS_LOG_ERROR("Cannot parse date/time from ticket id %s", ticketId.c_str());
            }

            if (ticketNumber < 0) {
                AIS_LOG_ERROR("Cannot parse ticket number from ticket id %s", ticketId.c_str());
            }
        }
    }
    else {
        AIS_LOG_ERROR("Unexpected length ticket id %s", ticketId.c_str());
    }

    if (!success) {
        try {
            if (boost::filesystem::is_regular_file(destFilePath)) {
                boost::filesystem::remove(destFilePath);
                AIS_LOG_WARN("File removed %s", destFilePath.c_str());
            }
        }
        catch (const boost::filesystem::filesystem_error& e) {
            AIS_LOG_WARN("File could not be removed %s", destFilePath.c_str());
        }
    }

    return success;
}


static std::string makeFileName(const std::string& productId, const std::chrono::system_clock::time_point& utcTime) {
    std::string tempStr = tes_common_ais::putTime(utcTime, "%Y%m%d.bin");
    if (!productId.empty()) {
        tempStr = productId + "_" + tempStr;
    }
    return tempStr;
}

static std::string fixTicketId(const std::string& ticketId_) {
    auto ticketId = ticketId_;
    if (17 == ticketId.length()) {
        ticketId.insert( 2, 1, '-');
        ticketId.insert( 5, 1, '-');
        ticketId.insert( 8, 1, '-');
        ticketId.insert(11, 1, '-');
        ticketId.insert(14, 1, '-');
        ticketId.insert(17, 1, '-');
    }
    return ticketId;
}

static bool isTicketIdValid(const std::string& ticketId_) {
    return (23 == ticketId_.length());
}

static uint32_t getTicketNumberFromTicketId(const std::string& ticketId_) {
    uint32_t ticketNumber;
    try {
        ticketNumber = std::stoul(ticketId_.substr(18));
    }
    catch (...) {
        ticketNumber = UINT32_MAX;
    }
    return ticketNumber;
}


static std::chrono::system_clock::time_point parseDateFromFileName(const std::string& fileName, std::tm* pTmStruct) {
    std::string datePart;

    auto pos = fileName.find_last_of('_');
    if (pos != std::string::npos) {
       ++pos;
       if (pos < fileName.size()) {
           // Get it
           datePart = fileName.substr(pos, 8);
       }
    }
    else {
        // Get it from index 0
        datePart = fileName.substr(0, 8);
    }

    std::tm tmUtc{}; // value-initialized (basically 0's)

    const char* in = datePart.c_str();

    const char* out = strptime(in, "%Y%m%d", &tmUtc);

    // yyyymmdd (8 characters)
    if ((nullptr == out) || ((out - in) != 8)) {
        return std::chrono::system_clock::time_point::min();
    }

    if (nullptr != pTmStruct) {
        *pTmStruct = tmUtc;
    }

    return tes_common_ais::getTimePointFromCalendarTime(tmUtc);
}

static int addTicketsToJson(rj::Writer<rj::StringBuffer>& writer, const LpsSaTotalsHistoryStorage& loadHistory,
        const std::chrono::system_clock::time_point& startUtcTime, const std::chrono::system_clock::time_point& endUtcTime,
        const LpsSaTotalsPrinterInfo& printerInfo) {
    int numAdded = 0;

    for (const auto& load : loadHistory.loads) {
        const auto& storeTime = load.getCurrentSubtotal().endTime.utcTime;
        if ((storeTime >= startUtcTime) && (storeTime < endUtcTime)) {
            //  This is one of them!!!
            writer.StartObject();
            writer.Key("id");
            writer.String(load.ticketId());
            writer.Key("displayTime");
            writer.String(tes_common_ais::putLocalTime(storeTime, tes_common_ais::date_time_formats::HH_MM_24HR));
            writer.Key("number");
            writer.Uint(load.ticketNumber());
            writer.EndObject();
            ++numAdded;
        }
    }

    return numAdded;
}
