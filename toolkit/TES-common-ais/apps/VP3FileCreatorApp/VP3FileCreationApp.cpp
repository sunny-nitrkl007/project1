#include <list>
#include <array>
#include <chrono>
#include <sstream>
#include <map>
#include <utility>
#include <ctime>

#include <sys/stat.h>
#include <fcntl.h>

#include <cmath>
#include <iomanip>
#include <chrono/convert.hpp>
#include "VP3RuntimeSupport.h"

#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/archive_exception.hpp>

#include <climits>
#include <algorithm>

/* For debugging
#include <ais/time/TimeStamp.h>
#include <ais/time/ConvertTime.h>
*/

#include <atomic>
#include <thread>
#include <csignal>

#include "VP3FileCreationApp.h"

namespace fs = boost::filesystem;


#define LASTDOWNLOADTIMESTAMP_FILENAME_BIN (R"(VP3FileCreatorApp.bin)")
#define PARTNUM_FILENAME_BIN (R"(PartNum.bin)")
#define STATUS_RECORD_FILENAME_BIN (R"(StatusRecord.bin)")
#define DEFAULT_STORAGE_ROOT (R"(/tmp/VP3FileCreatorApp/storage)")
#define DEFAULT_TEMP_ROOT (R"(/tmp/VP3FileCreatorApp/temp)")

// 10*2^10 = 10KB
#define DEFAULT_RECORD_DATA_SIZE_TX_TRIGGER (10240)
#define DEFAULT_RECORD_COUNT_TX_TRIGGER (100)

// 8*2^20 = 8MB
#define DEFAULT_MAX_VP3_STORAGE_SIZE (8388608)

#define DEFAULT_MAX_VP3_STORAGE_FILES (2500)

#define VP3_SUBDIR (R"(vp3)")

#define VP3_FILE_NUM 10129
#define VP3_CLEANUP_SLEEP_TIME 100000      //100 millisec

static constexpr uint8_t PRODUCT_ID_SIZE = 8;
static constexpr uint8_t SW_GROUP_PARTNUM_SIZE = 10;
static constexpr uint8_t MODEL_NUM_SIZE = 16;
static constexpr uint8_t ECM_PARTNUM_SIZE = 20;

/* For debugging
static std::string shmClockUTCString = "";
static std::string shmClockLocalString = "";
*/

int main(int argc, char** argv)
{
    return ros2_wrapper::Ros2TaskWrapper::run<VP3FileCreationApp>(argc, argv);
}

////////////////////////////////////////////////////////////////////////
// Function        : VP3FileCreationApp
// Description     : Construction of the class VP3FileCreationApp with initial values of the class
//
// Return Type     : None
// Argument [in]   : taskName
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
VP3FileCreationApp::VP3FileCreationApp(const std::string& taskName) :
    ros2_wrapper::Ros2TaskWrapper(taskName),
    tempRoot_(DEFAULT_TEMP_ROOT),
    storageRoot_(DEFAULT_STORAGE_ROOT),
    myRecordTypeContainers(),
    latestStatusRecord(),
    totalReceivedRecordSize_(0),
    totalReceivedRecordCount_(0),
    recordDataSizeTxTrigger_(DEFAULT_RECORD_DATA_SIZE_TX_TRIGGER),
    recordCountTxTrigger_(DEFAULT_RECORD_COUNT_TX_TRIGGER),
    resetLastDownloadTimestamp_(false),
    maxVP3StorageSize_(DEFAULT_MAX_VP3_STORAGE_SIZE),
    maxVP3StorageFiles_(DEFAULT_MAX_VP3_STORAGE_FILES),
    requireStatusRecord_(true),
    vp3TempPath_(fs::path(DEFAULT_TEMP_ROOT) / VP3_SUBDIR),
    vp3StoragePath_(fs::path(DEFAULT_STORAGE_ROOT) / VP3_SUBDIR),
    vp3TxPath_(),
    AppRegistered(false),
    AppRegOutput_(nullptr),
    FileTransferBridgeRequestOutput_(nullptr),
    vp3FilesDestinationApp("FileTransferBridgeApp"),
    LastDownloadTimestamp_(),
    productId_(),
    ecmPartNum_(),
    swGroupPartNum_(),
    modelNum_(),
    shmSeconds_(0),
    tzInfo_{0, -1}
{
}

VP3FileCreationApp::~VP3FileCreationApp( )
{
}

