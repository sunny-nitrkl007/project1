/*
 * LpsSaTotalsHistory.h
 *
 *  Created on: May 16, 2022
 *      Author: pf
 */

#ifndef LPSSATOTALSHISTORY_H_
#define LPSSATOTALSHISTORY_H_

#include <vector>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <map>
#include <utility>
#include <ctime>

#include <sys/stat.h>
#include <fcntl.h>

#include <boost/system/error_code.hpp>
#include <boost/filesystem.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

#include <chrono/print.hpp>

#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>

#include "LpsSaTotalsPrinterInfo.h"


class LpsSaTotalsHistoryStorage {
public:
    LpsSaTotalsHistoryStorage() : loads() {}

    std::vector<LpsSaLoadRecordChannelStorage> loads;

    bool load(const boost::filesystem::path& filePath);
    bool save(const boost::filesystem::path& filePath) const;

    void toCsv(std::ostream& os, const LpsSaTotalsPrinterInfo& printerInfo) const;

    template <class Archive>
    void serialize(Archive& ar, unsigned int version) {
        ar & loads;
    }
};

BOOST_CLASS_VERSION(LpsSaTotalsHistoryStorage, 1);


class LpsSaTotalsHistoryManager {
public:
    static constexpr long MAX_STORAGE_SIZE_BYTES = 1073741824; // 1GB
    //static constexpr long MAX_STORAGE_SIZE_BYTES = 1048576; // 1MB

    static constexpr uint16_t MIN_RETENTION_PERIOD_DAYS = 365; // Minimum 1 years
    static constexpr uint16_t MAX_RETENTION_PERIOD_DAYS = 366*10; // Maximum 10 years

    static constexpr uint16_t FILES_PER_DAY = 2; // 2 files per day

    static constexpr uint16_t MAX_STORAGE_FILE_COUNT_DEFAULT = MAX_RETENTION_PERIOD_DAYS * FILES_PER_DAY;

    static constexpr long MIN_RESERVED_STORAGE_SIZE_BYTES = 2048; // 2kB

    LpsSaTotalsHistoryManager(const boost::filesystem::path& storagePath) :
        storagePath_(storagePath),
        fileNameCache_(),
        maxStorageSize_(MAX_STORAGE_SIZE_BYTES),
        maxStorageFiles_(MAX_STORAGE_FILE_COUNT_DEFAULT),
        percentStorageUsed_(0.f) {}

    class Iterator {
    public:
        Iterator() : di_(), oldestTime_(0) {}

        Iterator(const boost::filesystem::path& dirPath) : Iterator(dirPath, 0) {}

        Iterator(const boost::filesystem::path& dirPath, std::time_t oldestTime) :
            di_(), oldestTime_(oldestTime) {
            try {
                di_ = boost::filesystem::directory_iterator(dirPath);

                // Advance to first file of the type we are looking for.
                if (di_ != boost::filesystem::directory_iterator()) {
                    if (!isInterestingFile(*di_)) {
                        ++(*this);
                    }
                }
            }
            catch (const boost::filesystem::filesystem_error& e) {
                AIS_LOG_ERROR(e.what());
                di_ = boost::filesystem::directory_iterator();
            }
        }

        Iterator(const Iterator&) = default; // copy
        Iterator(Iterator&&) = default; // move

        Iterator& operator=(const Iterator&) = default; // assign
        Iterator& operator=(Iterator&&) = default; // move assignment

        bool operator==(const Iterator& other) const {
            return di_ == other.di_;
        }

        bool operator!=(const Iterator& other) const {
            return di_ != other.di_;
        }

        // Pre-increment
        Iterator& operator++() {
            try {
                while (++di_ != boost::filesystem::directory_iterator()) {
                    if (isInterestingFile(*di_)) {
                        break;
                    }
                }
            }
            catch (const boost::filesystem::filesystem_error& e) {
                AIS_LOG_ERROR(e.what());
                di_ = boost::filesystem::directory_iterator();
            }
            return *this; // Return a reference to ourselves
        }

        static Iterator end() { return Iterator(); }

        const boost::filesystem::path& getPath() const { return di_->path(); }

        bool getLoadHistory(LpsSaTotalsHistoryStorage& loadHistory) const {
            return loadHistory.load(getPath());
        }

    protected:
        boost::filesystem::directory_iterator di_;
        std::time_t oldestTime_;

        // This function might throw exceptions
        bool isInterestingFile(const boost::filesystem::directory_entry& de) noexcept(false) {
            return isLoadHistoryFile(de) && isFileNewEnough(de);
        }

        // This function might throw exceptions
        bool isFileNewEnough(const boost::filesystem::directory_entry& de) const noexcept(false) {
            bool yes = true;
            if (oldestTime_ > 0) {
                if (boost::filesystem::last_write_time(de.path()) < oldestTime_) {
                    yes = false; // Older than oldest time.
                }
            }
            return yes;
        }

