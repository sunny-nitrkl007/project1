#pragma once

#include <algorithm>
#include <cstdint>
#include <deque>

namespace switch_input
{
enum TaskState { Initializing = 0, WaitingForPreConditions = 1, ExecutiveRunning = 2,
                 ShuttingDown = 3, Unknown = 4 };

struct HealthStatistics
{
    double rate = 0.0;
    double maximum = 0.0;
    double lifetimeMaximum = 0.0;
    double sleep = 0.0;
    double recentRate = 0.0;
    double recentMaximum = 0.0;
    uint32_t cycles = 0;
    uint32_t late = 0;
};

// All times are measured steady-clock seconds; the caller serializes access.
class HealthTracker
{
public:
    explicit HealthTracker(double now = 0.0) : intervalStart_(now) {}

    void complete(double now, double processing, double period)
    {
        ++statistics_.cycles;
        ++intervalCycles_;
        if (processing > period) {
            ++statistics_.late;
        }
        intervalMaximum_ = std::max(intervalMaximum_, processing);
        statistics_.lifetimeMaximum = std::max(statistics_.lifetimeMaximum, processing);
        update(now);
    }

    void waited(double duration) { statistics_.sleep += std::max(0.0, duration); }

    HealthStatistics report(double now)
    {
        update(now);
        history_.push_back({statistics_.rate, statistics_.maximum});
        if (history_.size() > 5) {
            history_.pop_front();
        }
        statistics_.recentRate = 0.0;
        statistics_.recentMaximum = 0.0;
        unsigned int samples = 0;
        for (size_t i = 1; i < history_.size(); ++i) {
            if (history_[i].rate != 0.0) {
                statistics_.recentRate += history_[i].rate;
                ++samples;
            }
            statistics_.recentMaximum = std::max(statistics_.recentMaximum, history_[i].maximum);
        }
        if (samples != 0) {
            statistics_.recentRate /= samples;
        }
        return statistics_;
    }

private:
    void update(double now)
    {
        const double interval = now - intervalStart_;
        if (interval >= 1.0) {
            statistics_.rate = intervalCycles_ / interval;
            statistics_.maximum = intervalMaximum_;
            intervalStart_ = now;
            intervalCycles_ = 0;
            intervalMaximum_ = 0.0;
        }
    }

    struct Sample { double rate; double maximum; };
    HealthStatistics statistics_;
    std::deque<Sample> history_;
    double intervalStart_;
    uint32_t intervalCycles_ = 0;
    double intervalMaximum_ = 0.0;
};
}
