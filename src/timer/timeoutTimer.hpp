#pragma once
#include "utils/types.hpp"

namespace timer
{

class TimeoutTimer
{
public:
    TimeoutTimer(u64 time, TimerCallback callback);
    TimeoutTimer();

    void start(u64 time, TimerCallback callback = nullptr);
    void run();
    void cancel();
    u64 elapsed();
    bool enabled() const;

protected:
    void fire();

    TimerCallback callback_;
    u64 startTime_;
    u64 time_;
    u64 lastTime_;
    bool enabled_;
};

} // namespace timer
