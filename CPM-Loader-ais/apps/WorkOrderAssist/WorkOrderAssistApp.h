#ifndef WORKORDERASSISTAPP_H
#define WORKORDERASSISTAPP_H

#include <mutex>
#include <atomic>
#include <memory>
#include <utility>
#include <functional>
#include <vector>
#include <unordered_map>
#include <queue>
#include <thread>
#include <chrono>
#include <future>

#include <boost/signals2.hpp>

#include <ais/task/Task.h>

#include <interfaces/ShmClock/InterfaceTypes.h>
#include <interfaces/AutonomyConditionDiagnostics/TxInterfaceInputChannel.h>
#include <interfaces/PartNumbers/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrReqstChannel/Channel/Output/channel.h>
#include <interfaces/LpsSaLoadRecordChannel/Channel/Input/channel.h>
#include <interfaces/WorkOrderAssist/SettingsInterfaceInputChannel.h>
#include <interfaces/WorkOrderAssist/SettingsInterfaceOutputChannel.h>
#include <interfaces/WorkOrderAssist/TxInterfaceOutputChannel.h>

#include "IApp.h"
#include "Server.h"
#include "IHubService.h"
#include "SettingsStorage.h"

/*
 * Work Order Assist App
 */
class WorkOrderAssistApp: public task::Task, woa_app::IApp
{
public:
    WorkOrderAssistApp(const std::string& taskName);
    virtual ~WorkOrderAssistApp();

    /* task::Task Interface */
    virtual bool initialize();
    virtual bool executive();
    virtual void cleanup();

    /* woa_app::IApp Interface */
    bool getSites(std::vector<woa_app::Site>& sites, int32_t& activeSiteId);
    bool refreshSite();
    bool selectSite(int32_t siteId, bool async);

    bool selectJob(int64_t jobId, const woa_app::Job::TimePoint& dateTime, bool async);
    bool releaseJob(int64_t jobId, bool async);
    bool completeJob(int64_t jobId, int16_t passCount, float materialWeight, const woa_app::Job::TimePoint& dateTime, bool async);

    int64_t visitJobs(std::function<void(const woa_app::Job&)> visit);
    void readSettings(WorkOrderAssistSettings& settings) const;
    void writeSettings(const WorkOrderAssistSettings& settings);
    bool isEnabled() const;

protected:
    inline std::string makeStoragePath(const std::string& fileName) const {
        return (storageRoot_ / fileName).string();
    }

    void jobsListener(std::vector<woa_app::Job>&& jobs, int64_t jobsHash);

    void notifyLoadRecordInput();

    void updateTimeZoneInfo();

    void updateInstallStatus();

    void updateLoaderCode();

    void updateFrozenJobs();

private:
    mutable std::mutex jobsMutex_;
    struct JobsData {
        JobsData() :
            activeSiteId(-1),
            activeJobId(-1),
            lastSelectedJobId(-1),
            jobsHash(0),
            jobs(),
            delayedJobs(),
            jobFreezeTimes(),
            siteNames() {}

        // This is made atomic so that it can be read from multiple threads without using the jobs mutex.
        // This is a special case where just this member is read.
        std::atomic<int32_t> activeSiteId;

        // This is made atomic so that it can be read from multiple threads without using the jobs mutex.
        // This is a special case where just this member is read.
        std::atomic<int64_t> activeJobId;

        int64_t lastSelectedJobId;
        int64_t jobsHash;

        typedef std::unordered_map<int64_t, woa_app::Job> JobMap;

        JobMap jobs;
        JobMap delayedJobs;
        std::unordered_map<int64_t, std::chrono::steady_clock::time_point> jobFreezeTimes;

        std::unordered_map<int32_t, std::string> siteNames;

        void updateActiveJobId(const std::string& loaderCode);
        void updateFrozenJobs();
        void freezeJob(const int64_t& jobId, const woa_app::Job& j);
    };

    JobsData jobsData_;

    class ActivityMonitor {
    public:
        ActivityMonitor() : maxCount_(UINT32_MAX), count_(UINT32_MAX) {}
        inline void reset() { maxCount_ = UINT32_MAX, count_ = UINT32_MAX; }
        bool update(task::Task* pTask);
        inline bool isActivityDetected() const { return count_ < maxCount_; }
        inline void reportActivity() { count_ = 0; }
    private:
        std::atomic<uint32_t> maxCount_;
        std::atomic<uint32_t> count_;
    };

    ActivityMonitor activityMonitor_;

    class SiteSelectionRefresher {
    public:
        SiteSelectionRefresher() : stop_(true), sleeping_(true), t_(), countSeconds_(0), periodSeconds_(0), pApp_(nullptr) {}

        virtual ~SiteSelectionRefresher() { stop(); }

        bool start(IApp* pApp, uint16_t periodSeconds);

        void stop();

        void sleep();

        bool wake(bool forceSelection = false);

        void wakeAsync();

        void setPeriod(uint16_t periodSeconds) { periodSeconds_ = periodSeconds; }

    private:
        void run();

        std::atomic_bool stop_;
        std::atomic_bool sleeping_;
        std::thread t_;
        std::atomic<uint16_t> countSeconds_;
        std::atomic<uint16_t> periodSeconds_;
        IApp* pApp_;
    };

    SiteSelectionRefresher siteSelectionRefresher_;

