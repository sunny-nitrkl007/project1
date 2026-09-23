#ifndef LPSSALISTMGRTESTAPP_H
#define LPSSALISTMGRTESTAPP_H

#include <string>
#include <future>

#include <boost/filesystem.hpp>

#include <ais/task/Task.h>

#include <interfaces/LpsSaListMgr/PostInterfaceOutputChannel.h>
#include <interfaces/LpsSaListMgr/NotifyInterfaceInputChannel.h>
#include <interfaces/LpsSaListMgr/TxInterfaceInputChannel.h>


class LpsSaListMgrTestApp: public task::Task
{
public:
    LpsSaListMgrTestApp(const std::string& taskName);
    virtual ~LpsSaListMgrTestApp();

    virtual bool initialize();
    virtual bool executive();
    virtual void cleanup();

protected:
    inline std::string makeTempPath(const std::string& fileName) const {
        return (tempRoot_ / fileName).string();
    }

private:
    std::future<std::string> kbInputFuture_;

    boost::filesystem::path tempRoot_;

    LpsSaListMgrPostInterfaceOutputChannel* postOutputChannel_;
    LpsSaListMgrNotifyInterfaceInputChannel* notifyInputChannel_;
    LpsSaListMgrTxInterfaceInputChannel* txInputChannel_;
};

#endif
