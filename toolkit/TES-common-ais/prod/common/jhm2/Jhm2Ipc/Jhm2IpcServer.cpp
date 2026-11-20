///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2IpcServer.cpp
/// @author    strubjc
/// @date      Mar 19, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#include "Jhm2IpcServer.h"

#include <cerrno>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#include <ais/log/AisLogger.h>

#define MAX_LISTEN_CONNECTIONS 10

Jhm2IpcServer::Jhm2IpcServer():
  m_socketFd( -1 ),
  m_maxSd( -1 )
{
  memset( m_buf, 0, JHM2_IPC_MAX_MSG_LEN );
  FD_ZERO( &m_masterFdSet );
}

Jhm2IpcServer::~Jhm2IpcServer()
{
  if ( m_socketFd > -1 )
  {
    close( m_socketFd );
    m_socketFd = -1;
  }
  FD_ZERO( &m_masterFdSet );
  m_maxSd = -1;
}

bool Jhm2IpcServer::initialize(  )
{
  return initialize("jhm2CgiLocalSocket");
}

bool Jhm2IpcServer::initialize( const std::string& sockPath )
{
  struct sockaddr_un servAddr;
  int on = 1;

  // make sure our path isn't too long
  const size_t maxLength = sizeof(servAddr.sun_path) - 1;
  if ( sockPath.length() + 1 > maxLength )
  {
    AIS_LOG_ERROR( "Specified path (%s: %zd bytes) exceeds maximum length (%zd bytes)",
              sockPath.c_str(),sockPath.length() + 1, maxLength );
    return false;
  }

  // fill in the address we intend to bind to communicate over
  memset( reinterpret_cast<void *>(&servAddr), 0, sizeof(servAddr) );
  servAddr.sun_family = AF_UNIX;

  // allocate a socket
  m_socketFd = socket(PF_UNIX, SOCK_STREAM, 0);
  if ( m_socketFd < 0 )
  {
    AIS_LOG_ERROR( "Failed to create data socket: %s", strerror(errno) );
    m_socketFd = -1;
    return false;
  }

  // Allow socket descriptor to be reuseable
  if ( setsockopt(m_socketFd, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on)) < 0 )
  {
    AIS_LOG_ERROR( "Failed to set socket options for reuse: %s", strerror(errno) );
    close(m_socketFd);
    m_socketFd = -1;
    return false;
  }

  // Set socket to be non-blocking.  All of the sockets for
  // the incoming connections will also be non-blocking since
  // they will inherit that state from the listening socket.
  if ( ioctl( m_socketFd, FIONBIO, (char *)&on ) < 0 )
  {
    AIS_LOG_ERROR( "Failed to set ioctl for non blocking socket: %s", strerror(errno) );
    close(m_socketFd);
    m_socketFd = -1;
    return false;
  }

  // Abstract namespace triggered via leading null
  strncpy( &servAddr.sun_path[1], sockPath.c_str(), sockPath.size() );
  const int servLen = 1 + sockPath.length() + sizeof(servAddr.sun_family);

  // bind must be unique: this is why clientPath_ is a unique combination of task name and unix path
  if ( bind( m_socketFd, reinterpret_cast<struct sockaddr *>(&servAddr), servLen ) < 0 )
  {
    AIS_LOG_ERROR( "Error binding socket: %s", strerror(errno) );
    close( m_socketFd );
    m_socketFd = -1;
    return false;
  }

  if( listen( m_socketFd, MAX_LISTEN_CONNECTIONS ) < 0 )
  {
   AIS_LOG_ERROR( "Error listening on socket: %s", strerror(errno) );
   close(m_socketFd);
   m_socketFd = -1;
   return false;
  }

  //Initialize the FD set
  FD_ZERO( &m_masterFdSet );
  m_maxSd = m_socketFd;
  FD_SET( m_socketFd, &m_masterFdSet );

  //If we got here's we've initialized properly
  return true;
}

