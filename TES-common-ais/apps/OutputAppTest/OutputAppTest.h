#ifndef OUTPUTAPPTEST_H
#define OUTPUTAPPTEST_H

#include <ais/task/Task.h>

#include <interfaces/OutputChannel/InterfaceTypes.h>

class OutputAppTest: public task::Task
{
public:
    OutputAppTest( const std::string& taskName );
    virtual ~OutputAppTest( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );
    void addNewCommand(OutputChannel::Port port,
          OutputChannel::State initState,
          OutputChannel::ChangeDuration stateChangeDuration,
          uint32_t duration,
          OutputChannel::State finalState);
    void publish();

protected:
private:
    OutputChannelOutput *outputChannelOutput;
    OutputChannel outputChannel;
    uint32_t counter;

};

#endif
