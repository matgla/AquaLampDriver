#pragma once
#include "timer/ITimer.hpp"
#include "utils/types.hpp"

namespace timer
{

class TimeoutTimer : public ITimer
{
  public:
    TimeoutTimer(u64 time, TimerCallback callback);
    TimeoutTimer();

    void start(u64 time);
    void start(u64 time, TimerCallback callback);
    void run() override;
    void cancel() override;
    u64 elapsed();
    bool enabled() const override;

  protected:
    void fire() override;

    TimerCallback callback_;
    u64 startTime_;
    u64 time_;
    u64 lastTime_;
    bool enabled_;
};

} // namespace timer
