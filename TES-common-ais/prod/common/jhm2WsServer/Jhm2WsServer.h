#ifndef JHM2WSSERVER_H
#define JHM2WSSERVER_H

#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <vector>

#include <ais/log/AisLogger.h>
#include <jhm2/Jhm2Keys.h>
#include <jhm2/Jhm2RequestProcessor/Jhm2RequestProcessor.h>

// Need to include <cstdlib> because <server_ws.hpp> needs it but doesn't include it.
#include <Simple-WebSocket-Server/server_ws.hpp>
#include <cstdlib>

#include "interfaces/JSON/jsonable.h"

#include <chrono/print.hpp>

namespace web_sockets {

class Jhm2WsServer
{
public:
    using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;

    // Prevent requestProcessor from accessing WsServer::Connection
    struct Connection
    {
        friend class Jhm2WsServer;
        bool isActive() const { return active; }
    private:
        bool active{false};
        SimpleWeb::SocketServerBase<SimpleWeb::WS>::Endpoint* pEndpoint{nullptr};
    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor
    ///////////////////////////////////////////////////////////////////////////////
    Jhm2WsServer();
    ~Jhm2WsServer();

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Start the server. NOTE: currently only a single requestProcessor is supported
    /// @param[in] requestProcessor Jhm2RequestProcessor&
    /// @param[in] endPoint Endpoint of the server
    ///            e.g. for http:://165.26.79.19/cpm, endpoint should be "cpm"
    /// @param[out] connection connection handle
    /// @param[in] port Server port, defaults to 443 (HTTPS)
    /// @return Connection with isActive() == true if successful, false otherwise
    ///////////////////////////////////////////////////////////////////////////////
    const Connection& start(Jhm2RequestProcessor& requestProcessor, std::string endPoint, uint16_t port = 443);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Stop the server
    /// @param[in] requestProcessorConnection connection handle
    /// @return true if successful, false otherwise
    ///////////////////////////////////////////////////////////////////////////////
    bool stop(const Connection& requestProcessorConnection);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Call in the main executive thread of the AIS task
    /// @return true if successful, false otherwise
    ///////////////////////////////////////////////////////////////////////////////
    bool update();

private:
    struct RequestEntry
    {
        RequestEntry(std::shared_ptr<WsServer::Connection>& connection) :
            connection{connection}
        {}

        RequestEntry(std::shared_ptr<WsServer::Connection>& connection, Jhm2ParamMsgRequest&& request) :
            connection{connection},
            request{std::move(request)}
        {}

        std::shared_ptr<WsServer::Connection> connection;
        Jhm2ParamMsgRequest request;
    };

    struct PeriodicRequestEntry : public RequestEntry
    {
        PeriodicRequestEntry(RequestEntry&& requestEntry, std::chrono::milliseconds rateMs) :
            RequestEntry{std::move(requestEntry)},
            rateMs{rateMs},
            nextTxTimepoint{std::chrono::steady_clock::now()}
        {}
        std::chrono::milliseconds rateMs;
        std::chrono::steady_clock::time_point nextTxTimepoint;
    };

    // Non-copyable
    Jhm2WsServer(const Jhm2WsServer&) = delete;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief callback function for Simple WebSocket Server for handling requests
    /// @param[in] connection connection
    /// @param[in] message message
    ///////////////////////////////////////////////////////////////////////////////
    void handleMessage(std::shared_ptr<WsServer::Connection> &connection, std::shared_ptr<WsServer::Message> &message);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief helper function for handleMessage
    /// @param[in] message message
    /// @param[out] requestEntry request info
    /// @param[out] errorMessage empty if no error occured, otherwise an errorMessage that should be sent as response to the client
    /// @return true if request should be queued for the RequestProcessor, false otherwise
    ///////////////////////////////////////////////////////////////////////////////
    bool parseMessage(std::shared_ptr<WsServer::Message> &message, RequestEntry& requestEntry, std::string& errorMessage);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief called periodically during update to service requets
    /// @param[in] requestEntry request info
    ///////////////////////////////////////////////////////////////////////////////
    void sendToRequestProcessor(RequestEntry& requestEntry);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Send response to client
    /// @param[in] requestEntry request info
    /// @param[in] httpStatusCode status code
    /// @param[in] body body
    ///////////////////////////////////////////////////////////////////////////////
    void sendResponse(RequestEntry& requestEntry, uint32_t httpStatusCode, const std::string& body = "{}");

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Start the server.
    ///////////////////////////////////////////////////////////////////////////////
    void serve();

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Stop the server.
    /// @return true if successful, false otherwise
    ///////////////////////////////////////////////////////////////////////////////
    bool stop();

    std::thread m_Thread;

    WsServer m_Server;

    std::mutex m_RequestMutex;

    // Periodic requests, lookup based on parameter name(s) or file name
    std::unordered_map<std::string, PeriodicRequestEntry> m_PeriodicRequests;

    // One-Time requests
    std::queue<RequestEntry> m_Requests;

    // NOTE: Only a single connection/requestProcessor is supported
    Connection m_RequestProcessorConnection;
    Jhm2RequestProcessor* m_pRequestProcessor;
};

}

#endif
