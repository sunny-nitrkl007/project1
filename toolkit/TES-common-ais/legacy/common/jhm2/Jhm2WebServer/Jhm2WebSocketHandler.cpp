///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2WebSocketHandler.cpp
/// @author    strubjc
/// @date      Apr 1, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#include "../Jhm2WebServer/Jhm2WebSocketHandler.h"

#include <ais/time/GetTime.h>
#include <ais/log/AisLogger.h>

namespace jhm2
{
  
  Jhm2WebSocketHandler::Jhm2WebSocketHandler (mg_connection* connection):
      m_pConnection( connection ),
      m_lastSend( localhostNow() )
  {
  }
  
  Jhm2WebSocketHandler::~Jhm2WebSocketHandler ()
  {
  }

  void Jhm2WebSocketHandler::handleNewData(const unsigned char* data, unsigned int dataSize)
  {
    AIS_LOG_NOTICE("Received WebSocket Data:");
    std::string newData((const char*)data,dataSize);
    AIS_LOG_NOTICE(newData);
  }

  bool Jhm2WebSocketHandler::isThisConnection( mg_connection* connection )
  {
    return ( ( m_pConnection != NULL ) &&
             ( connection != NULL ) &&
             ( m_pConnection == connection ) );
  }

  bool Jhm2WebSocketHandler::serviceConnection(const unsigned int& id)
  {
    //Check that this connection is still good
    if ( m_pConnection == NULL )
    {
      return false;
    }

//    TimeStamp timeNow = localhostNow();
//    //If it's time to send, send some data
//    if ( ( timeNow - m_lastSend ).toDouble() > 0.5 )
//    {
//      char buf[500];
//      snprintf(buf,500,"{tempVal: 65, id: %u}", id);
//      AIS_LOG_FATAL("Sending Websocket to %u", id);
//      mg_send_websocket_frame(m_pConnection, WEBSOCKET_OP_TEXT, buf, strlen(buf));
//      m_lastSend = timeNow;
//    }

    return true;
  }

  bool Jhm2WebSocketHandler::sendData( const std::string& data )
  {
    //Check that this connection is still good
    if ( m_pConnection == NULL )
    {
      return false;
    }
    mg_send_websocket_frame( m_pConnection, WEBSOCKET_OP_TEXT, data.c_str(), data.size() );
    return true;
  }

} /* namespace jhm2 */
