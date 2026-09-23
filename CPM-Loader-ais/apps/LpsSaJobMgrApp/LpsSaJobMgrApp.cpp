/*******************************************************************************
** COPYRIGHT (C) 2016-2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsSaJobMgrApp.cpp
DESCRIPTION:
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <chrono>

#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <fileio/sha1_fstream.hpp>
#include <scl_prmsw.h>
#include <lps_sea_defs.h>

#include <interfaces/LpsSaWeighReqstChannel/InterfaceTypes.h>
#include <interfaces/LpsSaWeighRespChannel/InterfaceTypes.h>
#include <interfaces/LpsSaWeighTxChannel/InterfaceTypes.h>

#include "LpsSaJobMgrApp.h"

namespace fs = boost::filesystem;

// This is the file that all of the tasks are stored in.
// A "task" is basically an in process load record.
#define TASKS_FILENAME_BIN (R"(Tasks.bin)")

// This is where the load record used to be stored before multi-task was supported.
// We read from this file and put it in task #1, then delete this file.
#define LOAD_RECORD_FILENAME_BIN (R"(LoadRecord.bin)")

#define CONFIG_FILENAME_BIN (R"(JobMgrCnfg.bin)")

#define STATS_FILENAME_BIN (R"(JobMgrStats.bin)")

#define SIMPLE_CAL_FILENAME_BIN (R"(JobMgrSimpleCal.bin)")

#define DEFAULT_STORAGE_ROOT (R"(/tmp/LpsSaJobMgrApp/storage)")

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
using namespace task;


/******************************************************************************
FUNCTION NAME:task::getTaskImplementation
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
AbstractTaskCore* task::getTaskImplementation(void)
{
    rclcpp::init(0, nullptr);
    std::cout<<"[ROS2][Initialized][JOB_MANAGER]";
    static LpsSaJobMgrApp thisTask("LpsSaJobMgrApp");
    return dynamic_cast<Task *>(&thisTask);
}

/******************************************************************************
FUNCTION NAME:LpsSaJobMgrApp::LpsSaJobMgrApp()
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
LpsSaJobMgrApp::LpsSaJobMgrApp(const std::string& taskName):
    Task(taskName), LpsJobMgrJobTrackerInfoTbl(),
    LpsSaJobMgrTxRosOut_(nullptr), LpsSaJobMgrReqstIn(nullptr), LpsSaJobMgrDebugRosOut_(nullptr), LpsSaJobMgrRespChannelOutput_(nullptr),
    weighAppTxDataReceived_(false), weighAppInf_(),
    rosNode_(nullptr), executor_(),
    LpsSaSwitchInput(nullptr), LpsSaOutputChannelRosOut_(nullptr), AisJhm2TxInput(nullptr), displayStateInputRos_(nullptr),
    ShmClockInputRos(nullptr), dataLinkDataInputRos_(nullptr), loadRecordOutputChannel_(nullptr),
    tasks_(), config_(), stats_(), simpleCal_(), storageRoot_(DEFAULT_STORAGE_ROOT), defaultTargetWeight_(0.0),
    machineMSN(), storeRejectedExpireTime(std::chrono::steady_clock::time_point::min()),
    autonomyConditionDiagnosticsTxInputRos_(nullptr),
    SEALevel1EssentialsInstalled_(true), SEALevel2ProInstalled_(true), SEALegalForTradeInstalled_(false),
    eddtInputRos_(nullptr), totalWeightAccuracy_(LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE)
{
}
/******************************************************************************
FUNCTION NAME:LpsSaJobMgrApp::~LpsSaJobMgrApp( )
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
LpsSaJobMgrApp::~LpsSaJobMgrApp( )
{
    cleanupRosInterfaces();
}

void LpsSaJobMgrApp::cleanupRosInterfaces()
{
    weighAppInf_.stop();

    delete LpsSaJobMgrTxRosOut_;
    LpsSaJobMgrTxRosOut_ = nullptr;
    delete LpsSaJobMgrReqstIn;
    LpsSaJobMgrReqstIn = nullptr;
    delete LpsSaJobMgrDebugRosOut_;
    LpsSaJobMgrDebugRosOut_ = nullptr;
    delete LpsSaJobMgrRespChannelOutput_;
    LpsSaJobMgrRespChannelOutput_ = nullptr;
    delete LpsSaSwitchInput;
    LpsSaSwitchInput = nullptr;
    delete LpsSaOutputChannelRosOut_;
    LpsSaOutputChannelRosOut_ = nullptr;
    delete AisJhm2TxInput;
    AisJhm2TxInput = nullptr;
    delete displayStateInputRos_;
    displayStateInputRos_ = nullptr;
    delete ShmClockInputRos;
    ShmClockInputRos = nullptr;
    delete dataLinkDataInputRos_;
    dataLinkDataInputRos_ = nullptr;
    delete loadRecordOutputChannel_;
    loadRecordOutputChannel_ = nullptr;
    delete autonomyConditionDiagnosticsTxInputRos_;
    autonomyConditionDiagnosticsTxInputRos_ = nullptr;
    delete eddtInputRos_;
    eddtInputRos_ = nullptr;
}
/******************************************************************************
FUNCTION NAME:LpsSaJobMgrApp::initialize
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:bool
*******************************************************************************/
bool LpsSaJobMgrApp::initialize( )
{
    bool everythingOk = true;
    LpsSaJobMgrCnfg defaultConfig;

    getLogger().log_info( "JobManager::initialize" );

    { // Get the configs.
        ConfigSection& configs = getTaskConfig();

        std::string storageRoot;
        if (configs.get("storageRoot", storageRoot)) {
            storageRoot_ = storageRoot;
        }
        else {
            storageRoot_ = DEFAULT_STORAGE_ROOT;
        }

        stats_.setFilePath(storageRoot_ / STATS_FILENAME_BIN);

        simpleCal_.setFilePath(storageRoot_ / SIMPLE_CAL_FILENAME_BIN);

        { // Default Horn Store Enable
            ConfigSection machineCfg;

            defaultConfig.hornStoreEnable = false;

            if (getTaskParser().getSection("MachineSpecificConfig", machineCfg)) {
                bool hornStoreEnable;
                if (machineCfg.get("HornStoreEnable", hornStoreEnable)) {
                    defaultConfig.hornStoreEnable = hornStoreEnable;
                    AIS_LOG_INFO("Default HornStoreEnable is: %d", defaultConfig.hornStoreEnable);
                }
                else {
                    AIS_LOG_INFO("Config section item not found, default HornStoreEnable is: %d", defaultConfig.hornStoreEnable);
                }
            }
            else {
                AIS_LOG_WARN("MachineSpecificConfig section not found, default HornStoreEnable is: %d", defaultConfig.hornStoreEnable);
            }
        }

        { // Simple Cal Max Trucks
            uint_least32_t simpleCalMaxTrucksSupported;
            if (configs.get("SimpleCalMaxTrucksSupported", simpleCalMaxTrucksSupported)) {
                // Got max simple cal trucks from config
                simpleCal_.setMaxQueueSize(simpleCalMaxTrucksSupported);
            }
        }

        { // Default Auto Store Pass Count
            ConfigSection machineCfg;

            defaultConfig.autoStorePassCount = LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_DEFAULT;

            if (getTaskParser().getSection("MachineSpecificConfig", machineCfg)) {
                uint16_t autoStorePassCount;
                if (machineCfg.get("AutoStorePassCountDefault", autoStorePassCount)) {
                    if (autoStorePassCount > LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_MAX) {
                        autoStorePassCount = LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_MAX;
                    }
                    else if (autoStorePassCount < LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_MIN) {
                        autoStorePassCount = LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_MIN;
                    }

                    defaultConfig.autoStorePassCount = autoStorePassCount;
                    AIS_LOG_INFO("Default AutoStorePassCount is: %d", defaultConfig.autoStorePassCount);
                }
                else {
                    AIS_LOG_INFO("Config section item not found, default AutoStorePassCount is: %d", defaultConfig.autoStorePassCount);
                }
            }
            else {
                AIS_LOG_WARN("MachineSpecificConfig section not found, default AutoStorePassCount is: %d", defaultConfig.autoStorePassCount);
            }
        }

        { // MSN
            ConfigSection machineType;
            if (!getTaskParser().getSection("MachineType", machineType)) {
                AIS_LOG_ERROR("MachineType section not found");
            }
            else {
                machineType.get("InternalMsn", machineMSN);
            }
        }

        AIS_LOG_INFO("Storage Root: %s", storageRoot_.c_str());
    }

    /* Initialize time information. */
    serviceHourMeter_ = 0;
    tzInfo_.offset = 0;
    tzInfo_.index = -1;

    rosNode_ = std::make_shared<rclcpp::Node>("job_mgr_node");
    executor_.add_node(rosNode_);

    /* Initialsing SCS interface*/
    LpsSaJobMgrTxRosOut_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>(rosNode_, "lps_sa_job_mgr_tx_channel");
    LpsSaJobMgrReqstIn = new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>(rosNode_, "lps_sa_job_mgr_reqst_channel");
    LpsSaJobMgrDebugRosOut_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>(rosNode_, "lps_sa_job_mgr_debug_channel");
    LpsSaJobMgrRespChannelOutput_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>(rosNode_, "lps_sa_job_mgr_resp_channel");
    LpsSaSwitchInput = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::SwitchInputScs>(rosNode_, "switch_input_scs");
    LpsSaOutputChannelRosOut_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::OutputChannel>(rosNode_, "output_channel");
    AisJhm2TxInput = new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::AisJhm2TxChannel>(rosNode_, "ais_jhm2_tx_channel");

    displayStateInputRos_ = new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface>(
            rosNode_, "lps_sa_ui_display_state_interface");

    ShmClockInputRos = new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::ShmClockInput>(rosNode_, "shm_clock_input");
    dataLinkDataInputRos_ = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::DataLinkData>(rosNode_, "data_link_data");
    autonomyConditionDiagnosticsTxInputRos_ = new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>(
            rosNode_, "autonomy_condition_diagnostics_tx_channel");
    eddtInputRos_ = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::EventDiagnosticData>(rosNode_, "event_diagnostic_data");

    if ( !ShmClockInputRos )
    {
        AIS_LOG_ERROR( "\n  ShmClockInput ROS2 interface not configured." );
    }

    if ( !LpsSaJobMgrTxRosOut_ )
    {
        AIS_LOG_ERROR( "\n  LpsSaJobMgrTx ROS2 interface not configured." );
    }

    if ( !LpsSaJobMgrDebugRosOut_ )
    {
        AIS_LOG_ERROR( "\n  LpsSaJobMgrDebug ROS2 interface not configured." );
    }

    if (!LpsSaJobMgrRespChannelOutput_) {
        AIS_LOG_ERROR("LpsSaJobMgrRespChannel ROS2 output not initialized");
    }

    if (!LpsSaJobMgrReqstIn) {
        AIS_LOG_ERROR("LpsSaJobMgrReqstChannel ROS2 input not initialized");
    }

    if ( !LpsSaSwitchInput )
    {
        AIS_LOG_ERROR( "\n LpsSaSwitchInput Interface  not configured." );
    }

    if ( !LpsSaOutputChannelRosOut_ )
    {
        AIS_LOG_ERROR( "\n OutputChannel ROS2 interface not configured." );
    }

    if (!AisJhm2TxInput) {
        AIS_LOG_ERROR("AisJhm2TxChannel ROS2 input not initialized");
    }

    if (!displayStateInputRos_) {
        AIS_LOG_ERROR("DisplayStateInput ROS2 input not initialized");
        everythingOk = false;
    }

    if (nullptr == dataLinkDataInputRos_) {
        AIS_LOG_ERROR("DataLinkData ROS2 input not initialized.");
        everythingOk = false;
    }

    if (nullptr == autonomyConditionDiagnosticsTxInputRos_) {
        AIS_LOG_ERROR("AutonomyConditionDiagnosticsTx ROS2 input not initialized.");
        everythingOk = false;
    }

    { // Initialize the WeighApp interface
        ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>* requestOutput =
                new ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>(rosNode_, "lps_sa_weigh_reqst_channel");
        ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighRespChannel>* responseInput =
                new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighRespChannel>(rosNode_, "lps_sa_weigh_resp_channel");
        ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighTxChannel>* txInput =
                new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighTxChannel>(rosNode_, "lps_sa_weigh_tx_channel");

        if (!weighAppInf_.start(getTaskName(), requestOutput, responseInput, txInput)) {
            AIS_LOG_ERROR("Failed to start weigh app interface.");
            everythingOk = false;
        }

        weighAppTxDataReceived_ = false;
    }

    // Get the load record output channel (now ROS2-only, bridge forwards to AIS SCS consumers)
    loadRecordOutputChannel_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>(rosNode_, "lps_sa_load_record_channel");
    if (nullptr == loadRecordOutputChannel_) {
        AIS_LOG_ERROR("\n Load record ROS2 output channel not initialized.");
        everythingOk = false;
    }

    if (nullptr == eddtInputRos_) {
        AIS_LOG_ERROR("EventDiagnosticData ROS2 input not initialized.");
        everythingOk = false;
    }

    // Initialize tasks
    tasks_.setFilePath(makeStoragePath(TASKS_FILENAME_BIN));
    tasks_.setDefaultTargetWeight(defaultTargetWeight_);

    // Load stuff from storage
    try {
        fs::create_directories(storageRoot_);
        fs::create_directories(TEMP_STORAGE_ROOT);

        if (!tasks_.load()) {
            LpsSaLoadRecordChannel loadRecord;
            if (loadOldLoadRecord(loadRecord)) {
                // Initialize from existing load record.
                tasks_.currentTaskLoadInit(loadRecord);
                tasks_.save();
            }
        }

        if (!config_.load(makeStoragePath(CONFIG_FILENAME_BIN))) {
            config_ = defaultConfig;
        }

        // Load statistics from file.
        stats_.load();

        // Load simple cal data from file.
        simpleCal_.load();
    }
    catch (const fs::filesystem_error& e) {
        AIS_LOG_ERROR(e.what());
        everythingOk = false;
    }

    // Delete old load record file that is no longer needed
    try {
        tes_common_ais::sha1_fstream::remove_files(makeStoragePath(LOAD_RECORD_FILENAME_BIN));
    }
    catch (const fs::filesystem_error& e) {
        AIS_LOG_ERROR(e.what());
    }

    parseUiConfigurableFeatures();		// check if Tip_Off is disabled via Show/Hide

    LpsSaJobMgrPtInit();

    // if multitask is disabled, reset LFT disable state
    if (!config_.multiTaskEnabled) {
        tasks_.allTasksResetLFTDisableState();
    }

    return everythingOk;
}

