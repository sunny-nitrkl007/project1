#include <fileio/directory.hpp>
#include <catdl/BMI_CDL_PID_Coaching.h>
#include "CoachingTask.h"
#include <catdllib_fid_def.h>           // for UNKNOWN1U
#include "version/version.h"        // for getversion()


using namespace task;

AbstractTaskCore *task::getTaskImplementation(void)
{
    static CoachingTask thisTask("CoachingTask");
    return dynamic_cast<Task *>(&thisTask);
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Constructs an instance of this class.
///
///////////////////////////////////////////////////////////////////////////////
CoachingTask::CoachingTask(const std::string& taskName ):
    Task{taskName},
    coachingShowHideStatusOutput{nullptr},
    coachingSummaryDataOutput{nullptr},
    coaching3x3DataOutput{nullptr},
    coachingTipHistoryOutput{nullptr},
    dataLinkDataInput{nullptr},
    breadcrumbLogOutput{nullptr},
    shmClockInput{nullptr},
    configs(getTaskConfig()),
    coachingAppSpecific{nullptr},
    coachingDataPath{DefaultCoachingDataPath},
    cycleRate_hz{0.0f},
    maxSavedOperators{15},
    BreadcrumbRequestedRecords{0},
    BreadcrumbMaxRecords{0},
    BreadcrumbMinRecords{0},
    BreadcrumbGpsTimeSeconds{60},
    BreadcrumbGpsDistanceMeters{50},
    displayRequiredTimeSeconds{30},
    nvmWriteWaitTimeSeconds{360},
    nvmWriteSecondsSinceEpoch{0},
    algorithmWmaWindowHrs{1.0},        // can't divide by zero, default to 1.0 hr
    algorithmIsPoisson{true},
    videoPath{DefaultVideoPath},
    shuttingDown{false},
    coachingSystemEnabled{false},
    coachingEnabledDefault{false},
    coachingInstalledDefault{false},
    coachingFake_SafeState{false},
    tipAutoEnableTimeSeconds_wsFlag{false},
    wsMutex{},
    pServer{nullptr},
    wsTimers{}
{
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys this class
///
///////////////////////////////////////////////////////////////////////////////
CoachingTask::~CoachingTask()
{
}


///////////////////////////////////////////////////////////////////////////////
/// @Coaching task Initialize function.
///////////////////////////////////////////////////////////////////////////////
bool CoachingTask::initialize()
{
    if (!task::InterfaceDb::bind("CoachingShowHideStatusOutput", coachingShowHideStatusOutput) ||
        !task::InterfaceDb::bind("CoachingSummaryDataOutput", coachingSummaryDataOutput) ||
        !task::InterfaceDb::bind("Coaching3x3DataOutput", coaching3x3DataOutput) ||
        !task::InterfaceDb::bind("CoachingTipHistoryOutput", coachingTipHistoryOutput) ||
        !task::InterfaceDb::bind("BreadcrumbLogOutput", breadcrumbLogOutput) ||
        !task::InterfaceDb::bind("DataLinkDataInput", dataLinkDataInput) ||
        !task::InterfaceDb::bind("ShmClockInput", shmClockInput))
    {
        return false;
    }

    // Retreive InternalMSN and enable coaching if it is != NOT_SET
    ConfigSection machineType;
    if (!getTaskParser().getSection("MachineType1", machineType))
    {
        AIS_LOG_ERROR("MachineType section not found, coaching is disabled");
    }
    else
    {
        if (machineType.get("InternalMsn", coachingShowHideStatus.internalMsn))
        {
            std::string internalMsnNotSet;
            if (configs.get("internalMsnNotSet", internalMsnNotSet) && coachingShowHideStatus.internalMsn != internalMsnNotSet)
            {
                coachingSystemEnabled = true;
            }
            else
            {
                AIS_LOG_WARN("InternalMsn is invalid (%s), coaching is disabled", internalMsnNotSet.c_str());
            }
        }
        else
        {
            AIS_LOG_ERROR("InternalMsn not not found, coaching is disabeld");
        }
    }

    // Create the websocket server
    uint16_t serverPort = DefaultWsPort;
    configs.get("serverPort", serverPort);

    pServer = std::unique_ptr<coaching_task::Server>(new coaching_task::Server(this, serverPort));
    if (pServer == nullptr)
    {
        AIS_LOG_ERROR("Failed to create server at port %u", serverPort);
        return false;
    }

    // Load default NVM path from config
    std::string configCoachingDataPath;
    if (!configs.get("coachingDataPath", configCoachingDataPath))
    {
        AIS_LOG_WARN("Failed to retreive coachingDataPath from NVM");
    }
    else
    {
        coachingDataPath = configCoachingDataPath;
    }
    AIS_LOG_INFO("Storage Root: %s", coachingDataPath.c_str());

    // Get Video Path from config
    std::string configVideoPath;
    if (!configs.get("videoPath", configVideoPath))
    {
        AIS_LOG_WARN("Unable to retrieve videoPath from config, using default: %s", videoPath.c_str());
    }
    else
    {
        videoPath = configVideoPath;
    }

    // Initialize tips
    coachingAppSpecific = CoachingAppSpecific::getAppSpecific(*this, coachingSummaryData, coaching3x3DataList);
    if (coachingAppSpecific == nullptr)
    {
        AIS_LOG_FATAL("coachingAppSpecific is NULL");
        return false;
    }

    // Initialize Coachging Tip History, should be done before loaded from NVM
    // publish after 10 seconds have passed to allow PCM to start all tasks
    coachingTipHistory.initialize(configs);
    tipHistoryStartupTimer.setTimeoutSec(10);
    tipHistoryStartupTimer.enableTimer();

    if (!coachingAppSpecific->initialize())
    {
        return false;
    }

    // Initialize breadcrumb log max records (can be overriden by NVM and UI)
    if (!configs.get("maxBreadcrumbRecords", BreadcrumbMaxRecords) ||
        !configs.get("maxRequestedBreadcrumbRecords", BreadcrumbRequestedRecords) ||
        !configs.get("minBreadcrumbRecords", BreadcrumbMinRecords) ||
        (BreadcrumbMinRecords > BreadcrumbMaxRecords))
    {
        AIS_LOG_FATAL("Unable to retrieve breadcrumbRecord settings from config");
        return false;
    }
    BreadcrumbRequestedRecords = limit(BreadcrumbRequestedRecords, BreadcrumbMinRecords, BreadcrumbMaxRecords);

    // Load breadcrumb GPS Time and Distance max configuration if available
    configs.get("maxBreadcrumbGpsTimeSeconds", BreadcrumbGpsTimeSeconds);
    AIS_LOG_INFO("BreadcrumbGpsTimeSeconds %d", BreadcrumbGpsTimeSeconds);
    configs.get("maxBreadcrumbGpsDistanceMeters", BreadcrumbGpsDistanceMeters);
    AIS_LOG_INFO("maxBreadcrumbGpsDistanceMeters %d", BreadcrumbGpsDistanceMeters);

    // Load 3x3, Summary, Breadcrumb records and Operator ID List from NVM
    configs.get("maxSavedOperators", maxSavedOperators);
    loadOperatorIdList();
    setOperatorId(DefaultOperatorId);

    // Initialize cycleRates
    if (!configs.get("cycleRate_hz", cycleRate_hz))
    {
        AIS_LOG_FATAL("Unable to retrieve cycleRate_hz from config");
        return false;
    }

    // Get reset time for Coaching Tip Summary Display Requirement Status
    configs.get("coachingTipSummaryDisplayRequiredTimeSeconds", displayRequiredTimeSeconds);

    // Get NVM Write Wait Time
    configs.get("NVMWriteWaitTimeSeconds", nvmWriteWaitTimeSeconds);

    // Set video path and operator ID
    setMetadata();

    // Trigger Key-On event
    breadcrumbLog.keyOn();

    // reset CoachingSummaryData::displayPageID to ZERO
    setTipViewed(0);

    // Set Show/Hide status flags (default to false)
    configs.get("coachingShowHidePracticeSupported", coachingShowHideStatus.practiceSupported);
    configs.get("coachingShowHideMapSupported", coachingShowHideStatus.mapSupported);

    // Set Coaching Enabled/Installed defaults (default to false)
    configs.get("coachingEnabledDefault", coachingEnabledDefault);
    configs.get("coachingInstalledDefault", coachingInstalledDefault);

    // Set Coaching FAKE SafeState (default to false)
    configs.get("coachingFake_SafeState", coachingFake_SafeState);

    // Start the Web Server
    std::lock_guard<std::mutex> lock(wsMutex);
    if (pServer->start())
    {
        AIS_LOG_INFO("Web server started.");
    }
    else
    {
        AIS_LOG_ERROR("Could not start web server.");
        pServer.reset();
        return false;
    }

    // Returns running Software Version string: "5946660-03Sep2020T03 SHA-1"
    std::string str= getversion();
    std::size_t pos = str.find(" ");      // position of " " in str
    std::string softwareVersion = str.substr(0,pos).c_str();
    coachingShowHideStatus.softwareVersion = softwareVersion;

    std::string configCoachingLanguagePath;
    if (!configs.get("coachingLanguagePath", configCoachingLanguagePath))
    {
        AIS_LOG_WARN("Failed to retreive coachingLanguagePath from .rb");
    }
    else
    {
        coachingShowHideStatus.langugeUrl = configCoachingLanguagePath;
    }
    AIS_LOG_INFO("languageUrl: %s", coachingShowHideStatus.langugeUrl.c_str());

    // Get Star % update Rate seconds
    configs.get("algorithmWmaWindowHrs", algorithmWmaWindowHrs);
    if ( 0 >= algorithmWmaWindowHrs)
    {
        algorithmWmaWindowHrs = 1.0;    // default to 1 hour, valu eMUST be greater than ZERO
    }
    coachingSummaryData.algorithmWmaWindowHrs = algorithmWmaWindowHrs;

    // Get AlgorithmType.... WMA or POISSON
    algorithmIsPoisson = true;                          // default
    coachingSummaryData.algorithmIsPoisson = true;      // default
    std::string configAlgorithmType;
    if (!configs.get("algorithmType", configAlgorithmType))
    {
        AIS_LOG_ALERT("Failed to retreive algorithmType, using POISSON");
    }
    else
    {
        if (configAlgorithmType == "WMA")
        {
            algorithmIsPoisson = false;
            coachingSummaryData.algorithmIsPoisson = false;
        }
    }
    AIS_LOG_ALERT("algorithmType: %s    %f", (coachingSummaryData.algorithmIsPoisson ? "POISSON" : "WMA"), algorithmWmaWindowHrs);


    // Read configuration from selected Robot_???????.rb
    auto& taskParser = getTaskParser();
    ConfigSection machineSpecificConfig;
    if (!taskParser.getSection("MachineSpecificConfig",machineSpecificConfig))
    {
        AIS_LOG_WARN("MachineSpecificConfig section not found");
    }
    else
    {
        machineSpecificConfig.getRequiredParam("coachingShowHideStandAloneUiSupported", coachingShowHideStatus.standAloneUiSupported);
    }
    AIS_LOG_ALERT("standAloneUiSupported = %d", coachingShowHideStatus.standAloneUiSupported);

    return true;
}

///////////////////////////////////////////////////////////////////////////////
/// @Coaching task executive function.
///////////////////////////////////////////////////////////////////////////////
bool CoachingTask::executive()
{
    // Prevent contention with websocket server
    std::lock_guard<std::mutex> lock(wsMutex);

    // Read SHM
    ShmClock shmClock;
    while (shmClockInput->get(shmClock))
    {
        coachingTipHistory.setShmSec(shmClock.get_SHM());
    }

    // Handle dataLinkData objects from all Bmi sources
    DataLinkData dataLinkData;
    while (dataLinkDataInput->get(dataLinkData))
    {
        // Parse dataLinkData object and set the Tip input globals
        coachingAppSpecific->getAndSetInputs(dataLinkData);
        // Provide GPS data to BreadcrumbLog
        DataLinkParam* dlParam;
        if (dataLinkData.GetParam(dlParam, GPSDataLinkParam::m_Pid, DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID))
        {
            checkGPS(dlParam);
        }

        // Check if Operator ID changed
        if (dataLinkData.GetParam(dlParam, SecuritySystemCurrentSecurityIDParam::CatExtId, DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID) ||
            dataLinkData.GetParam(dlParam, SecuritySystemCurrentSecurityIDParam::CatExtId, DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT))
        {
            if (0 == dlParam->GetVarLengthParamDsi())
            {
                const SecuritySystemCurrentSecurityIDParam idParam(*dlParam);
                std::string operatorId;
                if (idParam.getIDDescription(operatorId))
                {
                    // clean up response...remove any NULL characters
                    // Note: some responses contain all 0x00, some end with 0x00
                    operatorId.erase(std::find(operatorId.begin(), operatorId.end(), '\0'), operatorId.end());
                    AIS_LOG_INFO("Operator ID received from $%X: %s", SecuritySystemCurrentSecurityIDParam::CatExtId, operatorId.c_str());

                    if (operatorId.size() > 0)
                    {
                        setOperatorIdImpl(operatorId);
                    }
                    else
                    {
                        setOperatorIdImpl(DefaultOperatorId);   // set back to "None" if empty string
                    }
                }
                else
                {
                    AIS_LOG_INFO("OperatorID: fail... getDescription()  length:%d", idParam.getIDDescriptionLength());
                }
            }
            else
            {
                AIS_LOG_INFO("OperatorID: DSI");
            }
        }

        // Read $0xFFFF for Tip number to Trigger, if 0 do nothing
        uint32_t testTipTrigger;
        if (dataLinkData.GetLastPIDValueIfReceived(0xFFFF, testTipTrigger))
        {
            if (testTipTrigger)     // non Zero
            {
        		AIS_LOG_INFO("TipTrigger: %d", testTipTrigger);
                coachingSummaryData.setTipIncrement(testTipTrigger);
            }
        }
    }

    // Set machineInSafeState, coachingEnabled, coachingInstalled for SCS channels
    bool machineInSafeState = coachingAppSpecific->isMachineInSafeState();

    if (coachingFake_SafeState) // If Enable, Toggle machine_SafeState
    {
        static uint8_t counter = 0;
        if (counter++ > 128)
        {
            machineInSafeState = true;
        }
        else
        {
            machineInSafeState = false;
        }
        AIS_LOG_ALERT("coachingFake_SafeState: %d state:%d  counter:%d", coachingFake_SafeState, machineInSafeState, counter); // keep announcing this while TESTING
    }

    coachingSummaryData.machineInSafeState = machineInSafeState;
    for (auto &coaching3x3Data : coaching3x3DataList)
    {
        coaching3x3Data.machineInSafeState = machineInSafeState;
    }

    // Publish Show/Hide Status
    switch (coachingAppSpecific->getCoachingEnabledStatus())
    {
    case CoachingStatus::UNKNOWN:
    case CoachingStatus::FAULTED:
        coachingShowHideStatus.coachingEnabled = coachingEnabledDefault;
        break;
    case CoachingStatus::ENABLED:
        coachingShowHideStatus.coachingEnabled = coachingSystemEnabled;
        break;
    default: // CoachingStatus::DISABLED:
        coachingShowHideStatus.coachingEnabled = false;
        break;
    }

    switch (coachingAppSpecific->getCoachingInstalledStatus())
    {
    case CoachingStatus::UNKNOWN:
    case CoachingStatus::FAULTED:
        coachingShowHideStatus.coachingInstalled = coachingInstalledDefault;
        break;
    case CoachingStatus::ENABLED:
        coachingShowHideStatus.coachingInstalled = coachingSystemEnabled;
        break;
    default: // CoachingStatus::DISABLED:
        coachingShowHideStatus.coachingInstalled = false;
        break;
    }

    switch (coachingAppSpecific->getCoachingTempInstalledStatus())
    {
    case CoachingStatus::UNKNOWN:
    case CoachingStatus::FAULTED:
        coachingShowHideStatus.coachingTempInstalled = coachingInstalledDefault;
        break;
    case CoachingStatus::ENABLED:
        coachingShowHideStatus.coachingTempInstalled = coachingSystemEnabled;
        break;
    default: // CoachingStatus::DISABLED:
        coachingShowHideStatus.coachingTempInstalled = false;
        break;
    }

    coachingShowHideStatus.coachingTempTime = coachingAppSpecific->getCoachingTempTime();

    // Check SEA flags so the UI can behavior properly
    if (coachingShowHideStatus.coachingInstalled && coachingShowHideStatus.coachingEnabled)
    {
        coachingShowHideStatus.coachingTempInstalled   = true;
        coachingShowHideStatus.coachingTempTime        = 65503;    // larges NON-DSI value
    }
    else if (coachingShowHideStatus.coachingTempInstalled && (0 != coachingShowHideStatus.coachingTempTime))
    {
        coachingShowHideStatus.coachingInstalled   = true;
        coachingShowHideStatus.coachingEnabled     = true;
    }

    AIS_LOG_DEBUG("Install:%d  Enable:%d  Temp:%d Time:%d = I:%d E:%d", coachingAppSpecific->getCoachingInstalledStatus(), coachingAppSpecific->getCoachingEnabledStatus(), coachingAppSpecific->getCoachingTempInstalledStatus(), coachingAppSpecific->getCoachingTempTime(), coachingShowHideStatus.coachingInstalled, coachingShowHideStatus.coachingEnabled);

    // only set the SnoozeTime if Coaching Enabled
    if (coachingShowHideStatus.coachingInstalled && coachingShowHideStatus.coachingEnabled)
    {
        // Read Operator Coaching Tip Enable Timer Duration, update only on Change
        uint64_t  coachingTipSnoozeTimerHrs;
        if (dataLinkData.GetLastPIDValueIfReceived(BMI_CDL_PID_OPERATOR_COACHING_TIP_SNOOZE_TIMER, coachingTipSnoozeTimerHrs))
        {
            setTipAutoEnableTimeImpl(static_cast<uint64_t>(HoursToSeconds(static_cast<double>(coachingTipSnoozeTimerHrs))));
        }
    }

    coachingShowHideStatus.countOfBadges = coachingSummaryData.countOfBadges;
    coachingShowHideStatus.machineInSafeState = machineInSafeState;
    coachingShowHideStatus.diagnosticActiveFlag = coachingAppSpecific->isDiagnosticActiveFlag();
    coachingShowHideStatusOutput->publish(coachingShowHideStatus);

    checkBreadcrumbDlGoodBadStatus();   // check whether to add DL_GOOD or DL_BAD to BreadcrumbLog

    // Run the model and write to the real time output channel
    std::vector<CoachingTipResult_t> tipResults = coachingAppSpecific->updateModelTips();

    coachingSummaryData.updateTips(tipResults);
    coachingSummaryDataOutput->publish(coachingSummaryData);

    // Check for Tip triggering
    breadcrumbLog.updateTipResults(tipResults);
    auto publishTipHistory = coachingTipHistory.updateTipResults(tipResults);

    // loop thru all Cycles in coaching3x3OutList object and invoke Application Specific.update(), then publish
    for (auto &coaching3x3Data : coaching3x3DataList)
    {
        uint8_t cycleId = 0;
        // if cycle is running then update tip severity values
        bool cycleRunning = coachingAppSpecific->isCycleRunning(coaching3x3Data.name);
        bool cycleEnded   = coachingAppSpecific->isCycleEnded(coaching3x3Data.name);
        coaching3x3Data.update(coachingSummaryData.coachingTipOutputList, cycleRunning, cycleEnded);
        // publish if cycle has ended
        if (cycleEnded)
        {
            breadcrumbLog.incrementCycle(coaching3x3Data.name, cycleId);
            AIS_LOG_INFO("Cycle ended: %s", coaching3x3Data.name.c_str());
            coaching3x3DataOutput->publish(coaching3x3Data);
        }
        cycleId++;  // increment cycleId
    }

    // Check for Segment Changes AFTER Cycle-End check, want DUMP segment at start of Cycle
    uint8_t tempSegment = UNKNOWN1U;
    if (coachingAppSpecific->getCurrentSegment(tempSegment))
    {
        breadcrumbLog.segmentChange(tempSegment);
        AIS_LOG_INFO("Segment Changed To:%x",tempSegment);
    }

    // Publish to websocket
    for (size_t i = 0; i < wsTimers.size(); ++i)
    {
        if (wsTimers[i].isExpired())
        {
            sendDataToWs(static_cast<coaching_task::GrpId>(i));
        }
    }

    // Publish BreadcrumbLog
    if (breadcrumbLog.update())  // recordCounter is # of new records added since last update(),   save to NVM in case of Power-OFF, updates to Log not expected to happen very often and won't burn out NVM
    {
        if (0 == nvmWriteSecondsSinceEpoch)
        {
            nvmWriteSecondsSinceEpoch = std::time(NULL);	// assignt the currentTimeSecondsSinceEpoch to compare against
        }
        AIS_LOG_DEBUG("Need Write to NVM, seconds before write: %d", nvmWriteWaitTimeSeconds - (std::time(NULL) - nvmWriteSecondsSinceEpoch));
    }

    if (0 != nvmWriteSecondsSinceEpoch)		// wait for Time-Out to write to NVM, hopefully we get multiple updates before we write.
    {
        if (std::time(NULL) - nvmWriteSecondsSinceEpoch > nvmWriteWaitTimeSeconds)
        {
            saveCoachingRecords();
            AIS_LOG_DEBUG("Write NVM");
            nvmWriteSecondsSinceEpoch = 0;    // reset time for next
        }
    }

    //breadcrumbLogOutput->publish(breadcrumbLog);   // no one consumes, no need to publish, no need in hlogs

    // Publish Coaching Tip History
    if (publishTipHistory || tipHistoryStartupTimer.hasTimerExpired())
    {
        if (coachingShowHideStatus.coachingInstalled && coachingShowHideStatus.coachingEnabled)
        {
            coachingTipHistoryOutput->publish(coachingTipHistory);
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
/// @Sets operator ID and videoPath
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setMetadata()
{
    // Set video path and operator ID for Summary
    auto videoPathString = videoPath.string();
    coachingSummaryData.videoPath = videoPathString;
    coachingSummaryData.operatorName = activeOperatorId;
    coachingSummaryData.setCycleRate(cycleRate_hz);
    coachingSummaryData.displayRequiredTimeSeconds = displayRequiredTimeSeconds;
    coachingSummaryData.displayRequired = false;
    coachingSummaryData.setTipAutoEnableTime(coachingTipHistory.getTipAutoEnableTime()); // synch Summary with History
    coachingSummaryData.algorithmWmaWindowHrs = algorithmWmaWindowHrs;
    coachingSummaryData.algorithmIsPoisson = algorithmIsPoisson;

    // Set video path, operator ID for all 3x3 records
    for (auto &coaching3x3Data : coaching3x3DataList)
    {
        coaching3x3Data.videoPath = videoPathString;
        coaching3x3Data.operatorName = activeOperatorId;
    }

    // Set operator ID for breadcrumbs
    breadcrumbLog.operatorName = activeOperatorId;
    breadcrumbLog.setCycleRate(cycleRate_hz);

    // Set operator ID for Coaching
    coachingTipHistory.setActiveOperatorId(activeOperatorId);
}

///////////////////////////////////////////////////////////////////////////////
/// @Send corresponding data to websocket
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::sendDataToWs(coaching_task::GrpId grpId)
{
    switch (grpId)
    {
    case coaching_task::GRP_ID_SUMMARY:
        pServer->sendResponseData(grpId, coachingSummaryData);
        break;
    case coaching_task::GRP_ID_3X3:
        pServer->sendResponseData(grpId, coaching3x3DataList);
        break;
    case coaching_task::GRP_ID_BREADCRUMB:
        pServer->sendResponseData(grpId, breadcrumbLog);
        break;
    case coaching_task::GRP_ID_SHOW_HIDE_STATUS:
        pServer->sendResponseData(grpId, coachingShowHideStatus);
        break;
    default:
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @Wrapper function to sendDataToWs with mutex
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::sendData(coaching_task::GrpId grpId)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    sendDataToWs(grpId);
}

///////////////////////////////////////////////////////////////////////////////
/// @Set publishing rate for the provided grpId.  interval is in units of ms
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setPublishRate(coaching_task::GrpId grpId, uint32_t intervalMs)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    // Convert interval to cycles
    uint32_t cycles = cycleRate_hz * intervalMs / 1000;
    wsTimers[grpId].setTimer(cycles);
}

///////////////////////////////////////////////////////////////////////////////
/// @Reset Summary & 3x3 Data
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::resetStats()
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    AIS_LOG_DEBUG("################################ RESET ################################");
    coachingSummaryData.resetStats();
    coaching3x3DataList.resetStats();
    breadcrumbLog.commandReceived(BreadcrumbStatus::Type::RESET);   // remove only TIP records from breadcrumbLog

    // Set video path and operator ID
    setMetadata();
}

///////////////////////////////////////////////////////////////////////////////
/// @Set Operator Id and saves/loads from nvm
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setOperatorIdImpl(const std::string& operatorId)
{
    AIS_LOG_INFO("Operator ID Received: %s", operatorId.c_str());

    // When Operator changes, save current records to nvm, change operator,
    //  and read records from nvm for the new operator'
    if ((operatorId.size()) > 0 && (operatorId != activeOperatorId))
    {
        if (activeOperatorId.size() > 0)
        {
            breadcrumbLog.commandReceived(BreadcrumbStatus::Type::OPERATOR_INACTIVE);
            saveCoachingRecords();
        }
        activeOperatorId = operatorId;

        manageOperatorIdList();

        // Load records for current operator
        loadCoachingRecords();
        breadcrumbLog.commandReceived(BreadcrumbStatus::Type::OPERATOR_ACTIVE);
    }

    // Set operator ID for ShowHide
    coachingShowHideStatus.operatorName = operatorId;

    // Set operator ID for Coaching
    coachingTipHistory.setActiveOperatorId(activeOperatorId);

    coachingSummaryData.setTipAutoEnableTime(coachingTipHistory.getTipAutoEnableTime()); // synch Summary with History
    coachingSummaryData.algorithmWmaWindowHrs = algorithmWmaWindowHrs;
    coachingSummaryData.algorithmIsPoisson = algorithmIsPoisson;
}

///////////////////////////////////////////////////////////////////////////////
/// @Wrapper function to setOperatorIdImpl with mutex
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setOperatorId(const std::string& operatorId)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    setOperatorIdImpl(operatorId);
}


///////////////////////////////////////////////////////////////////////////////
/// @Set Tip Auto Enable Time 
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setTipAutoEnableTimeImpl(int64_t tipAutoEnableTimeSeconds)
{
    AIS_LOG_DEBUG("Snooze:%d oldSec:%d newSec:%d", tipAutoEnableTimeSeconds_wsFlag, coachingTipHistory.getTipAutoEnableTime(), tipAutoEnableTimeSeconds);

    if((tipAutoEnableTimeSeconds_wsFlag) || (0 == tipAutoEnableTimeSeconds))
    {
        AIS_LOG_DEBUG("Snooze.. IGNORE");
        tipAutoEnableTimeSeconds_wsFlag = false;
    }
    else
    {
        if (coachingTipHistory.getTipAutoEnableTime() != tipAutoEnableTimeSeconds)  // NOTE: testing PGT server using bmiEthernet, generates DataLinkData objects, which cause multiple breadcrumb records
        {
            AIS_LOG_DEBUG("Snooze.. CHANGE");
            coachingTipHistory.setTipAutoEnableTime(tipAutoEnableTimeSeconds);
            coachingSummaryData.setTipAutoEnableTime(tipAutoEnableTimeSeconds);
            breadcrumbLog.commandReceived(BreadcrumbStatus::Type::TIP_AUTOENABLE_TIME, tipAutoEnableTimeSeconds);
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
/// @Wrapper function to setTipAutoEnableTimeImpl with mutex
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setTipAutoEnableTime(int64_t tipAutoEnableTimeSeconds)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }
    setTipAutoEnableTimeImpl(tipAutoEnableTimeSeconds);
    tipAutoEnableTimeSeconds_wsFlag = true;             // value from Web Socket, ignore DLD next time
}

///////////////////////////////////////////////////////////////////////////////
/// @Wrapper function to setTipAutoEnableTimeImpl with mutex
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setElapsedTimeSec(int64_t elapsedTimeSec)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }
    coachingSummaryData.elapsedTimeHrs = static_cast<float>(elapsedTimeSec / 3600.0);   // convert to hours
}

///////////////////////////////////////////////////////////////////////////////
/// @Set Tip On or Off
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setOpTipOnOff(bool tipOn, uint32_t tipNumber)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    coachingSummaryData.setOpTipOnOff(tipOn, tipNumber);
    for (auto &coaching3x3Data : coaching3x3DataList)
    {
        coaching3x3Data.setOpTipOnOff(tipOn, tipNumber);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @Set Tip Show or Hide
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setSysTipShowHide(bool showTip, uint32_t tipNumber)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    coachingSummaryData.setSysTipShowHide(showTip, tipNumber);
    for (auto &coaching3x3Data : coaching3x3DataList)
    {
        coaching3x3Data.setSysTipShowHide(showTip, tipNumber);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @Notification that a tutorial was viewed for the provided tip
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setTutorialViewed(uint32_t tipNumber)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    coachingSummaryData.setTutorialViewed(tipNumber);
    //breadcrumbLog.commandReceived(BreadcrumbStatus::Type::TUTORIAL_VIEWED, tipNumber);
}

///////////////////////////////////////////////////////////////////////////////
/// @Notification that a tip was viewed for the provided tip
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setTipViewed(uint32_t tipNumber)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off    Ignore if Not SafeState
    if ((shuttingDown) || (!coachingShowHideStatus.machineInSafeState))
    {
        return;
    }

    coachingSummaryData.setTipViewed(tipNumber);    // setTipViewed() will IGNORE non TIP numbers
    //breadcrumbLog.commandReceived(BreadcrumbStatus::Type::TIP_VIEWED, tipNumber);
}

///////////////////////////////////////////////////////////////////////////////
/// @Notification that a tip INCREMENT ONLY for TESTING
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setTipIncrement(uint32_t tipNumber)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    coachingSummaryData.setTipIncrement(tipNumber);
}

///////////////////////////////////////////////////////////////////////////////
/// @Notification that a tip DECREMENT ONLY for TESTING
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setTipDecrement(uint32_t tipNumber)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    coachingSummaryData.setTipDecrement(tipNumber);
}

