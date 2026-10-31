///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2WebSocketProcessor.h
/// @author    strubjc
/// @date      Nov 14, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2WEBSOCKETPROCESSOR_H_
#define JHM2WEBSOCKETPROCESSOR_H_

#include <string>
#include <vector>

#include <ais/config/TaskParser.h>
#include "Jhm2WebSocketHandler.h"
#include "mongoose/mongoose.h"

class Jhm2WebSocketProcessor
{
  public:
    Jhm2WebSocketProcessor ();
    virtual ~Jhm2WebSocketProcessor ();

    virtual bool configure( TaskParser& cp );
    virtual bool update( );
    virtual void sendToAllActiveWebSockets( const std::string& data );
    virtual void addNewConnection( mg_connection* connection );
    virtual void processWebsocketFrame( mg_connection* connection, struct websocket_message* frame );
    virtual void closeConnection( mg_connection* connection );

  protected:
    virtual jhm2::Jhm2WebSocketHandler* getNewHandler( mg_connection* connection );

  private:
    typedef std::vector<jhm2::Jhm2WebSocketHandler*> WsHandlerList;

    WsHandlerList   m_activeWebSockets;
    pthread_mutex_t m_wsAccessMutex;

};

#endif /* JHM2WEBSOCKETPROCESSOR_H_ */