/******************************************************************************
FUNCTION:                   parseUiConfigurableFeatures
DESCRIPTION:                move the UI Config JSON file to tempRoot and parse it
PARAMETER DESCRIPTION:
RETURN VALUE:               Boolean  
*******************************************************************************/
bool LpsSaJobMgrApp::parseUiConfigurableFeatures() {
    bool ret = false;

    try {
        ConfigSection cs;
        if (getTaskParser().getSection("MachineSpecificConfig", cs)) {
            std::string uiConfigJsonFilePath;
            if (cs.get("UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH", uiConfigJsonFilePath)) {
                AIS_LOG_INFO("JSON file found: %s", uiConfigJsonFilePath.c_str());

                // Load JSON
                boost::property_tree::ptree tree;
                boost::property_tree::read_json(uiConfigJsonFilePath, tree);

                // Check if flags are set
                if (false == tree.get<bool>("TipOff.supported"))
                {
                    config_.tipOffMode = TIP_OFF_MODE_PILE;
                    config_.tipOffTriggerType = TIP_OFF_TRIGGER_DISABLED;
                    AIS_LOG_ERROR("TipOff Disabled via Show/Hide config file Type:%d  Mode:%d", config_.tipOffTriggerType, config_.tipOffMode);
                }

                ret = true;
            }
            else {
                AIS_LOG_ERROR("UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH not found in MachineSpecificConfig");
            }
        }
        else {
            AIS_LOG_ERROR("MachineSpecificConfig section not found");
        }
    }
    catch (const fs::filesystem_error& e) {
        AIS_LOG_ERROR(e.what());
    }
    catch (const std::exception &exception) {
        AIS_LOG_ERROR(exception.what());
    }
    catch (...)
    {
        AIS_LOG_ERROR("Could not copy JSON.");
    }

    return ret;
}

