#include <sstream>
#include <future>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <chrono>

#include <ais/task/Task.h>
#include <ais/log/AisLogger.h>

#include <fileio/oflocker.hpp>

#include <interfaces/SerialPrinter/RequestInterfaceOutputChannel.h>

#include "SerialPrinterTestApp.h"

namespace fs = boost::filesystem;

#define DEFAULT_TEMP_ROOT (R"(/tmp/SerialPrinterTestApp/temp)")

constexpr auto STRING1 = R"(Print 1
Line 1
Line 2
Line 3
Line 4
Line 5
Line 6
Line 7)";

constexpr auto STRING2 = R"(Print 2
Line 8
Line 9

Line 10
Line 11
Line 12
Line 13
Last Line)";

constexpr auto STRING3 = R"(  @@@@@@@         @@@    @@@@@@@@@@@@
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

constexpr auto STRING4 = R"(Print 4)";

constexpr auto STRING5 = "r,\rn,\nrn,\r\nnoner,\rn,\nrn,\r\nnone";

constexpr auto STRING6 = R"(20----------------20
21-----------------21
22------------------22
23-------------------23
24--------------------24
25---------------------25
26----------------------26
27-----------------------27
28------------------------28
29-------------------------29
30--------------------------30
31---------------------------31
32----------------------------32
33-----------------------------33
34------------------------------34
35-------------------------------35
36--------------------------------36
37---------------------------------37
38----------------------------------38
39-----------------------------------39
40------------------------------------40)";

/*
 * main() will call this function in order to get the task instance.
 */
task::AbstractTaskCore* task::getTaskImplementation(void) {
    static SerialPrinterTestApp thisTask("SerialPrinterTestApp");
    return dynamic_cast<Task*>(&thisTask);
}

/*
 * Constructor
 */
SerialPrinterTestApp::SerialPrinterTestApp(const std::string& taskName) :
    task::Task(taskName),
    kbInputFuture_(),
    tempRoot_(DEFAULT_TEMP_ROOT),
    requestChannelOutput_(nullptr) {
}

/*
 * Destructor
 */
SerialPrinterTestApp::~SerialPrinterTestApp() {
}

/*
 * AIS Task Initializer
 */
bool SerialPrinterTestApp::initialize() {
    bool everythingOk = true;
    AIS_LOG_INFO("SerialPrinterTestApp::initialize");

    { // Get the configs and print it out.
        ConfigSection& configs = getTaskConfig();

        std::string tempRoot;
        if (configs.get("tempRoot", tempRoot)) {
            tempRoot_ = tempRoot;
        }
        else {
            tempRoot_ = DEFAULT_TEMP_ROOT;
        }

        AIS_LOG_INFO("Temp Root: %s", tempRoot_.c_str());
    }

    requestChannelOutput_ = dynamic_cast<SerialPrinterRequestInterfaceOutputChannel*>(task::InterfaceDb::fetch("RequestOutput"));
    if (nullptr == requestChannelOutput_) {
        AIS_LOG_ERROR("No request output channel defined.");
        everythingOk = false;
    }

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
bool SerialPrinterTestApp::executive() {
    AIS_LOG_DEBUG("SerialPrinterTestApp::executive");

    /*
     * Get a command from keyboard input
     */
    std::string command("");
    if (kbInputFuture_.valid()) {
        // It is valid, poll it
        if (kbInputFuture_.wait_for(std::chrono::microseconds(1)) == std::future_status::ready) {
            command = kbInputFuture_.get();
            AIS_LOG_INFO(R"(Command received "%s")", command.c_str());
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

    if (!command.empty()) {
        std::string printString = "";
        uint8_t numberOfCopies = 1;

        if (command.rfind("P1", 0) == 0) {
            printString = STRING1;
        }

        else if (command.rfind("P2", 0) == 0) {
            printString = STRING2;
        }

        else if (command.rfind("P3", 0) == 0) {
            printString = STRING3;
        }

        else if (command.rfind("P4", 0) == 0) {
            printString = STRING4;
            numberOfCopies = 3;
        }

        else if (command.rfind("P5", 0) == 0) {
            printString = STRING5;
        }

        else if (command.rfind("P6", 0) == 0) {
            printString = STRING6;
        }

        /*
         * Print the requested string.
         */
        if (!printString.empty()) {
            SerialPrinterRequestInterface request;
            request.command = SerialPrinterRequestInterfaceCommand::PRINT;
            request.filePath((tempRoot_ / "print.txt").string());
            request.numberOfCopies(numberOfCopies);
            tes_common_ais::OFlocker ofl(request.filePath());
            if (ofl) {
                ofl.ofstream() << printString;
                ofl.close();
                requestChannelOutput_->publish(request);
                AIS_LOG_INFO("Requested print.");
            }
            else {
                AIS_LOG_ERROR("File could not be opened and locked for writing.");
            }
        }
    }

    return true;
}

/*
 * AIS Task Cleanup
 */
void SerialPrinterTestApp::cleanup() {
    AIS_LOG_INFO("SerialPrinterTestApp::cleanup");
}
