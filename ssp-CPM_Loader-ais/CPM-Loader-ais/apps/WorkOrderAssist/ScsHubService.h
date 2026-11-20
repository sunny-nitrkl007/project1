#ifndef WORKORDERASSIST__SCSHUBSERVICE_H
#define WORKORDERASSIST__SCSHUBSERVICE_H

#include <cstdint>
#include <cstdlib>
#include <mutex>
#include <vector>
#include <list>
#include <future>
#include <functional>
#include <chrono>
#include <stdexcept>
#include <exception>
#include <algorithm>

#include <boost/signals2.hpp>

//#define RAPIDJSON_NAMESPACE rapidjson110
//#define RAPIDJSON_HAS_STDSTRING 1
#include <ext/rapidjson/RapidJsonGuarded.h>

#include <ais/log/Logger.h>

#include <chrono/print.hpp>

#include <interfaces/IoTHubCommsInboundMessage/Channel/channels.h>
#include <interfaces/IoTHubCommsOutboundMessage/Channel/channels.h>
#include <interfaces/IoTHubCommsOutboundReturn/Channel/channels.h>

#include "IHubService.h"
#include "Data.h"

namespace woa_app {

class ScsHubService : public IHubService {
public:

    /*class CommError : public std::exception {
    public:
        CommError(const char* str = ""): what_(str) {}
        virtual const char* what() const noexcept { return what_; }
    private:
        const char* what_;
    };*/

    ScsHubService(const std::string& appName,
            IoTHubCommsInboundMessageInput* iotHubInboundMessageInput,
            IoTHubCommsOutboundMessageOutput* iotHubOutboundMessageOutput,
            IoTHubCommsOutboundReturnInput* iotHubOutboundReturnInput):
                started_(false),
                appName_(appName),
                iotHubInboundMessageInput_(iotHubInboundMessageInput),
                iotHubOutboundMessageOutput_(iotHubOutboundMessageOutput),
                iotHubOutboundReturnInput_(iotHubOutboundReturnInput),
                iotHubInboundMessageInputConnection_(),
                iotHubOutboundReturnInputConnection_(),
                jobsListenerMtx_(),
                jobsListener_(),
                getSitesPromisesMtx_(),
                getSitesPromises_(),
                selectSitePromisesMtx_(),
                selectSitePromises_(),
                updateJobPromisesMtx_(),
                updateJobPromises_() {}


    ScsHubService():
        ScsHubService("", nullptr, nullptr, nullptr) {}

    virtual ~ScsHubService() {
        stop();
    }

    /*
     * Start the hub service
     */
    bool start() {
        if (nullptr != iotHubInboundMessageInput_) {
            iotHubInboundMessageInputConnection_ = iotHubInboundMessageInput_->addNewDataSlot([this]{
                notifyInboundMessageInput();
            });
        }

        if (nullptr != iotHubOutboundReturnInput_) {
            iotHubOutboundReturnInputConnection_ = iotHubOutboundReturnInput_->addNewDataSlot([this]{
                notifyOutboundReturnInput();
            });
        }

        started_ = true;

        return true;
    }

    /*
     * Stop the hub service
     */
    bool stop() {
        if (nullptr != iotHubInboundMessageInput_) {
            iotHubInboundMessageInput_->removeNewDataSlot(iotHubInboundMessageInputConnection_);
        }

        if (nullptr != iotHubInboundMessageInput_) {
            iotHubOutboundReturnInput_->removeNewDataSlot(iotHubOutboundReturnInputConnection_);
        }

        started_ = false;

        return true;
    }

    /*
     * Get the list of sites available to this asset from the hub.
     * On success, the sites vector will contain the new sites.
     * On failure, the sites vector will be left untouched.
     * This is a blocking function call and returns true for success, else false.
     */
    bool getSites(std::vector<Site>& sites) {
        bool success;

        auto requestId = IoTHubCommsOutboundMessageStorage::getNextAppRequestId();

        // Create a promise queue entry
        GetSitesPromiseEntry pe;
        pe.requestId = requestId;

        // Get the future of that promise
        auto f = pe.p.get_future();

        { // Lock the promise queue
            std::lock_guard<std::mutex> lck(getSitesPromisesMtx_);
            auto& promises = getSitesPromises_;

            // Drop old promises if full.
            while (promises.size() >= getSitesPromisesMaxSize_) {
                // This will destroy the promise, resulting in a std::future_error
                promises.pop_front();
            }

            // Move the promise onto the queue
            promises.push_back(std::move(pe));
        }

        { // Build and publish the get sites request message
            static constexpr char str[] = "{}";
            static constexpr auto strSize = sizeof(str) / sizeof(str[0]);

            // Create a vector
            const uint8_t* buf = reinterpret_cast<const uint8_t*>(&str[0]);
            std::vector<uint8_t> contents(buf, buf + strSize);

            IoTHubCommsOutboundMessage msg;
            msg.appName = appName_;
            msg.appRequestId = requestId;
            msg.fileType = getSitesRequestFileId_;
            msg.messageContents = std::move(contents);
            msg.correlationId.clear();
            msg.generateMessageId = true;
            msg.oneShot = true;

            if (nullptr != iotHubOutboundMessageOutput_) {
                if (iotHubOutboundMessageOutput_->publish(msg)) {
                    AIS_LOG_NOTICE("Published GetSites request.");
                }
                else {
                    AIS_LOG_ERROR("Failed to publish GetSites request.");
                    // We already handed off the promise, we just need
                    // to wait for it to timeout.
                }
            }
            else {
                AIS_LOG_ERROR("Cannot attempt publish GetSites request.");
                // We already handed off the promise, we just need
                // to wait for it to timeout.
            }
        }

        // Wait on the future answer (with try/catch)
        try {
            auto status = f.wait_for(std::chrono::seconds(30));
            if (std::future_status::timeout == status) {
                AIS_LOG_ERROR("GetSites request timeout");
                success = false;
            }
            else {
                auto pSites = f.get();
                if (nullptr != pSites) {
                    sites = *pSites;
                    AIS_LOG_NOTICE("GetSites successful.");
                    success = true;
                }
                else {
                    AIS_LOG_ERROR("GetSites returns null");
                    success = false;
                }
            }
        }
        catch (const std::future_error& e) {
            AIS_LOG_ERROR("GetSites future error '%s'", e.what());
            success = false;
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("GetSites exception '%s'", e.what());
            success = false;
        }

        return success;
    }

