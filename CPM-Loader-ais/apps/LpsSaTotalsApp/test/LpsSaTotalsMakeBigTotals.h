#ifndef LPSSATOTALSMAKEBIGTOTALS_H
#define LPSSATOTALSMAKEBIGTOTALS_H

#include <ais/task/Task.h>

#include <interfaces/LpsSaLoadRecordChannel/Channel/Output/channel.h>


class LpsSaTotalsMakeBigTotals: public task::Task
{
public:
    LpsSaTotalsMakeBigTotals(const std::string& taskName);
    virtual ~LpsSaTotalsMakeBigTotals();

    virtual bool initialize();
    virtual bool executive();
    virtual void cleanup();

protected:

private:
    uint32_t count_;
    LpsSaLoadRecordChannelOutputChannel* lpsSaLoadRecordChannelOutput_;
};

#endif
