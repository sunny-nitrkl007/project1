///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2WebServer.cpp
/// @author    strubjc
/// @date      Apr 1, 2016
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#include "Jhm2WebServer.h"
#include <ais/config/ConfigSection.h>
#include <ais/log/AisLogger.h>
#include <ais/time/GetTime.h>
#include <ais/time/Timer.h>
#include <ais/util/threadName.h>
#include <threadUtils/PThreadLocker.h>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>

namespace jhm2
{
  Jhm2WebServer::Jhm2WebServer ():
    m_plisteningConnection(NULL),
    m_wsProc(NULL),
    m_wsAccessMutex(),
    m_httpPort("8000"),
    m_documentRoot("/home/pf/software/www"),
    m_enableCgi(false),
    m_cgiPattern(""),
    m_maxSleepTime_ms(0.01 * 1000),
    m_pServerThreadHandle(NULL),
    m_runServerThread(false)
  {
  }
  
  Jhm2WebServer::~Jhm2WebServer ()
  {
    pthread_mutex_destroy(&m_wsAccessMutex);
  }

  bool Jhm2WebServer::initialize( TaskParser& cp )
  {
    ConfigSection cs;
    if (!cp.getSection("Jhm2WebServer", cs))
    {
      AIS_LOG_FATAL("Could not find config section Jhm2WebServer");
      return false;
    }

    if (!cs.get("httpPort", m_httpPort))
    {
      AIS_LOG_FATAL("Could not find httpPort key in Jhm2WebServer config section");
      return false;
    }

    if (!cs.get("documentRoot", m_documentRoot))
    {
      AIS_LOG_FATAL("Could not find documentRoot key in Jhm2WebServer config section");
      return false;
    }

    if (!cs.get("maxSleepTime_ms", m_maxSleepTime_ms))
    {
      AIS_LOG_FATAL("Could not find maxSleepTime_ms key in Jhm2WebServer config section");
      return false;
    }

    m_enableCgi = cs.get("cgiPattern", m_cgiPattern);

//    if (m_reqProc)
//    {
//      return m_reqProc->configure(cp);
//    }

    for ( ReqProcMapT::iterator it = m_registeredReqProcs.begin(); it != m_registeredReqProcs.end(); ++it )
    {
      if (!it->second->configure(cp))
      {
        AIS_LOG_FATAL("Error configuring request processor for http endpoint %s", it->first.c_str());
        return false;
      }
    }

    if (m_wsProc)
    {
      if (!m_wsProc->configure(cp))
      {
        AIS_LOG_FATAL("Error configuring websocket processor");
        return false;
      }
    }

    return true;
  }


  bool Jhm2WebServer::registerRequestProcessor( const std::string& uri, Jhm2RequestProcessor* reqProc )
  {
    std::pair<ReqProcMapT::iterator,bool> retVal;
    retVal = m_registeredReqProcs.insert(std::make_pair(uri,reqProc));
    if ( !retVal.second )
    {
      AIS_LOG_FATAL("Trying to register processor with endpoint %s, but one already exists", uri.c_str());
      return false;
    }
    return true;
  }

  bool Jhm2WebServer::registerWsProcessor( const std::string& uri, Jhm2WebSocketProcessor* wsProc )
  {
    if ( m_wsProc )
    {
      AIS_LOG_FATAL("Trying to register WebSocket processor, but one already exists.. Only one websocket handler is currently supported.");
      return false;
    }
    m_wsProc = wsProc;
    return true;
  }

