#ifndef WORKORDERASSIST__DATA_H
#define WORKORDERASSIST__DATA_H

#include <chrono>

namespace woa_app {

struct Site {
    int32_t id;
    std::string name;
};

enum struct JobState : uint8_t {
    TODO,
    DOING,
    DONE,
    UNKNOWN
};

inline JobState jobStateFromString(const std::string& str) {
    JobState state;
    if (("to-do" == str) || ("todo" == str)) {
        state = JobState::TODO;
    }
    else if ("doing" == str) {
        state = JobState::DOING;
    }
    else if ("done" == str) {
        state = JobState::DONE;
    }
    else {
        state = JobState::UNKNOWN;
    }
    return state;
}

inline const char* jobStateToString(JobState state, bool useHyphen = false) {
    const char* str;
    switch (state) {
    case (JobState::TODO): {
        if (useHyphen) {
            // The UI API uses a hyphen
            str = "to-do";
        }
        else {
            // The back office doesn't use a hyphen
            str = "todo";
        }
        break;
    }
    case (JobState::DOING): {
        str = "doing";
        break;
    }
    case (JobState::DONE): {
        str = "done";
        break;
    }
    default: {
        str = "unknown";
        break;
    }
    }
    return str;
}

struct Job {
    using Clock = std::chrono::system_clock;
    using TimePoint = Clock::time_point;

    Job() = default;
    Job(int64_t id_, JobState state_, bool isLoaded_, const TimePoint& readyTime_,
            int32_t zoneId_, const std::string& zoneName_,
            int32_t siteId_,
            int64_t truckId_, const std::string& truckName_,
            int32_t materialId_, const std::string& materialName_, float targetMaterialWeight_) :
                id(id_), state(state_), isLoaded(isLoaded_), readyTime(readyTime_),
                zoneId(zoneId_), zoneName(zoneName_),
                siteId(siteId_),
                instruction(truckId_, truckName_, materialId_, materialName_, targetMaterialWeight_),
                result() {}

    /*
     * Providing default member initializers so that non-static
     * instances (like local variables) are properly default initialized.
     */
    bool stale{false}; // Set to true when the job is potentially out of sync with the back office.
    int64_t id{-1};
    JobState state{JobState::UNKNOWN};
    bool isLoaded{false};
    TimePoint readyTime{TimePoint::max()};
    int32_t zoneId{-1};
    std::string zoneName{};
    int32_t siteId{-1};

    struct Instruction {
        Instruction() = default;
        Instruction(int64_t truckId_, const std::string& truckName_,
                int32_t materialId_, const std::string& materialName_, float targetMaterialWeight_) :
                    truckId(truckId_), truckName(truckName_),
                    materialId(materialId_), materialName(materialName_), targetMaterialWeight(targetMaterialWeight_) {}
        int64_t truckId{-1};
        std::string truckName{};
        int32_t materialId{-1};
        std::string materialName{};
        float targetMaterialWeight{0.f};
    } instruction;

    struct Result {
        Result() = default;
        Result(const std::string& loaderCode_, int16_t loaderPassCount_, float loaderMaterialWeight_) :
            loaderCode(loaderCode_), loaderPassCount(loaderPassCount_), loaderMaterialWeight(loaderMaterialWeight_) {}
        std::string loaderCode{};
        int16_t loaderPassCount{0};
        float loaderMaterialWeight{0.f};
    } result;
};

struct ZoneSummary {
    /*
     * Providing default member initializers so that non-static
     * instances (like local variables) are properly default initialized.
     */
    ZoneSummary() = default;
    ZoneSummary(int32_t id_, const std::string& name_, int16_t numJobs_, const Job::TimePoint& oldestJobReadyTime_) :
        id(id_), name(name_), numJobs(numJobs_), oldestJobReadyTime(oldestJobReadyTime_) {}
    int32_t id{-1};
    std::string name{};
    int16_t numJobs{0};
    Job::TimePoint oldestJobReadyTime{Job::TimePoint::max()};
};

}

#endif
