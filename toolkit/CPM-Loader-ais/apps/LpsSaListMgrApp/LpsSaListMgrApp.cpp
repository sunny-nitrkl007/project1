#include <fstream>
#include <vector>
#include <iterator>
#include <utility>
#include <streambuf>
#include <chrono>
#include <array>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pkcs7.h>
#include <openssl/err.h>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <ais/task/Task.h>
#include <ais/log/Logger.h>

#include <base64/base64.hpp>

#include <interfaces/LpsSaListMgr/CPMListSync/CPMList.pb.h>
#include <interfaces/LpsSaListMgr/PostInterface.hpp>
#include <interfaces/LpsSaListMgr/NotifyInterface.hpp>
#include <interfaces/LpsSaListMgr/TxInterface.hpp>
#include <interfaces/FileTransferBridgeRequest/FileTransferBridgeRequest.h>
#include <interfaces/FileTransferBridgeResponse/FileTransferBridgeResponse.h>
#include <interfaces/FileTransferBridgeIndication/FileTransferBridgeIndication.h>

#include <fileio/sha1_fstream.hpp>
#include <chrono/convert.hpp>

#include "LpsSaListMgrApp.h"


namespace listsync = cat::cpm::list;
namespace fs = boost::filesystem;

#define LOCATIONS_PUBLISH_PERIOD_SEC (10.0f)
#define DEFAULT_FILE_TRANSFER_TX_DIR (R"(/tmp)")
#define DEFAULT_STORAGE_ROOT (R"(/tmp/LpsSaListMgrApp/storage)")
#define DEFAULT_TEMP_ROOT (R"(/tmp/LpsSaListMgrApp/temp)")

/*
 * main() will call this function in order to get the task instance.
 */
task::AbstractTaskCore* task::getTaskImplementation(void) {
    static LpsSaListMgrApp thisTask("LpsSaListMgrApp");
    return dynamic_cast<Task*>(&thisTask);
}

/*
 * Constructor
 */
LpsSaListMgrApp::LpsSaListMgrApp(const std::string& taskName) :
    task::Task(taskName),
    initNeeded_(true),
    initTimepoint_(std::chrono::steady_clock::now()),
    initListRevisionSent_(false),
    fileTransferTxDir_(DEFAULT_FILE_TRANSFER_TX_DIR),
    storageRoot_(DEFAULT_STORAGE_ROOT),
    tempRoot_(DEFAULT_TEMP_ROOT),
    truckListMgr_(),
    materialListMgr_(),
    operatorIdListMgr_(),
    customList1Mgr_(LpsSaListMgrInterfaceListType::CUSTOM1),
    customList2Mgr_(LpsSaListMgrInterfaceListType::CUSTOM2),
    customList3Mgr_(LpsSaListMgrInterfaceListType::CUSTOM3),
    customList4Mgr_(LpsSaListMgrInterfaceListType::CUSTOM4),
    postInputChannel_(nullptr),
    notifyOutputChannel_(nullptr),
    txOutputChannel_(nullptr),
    displayStateInput_(nullptr),
    fileTransferRequestOutputChannel_(nullptr),
    fileTransferResponseInputChannel_(nullptr),
    fileTransferIndicationInputChannel_(nullptr),
    inboxMonitor_() {
}

/*
 * Destructor
 */
LpsSaListMgrApp::~LpsSaListMgrApp() {
}

/*
 * AIS Task Initializer
 */
