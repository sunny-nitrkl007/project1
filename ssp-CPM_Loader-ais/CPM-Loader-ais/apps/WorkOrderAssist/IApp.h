#ifndef WORKORDERASSIST__IAPP_H
#define WORKORDERASSIST__IAPP_H

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

#include <interfaces/WorkOrderAssist/Settings.hpp>

#include "Data.h"

namespace woa_app {

/*
 * Handles local caching
 */
class IApp {
public:
    virtual ~IApp() {};

    /*
     * Gets the vector of sites from the back office.
     * This will block.
     */
    virtual bool getSites(std::vector<Site>& sites, int32_t& activeSiteId) = 0;

    /*
     * Selects the provided site, releasing the current job if
     * The site is changed.  This will block.
     */
    virtual bool refreshSite() = 0;
    virtual bool selectSite(int32_t siteId, bool async) = 0;

    /*
     * Selects, releases, or completes the specified (or currently active) job.
     * This will block.
     */
    virtual bool selectJob(int64_t jobId, const woa_app::Job::TimePoint& dateTime, bool async) = 0;
    virtual bool releaseJob(int64_t jobId, bool async) = 0;
    virtual bool completeJob(int64_t jobId, int16_t passCount, float materialWeight, const Job::TimePoint& dateTime, bool async) = 0;

    /*
     * Iterates through all jobs and calls the provided function for each job.
     * This visits each job in a thread safe way.  The provided function should
     * take care to be fast so that it is not locking the jobs collection for long.
     * Returns the active job id.
     */
    virtual int64_t visitJobs(std::function<void(const Job&)> visit) = 0;

    /*
     * Reads and writes the application settings.
     */
    virtual void readSettings(WorkOrderAssistSettings& settings) const = 0;
    virtual void writeSettings(const WorkOrderAssistSettings& settings) = 0;
    virtual bool isEnabled() const = 0;
};

}

#endif
