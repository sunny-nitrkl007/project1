#ifndef WORKORDERASSIST__IHUBSERVICE_H
#define WORKORDERASSIST__IHUBSERVICE_H

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

#include "Data.h"

namespace woa_app {

/*
 * Handles local caching
 */
class IHubService {
public:
    virtual ~IHubService() {};

    /*
     * Start the hub service
     */
    virtual bool start() = 0;

    /*
     * Stop the hub service
     */
    virtual bool stop() = 0;

    /*
     * Get the list of sites available to this asset from the hub.
     * On success, the sites vector will contain the new sites.
     * On failure, the sites vector will be left untouched.
     * This is a blocking function call and returns true for success, else false.
     */
    virtual bool getSites(std::vector<Site>& sites) = 0;

    /*
     * Select the site.
     * This is a blocking function call and returns true for success, else false.
     */
    virtual bool selectSite(int32_t siteId, int64_t jobsHash, const Job::TimePoint& dateTime) = 0;

    /*
     * Register jobs listener
     * This callback's argument is an rvalue reference to facilitate moving the vector instead of copying it.
     * The callback will be called from the hub's thread context, so protect as needed.
     */
    typedef std::function<void(std::vector<Job>&&, int64_t)> JobsListener;
    virtual void registerJobsListener(const JobsListener& listener) = 0;

    /*
     * Update a job.
     * These are blocking function calls and return true for success, else false.
     */
    virtual bool updateJobStatusStartDoing(int32_t siteId, int64_t jobId, int64_t stopDoingJobId, const Job::TimePoint& dateTime, const std::string& loaderCode) = 0;

    virtual bool updateJobStatusLoaded(int32_t siteId, int64_t jobId, int16_t passCount, float materialWeight, const Job::TimePoint& dateTime, const std::string& loaderCode) = 0;

    virtual bool updateJobStatusStopDoing(int32_t siteId, int64_t jobId) = 0;
};

}

#endif
