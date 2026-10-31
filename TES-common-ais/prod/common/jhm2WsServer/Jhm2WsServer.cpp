#include "Jhm2WsServer.h"

using namespace jhm2;
using namespace web_sockets;

namespace rj = rapidjson;

Jhm2WsServer::Jhm2WsServer()
{
}


Jhm2WsServer::~Jhm2WsServer()
{
    stop();
}


const Jhm2WsServer::Connection& Jhm2WsServer::start(Jhm2RequestProcessor& requestProcessor, std::string endPointStr, uint16_t port)
{
    m_Server.config.port = port;
    m_pRequestProcessor = &requestProcessor;

    // Create an endpoint
    auto &endpoint = m_Server.endpoint["^/" + endPointStr];

    AIS_LOG_NOTICE("WS Server: Configured for port %u at endpoint %s", port, endPointStr.c_str());

    // Register the callbacks for the endpoint
    endpoint.on_open = [this](std::shared_ptr<WsServer::Connection> connection) { AIS_LOG_NOTICE("WS Server: Opened connection %p.", connection.get()); };

    endpoint.on_message = [this](std::shared_ptr<WsServer::Connection> connection, std::shared_ptr<WsServer::Message> message) {
        AIS_LOG_NOTICE("WS Server: Received message from connection %p.", connection.get());
        handleMessage(connection, message);
    };

    endpoint.on_error = [this](std::shared_ptr<WsServer::Connection> connection, const SimpleWeb::error_code &ec) { AIS_LOG_ERROR("WS Server: Error in connection %p. Error: %d, error message: %s", connection.get(), ec.value(), ec.message().c_str()); };

    endpoint.on_close = [this](std::shared_ptr<WsServer::Connection> connection, int status, const std::string &reason) { AIS_LOG_NOTICE("WS Server: Closed connection %p with status code %d, reason: %s", connection.get(), status, reason.c_str()); };

    // Kill if currently running
    stop();

    // Start up a new thread for the server
    m_Thread = std::thread([this]() { serve(); });

    m_RequestProcessorConnection.pEndpoint = &endpoint; 
    m_RequestProcessorConnection.active = true;

    return m_RequestProcessorConnection;
}


bool Jhm2WsServer::stop(const Connection& clientConnection)
{
    (void)clientConnection;

    // Kill the server
    m_Server.stop();

    // Wait for it to stop
    if (m_Thread.joinable())
    {
        m_Thread.join();
    }

    m_RequestProcessorConnection.active = false;
    return true;
}


bool Jhm2WsServer::stop()
{
    return stop(m_RequestProcessorConnection);
}


