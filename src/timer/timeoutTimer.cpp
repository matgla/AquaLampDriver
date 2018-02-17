#include "timer/timeoutTimer.hpp"

#include "hal/time/time.hpp"
#include "utils/types.hpp"

#include "logger/logger.hpp"

namespace timer
{

TimeoutTimer::TimeoutTimer(const u64 time, TimerCallback callback)
    : callback_(std::move(callback)), startTime_(hal::time::Time::milliseconds()), time_(time),
      lastTime_(startTime_), enabled_(true)
{
}

TimeoutTimer::TimeoutTimer()
    : callback_(nullptr),
      startTime_(0),
      time_(0),
      lastTime_(0),
      enabled_(false)
{
}

void TimeoutTimer::run()
{
    if (!enabled_)
    {
        return;
    }

    lastTime_ = hal::time::Time::milliseconds();
    if (lastTime_ - startTime_ >= time_)
    {
        fire();
    }
}

u64 TimeoutTimer::elapsed()
{
    return lastTime_ - startTime_;
}

void TimeoutTimer::start(u64 time, TimerCallback callback)
{
    callback_  = callback;
    time_      = time;
    startTime_ = hal::time::Time::milliseconds();
    enabled_   = true;
}

void TimeoutTimer::restart(u64 milliseconds)
{
    time_      = milliseconds;
    startTime_ = hal::time::Time::milliseconds();
    enabled_   = true;
}


void TimeoutTimer::cancel()
{
    enabled_ = false;
}

bool TimeoutTimer::enabled() const
{
    return enabled_;
}


void TimeoutTimer::fire()
{
    if (enabled_)
    {
        enabled_ = false;
        if (callback_)
        {
            callback_();
        }
    }
}

} // namespace timer