////////////////////////////////////////////////////////////////////////
// Function        : Initialize
// Description     : The function which initializes the the Scs communication channel
//
// Return Type     : Returns boolean, either success or failure.
// Argument [in]   : None
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool VP3FileCreationApp::initialize( )
{

    declare_parameter<std::string>("logger_threshold", "error");
    ROS2Logger::Instance().SetLogLevel(get_parameter("logger_threshold").as_string());
    
    auto unsignedParameter = [this](const std::string& name, std::int64_t fallback, std::uint64_t maximum) {
        const auto value = declare_parameter<std::int64_t>(name, fallback);
        if (value < 0 || static_cast<std::uint64_t>(value) > maximum)
            throw std::invalid_argument("Out of range parameter: " + name);
        return value;
    };
    recordDataSizeTxTrigger_ = unsignedParameter("recordDataSizeTxTrigger", DEFAULT_RECORD_DATA_SIZE_TX_TRIGGER, UINT_MAX);
    recordCountTxTrigger_ = unsignedParameter("recordCountTxTrigger", DEFAULT_RECORD_COUNT_TX_TRIGGER, UINT_MAX);
    maxVP3StorageSize_ = unsignedParameter("maxVP3StorageSize", DEFAULT_MAX_VP3_STORAGE_SIZE, LONG_MAX);
    maxVP3StorageFiles_ = unsignedParameter("maxVP3StorageFiles", DEFAULT_MAX_VP3_STORAGE_FILES, UINT16_MAX);
    keyoffTimeoutMs_ = unsignedParameter("VP3KeyoffTimeout", 0, UINT32_MAX);
    requireStatusRecord_ = declare_parameter<bool>("requireStatusRecord", true);
    storageRoot_ = declare_parameter<std::string>("storageRoot", DEFAULT_STORAGE_ROOT);
    tempRoot_ = declare_parameter<std::string>("tempRoot", DEFAULT_TEMP_ROOT);
    vp3TxPath_ = declare_parameter<std::string>("VP3TxPath", "");
    cycleRateHz_ = declare_parameter<double>("cycleRateHz", 1.0);
    if (!std::isfinite(cycleRateHz_) || cycleRateHz_ <= 0 ||
        1e9 / cycleRateHz_ < 1 || 1e9 / cycleRateHz_ > INT64_MAX)
        throw std::invalid_argument("Invalid cycleRateHz");
    for (const auto& path : {storageRoot_, tempRoot_, vp3TxPath_}) {
        if (path.empty() || path.string().find('\0') != std::string::npos)
            throw std::invalid_argument("Empty or invalid filesystem path");
    }
    const auto scheduler = declare_parameter<std::string>("scheduler", "SCHED_OTHER");
    const auto priority = declare_parameter<std::int64_t>("priority", 0);
    int policy = SCHED_OTHER;
    if (scheduler == "SCHED_RR") policy = SCHED_RR;
    else if (scheduler == "SCHED_FIFO") policy = SCHED_FIFO;
    else if (scheduler != "SCHED_OTHER") throw std::invalid_argument("Invalid scheduler");
    if (priority < sched_get_priority_min(policy) || priority > sched_get_priority_max(policy))
        throw std::invalid_argument("Invalid scheduling priority");
    if (!applyRealtimeScheduling(policy, static_cast<int>(priority))) return false;
    vp3TempPath_ = tempRoot_ / VP3_SUBDIR;
    vp3StoragePath_ = storageRoot_ / VP3_SUBDIR;
    using RosRecord = cpm_common_interfaces::msg::VP3Record;
    subscribeQueue<RosRecord>("vp3_record", 100, recordQueue_, [](const RosRecord& message) {
        return VP3Record(vp3::RecordValue::fromMessage(message));
    });
    subscribeQueue<CreateFileRequest>("create_file_request", 10, requestQueue_, [](const CreateFileRequest& message) { return message; });
    subscribeQueue<AppReg>("vp3_app_reg_rx", 20, registrationQueue_, [](const AppReg& message) { return message; });
    subscribeQueue<PartNumbers>("part_numbers", 10, partQueue_, [](const PartNumbers& message) { return message; });
    subscribeQueue<ShmClock>("shm_clock_input", 10, clockQueue_, [](const ShmClock& message) { return message; });
    AppRegOutput_ = create_publisher<AppReg>("vp3_app_reg_tx", rclcpp::QoS(20).reliable().durability_volatile());
    FileTransferBridgeRequestOutput_ = create_publisher<FileTransferBridgeRequest>("file_transfer_bridge_request", rclcpp::QoS(20).reliable().durability_volatile());

    totalReceivedRecordSize_ = 0;
    totalReceivedRecordCount_ = 0;

    // Load stuff from storage and create directories
    try {
        fs::create_directories(storageRoot_);
        fs::create_directories(tempRoot_);

        if (!LastDownloadTimestamp_.load(makeStoragePath(LASTDOWNLOADTIMESTAMP_FILENAME_BIN))) {
            RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Inside reset if");
            resetLastDownloadTimestamp_ = true;
            LastDownloadTimestamp_.reset();
        }

        if (!ReadPartNumsFromNVM()) {
            swGroupPartNum_.clear();
            modelNum_.clear();
            ecmPartNum_.clear();
        }
        
        if (!vp3::readStorage(makeStoragePath(STATUS_RECORD_FILENAME_BIN), [this](auto& archive) { archive >> statusArchive_; })) {
            /*
             * Make a default status record that has the earliest time possible
             * and default values for all other fields.  This will act as the status
             * record until a real status record comes in.
             */
            latestStatusRecord = VP3RecordBuilder::makeDefaultStatusRecord();
        } else {
            latestStatusRecord = VP3Record(vp3::RecordValue::fromArchive(statusArchive_));
        }

        RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "At init LastDownloadTimestamp_.LastDownloadTimestamp.UTC : %d", LastDownloadTimestamp_.LastDownloadTimestamp.UTC);
        RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "At init LastDownloadTimestamp_.LastDownloadTimestamp.Offset : %d", LastDownloadTimestamp_.LastDownloadTimestamp.Offset);
        RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "At init LastDownloadTimestamp_.LastDownloadTimestamp.SMH : %d", LastDownloadTimestamp_.LastDownloadTimestamp.SMH);

        // Create the directories for VP3 file creation and storage.
        fs::create_directories(vp3TempPath_);
        fs::create_directories(vp3StoragePath_);
    }
    catch (const fs::filesystem_error& e) {
        RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
    }

    // Clean up vp3 file storage if it is taking up too much space.
    makeSpaceForNewVp3File(0);

    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "VP3FileCreationApp::initialize: %i, %i", recordDataSizeTxTrigger_, recordCountTxTrigger_);
    initialized_ = true;
    return true;
}