    /*
     * Select the site.
     * This is a blocking function call and returns true for success, else false.
     */
    bool selectSite(int32_t siteId, int64_t jobsHash, const Job::TimePoint& dateTime) {
        bool success;

        auto requestId = IoTHubCommsOutboundMessageStorage::getNextAppRequestId();

        // Create a promise queue entry
        SelectSitePromiseEntry pe;
        pe.requestId = requestId;

        // Get the future of that promise
        auto f = pe.p.get_future();

        { // Lock the promise queue
            std::lock_guard<std::mutex> lck(selectSitePromisesMtx_);
            auto& promises = selectSitePromises_;

            // Drop old promises if full.
            while (promises.size() >= selectSitePromisesMaxSize_) {
                // This will destroy the promise, resulting in a std::future_error
                promises.pop_front();
            }

            // Move the promise onto the queue
            promises.push_back(std::move(pe));
        }

        { // Build and publish the select site request message
            rapidjson::StringBuffer sb;
            rapidjson::Writer<rapidjson::StringBuffer> writer{ sb };
            writer.StartObject();
            {
                writer.Key("body");
                writer.StartObject();
                {
                    writer.Key("siteId");
                    writer.Int(siteId);

                    writer.Key("jobsHash");
                    writer.String(std::to_string(jobsHash)); // Convert Int64 to String

                    // If there is a time given, include it in this request
                    if (dateTime.time_since_epoch() > Job::TimePoint::duration::zero()) {
                        writer.Key("dateTime");
                        writer.String(tes_common_ais::putTime(dateTime, "%FT%TZ"));
                    }
                }
                writer.EndObject();
            }
            writer.EndObject();

            // Create a vector
            const uint8_t* buf = reinterpret_cast<const uint8_t*>(sb.GetString());
            std::vector<uint8_t> contents(buf, buf + sb.GetSize());

            IoTHubCommsOutboundMessage msg;
            msg.appName = appName_;
            msg.appRequestId = requestId;
            msg.fileType = selectSiteRequestFileId_;
            msg.messageContents = std::move(contents);
            msg.correlationId.clear();
            msg.generateMessageId = true;
            msg.oneShot = true;

            // This is to simulate communication delay for testing.
            //std::this_thread::sleep_for(std::chrono::seconds(5));

            if (nullptr != iotHubOutboundMessageOutput_) {
                if (iotHubOutboundMessageOutput_->publish(msg)) {
                    AIS_LOG_NOTICE("Published SelectSite request.");
                }
                else {
                    AIS_LOG_ERROR("Failed to publish SelectSite request.");
                    // We already handed off the promise, we just need
                    // to wait for it to timeout.
                }
            }
            else {
                AIS_LOG_ERROR("Cannot attempt publish SelectSite request.");
                // We already handed off the promise, we just need
                // to wait for it to timeout.
            }
        }

        // Wait on the future answer (with try/catch)
        try {
            auto status = f.wait_for(std::chrono::seconds(30));
            if (std::future_status::timeout == status) {
                AIS_LOG_ERROR("SelectSite request timeout");
                success = false;
            }
            else {
                f.get();
                AIS_LOG_NOTICE("SelectSite successful.");
                success = true;
            }
        }
        catch (const std::future_error& e) {
            AIS_LOG_ERROR("SelectSite future error '%s'", e.what());
            success = false;
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("SelectSite exception '%s'", e.what());
            success = false;
        }

        return success;
    }

    /*
     * Register jobs listener
     * This callback's argument is an rvalue reference to facilitate moving the vector instead of copying it.
     * The callback will be called from the hub's thread context, so protect as needed.
     */
    void registerJobsListener(const JobsListener& listener) {
        std::lock_guard<std::mutex> lck(jobsListenerMtx_);
        jobsListener_ = listener;
    }

    /*
     * Update a job.
     * These are blocking function calls and return true for success, else false.
     */
    bool updateJobStatusStartDoing(int32_t siteId, int64_t jobId, int64_t stopDoingJobId, const Job::TimePoint& dateTime, const std::string& loaderCode) {
        rapidjson::StringBuffer sb;

        rapidjson::Writer<rapidjson::StringBuffer> writer{ sb };
        //rapidjson::PrettyWriter<rapidjson::StringBuffer> writer{ sb };
        //writer.SetIndent(' ', 2);

        writer.StartObject();
        {
            writer.Key("command");
            writer.String("startDoing");

            writer.Key("body");
            writer.StartObject();
            {
                writer.Key("siteId");
                writer.Int(siteId);

                writer.Key("jobId");
                writer.Int64(jobId);

                // If there is a time given, include it in this request
                if (dateTime.time_since_epoch() > Job::TimePoint::duration::zero()) {
                    writer.Key("dateTime");
                    writer.String(tes_common_ais::putTime(dateTime, "%FT%TZ"));
                }

                // If there is a job to stop doing, include it in this request.
                if (stopDoingJobId >= 0) {
                    writer.Key("stopDoingJobId");
                    writer.Int64(stopDoingJobId);
                }
            }
            writer.EndObject();
        }
        writer.EndObject();

        AIS_LOG_NOTICE("%s", sb.GetString());

        // Create a vector
        const uint8_t* buf = reinterpret_cast<const uint8_t*>(sb.GetString());
        std::vector<uint8_t> contents(buf, buf + sb.GetSize());

        return updateJobStatus(std::move(contents));
    }

