///////////////////////////////////////////////////////////////////////////////
/// @file      jhm2ServerTask.h
/// @author    Josh Struble
/// @date      Apr 1, 2016
/// @brief     Web server task
///
/// @attention Copyright (C) 2016
/// @attention Caterpillar, Inc.
///////////////////////////////////////////////////////////////////////////////
#ifndef jhm2ServerTask_h
#define jhm2ServerTask_h

#include <ais/task/Task.h>
#include "Jhm2WebServer/Jhm2WebServer.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief This is the main task class for PcmRemoteTask
///
/// PcmRemoteTask will launch a curses interface once task initialization
/// is successful.  Through this interface, the user can configure a scenario,
/// start and stop the system, and monitor each PCM process.
///////////////////////////////////////////////////////////////////////////////
class jhm2ServerTask: public task::Task
{
  public:
    jhm2ServerTask( const std::string& taskName );
    virtual ~jhm2ServerTask( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

  protected:
  private:
    jhm2ServerTask(const jhm2ServerTask&);  ///< Protect from accidental use
    void operator=(const jhm2ServerTask&); ///< Protect from accidental use

    jhm2::Jhm2WebServer                 m_server;
//    Jhm2IpcServer                     m_requestServer;
//    AhsJhm2JsonRequestProcessor       m_requestProc;

};

#endif