////////////////////////////////////////////////////////////////////////
// Function        : executive
// Description     : This function publish all the parameters to be broadcasted
//
// Return Type     : Returns a High if the data publish success or Zero on failure
// Argument [in]   : None
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool VP3FileCreationApp::executive( )
{
    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "executive");

    UpdateRegistrations();

    getACDscsObject();
    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "swGroupPartNum_ %s", swGroupPartNum_.c_str());
    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "modelNum_ %s", modelNum_.c_str());
    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "ecmPartNum_ %s", ecmPartNum_.c_str());

    {
        bool createFileFlag = false;
        std::string createFileRequester;

        // Process any incoming records
        processIncomingRecords();

        // If we have enough data, trigger the creation of a file
        if ((recordDataSizeTxTrigger_ > 0) && (totalReceivedRecordSize_ > recordDataSizeTxTrigger_)) {
            createFileFlag = true;
            createFileRequester = "RecordDataSize";
        }
        // If we have enough records, trigger the creation of a file
        else if ((recordCountTxTrigger_ > 0) && (totalReceivedRecordCount_ > recordCountTxTrigger_)) {
            createFileFlag = true;
            createFileRequester = "RecordCount";
        }

        while (!requestQueue_.empty()) {
            const auto request = std::move(requestQueue_.front());
            requestQueue_.pop_front();
            if (request.file_number == VP3_FILE_NUM) {
                createFileFlag = true;
                createFileRequester = request.requester;
            }
        }

        // Check whether we need to create the file based on SCS Command or size/record count trigger
        if (createFileFlag) {
            if (myRecordTypeContainers.empty()) {
                RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "No file created because of no records, requester = %s.", createFileRequester.c_str());
            }
            else {
                createFile(createFileRequester);
            }
        }
    }

    /*In case of nvm corruption assign key on time to last download time*/
    if ((resetLastDownloadTimestamp_) && (tzInfo_.index >= 0 /* Received */)) {
        auto tp = std::chrono::system_clock::now();
        LastDownloadTimestamp_.LastDownloadTimestamp.UTC = tes_common_ais::systemClockTimePointToUidTime(tp);
        LastDownloadTimestamp_.LastDownloadTimestamp.Offset = tzInfo_.offset;
        LastDownloadTimestamp_.LastDownloadTimestamp.SMH = shmSeconds_;

        resetLastDownloadTimestamp_ = false;

        RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Reset LastDownloadTimestamp_.LastDownloadTimestamp.UTC : %d", LastDownloadTimestamp_.LastDownloadTimestamp.UTC);
        RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Reset LastDownloadTimestamp_.LastDownloadTimestamp.Offset : %d", LastDownloadTimestamp_.LastDownloadTimestamp.Offset);
        RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Reset LastDownloadTimestamp_.LastDownloadTimestamp.SMH : %d", LastDownloadTimestamp_.LastDownloadTimestamp.SMH);
    }

    /*
    { // For debugging
        auto now = std::chrono::system_clock::now();
        std::string nowStr = tes_common_ais::putTime(now, "%m/%d/%Y %H:%M:%S");
        TimeStamp cNow = commonNow();
        std::string commonNowStr = convertGPSToGMTString(cNow, "%m/%d/%Y %H:%M:%S");

        RCLCPP_WARN(rclcpp::get_logger("VP3FileCreationApp"), "SYS | %s | SHM | %s | SHML | %s | CMN | %s", nowStr.c_str(), shmClockUTCString.c_str(), shmClockLocalString.c_str(), commonNowStr.c_str());
    }
    */

    return true;
}


///////////////////////////////////////////////////////////////////////
// Function        : cleanup
// Description     : Which cleans the dump left, at the end of the thread
//
// Return Type     : None
// Argument [in]   : None
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void VP3FileCreationApp::startExecutiveTimer()
{
    createExecutiveTimer(cycleRateHz_);
}

// A spin_some() poll loop driving the receive pump that cleanup()/pumpFor()
// also call into, so queued ROS2 messages keep getting processed while VP3
// drains on shutdown.
int VP3FileCreationApp::runLifecycle(std::shared_ptr<rclcpp::executors::SingleThreadedExecutor> executor)
{
    startExecutiveTimer();
    setReceivePump([executor]() { executor->spin_some(); });

    while (rclcpp::ok()) {
        executor->spin_some();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}

void VP3FileCreationApp::pumpFor(std::chrono::milliseconds duration)
{
    const auto end = std::chrono::steady_clock::now() + duration;
    do {
        if (receivePump_) receivePump_();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    } while (std::chrono::steady_clock::now() < end && rclcpp::ok());
}

void VP3FileCreationApp::cleanup()
{
    if (!initialized_ || cleaned_) return;
    cleaned_ = true;
    if (executiveTimer_) executiveTimer_->cancel();
    const auto start = std::chrono::steady_clock::now();
    if (receivePump_) receivePump_();
    UpdateRegistrations();
    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "VP3FileCreationApp::cleanup");

    // Keep accumulating VP3 records as long as we are registered with apps producing them (or until a key-off timeout)
    while (!activeProducers_.empty() && std::chrono::steady_clock::now() - start < std::chrono::milliseconds(keyoffTimeoutMs_)) {
        pumpFor(std::chrono::milliseconds(120));

        // Process any new incoming records
        processIncomingRecords();

        // Update registration with other apps
        UpdateRegistrations();
    }

    // Process any remaining incoming records
    processIncomingRecords();

    latestStatusRecord.updateArchive(statusArchive_);
    vp3::writeStorage(makeStoragePath(STATUS_RECORD_FILENAME_BIN), [this](auto& archive) { archive << statusArchive_; });

    // Generate the last file and send it out
    if (myRecordTypeContainers.empty()) {
        RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "No cleanup file created because of no records.");
    }
    else {
        createFile("KeyOff");
    }

    // Log which apps are still trying to keep us alive.
    const auto& activeAppNames = activeProducers_;
    for (const auto& name : activeAppNames) {
        RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "ListActiveAppNames::%s", name.c_str());
    }

   
    // Add sleep so that we give some time for FTB to transfer the last file before unregistering  
    pumpFor(std::chrono::milliseconds(100));
    if (AppRegOutput_ && AppRegistered) {
        publishRegistration(AppReg::STATE_INACTIVE);
        pumpFor(std::chrono::milliseconds(100));
    }
}

