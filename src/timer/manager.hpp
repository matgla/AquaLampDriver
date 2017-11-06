#pragma once

#include <array>
#include <cstdint>
#include <pair>

#include "timer/intervalTimer.hpp"
#include "timer/timeoutTimer.hpp"

namespace timer
{

template <std::size_t IntervalsSize, std::size_t TimeoutsSize>
class Manager
{
public:
    using TimerId = u16;

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

    TimerId setTimeout(u32 milliseconds, ITimer::TimerCallback callback)
    {
        for (TimerId id = 0; i < timeouts_.size(); ++id)
        {
            auto& timeout = timeouts_[id];
            if (timeout.second == false)
            {
                timeout.second = true;
                timeout.first.start(milliseconds);
                logger_.info() << "Started timer with id: " << id;
                return id;
            }
        }

        logger_.warning() << "No empty slots for timeouts";
        return -1;
    }

    TimerId setInterval(u32 milliseconds, ITimer::TimerCallback callback, int times = -1)
    {
        for (TimerId id = 0; i < intervals_.size(); ++id)
        {
            auto& interval = intervals_[id];
            if (interval.second == false)
            {
                interval.second = true;
                interval.first.start(milliseconds);
                logger_.info() << "Started interval with id: " << id;
                return id;
            }
        }

        logger_.warning() << "No empty slots for intervals";
        return -1;
    }

    TimeoutTimer& getTimeoutTimer(TimerId id)
    {
        if (0 > id || timeouts_.length() <= id)
        {
            logger_.error() << "Requested nonexisting timeout, id: " << id;
            return nullptr;
        }
        return timeouts_[id].first;
    }

    IntervalTimer& getIntervalTimer(TimerId id)
    {
        if (0 > id || intervals_.length() <= id)
        {
            logger_.error() << "Requested nonexisting interval, id: " << id;
            return nullptr;
        }
        return intervals_[id].first;
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
            }
        }

        for (auto& interval : intervals_)
        {
            if (interval.second)
            {
                interval.first.run();
            }
        }
    }

private:
    using ManagedTimeout = std::pair<TimeoutTimer, bool>;
    using ManagedInterval = std::pair<IntervalTimer, bool>;
    using TimeoutContainer = std::array<ManagedTimeout, TimeoutsSize>;
    using IntervalContainer = std::array<ManagedInterval, TimeoutsSize>;

    TimeoutContainer timeouts_;
    TimeoutContainer intervals_;
    logger::Logger logger_;
};

} // namespace timer