    class HubServiceMonitor {
    public:
        HubServiceMonitor(float commsWarningTimeSeconds) :
            isCommunicationActive(false),
            txErrorCount(0),
            txSuccessCount(0),
            rxCount(0),
            timeOfLoss_(0),
            timeOfRx_(0),
            isCommunicationWarningActive_(false),
            commsWarningTimeSeconds_(static_cast<std::chrono::seconds::rep>(commsWarningTimeSeconds)) {}

        void reset() {
            isCommunicationActive = false;
            txErrorCount = 0;
            txSuccessCount = 0;
            rxCount = 0;
            timeOfLoss_ = 0;
            timeOfRx_ = 0;
            isCommunicationWarningActive_ = false;
        }

        void reportConnectionStatus(bool isUp) {
            if (!isUp) {
                isCommunicationActive = false;

                // Make sure the warning is armed
                armCommsWarning();
            }
            else {
                // We can't set communications active or clear any warning
                // because we haven't actually demonstrated successful communications.
            }
        }

        void reportCommTxResult(bool success) {
            if (success) {
                isCommunicationActive = true;
                ++txSuccessCount;
                clearCommsWarning();
            }
            else {
                isCommunicationActive = false;

                // Make sure the warning is armed
                armCommsWarning();

                ++txErrorCount;
            }
        }

        void reportCommRx() {
            isCommunicationActive = true;
            ++rxCount;
            timeOfRx_ = std::chrono::steady_clock::now().time_since_epoch().count();
            clearCommsWarning();
        }

        float secondsSinceLastRx() {
            auto timeSinceRx = std::chrono::steady_clock::now().time_since_epoch();
            timeSinceRx -= std::chrono::steady_clock::duration(timeOfRx_);
            return std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceRx).count() / 1000.f;
        }

        void clearCommsWarning() {
            // The communication warning is cleared, but it will become armed
            // again if we get another error
            isCommunicationWarningActive_ = false;
            timeOfLoss_ = 0;
        }

        void armCommsWarning() {
            if ((!isCommunicationWarningActive_) && (0 == timeOfLoss_)) {
                // It is not already armed or active, arm it.
                timeOfLoss_ = std::chrono::steady_clock::now().time_since_epoch().count();
            }
        }

        bool isCommsWarningActive() {
            bool warningActive = isCommunicationWarningActive_;

            if (warningActive || (0 == timeOfLoss_)) {
                // Either the warning is already active,
                // or it is not armed to become active,
                // leave it alone.
            }
            else {
                // Should the warning it be active?
                // It should be active if now minus timeOfLoss is > threshold
                auto timeSinceLoss = std::chrono::steady_clock::now().time_since_epoch();
                timeSinceLoss -= std::chrono::steady_clock::duration(timeOfLoss_);
                if (timeSinceLoss >= commsWarningTimeSeconds_) {
                    isCommunicationWarningActive_ = true;
                    warningActive = true;
                }
            }

            return warningActive;
        }

        std::atomic<bool> isCommunicationActive;
        std::atomic<uint16_t> txErrorCount;
        std::atomic<uint16_t> txSuccessCount;
        std::atomic<uint16_t> rxCount;

    private:
        std::atomic<std::chrono::steady_clock::duration::rep> timeOfLoss_;
        std::atomic<std::chrono::steady_clock::duration::rep> timeOfRx_;
        std::atomic<bool> isCommunicationWarningActive_;
        std::chrono::seconds commsWarningTimeSeconds_;
    };

    HubServiceMonitor hubServiceMonitor_;

    std::string loaderCode_;

    std::unique_ptr<woa_app::Server> pServer_;
    std::unique_ptr<woa_app::IHubService> pHubService_;

    boost::filesystem::path storageRoot_;

    WorkOrderAssistSettingsStorage settingsStorage_;
    std::atomic_bool publishSettings_;
    uint32_t publishSettingsUpdateCount_;

    // For setting job information
    LpsSaJobMgrReqstChannelOutputChannel* lpsSaJobMgrReqstChannelOutput_;

    // For getting completed load/job information
    LpsSaLoadRecordChannelInputChannel* lpsSaLoadRecordChannelInput_;
    boost::signals2::connection lpsSaLoadRecordChannelInputConnection_;

    // For publishing settings
    WorkOrderAssistSettingsInterfaceOutputChannel* settingsOutput_;

    // For receiving new settings
    WorkOrderAssistSettingsInterfaceInputChannel* settingsWrInput_;

    // For periodically publishing tx channels
    WorkOrderAssistTxInterfaceOutputChannel* txOutput_;
    uint32_t txOutputUpdateCount_;

    // For receiving local time information
    ShmClockInput* shmClockInput_;
    struct {
        int32_t offset;
        int32_t index;
    } tzInfo_;

    // For SEA install status
    AutonomyConditionDiagnosticsTxInterfaceInputChannel* autonomyConditionDiagnosticsTxInputChannel_;

    // For receiving machine serial number
    PartNumbersInput* partNumbersInput_;

    // For logging
    uint32_t logUpdateCount_;

    class AsyncFutures {
    public:
        AsyncFutures() : mtx_(), futures_() {}
        ~AsyncFutures() { waitAll(); }
        void add(std::future<void>&& f);
        bool checkNext();
        void waitAll() { while (waitNext()) { /* do nothing */ } }

    private:
        bool waitNext();

        std::mutex mtx_;
        std::queue<std::future<void> > futures_;
    };

    AsyncFutures asyncFutures_;
};


#endif
