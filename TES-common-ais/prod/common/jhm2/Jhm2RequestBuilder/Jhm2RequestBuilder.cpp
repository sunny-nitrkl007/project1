///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2RequestBuilder.cpp
/// @author    strubjc
/// @date      Mar 19, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#include "Jhm2RequestBuilder.h"
#include <ais/log/AisLogger.h>
#include <ais/serialization/TypeSerializer.h>
#include <ais/serialization/TypeRestorer.h>

Jhm2RequestBuilder::Jhm2RequestBuilder():
m_clientInitialized( false ),
m_ipcClient()
{
  std::string socketPath("jhm2CgiLocalSocket");
  if ( m_ipcClient.initialize( socketPath ) )
  {
    m_clientInitialized = true;
  }
}

Jhm2RequestBuilder::Jhm2RequestBuilder(const std::string& socketPath):
  m_clientInitialized( false ),
  m_ipcClient()
{
  if ( m_ipcClient.initialize( socketPath ) )
  {
    m_clientInitialized = true;
  }
}

Jhm2RequestBuilder::~Jhm2RequestBuilder()
{
  // TODO Auto-generated destructor stub
}

Jhm2ParamMsgRequest& Jhm2RequestBuilder::requestMsg()
{
  return m_jhm2RequestMsg;
}

std::string& Jhm2RequestBuilder::responseData()
{
  return m_responseData;
}

bool Jhm2RequestBuilder::sendRequest()
{
  return processRequest( m_jhm2RequestMsg, m_responseData );
}

bool Jhm2RequestBuilder::processRequest( const Jhm2ParamMsgRequest& req, std::string& resp )
{
  if ( !m_clientInitialized )
  {
    resp = "Error sending request to server, client not initialized";
    return false;
  }

  std::string reqMsg;
  TypeSerializer serializer;
  serializer.serializeType( reqMsg, req );

  if ( !m_ipcClient.requestParams( reqMsg, resp ) )
  {
    return false;
  }

  return true;
}