    bool updateJobStatusLoaded(int32_t siteId, int64_t jobId, int16_t passCount, float materialWeight, const Job::TimePoint& dateTime, const std::string& loaderCode) {
        rapidjson::StringBuffer sb;

        rapidjson::Writer<rapidjson::StringBuffer> writer{ sb };
        //rapidjson::PrettyWriter<rapidjson::StringBuffer> writer{ sb };
        //writer.SetIndent(' ', 2);
        writer.SetMaxDecimalPlaces(3);

        writer.StartObject();
        {
            writer.Key("command");
            writer.String("loaded");

            writer.Key("body");
            writer.StartObject();
            {
                writer.Key("siteId");
                writer.Int(siteId);

                writer.Key("jobId");
                writer.Int64(jobId);

                // If there is a time given, include it in this request
                if (dateTime.time_since_epoch() > Job::TimePoint::duration::zero()) {
                    writer.Key("dateTime");
                    writer.String(tes_common_ais::putTime(dateTime, "%FT%TZ"));
                }

                writer.Key("loaderPassCount");
                writer.Int(passCount);

                writer.Key("loaderMaterialWeight");
                writer.Double(materialWeight);
            }
            writer.EndObject();
        }
        writer.EndObject();

        AIS_LOG_NOTICE("%s", sb.GetString());

        // Create a vector
        const uint8_t* buf = reinterpret_cast<const uint8_t*>(sb.GetString());
        std::vector<uint8_t> contents(buf, buf + sb.GetSize());

        return updateJobStatus(std::move(contents));
    }

    bool updateJobStatusStopDoing(int32_t siteId, int64_t jobId) {
        rapidjson::StringBuffer sb;

        rapidjson::Writer<rapidjson::StringBuffer> writer{ sb };
        //rapidjson::PrettyWriter<rapidjson::StringBuffer> writer{ sb };
        //writer.SetIndent(' ', 2);

        writer.StartObject();
        {
            writer.Key("command");
            writer.String("stopDoing");

            writer.Key("body");
            writer.StartObject();
            {
                writer.Key("siteId");
                writer.Int(siteId);

                writer.Key("jobId");
                writer.Int64(jobId);
            }
            writer.EndObject();
        }
        writer.EndObject();

        AIS_LOG_NOTICE("%s", sb.GetString());

        // Create a vector
        const uint8_t* buf = reinterpret_cast<const uint8_t*>(sb.GetString());
        std::vector<uint8_t> contents(buf, buf + sb.GetSize());

        return updateJobStatus(std::move(contents));
    }

private:
    bool updateJobStatus(std::vector<uint8_t>&& contents) {
        bool success;

        auto requestId = IoTHubCommsOutboundMessageStorage::getNextAppRequestId();

        // Create a promise queue entry
        UpdateJobPromiseEntry pe;
        pe.requestId = requestId;

        // Get the future of that promise
        auto f = pe.p.get_future();

        { // Lock the promise queue
            std::lock_guard<std::mutex> lck(updateJobPromisesMtx_);
            auto& promises = updateJobPromises_;

            // Drop old promises if full.
            while (promises.size() >= updateJobPromisesMaxSize_) {
                // This will destroy the promise, resulting in a std::future_error
                promises.pop_front();
            }

            // Move the promise onto the queue
            promises.push_back(std::move(pe));
        }

        { // Publish the update job request message
            IoTHubCommsOutboundMessage msg;
            msg.appName = appName_;
            msg.appRequestId = requestId;
            msg.fileType = updateJobRequestFileId_;
            msg.messageContents = std::move(contents);
            msg.correlationId.clear();
            msg.generateMessageId = true;

            // This is to simulate communication delay for testing.
            //std::this_thread::sleep_for(std::chrono::seconds(5));

            if (nullptr != iotHubOutboundMessageOutput_) {
                if (iotHubOutboundMessageOutput_->publish(msg)) {
                    AIS_LOG_NOTICE("Published UpdateJob request.");
                }
                else {
                    AIS_LOG_ERROR("Failed to publish UpdateJob request.");
                    // We already handed off the promise, we just need
                    // to wait for it to timeout.
                }
            }
            else {
                AIS_LOG_ERROR("Cannot attempt publish UpdateJob request.");
                // We already handed off the promise, we just need
                // to wait for it to timeout.
            }
        }

        // Wait on the future answer (with try/catch)
        try {
            auto status = f.wait_for(std::chrono::seconds(30));
            if (std::future_status::timeout == status) {
                AIS_LOG_ERROR("UpdateJob request timeout");
                success = false;
            }
            else {
                f.get();
                AIS_LOG_NOTICE("UpdateJob successful.");
                success = true;
            }
        }
        catch (const std::future_error& e) {
            AIS_LOG_ERROR("UpdateJob future error '%s'", e.what());
            success = false;
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("UpdateJob exception '%s'", e.what());
            success = false;
        }

        return success;
    }