///////////////////////////////////////////////////////////////////////
// Function        : saveVp3Record
// Description     : Add data to block if block is already existing else create the block and add data to it
//
// Return Type     : None
// Argument [in]   : None
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void VP3FileCreationApp::saveVp3Record(const VP3Record& record, bool pushNewRecordTypeToFront)
{
    bool foundRecordTypeContainer = false;

    // Every VP3 file should contain a starting status record.
    if (record.getRecordType() == Record_Type::STATUS) {
        /*
        * Get a copy of the most recent status record so that we can make sure
        *  to start each new file with it.
        */
        latestStatusRecord = record;
    }
    else if (myRecordTypeContainers.empty()) {
        // If status records are required and we have a latest status record, then add it first
        if ((requireStatusRecord_) && (latestStatusRecord.getRecordType() == Record_Type::STATUS)) {
            // add status record to the front of the LIST
            myRecordTypeContainers.push_front(VP3RecordTypeContainer(latestStatusRecord));
            totalReceivedRecordSize_ += latestStatusRecord.getSizeOfRecord();
            ++totalReceivedRecordCount_;
        }
    }

    for (auto& container : myRecordTypeContainers) {
        if ((container.getRecordType() == record.getRecordType()) &&
                (container.equalUIDs(record.getUIDList())) &&
                (container.getSizeOfRecord() == record.getSizeOfRecord())) {
            container.addRBlockData(record.getRBlockData());
            totalReceivedRecordSize_ += record.getSizeOfRecord();
            ++totalReceivedRecordCount_;
            foundRecordTypeContainer = true;
            break;
        }
    }

    if (!foundRecordTypeContainer) {
        if (pushNewRecordTypeToFront) {
            // Add record type to the front of the list
            myRecordTypeContainers.push_front(VP3RecordTypeContainer(record));
        }
        else {
            // Add record type to the end of the list
            myRecordTypeContainers.push_back(VP3RecordTypeContainer(record));
        }

        totalReceivedRecordSize_ += record.getSizeOfRecord();
        ++totalReceivedRecordCount_;
    }
}

///////////////////////////////////////////////////////////////////////
// Function        : createFile
// Description     : This function creates the vp3 file
//
// Return Type     : None
// Argument [in]   : None
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void VP3FileCreationApp::createFile(const std::string& requester)
{
    FileTransferBridgeRequest fileTransferRequest;
    FILE* vp3File = nullptr;

    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Create File Requester: %s", requester.c_str());

    const auto alphaNumeric = [](char c) { return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'); };
    const bool validProduct = productId_.size() >= 8 &&
        std::all_of(productId_.begin(), productId_.begin() + 3, alphaNumeric) &&
        std::all_of(productId_.begin() + 3, productId_.begin() + 8, [](char c) { return c >= '0' && c <= '9'; });
    if (!validProduct) {
        RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Failed to create file, product id '%s' is not valid.", productId_.c_str());
        return;
    }

    Add_VP3_header_block();

    const auto clock = std::time(nullptr);
    std::tm utc{};
    if (!gmtime_r(&clock, &utc)) throw std::runtime_error("Cannot convert filename time");
    std::ostringstream filename;
    filename << VP3_FILE_NUM << '_' << productId_ << std::put_time(&utc, "%y%m%d%H%M%S") << "_DQ1.VP3";
    const std::string vp3FileName = filename.str();
    fileTransferRequest.name = vp3FileName;
    fileTransferRequest.telematics_file_number = VP3_FILE_NUM;

    fs::path tempFilePath = vp3TempPath_ / vp3FileName;
    fs::path storageFilePath = vp3StoragePath_ / vp3FileName;
    fs::path txFilePath = vp3TxPath_ / vp3FileName;

    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "VP3 Tx File Path: %s", txFilePath.c_str());

    vp3File = fopen(tempFilePath.c_str(), "wb+");

    if (nullptr != vp3File) {
        unsigned int sizeOfVp3File = 0;
        auto tpStart = std::chrono::system_clock::now();
        char P2[] = {'P', 0x02, 0x00, 0x00};
        char R2[] = {'R', 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        for (const auto& container : myRecordTypeContainers) {

            uint_to_byteArr(container.getNumberOfUIDs(), &P2[2]);

            fwrite(P2, sizeof(P2[0]), sizeof(P2)/sizeof(P2[0]), vp3File);
            if (ferror(vp3File)) {
                RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Error Writing P2 Block to VP3 file");
            }

            fwrite(container.getUID64().data(), container.getUID64().length(), 1, vp3File);
            if (ferror(vp3File)) {
                RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Error Writing UIDs to VP3 file");
            }

            uint_to_byteArr(container.getNumberOfUIDs()-1, &R2[4]);
            uint_to_byteArr(container.getSizeOfRecord(), &R2[6]);
            uint_to_byteArr(container.getNumberOfRecords(), &R2[8]);

            fwrite(R2, sizeof(R2[0]), sizeof(R2)/sizeof(R2[0]), vp3File);
            if (ferror(vp3File)) {
                RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Error Writing R2 Block to VP3 file");
            }

            fwrite(container.getRBlockData().data(), container.getRBlockData().length(), 1, vp3File);
            if (ferror(vp3File)) {
                RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Error Writing record data to VP3 file");
            }

            sizeOfVp3File += (14 + container.getUID64().length() + container.getRBlockData().length()); //calculating size of the file
        }

        if (fclose(vp3File)) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Error closing VP3 file");
        }

        auto tpEnd = std::chrono::system_clock::now();

        RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Duration (sec): %f", std::chrono::duration<double>(tpEnd - tpStart).count());

        bool copiedToStorage = false;

        // Make room for the new file in the storage directory
        if (makeSpaceForNewVp3File(sizeOfVp3File)) {
            // Copy the new file into the storage directory
            try {
                fs::copy_file(tempFilePath, storageFilePath, fs::copy_option::fail_if_exists);
                copiedToStorage = true;
            }
            catch (const fs::filesystem_error& e) {
                RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
            }
        }
        else {
            // Cannot make space!
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Cannot make space for new VP3 file in storage directoy.");
        }

        // Copy file to tx directory and publish the file transfer request
        try {
            if (copiedToStorage) {
                // Make a symbolic link to the storage location.
                fs::create_symlink(storageFilePath, txFilePath);
            }
            else {
                // Make a copy.
                fs::copy_file(tempFilePath, txFilePath, fs::copy_option::fail_if_exists);
            }

            fileTransferRequest.dir_path = txFilePath.parent_path().string() + "/";
            fileTransferRequest.size_in_bytes = sizeOfVp3File;
            if (FileTransferBridgeRequestOutput_) {
                FileTransferBridgeRequestOutput_->publish(fileTransferRequest);
                RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Published new VP3 file to file transfer bridge app. Size is %d", sizeOfVp3File);
            }
        }
        catch (const fs::filesystem_error& e) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
        }

        // Remove the Temp file
        try {
            fs::remove(tempFilePath);
        }
        catch (const fs::filesystem_error& e) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
        }
    }
    else {
        RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Could not fopen VP3 file");
    }

    // remove everything
    myRecordTypeContainers.clear();
    
    totalReceivedRecordSize_ = 0; // reset total record size counter
    totalReceivedRecordCount_ = 0;
}

