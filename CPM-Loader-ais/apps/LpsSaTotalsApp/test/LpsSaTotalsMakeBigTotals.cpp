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

#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>

#include "LpsSaTotalsMakeBigTotals.h"


/*
 * main() will call this function in order to get the task instance.
 */
task::AbstractTaskCore* task::getTaskImplementation(void) {
    static LpsSaTotalsMakeBigTotals thisTask("LpsSaTotalsMakeTotalsTest");
    return dynamic_cast<Task*>(&thisTask);
}

/*
 * Constructor
 */
LpsSaTotalsMakeBigTotals::LpsSaTotalsMakeBigTotals(const std::string& taskName) :
    task::Task(taskName),
    count_(0),
    lpsSaLoadRecordChannelOutput_(nullptr) {
}

/*
 * Destructor
 */
LpsSaTotalsMakeBigTotals::~LpsSaTotalsMakeBigTotals() {
}

/*
 * AIS Task Initializer
 */
bool LpsSaTotalsMakeBigTotals::initialize() {
    bool everythingOk = true;
    AIS_LOG_INFO("LpsSaTotalsMakeBigTotals::initialize");

    // Initialize input and output channels
    lpsSaLoadRecordChannelOutput_ = dynamic_cast<LpsSaLoadRecordChannelOutputChannel*>(task::InterfaceDb::fetch("LoadRecordOutput"));
    if (nullptr == lpsSaLoadRecordChannelOutput_) {
        AIS_LOG_ERROR("No load record output channel defined.");
        everythingOk = false;
    }

    count_ = 0;

    return everythingOk;
}

/*
 * AIS Task Executive
 */
bool LpsSaTotalsMakeBigTotals::executive() {
    AIS_LOG_DEBUG("LpsSaTotalsMakeBigTotals::executive");

    if (count_ < 5000) {
        ++count_;

        // Make new load record and publish
        auto now = std::chrono::system_clock::now();
        LpsSaLoadRecordChannel loadRecord;
        loadRecord.storeAction(LpsSaLoadRecordStoreAction::TICKET_NOT_FOR_TRADE);
        auto& subtotal = loadRecord.getCurrentSubtotal();
        subtotal.truckId = count_;
        subtotal.truckName = "This is a really big string to have for truck " + std::to_string(count_);
        subtotal.truckTargetWeightTonnes = 24.f;
        subtotal.materialId = count_;
        subtotal.materialName = "This is a really big string to have for material " + std::to_string(count_);
        subtotal.materialDensity = 1780.f;
        subtotal.tag1 = "This is a really big string to have for tag " + std::to_string(count_);
        subtotal.tag2 = "This is a really big string to have for tag " + std::to_string(count_);
        subtotal.tag3 = "This is a really big string to have for tag " + std::to_string(count_);
        subtotal.tag4 = "This is a really big string to have for tag " + std::to_string(count_);
        subtotal.addPass(8.f, 3, 0);
        subtotal.endTime = LpsSaLoadRecordTimeStamp(now, 0);

        if (lpsSaLoadRecordChannelOutput_->publish(loadRecord)) {
            AIS_LOG_NOTICE("Published load record # %d", count_);
        }
    }

    return true;
}

/*
 * AIS Task Cleanup
 */
void LpsSaTotalsMakeBigTotals::cleanup() {
    AIS_LOG_INFO("LpsSaTotalsMakeBigTotals::cleanup");
}
