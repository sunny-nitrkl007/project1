#ifndef WORKORDERASSIST__SERVER_H
#define WORKORDERASSIST__SERVER_H

#include <thread>
#include <memory>
#include <mutex>
#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <atomic>

#include <ais/log/Logger.h>

// Need to include <cstdlib> because <server_ws.hpp> needs it but doesn't include it.
#include <cstdlib>
#include <Simple-WebSocket-Server/server_ws.hpp>

//#define RAPIDJSON_NAMESPACE rapidjson110
//#define RAPIDJSON_HAS_STDSTRING 1
#include <ext/rapidjson/RapidJsonGuarded.h>

#include <chrono/print.hpp>

#include <interfaces/WorkOrderAssist/Settings.hpp>

#include "IApp.h"

namespace woa_app {

class Server {
public:
    using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;

    Server(IApp* pApp): Server(pApp, 8080) {}

    Server(IApp* pApp, uint16_t port, const std::string& loaderCode = ""):
        t_(),
        server_(),
        pApp_(pApp),
        zoneSummariesMtx_(),
        zoneSummaries_(),
        getSitesPending_(false) {

        server_.config.port = port;

        // Make sure we have 2 threads so that we have a free one when there is a blocking request on the first.
        server_.config.thread_pool_size = 2;

        AIS_LOG_NOTICE("WS Server: Configured for port %d", port);

        // Create an endpoint
        auto &endpoint = server_.endpoint[ENDPOINT];

        // Register the callbacks for the endpoint
        endpoint.on_open = [this](std::shared_ptr<WsServer::Connection> connection) {
            AIS_LOG_NOTICE("WS Server: Opened connection %p.", connection.get());
        };

        endpoint.on_message = [this](std::shared_ptr<WsServer::Connection> connection, std::shared_ptr<WsServer::Message> message) {
            AIS_LOG_DEBUG("WS Server: Received message from connection %p.", connection.get());
            handleMessage(connection, message);
        };

        endpoint.on_error = [this](std::shared_ptr<WsServer::Connection> connection, const SimpleWeb::error_code& ec) {
            AIS_LOG_ERROR("WS Server: Error in connection %p. Error: %d, error message: %s", connection.get(), ec.value(), ec.message().c_str());
        };

        endpoint.on_close = [this](std::shared_ptr<WsServer::Connection> connection, int status, const std::string& reason) {
            AIS_LOG_NOTICE("WS Server: Closed connection %p with status code %d, reason: %s", connection.get(), status, reason.c_str());
        };
    }

    ~Server() {
        stop();
    }

    /*
     * Start the server
     */
    bool start() {
        stop(); // Kill if currently running

        // Start up a new thread for the server
        t_ = std::thread([this]() { serve(); });

        return true;
    }

    /*
     * Stop the server
     */
    bool stop() {
        // Kill the server
        server_.stop();

        // Wait for it to stop
        if (t_.joinable()) {
            t_.join();
        }

        return true;
    }

private:
    inline bool getSites(std::vector<Site>& sites, int32_t& activeSiteId) {
        AIS_LOG_INFO("WS Server: calling getSites (%p).", pApp_);
        return nullptr != pApp_ ? pApp_->getSites(sites, activeSiteId) : false;
    }

    inline bool selectSite(int32_t siteId) {
        { // Clear zone summaries cache when switching sites
            std::lock_guard<std::mutex> lck(zoneSummariesMtx_);
            zoneSummaries_.clear();
        }

        AIS_LOG_INFO("WS Server: calling selectSite for %d (%p).", siteId, pApp_);
        if (nullptr != pApp_) {
            pApp_->selectSite(siteId, true);
            return true;
        }
        return false;
    }

    inline bool selectJob(int64_t jobId, const Job::TimePoint& dateTime) {
        AIS_LOG_INFO("WS Server: calling selectJob for %d (%p).", jobId, pApp_);
        if (nullptr != pApp_) {
            pApp_->selectJob(jobId, dateTime, true);
            return true;
        }
        return false;
    }

    inline bool releaseJob(int64_t jobId) {
        AIS_LOG_INFO("WS Server: calling releaseJob for %d (%p).", jobId, pApp_);
        if (nullptr != pApp_) {
            pApp_->releaseJob(jobId, true);
            return true;
        }
        return false;
    }

    inline bool completeJob(int64_t jobId, int16_t passCount, float materialWeight, const Job::TimePoint& dateTime) {
        AIS_LOG_INFO("WS Server: calling completeJob for %d (%p).", jobId, pApp_);
        if (nullptr != pApp_) {
            pApp_->completeJob(jobId, passCount, materialWeight, dateTime, true);
            return true;
        }
        return false;
    }

