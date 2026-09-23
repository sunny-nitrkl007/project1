#ifndef WORKORDERASSIST__MOCKHUBSERVICE_H
#define WORKORDERASSIST__MOCKHUBSERVICE_H

#include <cstdint>
#include <vector>
#include <functional>
#include <unordered_map>
#include <stdexcept>

#include <ais/log/Logger.h>

#include "IHubService.h"
#include "Data.h"

namespace woa_app {

class MockHubService : public IHubService {
public:
    MockHubService():
        currentSiteId_(0),
        jobsListener_(),
        siteJobs_(),
        running_(false),
        t_() {
        std::unordered_map<int64_t, Job> site;

        // Site 1
        site.emplace(1,  Job(1,  JobState::TODO, false, Job::Clock::now(), 1, "Zone 1", 1, 1, "Truck 1", 1, "Material 1", 24.0f));
        site.emplace(2,  Job(2,  JobState::TODO, false, Job::Clock::now(), 1, "Zone 1", 1, 2, "Truck 2", 2, "Material 2", 24.0f));
        site.emplace(3,  Job(3,  JobState::TODO, false, Job::Clock::now(), 1, "Zone 1", 1, 3, "Truck 3", 3, "Material 3", 24.0f));
        site.emplace(4,  Job(4,  JobState::TODO, false, Job::Clock::now(), 1, "Zone 1", 1, 4, "Truck 4", 4, "Material 4", 24.0f));
        site.emplace(5,  Job(5,  JobState::TODO, false, Job::Clock::now(), 1, "Zone 1", 1, 5, "Truck 5", 5, "Material 5", 24.0f));
        siteJobs_.emplace(1, std::move(site));
        site.clear();

        // Site 2
        site.emplace(6,  Job(6,  JobState::TODO, false, Job::Clock::now(), 2, "Zone 2", 2, 1, "Truck 1", 1, "Material 1", 24.0f));
        site.emplace(7,  Job(7,  JobState::TODO, false, Job::Clock::now(), 2, "Zone 2", 2, 2, "Truck 2", 2, "Material 2", 24.0f));
        site.emplace(8,  Job(8,  JobState::TODO, false, Job::Clock::now(), 2, "Zone 2", 2, 3, "Truck 3", 3, "Material 3", 24.0f));
        site.emplace(9,  Job(9,  JobState::TODO, false, Job::Clock::now(), 2, "Zone 2", 2, 4, "Truck 4", 4, "Material 4", 24.0f));
        site.emplace(10, Job(10, JobState::TODO, false, Job::Clock::now(), 2, "Zone 2", 2, 5, "Truck 5", 5, "Material 5", 24.0f));
        siteJobs_.emplace(2, std::move(site));
        site.clear();

        // Site 3
        site.emplace(11, Job(11, JobState::TODO, false, Job::Clock::now(), 1, "Zone 1", 3, 1, "Truck 1 - Carrier 1", 1, "Material 1", 24.0f));
        site.emplace(12, Job(12, JobState::TODO, false, Job::Clock::now(), 2, "Zone 2", 3, 2, "Truck 2 - Carrier 2", 2, "Material 2", 24.0f));
        site.emplace(13, Job(13, JobState::TODO, false, Job::Clock::now(), 3, "Zone 3", 3, 3, "Truck 3 - Carrier 3", 3, "Material 3", 24.0f));
        site.emplace(14, Job(14, JobState::TODO, false, Job::Clock::now(), 4, "Zone 4", 3, 4, "Truck 4 - Carrier 4", 4, "Material 4", 24.0f));
        site.emplace(15, Job(15, JobState::TODO, false, Job::Clock::now(), 5, "Zone 5", 3, 5, "Truck 5 - Carrier 5", 5, "Material 5", 24.0f));
        siteJobs_.emplace(3, std::move(site));
        site.clear();

        // Site 4
        site.emplace(16, Job(16, JobState::TODO, false, Job::Clock::now(), 1, "Zone 1", 4, 1, "Truck 1", 1, "Material 1", 24.0f));
        site.emplace(17, Job(17, JobState::TODO, false, Job::Clock::now(), 2, "Zone 2", 4, 2, "Truck 2", 2, "Material 2", 24.0f));
        site.emplace(18, Job(18, JobState::TODO, false, Job::Clock::now(), 3, "Zone 3", 4, 3, "Truck 3", 3, "Material 3", 24.0f));
        site.emplace(19, Job(19, JobState::TODO, false, Job::Clock::now(), 4, "Zone 4", 4, 4, "Truck 4", 4, "Material 4", 24.0f));
        site.emplace(20, Job(20, JobState::TODO, false, Job::Clock::now(), 5, "Zone 5", 4, 5, "Truck 5", 5, "Material 5", 24.0f));
        siteJobs_.emplace(4, std::move(site));
        site.clear();
    }

    virtual ~MockHubService() {
        stop();
    }


    /*
     * Start the hub service
     */
    bool start() {
        stop(); // Kill if currently running

        // Start up a new thread
        running_ = true;
        t_ = std::thread([this]() { run(); });

        return true;
    }