  void Jhm2WebServer::start(bool runInThread)
  {
    mg_mgr_init(&(this->m_mgr), NULL);
    //Event handler has to be static function to be compatible with c style function pointer
    m_plisteningConnection = mg_bind(&(this->m_mgr), m_httpPort.c_str(), &(this->eventHandler) );

    //Register endpoints for request processors, note they are all registered to the same api handler function
    //the uri will be used to decode within the api handler
    for ( ReqProcMapT::iterator it = m_registeredReqProcs.begin(); it != m_registeredReqProcs.end(); ++it )
    {
      AIS_LOG_NOTICE("Registering Endpoint for %s", it->first.c_str());
      mg_register_http_endpoint(m_plisteningConnection, it->first.c_str(), &(this->apiHandler) );
    }


    //Add pointer to this instance to the user data, so we can get to it from static event handler
    m_mgr.user_data = (void *)(this);
    if ( m_enableCgi )
    {
      m_servOpts.cgi_file_pattern = m_cgiPattern.c_str();
    }
    m_servOpts.document_root = m_documentRoot.c_str();
    mg_set_protocol_http_websocket(m_plisteningConnection);

    if (runInThread)
    {
      m_runServerThread = true;
      m_pServerThreadHandle = new boost::thread(boost::bind(&Jhm2WebServer::serverThread, this));
    }

  }

  void Jhm2WebServer::serverThread(void)
  {
    setCurrentThreadName("Jhm2WebServer");
    while ( m_runServerThread )
    {
      //Execute Thread Main
      serverThreadMain();
    }
  }


  void Jhm2WebServer::serverThreadMain(void)
  {
    //Just Run the update function
    update();
  }

  void Jhm2WebServer::serverThreadStop(void)
  {
    //Kill the thread
    m_runServerThread = false;
    //And wait for it to exit
    if (m_pServerThreadHandle)
    {
      m_pServerThreadHandle->join();
    }

    m_pServerThreadHandle = NULL;
  }


  bool Jhm2WebServer::update()
  {

    //Update registered request processors
    for ( ReqProcMapT::iterator it = m_registeredReqProcs.begin(); it != m_registeredReqProcs.end(); ++it )
    {
      it->second->update();
    }

    //Update registered websocket processor
    if ( m_wsProc )
    {
      m_wsProc->update();
    }

    //And Service the Web connections
    mg_mgr_poll(&(this->m_mgr),m_maxSleepTime_ms);

    return true;
  }

  void Jhm2WebServer::cleanup()
  {
    serverThreadStop();
    mg_mgr_free(&(this->m_mgr));
  }

  int Jhm2WebServer::is_equal(const struct mg_str *s1, const struct mg_str *s2)
  {
    return s1->len == s2->len && memcmp(s1->p, s2->p, s2->len) == 0;
  }

  Jhm2ParamMsgRequest::eRequestType Jhm2WebServer::getRequestType( const QueryT& query, std::string& errorString )
  {
    std::string requestTypeKey("requestType");

    //If request type key is included in the query
    if ( query.count(requestTypeKey) )
    {
      const ParamListT& reqType = query.find(requestTypeKey)->second;
      //Number of requests type values must also be one
      if ( reqType.size() == 1 )
      {
        std::set<std::string>::iterator it = reqType.begin();
        if ( *it == "ParameterRequest" )
          return Jhm2ParamMsgRequest::PARAMETER_MSG_REQUEST;

        if ( *it == "ImageRequest" )
          return Jhm2ParamMsgRequest::IMAGE_MSG_REQUEST;

        if ( *it == "CommandRequest" )
          return Jhm2ParamMsgRequest::COMMAND_MSG_REQUEST;

        if ( *it == "ChannelUpdate" )
          return Jhm2ParamMsgRequest::CHANNEL_UPDATE_REQUEST;

        errorString = "Invalid Request Type";
        return Jhm2ParamMsgRequest::INVALID_REQUEST;
      } else
      {
        errorString = "Invalid Request Type Value Count";
        return Jhm2ParamMsgRequest::INVALID_REQUEST;
      }
    }

    errorString = "Request Type Error";
    return Jhm2ParamMsgRequest::INVALID_REQUEST;
  }

