///////////////////////////////////////////////////////////////////////////////
/// @file      jhm2ServerTask.cpp
/// @author    Josh Struble
/// @date      Apr 1, 2016
/// @brief     Web server task
///
/// @attention Copyright (C) 2016
/// @attention Caterpillar, Inc.
///////////////////////////////////////////////////////////////////////////////
#include "jhm2ServerTask.h"

#include <ais/time/GetTime.h>

using namespace task;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// @brief This is the task creation method.
/// @return Task* Pointer to the instance of the task.
///////////////////////////////////////////////////////////////////////////////
AbstractTaskCore* task::getTaskImplementation( )
{
  static jhm2ServerTask thisTask("Jhm2ServerTask");
  return &thisTask;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Constructor
///
/// @param taskName Unique name for this task
///////////////////////////////////////////////////////////////////////////////
jhm2ServerTask::jhm2ServerTask( const std::string& taskName ):
    Task( taskName )
{

}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destructor
///////////////////////////////////////////////////////////////////////////////
jhm2ServerTask::~jhm2ServerTask( )
{

}

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize method.
///
/// This method initializes the task's interfaces and configurable parameters.
///
/// @return True if successful, False otherwise
///////////////////////////////////////////////////////////////////////////////
bool jhm2ServerTask::initialize( )
{
  if ( !m_server.initialize( getTaskParser() ) )
  {
    AIS_LOG_FATAL("Could not configure web server");
    return false;
  }
  m_server.start();

//  if ( !m_requestProc.configure( getTaskParser() ) )
//  {
//    AIS_LOG_FATAL("Could not configure task parameters");
//    return false;
//  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief This is the task's executive method.
///
/// This method will process user input from the keyboard.  Each key press
/// event is possibly a command to be relayed to the other PCM processes.
///
/// @return True if the task should continue executing, False otherwise.
///////////////////////////////////////////////////////////////////////////////
bool jhm2ServerTask::executive( )
{
  m_server.update();

//  m_requestProc.update();
//
//  if ( m_requestServer.initialized() )
//  {
//    m_requestServer.update( m_requestProc );
//  } else
//  {
//    if ( !m_requestServer.initialize() )
//    {
//      AIS_LOG_CRIT("Failed to initialize request server");
//    }
//  }

  return true;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief Cleanup task
///////////////////////////////////////////////////////////////////////////////
void jhm2ServerTask::cleanup( )
{
  m_server.cleanup();
//	m_requestProc.cleanup();
}