    bool parseGetSitesResponse(const IoTHubCommsInboundMessageStorage& msg,
            std::shared_ptr<std::vector<Site>>& pSites) {
        bool success;

        AIS_LOG_NOTICE("Parsing message of size %d", msg.messageContents.size());

        { // Log the message contents
            // SIGSEGV, Segmentation Fault occurs if the formatted string is > 1024 characters.
            // This is a bug in va_str that reuses a va_list multiple times.
            std::string temp((const char*)msg.messageContents.data(), std::min<std::size_t>(msg.messageContents.size(), 1000));
            AIS_LOG_NOTICE("\n%s\n", temp.c_str());
        }

        rapidjson::Document doc;
        doc.Parse((const char*)msg.messageContents.data(), msg.messageContents.size());
        if (doc.HasParseError()) {
            // Invalid message contents, notify of failure
            AIS_LOG_ERROR("Could not parse GetSites response message content.");
            success = false;
        }
        else {
            int16_t statusCode;
            { // Get Status Code
                auto statusCodeMemberIt = doc.FindMember("httpStatusCode");
                if (doc.MemberEnd() == statusCodeMemberIt) {
                    statusCode = 200;
                }
                else if (statusCodeMemberIt->value.IsInt()) {
                    statusCode = statusCodeMemberIt->value.GetInt();
                }
                else {
                    // Schema Error
                    statusCode = -1;
                }
            }

            auto bodyMemberIt = doc.FindMember("body");
            if (doc.MemberEnd() == bodyMemberIt) {
                // I ain't got no body (get it... no body... nobody)
                if ((200 == statusCode) || (204 == statusCode)) {
                    // No Content
                    pSites = std::make_shared<std::vector<Site>>();
                    if (nullptr != pSites) {
                        AIS_LOG_NOTICE("GetSites response message 'body' missing.");
                        success = true;
                    }
                    else {
                        AIS_LOG_ERROR("Could not create shared vector of sites.");
                        success = false;
                    }
                }
                else {
                    // Error (in status code)
                    AIS_LOG_ERROR("GetSites response message status code: %d", statusCode);
                    success = false;
                }
            }
            else if (200 == statusCode) {
                if (bodyMemberIt->value.IsObject()) {
                    const auto& bodyValue = bodyMemberIt->value;

                    // Parse the body contents
                    auto sitesMemberIt = bodyValue.FindMember("sites");
                    if (bodyValue.MemberEnd() == sitesMemberIt) {
                        // Schema Error
                        AIS_LOG_ERROR("GetSites response message 'body.sites' missing.");
                        success = false;
                    }
                    else if (sitesMemberIt->value.IsArray()) {
                        pSites = std::make_shared<std::vector<Site>>();
                        if (nullptr != pSites) {
                            success = true; // for now

                            // Loop through sites
                            const auto& sitesValue = sitesMemberIt->value;
                            for (const auto& siteValue : sitesValue.GetArray()) {
                                if (siteValue.IsObject()) {
                                    auto idMemberIt = siteValue.FindMember("siteId");
                                    auto nameMemberIt = siteValue.FindMember("name");
                                    auto endMemberIt = siteValue.MemberEnd();
                                    if ((endMemberIt == idMemberIt) || (endMemberIt == nameMemberIt)) {
                                        AIS_LOG_ERROR("GetSites 'body.sites[]' members must contain 'siteId' and 'name'");
                                        success = false;
                                        break;
                                    }
                                    else if (!(idMemberIt->value.IsInt())) {
                                        AIS_LOG_ERROR("GetSites 'body.sites[].siteId' must be an integer.");
                                        success = false;
                                        break;
                                    }
                                    else if (!(nameMemberIt->value.IsString())) {
                                        AIS_LOG_ERROR("GetSites 'body.sites[].name' must be a string.");
                                        success = false;
                                        break;
                                    }
                                    else {
                                        AIS_LOG_NOTICE("GetSites received 'siteId' %d", idMemberIt->value.GetInt());
                                        pSites->push_back(Site{
                                            idMemberIt->value.GetInt(),
                                            nameMemberIt->value.GetString()
                                        });
                                    }
                                }
                                else {
                                    // Schema Error
                                    AIS_LOG_ERROR("GetSites response message 'body.sites' contains non-object.");
                                    success = false;
                                    break;
                                }
                            }
                        }
                        else {
                            AIS_LOG_ERROR("Could not create shared vector of sites.");
                            success = false;
                        }
                    }
                    else {
                        // Schema Error
                        AIS_LOG_ERROR("GetSites response message 'body.sites' not array.");
                        success = false;
                    }
                }
                else {
                    // Schema Error
                    AIS_LOG_ERROR("GetSites response message 'body' not object.");
                    success = false;
                }
            }
            else {
                // Error (in status code)
                AIS_LOG_ERROR("GetSites response message status code: %d", statusCode);
                success = false;
            }
        }
        return success;
    }