        // This function might throw exceptions
        static bool isLoadHistoryFile(const boost::filesystem::directory_entry& de) noexcept(false) {
            bool yes = false;
            if (boost::filesystem::is_regular_file(de.status())) {
                if (de.path().extension() == ".bin") {
                    yes = true;
                }
            }
            return yes;
        }
    };

    void setStoragePath(const boost::filesystem::path& storagePath) {
        storagePath_ = storagePath;
    }

    bool addLoad(const LpsSaLoadRecordChannelStorage& loadRecord);

    Iterator iteratorAll() const {
        return Iterator(storagePath_);
    }

    uint16_t countAllFiles() const {
        uint16_t fileCount = 0;
        for (Iterator it = iteratorAll(); it != it.end(); ++it) {
            ++fileCount;
        }
        return fileCount;
    }

    Iterator iteratorNew() const {
        return Iterator(storagePath_, getLastDownloadTime());
    }

    uint16_t countNewFiles() const {
        uint16_t fileCount = 0;
        for (Iterator it = iteratorNew(); it != it.end(); ++it) {
            ++fileCount;
        }
        return fileCount;
    }

    void updateLastDownloadTime() {
        std::ofstream ofs(storagePath_.string() + "_last_download", std::ios_base::out | std::ios_base::trunc);
        if (ofs) {
            ofs << tes_common_ais::putTime(std::chrono::system_clock::now(), "%FT%T");
            ofs.close();
        }
    }

    std::time_t getLastDownloadTime() const {
        std::time_t t = 0;
        boost::filesystem::path p(storagePath_.string() + "_last_download");
        if (boost::filesystem::exists(p)) {
            try {
                t = boost::filesystem::last_write_time(p);
            }
            catch (const boost::filesystem::filesystem_error& e) {
                AIS_LOG_ERROR(e.what());
                t = 0;
            }
        }
        return t;
    }

    bool isMemoryLow() const {
        return percentStorageUsed_ >= 99.f;
    }

    bool isMemoryFull() const {
        return percentStorageUsed_ >= 100.f;
    }

    float getPercentStorageRemaining() const {
        float percentStorageRemaining = 100.f - percentStorageUsed_;
        if (percentStorageRemaining >= 100.f) {
            percentStorageRemaining = 100.f;
        }
        else if (percentStorageRemaining <= 0.f) {
            percentStorageRemaining = 0.f;
        }
        return percentStorageRemaining;
    }

    void setRetentionPeriod(uint16_t days) {
        if (days <= MIN_RETENTION_PERIOD_DAYS) {
            days = MIN_RETENTION_PERIOD_DAYS;
        }
        else if (days >= MAX_RETENTION_PERIOD_DAYS) {
            days = MAX_RETENTION_PERIOD_DAYS;
        }

        // Adding 1 to the number of days in order avoid deleting data too early when adding a new load to an existing file.
        maxStorageFiles_ = (days + 1) * FILES_PER_DAY;

        // This will delete files that are too old right away.
        updateStorageSpace();
    }

    bool updateStorageSpace(long newFileSize=0, uint16_t newFileCount=0);

    bool publishTicketHistory(const boost::filesystem::path& filePath,
            const LpsSaTotalsPrinterInfo& printerInfo,
            const std::string& productId,
            const std::string& localDate, int direction) const;

    bool publishTicketHistoryNext(const boost::filesystem::path& filePath,
            const LpsSaTotalsPrinterInfo& printerInfo,
            const std::string& productId,
            const std::string& localDate) const {
        return publishTicketHistory(filePath, printerInfo, productId, localDate, 1);
    }

    bool publishTicketHistoryPrevious(const boost::filesystem::path& filePath,
            const LpsSaTotalsPrinterInfo& printerInfo,
            const std::string& productId,
            const std::string& localDate) const {
        return publishTicketHistory(filePath, printerInfo, productId, localDate, -1);
    }

    bool publishTicketHistory(const boost::filesystem::path& filePath,
            const LpsSaTotalsPrinterInfo& printerInfo,
            const std::string& productId,
            const std::string& localDate) const {
        return publishTicketHistory(filePath, printerInfo, productId, localDate, 0);
    }

    bool publishTicketDetails(const boost::filesystem::path& filePath,
            const LpsSaTotalsPrinterInfo& printerInfo,
            const std::string& productId,
            const std::string& ticketId) const;

    bool printTicket(const boost::filesystem::path& filePath,
            const LpsSaTotalsPrinterInfo& printerInfo,
            const std::string& productId,
            const std::string& ticketId) const;

protected:

    boost::filesystem::path storagePath_;
    mutable std::vector<std::string> fileNameCache_;
    long maxStorageSize_;
    uint16_t maxStorageFiles_;
    float percentStorageUsed_;

};


#endif /* LPSSATOTALSHISTORY_H_ */