bool LpsSaListMgrApp::initialize() {
    bool everythingOk = true;
    AIS_LOG_NOTICE("LpsSaListMgrApp::initialize");

    { // Get the configs and print it out.
        ConfigSection& configs = getTaskConfig();
        std::string configStr;

        if (configs.get("fileTransferTxDir", configStr)) {
            fileTransferTxDir_ = configStr;
        }
        else {
            fileTransferTxDir_ = DEFAULT_FILE_TRANSFER_TX_DIR;
        }

        if (configs.get("storageRoot", configStr)) {
            storageRoot_ = configStr;
        }
        else {
            storageRoot_ = DEFAULT_STORAGE_ROOT;
        }

        if (configs.get("tempRoot", configStr)) {
            tempRoot_ = configStr;
        }
        else {
            tempRoot_ = DEFAULT_TEMP_ROOT;
        }

        AIS_LOG_NOTICE("File Transfer TX Dir: %s", fileTransferTxDir_.c_str());
        AIS_LOG_NOTICE("Storage Root: %s", storageRoot_.c_str());
        AIS_LOG_NOTICE("Temp Root: %s", tempRoot_.c_str());
    }

    // Initialize input and output channels
    postInputChannel_ = dynamic_cast<LpsSaListMgrPostInterfaceInputChannel*>(task::InterfaceDb::fetch("PostInput"));
    if (nullptr == postInputChannel_) {
        AIS_LOG_ERROR("No post input channel defined.");
        everythingOk = false;
    }

    notifyOutputChannel_ = dynamic_cast<LpsSaListMgrNotifyInterfaceOutputChannel*>(task::InterfaceDb::fetch("NotifyOutput"));
    if (nullptr == notifyOutputChannel_) {
        AIS_LOG_ERROR("No notify output channel defined.");
        everythingOk = false;
    }

    txOutputChannel_ = dynamic_cast<LpsSaListMgrTxInterfaceOutputChannel*>(task::InterfaceDb::fetch("TxOutput"));
    if (nullptr == txOutputChannel_) {
        AIS_LOG_ERROR("No tx output channel defined.");
        everythingOk = false;
    }

    displayStateInput_ = dynamic_cast<LpsSaUIDisplayStateInterfaceInputChannel*>(task::InterfaceDb::fetch("DisplayStateInput"));
    if (nullptr == displayStateInput_) {
        AIS_LOG_ERROR("No display state input channel defined.");
        everythingOk = false;
    }

    fileTransferRequestOutputChannel_ = dynamic_cast<FileTransferBridgeRequestOutputChannel*>(task::InterfaceDb::fetch("FileTransferBridgeRequestOutput"));
    if (nullptr == fileTransferRequestOutputChannel_) {
        AIS_LOG_ERROR("No file transfer request output channel defined.");
    }

    fileTransferResponseInputChannel_ = dynamic_cast<FileTransferBridgeResponseInputChannel*>(task::InterfaceDb::fetch("FileTransferBridgeResponseInput"));
    if (nullptr == fileTransferResponseInputChannel_) {
        AIS_LOG_ERROR("No file transfer response output channel defined.");
    }

    fileTransferIndicationInputChannel_ = dynamic_cast<FileTransferBridgeIndicationInputChannel*>(task::InterfaceDb::fetch("FileTransferBridgeIndicationInput"));
    if (nullptr == fileTransferIndicationInputChannel_) {
        AIS_LOG_ERROR("No file transfer indication input channel defined.");
    }

    // Load stuff from storage
    try {
        fs::create_directories(fileTransferTxDir_);
        fs::create_directories(storageRoot_);
        fs::create_directories(tempRoot_);
        fs::create_directories(inboxPath()); // Create inbox

        operatorIdListMgr_.initialize(storageRoot_);

        customList1Mgr_.initialize(storageRoot_);
        customList2Mgr_.initialize(storageRoot_);
        customList3Mgr_.initialize(storageRoot_);
        customList4Mgr_.initialize(storageRoot_);
        truckListMgr_.initialize(storageRoot_);
        materialListMgr_.initialize(storageRoot_);
    }
    catch (const fs::filesystem_error& e) {
        AIS_LOG_ERROR(e.what());
        everythingOk = false;
    }

    // Start the inbox directory monitor
    if (inboxMonitor_.start(inboxPath())) {
        AIS_LOG_NOTICE("Started the inbox monitor.");
    }
    else {
        AIS_LOG_ERROR("Could not start inbox monitor.");
        everythingOk = false;
    }

    return everythingOk;
}

/*
 * AIS Task Executive
 */
