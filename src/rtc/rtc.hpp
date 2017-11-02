#pragma once

#include <functional>

#include "logger/logger.hpp"
#include "utils.hpp"

namespace rtc
{

//static bool wasInitialized;

class Rtc
{
  public:
    static Rtc& get();
    static bool wasInitialized();

    void setTime(u32 day, u32 month, u32 year, u32 hours, u32 minutes, u32 seconds);
    u32 getTime();
    u32 alarmTime();
    void setAlarm(u32 time);
    void fire();
    void setHandler(std::function<void()> handler);
    void setSecondsHandler(std::function<void()> handler);
    std::function<void()>& getSecondsHandler();

  private:
    Rtc();
    void init();
    void initNvic();
    void initSecondsInterrupt();
    std::function<void()> timerCallback_;
    std::function<void()> secondsHandler_;
    u32 alarmTime_;
    bool alarmEnabled_;
    logger::Logger logger_;
};
} // namespace rtc