bool Jhm2WsServer::parseMessage(std::shared_ptr<WsServer::Message> &message, RequestEntry& requestEntry, std::string& errorMessage)
{
    auto& request = requestEntry.request;

    auto messageString = message->string();
    AIS_LOG_DEBUG("%s", messageString.c_str());

    rj::Document doc;
    doc.Parse(messageString);
    if (doc.HasParseError())
    {
        errorMessage = "rapidjson unable to parse message";
        return false;
    }

    // Convert JSON to Jhm2ParamMsgRequest
    request.m_requestType = Jhm2ParamMsgRequest::INVALID_REQUEST;

    auto itQueryStrings = doc.FindMember(QUERY_STRINGS_KEY);
    if (itQueryStrings == doc.MemberEnd() || !itQueryStrings->value.IsObject())
    {
        errorMessage = "unable to parse " + std::string(QUERY_STRINGS_KEY);
        return false;
    }

    // Parse request type
    auto itRequestType = itQueryStrings->value.FindMember(REQUEST_TYPE_KEY);
    if (itRequestType == itQueryStrings->value.MemberEnd() || !itRequestType->value.IsString())
    {
        errorMessage = "unable to parse " + std::string(REQUEST_TYPE_KEY);
        return false;
    }

    auto requestTypeStr = itRequestType->value.GetString();
    request.m_requestType = getJhm2RequestType(requestTypeStr);
    if (request.m_requestType == Jhm2ParamMsgRequest::INVALID_REQUEST)
    {
        errorMessage = "unable to parse " + std::string(REQUEST_TYPE_KEY);
        return false;
    }
    switch (request.m_requestType)
    {
    case Jhm2ParamMsgRequest::PARAMETER_MSG_REQUEST_2:
    case Jhm2ParamMsgRequest::COMMAND_MSG_REQUEST_2:
        request.m_inputFormat = Jhm2ParamMsgRequest::JSON_FORMAT_2;
        break;
    
    default:
        request.m_inputFormat = Jhm2ParamMsgRequest::JSON_FORMAT;
        break;
    }
    request.m_outputFormat = request.m_inputFormat;

    // Parse ParameterRequest or FileRequest
    if (request.m_requestType == Jhm2ParamMsgRequest::PARAMETER_MSG_REQUEST ||
        request.m_requestType == Jhm2ParamMsgRequest::PARAMETER_MSG_REQUEST_2 ||
        request.m_requestType == Jhm2ParamMsgRequest::FILE_MSG_REQUEST)
    {
        // Parse wsRequestType
        auto itWsRequestType = doc.FindMember(WS_REQUEST_TYPE_KEY);
        if (itWsRequestType == doc.MemberEnd() || !itWsRequestType->value.IsString())
        {
            errorMessage = "unable to parse " + std::string(WS_REQUEST_TYPE_KEY);
            return false;
        }
        auto wsRequestTypeCstr = itWsRequestType->value.GetString();
        Jhm2WebSocketRequest::Jhm2WsRequestType wsRequestType{getWsRequestType(wsRequestTypeCstr)};
        if (wsRequestType == Jhm2WebSocketRequest::WS_REQUEST_UNKNOWN)
        {
            errorMessage = "Invalid " + std::string(WS_REQUEST_TYPE_KEY) + ": " + std::string(wsRequestTypeCstr);
            return false;
        }
        AIS_LOG_DEBUG("wsRequestType set to %u (%s)", wsRequestType, wsRequestTypeCstr);

        // Check that paramsRequested or fileRequested is included
        auto itRequest = (request.m_requestType == Jhm2ParamMsgRequest::FILE_MSG_REQUEST) ? itQueryStrings->value.FindMember(FILEREQUESTED_KEY) : 
                          itQueryStrings->value.FindMember(PARAMSREQUESTED_KEY);

        if (itRequest == itQueryStrings->value.MemberEnd())
        {
            errorMessage = "unable to find " + std::string(PARAMSREQUESTED_KEY) + " or " + std::string(FILEREQUESTED_KEY);
            return false;
        }

        std::string requestKey;

        // Parse fileRequested
        if  (request.m_requestType == Jhm2ParamMsgRequest::FILE_MSG_REQUEST)
        {
            if (!itRequest->value.IsString())
            {
                errorMessage = "unable to parse " + std::string(FILEREQUESTED_KEY);
                return false;
            }
            auto valueCstr = itRequest->value.GetString();
            AIS_LOG_DEBUG("Added \"%s\" entry:\"%s\" to request", FILEREQUESTED_KEY, valueCstr);
            request.m_reqData.insert(Jhm2ParamMsgRequest::ReqDataMapElemT{FILEREQUESTED_KEY, Jhm2ParamMsgRequest::ReqDataT{valueCstr}});

            // Generate file key
            requestKey = valueCstr;
        }
        // Parse paramsRequested
        else
        {
            if (!itRequest->value.IsArray())
            {
                errorMessage = "unable to parse " + std::string(PARAMSREQUESTED_KEY);
                return false;
            }
            Jhm2ParamMsgRequest::ReqDataT array;
            std::vector<std::string> paramsRequested;
            for (auto itParam = itRequest->value.Begin(); itParam != itRequest->value.End(); ++itParam)
            {
                if (!itParam->IsString())
                {
                    errorMessage = "unable to parse " + std::string(PARAMSREQUESTED_KEY);
                    return false;
                }
                auto valueCstr = itParam->GetString();
                array.insert(valueCstr);
                AIS_LOG_DEBUG("Added \"%s\" array entry:\"%s\" to request", PARAMSREQUESTED_KEY, valueCstr);
                paramsRequested.push_back(valueCstr);
            }
            request.m_reqData.insert(Jhm2ParamMsgRequest::ReqDataMapElemT{PARAMSREQUESTED_KEY, std::move(array)});

            // Generate params key
            std::sort(paramsRequested.begin(), paramsRequested.end());
            for (auto& paramRequested : paramsRequested)
            {
                requestKey += paramRequested;
            }
        }

        // Parse wsRequestType
        switch (wsRequestType)
        {
        case Jhm2WebSocketRequest::WS_REQUEST_ADD:
        {
            // Parse rateSec, support either string or number. If not included, assume one-time request
            auto itRateSec = doc.FindMember(RATE_SEC_KEY);
            if (itRateSec != doc.MemberEnd())
            {
                double rateSec{0.0};
                if (itRateSec->value.IsString())
                {
                    auto rateSecCstr = itRateSec->value.GetString();
                    try
                    {
                        rateSec = std::atof(rateSecCstr);
                    }
                    catch(const std::exception& e)
                    {
                        errorMessage = "unable to parse " + std::string(RATE_SEC_KEY);
                        return false;
                    }
                }
                else if (itRateSec->value.IsInt())
                {
                    rateSec = itRateSec->value.GetInt();
                }
                else if (itRateSec->value.IsDouble())
                {
                    rateSec = itRateSec->value.GetDouble();
                }
                else
                {
                    errorMessage = "unable to parse " + std::string(RATE_SEC_KEY);
                    return false;
                }
                AIS_LOG_DEBUG("rateSec set to %f", rateSec);
                if (rateSec < 0.0)
                {
                    errorMessage = "invalid " + std::string(RATE_SEC_KEY);
                    return false;
                }
                else if (rateSec > 0.0)
                {
                    // Add new periodic request or update existing
                    auto rateMsChrono = std::chrono::milliseconds(static_cast<int64_t>(rateSec * 1000));

                    std::lock_guard<std::mutex> lock(m_RequestMutex);
                    {
                        auto itParam = m_PeriodicRequests.find(requestKey);
                        if (itParam != m_PeriodicRequests.end())
                        {
                            itParam->second.rateMs = rateMsChrono;
                            itParam->second.nextTxTimepoint = std::chrono::steady_clock::now();
                        }
                        else
                        {
                            m_PeriodicRequests.emplace(requestKey, PeriodicRequestEntry{std::move(requestEntry), rateMsChrono});
                        }
                        AIS_LOG_DEBUG("%s for %s requested at %f second rate (%u milliseconds)", wsRequestTypeCstr, requestKey.c_str(), rateSec, rateMsChrono.count());
                    }
                    // No error, but don't queue a duplicate request
                    return false;
                }
            }
            break;
        }
        case Jhm2WebSocketRequest::WS_REQUEST_REMOVE:
        {
            // Remove periodic request
            std::lock_guard<std::mutex> lock(m_RequestMutex);
            {
                auto itParam = m_PeriodicRequests.find(requestKey);
                if (itParam == m_PeriodicRequests.end())
                {
                    AIS_LOG_NOTICE("%s requested for %s but not found", wsRequestTypeCstr, requestKey.c_str());
                }
                else
                {
                    m_PeriodicRequests.erase(itParam);
                    AIS_LOG_DEBUG("%s for %s processed", wsRequestTypeCstr, requestKey.c_str());
                }
            }
            sendResponse(requestEntry, HTTP_STATUS_CODE_NO_CONTENT);
            // No error, but don't forward the request
            return false;
        }
        
        case Jhm2WebSocketRequest::WS_REQUEST_CANCEL:
        {
            // Remove all periodic requests
            std::lock_guard<std::mutex> lock(m_RequestMutex);
            {
                m_PeriodicRequests.clear();
            }
            AIS_LOG_DEBUG("%s processed", wsRequestTypeCstr);
            sendResponse(requestEntry, HTTP_STATUS_CODE_NO_CONTENT);
            // No error, but don't forward the request
            return false;
        }
        default:
            break;
        }
    }
    // Parse CommandRequest
    else if (request.m_requestType == Jhm2ParamMsgRequest::COMMAND_MSG_REQUEST ||
             request.m_requestType == Jhm2ParamMsgRequest::COMMAND_MSG_REQUEST_2)
    {
        auto itBody = doc.FindMember(BODY_KEY);
        if (itBody == doc.MemberEnd() || !itBody->value.IsObject())
        {
            errorMessage = "unable to parse " + std::string(BODY_KEY);
            return false;
        }
        // Store full object string
        rj::StringBuffer sb;
        rj::Writer<rj::StringBuffer> writer(sb);
        itBody->value.Accept(writer);
        request.m_reqData.insert(Jhm2ParamMsgRequest::ReqDataMapElemT{COMMANDREQUESTED_KEY, Jhm2ParamMsgRequest::ReqDataT{sb.GetString()}});
        AIS_LOG_DEBUG("Added \"%s\" entry:\"%s\" to request", COMMANDREQUESTED_KEY, sb.GetString());
    }
    else
    {
        errorMessage = "unsupported requestType: " + std::string(jhm2RequestTypeToCstr(request.m_requestType));
        return false;
    }
    return true;
}


