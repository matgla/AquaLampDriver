#pragma once

#include "utils/types.hpp"

namespace timer
{

class IntervalTimer
{
public:
    IntervalTimer(u64 time, TimerCallback callback, int times = -1);
    IntervalTimer();

    void run();
    void cancel();
    bool enabled() const;
    void start(u64 time, TimerCallback callback, int times = 1);

protected:
    void fire();

    TimerCallback callback_;
    u64 startTime_;
    u64 time_;
    bool enabled_;
    int times_;
};

} // namespace timer