/*
 * Receive new vp3 records and save them for the next vp3 file.
 */
void VP3FileCreationApp::processIncomingRecords() {
    while (!recordQueue_.empty()) {
        const auto record = std::move(recordQueue_.front());
        recordQueue_.pop_front();
        saveVp3Record(record);
    }
}

void VP3FileCreationApp::publishRegistration(std::uint8_t state)
{
    AppReg request;
    request.app_name = get_name();
    request.app_state = state;
    request.dest_app_name = vp3FilesDestinationApp;
    AppRegOutput_->publish(request);
}

void VP3FileCreationApp::UpdateRegistrations(void)
{
    while (!registrationQueue_.empty()) {
        auto message = std::move(registrationQueue_.front());
        registrationQueue_.pop_front();
        if (message.msg_type > AppReg::RESP || message.app_state > AppReg::STATE_INACTIVE || message.reg_status > AppReg::UNKNOWN) {
            RCLCPP_WARN(get_logger(), "Unsupported AppReg enum value");
            continue;
        }
        if (message.dest_app_name != get_name()) continue;
        if (message.msg_type == AppReg::REQ) {
            if (message.app_name.empty()) {
                message.reg_status = AppReg::NAME_EMPTY;
                AppRegOutput_->publish(message);
                continue;
            }
            if (message.app_state == AppReg::STATE_ACTIVE) {
                message.reg_status = activeProducers_.insert(message.app_name).second ? AppReg::REGISTERED : AppReg::ALREADY_REGISTERED;
            } else {
                activeProducers_.erase(message.app_name);
                message.reg_status = AppReg::UNREGISTERED;
            }
            std::swap(message.app_name, message.dest_app_name);
            message.msg_type = AppReg::RESP;
            AppRegOutput_->publish(message);
        } else if (message.app_name == vp3FilesDestinationApp &&
                   (message.reg_status == AppReg::REGISTERED || message.reg_status == AppReg::ALREADY_REGISTERED)) {
            AppRegistered = true;
        }
    }
    if (!AppRegistered && AppRegOutput_) publishRegistration(AppReg::STATE_ACTIVE);
}

