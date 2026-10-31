#ifndef TESTJHMTASK_H
#define TESTJHMTASK_H

/* includes */
#include <ais/task/Task.h>
#include <interfaces/CPMDemo/InterfaceTypes.h>

/* class definition */
class TestJhmTask: public task::Task
{
public:
    TestJhmTask( const std::string& taskName );
    virtual ~TestJhmTask( );
    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );
protected:
private:
    CPMDemoOutput *output_;
    CPMDemo        cpd;

    int iIncrement;
};

#endif
