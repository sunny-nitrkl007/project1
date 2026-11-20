///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2WebServer.h
/// @author    strubjc
/// @date      Apr 1, 2016
/// @brief     API Wrapper for Mongoose Web Server providing web socket streams
///            of requested parameter data
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#ifndef JHM2WEBSERVER_H_
#define JHM2WEBSERVER_H_

#include <ais/config/ConfigParser.h>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>
#include <pthread.h>

#include <jhm2/Jhm2RequestProcessor/Jhm2RequestProcessor.h>
#include <jhm2/Jhm2Param/Jhm2ParamMsgRequest.h>
#include "Jhm2WebSocketProcessor.h"
#include "mongoose/mongoose.h"

namespace jhm2
{
  
  class Jhm2WebServer
  {
    public:
      Jhm2WebServer ();
      virtual ~Jhm2WebServer ();

      virtual bool initialize( TaskParser& cp );
      virtual void start(bool runInThread=false);
      virtual bool update();
      virtual void cleanup();

      virtual bool registerRequestProcessor( const std::string& uri, Jhm2RequestProcessor* reqProc );
      virtual bool registerWsProcessor( const std::string& uri, Jhm2WebSocketProcessor* wsProc );

    private:

      //Type Definitions
      typedef Jhm2ParamMsgRequest::ReqDataT     ParamListT;
      typedef Jhm2ParamMsgRequest::ReqDataMapT  QueryT;

      typedef enum
      {
        RESP_Ok = 200,
        RESP_BadRequest = 400,
        RESP_Unauthorized = 401,
        RESP_Forbidden = 403,
        RESP_NotFound = 404,
        RESP_RequestedRangeNotSatisfiable = 416,
        RESP_InternalServerError = 500,
        RESP_NotImplemented = 501,
      } ResponseCode;

      typedef std::map<std::string, Jhm2RequestProcessor*> ReqProcMapT;

      //Utility Functions
      static int is_equal(const struct mg_str *s1, const struct mg_str *s2);
      static Jhm2ParamMsgRequest::eRequestType getRequestType( const QueryT& query, std::string& errorString );
      static Jhm2ParamMsgRequest::eFormat getOutputFormat( const QueryT& query );
      static bool decodeQuery( const struct mg_str& query, QueryT& decodedQuery );
      static ResponseCode handleNewRequest( const QueryT& req, const std::string& method, const std::string& body, std::stringstream& resp, Jhm2RequestProcessor* reqProc );
      static bool getExtraHeaders( const Jhm2ParamMsgRequestStorage::eFormat& outputFormat, std::stringstream& headers );

      //Mongoose Event Handlers
      static void eventHandler( struct mg_connection *nc, int ev, void *ev_data );
      static void apiHandler( struct mg_connection *nc, int ev, void *ev_data );

      //Internal State
      struct mg_mgr                 m_mgr;
      struct mg_connection*         m_plisteningConnection;
      struct mg_serve_http_opts     m_servOpts;
      ReqProcMapT                   m_registeredReqProcs;
      Jhm2WebSocketProcessor*       m_wsProc;
      pthread_mutex_t               m_wsAccessMutex;

      //Configuration
      std::string                   m_httpPort;
      std::string                   m_documentRoot;
      bool                          m_enableCgi;
      std::string                   m_cgiPattern;
      unsigned int                  m_maxSleepTime_ms;

      //ServerThread Stuff
      boost::thread*                m_pServerThreadHandle;
      bool                          m_runServerThread;
      void serverThread(void);
      void serverThreadMain(void);
      void serverThreadStop(void);

  };

} /* namespace jhm2 */

#endif /* JHM2WEBSERVER_H_ */
