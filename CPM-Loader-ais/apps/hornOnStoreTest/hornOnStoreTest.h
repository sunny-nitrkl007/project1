#ifndef HORNTEST_H
#define HORNTEST_H

#include <ais/task/Task.h>

#include <interfaces/LpsSaJobMgrTxChannel/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrReqstChannel/InterfaceTypes.h>
#include <interfaces/OutputChannel/InterfaceTypes.h>
#include <interfaces/SwitchInputScs/InterfaceTypes.h>

class hornOnStoreTest: public task::Task
{
public:
   hornOnStoreTest( const std::string& taskName );
    virtual ~hornOnStoreTest( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

    void SendHornEnableDisable( bool HornStoreState);
    void SetExternalStore( int pressed);
    void CheckScs( void );
    void SetUIStore( void );

protected:
private:
    SwitchInputScsOutput *SwitchInputScsOutput_;
    LpsSaJobMgrTxChannelInput *LpsSaJobMgrTxChannelInput_;
    LpsSaJobMgrReqstChannelOutput *LpsSaJobMgrReqstChannelOutput_;
    OutputChannelInput *OutputChannelInput_;

    LpsSaJobMgrTxChannel lastLpsSaJobMgrTxChannel;

    int counter = 0;

};

#endif
