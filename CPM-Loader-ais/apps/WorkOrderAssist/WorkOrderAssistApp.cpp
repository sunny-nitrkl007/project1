#include <sstream>
#include <chrono>
#include <thread>

#include <boost/filesystem.hpp>

#include <ais/task/Task.h>
#include <ais/log/Logger.h>

#include <chrono/print.hpp>
#include <chrono/tz.hpp>
#include <lps_sea_defs.h>

#include <interfaces/LpsSaJobMgrReqstChannel/LpsSaJobMgrReqstChannel.h>
#include <interfaces/IoTHubCommsInboundMessage/InterfaceTypes.h>
#include <interfaces/IoTHubCommsOutboundMessage/InterfaceTypes.h>
#include <interfaces/IoTHubCommsOutboundReturn/InterfaceTypes.h>
#include <interfaces/WorkOrderAssist/SettingsInterface.hpp>
#include <interfaces/WorkOrderAssist/TxInterface.hpp>
#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>

#include "WorkOrderAssistApp.h"
#include "ScsHubService.h"
#include "MockHubService.h"
#include "Server.h"

namespace fs = boost::filesystem;

#define SETTINGS_PUBLISH_PERIOD_SEC (10.0f)
#define TX_PUBLISH_PERIOD_SEC (1.0f)
#define LOG_UPDATE_PERIOD_SEC (10.0f)

// Refresh site selection every 10 minutes under normal operation.
// Attempt to select the site every 30 seconds when communication is lost.
#define SELECT_SITE_SLOW_REFRESH_PERIOD_SEC (600.0f)
#define SELECT_SITE_MEDIUM_REFRESH_PERIOD_SEC (60.0f)
#define SELECT_SITE_FAST_REFRESH_PERIOD_SEC (30.0f)

#define NO_ACTIVITY_TIME_SEC (1800.0f)

#define RX_TOO_QUIET_TIME_SEC (60.0f)

#define COMMS_WARNING_TIME_SEC (120.0f)

// When a change is made to the state of a job in the local cache and a
// request is made remotely to do the same, we freeze the local
// cache of that job for as long as it is expected to take for the remote
// change request to be applied.  This way our local cache is not reverted
// to the state prior to the change request being processed.
// The local cache of the job will be unfrozen after the time expires,
// and the most recent state of the job will be applied to the local cache.
#define JOB_CACHE_FREEZE_MIN_TIME_SEC (20.0f)
#define JOB_CACHE_FREEZE_MAX_TIME_SEC (90.0f)

#define SETTINGS_FILENAME_BIN (R"(WorkOrderAssistSettings.bin)")

#define DEFAULT_STORAGE_ROOT (R"(/tmp/WorkOrderAssistApp/storage)")

static inline bool loaderCodeDefiniteMatch(const std::string& localLoaderCode, const std::string& remoteLoaderCode);
static inline bool loaderCodePossibleMatch(const std::string& localLoaderCode, const std::string& remoteLoaderCode);
static inline bool loaderCodeDefiniteMismatch(const std::string& localLoaderCode, const std::string& remoteLoaderCode);

/*
 * main() will call this function in order to get the task instance.
 */
task::AbstractTaskCore* task::getTaskImplementation(void) {
    static WorkOrderAssistApp thisTask("WorkOrderAssist");
    return dynamic_cast<Task*>(&thisTask);
}

/*
 * Constructor
 */
WorkOrderAssistApp::WorkOrderAssistApp(const std::string& taskName) :
    task::Task(taskName),
    jobsMutex_(),
    jobsData_(),
    activityMonitor_(),
    siteSelectionRefresher_(),
    hubServiceMonitor_(COMMS_WARNING_TIME_SEC),
    loaderCode_(),
    pServer_(nullptr),
    pHubService_(nullptr),
    storageRoot_(DEFAULT_STORAGE_ROOT),
    settingsStorage_(),
    publishSettings_(true),
    publishSettingsUpdateCount_(0),
    lpsSaJobMgrReqstChannelOutput_(nullptr),
    lpsSaLoadRecordChannelInput_(nullptr),
    lpsSaLoadRecordChannelInputConnection_(),
    settingsOutput_(nullptr),
    settingsWrInput_(nullptr),
    txOutput_(nullptr),
    txOutputUpdateCount_(0),
    shmClockInput_(nullptr),
    tzInfo_{0, -1},
    autonomyConditionDiagnosticsTxInputChannel_(nullptr),
    partNumbersInput_(nullptr),
    logUpdateCount_(0),
    asyncFutures_() {
}

/*
 * Destructor
 */
WorkOrderAssistApp::~WorkOrderAssistApp() {
}

/*
 * AIS Task Initializer
 */