bool LpsSaListMgrApp::executive() {
    using T = LpsSaListMgrInterfaceListType;
    using F = LpsSaListMgrInterfaceListFormat;

    AIS_LOG_DEBUG("LpsSaListMgrApp::executive");

    bool operatorIdListChanged = false;

    struct PublishRequest {
        const LpsSaListMgr& listMgr;
        F format;
        std::string appName;
        uint32_t appRequestId;

        PublishRequest(const LpsSaListMgr& listMgr_, F format_) :
            listMgr(listMgr_), format(format_), appName(), appRequestId(0) {}

        PublishRequest(const LpsSaListMgr& listMgr_, const LpsSaListMgrPostInterfaceStorage& post_) :
            listMgr(listMgr_), format(post_.format), appName(post_.appName), appRequestId(post_.appRequestId) {}
    };

    std::vector<PublishRequest> publish;

    if (!initListRevisionSent_) {
        auto now = std::chrono::steady_clock::now();
        if ((now - initTimepoint_) > std::chrono::minutes(10)) {
            // Publish the list revisions to the backoffice without content for custom lists only for now
            sendListToBackOffice(customList1Mgr_, false);
            sendListToBackOffice(customList2Mgr_, false);
            sendListToBackOffice(customList3Mgr_, false);
            sendListToBackOffice(customList4Mgr_, false);
            sendListToBackOffice(truckListMgr_, false);
            sendListToBackOffice(materialListMgr_, false);

            initListRevisionSent_ = true;
        }
    }

    if (initNeeded_) {                
        // Publish the 'always publish' files
        publish.emplace_back(truckListMgr_, F::JSON);
        publish.emplace_back(truckListMgr_, F::CSV);
        publish.emplace_back(materialListMgr_, F::JSON);
        publish.emplace_back(materialListMgr_, F::CSV);
        publish.emplace_back(operatorIdListMgr_, F::JSON);
        publish.emplace_back(operatorIdListMgr_, F::CSV);
        publish.emplace_back(customList1Mgr_, F::JSON);
        publish.emplace_back(customList1Mgr_, F::CSV);
        publish.emplace_back(customList2Mgr_, F::JSON);
        publish.emplace_back(customList2Mgr_, F::CSV);
        publish.emplace_back(customList3Mgr_, F::JSON);
        publish.emplace_back(customList3Mgr_, F::CSV);
        publish.emplace_back(customList4Mgr_, F::JSON);
        publish.emplace_back(customList4Mgr_, F::CSV);
        initNeeded_ = false;
    }
    else {

        { // First receive files from offboard
            T type;
            while (updateListSyncRx(type)) {
                switch (type) {
                case (T::TRUCK): {
                    publish.emplace_back(truckListMgr_, F::JSON);
                    publish.emplace_back(truckListMgr_, F::CSV);
                    break;
                }
                case (T::MATERIAL): {
                    AIS_LOG_NOTICE("Loaded new material list from file bridge app.");
                    publish.emplace_back(materialListMgr_, F::JSON);
                    publish.emplace_back(materialListMgr_, F::CSV);
                    break;
                }
                case (T::CUSTOM1): {
                    AIS_LOG_NOTICE("Loaded new custom1 list from file bridge app.");
                    publish.emplace_back(customList1Mgr_, F::JSON);
                    publish.emplace_back(customList1Mgr_, F::CSV);
                    break;
                }
                case (T::CUSTOM2): {
                    AIS_LOG_NOTICE("Loaded new custom2 list from file bridge app.");
                    publish.emplace_back(customList2Mgr_, F::JSON);
                    publish.emplace_back(customList2Mgr_, F::CSV);
                    break;
                }                
                case (T::CUSTOM3): {
                    AIS_LOG_NOTICE("Loaded new custom3 list from file bridge app.");
                    publish.emplace_back(customList3Mgr_, F::JSON);
                    publish.emplace_back(customList3Mgr_, F::CSV);
                    break;
                }                
                case (T::CUSTOM4): {
                    AIS_LOG_NOTICE("Loaded new custom4 list from file bridge app.");
                    publish.emplace_back(customList4Mgr_, F::JSON);
                    publish.emplace_back(customList4Mgr_, F::CSV);
                    break;
                }
                default: {
                    AIS_LOG_WARN("Unsupported list type from offboard.");
                    break;
                }
                }
            }
        }

        { // See if we have any files in our inbox
            std::string fileName;
            while (inboxMonitor_.nextFile(fileName)) {
                // We got a new file dropped here
                boost::filesystem::path filePath = inboxMonitor_.makeFullPath(fileName);

                /*
                 * During testing it was found that something is causing a second IN_CLOSE_WRITE event
                 * on each file after the file read lock was removed and the file was closed.
                 *
                 * I don't know which specific operation is causing the event to be generated, but neither *should*.
                 * In any case, checking for the existence of the file should bail if we get a notification
                 * for a file that was removed.
                 *
                 * Also, we are loading the files with "NoLock" versions of the load function
                 * so that we can avoid the second IN_CLOSE_WRITE notification.
                 */
                try {
                    if (!boost::filesystem::is_regular_file(filePath)) {
                        AIS_LOG_WARN("Inbox file either doesn't exist or it not a regular file %s", filePath.c_str());
                        continue;
                    }
                }
                catch (const std::exception& e) {
                    AIS_LOG_ERROR("Inbox file %s status error %s", filePath.c_str(), e.what());
                    continue;
                }

                if (fileName == "operator_id_list.csv") {
                    if (operatorIdListMgr_.loadNoLock(F::CSV, filePath.string())) {
                        publish.emplace_back(operatorIdListMgr_, F::JSON);
                        publish.emplace_back(operatorIdListMgr_, F::CSV);
                        operatorIdListChanged = true;
                        AIS_LOG_NOTICE("New operator id list loaded from inbox. %s", fileName.c_str());
                    }
                    else {
                        AIS_LOG_WARN("Failed to load new operator id list from inbox. %s", fileName.c_str());
                    }
                }
                else if ((0 == fileName.rfind("custom_list_", 0)) || (fileName == "material_list.csv") ||
                        (fileName == "truck_list.csv") ) {
                    // Starts with "custom_list_"
                    LpsSaListMgr* pListMgr = nullptr;

                    if (fileName == "custom_list_1.csv") {
                        pListMgr = &customList1Mgr_;
                    }
                    else if (fileName == "custom_list_2.csv") {
                        pListMgr = &customList2Mgr_;
                    }
                    else if (fileName == "custom_list_3.csv") {
                        pListMgr = &customList3Mgr_;
                    }
                    else if (fileName == "custom_list_4.csv") {
                        pListMgr = &customList4Mgr_;
                    }
                    else if (fileName == "material_list.csv") {
                        pListMgr = &materialListMgr_;
                    }
                    else if (fileName == "truck_list.csv") {
                        pListMgr = &truckListMgr_;
                    }

                    if (nullptr != pListMgr) {
                        if (pListMgr->loadNoLock(F::CSV, filePath.string())) {
                            pListMgr->saveToStorage();
                            publish.emplace_back(*pListMgr, F::JSON);
                            publish.emplace_back(*pListMgr, F::CSV);
                            sendListToBackOffice(*pListMgr);
                            AIS_LOG_NOTICE("New list loaded from inbox. %s", fileName.c_str());
                        }
                        else {
                            AIS_LOG_WARN("Failed to load new list from inbox. %s", fileName.c_str());
                        }
                    }
                    else {
                        AIS_LOG_WARN("New unsupported file in inbox. %s", fileName.c_str());
                    }
                }
                else {
                    AIS_LOG_WARN("New unsupported file in inbox. %s", fileName.c_str());
                }

                // Remove the file.
                try {
                    if (boost::filesystem::remove(filePath)) {
                        AIS_LOG_NOTICE("Removed file %s", filePath.c_str());
                    }
                    else {
                        // File didn't exist to begin with.
                        AIS_LOG_WARN("How did we get here if the file didn't exist? %s", filePath.c_str());
                    }
                }
                catch (const std::exception& e) {
                    /*
                     * If we can't remove the file, we risk running an infinite loop
                     * where we continue to get notifications for the same file over
                     * and over again.  The safest thing to do here would be to bail
                     * so that we stop getting notifications.
                     */
                    AIS_LOG_ERROR("Cannot remove %s, stop listening to inbox - %s", filePath.c_str(), e.what());
                    inboxMonitor_.stop();
                }
            }
        }

        { // Handle one "post" request at a time from SCS
            LpsSaListMgrPostInterface post;

            if (postInputChannel_->get(post)) {
                LpsSaListMgr* pListMgr = nullptr;

                switch (post.type) {
                case (T::TRUCK): {
                    pListMgr = &truckListMgr_;
                    break;
                }
                case (T::MATERIAL): {
                    pListMgr = &materialListMgr_;
                    break;
                }
                case (T::CUSTOM1): {
                    pListMgr = &customList1Mgr_;
                    break;
                }
                case (T::CUSTOM2): {
                    pListMgr = &customList2Mgr_;
                    break;
                }
                case (T::CUSTOM3): {
                    pListMgr = &customList3Mgr_;
                    break;
                }
                case (T::CUSTOM4): {
                    pListMgr = &customList4Mgr_;
                    break;
                }
                default: {
                    AIS_LOG_WARN("Unsupported list type.");
                    break;
                }
                }

                // This is a generic handler for a list
                if (nullptr != pListMgr) {
                    if (post.filePath.empty()) {
                        if (!post.name.empty()) {
                            // Change the name
                            pListMgr->setListName(post.name);
                            pListMgr->saveToStorage();
                            sendListToBackOffice(*pListMgr);

                            // At least publish it JSON format since that includes the list name
                            if (post.format != F::JSON) {
                                publish.emplace_back(*pListMgr, F::JSON);
                            }
                        }

                        // Publish out the desired format.
                        publish.emplace_back(*pListMgr, post);
                    }
                    else if (pListMgr->load(post.format, post.filePath)) {
                        if (!post.name.empty()) {
                            // Change the name
                            pListMgr->setListName(post.name);
                        }

                        // Updated the list, save it and notify
                        pListMgr->saveToStorage();
                        sendListToBackOffice(*pListMgr);

                        publish.emplace_back(*pListMgr, post);
                        if (post.format != F::JSON) {
                            publish.emplace_back(*pListMgr, F::JSON);
                        }
                        if (post.format != F::CSV) {
                            publish.emplace_back(*pListMgr, F::CSV);
                        }
                    }
                    else {
                        AIS_LOG_ERROR("Failed to load file: %s", post.filePath.c_str());
                    }
                }
            }
        }
    }

    // If the operator id list changed, then save it and publish the changes.
    if (operatorIdListChanged) {
        operatorIdListMgr_.saveToStorage();
    }

    while (displayStateInput_->get(displayState)) {
    }

    { // Publish the changes and notify
        for (const auto& p : publish) {
            // Skip it if the format is unspecified.
            if (F::NONE == p.format) {
                continue;
            }

            // Get the file name based on the format
            std::string fileName = p.listMgr.getFileName(p.format);
            if (fileName.empty()) {
                continue;
            }

            // Make the path to publish to
            std::string filePath = makeTempPath(fileName);

            // Publish the file of the requested format
            if (p.listMgr.publish(p.format, filePath, displayState.state.getSettings().weightUnits)) {
                // Notify everyone that a new file is available.
                LpsSaListMgrNotifyInterface notify;
                notify.appName = p.appName;
                notify.appRequestId = p.appRequestId;
                notify.type = p.listMgr.getListType();
                notify.format = p.format;
                notify.name = p.listMgr.getListName();
                notify.filePath = filePath;
                notifyOutputChannel_->publish(notify);
           }
        }
    }

    { // Publish the locations every cycle
        LpsSaListMgrTxInterface tx;
        tx.basePath = tempRoot_.string();
        tx.customList1Name = customList1Mgr_.getListName();
        tx.customList2Name = customList2Mgr_.getListName();
        tx.customList3Name = customList3Mgr_.getListName();
        tx.customList4Name = customList4Mgr_.getListName();
        txOutputChannel_->publish(tx);
    }

    return true;
}

