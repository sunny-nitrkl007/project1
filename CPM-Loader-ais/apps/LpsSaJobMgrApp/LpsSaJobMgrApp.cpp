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
#include <pthread.h>
#include <sched.h>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "ROS2Logger.hpp"
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

/******************************************************************************
FUNCTION NAME:LpsSaJobMgrApp::LpsSaJobMgrApp()
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
LpsSaJobMgrApp::LpsSaJobMgrApp(const std::string& taskName):
    ros2_wrapper::Ros2TaskWrapper(taskName), LpsJobMgrJobTrackerInfoTbl(),
    LpsSaJobMgrTxRosOut_(nullptr), LpsSaJobMgrReqstIn(nullptr), LpsSaJobMgrDebugRosOut_(nullptr), LpsSaJobMgrRespChannelOutput_(nullptr),
    weighAppTxDataReceived_(false), weighAppInf_(),
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

   RCLCPP_INFO(get_logger(), "JobManager::initialize");

    { // Default matches config/LpsSaJobMgrApp.rb: "scheduler" => "SCHED_RR", "schedulerPriority" => 1.
        declare_parameter<std::string>("scheduler", "SCHED_RR");
        declare_parameter<int>("scheduler_priority", 1);
        std::string schedulerPolicy = get_parameter("scheduler").as_string();
        int schedulerPriority = static_cast<int>(get_parameter("scheduler_priority").as_int());
        if (!applyRealtimeScheduling(schedulerPolicy, schedulerPriority)) {
            RCLCPP_WARN(get_logger(), "Continuing without real-time scheduling.");
        }
    }

    { // Get the configs.
        declare_parameter<std::string>("storage_root", DEFAULT_STORAGE_ROOT);
        declare_parameter<int>("simple_cal_max_trucks_supported", 0);
        declare_parameter<bool>("horn_store_enable", false);
        declare_parameter<int>("auto_store_pass_count_default", LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_DEFAULT);
        declare_parameter<std::string>("internal_msn", machineMSN);
        declare_parameter<std::string>("ui_show_feature_config_json_file_path", "");

        storageRoot_ = get_parameter("storage_root").as_string();

        stats_.setFilePath(storageRoot_ / STATS_FILENAME_BIN);

        simpleCal_.setFilePath(storageRoot_ / SIMPLE_CAL_FILENAME_BIN);

        { // Default Horn Store Enable
            defaultConfig.hornStoreEnable = get_parameter("horn_store_enable").as_bool();
           RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"Default HornStoreEnable is: %d", defaultConfig.hornStoreEnable);
        }

        { // Simple Cal Max Trucks
            int simpleCalMaxTrucksSupported = get_parameter("simple_cal_max_trucks_supported").as_int();
            if (simpleCalMaxTrucksSupported > 0) {
                // Got max simple cal trucks from config
                simpleCal_.setMaxQueueSize(static_cast<uint_least32_t>(simpleCalMaxTrucksSupported));
            }
        }

        { // Default Auto Store Pass Count
            defaultConfig.autoStorePassCount = LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_DEFAULT;
            int autoStorePassCount = get_parameter("auto_store_pass_count_default").as_int();
            if (autoStorePassCount > LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_MAX) {
                autoStorePassCount = LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_MAX;
            }
            else if (autoStorePassCount < LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_MIN) {
                autoStorePassCount = LPSSAJOBMGRCNFG_AUTO_STORE_PASS_COUNT_MIN;
            }

            defaultConfig.autoStorePassCount = static_cast<uint16_t>(autoStorePassCount);
           RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"Default AutoStorePassCount is: %d", defaultConfig.autoStorePassCount);
        }

        { // MSN
            machineMSN = get_parameter("internal_msn").as_string();
        }

       RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"Storage Root: %s", storageRoot_.c_str());
    }

    /* Initialize time information. */
    serviceHourMeter_ = 0;
    tzInfo_.offset = 0;
    tzInfo_.index = -1;

    auto rosNode = shared_from_this();

    /* Initialsing SCS interface*/
    LpsSaJobMgrTxRosOut_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>(rosNode, "lps_sa_job_mgr_tx_channel");
    LpsSaJobMgrReqstIn = new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>(rosNode, "lps_sa_job_mgr_reqst_channel");
    LpsSaJobMgrDebugRosOut_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>(rosNode, "lps_sa_job_mgr_debug_channel");
    LpsSaJobMgrRespChannelOutput_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>(rosNode, "lps_sa_job_mgr_resp_channel");
    LpsSaSwitchInput = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::SwitchInputScs>(rosNode, "switch_input_scs");
    LpsSaOutputChannelRosOut_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::OutputChannel>(rosNode, "output_channel");
    AisJhm2TxInput = new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::AisJhm2TxChannel>(rosNode, "ais_jhm2_tx_channel");

    displayStateInputRos_ = new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface>(
            rosNode, "lps_sa_ui_display_state_interface");

    ShmClockInputRos = new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::ShmClockInput>(rosNode, "shm_clock_input");
    dataLinkDataInputRos_ = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::DataLinkData>(rosNode, "data_link_data");
    autonomyConditionDiagnosticsTxInputRos_ = new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>(
            rosNode, "autonomy_condition_diagnostics_tx_channel");
    eddtInputRos_ = new ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::EventDiagnosticData>(rosNode, "event_diagnostic_data");

    if ( !ShmClockInputRos )
    {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "\n  ShmClockInput ROS2 interface not configured." );
    }

    if ( !LpsSaJobMgrTxRosOut_ )
    {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "\n  LpsSaJobMgrTx ROS2 interface not configured." );
    }

    if ( !LpsSaJobMgrDebugRosOut_ )
    {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "\n  LpsSaJobMgrDebug ROS2 interface not configured." );
    }

    if (!LpsSaJobMgrRespChannelOutput_) {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"LpsSaJobMgrRespChannel ROS2 output not initialized");
    }

    if (!LpsSaJobMgrReqstIn) {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"LpsSaJobMgrReqstChannel ROS2 input not initialized");
    }

    if ( !LpsSaSwitchInput )
    {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "\n LpsSaSwitchInput Interface  not configured." );
    }

    if ( !LpsSaOutputChannelRosOut_ )
    {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "\n OutputChannel ROS2 interface not configured." );
    }

    if (!AisJhm2TxInput) {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"AisJhm2TxChannel ROS2 input not initialized");
    }

    if (!displayStateInputRos_) {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"DisplayStateInput ROS2 input not initialized");
        everythingOk = false;
    }

    if (nullptr == dataLinkDataInputRos_) {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"DataLinkData ROS2 input not initialized.");
        everythingOk = false;
    }

    if (nullptr == autonomyConditionDiagnosticsTxInputRos_) {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"AutonomyConditionDiagnosticsTx ROS2 input not initialized.");
        everythingOk = false;
    }

    { // Initialize the WeighApp interface
        ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>* requestOutput =
            new ros2_wrapper::RosOutputInterface<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>(rosNode, "lps_sa_weigh_reqst_channel");
        ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighRespChannel>* responseInput =
            new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighRespChannel>(rosNode, "lps_sa_weigh_resp_channel");
        ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighTxChannel>* txInput =
            new ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighTxChannel>(rosNode, "lps_sa_weigh_tx_channel");

        if (!weighAppInf_.start(get_name(), requestOutput, responseInput, txInput)) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Failed to start weigh app interface.");
            everythingOk = false;
        }

        weighAppTxDataReceived_ = false;
    }

    // Get the load record output channel (now ROS2-only, bridge forwards to AIS SCS consumers)
    loadRecordOutputChannel_ = new ros2_wrapper::RosOutputInterface<job_mgr_interfaces::msg::LpsSaLoadRecordChannel>(rosNode, "lps_sa_load_record_channel");
    if (nullptr == loadRecordOutputChannel_) {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"\n Load record ROS2 output channel not initialized.");
        everythingOk = false;
    }

    if (nullptr == eddtInputRos_) {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"EventDiagnosticData ROS2 input not initialized.");
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
       RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
        everythingOk = false;
    }

    // Delete old load record file that is no longer needed
    try {
        tes_common_ais::sha1_fstream::remove_files(makeStoragePath(LOAD_RECORD_FILENAME_BIN));
    }
    catch (const fs::filesystem_error& e) {
       RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
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
        std::string uiConfigJsonFilePath = get_parameter("ui_show_feature_config_json_file_path").as_string();
        if (!uiConfigJsonFilePath.empty()) {
                RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"JSON file found: %s", uiConfigJsonFilePath.c_str());

                // Load JSON
                boost::property_tree::ptree tree;
                boost::property_tree::read_json(uiConfigJsonFilePath, tree);

                // Check if flags are set
                if (false == tree.get<bool>("TipOff.supported"))
                {
                    config_.tipOffMode = TIP_OFF_MODE_PILE;
                    config_.tipOffTriggerType = TIP_OFF_TRIGGER_DISABLED;
                   RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"TipOff Disabled via Show/Hide config file Type:%d  Mode:%d", config_.tipOffTriggerType, config_.tipOffMode);
                }

                ret = true;
        }
        else {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"ui_show_feature_config_json_file_path parameter not set");
        }
    }
    catch (const fs::filesystem_error& e) {
       RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
    }
    catch (const std::exception &exception) {
       RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),exception.what());
    }
    catch (...)
    {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not copy JSON.");
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
   RCLCPP_DEBUG(get_logger(), "Executing JobManager Task");

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
       RCLCPP_ERROR(get_logger(), "\n Line no = %d,'LpsSaJobMgrUpdate:LpsSaJobMgrScsRx' function return code = %d\n", __LINE__, ret);
    }

    ret = LpsSaJobMgrPtUpdate();

    if(SUCCESS != ret)
    {
       RCLCPP_ERROR(get_logger(), "\n Line no = %d,'LpsSaJobMgrUpdate:LpsSaJobMgrPtUpdate' function return code = %d\n", __LINE__, ret);

        return FAIL;
    }

    /* send the UI Parameter to UI App*/
    ret =LpsSaJobMgrScsTx();
    if(SUCCESS != ret)
    {
       RCLCPP_ERROR(get_logger(), "\n Line no = %d,'LpsSaJobMgrUpdate:LpsSaJobMgrScsTx' function return code = %d\n", __LINE__, ret);

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

void LpsSaJobMgrApp::startExecutiveTimer( )
{
    double cycleRateHz = 10.0;
    declare_parameter<double>("cycle_rate_hz", cycleRateHz);
    cycleRateHz = get_parameter("cycle_rate_hz").as_double();
    createExecutiveTimer(cycleRateHz);
}

/******************************************************************************
FUNCTION LpsSaJobMgrApp::cleanup( )
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
void LpsSaJobMgrApp::cleanup( ) {
    RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"LpsSaJobMgrApp::cleanup");
    executiveTimer_.reset();
    cleanupRosInterfaces();

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
               RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
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
           RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"Loaded load record from storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not deserialize load record from storage.");
           RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
        }
        catch (const std::exception& e) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not deserialize load record from storage");
           RCLCPP_ERROR_STREAM(ROS2Logger::Instance().GetLogger(),e.what());
        }
        catch (...) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Could not deserialize load record from storage, unexpected error.");
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"Load record file was corrupt... fixed it.");
            }
            else {
               RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Load record file was corrupt... could not fix it.");
            }
        }
    }
    else {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Load record could not be opened from storage.");
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

int main(int argc, char** argv)
{
    return ros2_wrapper::Ros2TaskWrapper::run<LpsSaJobMgrApp>(argc, argv);
}