    inline bool readSettings(WorkOrderAssistSettings& settings) const {
        AIS_LOG_INFO("WS Server: calling readSettings (%p).", pApp_);
        if (nullptr != pApp_) {
            pApp_->readSettings(settings);
            return true;
        }
        return false;
    }

    inline bool writeSettings(const WorkOrderAssistSettings& settings) {
        AIS_LOG_INFO("WS Server: calling writeSettings (%p).", pApp_);
        if (nullptr != pApp_) {
            pApp_->writeSettings(settings);
            return true;
        }
        return false;
    }

    inline static std::string putTime(const std::chrono::system_clock::time_point& tp) {
        return tes_common_ais::putLocalTime(tp, tes_common_ais::date_time_formats::ISO_DATE_TIME_LOCAL);
    }

    void sendJobsToAll(int32_t zoneId = -1) {
        AIS_LOG_INFO("WS Server: sending jobs to all other connections.");
        auto ss = std::make_shared<WsServer::SendStream>();
        if (jobsToJson(*ss, zoneId)) {
            sendStreamToAll(ss);
        }
    }

    void sendStreamToAll(const std::shared_ptr<WsServer::SendStream>& ss) {
        auto& endpoint = server_.endpoint[ENDPOINT];
        std::unordered_set<std::shared_ptr<WsServer::Connection>> connections = endpoint.get_connections();
        for (auto& c : connections) {
            c->send(ss);
        }
    }

    bool zoneSummariesToJson(std::ostream& os) {
        // Build a json document
        namespace rj = rapidjson;
        rj::StringBuffer sb;
        rj::Writer<rj::StringBuffer> writer(sb);
        writer.SetMaxDecimalPlaces(2);
        writer.StartObject();
        writer.Key("Response");
        writer.String("GetZoneSummaries");

        { // Build zone summaries
            std::lock_guard<std::mutex> lck(zoneSummariesMtx_);

            if (zoneSummaries_.size() > MAX_ZONES) {
                // We have built up too many zones over time, just start over.
                zoneSummaries_.clear();
            }
            else {
                // Reset each zone
                for (auto& p : zoneSummaries_) {
                    ZoneSummary& z = p.second;
                    z.numJobs = 0;
                    z.oldestJobReadyTime = Job::TimePoint::max();
                }
            }

            if (nullptr != pApp_) {
                // Loop through all jobs, updating the summaries.
                pApp_->visitJobs([this](const Job& j){
                    if ((j.state == JobState::TODO) ||
                        ((j.state == JobState::DOING) && (!j.isLoaded))) {
                        try {
                            ZoneSummary& z = zoneSummaries_.at(j.zoneName);
                            ++z.numJobs;
                            if (j.readyTime < z.oldestJobReadyTime) {
                                z.oldestJobReadyTime = j.readyTime;
                            }
                        }
                        catch (const std::out_of_range& e) {
                            zoneSummaries_.emplace(j.zoneName, ZoneSummary(j.zoneId, j.zoneName, 1, j.readyTime));
                        }
                    }
                });
            }

            { // Loop through zone summaries and serialize
                writer.Key("Data");
                writer.StartObject();
                writer.Key("Zones");
                writer.StartArray();
                for (const auto& p : zoneSummaries_) {
                    const ZoneSummary& z = p.second;
                    writer.StartObject();
                    writer.Key("Id"), writer.Int(z.id);
                    writer.Key("Name"), writer.String(z.name);
                    writer.Key("NumJobs"), writer.Int(z.numJobs);
                    if (z.numJobs > 0) {
                        writer.Key("OldestJobReadyTime"), writer.String(putTime(z.oldestJobReadyTime));
                    }
                    else {
                        writer.Key("OldestJobReadyTime"), writer.Null();
                    }
                    writer.EndObject();
                }
                writer.EndArray();
                writer.EndObject(); // Data
            }
        }

        writer.EndObject(); // Root

        if (writer.IsComplete()) {
            os << sb.GetString();
            return true;
        }

        return false;
    }

    bool sitesToJson(std::ostream& os, const std::vector<Site>& sites, int32_t activeSiteId) const {
        // Build a json document
        namespace rj = rapidjson;
        rj::StringBuffer sb;
        rj::Writer<rj::StringBuffer> writer(sb);
        writer.SetMaxDecimalPlaces(2);
        writer.StartObject();
        writer.Key("Response");
        writer.String("GetSites");

        writer.Key("Data");
        writer.StartObject();
        writer.Key("Sites");
        writer.StartArray();
        for (const auto& s : sites) {
            writer.StartObject();
            writer.Key("Id"), writer.Int(s.id);
            writer.Key("Name"), writer.String(s.name);
            writer.EndObject();
        }
        writer.EndArray();

        writer.Key("ActiveSiteId");
        if (activeSiteId < 0) {
            writer.Null();
        }
        else {
            writer.Int(activeSiteId);
        }

        writer.EndObject(); // Data
        writer.EndObject(); // Root

        if (writer.IsComplete()) {
            os << sb.GetString();
            return true;
        }

        return false;
    }