///////////////////////////////////////////////////////////////////////
// Function        : Add_VP3_header_block
// Description     : This function creates the VP3 header blocks and maps the parameters to each block
//
// Return Type     : None
// Argument [in]   : None
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void VP3FileCreationApp::Add_VP3_header_block()
{
    using VP3RecordBuilder::UidType;

    /* UID definitions */
    static constexpr UidType UID_timestamp =  {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x07, 0x00, 0x0A, 0x13, 0x05, 0x00, 0x37 }};
    static constexpr UidType UID_ProductID = {{ 0xAA, 0x00, 0x0A, 0x00, 0x03, 0x00, 0xF2, 0x00, PRODUCT_ID_SIZE, 0x03, 0x18, 0x00, 0x37 }};
    static constexpr UidType UID_Software_Group_number = {{ 0xAA, 0x00, 0x0A, 0x00, 0x03, 0x00, 0xFE, 0x00, SW_GROUP_PARTNUM_SIZE, 0x03, 0x18, 0x00, 0x37 }};
    static constexpr UidType UID_Model_number = {{ 0xAA, 0x00, 0x0A, 0x81, 0x03, 0x00, 0x01, 0x00, MODEL_NUM_SIZE, 0x03, 0x18, 0x00, 0x37 }};
    static constexpr UidType UID_ECM_number = {{ 0xAA, 0x00, 0x0A, 0x00, 0x03, 0x00, 0xDB, 0x00, ECM_PARTNUM_SIZE, 0x03, 0x18, 0x00, 0x37 }};
    static constexpr UidType UID_Feature_Type = {{ 0xAA, 0x00, 0x0A, 0x81, 0x03, 0x00, 0x02, 0x00, 0x01, 0x06, 0x00, 0x00, 0x37 }};
    static constexpr UidType UID_No_of_Feature_Items = {{ 0xAA, 0x00, 0x0A, 0x81, 0x03, 0x00, 0x03, 0x00, 0x02, 0x08, 0x00, 0x00, 0x37 }};
    static constexpr UidType UID_Feature_Item_Num = {{ 0xAA, 0x00, 0x0A, 0x81, 0x03, 0x00, 0x04, 0x00, 0x02, 0x08, 0x00, 0x00, 0x37 }};
    static constexpr UidType UID_Security_Level = {{ 0xAA, 0x00, 0x0A, 0x81, 0x03, 0x00, 0x05, 0x00, 0x01, 0x06, 0x00, 0x00, 0x37 }};
    static constexpr UidType UID_Last_Download_Time = {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x07, 0x01, 0x0A, 0x13, 0x06, 0x00, 0x37 }};
    static constexpr UidType UID_Last_Reset_Time = {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x07, 0x02, 0x0A, 0x13, 0x07, 0x00, 0x37 }};
    static constexpr UidType UID_Buffer_Size = {{ 0xAA, 0x00, 0x0A, 0x81, 0x03, 0x00, 0x09, 0x00, 0x04, 0x0C, 0x00, 0x00, 0x37 }};
    static constexpr UidType UID_Buffer_Type = {{ 0xAA, 0x00, 0x0A, 0x81, 0x03, 0x00, 0x0A, 0x00, 0x01, 0x06, 0x00, 0x00, 0x37 }};
    static constexpr UidType UID_Timezone = {{ 0xAA, 0x00, 0x0A, 0x81, 0x01, 0x00, 0x72, 0x00, 0x01, 0x06, 0x00, 0x00, 0x37 }};

    /* constants */
    static constexpr uint8_t featureType = 0x0F;
    static constexpr uint16_t noOfFeatureitems = 0x0001;
    static constexpr uint16_t FeatureItemNum = 0x0001;
    static constexpr uint8_t securityLevel = 0x00;
    static constexpr uint32_t bufferSize = 0x00000000;
    static constexpr uint8_t buffertype = 0x00;

    // I guess last reset time is the same as the last download time
    LastDownloadTimestampStorage::Timestamp lastReset = LastDownloadTimestamp_.LastDownloadTimestamp;
    LastDownloadTimestampStorage::Timestamp lastDownload = LastDownloadTimestamp_.LastDownloadTimestamp;
    uint8_t timeZoneIndex = tzInfo_.index;

    LastDownloadTimestampStorage::Timestamp now;
    { // Fill in current timestamp
        auto tp = std::chrono::system_clock::now();
        now.UTC = tes_common_ais::systemClockTimePointToUidTime(tp);
        now.Offset = tzInfo_.offset;
        now.SMH = shmSeconds_;
    }

    /*
     * Build the Machine Info Record
     */
    VP3Record MachineInfoRecord;
    MachineInfoRecord.setRecordType(0);
    MachineInfoRecord.add_timestamp(UID_timestamp, now.UTC, now.Offset, now.SMH, true /* MSB */);

    { // Product Id
        std::string productId = productId_;
        productId.resize(PRODUCT_ID_SIZE, ' ');
        MachineInfoRecord.add_string_to_record(UID_ProductID, productId);
    }

    { // Software Part Number
        std::string swGroupPartNum = swGroupPartNum_;
        swGroupPartNum.resize(SW_GROUP_PARTNUM_SIZE, ' ');
        MachineInfoRecord.add_string_to_record(UID_Software_Group_number, swGroupPartNum);
    }

    // Model Number (if present)
    if (!modelNum_.empty()) {
        std::string modelNum = modelNum_;
        modelNum.resize(MODEL_NUM_SIZE, ' ');
        MachineInfoRecord.add_string_to_record(UID_Model_number, modelNum);
    }

    { // ECM Part Number
        std::string ecmPartNum = ecmPartNum_;
        ecmPartNum.resize(ECM_PARTNUM_SIZE, ' ');
        MachineInfoRecord.add_string_to_record(UID_ECM_number, ecmPartNum);
    }

    /*
     * Build the Download File Record
     */
    VP3Record DownloadFileRecord;
    DownloadFileRecord.setRecordType(0);
    DownloadFileRecord.add_data_to_record(UID_Feature_Type, featureType);
    DownloadFileRecord.add_data_to_record(UID_No_of_Feature_Items, noOfFeatureitems, true /* MSB */);

    /*
     * Build the Last Download Record
     */
    VP3Record LastDownloadRecord;
    LastDownloadRecord.setRecordType(0);
    LastDownloadRecord.add_data_to_record(UID_Feature_Item_Num, FeatureItemNum, true /* MSB */);
    LastDownloadRecord.add_data_to_record(UID_Security_Level, securityLevel);
    LastDownloadRecord.add_timestamp(UID_Last_Download_Time,
            lastDownload.UTC, lastDownload.Offset, lastDownload.SMH, true /* MSB */);
    LastDownloadRecord.add_timestamp(UID_Last_Reset_Time,
            lastReset.UTC, lastReset.Offset, lastReset.SMH, true  /* MSB */);
    LastDownloadRecord.add_data_to_record(UID_Buffer_Size, bufferSize, true  /* MSB */);
    LastDownloadRecord.add_data_to_record(UID_Buffer_Type, buffertype);
    LastDownloadRecord.add_data_to_record(UID_Timezone, timeZoneIndex);

    /*
     * The records need to be pushed to the front of the record list so that they
     * end up in the following order:
     *  - Machine Info Record
     *  - Download File Record
     *  - Last Download Record
     */
    saveVp3Record(LastDownloadRecord, true /* Push to front */);
    saveVp3Record(DownloadFileRecord, true /* Push to front */);
    saveVp3Record(MachineInfoRecord, true /* Push to front */);

    //Assign current time stamp to last download timestamp
    LastDownloadTimestamp_.LastDownloadTimestamp = now;

    // Save LastDownloadTimestamp
    LastDownloadTimestamp_.save(makeStoragePath(LASTDOWNLOADTIMESTAMP_FILENAME_BIN));
    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"),  "After save LastDownloadTimestamp_.LastDownloadTimestamp.UTC : %d",LastDownloadTimestamp_.LastDownloadTimestamp.UTC );
    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"),  "After save LastDownloadTimestamp_.LastDownloadTimestamp.Offset : %d",LastDownloadTimestamp_.LastDownloadTimestamp.Offset );
    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"),  "After save LastDownloadTimestamp_.LastDownloadTimestamp.SMH : %d",LastDownloadTimestamp_.LastDownloadTimestamp.SMH );
}

