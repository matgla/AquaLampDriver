#include "timer/timeoutTimer.hpp"

#include "hal/time/time.hpp"
#include "utils/types.hpp"

namespace timer
{

TimeoutTimer::TimeoutTimer(const u64 time, TimerCallback callback)
    : callback_(std::move(callback)), startTime_(hal::time::Time::milliseconds()), time_(time),
      enabled_(true)
{
}

TimeoutTimer::TimeoutTimer()
    : callback_(nullptr),
      enabled_(false)
{
}

void TimeoutTimer::run()
{
    if (!enabled_)
    {
        return;
    }

    if (hal::time::Time::milliseconds() - startTime_ >= time_)
    {
        fire();
    }
}

void TimeoutTimer::start(u64 time)
{
    time_ = time;
    startTime_ = hal::time::Time::milliseconds();
    enabled_ = true;
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