void Jhm2WsServer::handleMessage(std::shared_ptr<WsServer::Connection> &connection, std::shared_ptr<WsServer::Message> &message)
{
    RequestEntry requestEntry{connection};
    std::string errorMessage;
    if (!parseMessage(message, requestEntry, errorMessage))
    {
        // If there was an error, send a response with the errorMessage
        if (!errorMessage.empty())
        {
            AIS_LOG_ERROR("parseMessage failed: %s", errorMessage.c_str());
            rj::StringBuffer sb;
            rj::PrettyWriter<rj::StringBuffer> writer(sb);
            writer.SetIndent(' ', 2);
            writer.StartObject();
            {
                writer.Key("error");
                writer.String(errorMessage.c_str());
            }
            writer.EndObject();

            sendResponse(requestEntry, HTTP_STATUS_CODE_BAD_REQUEST, sb.GetString());
        }
        return;
    }

    // Add to queue
    std::lock_guard<std::mutex> lock(m_RequestMutex);
    m_Requests.emplace(std::move(requestEntry));
}

void Jhm2WsServer::sendResponse(RequestEntry& requestEntry, uint32_t httpStatusCode, const std::string& body)
{
    auto requestType = requestEntry.request.m_requestType;
    auto requestTypeCstr = jhm2RequestTypeToCstr(requestType);

    // Build a json document
    rj::StringBuffer sb;
    rj::PrettyWriter<rj::StringBuffer> writer(sb);
    writer.SetMaxDecimalPlaces(10);
    writer.SetIndent(' ', 2);
    writer.StartObject();
    {
        writer.Key(RESPONSE_TYPE_KEY);
        writer.String(requestTypeCstr);

        auto& reqData = requestEntry.request.m_reqData;
        if (requestType == Jhm2ParamMsgRequest::FILE_MSG_REQUEST)
        {
            auto it = reqData.find(FILEREQUESTED_KEY);
            if ((it != reqData.end()) && (!it->second.empty()))
            {
                // Only 1 file can be requested at a time
                writer.Key(FILEREQUESTED_KEY);
                writer.String(*it->second.begin());
            }
        }
        else // PARAMETER_MSG_REQUEST, PARAMETER_MSG_REQUEST_2
        {
            auto it = reqData.find(PARAMSREQUESTED_KEY);
            if ((it != reqData.end()) && (!it->second.empty()))
            {
                // Parameters are requested in an array
                writer.Key(PARAMSREQUESTED_KEY);
                writer.StartArray();
                {
                    for (auto& param : it->second)
                    {
                        writer.String(param);
                    }
                }
                writer.EndArray();
            }
        }

        writer.Key(BODY_KEY);
        // If body is not valid JSON, enter empty string and flag as an error
        {
            rj::Document doc;
            doc.Parse(body);
            if (doc.HasParseError())
            {
                AIS_LOG_NOTICE("Invalid JSON in response body: %s", body.c_str());
                writer.String("");
                httpStatusCode = HTTP_STATUS_CODE_INTERNAL_SERVER_ERROR;
            }
            else
            {   
                if (doc.ObjectEmpty())
                {
                    httpStatusCode = HTTP_STATUS_CODE_NO_CONTENT;
                }
                writer.RawValue(body.c_str(), body.size(), rj::kObjectType);
            }
        }

        writer.Key(HTTP_STATUS_CODE_KEY);
        writer.Uint(httpStatusCode);
    }
    writer.EndObject();

    if (writer.IsComplete())
    {
        auto ss = std::make_shared<WsServer::SendStream>();
        *ss << sb.GetString();
        requestEntry.connection->send(ss);
        AIS_LOG_DEBUG("Responding to requestType %s with HTTP Status code %u Message: %s", requestTypeCstr, httpStatusCode, sb.GetString());
    }
    else
    {
        AIS_LOG_ERROR("Response to requestType %s failed with JSON parsing error", requestTypeCstr);
    }
}


