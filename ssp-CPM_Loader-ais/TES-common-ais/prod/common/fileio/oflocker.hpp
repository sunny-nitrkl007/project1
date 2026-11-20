#pragma once

#include <string>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#ifndef OFLOCKER_HPP
#define OFLOCKER_HPP

namespace tes_common_ais {
    namespace fs = boost::filesystem;
    namespace ip = boost::interprocess;
    namespace pt = boost::posix_time;

    /*
     * OFlocker
     * Writes to a file with locking
     */
    class OFlocker {
    public:
        typedef ip::file_lock FileLockType;
        typedef ip::scoped_lock<FileLockType> ScopedLockType;

        constexpr static long defaultTimeoutSeconds = 10;

        OFlocker() : OFlocker(defaultTimeoutSeconds) {}

        OFlocker(long timeoutSeconds) :
            timeoutSeconds_(timeoutSeconds),
            ofs_(), fLock_(), sLock_() {}

        OFlocker(const char* filePath, std::ios_base::openmode mode = std::ios_base::out, long timeoutSeconds = defaultTimeoutSeconds) :
            OFlocker(timeoutSeconds) {
            open(filePath, mode);
        }

        OFlocker(const std::string& filePath, std::ios_base::openmode mode = std::ios_base::out, long timeoutSeconds = defaultTimeoutSeconds) :
            OFlocker(timeoutSeconds) {
            open(filePath, mode);
        }

        OFlocker(const fs::path& filePath, std::ios_base::openmode mode = std::ios_base::out, long timeoutSeconds = defaultTimeoutSeconds) :
            OFlocker(timeoutSeconds) {
            open(filePath, mode);
        }

        OFlocker(const OFlocker&) = delete;
        OFlocker(OFlocker&&) = delete;

        ~OFlocker() {
            try { close(); } catch (...) {}
        }

        inline void open(const char* filePath, std::ios_base::openmode mode = std::ios_base::out) {
            if (*this) return; // already open

            ofs_.open(filePath, mode);
            if (ofs_) {
                try {
                    fLock_ = FileLockType(filePath);
                    pt::ptime timeout = pt::second_clock::universal_time() + pt::seconds(timeoutSeconds_);
                    sLock_ = ScopedLockType(fLock_, timeout);
                }
                catch (const ip::interprocess_exception& e) {
                    ofs_.close();
                }
            }
        }

        inline void open(const std::string& filePath, std::ios_base::openmode mode = std::ios_base::out) {
            open(filePath.c_str(), mode);
        }

        inline void open(const fs::path& filePath, std::ios_base::openmode mode = std::ios_base::out) {
            open(filePath.string(), mode);
        }

        inline explicit operator bool() const {
            return ofs_.is_open() && sLock_.owns();
        }

        inline void close() {
            ofs_.flush();
            try {
                sLock_.unlock();
            }
            catch (const ip::lock_exception& e) {
                // already unlocked
            }
            ofs_.close();
        }

        inline std::ofstream& ofstream() {
            return ofs_;
        }

    private:
        /*
         * These must be in this order so that destruction of sLock happens before FLock_
         */
        long timeoutSeconds_;
        std::ofstream ofs_;
        FileLockType fLock_;
        ScopedLockType sLock_;
    };

}

#endif // OFLOCKER_HPP
