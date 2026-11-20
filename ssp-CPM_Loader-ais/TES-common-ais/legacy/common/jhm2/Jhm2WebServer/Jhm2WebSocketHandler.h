///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2WebSocketHandler.h
/// @author    strubjc
/// @date      Apr 1, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2WEBSOCKETHANDLER_H_
#define JHM2WEBSOCKETHANDLER_H_

#include <ais/time/TimeStamp.h>
#include "../Jhm2WebServer/mongoose/mongoose.h"

namespace jhm2
{
  
  class Jhm2WebSocketHandler
  {
    public:
      Jhm2WebSocketHandler ( mg_connection* connection );
      virtual ~Jhm2WebSocketHandler ();

      void handleNewData(const unsigned char* data, unsigned int dataSize);
      bool isThisConnection( mg_connection* connection );

      bool serviceConnection(const unsigned int& id);

      bool sendData( const std::string& data );

    private:
      mg_connection*  m_pConnection;
      TimeStamp       m_lastSend;

  };

} /* namespace jhm2 */

#endif /* JHM2WEBSOCKETHANDLER_H_ */
