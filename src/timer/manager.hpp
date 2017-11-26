#pragma once

#include <array>
#include <cstdint>
#include <utility>

#include "timer/intervalTimer.hpp"
#include "timer/timeoutTimer.hpp"

namespace timer
{
using TimerId = u16;

template <std::size_t IntervalsSize, std::size_t TimeoutsSize>
class Manager
{
public:
    Manager()
        : logger_("TimerManager")
    {
        for (auto& timeout : timeouts_)
        {
            timeout.second = false;
        }

        for (auto& interval : intervals_)
        {
            interval.second = false;
        }
    }

    TimerId setTimeout(u32 milliseconds, TimerCallback callback)
    {
        for (TimerId id = 0; id < timeouts_.size(); ++id)
        {
            auto& timeout = timeouts_[id];
            if (timeout.second == false)
            {
                timeout.second = true;
                timeout.first.start(milliseconds, callback);
                logger_.info() << "Started timer with id: " << id;
                return id;
            }
        }

        logger_.warning() << "No empty slots for timeouts";
        return -1;
    }

    TimerId setInterval(u64 milliseconds, TimerCallback callback, int times = -1)
    {
        for (TimerId id = 0; id < intervals_.size(); ++id)
        {
            auto& interval = intervals_[id];
            if (interval.second == false)
            {
                interval.second = true;
                interval.first.start(milliseconds, callback, times);
                logger_.info() << "Started interval with id: " << id;
                return id;
            }
        }

        logger_.warning() << "No empty slots for intervals";
        return -1;
    }

    TimeoutTimer* getTimeoutTimer(TimerId id)
    {
        if (0 > id || timeouts_.size() <= id)
        {
            logger_.error() << "Requested nonexisting timeout, id: " << id;
            return nullptr;
        }
        return &timeouts_[id].first;
    }

    IntervalTimer* getIntervalTimer(TimerId id)
    {
        if (0 > id || intervals_.size() <= id)
        {
            logger_.error() << "Requested nonexisting interval, id: " << id;
            return nullptr;
        }
        return &intervals_[id].first;
    }

    bool removeTimeoutTimer(TimerId id)
    {
        if (0 > id || timeouts_.length() <= id)
        {
            logger_.error() << "Trying to remove not existing timeout, id: " << id;
            return false;
        }

        timeouts_[id].first.cancel();
        timeouts_[id].second = false;
    }

    bool removeIntervalTimer(TimerId id)
    {
        if (0 > id || intervals_.length() <= id)
        {
            logger_.error() << " Trying to remove not existing interval, id: " << id;
            return false;
        }

        intervals_[id].first.cancel();
        intervals_[id].second = false;
    }

    void run()
    {
        for (auto& timeout : timeouts_)
        {
            if (timeout.second)
            {
                timeout.first.run();
                if (!timeout.first.enabled())
                {
                    timeout.second = false;
                }
            }
        }

        for (auto& interval : intervals_)
        {
            if (interval.second)
            {
                interval.first.run();
                if (!interval.first.enabled())
                {
                    interval.second = false;
                }
            }
        }
    }

private:
    using ManagedTimeout    = std::pair<TimeoutTimer, bool>;
    using ManagedInterval   = std::pair<IntervalTimer, bool>;
    using TimeoutContainer  = std::array<ManagedTimeout, TimeoutsSize>;
    using IntervalContainer = std::array<ManagedInterval, TimeoutsSize>;

    TimeoutContainer timeouts_;
    IntervalContainer intervals_;
    logger::Logger logger_;
};

} // namespace timer
