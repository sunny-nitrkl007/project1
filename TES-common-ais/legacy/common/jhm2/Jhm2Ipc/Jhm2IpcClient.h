///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2IpcClient.h
/// @author    strubjc
/// @date      Mar 19, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2IPCCLIENT_H_
#define JHM2IPCCLIENT_H_

#include <string>
#include "Jhm2IpcGlobals.h"


class Jhm2IpcClient
{
  public:
    Jhm2IpcClient();
    virtual ~Jhm2IpcClient();

    bool initialize( const std::string& sockPath );
    bool requestParams( const std::string& req, std::string& resp );

  private:
    std::string m_sockPath;
    char        m_buf[JHM2_IPC_MAX_MSG_LEN];
};

#endif /* JHM2IPCCLIENT_H_ */
