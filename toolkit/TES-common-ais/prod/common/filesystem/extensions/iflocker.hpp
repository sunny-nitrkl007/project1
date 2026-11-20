#pragma once

#include <string>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#ifndef NVM_FILESYSTEM_IFLOCKER_HPP
#define NVM_FILESYSTEM_IFLOCKER_HPP

namespace ros2_nvm {
namespace filesystem {

    /*
     * IFlocker
     * Reads from a file with locking
     */
    class IFlocker {
    public:
        typedef boost::interprocess::file_lock FileLockType;
        typedef boost::interprocess::sharable_lock<FileLockType> ShareableLockType;

        constexpr static long defaultTimeoutSeconds = 10;

        IFlocker() : IFlocker(defaultTimeoutSeconds) {}

        IFlocker(long timeoutSeconds) :
            timeoutSeconds_(timeoutSeconds),
            ifs_(), fLock_(), sLock_() {}

        IFlocker(const char* filePath, std::ios_base::openmode mode = std::ios_base::in, long timeoutSeconds = defaultTimeoutSeconds) :
            IFlocker(timeoutSeconds) {
            open(filePath, mode);
        }

        IFlocker(const std::string& filePath, std::ios_base::openmode mode = std::ios_base::in, long timeoutSeconds = defaultTimeoutSeconds) :
            IFlocker(timeoutSeconds) {
            open(filePath, mode);
        }

        IFlocker(const boost::filesystem::path& filePath, std::ios_base::openmode mode = std::ios_base::in, long timeoutSeconds = defaultTimeoutSeconds) :
            IFlocker(timeoutSeconds) {
            open(filePath, mode);
        }

        IFlocker(const IFlocker&) = delete;
        IFlocker(IFlocker&&) = delete;

        ~IFlocker() {
            try { close(); } catch (...) {}
        }

        inline void open(const char* filePath, std::ios_base::openmode mode = std::ios_base::in) {
            if (*this) return; // already open

            ifs_.open(filePath, mode);
            if (ifs_) {
                try {
                    fLock_ = FileLockType(filePath);
                    boost::posix_time::ptime timeout = boost::posix_time::second_clock::universal_time() + boost::posix_time::seconds(timeoutSeconds_);
                    sLock_ = ShareableLockType(fLock_, timeout);
                }
                catch (const boost::interprocess::interprocess_exception& e) {
                    ifs_.close();
                }
            }
        }

        inline void open(const std::string& filePath, std::ios_base::openmode mode = std::ios_base::in) {
            open(filePath.c_str(), mode);
        }

        inline void open(const boost::filesystem::path& filePath, std::ios_base::openmode mode = std::ios_base::in) {
            open(filePath.string(), mode);
        }

        inline explicit operator bool() const {
            return ifs_.is_open() && sLock_.owns();
        }

        inline void close() {
            try {
                sLock_.unlock();
            }
            catch (const boost::interprocess::lock_exception& e) {
                // already unlocked
            }
            ifs_.close();
        }

        inline std::ifstream& ifstream() {
            return ifs_;
        }

    private:
        /*
         * These must be in this order so that destruction of sLock happens before FLock_
         */
        long timeoutSeconds_;
        std::ifstream ifs_;
        FileLockType fLock_;
        ShareableLockType sLock_;
    };

}
}

#endif
