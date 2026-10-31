///////////////////////////////////////////////////////////////////////////////
/// @file      Jhm2RequestProcessor.cpp
/// @author    strubjc
/// @date      Mar 19, 2013
/// @brief     
///
///
/// @attention COPYRIGHT (C) 2012 CATERPILLAR INC. ALL RIGHTS RESERVED.
///////////////////////////////////////////////////////////////////////////////

#include "Jhm2RequestProcessor.h"
#include <ais/serialization/TypeSerializer.h>
#include <ais/serialization/TypeRestorer.h>
#include <ais/log/AisLogger.h>
#include <stdexcept>

Jhm2RequestProcessor::Jhm2RequestProcessor()
{
  // TODO Auto-generated constructor stub

}

Jhm2RequestProcessor::~Jhm2RequestProcessor()
{
  // TODO Auto-generated destructor stub
}

std::string Jhm2RequestProcessor::getEndpoint() const
{
  return "default";
}

bool Jhm2RequestProcessor::processRequest( const std::string& req, std::string& resp )
{
  Jhm2ParamMsgRequest request;

  try {
    TypeRestorer restorer;
    restorer.restoreType( request, req );
  } catch (const std::exception& e) {
    AIS_LOG_ERROR("Failed to deserialize request: %s", e.what());
    return false;
  }

  return processRequest(request,resp);
}

bool Jhm2RequestProcessor::processRequest( const Jhm2ParamMsgRequest& request, std::string& resp )
{
    auto format = request.m_outputFormat;
    Jhm2Msg* response = getResponse(request);
    if (nullptr == response) {
        //Error processing the request, return failure
        AIS_LOG_ERROR("Request Processor doesn't know how to process this request (%d)", request.m_requestType);
        return false;
    }

    // Use the new JSON format if the new request types were used.
    if ((Jhm2ParamMsgRequestStorage::PARAMETER_MSG_REQUEST_2 == request.m_requestType) &&
            (Jhm2ParamMsgRequestStorage::JSON_FORMAT == request.m_outputFormat)) {
        format = Jhm2ParamMsgRequestStorage::JSON_FORMAT_2;
    }
    else if ((Jhm2ParamMsgRequestStorage::COMMAND_MSG_REQUEST_2 == request.m_requestType) &&
            (Jhm2ParamMsgRequestStorage::JSON_FORMAT == request.m_outputFormat)) {
        format = Jhm2ParamMsgRequestStorage::JSON_FORMAT_2;
    }

    // Data buffer for response text
    std::stringstream ss;
    if (!response->getResponse(format, ss)) {
        //Error, response couldn't be generated
        AIS_LOG_ERROR("Response can't be sent with requested Output Format (%d)", request.m_outputFormat);
        delete response;
        return false;
    }

    // If we got here, everything was good...  Copy over the response data
    resp = ss.str();

    //Cleanup
    delete response;
    response = nullptr;

    //And return success
    return true;
}