void Jhm2WsServer::sendToRequestProcessor(RequestEntry& requestEntry)
{
    std::string response;
    auto success = m_pRequestProcessor->processRequest(requestEntry.request, response);
    auto httpStatusCode = !success                               ?  HTTP_STATUS_CODE_BAD_REQUEST :
                          (response.empty() || response == "{}") ?  HTTP_STATUS_CODE_NO_CONTENT :
                                                                    HTTP_STATUS_CODE_OK;
    sendResponse(requestEntry, httpStatusCode, response);
}


void Jhm2WsServer::serve()
{
    AIS_LOG_NOTICE("WS Server: serving...");

    try
    {
        m_Server.start();
    }
    catch (...)
    {
        AIS_LOG_ERROR("WebServer Exception");
    }

    AIS_LOG_WARN("WS Server: server stopped.");
}


bool Jhm2WsServer::update()
{
    auto timePointNow = std::chrono::steady_clock::now();
    std::lock_guard<std::mutex> lock(m_RequestMutex);

    // Check if any periodic request timers have expired
    for (auto& kv : m_PeriodicRequests)
    {
        auto& entry = kv.second;
        if (timePointNow >= entry.nextTxTimepoint)
        {
            entry.nextTxTimepoint = timePointNow + entry.rateMs;
            sendToRequestProcessor(entry);
        }
    }

    // Send any one-time requests
    while (!m_Requests.empty())
    {
        auto entry = m_Requests.front();
        sendToRequestProcessor(entry);
        m_Requests.pop();
    }
    return true;
}