  Jhm2ParamMsgRequest::eFormat Jhm2WebServer::getOutputFormat( const QueryT& query )
  {
    std::string outputFormatKey("outputFormat");
    if ( query.count(outputFormatKey) )
    {
      const ParamListT& outputFmt = query.find(outputFormatKey)->second;
      //Number of requests type values must also be one
      if ( outputFmt.size() > 0 )
      {
        std::set<std::string>::iterator it = outputFmt.begin();
        if ( *it == "xml" )
          return Jhm2ParamMsgRequest::XML_FORMAT;

        if ( *it == "json" )
          return Jhm2ParamMsgRequest::JSON_FORMAT;

        if ( *it == "jpg" )
          return Jhm2ParamMsgRequest::JPG_FORMAT;
      }
    }
    //Default to XML
    return Jhm2ParamMsgRequest::XML_FORMAT;
  }

  bool Jhm2WebServer::decodeQuery( const struct mg_str& query, QueryT& decodedQuery )
  {
    std::string queryStr(query.p, query.len);
    boost::char_separator<char> paramSep("&");
    boost::char_separator<char> listSep(",");
    typedef boost::tokenizer<boost::char_separator<char> > tokenizerT;
    tokenizerT params(queryStr, paramSep);

    decodedQuery.clear();

    for ( tokenizerT::iterator it = params.begin(); it != params.end(); ++it )
    {
      //Create the list
      ParamListT listItems;

      //Find the = sign
      std::size_t pos = (*it).find("=");
      if (pos ==  std::string::npos )
      {
        //No equal sign, just add the key with an empty map
        decodedQuery.insert(std::make_pair(*it, listItems));
      } else
      {
        //Get the key
        std::string key = (*it).substr(0,pos);
        //And the value (or list of values)
        std::string val = (*it).substr(pos+1, std::string::npos);
        tokenizerT paramList(val, listSep);
        for ( tokenizerT::iterator it2 = paramList.begin(); it2 != paramList.end(); ++it2 )
        {
          listItems.insert(*it2);
        }
        //Insert into the decoded query
        decodedQuery.insert(std::make_pair(key, listItems));
      }

    }

    return true;
  }

  void Jhm2WebServer::eventHandler( struct mg_connection *nc, int ev, void *ev_data )
  {
    Jhm2WebServer& thisWs = *((Jhm2WebServer*)(nc->mgr->user_data));

    if (ev != 0)
    {
      AIS_LOG_DEBUG("Event Received, type %u", ev);
    }

    switch (ev)
    {
      case MG_EV_HTTP_REQUEST:
      {
        struct http_message *hm = (struct http_message *) ev_data;
        std::string reqMsg(hm->message.p, hm->message.len);
        AIS_LOG_NOTICE("Received html request:");
        AIS_LOG_NOTICE(reqMsg);

        //Usual HTTP request - serve static files
        mg_serve_http(nc, hm, thisWs.m_servOpts);
        break;
      }
      case MG_EV_WEBSOCKET_HANDSHAKE_DONE:
      {
        AIS_LOG_NOTICE("Received ws handshake done" );

        //If we can handle websockets, add a new one
        if ( thisWs.m_wsProc )
        {
          thisWs.m_wsProc->addNewConnection(nc);
        }

        break;
      }
      case MG_EV_WEBSOCKET_FRAME:
      {
        struct websocket_message *wm = (struct websocket_message *) ev_data;
        std::string wsFrame((char*)wm->data, wm->size);
        AIS_LOG_NOTICE("Received websocket frame (flags %u):", wm->flags);
        AIS_LOG_NOTICE(wsFrame);

        //If we can handle websockets, process the frame
        if ( thisWs.m_wsProc )
        {
          thisWs.m_wsProc->processWebsocketFrame(nc, wm);
        }

        break;
      }
      case MG_EV_CLOSE:
      {
        AIS_LOG_NOTICE("Received a disconnect");
        //Disconnect received
        //See if it's a websocket connection
        if (nc->flags & MG_F_IS_WEBSOCKET)
        {
          AIS_LOG_NOTICE("Disconnect is ws close");
          //If we can handle websockets, service this disconnect
          if ( thisWs.m_wsProc )
          {
            thisWs.m_wsProc->closeConnection(nc);
          }
        }
        break;
      }
      default:
        break;
    }
  }

