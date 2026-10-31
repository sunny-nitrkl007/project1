#ifndef COACHINGTASK_SERVER_H
#define COACHINGTASK_SERVER_H

#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <ais/log/AisLogger.h>

// Need to include <cstdlib> because <server_ws.hpp> needs it but doesn't include it.
#include <Simple-WebSocket-Server/server_ws.hpp>
#include <cstdlib>

#include "interfaces/JSON/jsonable.h"

#include <chrono/print.hpp>

#include "CoachingTaskWsInterface.h"

namespace coaching_task
{

class Server
{
public:
    using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;

    Server(IWsApp *pApp) : Server(pApp, 8080) {}

    Server(IWsApp *pApp, uint16_t port, const std::string &loaderCode = "") : t(), server(), pApp(pApp)
    {
        server.config.port = port;

        AIS_LOG_NOTICE("WS Server: Configured for port %d", port);

        // Create an endpoint
        auto &endpoint = server.endpoint[ENDPOINT];

        // Register the callbacks for the endpoint
        endpoint.on_open = [this](std::shared_ptr<WsServer::Connection> connection) { AIS_LOG_NOTICE("WS Server: Opened connection %p.", connection.get()); };

        endpoint.on_message = [this](std::shared_ptr<WsServer::Connection> connection, std::shared_ptr<WsServer::Message> message) {
            AIS_LOG_NOTICE("WS Server: Received message from connection %p.", connection.get());
            handleMessage(connection, message);
        };

        endpoint.on_error = [this](std::shared_ptr<WsServer::Connection> connection, const SimpleWeb::error_code &ec) { AIS_LOG_ERROR("WS Server: Error in connection %p. Error: %d, error message: %s", connection.get(), ec.value(), ec.message().c_str()); };

        endpoint.on_close = [this](std::shared_ptr<WsServer::Connection> connection, int status, const std::string &reason) { AIS_LOG_NOTICE("WS Server: Closed connection %p with status code %d, reason: %s", connection.get(), status, reason.c_str()); };
    }

    ~Server() { stop(); }

    /*
     * Start the server
     */
    bool start()
    {
        stop(); // Kill if currently running

        // Start up a new thread for the server
        t = std::thread([this]() { serve(); });

        return true;
    }

    /*
     * Stop the server
     */
    bool stop()
    {
        // Kill the server
        server.stop();

        // Wait for it to stop
        if (t.joinable())
        {
            t.join();
        }

        return true;
    }

    /*
     * Send the response data
     */
    void sendResponseData(uint32_t grpId, const jsonable& responseData)
    {
        auto ss = std::make_shared<WsServer::SendStream>();
        if (responseToJson(grpId, responseData, *ss))
        {
            for (auto &connection : server.get_connections())
            {
                connection->send(ss);
            }
        }
    }

private:
    inline static std::string putTime(const std::chrono::system_clock::time_point &tp) { return tes_common_ais::putLocalTime(tp, tes_common_ais::date_time_formats::ISO_DATE_TIME_LOCAL); }

    bool responseToJson(uint32_t grpId, const jsonable& responseData, std::ostream &os)
    {
        // Build a json document
        namespace rj = rapidjson;
        rj::StringBuffer sb;
        rj::PrettyWriter<rj::StringBuffer> writer(sb);
        writer.SetMaxDecimalPlaces(10);
        writer.SetIndent(' ', 2);
        writer.StartObject();
        writer.Key("Response");
        writer.StartArray();

        writer.StartObject();
        writer.Key("GrpId"), writer.Uint(grpId);
        writer.EndObject();

        writer.StartObject();
        writer.Key("GrpVal");
        writer.StartArray();

        writer.StartObject();
        switch (grpId)
        {
        case coaching_task::GRP_ID_SUMMARY:
            writer.Key("GetSummary");
            break;
        case coaching_task::GRP_ID_3X3:
            writer.Key("Get3x3");
            break;
        case coaching_task::GRP_ID_BREADCRUMB:
            writer.Key("GetBreadcrumbs");
            break;
        case coaching_task::GRP_ID_SHOW_HIDE_STATUS:
            writer.Key("GetShowHideStatus");
            break;
        
        default:
            break;
        }
        
        writer.StartArray();

        responseData.toJson(writer);

        writer.EndArray();
        writer.EndObject();
        writer.EndArray();
        writer.EndObject();
        writer.EndArray();
        writer.EndObject();

        if (writer.IsComplete())
        {
            os << sb.GetString();
            return true;
        }

        return false;
    }

    static inline const rapidjson::Document::ValueType &getJsonMemberSafe(const rapidjson::Document::ValueType &d, const char *name)
    {
        static const auto nullValue = rapidjson::Document::ValueType();
        if (d.IsObject())
        {
            auto it = d.FindMember(name);
            if (it != d.MemberEnd())
            {
                return it->value;
            }
            else
            {
                return nullValue;
            }
        }
        else
        {
            return nullValue;
        }
    }

