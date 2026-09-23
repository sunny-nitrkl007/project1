#ifndef LPSSALISTMGRAPP_H
#define LPSSALISTMGRAPP_H

#include <string>
#include <chrono>
#include <array>

#include <boost/filesystem.hpp>

#include <ais/task/Task.h>

#include <interfaces/LpsSaListMgr/PostInterfaceInputChannel.h>
#include <interfaces/LpsSaListMgr/NotifyInterfaceOutputChannel.h>
#include <interfaces/LpsSaListMgr/TxInterfaceOutputChannel.h>
#include <interfaces/LpsSaUI/DisplayStateInterfaceInputChannel.h>
#include <interfaces/FileTransferBridgeRequest/Channel/channels.h>
#include <interfaces/FileTransferBridgeResponse/Channel/channels.h>
#include <interfaces/FileTransferBridgeIndication/Channel/channels.h>
#include <interfaces/LpsSaListMgr/PostInterface.hpp>

#include "LpsSaMaterialListMgr.hpp"
#include "LpsSaTruckListMgr.hpp"
#include "OperatorIdListMgr.hpp"
#include "LpsSaCustomListMgr.hpp"
#include "DirectoryMonitor.hpp"

class LpsSaListMgrApp: public task::Task
{
public:
    LpsSaListMgrApp(const std::string& taskName);
    virtual ~LpsSaListMgrApp();

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

    inline boost::filesystem::path inboxPath() const {
        return tempRoot_ / "inbox";
    }

    bool updateListSyncRx(LpsSaListMgrInterfaceListType& type);
    bool sendListToBackOffice(const LpsSaListMgr& listMgr, bool content = true);

private:
    bool initNeeded_;
    std::chrono::steady_clock::time_point initTimepoint_;
    bool initListRevisionSent_;

    boost::filesystem::path fileTransferTxDir_;
    boost::filesystem::path storageRoot_;
    boost::filesystem::path tempRoot_;

    LpsSaTruckListMgr truckListMgr_;
    LpsSaMaterialListMgr materialListMgr_;
    OperatorIdListMgr operatorIdListMgr_;
    LpsSaCustomListMgr customList1Mgr_;
    LpsSaCustomListMgr customList2Mgr_;
    LpsSaCustomListMgr customList3Mgr_;
    LpsSaCustomListMgr customList4Mgr_;

    LpsSaListMgrPostInterfaceInputChannel* postInputChannel_;
    LpsSaListMgrNotifyInterfaceOutputChannel* notifyOutputChannel_;
    LpsSaListMgrTxInterfaceOutputChannel* txOutputChannel_;
    LpsSaUIDisplayStateInterfaceInputChannel* displayStateInput_;
    FileTransferBridgeRequestOutputChannel* fileTransferRequestOutputChannel_;
    FileTransferBridgeResponseInputChannel* fileTransferResponseInputChannel_;
    FileTransferBridgeIndicationInputChannel* fileTransferIndicationInputChannel_;

    DirectoryMonitor inboxMonitor_;
    LpsSaUIDisplayStateInterface displayState;
};

#endif
