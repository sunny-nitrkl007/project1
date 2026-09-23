#ifndef LPSSATOTALSTESTAPP_H
#define LPSSATOTALSTESTAPP_H

#include <string>
#include <future>

#include <ais/task/Task.h>

#include <interfaces/LpsSaTotals/TotalsInterfaceInputChannel.h>
#include <interfaces/LpsSaTotals/RequestInterfaceOutputChannel.h>
#include <interfaces/LpsSaTotals/ResponseInterfaceInputChannel.h>
#include <interfaces/LpsSaLoadRecordChannel/Channel/Output/channel.h>


class LpsSaTotalsTestApp: public task::Task
{
public:
    LpsSaTotalsTestApp(const std::string& taskName);
    virtual ~LpsSaTotalsTestApp();

    virtual bool initialize();
    virtual bool executive();
    virtual void cleanup();

protected:

private:
    uint32_t number_;
    std::future<std::string> kbInputFuture_;

    LpsSaTotalsInterfaceInputChannel* totalsChannelInput_;
    LpsSaTotalsRequestInterfaceOutputChannel* requestChannelOutput_;
    LpsSaTotalsResponseInterfaceInputChannel* responseChannelInput_;
    LpsSaLoadRecordChannelOutputChannel* lpsSaLoadRecordChannelOutput_;
};

#endif