/******************************************************************************
FUNCTION LpsSaJobMgrApp::executive( )
DESCRIPTION:It will send the parameter to UI App,and send the cmds to Weighing App
            and set the response UI App
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
bool LpsSaJobMgrApp::executive( )
{
    getLogger().log_debug( "Executing JobManager Task" );

    // ROS2/DDS: drain pending callbacks for weighAppInf_'s 3 channels
    executor_.spin_some();

    if (nullptr != autonomyConditionDiagnosticsTxInputRos_) {
        cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel txData;
        while (autonomyConditionDiagnosticsTxInputRos_->get(txData)) {
            for (const auto & element : txData.sea_list) {
                if (element.reason_code == LPS_SEA_REASON_CODE_149) {
                    SEALevel1EssentialsInstalled_ = AutonomyConditionDiagnosticsTxInterfaceStorage::checkSEAEnableStatus(element.status);
                }
                else if (element.reason_code == LPS_SEA_REASON_CODE_245) {
                    SEALevel2ProInstalled_ = AutonomyConditionDiagnosticsTxInterfaceStorage::checkSEAEnableStatus(element.status);
                }
                else if (element.reason_code == LPS_SEA_LFT_REASON_CODE_312) {
                    SEALegalForTradeInstalled_ = AutonomyConditionDiagnosticsTxInterfaceStorage::checkSEAEnableStatus(element.status);
                    if (!SEALegalForTradeInstalled_) {
                        // reset LFT to always enabled
                        tasks_.allTasksResetLFTDisableState();
                    }
                }
            }
        }
    }

    boolean ret;
    ret=LpsSaJobMgrScsRx();
    if(SUCCESS != ret)
    {
        getLogger().log_error("\n Line no = %d,'LpsSaJobMgrUpdate:LpsSaJobMgrScsRx' function return code = %d\n",__LINE__,ret );
    }

    ret = LpsSaJobMgrPtUpdate();

    if(SUCCESS != ret)
    {
        getLogger().log_error( "\n Line no = %d,'LpsSaJobMgrUpdate:LpsSaJobMgrPtUpdate' function return code = %d\n",__LINE__,ret );

        return FAIL;
    }

    /* send the UI Parameter to UI App*/
    ret =LpsSaJobMgrScsTx();
    if(SUCCESS != ret)
    {
        getLogger().log_error( "\n Line no = %d,'LpsSaJobMgrUpdate:LpsSaJobMgrScsTx' function return code = %d\n",__LINE__,ret );

        return FAIL;
    }

    if (nullptr != LpsSaJobMgrDebugRosOut_) {
        job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel txOut;
        txOut.current_state = LpsSaJobMgrWmOutput.pt_current_state;
        txOut.tipoff_assist_activation_count = stats_.tipoffAssistActivationCount;
        LpsSaJobMgrDebugRosOut_->publish(txOut);
    }

    // Save statistics if needed
    stats_.save();

    // Reset simple cal data if we have received data from the weigh app saying that we are not calibrated.
    if ((LPS_WEIGH_SYSTEM_CALIBRATED != LpsJobMgrJobTrackerInfoTbl.CalStat) && (weighAppTxDataReceived_)) {
        if (simpleCal_.queueSize() > 0) {
            simpleCal_.reset();
        }
    }

    // Save simple cal data if needed.
    simpleCal_.save();

    // Return true for the executive method to be periodically invoked
    return true;

}