  Jhm2WebServer::ResponseCode Jhm2WebServer::handleNewRequest( const QueryT& req, const std::string& method, const std::string& body, std::stringstream& resp, Jhm2RequestProcessor* reqProc )
  {
    std::string errorString;
    Jhm2ParamMsgRequest reqMsg;

    //Set the request type
    reqMsg.m_requestType = getRequestType( req, errorString );
    if ( reqMsg.m_requestType == Jhm2ParamMsgRequest::INVALID_REQUEST )
    {
      //Invalid request
      return RESP_NotFound;
    }

    //Set the output format
    reqMsg.m_outputFormat = getOutputFormat( req );

    //Populate the parameter data
    reqMsg.m_reqData = req;

    //And Populate the message body (for post data)
    reqMsg.m_postData = body;

    //Process the request using the reqProcessor
    std::string response;
    if ( reqProc->processRequest( reqMsg, response ) )
    {
      resp << response;
      return RESP_Ok;
    }

    //The request didn't work, return an error
    return RESP_InternalServerError;
  }

  bool Jhm2WebServer::getExtraHeaders( const Jhm2ParamMsgRequestStorage::eFormat& outputFormat, std::stringstream& headers )
  {
    headers << "Access-Control-Allow-Origin: *" << "\r\n";
    headers << "Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS" << "\r\n";
    headers << "Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With" << "\r\n";

    switch( outputFormat )
    {
      case Jhm2ParamMsgRequest::XML_FORMAT:
        headers << "Content-type: text/xml";
        break;
      case Jhm2ParamMsgRequest::JSON_FORMAT:
        headers << "Content-type: application/json";
        break;
      case Jhm2ParamMsgRequest::JPG_FORMAT:
        headers << "Content-type: image/jpg";
        break;
      default:
        return false;
    }

    return true;
  }

  void Jhm2WebServer::apiHandler( struct mg_connection *nc, int ev, void *ev_data )
  {
    Jhm2WebServer& thisWs = *((Jhm2WebServer*)(nc->mgr->user_data));

    struct http_message *hm = (struct http_message *) ev_data;
    std::string reqMsg(hm->message.p, hm->message.len);
    AIS_LOG_NOTICE("Received html request at API");
    AIS_LOG_NOTICE(reqMsg);

    std::string uri(hm->uri.p, hm->uri.len);
    std::string body(hm->body.p, hm->body.len);
    std::string method(hm->method.p,hm->method.len);

    if ( thisWs.m_registeredReqProcs.count( uri ) == 0 )
    {
      AIS_LOG_FATAL("Handling registered endpoint %s, but not handler exists", uri.c_str());
      return;
    }

    Jhm2RequestProcessor* thisProc = thisWs.m_registeredReqProcs[uri];

    //If this is an OPTIONS request, just send the headers
    if ( method == "OPTIONS" )
    {
      std::stringstream headers;
      getExtraHeaders( Jhm2ParamMsgRequest::JSON_FORMAT, headers );
      mg_send_head( nc, RESP_Ok, 0, headers.str().c_str() );
      return;
    }

    QueryT request;
    if ( decodeQuery( hm->query_string, request ) )
    {
      std::stringstream response;
      ResponseCode responseCode = handleNewRequest( request, method, body, response, thisProc );
      std::stringstream extraHeaders;
      //Try to apply our extra headers
      if (getExtraHeaders( getOutputFormat(request), extraHeaders ) )
      {
        //Good to go, return the response code from the handleNewRequest above
        mg_send_head( nc, responseCode, response.str().length(), extraHeaders.str().c_str() );
        if ( !response.str().empty() )
        {
          //And send data if any
          mg_send( nc,response.str().c_str(), response.str().length() );
        }
      } else
      {
        //extra headers failed, so output format is incorrect
        mg_send_head(nc,RESP_NotImplemented,0,NULL);
      }
    } else
    {
      //decodeQuery failed, so the formatting is incorrect
      mg_send_head(nc,RESP_BadRequest,0,NULL);
    }
  }

} /* namespace jhm2 */