///////////////////////////////////////////////////////////////////////
// Function        : getACDscsObject
// Description     : This function receives the parameters from acd app and passes it to header block
//
// Return Type     : None
// Argument [in]   : None
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void VP3FileCreationApp::getACDscsObject()
{
    while (!partQueue_.empty()) {
        const auto partNumbers = std::move(partQueue_.front());
        partQueue_.pop_front();
        bool updateFile = false;

        if (partNumbers.product_id_num_set) {
            std::string productId(partNumbers.product_id_num);
            if (productId_ != productId) {
                productId_ = std::move(productId);
                // product id is not stored in the file
            }
        }

        if (partNumbers.ecm_part_num_set) { 
            std::string ecmPartNum(partNumbers.ecm_part_num);
            if (ecmPartNum_ != ecmPartNum) {
                ecmPartNum_ = std::move(ecmPartNum);
                updateFile = true;
            }
        }

        if (partNumbers.sw_group_part_num_set) {
            std::string swGroupPartNum(partNumbers.sw_group_part_num);
            if (swGroupPartNum_ != swGroupPartNum) {
                swGroupPartNum_ = std::move(swGroupPartNum);
                updateFile = true;
            }
        }

        if (partNumbers.model_num_set) {
            std::string modelNum(partNumbers.model_num);
            if (modelNum_ != modelNum) {
                modelNum_ = std::move(modelNum);
                updateFile = true;
            }
        }

        if (updateFile) {
            WritePartNumsToNVM(); // save the new data to nvm
        }
    }

    while (!clockQueue_.empty()) {
        const auto shmClock = std::move(clockQueue_.front());
        clockQueue_.pop_front();
        const auto offset = shmClock.utc_offset_min;
        const auto index = shmClock.tzone_info[19];
        if (offset < INT16_MIN || offset > INT16_MAX) {
            RCLCPP_WARN(get_logger(), "Clock UTC offset is not representable in VP3 header");
        } else if (tzInfo_.offset != offset || tzInfo_.index != index) {
            const auto tz = vp3::timezoneString(shmClock.tzone_info);
            if (setenv("TZ", tz.c_str(), 1) == 0) tzset();
            else RCLCPP_ERROR(get_logger(), "Could not set TZ environment variable");
            tzInfo_.offset = offset;
            tzInfo_.index = index;
        }
        shmSeconds_ = shmClock.shm_sec;

            /*
            { // For debugging
                shmClockUTCString = convertGPSToGMTString(shmClock.get_UTC(), "%m/%d/%Y %H:%M:%S");
                shmClockLocalString = shmClock.get_Local_time_str();
            }
            */
    }
}

///////////////////////////////////////////////////////////////////////
// Function        : LastDownloadTimestampStorage::load
// Description     : Used to read nvm parameter values at init
//
// Return Type     : None
// Argument [in]   : None
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool LastDownloadTimestampStorage::load(const fs::path& filePath) {
    bool success = false;
    tes_common_ais::sha1_ifstream ifs{ true }; // two_copy
    ifs.open(filePath.string(), std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia >> *this;
            RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Loaded Last Download Timestamp from storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Could not deserialize Last Download Timestamp from storage.");
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
            reset();
        }
        catch (const std::exception& e) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Could not deserialize Last Download Timestamp from storage.");
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
        }
        catch (...) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Could not deserialize Last Download Timestamp from storage, unexpected error.");
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                RCLCPP_WARN(rclcpp::get_logger("VP3FileCreationApp"), "Last Download Timestamp file was corrupt... fixed it.");
            }
            else {
                RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Last Download Timestamp file was corrupt... could not fix it.");
            }
        }
    }
    else {
        RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Last Download Timestamp could not be opened from storage.");
    }

    return success;
}

///////////////////////////////////////////////////////////////////////
// Function        : LastDownloadTimestampStorage::save
// Description     : Used to save nvm parameter values at cleanup
//
// Return Type     : None
// Argument [in]   : None
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool LastDownloadTimestampStorage::save(const fs::path& filePath) {
    bool success = false;
    tes_common_ais::sha1_ofstream ofs{ true }; // two_copy
    ofs.open(filePath.string(), std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Read the file in
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa << *this;
            RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Saved Last Download Timestamp to storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Could not serialize Last Download Timestamp to storage.");
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
        }

        ofs.close();
    }
    else {
        RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Last Download Timestamp could not be opened from storage.");
    }

    return success;
}

/*
 * Make Last Download Timestamp printable.
 */
std::ostream& operator<<(std::ostream& os, const LastDownloadTimestampStorage& o) {
    return os << "LastDownload (UTC: " << o.LastDownloadTimestamp.UTC << ", Offset: " << o.LastDownloadTimestamp.Offset << ", SMH: " << o.LastDownloadTimestamp.SMH << ")";
}