bool WorkOrderAssistApp::initialize() {
    bool everythingOk = true;
    uint16_t serverPort;
    AIS_LOG_DEBUG("WorkOrderAssistApp::initialize");

    { // Get the configs and print it out.
        ConfigSection& configs = getTaskConfig();

        if (!configs.get("serverPort", serverPort)) {
            serverPort = 55555;
        }

        std::string storageRoot;
        if (configs.get("storageRoot", storageRoot)) {
            storageRoot_ = storageRoot;
        }
        else {
            storageRoot_ = DEFAULT_STORAGE_ROOT;
        }

        AIS_LOG_INFO("Storage Root: %s", storageRoot_.c_str());
    }

    // Create the server
    pServer_ = std::unique_ptr<woa_app::Server>(new woa_app::Server(this, serverPort));
    if (nullptr == pServer_) {
        AIS_LOG_ERROR("Cannot create server.");
        everythingOk = false;
    }

    { // Create the hub service
        IoTHubCommsInboundMessageInput* iotHubInboundMessageInput =
                dynamic_cast<IoTHubCommsInboundMessageInput*>(task::InterfaceDb::fetch("IoTHubInboundMessageInput"));

        IoTHubCommsOutboundMessageOutput* iotHubOutboundMessageOutput =
                dynamic_cast<IoTHubCommsOutboundMessageOutput*>(task::InterfaceDb::fetch("IoTHubOutboundMessageOutput"));

        IoTHubCommsOutboundReturnInput* iotHubOutboundReturnInput =
                dynamic_cast<IoTHubCommsOutboundReturnInput*>(task::InterfaceDb::fetch("IoTHubOutboundReturnInput"));

        if (nullptr == iotHubInboundMessageInput) {
            AIS_LOG_ERROR("No IoTHub inbound message input channel defined.");
            everythingOk = false;
        }
        else if (nullptr == iotHubOutboundMessageOutput) {
            AIS_LOG_ERROR("No IoTHub outbound message output channel defined.");
            everythingOk = false;
        }
        else if (nullptr == iotHubOutboundReturnInput) {
            AIS_LOG_ERROR("No IoTHub outbound return input channel defined.");
            everythingOk = false;
        }
        else {
            // Create the hub service

            // For testing we can installed the "Mock" hub service.
            //pHubService_ = std::unique_ptr<woa_app::IHubService>(new woa_app::MockHubService());

            pHubService_ = std::unique_ptr<woa_app::IHubService>(new woa_app::ScsHubService(
                    getTaskName(),
                    iotHubInboundMessageInput,
                    iotHubOutboundMessageOutput,
                    iotHubOutboundReturnInput));

            if (nullptr == pHubService_) {
                AIS_LOG_ERROR("Cannot create hub service.");
                everythingOk = false;
            }
            else {
                // Install job listener
                pHubService_->registerJobsListener([this](std::vector<woa_app::Job>&& jobs, int64_t jobsHash) {
                    jobsListener(std::move(jobs), jobsHash);
                });
            }
        }
    }

    // Initialize input and output channels
    if (!task::InterfaceDb::bind("LpsSaJobMgrReqstChannelOutput", lpsSaJobMgrReqstChannelOutput_)) {
        AIS_LOG_ERROR("No LpsSaJobMgr request helper defined.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("LoadRecordInput", lpsSaLoadRecordChannelInput_)) {
        AIS_LOG_ERROR("No LoadRecord input channel defined.");
        everythingOk = false;
    }
    else {
        // Attach a listener for load records.
        lpsSaLoadRecordChannelInputConnection_ = lpsSaLoadRecordChannelInput_->addNewDataSlot([this]{
            notifyLoadRecordInput();
        });
    }

    if (!task::InterfaceDb::bind("SettingsOutput", settingsOutput_)) {
        AIS_LOG_ERROR("No Settings output channel defined.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("SettingsWrInput", settingsWrInput_)) {
        AIS_LOG_ERROR("No Settings write input channel defined.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("TxOutput", txOutput_)) {
        AIS_LOG_ERROR("No Tx output channel defined.");
        everythingOk = false;
    }

    txOutputUpdateCount_ = UINT32_MAX;

    // Get SHM clock input channel
    if (!task::InterfaceDb::bind("ShmClockInput", shmClockInput_)) {
        AIS_LOG_ERROR("No SHM clock input channel defined.");
        everythingOk = false;
    }

    // We initially do not know the time zone info
    tzInfo_.offset = 0;
    tzInfo_.index = -1;

    if (!task::InterfaceDb::bind("AutonomyConditionDiagnosticsTxChannelInput", autonomyConditionDiagnosticsTxInputChannel_)) {
        AIS_LOG_ERROR("No AutonomyConditionDiagnosticsTxChannel input channel defined.");
        everythingOk = false;
    }

    // Get part numbers input channel
    if (!task::InterfaceDb::bind("PartNumbersInput", partNumbersInput_)) {
        AIS_LOG_ERROR("No PartNumbers input channel defined.");
        everythingOk = false;
    }

    // We initially do not know the loader code (product id/machine serial number)
    loaderCode_ = "";

    // Load stuff from storage
    try {
        fs::create_directories(storageRoot_);

        // Load settings
        settingsStorage_.setFilePath(makeStoragePath(SETTINGS_FILENAME_BIN));
        settingsStorage_.load();
        publishSettings_ = true;
        publishSettingsUpdateCount_ = 0;
    }
    catch (const fs::filesystem_error& e) {
        AIS_LOG_ERROR(e.what());
        everythingOk = false;
    }

    { // Initialize the job information
        WorkOrderAssistSettings settings;
        readSettings(settings);

        jobsData_.activeSiteId = settings.siteId;
        jobsData_.activeJobId = -1;

        jobsData_.lastSelectedJobId = -1;
        jobsData_.jobsHash = 0;

        jobsData_.jobs.clear();
        jobsData_.delayedJobs.clear();
        jobsData_.jobFreezeTimes.clear();

        jobsData_.siteNames.clear();
        jobsData_.siteNames[settings.siteId] = settings.siteName;
    }

    // Initialize the activity monitor
    activityMonitor_.reset();

    // Initialize the hub service monitor
    hubServiceMonitor_.reset();

    // If everything is OK so far... start up the IoT Hub service.
    if (everythingOk) {
        // Start the IoT Hub Service
        if (pHubService_->start()) {
            AIS_LOG_NOTICE("IoT Hub service started.");
        }
        else {
            AIS_LOG_ERROR("Could not start hub service.");
            everythingOk = false;
        }
    }

    // If everything is OK so far... start up the web server.
    if (everythingOk) {
        // Start the Web Server
        if (pServer_->start()) {
            AIS_LOG_NOTICE("Web server started.");
        }
        else {
            AIS_LOG_ERROR("Could not start web server.");
            everythingOk = false;
        }
    }

    // If everything is OK so far...
    if (everythingOk) {
        // Start a thread to periodically refresh the site selection.
        siteSelectionRefresher_.start(this, SELECT_SITE_FAST_REFRESH_PERIOD_SEC);
    }

    if (!everythingOk) {
        // Failed... get rid of services
        pServer_.reset();
        pHubService_.reset();
    }

    logUpdateCount_ = UINT32_MAX;

    if (everythingOk) {
        AIS_LOG_NOTICE("Everything initialized OK.");
    }

    return everythingOk;
}

/*
 * AIS Task Executive
 */
bool WorkOrderAssistApp::executive() {
    AIS_LOG_DEBUG("WorkOrderAssistApp::executive");

    // Keep track of time zone
    updateTimeZoneInfo();

    // Keep track in installation status
    updateInstallStatus();

    // Handle any request to write the settings
    if (nullptr != settingsWrInput_) {
        bool receivedSettings = false;
        WorkOrderAssistSettingsInterface newSettings;
        while (settingsWrInput_->get(newSettings)) {
            receivedSettings = true;
        }

        if (receivedSettings) {
            WorkOrderAssistSettings settings;
            readSettings(settings);

            // We only support setting a couple of settings through this interface
            settings.enabled = newSettings.enabled;
            settings.jobTimeWarningMinutes = newSettings.jobTimeWarningMinutes;

            writeSettings(settings);
        }
    }

    // Keep track of loader code (product id / machine serial number)
    updateLoaderCode();

    // Update frozen jobs when they become unfrozen
    updateFrozenJobs();

    // Update the activity monitor
    bool activityDetected = activityMonitor_.update(this);

    // Put the site selection refresh to sleep if there is no activity detected
    // Also clear any communications warning
    if ((!activityDetected) || (!isEnabled())) {
        siteSelectionRefresher_.sleep();
        hubServiceMonitor_.clearCommsWarning();
    }

    // Set the site selection refresh period based on the communication status
    if (hubServiceMonitor_.isCommunicationActive) {
        // Communication is active, we can slow down the refresh
        // to maintain a site selection.
        if (hubServiceMonitor_.secondsSinceLastRx() >= RX_TOO_QUIET_TIME_SEC) {
            // We haven't received jobs in a while, maybe we lost connection?
            // Speed up the refresh period to get the data flow re-established.
            // This is an ICA due to the fact that CDA will not attempt to
            // re-establish connection after connection loss unless a Tx attempt
            // is made.  This means that our Rx will be blocked unless we get
            // it to re-establish connection with a Tx.
            siteSelectionRefresher_.setPeriod(SELECT_SITE_MEDIUM_REFRESH_PERIOD_SEC);
        }
        else {
            // Everything is good, we are receiving data and comms are active.
            // Slow down the site selection refresh to the slowest heartbeat.
            siteSelectionRefresher_.setPeriod(SELECT_SITE_SLOW_REFRESH_PERIOD_SEC);
        }
    }
    else {
        // Communication is not active, speed up the refresh
        // to try and establish communication again.
        siteSelectionRefresher_.setPeriod(SELECT_SITE_FAST_REFRESH_PERIOD_SEC);
    }

    { // Handle periodic triggering of settings publishing
        float maxUpdateCount = SETTINGS_PUBLISH_PERIOD_SEC * static_cast<float>(getCycleRateHz());

        ++publishSettingsUpdateCount_;

        if (publishSettingsUpdateCount_ >= maxUpdateCount) {
            publishSettingsUpdateCount_ = 0;
            publishSettings_ = true;
        }
    }

    // Publish the settings if needed
    if (publishSettings_.exchange(false) && (nullptr != settingsOutput_)) {
        WorkOrderAssistSettingsInterface settings;
        readSettings(settings);
        settingsOutput_->publish(settings);
        AIS_LOG_INFO("Published settings.");
    }

    { // Handle periodic triggering of tx publishing
        float maxUpdateCount = TX_PUBLISH_PERIOD_SEC * static_cast<float>(getCycleRateHz());

        if (txOutputUpdateCount_ >= maxUpdateCount) {
            if (nullptr != txOutput_) {
                WorkOrderAssistTxInterface txData;

                txData.activityDetected = activityDetected;

                { // Get jobs data
                    std::lock_guard<std::mutex> lock(jobsMutex_);
                    txData.activeSiteId = jobsData_.activeSiteId;
                    txData.activeJobId = jobsData_.activeJobId;
                    txData.numberOfJobs = jobsData_.jobs.size();
                }

                txData.hubServiceCommsActive = hubServiceMonitor_.isCommunicationActive;
                txData.hubServiceTxErrorCount = hubServiceMonitor_.txErrorCount;
                txData.hubServiceTxSuccessCount = hubServiceMonitor_.txSuccessCount;
                txData.hubServiceRxCount = hubServiceMonitor_.rxCount;

                txData.commsWarningActive = hubServiceMonitor_.isCommsWarningActive();

                txOutput_->publish(txData);
            }
            txOutputUpdateCount_ = 0;
        }

        ++txOutputUpdateCount_;
    }

    { // Handle periodic triggering of logging
        float maxLogUpdateCount = LOG_UPDATE_PERIOD_SEC * static_cast<float>(getCycleRateHz());

        if (logUpdateCount_ >= maxLogUpdateCount) {
            AIS_LOG_NOTICE("Site: %d, Job: %d, JobsHash: %lld", jobsData_.activeSiteId.load(), jobsData_.activeJobId.load(), jobsData_.jobsHash);

            if (!activityDetected) {
                AIS_LOG_NOTICE("No activity detected.");
            }

            logUpdateCount_ = 0;
        }

        ++logUpdateCount_;
    }

    /*
     * Continually check for the next async task to complete
     * This only blocks if the launch policy of the task is deferred.
     */
    asyncFutures_.checkNext();

    return true;
}

/*
 * AIS Task Cleanup
 */
void WorkOrderAssistApp::cleanup() {
    AIS_LOG_DEBUG("WorkOrderAssistApp::cleanup");

    if (nullptr != lpsSaLoadRecordChannelInput_) {
        lpsSaLoadRecordChannelInput_->removeNewDataSlot(lpsSaLoadRecordChannelInputConnection_);
    }

    siteSelectionRefresher_.stop();

    AIS_LOG_NOTICE("Killing server and hub service.");
    pServer_.reset(); // Kill the server (release unique_ptr and object is destroyed)
    pHubService_.reset(); // Kill the hub service (release unique_ptr and object is destroyed)

    // Wait for all async tasks to complete.
    asyncFutures_.waitAll();
}


bool WorkOrderAssistApp::getSites(std::vector<woa_app::Site>& sites, int32_t& activeSiteId) {

    if (!isEnabled()) {
        // We are not enabled.
        return false;
    }

    bool success = false;
    bool saveSettings = false;

    activityMonitor_.reportActivity(); // Indicate new activity detected

    activeSiteId = jobsData_.activeSiteId;

    if (pHubService_) {
        success = pHubService_->getSites(sites);

        if (success) {
            std::lock_guard<std::mutex> lock(jobsMutex_);

            // Fill in the local cache
            jobsData_.siteNames.clear();
            for (const auto& site : sites) {
                jobsData_.siteNames[site.id] = site.name;

                // If the currently active site is found, update it's name in settings.
                if (site.id == activeSiteId) {
                    settingsStorage_.setSite(activeSiteId, site.name);
                    saveSettings = true;
                }
            }
        }

        // Report the communication result to the hub service monitor.
        hubServiceMonitor_.reportCommTxResult(success);
    }

    if (saveSettings) {
        settingsStorage_.save();
        publishSettings_ = true;
    }

    return success;
}

bool WorkOrderAssistApp::refreshSite() {

    if (!isEnabled()) {
        // We are not enabled.
        return false;
    }

    bool success = false;
    int32_t siteId;
    int64_t jobsHash;

    { // Update local jobs
        std::lock_guard<std::mutex> lock(jobsMutex_);
        // We are just refreshing the same site.
        siteId = jobsData_.activeSiteId;
        jobsHash = jobsData_.jobsHash;
    }

    if (pHubService_) {
        if (siteId >= 0) {
            success = pHubService_->selectSite(siteId, jobsHash, woa_app::Job::Clock::now());

            // Report the communication result to the hub service monitor.
            hubServiceMonitor_.reportCommTxResult(success);
        }
        else {
            // No site to refresh
            success = true;
        }
    }

    return success;
}

bool WorkOrderAssistApp::selectSite(int32_t siteId, bool async) {

    if (!isEnabled()) {
        // We are not enabled.
        return false;
    }

    bool success;
    bool saveSettings = false;

    int32_t oldSiteId = -1;
    int64_t oldJobId = -1;

    if (siteId >= 0) {
        activityMonitor_.reportActivity(); // Indicate new activity detected
    }
    else {
        return false;
    }

    { // Update local jobs
        std::lock_guard<std::mutex> lock(jobsMutex_);
        if (jobsData_.activeSiteId != siteId) {

            // See if we need to release the currently active job
            try {
                woa_app::Job& j = jobsData_.jobs.at(jobsData_.activeJobId);
                if ((j.state == woa_app::JobState::DOING) && (!j.isLoaded)) {
                    j.state = woa_app::JobState::TODO;
                    oldSiteId = jobsData_.activeSiteId;
                    oldJobId = jobsData_.activeJobId;
                }
            }
            catch (...) {
                // Cannot find active job.
            }

            jobsData_.activeSiteId = siteId;
            jobsData_.jobsHash = 0;
            jobsData_.activeJobId = -1;
            jobsData_.lastSelectedJobId = -1;
            jobsData_.jobs.clear();
            jobsData_.delayedJobs.clear();
            jobsData_.jobFreezeTimes.clear();

            // If the site id is not in the site map, then we will not know the
            // name and it will be updated the next time we get the sites.
            // However, we *should* know the name since it should have been picked
            // from the list to begin with.  If the site id doesn't exist in the
            // map, then a default site will be created there.
            settingsStorage_.setSite(siteId, jobsData_.siteNames[siteId]);
            saveSettings = true;
        }
    }

    if (async) {
        /*
         * Launch an async task to select the site.
         *  std::async returns a future which blocks on destruction until the
         *  ascynchronous task completes.  This means we cannot just throw the
         *  returned future away, otherwise we will block.  We keep track of the
         *  future in asyncFutures_ and periodically check them in executive.
         */
        asyncFutures_.add(
            std::async(std::launch::async, [this, oldSiteId, oldJobId]() {
                // Wake up the site selection refresher if it is asleep.
                // Force it to send the site selection even it is already awake.
                siteSelectionRefresher_.wake(true);

                if (pHubService_) {
                    // Release the old job if needed.
                    if ((oldSiteId >= 0) && (oldJobId >= 0)) {
                        // Best effort, currently ignoring if unsuccessful
                        bool commResult = pHubService_->updateJobStatusStopDoing(oldSiteId, oldJobId);
                        // Report the communication result to the hub service monitor.
                        hubServiceMonitor_.reportCommTxResult(commResult);
                    }
                }
            })
        );

        success = true;
    }
    else {
        // Wake up the site selection refresher if it is asleep.
        // Force it to send the site selection even it is already awake.
        success = siteSelectionRefresher_.wake(true);

        if (pHubService_) {
            // Release the old job if needed.
            if ((oldSiteId >= 0) && (oldJobId >= 0)) {
                // Best effort, currently ignoring if unsuccessful
                bool commResult = pHubService_->updateJobStatusStopDoing(oldSiteId, oldJobId);
                // Report the communication result to the hub service monitor.
                hubServiceMonitor_.reportCommTxResult(commResult);
            }
        }
    }

    if (saveSettings) {
        settingsStorage_.save();
        publishSettings_ = true;
    }

    return success;
}

bool WorkOrderAssistApp::selectJob(int64_t jobId, const woa_app::Job::TimePoint& dateTime, bool async) {

    if (!isEnabled()) {
        // We are not enabled.
        return false;
    }

    bool success = false;
    int32_t siteId = -1;
    int64_t oldJobId = -1;
    int64_t newJobId = -1;
    LpsSaJobMgrReqstChannel requestData;

    if (jobId >= 0) {
        activityMonitor_.reportActivity(); // Indicate new activity detected
        siteSelectionRefresher_.wakeAsync(); // Wake up the site selection refresher if asleep.
    }
    else {
        return false;
    }

    { // Update local jobs
        std::lock_guard<std::mutex> lock(jobsMutex_);
        siteId = jobsData_.activeSiteId;

        /*
         * Select the new job if nobody currently has the job
         *  - The job is taken if it is not in the "to-do" state
         *
         * Release the active job if
         *  - I do currently have the job, and it is not loaded AND selecting a new job was OK
         */
        try {
            woa_app::Job& j = jobsData_.jobs.at(jobId);
            if (j.state == woa_app::JobState::TODO) {
                j.state = woa_app::JobState::DOING;
                j.isLoaded = false;
                j.result.loaderCode = loaderCode_;
                j.stale = true;
                newJobId = jobId;
            }
            else if ((loaderCodePossibleMatch(loaderCode_, j.result.loaderCode)) &&
                     (j.state == woa_app::JobState::DOING) &&
                     (!j.isLoaded)) {
                // This job is already ours
                newJobId = jobId;
            }
            else {
                // Job cannot be taken, it is not "to-do" and it is not already ours
            }

            // Freeze the job
            if (newJobId >= 0) {
                jobsData_.freezeJob(newJobId, j);
            }

            // If there is a new job selected, build the request
            if (newJobId >= 0) {
                // Dispatch only supports
                requestData.command = LpsSaJobMgrReqstChannel::Command::WRITE_TARGET_TYPE;
                requestData.data.targetType = LpsSaLoadRecordTargetType::SINGLE;

                { // Material Id
                    LpsSaJobMgrReqst request;
                    request.command = LpsSaJobMgrReqstCommand::WRITE_MATERIAL_ID;
                    request.materialId(static_cast<uint32_t>(j.instruction.materialId));
                    requestData.requests.push_back(std::move(request));
                }

                { // Material Name
                    LpsSaJobMgrReqst request;
                    request.command = LpsSaJobMgrReqstCommand::WRITE_MATERIAL_NAME;
                    request.materialName(j.instruction.materialName);
                    requestData.requests.push_back(std::move(request));
                }

                { // Material Density
                    LpsSaJobMgrReqst request;
                    request.command = LpsSaJobMgrReqstCommand::WRITE_MATERIAL_DENSITY;
                    request.materialDensity(0.f);
                    requestData.requests.push_back(std::move(request));
                }

                { // Truck Id
                    LpsSaJobMgrReqst request;
                    request.command = LpsSaJobMgrReqstCommand::WRITE_TRUCK_ID;
                    if ((j.instruction.truckId < 0) || (j.instruction.truckId > UINT32_MAX)) {
                        request.truckId(UINT32_MAX);
                    }
                    else {
                        request.truckId(static_cast<uint32_t>(j.instruction.truckId));
                    }
                    requestData.requests.push_back(std::move(request));
                }

                { // Truck Name
                    LpsSaJobMgrReqst request;
                    request.command = LpsSaJobMgrReqstCommand::WRITE_TRUCK_NAME;
                    request.truckName(j.instruction.truckName);
                    requestData.requests.push_back(std::move(request));
                }

                { // Truck Target Weight
                    LpsSaJobMgrReqst request;
                    request.command = LpsSaJobMgrReqstCommand::WRITE_TRUCK_TARGET_WEIGHT;
                    request.truckTargetWeight(j.instruction.targetMaterialWeight);
                    requestData.requests.push_back(std::move(request));
                }
            }
        }
        catch (...) {
            // Cannot find new job
        }

        // If there is a new job selected
        if (newJobId >= 0) {

            // Store this as the last selected job
            jobsData_.lastSelectedJobId = newJobId;

            // If the new job is different from the currently active job
            if (newJobId != jobsData_.activeJobId) {
                // Release the currently active job
                try {
                    woa_app::Job& j = jobsData_.jobs.at(jobsData_.activeJobId);
                    if (!j.isLoaded) {
                        j.state = woa_app::JobState::TODO;
                        j.stale = true;
                        oldJobId = jobsData_.activeJobId;
                    }
                    else {
                        // Job cannot be released, it is already loaded
                    }

                    // Freeze the job
                    if (oldJobId >= 0) {
                        jobsData_.freezeJob(oldJobId, j);
                    }
                }
                catch (...) {
                    // Cannot find active job.
                    // This could be because there wasn't an active job (jobsData_.activeJobId < 0)
                }

                // Whether we were able to release the old
                // job or not, we move to the new one.
                jobsData_.activeJobId = newJobId;
            }
        }
    }

    // Send the information to job manager if possible.
    if (nullptr != lpsSaJobMgrReqstChannelOutput_) {
        if (newJobId >= 0) {
            if (lpsSaJobMgrReqstChannelOutput_->publish(requestData)) {
                AIS_LOG_INFO("Published job manager request to set job information.");
            }
            else {
                AIS_LOG_ERROR("Failed to publish job manager request to set job information.");
            }
        }
    }

    // Send the information to the back office if possible.
    if (pHubService_) {
        if ((siteId >= 0) && (newJobId >= 0)) {
            if (async) {
                /*
                 * Launch an async task to select the job.
                 *  std::async returns a future which blocks on destruction until the
                 *  ascynchronous task completes.  This means we cannot just throw the
                 *  returned future away, otherwise we will block.  We keep track of the
                 *  future in asyncFutures_ and periodically check them in executive.
                 */
                asyncFutures_.add(
                    std::async(std::launch::async, [this, siteId, newJobId, oldJobId, dateTime]() {
                        bool commResult = pHubService_->updateJobStatusStartDoing(siteId, newJobId, oldJobId, dateTime, loaderCode_);

                        // Report the communication result to the hub service monitor.
                        hubServiceMonitor_.reportCommTxResult(commResult);
                    })
                );
                success = true;
            }
            else {
                success = pHubService_->updateJobStatusStartDoing(siteId, newJobId, oldJobId, dateTime, loaderCode_);

                // Report the communication result to the hub service monitor.
                hubServiceMonitor_.reportCommTxResult(success);
            }
        }
    }

    return success;
}

/*
 * jobId - The job that you think you are releasing.  If it does not match the active job, nothing will happen
 */
bool WorkOrderAssistApp::releaseJob(int64_t jobId, bool async) {

    if (!isEnabled()) {
        // We are not enabled.
        return false;
    }

    bool success = false;
    int32_t siteId = -1;

    if (jobId >= 0) {
        activityMonitor_.reportActivity(); // Indicate new activity detected
        siteSelectionRefresher_.wakeAsync(); // Wake up the site selection refresher if asleep.
    }
    else {
        return false;
    }

    { // Update local job
        std::lock_guard<std::mutex> lock(jobsMutex_);

        // Only release the job if it is the currently active job
        if (jobsData_.activeJobId == jobId) {
            try {
                woa_app::Job& j = jobsData_.jobs.at(jobsData_.activeJobId);
                if ((j.state == woa_app::JobState::DOING) && (!j.isLoaded)) {
                    j.state = woa_app::JobState::TODO;
                    j.stale = true;
                    siteId = jobsData_.activeSiteId;
                    jobId = jobsData_.activeJobId;
                    jobsData_.freezeJob(jobId, j);
                }

                jobsData_.activeJobId = -1;
            }
            catch (...) {
                // Cannot find active job.
                jobId = -1;
            }
        }
        else {
            jobId = -1;
        }
    }

    // Send the information to job manager if possible.
    if (nullptr != lpsSaJobMgrReqstChannelOutput_) {
        if (jobId >= 0) {
            // Clear out the existing truck name
            LpsSaJobMgrReqstChannel requestData;

            { // Truck Id
                LpsSaJobMgrReqst request;
                request.command = LpsSaJobMgrReqstCommand::WRITE_TRUCK_ID;
                request.truckId(0);
                requestData.requests.push_back(std::move(request));
            }

            { // Truck Name
                LpsSaJobMgrReqst request;
                request.command = LpsSaJobMgrReqstCommand::WRITE_TRUCK_NAME;
                request.truckName(LpsSaLoadRecordChannel::defaultTag());
                requestData.requests.push_back(std::move(request));
            }

            if (lpsSaJobMgrReqstChannelOutput_->publish(requestData)) {
                AIS_LOG_INFO("Published job manager request to set job information.");
            }
            else {
                AIS_LOG_ERROR("Failed to publish job manager request to set job information.");
            }
        }
    }

    if (pHubService_) {
        if ((siteId >= 0) && (jobId >= 0)) {
            if (async) {
                /*
                 * Launch an async task to release the job.
                 *  std::async returns a future which blocks on destruction until the
                 *  ascynchronous task completes.  This means we cannot just throw the
                 *  returned future away, otherwise we will block.  We keep track of the
                 *  future in asyncFutures_ and periodically check them in executive.
                 */
                asyncFutures_.add(
                    std::async(std::launch::async, [this, siteId, jobId]() {
                        bool commResult = pHubService_->updateJobStatusStopDoing(siteId, jobId);

                        // Report the communication result to the hub service monitor.
                        hubServiceMonitor_.reportCommTxResult(commResult);
                    })
                );
                success = true;
            }
            else {
                success = pHubService_->updateJobStatusStopDoing(siteId, jobId);

                // Report the communication result to the hub service monitor.
                hubServiceMonitor_.reportCommTxResult(success);
            }
        }
    }

    return success;
}

/*
 * jobId - The job that you think you are completing.  If it does not match the active job, nothing will happen
 */
bool WorkOrderAssistApp::completeJob(int64_t jobId, int16_t passCount, float materialWeight, const woa_app::Job::TimePoint& dateTime, bool async) {

    if (!isEnabled()) {
        // We are not enabled.
        return false;
    }

    bool success = false;
    int32_t siteId = -1;

    if (jobId >= 0) {
        activityMonitor_.reportActivity(); // Indicate new activity detected
        siteSelectionRefresher_.wakeAsync(); // Wake up the site selection refresher if asleep.
    }
    else {
        return false;
    }

    { // Update local job
        std::lock_guard<std::mutex> lock(jobsMutex_);

        // Only complete the job if it is the currently active job
        if (jobsData_.activeJobId == jobId) {
            try {
                woa_app::Job& j = jobsData_.jobs.at(jobId);
                j.state = woa_app::JobState::DOING;
                j.isLoaded = true;
                j.result.loaderCode = loaderCode_;
                j.stale = true;
                siteId = jobsData_.activeSiteId;
                jobsData_.activeJobId = -1;
                jobsData_.freezeJob(jobId, j);
            }
            catch (...) {
                // Cannot find active job.
                jobId = -1;
            }
        }
        else {
            jobId = -1;
        }
    }

    // Send the information to job manager if possible.
    if (nullptr != lpsSaJobMgrReqstChannelOutput_) {
        if (jobId >= 0) {
            // Clear out the existing truck name
            LpsSaJobMgrReqstChannel requestData;

            { // Truck Id
                LpsSaJobMgrReqst request;
                request.command = LpsSaJobMgrReqstCommand::WRITE_TRUCK_ID;
                request.truckId(0);
                requestData.requests.push_back(std::move(request));
            }

            { // Truck Name
                LpsSaJobMgrReqst request;
                request.command = LpsSaJobMgrReqstCommand::WRITE_TRUCK_NAME;
                request.truckName(LpsSaLoadRecordChannel::defaultTag());
                requestData.requests.push_back(std::move(request));
            }

            if (lpsSaJobMgrReqstChannelOutput_->publish(requestData)) {
                AIS_LOG_INFO("Published job manager request to set job information.");
            }
            else {
                AIS_LOG_ERROR("Failed to publish job manager request to set job information.");
            }
        }
    }

    // This is to simulate communication delay for verifying robustness.
    //std::this_thread::sleep_for(std::chrono::seconds(60));

    if (pHubService_) {
        if ((siteId >= 0) && (jobId >= 0)) {
            if (async) {
                /*
                 * Launch an async task to complete the job.
                 *  std::async returns a future which blocks on destruction until the
                 *  ascynchronous task completes.  This means we cannot just throw the
                 *  returned future away, otherwise we will block.  We keep track of the
                 *  future in asyncFutures_ and periodically check them in executive.
                 */
                asyncFutures_.add(
                    std::async(std::launch::async, [this, siteId, jobId, passCount, materialWeight, dateTime]() {
                        bool commResult = pHubService_->updateJobStatusLoaded(siteId, jobId, passCount, materialWeight, dateTime, loaderCode_);

                        // Report the communication result to the hub service monitor.
                        hubServiceMonitor_.reportCommTxResult(commResult);
                    })
                );
                success = true;
            }
            else {
                success = pHubService_->updateJobStatusLoaded(siteId, jobId, passCount, materialWeight, dateTime, loaderCode_);

                // Report the communication result to the hub service monitor.
                hubServiceMonitor_.reportCommTxResult(success);
            }
        }
    }

    return success;
}

int64_t WorkOrderAssistApp::visitJobs(std::function<void(const woa_app::Job&)> visit) {

    if (!isEnabled()) {
        // We are not enabled.
        return -1;
    }

    activityMonitor_.reportActivity(); // Indicate new activity detected
    siteSelectionRefresher_.wakeAsync(); // Wake up the site selection refresher if asleep.

    { // Lock jobs and loop over them.
        std::lock_guard<std::mutex> lock(jobsMutex_);
        if (visit) {
            for (const auto& j : jobsData_.jobs) {
                visit(j.second);
            }
        }
    }

    return jobsData_.activeJobId;
}

void WorkOrderAssistApp::readSettings(WorkOrderAssistSettings& settings) const {
    settingsStorage_.getSettings(settings);
}

void WorkOrderAssistApp::writeSettings(const WorkOrderAssistSettings& settings) {
    settingsStorage_.setSettings(settings);
    settingsStorage_.save();
    publishSettings_ = true;
}

bool WorkOrderAssistApp::isEnabled() const {
    return settingsStorage_.isEnabled();
}

void WorkOrderAssistApp::jobsListener(std::vector<woa_app::Job>&& jobs, int64_t jobsHash) {
    { // Protect jobs data with mutex
        std::lock_guard<std::mutex> lock(jobsMutex_);

        // Ignore anything that is older than what we already have.
        if (jobsHash >= jobsData_.jobsHash) {
            std::unordered_map<int64_t, woa_app::Job> oldJobs;

            oldJobs.swap(jobsData_.jobs);
            // jobsData_.jobs is now empty

            jobsData_.delayedJobs.clear();

            // For any job that is frozen, just keep the version of the job we had
            for (auto& kv : jobsData_.jobFreezeTimes) {
                int64_t jobId = kv.first;
                auto ji = oldJobs.find(jobId);
                if (ji != oldJobs.end()) {
                    // Found it, move it over.
                    jobsData_.jobs.emplace(jobId, std::move(ji->second));
                }
            }

            for (auto& j : jobs) {
                // Totally ignore all jobs from 'other' sites
                if (j.siteId != jobsData_.activeSiteId) {
                    continue;
                }

                // A job will either be made active right away, or be delayed if it is frozen
                if (jobsData_.jobFreezeTimes.count(j.id) > 0) {
                    // It is frozen, delay this incoming job
                    AIS_LOG_INFO("Job %d delayed because it is frozen.", j.id);

                    jobsData_.delayedJobs.emplace(j.id, std::move(j));
                }
                else {
                    // This job is live, not frozen
                    jobsData_.jobs.emplace(j.id, std::move(j));
                }
            }

            jobsData_.updateActiveJobId(loaderCode_);

            jobsData_.jobsHash = jobsHash;
        }
        else {
            AIS_LOG_ERROR("Received jobsHash (%lld) is older than current jobsHash (%lld)", jobsHash, jobsData_.jobsHash);
        }
    }

    // Report the communication result to the hub service monitor.
    hubServiceMonitor_.reportCommRx();
}

void WorkOrderAssistApp::notifyLoadRecordInput() {
    // Check to see if we have any load records published,
    // indicating that a load/job is complete.
    if (nullptr != lpsSaLoadRecordChannelInput_) {
        LpsSaLoadRecordChannel data;
        if (lpsSaLoadRecordChannelInput_->get(data)) {
            // The simple rule is this, if a job is active, then it will be completed on the next store
            // as long as it is not an auto-store.
            if (LpsSaLoadRecordStoreAction::AUTO != data.storeAction()) {
                AIS_LOG_INFO("Load record received.");
                int64_t jobId = jobsData_.activeJobId;
                int16_t passCount = static_cast<int16_t>(data.passCount());
                float weightTonnes = data.weightTonnes();
                std::chrono::system_clock::time_point endTime = data.getCurrentSubtotal().endTime.utcTime;

                // This is to recreate the original issue.
                //std::this_thread::sleep_for(std::chrono::seconds(60));

                /*
                 * We cannot block here because it will block the entire SCS notification
                 *  system of any incoming inputs.  This happens to be the same system
                 *  that would notify us that the job has been updated.
                 */
                completeJob(jobId, passCount, weightTonnes, endTime, true);
            }
        }
    }
}

void WorkOrderAssistApp::updateTimeZoneInfo() {
    /* Receive local time offset and override the local time offset in chrono/print.hpp */
    if (nullptr != shmClockInput_) {
        ShmClock shmClock;
        while (shmClockInput_->get(shmClock)) {
            int32_t offset = shmClock.get_UTC_offset();
            tzone_tx_comm_struct tzone;
            if (tes_common_ais::get_tz_struct(tzone, shmClock)) {
                if ((tzInfo_.offset != offset) || (tzInfo_.index != tzone.tzone_id)) {
                    std::string tzStr = tes_common_ais::makeTZString(tzone);
                    if (tes_common_ais::setTZString(tzStr)) {
                        AIS_LOG_NOTICE("Set TZ environment variable to '%s'.", tzStr.c_str());
                        tes_common_ais::clearLocalTimeOffsetOverride();
                    }
                    else {
                        AIS_LOG_ERROR("Could not set TZ environment variable to '%s'.", tzStr.c_str());
                        tes_common_ais::setLocalTimeOffsetOverride(std::chrono::minutes(offset));
                    }
                    tzInfo_.offset = offset;
                    tzInfo_.index = tzone.tzone_id;
                }
            }
            else {
                AIS_LOG_ERROR("Could not get tzone_tx_comm_struct");
            }
        }
    }
}

void WorkOrderAssistApp::updateInstallStatus() {
    if (nullptr != autonomyConditionDiagnosticsTxInputChannel_) {
        bool received = false;
        bool installed = false;

        AutonomyConditionDiagnosticsTxInterface txData;
        while ( autonomyConditionDiagnosticsTxInputChannel_->get( txData ) )
        {
            for (const auto & element : txData.seaList){
                if (element.reason_code == LPS_SEA_REASON_CODE_245) {
                    installed = txData.checkSEAInstallStatus(element.status);
                    received = true;
                    break;
                }
            }
        }

        if (received) {
            WorkOrderAssistSettings settings;
            readSettings(settings);
            if (settings.installed != installed) {
                settings.installed = installed;
                writeSettings(settings);
            }
        }
    }
}

void WorkOrderAssistApp::updateLoaderCode() {
    if (nullptr != partNumbersInput_) {
        PartNumbers partNumbers;
        while (partNumbersInput_->get(partNumbers)) {
            if (partNumbers.IsProductIdNumSet()) {
                std::string loaderCode = partNumbers.GetProductIdNum();
                if (loaderCode != loaderCode_) {
                    loaderCode_.assign(std::move(loaderCode));
                    AIS_LOG_NOTICE("Loader code updated to %s", loaderCode_.c_str());
                }
            }
        }
    }
}

void WorkOrderAssistApp::updateFrozenJobs() {
    std::lock_guard<std::mutex> lock(jobsMutex_);

    // Update frozen jobs when they become unfrozen
    jobsData_.updateFrozenJobs();

    // Update the active job id if anything changed due to jobs
    // getting unfrozen.
    jobsData_.updateActiveJobId(loaderCode_);
}

bool WorkOrderAssistApp::ActivityMonitor::update(task::Task* pTask) {
    // Update the max count (probably didn't change)
    if (nullptr != pTask) {
        maxCount_ = static_cast<uint32_t>(NO_ACTIVITY_TIME_SEC * static_cast<float>(pTask->getCycleRateHz()));
    }

    // Update the count
    // Need to use post-increment here because we want to compare the value before incrementing it.
    if (count_++ >= UINT32_MAX) {
        count_ = UINT32_MAX;
    }

    return isActivityDetected();
}

bool WorkOrderAssistApp::SiteSelectionRefresher::start(IApp* pApp, uint16_t periodSeconds) {
    stop(); // Kill if currently running

    pApp_ = pApp;
    periodSeconds_ = periodSeconds;
    countSeconds_ = 0;

    // Start up a new thread
    stop_ = false;
    sleeping_ = true;
    t_ = std::thread([this]() { run(); });

    return true;
}

void WorkOrderAssistApp::SiteSelectionRefresher::stop() {
    stop_ = true;
    try {
        // Wait for the thread to die.
        t_.join();
    }
    catch (const std::system_error& e) {
        // Not joinable
    }
}

void WorkOrderAssistApp::SiteSelectionRefresher::sleep() {
    if (!sleeping_) {
        AIS_LOG_ALERT("Site selection refresh is going to sleep.");
    }
    sleeping_ = true;
}

bool WorkOrderAssistApp::SiteSelectionRefresher::wake(bool forceSelection) {
    bool success = false;

    if (sleeping_) {
        AIS_LOG_ALERT("Site selection refresh is waking up.");
    }

    // Only wake up if we are sleeping or we are being forced to issue the site selection
    if (forceSelection || sleeping_) {
        // While we are refreshing the site, pause the refresh thread
        // Don't worry about the race condition, the worst that can happen
        // is that we send two site selection messages.
        sleeping_ = true;

        // Reset the counter
        countSeconds_ = 0;

        // If refresh now is desired, then refresh now if possible.
        if (nullptr != pApp_) {
            success = pApp_->refreshSite();
            if (!success) {
                countSeconds_ = periodSeconds_.load(); // Force a retry
            }
        }

        // Signal we are no longer sleeping.
        sleeping_ = false;
    }
    else {
        // Already awake.
        success = true;
    }

    return success;
}

void WorkOrderAssistApp::SiteSelectionRefresher::wakeAsync() {
    if (sleeping_) {
        // Force a site selection at the next opportunity
        countSeconds_ = periodSeconds_.load();

        // Signal we are no longer sleeping
        sleeping_ = false;
    }
}

void WorkOrderAssistApp::SiteSelectionRefresher::run() {
    while (!stop_) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // If we are sleeping, just skip the rest
        if (sleeping_) {
            continue;
        }

        // We have waited one more second
        ++countSeconds_;

        // If we have waited enough seconds, refresh the site.
        if (countSeconds_ >= periodSeconds_) {

            // Reset the counter
            countSeconds_ = 0;

            if (nullptr != pApp_) {
                if (!pApp_->refreshSite()) {
                    countSeconds_ = periodSeconds_.load(); // Force a retry
                }
            }
        }
    }
}

void WorkOrderAssistApp::JobsData::updateActiveJobId(const std::string& loaderCode) {

    // Initialize last selected job id if needed
    if (lastSelectedJobId < 0) {
        // This is for first time initialization of the last selected job id
        for (auto& kv : jobs) {
            const woa_app::Job& j = kv.second;

            /*
             * We haven't yet selected a job, we need to latch onto one if
             * the back office says that we do have a selected job.
             * This only works if we have configured a loader code.
             */
            if ((loaderCodeDefiniteMatch(loaderCode, j.result.loaderCode)) &&
                    (j.state == woa_app::JobState::DOING) &&
                    (!j.isLoaded)) {
                // Whoa! This is my job!
                lastSelectedJobId = j.id;
                break;
            }
        }
    }

    /*
     * There is a race condition with setting a job state and getting the updated list from the
     * back office, we could end up setting the active job right after we unselected it.
     *
     * Example #1 - Job Loaded:
     *  - Back office sends job list
     *  - We complete the active job (send "loaded" message to back office and update local cache)
     *      jobsData_.activeJobId == -1 and job is loaded
     *  - We receive the job list from the back office (without the most recently loaded job updated)
     *      Since jobsData_.activeJobId < 0, and the job is "doing" and not loaded,
     *      jobsData_.activeJobId gets set to the job that was just loaded
     *  - Back office receives "loaded" message and processes it
     *  - Back office sends job list
     *  - We receive the job list from the back office (with the most recently loaded job updated)
     *      Since jobsData_.activeJobId >= 0, and the job is "doing" and loaded,
     *      jobsData_.activeJobId gets set to -1
     *
     * Example #2 - Job Released:
     *  - Back office sends job list
     *  - We release the active job (send "stop doing" message to back office and update local cache)
     *      jobsData_.activeJobId == -1 and job is to-do
     *  - We receive the job list from the back office (without the most recently released job updated)
     *      Since jobsData_.activeJobId < 0, and the job is "doing" and not loaded,
     *      jobsData_.activeJobId gets set to the job that we just unselected
     *  - Back office receives the "stop doing" message and processes it
     *  - Back office sends job list
     *  - We receive the job list from the back office (with the most recently released job updated)
     *      Since jobsData_.activeJobId >= 0, and the job is "to-do"
     *      jobsData_.activeJobId gets set to -1
     *
     * Example #3 - Job Selected:
     *  - Back office sends job list
     *  - We select an active job
     *      Send "stop doing" for previously active job and update local cache.
     *      Send "start doing" for newly active job and update local cache.
     *      jobsData_.activeJobId >= 0 and job is doing
     *  - We receive the job list from the back office (without the most recent changes)
     *      Since jobsData_.activeJobId >= 0, but the active job state is still "to-do",
     *      jobsData_.activeJobId gets set to -1
     *  - Back office received and processes the "stop doing" and "start doing" messages
     *  - Back office sends job list
     *  - We receive the job list from the back office (with the most recent changes)
     *      Since jobsData_.activeJobId < 0, but jobsData_.lastSelectedJobId is >= 0 and the job is "doing" and not loaded,
     *      jobsData_.activeJobId gets set to jobsData_.lastSelectedJobId
     *
     * The race condition is auto-mending.
     * The worst that would happen is that the UI briefly shows the intermediate state before
     *  correcting itself.
     */

    // If we have an active job, see if we shouldn't
    if (activeJobId >= 0) {
        JobsData::JobMap::const_iterator ji = jobs.find(activeJobId);
        if (ji != jobs.end()) {
            // The active job is in the list
            const woa_app::Job& j = ji->second;
            if ((j.state != woa_app::JobState::DOING) || (j.isLoaded)) {
                /* This job is not "doing" or already loaded */
                activeJobId = -1;
            }
            else if (loaderCodeDefiniteMismatch(loaderCode, j.result.loaderCode)) {
                // The loader code doesn't match, it's not mine.
                activeJobId = -1;
            }
        }
        else {
            // The active job is not here
            activeJobId = -1;
        }
    }

    // If we don't have an active job, see if we can find one
    if (activeJobId < 0) {
        /*
         * The active job is the job that:
         *  - Was last selected
         *  - Is "doing"
         *  - Is not loaded
         *  - Is equal to my loader code (or at least possibly equal)
         */
        for (auto& kv : jobs) {
            const woa_app::Job& j = kv.second;
            if (j.id == lastSelectedJobId) {
                if ((j.state == woa_app::JobState::DOING) && (!j.isLoaded)) {
                    /* The last selected job is "doing" and not loaded, is it mine? */
                    if (loaderCodePossibleMatch(loaderCode, j.result.loaderCode)) {
                        /* If my loader code matches, then it is mine, even if it is empty. */
                        activeJobId = j.id;
                        break;
                    }
                }
            }
        }
    }
}

void WorkOrderAssistApp::JobsData::updateFrozenJobs() {
    auto steadyNow = std::chrono::steady_clock::now();

    auto fji = jobFreezeTimes.begin(); // Frozen Job index
    while (fji != jobFreezeTimes.end()) {
        bool dropFreezeTime = false;

        if (steadyNow >= (fji->second + std::chrono::seconds(static_cast<std::chrono::seconds::rep>(JOB_CACHE_FREEZE_MAX_TIME_SEC)))) {
            int64_t jobId = fji->first;

            // We have a job that should be unfrozen
            // see if it is in the delayed list
            auto dji = delayedJobs.find(jobId);
            if (dji != delayedJobs.end()) {
                // Found a delayed job, need to apply it
                AIS_LOG_INFO("Job %d unfrozen due to timeout.", jobId);
                jobs[jobId] = dji->second;
                delayedJobs.erase(dji);
            }
            else {
                // Did not find a delayed job, must be gone.
                AIS_LOG_INFO("Freeze timeout, did not find a delayed job %d, must be gone.", jobId);
                jobs.erase(jobId);
            }

            dropFreezeTime = true;
        }
        else if (steadyNow >= (fji->second + std::chrono::seconds(static_cast<std::chrono::seconds::rep>(JOB_CACHE_FREEZE_MIN_TIME_SEC)))) {
            int64_t jobId = fji->first;

            /*
             * The job has been frozen for at least the minimum amount of time.
             * If the state of the delayed job matches the state that we have frozen, and the delayed job is not stale, then take it off ice.
             */
            auto ji = jobs.find(jobId);
            if (ji != jobs.end()) {
                woa_app::Job& j = ji->second;

                // We have a frozen copy of the job, see if we have a fresh delayed one.
                auto dji = delayedJobs.find(jobId);
                if (dji != delayedJobs.end()) {
                    // We have a delayed one, is it fresh?
                    const woa_app::Job& dj = dji->second;
                    if (!dj.stale) {
                        // We have a delayed job, and it is fresh, see if it matches our state.
                        if ((dj.state == j.state) && (dj.isLoaded == j.isLoaded)) {
                            // It matches, unfreeze.
                            AIS_LOG_INFO("Job %d unfrozen due to matching state.", jobId);
                            j = dj;
                            delayedJobs.erase(dji);
                            dropFreezeTime = true;
                        }
                    }
                }
                else {
                    // We don't have a delayed one, it is gone, see if we agree it should be gone.
                    if ((woa_app::JobState::DOING == j.state) && (j.isLoaded)) {
                        AIS_LOG_INFO("Job %d unfrozen due to matching loaded state.", jobId);
                        jobs.erase(ji);
                        dropFreezeTime = true;
                    }
                }
            }
            else {
                // We don't have any knowledge of this job... weird.
                delayedJobs.erase(jobId);
                dropFreezeTime = true;
                AIS_LOG_INFO("Job %d unfrozen, but we don't have a frozen copy of it... weird.", jobId);
            }
        }

        if (dropFreezeTime) {
            // We can drop this from the list of freeze times
            fji = jobFreezeTimes.erase(fji);
        }
        else {
            // Move to the next freeze time.
            ++fji;
        }
    }
}

void WorkOrderAssistApp::JobsData::freezeJob(const int64_t& jobId, const woa_app::Job& j) {
    // Put this job on ice
    // If the freeze time expires and we don't have anything new reported by
    // the back office, then we will just restore the job state to this.
    delayedJobs[jobId] = j;

    // This job can be unfrozen later
    jobFreezeTimes[jobId] = std::chrono::steady_clock::now();

    AIS_LOG_INFO("Job %d frozen.", jobId);
}

/*
 * Add a future to the queue of futures so that we can wait for them to finish
 */
void WorkOrderAssistApp::AsyncFutures::add(std::future<void>&& f) {
    std::lock_guard<std::mutex> lock(mtx_);
    futures_.push(std::move(f));
}

/*
 * Checks to next future on the queue to see if it is ready.
 *  If it is ready, already done, it gets rid of it.
 *  If it is deferred, it performs the task, then gets rid of it.
 *  It only does one at and time and return true if there was a future in the queue.
 */
bool WorkOrderAssistApp::AsyncFutures::checkNext() {
    std::unique_lock<std::mutex> lock(mtx_);
    bool empty = futures_.empty();
    if (!empty) {
        auto& f = futures_.front();
        if (f.valid()) {
            if (f.wait_for(std::chrono::seconds(0)) != std::future_status::timeout) {
                /*
                 * It's either ready or deferred.
                 * If it is ready, then we can just get rid of it.
                 * If it is deferred, we can get rid of it, but the destructor will block
                 *  as the deferred action is taken so we should unlock first before
                 *  allowing it to destruct.
                 */
                auto ftemp(std::move(f)); // Move the future away from the queue
                futures_.pop(); // Get rid of the now moved/invalid front
                lock.unlock(); // Unlock before the wait
                ftemp.wait(); // If ready, this does nothing.  If deferred, this will perform the action.
            }
            else {
                // It's not ready, leave it on the queue.
            }
        }
        else {
            futures_.pop(); // Get rid of the invalid front
        }
    }
    return !empty;
}

/*
 * Waits for the next future on the queue to be ready.
 *  It only does one at and time and return true if there was a future in the queue.
 */
bool WorkOrderAssistApp::AsyncFutures::waitNext() {
    std::unique_lock<std::mutex> lock(mtx_);
    bool empty = futures_.empty();
    if (!empty) {
        auto f(std::move(futures_.front()));
        futures_.pop(); // Get rid of the now moved/invalid front
        lock.unlock();

        if (f.valid()) {
            // Wait for the future to be ready (finish)
            f.wait();
        }
    }
    return !empty;
}

static inline bool loaderCodeDefiniteMatch(const std::string& localLoaderCode, const std::string& remoteLoaderCode) {
    bool definiteMatch = false;
    if ((!localLoaderCode.empty()) &&
            (!remoteLoaderCode.empty()) &&
            (remoteLoaderCode.find(localLoaderCode) != std::string::npos)) {
        definiteMatch = true;
    }
    return definiteMatch;
}

static inline bool loaderCodePossibleMatch(const std::string& localLoaderCode, const std::string& remoteLoaderCode) {
    bool possibleMatch = false;
    if (localLoaderCode.empty() || remoteLoaderCode.empty()) {
        possibleMatch = true;
    }
    else if (remoteLoaderCode.find(localLoaderCode) != std::string::npos) {
        possibleMatch = true;
    }
    return possibleMatch;
}

static inline bool loaderCodeDefiniteMismatch(const std::string& localLoaderCode, const std::string& remoteLoaderCode) {
    bool definiteMismatch = false;
    if ((!localLoaderCode.empty()) &&
            (!remoteLoaderCode.empty()) &&
            (remoteLoaderCode.find(localLoaderCode) == std::string::npos)) {
        definiteMismatch = true;
    }
    return definiteMismatch;
}
