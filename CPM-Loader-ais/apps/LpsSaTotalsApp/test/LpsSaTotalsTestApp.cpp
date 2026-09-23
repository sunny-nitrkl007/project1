#include <sstream>
#include <future>
#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <algorithm>
#include <cctype>

#include <ais/task/Task.h>
#include <ais/log/Logger.h>

#include <chrono/print.hpp>
#include <fileio/iflocker.hpp>

#include <interfaces/LpsSaTotals/TotalsInterfaceInputChannel.h>
#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>

#include "LpsSaTotalsTestApp.h"


std::ostream& operator<<(std::ostream& os, const LpsSaTotalsInterfaceStorage& o) {
    os << "Totals (L: " << o.loadCount << ", P: " << o.passCount << ", W: " << o.weightTonnes << ") | ";
    os << "Trip A (L: " << o.trips[0].loadCount << ", P: " << o.trips[0].passCount << ", W: " << o.trips[0].weightTonnes << ") | ";
    os << "Trip B (L: " << o.trips[1].loadCount << ", P: " << o.trips[1].passCount << ", W: " << o.trips[1].weightTonnes << ")";
    return os;
}

/*
 * main() will call this function in order to get the task instance.
 */
task::AbstractTaskCore* task::getTaskImplementation(void) {
    static LpsSaTotalsTestApp thisTask("LpsSaTotalsTestApp");
    return dynamic_cast<Task*>(&thisTask);
}

/*
 * Constructor
 */
LpsSaTotalsTestApp::LpsSaTotalsTestApp(const std::string& taskName) :
    task::Task(taskName),
    number_(0),
    kbInputFuture_(),
    totalsChannelInput_(nullptr),
    requestChannelOutput_(nullptr),
    responseChannelInput_(nullptr),
    lpsSaLoadRecordChannelOutput_(nullptr) {
}

/*
 * Destructor
 */
LpsSaTotalsTestApp::~LpsSaTotalsTestApp() {
}

/*
 * AIS Task Initializer
 */
bool LpsSaTotalsTestApp::initialize() {
    bool everythingOk = true;
    AIS_LOG_INFO("LpsSaTotalsTestApp::initialize");

    // Initialize input and output channels
    totalsChannelInput_ = dynamic_cast<LpsSaTotalsInterfaceInputChannel*>(task::InterfaceDb::fetch("TotalsInput"));
    if (nullptr == totalsChannelInput_) {
        AIS_LOG_ERROR("No totals input channel defined.");
        everythingOk = false;
    }

    requestChannelOutput_ = dynamic_cast<LpsSaTotalsRequestInterfaceOutputChannel*>(task::InterfaceDb::fetch("RequestOutput"));
    if (nullptr == requestChannelOutput_) {
        AIS_LOG_ERROR("No request output channel defined.");
        everythingOk = false;
    }

    responseChannelInput_ = dynamic_cast<LpsSaTotalsResponseInterfaceInputChannel*>(task::InterfaceDb::fetch("ResponseInput"));
    if (nullptr == responseChannelInput_) {
        AIS_LOG_ERROR("No response input channel defined.");
        everythingOk = false;
    }

    lpsSaLoadRecordChannelOutput_ = dynamic_cast<LpsSaLoadRecordChannelOutputChannel*>(task::InterfaceDb::fetch("LoadRecordOutput"));
    if (nullptr == lpsSaLoadRecordChannelOutput_) {
        AIS_LOG_ERROR("No load record output channel defined.");
        everythingOk = false;
    }

    number_ = 0;

    return everythingOk;
}

/*
 * AIS Task Executive
 */
