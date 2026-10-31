///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2WebSocketProcessor.cpp
/// @author    strubjc
/// @date      Nov 14, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#include <threadUtils/PThreadLocker.h>

#include <ais/log/AisLogger.h>
#include "Jhm2WebSocketProcessor.h"

Jhm2WebSocketProcessor::Jhm2WebSocketProcessor ()
{
  pthread_mutex_init(&m_wsAccessMutex, NULL);
  
}

Jhm2WebSocketProcessor::~Jhm2WebSocketProcessor ()
{
  pthread_mutex_destroy(&m_wsAccessMutex);
}

bool Jhm2WebSocketProcessor::configure( TaskParser& cp )
{

  return true;
}

bool Jhm2WebSocketProcessor::update( )
{
  {
    PThreadLocker lock(&m_wsAccessMutex);

    //Service the web sockets
    for ( unsigned int i = 0; i < m_activeWebSockets.size(); ++i )
    {
      m_activeWebSockets.at(i)->serviceConnection(i);
    }
  }

  return true; // Compilation warnings
}

void Jhm2WebSocketProcessor::sendToAllActiveWebSockets( const std::string& data )
{
  PThreadLocker lock(&m_wsAccessMutex);

  for ( unsigned int i = 0; i < m_activeWebSockets.size(); ++i )
  {
    m_activeWebSockets.at(i)->sendData(data);
  }

}

void Jhm2WebSocketProcessor::addNewConnection( mg_connection* connection )
{
  PThreadLocker lock(&m_wsAccessMutex);

  //New websocket connection, create and attach handler
  m_activeWebSockets.push_back(getNewHandler(connection));

  AIS_LOG_NOTICE("Added websocket id %u [WS Count=%u]", m_activeWebSockets.size() - 1, m_activeWebSockets.size() );
}

void Jhm2WebSocketProcessor::processWebsocketFrame( mg_connection* connection, struct websocket_message* frame )
{
  PThreadLocker lock(&m_wsAccessMutex);

  // New websocket message. Send to appropriate handler
  for ( unsigned int i = 0; i < m_activeWebSockets.size(); ++i )
  {
    if ( m_activeWebSockets.at(i)->isThisConnection( connection ) )
    {
      m_activeWebSockets.at(i)->handleNewData( frame->data, frame->size );
      AIS_LOG_NOTICE("Found active ws handler %u", i);
    }
  }
}

void Jhm2WebSocketProcessor::closeConnection( mg_connection* connection )
{
  //And Remove appropriate handler
  for ( WsHandlerList::iterator it = m_activeWebSockets.begin(); it != m_activeWebSockets.end(); ++it )
  {
    if ( (*it)->isThisConnection( connection ) )
    {
      delete (*it);
      m_activeWebSockets.erase(it);
      AIS_LOG_NOTICE("Found active ws handler to disconnect [WS Count=%u]", m_activeWebSockets.size());
    }
  }
}

jhm2::Jhm2WebSocketHandler* Jhm2WebSocketProcessor::getNewHandler( mg_connection* connection )
{
  return new jhm2::Jhm2WebSocketHandler( connection );
}



