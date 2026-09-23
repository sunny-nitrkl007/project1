#include <fstream>
#include <iterator>

#include <boost/filesystem.hpp>

#include <ais/task/Task.h>
#include <ais/log/Logger.h>

#include <fileio/iflocker.hpp>
#include <fileio/oflocker.hpp>

#include <interfaces/LpsSaListMgr/InterfaceCommon.h>
#include <interfaces/LpsSaListMgr/PostInterface.hpp>
#include <interfaces/LpsSaListMgr/NotifyInterface.hpp>
#include <interfaces/LpsSaListMgr/TxInterface.hpp>

#include "LpsSaListMgrTestApp.h"

namespace fs = boost::filesystem;
namespace ip = boost::interprocess;
namespace pt = boost::posix_time;

#define DEFAULT_TEMP_ROOT (R"(/tmp/LpsSaListMgrTestApp/temp)")

/*
 * main() will call this function in order to get the task instance.
 */
task::AbstractTaskCore* task::getTaskImplementation(void) {
    static LpsSaListMgrTestApp thisTask("LpsSaListMgrTestApp");
    return dynamic_cast<Task*>(&thisTask);
}

/*
 * Constructor
 */
LpsSaListMgrTestApp::LpsSaListMgrTestApp(const std::string& taskName) :
    task::Task(taskName),
    kbInputFuture_(),
    tempRoot_(DEFAULT_TEMP_ROOT),
    postOutputChannel_(nullptr),
    notifyInputChannel_(nullptr),
    txInputChannel_(nullptr) {
}

/*
 * Destructor
 */
LpsSaListMgrTestApp::~LpsSaListMgrTestApp() {
}

/*
 * AIS Task Initializer
 */
bool LpsSaListMgrTestApp::initialize() {
    bool everythingOk = true;
    AIS_LOG_NOTICE("LpsSaListMgrTestApp::initialize");

    { // Get the configs and print it out.
        ConfigSection& configs = getTaskConfig();

        std::string tempRoot;
        if (configs.get("tempRoot", tempRoot)) {
            tempRoot_ = tempRoot;
        }
        else {
            tempRoot_ = DEFAULT_TEMP_ROOT;
        }

        AIS_LOG_NOTICE("Temp Root: %s", tempRoot_.c_str());
    }

    // Initialize input and output channels
    postOutputChannel_ = dynamic_cast<LpsSaListMgrPostInterfaceOutputChannel*>(task::InterfaceDb::fetch("PostOutput"));
    if (nullptr == postOutputChannel_) {
        AIS_LOG_ERROR("No post output channel defined.");
        everythingOk = false;
    }

    notifyInputChannel_ = dynamic_cast<LpsSaListMgrNotifyInterfaceInputChannel*>(task::InterfaceDb::fetch("NotifyInput"));
    if (nullptr == notifyInputChannel_) {
        AIS_LOG_ERROR("No notify input channel defined.");
        everythingOk = false;
    }

    txInputChannel_ = dynamic_cast<LpsSaListMgrTxInterfaceInputChannel*>(task::InterfaceDb::fetch("TxInput"));
    if (nullptr == txInputChannel_) {
        AIS_LOG_ERROR("No tx input channel defined.");
        everythingOk = false;
    }

    // Load stuff from storage
    try {
        fs::create_directories(tempRoot_);
    }
    catch (const fs::filesystem_error& e) {
        AIS_LOG_ERROR(e.what());
        everythingOk = false;
    }

    return everythingOk;
}

/*
 * AIS Task Executive
 */
