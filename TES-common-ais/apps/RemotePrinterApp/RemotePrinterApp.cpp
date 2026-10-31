#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <ais/task/Task.h>
#include <ais/log/AisLogger.h>

#include <fileio/iflocker.hpp>

#include <interfaces/SerialPrinter/RequestInterface.hpp>
#include <interfaces/FileTransferBridgeRequest/InterfaceTypes.h>

#include "Payload/Payload.pb.h"

#include "RemotePrinterApp.h"

namespace fs = boost::filesystem;

constexpr auto DEFAULT_TEMP_ROOT = (R"(/tmp/RemotePrinterApp/temp)");

static constexpr auto TEST_STRING = R"(  @@@@@@@         @@@    @@@@@@@@@@@@
 @@@@@@@@@       @@@@@   @@@@@@@@@@@@
@@@@@@@@@@@      @@@@@   @@@@@@@@@@@@
@@@@@ @@@@@      @@@@@   @@@@@@@@@@@@
@@@@   @@@@     @@@@@@@     @@@@@
@@@@   @@@@     @@@@@@@     @@@@@
@@@@   @@@@    @@@@@@@@@    @@@@@
@@@@   @@@@    @@@@ @@@@    @@@@@
@@@@   @@@@    @@@   @@@    @@@@@
@@@@   @@@@   @@@@   @@@@   @@@@@
@@@@          @@@@@@@@@@@   @@@@@
@@@@          @@@@@@@@@@@   @@@@@
@@@@          @@@@@ @@@@@   @@@@@
@@@@         @@@@@   @@@@@  @@@@@
@@@@   @@@@  @@@@  :  @@@@  @@@@@
@@@@   @@@@  @@@  :::  @@@  @@@@@
@@@@   @@@@  @@ .:::::. @@  @@@@@
@@@@   @@@@  @ .:::::::. @  @@@@@
@@@@   @@@@   .:::::::::.   @@@@@
@@@@   @@@@  :::::::::::::  @@@@@
@@@@@ @@@@  :::::::::::::::  @@@@
@@@@@@@@@ .:::::::::::::::::. @@@
 @@@@@@@ .:::::::::::::::::::. @@
  @@@@@ ::::::::::::::::::::::: @)";


/*
 * main() will call this function in order to get the task instance.
 */
task::AbstractTaskCore* task::getTaskImplementation(void) {
    static RemotePrinterApp thisTask("RemotePrinterApp");
    return dynamic_cast<Task*>(&thisTask);
}


/*
 * Constructor
 */
RemotePrinterApp::RemotePrinterApp(const std::string& taskName) :
    task::Task(taskName),
    destinationFid_(0),
    requestInputChannel_(nullptr),
    fileTransferBridgeRequestOutput_(nullptr),
    tempRoot_(DEFAULT_TEMP_ROOT) {
}


/*
 * Destructor
 */
RemotePrinterApp::~RemotePrinterApp() {
}


/*
 * AIS Task Initializer
 */