/******************************************************************************
FUNCTION LpsSaJobMgrApp::cleanup( )
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsSaJobMgrApp::cleanup( ) {
    AIS_LOG_INFO("LpsSaJobMgrApp::cleanup");
    cleanupRosInterfaces();
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }

    // Wait for possible write to robot file
    sleep(2);

    // Remove the default config if robot has changed
    std::ifstream machineModelFp("/opt/etc/robot");
    std::string newMachineMSN;

    if(machineModelFp.good()) {
        machineModelFp >> newMachineMSN;
        if ((machineMSN.compare(newMachineMSN) != 0) && !(newMachineMSN == "CAT99999") && !(machineMSN == "CAT99999")) {
            try {
                tes_common_ais::sha1_fstream::remove_files(makeStoragePath(CONFIG_FILENAME_BIN));
            }
            catch (const fs::filesystem_error& e) {
                AIS_LOG_ERROR(e.what());
            }

            simpleCal_.reset();
        }
    }
}

bool LpsSaJobMgrApp::loadOldLoadRecord(LpsSaLoadRecordChannel& loadRecord) {
    bool success = false;

    tes_common_ais::sha1_ifstream ifs{ true }; // two_copy
    ifs.open(makeStoragePath(LOAD_RECORD_FILENAME_BIN), std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia >> loadRecord;
            AIS_LOG_INFO("Loaded load record from storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not deserialize load record from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("Could not deserialize load record from storage");
            AIS_LOG_ERROR(e.what());
        }
        catch (...) {
            AIS_LOG_ERROR("Could not deserialize load record from storage, unexpected error.");
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                AIS_LOG_WARN("Load record file was corrupt... fixed it.");
            }
            else {
                AIS_LOG_ERROR("Load record file was corrupt... could not fix it.");
            }
        }
    }
    else {
        AIS_LOG_ERROR("Load record could not be opened from storage.");
    }

    if (!success) {
        loadRecord = LpsSaLoadRecordChannel();
        loadRecord.getCurrentSubtotal().truckTargetWeightTonnes = defaultTargetWeight_;
    }

    return success;
}

bool LpsSaJobMgrApp::saveConfig() {
    return config_.save(makeStoragePath(CONFIG_FILENAME_BIN));
}