    bool jobsToJson(std::ostream& os, int32_t zoneId = -1) const {
        // Build a json document
        namespace rj = rapidjson;
        rj::StringBuffer sb;
        rj::Writer<rj::StringBuffer> writer(sb);

        // Using max decimal places 3 so that the UI can round to 2 after units conversion.
        writer.SetMaxDecimalPlaces(3);

        writer.StartObject();
        writer.Key("Response");
        writer.String("GetJobs");

        int64_t activeJobId;

        writer.Key("Data");
        writer.StartObject();

        writer.Key("Jobs");
        writer.StartArray();
        if (nullptr != pApp_) {
            activeJobId = pApp_->visitJobs([&writer, zoneId](const Job& j){
                if (((zoneId < 0) || (j.zoneId == zoneId)) && (!j.isLoaded)) {
                    writer.StartObject();
                    writer.Key("Id"), writer.Int64(j.id);
                    writer.Key("State"), writer.String(jobStateToString(j.state, true));
                    writer.Key("IsLoaded"), writer.tBool(j.isLoaded);
                    writer.Key("ReadyTime"), writer.String(putTime(j.readyTime));
                    writer.Key("ZoneId"), writer.Int(j.zoneId);
                    writer.Key("ZoneName"), writer.String(j.zoneName);
                    writer.Key("Instruction");
                    writer.StartObject();
                    writer.Key("TruckName"), writer.String(j.instruction.truckName);
                    writer.Key("MaterialName"), writer.String(j.instruction.materialName);
                    writer.Key("TargetMaterialWeight"), writer.Double(j.instruction.targetMaterialWeight);
                    writer.EndObject();
                    writer.EndObject();
                }
            });
        }
        else {
            activeJobId = -1;
        }
        writer.EndArray();

        writer.Key("ActiveJobId");
        if (activeJobId < 0) {
            writer.Null();
        }
        else {
            writer.Int64(activeJobId);
        }

        writer.EndObject(); // Data

        writer.EndObject(); // Root

        if (writer.IsComplete()) {
            os << sb.GetString();
            return true;
        }

        return false;
    }

    bool settingsToJson(std::ostream& os, const WorkOrderAssistSettings& settings) const {
        // Build a json document
        namespace rj = rapidjson;
        rj::StringBuffer sb;
        rj::Writer<rj::StringBuffer> writer(sb);
        writer.SetMaxDecimalPlaces(2);
        writer.StartObject();

        writer.Key("Response");
        writer.String("ReadSettings");

        writer.Key("Data");
        writer.StartObject();
        writer.Key("Installed"), writer.tBool(settings.installed);
        writer.Key("Enabled"), writer.tBool(settings.enabled);
        writer.Key("JobTimeWarningMinutes"), writer.Double(settings.jobTimeWarningMinutes);
        writer.Key("SiteId"), writer.Int(settings.siteId);
        writer.Key("SiteName"), writer.String(settings.siteName);
        writer.EndObject(); // Data

        writer.EndObject(); // Root

        if (writer.IsComplete()) {
            os << sb.GetString();
            return true;
        }

        return false;
    }

    static inline const rapidjson::Document::ValueType& getJsonMemberSafe(const rapidjson::Document::ValueType& d, const char* name) {
        static const auto nullValue = rapidjson::Document::ValueType();
        if (d.IsObject()) {
            auto it = d.FindMember(name);
            if (it != d.MemberEnd()) {
                return it->value;
            }
            else {
                return nullValue;
            }
        }
        else {
            return nullValue;
        }
    }