///////////////////////////////////////////////////////////////////////////////
/// @Override default value for maximum breadcrumb records for the active operator
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setBreadcrumbRequestedRecords(size_t BreadcrumbRequetsedRecords)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    this->BreadcrumbRequestedRecords = limit(BreadcrumbRequetsedRecords, BreadcrumbMinRecords, BreadcrumbMaxRecords);
    breadcrumbLog.setMaxRecords(this->BreadcrumbRequestedRecords);
    breadcrumbLog.commandReceived(BreadcrumbStatus::Type::SET_BREADCRUMB_RECORDS, BreadcrumbRequetsedRecords);
}

///////////////////////////////////////////////////////////////////////////////
/// @Override default value for maximum breadcrumb records for the active operator
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setBreadcrumbGpsTimeSeconds(size_t BreadcrumbGpsTimeSeconds)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    AIS_LOG_INFO("BreadcrumbGpsTimeSeconds %d", BreadcrumbGpsTimeSeconds);

    breadcrumbLog.setMaxTimeSeconds(BreadcrumbGpsTimeSeconds);
    breadcrumbLog.commandReceived(BreadcrumbStatus::Type::SET_BREADCRUMB_GPS_TIME_SECONDS, BreadcrumbGpsTimeSeconds);
}

///////////////////////////////////////////////////////////////////////////////
/// @Override default value for maximum breadcrumb records for the active operator
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::setBreadcrumbGpsDistanceMeters(size_t BreadcrumbGpsDistanceMeters)
{
    // Prevent contention with executive
    std::lock_guard<std::mutex> lock(wsMutex);

    // Ignore after key-off
    if (shuttingDown)
    {
        return;
    }

    AIS_LOG_INFO("BreadcrumbGpsDistanceMeters %d", BreadcrumbGpsDistanceMeters);

    breadcrumbLog.setMaxDistanceMeters(BreadcrumbGpsDistanceMeters);
    breadcrumbLog.commandReceived(BreadcrumbStatus::Type::SET_BREADCRUMB_GPS_DISTANCE_METERS, BreadcrumbGpsDistanceMeters);
}


