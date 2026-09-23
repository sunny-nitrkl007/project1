#ifndef LPSSATOTALSAPP_H
#define LPSSATOTALSAPP_H

#include <string>

#include <boost/filesystem.hpp>

#include <ais/task/Task.h>

#include <interfaces/LpsSaLoadRecordChannel/Channel/Input/channel.h>
#include <interfaces/LpsSaTotals/RequestInterfaceInputChannel.h>
#include <interfaces/LpsSaTotals/ResponseInterfaceOutputChannel.h>
#include <interfaces/LpsSaTotals/TotalsInterfaceOutputChannel.h>
#include <interfaces/SerialPrinter/RequestInterfaceOutputChannel.h>
#include <interfaces/LpsSaListMgr/TxInterfaceInputChannel.h>
#include <interfaces/LpsSaTotals/PrinterCnfgInterfaceInputChannel.h>
#include <interfaces/LpsSaTotals/PrinterCnfgInterfaceOutputChannel.h>
#include <interfaces/LpsSaUI/DisplayStateInterfaceInputChannel.h>
#include <interfaces/ShmClock/InterfaceTypes.h>
#include <interfaces/VP3Record/Channel/channels.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/PartNumbers/InterfaceTypes.h>
#include <interfaces/FileTransferBridgeRequest/InterfaceTypes.h>
#include <interfaces/AutonomyConditionDiagnostics/TxInterfaceInputChannel.h>
#include <interfaces/LpsSaTotals/USBSaveProgressInterfaceOutputChannel.h>
#include <interfaces/LpsSaWeighReqstChannel/InterfaceTypes.h>

#include "LpsSaTotalsHistory.h"
#include "LpsSaTotalsLifetime.h"
#include "LpsSaTotalsMaterial.h"
#include "LpsSaTotalsLoadHistory.h"
#include "LpsSaTotalsPrinterInfo.h"
#include "LpsSaTotalsLastLoad.h"
#include "LpsSaTotalsTelemetry.h"
#include "LpsSaTotalsMapped.h"
#include "LpsSaTotalsOperatorId.h"
#ifdef GRPC_SUPPORTED
#include "CDAUSBWriter.hpp"
#endif

/*
 * Lifetime Totals App
 */
class LpsSaTotalsApp: public task::Task
{
public:
	LpsSaTotalsApp(const std::string& taskName);
    virtual ~LpsSaTotalsApp();

    virtual bool initialize();
    virtual bool executive();
    virtual void cleanup();

protected:
    inline std::string makeTempPath(const std::string& fileName) const {
        return (tempRoot_ / fileName).string();
    }

    inline std::string makeStoragePath(const std::string& fileName) const {
        return (storageRoot_ / fileName).string();
    }

    inline std::string fileTransferTxPath(const std::string& fileName) const {
        return (fileTransferTxDir_ / fileName).string();
    }

    bool sendReqstResponse(const LpsSaTotalsRequestInterface& request, bool success, const std::string& arg1 = "");

    LpsSaTotalsMapped const* tagTotalsByIndex(uint32_t index, std::string& prefix) const {
        LpsSaTotalsMapped const* tagTotals = nullptr;
        if (1 == index) {
            prefix = "Tag1";
            tagTotals = &tag1Totals_;
        }
        else if (2 == index) {
            prefix = "Tag2";
            tagTotals = &tag2Totals_;
        }
        else if (3 == index) {
            prefix = "Tag3";
            tagTotals = &tag3Totals_;
        }
        else if (4 == index) {
            prefix = "Tag4";
            tagTotals = &tag4Totals_;
        }
        return tagTotals;
    }

    LpsSaDailyTotalsMapped const* tagTotalsTodayByIndex(uint32_t index, std::string& prefix) const {
        LpsSaDailyTotalsMapped const* tagTotals = nullptr;
        if (1 == index) {
            prefix = "Tag1";
            tagTotals = &tag1TotalsToday_;
        }
        else if (2 == index) {
            prefix = "Tag2";
            tagTotals = &tag2TotalsToday_;
        }
        else if (3 == index) {
            prefix = "Tag3";
            tagTotals = &tag3TotalsToday_;
        }
        else if (4 == index) {
            prefix = "Tag4";
            tagTotals = &tag4TotalsToday_;
        }
        return tagTotals;
    }

    void updateMemoryEvents();

private:
    bool initNeeded_;
    uint32_t printerCnfgUpdateCount_;
    struct {
        int32_t offset;
        int32_t index;
    } tzInfo_;
    uint32_t serviceHourMeter_;

    boost::filesystem::path storageRoot_;
    boost::filesystem::path tempRoot_;
    boost::filesystem::path fileTransferTxDir_;

    LpsSaLoadRecordChannelInputChannel* lpsSaLoadRecordChannelInput_;
    LpsSaTotalsRequestInterfaceInputChannel* requestChannelInput_;
    LpsSaTotalsResponseInterfaceOutputChannel* responseChannelOutput_;
    LpsSaTotalsInterfaceOutputChannel* totalsChannelOutput_;
    SerialPrinterRequestInterfaceOutputChannel* printerRequestChannelOutput_;
    LpsSaTotalsPrinterCnfgInterfaceInputChannel* writePrinterCnfgInput_;
    LpsSaTotalsPrinterCnfgInterfaceOutputChannel* printerCnfgOutput_;
    LpsSaUIDisplayStateInterfaceInputChannel* displayStateInput_;
    ShmClockInput* shmClockInput_;
    VP3RecordOutputChannel* vp3CreateRecordInterface_;
    DataLinkDataInput* dataLinkDataInput_;
    PartNumbersInput* partNumbersInput_;
    FileTransferBridgeRequestOutput* fileTransferBridgeRequestOutput_;
    LpsSaListMgrTxInterfaceInputChannel* lpsSaListMgrInput_;
    AutonomyConditionDiagnosticsTxInterfaceInputChannel* autonomyConditionDiagnosticsTxInputChannel_;
    LpsSaTotalsUSBSaveProgressInterfaceOutputChannel* USBSaveProgressOutput_;
    LpsSaWeighReqstChannelOutput* weighAppRequestOutput_;

    LpsSaTotalsHistoryManager historyManager_;
    LpsSaTotalsLifetimeStorage lifetimeTotals_;
    LpsSaTotalsMaterialStorage materialTotals_;
    LpsSaDailyTotalsMapped materialTotalsToday_;
    LpsSaTotalsLoadHistoryStorage loadHistory_;
    LpsSaTotalsLoadHistoryStorage loadHistoryToday_;
    LpsSaTotalsPrinterInfo printerInfo_;
    LpsSaTotalsLastLoad lastLoad_;
    LpsSaTotalsTelemetry telemetry_;
    LpsSaTotalsMapped truckTotals_;
    LpsSaDailyTotalsMapped truckTotalsToday_;
    LpsSaTotalsMapped tag1Totals_;
    LpsSaDailyTotalsMapped tag1TotalsToday_;
    LpsSaTotalsMapped tag2Totals_;
    LpsSaDailyTotalsMapped tag2TotalsToday_;
    LpsSaTotalsMapped tag3Totals_;
    LpsSaDailyTotalsMapped tag3TotalsToday_;
    LpsSaTotalsMapped tag4Totals_;
    LpsSaDailyTotalsMapped tag4TotalsToday_;
    LpsSaTotalsOperatorId operatorId_;

    std::string productId;
    std::string equipmentId;
    bool SEALevel2Installed;

#ifdef GRPC_SUPPORTED
    CDAUSBWriter cdaUSBWriter_;
#endif
};


#endif