/*
 * AIS Task Cleanup
 */
void LpsSaListMgrApp::cleanup() {
    AIS_LOG_NOTICE("LpsSaListMgrApp::cleanup");

    // Stop the inbox monitor.
    inboxMonitor_.stop();
}

/*
 * Update list synchronization RX
 *  returns true if a new list was received and sets the 'type' of the list.
 *  This is meant to be called repeatedly until it returns false.
 */
bool LpsSaListMgrApp::updateListSyncRx(LpsSaListMgrInterfaceListType& type) {
    if (nullptr != fileTransferIndicationInputChannel_) {
        FileTransferBridgeIndication ind;

        while (fileTransferIndicationInputChannel_->get(ind)) {            
            unsigned int filetype = ind.fileAttr.TelematicsFileNumber;
            if ( (10638 == filetype) || (10639 == filetype) || (10640 == filetype) || (10641 == filetype) ||
                    (10642 == filetype) || (10643 == filetype)) {
                // received new list sync file type (protobuf)

                // Build the path
                fs::path p(ind.fileAttr.DirPath);
                p /= ind.fileAttr.Name;

                // Open the file
                std::ifstream ifs(p.string());
                if (ifs) {
                    LpsSaListMgr* listMgrPtr;
                    if (10638 == ind.fileAttr.TelematicsFileNumber) {
                        listMgrPtr = &customList1Mgr_;
                        type = LpsSaListMgrInterfaceListType::CUSTOM1;
                    }
                    else if (10639 == ind.fileAttr.TelematicsFileNumber) {
                        listMgrPtr = &customList2Mgr_;
                        type = LpsSaListMgrInterfaceListType::CUSTOM2;
                    }
                    else if (10640 == ind.fileAttr.TelematicsFileNumber) {
                        listMgrPtr = &customList3Mgr_;
                        type = LpsSaListMgrInterfaceListType::CUSTOM3;
                    }
                    else if (10641 == ind.fileAttr.TelematicsFileNumber) {
                        listMgrPtr = &customList4Mgr_;
                        type = LpsSaListMgrInterfaceListType::CUSTOM4;
                    }
                    else if (10642 == ind.fileAttr.TelematicsFileNumber) {
                        listMgrPtr = &truckListMgr_;
                        type = LpsSaListMgrInterfaceListType::TRUCK;
                    }
                    else if (10643 == ind.fileAttr.TelematicsFileNumber) {
                        listMgrPtr = &materialListMgr_;
                        type = LpsSaListMgrInterfaceListType::MATERIAL;
                    }
                    else {
                        AIS_LOG_ALERT("Unhandled file type received: %d", ind.fileAttr.TelematicsFileNumber);
                        continue;
                    }
                    
                    listsync::List listParsedProtoBuf;                    
                    if (listParsedProtoBuf.ParseFromIstream(&ifs)) {
                        std::chrono::system_clock::time_point revision = {};
                        if (listMgrPtr->hasContent(listParsedProtoBuf)) {
                            if (listMgrPtr->isNewer(listParsedProtoBuf, revision)) {
                                // backoffice list is newer than onboard, make this the new list
                                if (listMgrPtr->loadFromProtobuf(listParsedProtoBuf)) {
                                    // save to storage and pass new list revision
                                    listMgrPtr->saveToStorage(revision);
                                    return true;
                                }
                                else {
                                    AIS_LOG_ERROR("File parse error for list filetype: %d", ind.fileAttr.TelematicsFileNumber);
                                }
                            }
                        }
                        else {
                            // only revision status sent, if backoffice is older, send ours otherwise do nothing
                            if (listMgrPtr->isOlder(listParsedProtoBuf, revision)) {
                                // backoffice is older, send ours
                                sendListToBackOffice(*listMgrPtr);
                            }
                            else if  (listMgrPtr->isNewer(listParsedProtoBuf, revision)) {
                                // backoffice revision is newer but did not send content
                                AIS_LOG_ERROR("Backoffice is newer for list filetype: %d but did not send the contents", ind.fileAttr.TelematicsFileNumber);
                            }
                            else {
                                // backoffice revision is the same as ours, do nothing
                            }
                        }
                    }

                    ifs.close();
                }
                
            }
        }
    }
    return false;
}