    /*
     * Stop the hub service
     */
    bool stop() {
        // Kill thread.
        if (t_.joinable()) {
            running_ = false;
            t_.join();
        }
        return true;
    }

    /*
     * Get the list of sites available to this asset from the hub.
     * On success, the sites vector will contain the new sites.
     * On failure, the sites vector will be left untouched.
     * This is a blocking function call and returns true for success, else false.
     */
    bool getSites(std::vector<Site>& sites) {
        std::this_thread::sleep_for(std::chrono::seconds(3)); // simulate latency
        sites.clear();
        sites.push_back(Site{1, "Site 1"});
        sites.push_back(Site{2, "Site 2"});
        sites.push_back(Site{3, "Site 3"});
        sites.push_back(Site{4, "Site 4"});
        AIS_LOG_NOTICE("GetSites successful.");
        return true;
    }

    /*
     * Select the site.
     * This is a blocking function call and returns true for success, else false.
     */
    bool selectSite(int32_t siteId, int64_t jobsHash, const Job::TimePoint& dateTime) {
        std::this_thread::sleep_for(std::chrono::seconds(3)); // simulate latency
        currentSiteId_ = siteId;
        AIS_LOG_NOTICE("SelectSite successful.");
        return true;
    }

    /*
     * Register jobs listener
     * This callback's argument is an rvalue reference to facilitate moving the vector instead of copying it.
     * The callback will be called from the hub's thread context, so protect as needed.
     */
    void registerJobsListener(const JobsListener& listener) {
        jobsListener_ = listener;
    }

    /*
     * Update a job.
     * These are blocking function calls and return true for success, else false.
     */
    bool updateJobStatusStartDoing(int32_t siteId, int64_t jobId, int64_t stopDoingJobId, const Job::TimePoint& /*dateTime*/, const std::string& loaderCode) {
        bool success;
        std::this_thread::sleep_for(std::chrono::seconds(3)); // simulate latency

        // If there is a job to stop doing, take care of that first.
        if (stopDoingJobId >= 0) {
            try {
                Job& job = siteJobs_.at(siteId).at(stopDoingJobId);
                job.state = JobState::TODO;
                job.isLoaded = false;
                AIS_LOG_NOTICE("UpdateJob successful.");
            }
            catch (const std::out_of_range& e) {
                AIS_LOG_ERROR("UpdateJob error '%s'", e.what());
            }
        }

        // Now start doing the new job
        try {
            Job& job = siteJobs_.at(siteId).at(jobId);
            job.state = JobState::DOING;
            job.isLoaded = false;
            job.result.loaderCode = loaderCode;
            AIS_LOG_NOTICE("UpdateJob successful.");
            success = true;
        }
        catch (const std::out_of_range& e) {
            AIS_LOG_ERROR("UpdateJob error '%s'", e.what());
            success = false;
        }

        return success;
    }

    bool updateJobStatusLoaded(int32_t siteId, int64_t jobId, int16_t passCount, float materialWeight, const Job::TimePoint& /*dateTime*/, const std::string& loaderCode) {
        bool success;
        std::this_thread::sleep_for(std::chrono::seconds(3)); // simulate latency
        try {
            Job& job = siteJobs_.at(siteId).at(jobId);
            job.state = JobState::DOING;
            job.isLoaded = true;
            job.result.loaderCode = loaderCode;
            job.result.loaderPassCount = passCount;
            job.result.loaderMaterialWeight = materialWeight;
            AIS_LOG_NOTICE("UpdateJob successful.");
            success = true;
        }
        catch (const std::out_of_range& e) {
            AIS_LOG_ERROR("UpdateJob error '%s'", e.what());
            success = false;
        }
        return success;
    }

    bool updateJobStatusStopDoing(int32_t siteId, int64_t jobId) {
        bool success;
        std::this_thread::sleep_for(std::chrono::seconds(3)); // simulate latency
        try {
            Job& job = siteJobs_.at(siteId).at(jobId);
            job.state = JobState::TODO;
            job.isLoaded = false;
            AIS_LOG_NOTICE("UpdateJob successful.");
            success = true;
        }
        catch (const std::out_of_range& e) {
            AIS_LOG_ERROR("UpdateJob error '%s'", e.what());
            success = false;
        }
        return success;
    }

private:
    void run() {
        // Do stuff while still running
        while (running_) {
            if (jobsListener_) {
                std::vector<Job> jobs;
                // Find all jobs for the current site
                try {
                    const std::unordered_map<int64_t, Job>& js = siteJobs_.at(currentSiteId_);
                    for (const auto& p : js) {
                        const Job& j = p.second;
                        if (!j.isLoaded) {
                            if ((j.state == JobState::TODO) || (j.state == JobState::DOING)) {
                                jobs.push_back(j);
                            }
                        }
                    }
                }
                catch (const std::out_of_range& e) {
                    // nothing
                }
                jobsListener_(std::move(jobs), 0);
            }
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }

    int32_t currentSiteId_;
    JobsListener jobsListener_;
    std::unordered_map<int32_t, std::unordered_map<int64_t, Job> > siteJobs_;
    bool running_;
    std::thread t_;
};

}

#endif