    void handleMessage(std::shared_ptr<WsServer::Connection> &connection, std::shared_ptr<WsServer::Message> &message)
    {
        if (pApp == nullptr)
        {
            return;
        }
        namespace rj = rapidjson;
        rj::Document d;
        if (d.Parse(message->string()).HasParseError())
        {
            return; // Parse error
        }

        const auto &jsonCmd = getJsonMemberSafe(d, "Command");
        if (jsonCmd.IsString())
        {
            std::string cmd = jsonCmd.GetString();
            const auto &grpIdTemp = getJsonMemberSafe(d, "GrpId");
            coaching_task::GrpId grpId = grpIdTemp.IsUint() ? static_cast<coaching_task::GrpId>(grpIdTemp.GetUint()) : GRP_ID_NOT_FOUND;
            const auto &tipNumber = getJsonMemberSafe(d, "TipId");
            const auto &seconds = getJsonMemberSafe(d, "Seconds");
            const auto &value = getJsonMemberSafe(d, "Value");

            if (cmd == "Start")
            {
                uint32_t interval = 0;
                const auto &intervalTemp = getJsonMemberSafe(d, "Interval");
                if (intervalTemp.IsUint())
                {
                    interval = intervalTemp.GetUint();
                }

                // Send immediately
                pApp->sendData(grpId);

                // Set up publish rate
                if (interval > 0)
                {
                    pApp->setPublishRate(grpId, interval);
                }
            }
            else if (cmd == "Stop")
            {
                pApp->setPublishRate(grpId, 0);
            }
            else if (cmd == "Operator")
            {
                const auto &operatorId = getJsonMemberSafe(d, "Name");
                if (operatorId.IsString())
                {
                    pApp->setOperatorId(operatorId.GetString());
                }
            }
            else if (cmd == "Reset")
            {
                pApp->resetStats();
            }
            else if (cmd == "TipAutoEnableTime")
            {
                if(seconds.IsUint())
                {
                    pApp->setTipAutoEnableTime(seconds.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: tipAutoEnableTime not an int", cmd.c_str());
                } 
            }
            else if (cmd == "ElapsedTimeSec")
            {
                if(seconds.IsUint())
                {
                    pApp->setElapsedTimeSec(seconds.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: ElapsedTimeSec not an int", cmd.c_str());
                } 
            }
            else if (cmd == "TipOn")
            {
                if (tipNumber.IsUint())
                {
                    pApp->setOpTipOnOff(true, tipNumber.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: TipId not found", cmd.c_str());
                }
            }
            else if (cmd == "TipOff")
            {
                if (tipNumber.IsUint())
                {
                    pApp->setOpTipOnOff(false, tipNumber.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: TipId not found", cmd.c_str());
                }
            }
            else if (cmd == "TipShow")
            {
                if (tipNumber.IsUint())
                {
                    pApp->setSysTipShowHide(true, tipNumber.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: TipId not found", cmd.c_str());
                }
            }
            else if (cmd == "TipHide")
            {
                if (tipNumber.IsUint())
                {
                    pApp->setSysTipShowHide(false, tipNumber.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: TipId not found", cmd.c_str());
                }
            }
            else if (cmd == "SetBreadcrumbRecords")
            {
                if (value.IsUint())
                {
                    pApp->setBreadcrumbRequestedRecords(value.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: Value not found", cmd.c_str());
                }
            }
            else if (cmd == "SetBreadcrumbGpsTimeSeconds")
            {
                if (value.IsUint())
                {
                    pApp->setBreadcrumbGpsTimeSeconds(value.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: Value not found", cmd.c_str());
                }
            }
            else if (cmd == "SetBreadcrumbGpsDistanceMeters")
            {
                if (value.IsUint())
                {
                    pApp->setBreadcrumbGpsDistanceMeters(value.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: Value not found", cmd.c_str());
                }
            }
            else if (cmd == "TutorialViewed")
            {
                if (tipNumber.IsUint())
                {
                    pApp->setTutorialViewed(tipNumber.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: Value not found", cmd.c_str());
                }
            }
            else if (cmd == "TipViewed")
            {
                if (tipNumber.IsUint())
                {
                    pApp->setTipViewed(tipNumber.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: Value not found", cmd.c_str());
                }
            }
            else if (cmd == "TipIncrement")
            {
                if (tipNumber.IsUint())
                {
                    pApp->setTipIncrement(tipNumber.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: Value not found", cmd.c_str());
                }
            }
            else if (cmd == "TipDecrement")
            {
                if (tipNumber.IsUint())
                {
                    pApp->setTipDecrement(tipNumber.GetUint());
                }
                else
                {
                    AIS_LOG_ERROR("%s: Value not found", cmd.c_str());
                }
            }
            else
            {
                // Error, just ignore the message
            }
        }
    }

    void serve()
    {
        AIS_LOG_NOTICE("WS Server: serving...");
        server.start();
        AIS_LOG_WARN("WS Server: server stopped.");
    }

    static constexpr const char *ENDPOINT = "^/coaching";

    std::thread t;

    WsServer server;

    IWsApp *pApp;
};

} // namespace coaching_task

#endif
