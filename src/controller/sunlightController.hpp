#pragma once

#include <ctime>

#include "logger/logger.hpp"

namespace controller
{

class SunlightController
{
public:
    enum class State
    {
        Off,
        Sunrise,
        Sunshine
    };

    SunlightController();
    SunlightController(const std::time_t sunriseStartTime,
                       const std::time_t sunriseLength,
                       const std::time_t sunshineStartTime,
                       const std::time_t sunshineLength);
    
    const State state() const;
    void run(std::time_t currentTime);

    void setSunriseStartTime(const u8 hours, const u8 minutes, const u8 seconds);
    void setSunshineStartTime(const u8 hours, const u8 minutes, const u8 seconds);
    void setSunriseLength(const std::time_t sunriseLength);
    void setSunshineLength(const std::time_t sunshineLength);

private:
    std::time_t getSeconds(int hour, int minute, int second);

    u8 sunriseStartHour_;
    u8 sunriseStartMinute_;
    u8 sunriseStartSecond_;
    std::time_t sunriseLength_;
    std::time_t sunriseStartTime_;

    u8 sunshineStartHour_;
    u8 sunshineStartMinute_;
    u8 sunshineStartSecond_;
    std::time_t sunshineStartTime_;
    std::time_t sunshineLength_;

    logger::Logger logger_;

    State state_;
};

} // namespace controller