bool Jhm2IpcServer::update( Jhm2RequestProcessor& proc )
{
  fd_set workingSet;

  // Copy the master fd_set over to the working fd_set.
  memcpy(&workingSet, &m_masterFdSet, sizeof(m_masterFdSet));

  // Initialize the timeval struct to 0.  We don't want to wait for connections
  struct timeval selectTimeout;
  selectTimeout.tv_sec = 0;
  //selectTimeout.tv_usec = 100000; //100ms
  selectTimeout.tv_usec = 0; //100ms

  // Call select() and wait 100ms for it to complete.
  int selRetVal = select( m_maxSd + 1, &workingSet, NULL, NULL, &selectTimeout );

  // Check to see if the select call failed.
  if (selRetVal < 0)
  {
    AIS_LOG_ERROR( "Socket Select Failed: %s", strerror(errno) );
    close(m_socketFd);
    m_socketFd = -1;
    return false;
  }

  // No FD's ready to read, simply exit the update loop.
  if (selRetVal == 0)
  {
    AIS_LOG_INFO("Select indicated no work to do...");
    return true;
  }

  // One or more descriptors are readable.  Need to
  // determine which ones they are.
  int desc_ready = selRetVal;
  for ( int i = 0; i <= m_maxSd  &&  desc_ready > 0; ++i )
  {
     // Check to see if this descriptor is ready
     if ( FD_ISSET(i, &workingSet) )
     {
        // A descriptor was found that was readable - one
        // less has to be looked for.  This is being done
        // so that we can stop looking at the working set
        // once we have found all of the descriptors that
        // were ready.
        desc_ready -= 1;

        // Check to see if this is the listening socket
        if (i == m_socketFd)
        {
           AIS_LOG_INFO("Listening Socket is Readable");
           // Accept all incoming connections that are
           // queued up on the listening socket before we
           // loop back and call select again.
           int new_sd = 0;
           do
           {
              // Accept each incoming connection.  If
              // accept fails with EWOULDBLOCK, then we
              // have accepted all of them.  Any other
              // failure on accept will cause us to end the
              // server.
              new_sd = accept(m_socketFd, NULL, NULL);
              if (new_sd < 0)
              {
                 if (errno != EWOULDBLOCK)
                 {
                   AIS_LOG_ERROR( "Socket Accept Failed: %s", strerror(errno) );
                   close(m_socketFd);
                   m_socketFd = -1;
                   return false;
                 }
                 break;
              }

              // Add the new incoming connection to the
              // master read set
              AIS_LOG_INFO( "New Incoming Read Connection - %d", new_sd );
              FD_SET(new_sd, &m_masterFdSet);
              if (new_sd > m_maxSd)
                m_maxSd = new_sd;

              // Loop back up and accept another incoming
              // connection
           } while ( new_sd != -1 );
        } else //This is not the listening socket, therefore an existing connection must be readable
        {
           AIS_LOG_INFO( "Descriptor %d is readable", i );

           // Receive all incoming data on this socket
           // before we loop back and call select again.
           serviceConnection( i, proc );

           // Since we only ever care about one request at a time, we always
           // want to close this connection after the request was serviced
           // This clean up process includes removing the
           // descriptor from the master set and
           // determining the new maximum descriptor value
           // based on the bits that are still turned on in
           // the master set.
           {
              close( i );
              FD_CLR( i, &m_masterFdSet );
              if (i == m_maxSd)
              {
                 while ( FD_ISSET( m_maxSd, &m_masterFdSet ) == false )
                   m_maxSd -= 1;
              }
           }
        } /* End of existing connection is readable */
     } /* End of if (FD_ISSET(i, &working_set)) */
  } /* End of loop through selectable descriptors */

  return true;
}

bool Jhm2IpcServer::initialized() const
{
  return ( m_socketFd > -1 );
}

bool Jhm2IpcServer::serviceConnection( int connection_fd, Jhm2RequestProcessor& proc )
{
  int numBytesRecvd;

  numBytesRecvd = read(connection_fd, m_buf, JHM2_IPC_MAX_MSG_LEN);
  if ( numBytesRecvd <= 0 )
  {
    AIS_LOG_ERROR( "Received Empty Data or error from Client - %d", numBytesRecvd );
    return false;
  }
  AIS_LOG_INFO( "Read request with %d bytes", numBytesRecvd );

  std::string incomingMsg, outgoingMsg;
  incomingMsg.assign( m_buf, numBytesRecvd );

  if ( !proc.processRequest( incomingMsg, outgoingMsg ) )
  {
    AIS_LOG_ERROR( "Error processing request from Client" );
    return false;
  }

  int numBytesWrote = write(connection_fd, outgoingMsg.c_str(), outgoingMsg.size() );
  if ( numBytesWrote <= 0 )
  {
    AIS_LOG_ERROR( "Error sending response to Client" );
    return false;
  }
  AIS_LOG_INFO( "Wrote Response with %d bytes", numBytesWrote );

  return true;
}