bool LpsSaTotalsTestApp::executive() {
    AIS_LOG_DEBUG("LpsSaTotalsTestApp::executive");

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
        if (command.rfind("CLR A", 0) == 0) {
            LpsSaTotalsRequestInterface request;
            request.command = LpsSaTotalsRequestInterfaceCommand::CLEAR_TRIP_TOTAL_A;
            requestChannelOutput_->publish(request);
        }

        else if (command.rfind("CLR B", 0) == 0) {
            LpsSaTotalsRequestInterface request;
            request.command = LpsSaTotalsRequestInterfaceCommand::CLEAR_TRIP_TOTAL_B;
            requestChannelOutput_->publish(request);
        }

        else if (command.rfind("CLR M", 0) == 0) {
            LpsSaTotalsRequestInterface request;
            request.command = LpsSaTotalsRequestInterfaceCommand::CLEAR_MATERIAL_TOTALS_ALL;
            requestChannelOutput_->publish(request);
        }

        else if (command.rfind("CLR L", 0) == 0) {
            // Clear last material
            LpsSaTotalsRequestInterface request;
            request.command = LpsSaTotalsRequestInterfaceCommand::CLEAR_MATERIAL_TOTAL;
            request.materialName("Material " + std::to_string(number_));
            requestChannelOutput_->publish(request);
        }

        else if (command.rfind("CLR T", 0) == 0) {
            // Clear truck report
            LpsSaTotalsRequestInterface request;
            request.command = LpsSaTotalsRequestInterfaceCommand::CLEAR_TRUCK_REPORT_ALL;
            requestChannelOutput_->publish(request);
        }

        else if (command.rfind("LOAD", 0) == 0) {
            number_++;
            auto now = std::chrono::system_clock::now();
            LpsSaLoadRecordChannel loadRecord;
            loadRecord.storeAction(LpsSaLoadRecordStoreAction::UI);
            auto& subtotal = loadRecord.getCurrentSubtotal();
            subtotal.truckId = number_;
            subtotal.truckName = "Truck " + std::to_string(number_);
            subtotal.truckTargetWeightTonnes = 20.0;
            subtotal.materialId = number_;
            subtotal.materialName = "Material " + std::to_string(number_);
            subtotal.materialDensity = 1780.0;
            subtotal.addPass(1.0, 3, 3);
            subtotal.addPass(2.0, 3, 4);
            subtotal.addPass(3.0, 3, 5);
/*            subtotal.addPass(4.0, 3, 5);
            subtotal.addPass(5.0, 3, 5);
            subtotal.addPass(6.0, 3, 5);
            subtotal.addPass(7.0, 3, 5);
            subtotal.addPass(8.0, 3, 5);
            subtotal.addPass(9.0, 3, 5);
            subtotal.addPass(10.0, 3, 5);
            subtotal.addPass(11.0, 3, 5);
            subtotal.addPass(12.0, 3, 5);
            subtotal.addPass(13.0, 3, 5);
            subtotal.addPass(14.0, 3, 5);
            subtotal.addPass(15.0, 3, 5);
            subtotal.addPass(16.0, 3, 5);
            subtotal.addPass(17.0, 3, 5);
            subtotal.addPass(18.0, 3, 5);
            subtotal.addPass(19.0, 3, 5);
            subtotal.addPass(20.0, 3, 5);
            subtotal.addPass(21.0, 3, 5);
            subtotal.addPass(22.0, 3, 5);
            subtotal.addPass(23.0, 3, 5);
            subtotal.addPass(24.0, 3, 5);
            subtotal.addPass(25.0, 3, 5);
            subtotal.addPass(26.0, 3, 5);
            subtotal.addPass(27.0, 3, 5);
            subtotal.addPass(28.0, 3, 5);*/
            subtotal.endTime.utcTime = now;
            subtotal.endTime.shmTime = 6;
            lpsSaLoadRecordChannelOutput_->publish(loadRecord);
        }

        else if (command.rfind("PUB M", 0) == 0) {
            LpsSaTotalsRequestInterface request;
            request.command = LpsSaTotalsRequestInterfaceCommand::PUBLISH_MATERIAL_TOTALS;
            requestChannelOutput_->publish(request);
        }

        else if (command.rfind("PRINT M", 0) == 0) {
            LpsSaTotalsRequestInterface request;
            request.command = LpsSaTotalsRequestInterfaceCommand::PRINT_MATERIAL_TOTALS_ALL;
            requestChannelOutput_->publish(request);
        }

        else if (command.rfind("PRINT T", 0) == 0) {
            LpsSaTotalsRequestInterface request;
            request.command = LpsSaTotalsRequestInterfaceCommand::PRINT_TRUCK_REPORT_ALL;
            requestChannelOutput_->publish(request);
        }

        else if (command.rfind("PRINT L", 0) == 0) {
            LpsSaTotalsRequestInterface request;
            request.command = LpsSaTotalsRequestInterfaceCommand::PRINT_TRUCK_TICKET;
            requestChannelOutput_->publish(request);
        }
    }

    { // Handle response
        LpsSaTotalsResponseInterface response;
        while (responseChannelInput_->get(response)) {
            if (response.success) {
                AIS_LOG_INFO("Command (%d) success.", response.command);

                if (LpsSaTotalsRequestInterfaceCommand::PUBLISH_MATERIAL_TOTALS == response.command) {
                    // Open the file and print it.
                    tes_common_ais::IFlocker ifl(response.filePath());
                    if (ifl) {
                        std::cout << ifl.ifstream().rdbuf() << std::endl;
                        ifl.close();
                        AIS_LOG_INFO("Publish material totals OK.");
                    }
                    else {
                        AIS_LOG_ERROR("Cannot open and lock material totals file for reading.");
                    }
                }
            }
            else {
                AIS_LOG_ERROR("Command (%d) failed.", response.command);
            }
        }
    }

    { // Print totals to the screen
        LpsSaTotalsInterface totals;
        while (totalsChannelInput_->get(totals)) {
            // Log
            std::stringstream ss;
            ss << totals;
            AIS_LOG_INFO(ss.str());
        }
    }

    return true;
}

/*
 * AIS Task Cleanup
 */
void LpsSaTotalsTestApp::cleanup() {
    AIS_LOG_INFO("LpsSaTotalsTestApp::cleanup");
}