bool RemotePrinterApp::initialize() {
    bool everythingOk = true;
    AIS_LOG_INFO("RemotePrinterApp::initialize");

    // This will abort the program if there is a problem.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    { // Get the configs and print it out.
        ConfigSection& configs = getTaskConfig();

        // Get Destination FID
        if (!configs.get("destinationFid", destinationFid_)) {
            destinationFid_ = 0;
        }

        AIS_LOG_INFO("Destination Fid '%d'", destinationFid_);

        { // Get temp directory
            std::string tempRoot;
            if (configs.get("tempRoot", tempRoot)) {
                tempRoot_ = tempRoot;
            }
            else {
                tempRoot_ = DEFAULT_TEMP_ROOT;
            }

            AIS_LOG_INFO("Temp root '%s'", tempRoot_.c_str());
        }
    }

    // Bind the print request input interface.
    if (!task::InterfaceDb::bind("RequestInput", requestInputChannel_)) {
        AIS_LOG_ERROR("No request input channel defined.");
        everythingOk = false;
    }

    // Bind the file transfer bridge request output interface.
    if (!task::InterfaceDb::bind("FileTransferBridgeRequestOutput", fileTransferBridgeRequestOutput_)) {
        AIS_LOG_ERROR("No file transfer bridge request output channel defined.");
        everythingOk = false;
    }

    // Create temp directory
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
bool RemotePrinterApp::executive() {
    AIS_LOG_DEBUG("RemotePrinterApp::executive");

    // Handle one request at a time
    SerialPrinterRequestInterface request;

    if (requestInputChannel_->get(request)) {
        switch (request.command) {
            case (SerialPrinterRequestInterfaceCommand::PRINT): {
                tes_common_ais::IFlocker ifl(request.filePath());
                if (ifl) {
                    std::ifstream& ifs = ifl.ifstream();

                    std::ostringstream oss;
                    oss << ifs.rdbuf();

                    // If the last character is not a new line, add it.
                    if (NEW_LINE != ifs.seekg(-1, std::ios_base::end).get()) {
                        oss << NEW_LINE;
                    }

                    // Add the form feed to give some space for the next copy
                    oss << FORM_FEED;

                    print(oss.str(), request.numberOfCopies());

                    ifl.close();
                }
                else {
                    AIS_LOG_ERROR("Cannot open and lock print request file for reading.");
                }
                break;
            }
            case (SerialPrinterRequestInterfaceCommand::TEST): {
                std::ostringstream oss;
                oss << TEST_STRING << NEW_LINE << FORM_FEED;
                print(oss.str(), request.numberOfCopies());
                break;
            }
            default: {
                AIS_LOG_WARN("Unsupported command.");
                break;
            }
        }
    }

    return true;
}


/*
 * Print a string
 */
bool RemotePrinterApp::print(const std::string& str, uint8_t numberOfCopies) {

    AIS_LOG_NOTICE("Printing %d copies.", numberOfCopies);

    if (str.empty() || (numberOfCopies == 0)) {
        return true;
    }

    bool success = false;

    // Create the message
    Cat::Payload::PrinterReport printMessage;
    printMessage.set_number_of_copies(numberOfCopies);
    printMessage.set_raw_text(str);

    // Create file name
    std::string fileName;
    {
        std::stringstream ss;
        ss << static_cast<unsigned int>(FileTransferBridgeRequest::FileType::PRINT) << ".prt";
        fileName = ss.str();
    }

    // Create file path
    fs::path filePath = tempRoot_ / fileName;

    std::size_t bytesWritten = 0;

    { // Open the file and write it
        std::ofstream ofs(filePath.string(), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
        if (ofs) {
            if (printMessage.SerializeToOstream(&ofs)) {
                bytesWritten = ofs.tellp();
            }
            ofs.close();
        }
    }

    // Fill out the request to file transfer bridge
    if (bytesWritten > 0) {
        if (nullptr != fileTransferBridgeRequestOutput_) {
            FileTransferBridgeRequest request;
            request.fileAttr.Name = fileName;
            request.fileAttr.TelematicsFileNumber = static_cast<uint32_t>(FileTransferBridgeRequest::FileType::PRINT);
            request.fileAttr.DirPath = filePath.parent_path().string() + "/";
            request.fileAttr.SizeInBytes = bytesWritten;
            request.fileAttr.FidDestination = destinationFid_;

            if (fileTransferBridgeRequestOutput_->publish(request)) {
                AIS_LOG_NOTICE("Published print request to file transfer bridge.");
                success = true;
            }
            else {
                AIS_LOG_ERROR("Failed to publish print request to file transfer bridge.");
            }
        }
        else {
            AIS_LOG_ERROR("Cannot publish print request to file transfer bridge, no output interface.");
        }
    }
    else {
        AIS_LOG_ERROR("Failed to write to the file for the print request.");
    }

    return success;
}


/*
 * AIS Task Cleanup
 */
void RemotePrinterApp::cleanup() {
    AIS_LOG_INFO("RemotePrinterApp::cleanup");
}
