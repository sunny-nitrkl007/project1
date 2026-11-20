///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2IpcClient.cpp
/// @author    strubjc
/// @date      Mar 19, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#include "Jhm2IpcClient.h"

#include <cerrno>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#include <ais/log/AisLogger.h>

Jhm2IpcClient::Jhm2IpcClient()
{
  // TODO Auto-generated constructor stub

}

Jhm2IpcClient::~Jhm2IpcClient()
{
  // TODO Auto-generated destructor stub
}

bool Jhm2IpcClient::initialize( const std::string& sockPath )
{
  m_sockPath = sockPath;
  return true;
}

bool Jhm2IpcClient::requestParams( const std::string& req, std::string& resp )
{
  int socket_fd = -1;
  struct sockaddr_un servAddr;

  // make sure our path isn't too long
  const size_t maxLength = sizeof(servAddr.sun_path) - 1;
  if ( m_sockPath.length() + 1 > maxLength )
  {
    std::ostringstream oss;
    oss << "Specified path (" << m_sockPath << ": " << m_sockPath.length() + 1 << " bytes) exceeds maximum length (" << maxLength << " bytes)";
    resp = oss.str();
    return false;
  }

  // fill in the address we intend to bind to communicate over
  memset( reinterpret_cast<void *>(&servAddr), 0, sizeof(servAddr) );
  servAddr.sun_family = AF_UNIX;

  // allocate a socket
  if ( (socket_fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0 )
  {
    std::ostringstream oss;
    oss << "Failed to create data socket: " << strerror(errno);
    resp = oss.str();
    return false;
  }

  // Abstract namespace triggered via leading null
  strncpy( &servAddr.sun_path[1], m_sockPath.c_str(), m_sockPath.size() );
  const int servLen = 1 + m_sockPath.length() + sizeof(servAddr.sun_family);

  if( connect(socket_fd, (struct sockaddr *) &servAddr, servLen) < 0 )
  {
    std::ostringstream oss;
    oss << "Failed to connect to data socket: " << strerror(errno);
    resp = oss.str();
    return false;
  }

  int writeRetVal = write( socket_fd, req.c_str(), req.size() );
  if ( writeRetVal < 0 )
  {
    std::ostringstream oss;
    oss << "Failed to send data to server: " << strerror(errno);
    resp = oss.str();
    return false;
  }

  int numBytesRecvd = read(socket_fd, m_buf, JHM2_IPC_MAX_MSG_LEN);
  if ( numBytesRecvd <= 0 )
  {
    resp = "Error receiving data from server";
    return false;
  }

  resp.assign( m_buf, numBytesRecvd );

  close(socket_fd);

  //If we got here's we've initialized properly
  return true;
}