bool LpsSaListMgrTestApp::executive() {
    AIS_LOG_DEBUG("LpsSaListMgrTestApp::executive");

    // Print out when the file locations get published.
    LpsSaListMgrTxInterface tx;
    if (txInputChannel_->get(tx)) {
        AIS_LOG_NOTICE("Received locations:");
        AIS_LOG_NOTICE("\t%s", tx.getTruckListJsonPath().c_str());
        AIS_LOG_NOTICE("\t%s", tx.getTruckListCsvPath().c_str());
        AIS_LOG_NOTICE("\t%s", tx.getMaterialListJsonPath().c_str());
        AIS_LOG_NOTICE("\t%s", tx.getMaterialListCsvPath().c_str());
    }

    // Print out all file notifications.
    LpsSaListMgrNotifyInterface notify;
    while (notifyInputChannel_->get(notify)) {
        const char* type = LpsSaListMgrInterfaceListType_string(notify.type);
        const char* format = LpsSaListMgrInterfaceListFormat_string(notify.format);
        AIS_LOG_NOTICE("%s list published in %s format at '%s'.", type, format, notify.filePath.c_str());

        if (LpsSaListMgrInterfaceListFormat::JSON == notify.format) {
            tes_common_ais::IFlocker ifl(notify.filePath);
            if (ifl) {
                // Read the file and print it.
                std::istreambuf_iterator<char> begin(ifl.ifstream()), end;
                std::string contents{ begin, end };
                ifl.close();
                AIS_LOG_NOTICE("%s", contents.c_str());
            }
            else {
                AIS_LOG_ERROR("File could not be opened and locked for reading.");
            }
        }
    }

    /*
     * Get a command from keyboard input
     */
    std::string command("");
    if (kbInputFuture_.valid()) {
        // It is valid, poll it
        if (kbInputFuture_.wait_for(std::chrono::microseconds(1)) == std::future_status::ready) {
            command = kbInputFuture_.get();
            AIS_LOG_NOTICE(R"(Command received "%s")", command.c_str());
        }
    }

    if (!kbInputFuture_.valid()) {
        // Not valid, start a new async operation to get keyboard input.
        kbInputFuture_ = std::async(std::launch::async, [] {
                std::string s;
                std::getline(std::cin, s);
                return s;
        });
    }

    // Convert to upper case
    std::transform(command.begin(), command.end(), command.begin(), toupper);

    std::string truckList;
    std::string materialList;

    if (!command.empty()) {
        if (command.rfind("A", 0) == 0) {
            truckList = R"({
  "TruckList": [
    { "name": "A Truck 1", "id": 10, "targetWeight": 11.1 },
    { "name": "A Truck 2", "id": 20, "targetWeight": 12.1 },
    { "name": "A Truck 3", "id": 30, "targetWeight": 13.1 },
    { "name": "A Truck 4", "id": 40, "targetWeight": 14.1 },
    { "name": "A Truck 5", "id": 50, "targetWeight": 15.1 }
  ]
})";
        }

        else if (command.rfind("B", 0) == 0) {
            truckList = R"({
  "TruckList": [
    { "name": "B Truck 6", "id": 60, "targetWeight": 16.1 },
    { "name": "B Truck 7", "id": 70, "targetWeight": 17.1 },
    { "name": "B Truck 8", "id": 80, "targetWeight": 18.1 },
    { "name": "B Truck 9", "id": 90, "targetWeight": 19.1 },
    { "name": "B Truck 10", "id": 100, "targetWeight": 20.1 }
  ]
})";
        }

        else if (command.rfind("X", 0) == 0) {
            materialList = R"({
  "MaterialList": [
    { "name": "X Material 1", "id": 10, "density": 1710 },
    { "name": "X Material 2", "id": 20, "density": 1720 },
    { "name": "X Material 3", "id": 30, "density": 1730 },
    { "name": "X Material 4", "id": 40, "density": 1740 },
    { "name": "X Material 5", "id": 50, "density": 1750 }
  ]
})";
        }

        else if (command.rfind("Y", 0) == 0) {
            materialList = R"({
  "MaterialList": [
    { "name": "Y Material 6", "id": 60, "density": 1760 },
    { "name": "Y Material 7", "id": 70, "density": 1770 },
    { "name": "Y Material 8", "id": 80, "density": 1780 },
    { "name": "Y Material 9", "id": 90, "density": 1790 },
    { "name": "Y Material 10", "id": 100, "density": 1800 }
  ]
})";
        }
    }

    // Post new truck list if not empty.
    if (!truckList.empty()) {
        LpsSaListMgrPostInterface post;
        post.type = LpsSaListMgrInterfaceListType::TRUCK;
        post.format = LpsSaListMgrInterfaceListFormat::JSON;
        post.filePath = (tempRoot_ / "TruckList.json").string();

        tes_common_ais::OFlocker ofl(post.filePath);
        if (ofl) {
            ofl.ofstream() << truckList;
            ofl.close();
            postOutputChannel_->publish(post);
            AIS_LOG_NOTICE("Posted new truck list file.");
        }
        else {
            AIS_LOG_ERROR("Truck list file could not be opened and locked for writing.");
        }
    }

    // Post new material list if not empty.
    if (!materialList.empty()) {
        LpsSaListMgrPostInterface post;
        post.type = LpsSaListMgrInterfaceListType::MATERIAL;
        post.format = LpsSaListMgrInterfaceListFormat::JSON;
        post.filePath = (tempRoot_ / "MaterialList.json").string();

        tes_common_ais::OFlocker ofl(post.filePath);
        if (ofl) {
            ofl.ofstream() << materialList;
            ofl.close();
            postOutputChannel_->publish(post);
            AIS_LOG_NOTICE("Posted new material list file.");
        }
        else {
            AIS_LOG_ERROR("Material list file could not be opened and locked for writing.");
        }
    }

    return true;
}

/*
 * AIS Task Cleanup
 */
void LpsSaListMgrTestApp::cleanup() {
    AIS_LOG_NOTICE("LpsSaListMgrTestApp::cleanup");
}
