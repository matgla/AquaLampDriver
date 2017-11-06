#include "timer/intervalTimer.hpp"

#include <algorithm>

#include "hal/time/time.hpp"
#include "timer/ITimer.hpp"
#include "utils/types.hpp"

namespace timer
{

IntervalTimer::IntervalTimer(const u64 time, TimerCallback callback, const int times)
    : callback_(std::move(callback)), startTime_(hal::time::Time::milliseconds()), time_(time),
      enabled_(true), times_(times)
{
}

IntervalTimer::IntervalTimer()
    : callback_(nullptr), startTime_(0), time_(0), enabled_(false), times_(-1)
{
}

void IntervalTimer::run()
{
    if (hal::time::Time::milliseconds() - startTime_ >= time_)
    {
        fire();
    }
}

void IntervalTimer::cancel()
{
    enabled_ = false;
}

bool IntervalTimer::enabled() const
{
    return enabled_;
}

void IntervalTimer::start(u64 time, TimerCallback callback, int times = 1)
{
    callback_ = callback;
    times_ = times;
    startTime_ = hal::time::Time::milliseconds();
    enabled_ = true;
    time_ = time;
}

void IntervalTimer::fire()
{
    if (enabled_)
    {
        startTime_ = hal::time::Time::milliseconds();

        if (-1 != times_)
        {
            --times_;
        }

        if (times_ == 0)
        {
            enabled_ = false;
        }

        if (callback_)
        {
            callback_();
        }
    }
}

} // namespace timer
