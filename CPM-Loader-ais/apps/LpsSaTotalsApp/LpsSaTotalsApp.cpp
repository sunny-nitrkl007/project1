#include <sstream>
#include <string>
#include <ctime>

#include <boost/filesystem.hpp>

#include <ais/task/Task.h>
#include <ais/log/Logger.h>

#include <chrono/print.hpp>
#include <chrono/tz.hpp>
#include <fileio/directory.hpp>
#include <fileio/oflocker.hpp>
#include <lps_sea_defs.h>
#include <scl_prmsw.h>

#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>
#include <interfaces/LpsSaTotals/RequestInterface.hpp>
#include <interfaces/LpsSaTotals/ResponseInterface.hpp>
#include <interfaces/LpsSaTotals/TotalsInterface.hpp>
#include <interfaces/SerialPrinter/RequestInterface.hpp>
#include <interfaces/LpsSaTotals/PrinterCnfgInterface.hpp>
#include <interfaces/LpsSaUI/DisplayStateInterface.hpp>
#include <interfaces/ShmClock/ShmClock.h>
#include <interfaces/CreateFileRequest/CreateFileRequest.h>
#include <interfaces/LpsSaListMgr/TxInterface.hpp>

#include <autonomyConditions/conditions/PayloadMemoryLow.h>
#include <autonomyConditions/conditions/PayloadMemoryFull.h>

#include "LpsSaTotalsApp.h"
#include "LpsSaTotalsVP3LoadBuilder.h"
#include "LpsSaTotalsLastStoredTruckMessage.h"
#include "LpsSaTotalsCPMTicket.h"

namespace fs = boost::filesystem;

#define PRINTER_CNFG_PUBLISH_PERIOD_SEC (10.0f)

#define TOTALS_FILENAME_STEM(PREFIX) (std::string(PREFIX).append("Totals"))
#define TOTALS_TODAY_FILENAME_STEM(PREFIX) (std::string(PREFIX).append("TotalsToday"))
#define TOTALS_PREVIOUS_DAY_FILENAME_STEM(PREFIX) (std::string(PREFIX).append("TotalsPreviousDay"))

#define FILENAME_BIN(STEM) (std::string(STEM).append(".bin"))
#define FILENAME_JSON(STEM) (std::string(STEM).append(".json"))
#define FILENAME_TXT(STEM) (std::string(STEM).append(".txt"))

#define TOTALS_FILENAME_BIN(PREFIX) FILENAME_BIN(TOTALS_FILENAME_STEM(PREFIX))
#define TOTALS_FILENAME_JSON(PREFIX) FILENAME_JSON(TOTALS_FILENAME_STEM(PREFIX))
#define TOTALS_FILENAME_TXT(PREFIX) FILENAME_TXT(TOTALS_FILENAME_STEM(PREFIX))

#define TOTALS_TODAY_FILENAME_BIN(PREFIX) FILENAME_BIN(TOTALS_TODAY_FILENAME_STEM(PREFIX))
#define TOTALS_TODAY_FILENAME_JSON(PREFIX) FILENAME_JSON(TOTALS_TODAY_FILENAME_STEM(PREFIX))
#define TOTALS_TODAY_FILENAME_TXT(PREFIX) FILENAME_TXT(TOTALS_TODAY_FILENAME_STEM(PREFIX))

#define TOTALS_PREVIOUS_DAY_FILENAME_BIN(PREFIX) FILENAME_BIN(TOTALS_PREVIOUS_DAY_FILENAME_STEM(PREFIX))
#define TOTALS_PREVIOUS_DAY_FILENAME_JSON(PREFIX) FILENAME_JSON(TOTALS_PREVIOUS_DAY_FILENAME_STEM(PREFIX))
#define TOTALS_PREVIOUS_DAY_FILENAME_TXT(PREFIX) FILENAME_TXT(TOTALS_PREVIOUS_DAY_FILENAME_STEM(PREFIX))

#define TICKET_HISTORY_FILENAME_JSON (R"(TicketHistory.json)")
#define TICKET_DETAILS_FILENAME_JSON (R"(TicketDetails.json)")

#define LOAD_HISTORY_FILENAME_BIN (R"(LoadHistory.bin)")
#define LOAD_HISTORY_FILENAME_TXT (R"(LoadHistory.txt)")
#define LOAD_HISTORY_TODAY_FILENAME_BIN (R"(LoadHistoryToday.bin)")
#define LOAD_HISTORY_TODAY_FILENAME_TXT (R"(LoadHistoryToday.txt)")
#define LOAD_HISTORY_PREVIOUS_DAY_FILENAME_BIN (R"(LoadHistoryPreviousDay.bin)")
#define LOAD_HISTORY_PREVIOUS_DAY_FILENAME_TXT (R"(LoadHistoryPreviousDay.txt)")

#define PRINTER_INFO_FILENAME_BIN (R"(PrinterInfo.bin)")

#define TRUCK_TICKET_FILENAME_TXT (R"(TruckTicket.txt)")
#define LAST_STORED_TRUCK_FILENAME_JSON (R"(LastStoredTruckInfo.json)")

#define ADDITIONAL_TRUCK_TICKET_FILENAME_TXT (R"(AdditionalTruckTicket.txt)")

#define LAST_LOAD_FILENAME_BIN (R"(LastLoad.bin)")

#define DEFAULT_STORAGE_ROOT (R"(/tmp/LpsSaTotalsApp/storage)")
#define DEFAULT_TEMP_ROOT (R"(/tmp/LpsSaTotalsApp/temp)")
#define DEFAULT_FILE_TRANSFER_TX_DIR (R"(/opt/appdata/CPM/FileTransferBridgeApp/TxFiles)")

#define HISTORY_SUBDIR (R"(history)")

/*
 * main() will call this function in order to get the task instance.
 */
task::AbstractTaskCore* task::getTaskImplementation(void) {
    static LpsSaTotalsApp thisTask("LpsSaTotalsApp");
    return dynamic_cast<Task*>(&thisTask);
}

/*
 * Constructor
 */
LpsSaTotalsApp::LpsSaTotalsApp(const std::string& taskName) :
    task::Task(taskName),
    initNeeded_(true),
    printerCnfgUpdateCount_(0),
    tzInfo_{0, -1},
    serviceHourMeter_(0),
    storageRoot_(DEFAULT_STORAGE_ROOT),
    tempRoot_(DEFAULT_TEMP_ROOT),
    fileTransferTxDir_(DEFAULT_FILE_TRANSFER_TX_DIR),
    lpsSaLoadRecordChannelInput_(nullptr),
    requestChannelInput_(nullptr),
    responseChannelOutput_(nullptr),
    totalsChannelOutput_(nullptr),
    printerRequestChannelOutput_(nullptr),
    writePrinterCnfgInput_(nullptr),
    printerCnfgOutput_(nullptr),
    displayStateInput_(nullptr),
    shmClockInput_(nullptr),
    vp3CreateRecordInterface_(nullptr),
    dataLinkDataInput_(nullptr),
    partNumbersInput_(nullptr),
    fileTransferBridgeRequestOutput_(nullptr),
    lpsSaListMgrInput_(nullptr),
    autonomyConditionDiagnosticsTxInputChannel_(nullptr),
    USBSaveProgressOutput_(nullptr),
    weighAppRequestOutput_(nullptr),
    historyManager_(fs::path(DEFAULT_STORAGE_ROOT) / HISTORY_SUBDIR),
    lifetimeTotals_(),
    materialTotals_(), materialTotalsToday_("Material"),
    loadHistory_(), loadHistoryToday_(),
    printerInfo_(),
    lastLoad_(),
    telemetry_(),
    truckTotals_("Truck"), truckTotalsToday_("Truck"),
    tag1Totals_("Tag1"), tag1TotalsToday_("Tag1"),
    tag2Totals_("Tag2"), tag2TotalsToday_("Tag2"),
    tag3Totals_("Tag3"), tag3TotalsToday_("Tag3"),
    tag4Totals_("Tag4"), tag4TotalsToday_("Tag4"),
    operatorId_(),
    productId(),
    equipmentId(),
    SEALevel2Installed(false)
#ifdef GRPC_SUPPORTED
    ,cdaUSBWriter_(historyManager_)
#endif
{
}

/*
 * Destructor
 */
LpsSaTotalsApp::~LpsSaTotalsApp() {
}

/*
 * AIS Task Initializer
 */