///////////////////////////////////////////////////////////////////////////////
/// @Override default value for maximum breadcrumb records for the active operator
///   Must not be called by executive
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::checkBreadcrumbDlGoodBadStatus()
{
    static uint8_t counterDSI = 42;     // 42/(8.334Hz) = 5 second debounce
    static BreadcrumbStatus::Type currentDlState = BreadcrumbStatus::Type::DL_GOOD;

    if (coachingAppSpecific->isDiagnosticActiveFlag() && (BreadcrumbStatus::Type::DL_GOOD == currentDlState))
    {
        if (0 == counterDSI)
        {
            breadcrumbLog.commandReceived(BreadcrumbStatus::Type::DL_BAD, 1);
            currentDlState = BreadcrumbStatus::Type::DL_BAD;
            counterDSI = 42; // 42/(8.334Hz) = 5 second debounce
        }
        else
        {
            counterDSI--;   // decrement
        }
    }
    else if (!coachingAppSpecific->isDiagnosticActiveFlag() && (BreadcrumbStatus::Type::DL_BAD == currentDlState))
    {
        if (0 == counterDSI)
        {
            breadcrumbLog.commandReceived(BreadcrumbStatus::Type::DL_GOOD, 1);
            currentDlState = BreadcrumbStatus::Type::DL_GOOD;
            counterDSI = 42; // 42/(8.334Hz) = 5 second debounce
        }
        else
        {
            counterDSI--;   // decrement
        }
    }
    else
    {
        counterDSI = 42; // 42/(8.334Hz) = 5 second debounce
    }

    AIS_LOG_INFO("checkBreadcrumbDlGoodBadStatus() state:%d  counter:%d  isDiagActive:%d", currentDlState, counterDSI, coachingAppSpecific->isDiagnosticActiveFlag());
}

///////////////////////////////////////////////////////////////////////////////
/// @Coaching task cleanup function.
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::cleanup()
{
    // Prevent contention with websocket server
    std::lock_guard<std::mutex> lock(wsMutex);
    shuttingDown = true;

    // End all active cycles and save to NVM
    for (auto &coaching3x3Data : coaching3x3DataList)
    {
        // if cycle is running then update tip severity values
        if (coachingAppSpecific->isCycleRunning(coaching3x3Data.name))
        {
            coaching3x3Data.update(coachingSummaryData.coachingTipOutputList, true, true);
            AIS_LOG_INFO("Cycle ended (Key-Off): %s", coaching3x3Data.name.c_str());
            coaching3x3DataOutput->publish(coaching3x3Data);
        }
    }

    // Trigger Key-Off event
    breadcrumbLog.keyOff();

    // Save 3x3, Summary, Breadcrumb records and Operator ID List to NVM
    saveCoachingRecords();
    saveOperatorIdList();
    pServer.reset(); // Kill the server (release unique_ptr and object is destroyed)
}
