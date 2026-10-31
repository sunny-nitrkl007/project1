///////////////////////////////////////////////////////////////////////////////
/// @file      jhm2CgiApp.cpp
/// @author    Josh Struble
/// @date      Mar 18, 2013
/// @brief     CGI app intended to serve parameters to a javascript page
///
/// @attention Copyright (C) 2013
/// @attention Caterpillar, Inc.
///////////////////////////////////////////////////////////////////////////////
#include <boost/cgi/cgi.hpp>
#include <Jhm2RequestBuilder/Jhm2RequestBuilder.h>
#include "boost/property_tree/json_parser.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>

namespace cgi = boost::cgi;

const std::string requestTypeKey("requestType");
const std::string outputFormatKey("outputFormat");
const std::string jsonKey("JSON");

void expandString( const std::string &input, std::set<std::string> &output )
{
  std::stringstream ss(input);
  output.clear();
  while (ss)
  {
    std::string val;
    if (!getline( ss, val, ',')) break;
    output.insert(val);
  }
}

Jhm2ParamMsgRequest::eRequestType getRequestType( cgi::request& req, std::string& errorString )
{
  //request type key must only be included once, and must always be included
  if ( req.get.count(requestTypeKey.c_str()) == 1 )
  {
    std::set<std::string> reqType;
    expandString( std::string(req.get[requestTypeKey.c_str()]), reqType );
    //Number of requests type values must also be one
    if ( reqType.size() == 1 )
    {
      std::set<std::string>::iterator it = reqType.begin();
      if (*it == "ParameterRequest2") {
          return Jhm2ParamMsgRequest::PARAMETER_MSG_REQUEST_2;
      }
      else if (*it == "CommandRequest2") {
          return Jhm2ParamMsgRequest::COMMAND_MSG_REQUEST_2;
      }
      else if (*it == "FileRequest") {
          return Jhm2ParamMsgRequest::FILE_MSG_REQUEST;
      }
      else if (*it == "ParameterRequest") {
          return Jhm2ParamMsgRequest::PARAMETER_MSG_REQUEST;
      }
      else if (*it == "CommandRequest") {
          return Jhm2ParamMsgRequest::COMMAND_MSG_REQUEST;
      }
      else if (*it == "ImageRequest") {
          return Jhm2ParamMsgRequest::IMAGE_MSG_REQUEST;
      }
      else if (*it == "ChannelUpdate") {
          return Jhm2ParamMsgRequest::CHANNEL_UPDATE_REQUEST;
      }

      errorString = "Invalid Request Type";
      return Jhm2ParamMsgRequest::INVALID_REQUEST;
    }
    else {
      errorString = "Invalid Request Type Value Count";
      return Jhm2ParamMsgRequest::INVALID_REQUEST;
    }
  }

  errorString = "Request Type Error";
  return Jhm2ParamMsgRequest::INVALID_REQUEST;
}

Jhm2ParamMsgRequest::eFormat getOutputFormat( cgi::request& req )
{
  if ( req.get.count(outputFormatKey.c_str()) > 0 )
  {
    std::set<std::string> outputFmt;
    expandString( std::string(req.get[outputFormatKey.c_str()]), outputFmt );
    //Number of requests type values must also be one
    if (!outputFmt.empty())
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
  //Default to JSON
  return Jhm2ParamMsgRequest::JSON_FORMAT;
}

void populateParamData( cgi::request& req, Jhm2ParamMsgRequest::ReqDataMapT& data )
{
  cgi::get_map::iterator it;
  for ( it = req.get.begin(); it != req.get.end(); ++it )
  {
    Jhm2ParamMsgRequest::ReqDataT newData;
    expandString(it->second, newData);
    data.insert(Jhm2ParamMsgRequest::ReqDataMapElemT(std::string(it->first.c_str()), newData));
  }
}

void populateCmdData( std::string req, Jhm2ParamMsgRequest::ReqDataMapT& data )
{
  Jhm2ParamMsgRequest::ReqDataT newData;
  newData.insert(req);
  (data)["commandRequested"] = newData;
}

void populateErrorResponse( cgi::response& resp, Jhm2ParamMsgRequest::eFormat format, const std::string& errorString )
{
  if ( format == Jhm2ParamMsgRequest::JSON_FORMAT )
  {
    resp << cgi::content_type("application/json");
    resp << "{ \"Error\": \"" << errorString << "\" }";

  } else
  {
    resp << cgi::content_type("text/xml");
    resp << "<?xml version=\"1.0\"?>";
    resp << "<Error>" << errorString << "</Error>";
  }
}

void populateResponse( cgi::response& resp, Jhm2RequestBuilder& builder )
{
  switch( builder.requestMsg().m_outputFormat )
  {
    case Jhm2ParamMsgRequest::XML_FORMAT:
      resp << cgi::content_type("text/xml");
      resp << "<?xml version=\"1.0\"?>";
      resp << builder.responseData();
      break;
    case Jhm2ParamMsgRequest::JSON_FORMAT:
      resp << cgi::content_type("application/json; charset=utf-8");
      resp << builder.responseData();
      break;
    case Jhm2ParamMsgRequest::JPG_FORMAT:
      resp << cgi::content_type("image/jpg");
      resp << builder.responseData();
      break;
    default:
      populateErrorResponse( resp, builder.requestMsg().m_outputFormat, "Invalid Output Format" );
      break;
  }
}

int main()
{
    boost::system::error_code ec;
    cgi::request req(ec);
    cgi::response resp;
    Jhm2RequestBuilder reqBuilder;

    // Set the output format
    reqBuilder.requestMsg().m_outputFormat = getOutputFormat(req);

    { // Set the request type
        std::string errorString;

        reqBuilder.requestMsg().m_requestType = getRequestType(req, errorString);

        if (reqBuilder.requestMsg().m_requestType == Jhm2ParamMsgRequest::INVALID_REQUEST) {
            //Invalid request
            resp << boost::cgi::common::http::status_code::bad_request;
            populateErrorResponse(resp, reqBuilder.requestMsg().m_outputFormat, errorString);
            return cgi::commit(req, resp);
        }
    }

    // Add the post data
    reqBuilder.requestMsg().m_postData = req.post_buffer();

    std::string str(reqBuilder.requestMsg().m_postData);

    // Populate the parameter data
    populateParamData(req, reqBuilder.requestMsg().m_reqData);

    if (!str.empty()) {
        populateCmdData(str, reqBuilder.requestMsg().m_reqData);
    }

    // Finally send off the request
    if (!reqBuilder.sendRequest()) {
        // The request didn't work, return an error
        resp << boost::cgi::common::http::status_code::internal_server_error;
        populateErrorResponse(resp, reqBuilder.requestMsg().m_outputFormat, reqBuilder.responseData());
        return cgi::commit(req, resp);
    }

    // Response must have been good, formulate the response data
    populateResponse(resp, reqBuilder);

    // Finally, send the response to the client that made the request.
    return cgi::commit(req, resp);

}