bool LpsSaTotalsApp::initialize() {
    bool everythingOk = true;
    AIS_LOG_INFO("LpsSaTotalsApp::initialize");

#ifdef GRPC_SUPPORTED
    std::string cda_server_ip_addr = "";
    std::string cda_server_port = "";
#endif

    { // Get the configs and print it out.
        ConfigSection& configs = getTaskConfig();

        std::string configStr;
        if (configs.get("storageRoot", configStr)) {
            storageRoot_ = configStr;
        }

        if (configs.get("tempRoot", configStr)) {
            tempRoot_ = configStr;
        }

        if (configs.get("fileTransferTxDir", configStr)) {
            fileTransferTxDir_ = configStr;
        }

#ifdef GRPC_SUPPORTED
        if (!configs.get("cdaServerIpAddress", cda_server_ip_addr)) {
            AIS_LOG_ERROR("cdaServerIpAddress not found in config");
            everythingOk = false;
        }

        if (!configs.get("cdaServerPort", cda_server_port)) {
            AIS_LOG_ERROR("cdaServerPort not found in config");
            everythingOk = false;
        }
#endif

        AIS_LOG_INFO("Storage Root: %s", storageRoot_.c_str());
        AIS_LOG_INFO("Temp Root: %s", tempRoot_.c_str());
        AIS_LOG_INFO("File Tx Root: %s", fileTransferTxDir_.c_str());
#ifdef GRPC_SUPPORTED
        AIS_LOG_INFO("cdaServerIpAddress: %s", cda_server_ip_addr.c_str());
        AIS_LOG_INFO("cdaServerPort: %s", cda_server_port.c_str());
#endif
    }

    // Initialize input and output channels
    lpsSaLoadRecordChannelInput_ = dynamic_cast<LpsSaLoadRecordChannelInputChannel*>(task::InterfaceDb::fetch("LoadRecordInput"));
    if (nullptr == lpsSaLoadRecordChannelInput_) {
        AIS_LOG_ERROR("No load record input channel defined.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("ListTxInput", lpsSaListMgrInput_)) {
        AIS_LOG_ERROR("No list tx input channel defined.");
        everythingOk = false;
    }

    autonomyConditionDiagnosticsTxInputChannel_ = dynamic_cast<AutonomyConditionDiagnosticsTxInterfaceInputChannel*>(task::InterfaceDb::fetch("AutonomyConditionDiagnosticsTxChannelInput"));
    if (nullptr == autonomyConditionDiagnosticsTxInputChannel_) {
        AIS_LOG_ERROR("autonomyConditionDiagnosticsTxInputChannel_ Interface not configured.");
        everythingOk = false;
    }

    USBSaveProgressOutput_ = dynamic_cast<LpsSaTotalsUSBSaveProgressInterfaceOutputChannel*>(task::InterfaceDb::fetch("LpsSaTotalsUSBSaveProgressOutput"));
    if (nullptr == USBSaveProgressOutput_) {
        AIS_LOG_ERROR("USBSaveProgressOutput_ Interface not configured.");
        everythingOk = false;
    }

    requestChannelInput_ = dynamic_cast<LpsSaTotalsRequestInterfaceInputChannel*>(task::InterfaceDb::fetch("RequestInput"));
    if (nullptr == requestChannelInput_) {
        AIS_LOG_ERROR("No request input channel defined.");
        everythingOk = false;
    }

    responseChannelOutput_ = dynamic_cast<LpsSaTotalsResponseInterfaceOutputChannel*>(task::InterfaceDb::fetch("ResponseOutput"));
    if (nullptr == responseChannelOutput_) {
        AIS_LOG_ERROR("No response output channel defined.");
        everythingOk = false;
    }

    totalsChannelOutput_ = dynamic_cast<LpsSaTotalsInterfaceOutputChannel*>(task::InterfaceDb::fetch("TotalsOutput"));
    if (nullptr == totalsChannelOutput_) {
        AIS_LOG_ERROR("No totals output channel defined.");
        everythingOk = false;
    }

    printerRequestChannelOutput_ = dynamic_cast<SerialPrinterRequestInterfaceOutputChannel*>(task::InterfaceDb::fetch("PrinterRequestOutput"));
    if (nullptr == printerRequestChannelOutput_) {
        AIS_LOG_WARN("No printer request output channel defined.");
    }

    writePrinterCnfgInput_ = dynamic_cast<LpsSaTotalsPrinterCnfgInterfaceInputChannel*>(task::InterfaceDb::fetch("WritePrinterCnfgInput"));
    if (nullptr == writePrinterCnfgInput_) {
        AIS_LOG_WARN("No write printer configuration input channel defined.");
    }

    printerCnfgOutput_ = dynamic_cast<LpsSaTotalsPrinterCnfgInterfaceOutputChannel*>(task::InterfaceDb::fetch("PrinterCnfgOutput"));
    if (nullptr == printerCnfgOutput_) {
        AIS_LOG_WARN("No printer configuration output channel defined.");
    }

    displayStateInput_ = dynamic_cast<LpsSaUIDisplayStateInterfaceInputChannel*>(task::InterfaceDb::fetch("DisplayStateInput"));
    if (nullptr == displayStateInput_) {
        AIS_LOG_WARN("No display state input channel defined.");
    }

    shmClockInput_ = dynamic_cast<ShmClockInput*>(task::InterfaceDb::fetch("ShmClockInput"));
    if (nullptr == shmClockInput_) {
        AIS_LOG_WARN("No SHM Clock input channel defined.");
    }

    vp3CreateRecordInterface_ = dynamic_cast<VP3RecordOutputChannel*>(task::InterfaceDb::fetch("VP3CreateRecordOutput"));
    if (nullptr == vp3CreateRecordInterface_) {
        AIS_LOG_WARN("No VP3 Record output channel defined.");
    }

    dataLinkDataInput_ = dynamic_cast<DataLinkDataInput*>(task::InterfaceDb::fetch("DataLinkDataInput"));
    if (nullptr == dataLinkDataInput_) {
        AIS_LOG_ERROR("No Data Link Data input channel defined.");
        everythingOk = false;
    }

    partNumbersInput_ = dynamic_cast<PartNumbersInput*>(task::InterfaceDb::fetch("PartNumbersInput"));
    if (nullptr == partNumbersInput_) {
        AIS_LOG_ERROR("No Part Numbers input channel defined.");
        everythingOk = false;
    }

    fileTransferBridgeRequestOutput_ = dynamic_cast<FileTransferBridgeRequestOutput*>(task::InterfaceDb::fetch("FileTransferBridgeRequestOutput"));
    if (nullptr == fileTransferBridgeRequestOutput_) {
        AIS_LOG_ERROR("No File Transfer Bridge Request output channel defined.");
        everythingOk = false;
    }

    if (!task::InterfaceDb::bind("LpsSaWeighReqstOutput", weighAppRequestOutput_)) {
        AIS_LOG_ERROR("LpsSaWeighReqstChannelOutput Interface not configured.");
        everythingOk = false;
    }

    // Load stuff from storage
    try {
        tes_common_ais::directory::create(storageRoot_);
        tes_common_ais::directory::create(tempRoot_);
        tes_common_ais::directory::create(fileTransferTxDir_);

        { // Make the history directory
            const auto historyStoragePath = storageRoot_ / HISTORY_SUBDIR;
            tes_common_ais::directory::create(historyStoragePath);
            historyManager_.setStoragePath(historyStoragePath);
        }

        if (!lifetimeTotals_.load(makeStoragePath(TOTALS_FILENAME_BIN("Lifetime")))) {
            lifetimeTotals_.reset();
        }

        if (!materialTotals_.load(makeStoragePath(TOTALS_FILENAME_BIN("Material")))) {
            materialTotals_.reset();
        }

        if (!materialTotalsToday_.load(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Material")))) {
            materialTotalsToday_.reset();
        }

        if (!truckTotals_.load(makeStoragePath(TOTALS_FILENAME_BIN("Truck")))) {
            truckTotals_.reset();
        }

        if (!truckTotalsToday_.load(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Truck")))) {
            truckTotalsToday_.reset();
        }

        if (!tag1Totals_.load(makeStoragePath(TOTALS_FILENAME_BIN("Tag1")))) {
            tag1Totals_.reset();
        }

        if (!tag1TotalsToday_.load(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Tag1")))) {
            tag1TotalsToday_.reset();
        }

        if (!tag2Totals_.load(makeStoragePath(TOTALS_FILENAME_BIN("Tag2")))) {
            tag2Totals_.reset();
        }

        if (!tag2TotalsToday_.load(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Tag2")))) {
            tag2TotalsToday_.reset();
        }

        if (!tag3Totals_.load(makeStoragePath(TOTALS_FILENAME_BIN("Tag3")))) {
            tag3Totals_.reset();
        }

        if (!tag3TotalsToday_.load(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Tag3")))) {
            tag3TotalsToday_.reset();
        }

        if (!tag4Totals_.load(makeStoragePath(TOTALS_FILENAME_BIN("Tag4")))) {
            tag4Totals_.reset();
        }

        if (!tag4TotalsToday_.load(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Tag4")))) {
            tag4TotalsToday_.reset();
        }

        if (!loadHistory_.load(makeStoragePath(LOAD_HISTORY_FILENAME_BIN))) {
            loadHistory_.reset();
        }

        if (!loadHistoryToday_.load(makeStoragePath(LOAD_HISTORY_TODAY_FILENAME_BIN))) {
            loadHistoryToday_.reset();
        }

        if (!printerInfo_.load(makeStoragePath(PRINTER_INFO_FILENAME_BIN))) {
            printerInfo_.reset();
        }

        if (!lastLoad_.load(makeStoragePath(LAST_LOAD_FILENAME_BIN))) {
            lastLoad_.reset();
        }
    }
    catch (const fs::filesystem_error& e) {
        AIS_LOG_ERROR(e.what());
        everythingOk = false;
    }

    initNeeded_ = true;
    printerCnfgUpdateCount_ = 0;
    tzInfo_.offset = 0;
    tzInfo_.index = -1;
    serviceHourMeter_ = 0;

#ifdef GRPC_SUPPORTED
    // Connect to CDA-USB server
    cdaUSBWriter_.initCDAUSBWriter(cda_server_ip_addr, cda_server_port);
#endif

    // Set the retention period
    historyManager_.setRetentionPeriod(printerInfo_.config.truckTicket.retentionPeriod);

    // Update the memory low/full events
    updateMemoryEvents();

    return everythingOk;
}

/*
 * AIS Task Executive
 */
bool LpsSaTotalsApp::executive() {
    AIS_LOG_DEBUG("LpsSaTotalsApp::executive");

    bool saveLastLoad = false;
    bool saveLifetimeTotals = false;
    bool saveMaterialTotals = false;
    bool saveTruckTotals = false;
    bool saveTag1Totals = false;
    bool saveTag2Totals = false;
    bool saveTag3Totals = false;
    bool saveTag4Totals = false;
    bool saveLoadHistory = false;
    bool savePrinterInfo = false;
    bool publishPrinterInfo = false;
    bool operatorIdChanged = false;

    if (initNeeded_) {
        publishPrinterInfo = true; // Publish the printer config once on startup.
        initNeeded_ = false;
    }

    /* Receive local time offset and override the local time offset in chrono/print.hpp */
    if (nullptr != shmClockInput_) {
        ShmClock shmClock;
        while (shmClockInput_->get(shmClock)) {
            int32_t offset = shmClock.get_UTC_offset();
            tzone_tx_comm_struct tzone;
            if (tes_common_ais::get_tz_struct(tzone, shmClock)) {
                if ((tzInfo_.offset != offset) || (tzInfo_.index != tzone.tzone_id)) {
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
            }
            else {
                AIS_LOG_ERROR("Could not get tzone_tx_comm_struct");
            }

            serviceHourMeter_ = shmClock.get_SHM();
        }
    }

    // Parse Datalink input channel
    if (nullptr != dataLinkDataInput_) {
        DataLinkData dataLinkData;
        while (dataLinkDataInput_->get(dataLinkData)) {
            // Update operator id with new datalink data
            if (operatorId_.updateWithDataLinkData(dataLinkData)) {
                AIS_LOG_INFO("Operator Id changed to '%s'", operatorId_.getDescription().c_str());
                operatorIdChanged = true;
            }

            // Update telemetry with new datalink data
            telemetry_.updateDataLinkData(dataLinkData);
        }
    }

    // Determine SEA Level 2 Status
    if (nullptr != autonomyConditionDiagnosticsTxInputChannel_) {
        AutonomyConditionDiagnosticsTxInterface txData;
        while (autonomyConditionDiagnosticsTxInputChannel_->get(txData)) {
            for (const auto & element : txData.seaList){
                if (element.reason_code == LPS_SEA_REASON_CODE_245) {
                    SEALevel2Installed = txData.checkSEAEnableStatus(element.status);
                }
                else if (element.reason_code == LPS_SEA_LFT_REASON_CODE_312) {
                    bool SEALegalForTradeInstalled = txData.checkSEAEnableStatus(element.status);
                    if (SEALegalForTradeInstalled != printerInfo_.legalForTradeInstalled) {
                        printerInfo_.legalForTradeInstalled = SEALegalForTradeInstalled;
                        savePrinterInfo = true;
                    }
                }
            }
        }
    }

    // Store Product ID
    if (nullptr != partNumbersInput_) {
        PartNumbers partNumbers;
        while (partNumbersInput_->get(partNumbers)) {
            if (partNumbers.IsProductIdValid()) {
                productId = partNumbers.GetProductIdNum();
                equipmentId = partNumbers.GetEquipmentId();
#ifdef GRPC_SUPPORTED
                cdaUSBWriter_.setProductId(productId);
#endif
            }
        }
    }

    // Get printer config settings if available
    if (nullptr != writePrinterCnfgInput_) {
        LpsSaTotalsPrinterCnfgInterface printerCnfg;
        while (writePrinterCnfgInput_->get(printerCnfg)) {

            // If ticket number is being written, we need to notify the weigh app to break the LFT seal.
            // Since the ticket number is used to make ticket identifier unique, it is a legally relevant parameter.
            if (printerInfo_.config.truckTicket.ticketNumber != printerCnfg.config.truckTicket.ticketNumber) {
                if (nullptr != weighAppRequestOutput_) {
                    LpsSaWeighReqstChannel request;
                    request.appName = getTaskName();
                    request.command = LpsSaWeighReqstChannel::Command::NOTIFY_TICKET_NUMBER_WRITE;
                    request.arg.u = printerCnfg.config.truckTicket.ticketNumber;
                    if (!weighAppRequestOutput_->publish(request)) {
                        AIS_LOG_ERROR("Failed to publish weigh app request.");
                    }
                }
            }

            if (printerInfo_.config.truckTicket.retentionPeriod != printerCnfg.config.truckTicket.retentionPeriod) {
                historyManager_.setRetentionPeriod(printerCnfg.config.truckTicket.retentionPeriod);
            }

            printerInfo_.config = printerCnfg.config;
            if (!printerInfo_.config.installed) {
                AIS_LOG_ALERT("Printer configuration written, not installed.");
            }
            savePrinterInfo = true;
        }
    }

    // Make sure we are printing in the units that are defined by the display settings
    if (nullptr != displayStateInput_) {
        LpsSaUIDisplayStateInterface displayState;
        while (displayStateInput_->get(displayState)) {
            // Update the printer configuration if the display setting have changed.
            if ((displayState.state.getSettings().weightUnits != printerInfo_.weightUnits) ||
                    (displayState.state.getWeightDecimalPrecision() != printerInfo_.weightDecimalPrecision) ||
                    (displayState.state.getWeightInterval() != printerInfo_.weightInterval)) {
                printerInfo_.weightUnits = displayState.state.getSettings().weightUnits;
                printerInfo_.weightDecimalPrecision = displayState.state.getWeightDecimalPrecision();
                printerInfo_.weightInterval = displayState.state.getWeightInterval();
                savePrinterInfo = true;
            }
        }
    }

    if (lpsSaListMgrInput_ != nullptr) {
        LpsSaListMgrTxInterface listNames;
        while (lpsSaListMgrInput_->get(listNames)) {
            tag1Totals_.printHeader = listNames.customList1Name;
            tag1TotalsToday_.printHeader = listNames.customList1Name;

            tag2Totals_.printHeader = listNames.customList2Name;
            tag2TotalsToday_.printHeader = listNames.customList2Name;

            tag3Totals_.printHeader = listNames.customList3Name;
            tag3TotalsToday_.printHeader = listNames.customList3Name;

            tag4Totals_.printHeader = listNames.customList4Name;
            tag4TotalsToday_.printHeader = listNames.customList4Name;
        }
    }

    { // Process load record (one per executive loop)
        LpsSaLoadRecordChannel loadRecord;
        if (lpsSaLoadRecordChannelInput_->get(loadRecord)) {
            uint32_t numPasses = loadRecord.passCount();
            float weightTonnes = loadRecord.weightTonnes();
            uint32_t numLoads;
            auto subtotalCount = loadRecord.subtotalCount();

            if (LpsSaLoadRecordStoreAction::AUTO != loadRecord.storeAction()) {
                // Non-Auto Store results in a load count increment.
                // Basically this is a count of the number of times the operator
                // manually stored a load.
                numLoads = 1;

                // Ticket number is used for printed tickets.
                loadRecord.ticketNumber(printerInfo_.config.truckTicket.ticketNumber);
            }
            else {
                // Auto Store does not result in load count increment.
                numLoads = 0;

                // Ticket number is not used for auto-store
                loadRecord.ticketNumber(0xFFFF);
            }

            // Set some additional load record information captured at the time we receive it.
            loadRecord.productId(productId);
            loadRecord.equipmentId(equipmentId);
            loadRecord.weightInterval(printerInfo_.weightInterval);
            loadRecord.weightDecimalPrecision(printerInfo_.weightDecimalPrecision);
            loadRecord.weightUnits(printerInfo_.weightUnits);

            // Add the load record to load record history
            historyManager_.addLoad(loadRecord);

            // Update the memory low/full events
            updateMemoryEvents();

            lifetimeTotals_.update(numLoads, numPasses, weightTonnes);
            saveLifetimeTotals = true;

            // We do increment loads for material totals, even on auto-store.
            for (uint32_t x=1; x<=subtotalCount; x++) {
                const auto& subtotal = loadRecord.getSubtotalByIndex(x);

                const auto subtotalStartOfDay = tes_common_ais::getUTCStartOfLocalDay(subtotal.endTime.utcTime);

                materialTotals_.update(subtotal.materialName, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                if (materialTotalsToday_.resetTime < subtotalStartOfDay) {
                    // No reset yet today.
                    materialTotalsToday_.save(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN("Material")));
                    materialTotalsToday_.reset();
                }
                materialTotalsToday_.update(subtotal.materialName, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                saveMaterialTotals = true;

                truckTotals_.update(subtotal.truckName, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                if (truckTotalsToday_.resetTime < subtotalStartOfDay) {
                    // No reset yet today.
                    truckTotalsToday_.save(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN("Truck")));
                    truckTotalsToday_.reset();
                }
                truckTotalsToday_.update(subtotal.truckName, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                saveTruckTotals = true;

                tag1Totals_.update(subtotal.tag1, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                if (tag1TotalsToday_.resetTime < subtotalStartOfDay) {
                    // No reset yet today.
                    tag1TotalsToday_.save(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN("Tag1")));
                    tag1TotalsToday_.reset();
                }
                tag1TotalsToday_.update(subtotal.tag1, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                saveTag1Totals = true;

                tag2Totals_.update(subtotal.tag2, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                if (tag2TotalsToday_.resetTime < subtotalStartOfDay) {
                    // No reset yet today.
                    tag2TotalsToday_.save(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN("Tag2")));
                    tag2TotalsToday_.reset();
                }
                tag2TotalsToday_.update(subtotal.tag2, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                saveTag2Totals = true;

                tag3Totals_.update(subtotal.tag3, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                if (tag3TotalsToday_.resetTime < subtotalStartOfDay) {
                    // No reset yet today.
                    tag3TotalsToday_.save(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN("Tag3")));
                    tag3TotalsToday_.reset();
                }
                tag3TotalsToday_.update(subtotal.tag3, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                saveTag3Totals = true;

                tag4Totals_.update(subtotal.tag4, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                if (tag4TotalsToday_.resetTime < subtotalStartOfDay) {
                    // No reset yet today.
                    tag4TotalsToday_.save(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN("Tag4")));
                    tag4TotalsToday_.reset();
                }
                tag4TotalsToday_.update(subtotal.tag4, numLoads, subtotal.passCount(), subtotal.weightTonnes());
                saveTag4Totals = true;

                loadHistory_.addLoad(LpsSaTotalsLoadHistoryStorage::Load(
                        subtotal.endTime.utcTime,
                        subtotal.truckId,
                        subtotal.materialId,
                        subtotal.truckName,
                        subtotal.materialName,
                        subtotal.passCount(),
                        subtotal.weightTonnes(),
                        subtotal.tag1,
                        subtotal.tag2,
                        subtotal.tag3,
                        subtotal.tag4));

                if (loadHistoryToday_.resetTime < subtotalStartOfDay) {
                    loadHistoryToday_.save(makeStoragePath(LOAD_HISTORY_PREVIOUS_DAY_FILENAME_BIN));
                    loadHistoryToday_.reset();
                }

                loadHistoryToday_.addLoad(LpsSaTotalsLoadHistoryStorage::Load(
                        subtotal.endTime.utcTime,
                        subtotal.truckId,
                        subtotal.materialId,
                        subtotal.truckName,
                        subtotal.materialName,
                        subtotal.passCount(),
                        subtotal.weightTonnes(),
                        subtotal.tag1,
                        subtotal.tag2,
                        subtotal.tag3,
                        subtotal.tag4));
                saveLoadHistory = true;
            }

            // Auto Store does not result in auto printing.
            if (LpsSaLoadRecordStoreAction::AUTO != loadRecord.storeAction()) {
                // Set the last load record for ticket printing.
                lastLoad_.set(loadRecord);
                saveLastLoad = true;

                // Print the truck ticket if needed
                if (lastLoad_.isSet &&
                        printerInfo_.config.installed &&
                        (printerInfo_.config.truckTicket.numCopies > 0) &&
                        (nullptr != printerRequestChannelOutput_)) {
                    std::string filePath(makeTempPath(TRUCK_TICKET_FILENAME_TXT));
                    if (lastLoad_.print(filePath, printerInfo_)) {
                        // Build a print request to the printer app
                        SerialPrinterRequestInterface printRequest;
                        printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                        printRequest.filePath(filePath);
                        printRequest.numberOfCopies(printerInfo_.config.truckTicket.numCopies);
                        if (printerRequestChannelOutput_->publish(printRequest)) {
                            ++printerInfo_.totals.numTruckTickets;
                            savePrinterInfo = true;
                        }
                    }
                }

                // Increment the truck ticket number, even if there are 0 copies to be printed.
                //  The reason for this is because we want to have a unique ticket number for
                //  additional ticket requests even if the initial number of copies was 0.
                ++printerInfo_.config.truckTicket.ticketNumber;
                if (printerInfo_.config.truckTicket.ticketNumber > 65503) {
                    printerInfo_.config.truckTicket.ticketNumber = 0;
                }
                savePrinterInfo = true;
            }

            // Send UDP message if configured.
            if ((printerInfo_.config.udpTransferEnabled) && (SEALevel2Installed)) {
                std::string filename(makeTempPath(LAST_STORED_TRUCK_FILENAME_JSON));
                if(!LastTruckMessage::sendLastTruckMessage(filename, loadRecord, printerInfo_.config.udpTransferIp,
                        printerInfo_.config.udpTransferPort, productId)) {
                    AIS_LOG_ERROR("Failed to send UDP message");
                }
            }

            // Create and send the eTicket file
            {
                FileTransferBridgeRequest request;
                request.fileAttr = request.GenerateFileNamev2(FileTransferBridgeRequestStorage::FileType::CPMTicket, productId);
                request.fileAttr.DirPath = fileTransferTxDir_.string() + fs::path::preferred_separator;

                std::string filePath = fileTransferTxPath(request.fileAttr.Name);

                try {
                    std::ofstream ofs(filePath, std::ios_base::binary | std::ios_base::out);
                    if (ofs) {
                        CPMTicket::generateCPMTicket(ofs, loadRecord);
                        request.fileAttr.SizeInBytes = ofs.tellp();
                        ofs.close();

                        // We have a file, send the request
                        if (nullptr != fileTransferBridgeRequestOutput_) {
                            if (fileTransferBridgeRequestOutput_->publish(request)) {
                                AIS_LOG_NOTICE("File transfer request published, \"%s\".", filePath.c_str());
                            }
                            else {
                                AIS_LOG_ERROR("Unable to publish file transfer request.");
                            }
                        }
                    }
                }
                catch (...) {
                    AIS_LOG_ERROR("Failed to create CPM Ticket file");
                }
            }            

            // Send TMAC Pcs Cycle file
            {
                FileTransferBridgeRequest request;
                request.fileAttr = request.GenerateFileNamev2(FileTransferBridgeRequestStorage::FileType::PCS_CYCLE, productId);
                request.fileAttr.DirPath = fileTransferTxDir_.string() + fs::path::preferred_separator;

                std::string filePath = fileTransferTxPath(request.fileAttr.Name);

                try {
                    std::ofstream ofs(filePath, std::ios_base::binary | std::ios_base::out);
                    if (ofs) {
                        std::string msg = telemetry_.generatePcsCycleMsg(loadRecord, operatorId_);
                        ofs << msg;
                        ofs.close();
                        request.fileAttr.SizeInBytes = msg.length();

                        // We have a file, send the request
                        if (nullptr != fileTransferBridgeRequestOutput_) {
                            if (fileTransferBridgeRequestOutput_->publish(request)) {
                                AIS_LOG_NOTICE("File transfer request published, \"%s\".", filePath.c_str());
                            }
                            else {
                                AIS_LOG_ERROR("Unable to publish file transfer request.");
                            }
                        }
                    }
                }
                catch (...) {
                    AIS_LOG_ERROR("Failed to create TMAC Pcs Cycle file");
                }
            }

            { // Log
                std::stringstream ss;
                ss << lifetimeTotals_;
                AIS_LOG_INFO(ss.str());
            }
        }
    }

    /*
     * If operator id changed and we didn't just publish vp3 records
     * then we need to send a status record to vp3 to record the change
     * in operator id.
     */
    if (operatorIdChanged) {
        // Create and send the vp3 record
        if (nullptr != vp3CreateRecordInterface_) {
            VP3Record r = VP3LoadBuilder::generateVP3StatusRecord(serviceHourMeter_, operatorId_);
            if (!vp3CreateRecordInterface_->publish(r)) {
                AIS_LOG_ERROR("Failed to publish vp3 record type %d.", r.getRecordType());
            }
            AIS_LOG_INFO("VP3 record created.");
        }
    }

    // Process requests
    LpsSaTotalsRequestInterface request;
    while (requestChannelInput_->get(request)) {
        switch (request.command) {

#ifdef GRPC_SUPPORTED
        case (LpsSaTotalsRequestInterfaceCommand::USB_CMD_SAVE_ALL): {
            cdaUSBWriter_.processUSBSaveCmd(CDAUSBWriter::USB_CMD_SAVE_ALL);
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("USB_CMD_SAVE_ALL received");
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::USB_CMD_SAVE_NEW): {
            cdaUSBWriter_.processUSBSaveCmd(CDAUSBWriter::USB_CMD_SAVE_NEW);
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("USB_CMD_SAVE_NEW received");
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::USB_CMD_SAVE_CANCEL): {
            cdaUSBWriter_.processUSBSaveCmd(CDAUSBWriter::USB_CMD_CANCEL_SAVE);
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("USB_CMD_SAVE_CANCEL received");
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::USB_SAVE_PROGRESS): {
            CDAUSBWriter::USBSaveProgress_t progress = cdaUSBWriter_.getUSBSaveProgress();
            // populate interface and publish
            if (USBSaveProgressOutput_) {
                LpsSaTotalsUSBSaveProgressInterface USBSaveProgress;
                USBSaveProgress.filesTransfered = progress.filesTransferred;
                USBSaveProgress.totalFiles = progress.totalFiles;
                USBSaveProgress.state = progress.status;
                USBSaveProgressOutput_->publish(USBSaveProgress);
                AIS_LOG_INFO("USB_SAVE_PROGRESS published");
            }

            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("USB_SAVE_PROGRESS received");
            break;
        }
#endif

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_MATERIAL_TOTALS): {
            const std::string filePath(makeTempPath(TOTALS_FILENAME_JSON("Material")));

            if (materialTotals_.publish(filePath, printerInfo_)) {
                sendReqstResponse(request, true, filePath); // Publish response
                AIS_LOG_INFO("Material totals published");
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to publish material totals");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_MATERIAL_TOTALS_TODAY): {
            const std::string filePath(makeTempPath(TOTALS_TODAY_FILENAME_JSON("Material")));
            const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

            if (materialTotalsToday_.resetTime >= startOfToday) {
                if (materialTotalsToday_.publish(filePath, printerInfo_)) {
                    sendReqstResponse(request, true, filePath); // Publish response
                    AIS_LOG_INFO("Material totals today published");
                }
                else {
                    sendReqstResponse(request, false); // Publish response
                    AIS_LOG_ERROR("Failed to publish material totals today");
                }
            }
            else {
                LpsSaDailyTotalsMapped emptyTotals(materialTotalsToday_.printHeader);
                emptyTotals.reset(); // This sets the reset time to now.
                if (emptyTotals.publish(filePath, printerInfo_)) {
                    sendReqstResponse(request, true, filePath); // Publish response
                    AIS_LOG_INFO("Material totals today published, empty");
                }
                else {
                    sendReqstResponse(request, false); // Publish response
                    AIS_LOG_ERROR("Failed to publish material totals today");
                }
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_MATERIAL_TOTALS_PREVIOUS_DAY): {
            const std::string filePath = makeTempPath(TOTALS_PREVIOUS_DAY_FILENAME_JSON("Material"));
            const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

            if (materialTotalsToday_.resetTime >= startOfToday) {
                // Load previous day and publish it
                LpsSaDailyTotalsMapped previousDayTotals(materialTotalsToday_.printHeader);
                previousDayTotals.load(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN("Material")));
                if (previousDayTotals.publish(filePath, printerInfo_)) {
                    sendReqstResponse(request, true, filePath); // Publish response
                    AIS_LOG_INFO("Material totals previous day published");
                }
                else {
                    sendReqstResponse(request, false); // Publish response
                    AIS_LOG_ERROR("Failed to publish material totals previous day");
                }
            }
            else {
                // "today" is the previous day
                if (materialTotalsToday_.publish(filePath, printerInfo_)) {
                    sendReqstResponse(request, true, filePath); // Publish response
                    AIS_LOG_INFO("Material totals previous day published");
                }
                else {
                    sendReqstResponse(request, false); // Publish response
                    AIS_LOG_ERROR("Failed to publish material totals previous day");
                }
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_TRUCK_TOTALS): {
            const std::string filePath(makeTempPath(TOTALS_FILENAME_JSON("Truck")));

            if (truckTotals_.publish(filePath, printerInfo_)) {
                sendReqstResponse(request, true, filePath); // Publish response
                AIS_LOG_INFO("Truck totals published");
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to publish truck totals");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_TRUCK_TOTALS_TODAY): {
            const std::string filePath(makeTempPath(TOTALS_TODAY_FILENAME_JSON("Truck")));
            const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

            if (truckTotalsToday_.resetTime >= startOfToday) {
                if (truckTotalsToday_.publish(filePath, printerInfo_)) {
                    sendReqstResponse(request, true, filePath); // Publish response
                    AIS_LOG_INFO("Truck totals today published");
                }
                else {
                    sendReqstResponse(request, false); // Publish response
                    AIS_LOG_ERROR("Failed to publish truck totals today");
                }
            }
            else {
                LpsSaDailyTotalsMapped emptyTotals(truckTotalsToday_.printHeader);
                emptyTotals.reset(); // This sets the reset time to now.
                if (emptyTotals.publish(filePath, printerInfo_)) {
                    sendReqstResponse(request, true, filePath); // Publish response
                    AIS_LOG_INFO("Truck totals today published, empty");
                }
                else {
                    sendReqstResponse(request, false); // Publish response
                    AIS_LOG_ERROR("Failed to publish truck totals today");
                }
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_TRUCK_TOTALS_PREVIOUS_DAY): {
            const std::string filePath = makeTempPath(TOTALS_PREVIOUS_DAY_FILENAME_JSON("Truck"));
            const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

            if (truckTotalsToday_.resetTime >= startOfToday) {
                // Load previous day and publish it
                LpsSaDailyTotalsMapped previousDayTotals(truckTotalsToday_.printHeader);
                previousDayTotals.load(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN("Truck")));
                if (previousDayTotals.publish(filePath, printerInfo_)) {
                    sendReqstResponse(request, true, filePath); // Publish response
                    AIS_LOG_INFO("Truck totals previous day published");
                }
                else {
                    sendReqstResponse(request, false); // Publish response
                    AIS_LOG_ERROR("Failed to publish truck totals previous day");
                }
            }
            else {
                // "today" is the previous day
                if (truckTotalsToday_.publish(filePath, printerInfo_)) {
                    sendReqstResponse(request, true, filePath); // Publish response
                    AIS_LOG_INFO("Truck totals previous day published");
                }
                else {
                    sendReqstResponse(request, false); // Publish response
                    AIS_LOG_ERROR("Failed to publish truck totals previous day");
                }
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_TAG_TOTALS): {
            const uint32_t tagTotalsIndex = request.tagTotalsIndex();
            std::string fileNamePrefix;
            LpsSaTotalsMapped const* tagTotals = tagTotalsByIndex(tagTotalsIndex, fileNamePrefix);
            const std::string filePath = makeTempPath(TOTALS_FILENAME_JSON(fileNamePrefix));

            if ((nullptr != tagTotals) && (tagTotals->publish(filePath, printerInfo_))) {
                sendReqstResponse(request, true, filePath); // Publish response
                AIS_LOG_INFO("Tag totals published");
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to publish tag totals");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_TAG_TOTALS_TODAY): {
            const uint32_t tagTotalsIndex = request.tagTotalsIndex();
            std::string fileNamePrefix;
            LpsSaDailyTotalsMapped const* tagTotals = tagTotalsTodayByIndex(tagTotalsIndex, fileNamePrefix);

            if (nullptr != tagTotals) {
                const std::string filePath = makeTempPath(TOTALS_TODAY_FILENAME_JSON(fileNamePrefix));
                const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

                if (tagTotals->resetTime >= startOfToday) {
                    if (tagTotals->publish(filePath, printerInfo_)) {
                        sendReqstResponse(request, true, filePath); // Publish response
                        AIS_LOG_INFO("Tag totals today published");
                    }
                    else {
                        sendReqstResponse(request, false); // Publish response
                        AIS_LOG_ERROR("Failed to publish tag totals today");
                    }
                }
                else {
                    LpsSaDailyTotalsMapped emptyTotals(tagTotals->printHeader);
                    emptyTotals.reset(); // This sets the reset time to now.
                    if (emptyTotals.publish(filePath, printerInfo_)) {
                        sendReqstResponse(request, true, filePath); // Publish response
                        AIS_LOG_INFO("Tag totals today published, empty");
                    }
                    else {
                        sendReqstResponse(request, false); // Publish response
                        AIS_LOG_ERROR("Failed to publish tag totals today");
                    }
                }
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to publish tag totals today");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_TAG_TOTALS_PREVIOUS_DAY): {
            std::string fileNamePrefix;
            const uint32_t tagTotalsIndex = request.tagTotalsIndex();
            LpsSaDailyTotalsMapped const* tagTotals = tagTotalsTodayByIndex(tagTotalsIndex, fileNamePrefix);

            if (nullptr != tagTotals) {
                const std::string filePath = makeTempPath(TOTALS_PREVIOUS_DAY_FILENAME_JSON(fileNamePrefix));
                const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

                if (tagTotals->resetTime >= startOfToday) {
                    // Load previous day and publish it
                    LpsSaDailyTotalsMapped previousDayTotals(tagTotals->printHeader);
                    previousDayTotals.load(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN(fileNamePrefix)));
                    if (previousDayTotals.publish(filePath, printerInfo_)) {
                        sendReqstResponse(request, true, filePath); // Publish response
                        AIS_LOG_INFO("Tag totals previous day published");
                    }
                    else {
                        sendReqstResponse(request, false); // Publish response
                        AIS_LOG_ERROR("Failed to publish tag totals previous day");
                    }
                }
                else {
                    // "today" is the previous day
                    if (tagTotals->publish(filePath, printerInfo_)) {
                        sendReqstResponse(request, true, filePath); // Publish response
                        AIS_LOG_INFO("Tag totals previous day published");
                    }
                    else {
                        sendReqstResponse(request, false); // Publish response
                        AIS_LOG_ERROR("Failed to publish tag totals previous day");
                    }
                }
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to publish tag totals previous day");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_TICKET_HISTORY): {
            const std::string filePath = makeTempPath(TICKET_HISTORY_FILENAME_JSON);
            const std::string localDateStr = request.localDateStr();
            if (historyManager_.publishTicketHistory(filePath, printerInfo_, productId, localDateStr)) {
                sendReqstResponse(request, true, filePath); // Publish response
                AIS_LOG_INFO("Ticket history published");
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to publish ticket history");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_TICKET_HISTORY_NEXT): {
            const std::string filePath = makeTempPath(TICKET_HISTORY_FILENAME_JSON);
            const std::string localDateStr = request.localDateStr();
            if (historyManager_.publishTicketHistoryNext(filePath, printerInfo_, productId, localDateStr)) {
                sendReqstResponse(request, true, filePath); // Publish response
                AIS_LOG_INFO("Ticket history next published");
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to publish ticket history next");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_TICKET_HISTORY_PREVIOUS): {
            const std::string filePath = makeTempPath(TICKET_HISTORY_FILENAME_JSON);
            const std::string localDateStr = request.localDateStr();
            if (historyManager_.publishTicketHistoryPrevious(filePath, printerInfo_, productId, localDateStr)) {
                sendReqstResponse(request, true, filePath); // Publish response
                AIS_LOG_INFO("Ticket history previous published");
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to publish ticket history previous");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PUBLISH_TICKET_DETAILS): {
            const std::string filePath = makeTempPath(TICKET_DETAILS_FILENAME_JSON);
            const std::string ticketId = request.ticketId();
            if (historyManager_.publishTicketDetails(filePath, printerInfo_, productId, ticketId)) {
                sendReqstResponse(request, true, filePath); // Publish response
                AIS_LOG_INFO("Ticket details published");
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to publish ticket details");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_TRUCK_TOTALS_ALL): {
            bool success = false;
            if ((printerInfo_.config.installed) && (nullptr != printerRequestChannelOutput_)) {
                const std::string filePath(makeTempPath(TOTALS_FILENAME_TXT("Truck")));

                if (truckTotals_.print(filePath, printerInfo_)) {
                    SerialPrinterRequestInterface printRequest;
                    printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                    printRequest.filePath(filePath);
                    printRequest.numberOfCopies(1);
                    if (printerRequestChannelOutput_->publish(printRequest)) {
                        success = true;
                    }
                }
            }
            if (success) {
                ++printerInfo_.totals.numTruckTotals;
                savePrinterInfo = true;
                sendReqstResponse(request, true);
                AIS_LOG_INFO("Truck Totals print requested");
        	}
        	else {
        		sendReqstResponse(request, false);
        		AIS_LOG_ERROR("Failed to request Truck Totals print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_TRUCK_TOTALS_TODAY): {
            bool success = false;
            if ((printerInfo_.config.installed) && (nullptr != printerRequestChannelOutput_)) {
                const std::string filePath(makeTempPath(TOTALS_TODAY_FILENAME_TXT("Truck")));
                const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

                if (truckTotalsToday_.resetTime >= startOfToday) {
                    if (truckTotalsToday_.print(filePath, printerInfo_)) {
                        success = true;
                    }
                }
                else {
                    LpsSaDailyTotalsMapped emptyTotals(truckTotalsToday_.printHeader);
                    emptyTotals.reset(); // This sets the reset time to now.
                    if (emptyTotals.print(filePath, printerInfo_)) {
                        success = true;
                    }
                }

                if (success) {
                    SerialPrinterRequestInterface printRequest;
                    printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                    printRequest.filePath(filePath);
                    printRequest.numberOfCopies(1);
                    if (!printerRequestChannelOutput_->publish(printRequest)) {
                        success = false;
                    }
                }
            }

            if (success) {
                ++printerInfo_.totals.numTruckTotals;
                savePrinterInfo = true;
                sendReqstResponse(request, true);
                AIS_LOG_INFO("Truck Totals today print requested");
            }
            else {
                sendReqstResponse(request, false);
                AIS_LOG_ERROR("Failed to request Truck Totals today print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_TRUCK_TOTALS_PREVIOUS_DAY): {
            bool success = false;
            if ((printerInfo_.config.installed) && (nullptr != printerRequestChannelOutput_)) {
                const std::string filePath(makeTempPath(TOTALS_PREVIOUS_DAY_FILENAME_TXT("Truck")));
                const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

                if (truckTotalsToday_.resetTime >= startOfToday) {
                    // Load previous day and publish it
                    LpsSaDailyTotalsMapped previousDayTotals(truckTotalsToday_.printHeader);
                    previousDayTotals.load(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN("Truck")));
                    if (previousDayTotals.print(filePath, printerInfo_)) {
                        success = true;
                    }
                }
                else {
                    // "today" is the previous day
                    if (truckTotalsToday_.print(filePath, printerInfo_)) {
                        success = true;
                    }
                }

                if (success) {
                    SerialPrinterRequestInterface printRequest;
                    printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                    printRequest.filePath(filePath);
                    printRequest.numberOfCopies(1);
                    if (!printerRequestChannelOutput_->publish(printRequest)) {
                        success = false;
                    }
                }
            }

            if (success) {
                ++printerInfo_.totals.numTruckTotals;
                savePrinterInfo = true;
                sendReqstResponse(request, true);
                AIS_LOG_INFO("Truck Totals previous day print requested");
            }
            else {
                sendReqstResponse(request, false);
                AIS_LOG_ERROR("Failed to request Truck Totals previous day print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_TAG_TOTALS_ALL): {
            bool success = false;
            const uint32_t tagTotalsIndex = request.tagTotalsIndex();

            if ((printerInfo_.config.installed) && (nullptr != printerRequestChannelOutput_)) {
                std::string fileNamePrefix;
                LpsSaTotalsMapped const* tagTotals = tagTotalsByIndex(tagTotalsIndex, fileNamePrefix);
                const std::string filePath = makeTempPath(TOTALS_FILENAME_TXT(fileNamePrefix));

                if ((nullptr != tagTotals) && (tagTotals->print(filePath, printerInfo_))) {
                    SerialPrinterRequestInterface printRequest;
                    printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                    printRequest.filePath(filePath);
                    printRequest.numberOfCopies(1);
                    if (printerRequestChannelOutput_->publish(printRequest)) {
                        success = true;
                    }
                }
            }

            if (success) {
                if (1 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag1Reports;
                }
                else if (2 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag2Reports;
                }
                else if (3 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag3Reports;
                }
                else if (4 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag4Reports;
                }

                savePrinterInfo = true;
                sendReqstResponse(request, true);
                AIS_LOG_INFO("Tag totals print requested");
            }
            else {
                sendReqstResponse(request, false);
                AIS_LOG_ERROR("Failed to request Tag Totals print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_TAG_TOTALS_TODAY): {
            bool success = false;
            const uint32_t tagTotalsIndex = request.tagTotalsIndex();

            if ((printerInfo_.config.installed) && (nullptr != printerRequestChannelOutput_)) {
                std::string fileNamePrefix;
                LpsSaDailyTotalsMapped const* tagTotals = tagTotalsTodayByIndex(tagTotalsIndex, fileNamePrefix);

                if (nullptr != tagTotals) {
                    const std::string filePath = makeTempPath(TOTALS_TODAY_FILENAME_TXT(fileNamePrefix));
                    const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

                    if (tagTotals->resetTime >= startOfToday) {
                        if (tagTotals->print(filePath, printerInfo_)) {
                            success = true;
                        }
                    }
                    else {
                        LpsSaDailyTotalsMapped emptyTotals(tagTotals->printHeader);
                        emptyTotals.reset(); // This sets the reset time to now.
                        if (emptyTotals.print(filePath, printerInfo_)) {
                            success = true;
                        }
                    }

                    if (success) {
                        SerialPrinterRequestInterface printRequest;
                        printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                        printRequest.filePath(filePath);
                        printRequest.numberOfCopies(1);
                        if (!printerRequestChannelOutput_->publish(printRequest)) {
                            success = false;
                        }
                    }
                }
            }

            if (success) {
                if (1 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag1Reports;
                }
                else if (2 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag2Reports;
                }
                else if (3 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag3Reports;
                }
                else if (4 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag4Reports;
                }

                savePrinterInfo = true;
                sendReqstResponse(request, true);
                AIS_LOG_INFO("Tag totals today print requested");
            }
            else {
                sendReqstResponse(request, false);
                AIS_LOG_ERROR("Failed to request Tag Totals today print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_TAG_TOTALS_PREVIOUS_DAY): {
            bool success = false;
            const uint32_t tagTotalsIndex = request.tagTotalsIndex();

            if ((printerInfo_.config.installed) && (nullptr != printerRequestChannelOutput_)) {
                std::string fileNamePrefix;
                LpsSaDailyTotalsMapped const* tagTotals = tagTotalsTodayByIndex(tagTotalsIndex, fileNamePrefix);

                if (nullptr != tagTotals) {
                    const std::string filePath = makeTempPath(TOTALS_PREVIOUS_DAY_FILENAME_TXT(fileNamePrefix));
                    const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

                    if (tagTotals->resetTime >= startOfToday) {
                        // Load previous day and publish it
                        LpsSaDailyTotalsMapped previousDayTotals(tagTotals->printHeader);
                        previousDayTotals.load(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN(fileNamePrefix)));
                        if (previousDayTotals.print(filePath, printerInfo_)) {
                            success = true;
                        }
                    }
                    else {
                        // "today" is the previous day
                        if (tagTotals->print(filePath, printerInfo_)) {
                            success = true;
                        }
                    }

                    if (success) {
                        SerialPrinterRequestInterface printRequest;
                        printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                        printRequest.filePath(filePath);
                        printRequest.numberOfCopies(1);
                        if (!printerRequestChannelOutput_->publish(printRequest)) {
                            success = false;
                        }
                    }
                }
            }

            if (success) {
                if (1 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag1Reports;
                }
                else if (2 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag2Reports;
                }
                else if (3 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag3Reports;
                }
                else if (4 == tagTotalsIndex) {
                    ++printerInfo_.totals.numTag4Reports;
                }

                savePrinterInfo = true;
                sendReqstResponse(request, true);
                AIS_LOG_INFO("Tag totals previous day print requested");
            }
            else {
                sendReqstResponse(request, false);
                AIS_LOG_ERROR("Failed to request Tag Totals previous day print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_MATERIAL_TOTALS_ALL): {
            bool success = false;
            if (printerInfo_.config.installed && (nullptr != printerRequestChannelOutput_)) {
                const std::string filePath(makeTempPath(TOTALS_FILENAME_TXT("Material")));
                if (materialTotals_.print(filePath, printerInfo_)) {
                    // Build a print request to the printer app
                    SerialPrinterRequestInterface printRequest;
                    printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                    printRequest.filePath(filePath);
                    printRequest.numberOfCopies(1);
                    if (printerRequestChannelOutput_->publish(printRequest)) {
                        success = true;
                    }
                }
            }

            if (success) {
                ++printerInfo_.totals.numMaterialReports;
                savePrinterInfo = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Material totals print requested");
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to request material totals print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_MATERIAL_TOTALS_TODAY): {
            bool success = false;
            if ((printerInfo_.config.installed) && (nullptr != printerRequestChannelOutput_)) {
                const std::string filePath(makeTempPath(TOTALS_TODAY_FILENAME_TXT("Material")));
                const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

                if (materialTotalsToday_.resetTime >= startOfToday) {
                    if (materialTotalsToday_.print(filePath, printerInfo_)) {
                        success = true;
                    }
                }
                else {
                    LpsSaDailyTotalsMapped emptyTotals(materialTotalsToday_.printHeader);
                    emptyTotals.reset(); // This sets the reset time to now.
                    if (emptyTotals.print(filePath, printerInfo_)) {
                        success = true;
                    }
                }

                if (success) {
                    SerialPrinterRequestInterface printRequest;
                    printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                    printRequest.filePath(filePath);
                    printRequest.numberOfCopies(1);
                    if (!printerRequestChannelOutput_->publish(printRequest)) {
                        success = false;
                    }
                }
            }

            if (success) {
                ++printerInfo_.totals.numMaterialReports;
                savePrinterInfo = true;
                sendReqstResponse(request, true);
                AIS_LOG_INFO("Material Totals today print requested");
            }
            else {
                sendReqstResponse(request, false);
                AIS_LOG_ERROR("Failed to request Material Totals today print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_MATERIAL_TOTALS_PREVIOUS_DAY): {
            bool success = false;
            if ((printerInfo_.config.installed) && (nullptr != printerRequestChannelOutput_)) {
                const std::string filePath(makeTempPath(TOTALS_PREVIOUS_DAY_FILENAME_TXT("Material")));
                const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

                if (materialTotalsToday_.resetTime >= startOfToday) {
                    // Load previous day and publish it
                    LpsSaDailyTotalsMapped previousDayTotals(materialTotalsToday_.printHeader);
                    previousDayTotals.load(makeStoragePath(TOTALS_PREVIOUS_DAY_FILENAME_BIN("Material")));
                    if (previousDayTotals.print(filePath, printerInfo_)) {
                        success = true;
                    }
                }
                else {
                    // "today" is the previous day
                    if (materialTotalsToday_.print(filePath, printerInfo_)) {
                        success = true;
                    }
                }

                if (success) {
                    SerialPrinterRequestInterface printRequest;
                    printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                    printRequest.filePath(filePath);
                    printRequest.numberOfCopies(1);
                    if (!printerRequestChannelOutput_->publish(printRequest)) {
                        success = false;
                    }
                }
            }

            if (success) {
                ++printerInfo_.totals.numMaterialReports;
                savePrinterInfo = true;
                sendReqstResponse(request, true);
                AIS_LOG_INFO("Material Totals previous day print requested");
            }
            else {
                sendReqstResponse(request, false);
                AIS_LOG_ERROR("Failed to request Material Totals previous day print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_MATERIAL_TOTAL): {
            /*
             * Not going to be supported for CPM 2.0
             */
            AIS_LOG_WARN("Command %i not supported", request.command);
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_TRUCK_REPORT_ALL): {
            bool success = false;

            if (printerInfo_.config.installed && (nullptr != printerRequestChannelOutput_)) {
                std::string filePath(makeTempPath(LOAD_HISTORY_FILENAME_TXT));
                if (loadHistory_.print(filePath, printerInfo_, false)) {
                    // Build a print request to the printer app
                    SerialPrinterRequestInterface printRequest;
                    printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                    printRequest.filePath(filePath);
                    printRequest.numberOfCopies(1);
                    if (printerRequestChannelOutput_->publish(printRequest)) {
                        success = true;
                    }
                }
            }

            if (success) {
                ++printerInfo_.totals.numTruckReports;
                savePrinterInfo = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Load history print requested");
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to request load history print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_TRUCK_REPORT_TODAY ): {
            bool success = false;
            if (printerInfo_.config.installed && (nullptr != printerRequestChannelOutput_)) {
                std::string filePath(makeTempPath(LOAD_HISTORY_TODAY_FILENAME_TXT));
                const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

                if (loadHistoryToday_.resetTime >= startOfToday) {
                    if (loadHistoryToday_.print(filePath, printerInfo_, true)) {
                        success = true;
                    }
                }
                else {
                    LpsSaTotalsLoadHistoryStorage emptyLoadHistory;
                    emptyLoadHistory.reset();
                    if (emptyLoadHistory.print(filePath, printerInfo_, true)) {
                        success = true;
                    }
                }

                if (success)
                {
                    // Build a print request to the printer app
                    SerialPrinterRequestInterface printRequest;
                    printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                    printRequest.filePath(filePath);
                    printRequest.numberOfCopies(1);
                    if (!printerRequestChannelOutput_->publish(printRequest)) {
                        success = false;
                    }
                }
            }

            if (success) {
                ++printerInfo_.totals.numTruckReports;
                savePrinterInfo = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Load history print requested");
            }
            else {
                sendReqstResponse(request, false); // Publish response

                AIS_LOG_ERROR("Failed to request load history print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_TRUCK_REPORT_PREVIOUS_DAY ): {
            bool success = false;

            if (printerInfo_.config.installed && (nullptr != printerRequestChannelOutput_)) {
                std::string filePath(makeTempPath(LOAD_HISTORY_PREVIOUS_DAY_FILENAME_TXT));
                const auto startOfToday = tes_common_ais::getUTCStartOfLocalDay();

                if (loadHistoryToday_.resetTime >= startOfToday) {
                    LpsSaTotalsLoadHistoryStorage loadHistoryPreviousDay;
                    loadHistoryPreviousDay.load(makeStoragePath(LOAD_HISTORY_PREVIOUS_DAY_FILENAME_BIN));
                    if (loadHistoryPreviousDay.print(filePath, printerInfo_, true)) {
                        success = true;
                    }
                }
                else {
                    if (loadHistoryToday_.print(filePath, printerInfo_, true)) {
                        success = true;
                    }
                }

                if (success) {
                    // Build a print request to the printer app
                    SerialPrinterRequestInterface printRequest;
                    printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                    printRequest.filePath(filePath);
                    printRequest.numberOfCopies(1);
                    if (!printerRequestChannelOutput_->publish(printRequest)) {
                        success = false;
                    }
                }
            }

            if (success) {
                ++printerInfo_.totals.numTruckReports;
                savePrinterInfo = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Load history print requested");
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to request load history print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::PRINT_TRUCK_TICKET): {
            bool success = false;

            if (printerInfo_.config.installed && (nullptr != printerRequestChannelOutput_)) {
                std::string filePath(makeTempPath(ADDITIONAL_TRUCK_TICKET_FILENAME_TXT));
                auto ticketId = request.ticketId();

                if (ticketId.empty()) {
                    // Ticket Id is empty, print the last stored ticket
                    if ((lastLoad_.isSet) && (lastLoad_.print(filePath, printerInfo_))) {
                        // Build a print request to the printer app
                        SerialPrinterRequestInterface printRequest;
                        printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                        printRequest.filePath(filePath);
                        printRequest.numberOfCopies(1);
                        if (printerRequestChannelOutput_->publish(printRequest)) {
                            success = true;
                        }
                    }
                }
                else {
                    // Ticket Id was provided, print that ticket
                    if (historyManager_.printTicket(filePath, printerInfo_, productId, ticketId)) {
                        // Build a print request to the printer app
                        SerialPrinterRequestInterface printRequest;
                        printRequest.command = SerialPrinterRequestInterfaceCommand::PRINT;
                        printRequest.filePath(filePath);
                        printRequest.numberOfCopies(1);
                        if (printerRequestChannelOutput_->publish(printRequest)) {
                            success = true;
                        }
                    }
                }
            }

            if (success) {
                ++printerInfo_.totals.numAdditionalTruckTickets;
                savePrinterInfo = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Additional truck ticket print requested");
            }
            else {
                sendReqstResponse(request, false); // Publish response
                AIS_LOG_ERROR("Failed to request additional truck ticket print");
            }
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::CLEAR_ALL_PRINTED_REPORTS): {
            /*
             * Clear all of the printed reports
             */
            loadHistory_.reset();
            saveLoadHistory = true;

            materialTotals_.reset();
            saveMaterialTotals = true;

            truckTotals_.reset();
            saveTruckTotals = true;

            tag1Totals_.reset();
            saveTag1Totals = true;

            tag2Totals_.reset();
            saveTag2Totals = true;

            tag3Totals_.reset();
            saveTag3Totals = true;

            tag4Totals_.reset();
            saveTag4Totals = true;

            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("Cleared all printed reports");
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::CLEAR_TRUCK_REPORT_ALL): {
            loadHistory_.reset();
            saveLoadHistory = true;
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("Cleared truck report");
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::CLEAR_MATERIAL_TOTALS_ALL): {
            materialTotals_.reset();
            saveMaterialTotals = true;
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("Cleared material totals");
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::CLEAR_MATERIAL_TOTAL): {
            std::string materialName(request.materialName());
            materialTotals_.reset(materialName);
            saveMaterialTotals = true;
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("Cleared %s material total", materialName.c_str());
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::CLEAR_TRUCK_TOTALS_ALL): {
            truckTotals_.reset();
            saveTruckTotals = true;
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("Cleared truck totals");
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::CLEAR_TRUCK_TOTAL): {
            std::string truckName(request.truckName());
            truckTotals_.reset(truckName);
            saveTruckTotals = true;
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("Cleared %s truck total", truckName.c_str());
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::CLEAR_TAG_TOTALS_ALL): {
            uint32_t tagTotalsIndex = request.tagTotalsIndex();

            if (1 == tagTotalsIndex) {
                tag1Totals_.reset();
                saveTag1Totals = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Cleared tag 1 totals");
            }
            else if (2 == tagTotalsIndex) {
                tag2Totals_.reset();
                saveTag2Totals = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Cleared tag 2 totals");
            }
            else if (3 == tagTotalsIndex) {
                tag3Totals_.reset();
                saveTag3Totals = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Cleared tag 3 totals");
            }
            else if (4 == tagTotalsIndex) {
                tag4Totals_.reset();
                saveTag4Totals = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Cleared tag 4 totals");
            }
            else {
                AIS_LOG_ERROR("Failed to clear tag totals, invalid index.");
            }

            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::CLEAR_TAG_TOTAL): {
            uint32_t tagTotalsIndex = request.tagTotalsIndex();
            std::string tagName(request.tagItemName());

            if (1 == tagTotalsIndex) {
                tag1Totals_.reset(tagName);
                saveTag1Totals = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Cleared %s tag 1 total", tagName.c_str());
            }
            else if (2 == tagTotalsIndex) {
                tag2Totals_.reset(tagName);
                saveTag2Totals = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Cleared %s tag 2 total", tagName.c_str());
            }
            else if (3 == tagTotalsIndex) {
                tag3Totals_.reset(tagName);
                saveTag3Totals = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Cleared %s tag 3 total", tagName.c_str());
            }
            else if (4 == tagTotalsIndex) {
                tag4Totals_.reset(tagName);
                saveTag4Totals = true;
                sendReqstResponse(request, true); // Publish response
                AIS_LOG_INFO("Cleared %s tag 4 total", tagName.c_str());
            }
            else {
                AIS_LOG_ERROR("Failed to clear tag total, invalid index.");
            }

            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::CLEAR_TRIP_TOTAL_A): {
            lifetimeTotals_.resetTripA();
            saveLifetimeTotals = true;
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("Cleared trip A");
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::CLEAR_TRIP_TOTAL_B): {
            lifetimeTotals_.resetTripB();
            saveLifetimeTotals = true;
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("Cleared trip B");
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::WRITE_LIFETIME_TOTAL_WEIGHT): {
            lifetimeTotals_.setLifetimeWeight(request.weight());
            saveLifetimeTotals = true;
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("Lifetime total weight written.");
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::WRITE_LIFETIME_TOTAL_PASS_COUNT): {
            lifetimeTotals_.setLifetimePassCount(request.passCount());
            saveLifetimeTotals = true;
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("Lifetime total pass count written.");
            break;
        }

        case (LpsSaTotalsRequestInterfaceCommand::WRITE_LIFETIME_TOTAL_LOAD_COUNT): {
            lifetimeTotals_.setLifetimeLoadCount(request.loadCount());
            saveLifetimeTotals = true;
            sendReqstResponse(request, true); // Publish response
            AIS_LOG_INFO("Lifetime total load count written.");
            break;
        }

        default: {
            AIS_LOG_WARN("Command %i not supported", request.command);
            break;
        }
        }
    }

    // Save lifetime totals
    if (saveLifetimeTotals) {
        lifetimeTotals_.save(makeStoragePath(TOTALS_FILENAME_BIN("Lifetime")));
    }

    // Save material totals
    if (saveMaterialTotals) {
        materialTotals_.save(makeStoragePath(TOTALS_FILENAME_BIN("Material")));
        materialTotalsToday_.save(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Material")));
    }

    if (saveTruckTotals) {
        truckTotals_.save(makeStoragePath(TOTALS_FILENAME_BIN("Truck")));
        truckTotalsToday_.save(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Truck")));
    }

    if (saveTag1Totals) {
        tag1Totals_.save(makeStoragePath(TOTALS_FILENAME_BIN("Tag1")));
        tag1TotalsToday_.save(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Tag1")));
    }

    if (saveTag2Totals) {
        tag2Totals_.save(makeStoragePath(TOTALS_FILENAME_BIN("Tag2")));
        tag2TotalsToday_.save(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Tag2")));
    }

    if (saveTag3Totals) {
        tag3Totals_.save(makeStoragePath(TOTALS_FILENAME_BIN("Tag3")));
        tag3TotalsToday_.save(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Tag3")));
    }

    if (saveTag4Totals) {
        tag4Totals_.save(makeStoragePath(TOTALS_FILENAME_BIN("Tag4")));
        tag4TotalsToday_.save(makeStoragePath(TOTALS_TODAY_FILENAME_BIN("Tag4")));
    }

    if (saveLoadHistory) {
        loadHistory_.save(makeStoragePath(LOAD_HISTORY_FILENAME_BIN));
        loadHistoryToday_.save(makeStoragePath(LOAD_HISTORY_TODAY_FILENAME_BIN));
    }

    if (savePrinterInfo) {
        printerInfo_.save(makeStoragePath(PRINTER_INFO_FILENAME_BIN));
        publishPrinterInfo = true; // We save it because is changed, if it changed, publish
    }

    if (saveLastLoad) {
        lastLoad_.save(makeStoragePath(LAST_LOAD_FILENAME_BIN));
    }

    { // Handle periodic triggering of printer config publishing
        float maxUpdateCount = PRINTER_CNFG_PUBLISH_PERIOD_SEC * static_cast<float>(getCycleRateHz());

        printerCnfgUpdateCount_++;

        if (printerCnfgUpdateCount_ >= maxUpdateCount) {
            printerCnfgUpdateCount_ = 0;
            publishPrinterInfo = true;
        }
    }

    // Publish the printer config is needed
    if (publishPrinterInfo && (nullptr != printerCnfgOutput_)) {
        LpsSaTotalsPrinterCnfgInterface printerCnfg;
        printerCnfg.config = printerInfo_.config;
        printerCnfgOutput_->publish(printerCnfg);
        AIS_LOG_INFO("Published printer config.");
    }

    { // Publish lifetime totals periodically
        LpsSaTotalsInterface totals;
        totals.loadCount = lifetimeTotals_.lifetime.loadCount;
        totals.passCount = lifetimeTotals_.lifetime.passCount;
        totals.weightTonnes = lifetimeTotals_.lifetime.weightTonnes;
        totals.trips[0].loadCount = lifetimeTotals_.lifetime.loadCount - lifetimeTotals_.tripSnapshots[0].loadCount;
        totals.trips[0].passCount = lifetimeTotals_.lifetime.passCount - lifetimeTotals_.tripSnapshots[0].passCount;
        totals.trips[0].weightTonnes = lifetimeTotals_.lifetime.weightTonnes - lifetimeTotals_.tripSnapshots[0].weightTonnes;
        totals.trips[1].loadCount = lifetimeTotals_.lifetime.loadCount - lifetimeTotals_.tripSnapshots[1].loadCount;
        totals.trips[1].passCount = lifetimeTotals_.lifetime.passCount - lifetimeTotals_.tripSnapshots[1].passCount;
        totals.trips[1].weightTonnes = lifetimeTotals_.lifetime.weightTonnes - lifetimeTotals_.tripSnapshots[1].weightTonnes;
        totals.memoryRemainingPct = historyManager_.getPercentStorageRemaining();
        totalsChannelOutput_->publish(totals);
    }

    return true;
}

/*
 * AIS Task Cleanup
 */
void LpsSaTotalsApp::cleanup() {
    AIS_LOG_INFO("LpsSaTotalsApp::cleanup");
}

/*
 * Send the response to the app that made the request.
 */
bool LpsSaTotalsApp::sendReqstResponse(const LpsSaTotalsRequestInterface& request, bool success, const std::string& arg1) {
    // Build the response
    LpsSaTotalsResponseInterface response;
    response.appName = request.appName;
    response.appRequestId = request.appRequestId;
    response.command = request.command;
    response.success = success;
    response.arg1 = arg1;

    /* send response SCS channel */
    if (responseChannelOutput_) {
        if (responseChannelOutput_->publish(response)) {
            AIS_LOG_INFO("Published response, command=%d, success=%d", request.command, success);
            return true;
        }
    }

    AIS_LOG_ERROR("Failed to publish response, command=%d, success=%d", request.command, success);
    return false;
}

/*
 * Update the autonomy conditions for memory low and full events
 */
void LpsSaTotalsApp::updateMemoryEvents() {
    if (historyManager_.isMemoryFull()) {
        clearAutonomyCondition<PayloadMemoryLow>();
        setAutonomyCondition(PayloadMemoryFull());
    }
    else if (historyManager_.isMemoryLow()) {
        setAutonomyCondition(PayloadMemoryLow());
        clearAutonomyCondition<PayloadMemoryFull>();
    }
    else {
        clearAutonomyCondition<PayloadMemoryLow>();
        clearAutonomyCondition<PayloadMemoryFull>();
    }
}