    bool parseSendJobs(const IoTHubCommsInboundMessageStorage& msg,
            std::vector<Job>& jobs, int64_t& jobsHash) {
        bool success;

        AIS_LOG_NOTICE("Parsing message of size %d", msg.messageContents.size());

        { // Log the message contents
            // SIGSEGV, Segmentation Fault occurs if the formatted string is > 1024 characters.
            // This is a bug in va_str that reuses a va_list multiple times.
            std::string temp((const char*)msg.messageContents.data(), std::min<std::size_t>(msg.messageContents.size(), 1000));
            AIS_LOG_NOTICE("\n%s\n", temp.c_str());
        }

        rapidjson::Document doc;
        doc.Parse((const char*)msg.messageContents.data(), msg.messageContents.size());
        if (doc.HasParseError()) {
            // Invalid message contents, notify of failure
            AIS_LOG_ERROR("Could not parse SendJobs message content.");
            success = false;
        }
        else {
            int16_t statusCode;
            { // Get Status Code
                auto statusCodeMemberIt = doc.FindMember("httpStatusCode");
                if (doc.MemberEnd() == statusCodeMemberIt) {
                    statusCode = 200;
                }
                else if (statusCodeMemberIt->value.IsInt()) {
                    statusCode = statusCodeMemberIt->value.GetInt();
                }
                else {
                    // Schema Error
                    statusCode = -1;
                }
            }

            auto bodyMemberIt = doc.FindMember("body");
            if (doc.MemberEnd() == bodyMemberIt) {
                // I ain't got no body (get it... no body... nobody)
                if ((200 == statusCode) || (204 == statusCode)) {
                    // No Content
                    jobsHash = 0;
                    success = true;
                }
                else {
                    // Error (in status code)
                    AIS_LOG_ERROR("SendJobs message status code: %d", statusCode);
                    success = false;
                }
            }
            else if (200 == statusCode) {
                if (bodyMemberIt->value.IsObject()) {
                    const auto& bodyValue = bodyMemberIt->value;

                    // Parse the body contents
                    auto jobsMemberIt = bodyValue.FindMember("jobs");
                    if (bodyValue.MemberEnd() == jobsMemberIt) {
                        // Schema Error
                        AIS_LOG_ERROR("SendJobs message 'body.jobs' missing.");
                        success = false;
                    }
                    else if (jobsMemberIt->value.IsArray()) {
                        success = true; // for now

                        // Loop through jobs
                        const auto& jobsValue = jobsMemberIt->value;
                        for (const auto& jobValue : jobsValue.GetArray()) {
                            if (jobValue.IsObject()) {
                                // Build the job object
                                Job job;
                                do { // A code block where 'break' works
                                    auto endMemberIt = jobValue.MemberEnd();

                                    { // Job Id
                                        auto memberIt = jobValue.FindMember("jobId");
                                        if (endMemberIt == memberIt) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[]' members must contain 'jobId'");
                                            success = false;
                                            break;
                                        }
                                        else if (!(memberIt->value.IsInt64())) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[].jobId' must be an Int64.");
                                            success = false;
                                            break;
                                        }
                                        else {
                                            job.id = memberIt->value.GetInt64();
                                        }
                                    }

                                    { // Job State
                                        auto memberIt = jobValue.FindMember("jobState");
                                        if (endMemberIt == memberIt) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[]' members must contain 'jobState'");
                                            success = false;
                                            break;
                                        }
                                        else if (!(memberIt->value.IsString())) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[].jobState' must be a String.");
                                            success = false;
                                            break;
                                        }
                                        else {
                                            const std::string& state = memberIt->value.GetString();
                                            job.state = jobStateFromString(state);
                                            if (JobState::UNKNOWN == job.state) {
                                                AIS_LOG_ERROR("SendJobs 'body.jobs[].jobState' unknown value '%s'", state.c_str());
                                                success = false;
                                                break;
                                            }
                                        }
                                    }

                                    { // Is Loaded
                                        auto memberIt = jobValue.FindMember("isLoaded");
                                        if (endMemberIt == memberIt) {
                                            job.isLoaded = false;
                                        }
                                        else if (memberIt->value.IsNull()) {
                                            job.isLoaded = false;
                                        }
                                        else if (!(memberIt->value.IsBool())) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[].isLoaded' must be a Bool.");
                                            success = false;
                                            break;
                                        }
                                        else {
                                            job.isLoaded = memberIt->value.GetBool();
                                        }
                                    }

                                    { // Ready Date Time
                                        auto memberIt = jobValue.FindMember("readyDateTime");
                                        if (endMemberIt == memberIt) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[]' members must contain 'readyDateTime'");
                                            success = false;
                                            break;
                                        }
                                        else if (!(memberIt->value.IsString())) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[].readyDateTime' must be a String");
                                            success = false;
                                            break;
                                        }
                                        else {
                                            job.readyTime = tes_common_ais::getTimeISO8601UTC(memberIt->value.GetString());
                                            if (job.readyTime.min() == job.readyTime) {
                                                AIS_LOG_ERROR("SendJobs 'body.jobs[].readyDateTime' could not be parsed");
                                                success = false;
                                                break;
                                            }
                                        }
                                    }

                                    { // Zone Id
                                        auto memberIt = jobValue.FindMember("zoneId");
                                        if (endMemberIt == memberIt) {
                                            job.zoneId = INT32_MIN;
                                        }
                                        else if (memberIt->value.IsNull()) {
                                            job.zoneId = INT32_MIN;
                                        }
                                        else if (!(memberIt->value.IsInt())) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[].zoneId' must be an Int.");
                                            success = false;
                                            break;
                                        }
                                        else {
                                            job.zoneId = memberIt->value.GetInt();
                                        }
                                    }

                                    { // Zone Name
                                        auto memberIt = jobValue.FindMember("zoneName");
                                        if (endMemberIt == memberIt) {
                                            job.zoneName.clear();
                                        }
                                        else if (memberIt->value.IsNull()) {
                                            job.zoneName.clear();
                                        }
                                        else if (!(memberIt->value.IsString())) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[].zoneName' must be a String.");
                                            success = false;
                                            break;
                                        }
                                        else {
                                            job.zoneName = memberIt->value.GetString();
                                        }
                                    }

