#include <list>
#include <array>
#include <chrono>
#include <sstream>
#include <map>
#include <utility>
#include <ctime>

#include <sys/stat.h>
#include <fcntl.h>

#include <ecminfolib_private.h>

#include <chrono/convert.hpp>
#include <chrono/print.hpp>
#include <chrono/tz.hpp>
#include <fileio/iflocker.hpp>
#include <fileio/oflocker.hpp>
#include <fileio/sha1_fstream.hpp>

#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/archive_exception.hpp>

#include <ais/log/AisLogger.h>
#include <fileio/nvm.hpp>
namespace nvm = tes_common_ais::nvm;

/* For debugging
#include <ais/time/TimeStamp.h>
#include <ais/time/ConvertTime.h>
*/

#include <interfaces/FileTransferBridgeRequest/InterfaceTypes.h>

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

task::AbstractTaskCore* task::getTaskImplementation(void)
{
    static VP3FileCreationApp thisTask("VP3FileCreationApp");
    return dynamic_cast<Task *>(&thisTask);
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
    task::Task(taskName),
    tempRoot_(DEFAULT_TEMP_ROOT),
    storageRoot_(DEFAULT_STORAGE_ROOT),
    VP3_Rec_input_(nullptr),
    createFileRequestInput_(nullptr),
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
    AppRegList(taskName),
    AppRegInput_(nullptr),
    AppRegOutput_(nullptr),
    FileTransferBridgeRequestOutput_(nullptr),
    vp3FilesDestinationApp("FileTransferBridgeApp"),
    LastDownloadTimestamp_(),
    ShmClockInput_(nullptr),
    PartNumbersInput_(nullptr),
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
    if (!task::InterfaceDb::bind("VP3RecordInput", VP3_Rec_input_)) {
        AIS_LOG_FATAL("VP3RecordInput interface not defined");
        return false;
    }

    if (!task::InterfaceDb::bind("CreateFileRequestInput", createFileRequestInput_)) {
        AIS_LOG_FATAL("CreateFileRequestInput interface not defined");
        return false;
    }

    if (!task::InterfaceDb::bind("AppRegOutput", AppRegOutput_)) {
        AIS_LOG_FATAL("AppRegOutput interface not defined");
        return false;
    }

    if (!task::InterfaceDb::bind("AppRegInput", AppRegInput_)) {
        AIS_LOG_FATAL("AppRegInput interface not defined");
        return false;
    }

    if (!task::InterfaceDb::bind("FileTransferBridgeRequestOutput", FileTransferBridgeRequestOutput_)) {
        AIS_LOG_FATAL("FileTransferBridgeRequestOutput interface not defined");
        return false;
    }

    if (!task::InterfaceDb::bind("PartNumbersInput", PartNumbersInput_)) {
        AIS_LOG_FATAL("PartNumbersInput interface not defined");
        return false;
    }

    if (!task::InterfaceDb::bind("ShmClockInput", ShmClockInput_)) {
        AIS_LOG_FATAL("ShmClockInput interface not defined");
        return false;
    }

    { // Get the configs and print it out.
        ConfigSection& configs = getTaskConfig();

        if (!configs.get("recordDataSizeTxTrigger", recordDataSizeTxTrigger_)) {
            recordDataSizeTxTrigger_ = DEFAULT_RECORD_DATA_SIZE_TX_TRIGGER;
        }

        if (!configs.get("recordCountTxTrigger", recordCountTxTrigger_)) {
            recordCountTxTrigger_ = DEFAULT_RECORD_COUNT_TX_TRIGGER;
        }

        if (!configs.get("maxVP3StorageSize", maxVP3StorageSize_)) {
            maxVP3StorageSize_ = DEFAULT_MAX_VP3_STORAGE_SIZE;
        }

        if (!configs.get("maxVP3StorageFiles", maxVP3StorageFiles_)) {
            maxVP3StorageFiles_ = DEFAULT_MAX_VP3_STORAGE_FILES;
        }

        // Are status records required?
        if (!configs.get("requireStatusRecord", requireStatusRecord_)) {
            requireStatusRecord_ = true;
        }

        std::string storageRoot;
        if (configs.get("storageRoot", storageRoot)) {
            storageRoot_ = storageRoot;
        }
        else {
            storageRoot_ = DEFAULT_STORAGE_ROOT;
        }

        std::string tempRoot;
        if (configs.get("tempRoot", tempRoot)) {
            tempRoot_ = tempRoot;
        }
        else {
            tempRoot_ = DEFAULT_TEMP_ROOT;
        }

        std::string vp3TxPath;
        if (configs.get("VP3TxPath", vp3TxPath)) {
            vp3TxPath_ = vp3TxPath;
        }
        else {
            AIS_LOG_FATAL("'VP3TxPath' configuration not found.");
            return false;
        }

        // Initialize the subdirectories for VP3 file creation and storage.
        vp3TempPath_ = tempRoot_ / VP3_SUBDIR;
        vp3StoragePath_ = storageRoot_ / VP3_SUBDIR;

        AIS_LOG_INFO("Storage Root: %s", storageRoot_.c_str());
        AIS_LOG_INFO("Temp Root: %s", tempRoot_.c_str());
        AIS_LOG_INFO("VP3 Tx Path: %s", vp3TxPath_.c_str());
        AIS_LOG_INFO("VP3 Temp Path: %s", vp3TempPath_.c_str());
        AIS_LOG_INFO("VP3 Storage Path: %s", vp3StoragePath_.c_str());

        { // Get key off timeout
            unsigned int keyoffTime;
            if (!configs.get("VP3KeyoffTimeout", keyoffTime)) {
                keyoffTime = 0;
            }

            AIS_LOG_INFO("Key off Timeout: %u" , keyoffTime);

            AppRegList.SetKeyOffTimeOutMSec(keyoffTime);
        }
    }

    totalReceivedRecordSize_ = 0;
    totalReceivedRecordCount_ = 0;

    // Load stuff from storage and create directories
    try {
        fs::create_directories(storageRoot_);
        fs::create_directories(tempRoot_);

        if (!LastDownloadTimestamp_.load(makeStoragePath(LASTDOWNLOADTIMESTAMP_FILENAME_BIN))) {
            AIS_LOG_INFO("Inside reset if");
            resetLastDownloadTimestamp_ = true;
            LastDownloadTimestamp_.reset();
        }

        if (!ReadPartNumsFromNVM()) {
            swGroupPartNum_.clear();
            modelNum_.clear();
            ecmPartNum_.clear();
        }
        
        if (!nvm::read(storageRoot_, STATUS_RECORD_FILENAME_BIN, latestStatusRecord)) {
            /*
             * Make a default status record that has the earliest time possible
             * and default values for all other fields.  This will act as the status
             * record until a real status record comes in.
             */
            latestStatusRecord = VP3RecordBuilder::makeStatusRecord(0, 0, 0, "", "", 0.f, "");
        }

        AIS_LOG_INFO("At init LastDownloadTimestamp_.LastDownloadTimestamp.UTC : %d", LastDownloadTimestamp_.LastDownloadTimestamp.UTC);
        AIS_LOG_INFO("At init LastDownloadTimestamp_.LastDownloadTimestamp.Offset : %d", LastDownloadTimestamp_.LastDownloadTimestamp.Offset);
        AIS_LOG_INFO("At init LastDownloadTimestamp_.LastDownloadTimestamp.SMH : %d", LastDownloadTimestamp_.LastDownloadTimestamp.SMH);

        // Create the directories for VP3 file creation and storage.
        fs::create_directories(vp3TempPath_);
        fs::create_directories(vp3StoragePath_);
    }
    catch (const fs::filesystem_error& e) {
        AIS_LOG_ERROR(e.what());
    }

    // Clean up vp3 file storage if it is taking up too much space.
    makeSpaceForNewVp3File(0);

    AIS_LOG_INFO("VP3FileCreationApp::initialize: %i, %i", recordDataSizeTxTrigger_, recordCountTxTrigger_);
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
    AIS_LOG_INFO("executive");

    UpdateRegistrations();

    getACDscsObject();
    AIS_LOG_INFO("swGroupPartNum_ %s", swGroupPartNum_.c_str());
    AIS_LOG_INFO("modelNum_ %s", modelNum_.c_str());
    AIS_LOG_INFO("ecmPartNum_ %s", ecmPartNum_.c_str());

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

        if (nullptr != createFileRequestInput_) {
            // Consume all records looking for Mine
            CreateFileRequest request;
            while (createFileRequestInput_->get(request)) {
                if (request.fileNumber == VP3_FILE_NUM) {
                    createFileFlag = true;
                    createFileRequester = request.Requester;
                }
            }
        }

        // Check whether we need to create the file based on SCS Command or size/record count trigger
        if (createFileFlag) {
            if (myRecordTypeContainers.empty()) {
                AIS_LOG_NOTICE("No file created because of no records, requester = %s.", createFileRequester.c_str());
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

        AIS_LOG_INFO("Reset LastDownloadTimestamp_.LastDownloadTimestamp.UTC : %d", LastDownloadTimestamp_.LastDownloadTimestamp.UTC);
        AIS_LOG_INFO("Reset LastDownloadTimestamp_.LastDownloadTimestamp.Offset : %d", LastDownloadTimestamp_.LastDownloadTimestamp.Offset);
        AIS_LOG_INFO("Reset LastDownloadTimestamp_.LastDownloadTimestamp.SMH : %d", LastDownloadTimestamp_.LastDownloadTimestamp.SMH);
    }

    /*
    { // For debugging
        auto now = std::chrono::system_clock::now();
        std::string nowStr = tes_common_ais::putTime(now, "%m/%d/%Y %H:%M:%S");
        TimeStamp cNow = commonNow();
        std::string commonNowStr = convertGPSToGMTString(cNow, "%m/%d/%Y %H:%M:%S");

        AIS_LOG_WARN("SYS | %s | SHM | %s | SHML | %s | CMN | %s", nowStr.c_str(), shmClockUTCString.c_str(), shmClockLocalString.c_str(), commonNowStr.c_str());
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
void VP3FileCreationApp::cleanup()
{
    AIS_LOG_INFO("VP3FileCreationApp::cleanup");

    // Keep accumulating VP3 records as long as we are registered with apps producing them (or until a key-off timeout)
    while (!AppRegList.IsAppRegListEmpty() && !AppRegList.IsKeyOffTimeOut()) {

        usleep(VP3_CLEANUP_SLEEP_TIME); // sleep 100 msec + 20 msec in IsKeyOffTimeOut for each loop. total of 120ms

        AIS_LOG_NOTICE("Waiting %d : %d", AppRegList.GetTimeDiffMSec(), AppRegList.GetKeyOffTimeOutMSec());

        // Process any new incoming records
        processIncomingRecords();

        // Update registration with other apps
        UpdateRegistrations();
    }

    nvm::store(storageRoot_, STATUS_RECORD_FILENAME_BIN, latestStatusRecord);

    // Process any remaining incoming records
    processIncomingRecords();

    // Generate the last file and send it out
    if (myRecordTypeContainers.empty()) {
        AIS_LOG_NOTICE("No cleanup file created because of no records.");
    }
    else {
        createFile("KeyOff");
    }

    // Log which apps are still trying to keep us alive.
    const auto& activeAppNames = AppRegList.GetActiveAppNames();
    for (const auto& name : activeAppNames) {
        AIS_LOG_NOTICE("ListActiveAppNames::%s", name.c_str());
    }

   
    // Add sleep so that we give some time for FTB to transfer the last file before unregistering  
    usleep(VP3_CLEANUP_SLEEP_TIME); // sleep 100 msec + 20 msec in IsKeyOffTimeOut for each loop. total of 120ms
        
    if ((nullptr != AppRegOutput_) && AppRegistered) {
        // Build a registration severance request from this app
        AppReg newRequest;
        newRequest.SetAppRegAttr(AppRegList.GetAppName(), AppRegStorage::APP_REG_STATE_INACTIVE, vp3FilesDestinationApp);
        AppRegOutput_->publish(newRequest);
        AIS_LOG_NOTICE("Vp3FileCreatorApp: Unregistration with %s", vp3FilesDestinationApp.c_str());
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

    AIS_LOG_NOTICE("Create File Requester: %s", requester.c_str());

    if (!PartNumbers::IsProductIdValid(productId_)) {
        AIS_LOG_ERROR("Failed to create file, product id '%s' is not valid.", productId_.c_str());
        return;
    }

    Add_VP3_header_block();

    std::string vp3FileName = fileTransferRequest.GenerateFileNamev2(VP3_FILE_NUM, productId_, "VP3").Name;

    fs::path tempFilePath = vp3TempPath_ / vp3FileName;
    fs::path storageFilePath = vp3StoragePath_ / vp3FileName;
    fs::path txFilePath = vp3TxPath_ / vp3FileName;

    AIS_LOG_NOTICE("VP3 Tx File Path: %s", txFilePath.c_str());

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
                AIS_LOG_ERROR("Error Writing P2 Block to VP3 file");
            }

            fwrite(container.getUID64().data(), container.getUID64().length(), 1, vp3File);
            if (ferror(vp3File)) {
                AIS_LOG_ERROR("Error Writing UIDs to VP3 file");
            }

            uint_to_byteArr(container.getNumberOfUIDs()-1, &R2[4]);
            uint_to_byteArr(container.getSizeOfRecord(), &R2[6]);
            uint_to_byteArr(container.getNumberOfRecords(), &R2[8]);

            fwrite(R2, sizeof(R2[0]), sizeof(R2)/sizeof(R2[0]), vp3File);
            if (ferror(vp3File)) {
                AIS_LOG_ERROR("Error Writing R2 Block to VP3 file");
            }

            fwrite(container.getRBlockData().data(), container.getRBlockData().length(), 1, vp3File);
            if (ferror(vp3File)) {
                AIS_LOG_ERROR("Error Writing record data to VP3 file");
            }

            sizeOfVp3File += (14 + container.getUID64().length() + container.getRBlockData().length()); //calculating size of the file
        }

        if (fclose(vp3File)) {
            AIS_LOG_ERROR("Error closing VP3 file");
        }

        auto tpEnd = std::chrono::system_clock::now();

        AIS_LOG_INFO("Duration (sec): %lf", std::chrono::duration_cast<std::chrono::milliseconds>(tpEnd - tpStart).count());

        bool copiedToStorage = false;

        // Make room for the new file in the storage directory
        if (makeSpaceForNewVp3File(sizeOfVp3File)) {
            // Copy the new file into the storage directory
            try {
                fs::copy_file(tempFilePath, storageFilePath, fs::copy_option::fail_if_exists);
                copiedToStorage = true;
            }
            catch (const fs::filesystem_error& e) {
                AIS_LOG_ERROR(e.what());
            }
        }
        else {
            // Cannot make space!
            AIS_LOG_ERROR("Cannot make space for new VP3 file in storage directoy.");
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

            fileTransferRequest.fileAttr.DirPath = txFilePath.parent_path().string() + "/";
            fileTransferRequest.fileAttr.SizeInBytes = sizeOfVp3File;

            if (nullptr != FileTransferBridgeRequestOutput_) {
                if (FileTransferBridgeRequestOutput_->publish(fileTransferRequest)) {
                    AIS_LOG_NOTICE("Published new VP3 file to file transfer bridge app.  Size is %d", sizeOfVp3File);
                }
                else {
                    AIS_LOG_ERROR("Failed to publish VP3 file to file transfer bridge app.");
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            AIS_LOG_ERROR(e.what());
        }

        // Remove the Temp file
        try {
            fs::remove(tempFilePath);
        }
        catch (const fs::filesystem_error& e) {
            AIS_LOG_ERROR(e.what());
        }
    }
    else {
        AIS_LOG_ERROR("Could not fopen VP3 file");
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
    if (nullptr != VP3_Rec_input_) {
        VP3Record record;
        while (VP3_Rec_input_->get(record)) {
            saveVp3Record(record);
        }
    }
}

void VP3FileCreationApp::UpdateRegistrations(void)
{
    AIS_LOG_INFO( "AppRegTest::UpdateRegistrations" );

    // Service all incoming requests and responses
    if (nullptr != AppRegInput_) {
        AppReg incomingReqResp;
        while (AppRegInput_->get(incomingReqResp)) {
            // Service only requests and responses addressed to this app
            if (incomingReqResp.IsMsgAddressedToMe(AppRegList.GetAppName())) {
                const bool isRequest = (incomingReqResp.GetMsgType() == AppRegStorage::APP_REG_REQ);
                AIS_LOG_INFO("Received register/unregister (%d) request or response (%d) from app '%s'",
                   static_cast<int>(incomingReqResp.GetAppState()),
                   static_cast<int>(incomingReqResp.GetMsgType()),
                   incomingReqResp.GetAppName().c_str());

                // If this was a request then send a response
                if (isRequest) {
                    AppRegList.UpdateAppRegState(&incomingReqResp);
                    AppRegOutput_->publish(incomingReqResp);
                }
                else if (vp3FilesDestinationApp == incomingReqResp.GetAppName() &&
                         (incomingReqResp.GetRegStatus() == AppRegStorage::APP_REG_APP_NAME_REGISTERED ||
                          incomingReqResp.GetRegStatus() == AppRegStorage::APP_REG_APP_NAME_ALREADY_REGISTERED)) {
                    AppRegistered = true;
                }
            }
        }
    }

    // Who is registered?
    const auto& activeAppNames = AppRegList.GetActiveAppNames();
    for (const auto& name : activeAppNames) {
        AIS_LOG_DEBUG("ListActiveAppNames::%s",name.c_str());
    }

    // Send out registration requests
    if (nullptr != AppRegOutput_) {
        if (!AppRegistered) {
            // Build a registration request from this app
            AppReg newRequest;
            newRequest.SetAppRegAttr(AppRegList.GetAppName(), AppRegStorage::APP_REG_STATE_ACTIVE, vp3FilesDestinationApp);
            AIS_LOG_INFO("Attempting to register with app '%s'", vp3FilesDestinationApp.c_str());
            AppRegOutput_->publish(newRequest);
        }
    }
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
    AIS_LOG_INFO( "After save LastDownloadTimestamp_.LastDownloadTimestamp.UTC : %d",LastDownloadTimestamp_.LastDownloadTimestamp.UTC );
    AIS_LOG_INFO( "After save LastDownloadTimestamp_.LastDownloadTimestamp.Offset : %d",LastDownloadTimestamp_.LastDownloadTimestamp.Offset );
    AIS_LOG_INFO( "After save LastDownloadTimestamp_.LastDownloadTimestamp.SMH : %d",LastDownloadTimestamp_.LastDownloadTimestamp.SMH );
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
    PartNumbers partNumbers;
    while (PartNumbersInput_->get(partNumbers)) {
        bool updateFile = false;

        if (partNumbers.IsProductIdNumSet()) {
            std::string productId(partNumbers.GetProductIdNum());
            if (productId_ != productId) {
                productId_ = std::move(productId);
                // product id is not stored in the file
            }
        }

        if (partNumbers.IsECMPartNumSet()) { 
            std::string ecmPartNum(partNumbers.GetECMPartNum());
            if (ecmPartNum_ != ecmPartNum) {
                ecmPartNum_ = std::move(ecmPartNum);
                updateFile = true;
            }
        }

        if (partNumbers.IsSwGroupPartNumSet()) {
            std::string swGroupPartNum(partNumbers.GetSwGroupPartNum());
            if (swGroupPartNum_ != swGroupPartNum) {
                swGroupPartNum_ = std::move(swGroupPartNum);
                updateFile = true;
            }
        }

        if (partNumbers.IsModelNumSet()) {
            std::string modelNum(partNumbers.GetModelNum());
            if (modelNum_ != modelNum) {
                modelNum_ = std::move(modelNum);
                updateFile = true;
            }
        }

        if (updateFile) {
            WritePartNumsToNVM(); // save the new data to nvm
        }
    }

    ShmClock shmClock;
    while (ShmClockInput_->get(shmClock)) {
        int32_t offset = shmClock.get_UTC_offset();
        tzone_tx_comm_struct tzone;

        if (tes_common_ais::get_tz_struct(tzone, shmClock) && ((tzInfo_.offset != offset) || (tzInfo_.index != tzone.tzone_id))) {
            std::string tzStr = tes_common_ais::makeTZString(tzone);
            if (tes_common_ais::setTZString(tzStr)) {
                AIS_LOG_INFO("Set TZ environment variable to '%s'.", tzStr.c_str());
                tes_common_ais::clearLocalTimeOffsetOverride();
            }
            else {
                AIS_LOG_ERROR("Could not set TZ environment variable to '%s'.", tzStr.c_str());
                tes_common_ais::setLocalTimeOffsetOverride(std::chrono::minutes(offset));
            }
            tzInfo_.offset = offset;
            tzInfo_.index = tzone.tzone_id;
        }

        shmSeconds_ = shmClock.get_SHM();

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
            AIS_LOG_INFO("Loaded Last Download Timestamp from storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not deserialize Last Download Timestamp from storage.");
            AIS_LOG_ERROR(e.what());
            reset();
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("Could not deserialize Last Download Timestamp from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (...) {
            AIS_LOG_ERROR("Could not deserialize Last Download Timestamp from storage, unexpected error.");
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                AIS_LOG_WARN("Last Download Timestamp file was corrupt... fixed it.");
            }
            else {
                AIS_LOG_ERROR("Last Download Timestamp file was corrupt... could not fix it.");
            }
        }
    }
    else {
        AIS_LOG_ERROR("Last Download Timestamp could not be opened from storage.");
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
            AIS_LOG_INFO("Saved Last Download Timestamp to storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not serialize Last Download Timestamp to storage.");
            AIS_LOG_ERROR(e.what());
        }

        ofs.close();
    }
    else {
        AIS_LOG_ERROR("Last Download Timestamp could not be opened from storage.");
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
            AIS_LOG_ERROR("Could not deserialize %s from storage.", PARTNUM_FILENAME_BIN);
            AIS_LOG_ERROR(e.what());
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("Could not deserialize %s from storage.", PARTNUM_FILENAME_BIN);
            AIS_LOG_ERROR(e.what());
        }
        catch (...) {
            AIS_LOG_ERROR("Could not deserialize %s from storage, unexpected error.", PARTNUM_FILENAME_BIN);
        }

        ifs.close();
        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                AIS_LOG_WARN("%s was corrupt... fixed it.", PARTNUM_FILENAME_BIN);
            }
            else {
                AIS_LOG_ERROR("%s was corrupt... could not fix it.", PARTNUM_FILENAME_BIN);
            }
        }
    }
    else {
        AIS_LOG_ERROR("%s could not be opened from storage.", PARTNUM_FILENAME_BIN);
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
            AIS_LOG_NOTICE("Saving %s to storage.", PARTNUM_FILENAME_BIN);
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not serialize %s to storage.", PARTNUM_FILENAME_BIN);
            AIS_LOG_ERROR(e.what());
        }
        ofs.close();
    }
    else {
        AIS_LOG_ERROR("%s could not be saved to storage.", PARTNUM_FILENAME_BIN);
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
                        AIS_LOG_WARN("Cannot get file size of %s", de.path().c_str());
                    }
                }
                else {
                    AIS_LOG_NOTICE("%s is not a regular file", de.path().c_str());
                }
            }
            catch (const fs::filesystem_error& e) {
                AIS_LOG_ERROR(e.what());
            }
        }
    }

    auto numFiles = fileMap.size();
    auto maxFiles = maxVP3StorageFiles_;
    AIS_LOG_NOTICE("Found %d files, maximum is %d", numFiles, maxVP3StorageFiles_);

    auto maxSize = maxVP3StorageSize_;
    AIS_LOG_NOTICE("Found %d bytes worth of data in storage directory, maximum is %d", totalSize, maxSize);

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
                AIS_LOG_NOTICE("Deleted file %s, %d files, %d bytes remaining", it->second.first.c_str(), numFiles, totalSize);
            }
            catch (const fs::filesystem_error& e) {
                AIS_LOG_ERROR(e.what());
            }

            ++it;
        }
    }

    std::clock_t endCpuTime = std::clock();
    auto endTime = std::chrono::high_resolution_clock::now();

    { // Log the time it took
        double elapsedCpuTime = 1000.0 * (endCpuTime - startCpuTime) / CLOCKS_PER_SEC;
        AIS_LOG_NOTICE("Took %f milliseconds of CPU time to make space for new vp3 files.", elapsedCpuTime);

        double elapsedTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
        AIS_LOG_NOTICE("Took %f milliseconds of wall clock time to make space to new vp3 files.", elapsedTime);
    }

    bool haveSpace = ((numFiles + newVp3FileCount) <= maxFiles) && ((totalSize + newVp3FileSize) <= maxSize);

    return haveSpace;
}
