#ifndef DIRECTORYMONITOR_HPP
#define DIRECTORYMONITOR_HPP

#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <chrono>

#include <unistd.h>
#include <sys/poll.h>
#include <sys/inotify.h>
#include <errno.h>

#include <boost/filesystem.hpp>

#include <ais/log/Logger.h>

class DirectoryMonitor {
public:
    DirectoryMonitor() :
        directory_(),
        fd_(-1),
        wd_(-1),
        newFilesMtx_(),
        newFiles_(),
        run_(false),
        t_() {}

    bool start(const boost::filesystem::path& directory) {
        stop(); // Kill if currently running

        // Set the directory
        directory_ = directory.c_str();

        fd_ = inotify_init();
        if (fd_ >= 0) {
            // Add watch
            wd_ = inotify_add_watch(fd_, directory_.c_str(), IN_CLOSE_WRITE | IN_MOVED_TO | IN_ONLYDIR);
            if (wd_ >= 0) {
                // Start thread to watch for new files.
                AIS_LOG_NOTICE("Added watch to %s", directory_.c_str());
                run_ = true;
                t_ = std::thread([this]() { run(); });
            }
            else {
                AIS_LOG_ERROR("Failed to add a watch to %s", directory_.c_str());
            }
        }
        else {
            AIS_LOG_ERROR("Failed to initialize inotify.");
        }

        return t_.joinable();
    }

    void stop() {
        // Kill thread.
        if (t_.joinable()) {
            run_ = false;
            t_.join();
        }

        if (fd_ >= 0) {
            if (wd_ >= 0) {
                inotify_rm_watch(fd_, wd_);
                wd_ = -1;
            }
            close(fd_);
            fd_ = -1;
        }
    }

    bool nextFile(std::string& fileName) {
        bool gotOne;
        std::lock_guard<std::mutex> lck(newFilesMtx_);
        if (newFiles_.empty()) {
            gotOne = false;
        }
        else {
            // pop the next one off.
            fileName = newFiles_.front();
            newFiles_.pop();
            gotOne = true;
        }
        return gotOne;
    }

    inline boost::filesystem::path makeFullPath(const std::string& fileName) {
        return boost::filesystem::path(directory_) / fileName;
    }

private:
    static constexpr int pollTimeout_ = 99; // milliseconds
    static constexpr int retryTimeout_ = 500; // milliseconds

    void handleEvent(const struct inotify_event* pEvent) {
        if ((pEvent->wd == wd_) && ((pEvent->mask & (IN_CLOSE_WRITE | IN_MOVED_TO)) != 0)) {
            if ((pEvent->mask & IN_ISDIR) != 0) {
                // This is a directory, we don't care about this.
                AIS_LOG_WARN("New directory?");
            }
            else if (pEvent->len > 0) {
                { // We got a new file and it has a name!
                    std::lock_guard<std::mutex> lck(newFilesMtx_);
                    newFiles_.emplace(pEvent->name);
                }
                AIS_LOG_NOTICE("New file queued %s (0x%x)", pEvent->name, pEvent->mask);
            }
            else {
                // We got a new file without a name?
                AIS_LOG_WARN("New file, no name?");
            }
        }
        else {
            // Why did we get notified for this?
            AIS_LOG_WARN("Notified for something we aren't listening for 0x%x.", pEvent->mask);
        }
    }

    void run() {
        /*
         * The buffer must be big enough to read the maximum event size
         * sizeof(struct inotify_event) + max # chars in a file name + 1 for the null terminating character
         * See inotify man page:
         *  http://man7.org/linux/man-pages/man7/inotify.7.html
         */
        uint8_t readBuffer[sizeof(struct inotify_event) + NAME_MAX + 1] __attribute__ ((aligned(__alignof__(struct inotify_event))));
        struct pollfd pfd = { fd_, POLLIN, 0 };
        while (run_) {
            int ret = poll(&pfd, 1, pollTimeout_);
            if (0 == ret) {
                // we timed out
            }
            else if (ret < 0) {
                // we have poll error
                AIS_LOG_ERROR("poll error (%d): %s", errno, strerror(errno));
                std::this_thread::sleep_for(std::chrono::milliseconds(retryTimeout_));
            }
            else if (1 != ret) {
                // how did we poll more that 1?
                AIS_LOG_ERROR("poll returned more than 1 (%d)?", ret);
                std::this_thread::sleep_for(std::chrono::milliseconds(retryTimeout_));
            }
            else if ((pfd.revents & POLLIN) != 0) {
                // we have input available to read
                auto len = read(fd_, static_cast<void*>(&readBuffer[0]), sizeof(readBuffer));
                if (len < 0) {
                    // read error
                    AIS_LOG_ERROR("read error (%d): %s", errno, strerror(errno));
                    std::this_thread::sleep_for(std::chrono::milliseconds(retryTimeout_));
                }
                else if (0 == len) {
                    // didn't read anything
                    AIS_LOG_WARN("read of 0 length");
                    std::this_thread::sleep_for(std::chrono::milliseconds(retryTimeout_));
                }
                else {
                    // Some non-error thing happened, loop through the possibly multiple events
                    // that were read and handle them.
                    int count = 0;
                    uint8_t* pBuffer = &readBuffer[0];
                    while (pBuffer <= &readBuffer[len-1]) {
                        auto pEvent = reinterpret_cast<const struct inotify_event*>(pBuffer);
                        handleEvent(pEvent);
                        pBuffer += (sizeof(struct inotify_event) + pEvent->len);
                        ++count;
                    }

                    AIS_LOG_NOTICE("%d inotify events handled.", count);

                    // don't spin forever, play nicely.
                    std::this_thread::yield();
                }
            }
            else {
                // some other event occurred that we don't care about
                AIS_LOG_WARN("poll returned event not recognized 0x%x.", pfd.revents);
                std::this_thread::sleep_for(std::chrono::milliseconds(retryTimeout_));
            }

            // Reset received events.
            pfd.revents = 0;
        }
    }

    std::string directory_;
    int fd_;
    int wd_;

    std::mutex newFilesMtx_;
    std::queue<std::string> newFiles_;

    volatile bool run_;
    std::thread t_;
};

#endif