///////////////////////////////////////////////////////////////////////
// Function        : VP3FileCreationApp::ReadPartNumsFromNVM
// Description     : Used to read/load nvm parameter values at init
//
// Return Type     : None
// Argument [in]   : None
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool VP3FileCreationApp::ReadPartNumsFromNVM()
{
    bool success = false;
    tes_common_ais::sha1_ifstream ifs{ true }; // two_copy
    std::string filePath = makeStoragePath(PARTNUM_FILENAME_BIN);
    ifs.open(filePath, std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia >> swGroupPartNum_ >> modelNum_ >> ecmPartNum_;

            // If SW Group Part Number is all spaces, clear it out.
            if (swGroupPartNum_ == std::string(SW_GROUP_PARTNUM_SIZE, ' ')) {
                swGroupPartNum_.clear();
            }

            // If model number is all spaces, clear it out.
            if (modelNum_ == std::string(MODEL_NUM_SIZE, ' ')) {
                modelNum_.clear();
            }

            // If ECM Part Number is all spaces, clear it out.
            if (ecmPartNum_ == std::string(ECM_PARTNUM_SIZE, ' ')) {
                ecmPartNum_.clear();
            }

            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Could not deserialize %s from storage.", PARTNUM_FILENAME_BIN);
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
        }
        catch (const std::exception& e) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Could not deserialize %s from storage.", PARTNUM_FILENAME_BIN);
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
        }
        catch (...) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Could not deserialize %s from storage, unexpected error.", PARTNUM_FILENAME_BIN);
        }

        ifs.close();
        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                RCLCPP_WARN(rclcpp::get_logger("VP3FileCreationApp"), "%s was corrupt... fixed it.", PARTNUM_FILENAME_BIN);
            }
            else {
                RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s was corrupt... could not fix it.", PARTNUM_FILENAME_BIN);
            }
        }
    }
    else {
        RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s could not be opened from storage.", PARTNUM_FILENAME_BIN);
    }

    return success;
}

///////////////////////////////////////////////////////////////////////
// Function        : VP3FileCreationApp::WritePartNumsToNVM
// Description     : Used to save nvm parameter values at cleanup
//
// Return Type     : None
// Argument [in]   : None
//
// Argument [out]  : None
//
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool VP3FileCreationApp::WritePartNumsToNVM()
{
    bool success = false;
    tes_common_ais::sha1_ofstream ofs{ true }; // two_copy
    std::string filePath = makeStoragePath(PARTNUM_FILENAME_BIN);
    ofs.open(filePath, std::ios_base::out | std::ios_base::binary);    
    if (ofs) {
        // Write to the file
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa << swGroupPartNum_ << modelNum_ << ecmPartNum_;
            RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Saving %s to storage.", PARTNUM_FILENAME_BIN);
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Could not serialize %s to storage.", PARTNUM_FILENAME_BIN);
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
        }
        ofs.close();
    }
    else {
        RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s could not be saved to storage.", PARTNUM_FILENAME_BIN);
    }
    return success;
}

/*
 * Makes space for a new VP3 file.
 */
bool VP3FileCreationApp::makeSpaceForNewVp3File(long int newVp3FileSize)
{
    std::clock_t startCpuTime = std::clock();
    auto startTime = std::chrono::high_resolution_clock::now();

    // Using a multimap here just in case multiple files have the same
    // modification time.  This case was seen during testing when all
    // files were created at once.
    typedef std::multimap<std::time_t, std::pair<std::string, long int> > FileMap;
    FileMap fileMap;
    long int totalSize = 0;

    uint16_t newVp3FileCount = 1;
    if (newVp3FileSize <= 0) {
        newVp3FileCount = 0;
    }

    { // Index the storage directory
        struct stat fstat;
        for (fs::directory_iterator it(vp3StoragePath_); it != fs::directory_iterator(); ++it) {
            const fs::directory_entry& de = *it;
            try {
                if (fs::is_regular_file(de.status())) {
                    if (stat(de.path().c_str(), &fstat) >= 0) {
                        fileMap.emplace(fstat.st_mtim.tv_sec, FileMap::mapped_type(de.path().filename().string(), fstat.st_size));
                        totalSize += fstat.st_size;
                    }
                    else {
                        RCLCPP_WARN(rclcpp::get_logger("VP3FileCreationApp"), "Cannot get file size of %s", de.path().c_str());
                    }
                }
                else {
                    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "%s is not a regular file", de.path().c_str());
                }
            }
            catch (const fs::filesystem_error& e) {
                RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
            }
        }
    }

    auto numFiles = fileMap.size();
    auto maxFiles = maxVP3StorageFiles_;
    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Found %zu files, maximum is %d", numFiles, maxVP3StorageFiles_);

    auto maxSize = maxVP3StorageSize_;
    RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Found %ld bytes worth of data in storage directory, maximum is %ld", totalSize, maxSize);

    { // Remove files until we have enough space.
        FileMap::const_iterator it = fileMap.cbegin();
        FileMap::const_iterator endIt = fileMap.cend();
        while (((numFiles + newVp3FileCount) > maxFiles) || ((totalSize + newVp3FileSize) > maxSize)) {
            if (it == endIt) {
                // No more files to delete
                break;
            }

            try {
                // Delete the file
                fs::remove(vp3StoragePath_ / it->second.first);
                totalSize -= it->second.second;
                --numFiles;
                RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Deleted file %s, %zu files, %ld bytes remaining", it->second.first.c_str(), numFiles, totalSize);
            }
            catch (const fs::filesystem_error& e) {
                RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "%s", e.what());
            }

            ++it;
        }
    }

    std::clock_t endCpuTime = std::clock();
    auto endTime = std::chrono::high_resolution_clock::now();

    { // Log the time it took
        double elapsedCpuTime = 1000.0 * (endCpuTime - startCpuTime) / CLOCKS_PER_SEC;
        RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Took %f milliseconds of CPU time to make space for new vp3 files.", elapsedCpuTime);

        double elapsedTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
        RCLCPP_INFO(rclcpp::get_logger("VP3FileCreationApp"), "Took %f milliseconds of wall clock time to make space to new vp3 files.", elapsedTime);
    }

    bool haveSpace = ((numFiles + newVp3FileCount) <= maxFiles) && ((totalSize + newVp3FileSize) <= maxSize);

    return haveSpace;
}
