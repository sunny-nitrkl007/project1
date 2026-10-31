
#include "TestJhmTask.h"

using namespace task;

AbstractTaskCore* task::getTaskImplementation(void)
{
    static TestJhmTask thisTask("TestJhmTask");
    return dynamic_cast<Task *>(&thisTask);
}

TestJhmTask::TestJhmTask( const std::string& taskName ):
    Task( taskName ),
    output_( NULL )
{
}

TestJhmTask::~TestJhmTask( )
{
}

bool TestJhmTask::initialize( )
{
    output_ = dynamic_cast<CPMDemoOutput*>
        ( task::InterfaceDb::fetch("CPMDemoOutput") );
    if ( NULL == output_ ) {
        AIS_LOG_FATAL("Cannot initialize CPMDemoOutput");
        return false;
    }

    iIncrement =0;

    return true;
}


bool TestJhmTask::executive( )
{
    AIS_LOG_INFO( "%s::executive", getTaskName().c_str() );

    if ( output_ ) {

        iIncrement++;

        cpd.set_northing_top(12);
        cpd.set_easting_top(13);
        cpd.set_elevation(iIncrement);
        cpd.set_northing_bottom(15);
        cpd.set_easting_bottom(17);
        output_->publish( cpd );
    }

    return true;
}

void TestJhmTask::cleanup( )
{
    AIS_LOG_INFO( "%s::cleanup", getTaskName().c_str() );
}