    void handleMessage(std::shared_ptr<WsServer::Connection>& connection, std::shared_ptr<WsServer::Message>& message) {
        namespace rj = rapidjson;
        rj::Document d;

        if (d.Parse(message->string()).HasParseError()) {
            return; // Parse error
        }

        const auto& mId = getJsonMemberSafe(d, "Command");
        if (mId.IsString()) {
            // For now, just do if-else-if
            if (mId == "GetJobs") {
                // Get zone id, if provided
                int32_t zoneId = -1;
                const auto& mData = getJsonMemberSafe(d, "Data");
                const auto& mZoneId = getJsonMemberSafe(mData, "ZoneId");
                if (mZoneId.IsInt()) {
                    zoneId = mZoneId.GetInt();
                }

                auto ss = std::make_shared<WsServer::SendStream>();
                if (jobsToJson(*ss, zoneId)) {
                    connection->send(ss);
                }
            }
            else if (mId == "SetJobState") {
                const auto& mData = getJsonMemberSafe(d, "Data");
                const auto& mJobId = getJsonMemberSafe(mData, "Id");
                const auto& mState = getJsonMemberSafe(mData, "State");
                if (mJobId.IsInt64() && mState.IsString()) {
                    if (mState == "doing") {
                        selectJob(mJobId.GetInt64(), Job::Clock::now()); // Ignore success/failure for now
                        sendJobsToAll();
                    }
                    else if (mState == "to-do") {
                        releaseJob(mJobId.GetInt64()); // Ignore success/failure for now
                        sendJobsToAll();
                    }
                }
            }
            else if (mId == "GetZoneSummaries") {
                auto ss = std::make_shared<WsServer::SendStream>();
                if (zoneSummariesToJson(*ss)) {
                    connection->send(ss);
                }
            }
            else if (mId == "SetSiteId") {
                const auto& mData = d["Data"];
                const auto& mSiteId = getJsonMemberSafe(mData, "SiteId");
                if (mSiteId.IsInt()) {
                    selectSite(mSiteId.GetInt()); // Ignore success/failure for now
                    sendJobsToAll();
                }
            }
            else if (mId == "GetSites") {
                if (!getSitesPending_.exchange(true)) {
                    std::vector<Site> sites;
                    int32_t activeSiteId;
                    if (getSites(sites, activeSiteId)) {
                        auto ss = std::make_shared<WsServer::SendStream>();
                        if (sitesToJson(*ss, sites, activeSiteId)) {
                            sendStreamToAll(ss);
                        }
                    }
                    getSitesPending_ = false;
                }
            }
            else if (mId == "ReadSettings") {
                WorkOrderAssistSettings settings;
                if (readSettings(settings)) {
                    auto ss = std::make_shared<WsServer::SendStream>();
                    if (settingsToJson(*ss, settings)) {
                        connection->send(ss);
                    }
                }
            }
            else if (mId == "WriteSettings") {
                WorkOrderAssistSettings settings;
                if (readSettings(settings)) {
                    const auto& mData = getJsonMemberSafe(d, "Data");

                    const auto& mEnabled = getJsonMemberSafe(mData, "Enabled");
                    if (mEnabled.IsBool()) {
                        settings.enabled = mEnabled.GetBool();
                    }

                    const auto& mJobTimeWarningMinutes = getJsonMemberSafe(mData, "JobTimeWarningMinutes");
                    if (mJobTimeWarningMinutes.IsNumber()) {
                        settings.jobTimeWarningMinutes = mJobTimeWarningMinutes.GetFloat();
                    }

                    if (!writeSettings(settings)) {
                        readSettings(settings);
                    }

                    auto ss = std::make_shared<WsServer::SendStream>();
                    if (settingsToJson(*ss, settings)) {
                        connection->send(ss);
                    }
                }
            }
            else if (mId == "SetJobLoadedTest") {
                const auto& mData = getJsonMemberSafe(d, "Data");
                const auto& mJobId = getJsonMemberSafe(mData, "Id");
                const auto& mPassCount = getJsonMemberSafe(mData, "PassCount");
                const auto& mWeight = getJsonMemberSafe(mData, "Weight");
                if (mJobId.IsInt64()) {
                    if (mPassCount.IsInt() && mWeight.IsNumber()) {
                        completeJob(mJobId.GetInt64(), mPassCount.GetInt(), mWeight.GetFloat(), Job::Clock::now());
                    }
                    else {
                        completeJob(mJobId.GetInt64(), 3, 23.9, Job::Clock::now());
                    }
                    sendJobsToAll();
                }
            }
            else {
                // Error, just ignore the message
            }
        }
    }

    void serve() {
        AIS_LOG_NOTICE("WS Server: serving...");
        server_.start();
        AIS_LOG_WARN("WS Server: server stopped.");
    }

    static constexpr const char* ENDPOINT = "^/woa";
    static constexpr std::size_t MAX_ZONES = 100;

    std::thread t_;

    WsServer server_;

    IApp* pApp_;

    // Keep a zone summary map so that we can remember empty zones
    mutable std::mutex zoneSummariesMtx_;
    std::map<std::string, ZoneSummary> zoneSummaries_;

    // Get site request is currently pending.
    std::atomic<bool> getSitesPending_;

};

}

#endif