                                    { // Site Id
                                        auto memberIt = jobValue.FindMember("siteId");
                                        if (endMemberIt == memberIt) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[]' members must contain 'siteId'");
                                            success = false;
                                            break;
                                        }
                                        else if (!(memberIt->value.IsInt())) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[].siteId' must be an Int.");
                                            success = false;
                                            break;
                                        }
                                        else {
                                            job.siteId = memberIt->value.GetInt();
                                        }
                                    }

                                    { // Instruction
                                        auto memberIt = jobValue.FindMember("instruction");
                                        if (endMemberIt == memberIt) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[]' members must contain 'instruction'");
                                            success = false;
                                            break;
                                        }
                                        else if (!(memberIt->value.IsObject())) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[].instruction' must be an Object.");
                                        }
                                        else {
                                            const auto& instValue = memberIt->value;
                                            auto endMemberIt2 = instValue.MemberEnd();

                                            { // Truck Id
                                                auto memberIt2 = instValue.FindMember("truckId");
                                                if (endMemberIt2 == memberIt2) {
                                                    job.instruction.truckId = INT64_MIN;
                                                }
                                                else if (memberIt2->value.IsNull()) {
                                                    job.instruction.truckId = INT64_MIN;
                                                }
                                                else if (!(memberIt2->value.IsInt64())) {
                                                    AIS_LOG_ERROR("SendJobs 'body.jobs[].instruction.truckId' must be an Int64.");
                                                    success = false;
                                                    break;
                                                }
                                                else {
                                                    job.instruction.truckId = memberIt2->value.GetInt64();
                                                }
                                            }

                                            { // Truck Name
                                                auto memberIt2 = instValue.FindMember("truckName");
                                                if (endMemberIt2 == memberIt2) {
                                                    AIS_LOG_ERROR("SendJobs 'body.jobs[].instruction' members must contain 'truckName'");
                                                    success = false;
                                                    break;
                                                }
                                                else if (!(memberIt2->value.IsString())) {
                                                    AIS_LOG_ERROR("SendJobs 'body.jobs[].instruction.truckName' must be a String.");
                                                    success = false;
                                                    break;
                                                }
                                                else {
                                                    job.instruction.truckName = memberIt2->value.GetString();
                                                }
                                            }

                                            { // Material Id
                                                auto memberIt2 = instValue.FindMember("materialId");
                                                if (endMemberIt2 == memberIt2) {
                                                    job.instruction.materialId = INT32_MIN;
                                                }
                                                else if (memberIt2->value.IsNull()) {
                                                    job.instruction.materialId = INT32_MIN;
                                                }
                                                else if (!(memberIt2->value.IsInt())) {
                                                    AIS_LOG_ERROR("SendJobs 'body.jobs[].instruction.materialId' must be an Int.");
                                                    success = false;
                                                    break;
                                                }
                                                else {
                                                    job.instruction.materialId = memberIt2->value.GetInt();
                                                }
                                            }

                                            { // Material Name
                                                auto memberIt2 = instValue.FindMember("materialName");
                                                if (endMemberIt2 == memberIt2) {
                                                    job.instruction.materialName.clear();
                                                }
                                                else if (memberIt2->value.IsNull()) {
                                                    job.instruction.materialName.clear();
                                                }
                                                else if (!(memberIt2->value.IsString())) {
                                                    AIS_LOG_ERROR("SendJobs 'body.jobs[].instruction.materialName' must be a String.");
                                                    success = false;
                                                    break;
                                                }
                                                else {
                                                    job.instruction.materialName = memberIt2->value.GetString();
                                                }
                                            }

                                            { // Target Material Weight
                                                auto memberIt2 = instValue.FindMember("targetMaterialWeight");
                                                if (endMemberIt2 == memberIt2) {
                                                    job.instruction.targetMaterialWeight = 0.f;
                                                }
                                                else if (memberIt2->value.IsNull()) {
                                                    job.instruction.targetMaterialWeight = 0.f;
                                                }
                                                else if (!(memberIt2->value.IsFloat())) {
                                                    AIS_LOG_ERROR("SendJobs 'body.jobs[].instruction.targetMaterialWeight' must be a Float.");
                                                    success = false;
                                                    break;
                                                }
                                                else {
                                                    job.instruction.targetMaterialWeight = memberIt2->value.GetFloat();
                                                }
                                            }
                                        }
                                    }

                                    { // Result
                                        auto memberIt = jobValue.FindMember("result");
                                        if (endMemberIt == memberIt) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[]' members must contain 'result'");
                                            success = false;
                                            break;
                                        }
                                        else if (!(memberIt->value.IsObject())) {
                                            AIS_LOG_ERROR("SendJobs 'body.jobs[].result' must be an Object.");
                                        }
                                        else {
                                            const auto& resultValue = memberIt->value;
                                            auto endMemberIt2 = resultValue.MemberEnd();

                                            { // Loader Code
                                                auto memberIt2 = resultValue.FindMember("loaderCode");
                                                if (endMemberIt2 == memberIt2) {
                                                    job.result.loaderCode.clear();
                                                }
                                                else if (memberIt2->value.IsNull()) {
                                                    job.result.loaderCode.clear();
                                                }
                                                else if (!(memberIt2->value.IsString())) {
                                                    AIS_LOG_ERROR("SendJobs 'body.jobs[].result.loaderCode' must be a String.");
                                                    success = false;
                                                    break;
                                                }
                                                else {
                                                    job.result.loaderCode = memberIt2->value.GetString();
                                                }
                                            }

                                            { // Loader Pass Count
                                                auto memberIt2 = resultValue.FindMember("loaderPassCount");
                                                if (endMemberIt2 == memberIt2) {
                                                    job.result.loaderPassCount = 0;
                                                }
                                                else if (memberIt2->value.IsNull()) {
                                                    job.result.loaderPassCount = 0;
                                                }
                                                else if (!(memberIt2->value.IsInt())) {
                                                    AIS_LOG_ERROR("SendJobs 'body.jobs[].result.loaderPassCount' must be an Int.");
                                                    success = false;
                                                    break;
                                                }
                                                else {
                                                    job.result.loaderPassCount = static_cast<int16_t>(memberIt2->value.GetInt());
                                                }
                                            }

                                            { // Loader Material Weight
                                                auto memberIt2 = resultValue.FindMember("loaderMaterialWeight");
                                                if (endMemberIt2 == memberIt2) {
                                                    job.result.loaderMaterialWeight = 0.f;
                                                }
                                                else if (memberIt2->value.IsNull()) {
                                                    job.result.loaderMaterialWeight = 0.f;
                                                }
                                                else if (!(memberIt2->value.IsFloat())) {
                                                    AIS_LOG_ERROR("SendJobs 'body.jobs[].result.loaderMaterialWeight' must be a Float.");
                                                    success = false;
                                                    break;
                                                }
                                                else {
                                                    job.result.loaderMaterialWeight = memberIt2->value.GetFloat();
                                                }
                                            }
                                        }
                                    }

                                } while (false);

                                if (success) {
                                    jobs.push_back(std::move(job));
                                    // keep going.
                                }
                                else {
                                    break;
                                }
                            }
                            else {
                                // Schema Error
                                AIS_LOG_ERROR("SendJobs message 'body.jobs' contains non-object.");
                                success = false;
                                break;
                            }
                        }

                        // If we are successful so far, get the jobs hash
                        if (success) {
                            AIS_LOG_NOTICE("SendJobs message received with %d jobs", jobs.size());

                            auto jobsHashMemberIt = bodyValue.FindMember("jobsHash");
                            if (bodyValue.MemberEnd() == jobsHashMemberIt) {
                                // Missing
                                AIS_LOG_NOTICE("SendJobs message has missing 'jobsHash'");
                                jobsHash = 0;
                            }
                            else if (jobsHashMemberIt->value.IsNull()) {
                                AIS_LOG_NOTICE("SendJobs message has null 'jobsHash'");
                                jobsHash = 0;
                            }
                            else if (jobsHashMemberIt->value.IsInt64()) {
                                jobsHash = jobsHashMemberIt->value.GetInt64();
                                AIS_LOG_NOTICE("SendJobs message has 'jobsHash' = %lld", jobsHash);
                            }
                            else if (jobsHashMemberIt->value.IsString()) {
                                std::string jobsHashStr = jobsHashMemberIt->value.GetString();
                                jobsHash = std::strtoll(jobsHashStr.c_str(), nullptr, 10);
                                AIS_LOG_NOTICE("SendJobs message has 'jobsHash' = %lld", jobsHash);
                            }
                            else {
                                AIS_LOG_ERROR("SendJobs message 'body.jobsHash' should be either Int64 or String.");
                                jobsHash = 0;
                            }
                        }
                    }
                    else {
                        // Schema Error
                        AIS_LOG_ERROR("SendJobs message 'body.jobs' not array.");
                        success = false;
                    }
                }
                else {
                    // Schema Error
                    AIS_LOG_ERROR("SendJobs message 'body' not object.");
                    success = false;
                }
            }
            else {
                // Error (in status code)
                AIS_LOG_ERROR("SendJobs message status code: %d", statusCode);
                success = false;
            }
        }
        return success;
    }

    void notifyInboundMessageInput(void) {
        if (nullptr != iotHubInboundMessageInput_) {
            IoTHubCommsInboundMessage msg;
            while (iotHubInboundMessageInput_->get(msg)) {
                // Is this a file type I care about?
                // Switch on file type.
                switch (msg.fileType) {

                // Get Sites Response
                case (getSitesResponseFileId_): {
                    std::shared_ptr<std::vector<Site>> pSites;

                    AIS_LOG_NOTICE("GetSitesResponse message received.");

                    if (parseGetSitesResponse(msg, pSites)) {
                        // Notify of new sites
                        std::lock_guard<std::mutex> lck(getSitesPromisesMtx_);
                        for (auto& pe : getSitesPromises_) {
                            pe.p.set_value(pSites);
                        }
                        getSitesPromises_.clear();
                    }
                    else {
                        // Notify of error
                        std::lock_guard<std::mutex> lck(getSitesPromisesMtx_);
                        for (auto& pe : getSitesPromises_) {
                            pe.p.set_exception(std::make_exception_ptr(std::exception()));
                        }
                        getSitesPromises_.clear();
                    }
                    break;
                }

                // Select Site Response
                case (selectSiteResponseFileId_): {
                    // Not doing anything with this right now.
                    AIS_LOG_NOTICE("SelectSiteResponse message received.");

                    AIS_LOG_NOTICE("Parsing message of size %d", msg.messageContents.size());

                    { // Log the message contents
                        // SIGSEGV, Segmentation Fault occurs if the formatted string is > 1024 characters.
                        // This is a bug in va_str that reuses a va_list multiple times.
                        std::string temp((const char*)msg.messageContents.data(), std::min<std::size_t>(msg.messageContents.size(), 1000));
                        AIS_LOG_NOTICE("\n%s\n", temp.c_str());
                    }

                    break;
                }

                // Send Jobs
                case (sendJobsFileId_): {
                    std::vector<Job> jobs;
                    int64_t jobsHash;

                    AIS_LOG_NOTICE("SendJobs message received.");

                    if (!parseSendJobs(msg, jobs, jobsHash)) {
                        jobs.clear();
                        jobsHash = 0;
                    }

                    { // Notify the callback
                        std::lock_guard<std::mutex> lck(jobsListenerMtx_);
                        if (jobsListener_) {
                            jobsListener_(std::move(jobs), jobsHash);
                        }
                    }
                    break;
                }

                // Update Job Response
                case (updateJobResponseFileId_): {
                    // Not doing anything with this right now.
                    AIS_LOG_NOTICE("UpdateJobResponse message received.");

                    AIS_LOG_NOTICE("Parsing message of size %d", msg.messageContents.size());

                    { // Log the message contents
                        // SIGSEGV, Segmentation Fault occurs if the formatted string is > 1024 characters.
                        // This is a bug in va_str that reuses a va_list multiple times.
                        std::string temp((const char*)msg.messageContents.data(), std::min<std::size_t>(msg.messageContents.size(), 1000));
                        AIS_LOG_NOTICE("\n%s\n", temp.c_str());
                    }

                    break;
                }

                default: {
                    // This is not a file type we are looking for.
                    break;
                }
                }
            }
        }
    }

    void notifyOutboundReturnInput(void) {
        if (nullptr != iotHubOutboundReturnInput_) {
            IoTHubCommsOutboundReturn ret;
            while (iotHubOutboundReturnInput_->get(ret)) {
                if (ret.appName != appName_) {
                    // This is not for me, continue.
                    continue;
                }

                // This is for me.
                // Switch on file type.
                switch (ret.fileType) {

                // Get Sites Request
                case(getSitesRequestFileId_): {
                    AIS_LOG_NOTICE("GetSitesRequest return received.");
                    if (ret.returnStateOk()) {
                        // Do nothing with this, just wait for the response message
                    }
                    else {
                        GetSitesPromise p;
                        bool foundIt = false;
                        { // Lock the get sites promises to find
                            std::lock_guard<std::mutex> lck(getSitesPromisesMtx_);
                            for (auto it = getSitesPromises_.begin(); it != getSitesPromises_.end(); ++it) {
                                if (ret.appRequestId == it->requestId) {
                                    // Something happened to this one.
                                    p.swap(it->p);
                                    getSitesPromises_.erase(it);
                                    foundIt = true;
                                    break;
                                }
                            }
                        }

                        if (foundIt) {
                            // Need to notify the future of the problem.
                            AIS_LOG_ERROR("GetSites request failure: %d", ret.returnState);
                            p.set_exception(std::make_exception_ptr(std::exception()));
                        }
                    }
                    break;
                }

                // Select Site Request
                case(selectSiteRequestFileId_): {
                    SelectSitePromise p;
                    bool foundIt = false;

                    AIS_LOG_NOTICE("SelectSiteRequest return received.");

                    { // Lock the get sites promises to find
                        std::lock_guard<std::mutex> lck(selectSitePromisesMtx_);
                        for (auto it = selectSitePromises_.begin(); it != selectSitePromises_.end(); ++it) {
                            if (ret.appRequestId == it->requestId) {
                                // Something happened to this one.
                                p.swap(it->p);
                                selectSitePromises_.erase(it);
                                foundIt = true;
                                break;
                            }
                        }
                    }

                    if (foundIt) {
                        if (ret.returnStateOk()) {
                            p.set_value();
                        }
                        else {
                            // Need to notify the future of the problem.
                            AIS_LOG_ERROR("SelectSite request failure: %d", ret.returnState);
                            p.set_exception(std::make_exception_ptr(std::exception()));
                        }
                    }
                    break;
                }

                // Update Job Request
                case(updateJobRequestFileId_): {
                    UpdateJobPromise p;
                    bool foundIt = false;

                    AIS_LOG_NOTICE("UpdateJobRequest return received.");

                    { // Lock the get sites promises to find
                        std::lock_guard<std::mutex> lck(updateJobPromisesMtx_);
                        for (auto it = updateJobPromises_.begin(); it != updateJobPromises_.end(); ++it) {
                            if (ret.appRequestId == it->requestId) {
                                // Something happened to this one.
                                p.swap(it->p);
                                updateJobPromises_.erase(it);
                                foundIt = true;
                                break;
                            }
                        }
                    }

                    if (foundIt) {
                        if (ret.returnStateOk()) {
                            p.set_value();
                        }
                        else {
                            // Need to notify the future of the problem.
                            AIS_LOG_ERROR("UpdateJob request failure: %d", ret.returnState);
                            p.set_exception(std::make_exception_ptr(std::exception()));
                        }
                    }
                    break;
                }
                default: {
                    break;
                }
                }
            }
        }
    }

    static constexpr uint32_t getSitesRequestFileId_ = 10370;
    static constexpr uint32_t getSitesResponseFileId_ = 10371;
    static constexpr uint32_t selectSiteRequestFileId_ = 10372;
    static constexpr uint32_t selectSiteResponseFileId_ = 10373;
    static constexpr uint32_t sendJobsFileId_ = 10374;
    static constexpr uint32_t updateJobRequestFileId_ = 10375;
    static constexpr uint32_t updateJobResponseFileId_ = 10376;

    bool started_;

    std::string appName_;

    // IoTHubComms Interface Channels
    IoTHubCommsInboundMessageInput* iotHubInboundMessageInput_;
    IoTHubCommsOutboundMessageOutput* iotHubOutboundMessageOutput_;
    IoTHubCommsOutboundReturnInput* iotHubOutboundReturnInput_;

    boost::signals2::connection iotHubInboundMessageInputConnection_;
    boost::signals2::connection iotHubOutboundReturnInputConnection_;

    std::mutex jobsListenerMtx_;
    JobsListener jobsListener_;

    typedef std::promise<std::shared_ptr<const std::vector<Site>>> GetSitesPromise;
    typedef struct {
        uint32_t requestId = 0;
        // Ignore response message id for now, any response will fulfill this.
        GetSitesPromise p;
    } GetSitesPromiseEntry;

    static constexpr uint32_t getSitesPromisesMaxSize_ = 3;
    std::mutex getSitesPromisesMtx_;
    std::list<GetSitesPromiseEntry> getSitesPromises_;

    typedef std::promise<void> SelectSitePromise;
    typedef struct {
        uint32_t requestId = 0;
        // Ignore response message id for now, we just care that it got sent off.
        SelectSitePromise p;
    } SelectSitePromiseEntry;

    static constexpr uint32_t selectSitePromisesMaxSize_ = 1;
    std::mutex selectSitePromisesMtx_;
    std::list<SelectSitePromiseEntry> selectSitePromises_;

    typedef std::promise<void> UpdateJobPromise;
    typedef struct {
        uint32_t requestId = 0;
        // Ignore response message id for now, we just care that it got sent off.
        UpdateJobPromise p;
    } UpdateJobPromiseEntry;

    static constexpr uint32_t updateJobPromisesMaxSize_ = 1;
    std::mutex updateJobPromisesMtx_;
    std::list<UpdateJobPromiseEntry> updateJobPromises_;
};

}

#endif
