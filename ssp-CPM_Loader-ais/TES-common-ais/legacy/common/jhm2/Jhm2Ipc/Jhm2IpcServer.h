///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2IpcServer.h
/// @author    strubjc
/// @date      Mar 19, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2IPCSERVER_H_
#define JHM2IPCSERVER_H_

#include <string>
#include "Jhm2IpcGlobals.h"
#include <jhm2/Jhm2RequestProcessor/Jhm2RequestProcessor.h>
#include <sys/select.h> //for fd_set

class Jhm2IpcServer
{
  public:
    Jhm2IpcServer();
    virtual ~Jhm2IpcServer();

    bool initialize( );
    bool initialize( const std::string& sockPath );
    bool update( Jhm2RequestProcessor& proc );

    bool initialized() const;
  private:
    bool serviceConnection( int connection_fd, Jhm2RequestProcessor& proc );

    int             m_socketFd;
    char            m_buf[JHM2_IPC_MAX_MSG_LEN];
    fd_set          m_masterFdSet;
    int             m_maxSd;


};

#endif /* JHM2IPCSERVER_H_ */