bool LpsSaListMgrApp::sendListToBackOffice(const LpsSaListMgr& listMgr, bool content) {
    bool success = false;
    {
        FileTransferBridgeRequest request;
        request.fileAttr = request.GenerateFileName(listMgr.getListFileType(), "pb");
        request.fileAttr.Name = std::to_string(listMgr.getListFileType()) + "_" + request.fileAttr.Name;
        request.fileAttr.DirPath = fileTransferTxDir_.string() + fs::path::preferred_separator;

        std::string filePath = (fileTransferTxDir_ / request.fileAttr.Name).string();

        AIS_LOG_INFO("send: %s", request.fileAttr.Name.c_str());

        // Generate the file
        std::ofstream ofs(filePath);
        if (content) {
            listMgr.serializeToProtobuf(ofs);
        }
        else {
            listMgr.createListRevision(ofs);
        }
        
        request.fileAttr.SizeInBytes = ofs.tellp();
        ofs.close();

        // Send the file
        if (nullptr != fileTransferRequestOutputChannel_) {
            if (fileTransferRequestOutputChannel_->publish(request)) {
                success = true;
            }
            else {
                AIS_LOG_ERROR("Unable to publish file transfer request.");
            }
        }
        else {
            AIS_LOG_ERROR("No file transfer request output channel defined.");
        }
    }

    return success;
}

